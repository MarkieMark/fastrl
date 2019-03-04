/**
 * Mark Benjamin 1st June 2017
 */

#include <limits>
#include "epsilon_greedy.h"
#include "policy_utils.h"

EpsilonGreedy::EpsilonGreedy(QProvider * planner, double epsilon_) {
    qPlanner = planner;
    epsilon = epsilon_;
}

double EpsilonGreedy::getEpsilon() {
    return epsilon;
}

void EpsilonGreedy::setEpsilon(double epsilon_) {
    epsilon = epsilon_;
}

void EpsilonGreedy::setSolver(MDPSolverInterface * solver) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    qPlanner = dynamic_cast<QProvider*>(solver);
#pragma clang diagnostic pop
    if (qPlanner == nullptr) {
        throw runtime_error("Planner Not a QProvider / QComputablePlanner");
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc30-c"
Action * EpsilonGreedy::action(State * s) {
    vector<QValue *> qValues = qPlanner->qValues(s);
    double roll = drand48();
    if (roll <= epsilon) { // TODO NB unusual use of epsilon
        return qValues[rand() % qValues.size()]->a;
    }
    vector<QValue *> maxActions = vector<QValue *>();
    maxActions.push_back(qValues[0]);
    double maxQ = qValues[0]->q;
    for (auto it = qValues.begin() + 1; it != qValues.end(); ++it) {
        if ((*it)->q == maxQ) {
            maxActions.push_back(*it);
        } else if ((*it)->q > maxQ) {
            maxActions.clear();
            maxActions.push_back(*it);
            maxQ = (*it)->q;
        }
    }
    return maxActions[rand() % maxActions.size()]->a;
}
#pragma clang diagnostic pop

double EpsilonGreedy::actionProb(State * s, Action * a) {
    return PolicyUtils::actionProbFromEnum(this, s, a);
}

vector<ActionProb *> EpsilonGreedy::policyDistribution(State * s) {
    vector<QValue *> qValues = qPlanner->qValues(s);
    vector<ActionProb *> dist = vector<ActionProb *>();
    double maxQ = numeric_limits<double>::min();
    int nMax = 0;
    for (QValue * q : qValues) {
        if (q->q > maxQ) {
            maxQ = q->q;
            nMax = 1;
        } else if (q->q == maxQ) {
            nMax++;
        }
        auto *ap = new ActionProb(q->a, epsilon * (1. / qValues.size()));
        dist.push_back(ap);
    }
    for (int i = 0; i < dist.size(); i++) {
        QValue * q = qValues[i];
        if (q->q == maxQ) {
            dist[i]->pSelection += (1. - epsilon) / nMax;
        }
    }
    return dist;
}

bool EpsilonGreedy::definedFor(State * s) { return true; }