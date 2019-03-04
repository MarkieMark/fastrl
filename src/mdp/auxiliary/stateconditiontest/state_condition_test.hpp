/*
 * Mark Benjamin 4th March 2019
 * (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_MDP_AUXILIARY_STATE_CONDITION_TEST_STATE_CONDITION_TEST_HPP
#define FASTRL_MDP_AUXILIARY_STATE_CONDITION_TEST_STATE_CONDITION_TEST_HPP

#include "../../core/state/state.hpp"

class StateConditionTest {
public:
    virtual bool satisfies(State * s) {throw runtime_error("StateConditionTest::satisfies() Not Implemented");}
};

#endif //FASTRL_MDP_AUXILIARY_STATE_CONDITION_TEST_STATE_CONDITION_TEST_HPP