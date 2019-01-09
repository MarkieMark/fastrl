//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_MDP_SINGLEAGENT_COMMON_UNIFORM_COST_RF_H
#define FASTRL_MDP_SINGLEAGENT_COMMON_UNIFORM_COST_RF_H

#include "../model/reward_function.hpp"

class UniformCostRF : public RewardFunction {
public:
    UniformCostRF();
    double reward(State s, Action a, State s_prime);
};

#endif // FASTRL_MDP_SINGLEAGENT_COMMON_UNIFORM_COST_RF_H
