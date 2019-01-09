//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_STATE_GRID_WORLD_STATE_H
#define FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_STATE_GRID_WORLD_STATE_H

#include "../../../../mdp/core/oo/state/mutable_OO_state.hpp"
#include "../../../../mdp/core/state/mutable_state.hpp"
#include "grid_agent.h"
#include "grid_location.h"
#include "../../../../mdp/core/oo/state/OO_variable_key.hpp"
#include "../../../../mdp/core/oo/state/key_container.hpp"

class GridWorldState : public MutableOOState {
public:
    GridAgent * agent;
    vector<GridLocation *> locations = vector<GridLocation *>();

    GridWorldState();
    GridWorldState(GridAgent *agent, vector<GridLocation *> locations);
    GridWorldState(int x_, int y_, vector<GridLocation *> locations);

    MutableOOState * addObject(ObjectInstance o);
    MutableOOState * removeObject(string objectName) override;
    MutableOOState * renameObject(string objectName, string newName) override;
    unsigned long numObjects();
    ObjectInstance * object(string objectName) override;
    vector<ObjectInstance *> objects() override;
    vector<ObjectInstance *> objectsOfClass(string objectClass) override;
    MutableState * set(KeyContainer * variableKey, void * value) override;
    vector<KeyContainer *> variableKeys() override;
    // TODO check assumption that all values are integers
    int get(KeyContainer * variableKey);
    State * makeCopy() override;
    long locationInd(string objectName);
    string toString();
//    GridAgent * touchAgent();
//    vector<GridLocation *> touchLocations();
//    vector<GridLocation *> deepTouchLocations();
//    GridLocation * touchLocation(int ind);
};


#endif // FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_STATE_GRID_WORLD_STATE_H
