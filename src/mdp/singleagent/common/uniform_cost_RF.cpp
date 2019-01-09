#include "../model/reward_function.hpp"
#include "uniform_cost_RF.h"

/**
 * Mark Benjamin 31st May 2017
 */

UniformCostRF::UniformCostRF() = default;
double UniformCostRF::reward(State s, Action a, State s_prime) {
    return -1.;
}