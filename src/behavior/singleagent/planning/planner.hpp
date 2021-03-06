/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_PLANNER_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_PLANNER_HPP

#include "../../../mdp/core/state/state.hpp"
#include "../../policy/policy.hpp"

class Planner {
public:
    virtual Policy * planFromState(State * initialState) { throw runtime_error("Planner::planFromState() Not Implemented"); }
};

#endif // FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_PLANNER_HPP