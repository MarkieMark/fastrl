//
// Mark Benjamin 6/1/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_BEHAVIOR_VALUEFUNCTION_Q_PROVIDER_H
#define FASTRL_BEHAVIOR_VALUEFUNCTION_Q_PROVIDER_H

#include "Q_function.hpp"
#include "../policy/enumerable_policy.hpp"
#include "Q_value.hpp"

class QProvider : public QFunction {
public:
    virtual vector<QValue *> qValues(State *s) { throw runtime_error("Not Implemented"); }
};

class QProviderHelper {
private:
    QProviderHelper() = default;
public:
    static double maxQ(QProvider * qSource, State *s);
    static double policyValue(QProvider * qSource, State *s, EnumerablePolicy * p);
};

#endif // FASTRL_BEHAVIOR_VALUEFUNCTION_Q_PROVIDER_H
