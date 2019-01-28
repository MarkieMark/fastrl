/*
 * Mark Benjamin 28 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include "state_render_layer.h"
#include "../mdp/core/state/null_state.hpp"

StateRenderLayer::StateRenderLayer() {
    current_state = &NullState::instance();
}

void StateRenderLayer::render(QPainter * qp, float width, float height) {
    if(current_state == nullptr || dynamic_cast<NullState *>(current_state) != nullptr) {
        return; //don't render anything if there is no state to render
    }
    for(StatePainter * sp : state_painters){
        sp->paint(qp, current_state, width, height);
    }
}