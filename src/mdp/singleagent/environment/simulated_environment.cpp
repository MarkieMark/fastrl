/**
 * Mark Benjamin 1st June 2017
 */

#include "simulated_environment.h"
#include "../../auxiliary/common/constant_state_generator.hpp"

SimulatedEnvironment::SimulatedEnvironment(SADomain *domain) {
    if (domain->getModel() == nullptr) {
        throw runtime_error("SimulatedEnvironment needs a Domain with a Model");
    }
    model = domain->getModel();
}

SimulatedEnvironment::SimulatedEnvironment(SADomain *domain, State * initialState) {
    stateGenerator = new ConstantStateGenerator(initialState);
    currentState = initialState;
    if (domain->getModel() == nullptr) {
        throw runtime_error("SimulatedEnvironment needs a Domain with a Model");
    }
    model = domain->getModel();
}

SimulatedEnvironment::SimulatedEnvironment(
        SADomain *domain, StateGenerator * state_generator) {
    stateGenerator = state_generator;
    currentState = stateGenerator->generateState();
    if (domain->getModel() == nullptr) {
        throw runtime_error("SimulatedEnvironment needs a Domain with a Model");
    }
    model = domain->getModel();
}

SimulatedEnvironment::SimulatedEnvironment(SampleModel * model_) {
    model = model_;
}

SimulatedEnvironment::SimulatedEnvironment(SampleModel *model_, State *initialState) {
    stateGenerator = new ConstantStateGenerator(initialState);
    currentState = initialState;
    model = model_;
}

SimulatedEnvironment::SimulatedEnvironment(SampleModel *model_, StateGenerator *state_generator) {
    stateGenerator = state_generator;
    currentState = stateGenerator->generateState();
    model = model_;
}

StateGenerator* SimulatedEnvironment::getStateGenerator() {
    return stateGenerator;
}

void SimulatedEnvironment::setStateGenerator(StateGenerator *state_generator) {
    stateGenerator = state_generator;
}

void SimulatedEnvironment::addObservers(vector<EnvironmentObserver *> observers_) {
    for (EnvironmentObserver * o : observers_) {
        _observers.push_back(o);
    }
}

void SimulatedEnvironment::clearAllObservers() {
    _observers.clear();
}

void SimulatedEnvironment::removeObservers(vector<EnvironmentObserver *> observers_) {
    vector<EnvironmentObserver *> newObservers;
    for (EnvironmentObserver * o : observers_) {
        // TODO looks kind of inefficient
        newObservers = _observers;
        for (EnvironmentObserver * e : _observers) {
            if (e != o) {
                newObservers.push_back(e);
            }
        }
        _observers = newObservers;
    }
}

vector<EnvironmentObserver *> SimulatedEnvironment::observers() {
    return _observers;
}

void SimulatedEnvironment::setAllowActionFromTerminalStates(bool allow) {
    this->allowActionFromTerminalStates = allow;
}

void SimulatedEnvironment::setCurrentStateTo(State *s) {
    if (stateGenerator == nullptr) {
        stateGenerator = new ConstantStateGenerator(s);
    }
    currentState = s;
}

State* SimulatedEnvironment::currentObservation() {
    return currentState;
}

EnvironmentOutcome* SimulatedEnvironment::act(Action *a) {
    for (EnvironmentObserver * observer : _observers) {
        observer->observeEnvironmentActionInitiation(currentState, a);
    }
    EnvironmentOutcome * eo;
    if (allowActionFromTerminalStates || !isInTerminalState()) {
        eo = model->sample(currentState, a);
    } else {
        eo = new EnvironmentOutcome(currentState, a, currentState, 0., true);
    }
    _lastReward = eo->reward;
    done = eo->done;
    currentState = eo->o_prime;
    for (EnvironmentObserver * observer : _observers) {
        observer->observeEnvironmentInteraction(eo);
    }
    /* todo added return */
    return eo;
}

double SimulatedEnvironment::lastReward() {
    return _lastReward;
}

bool SimulatedEnvironment::isInTerminalState() {
    return done;
}

void SimulatedEnvironment::resetEnvironment() {
    _lastReward = 0.;
    done = false;
    currentState = stateGenerator->generateState();
    for (EnvironmentObserver * observer : _observers) {
        observer->observeEnvironmentReset(this);
    }
}