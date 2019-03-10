/*
 * Mark Benjamin 25 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_GRID_WORLD_VISUALIZER_H
#define FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_GRID_WORLD_VISUALIZER_H


#include <vector>
#include "../../../mdp/core/domain.hpp"
#include "../../../visualizer/visualizer.h"
#include "../../../visualizer/state_render_layer.h"
#include "../../../visualizer/object_state_painters.hpp"

//class ObjectPainter;

class GridWorldVisualizer {
public:
    GridWorldVisualizer() = default;
    static Visualizer * getVisualizer(Domain * d, vector<vector<unsigned int>> &map);
    static Visualizer * getVisualizer(vector<vector<unsigned int>> &map);
    static StateRenderLayer * getRenderLayer(Domain * d, vector<vector<unsigned int>> &map);
    static StateRenderLayer * getRenderLayer(vector<vector<unsigned int>> &map);
};

class GridWorldMapPainter : public StatePainter {
public:
    unsigned long dwidth;
    unsigned long dheight;
    vector<vector<unsigned int>>map;
    explicit GridWorldMapPainter(vector<vector<unsigned int>> map);
    void paint(QPainter * qp, State * s, float canvas_width, float canvas_height) override;
};

class GridWorldCellPainter : public ObjectPainter {
public:
    QColor col;
    unsigned long dwidth;
    unsigned long dheight;
    vector<vector<unsigned int>> map;
    int shape = 0; //0 for rectangle 1 for ellipse
    GridWorldCellPainter(QColor col, vector<vector<unsigned int>> map);
    GridWorldCellPainter(int shape, QColor col, vector<vector<unsigned int>> map);
    void paintObject(QPainter * qp, OOState * s, ObjectInstance * ob, float canvas_width, float canvas_height) override;
};

class GridWorldLocationPainter : public ObjectPainter {
public:
    vector<QColor> baseColors;
    unsigned long dwidth;
    unsigned long dheight;
    vector<vector<unsigned int>> map;
    explicit GridWorldLocationPainter(vector<vector<unsigned int>> map);
    void paintObject(QPainter *qp, OOState * s, ObjectInstance * ob, float canvas_width, float canvas_height) override;
};

#endif //FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_GRID_WORLD_VISUALIZER_H
