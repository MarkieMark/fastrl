/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_MDP_AUXILIARY_STATE_GENERATOR_HPP
#define FASTRL_MDP_AUXILIARY_STATE_GENERATOR_HPP

#include "../core/state/state.hpp"

class StateGenerator {
public:
    virtual State * generateState() { throw runtime_error("Not Implemented"); }
};

#endif // FASTRL_MDP_AUXILIARY_STATE_GENERATOR_HPP