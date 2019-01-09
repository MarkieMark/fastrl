/**
 * Mark Benjamin 1st June 2017
 */

#include <limits>
#include <cmath>
#include "Q_provider.h"

double QProviderHelper::maxQ(QProvider *qSource, State *s) {
    vector<QValue *> qs = qSource->qValues(s);
    if (qs.empty()) {
        return 0;
    }
    double max = numeric_limits<double>::min();
    for (QValue * q : qs) {
        max = fmax(q->q, max);
    }
    return max;
}

double QProviderHelper::policyValue(QProvider *qSource, State *s, EnumerablePolicy *p) {
    double val = 0.;
    vector<ActionProb *> aps = p->policyDistribution(s);
    if (aps.empty()) {
        return 0.;
    }
    for (ActionProb * ap : aps) {
        double q = qSource->qValue(s, ap->pa);
        val += q * ap->pSelection;
    }
    return val;
}