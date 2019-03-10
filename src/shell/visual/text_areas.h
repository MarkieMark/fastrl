/*
 * Mark Benjamin 08 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_SHELL_VISUAL_TEXT_AREAS_H
#define FASTRL_SHELL_VISUAL_TEXT_AREAS_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include "text_area_streams.h"

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

class ListenTextEdit : public QTextEdit {
    Q_OBJECT
public slots:
        void addText(const QString &s);
};

#endif //FASTRL_SHELL_VISUAL_TEXT_AREAS_H
