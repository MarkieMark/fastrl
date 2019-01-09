#ifndef FASTRL_MDP_CORE_OO_STATE_OBJECT_INSTANCE_HPP
#define FASTRL_MDP_CORE_OO_STATE_OBJECT_INSTANCE_HPP

#include <string>
#include "../../state/state.hpp"

/**
 * Mark Benjamin 30th May 2017
 */

class ObjectInstance : public State {
public:
    virtual string className() { throw runtime_error("Not Implemented"); }
    virtual string name() { throw runtime_error("Not Implemented"); }
    virtual ObjectInstance* copyWithName(string object_name) {throw runtime_error("Not Implemented"); } // NOLINT(performance-unnecessary-value-param)

    ObjectInstance() = default;
};

#endif // FASTRL_MDP_CORE_OO_STATE_OBJECT_INSTANCE_HPP