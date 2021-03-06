/**
 * Mark Benjamin 1st June 2017
 */

#include "option.h"
#include "../../policy/support/annotated_action.hpp"

EnvironmentOptionOutcome * OptionHelper::control(Option *o, Environment *env, double discountFactor) {
    State * initial = env->currentObservation();
    State * current = initial;
    auto * episode = new Episode(current);
    auto * history = new Episode(current);
    double roll;
    double pTransition;
    long nIterations = 0;
    double reward = 0.;
    double cDiscount  =1.;
    do {
        Action *a = o->policy(current, history);
        EnvironmentOutcome * eo = env->act(a);
        nIterations++;
        reward += cDiscount * eo->reward;
        current = eo->o_prime;
        cDiscount *= discountFactor;
        history->transition(a, eo->o_prime, eo->reward);
        stringstream s;
        s << o->to_string() << "(" << nIterations << ")";
        AnnotatedAction * annotatedAction = new AnnotatedAction(a, s.str());
        episode->transition(annotatedAction, eo->o_prime, reward);
        pTransition = o->probabilityOfTermination(eo->o_prime, history);
        roll = drand48();
    } while ((roll > pTransition) && (!env->isInTerminalState()));
    auto * eoo = new EnvironmentOptionOutcome(
            initial, o, current, reward, env->isInTerminalState(), discountFactor, episode);
    return eoo;
}
