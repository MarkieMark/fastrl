//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_STATE_GRID_AGENT_H
#define FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_STATE_GRID_AGENT_H

#include <string>
#include <QtCore/QArgument>
#include <QObject>
#include "../../../../mdp/core/oo/state/object_instance.hpp"
#include "../grid_world_domain.h"

using namespace std;

class GridAgent : public QObject, public ObjectInstance {
    Q_OBJECT
private:
    vector<KeyContainer *> keys = vector<KeyContainer *>(
            {new KeyContainer(GridWorldDomain::VAR_X()),
             new KeyContainer(GridWorldDomain::VAR_Y())});
public:
    int x;
    int y;
    string _name;
    Q_INVOKABLE explicit GridAgent(int x_ = -1, int y_ = -1, string name_ = "agent");
    // todo check -1 default values for consistency with code base
    GridAgent *instantiate();
    string className() override;
    string name() override;
    ObjectInstance* copyWithName(string objectName) override;
    vector<KeyContainer *> variableKeys() override;
    // TODO check assumption that all values are integers
    int getIntValue(KeyContainer *variableKey) override;
    State* makeCopy() override;
    string getName();
    void setName(string name_);
    void setLoc(int x, int y);
    string toString();
};
#endif // FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_STATE_GRID_AGENT_H
