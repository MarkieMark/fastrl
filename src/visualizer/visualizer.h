/*
 * Mark Benjamin 25 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_VISUALIZER_VISUALIZER_H
#define FASTRL_VISUALIZER_VISUALIZER_H

#include "multi_layer_renderer.hpp"
#include "state_render_layer.h"
#include "state_action_render_layer.hpp"

class Visualizer : public MultiLayerRenderer {
Q_OBJECT
public:
    StateRenderLayer * s_render = nullptr;
    StateActionRenderLayer * sa_render = nullptr;
    bool saAfterStateRL = false;
    explicit Visualizer() : MultiLayerRenderer() {
        s_render = new StateRenderLayer();
        render_layers.push_back(s_render);
    }
    explicit Visualizer(StateRenderLayer * srender) : MultiLayerRenderer() {
        s_render = srender;
        render_layers.push_back(s_render);
    }
    void setSetRenderLayer(StateRenderLayer * srender){
        render_layers.erase(remove(render_layers.begin(), render_layers.end(), s_render), render_layers.end());
        render_layers.push_back(srender);
        s_render = srender;
    }
    void setStateActionRenderLayer(StateActionRenderLayer * sarender, bool afterStateRL){

        saAfterStateRL = afterStateRL;

        if(sa_render != nullptr){
            render_layers.erase(remove(render_layers.begin(), render_layers.end(), sa_render), render_layers.end());
        }
        sa_render = sarender;
        int srenderPos = 0;
        for(int i = 0; i < render_layers.size(); i++){
            if(render_layers[i] == s_render){
                srenderPos = i;
                break;
            }
        }

        if(afterStateRL){
            render_layers.insert(render_layers.begin() + srenderPos + 1, sarender);
        } else {
            render_layers.insert(render_layers.begin() + srenderPos, sarender);
        }
    }
    void addStatePainter(StatePainter * sp) {
        s_render->addStatePainter(sp);
    }
    StateRenderLayer * getStateRenderLayer(){
        return s_render;
    }
    void updateState(State * s){
        s_render->updateState(s);
        if(sa_render != nullptr){
            sa_render->clearStateAction();
        }
        update();
    }
    void updateStateAction(State * s, Action * a){
        s_render->updateState(s);
        if(sa_render != nullptr) {
            sa_render->updateStateAction(s, a);
        }
        update();
    }
    Visualizer * makeCopy(){
        auto * v = new Visualizer(s_render);
        if(sa_render != nullptr) {
            v->setStateActionRenderLayer(sa_render, saAfterStateRL);
        }
        for(RenderLayer * rl : render_layers) {
            if(rl != s_render && rl != sa_render){
                render_layers.push_back(rl);
            }
        }
        return v;
    }
};

#endif //FASTRL_VISUALIZER_VISUALIZER_H
