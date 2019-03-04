/*
 * Mark Benjamin 04 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include <iostream>
#include "DFS.h"
#include "../../../../../../include/macros.h"
#include "../../../../options/option_type.hpp"
#include "../../../../options/option.h"

DFS::DFS(SADomain * domain, StateConditionTest * gc, int max_depth, bool maintain_closed, bool options_first) {
    deterministicPlannerInit(domain, gc);
    maxDepth = max_depth;
    maintainClosed = maintain_closed;
    if (options_first) {
        setOptionsFirst();
    }
//    rand = RandomFactory.getMapped(0);
}

SDPlannerPolicy * DFS::planFromState(State * initialState) {
    // todo check equality test
    if(optionsFirst){
        sortActionsWithOptionsFirst();
    }
    numVisited = 0;
    if (internal_policy.find(initialState) != internal_policy.end()) {
        return new SDPlannerPolicy(this); //no need to plan since this is already solved
    }
    set<State *> statesOnPath = set<State *>();
    auto * sn = new SearchNode(initialState);
    SearchNode * result = dfs(sn, 0, statesOnPath);
    if (result != nullptr) {
        encodePlanIntoPolicy(result);
    }
    D("Num visited: " << numVisited);
    return new SDPlannerPolicy(this);
}

void DFS::resetSolver(){
    DeterministicPlanner::resetSolver();
    numVisited = 0;
}

SearchNode * DFS::dfs(SearchNode * n, int depth, set<State *> statesOnPath) {
    // todo check equality tests
    numVisited++;
    if (goal_condition->satisfies(n->s)) {
        //found goal!
        return n;
    }
    if (maxDepth != -1 && depth > maxDepth) {
        return nullptr; //back track
    }
    if (model->terminal(n->s)) {
        return nullptr; //treat as end of a path
    }
    //otherwise we need to generate successors and search them
    statesOnPath.insert(n->s);
    //shuffle actions for a random walk, but keep options as priority if set that way
    vector<Action *> gas = applicableActions(n->s);
    if (optionsFirst) {
        int no = numOptionsInGAs(gas);
        shuffleGroundedActions(gas, 0, no);
        shuffleGroundedActions(gas, no, int(gas.size()));
    } else {
        shuffleGroundedActions(gas, 0, int(gas.size()));
    }
    //generate a search successors from the order of grounded actions
    for(Action * ga : gas){
        State * sp = model->sample(n->s, ga)->o_prime;
        if (statesOnPath.find(sp) == statesOnPath.end()) {
            auto * snp = new SearchNode(sp, ga, n);
            SearchNode * result = dfs(snp, depth + 1, statesOnPath);
            if (result != nullptr) {
                return result;
            }
        }
    }
    //no successors found a solution
    if (!maintainClosed) {
        statesOnPath.erase(n->s);
    }
    return nullptr;
}

void DFS::setOptionsFirst() {
    optionsFirst = true;
    sortActionsWithOptionsFirst();
}

int DFS::numOptionsInGAs(vector<Action *> gas) {
    for(int i = 0; i < gas.size(); i++){
        if(dynamic_cast<Option *>(gas[i]) != nullptr){
            return i;
        }
    }
    return int(gas.size());
}

void DFS::shuffleGroundedActions(vector<Action *> gas, int s, int e) {
    int r = e - s;
    for(int i = s; i < e; i++){
        Action * ga = gas[i];
        int j = int(drand48() * r) + s;
        gas[i] = gas[j];
        gas[j] = ga;
    }

}

void DFS::sortActionsWithOptionsFirst() {
    vector<ActionType *> s_actions = vector<ActionType *>(actionTypes.size());
    for (ActionType * a : actionTypes){
        if (dynamic_cast<OptionType *>(a) != nullptr) {
            s_actions.push_back(a);
        }
    }
    for(ActionType * a : actionTypes){
        if(dynamic_cast<OptionType *>(a) == nullptr) {
            s_actions.push_back(a);
        }
    }
    actionTypes = s_actions;
}
