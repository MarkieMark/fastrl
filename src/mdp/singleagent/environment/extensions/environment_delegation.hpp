/*
 * Mark Benjamin 26th February 2019
 * (c) February 26th 2019 Mark Benjamin
 */

#include "../environment.hpp"

class EnvironmentDelegation : public Environment {
public:
    virtual Environment  * getEnvironmentDelegate() { throw runtime_error("EnvironmentDelegation::getEnvironmentDelegate() Not Implemented");}
    virtual void setEnvironmentDelegate(Environment * delegate) {throw runtime_error("EnvironmentDelegation::setEnvironmentDelegate() Not Implemented");}
};

class EnvironmentDelegationHelper {

protected:
    EnvironmentDelegation * ed;
    explicit EnvironmentDelegationHelper(EnvironmentDelegation * ed_) : ed(ed_) { }
public:
    static Environment * getRootEnvironmentDelegate(EnvironmentDelegation * ed_) {
        Environment * envChild = ed_->getEnvironmentDelegate();
        if(dynamic_cast<EnvironmentDelegation *>(envChild) != nullptr) {
            envChild = getRootEnvironmentDelegate((EnvironmentDelegation *) envChild);
        }
        return envChild;
    }
//    static Environment * getDelegateImplementing(Environment * env, Class<?> type){
//
//        if(type.isAssignableFrom(env.getClass())){
//            return env;
//        }
//        else if(env instanceof EnvironmentDelegation){
//            return getDelegateImplementing(((EnvironmentDelegation)env).getEnvironmentDelegate(), type);
//        }
//
//        return null;
//
//    }
};