/*
 * Mark Benjamin 05 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_BEST_FIRST_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_BEST_FIRST_H

#include <queue>
#include "../deterministic_planner.h"
#include "prioritized_search_node.hpp"
#include "../SD_planner_policy.h"

class BestFirst : public DeterministicPlanner {
public:
    virtual double computeF(PrioritizedSearchNode * parentNode, Action * generatingAction,
            State * successorState, double r) {
        throw runtime_error("BestFirst::computeF() Not Implemented");
    }
    virtual void prePlanPrep() { }
    virtual void postPlanPrep() { }
    virtual void insertIntoOpen(priority_queue<PrioritizedSearchNode *> &openQueue, PrioritizedSearchNode * psn) {
        // todo PrioritizedSearchNode needs relevant comparison
        openQueue.push(psn);
    }
    virtual void updateOpen(priority_queue<PrioritizedSearchNode* > &openQueue, PrioritizedSearchNode * openPSN,
            PrioritizedSearchNode * psn) {
        // todo add relevant ability
//        openPSN->setAuxInfoTo(psn);
//        openQueue.refreshPriority(openPSN);
    }

    SDPlannerPolicy * planFromState(State * initialState) override;
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_BEST_FIRST_H
