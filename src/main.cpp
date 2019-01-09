//
// Mark Benjamin 5/30/17.
// Copyright (c) 2017 Mark Benjamin
//

#include <string>
#include <iostream>
#include <sstream>
#include "domain/singleagent/gridworld/grid_world_domain.h"

using namespace std;

#include <algorithm>

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

int main (int argc, char ** argv) {
//    cout << argc << endl;
    vector<string> args = vector<string>();
    for (int i = 0; i < argc; i++) {
//        cout << i << " \"" << argv[i] <<"\"" << endl;
        args.emplace_back(string(argv[i]));
        cout << "arg" << i << " " << args[i] << endl;
    }
    cout << "args " << args.size() << endl;
    if (argc > 1) {
        char *mainName = getCmdOption(argv, argv + argc, "-main");
        if (string(mainName) == "GridWorldDomain") {
            // TODO replace with QMetaType / QMetaObject reflection
            try {
                GridWorldDomain::main(args);
            } catch (string &e) {
                cout << "error " << e << endl;
            }
        } else {
            cout << "Unrecognized class name" << endl;
        }
    } else {
        cout << endl << "usage:" << endl << "$ " << args[0] << " -main <MainClassName> [<option_number>]" << endl << endl;
        cout << "For instance" << endl << "$ " << args[0] << " -main GridWorldDomain 2" << endl << endl;
    }
}
