/*
 * Mark Benjamin 05 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_VALUE_ITERATION_VALUE_ITERATION_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_VALUE_ITERATION_VALUE_ITERATION_HPP

#include <iostream>
#include "../../../../policy/greedy_Q_policy.h"
#include "../../planner.hpp"
#include "../dynamic_programming.hpp"

//#define grid_world_state_debug(s, info) \
//    auto * gws = dynamic_cast<GridWorldState *>(s); \
//    if (gws != nullptr) { \
//        D(info << "State " << s << " id " << std::hex << s->id() << std::dec << " (" << gws->agent->x << "," << gws->agent->y << ")"); \
//    } else { \
//        D(info << "State " << s << " id " << std::hex << s->id() << std::dec << ((dynamic_cast<NullState *>(s) != nullptr) ?  "; NullS"  : "NGWS")); \
//    } \

class ValueIteration : public DynamicProgramming, public Planner {
public:
    double maxDelta;
    int maxIterations;
    bool foundReachableStates = false;
    bool stopReachabilityFromTerminalStates = false;
    bool hasRunVI = false;

    ValueIteration(SADomain * domain, double gamma, double max_delta, int max_iterations) {
        DPPInit(domain, gamma);
        maxDelta = max_delta;
        maxIterations = max_iterations;
    }

    void recomputeReachableStates() {
        foundReachableStates = false;
    }

    void setStopReachabilityTerminalStatePruning(bool newBool) {
        stopReachabilityFromTerminalStates = newBool;
    }

    GreedyQPolicy * planFromState(State * initialState) override {
        if (performReachabilityFrom(initialState) || !hasRunVI) {
            runVI();
        }
        return new GreedyQPolicy(this);
    }

    void resetSolver() override {
        DynamicProgramming::resetSolver();
        foundReachableStates = false;
        hasRunVI = false;
    }

    void runVI() {
        if(!foundReachableStates){
            throw runtime_error("ValueIteration::runVI() Cannot run VI until the reachable states have been found. Use the planFromState or performReachabilityFrom method at least once before calling runVI.");
        }
        set<State *> states;
        for (const auto &el : valueFunction) {
            states.insert(el.first);
        }
        int i;
        for (i = 0; i < maxIterations; i++) {
            D("Iteration " << i);
#ifdef DEBUG_FLAG
            print_grid_value_function();
#endif //DEBUG_FLAG
            double delta = 0.;
            for (State * sh : states) {
                double v = value(sh);
                double maxQ = performBellmanUpdateOn(sh);
                delta = max(abs(maxQ - v), delta);
            }
            if(delta < maxDelta){
                break; //approximated well enough; stop iterating
            }
        }
        D("Passes: " << i);
        hasRunVI = true;
    }

    bool performReachabilityFrom(State * si) {
        // todo check State operator== override for set membership
        //if this is not a new state and we are not required to perform a new reachability analysis, then this method does not need to do anything.
        if (!valueFunction.empty() && valueFunction.count(si) > 0 && foundReachableStates) {
            return false; //no need for additional reachability testing
        }
        D("Starting reachability analysis");
        //add to the open list
        queue<State *> openList = queue<State *>();
        unordered_set<State *, StateHashFunction, StateEqualFunction> openedSet;
        openList.push(si);
        openedSet.insert(si);
        while (!openList.empty()) {
            State * s = openList.front();
            openList.pop();
            //skip this if it's already been expanded
            if (!valueFunction.empty() && valueFunction.count(s) > 0) {
                continue;
            }
            //do not need to expand from terminal states if set to prune
            if (model->terminal(s) && stopReachabilityFromTerminalStates) {
                continue;
            }
            valueFunction[s] = valueInitializer->value(s);
            vector<Action *> actions = applicableActions(s);
            for (Action * a : actions) {
                vector<TransitionProb *> tps = dynamic_cast<FullModel *>(model)->transitions(s, a);
                State * ts;
                for (TransitionProb * tp : tps) {
                    ts = tp->eo->o_prime;
                    if (openedSet.count(ts) == 0 && valueFunction.count(ts) == 0) {
                        openedSet.insert(ts);
                        openList.push(ts);
                    }
                }
            }
        }
        D("Finished reachability analysis; # states: " << valueFunction.size());
        foundReachableStates = true;
        hasRunVI = false;
        return true;
    }
};


#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_VALUE_ITERATION_VALUE_ITERATION_HPP
