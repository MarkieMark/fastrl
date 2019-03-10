
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_POLICY_GLYPH_PAINTER_2D_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_POLICY_GLYPH_PAINTER_2D_HPP

#include "../../../../policy/enumerable_policy.hpp"
#include "../../../../policy/support/action_prob.hpp"
#include "../state_policy_painter.hpp"

class PolicyGlyphPainter2D : public StatePolicyPainter {
public:
    enum class PolicyGlyphRenderStyle {
        MAXACTION,
        MAXACTIONSOFTIE,
        DISTSCALED
    };

    KeyContainer * h_key = nullptr;
    KeyContainer * v_key = nullptr;
    VariableDomain * h_range = nullptr;
    VariableDomain * v_range = nullptr;
    float h_width = 0.F;
    float v_width = 0.F;
    PolicyGlyphRenderStyle renderStyle = PolicyGlyphRenderStyle::MAXACTIONSOFTIE;
    float softieDelta = 0.01;
    map<string, ActionGlyphPainter *> actionNamePainterMap = map<string, ActionGlyphPainter *>();

    void setHVKeys(KeyContainer * h_key_, KeyContainer * v_key_, VariableDomain * h_range_, VariableDomain * v_range_,
            float h_width_, float v_width_) {
        h_key = h_key_;
        v_key = v_key_;
        h_range = h_range_;
        v_range = v_range_;
        h_width = h_width_;
        v_width = v_width_;
    }

    void setActionNameGlyphPainter(const string &actionName, ActionGlyphPainter * actionPainter) {
        actionNamePainterMap[actionName] = actionPainter;
    }

    PolicyGlyphRenderStyle getRenderStyle() {
        return renderStyle;
    }

    void setRenderStyle(PolicyGlyphRenderStyle render_style) {
        renderStyle = render_style;
    }

    void setSoftieDelta(float delta) {
        softieDelta = delta;
    }

    float getSoftieDelta() {
        return softieDelta;
    }

    void paintStatePolicy(QPainter * qp, State * s, Policy * policy, float canvas_width, float canvas_height) override {
        int h = s->getIntValue(h_key);
        int v = s->getIntValue(v_key);
//        D("(" << h << "," << v << ")");
        float width = canvas_width / ((float)(h_range->span() / h_width));
        float height = canvas_height / ((float)(v_range->span() / v_width));
        auto normH = (float)(h_range->norm(h));
        float h_val = normH * canvas_width;
        auto normV = (float)(v_range->norm(v));
        float v_val = canvas_height - height - normV*canvas_height;
        vector<ActionProb *> p_dist;
        if(dynamic_cast<EnumerablePolicy *>(policy) != nullptr) {
            p_dist = dynamic_cast<EnumerablePolicy *>(policy)->policyDistribution(s);
        } else {
            p_dist.push_back(new ActionProb(policy->action(s), 1.));
        }
        float max_p = 0.F;
        for (ActionProb * ap : p_dist) {
            if (ap->pSelection > max_p) {
                max_p = (float)(ap->pSelection);
            }
        }
        if (renderStyle != PolicyGlyphRenderStyle::DISTSCALED) {
            if (renderStyle == PolicyGlyphRenderStyle::MAXACTIONSOFTIE) {
                max_p -= softieDelta;
            }
            for (ActionProb * ap : p_dist) {
                if (ap->pSelection >= max_p) {
                    ActionGlyphPainter * agp = actionNamePainterMap[ap->pa->actionName()];
                    if (agp != nullptr) {
                        agp->paintGlyph(qp, h_val, v_val, width, height);
                    }
                }
            }
        } else {
            for (ActionProb * ap : p_dist) {
                vector<float> scaledRect = rescaleRect(h_val, v_val, width, height, (float)(ap->pSelection / max_p));
                ActionGlyphPainter * agp = actionNamePainterMap[ap->pa->actionName()];
                if (agp != nullptr) {
                    agp->paintGlyph(qp, scaledRect[0], scaledRect[1], scaledRect[2], scaledRect[3]);
                }
            }
        }
    }

    vector<float> rescaleRect(float h, float v, float width, float height, float scale) {
        float c_h = h + (width / 2.F);
        float c_v = v + (height / 2.F);
        float nw = scale * width;
        float nh = scale * height;
        float n_h = c_h - (nw / 2.F);
        float n_v = c_v - (nh / 2.F);
        return vector<float>{n_h, n_v, nw, nh};
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_POLICY_GLYPH_PAINTER_2D_HPP
