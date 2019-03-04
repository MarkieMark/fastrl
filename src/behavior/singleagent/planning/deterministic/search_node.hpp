/*
 * Mark Benjamin 4th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_SEARCH_NODE_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_SEARCH_NODE_HPP

#include "../../../../mdp/core/state/state.hpp"
#include "../../../../mdp/core/action/action.hpp"

class SearchNode {
public:
    State * s;
    Action * generatingAction;
    SearchNode * backPointer;
    explicit SearchNode(State * s_, Action * ga = nullptr, SearchNode * bp = nullptr)
    : s(s_), generatingAction(ga), backPointer(bp) { }

    //todo equality test is whether state s is equal
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_SEARCH_NODE_HPP