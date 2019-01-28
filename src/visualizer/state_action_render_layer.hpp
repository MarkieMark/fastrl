/*
 * Mark Benjamin 25 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_VISUALIZER_STATE_ACTION_RENDER_LAYER_HPP
#define FASTRL_VISUALIZER_STATE_ACTION_RENDER_LAYER_HPP

#include "render_layer.hpp"
#include "../mdp/core/state/state.hpp"
#include "../mdp/core/action/action.hpp"
#include "../mdp/core/state/null_state.hpp"

class StateActionRenderLayer : public RenderLayer {
public:
    State * render_state = nullptr;
    Action * render_action = nullptr;
    StateActionRenderLayer() = default;
    State * getRenderState() { return render_state; }
    Action * getRenderAction() { return render_action; }
    void updateStateAction(State * s, Action * a) {render_state = s; render_action = a; }
    void clearStateAction() {render_state = nullptr; render_action = nullptr; }
    void render(QPainter * qp, float width, float height) override {
        if (render_state != nullptr && render_action != nullptr && dynamic_cast<NullState *>(render_state) != nullptr) {
            renderStateAction(qp, render_state, render_action, width, height);
        }
    }
    virtual void renderStateAction(QPainter * qp, State * s, Action * a, float width, float height) {
        throw runtime_error("StateActionRenderLayer::renderStateAction() Not implemented");
    }
};


#endif //FASTRL_VISUALIZER_STATE_ACTION_RENDER_LAYER_HPP
