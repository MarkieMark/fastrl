/*
 * Mark Benjamin 05 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_TDMETHODS_SARSA_LAM_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_TDMETHODS_SARSA_LAM_HPP

#include <queue>
#include "../../../../include/classes.h"
#include "Q_learning.h"
#include "../../options/option.h"

class SarsaLamEligibilityTrace {
public:
    double eligibility;
    State * s;
    QValue * q;
    double initialQ;

    SarsaLamEligibilityTrace(State * s_, QValue * q_, double eligibility_)
    : s(s_), q(q_), eligibility(eligibility_), initialQ(q->q) { }
};


class SarsaLam : public QLearning {
public:
    double lambda = 0.7;
    SarsaLam(SADomain * domain, double gamma, double qInit, double learningRate, double lambda)
    : QLearning(domain, gamma, qInit, learningRate) {
        sarsalamInit(lambda);
    }

    SarsaLam(SADomain * domain, double gamma, double qInit,
            double learningRate, int maxEpisodeSize, double lambda)
        : QLearning(domain, gamma, qInit, learningRate, maxEpisodeSize) {
        sarsalamInit(lambda);
    }

    SarsaLam(SADomain * domain, double gamma, double qInit, double learningRate,
            Policy * learningPolicy, int maxEpisodeSize, double lambda)
        : QLearning(domain, gamma, qInit, learningRate, learningPolicy, maxEpisodeSize) {
        sarsalamInit(lambda);
    }

    SarsaLam(SADomain * domain, double gamma, QFunction * qInit, double learningRate,
            Policy * learningPolicy, int maxEpisodeSize, double lambda)
        : QLearning(domain, gamma, qInit, learningRate, learningPolicy, maxEpisodeSize) {
        sarsalamInit(lambda);
    }

    void sarsalamInit(double l) {
        lambda = l;
    }


    Episode * runLearningEpisode(Environment * env, int maxIter) override {
        // todo double check details of how traces are added to vector, order of perusal etcetera
        State * initialState = env->currentObservation();
        auto * ea = new Episode(initialState);
        maxQChangeInMostRecentEpisode = 0.;
        State * curState = initialState;
        episodeIterationCounter = 0;
        vector<SarsaLamEligibilityTrace *> traces = vector<SarsaLamEligibilityTrace *>();
        Action * action = learningPolicy->action(curState);
        QValue * curQ = getQ(curState, action);
        while(!env->isInTerminalState() && (episodeIterationCounter < maxIter || maxIter == -1)){
            EnvironmentOutcome * eo;
            if (dynamic_cast<Option *>(action) == nullptr) {
                eo = env->act(action);
            } else {
                eo = dynamic_cast<Option *>(action)->control(env, gamma);
            }
            State * nextState = eo->o_prime;
            Action * nextAction = learningPolicy->action(nextState);
            QValue * nextQ = getQ(nextState, nextAction);
            double nextQV = nextQ->q;
            if(env->isInTerminalState()){
                nextQV = 0.;
            }
            //manage option specifics
            double r = eo->reward;
            double discount = dynamic_cast<EnvironmentOptionOutcome *>(eo) != nullptr ?
                    dynamic_cast<EnvironmentOptionOutcome *>(eo)->discount : gamma;
            long inc = dynamic_cast<EnvironmentOptionOutcome *>(eo) != nullptr ?
                    dynamic_cast<EnvironmentOptionOutcome *>(eo)->nIterations() : 1;
            episodeIterationCounter += inc;
            if (dynamic_cast<Option *>(action) == nullptr || !shouldDecomposeOptions){
                ea->transition(action, nextState, r);
            } else {
                ea->appendThenMergeEpisode(dynamic_cast<EnvironmentOptionOutcome *>(eo)->episode);
            }
            //delta
            double delta = r + (discount * nextQV) - curQ->q;
            //update all
            bool foundCurrentQTrace = false;
            for (SarsaLamEligibilityTrace * et : traces) {
                if (et->s == curState) {
                    if(et->q->a == action) {
                        foundCurrentQTrace = true;
                        et->eligibility = 1.; //replacing traces
                    } else {
                        et->eligibility = 0.; //replacing traces
                    }
                }
                double learning_rate = learningRate->pollLearningRate(agentIterationCounter, et->s, et->q->a);
                et->q->q = et->q->q + (learning_rate * et->eligibility * delta);
                et->eligibility = et->eligibility * lambda * discount;
                double deltaQ = abs(et->initialQ - et->q->q);
                if (deltaQ > maxQChangeInMostRecentEpisode){
                    maxQChangeInMostRecentEpisode = deltaQ;
                }
            }
            if (!foundCurrentQTrace) {
                //then update and add it
                double learning_rate = learningRate->pollLearningRate(agentIterationCounter, curQ->s, curQ->a);
                curQ->q = curQ->q + (learning_rate * delta);
                auto * et = new SarsaLamEligibilityTrace(curState, curQ, lambda * discount);
                traces.push_back(et);
                double deltaQ = abs(et->initialQ - et->q->q);
                if(deltaQ > maxQChangeInMostRecentEpisode){
                    maxQChangeInMostRecentEpisode = deltaQ;
                }
            }
            //move on
            curState = nextState;
            action = nextAction;
            curQ = nextQ;
            agentIterationCounter++;
        }
        return ea;
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_TDMETHODS_SARSA_LAM_HPP
