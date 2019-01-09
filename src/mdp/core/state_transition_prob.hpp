/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_CORE_STATE_TRANSITION_PROB_HPP
#define FASTRL_MDP_CORE_STATE_TRANSITION_PROB_HPP

#include "state/state.hpp"

class StateTransitionProb {
public:
    State * s;
    double p;
    StateTransitionProb() = default;
    StateTransitionProb(State * s_, double p_) : s(s_), p(p_) { }
};

#endif // FASTRL_MDP_CORE_STATE_TRANSITION_PROB_HPP