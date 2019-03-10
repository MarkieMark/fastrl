/*
 * Mark Benjamin 05 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_DYNAMIC_PROGRAMMING_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_DYNAMIC_PROGRAMMING_H

#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include "../../../../domain/singleagent/gridworld/grid_world_domain.h"
#include "../../../../mdp/singleagent/model/transition_prob.hpp"
#include "../../../../mdp/singleagent/model/full_model.h"
#include "../../../valuefunction/Q_provider.h"
#include "../../../valuefunction/value_function.hpp"
#include "../../../valuefunction/constant_value_function.hpp"
#include "../../../policy/policy_utils.h"
#include "../../options/option.h"
#include "../../MDP_solver.hpp"
#include "dpoperator/DP_operator.hpp"
#include "dpoperator/bellman_operator.hpp"

class DynamicProgramming : public MDPSolver, /*public ValueFunction,*/ public QProvider {
public:
    unordered_map<State *, double, StateHashFunction, StateEqualFunction> valueFunction;
    ValueFunction * valueInitializer = new ConstantValueFunction();
    DPOperator * oper = new BellmanOperator();

    void DPPInit(SADomain * domain, double gamma) {
        solverInit(domain, gamma);
    }

    SampleModel * getModel() override {
        return model;
    }

    void resetSolver() override {
        valueFunction.erase(valueFunction.begin(), valueFunction.end());
    }

    void setValueFunctionInitialization(ValueFunction * vfInit) {
        valueInitializer = vfInit;
    }

    ValueFunction * getValueFunctionInitialization() {
        return valueInitializer;
    }

    DPOperator * getOperator() {
        return oper;
    }

    void setOperator(DPOperator * op) {
        oper = op;
    }

    bool hasComputedValueFor(State * s) {
        return valueFunction.count(s) > 0;
    }

    double value(State * s) override {
        if (model->terminal(s)) {
            return 0.;
        }
        auto it = valueFunction.find(s);
        return it == valueFunction.end() ? getDefaultValue(s) : it->second;
    }

    vector<QValue *> qValues(State * s) override {
        vector<Action *> gas = applicableActions(s);
        vector<QValue *> qs = vector<QValue *>();
        for(Action * ga : gas){
            auto * q = new QValue(s, ga, qValue(s, ga));
            qs.push_back(q);
        }
        return qs;
    }

    double qValue(State * s, Action * a) override {
        double dq = computeQ(s, a);
        return dq;
    }

    vector<State *> getAllStates() {
        vector<State *> result = vector<State *>();
        set<State *> shs;
        for (auto p : valueFunction) {
            shs.insert(p.first);
        }
        for(State * sh : shs){
            result.push_back(sh);
        }
        return result;
    }

    DynamicProgramming * getCopyOfValueFunction() {
        auto * dpCopy = new DynamicProgramming();
        dpCopy->DPPInit(domain, gamma);
        //copy the value function
        for(auto e : valueFunction) {
            dpCopy->valueFunction[e.first] = e.second;
        }
        return dpCopy;
    }

    double performBellmanUpdateOn(State * s) {
        if(model->terminal(s)) {
            //terminal states always have a state value of 0
            valueFunction[s] = 0.;
            return 0.;
        }
        vector<Action *> gas = applicableActions(s);
        vector<double> qs = vector<double>();
        for(Action * ga : gas){
            double q = computeQ(s, ga);
            qs.push_back(q);
        }
        double nv = oper->apply(qs);
        valueFunction[s] = nv;
        return nv;
    }


    double performFixedPolicyBellmanUpdateOn(State * s, EnumerablePolicy * p) {
        if (model->terminal(s)) {
            //terminal states always have a state value of 0
            valueFunction[s] = 0.;
            return 0.;
        }
        double weightedQ = 0.;
        vector<ActionProb *> policyDistribution = p->policyDistribution(s);
        //List <GroundedAction> gas = sh.s.getAllGroundedActionsFor(this.actions);
        vector<Action *> gas = applicableActions(s);
        for(Action * ga : gas){
            double policyProb = PolicyUtils::actionProbFromDistribution(ga, policyDistribution);
            if(policyProb == 0.){
                continue; //doesn't contribute
            }
            double q = computeQ(s, ga);
            weightedQ += policyProb * q;
        }
        valueFunction[s] = weightedQ;
        return weightedQ;
    }

    double computeQ(State * s, Action * ga) {
        double q = 0.;
        vector<TransitionProb *> tps = dynamic_cast<FullModel *>(model)->transitions(s, ga);
        if (dynamic_cast<Option *>(ga) != nullptr) {
            //for options, expected reward is on state-action level and always the same, so only add it once
            q += tps[0]->eo->reward;
            for(TransitionProb * tp : tps){
                double vp = value(tp->eo->o_prime);
                //note that for options, tp.p will be the *discounted* probability of transition to s',
                //so there is no need for a discount factor to be included
                q += tp->p * vp;
            }
        } else {
            for (TransitionProb * tp : tps) {
                double vp = value(tp->eo->o_prime);
                double discount = gamma;
                double r = tp->eo->reward;
                q += tp->p * (r + (discount * vp));
            }
        }
        return q;
    }

    double getDefaultValue(State * s) {
        return valueInitializer->value(s);
    }

    void print_grid_value_function() {
//        D(model);
        if (dynamic_cast<FactoredModel *>(model) != nullptr &&
                dynamic_cast<GridWorldModel *>(dynamic_cast<FactoredModel *>(model)->getStateModel()) != nullptr) {
            auto gwm = dynamic_cast<GridWorldModel *>(dynamic_cast<FactoredModel *>(model)->getStateModel());
            vector<vector<unsigned int>> map = gwm->map;
            unsigned long d1 = map.size();
            unsigned long d2 = map[0].size();
//            D("map dimensions " << d1 << ", " <<  d2);
            vector<vector<double>> value_map;
            int i, j;
            for (i = 0; i < d1; i++) {
                value_map.emplace_back(vector<double>(d2));
                for (j = 0; j < d2; j++) {
                    value_map[i][j] = 0.;
                }
            }
//            D("Value Function " << valueFunction.size());
            for (auto p : valueFunction) {
                State * s = p.first;
                if (dynamic_cast<GridWorldState *>(s) != nullptr) {
                    auto * gws = dynamic_cast<GridWorldState *>(s);
//                    D(s << ":" << gws->agent->x << "," << gws->agent->y);
                    value_map[gws->agent->y][gws->agent->x] = p.second;
                } else {
//                    D("non gridworld State " << s);
                }
            }
            for (j = 0; j < d2; j++) {
                for (i = 0; i < d1; i++) {
                    cout << setw(7) << setprecision(4) << value_map[d2 - j - 1][i] << " ";
                }
                cout << endl;
            }
        }
    }

};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_DYNAMIC_PROGRAMMING_H
