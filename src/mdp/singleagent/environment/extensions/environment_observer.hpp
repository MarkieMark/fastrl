/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_ENVIRONMENT_OBSERVER_HPP
#define FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_ENVIRONMENT_OBSERVER_HPP

#include "../../../core/state/state.hpp"
#include "../../../core/action/action.hpp"
#include "../environment_outcome.hpp"
#include "../environment.hpp"

class EnvironmentObserver {
public:
    virtual void observeEnvironmentActionInitiation(State *observation, Action *action) { throw runtime_error("EnvironmentObserver::observeEnvironmentActionInitiation() Not Implemented"); }
    virtual void observeEnvironmentInteraction(EnvironmentOutcome *eo) { throw runtime_error("EnvironmentObserver::observeEnvironmentInteraction() Not Implemented"); }
    virtual void observeEnvironmentReset(Environment * resetEnvironment) { throw runtime_error("EnvironmentObserver::observeEnvironmentReset() Not Implemented"); }
};

#endif // FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_ENVIRONMENT_OBSERVER_HPP