#include "OO_state_utilities.h"
#include "../../state/state_utilities.hpp"

using namespace std;

/**
 * Returns the {@link ObjectInstance} with the given name
 * @param objects a vector {@link ObjectInstance}s
 * @param name the name of the query {@link ObjectInstance}
 * @param T the type of the {@link ObjectInstance}
 * @return the found {@link ObjectInstance} or null if it is not found
 */
ObjectInstance OOStateUtilities::objectWithName(vector<ObjectInstance> objects, string name){
    for(ObjectInstance ob : objects){
        if(ob.name()== name){
            return ob;
        }
    }
    return {};
    // was return ObjectInstance();
}

/**
 * Returns the index of an {@link ObjectInstance} with the given name in a vector
 * @param objects a vector {@link ObjectInstance}s
 * @param name the name of the query {@link ObjectInstance}
 * @param T the type of the {@link ObjectInstance}
 * @return the index of the found {@link ObjectInstance} or -1 if it is not found
 */
int OOStateUtilities::objectIndexWithName(vector<ObjectInstance> objects, string name) {
    for(unsigned int i = 0; i < objects.size(); i++){
        ObjectInstance ob = objects[i];
        if(ob.name() == name){
            return i;
        }
    }
    return -1;
}


/**
 * Returns all object-variable_key keys. Useful for implementing the {@link OOState#variableKeys()} method.
 * @param s the input state
 * @return the vector of all keys.
 */
vector<KeyContainer *> OOStateUtilities::flatStateKeys(OOState s) {
    vector<KeyContainer *> flatKeys = vector<KeyContainer *>();
    stringstream st;
    for(ObjectInstance *o : s.objects()){
        vector<KeyContainer *> keys = o->variableKeys();
        for(KeyContainer * key : keys) {
            st << o->name() << ":";
            if (key->isString) {
                st << key->s;
            } else {
                st << key->vk.objVarKey;
            }
            KeyContainer * fKey = new KeyContainer(OOVariableKey(st.str()));
            flatKeys.push_back(fKey);
        }
    }
    return flatKeys;
}

/**
 * Returns the value of an {@link ObjectInstance} variable, where the key is a {@link OOVariableKey} or a string
 * representation of an {@link OOVariableKey}.
 * @param s the input state
 * @param variableKey the object-variable key
 * @return the value of the object variable.
 */
int OOStateUtilities::get(OOState s, KeyContainer * variableKey) {
    KeyContainer * key = generateOOVariableKey(variableKey);
    ObjectInstance * o = s.object(key->vk.objName);
    return o->getIntValue(key);
}

/**
 * Generates an {@link OOVariableKey} from a key that is either already an {@link OOVariableKey} or a string representation of one.
 * @param key an {@link OOVariableKey} or a string representation of one.
 * @return the corresponding {@link OOVariableKey}
 */
KeyContainer * OOStateUtilities::generateOOVariableKey(KeyContainer *key) {
    if(!(key->isString)) {
        return key;
    } else {
        return new KeyContainer(OOVariableKey(key->s));
    }
}


/**
 * Returns a vector of vector of {@link ObjectInstance}s where the objects are organized by their class.
 * @param s the input {@link OOState}
 * @return the {@link ObjectInstance}s organized by their class
 */
map<string, vector<ObjectInstance *>> OOStateUtilities::objectsByClass(OOState s) {
    set<string> classes = objectClassesPresent(s);
    map<string, vector<ObjectInstance *>> obsByClass;
    for(string className : classes){
        vector<ObjectInstance *> obs = vector<ObjectInstance *>(s.objectsOfClass(className));
        obsByClass.insert(pair<string, vector<ObjectInstance *>>(className, obs));
    }
    return obsByClass;
}

/**
 * Returns the set of object classes that have instantiated {@link ObjectInstance}s in the input state.
 * @param s the input state
 * @return the set of object classes that have instantiated {@link ObjectInstance}s in the input state.
 */
set<string> OOStateUtilities::objectClassesPresent(OOState s) {
    vector<ObjectInstance *> obs = s.objects();
    set<string> classes = set<string>();
    for(ObjectInstance *ob : obs){
        classes.insert(ob->className());
    }
    return classes;
}


/**
 * A common approach for turning an {@link OOState} into a string representation. Useful for implementing
 * {@link Object#to_string()} methods.
 * @param s the input {@link OOState}
 * @return the string representation
 */
string OOStateUtilities::ooStateTostring(OOState * s) {
    stringstream buf;
    buf << ("{\n");
    for(ObjectInstance * o : s->objects()){
        buf << objectInstanceToString(o);
        buf << "\n";
    }
    buf << "}";
    return buf.str();
}


/**
 * A common approach for turning an {@link ObjectInstance} into a string representation. Useful for implementing the
 * {@link Object#to_string()} method.
 * @param o the input {@link ObjectInstance}
 * @return the string representation
 */
string OOStateUtilities::objectInstanceToString(ObjectInstance * o) {
    stringstream buf;
    buf << o->name() << " (" << o->className() << "): " << StateUtilities::stateToString(o);
    return buf.str();
}

/**
 * Returns all possible object assignments from a {@link OOState} for a given set of parameters that are typed
 * to OO-MDP object classes. For example, parameters for a {@link burlap.mdp.core.oo.propositional.PropositionalFunction}
 * or {@link burlap.mdp.core.oo.ObjectParameterizedAction}.
 * @param s the {@link OOState}
 * @param paramClasses the object class type for a parameter array that needs object assignments
 * @param paramOrderGroups indicates the order group of a parameter. Parameters in the same
 *                         order group can have their object assignments shuffled without affecting the evaluation.
 *                         By default, you probably can have a unique order group for each parameters
 * @return the vector of all object assignments, where each object assignment is a vector of object names of equal size
 * to the input parameters.
 */
vector<vector<string>> OOStateUtilities::getPossibleBindingsGivenParamOrderGroups(
        OOState s, vector<string> paramClasses, vector<string> paramOrderGroups) {

    vector<vector<string>> res = vector<vector<string>>();
    vector<vector<string>> currentBindingSets = vector<vector<string>>();
    vector<string> uniqueRenames = identifyUniqueClassesInParameters(paramOrderGroups);
    vector<string> uniqueParamClasses = identifyUniqueClassesInParameters(paramClasses);

    map<string, vector <ObjectInstance *>> instanceMap = objectsByClass(s);

    //first make sure we have objects for each class parameter; if not return empty vector
    for(const string &oClass : uniqueParamClasses){
        int n = getNumOccurrencesOfClassInParameters(oClass, paramClasses);
        vector<ObjectInstance *> objectsOfClass = instanceMap.find(oClass)->second;
        if(objectsOfClass.size() < n){
            return res;
        }
    }
    getPossibleRenameBindingsHelper(res, currentBindingSets, 0, s.objects(), uniqueRenames, paramClasses, paramOrderGroups);
    return res;
}


vector<string> OOStateUtilities::identifyUniqueClassesInParameters(
        vector<string> paramClasses) {
    vector<string> unique = vector<string>();
    for (const auto &param_class : paramClasses) {
        if(find(unique.begin(), unique.end(), param_class) == unique.end()){
            unique.push_back(param_class);
        }
    }
    return unique;
}



void OOStateUtilities::getPossibleRenameBindingsHelper(
        vector<vector<string>> res, vector<vector<string>> currentBindingSets,
        int bindIndex, vector<ObjectInstance *> remainingObjects,
        vector<string> uniqueOrderGroups, vector<string> paramClasses,
        vector<string> paramOrderGroups) {

    if(bindIndex == uniqueOrderGroups.size()){
        //base case, put it all together and add it to the result
        res.push_back(getBindingFromCombinationSet(currentBindingSets, uniqueOrderGroups, paramOrderGroups));
        return ;
    }

    //otherwise we're in the recursive case

    string r = uniqueOrderGroups[bindIndex];
    string c = parameterClassAssociatedWithOrderGroup(r, paramOrderGroups, paramClasses);
    vector<ObjectInstance *> objects = objectsMatchingClass(remainingObjects, c);
    unsigned long k = numOccurrencesOfOrderGroup(r, paramOrderGroups);
    vector<vector<string>> combs = getAllCombinationsOfObjects(objects, k);
    for(const vector<string> &cb : combs){

        vector<vector<string>> nextBinding = vector<vector<string>>(currentBindingSets.size());
        for(const vector<string> &prevBind : currentBindingSets){
            nextBinding.push_back(prevBind);
        }
        nextBinding.push_back(cb);
        vector <ObjectInstance *> nextObsRemaining = objectVectorDifference(remainingObjects, cb);

        //recursive step
        getPossibleRenameBindingsHelper(res, nextBinding, bindIndex+1, nextObsRemaining,
                                        uniqueOrderGroups, paramClasses, paramOrderGroups);
    }
}

/**
 * for a specific parameter order group, return a possible binding
 * @param comboSets is a vector of the bindings for each order group. For instance, if the order groups for each parameter were P, Q, P, Q, R; then there would be three vectors
 * @param orderGroupAssociatedWithSet which order group each vector of bindings in comboSets is for
 * @param orderGroups the parameter order groups for each parameter
 * @return a binding as a vector of object instance names
 */
vector<string> OOStateUtilities::getBindingFromCombinationSet(
        vector<vector<string>> comboSets,
        vector <string> orderGroupAssociatedWithSet,
        vector<string> orderGroups) {

    vector<string> res = vector <string>(orderGroups.size());
    //add the necessary space first
    for(int i = 0; i < orderGroups.size(); i++){
        res.emplace_back("");
    }

    //apply the parameter bindings for each rename combination
    for(int i = 0; i < comboSets.size(); i++){
        vector <string> renameCombo = comboSets[i];
        string r = orderGroupAssociatedWithSet[i];

        //find the parameter indices that match this rename and set a binding accordingly
        int ind = 0;
        for(int j = 0; j < orderGroups.size(); j++){
            if(orderGroups[j] == r){
                res[j] = renameCombo[ind];
                ind++;
            }
        }
    }

    return res;
}

int OOStateUtilities::getNumOccurrencesOfClassInParameters(
        string className, vector<string> paramClasses) {
    int num = 0;
    for (const auto &param_class : paramClasses) {
        if(param_class == className) {
            num++;
        }
    }
    return num;
}

string OOStateUtilities::parameterClassAssociatedWithOrderGroup(
        string orderGroup, vector<string> orderGroups,
        vector<string> paramClasses) {
    for(int i = 0; i < orderGroups.size(); i++){
        if(orderGroups[i] == orderGroup){
            return paramClasses[i];
        }
    }
    return "";
}

unsigned long OOStateUtilities::numOccurrencesOfOrderGroup(
        string rename, vector<string> orderGroups) {
    unsigned long num = 0;
    for (const auto &order_group : orderGroups) {
        if(order_group == rename){
            num++;
        }
    }

    return num;

}


vector<ObjectInstance *> OOStateUtilities::objectsMatchingClass(
        vector<ObjectInstance *> objects, string className) {
    vector<ObjectInstance *> filtered = vector<ObjectInstance *>(objects.size());
    for(ObjectInstance *ob : objects){
        if(ob->className() == className) {
            filtered.push_back(ob);
        }
    }
    return filtered;
}


vector<vector<string>> OOStateUtilities::getAllCombinationsOfObjects(
        vector <ObjectInstance *> objects, unsigned long k) {

    vector <vector<string>> allCombs = vector <vector<string>>();

    unsigned long n = objects.size();
    vector<int> comb = initialComb(k, n);
    allCombs.push_back(getVectorOfBindingsFromCombination(objects, comb));
    while(nextComb(comb, k, n) == 1){
        allCombs.push_back(getVectorOfBindingsFromCombination(objects, comb));
    }

    return allCombs;

}


vector<string> OOStateUtilities::getVectorOfBindingsFromCombination(
        vector <ObjectInstance *> objects, vector<int> comb) {
    vector<string> res = vector<string>(comb.size());
    for (int i : comb) {
        res.push_back(objects[i]->name());
    }
    return res;
}


vector <ObjectInstance *> OOStateUtilities::objectVectorDifference(
        vector <ObjectInstance *> objects, vector <string> toRemove) {
    vector <ObjectInstance *> remaining = vector<ObjectInstance *>(objects.size());
    for(ObjectInstance *oi : objects){
        string oName = oi->name();
        if(find(toRemove.begin(), toRemove.end(), oName) == toRemove.end()){
            remaining.push_back(oi);
        }
    }
    return remaining;
}



vector<int> OOStateUtilities::initialComb(unsigned long k, unsigned long n) {
    vector<int> res = vector<int>(k);
    for(int i = 0; i < k; i++){
        res[i] = i;
    }
    return res;
}

/**
 * Iterates through combinations.
 * Modified code from: http://compprog.wordpress.com/tag/generating-combinations/
 * @param comb the last combination of elements selected
 * @param k number of elements in any combination (n choose k)
 * @param n number of possible elements (n choose k)
 * @return 0 when there are no more combinations; 1 when a new combination is generated
 */
int OOStateUtilities::nextComb(vector<int> comb, unsigned long k, unsigned long n) {

    unsigned long i = k-1;
    comb[i]++;

    while(i > 0 && comb[i] >= n-k+1+i){
        i--;
        comb[i]++;
    }

    if(comb[0] > n-k){
        return 0;
    }

    /* comb now looks like (..., x, n, n, n, ..., n).
    Turn it into (..., x, x + 1, x + 2, ...) */
    for(i = i+1; i < k; i++){
        comb[i] = comb[i-1] + 1;
    }
    return 1;
}
