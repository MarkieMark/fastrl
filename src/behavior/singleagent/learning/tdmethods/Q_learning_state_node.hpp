/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_TDMETHODS_Q_LEARNING_STATE_NODE_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_TDMETHODS_Q_LEARNING_STATE_NODE_HPP

#include "../../../../mdp/core/state/state.hpp"
#include "../../../valuefunction/Q_value.hpp"

class QLearningStateNode {
public:
    /*Hashable*/State * s = nullptr;
    vector<QValue *> qEntry;
    QLearningStateNode() = default;

    explicit QLearningStateNode(/*Hashable*/State *s_) : s(s_), qEntry(vector<QValue *>()) { }
    void addQValue(Action *a, double q) {
        auto * qv = new QValue(s/*->s()*/, a, q);
        qEntry.push_back(qv);
    }
};

#endif // FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_TDMETHODS_Q_LEARNING_STATE_NODE_HPP
