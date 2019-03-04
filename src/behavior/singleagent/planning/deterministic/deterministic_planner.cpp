/*
 * Mark Benjamin 04 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include <set>
#include "deterministic_planner.h"
#include "../../options/option.h"

void DeterministicPlanner::deterministicPlannerInit(SADomain * domain, StateConditionTest * g_c) {
    solverInit(domain, 1.); //goal condition doubles as termination function for deterministic planners
    goal_condition = g_c;
    internal_policy = map<State *, Action *>();
}

bool DeterministicPlanner::hasCachedPlanForState(State * s) {
    return internal_policy.find(s) != internal_policy.end();
}

Action * DeterministicPlanner::getSelectedActionForState(State * s) {
    Action * res = internal_policy.find(s)->second;
    if(res == nullptr){
        planFromState(s);
        res = internal_policy.find(s)->second;
    }
    return res;
}

void DeterministicPlanner::encodePlanIntoPolicy(SearchNode * lastVisitedNode){
    if(lastVisitedNode == nullptr) {
        throw runtime_error("DeterministicPlanner::encodePlanIntoPolicy() Planning failed to locate the goal state");
    }
    SearchNode * current_node = lastVisitedNode;
    while(current_node->backPointer != nullptr) {
        State * bps = current_node->backPointer->s;
        if(internal_policy.find(bps) == internal_policy.end()) { //makes sure earlier plan duplicate nodes do not replace the correct later visits
            internal_policy.insert(pair<State *, Action *>(bps, current_node->generatingAction));
        }
        current_node = current_node->backPointer;
    }
}

bool DeterministicPlanner::planContainsOption(SearchNode * lastVisitedNode){
    if (lastVisitedNode == nullptr) {
        return false;
    }
    SearchNode * current_node = lastVisitedNode;
    while(current_node->backPointer != nullptr){
        if(dynamic_cast<Option *>(current_node->generatingAction) != nullptr){
            return true;
        }
        current_node = current_node->backPointer;
    }
    return false;
}

bool DeterministicPlanner::planHasDuplicateStates(SearchNode * lastVisitedNode){

    set<State *> statesInPlan = set<State *>();
    SearchNode * current_node = lastVisitedNode;
    while(current_node->backPointer != nullptr) {
        if(statesInPlan.find(current_node->s) != statesInPlan.end()) {
            return true;
        }
        statesInPlan.insert(current_node->s);
        current_node = current_node->backPointer;
    }
    return false;
}

