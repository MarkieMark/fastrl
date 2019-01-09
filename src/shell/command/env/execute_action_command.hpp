/**
 * Mark Benjamin 18th January 2019
 */

#ifndef FASTRL_SHELL_COMMAND_ENV_EXECUTE_ACTION_COMMAND_HPP
#define FASTRL_SHELL_COMMAND_ENV_EXECUTE_ACTION_COMMAND_HPP

#include "../../fastrl_shell.h"

class ExecuteActionCommand : public ShellCommand {
public:
    explicit ExecuteActionCommand(Domain domain_) {
        cout << "ExecuteActionCommand()" << endl;
    }
    string commandName() override {
        return "ex";
    }
};


#endif // FASTRL_SHELL_COMMAND_ENV_EXECUTE_ACTION_COMMAND_HPP