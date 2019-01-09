//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#include "full_state_model.h"

vector<StateTransitionProb *> FullStateModelHelper::deterministicTransition(
        SampleStateModel * model, State * s, Action * a) {
    return vector<StateTransitionProb *>({new StateTransitionProb(model->sample(s, a), 1.)});
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc30-c"
State * FullStateModelHelper::sampleByEnumeration(FullStateModel * model, State * s, Action * a) {
    vector<StateTransitionProb *> tps = model->stateTransitions(s, a);
    double roll = static_cast<double>(rand()) / RAND_MAX;
    double sum = 0;
    for (StateTransitionProb * tp : tps) {
        sum += tp->p;
        if (roll < sum) {
            return tp->s;
        }
    }
    /* todo added nullptr */
    return nullptr;
}
#pragma clang diagnostic pop
