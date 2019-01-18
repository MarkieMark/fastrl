//
// Mark Benjamin 5/30/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_MDP_CORE_OO_PROPOSITIONAL_PROPOSITIONAL_FUNCTION_H
#define FASTRL_MDP_CORE_OO_PROPOSITIONAL_PROPOSITIONAL_FUNCTION_H

#include <string>
#include <vector>
#include "../../../../include/classes.h"
#include "../state/OO_state.hpp"

using namespace std;

class PropositionalFunction {
private:
    string name;
    vector <string> parameterClasses;
    vector <string> parameterOrderGroup;

public:
    PropositionalFunction();
    PropositionalFunction(string name_, vector <string> parameter_classes);
    PropositionalFunction(string name_, vector<string> parameter_classes,
                          vector<string> parameter_order_group);
    string getName();
    vector<string> getParameterClasses();
    vector<string> getParameterOrderGroups();
    virtual bool isTrue(OOState s, vector<string> params) { throw runtime_error("PropositionalFunction::isTrue() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
    vector<GroundedProp> allGroundings(OOState s);
    bool someGroundingIsTrue(OOState s);
    static vector<GroundedProp> allGroundingsFromList(vector<PropositionalFunction> pfs, OOState s);
    PropositionalFunction findPF(vector<PropositionalFunction> pfs, string pfName);
    bool operator==(const PropositionalFunction &comp) {
        return name == comp.name;
    }
    string to_string() { return name; }
};

#endif // FASTRL_MDP_CORE_OO_PROPOSITIONAL_PROPOSITIONAL_FUNCTION_H
