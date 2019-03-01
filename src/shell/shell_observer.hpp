#include <utility>

/*
 * Mark Benjamin 9th January 2019.
 */

#ifndef FASTRL_FASTRL_SHELL_SHELL_OBSERVER_HPP
#define FASTRL_FASTRL_SHELL_SHELL_OBSERVER_HPP

#include "fastrl_shell.h"
#include "../include/classes.h"

class ShellObserver {
public:
    virtual void observeCommand(FastRLShell * shell, ShellCommandEvent * event) {throw runtime_error("ShellObserver::observeCommand() Not implemented"); }
};

class ShellCommandEvent {
public:
    string commandString;
    ShellCommand * command;
    int returnCode;
    ShellCommandEvent(string command_string, ShellCommand * comm, int return_code) :
        commandString(move(command_string)), command(comm), returnCode(return_code) { }
};

#endif // FASTRL_FASTRL_SHELL_SHELL_OBSERVER_HPP
