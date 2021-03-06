#ifndef FASTRL_MDP_CORE_OO_STATE_STATE_HPP
#define FASTRL_MDP_CORE_OO_STATE_STATE_HPP

#include "../../state/state.hpp"
#include "object_instance.hpp"

/**
 * Mark Benjamin 30th May 2017
 */

class OOState : virtual State {
public:
    int numObjects = -1;
    virtual ObjectInstance * object(string object_name) const { throw runtime_error("OOState::object() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
    virtual vector<ObjectInstance *> objects() const { throw runtime_error("OOState::objects() Not Implemented"); }
    virtual vector<ObjectInstance *> objectsOfClass(string object_class) const { throw runtime_error("OOState::objectsOfClass() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
};

#endif // FASTRL_MDP_CORE_OO_STATE_STATE_HPP
