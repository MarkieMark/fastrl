/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_VALUEFUNCTION_VALUE_FUNCTION_HPP
#define FASTRL_BEHAVIOR_VALUEFUNCTION_VALUE_FUNCTION_HPP

#include "../../mdp/core/state/state.hpp"

class ValueFunction {
public:
    virtual double value(State *s) { throw runtime_error("ValueFunction::value() Not Implemented"); }
};

#endif // FASTRL_BEHAVIOR_VALUEFUNCTION_VALUE_FUNCTION_HPP