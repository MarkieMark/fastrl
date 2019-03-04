/*
 * Mark Benjamin 05 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_DPOPERATOR_BELLMAN_OPERATOR_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_DPOPERATOR_BELLMAN_OPERATOR_HPP

#include "DP_operator.hpp"

class BellmanOperator : public DPOperator {
public:
    double apply(vector<double> &qs) override {
        double m = qs[0];
        for(double q : qs) {
            m = m > q ? m : q;
        }
        return m;
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_DPOPERATOR_BELLMAN_OPERATOR_HPP
