/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_CORE_ACTION_ACTION_TYPE_HPP
#define FASTRL_MDP_CORE_ACTION_ACTION_TYPE_HPP

#include <string>
#include <vector>
#include "action.hpp"
#include "../state/state.hpp"

class ActionType {
public:
    virtual string typeName() { throw runtime_error("ActionType::typeName() Not Implemented"); }
    virtual Action * associatedAction(string stringRepresentation) { throw runtime_error("ActionType::associatedAction() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
    virtual vector<Action *> allApplicableActions(State * s) { throw runtime_error("ActionType::allApplicableActions() Not Implemented"); }
};

#endif