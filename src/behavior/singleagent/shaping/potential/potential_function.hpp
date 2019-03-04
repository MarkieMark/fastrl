/*
 * Mark Benjamin 06 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_SHAPING_POTENTIAL_POTENTIAL_FUNCTION_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_SHAPING_POTENTIAL_POTENTIAL_FUNCTION_HPP

#include <stdexcept>
#include "../../../../mdp/core/state/state.hpp"

using namespace std;

class PotentialFunction {
public:
    virtual double potentialValue(State * s) {throw runtime_error("PotentialFunction::potentialValue() Not Implemented");}
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_SHAPING_POTENTIAL_POTENTIAL_FUNCTION_HPP
