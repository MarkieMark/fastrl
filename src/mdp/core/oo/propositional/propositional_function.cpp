#include <utility>

#include <utility>

#include <utility>

/**
 * Mark Benjamin 30th May 2017
 */

#include <string>
#include <vector>
#include <sstream>
#include "../state/OO_state.hpp"
#include "grounded_prop.h"
#include "../state/OO_state_utilities.h"

using namespace std;

PropositionalFunction::PropositionalFunction() {
    name = "NULL";
}

PropositionalFunction::PropositionalFunction(string name_, vector<string> parameter_classes)
    : name(move(name_)), parameterClasses(parameter_classes)
{
    vector<string> rcn = vector<string>(parameter_classes.size());
    stringstream s;
    for (int i = 0; i < parameter_classes.size(); i++) {
        s << name << ".P" << i;
        rcn[i] = s.str();
        s.str(string());
    }
    parameterOrderGroup = rcn;
}

PropositionalFunction::PropositionalFunction(string name_, vector<string> parameter_classes,
                          vector<string> parameter_order_group)
    : name(move(name_)), parameterClasses(move(parameter_classes)), parameterOrderGroup(move(parameter_order_group)) { }

string PropositionalFunction::getName() { return name; }
vector<string> PropositionalFunction::getParameterClasses() { return parameterClasses; }
vector<string> PropositionalFunction::getParameterOrderGroups() { return parameterOrderGroup; };

/**
 * Returns all possible groundings of this {@link PropositionalFunction} for the given {@link State}
 * @param s the {@link State} in which all groundings will be returned
 * @return a {@link List} of all possible groundings of this {@link PropositionalFunction} for the given {@link State}
 */
vector<GroundedProp *> PropositionalFunction::allGroundings(OOState * s) {
    vector<GroundedProp* > res;
    if(getParameterClasses().empty()){
        res.emplace_back(new GroundedProp(*this, vector<string>()));
        return res; //no parameters so just the single gp without params
    }

//    if(!(s instanceof OOState)){
//        throw new RuntimeException("Cannot generate all GroundedProp objects for state " + s.getClass().getName() + " because it does not implement OOState");
//    }

    vector<vector<string>> bindings = OOStateUtilities::getPossibleBindingsGivenParamOrderGroups(
            s, getParameterClasses(), getParameterOrderGroups());

    for(const vector<string> &params : bindings){
        const vector<string> &params_ = params;
        GroundedProp * gp = new GroundedProp(*this, params_);
        res.push_back(gp);
    }
    return res;
}

/**
 * Returns true if there existing a {@link GroundedProp} for the provided {@link State} that is in true in the {@link State}.
 * @param s the {@link State} to test.
 * @return true if there existing a {@link GroundedProp} for the provided {@link State} that is in true in the {@link State}; false otherwise.
 */
bool PropositionalFunction::someGroundingIsTrue(OOState * s){
    vector<GroundedProp* > gps = allGroundings(s);
    for(GroundedProp * gp : gps){
        if(gp->isTrue(s)){
            return true;
        }
    }
    return false;
}


    // should be unnecessary in c++
//    int hashCode(){
//        return name.hashCode();
//    }

/**
 * Returns all possible groundings for all of the {@link PropositionalFunction}s in the provided list for the given {@link State}.
 * @param pfs The list of {@link PropositionalFunction}s for which all groundings will be returned.
 * @param s the {@link State} in which the groundings should be produced.
 * @return a {@link List} of all possible groundings for all of the {@link PropositionalFunction}s in the provided list for the given {@link State}
 */
 vector<GroundedProp *> PropositionalFunction::allGroundingsFromList(vector<PropositionalFunction *> pfs, OOState * s){
    vector<GroundedProp *> res;
    for(PropositionalFunction * pf : pfs){
        vector<GroundedProp *> gps = pf->allGroundings(s);
        res.insert(res.end(), gps.begin(), gps.end());
    }
    return res;
}


/**
 * Used to retrieve a {@link PropositionalFunction} with a specified name from a list of them.
 * @param pfs The list of {@link PropositionalFunction} objects to search.
 * @param pfName The name of the {@link PropositionalFunction}
 * @return the {@link PropositionalFunction} with the name or null if it does not exist
 */
PropositionalFunction * PropositionalFunction::findPF(vector<PropositionalFunction *> pfs, string pfName){
    for(PropositionalFunction * pf : pfs){
        if(pf->getName() == pfName){
            return pf;
        }
    }
    return new PropositionalFunction();
}
