//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_STATE_GRID_LOCATION_H
#define FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_STATE_GRID_LOCATION_H

#include <QtCore/QObject>
#include <string>
#include "../../../../mdp/core/oo/state/object_instance.hpp"

using namespace std;

class GridLocation : public QObject, public ObjectInstance {
    Q_OBJECT
private:
    vector<KeyContainer *> keys;
public:
    int x;
    int y;
    int type;
    string _name;
    Q_INVOKABLE explicit GridLocation(int x_ = -1, int y_ = -1, int type_ = -1, string name_ = "");
    // todo check -1 default values for consistency with code base
    string className() override;
    string name() override;
    ObjectInstance* copyWithName(string objectName) override;
    vector<KeyContainer *> variableKeys() override;
    // TODO check assumption that all values are integers
    int getIntValue(KeyContainer *variableKey) override;
    State* makeCopy() override;
    string toString();
    string getName();
    void setName(string name_);
    void setLoc(int x_, int y_);
    void setType(int type_);
};

#endif // FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_STATE_GRID_LOCATION_H
