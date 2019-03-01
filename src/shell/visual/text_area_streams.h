/*
 * Mark Benjamin 30th January 2019
 * (c) Mark Benjamin 2019
 */

#ifndef FASTRL_SHELL_VISUAL_TEXT_AREA_STREAMS_H
#define FASTRL_SHELL_VISUAL_TEXT_AREA_STREAMS_H

#include <QtWidgets/QTextEdit>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include "../fastrl_shell.h"
#include "../../include/classes.h"

using namespace std;

class TextAreaStreams {
public:
    QTextEdit * area;
    string inputBuf;
    mutex * m_buf_p;
    condition_variable * cv_buf_p;
    FastRLShell * shell;

    explicit TextAreaStreams(QTextEdit * area_);

    void setLockPointers(mutex * m_p, condition_variable * cv_p);

    void setShell(FastRLShell * sh) {
        shell = sh;
    }

    string getInput();

    void printOutput(string s);

    /**
     * Adds data to the istream
     * @param input the string data to add.
     */
    void receiveInput(string &input);
};

#endif //FASTRL_SHELL_VISUAL_TEXT_AREA_STREAMS_H
