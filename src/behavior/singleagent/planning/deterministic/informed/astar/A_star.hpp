/*
 * Mark Benjamin 05 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_ASTAR_A_STAR_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_ASTAR_A_STAR_HPP

#include "../best_first.h"
#include "../heuristic.hpp"

class AStar : public BestFirst {
public:
    Heuristic * heuristic;
    map<State *, double> cumulativeRewardMap;
    double lastComputedReward = 0.;

    AStar(SADomain * domain, StateConditionTest * gc, Heuristic * h) {
        deterministicPlannerInit(domain, gc);
        heuristic = h;
    }

    void postPlanPrep() override {
        cumulativeRewardMap.erase(cumulativeRewardMap.begin(), cumulativeRewardMap.end());
    }

    void insertIntoOpen(priority_queue<PrioritizedSearchNode *> &openQueue, PrioritizedSearchNode * psn) override {
        BestFirst::insertIntoOpen(openQueue, psn);
        cumulativeRewardMap.insert(pair<State *, double>(psn->s, lastComputedReward));
    }
    void updateOpen(priority_queue<PrioritizedSearchNode *> &openQueue,
            PrioritizedSearchNode * openPSN, PrioritizedSearchNode * psn) override {
        BestFirst::updateOpen(openQueue, openPSN, psn);
        cumulativeRewardMap.insert(pair<State *, double>(psn->s, lastComputedReward));
    }
    double computeF(PrioritizedSearchNode * parentNode, Action * generatingAction,
            State * successorState, double r) override {
        double cr = 0.;
        if (parentNode != nullptr) {
            double pcr = cumulativeRewardMap.find(parentNode->s)->second;
            cr = pcr + r;
        }
        double H  = heuristic->h(successorState);
        lastComputedReward = cr;
        double F = cr + H;
        return F;
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_ASTAR_A_STAR_HPP
