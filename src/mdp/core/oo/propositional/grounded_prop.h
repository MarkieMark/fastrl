//
// Mark Benjamin 5/30/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_MDP_CORE_OO_PROPOSITIONAL_GROUNDED_PROP_H
#define FASTRL_MDP_CORE_OO_PROPOSITIONAL_GROUNDED_PROP_H

#include "../../../../include/classes.h"
#include "propositional_function.h"
#include "../state/OO_state.hpp"

class GroundedProp {
public:
    PropositionalFunction pf;
    vector<string> params;

    GroundedProp(PropositionalFunction p, vector<string> par) :
        pf(move(p)), params(move(par)) { }

    bool isTrue(OOState s);
};

#endif //FASTRL_MDP_CORE_OO_PROPOSITIONAL_GROUNDED_PROP_H
