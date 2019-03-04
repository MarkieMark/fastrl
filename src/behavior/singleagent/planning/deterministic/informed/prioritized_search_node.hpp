/*
 * Mark Benjamin 05 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_PRIORITIZED_SEARCH_NODE_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_PRIORITIZED_SEARCH_NODE_HPP

#include "../search_node.hpp"

class PrioritizedSearchNode : public SearchNode {
public:
    double priority;

    PrioritizedSearchNode(State * s, double p) : SearchNode(s) {
        priority = p;
    }
    PrioritizedSearchNode(State * s, Action * ga, SearchNode * bp, double p) : SearchNode(s, ga, bp) {
        priority = p;
    }
    // todo equality / comparison operators; for priority_queue particularly
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_PRIORITIZED_SEARCH_NODE_HPP
