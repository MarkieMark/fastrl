/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_CORE_STATE_MUTABLE_STATE_HPP
#define FASTRL_MDP_CORE_STATE_MUTABLE_STATE_HPP

#include "state.hpp"

class MutableState : virtual public State {
public:
    virtual MutableState * set(KeyContainer * variableKey, void *value) { throw runtime_error("Not Implemented"); }
};

#endif // FASTRL_MDP_CORE_STATE_MUTABLE_STATE_HPP