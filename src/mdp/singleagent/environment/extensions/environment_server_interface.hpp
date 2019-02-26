/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_ENVIRONMENT_SERVER_INTERFACE_HPP
#define FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_ENVIRONMENT_SERVER_INTERFACE_HPP

#include "../environment.hpp"
#include "environment_observer.hpp"

class EnvironmentServerInterface : virtual public Environment {
public:
    virtual void addObservers(vector<EnvironmentObserver *> observers) { throw runtime_error("EnvironmentServerInterface::addObservers() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
    virtual void clearAllObservers() { throw runtime_error("EnvironmentServerInterface::clearAllObservers() Not Implemented"); }
    virtual void removeObservers(vector<EnvironmentObserver *> observers) { throw runtime_error("EnvironmentServerInterface::removeObservers() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
    virtual vector<EnvironmentObserver *> observers() { throw runtime_error("EnvironmentServerInterface::observers() Not Implemented"); }
};

#endif // FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_ENVIRONMENT_SERVER_INTERFACE_HPP