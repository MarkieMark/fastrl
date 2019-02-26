//
// Mark Benjamin 6/1/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_SIMULATED_ENVIRONMENT_H
#define FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_SIMULATED_ENVIRONMENT_H

#include "../SA_domain.h"
#include "../model/sample_model.hpp"
#include "../../auxiliary/state_generator.hpp"
#include "extensions/environment_observer.hpp"
#include "extensions/environment_server_interface.hpp"
#include "extensions/state_settable_environment.hpp"

class SimulatedEnvironment : public StateSettableEnvironment, public EnvironmentServerInterface {
public:
    SampleModel * model;
    StateGenerator * stateGenerator;
    State * currentState;
    double _lastReward = 0.;
    bool done = false;
    bool allowActionFromTerminalStates = false;
    vector<EnvironmentObserver *> _observers = vector<EnvironmentObserver *>();
    explicit SimulatedEnvironment(SADomain * domain);
    SimulatedEnvironment(SADomain * domain, State * initialState);
    SimulatedEnvironment(SADomain * domain, StateGenerator * state_generator);
    explicit SimulatedEnvironment(SampleModel * model_);
    SimulatedEnvironment(SampleModel * model_, State * initialState);
    SimulatedEnvironment(SampleModel * model_, StateGenerator * state_generator);
    StateGenerator * getStateGenerator();
    void setStateGenerator(StateGenerator * state_generator);
    void addObservers(vector<EnvironmentObserver *> observers_) override;
    void clearAllObservers() override;
    void removeObservers(vector<EnvironmentObserver *> observers_) override;
    vector<EnvironmentObserver *> observers() override;
    void setAllowActionFromTerminalStates(bool allow);
    void setCurrentStateTo(State *s) override;
    State * currentObservation() override;
    EnvironmentOutcome * act(Action *a) override;
    double lastReward() override;
    bool isInTerminalState() override;
    void resetEnvironment() override;
};


#endif // FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_SIMULATED_ENVIRONMENT_H
