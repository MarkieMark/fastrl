/**
 * Mark Benjamin 30th May 2017
 */

#ifndef FASTRL_MDP_CORE_OO_STATE_OBJECT_INSTANCE_HPP
#define FASTRL_MDP_CORE_OO_STATE_OBJECT_INSTANCE_HPP

#include <string>
#include "../../state/state.hpp"

class ObjectInstance : public State {
public:
    virtual string className() { throw runtime_error("ObjectInstance::className() Not Implemented"); }
    virtual string name() { throw runtime_error("ObjectInstance::name() Not Implemented"); }
    virtual ObjectInstance* copyWithName(string object_name) {throw runtime_error("ObjectInstance::copyWithName() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)

    ObjectInstance() = default;
};

#endif // FASTRL_MDP_CORE_OO_STATE_OBJECT_INSTANCE_HPP