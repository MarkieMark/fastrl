/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_MODEL_TRANSITION_PROB_HPP
#define FASTRL_MDP_SINGLEAGENT_MODEL_TRANSITION_PROB_HPP

#include "../environment/environment_outcome.hpp"

class TransitionProb {
public:
    double p = 0.;
    EnvironmentOutcome* eo = nullptr;
    TransitionProb() = default;
    TransitionProb(double p_, EnvironmentOutcome * eo_) : p(p_), eo(eo_) { }
};

#endif // FASTRL_MDP_SINGLEAGENT_MODEL_TRANSITION_PROB_HPP