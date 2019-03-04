/*
 * Mark Benjamin 04 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include "SD_planner_policy.h"

void SDPlannerPolicy::setSolver(MDPSolverInterface * solver) {
    if (dynamic_cast<DeterministicPlanner *>(solver) == nullptr) {
        throw runtime_error("SDPlannerPolicy::setSolver() Planner is not a Deterministic Planner");
    }
    p = dynamic_cast<DeterministicPlanner *>(solver);
}

Action * SDPlannerPolicy::action(State * s) {
    if (p == nullptr) {
        throw runtime_error("SDPlannerPolicy::action() The valueFunction used by this Policy is not defined; "
                            "therefore, the policy is undefined.");
    }
    if (p->hasCachedPlanForState(s)) {
        Action * ga = p->getSelectedActionForState(s);
        //the surrounding if condition will probably be sufficient for null cases, but doing double check just to make sure.
        if (ga == nullptr) {
            throw runtime_error("SDPlannerPolicy::action() Policy is undefined for the provided state");
        }
        return ga;
    }
    throw runtime_error("SDPlannerPolicy::action() Policy is undefined for the provided state");
}

double SDPlannerPolicy::actionProb(State * s, Action * a) {
    //todo check equality test
    if (a == action(s)) {
        return 1.;
    }
    return 0.;
}

vector<ActionProb *> SDPlannerPolicy::policyDistribution(State * s) {
    Action * selectedAction = action(s);
    if (selectedAction == nullptr) {
        throw runtime_error("SDPlannerPolicy::policyDistribution() Policy is undefined for the provided state");
    }
    vector<ActionProb *> res = vector<ActionProb *>();
    auto * ap = new ActionProb(selectedAction, 1.);
    res.push_back(ap);
    return res;
}

bool SDPlannerPolicy::definedFor(State * s) {
    if (p == nullptr) {
        throw runtime_error("SDPlannerPolicy::definedFor() The valueFunction used by this Policy is not defined; therefore, the policy is undefined.");
    }
    return p->hasCachedPlanForState(s);
}
