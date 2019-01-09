#include "greedy_Q_policy.h"
#include "policy_utils.h"

/**
 * Mark Benjamin 1st June 2017
 */

GreedyQPolicy::GreedyQPolicy(QProvider *provider) {
    qplanner = provider;
}

void GreedyQPolicy::setSolver(MDPSolverInterface *solver) {
    // TODO c++ casting may need to follow hierarchy paths
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    qplanner = dynamic_cast<QProvider*>(solver);
#pragma clang diagnostic pop
    if (qplanner == nullptr){
        throw runtime_error("Planner is not a QProvider / QComputablePlanner");
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc30-c"
Action* GreedyQPolicy::action(State *s) {
    vector<QValue *> qValues = qplanner->qValues(s);
    vector<QValue *> maxActions = vector<QValue *>();
    maxActions.push_back(qValues[0]);
    double maxQ = qValues[0]->q;
    for (auto it = qValues.begin() + 1; it < qValues.end(); ++it) {
        if ((*it)->q == maxQ) {
            maxActions.push_back((*it));
        } else if ((*it)->q > maxQ){
            maxActions.clear();
            maxActions.push_back((*it));
            maxQ = (*it)->q;
        }
    }
    return maxActions[rand() % maxActions.size()]->a;
}
#pragma clang diagnostic pop

double GreedyQPolicy::actionProb(State *s, Action *a) {
    return PolicyUtils::actionProbFromEnum(this, s, a);
}

vector<ActionProb *> GreedyQPolicy::policyDistribution(State *s) {
    vector<QValue *> qValues = qplanner->qValues(s);
    long nMax = 1;
    double maxQ = qValues[0]->q;
    for (auto it = qValues.begin() + 1; it < qValues.end(); ++it) {
        if ((*it)->q == maxQ) {
            nMax++;
        } else if ((*it)->q > maxQ) {
            nMax = 1;
            maxQ = (*it)->q;
        }
    }
    vector<ActionProb *> res = vector<ActionProb *>();
    double uniformMax = 1./(double)nMax;
    double p;
    for (QValue * q : qValues) {
        p = 0;
        if (q->q == maxQ) {
            p = uniformMax;
        }
        auto * ap = new ActionProb(q->a, p);
        res.push_back(ap);
    }
    return res;
}

bool GreedyQPolicy::definedFor(State *s) { return true; }
