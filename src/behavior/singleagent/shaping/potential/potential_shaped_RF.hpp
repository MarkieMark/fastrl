/*
 * Mark Benjamin 06 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_SHAPING_POTENTIAL_POTENTIAL_SHAPED_RF_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_SHAPING_POTENTIAL_POTENTIAL_SHAPED_RF_HPP

#include "../shaped_reward_function.hpp"
#include "../../../../mdp/singleagent/model/reward_function.hpp"
#include "potential_function.hpp"

class PotentialShapedRF : public ShapedRewardFunction {
public:
    PotentialFunction * potentialFunction;
    double discount;

    PotentialShapedRF(RewardFunction * baseRF, PotentialFunction * potential_function, double disc)
        : ShapedRewardFunction(baseRF) {
        potentialFunction = potential_function;
        discount = disc;
    }

    double additiveReward(State * s, Action * a, State * s_prime) override {
        return (discount * potentialFunction->potentialValue(s_prime)) - potentialFunction->potentialValue(s);
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_SHAPING_POTENTIAL_POTENTIAL_SHAPED_RF_HPP
