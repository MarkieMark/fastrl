/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_VALUEFUNCTION_Q_VALUE_HPP
#define FASTRL_BEHAVIOR_VALUEFUNCTION_Q_VALUE_HPP

#include "../../mdp/core/state/state.hpp"
#include "../../mdp/core/action/action.hpp"

class QValue {
public:
    State * s = nullptr;
    Action * a = nullptr;
    double q = 0.;
    QValue() = default;
    QValue(State * s_, Action * a_, double q_) : s(s_), a(a_), q(q_) { }
    explicit QValue(QValue * src) : s(src->s->makeCopy()) , a(src->a->makeCopy()), q(src->q) { }
};

#endif // FASTRL_BEHAVIOR_VALUEFUNCTION_Q_VALUE_HPP
