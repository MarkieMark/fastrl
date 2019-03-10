/*
 * Mark Benjamin 28th January 2019
 * (c) Mark Benjamin 2019
 */

#ifndef FASTRL_MDP_CORE_STATE_NULL_STATE_HPP
#define FASTRL_MDP_CORE_STATE_NULL_STATE_HPP

#include "state.hpp"

class NullState : public State {
private:
    NullState() = default;
public:
    static NullState &instance() {
        static NullState instance;
        return instance;
    }
    vector<KeyContainer *> variableKeys() const override {
        return vector<KeyContainer *>();
    }
    int getIntValue (KeyContainer * variableKey) const override {
        return 0;
    }
    State * makeCopy() override {
        return this;
    }

    bool operator==(State &comp) const {
        // todo check that it overrides State::operator==()
        return comp == *this;
    }
//    int hashCode() {
//        return 0;
//    }

    string to_string() override {
        return "";
    }

    NullState(NullState const&) = delete;
    void operator=(NullState const&) = delete;
};

#endif //FASTRL_MDP_CORE_STATE_NULL_STATE_HPP
