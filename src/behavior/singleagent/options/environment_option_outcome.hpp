/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_OPTIONS_ENVIRONMENT_OPTION_OUTCOME_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_OPTIONS_ENVIRONMENT_OPTION_OUTCOME_HPP

#include <cmath>
#include "../../../mdp/singleagent/environment/environment_outcome.hpp"
#include "../episode.h"

class EnvironmentOptionOutcome : public EnvironmentOutcome {
public:
    double discount;
    Episode * episode;
    EnvironmentOptionOutcome(State *s, Action *a, State *sp, double reward, bool done, double discountFactor, Episode * episode_)
        : EnvironmentOutcome(s, a, sp, reward, done)
    {
        discount = pow(discountFactor, episode->actionSequence.size());
        episode = episode_;
    }
    long nIterations() override { return episode->actionSequence.size(); }
};

#endif // FASTRL_BEHAVIOR_SINGLEAGENT_OPTIONS_ENVIRONMENT_OPTION_OUTCOME_HPP