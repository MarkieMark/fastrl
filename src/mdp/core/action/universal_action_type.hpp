#include <utility>

#include <utility>

/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_CORE_ACTION_UNIVERSAL_ACTION_TYPE_HPP
#define FASTRL_MDP_CORE_ACTION_UNIVERSAL_ACTION_TYPE_HPP

#include "action_type.hpp"

class UniversalActionType : public ActionType {
public:
    string _typeName;
    Action * action = nullptr;
    vector<Action *> allActions;

    explicit UniversalActionType(string type_name) : _typeName(move(type_name)) { }

    explicit UniversalActionType(Action * action) : UniversalActionType(action->actionName(), action) { }

    UniversalActionType(string type_name, Action * action_)
        : _typeName(move(type_name)), action(action_), allActions(vector<Action *>({action})) { }

    string typeName() override { return _typeName; }
    Action * associatedAction(string stringRep) override { return action; }
    vector<Action *> allApplicableActions(State s) { return allActions; } // NOLINT(performance-unnecessary-value-param)
};

#endif // FASTRL_MDP_CORE_ACTION_UNIVERSAL_ACTION_TYPE_HPP
