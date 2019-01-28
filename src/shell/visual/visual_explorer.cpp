/*
 * Mark Benjamin 30th January 2019
 * (c) Mark Benjamin 2019
 */

#include <QtWidgets/QVBoxLayout>
#include "visual_explorer.h"
#include "../../mdp/core/oo/OO_domain.h"
#include "../../mdp/core/oo/propositional/grounded_prop.h"

VisualExplorer::VisualExplorer(SADomain * domain, Visualizer * painter, State * base_state) : QMainWindow(nullptr) {
    Environment * env = new SimulatedEnvironment(domain, base_state);
    init(domain, env, painter, 700, 700);
}

VisualExplorer::VisualExplorer(SADomain * domain, Environment * env, Visualizer * painter) : QMainWindow(nullptr) {
    init(domain, env, painter, 700, 700);
}

VisualExplorer::VisualExplorer(SADomain * domain, Environment * env, Visualizer * painter, int w, int h) : QMainWindow(nullptr) {
    init(domain, env, painter, w, h);
}

void VisualExplorer::init(SADomain * domain_, Environment * env_, Visualizer * painter_, int w, int h) {
    domain = domain_;
    env = env_;
    painter = painter_;
    keyActionMap = map<string, Action *>();
    keyShellMap.insert(pair<string, string>("`", "reset"));
    canvas_width = w;
    canvas_height = h;
    propViewer = new QTextEdit();
    propViewer->setReadOnly(true);
}

void VisualExplorer::startLiveStatePolling(const int msPollDelay){
    pollInterval = msPollDelay;
    if (livePollingTimer != nullptr) {
        if (!(livePollingTimer->isActive())) {
            livePollingTimer->start();
        }
        return;
    }

    auto * timer = new QTimer();
    timer->setInterval(pollInterval);
    timer->start();
}

void VisualExplorer::animation_timer_poll() {
    State * s = env->currentObservation();
    if(s != nullptr) {
        updateState(s);
    }
}

void VisualExplorer::live_timer_poll() {
    animation_timer_poll();
}

void VisualExplorer::stopLivePolling() {
    if (livePollingTimer->isActive()) {
        livePollingTimer->stop();
    }
}

void VisualExplorer::updateState(State * s) {
    painter->updateState(s);
    updatePropTextArea(s);
}

void VisualExplorer::updatePropTextArea(State * s) {
    if(dynamic_cast<OODomain *>(domain) == nullptr || dynamic_cast<OOState *>(s) == nullptr){
        return;
    }
    string buf;
    vector<PropositionalFunction *> props = dynamic_cast<OODomain *>(domain)->propFunctions();
    for (PropositionalFunction * pf : props) {
        vector<GroundedProp *> gps = pf->allGroundings(dynamic_cast<OOState *>(s));
        for(GroundedProp * gp : gps) {
            if(gp->isTrue(dynamic_cast<OOState *>(s))) {
                buf += gp->to_string();
                buf += "\n";
            }
        }
    }
    propViewer->setText(QString::fromStdString(buf));
}

void VisualExplorer::observeCommand(FastRLShell * shell, ShellCommandEvent * event) {
    if(event->returnCode == 1){
        updateState(env->currentObservation());
    }
    if(dynamic_cast<ObservationCommand *>(event->command) != nullptr){
        updateState(env->currentObservation());
    }
}

void VisualExplorer::handleAct() {
    string actionCommand = actionField->toPlainText().toStdString();
    if(actionCommand.empty()){
        return;
    }
    shell->actionCommand("ac " + actionCommand);
    actionField->clear();
}

void VisualExplorer::handleKeyPressed(QKeyEvent * e) {
    string key;
    key += char(e->key());
//    cout << key << " pressed" << endl;
    //otherwise this could be an action, see if there is an action mapping
    auto found = keyActionMap.find(key);
    if (found != keyActionMap.end()) {
        Action * mappedAction = found->second;
//        cout << mappedAction->to_string() << endl;
        implementAction(mappedAction);
    } else {
        auto found_ = keyShellMap.find(key);
        if (found_ !=  keyShellMap.end() && shell != nullptr) {
            string shellCommand = found_->second;
//            cout << shellCommand << endl;
            dynamic_cast<FastRLShell *>(shell)->actionCommand(shellCommand);
        }
    }
}

void VisualExplorer::implementAction(Action * a) {
    EnvironmentOutcome * eo = env->act(a);
    updateState(eo->o_prime);
}

void VisualExplorer::initGUI() {
//    painter->resize(canvas_width - 50, canvas_height - 50);
    cout << "canvas width " << canvas_width << ", canvas height " << canvas_height << endl;
// need to add some encapsulation
    propViewer->resize(canvas_width, 100);
//    painter->resize(canvas_width - 100, canvas_height - 300);
    resize(canvas_width, canvas_height);
    auto * containerVE = new QWidget(this);
    auto * qvl = new QVBoxLayout();
    auto * qhl = new QHBoxLayout();
    auto * qhw = new QWidget();
    propViewer->setFixedHeight(100);
    qvl->addWidget(painter);
    qvl->setSpacing(3);
    qvl->addWidget(propViewer);
    actionField = new EnterButtonTextEdit();
    actionButton = new QPushButton("Act");
    actionField->button = actionButton;
    // todo connect actionField return key to actionButton click, clear actionField upon click
    qhl->addWidget(actionField);
    qhl->addWidget(actionButton);
    qhw->setLayout(qhl);
    qhw->setFixedHeight(50);
//    qhl->setFixedHeight(50);
    qvl->addWidget(qhw);
    showShellButton = new QPushButton("Show Shell");
    qvl->addWidget(showShellButton);
    containerVE->setLayout(qvl);
    setCentralWidget(containerVE);
    // check focused painter key event calls this->keyPressEvent()
    // ditto for propViewer
    connect(actionButton, &QPushButton::clicked, this, &VisualExplorer::handleAct);
    connect(showShellButton, &QPushButton::clicked, this, &VisualExplorer::showShell);

    painter->repaint();
    painter->updateState(env->currentObservation());

    updatePropTextArea(env->currentObservation());
    consoleWindow = new QMainWindow();
    consoleWindow->resize(canvas_width, canvas_height);
    stateConsole = new ShiftFocusTextEdit();
    tstreams = new TextAreaStreams(stateConsole);
    consoleCommand = new EnterTextEdit();
    consoleCommand->streams = tstreams;
    stateConsole->refocusWidget = consoleCommand;
    consoleCommand->outputTextEdit = stateConsole;
//    check wrap
//    check caret
    stateConsole->setReadOnly(true);
    stateConsole->setContentsMargins(10, 5, 10, 5);
    // check scrolling
    auto * cvbl = new QVBoxLayout();
    cvbl->addWidget(stateConsole);
    shell = new EnvironmentShell(domain, env, tstreams->getTin(), tstreams->getTout());
    tstreams->setShell(shell);
    tstreams->setLockPointers(&(shell->m_is), &(shell->cv_is), &(shell->lck_is));
    tstreams->getTin()->pointersFromStreams();
    auto vso = vector<ShellObserver *>{this};

    shell->addObservers(vso);
    shell->setVisualizer(painter);

//    shell->addCommand(new LivePollCommand());

//    shell->thread_start();

    consoleCommand->setFixedHeight(30);
    cvbl->addWidget(consoleCommand);
    auto * containerVEC = new QWidget(consoleWindow);
    consoleWindow->setCentralWidget(containerVEC);
    containerVEC->setLayout(cvbl);
    consoleWindow->setVisible(false);
    setWindowTitle("FastRL Visual Interface");
//    cout << "set window title" << endl;
    show();
    painter->repaint();
    painter->updateState(env->currentObservation());
//    cout << "interface show" << endl;
//    consoleWindow->show();
//    cout << "console show" << endl;
}

void VisualExplorer::keyPressEvent(QKeyEvent * e) {
    handleKeyPressed(e);
}

void VisualExplorer::showShell() {
    consoleWindow->setWindowTitle("shell console");
    consoleWindow->setVisible(true);
    consoleWindow->show();
    consoleCommand->setFocus();
    shell->thread_start();
}

void ShiftFocusTextEdit::mousePressEvent(QMouseEvent *event) {
    refocusWidget->setFocus();
}

void EnterTextEdit::keyPressEvent(QKeyEvent *e) {
//    cout << char(e->key());
    if (e->key() == Qt::Key_Return) {
//        cout << endl;
        QString command = toPlainText();
        string cmd = command.toStdString();
        cout << "'" << cmd << "'" << endl;
        outputTextEdit->moveCursor(QTextCursor::End);
        outputTextEdit->insertPlainText(command);
        outputTextEdit->moveCursor(QTextCursor::End);
        setPlainText(QString(""));
        cmd += "\n";
        streams->receiveInput(cmd);
    } else {
        QTextEdit::keyPressEvent(e);
    }
}

void EnterButtonTextEdit::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Return) {
        button->click();
    } else {
        QTextEdit::keyPressEvent(e);
    }
}
