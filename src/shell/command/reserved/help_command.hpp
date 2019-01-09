/**
 * Mark Benjamin 9th January 2019
 */

#ifndef FASTRL_SHELL_COMMAND_RESERVED_HELP_COMMAND_HPP
#define FASTRL_SHELL_COMMAND_RESERVED_HELP_COMMAND_HPP

class HelpCommand : public ShellCommand {
public:
    string commandName() override {
        return "help";
    }

    int call(FastRLShell * shell, string argString, istream * is, ostream * os) override {
        *os << shell->getHelpText() << endl;
        return 0;
    }
};

#endif // FASTRL_SHELL_COMMAND_RESERVED_HELP_COMMAND_HPP
