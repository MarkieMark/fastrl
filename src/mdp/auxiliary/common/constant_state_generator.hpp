/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_MDP_AUXILIARY_COMMON_CONSTANT_STATE_GENERATOR_HPP
#define FASTRL_MDP_AUXILIARY_COMMON_CONSTANT_STATE_GENERATOR_HPP

#include "../state_generator.hpp"

class ConstantStateGenerator : public StateGenerator {
public:
    State * src;
    explicit ConstantStateGenerator(State * src_) : src(src_) { }
    State * generateState() override { return src; }
};

#endif // FASTRL_MDP_AUXILIARY_COMMON_CONSTANT_STATE_GENERATOR_HPP