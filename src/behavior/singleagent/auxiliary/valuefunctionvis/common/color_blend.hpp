
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_COLOR_BLEND_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_COLOR_BLEND_HPP

#include <QColor>
#include <stdexcept>

using namespace std;

class ColorBlend {
public:
    virtual QColor * color(double val) { throw runtime_error("ColorBlend::color() Not Implemented"); }
    virtual void rescale(double min_val, double max_val) { throw runtime_error("ColorBlend::rescale() Not Implemented"); }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_COMMON_COLOR_BLEND_HPP
