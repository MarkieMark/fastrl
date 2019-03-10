
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_ARROW_ACTION_GLYPH_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_ARROW_ACTION_GLYPH_HPP

#include <cmath>
#include <QColor>
#include "action_glyph_painter.hpp"
#include "policy_glyph_painter2d.hpp"


class ArrowActionGlyph : public ActionGlyphPainter {
public:
    int direction = 0;
    QColor * fill_color = new QColor(Qt::black);

    static PolicyGlyphPainter2D * getNSEWPolicyGlyphPainter(KeyContainer * h_var, KeyContainer * v_var,
            VariableDomain * h_range, VariableDomain * v_range, float h_width, float v_width,
            const string &northActionName, const string &southActionName,
            const string &eastActionName, const string &westActionName) {
        auto * spp = new PolicyGlyphPainter2D();
        spp->setHVKeys(h_var, v_var, h_range, v_range, h_width, v_width);
        spp->setActionNameGlyphPainter(northActionName, new ArrowActionGlyph(0));
        spp->setActionNameGlyphPainter(southActionName, new ArrowActionGlyph(1));
        spp->setActionNameGlyphPainter(eastActionName, new ArrowActionGlyph(2));
        spp->setActionNameGlyphPainter(westActionName, new ArrowActionGlyph(3));
        spp->setRenderStyle(PolicyGlyphPainter2D::PolicyGlyphRenderStyle::DISTSCALED);
        return spp;
    }

    explicit ArrowActionGlyph(int direction_) {
        direction = direction_;
    }

    void paintGlyph(QPainter * qp, float x, float y, float width, float height) override {
        if (width == 0.F && height == 0.F) return;
        int minSize = 30;
        if(width < minSize || height < minSize){
                return;
        }
//        force square for easy drawing
        auto * glyphImage = new QPixmap((int)width, (int)height);
        auto * img_qp = new QPainter(glyphImage);
        img_qp->fillRect(glyphImage->rect(), Qt::white);
        float ch = width / 2.F;
        //float cv = ch;
        float arrowHeight = .15F * width;
        float shaftWidth = 0.05F * width;
        float shaftHeight = (width / 2.F) - arrowHeight;
        float shaftRadius = shaftWidth / 2.F;
        float sh = ch - shaftRadius;
        float sv = arrowHeight;
        QRectF rf(sh, sv, shaftWidth, shaftHeight);
        QPointF pf(sh + shaftWidth, sv + shaftHeight / 2);
        img_qp->fillRect(rf, *fill_color);
        float arrowHeadWidth = 2.5F * shaftRadius;
        QPointF point1(ch - arrowHeadWidth, arrowHeight);
        QPointF point2(ch, 0);
        QPointF point3(ch + arrowHeadWidth, arrowHeight);
        QPainterPath path(point1);
        path.lineTo(point2);
        path.lineTo(point3);
        path.closeSubpath();
        QBrush brush(*fill_color);
        img_qp->fillPath(path, brush);
        qp->setCompositionMode(QPainter::CompositionMode_Multiply);
        int rotationRequired = 0;
        if (direction == 1) {
            rotationRequired = 180;
        }
        else if (direction == 2) {
            rotationRequired = 90;
        }
        else if (direction == 3) {
            rotationRequired = 270;
        }
        if (direction > 0) {
            if (direction == 2) {
                qp->translate(x + width, y);
            } else if (direction == 1) {
                qp->translate(x + width, y + height);
            } else if (direction == 3) {
                qp->translate(x, y + height);
            }
            qp->rotate(rotationRequired);
            qp->drawPixmap(0, 0, *glyphImage);
            qp->resetTransform();
        } else {
            qp->drawPixmap((int) x, (int) y, *glyphImage);
        }
        qp->setCompositionMode(QPainter::CompositionMode_Source);
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_ARROW_ACTION_GLYPH_HPP
