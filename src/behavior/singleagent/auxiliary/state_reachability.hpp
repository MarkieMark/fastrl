
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_STATE_REACHABILITY_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_STATE_REACHABILITY_HPP

#include <unordered_set>
#include "../../../mdp/singleagent/model/full_model.h"
#include "../../../mdp/core/action/action_utils.h"
#include "../../policy/enumerable_policy.hpp"

using namespace std;

class StateReachability {
private:
    StateReachability() = default;
public:
    static vector<State *> getReachableStates(State * from, SADomain * inDomain) {
        if(dynamic_cast<FullModel *>(inDomain->getModel()) == nullptr){
            throw runtime_error("StateReachability::getReachableStates() State reachability requires"
                                " a domain with a FullModel, but one is not provided");
        }
        auto * model = dynamic_cast<FullModel *>(inDomain->getModel());
        unordered_set<State *, StateHashFunction, StateEqualFunction> states;
        vector<ActionType *> actionTypes = inDomain->getActionTypes();
        int nGenerated = 0;
        vector<State *> openList;
        openList.push_back(from);
        states.insert(from);
        auto firstTime = chrono::system_clock::now();
        auto lastTime = firstTime;
        chrono::seconds oneSecond(1);
        while (!openList.empty()) {
            State * s = openList.back();
            openList.pop_back();
            vector<Action *> gas = ActionUtils::allApplicableActionsForTypes(actionTypes, s);
            for (Action * ga : gas) {
                vector<TransitionProb *> tps = model->transitions(s, ga);
                nGenerated += tps.size();
                for (TransitionProb * tp : tps) {
                    State * ns = tp->eo->o_prime;
                    if (ns != nullptr && dynamic_cast<NullState *>(ns) == nullptr
                            && states.insert(ns).second && !tp->eo->done) {
                        openList.push_back(ns);
                    }
                }
            }
            auto currentTime = chrono::system_clock::now();
            if ((currentTime - lastTime) >= oneSecond) {
                D("Num generated: " << nGenerated << " Unique: " << (states.size()) <<
                                   " time: " << (chrono::duration_cast<chrono::seconds>(currentTime - firstTime)).count());
                lastTime = currentTime;
            }
        }
        auto currentTime = chrono::system_clock::now();
        D("Num generated: " << nGenerated << "; num unique: " << states.size() <<
            " time: " << (chrono::duration_cast<chrono::milliseconds>(currentTime - firstTime)).count() << "ms");
        return vector<State *>(states.begin(), states.end());
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_STATE_REACHABILITY_HPP
