/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_CORE_ACTION_SIMPLE_ACTION_HPP
#define FASTRL_MDP_CORE_ACTION_SIMPLE_ACTION_HPP

#include "action.hpp"

class SimpleAction : public Action {
public:
    string name;
    SimpleAction() = default;
    explicit SimpleAction(string name_) : name(move(name_)) {}
    string actionName() override { return name; }
    SimpleAction * copy() { return new SimpleAction(name); }
    string getName() { return name; }
    void setName(string name_) { name = move(name_); }
//    bool equals()
//    int hashCode()
    string to_string() override { return name; }

};

#endif //FASTRL_MDP_CORE_ACTION_SIMPLE_ACTION_HPP
