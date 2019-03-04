/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_LEARNING_AGENT_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_LEARNING_AGENT_HPP

#include "../../../mdp/singleagent/environment/environment.hpp"
#include "../episode.h"

class LearningAgent {
public:
    virtual Episode * runLearningEpisode(Environment *env) { throw runtime_error("LearningAgent::runLearningEpisode(env) Not Implemented"); }
    virtual Episode * runLearningEpisode(Environment *env, int maxIterations) { throw runtime_error("LearningAgent::runLearningEpisode(env, maxIter) Not Implemented"); }
};

#endif // FASTRL_BEHAVIOR_SINGLEAGENT_LEARNING_LEARNING_AGENT_HPP