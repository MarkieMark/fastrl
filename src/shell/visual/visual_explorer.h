#include <utility>

/*
 * Mark Benjamin 29 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_SHELL_VISUAL_VISUAL_EXPLORER_H
#define FASTRL_SHELL_VISUAL_VISUAL_EXPLORER_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QTimer>
#include <QKeyEvent>
#include "../shell_observer.hpp"
#include "../../mdp/singleagent/environment/environment.hpp"
#include "../../mdp/singleagent/SA_domain.h"
#include "../../visualizer/visualizer.h"
#include "../environment_shell.h"
#include "text_area_streams.h"

class EnterTextEdit;
class ShiftFocusTextEdit;
class EnterButtonTextEdit;

class VisualExplorer : public QMainWindow, public ShellObserver {
Q_OBJECT
public:
    Environment * env;
    SADomain * domain;
    map <string, Action *> keyActionMap;
    map <string, string> keyShellMap;
    Visualizer * painter;
    QTextEdit * propViewer;
    EnterButtonTextEdit * actionField;
    EnterTextEdit * consoleCommand;
    ShiftFocusTextEdit * stateConsole;
    QPushButton * actionButton;
    QPushButton * showShellButton;
    int canvas_width;
    int	canvas_height;
    QMainWindow * consoleWindow;
    QTimer * livePollingTimer;
    int pollInterval;
    EnvironmentShell * shell;
    TextAreaStreams * tstreams;
    VisualExplorer(SADomain * domain, Visualizer * painter, State * base_state);
    VisualExplorer(SADomain * domain, Environment * env, Visualizer * painter);
    VisualExplorer(SADomain * domain, Environment * env, Visualizer * painter, int w, int h);
    void init(SADomain * domain, Environment * env, Visualizer * painter, int w, int h);
    Visualizer * getVisualizer() {
        return painter;
    }
    EnvironmentShell * getShell() {
        return shell;
    }
    void addKeyAction(string key, Action * action){
        keyActionMap.insert(pair<string, Action*>(key, action));
    }
    void addKeyAction(string key, string actionTypeName, string paramStringRep) {
        keyActionMap.insert(pair<string, Action *>(key, domain->getAction(
                std::move(actionTypeName))->associatedAction(std::move(paramStringRep))));
    }
    void addKeyShellCommand(string key, string shellCommand){
        keyShellMap.insert(pair<string, string>(key, shellCommand));
    }
    void startLiveStatePolling(int msPollDelay);
    void stopLivePolling();
    void updateState(State * s);
    void updatePropTextArea(State * s);
    void observeCommand(FastRLShell * shell, ShellCommandEvent * event) override;
    void handleAct();
    void handleKeyPressed(QKeyEvent * e);
    void implementAction(Action * a);
    void initGUI();
    void showShell();
public slots:
    void animation_timer_poll();
    void live_timer_poll();
protected:
    void keyPressEvent(QKeyEvent * e) override;
};

class ShiftFocusTextEdit : public QTextEdit {
    Q_OBJECT
public:
    QWidget * refocusWidget = nullptr;
    explicit ShiftFocusTextEdit(QWidget * parent = nullptr) : QTextEdit(parent) { }
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

class EnterTextEdit : public QTextEdit {
public:
    QTextEdit * outputTextEdit = nullptr;
    TextAreaStreams * streams = nullptr;
    explicit EnterTextEdit(QWidget * parent = nullptr) : QTextEdit(parent) { }
protected:
    void keyPressEvent(QKeyEvent * e) override;
};

class EnterButtonTextEdit : public QTextEdit {
public:
    QPushButton * button = nullptr;
    explicit EnterButtonTextEdit(QWidget * parent = nullptr) : QTextEdit(parent) { }
protected:
    void keyPressEvent(QKeyEvent * e) override;
};

#endif //FASTRL_SHELL_VISUAL_VISUAL_EXPLORER_H
