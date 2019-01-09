/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_MDP_SOLVER_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_MDP_SOLVER_HPP

#include "MDP_solver_interface.hpp"
#include "../../mdp/core/action/action_utils.h"

class MDPSolver : public MDPSolverInterface {
public:
    SADomain *domain;
    SampleModel *model;
//    HashableStateFactory * hashingFactory;
    double gamma;
    vector<ActionType *> actionTypes = vector<ActionType *>();
    int debugCode;
    bool usingOptionModel = false;

    void resetSolver() override { throw runtime_error("Not Implemented"); }
    void solverInit(SADomain * domain_, double gamma_/*, HashableStateFactory * factory*/) override {
        gamma = gamma_;
//        hashingFactory = factory;
        setDomain(domain);
    }
    void addActionType(ActionType * a) override {
        bool contains = false;
        for (ActionType *at : actionTypes) {
            if (at == a) { // TODO compare content rather than pointer
                contains = true;
            }
        }
        if (!contains) actionTypes.push_back(a);
    }
    void setModel(SampleModel *model_) override {
        model = model_;
    }
    SampleModel * getModel() override {
        return model;
    }
    void setActionTypes(vector<ActionType *> action_types) override {
        actionTypes = action_types;
    }
    vector<ActionType *> getActionTypes() override {
        return actionTypes; // TODO maybe should copy
    }
//    void setHashingFactory(HashableStateFactory * factory) {
//        hashingFactory = factory;
//    }
//    HashableStateFactory getHashingFactory() {
//        return hashingFactory;
//    }
    double getGamma() override { return gamma; }
    void setGamma(double gamma_) override { gamma = gamma_; }
    void setDebugCode(int code) override { debugCode = code; }
    int getDebugCode() override { return debugCode; }
    void toggleDebugPrinting(bool active) override {
//        DPrint::toggleCode(debugCode, active);
    }
    void setDomain(SADomain * domain_) override {
        domain = domain_;
        if (domain == nullptr) return;
        model = domain_->getModel();
        vector<ActionType *> action_types = domain->getActionTypes();
        actionTypes = vector<ActionType *>(action_types.begin(), action_types.end());
    }
    Domain * getDomain() override { return domain; }
//    HashableState * stateHash(State *s) { return hashingFactory.hashState(s); }
    vector<Action *> applicableActions(State *s) {
        return ActionUtils::allApplicableActionsForTypes(actionTypes, s);
    }
};

#endif // FASTRL_BEHAVIOR_SINGLEAGENT_MDP_SOLVER_HPP
