#include "state/state.hpp"

#ifndef FASTRL_MDP_CORE_TERMINAL_FUNCTION_HPP
#define FASTRL_MDP_CORE_TERMINAL_FUNCTION_HPP

class TerminalFunction {
public:
    virtual bool isTerminal(State * s) { throw runtime_error("TerminalFunction::isTerminal() Not Implemented"); }
};

#endif // FASTRL_MDP_CORE_TERMINAL_FUNCTION_HPP