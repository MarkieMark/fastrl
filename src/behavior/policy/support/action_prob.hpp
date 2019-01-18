/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_POLICY_SUPPORT_ACTION_PROB_HPP
#define FASTRL_BEHAVIOR_POLICY_SUPPORT_ACTION_PROB_HPP

#include <sstream>
#include "../../../mdp/core/action/action.hpp"

class ActionProb {
public:
    Action * pa;
    double pSelection;
    explicit ActionProb(Action * a_ = nullptr, double p = -1.) {
        pa = a_;
        pSelection = p;
    }
    string to_string() {
        stringstream s;
        s << pSelection << ": " << pa/*->to_string()*/; // TODO Action may need to_string() method
        return s.str();
    }
};

#endif // FASTRL_BEHAVIOR_POLICY_SUPPORT_ACTION_PROB_HPP