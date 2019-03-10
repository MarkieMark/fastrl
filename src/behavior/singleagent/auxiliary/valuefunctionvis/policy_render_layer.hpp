#include <utility>


/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_POLICY_RENDER_LAYER_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_POLICY_RENDER_LAYER_HPP

#include "../../../../visualizer/render_layer.hpp"
#include "state_policy_painter.hpp"

class PolicyRenderLayer : public RenderLayer {
public:
    vector<State *> statesToPaint = vector<State *>();
    StatePolicyPainter * spp = nullptr;
    Policy * policy = nullptr;

    PolicyRenderLayer(vector<State *> states, StatePolicyPainter * spp_, Policy * policy_)
    : statesToPaint(move(states)), spp(spp_), policy(policy_) { }

    vector<State *> getStatesToPaint() {
        return statesToPaint;
    }

    void setStatesToPaint(const vector<State *> &stateValuesToPaint) {
        statesToPaint = stateValuesToPaint;
    }

    StatePolicyPainter * getSpp() {
        return spp;
    }

    void setSpp(StatePolicyPainter * spp_) {
        spp = spp_;
    }

    Policy * getPolicy() {
        return policy;
    }

    void setPolicy(Policy * policy_) {
        policy = policy_;
    }

    void render(QPainter * qp, float width, float height) override {
        if (spp == nullptr || policy == nullptr) {
            return;
        }
        for (State * s : statesToPaint) {
            spp->paintStatePolicy(qp, s, policy, width, height);
        }
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_POLICY_RENDER_LAYER_HPP
