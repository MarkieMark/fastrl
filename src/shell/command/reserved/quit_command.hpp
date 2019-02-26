/**
 * Mark Benjamin 9th January 2019
 */

#ifndef FASTRL_SHELL_COMMAND_RESERVED_QUIT_COMMAND_HPP
#define FASTRL_SHELL_COMMAND_RESERVED_QUIT_COMMAND_HPP

class QuitCommand : public ShellCommand {
public:
    string commandName() override {
        return "quit";
    }

    int call(FastRLShell * shell, string argString, StreamWrapper * s) override {
        shell->close();
        return 0;
    }
};

#endif // FASTRL_SHELL_COMMAND_RESERVED_QUIT_COMMAND_HPP
