//
// Mark Benjamin 6/1/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_BEHAVIOR_POLICY_EPSILON_GREEDY_H
#define FASTRL_BEHAVIOR_POLICY_EPSILON_GREEDY_H

#include "solver_derived_policy.hpp"
#include "enumerable_policy.hpp"
#include "../valuefunction/Q_provider.h"

class EpsilonGreedy : public SolverDerivedPolicy, public EnumerablePolicy {
public:
    QProvider * qPlanner;
    double epsilon;
    explicit EpsilonGreedy(QProvider * planner = nullptr, double epsilon_ = -1.);
    double getEpsilon();
    void setEpsilon(double epsilon_);
    void setSolver(MDPSolverInterface * solver) override;
    Action * action(State *s) override;
    double actionProb(State *s, Action *a) override;
    vector<ActionProb *> policyDistribution(State *s) override;
    bool definedFor(State *s) override;
};

#endif // FASTRL_BEHAVIOR_POLICY_EPSILON_GREEDY_H
