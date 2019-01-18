/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_ENVIRONMENT_OUTCOME_HPP
#define FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_ENVIRONMENT_OUTCOME_HPP

#include "../../core/state/state.hpp"
#include "../../core/action/action.hpp"

class EnvironmentOutcome {
public:
    State * o;
    Action * a;
    State * o_prime;
    double reward;
    bool done;
    explicit EnvironmentOutcome(State * o_ = nullptr, Action * a_ = nullptr, State * o_prime_ = nullptr,
                       double reward_ = -1., bool done_ = false)
        : o(o_), a(a_), o_prime(o_prime_), reward(reward_), done(done_) { }
    virtual long nIterations() { throw runtime_error("EnvironmentOutcome::nIterations() Not Implemented"); }
};

#endif // FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_ENVIRONMENT_OUTCOME_HPP
