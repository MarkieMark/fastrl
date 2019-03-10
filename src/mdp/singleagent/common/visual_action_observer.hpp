
/*
 * Mark Benjamin 6th March 2019
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_MDP_SINGLEAGENT_COMMON_VISUAL_ACTION_OBSERVER_HPP
#define FASTRL_MDP_SINGLEAGENT_COMMON_VISUAL_ACTION_OBSERVER_HPP

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include "../../../shell/visual/text_areas.h"
#include "../../../visualizer/visualizer.h"
#include "../../core/oo/OO_domain.h"
#include "../../core/oo/propositional/grounded_prop.h"
#include "../environment/extensions/environment_observer.hpp"

class VisualActionObserver : public QMainWindow, public EnvironmentObserver {
Q_OBJECT
public:
    OODomain * domain;
    Visualizer * painter;
    ListenTextEdit * propViewer;
    int canvas_width;
    int canvas_height;
    long actionRenderDelay = 17; // milliseconds
    bool repaintStateOnEnvironmentInteraction = true;
    bool repaintOnActionInitiation = false;

    explicit VisualActionObserver(Visualizer * p, OODomain * d = nullptr, int canvasWidth = 800, int canvasHeight = 800)
    : painter(p), domain(d), canvas_width(canvasWidth), canvas_height(canvasHeight) {
        propViewer = new ListenTextEdit();
        propViewer->setReadOnly(true);
//        cout << "canvas width " << canvas_width << ", canvas height " << canvas_height << endl;
    }

    void setFrameDelay(bool d) { actionRenderDelay = d; }

    Visualizer * getPainter() { return painter; }

    void setPainter(Visualizer * p) { painter = p; }

    void setRepaintStateOnEnvironmentInteraction(bool isRepaint) { repaintStateOnEnvironmentInteraction = isRepaint; }

    void setRepaintOnActionInitiation(bool isRepaint) { repaintOnActionInitiation = isRepaint; }

    void initGUI() {
        painter->resize(canvas_width, canvas_height);
        propViewer->resize(canvas_width, 100);
        QWidget * container = new QWidget(this);
        QWidget * bc = new QWidget();
        bc->setMaximumHeight(100);
        auto * qvl = new QVBoxLayout();
        auto * qhl = new QHBoxLayout();
        qvl->addWidget(painter);
        qhl->addWidget(propViewer);
        bc->setLayout(qhl);
        qvl->addWidget(bc);
        connect(this, &VisualActionObserver::newPropText, propViewer, &ListenTextEdit::addText);
        container->setLayout(qvl);
        setCentralWidget(container);
        resize(canvas_width, canvas_height + 100);
        show();
//        update();
//        setVisible(true);
    }

    void observeEnvironmentActionInitiation(State * o, Action * action) override {
        if (repaintOnActionInitiation) {
            painter->updateStateAction(o, action);
            updatePropTextArea(o);
        }
    }

    void observeEnvironmentInteraction(EnvironmentOutcome * eo) override {
        if (repaintStateOnEnvironmentInteraction) {
            painter->updateState(eo->o_prime);
            updatePropTextArea(eo->o_prime);
        }
        this_thread::sleep_for(chrono::milliseconds(actionRenderDelay));
    }

    void observeEnvironmentReset(Environment * resetEnvironment) override {
        painter->updateState(resetEnvironment->currentObservation());
        updatePropTextArea(resetEnvironment->currentObservation());
        this_thread::sleep_for(chrono::milliseconds(actionRenderDelay));
    }

    void updatePropTextArea(State * s) {
        if (domain == nullptr || dynamic_cast<OOState *>(s) == nullptr) {
            return;
        }
        string buf;
        vector<PropositionalFunction *> props = domain->propFunctions();
        for (PropositionalFunction * pf : props) {
            vector<GroundedProp *> gps = pf->allGroundings(dynamic_cast<OOState *>(s));
            for (GroundedProp * gp : gps) {
                if (gp->isTrue(dynamic_cast<OOState *>(s))) {
                    buf += gp->to_string() + string("\n");
                }
            }
        }
        emit newPropText(QString::fromStdString(buf));
    }

signals:
    void newPropText(const QString &s);

};

#endif //FASTRL_MDP_SINGLEAGENT_COMMON_VISUAL_ACTION_OBSERVER_HPP
