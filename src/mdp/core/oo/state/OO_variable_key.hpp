/**
 * Mark Benjamin 31st May 2017
 */

#ifndef MDP_CORE_OO_STATE_OO_VARIABLE_KEY_HPP
#define MDP_CORE_OO_STATE_OO_VARIABLE_KEY_HPP

#include <string>
#include <sstream>

using namespace std;

class OOVariableKey {
public:
    string objName;
    string objVarKey;

    explicit OOVariableKey(const string &strVersion) {
        if (strVersion.empty()) { return; }
        unsigned long ind = strVersion.find(':');
        if (ind == -1) {
            throw runtime_error("String Representation Not Parseable");
        }
        objName = strVersion.substr(0, ind);
        objVarKey = strVersion.substr(ind + 1);
    }

    explicit OOVariableKey(string obj_name, string obj_var_key)
            : objName(move(obj_name)), objVarKey(move(obj_var_key)) { }

    string to_string() {
        return objName + ":" + objVarKey;
    }
};


#endif // MDP_CORE_OO_STATE_OO_VARIABLE_KEY_HPP
