#include "grid_location.h"
#include "../grid_world_domain.h"
#include "../../../../mdp/core/oo/state/OO_state_utilities.h"

/**
 * Mark Benjamin 31st May 2017
 */

GridLocation::GridLocation(int x_, int y_, int type_, string name_)
    : x(x_), y(y_), type(type_), _name(move(name_))
{
    keys = vector<KeyContainer *>({new KeyContainer(GridWorldDomain::VAR_X()),
                                   new KeyContainer(GridWorldDomain::VAR_Y()),
                                   new KeyContainer(GridWorldDomain::VAR_TYPE())});
}

string GridLocation::className() {
    return GridWorldDomain::CLASS_LOCATION();
}

string GridLocation::name() {
    return _name;
}

ObjectInstance* GridLocation::copyWithName(string objectName) {
    auto newLocation = dynamic_cast<GridLocation *>(makeCopy());
    newLocation->_name = objectName;
    return dynamic_cast<ObjectInstance *>(newLocation);
}

vector<KeyContainer *> GridLocation::variableKeys() const {
    return keys;
}

int GridLocation::getIntValue(KeyContainer *variableKey) const {
    string comp = (variableKey->isString ? variableKey->s : variableKey->vk->objVarKey);
    if (comp == GridWorldDomain::VAR_X()) {
        return x;
    } else if (comp == GridWorldDomain::VAR_Y()) {
        return y;
    } else if (comp == GridWorldDomain::VAR_TYPE()) {
        return type;
    }
    /* todo added return */
    return -1;
}

State* GridLocation::makeCopy() {
    return dynamic_cast<State *>(new GridLocation(x, y, type, _name));
}

string GridLocation::to_string() {
    ObjectInstance * oi = this;
    return OOStateUtilities::objectInstanceToString(oi);
}

string GridLocation::getName() {
    return _name;
}

void GridLocation::setName(string name_) {
    _name = move(name_);
}

void GridLocation::setLoc(int x_, int y_) {
    x = x_;
    y = y_;
}

void GridLocation::setType(int type_) {
    type = type_;
}
