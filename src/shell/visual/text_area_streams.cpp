/*
 * Mark Benjamin 29 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include "text_area_streams.h"

string TextAreaStreams::getInput() {
    string ret;
    ret = string(inputBuf);
    cout << "retrieving '" << ret << "' from TAS::getInput()" << endl;
    inputBuf = "";
    return ret;
}

void TextAreaStreams::printOutput(string s) {
    area->moveCursor(QTextCursor::End);
    area->insertPlainText(QString::fromStdString(s));
    area->moveCursor(QTextCursor::End);
}

TextAreaStreams::TextAreaStreams(QTextEdit * area_) :
    area(area_) {
    inputBuf = string("");
}

void TextAreaStreams::setLockPointers(mutex * m_p, condition_variable * cv_p) {
    m_buf_p = m_p;
    cv_buf_p = cv_p;
}

void TextAreaStreams::receiveInput(string &input) {
    QString qs = QString::fromStdString(input);
    cout << "TextAreaStreams::receiveInput() QString '" << qs.toStdString() << "'" << endl;
//    area->append(qs);
    unique_lock<mutex> lck(*m_buf_p);
//    cout << "unique locked in TAS::receiveInput()" << endl;
//    string s = qs.toStdString();
    unsigned long isz = inputBuf.size();
    if (isz < 1) {
        inputBuf = string(input);
    } else {
//        inputBuf += *input;
        cout << "inputBuf non empty " << isz << " " << endl;
        cout << "'" << inputBuf << "'" << endl;
        string temp;
        temp += inputBuf;
        temp += input;
        inputBuf = temp;
    }
    shell->input_ready = true;
//    cout << "notifying from TAS::receiveInput()" << endl;
    cv_buf_p->notify_all();
//    cout << "unlocking unique from TAS::receiveInput()" << endl;
    lck.unlock();
//    cout << "unlocked unique from TAS::receiveInput()" << endl;
}
