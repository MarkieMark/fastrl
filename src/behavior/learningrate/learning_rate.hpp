/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_LEARNINGRATE_LEARNING_RATE_HPP
#define FASTRL_BEHAVIOR_LEARNINGRATE_LEARNING_RATE_HPP

#include "../../mdp/core/state/state.hpp"
#include "../../mdp/core/action/action.hpp"

class LearningRate {
public:
    virtual double peekAtLearningRate(State *s, Action *a) { throw runtime_error("LearningRate::peekAtLearningRate(state, action) Not Implemented"); }
    virtual double pollLearningRate(int agentTime, State *s, Action *a) { throw runtime_error("LearningRate::pollLearningRate(state, action) Not Implemented"); }
    virtual double peekAtLearningRate(int featureId) { throw runtime_error("LearningRate::peekAtLearningRate(featureId) Not Implemented"); }
    virtual double pollLearningRate(int agentTime, int featureId) { throw runtime_error("LearningRate::pollLearningRate(featureId) Not Implemented"); }
    virtual void resetDecay() { throw runtime_error("LearningRate::resetDecay() Not Implemented"); }
};

#endif // FASTRL_BEHAVIOR_LEARNINGRATE_LEARNING_RATE_HPP