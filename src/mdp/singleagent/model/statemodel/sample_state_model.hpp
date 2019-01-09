/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_MODEL_STATEMODEL_SAMPLE_STATE_MODEL_HPP
#define FASTRL_MDP_SINGLEAGENT_MODEL_STATEMODEL_SAMPLE_STATE_MODEL_HPP

#include "../../../core/action/action.hpp"
#include "../../../core/state/state.hpp"

class SampleStateModel {
public:
    virtual State * sample(State * s, Action * a) { throw runtime_error("Not Implemented"); }
};

#endif // FASTRL_MDP_SINGLEAGENT_MODEL_STATEMODEL_SAMPLE_STATE_MODEL_HPP