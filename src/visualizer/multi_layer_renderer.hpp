/*
 * Mark Benjamin 25 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_VISUALIZER_MULTI_LAYER_RENDERER_HPP
#define FASTRL_VISUALIZER_MULTI_LAYER_RENDERER_HPP

#include <QtWidgets/QWidget>
#include "render_layer.hpp"

class MultiLayerRenderer : public QWidget {
Q_OBJECT
public:
    vector<RenderLayer *> render_layers;
    QColor bg_color = Qt::white;
    // offscreen image for buffering & its buffer
    QPixmap * offscreen = nullptr;
    QPainter * buffer_qp = nullptr;
    QWidget * clickFocusWidget = nullptr;
    int mem_render_width = 0;
    int mem_render_height = 0;

    explicit MultiLayerRenderer(QWidget * parent = nullptr) : QWidget(parent) { }

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
            l->render(buffer_qp, width(), height());
        }
        qp->drawPixmap(0, 0, *offscreen);
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

    void mousePressEvent(QMouseEvent * event) override {
        if (clickFocusWidget != nullptr) {
            clickFocusWidget->setFocus();
        } else {
            QWidget::mousePressEvent(event);
        }
    }
};

#endif //FASTRL_VISUALIZER_MULTI_LAYER_RENDERER_HPP
