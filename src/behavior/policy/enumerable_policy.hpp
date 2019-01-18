/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_POLICY_ENUMERABLE_POLICY_HPP
#define FASTRL_BEHAVIOR_POLICY_ENUMERABLE_POLICY_HPP

#include "policy.hpp"
#include "support/action_prob.hpp"

class EnumerablePolicy : virtual public Policy {
public:
    virtual vector<ActionProb *> policyDistribution(State *s) { throw runtime_error("EnumerablePolicy::policyDistribution() Not Implemented"); }
};

#endif