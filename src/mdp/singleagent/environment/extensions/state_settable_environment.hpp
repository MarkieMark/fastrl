/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_STATE_SETTABLE_ENVIRONMENT_HPP
#define FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_STATE_SETTABLE_ENVIRONMENT_HPP

#include "../environment.hpp"

class StateSettableEnvironment : virtual public Environment {
public:
    virtual void setCurrentStateTo(State *s) { throw runtime_error("StateSettableEnvironment::setCurrentStateTo() Not Implemented"); }
};

#endif // FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_STATE_SETTABLE_ENVIRONMENT_HPP