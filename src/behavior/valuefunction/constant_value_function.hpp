/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_VALUEFUNCTION_CONSTANT_VALUE_FUNCTION_HPP
#define FASTRL_BEHAVIOR_VALUEFUNCTION_CONSTANT_VALUE_FUNCTION_HPP

#include "Q_function.hpp"

class ConstantValueFunction : public QFunction {
public:
    double _value = 0.;
    explicit ConstantValueFunction(double val = -1) : _value(val) { }
    // todo check -1 value for consistency with code base
    double value(State *s) override { return _value; }
    double qValue(State *s, Action *a) override { return _value; }
};

#endif // FASTRL_BEHAVIOR_VALUEFUNCTION_CONSTANT_VALUE_FUNCTION_HPP