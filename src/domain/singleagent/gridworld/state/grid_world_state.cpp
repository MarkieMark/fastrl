#include "grid_world_state.h"
#include "../../../../mdp/core/state/mutable_state.hpp"
#include "../../../../mdp/core/oo/state/OO_variable_key.hpp"
#include "../../../../mdp/core/oo/state/OO_state_utilities.h"

/**
 * Mark Benjamin 31st May 2017
 */

GridWorldState::GridWorldState() = default;

GridWorldState::GridWorldState(GridAgent * agent_, vector<GridLocation *> locations_) {
    agent = agent_;
    if (locations_.empty()) {
        locations = vector<GridLocation *>();
    } else {
        locations = locations_;
    }
}

GridWorldState::GridWorldState(int x_, int y_, vector<GridLocation *> locations_)
    : GridWorldState(new GridAgent(x_, y_), move(locations_)) { }

MutableOOState * GridWorldState::addObject(ObjectInstance o) {
    auto * loc = dynamic_cast<GridLocation *>(&o);
    locations.push_back(loc);
    return this;
}

MutableOOState * GridWorldState::removeObject(string objectName) {
    if (objectName == agent->name()) {
        throw runtime_error("Agent Must Stay");
    }
    long ind = locationInd(objectName);
    if (ind == -1) {
        throw runtime_error("Object Not Found");
    }
    vector<GridLocation *> newLocations = vector<GridLocation *>();
    for (long i = 0; i < locations.size(); i++) {
        if (i != ind) {
            newLocations.push_back(locations[i]);
        }
    }
    locations = newLocations;
    return this;
}

MutableOOState * GridWorldState::renameObject(string objectName, string newName) {
    if (objectName == agent->name()) {
        agent = dynamic_cast<GridAgent *>(agent->copyWithName(newName));
    } else {
        long ind = locationInd(objectName);
        if (ind == -1) {
            throw runtime_error("Object Not Found");
        }
        GridLocation * newLoc = dynamic_cast<GridLocation *>(locations[ind]->copyWithName(newName));
        vector<GridLocation *> newLocations = vector<GridLocation *>();
        for (int i = 0; i < locations.size(); i++) {
            if (i != ind) {
                newLocations.push_back(locations[i]);
            }
        }
        locations = newLocations;
        locations.push_back(newLoc);
    }
    return this;
}

unsigned long GridWorldState::numObjects() {
    return 1 + locations.size();
}

ObjectInstance * GridWorldState::object(string objectName) {
    if (objectName == agent->name()) {
        return agent;
    }
    long ind = locationInd(objectName);
    if (ind != -1) {
        return locations[ind];
    }
    return nullptr;
}

vector<ObjectInstance *> GridWorldState::objects() {
    vector<ObjectInstance *> obs = vector<ObjectInstance *>();
    obs.push_back(dynamic_cast<ObjectInstance *>(agent));
    obs.insert(obs.end(), locations.begin(), locations.end());
    return obs;
}

vector<ObjectInstance *> GridWorldState::objectsOfClass(string objectClass) {
    if (objectClass == "agent") {
        return vector<ObjectInstance *>({agent});
    } else if (objectClass == "location") {
        return vector<ObjectInstance *>(locations.begin(), locations.end());
    }
    throw runtime_error("Object Class Not Recognized");
}

MutableState * GridWorldState::set(KeyContainer *variableKey, void *value) {
    KeyContainer * key = OOStateUtilities::generateOOVariableKey(variableKey);
    int iv = *((int *) value);
    if (key->vk.objName == agent->name()) {
        if (key->vk.objVarKey == GridWorldDomain::VAR_X()) {
            agent->x = iv;
        } else if (key->vk.objVarKey == GridWorldDomain::VAR_Y()) {
            agent->y = iv;
        }
        return this;
    }
    long ind = locationInd(key->vk.objName);
    if (ind != -1) {
        if (key->vk.objVarKey == GridWorldDomain::VAR_X()) {
            locations[ind]->x = iv;
        } else if (key->vk.objVarKey == GridWorldDomain::VAR_Y()) {
            locations[ind]->y = iv;
        } else if (key->vk.objVarKey == GridWorldDomain::VAR_TYPE()) {
            locations[ind]->type = iv;
        }
        return this;
    }
    throw runtime_error("Unrecognized Variable Key");
}

vector<KeyContainer *> GridWorldState::variableKeys() {
    OOState * oos = this;
    return OOStateUtilities::flatStateKeys(*oos);
}

int GridWorldState::get(KeyContainer * variableKey) {
    KeyContainer * key = OOStateUtilities::generateOOVariableKey(variableKey);
    if (key->vk.objName == agent->name()) {
        return agent->getIntValue(key);
    }
    long ind = locationInd(key->vk.objName);
    if (ind == -1) {
        throw runtime_error("Object Not Found");
    }
    return locations[ind]->getIntValue(key);
}

State * GridWorldState::makeCopy() {
    return dynamic_cast<State *>( new GridWorldState(agent, locations));
}

long GridWorldState::locationInd(string objName) {
    long ind = -1;
    for (long i = 0; i < locations.size(); i++) {
        if (locations[i]->name() == objName) {
            ind = i;
            break;
        }
    }
    return ind;
}

string GridWorldState::toString() {
    OOState *oos = this;
    return OOStateUtilities::ooStateTostring(*oos);
}

