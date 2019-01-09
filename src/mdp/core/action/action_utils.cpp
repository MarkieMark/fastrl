/**
 * Mark Benjamin 1st June 2017
 */

#include "action_utils.h"

vector<Action *> ActionUtils::allApplicableActionsForTypes(vector < ActionType * > actionTypes, State * s) {
    vector<Action *> ret = vector<Action *>();
    for (ActionType *a : actionTypes) {
        vector<Action *> applicable = a->allApplicableActions(s);
        ret.insert(ret.end(), applicable.begin(), applicable.end());
    }
    return ret;
}