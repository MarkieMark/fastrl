/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_POLICY_POLICY_HPP
#define FASTRL_BEHAVIOR_POLICY_POLICY_HPP

#include "../../mdp/core/state/state.hpp"
#include "../../mdp/core/action/action.hpp"

class Policy {
public:
    virtual Action * action(State *s) { throw runtime_error("Not Implemented"); }
    virtual double actionProb(State *s, Action *a) { throw runtime_error("Not Implemented"); }
    virtual bool definedFor(State *s) { throw runtime_error("Not Implemented"); }
};


#endif // FASTRL_BEHAVIOR_POLICY_POLICY_HPP