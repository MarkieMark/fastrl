/*
 * Mark Benjamin 06 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_POLICYITERATION_POLICY_ITERATION_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_POLICYITERATION_POLICY_ITERATION_H

#include <iostream>
#include <queue>
#include <set>
#include <limits>
#include "../../../../../include/macros.h"
#include "../../../../policy/greedy_Q_policy.h"
#include "../../planner.hpp"
#include "../dynamic_programming.hpp"

class PolicyIteration : public DynamicProgramming, public Planner {
public:
    double maxEvalDelta;
    double maxPIDelta;
    int maxIterations;
    int maxPolicyIterations;
    EnumerablePolicy * evaluativePolicy;
    bool foundReachableStates = false;
    int totalPolicyIterations = 0;
    int totalValueIterations = 0;
    bool hasRunPlanning = false;

    PolicyIteration(SADomain * domain, double gamma, double max_delta, int max_evaluation_iterations,
            int max_policy_iterations) {
        DPPInit(domain, gamma);
        maxEvalDelta = max_delta;
        maxPIDelta = max_delta;
        maxIterations = max_evaluation_iterations;
        maxPolicyIterations = max_policy_iterations;
        evaluativePolicy = new GreedyQPolicy(getCopyOfValueFunction());
    }

    PolicyIteration(SADomain * domain, double gamma, double max_p_i_delta, double max_eval_delta,
            int max_evaluation_iterations, int max_policy_iterations) {
        DPPInit(domain, gamma);
        maxEvalDelta = max_eval_delta;
        maxPIDelta = max_p_i_delta;
        maxIterations = max_evaluation_iterations;
        maxPolicyIterations = max_policy_iterations;
        evaluativePolicy = new GreedyQPolicy(getCopyOfValueFunction());
    }

    void setPolicyToEvaluate(EnumerablePolicy * p) {
        evaluativePolicy = p;
    }

    Policy * getComputedPolicy() {
        return evaluativePolicy;
    }

    void recomputeReachableStates(){
        foundReachableStates = false;
    }

    int getTotalPolicyIterations() {
        return totalPolicyIterations;
    }

    int getTotalValueIterations() {
        return totalValueIterations;
    }

    GreedyQPolicy * planFromState(State * initialState) override {
        int iterations = 0;
        if (performReachabilityFrom(initialState) || !hasRunPlanning) {
            double delta;
            do {
                delta = evaluatePolicy();
                iterations++;
                evaluativePolicy = new GreedyQPolicy(getCopyOfValueFunction());
            } while (delta > maxPIDelta && iterations < maxPolicyIterations);
            hasRunPlanning = true;
        }
        D("Total policy iterations: " << iterations);
        totalPolicyIterations += iterations;
        return dynamic_cast<GreedyQPolicy *>(evaluativePolicy);
    }

    void resetSolver() override {
        DynamicProgramming::resetSolver();
        foundReachableStates = false;
        totalValueIterations = 0;
        totalPolicyIterations = 0;
    }

    double evaluatePolicy() {
        if(!foundReachableStates) {
            throw runtime_error("PolicyIteration::evaluatePolicy() Cannot run VI until the reachable states have been found. Use planFromState method at least once or instead.");
        }
        double maxChangeInPolicyEvaluation = -numeric_limits<double>::infinity();
        set<State *> states;
        for (const auto &p : valueFunction) {
            states.insert(p.first);
        }
        int i;
        for (i = 0; i < maxIterations; i++) {
            double delta = 0.;
            for(State * s : states) {
                double v = value(s);
                double maxQ = performFixedPolicyBellmanUpdateOn(s, evaluativePolicy);
                delta = max(abs(maxQ - v), delta);
            }
            maxChangeInPolicyEvaluation = max(delta, maxChangeInPolicyEvaluation);
            if (delta < maxEvalDelta) {
                i++;
                break; //approximated well enough; stop iterating
            }
        }
        D("Iterations in inner VI for policy eval: " << i);
        totalValueIterations += i;
        return maxChangeInPolicyEvaluation;
    }

    bool performReachabilityFrom(State * si) {
        //if this is not a new state and we are not required to perform a new reachability analysis, then this method does not need to do anything.
        if (valueFunction.count(si) > 0 && foundReachableStates) {
            return false; //no need for additional reachability testing
        }
        D("Starting reachability analysis");
        //add to the open list
        queue<State *> openList = queue<State *>();
        set<State *> openedSet = set<State *>();
        openList.push(si);
        openedSet.insert(si);
        while (!openList.empty()) {
            State * s = openList.front();
            openList.pop();
            //skip this if it's already been expanded
            if (valueFunction.find(s) != valueFunction.end()) {
                continue;
            }
            //do not need to expand from terminal states
            if (model->terminal(s)) {
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
        foundReachableStates = true;
        return true;
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_POLICYITERATION_POLICY_ITERATION_H
