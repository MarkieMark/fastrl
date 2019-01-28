/*
 * Mark Benjamin 25 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_VISUALIZER_MULTI_LAYER_RENDERER_H
#define FASTRL_VISUALIZER_MULTI_LAYER_RENDERER_H

#include <QtWidgets/QWidget>
#include "render_layer.hpp"

class MultiLayerRenderer : public QWidget {
public:
    vector<RenderLayer *> render_layers;
    QColor bg_color = Qt::white;
//    QColor bg_color = Qt::gray;

    // offscreen image for buffering & its buffer
    QPixmap * offscreen = nullptr;
    QPainter * buffer_qp = nullptr;

    int mem_render_width = 0;
    int mem_render_height = 0;

    MultiLayerRenderer() = default;
    void addRenderLayer(RenderLayer * l) { render_layers.push_back(l); }
    void insertRenderLayer(int i, RenderLayer * l) {render_layers.insert(render_layers.begin() + i, l); }
    void removeRenderLayer(int i) {render_layers.erase(render_layers.begin() + i); }
    unsigned long nRenderLayers() { return render_layers.size(); }
    void setBgColor(QColor &col) { bg_color = col; }
    QColor getBgColor() { return bg_color; }
    void paintComponent(QPainter * qp) {
        initOffScreen();
        buffer_qp->fillRect(0, 0, width(), height(), bg_color);
        for(RenderLayer * l : render_layers) {
//            l->render(buffer_qp, width(), height());
            l->render(qp, width(), height());
        }
//        qp->drawPixmap(0, 0, *offscreen);
    }
    void initOffScreen() {
        if (buffer_qp == nullptr || mem_render_width != width() || mem_render_height != height()) {
            offscreen = new QPixmap(width(), height());
            buffer_qp = new QPainter(offscreen);
            mem_render_height = height();
            mem_render_width = width();
        }
    }
protected:
    void paintEvent(QPaintEvent * e) override {
        QPainter qp(this);
        paintComponent(&qp);
    }
};

#endif //FASTRL_VISUALIZER_MULTI_LAYER_RENDERER_H
