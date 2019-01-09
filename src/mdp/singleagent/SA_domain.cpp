/**
 * Mark Benjamin 31st May 2017
 */

#include "SA_domain.h"

SADomain::SADomain() {
    actionTypes = vector<ActionType *>();
    actionMap = map<string, ActionType *>();
}

SADomain * SADomain::addActionType(ActionType * act) {
    if (actionMap.find(act->typeName()) == actionMap.end()) {
        actionTypes.push_back(act);
        actionMap.insert(pair<string, ActionType *>(act->typeName(), act));
    }
    return this;
}

SADomain * SADomain::addActionTypes(vector<ActionType *> actions) {
    for (ActionType * action : actions) {
        addActionType(action);
    }
    return this;
}

SADomain * SADomain::setActionTypes(vector<ActionType *> actions) {
    actionTypes.clear();
    actionMap.clear();
    for (ActionType * at : actions) {
        addActionType(at);
    }
    return this;
}

SADomain * SADomain::clearActionTypes() {
    actionMap.clear();
    actionTypes.clear();
    return this;
}

vector<ActionType *> SADomain::getActionTypes() {
    return vector<ActionType *>(actionTypes.begin(), actionTypes.end());
}

ActionType * SADomain::getAction(string name) {
    return actionMap.find(name)->second;
}

SampleModel * SADomain::getModel() {
    return model;
}

void SADomain::setModel(SampleModel * model_) {
    model = model_;
}