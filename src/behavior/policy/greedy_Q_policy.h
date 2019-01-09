//
// Mark Benjamin 6/1/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_BEHAVIOR_POLICY_GREEDY_Q_POLICY_H
#define FASTRL_BEHAVIOR_POLICY_GREEDY_Q_POLICY_H

#include "solver_derived_policy.hpp"
#include "enumerable_policy.hpp"
#include "../valuefunction/Q_provider.h"

class GreedyQPolicy : public SolverDerivedPolicy, public EnumerablePolicy {
public:
    QProvider * qplanner;
    explicit GreedyQPolicy(QProvider * provider = nullptr);
    void setSolver(MDPSolverInterface * solver) override;
    Action * action(State *s) override;
    double actionProb(State *s, Action * a) override;
    vector<ActionProb *> policyDistribution(State *s) override;
    bool definedFor(State *s) override;
};

#endif // FASTRL_BEHAVIOR_POLICY_GREEDY_Q_POLICY_H
