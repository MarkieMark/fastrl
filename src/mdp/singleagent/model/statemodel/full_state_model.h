/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_MODEL_STATEMODEL_FULL_STATE_MODEL_HPP
#define FASTRL_MDP_SINGLEAGENT_MODEL_STATEMODEL_FULL_STATE_MODEL_HPP

#include "sample_state_model.hpp"
#include "../../../core/state_transition_prob.hpp"


class FullStateModel : public SampleStateModel {
public:
    virtual vector<StateTransitionProb *> stateTransitions(State * s, Action * a) { throw runtime_error("Not Implemented"); }
};

class FullStateModelHelper {
public:
    static vector<StateTransitionProb *> deterministicTransition(
            SampleStateModel * model, State * s, Action * a);
    static State * sampleByEnumeration(FullStateModel * model, State * s, Action * a);
};

#endif // FASTRL_MDP_SINGLEAGENT_MODEL_STATEMODEL_FULL_STATE_MODEL_HPP