//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_MDP_CORE_OO_STATE_OO_STATE_UTILITIES_H
#define FASTRL_MDP_CORE_OO_STATE_OO_STATE_UTILITIES_H

#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include "object_instance.hpp"
#include "OO_state.hpp"
#include "OO_variable_key.hpp"
#include "key_container.hpp"

using namespace std;

class OOStateUtilities {
public:
    static ObjectInstance objectWithName(vector<ObjectInstance> objects, string name);
    static int objectIndexWithName(vector<ObjectInstance> objects, string name);
    static vector<KeyContainer *> flatStateKeys(OOState s);
    // TODO check assumption that all values are integers
    static int get(OOState s, KeyContainer * variableKey);
    static KeyContainer * generateOOVariableKey(KeyContainer *key);
    static map<string, vector<ObjectInstance *>> objectsByClass(OOState * s);
    static set<string> objectClassesPresent(OOState * s);
    static string ooStateTostring(OOState * s);
    static string objectInstanceToString(ObjectInstance * o);
    static vector<vector<string>> getPossibleBindingsGivenParamOrderGroups(
            OOState * s, vector<string> paramClasses, vector<string> paramOrderGroups);
    static vector<string> identifyUniqueClassesInParameters(vector<string> paramClasses);
    static void getPossibleRenameBindingsHelper(
            vector<vector<string>> res, vector<vector<string>> currentBindingSets,
            int bindIndex, vector<ObjectInstance *> remainingObjects,
            vector<string> uniqueOrderGroups, vector<string> paramClasses,
            vector<string> paramOrderGroups);
    static vector<string> getBindingFromCombinationSet(
            vector<vector<string>> comboSets,
            vector <string> orderGroupAssociatedWithSet,
            vector<string> orderGroups);
    static int getNumOccurrencesOfClassInParameters(
            string className, vector<string> paramClasses);
    static string parameterClassAssociatedWithOrderGroup(
            string orderGroup, vector<string> orderGroups,
            vector<string> paramClasses);
    static unsigned long numOccurrencesOfOrderGroup(
            string rename, vector<string> orderGroups);
    static vector<ObjectInstance *> objectsMatchingClass(
            vector<ObjectInstance *> objects, string className);
    static vector<vector<string>> getAllCombinationsOfObjects(
            vector <ObjectInstance *> objects, unsigned long k);
    static vector<string> getVectorOfBindingsFromCombination(
            vector <ObjectInstance *> objects, vector<int> comb);
    static vector<ObjectInstance *> objectVectorDifference(
            vector <ObjectInstance *> objects, vector <string> toRemove);
    static vector<int> initialComb(unsigned long k, unsigned long n);
    static int nextComb(vector<int> comb, unsigned long k, unsigned long n);
};

#endif // FASTRL_MDP_CORE_OO_STATE_OO_STATE_UTILITIES_H
