/*
 * Mark Benjamin 25 February 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include "stream_wrapper.h"

string StreamWrapper::getInput() {
    string ret;
    if (source_is_stdin) {
        getline(cin, ret);
    } else {
        cout << "wrapper getting input from source" << endl;
        ret = tas->getInput();
    }
    cout << "wrapper input " << ret << endl;
    return ret;
}

void StreamWrapper::printOutput(string s, bool nl) {
    if (nl) {
        s += "\n";
    }
    if (dest_is_stdout) {
        cout << s;
    } else {
        tas->printOutput(s);
    }
}
