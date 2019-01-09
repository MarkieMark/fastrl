/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_ENVIRONMENT_HPP
#define FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_ENVIRONMENT_HPP

#include "../../core/state/state.hpp"
#include "../../core/action/action.hpp"
#include "environment_outcome.hpp"

class Environment {
public:
    virtual State * currentObservation() { throw runtime_error("Not Implemented"); }
    virtual EnvironmentOutcome * act(Action *a) { throw runtime_error("Not Implemented"); }
    virtual double lastReward() { throw runtime_error("Not Implemented"); }
    virtual bool isInTerminalState() { throw runtime_error("Not Implemented"); }
    virtual void resetEnvironment() { throw runtime_error("Not Implemented"); }
};

#endif // FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_ENVIRONMENT_HPP