/*
 * Mark Benjamin 25 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_VISUALIZER_RENDER_LAYER_HPP
#define FASTRL_VISUALIZER_RENDER_LAYER_HPP

#include <stdexcept>
#include <QtGui/QPainter>

using namespace std;

class RenderLayer {
public:
    virtual void render(QPainter * qp, float width, float height) { throw runtime_error("RenderLayer::render() Not implemented"); }
};

#endif //FASTRL_VISUALIZER_MULTI_LAYER_RENDERER_H
