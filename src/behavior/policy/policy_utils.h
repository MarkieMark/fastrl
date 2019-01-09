//
// Mark Benjamin 6/1/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_BEHAVIOR_POLICY_UTILS_H
#define FASTRL_BEHAVIOR_POLICY_UTILS_H

#include "enumerable_policy.hpp"
#include "../singleagent/episode.h"
#include "../../mdp/singleagent/model/sample_model.hpp"
#include "../../mdp/singleagent/environment/environment.hpp"

class PolicyUtils {
private:
    PolicyUtils();
    /**
 * Indicates whether rollout methods will decompose {@link fastrl.behavior.singleagent.options.Option}
 * selections into the primitive {@link Action} objects they execute and annotate them with the name
 * of the calling {@link fastrl.behavior.singleagent.options.Option} in the returned
 * {@link Episode}. Default value is true.
 */
public:
    static bool rolloutsDecomposeOptions;
    static double actionProbFromEnum(EnumerablePolicy * p, State *s, Action *a);
    static double actionProbFromDistribution(Action *a, vector<ActionProb *> distribution);
    static vector<ActionProb *> deterministicPolicyDistribution(Policy *p, State *s);
    static Action * sampleFromActionDistribution(EnumerablePolicy *p, State *s);
    static Episode * rollout(Policy *p, State *s, SampleModel *model);
    static Episode * rollout(Policy *p, State *s, SampleModel *model, int n_iterations);
    static Episode * rollout(Policy *p, Environment * env);
    static Episode * rollout(Policy *p, Environment * env, int n_iterations);
    static void followThenSavePolicy(Policy *p, Environment * env, Episode *e);
};


#endif //FASTRL_BEHAVIOR_POLICY_UTILS_H
