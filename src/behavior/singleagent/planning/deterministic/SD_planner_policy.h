/*
 * Mark Benjamin 04 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_SD_PLANNER_POLICY_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_SD_PLANNER_POLICY_H

#include "../../../policy/enumerable_policy.hpp"
#include "../../../policy/solver_derived_policy.hpp"
#include "deterministic_planner.h"

class SDPlannerPolicy : public SolverDerivedPolicy, public EnumerablePolicy {
public:
    DeterministicPlanner * p;
    explicit SDPlannerPolicy(DeterministicPlanner * dp = nullptr) : p(dp) { }
    void setSolver(MDPSolverInterface * solver) override;
    Action * action(State * s) override;
    double actionProb(State * s, Action * a) override;
    vector<ActionProb *> policyDistribution(State * s) override;
    bool definedFor(State * s) override;
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_SD_PLANNER_POLICY_H
