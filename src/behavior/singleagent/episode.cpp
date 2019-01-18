#include <fstream>
#include <iostream>
#include "episode.h"
#include "../../domain/singleagent/gridworld/grid_world_domain.h"
#include "../../domain/singleagent/gridworld/state/grid_world_state.h"
#include "../policy/policy.hpp"

/**
 * Mark Benjamin 1st June 2017
 */

Episode::Episode(State *initialState) {
    if (initialState != nullptr)
    {
        initializeInState(initialState);
    }
}

void Episode::initializeInState(State *initialState) {
    if (!stateSequence.empty()) {
        throw runtime_error("Episode Already Started");
    }
    stateSequence.push_back(initialState);
}

void Episode::addState(State *s) {
    stateSequence.push_back(s);
}

void Episode::addAction(Action *a) {
    actionSequence.push_back(a);
}

void Episode::addReward(double r) {
    rewardSequence.push_back(r);
}

void Episode::transition(Action *a, State *s_prime, double r){
    stateSequence.push_back(s_prime);
    actionSequence.push_back(a);
    rewardSequence.push_back(r);
}

void Episode::transition(EnvironmentOutcome *eo) {
    stateSequence.push_back(eo->o_prime);
    actionSequence.push_back(eo->a);
    rewardSequence.push_back(eo->reward);
}

State * Episode::state(int t) {
    if (t >= stateSequence.size()) {
        throw runtime_error("Episode does not go that far");
    }
    return stateSequence[t];
}

Action * Episode::action(int t) {
    if (t == actionSequence.size()) {
        throw runtime_error("No Action at the limit");
    }
    if (t > actionSequence.size()) {
        throw runtime_error("Episode does not go that far");
    }
    return actionSequence[t];
}

double Episode::reward(int t) {
    if (t == 0) {
        throw runtime_error("No reward at time 0");
    }
    if (t > rewardSequence.size()) {
        throw runtime_error("Episode does not go that far");
    }
    return rewardSequence[t - 1];
}

long Episode::nIterations() {
    return stateSequence.size();
}

long Episode::maxIteration() {
    return stateSequence.size() - 1;
}

long Episode::nActions() {
    return actionSequence.size();
}

double Episode::discountedReturn(double discountFactor) {
    double discount = 1.;
    double sum = 0.;
    for (double r : rewardSequence) {
        sum += discount * r;
        discount *= discountFactor;
    }
    return sum;
}

void Episode::appendThenMergeEpisode(Episode *e) {
    for (int i = 0; i < e->nIterations() - 1; i++) {
        transition(e->action(i), e->state(i + 1), e->reward(i + 1));
    }
}

string Episode::actionString() {
    return actionString("; ");
}

string Episode::actionString(string delimiter) {
    stringstream s;
    bool first = true;
    for (Action *a : actionSequence) {
        if (!first) {
            s << delimiter;
        }
        s << a/*.to_string()*/; // TODO Action.to_string()
        first = false;
    }
    return s.str();
}

void Episode::writeEpisodes(
        vector<Episode *> episodes, string directoryPath,
        string baseFileName) {
    if (!(directoryPath.substr(directoryPath.size() - 1) == "/")) {
        directoryPath += "/";
    }
    Episode *e;
    stringstream w;
    for (int i = 0; i < episodes.size(); i++) {
        e = episodes[i];
        w << directoryPath << baseFileName << i;
        e->write(w.str());
        w.str(string());
    }
}

void Episode::write(string path) {
    if (!(path.substr(path.size() - 8) == ".episode")) {
        path += ".episode";
    }
    ofstream file(path);
    // boost::serialization
    // http://www.boost.org/doc/libs/1_36_0/libs/serialization/example/demo.cpp
    // Java BURLAP code uses Yaml
}

vector<Episode *> Episode::readEpisodes(string directoryPath) {
    if (!(directoryPath.substr(directoryPath.size() - 1) == "/")) {
        directoryPath += "/";
    }
    // read files in directory
    // check whether individual files end in ".episode"
    // sort the list of valid files
    vector<Episode *> eas = vector<Episode *>();
    // individually call
    // Episode ea = read(fileName)
    // eas.push_back(ea);
    return eas;
}

Episode * Episode::read(string path) {
    // see write() for boost::serialization, Yaml
    /* todo added nullptr */
    return nullptr;
}

Episode* Episode::makeCopy() {
    auto * e = new Episode();
    e->stateSequence = vector<State *>(stateSequence.begin(), stateSequence.end());
    e->actionSequence = vector<Action *>(actionSequence.begin(), actionSequence.end());
    e->rewardSequence = vector<double>(rewardSequence.begin(), rewardSequence.end());
    return e;
}

void Episode::main(string *args) {
    auto * gwd = new GridWorldDomain(11, 11);
    SADomain * domain = gwd->generateDomain();
    State *s = new GridWorldState(new GridAgent(1, 3), vector<GridLocation *>());
//    Policy * p = new RandomPolicy(domain);
//    Episode e = PolicyUtils.rollout(p, s, domain->getModel(), 30);

//    Here test serialization functionality

//    cout << e.actionString() << endl;
//    cout << e.state(0)/*.to_string()*/ << endl;
//    cout << e.actionSequence.size() << endl;
//    cout << e.stateSequence.size() << endl;
}



