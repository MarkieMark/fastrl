#include "grid_agent.h"
#include "../../../../mdp/core/oo/state/OO_state_utilities.h"

/**
 * Mark Benjamin 31st May 2017
 */

GridAgent::GridAgent(int x_, int y_, string name_)
    : _name(move(name_)), x(x_), y(y_) { }

GridAgent* GridAgent::instantiate() {
    return (GridAgent*) staticMetaObject.newInstance();
//    return (GridAgent*) metaObject()->newInstance();
}

string GridAgent::className() {
    return GridWorldDomain::CLASS_AGENT();
}

string GridAgent::name() {
    return _name;
}

ObjectInstance* GridAgent::copyWithName(string objectName) {
    auto *nAgent = dynamic_cast<GridAgent *> (((*this).makeCopy()));
    nAgent->_name = objectName;
    return dynamic_cast<ObjectInstance *>(nAgent);
}

State* GridAgent::makeCopy() {
    return dynamic_cast<State *>(new GridAgent(x, y, _name));
}

vector<KeyContainer *> GridAgent::variableKeys() {
    return keys;
}

int GridAgent::getIntValue(KeyContainer *variableKey) {
    string comp = (variableKey->isString ? variableKey->s : variableKey->vk.objVarKey);
    if (comp == GridWorldDomain::VAR_X()) {
        return x;
    } else if (comp == GridWorldDomain::VAR_Y()) {
        return y;
    }
    /* todo added return */
    return -1;
}

string GridAgent::getName() {
    return _name;
}

void GridAgent::setName(string name_) {
    if (name_.empty()) {
        _name = "agent";
    } else {
        _name = name_;
    }
}

void GridAgent::setLoc(int x_, int y_) {
    x = x_;
    y = y_;
}

string GridAgent::toString() {
    ObjectInstance* oi = this;
    return OOStateUtilities::objectInstanceToString(*oi);
}