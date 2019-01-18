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
    virtual State * currentObservation() { throw runtime_error("Environment::currentObservation() Not Implemented"); }
    virtual EnvironmentOutcome * act(Action *a) { throw runtime_error("Environment::act() Not Implemented"); }
    virtual double lastReward() { throw runtime_error("Environment::lastReward() Not Implemented"); }
    virtual bool isInTerminalState() { throw runtime_error("Environment::isInTerminalState() Not Implemented"); }
    virtual void resetEnvironment() { throw runtime_error("Environment::resetEnvironment() Not Implemented"); }
};

#endif // FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_ENVIRONMENT_HPP