//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#include "full_model.h"

vector<TransitionProb *> FullModelHelper::deterministicTransition(SampleModel * model, State * s, Action * a) {
    EnvironmentOutcome * eo = model->sample(s, a);
    return vector<TransitionProb *>({new TransitionProb(1., eo)});
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
EnvironmentOutcome * FullModelHelper::sampleByEnumeration(FullModel * model, State * s, Action * a) {
    vector<TransitionProb *> tps = model->transitions(s, a);
    double roll = static_cast<double>(rand()) / RAND_MAX; // NOLINT(cert-msc30-c)
    double sum = 0;
    for (TransitionProb * tp : tps) {
        sum += tp->p;
        if (roll < sum) {
            return tp->eo;
        }
    }
    /* todo added nullptr */
    return nullptr;
}
#pragma clang diagnostic pop
