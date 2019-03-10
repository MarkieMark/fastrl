
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_MDP_CORE_STATE_VARDOMAIN_VARIABLE_DOMAIN_HPP
#define FASTRL_MDP_CORE_STATE_VARDOMAIN_VARIABLE_DOMAIN_HPP

class VariableDomain {
public:
    double lower;
    double upper;
    VariableDomain()  = default;
    VariableDomain(double lower_, double upper_) : lower(lower_), upper(upper_) { }
    double span(){
        return upper - lower;
    }

    double norm(double d){
        return (d - lower) / span();
    }
};

#endif //FASTRL_MDP_CORE_STATE_VARDOMAIN_VARIABLE_DOMAIN_HPP
