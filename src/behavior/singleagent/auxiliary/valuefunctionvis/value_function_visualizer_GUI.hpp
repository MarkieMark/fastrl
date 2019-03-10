
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_VALUE_FUNCTION_VISUALIZER_GUI_HPP
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_VALUE_FUNCTION_VISUALIZER_GUI_HPP

#include <QMainWindow>
#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../../../../mdp/core/state/vardomain/variable_domain.hpp"
#include "../../../../visualizer/multi_layer_renderer.hpp"
#include "../../../policy/policy.hpp"
#include "../../../valuefunction/value_function.hpp"
#include "common/arrow_action_glyph.hpp"
#include "common/policy_glyph_painter2d.hpp"
#include "common/state_value_painter2d.hpp"
#include "policy_render_layer.hpp"
#include "state_value_painter.hpp"
#include "state_policy_painter.hpp"
#include "static_domain_painter.hpp"
#include "value_function_render_layer.hpp"

class ValueFunctionVisualizerGUI : public QMainWindow {
Q_OBJECT;
public:
    MultiLayerRenderer * renderer = nullptr;
    ValueFunctionRenderLayer * vfLayer = nullptr;
    PolicyRenderLayer * pLayer = nullptr;
    StateValuePainter * svp = nullptr;
    StatePolicyPainter * spp = nullptr;
    vector<State *> statesToPaint = vector<State *>();
    StaticDomainPainter	* sdp = nullptr;
    QCheckBox * showPolicy = nullptr;
    int canvas_width = 800;
    int canvas_height = 800;

    static ValueFunctionVisualizerGUI * createGridWorldBasedValueFunctionVisualizerGUI(
            const vector<State *> &states, ValueFunction * valueFunction, Policy * p,
            KeyContainer * h_var, KeyContainer * v_var, VariableDomain * h_range, VariableDomain * v_range,
            float h_width, float v_width, const string &northActionName, const string &southActionName,
            const string &eastActionName, const string &westActionName) {
        auto * svp_ = new StateValuePainter2D();
        svp_->setHVKeys(h_var, v_var, h_range, v_range, h_width, v_width);
        PolicyGlyphPainter2D * spp = ArrowActionGlyph::getNSEWPolicyGlyphPainter(h_var, v_var, h_range, v_range, h_width, v_width,
                northActionName, southActionName, eastActionName, westActionName);

        auto * gui = new ValueFunctionVisualizerGUI(states, svp_, valueFunction);
        gui->setSpp(spp);
        gui->setPolicy(p);
        gui->setBgColor(Qt::white);
        return gui;
    }

    ValueFunctionVisualizerGUI() = default;

    ValueFunctionVisualizerGUI(const vector<State *> &states, StateValuePainter * svp_, ValueFunction * valueFunction) {
        statesToPaint = states;
        svp = svp_;
        renderer = new MultiLayerRenderer();
        vfLayer = new ValueFunctionRenderLayer(statesToPaint, svp, valueFunction);
        pLayer = new PolicyRenderLayer(states, nullptr, nullptr);
        renderer->addRenderLayer(vfLayer);
        renderer->addRenderLayer(pLayer);
    }

    MultiLayerRenderer * getMultiLayerRenderer(){
        return renderer;
    }

    StateValuePainter * getSvp() {
        return svp;
    }

    void setSvp(StateValuePainter * svp_) {
        svp = svp_;
        vfLayer->setSvp(svp);
    }

    StatePolicyPainter * getSpp() {
        return spp;
    }

    void setSpp(StatePolicyPainter * spp_) {
        spp = spp_;
        if (spp != nullptr && showPolicy != nullptr) {
            showPolicy->setEnabled(true);
            pLayer->setSpp(spp);
        }
    }

    void setBgColor(QColor col){
        renderer->setBgColor(col);
    }

    void setPolicy(Policy * p) {
        pLayer->setPolicy(p);
    }

    void initGUI() {
        renderer->resize(canvas_width, canvas_height);
        auto * contentPane = new QWidget(this);
        auto * qvl = new QVBoxLayout(contentPane);
        showPolicy = new QCheckBox("Show Policy", contentPane);
        showPolicy->setChecked(false);
        connect(showPolicy, SIGNAL(clicked(bool)), this, SLOT(policyToggled(bool)));
        qvl->addWidget(renderer);
        qvl->addWidget(showPolicy);
        contentPane->setLayout(qvl);

        if (spp == nullptr) {
            showPolicy->setEnabled(false);
        } else {
            showPolicy->setCheckable(true);
        }
        setCentralWidget(contentPane);
        resize(canvas_width, canvas_height + 20);
        setVisible(true);
        show();
        renderer->update();
    }

public slots:
    void policyToggled(bool checked) {
        D("checked=" << checked);
        if (checked) {
            pLayer->setSpp(spp);
        } else {
            pLayer->setSpp(nullptr);
        }
        renderer->update();
    }
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_VALUEFUNCTIONVIS_VALUE_FUNCTION_VISUALIZER_GUI_HPP
