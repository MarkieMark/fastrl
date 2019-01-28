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

using namespace std;

class TextAreaStreams;

class TextOut : public ostream, public streambuf {
public:
    QTextEdit * area_p;
    explicit TextOut(TextAreaStreams * tas);
    int overflow(int b) override;
};

class TextIn : public istream, public streambuf {
public:
    TextAreaStreams * tas;
    string * input_buf_p;
    int * buf_index_p;
    mutex * m_buf_p;
    condition_variable * cv_buf_p;
    unique_lock<mutex> * lck_buf_p;
    explicit TextIn(TextAreaStreams * tas);
    void pointersFromStreams();
    int underflow() override;
};

class TextAreaStreams {
public:
    QTextEdit * area;
    string inputBuf;
    int bufIndex = 0;
    mutex * m_buf_p;
    condition_variable * cv_buf_p;
    unique_lock<mutex> * lck_buf_p;
    TextOut * tout;
    TextIn * tin;
    FastRLShell * shell;

    explicit TextAreaStreams(QTextEdit * area_);

    void setLockPointers(mutex * m_p, condition_variable * cv_p, unique_lock<mutex> * lck_p);

    void setShell(FastRLShell * sh){
        shell = sh;
    }

    TextOut * getTout() {
        return tout;
    }

    TextIn * getTin() {
        return tin;
    }

    /**
     * Adds data to the istream
     * @param input the string data to add.
     */
    void receiveInput(string &input);
};

#endif //FASTRL_SHELL_VISUAL_TEXT_AREA_STREAMS_H
