/**
 * Mark Benjamin 18th January 2019
 */

#ifndef FASTRL_SHELL_COMMAND_ENV_OBSERVATION_COMMAND_H
#define FASTRL_SHELL_COMMAND_ENV_OBSERVATION_COMMAND_H

#include "../../fastrl_shell.h"
#include "../../environment_shell.h"

class ObservationCommand : public ShellCommand {
public:
    explicit ObservationCommand() = default;

    string commandName() override {
        return "obs";
    }
    int call(FastRLShell * shell, string argString, istream * is, ostream * os) override;
};

#endif // FASTRL_SHELL_COMMAND_ENV_OBSERVATION_COMMAND_H
