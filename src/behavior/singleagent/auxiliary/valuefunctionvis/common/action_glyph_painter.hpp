
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_ACTION_GLYPH_PAINTER_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_ACTION_GLYPH_PAINTER_HPP

#include <QPainter>

class ActionGlyphPainter {
public:
    virtual void paintGlyph(QPainter * qp, float x, float y, float width, float height) {
        throw runtime_error("ActionGlyphPainter::paintGlyph() Not Implemented");
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_ACTION_GLYPH_PAINTER_HPP
