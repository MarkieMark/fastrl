/*
 * 26th February 2019 Mark Benjamin
 * (c) Mark Benjamin February 26th 2019
 */

#ifndef FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_ENVIRONMENT_SERVER_H
#define FASTRL_MDP_SINGLEAGENT_ENVIRONMENT_EXTENSIONS_ENVIRONMENT_SERVER_H

#include <vector>
#include <algorithm>
#include "environment_server_interface.hpp"
#include "environment_delegation.hpp"
#include "state_settable_environment.hpp"

using namespace std;

class EnvironmentServer : public EnvironmentServerInterface, public EnvironmentDelegation {

public:
    Environment * delegate;
    vector<EnvironmentObserver *> observers = vector<EnvironmentObserver *>();
    static EnvironmentServerInterface * constructServerOrAddObservers(Environment * env, vector<EnvironmentObserver *> observers_);
    static EnvironmentServer * constructor(Environment * delegate_, vector<EnvironmentObserver *> observers_);
    EnvironmentServer(Environment * delegate_, vector<EnvironmentObserver *> observers_);
    Environment * getEnvironmentDelegate() override;
    void setEnvironmentDelegate(Environment * delegate) override;
    void addObservers(vector<EnvironmentObserver *> observers_) override;
    void clearAllObservers() override;
    void removeObservers(vector<EnvironmentObserver *> observers_) override;
    vector <EnvironmentObserver * > getObservers();
    State * currentObservation() override;
    EnvironmentOutcome * act(Action * ga) override;
    double lastReward() override;
    bool isInTerminalState() override;
    void resetEnvironment() override;
};

class StateSettableEnvironmentServer : public EnvironmentServer , public StateSettableEnvironment {
public:
    StateSettableEnvironmentServer(StateSettableEnvironment * delegate_, vector<EnvironmentObserver *> observers_);
    void setCurrentStateTo(State * s) override;
};

#endif
