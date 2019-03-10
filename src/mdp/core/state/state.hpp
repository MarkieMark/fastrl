/**
 * Mark Benjamin 30th May 2017
 */

#ifndef FASTRL_MDP_CORE_STATE_STATE_HPP
#define FASTRL_MDP_CORE_STATE_STATE_HPP

#include <vector>
#include <string>
#include <functional>
#include "../../../include/macros.h"
#include "../oo/state/OO_variable_key.hpp"
#include "../oo/state/key_container.hpp"

using namespace std;

class State {
public:
    bool equalityII = true; // identifier independence; may be false for relational domains
    size_t _hash = 0;

    virtual vector<KeyContainer *> variableKeys() const { throw runtime_error("State::variableKeys() Not Implemented"); }

    virtual int getIntValue(KeyContainer * variableKey) const { throw runtime_error("State::getIntValue() Not Implemented"); }

    virtual State * makeCopy() { throw runtime_error("State::makeCopy() Not Implemented"); }

    virtual bool operator==(const State &comp) const {
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

    virtual bool operator>(const State &comp) const {
        // todo account for potential hash collisions
        return id() > comp.id();
    }

    virtual bool operator<(const State &comp) const {
        return !operator>(comp);
    }

    inline void hash_func(uint32_t * current, uint32_t in) const {
        *current ^= in + 0x9e3779b9U + (*current << 6U) + (*current >> 2U);
    }

    virtual unsigned long id() const {
//        D("State " << this);
        vector<KeyContainer *> myKeys = variableKeys();
        uint32_t my_hash_code = 0;
        int i;
        for (i = 0; i < myKeys.size(); i++) {
            hash_func(&my_hash_code, (uint32_t)getIntValue(myKeys[i]));
//            D("Key " << i << " " << myKeys[i] << " " << myKeys[i]->to_string() << " Val " << getIntValue(myKeys[i]) << " hc " << my_hash_code);
        }
        return my_hash_code;
    }

    virtual void update_id() {
        _hash = id();
    }

    virtual string to_string() { return "State base class"; }
};

struct StateHashFunction {
public:
    size_t operator()(const State * s) const {
        return s->id();
    }
};

struct StateEqualFunction {
public:
    bool operator() (const State * s1, const State * s2) const {
        return s1->id() == s2->id();
    }
};

#endif // FASTRL_MDP_CORE_STATE_STATE_HPP
