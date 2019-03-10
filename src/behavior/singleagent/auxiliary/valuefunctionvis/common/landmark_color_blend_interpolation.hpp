
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_LANDMARK_COLOR_BLEND_INTERPOLATION_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_LANDMARK_COLOR_BLEND_INTERPOLATION_HPP

#include <QColor>
#include <cmath>
#include <vector>
#include "color_blend.hpp"

class LandmarkColorBlendInterpolation : public ColorBlend {
public:
    vector<double> landmarkValues;
    vector<double> originalLandmarkValues;
    vector <QColor *> landmarkColors;
    double polyDegree = 1.;

    LandmarkColorBlendInterpolation() = default;

    explicit LandmarkColorBlendInterpolation(double poly_degree) {
        polyDegree = poly_degree;
    }

    void setPolynomialDegree(double poly_degree){
        polyDegree = poly_degree;
    }

    double getPolynomialDegree(){
        return polyDegree;
    }

    void addNextLandMark(double val, QColor * c) {
        landmarkValues.push_back(val);
        landmarkColors.push_back(c);
        originalLandmarkValues.push_back(val);
    }

    void rescale(double min_val, double max_val) override {
        double origMin = originalLandmarkValues[0];
        double origMax = originalLandmarkValues[originalLandmarkValues.size() - 1];
        if (origMin == min_val && origMax == max_val) {
            return ; //already correctly scaled
        }
        double origRange = origMax - origMin;
        double newRange = max_val - min_val;
        for (int i = 0; i < landmarkValues.size(); i++) {
            double v = originalLandmarkValues[i];
            double t = (v - origMin) / origRange;
            double nv = t * newRange + min_val;
            landmarkValues[i] = nv;
        }
    }

    QColor * color(double v) override {
        //end point?
        if (v <= landmarkValues[0]) {
            return landmarkColors[0];
        }
        if (v >= landmarkValues[landmarkValues.size() - 1]) {
            return landmarkColors[landmarkColors.size() - 1];
        }
        //which is the interpolation end point?
        int ePoint = 1;
        for(int i = 1; i < landmarkValues.size(); i++){
            ePoint = i;
            if (landmarkValues[i] > v) {
                break ;
            }
        }
        double sv = landmarkValues[ePoint - 1];
        double ev = landmarkValues[ePoint];
        double vRange = ev - sv;
        double t = (v - sv) / vRange;
        t = pow(t, polyDegree);
        QColor * s_c = landmarkColors[ePoint - 1];
        QColor * e_c = landmarkColors[ePoint];
        vector<qreal> s_color_comp(4);
        vector<qreal> e_color_comp(4);
        s_c->getRgbF(&(s_color_comp[0]), &(s_color_comp[1]), &(s_color_comp[2]), &(s_color_comp[3]));
        e_c->getRgbF(&(e_color_comp[0]), &(e_color_comp[1]), &(e_color_comp[2]), &(e_color_comp[3]));
        qreal red = interpolate(s_color_comp[0], e_color_comp[0], (qreal)t);
        qreal green = interpolate(s_color_comp[1], e_color_comp[1], (qreal)t);
        qreal blue = interpolate(s_color_comp[2], e_color_comp[2], (qreal)t);
        qreal alpha = interpolate(s_color_comp[3], e_color_comp[3], (qreal)t);
        auto * finalColor = new QColor();
        finalColor->setRedF(red);
        finalColor->setGreenF(green);
        finalColor->setBlueF(blue);
        return finalColor;
    }

    qreal interpolate(qreal s, qreal e, qreal t){
        qreal range = e - s;
        return s + t * range;
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_LANDMARK_COLOR_BLEND_INTERPOLATION_HPP
