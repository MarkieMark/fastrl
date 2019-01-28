/*
 * Mark Benjamin 28 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include "grid_world_terminal_function.h"

bool GridWorldTerminalFunction::isTerminal(State * s) {
    auto *s_ = dynamic_cast<GridWorldState *>(s);
    return isTerminalPosition(s_->agent->x, s_->agent->y);
}
