/*
 * Mark Benjamin 28 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include "grid_world_terminal_function.h"
#include "../../../mdp/core/state/null_state.hpp"

bool GridWorldTerminalFunction::isTerminal(State * s) {
    if (s == nullptr || s == &NullState::instance()) {
        return false;
    }
    auto *s_ = dynamic_cast<GridWorldState *>(s);
    return isTerminalPosition(s_->agent->x, s_->agent->y);
}
