/*
 * Mark Benjamin 06 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_SHAPING_SHAPED_REWARD_FUNCTION_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_SHAPING_SHAPED_REWARD_FUNCTION_HPP

#include "../../../mdp/singleagent/model/reward_function.hpp"

class ShapedRewardFunction : public RewardFunction {
public:
    RewardFunction * baseRF;
    virtual double additiveReward(State * s, Action * a, State * s_prime) {throw runtime_error("ShapedRewardFunction::additiveReward() Not Implemented");}
    explicit ShapedRewardFunction(RewardFunction * base_r_f) {
            baseRF = base_r_f;
        }

    double reward(State * s, Action * a, State * s_prime) override {
            return baseRF->reward(s, a, s_prime) + additiveReward(s, a, s_prime);
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_SHAPING_SHAPED_REWARD_FUNCTION_HPP
