/*
 * Mark Benjamin 05 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include <iostream>
#include "best_first.h"
#include "../../../../../include/macros.h"

SDPlannerPolicy * BestFirst::planFromState(State * initialState) {
    //first see whether to plan
    if (internal_policy.find(initialState) != internal_policy.end()) {
        return new SDPlannerPolicy(this); //no need to plan; already solved
    }
    //a plan is not cached so being planning process
    prePlanPrep();
    priority_queue<PrioritizedSearchNode *> openQueue = priority_queue<PrioritizedSearchNode *>(/*new PrioritizedSearchNode::PSNComparator()*/);
    map<SearchNode *, double> openPriority = map<SearchNode *, double>();
    map<PrioritizedSearchNode *, PrioritizedSearchNode *> closedSet = map<PrioritizedSearchNode *,PrioritizedSearchNode *>();
    auto * ipn = new PrioritizedSearchNode(initialState, computeF(nullptr, nullptr, initialState, 0.));
    insertIntoOpen(openQueue, ipn);
    openPriority.insert(pair<SearchNode *, double>(dynamic_cast<SearchNode *>(ipn), ipn->priority));
    int nExpanded = 0;
    PrioritizedSearchNode * lastVisitedNode = nullptr;
    double minF = ipn->priority;
    while (!openQueue.empty()) {
        PrioritizedSearchNode * node = openQueue.top();
        openQueue.pop();
        openPriority.erase(dynamic_cast<SearchNode *>(node));
        closedSet.insert(pair<PrioritizedSearchNode *, PrioritizedSearchNode *>(node, node));
        nExpanded++;
        if (node->priority < minF) {
            minF = node->priority;
            D("Min F Expanded: " << minF << "; Nodes expanded so far: " << nExpanded << "; Open size: " << openQueue.size());
        }
        State * s = node->s;
        if (goal_condition->satisfies(s)) {
            lastVisitedNode = node;
            break;
        }
        if (model->terminal(s)) {
            continue; //do not expand nodes from a terminal state
        }
        //generate successors
        for(ActionType * a : actionTypes){
            //List<GroundedAction> gas = s.getAllGroundedActionsFor(a);
            vector<Action *> gas = a->allApplicableActions(s);
            for(Action * ga : gas){
                EnvironmentOutcome * eo = model->sample(s, ga);
                State * ns = eo->o_prime;
                double F = computeF(node, ga, ns, eo->reward);
                auto * npn = new PrioritizedSearchNode(ns, ga, node, F);
                //check closed
                PrioritizedSearchNode * closedPSN = closedSet.find(npn)->second;
                if (closedPSN != nullptr && F <= closedPSN->priority) {
                    continue; //no need to reopen; current path is a worse path to an already explored node
                }
                //check open
                auto it = openPriority.find(dynamic_cast<SearchNode *>(npn));
                if (it == openPriority.end()) {
                    insertIntoOpen(openQueue, npn);
                } else if (F > it->second) {
                    // adjust new priority value
                    // todo double check time for adding to heap; may need to make stack, reverse, then add to heap
                    auto newQueue = priority_queue<PrioritizedSearchNode *>();
                    while (!openQueue.empty()) {
                        auto * the_node = openQueue.top();
                        openQueue.pop();
                        if (dynamic_cast<SearchNode *>(the_node) != dynamic_cast<SearchNode *>(npn)) {
                            newQueue.push(the_node);
                        }
                    }
                    newQueue.push(npn);
                    openQueue = newQueue;
                }
            }
        }
    }
    //search to goal complete. Now follow back pointers to set policy
    encodePlanIntoPolicy(lastVisitedNode);
    D("Num Expanded: " << nExpanded);
    postPlanPrep();
    return new SDPlannerPolicy(this);
}
