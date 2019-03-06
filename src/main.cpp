//
// Mark Benjamin 5/30/17.
// Copyright (c) 2017 Mark Benjamin
//

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <QMetaType>
#include "domain/singleagent/gridworld/grid_world_domain.h"
#include "include/entry_point.hpp"
#include "include/macros.h"
#include "main.h"

char* getCmdOption(char ** begin, char ** end, const string & option) {
    char ** itr = find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return nullptr;
}

bool cmdOptionExists(char** begin, char** end, const string& option) {
    return find(begin, end, option) != end;
}

void printMainArgs(int argc, char * argv[]) {
    for (int i = 0; i < argc; i++) {
        cout << i << " \"" << argv[i] <<"\"" << endl;
    }
    cout << "args " << argc << endl;
}

int main (int argc, char * argv[]) {
    printMainArgs(argc, argv);
    ENTRY(GridWorldDomain);
    if (argc > 1) {
        char *mainName = getCmdOption(argv, argv + argc, "-main");
        int id = QMetaType::type(mainName);
        if (id != QMetaType::UnknownType) {
            auto * mainClassPtr = static_cast<EntryPoint *>(QMetaType::create(id));
            int ret = mainClassPtr->main(argc, argv);
            QMetaType::destroy(id, mainClassPtr);
            mainClassPtr = nullptr;
            return ret;
        } else {
            cout << "Unrecognized class name" << endl;
        }
    } else {
        cout << endl << "usage:" << endl << "$ " << *(argv[0]) << " -main <MainClassName> [<option_number>]" << endl << endl;
        cout << "For instance" << endl << "$ " << *(argv[0]) << " -main GridWorldDomain 2" << endl << endl;
    }
}
