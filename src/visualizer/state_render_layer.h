/*
 * Mark Benjamin 25 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_VISUALIZER_STATE_RENDER_LAYER_H
#define FASTRL_VISUALIZER_STATE_RENDER_LAYER_H

#include "render_layer.hpp"
#include "object_state_painters.hpp"

class StateRenderLayer : public RenderLayer {
public:
    State * current_state;
    vector<StatePainter *> state_painters;
    StateRenderLayer();
    void addStatePainter(StatePainter * sp) {
        state_painters.push_back(sp);
    }
    void updateState(State * s) {
        current_state = s;
    }
    State * getCurrentState() {
        return current_state;
    }
    vector<StatePainter *> getStatePainters() {
        return state_painters;
    }
    void render(QPainter * qp, float width, float height) override;
};


#endif //FASTRL_VISUALIZER_STATE_RENDER_LAYER_H
