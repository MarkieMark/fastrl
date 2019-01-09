//
// Mark Benjamin 5/31/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_MDP_AUXILIARY_COMMON_NULL_TERMINATION_H
#define FASTRL_MDP_AUXILIARY_COMMON_NULL_TERMINATION_H

#include "../../core/terminal_function.hpp"

class NullTermination : public TerminalFunction {
public:
    NullTermination();
    bool isTerminal(State s);
};
#endif // FASTRL_MDP_AUXILIARY_COMMON_NULL_TERMINATION_H
