/*
 * Mark Benjamin 29 January 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include "text_area_streams.h"

TextOut::TextOut(TextAreaStreams * tas) : ostream(this) {
    area_p = tas->area;
}

int TextOut::overflow(int b) {
    string s = string();
    s += char(b);
    area_p->moveCursor(QTextCursor::End);
    area_p->insertPlainText(QString::fromStdString(s));
    area_p->moveCursor(QTextCursor::End);
//    cout << "{" << char(b) << "}";
    return b;
}

TextIn::TextIn(TextAreaStreams * tas_) : istream(this) {
    tas = tas_;
}

void TextIn::pointersFromStreams() {
    input_buf_p = &(tas->inputBuf);
    buf_index_p = &(tas->bufIndex);
    m_buf_p = tas->m_buf_p;
    cv_buf_p = tas->cv_buf_p;
    lck_buf_p = tas->lck_buf_p;
}

int TextIn::underflow() {
    int b;
//    unique_lock<mutex> lck(*m_buf_p);
//    while (input_buf_p->empty()) {
//        cv_buf_p->wait(lck);
//    }
    if(*buf_index_p == input_buf_p->size()) {
        b = -1;
    } else {
        char c = (*input_buf_p)[*buf_index_p];
        b = int(c);
    }
    (*buf_index_p)++;
    if (*buf_index_p == input_buf_p->size() + 1) {
//        input_buf_p->erase();
        *input_buf_p = "";
        *buf_index_p = 0;
    }
//    lck_buf_p->unlock();
//    m_buf_p->unlock();
    //        input_buf_p->notifyAll();
    cout << "[" << char(b) << "]";
    return b;
}

TextAreaStreams::TextAreaStreams(QTextEdit * area_) :
    area(area_) {
    tout = new TextOut(this);
    tin = new TextIn(this);
    inputBuf = string("");
}

void TextAreaStreams::setLockPointers(mutex * m_p, condition_variable * cv_p, unique_lock<mutex> * lck_p) {
    m_buf_p = m_p;
    cv_buf_p = cv_p;
    lck_buf_p = lck_p;
}

void TextAreaStreams::receiveInput(string &input) {
    QString qs = QString::fromStdString(input);
    cout << "TextAreaStreams::receiveInput() QString '" << qs.toStdString() << "'" << endl;
//    area->append(qs);
    *lck_buf_p = unique_lock<mutex>(*m_buf_p);
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
    cv_buf_p->notify_all();
    lck_buf_p->unlock();
}
