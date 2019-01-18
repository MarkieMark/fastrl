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
    virtual string actionName() { throw runtime_error("Action::actionName() Not Implemented"); }
    virtual Action * makeCopy() { throw runtime_error("Action::makeCopy() Not Implemented"); }
    virtual string to_string() { throw runtime_error("Action::to_string() Not Implemented"); }
};

#endif // FASTRL_MDP_CORE_ACTION_ACTION_HPP