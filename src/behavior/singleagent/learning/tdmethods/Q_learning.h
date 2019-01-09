//
// Mark Benjamin 6/1/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_TDMETHODS_Q_LEARNING_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_TDMETHODS_Q_LEARNING_H

#include <limits>
#include "../../../valuefunction/Q_provider.h"
#include "../learning_agent.hpp"
#include "../../planning/planner.hpp"
#include "../../MDP_solver.hpp"
#include "Q_learning_state_node.hpp"
#include "../../../learningrate/learning_rate.hpp"
#include "../../../policy/greedy_Q_policy.h"

class QLearning : public MDPSolver, public QProvider, public LearningAgent, public Planner{
public:
    map</*Hashable*/State *, QLearningStateNode *> qFunction;
    QFunction * qInitFunction;
    LearningRate * learningRate;
    Policy * learningPolicy;
    int maxEpisodeSize;
    int episodeIterationCounter;
    int nEpisodesForPlanning;
    double maxQChangeForPlanningConvergence = numeric_limits<double>::max();
    double maxQChangeInMostRecentEpisode = numeric_limits<double>::max();
    bool shouldDecomposeOptions = true;
    int agentIterationCounter = 0;
    QLearning(SADomain * domain_, double gamma_,
            /*HashableStateFactory * factory,*/ double qInitial,
            double learning_rate);
    QLearning(SADomain * domain_, double gamma_,
            /*HashableStateFactory * factory,*/ double qInitial,
              double learning_rate, int max_episode_size);
    QLearning(SADomain * domain_, double gamma_,
            /*HashableStateFactory * factory,*/ double qInitial,
              double learning_rate, Policy * learning_policy,
              int max_episode_size);
    QLearning(SADomain * domain_, double gamma_,
            /*HashableStateFactory * factory,*/ QFunction * qInitial,
              double learning_rate, Policy * learning_policy,
              int max_episode_size);

    void QLInit(SADomain * domain_, double gamma_,
            /*HashableStateFactory * factory,*/ QFunction * qInitial,
              double learning_rate, Policy * learning_policy,
              int max_episode_size);
    void initializeForPlanning(int n_episodes_for_planning);
    void setLearningRateFunction(LearningRate * lr);
    void setQInitFunction(QFunction * q_init);
    void setLearningPolicy(Policy *p);
    void setMaximumEpisodesForPlanning(int n);
    void setMaxQChangeForPlanningConvergence(double m);
    int getLastEpisodeIterations();
    void toggleShouldDecomposeOption(bool active);
    vector<QValue *> qValues(State *s) override;
    double qValue(State *s, Action *a) override;
    vector<QValue *> getQs(/*Hashable*/State *s);
    QValue * getQ(/*Hashable*/State *s, Action *a);
    double value(State * s) override;
    QLearningStateNode * getStateNode(/*Hashable*/State *s);
    double getMaxQ(/*Hashable*/State *s);
    Policy * planFromState(State * initial_state) override;
    Episode * runLearningEpisode(Environment * env) override;
    Episode * runLearningEpisode(Environment * env, int max_iterations) override;
    void resetSolver() override;
//    void writeQTable(string path);
//    void loadQTable(string path);
};
#endif // FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_TDMETHODS_Q_LEARNING_H
