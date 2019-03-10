
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_STATE_POLICY_PAINTER_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_STATE_POLICY_PAINTER_HPP

class StatePolicyPainter {
public:
    virtual void paintStatePolicy(QPainter * qp, State * s, Policy * policy, float canvas_width, float canvas_height) {
        throw runtime_error("StatePolicyPainter::paintStatePolicy() Not Implemented");
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_STATE_POLICY_PAINTER_HPP
