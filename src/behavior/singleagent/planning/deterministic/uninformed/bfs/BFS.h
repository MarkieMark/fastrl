/*
 * Mark Benjamin 04 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_UNINFORMED_BFS_BFS_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_UNINFORMED_BFS_BFS_H

#include "../../deterministic_planner.h"
#include "../../SD_planner_policy.h"

class BFS : public DeterministicPlanner {
public:
    BFS(SADomain * domain, StateConditionTest * gc) { DeterministicPlanner::deterministicPlannerInit(domain, gc); }
    SDPlannerPolicy * planFromState(State * initialState) override;
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_UNINFORMED_BFS_BFS_H
