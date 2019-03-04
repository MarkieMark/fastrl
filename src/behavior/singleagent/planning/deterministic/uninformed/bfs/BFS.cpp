/*
 * Mark Benjamin 04 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include <set>
#include <queue>
#include <iostream>
#include "BFS.h"
#include "../../../../../../include/macros.h"

SDPlannerPolicy * BFS::planFromState(State * initialState) {
    if (internal_policy.find(initialState) != internal_policy.end()) {
        return new SDPlannerPolicy(this);
    }
    queue<SearchNode *> openQueue = queue<SearchNode *>();
    set<SearchNode *> openedSet = set<SearchNode *>();
    auto * initialSearchNode = new SearchNode(initialState);
    openQueue.push(initialSearchNode);
    openedSet.insert(initialSearchNode);
    // todo check equality test
    SearchNode * lastVisitedNode = nullptr;
    int nExpanded = 0;
    while (!openQueue.empty()) {
        SearchNode * node = openQueue.front();
        openQueue.pop();
        nExpanded++;
        State * s = node->s;
        if (goal_condition->satisfies(s)) {
            lastVisitedNode = node;
            break;
        }
        if (model->terminal(s)) {
            continue; //don't expand terminal states
        }
        //first get all grounded actions for this state
        vector<Action *> gas = ActionUtils::allApplicableActionsForTypes(actionTypes, s);
        //add children reach from each deterministic action
        for(Action * ga : gas){
            State * ns = model->sample(s, ga)->o_prime;
            auto * nsn = new SearchNode(ns, ga, node);
            if (openedSet.find(nsn) != openedSet.end()) {
                continue;
            }
            //otherwise add for expansion
            openQueue.push(nsn);
            openedSet.insert(nsn);
        }
    }
    encodePlanIntoPolicy(lastVisitedNode);
    D("BFS number of nodes " << nExpanded);
    return new SDPlannerPolicy(this);
}
