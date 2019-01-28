/*
 * Mark Benjamin 28 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_VISUALIZER_PAINTERS_H
#define FASTRL_VISUALIZER_PAINTERS_H

#include <QtGui/QPainter>
#include "../mdp/core/state/state.hpp"
#include "../mdp/core/oo/state/OO_state.hpp"

class ObjectPainter {
public:
    virtual void paintObject(QPainter * qp, OOState * s, ObjectInstance * ob, float canvas_width, float canvas_height) {
        throw runtime_error("ObjectPainter::paintObject() Not implemented"); }
};


class StatePainter {
public:
    virtual void paint(QPainter * qp, State * s, float canvas_width, float canvas_height) {
        throw runtime_error("StatePainter::paint() Not implemented"); }
};

#endif //FASTRL_VISUALIZER_PAINTERS_H
