#include "../../core/state/state.hpp"
#include "../../core/action/action.hpp"

/**
 * Mark Benjamin 30th May 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_MODEL_REWARD_FUNCTION_HPP
#define FASTRL_MDP_SINGLEAGENT_MODEL_REWARD_FUNCTION_HPP

class RewardFunction {
public:
    virtual double reward(State * s, Action * a, State * s_prime) { throw runtime_error("Not Implemented"); }
};

#endif // FASTRL_MDP_SINGLEAGENT_MODEL_REWARD_FUNCTION_HPP