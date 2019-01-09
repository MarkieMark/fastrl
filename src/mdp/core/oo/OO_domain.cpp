//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#include "OO_domain.h"

void OODomainHelper::addPfsToDomain(OODomain * domain, vector<PropositionalFunction *> pfs) {
    for (PropositionalFunction * pf : pfs) {
        domain->addPropFunction(pf);
    }
}

