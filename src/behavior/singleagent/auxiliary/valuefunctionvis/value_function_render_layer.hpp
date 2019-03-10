#include <utility>


/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_VALUE_FUNCTION_RENDER_LAYER_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_VALUE_FUNCTION_RENDER_LAYER_HPP

#include "../../../../visualizer/render_layer.hpp"
#include "state_value_painter.hpp"
#include "../../../valuefunction/value_function.hpp"
#include "../../../../domain/singleagent/gridworld/state/grid_world_state.h"

class ValueFunctionRenderLayer : public RenderLayer {
public:
    vector<State *> statesToPaint;
    StateValuePainter * svp;
    ValueFunction * valueFunction;

    ValueFunctionRenderLayer(vector<State *> states, StateValuePainter * svp_, ValueFunction * valueFunction_)
    : statesToPaint(move(states)), svp(svp_), valueFunction(valueFunction_) { }

    vector<State *> getStatesToPaint() {
        return statesToPaint;
    }

    void setStatesToPaint(vector<State *> stateValuesToPaint) {
        statesToPaint = move(stateValuesToPaint);
    }

    StateValuePainter * getSvp() {
        return svp;
    }

    void setSvp(StateValuePainter * svp_) {
        svp = svp_;
    }

    void render(QPainter * qp, float width, float height) override {
        vector<double> values;
        double minV = numeric_limits<double>::infinity();
        double maxV = -minV;
        for (State * s : statesToPaint) {
            double v = valueFunction->value(s);
            values.push_back(v);
            if (v < minV) {
                minV = v;
            }
            if (v > maxV) {
                maxV = v;
            }
        }
        svp->rescale(minV, maxV);
        auto vIter = values.begin();
        for (State * s : statesToPaint) {
            svp->paintStateValue(qp, s, *(vIter++), width, height);
        }
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_VALUE_FUNCTION_RENDER_LAYER_HPP
