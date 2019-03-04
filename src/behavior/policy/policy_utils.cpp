/**
 * Mark Benjamin 1st June 2017
 */

#include "policy_utils.h"
#include "../../mdp/singleagent/environment/simulated_environment.h"
#include "../singleagent/options/option.h"

bool PolicyUtils::rolloutsDecomposeOptions = true;

PolicyUtils::PolicyUtils() = default;

/**
 * Returns the probability of the policy taking action a in state s by searching for the action
 * in the returned policy distribution from the provided {@link EnumerablePolicy}.
 * @param p the {@link EnumerablePolicy}
 * @param s the state in which the action would be taken
 * @param a the action being queried
 * @return the probability of this policy taking action ga in state s
 */
double PolicyUtils::actionProbFromEnum(EnumerablePolicy * p, State * s, Action * a){
    vector<ActionProb *> probs = p->policyDistribution(s);
    if(probs.empty()) {
        throw runtime_error("Policy Not Defined");
    }
    for(ActionProb * ap : probs){
        if(ap->pa == a) { // TODO check equality test
            return ap->pSelection;
        }
    }
    return 0.;
}

/**
 * Searches the input distribution for the occurrence of the input action and returns its probability.
 * @param a the {@link Action} for which its probability in specified distribution should be returned.
 * @param distribution the probability distribution over actions.
 * @return the probability of selecting action ga according to the probability specified in distribution.
 */
double PolicyUtils::actionProbFromDistribution(Action *a, vector<ActionProb *> distribution){
    if(distribution.empty()) {
        throw runtime_error("Distribution Empty");
    }
    for(ActionProb * ap : distribution){
        if(ap->pa == a) { // TODO check equality test
            return ap->pSelection;
        }
    }
    return 0.;
}

/**
 * A helper method for defining deterministic policies. This method relies on the {@link Policy#action(State)} method being
 * implemented and will return a list of {@link ActionProb} objects with a single instance: the result of
 * the {@link Policy#action(State)} method with assigned probability 1.
 * @param p the {@link Policy}
 * @param s the state for which the action distribution should be returned.
 * @return a deterministic action distribution for the action returned by the getAction method.
 */
vector<ActionProb *> PolicyUtils::deterministicPolicyDistribution(Policy *p, State *s){
    Action * a = p->action(s);
    if(a == nullptr){
        throw runtime_error("Policy Not Defined");
    }
    auto * ap = new ActionProb(a, 1.);
    vector<ActionProb * > aps = vector<ActionProb *>();
    aps.push_back(ap);
    return aps;
}

/**
 * This is a helper method for stochastic policies. If the policy is stochastic, then rather than
 * having the policy define both the {@link Policy#action(State)} method and
 * {@link EnumerablePolicy#policyDistribution(State)} method,
 * the objects needs to only define the {@link EnumerablePolicy#policyDistribution(State)} method and
 * the {@link Policy#action(State)} method can simply
 * return the result of this method to sample an action.
 * @param p the {@link EnumerablePolicy}
 * @param s the input state from which an action should be selected.
 * @return an {@link Action} to take
 */
Action * PolicyUtils::sampleFromActionDistribution(EnumerablePolicy *p, State *s){
    double roll = drand48();
    vector<ActionProb *> probs = p->policyDistribution(s);
    if(probs.empty()){
        throw runtime_error("Policy Not Defined");
    }
    double sump = 0.;
    for(ActionProb * ap : probs){
        sump += ap->pSelection;
        if(roll < sump){
            return ap->pa;
        }
    }
    throw runtime_error("Policy Action Distribution Not Summing to 1");
}

/**
 * This method will return the an episode that results from following the given policy from state s. The episode will terminate
 * when the policy reaches a terminal state.
 * @param p the {@link Policy} to roll out
 * @param s the state from which to roll out the policy
 * @param model the model from which to sample
 * @return an EpisodeAnalysis object that records the events from following the policy.
 */
Episode * PolicyUtils::rollout(Policy *p, State *s, SampleModel *model){
    return rollout(p, new SimulatedEnvironment(model, s));
}

/**
 * This method will return the an episode that results from following the given policy from state s. The episode will terminate
 * when the policy reaches a terminal state or when the number of steps surpasses maxSteps.
 * @param p the {@link Policy} to roll out
 * @param s the state from which to roll out the policy
 * @param model the model from which to same state transitions
 * @param maxSteps the maximum number of steps to take before terminating the policy rollout.
 * @return an EpisodeAnalysis object that records the events from following the policy.
 */
Episode * PolicyUtils::rollout(Policy *p, State *s, SampleModel *model, int n_iterations){
    return rollout(p, new SimulatedEnvironment(model, s), n_iterations);
}

/**
 * Follows the policy in the given {@link burlap.mdp.singleagent.environment.Environment}. The policy will stop being followed once a terminal state
 * in the environment is reached.
 * @param p the {@link Policy}
 * @param env The {@link burlap.mdp.singleagent.environment.Environment} in which this policy is to be evaluated.
 * @return An {@link Episode} object specifying the interaction with the environment.
 */
Episode * PolicyUtils::rollout(Policy *p, Environment * env){
    auto * ea = new Episode(env->currentObservation());
    do{
        followThenSavePolicy(p, env, ea);
    }while(!env->isInTerminalState());
    return ea;
}

/**
 * Follows the policy in the given {@link burlap.mdp.singleagent.environment.Environment}. The policy will stop being followed once a terminal state
 * in the environment is reached or when the provided number of steps has been taken.
 * @param p the {@link Policy}
 * @param env The {@link burlap.mdp.singleagent.environment.Environment} in which this policy is to be evaluated.
 * @param numSteps the maximum number of steps to take in the environment.
 * @return An {@link Episode} object specifying the interaction with the environment.
 */
Episode * PolicyUtils::rollout(Policy * p, Environment * env, int n_iterations){
    auto * ea = new Episode(env->currentObservation());
    long nIterations;
    do{
        followThenSavePolicy(p, env, ea);
        nIterations = ea->nIterations();
    }while(!env->isInTerminalState() && nIterations < n_iterations);
    return ea;
}

/**
 * Follows this policy for one time step in the provided {@link burlap.mdp.singleagent.environment.Environment} and
 * records the interaction in the provided {@link Episode} object. If the policy
 * selects an {@link burlap.behavior.singleagent.options.Option}, then how the option's interaction in the environment
 * is recorded depends on the {@link #rolloutsDecomposeOptions} flag.
 * If {@link #rolloutsDecomposeOptions} is false, then the option is recorded as a single action. If it is true, then
 * the individual primitive actions selected by the environment are recorded.
 * @param p the {@link Policy}
 * @param env The {@link burlap.mdp.singleagent.environment.Environment} in which this policy should be followed.
 * @param ea The {@link Episode} object to which the action selection will be recorded.
 */
void PolicyUtils::followThenSavePolicy(Policy *p, Environment *env, Episode *e){
    //follow policy
    Action * a = p->action(env->currentObservation());
    if(a == nullptr){
        throw runtime_error("Policy Not Defined");
    }
    EnvironmentOutcome * eo = env->act(a);
    if(dynamic_cast<Option *>(a) && rolloutsDecomposeOptions){
        e->appendThenMergeEpisode(dynamic_cast<EnvironmentOptionOutcome* >(eo)->episode);
    } else{
        e->transition(a, eo->o_prime, eo->reward);
    }
}
