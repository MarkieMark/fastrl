//
// Mark Benjamin 6/1/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_MDP_CORE_ACTION_ACTION_UTILS_H
#define FASTRL_MDP_CORE_ACTION_ACTION_UTILS_H

#include <vector>
#include "action.hpp"
#include "action_type.hpp"
#include "../state/state.hpp"

class ActionUtils {
public:
    static vector<Action *> allApplicableActionsForTypes(vector<ActionType *> actionTypes, State *s);
};

#endif // FASTRL_MDP_CORE_ACTION_ACTION_UTILS_H
