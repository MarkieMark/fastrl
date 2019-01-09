/**
 * Mark Benjamin 30th May 2017
 */

#ifndef FASTRL_MDP_CORE_ACTION_ACTION_HPP
#define FASTRL_MDP_CORE_ACTION_ACTION_HPP

#include <string>
#include <stdexcept>

using namespace std;

class Action {
public:
    virtual string actionName() { throw runtime_error("Not Implemented"); }
    virtual Action * makeCopy() { throw runtime_error("Not Implemented"); }
    virtual string toString() { throw runtime_error("Not Implemented"); }
};

#endif // FASTRL_MDP_CORE_ACTION_ACTION_HPP