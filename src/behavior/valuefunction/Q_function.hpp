//
// Mark Benjamin 6/1/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_BEHAVIOR_VALUEFUNCTION_Q_FUNCTION_HPP
#define FASTRL_BEHAVIOR_VALUEFUNCTION_Q_FUNCTION_HPP

#include "../../mdp/core/state/state.hpp"
#include "../../mdp/core/action/action.hpp"
#include "value_function.hpp"

class QFunction : public ValueFunction {
public:
    virtual double qValue(State * s, Action * a) { throw runtime_error("QFunction::qValue() Not Implemented"); }
};

#endif // FASTRL_BEHAVIOR_VALUEFUNCTION_Q_FUNCTION_HPP