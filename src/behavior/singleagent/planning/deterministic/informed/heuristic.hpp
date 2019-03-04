/*
 * Mark Benjamin 05 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_HEURISTIC_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_HEURISTIC_HPP

#include <stdexcept>
#include "../../../../../mdp/core/state/state.hpp"

using namespace std;

class Heuristic {
public:
    virtual double h(State * s) { throw runtime_error("Heuristic::h() Not Implemented"); return 0.; }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_PLANNING_DETERMINISTIC_INFORMED_HEURISTIC_HPP
