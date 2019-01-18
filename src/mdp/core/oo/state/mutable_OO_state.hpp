/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_CORE_OO_STATE_MUTABLE_OO_STATE_HPP
#define FASTRL_MDP_CORE_OO_STATE_MUTABLE_OO_STATE_HPP

#include "../../state/mutable_state.hpp"
#include "OO_state.hpp"

class MutableOOState : virtual public OOState, virtual public MutableState {
public:
    virtual MutableOOState * addObject(ObjectInstance * o) { throw runtime_error("MutableOOState::addObject() Not Implemented"); }
    virtual MutableOOState * removeObject(string objectName) { throw runtime_error("MutableOOState::removeObject() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
    virtual MutableOOState * renameObject(string objectName, string newName) { throw runtime_error("MutableOOState::renameObject() Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
};


#endif // FASTRL_MDP_CORE_OO_STATE_MUTABLE_OO_STATE_HPP