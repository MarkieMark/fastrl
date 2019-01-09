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

    explicit OOVariableKey(string strVersion = "", string obj_name = "", string obj_var_key = "") // NOLINT(performance-unnecessary-value-param)
        : objName(move(obj_name)), objVarKey(move(obj_var_key)) {
        if (strVersion.empty()) { return; }
        unsigned long ind = strVersion.find(':');
        if (ind == -1) {
            throw runtime_error("String Representation Not Parseable");
        }
        objName = strVersion.substr(0, ind);
        objVarKey = strVersion.substr(ind + 1);
    }

    string toString() {
        stringstream s;
        s << objName << ":" << objVarKey;
        return s.str();
    }
};


#endif // MDP_CORE_OO_STATE_OO_VARIABLE_KEY_HPP
