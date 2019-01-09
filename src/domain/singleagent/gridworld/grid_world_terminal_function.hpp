/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_GRID_WORLD_TERMINAL_FUNCTION_HPP
#define FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_GRID_WORLD_TERMINAL_FUNCTION_HPP

#include <set>
#include <vector>
#include "../../../mdp/core/terminal_function.hpp"
#include "state/grid_world_state.h"

class GridWorldTerminalFunction : public TerminalFunction {
    typedef pair<int, int> TFPoint;
public:
    set<TFPoint> terminalPositions = set<TFPoint>();

    GridWorldTerminalFunction() = default;
    GridWorldTerminalFunction(int x, int y) {
        terminalPositions.insert(pair<int, int>(x, y));
    }
    explicit GridWorldTerminalFunction(vector<TFPoint> terminal_positions) {
        for (TFPoint p : terminal_positions) {
            terminalPositions.insert(p);
        }
    }
    void markAsTerminalPosition(int x, int y) {
        terminalPositions.insert(TFPoint(x, y));
    }

    void unmarkTerminalPosition(int x, int y) {
        // TODO double check semantics
        terminalPositions.erase(TFPoint(x, y));
    }

    void unmarkAllTerminalPositions() {
        terminalPositions.clear();
    }

    bool isTerminalPosition(int x, int y) {
        return (terminalPositions.find(TFPoint(x, y)) != terminalPositions.end());
    }

    bool isTerminal(State *s) override {
        auto *s_ = dynamic_cast<GridWorldState *>(s);
        return isTerminalPosition(s_->agent->x, s_->agent->y);
    }
};

#endif // FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_GRID_WORLD_TERMINAL_FUNCTION_HPP
