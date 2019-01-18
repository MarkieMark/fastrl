//
// Created by mark on 1/18/19.
//
#include "observation_command.h"

int ObservationCommand::call(FastRLShell * shell, string argString, istream * is, ostream * os) {
    cout << "ObservationCommand::call()" << endl;
    ShellOptParser sp = ShellOptParser(argString);
    if (sp.isOpt("h") || sp.isOpt("-h")) {
        *os << "Prints the current observation from the environment." << endl;
        return 0;
    }
    EnvironmentShell * esh;
    esh = dynamic_cast<EnvironmentShell *>(shell);
    Environment * env = esh->getEnv();
    State * s = env->currentObservation();
    *os << s << " " << typeid(s).name() << " " << s->to_string() << endl;
    return 0;
}
