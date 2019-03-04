/*
 * Mark Benjamin 04 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_DETERMINISTIC_PLANNER_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_DETERMINISTIC_PLANNER_H

#include "../../../../mdp/auxiliary/stateconditiontest/state_condition_test.hpp"
#include "../../MDP_solver.hpp"
#include "../planner.hpp"
#include "search_node.hpp"

class DeterministicPlanner : public MDPSolver, public Planner {
public:
    StateConditionTest * goal_condition;
    map<State *, Action *> internal_policy;
    void deterministicPlannerInit(SADomain * domain, StateConditionTest * g_c);
    void resetSolver() override { internal_policy.clear(); }
    bool hasCachedPlanForState(State * s);
    Action * getSelectedActionForState(State * s);
    void encodePlanIntoPolicy(SearchNode * lastVisitedNode);
    bool planContainsOption(SearchNode * lastVisitedNode);
    bool planHasDuplicateStates(SearchNode * lastVisitedNode);
};


#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_DETERMINISTIC_PLANNER_H
