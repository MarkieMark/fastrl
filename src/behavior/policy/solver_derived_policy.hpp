/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_POLICY_SOLVER_DERIVED_POLICY_HPP
#define FASTRL_BEHAVIOR_POLICY_SOLVER_DERIVED_POLICY_HPP

#include "policy.hpp"
#include "../singleagent/MDP_solver_interface.hpp"

class SolverDerivedPolicy : virtual public Policy {
public:
    virtual void setSolver(MDPSolverInterface * solver) { throw runtime_error("SolverDerivedPolicy::setSolver() Not Implemented"); }
};

#endif