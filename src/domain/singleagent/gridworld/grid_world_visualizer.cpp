/*
 * Mark Benjamin 25 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include <utility>
#include "grid_world_visualizer.h"
#include "../../../visualizer/OO_state_painter.hpp"
#include "grid_world_domain.h"

/**
 * Returns visualizer for a grid world domain with the provided wall map. This method has been deprecated because the domain is no longer necessary.
 * Use the {@link #getVisualizer(vector<vector<unsigned int>>)} method instead.
 * @param d the domain of the grid world
 * @param map the wall map matrix where 0s indicate it is clear of walls, 1s indicate a full cell wall in that cell, 2s indicate a 1D north wall, 3s indicate a 1D east wall, and 4s indicate a 1D north and east wall.
 * @return a grid world domain visualizer
 */
Visualizer * GridWorldVisualizer::getVisualizer(Domain * d, vector<vector<unsigned int>> map) {
    StateRenderLayer * r = getRenderLayer(d, move(map));
    auto * v = new Visualizer(r);
    return v;
}

/**
 * Returns visualizer for a grid world domain with the provided wall map.
 * @param map the wall map matrix where 0s indicate it is clear of walls, 1s indicate a full cell wall in that cell, 2s indicate a 1D north wall, 3s indicate a 1D east wall, and 4s indicate a 1D north and east wall.
 * @return a grid world domain visualizer
 */
Visualizer * GridWorldVisualizer::getVisualizer(vector<vector<unsigned int>> map) {
    StateRenderLayer * r = getRenderLayer(move(map));
    auto * v = new Visualizer(r);
    return v;
}

/**
 * Returns state render layer for a gird world domain with the provided wall map. This method has been deprecated because the domain object is no
 * longer necessary. Use the {@link #getRenderLayer(vector<vector<unsigned int>>)} method instead.
 * @param d the domain of the grid world
 * @param map the wall map matrix where 0s indicate it is clear of walls, 1s indicate a full cell wall in that cell, 2s indicate a 1D north wall, 3s indicate a 1D east wall, and 4s indicate a 1D north and east wall.
 * @return a grid world domain state render layer
 */
StateRenderLayer * GridWorldVisualizer::getRenderLayer(Domain * d, vector<vector<unsigned int>> map) {
    auto * r = new StateRenderLayer();
    r->addStatePainter(new GridWorldMapPainter(map));
    auto * oopainter = new OOStatePainter();
    oopainter->addObjectClassPainter(GridWorldDomain::CLASS_LOCATION(), new GridWorldLocationPainter(map));
    oopainter->addObjectClassPainter(GridWorldDomain::CLASS_AGENT(), new GridWorldCellPainter(1, Qt::gray, map));
    r->addStatePainter(oopainter);
    return r;
}

/**
 * Returns state render layer for a gird world domain with the provided wall map.
 * @param map the wall map matrix where 0s indicate it is clear of walls, 1s indicate a full cell wall in that cell, 2s indicate a 1D north wall, 3s indicate a 1D east wall, and 4s indicate a 1D north and east wall.
 * @return a grid world domain state render layer
 */
StateRenderLayer * GridWorldVisualizer::getRenderLayer(vector<vector<unsigned int>> map) {
    auto * r = new StateRenderLayer();
    r->addStatePainter(new GridWorldMapPainter(map));
    auto * oopainter = new OOStatePainter();
    oopainter->addObjectClassPainter(GridWorldDomain::CLASS_LOCATION(), new GridWorldLocationPainter(map));
    oopainter->addObjectClassPainter(GridWorldDomain::CLASS_AGENT(), new GridWorldCellPainter(1, Qt::gray, map));
    r->addStatePainter(oopainter);
    return r;
}

/**
 * A static painter class for rendering the walls of the grid world as black squares or black lines for 1D walls.
 * original @author James MacGlashan
 *
 */

    /**
     * Initializes for the domain and wall map
     * @param map the wall map matrix where 1s indicate a wall in that cell and 0s indicate it is clear of walls
     */
GridWorldMapPainter::GridWorldMapPainter(vector<vector<unsigned int>> map_) {
        dwidth = map_.size();
        dheight = map_[0].size();
        map = map_;
}
void GridWorldMapPainter::paint(QPainter * qp, State * s, float canvas_width, float canvas_height) {
    //draw the walls; make them black
    QPen pen = QPen();
    //set stroke for 1d walls
//    qp->setStroke(new BasicStroke(4));
    pen.setWidth(4);
//    pen.setColor(Qt::darkGreen);
    qp->setPen(pen);
//    cout << "Map Painter canvas width " << canvas_width << ", canvas_height " << canvas_height << endl;
    float domainXScale = dwidth;
    float domainYScale = dheight;
//    cout << "domain h scale " << dwidth << ", v scale " << dheight << endl;
    //determine then normalized width
    float norm_width = (1.0f / domainXScale) * canvas_width;
    float norm_height = (1.0f / domainYScale) * canvas_height;
//    cout << "norm width " << norm_width << ", height " << norm_height << endl;
    //pass through every grid of the map; show walls
    for(int i = 0; i < dwidth; i++) {
        for(int j = 0; j < dheight; j++){
//            if ((i == 0) || (i == dwidth - 1) || (j == 0) || (j == dheight - 1)) continue;
            bool drawNorthWall = false;
            bool drawEastWall = false;
            if(map[i][j] == 1) {
//                cout << "solid wall at " << i << "," << j << endl;
                float rx = i * norm_width;
                float ry = canvas_height - norm_height - j * norm_height;
//                cout << "filling rectangle from " << rx << "," << ry << " width " << norm_width << ", height " << norm_height << endl;
                qp->fillRect(QRectF(rx, ry, norm_width, norm_height), pen.brush());
            }
            else if(map[i][j] == 2) {
//                cout << "North wall at " << i << "," << j << endl;
                drawNorthWall = true;
            }
            else if(map[i][j] == 3) {
//                cout << "East wall at " << i << "," << j << endl;
                drawEastWall = true;
            }
            else if(map[i][j] == 4) {
//                cout << "North & East wall at " << i << "," << j << endl;
                drawNorthWall = true;
                drawEastWall = true;
            }
            auto left = int(i * norm_width);
            auto top = int(canvas_height - norm_height - j * norm_height);
            if(drawNorthWall){
                qp->drawLine(left, top, int(left + norm_width), top);
            }
            if(drawEastWall){
                qp->drawLine(int(left + norm_width), top, int(left + norm_width), int(top + norm_height));
            }
        }
    }
}

/**
 * A painter for a grid world cell which will fill the cell with a given color and where the cell position
 * is indicated by the x and y attribute for the mapped object instance
 * @author James MacGlashan
 *
 */
/**
 * Initializes painter for a rectangle shape cell
 * @param col the color to paint the cell
 * @param map the wall map matrix where 1s indicate a wall in that cell and 0s indicate it is clear of walls
 */
GridWorldCellPainter::GridWorldCellPainter(QColor col_, vector<vector<unsigned int>> map_) {
    col = move(col_);
    dwidth = map_.size();
    dheight = map_[0].size();
    map = map_;
}

/**
 * Initializes painter with filling the cell with the given shape
 * @param shape the shape with which to fill the cell. 0 for a rectangle, 1 for an ellipse.
 * @param col the color to paint the cell
 * @param map the wall map matrix where 1s indicate a wall in that cell and 0s indicate it is clear of walls
 */
GridWorldCellPainter::GridWorldCellPainter(int shape_, QColor col_, vector<vector<unsigned int>> map_) {
    col = move(col_);
    dwidth = map_.size();
    dheight = map_[0].size();
    map = map_;
    shape = shape_;
}

void GridWorldCellPainter::paintObject(QPainter * qp, OOState * s, ObjectInstance * ob, float canvas_width, float canvas_height) {
    //set the color of the object
    QPen pen = qp->pen();
    pen.setColor(col);
    qp->setPen(pen);
    float domainXScale = dwidth;
    float domainYScale = dheight;
    //determine then normalized width
    float norm_width = (1.0f / domainXScale) * canvas_width;
    float norm_height = (1.0f / domainYScale) * canvas_height;
    float rx = ob->getIntValue(new KeyContainer(GridWorldDomain::VAR_X())) * norm_width;
    float ry = canvas_height - norm_height - ob->getIntValue(new KeyContainer(GridWorldDomain::VAR_Y())) * norm_height;
    if(shape == 0) {
        qp->fillRect(QRectF(rx, ry, norm_width, norm_height), pen.brush());
    }
    else{
        qp->setBrush(col);
        qp->drawEllipse(QRectF(rx, ry, norm_width, norm_height));
    }
}

/**
 * A painter for location objects which will fill the cell with a given color and where the cell position
 * is indicated by the x and y attribute for the mapped object instance
 * @author James MacGlashan
 *
 */
/**
 * Initializes painter
 * @param map the wall map matrix where 1s indicate a wall in that cell and 0s indicate it is clear of walls
 */
GridWorldLocationPainter::GridWorldLocationPainter(vector<vector<unsigned int>> map_) {
    dwidth = map_.size();
    dheight = map_[0].size();
    map = map_;
    baseColors = vector<QColor>(5);
    baseColors.emplace_back(Qt::blue);
    baseColors.emplace_back(Qt::red);
    baseColors.emplace_back(Qt::green);
    baseColors.emplace_back(Qt::yellow);
    baseColors.emplace_back(Qt::magenta);
}

void GridWorldLocationPainter::paintObject(QPainter * qp, OOState * s, ObjectInstance * ob, float canvas_width, float canvas_height) {
    auto type = ob->getIntValue(new KeyContainer(GridWorldDomain::VAR_TYPE()));
    unsigned long multiplier = max(type, 0) / baseColors.size();
    unsigned long colIndex = type % baseColors.size();
    QColor col = baseColors[colIndex];
    for(int i = 0; i < multiplier; i++){
        col = col.darker();
    }
    //set the color of the object
    QPen pen = qp->pen();
    pen.setColor(col);
    qp->setPen(pen);
    float domainXScale = dwidth;
    float domainYScale = dheight;
    //determine then normalized width
    float norm_width = (1.0f / domainXScale) * canvas_width;
    float norm_height = (1.0f / domainYScale) * canvas_height;
    float rx = ob->getIntValue(new KeyContainer(GridWorldDomain::VAR_X())) * norm_width;
    float ry = canvas_height - norm_height - ob->getIntValue(new KeyContainer(GridWorldDomain::VAR_X())) * norm_height;
    qp->fillRect(QRectF(rx, ry, norm_width, norm_height), pen.brush());
}
