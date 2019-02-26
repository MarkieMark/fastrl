/*
 * Mark Benjamin 26 February 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include "environment_server.h"

EnvironmentServerInterface * EnvironmentServer::constructServerOrAddObservers(Environment * env, vector<EnvironmentObserver *> observers_) {
    if(dynamic_cast<EnvironmentServerInterface *>(env) != nullptr) {
        auto ret = dynamic_cast<EnvironmentServerInterface *>(env);
        ret->addObservers(observers_);
        return ret;
    } else {
        return constructor(env, observers_);
    }
}

EnvironmentServer * EnvironmentServer::constructor(Environment * delegate_, vector<EnvironmentObserver *> observers_){
    if(dynamic_cast<StateSettableEnvironment *>(delegate_) != nullptr){
        return new StateSettableEnvironmentServer(dynamic_cast<StateSettableEnvironment *>(delegate_), vector<EnvironmentObserver *>());
    }
    return new EnvironmentServer(delegate_, move(observers_));
}

EnvironmentServer::EnvironmentServer(Environment * delegate_, vector<EnvironmentObserver *> observers_) {
    delegate = delegate_;
    for (EnvironmentObserver * observer : observers_) {
        observers.push_back(observer);
    }
}

Environment * EnvironmentServer::getEnvironmentDelegate() {
    return delegate;
}

void EnvironmentServer::setEnvironmentDelegate(Environment * delegate_) {
    delegate = delegate_;
}

void EnvironmentServer::addObservers(vector<EnvironmentObserver *> observers_) {
    for(EnvironmentObserver * observer : observers_){
        observers.push_back(observer);
    }
}

void EnvironmentServer::clearAllObservers(){
    observers.clear();
}

void EnvironmentServer::removeObservers(vector<EnvironmentObserver *> observers_) {
    for(EnvironmentObserver * observer : observers_) {
        auto it = std::remove(observers.begin(), observers.end(), observer);
        observers.erase(it, observers.end());
    }
}

vector <EnvironmentObserver *> EnvironmentServer::getObservers() {
    return observers;
}

State * EnvironmentServer::currentObservation() {
    return delegate->currentObservation();
}

EnvironmentOutcome * EnvironmentServer::act(Action * ga) {
    for(EnvironmentObserver * observer : observers){
        observer->observeEnvironmentActionInitiation(delegate->currentObservation(), ga);
    }
    EnvironmentOutcome * eo = delegate->act(ga);
    for(EnvironmentObserver * observer : observers){
        observer->observeEnvironmentInteraction(eo);
    }
    return eo;
}

double EnvironmentServer::lastReward() {
    return delegate->lastReward();
}

bool EnvironmentServer::isInTerminalState() {
    return delegate->isInTerminalState();
}

void EnvironmentServer::resetEnvironment() {
    delegate->resetEnvironment();
    for(EnvironmentObserver * observer : observers){
        observer->observeEnvironmentReset(delegate);
    }
}

StateSettableEnvironmentServer::StateSettableEnvironmentServer(
        StateSettableEnvironment * delegate_, vector<EnvironmentObserver *> observers_)
: EnvironmentServer(delegate_, move(observers_)) { }

void StateSettableEnvironmentServer::setCurrentStateTo(State * s) {
    dynamic_cast<StateSettableEnvironment *>(delegate)->setCurrentStateTo(s);
}
