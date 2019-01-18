/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_MODEL_SAMPLE_MODEL_HPP
#define FASTRL_MDP_SINGLEAGENT_MODEL_SAMPLE_MODEL_HPP

#include "../environment/environment_outcome.hpp"

class SampleModel {
public:
    virtual EnvironmentOutcome * sample(State * s, Action * a) { throw runtime_error("SampleModel::sample() Not Implemented"); }
    virtual bool terminal(State * s) { throw runtime_error("SampleModel::terminal() Not Implemented"); }
};

#endif // FASTRL_MDP_SINGLEAGENT_MODEL_SAMPLE_MODEL_HPP
