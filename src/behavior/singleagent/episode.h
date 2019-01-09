//
// Mark Benjamin 6/1/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_EPISODE_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_EPISODE_H

//#include <boost/serialization>
#include "../../mdp/core/state/state.hpp"
#include "../../mdp/core/action/action.hpp"
#include "../../mdp/singleagent/environment/environment_outcome.hpp"

class Episode {
public:
    vector<State *> stateSequence = vector<State *>();
    vector<Action *> actionSequence = vector<Action *>();
    vector<double> rewardSequence = vector<double>();
    explicit Episode(State * initialState = nullptr);
    void initializeInState(State * initialState);
    void addState(State * s);
    void addAction(Action *a);
    void addReward(double r);
    void transition(Action * a, State * s_prime, double r);
    void transition(EnvironmentOutcome * eo);
    State * state(int t);
    Action * action(int t);
    double reward(int t);
    long nIterations();
    long maxIteration();
    long nActions();
    double discountedReturn(double discountFactor);
    void appendThenMergeEpisode(Episode * e);
    string actionString();
    string actionString(string delimiter);
    static void writeEpisodes(vector<Episode *> episodes, string directoryPath, string baseFileName);
    void write(string path);
    static vector<Episode *> readEpisodes(string directoryPath);
    static Episode * read(string path);
    Episode * makeCopy();
//    Episode * parseEpisode(string episodeString);
    static void main(string args[]);
};

#endif // FASTRL_BEHAVIOR_SINGLEAGENT_EPISODE_H
