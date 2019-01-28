/**
 * Mark Benjamin 30th May 2017
 */

#ifndef FASTRL_MDP_CORE_STATE_STATE_HPP
#define FASTRL_MDP_CORE_STATE_STATE_HPP

#include <vector>
#include <string>
#include "../oo/state/OO_variable_key.hpp"
#include "../oo/state/key_container.hpp"

using namespace std;

class State {
public:
    virtual vector<KeyContainer *> variableKeys() { throw runtime_error("State::variableKeys() Not Implemented"); }
    virtual int getIntValue(KeyContainer * variableKey) { throw runtime_error("State::getIntValue() Not Implemented"); }
    virtual State * makeCopy() { throw runtime_error("State::makeCopy() Not Implemented"); }
    virtual bool operator==(State &comp) {
        vector<KeyContainer *> myKeys = variableKeys();
        vector<KeyContainer *> compKeys = comp.variableKeys();
        if (myKeys.size() != compKeys.size()) return false;
        for (int i = 0; i < myKeys.size(); i++) {
            // TODO check assumption that all values are integers
            if ((getIntValue(myKeys[i]) !=
                    comp.getIntValue(myKeys[i])) ||
                (getIntValue(compKeys[i]) !=
                        comp.getIntValue(compKeys[i])))
                return false;
        }
        return true;
    }
    virtual string to_string() { return "State base class"; }
};

#endif // FASTRL_MDP_CORE_STATE_STATE_HPP
