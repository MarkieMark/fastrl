
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_STATE_VALUE_PAINTER_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_STATE_VALUE_PAINTER_HPP

class StateValuePainter {
public:
    bool shouldRescaleValues = true;

    virtual void paintStateValue(QPainter * qp, State * s, double value, float canvas_width, float canvas_height) {
        throw runtime_error("StateValuePainter::paintStateValue() Not Implemented");
    }

    virtual void rescale(double lowerValue, double upperValue) {
        throw runtime_error("StateValuePainter::rescale() Not Implemented");
    }

    virtual void useValueRescaling(bool rescale) {
        shouldRescaleValues = rescale;
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_STATE_VALUE_PAINTER_HPP
