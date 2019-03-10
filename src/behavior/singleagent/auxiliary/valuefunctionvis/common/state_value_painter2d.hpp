
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_STATE_VALUE_PAINTER_2D_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_STATE_VALUE_PAINTER_2D_HPP

#include <QPen>
#include <QFont>
#include <cstring>
#include "../state_value_painter.hpp"
#include "color_blend.hpp"
#include "landmark_color_blend_interpolation.hpp"
#include "../../../../../mdp/core/state/null_state.hpp"

class StateValuePainter2D : public StateValuePainter {
public:
    KeyContainer * h_key = nullptr;
    KeyContainer * v_key = nullptr;
    VariableDomain * h_range = nullptr;
    VariableDomain * v_range = nullptr;
    double h_width = 0.;
    double v_width = 0.;
    ColorBlend * colorBlend;
    int n_h_grid = -1;
    int n_v_grid = -1;
    bool renderValueString = true;
    int vsFontSize = 10;
    QColor * vsFontColor = new QColor(Qt::black);
    float vsOffsetFromLeft = 0.f;
    float vsOffsetFromTop = 0.75f;
    unsigned long vsPrecision = 2;

    explicit StateValuePainter2D() {
        auto * rb = new LandmarkColorBlendInterpolation();
        rb->addNextLandMark(0., new QColor(Qt::red));
        rb->addNextLandMark(1., new QColor(Qt::blue));
        colorBlend = rb;
    }

    explicit StateValuePainter2D(ColorBlend * color_blend){
        colorBlend = color_blend;
    }

    void setColorBlend(ColorBlend * color_blend){
        colorBlend = color_blend;
    }

    void setHVKeys(KeyContainer * h_key_, KeyContainer * v_key_, VariableDomain * h_range_, VariableDomain * v_range_,
            double h_width_, double v_width_) {
        h_key = h_key_;
        v_key = v_key_;
        h_range = h_range_;
        v_range = v_range_;
        h_width = h_width_;
        v_width = v_width_;
    }

    void toggleValueStringRendering(bool render_value_string) {
        renderValueString = render_value_string;
    }

    void setValueStringRenderingFormat(int fontSize, QColor * fontColor, unsigned long precision, float offsetFromLeft, float offsetFromTop) {
        vsFontSize = fontSize;
        vsFontColor = fontColor;
        vsPrecision = precision;
        vsOffsetFromLeft = offsetFromLeft;
        vsOffsetFromTop = offsetFromTop;
    }

    void set_n_h_grid(int n_h) {
        n_h_grid = n_h;
    }

    void set_n_v_grid(int n_v) {
        n_v_grid = n_v;
    }

    void rescale(double lowerValue, double upperValue) override {
        if (!shouldRescaleValues) {
            return ;
        }
        colorBlend->rescale(lowerValue, upperValue);
    }

    void paintStateValue(QPainter * qp, State * s, double value, float canvas_width, float canvas_height) override {
        int h = s->getIntValue(h_key);
        int v = s->getIntValue(v_key);
        double width = canvas_width / (h_range->span() / h_width);
        double height = canvas_height / (v_range->span() / v_width);
        double normH = h_range->norm(h);
        double h_val = normH * canvas_width;
        double normV = v_range->norm(v);
        double v_val = canvas_height - height - normV * canvas_height;
        qp->fillRect((int)h_val, (int)v_val, (int)width, (int)height, *(colorBlend->color(value)));
        if (renderValueString){
            QPen pen;
            pen.setColor(*vsFontColor);
            qp->setPen(pen);
            QFont sansFont("Helvetica", vsFontSize, QFont::Bold);
            qp->setFont(sansFont);
            string fstring;
            fstring.resize(vsPrecision + 3);
            string for_string = string("%.") + to_string(vsPrecision) + string("f");
            sprintf(&fstring[0], &for_string[0], value);
            auto s_h_val = (int)(h_val + vsOffsetFromLeft * width);
            auto s_v_val = (int)(v_val + vsOffsetFromTop * height);
            qp->drawText(s_h_val, s_v_val, QString::fromStdString(fstring));
        }
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_STATE_VALUE_PAINTER_2D_HPP
