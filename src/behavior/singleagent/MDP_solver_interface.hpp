/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_MDP_SOLVER_INTERFACE_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_MDP_SOLVER_INTERFACE_HPP

#include "../../mdp/singleagent/SA_domain.h"

class MDPSolverInterface {
    virtual void solverInit(SADomain * domain_, double gamma_ /*, HashableStateFactory factory */) { throw runtime_error("Not Implemented"); }
    virtual void resetSolver() { throw runtime_error("Not Implemented"); }
    virtual void setDomain(SADomain *domain_) { throw runtime_error("Not Implemented"); }
    virtual void setModel(SampleModel *model_) { throw runtime_error("Not Implemented"); }
    virtual SampleModel * getModel() { throw runtime_error("Not Implemented"); }
    virtual Domain * getDomain() { throw runtime_error("Not Implemented"); }
    virtual void addActionType(ActionType * a) { throw runtime_error("Not Implemented"); }
    virtual void setActionTypes(vector<ActionType *> action_types) { throw runtime_error("Not Implemented"); } // NOLINT(performance-unnecessary-value-param)
    virtual vector<ActionType *> getActionTypes() { throw runtime_error("Not Implemented"); }
//    virtual void setHashingFactory(HashableStateFactory * factory) { throw runtime_error("Not Implemented"); }
//    virtual HashableStateFactory * getHashingFactory() { throw runtime_error("Not Implemented"); }
    virtual double getGamma() { throw runtime_error("Not Implemented"); }
    virtual void setGamma(double gamma_) { throw runtime_error("Not Implemented"); }
    virtual void setDebugCode(int code) { throw runtime_error("Not Implemented"); }
    virtual int getDebugCode() { throw runtime_error("Not Implemented"); }
    virtual void toggleDebugPrinting(bool active) { throw runtime_error("Not Implemented"); }
};

#endif // FASTRL_BEHAVIOR_SINGLEAGENT_MDP_SOLVER_INTERFACE_HPP