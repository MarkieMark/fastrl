//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_MDP_SINGLEAGENT_MODEL_FACTORED_MODEL_H
#define FASTRL_MDP_SINGLEAGENT_MODEL_FACTORED_MODEL_H

#include <iostream>
#include "task_factored_model.hpp"
#include "full_model.h"
#include "../model/statemodel/sample_state_model.hpp"
#include "statemodel/full_state_model.h"

class FactoredModel : public TaskFactoredModel, public FullModel {
private:
    FullStateModel * stateModel;
    RewardFunction * rf;
    TerminalFunction * tf;
public:
    FactoredModel();
    FactoredModel(FullStateModel * state_model, RewardFunction * rf_, TerminalFunction * tf_);
    void useRewardFunction(RewardFunction * rf_) override;
    void useTerminalFunction(TerminalFunction * tf_) override;
    RewardFunction * rewardFunction() override;
    TerminalFunction * terminalFunction() override;
    EnvironmentOutcome * sample(State * s, Action * a) override;
    vector<TransitionProb *> transitions(State * s, Action * a) override;
    FullStateModel * getStateModel();
    void setStateModel(FullStateModel * state_model);
    RewardFunction * getRf();
    void setRf(RewardFunction * rf_);
    TerminalFunction * getTf();
    void setTf(TerminalFunction * tf_);
    bool terminal(State * s) override;
};


#endif // FASTRL_MDP_SINGLEAGENT_MODEL_FACTORED_MODEL_H
