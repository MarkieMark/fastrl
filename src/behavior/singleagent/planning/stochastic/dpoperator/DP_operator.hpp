/*
 * Mark Benjamin 05 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_DPOPERATOR_DP_OPERATOR_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_DPOPERATOR_DP_OPERATOR_HPP

#include <vector>
#include <stdexcept>

using namespace std;

class DPOperator {
public:
    virtual double apply(vector<double> &qs) {throw runtime_error("DPOperator::apply() Not Implemented");}
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_STOCHASTIC_DPOPERATOR_DP_OPERATOR_HPP
