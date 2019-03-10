//
// Mark Benjamin 6/2/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_MDP_CORE_OO_STATE_KEY_CONTAINER_HPP
#define FASTRL_MDP_CORE_OO_STATE_KEY_CONTAINER_HPP

#include <string>
#include "OO_variable_key.hpp"

using namespace std;

class KeyContainer {
public:
    bool isString;
    string s;
    OOVariableKey * vk = nullptr;
    explicit KeyContainer(string s_) : isString(true), s(move(s_)) { }
    explicit KeyContainer(OOVariableKey * vk_) : isString(false), vk(vk_) { }
    string to_string() {
        if (isString) {
            return s;
        } else {
            return vk->to_string();
        }
    }
};

#endif // FASTRL_MDP_CORE_OO_STATE_KEY_CONTAINER_HPP
