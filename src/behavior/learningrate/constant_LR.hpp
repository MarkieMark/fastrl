/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_LEARNINGRATE_CONSTANT_LR_HPP
#define FASTRL_BEHAVIOR_LEARNINGRATE_CONSTANT_LR_HPP

#include "learning_rate.hpp"

class ConstantLR : public LearningRate {
public:
    double learningRate;
    explicit ConstantLR(double learning_rate = 0.1) {
        learningRate = learning_rate;
    }
    double peekAtLearningRate(State *s, Action *a) override {
        return learningRate;
    }
    double pollLearningRate(int agentTime, State *s, Action *a) override {
        return learningRate;
    }
    void resetDecay() override {}
    double peekAtLearningRate(int featureId) override {
        return learningRate;
    }
    double pollLearningRate(int agentTime, int featureId) override {
        return learningRate;
    }
};

#endif // FASTRL_BEHAVIOR_LEARNINGRATE_CONSTANT_LR_HPP