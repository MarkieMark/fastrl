/*
 * Mark Benjamin 06 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include "../dynamic_programming.hpp"
#include "../../../../../include/macros.h"

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_POLICYITERATION_POLICY_EVALUATION_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_POLICYITERATION_POLICY_EVALUATION_HPP


class PolicyEvaluation : public DynamicProgramming {
public:
    double maxEvalDelta;
    double maxEvalIterations;

    PolicyEvaluation(SADomain * domain, double gamma, double max_eval_delta, double max_eval_iterations) {
        DPPInit(domain, gamma);
        maxEvalDelta = max_eval_delta;
        maxEvalIterations = max_eval_iterations;
    }

    void evaluatePolicy(EnumerablePolicy * policy, State * s) {
        performReachabilityFrom(s);
        evaluatePolicy(policy);
    }

    void evaluatePolicy(EnumerablePolicy * policy) {
        if (valueFunction.empty()) {
        throw runtime_error("PolicyEvaluation::evaluatePolicy() Cannot evaluate policy, because no"
                            " states have been expanded. Use the performStateReachability method "
                            "or call the evaluatePolicy method that takes a seed initial state as input.");
        }
        double maxChangeInPolicyEvaluation = -numeric_limits<double>::infinity();

        set<State *> states;
        for (const auto &p : valueFunction) {
            states.insert(p.first);
        }
        int i;
        for (i = 0; i < maxEvalIterations; i++) {
            double delta = 0.;
            for (State * s : states) {
                double v = value(s);
                double maxQ = performFixedPolicyBellmanUpdateOn(s, policy);
                delta = max(abs(maxQ - v), delta);
            }
            maxChangeInPolicyEvaluation = max(delta, maxChangeInPolicyEvaluation);
            if (delta < maxEvalDelta) {
                i++;
                break; //approximated well enough; stop iterating
            }
        }
    }

    bool performReachabilityFrom(State * si) {
        //if this is not a new state and we are not required to perform a new reachability analysis, then this method does not need to do anything.
        if (valueFunction.count(si) > 0) {
            return false; //no need for additional reachability testing
        }
        D("Starting reachability analysis");

        //add to the open list
        // todo double check queue semantics should be FIFO not stack LIFO
        queue<State *> openList = queue<State *>();
        set<State *> openedSet = set<State *>();
        openList.push(si);
        openedSet.insert(si);
        while (!openList.empty()) {
            State * s = openList.front();
            openList.pop();
            //skip this if it's already been expanded
            if (valueFunction.count(s) > 0) {
                continue;
            }
            //do not need to expand from terminal states
            if(model->terminal(s)) {
                continue;
            }
            valueFunction[s] = valueInitializer->value(s);
            vector<Action *> actions = applicableActions(s);
            for (Action * a : actions) {
                vector<TransitionProb *> tps = dynamic_cast<FullModel *>(model)->transitions(s, a);
                for (TransitionProb * tp : tps) {
                    State * ts = tp->eo->o_prime;
                    if (openedSet.count(ts) == 0 && valueFunction.count(ts) == 0) {
                        openedSet.insert(ts);
                        openList.push(ts);
                    }
                }
            }
        }
        D("Finished reachability analysis; # states: " << valueFunction.size());
        return true;
    }

};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_POLICYITERATION_POLICY_EVALUATION_HPP
