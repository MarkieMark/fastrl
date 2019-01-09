//
// Mark Benjamin 6/1/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_OPTIONS_OPTION_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_OPTIONS_OPTION_H

#include "../../../mdp/core/action/action.hpp"
#include "../../../mdp/core/state/state.hpp"
#include "../episode.h"
#include "../../policy/support/action_prob.hpp"
#include "../../../mdp/singleagent/environment/environment.hpp"
#include "environment_option_outcome.hpp"

class Option : public Action {
public:
    virtual bool inInitiationSet(State *s) { throw runtime_error("Not Implemented"); }
    virtual Action * policy(State *s, Episode *history) { throw runtime_error("Not Implemented"); }
    virtual vector<ActionProb *> policyDistribution(State *s, Episode *history) { throw runtime_error("Not Implemented"); }
    virtual double probabilityOfTermination(State *s, Episode *history) { throw runtime_error("Not Implemented"); }
    virtual EnvironmentOptionOutcome * control(Environment *env, double discount) { throw runtime_error("Not Implemented"); }
    virtual bool markov() { throw runtime_error("Not Implemented"); }
    string toString() override { throw runtime_error("Not Implemented"); }
};

class OptionHelper {
    static EnvironmentOptionOutcome * control(Option *o, Environment * env, double discount);
};

#endif // FASTRL_BEHAVIOR_SINGLEAGENT_OPTIONS_OPTION_H
