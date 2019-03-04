/*
 * Mark Benjamin 4th March 2019
 * (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_MDP_AUXILIARY_STATE_CONDITION_TEST_TF_GOAL_CONDITION_HPP
#define FASTRL_MDP_AUXILIARY_STATE_CONDITION_TEST_TF_GOAL_CONDITION_HPP

#include "state_condition_test.hpp"
#include "../../core/terminal_function.hpp"

class TFGoalCondition : public StateConditionTest {
public:
    TerminalFunction * tf;
    explicit TFGoalCondition(TerminalFunction * tf_) : tf(tf_) { }
    TerminalFunction * getTf() { return tf; }
    void setTf(TerminalFunction * tf_) { tf = tf; }
    bool satisfies(State * s) override {return tf->isTerminal(s); }
};

#endif //FASTRL_MDP_AUXILIARY_STATE_CONDITION_TEST_TF_GOAL_CONDITION_HPP