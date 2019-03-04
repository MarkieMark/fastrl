/*
 * Mark Benjamin 04 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_UNINFORMED_DFS_DFS_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_UNINFORMED_DFS_DFS_H

#include <set>
#include "../../SD_planner_policy.h"
#include "../../deterministic_planner.h"

class DFS : public DeterministicPlanner {
public:
    int maxDepth;
    bool maintainClosed;
    bool optionsFirst;
//    Random rand;
    int numVisited;

    DFS(SADomain * domain, StateConditionTest * gc, int maxDepth = -1,
            bool maintainClosed = false, bool optionsFirst = false);

    int getNumVisited() { return numVisited; }
    SDPlannerPolicy * planFromState(State * initialState) override;
    void resetSolver() override;
    SearchNode * dfs(SearchNode * n, int depth, set<State *> statesOnPath);
    void setOptionsFirst();
    int numOptionsInGAs(vector<Action *> gas);
    void shuffleGroundedActions(vector<Action *> gas, int s, int e);
    void sortActionsWithOptionsFirst();
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_UNINFORMED_DFS_DFS_H
