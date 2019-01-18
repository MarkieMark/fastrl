/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_CORE_DOMAIN_HPP
#define FASTRL_MDP_CORE_DOMAIN_HPP

#include <string>

using namespace std;

class Domain {
public:
    virtual string to_string() = 0;
};

#endif // FASTRL_MDP_CORE_DOMAIN_HPP
