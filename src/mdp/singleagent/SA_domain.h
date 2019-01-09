//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_MDP_SINGLEAGENT_SA_DOMAIN_H
#define FASTRL_MDP_SINGLEAGENT_SA_DOMAIN_H

#include "../core/domain.hpp"
#include "../core/action/action_type.hpp"
#include "model/sample_model.hpp"
#include <vector>
#include <map>

class SADomain : public Domain {
public:
    vector<ActionType *> actionTypes;
    map<string, ActionType *> actionMap;
    SampleModel * model;
    SADomain();

    SADomain * addActionType(ActionType * act);
    SADomain * addActionTypes(vector<ActionType *> actions);
    SADomain * setActionTypes(vector<ActionType *> actions);
    SADomain * clearActionTypes();
    vector<ActionType *> getActionTypes();
    ActionType * getAction(string name);
    SampleModel * getModel();
    void setModel(SampleModel * model_);

};

#endif // FASTRL_MDP_SINGLEAGENT_SA_DOMAIN_H
