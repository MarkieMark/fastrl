#include <map>
#include <QtCore/QMetaObject>
#include "../../core/oo/propositional/propositional_function.h"
#include "../SA_domain.h"
#include "../../core/oo/OO_domain.h"

/**
 * Mark Benjamin 30th May 2017
 */

class OOSADomain : public SADomain , public OODomain {
private:
    map<string, QMetaObject> stateClassesMap = map<string, QMetaObject>();
    map<string, PropositionalFunction *> propFunctionMap = map<string, PropositionalFunction *>();

public:
    vector<QMetaObject> stateClasses() override {
        vector<QMetaObject> ret = vector<QMetaObject>();
        for (const auto &p : stateClassesMap) {
            ret.push_back(p.second);
        }
        return ret;
    }

    QMetaObject stateClass(string className) override {
        return stateClassesMap.find(className)->second;
    }

    OOSADomain * addStateClass(string className, QMetaObject stateClass) {
        stateClassesMap.insert(pair<string, QMetaObject>(className, stateClass));
        return this;
    }

    vector<PropositionalFunction *> propFunctions() override {
        vector<PropositionalFunction *> ret = vector<PropositionalFunction *>();
        for (const auto &p : propFunctionMap) {
            ret.push_back(p.second);
        }
        return ret;
}

    PropositionalFunction * propFunction(string name) { // NOLINT(performance-unnecessary-value-param)
        return propFunctionMap.find(name)->second;
    }

    OODomain * addPropFunction(PropositionalFunction * prop) override {
        propFunctionMap.insert(
                pair<string, PropositionalFunction *>(prop->getName(), prop));
        return this;
    }
};
