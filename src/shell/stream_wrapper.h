/*
 * Mark Benjamin 25 February 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_SHELL_STREAM_WRAPPER_H
#define FASTRL_SHELL_STREAM_WRAPPER_H

#include <string>
#include <iostream>
#include "visual/text_area_streams.h"

using namespace std;

class TextAreaStreams;

class StreamWrapper {
public:
    explicit StreamWrapper(TextAreaStreams * tas_) {
        if (tas_ != nullptr) {
            tas = tas_;
            source_is_stdin = false;
            dest_is_stdout = false;
        }
    }

    string getInput();
    void printOutput(string s, bool nl = true);
    bool source_is_stdin = true;
    bool dest_is_stdout = true;
private:
    TextAreaStreams * tas;
};

#endif //FASTRL_SHELL_STREAM_WRAPPER_H
