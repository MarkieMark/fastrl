/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_CORE_OO_OO_DOMAIN_HPP
#define FASTRL_MDP_CORE_OO_OO_DOMAIN_HPP

#include <QtCore/QObject>
#include <vector>
#include "../domain.hpp"
#include "propositional/propositional_function.h"

using namespace std;

class OODomain : public Domain {
public:
    virtual vector<QMetaObject> stateClasses() { throw runtime_error("OODomain::stateClasses() Not Implemented"); }
    virtual QMetaObject stateClass(string className) { throw runtime_error("OODomain::stateClass() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
    virtual OODomain * addStateClass(string className, QObject stateClass) { throw runtime_error("OODomain::addStateClass() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
    virtual vector<PropositionalFunction *> propFunctions()  { throw runtime_error("OODomain::propFunctions() Not Implemented"); }
    virtual OODomain * addPropFunction(PropositionalFunction * prop) { throw runtime_error("OODomain::addPropFunction() Not Implemented"); }
};

class OODomainHelper {
public:
    static void addPfsToDomain(OODomain * domain, vector<PropositionalFunction *> pfs);
};

#endif // FASTRL_MDP_CORE_OO_OO_DOMAIN_HPP