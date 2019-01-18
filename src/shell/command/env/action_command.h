/*
 * Mark Benjamin 21st January 2019.
 */

#ifndef FASTRL_SHELL_COMMAND_ENV_EXECUTE_ACTION_COMMAND_H
#define FASTRL_SHELL_COMMAND_ENV_EXECUTE_ACTION_COMMAND_H

#include <numeric>
#include "../../fastrl_shell.h"
#include "../../environment_shell.h"

class ActionCommand : public ShellCommand {
public:
    Domain * domain;
    map<string, string> action_name_map;
    explicit ActionCommand(Domain * domain_) : domain(domain_) {
//        cout << "ActionCommand()" << endl;
    }

    string commandName() override {
        return "ac";
    }

    int call(FastRLShell * shell, string argString, istream * is, ostream * os) override;
};

#endif //FASTRL_SHELL_COMMAND_ENV_EXECUTE_ACTION_COMMAND_H
