#include "factored_model.h"
#include "../../core/state_transition_prob.hpp"
#include "statemodel/full_state_model.h"

/**
 * Mark Benjamin 31st May 2017
 */

FactoredModel::FactoredModel() = default;

FactoredModel::FactoredModel(FullStateModel * state_model, RewardFunction * rf_, TerminalFunction * tf_)
    : stateModel(state_model), rf(rf_), tf(tf_) { }

void FactoredModel::useRewardFunction(RewardFunction * rf_) {
    rf = rf_;
}

void FactoredModel::useTerminalFunction(TerminalFunction * tf_) {
    tf = tf_;
}

RewardFunction * FactoredModel::rewardFunction() {
    return rf;
}

TerminalFunction * FactoredModel::terminalFunction() {
    return tf;
}

EnvironmentOutcome * FactoredModel::sample(State * s, Action * a) {
    State * s_prime = stateModel->sample(s, a);
    double reward = rf->reward(s, a, s_prime);
    bool done = tf->isTerminal(s_prime);
    auto * eo = new EnvironmentOutcome(s, a, s_prime, reward, done);
    return eo;
}

vector<TransitionProb *> FactoredModel::transitions(State * s, Action * a) {
    vector<StateTransitionProb *> sps = stateModel->stateTransitions(s, a);
    vector<TransitionProb *> tps = vector<TransitionProb *>();
    for (StateTransitionProb * sp : sps) {
        double reward = rf->reward(s, a, sp->s);
        bool done = tf->isTerminal(sp->s);
        auto * tp = new TransitionProb(
                sp->p, new EnvironmentOutcome(s, a, sp->s, reward, done));
        tps.push_back(tp);
    }
    return tps;
}

FullStateModel * FactoredModel::getStateModel() {
    return stateModel;
}

void FactoredModel::setStateModel(FullStateModel * state_model) {
    stateModel = state_model;
}

RewardFunction * FactoredModel::getRf() {
    return rf;
}

void FactoredModel::setRf(RewardFunction * rf_) {
    rf = rf_;
}

TerminalFunction * FactoredModel::getTf() {
    return tf;
}

void FactoredModel::setTf(TerminalFunction * tf_) {
    tf = tf_;
}

bool FactoredModel::terminal(State * s) {
    return tf->isTerminal(s);
}
