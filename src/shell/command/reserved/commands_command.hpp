/**
 * Mark Benjamin 9th January 2019
 */

#ifndef FASTRL_SHELL_COMMAND_RESERVED_COMMANDS_COMMAND_HPP
#define FASTRL_SHELL_COMMAND_RESERVED_COMMANDS_COMMAND_HPP

#include "../../fastrl_shell.h"

class CommandsCommand : public ShellCommand {
//protected OptionParser parser = new OptionParser("h*");
//

public:
    string commandName() override {
        return "cmds";
    }


    int call(FastRLShell * shell, string argString, StreamWrapper * s) override {

//        OptionSet oset = parser.parse(argString.split(" "));
//        if(oset.has("h")){
//            os.println("Lists all commands this shell can execute.");
//            return 0;
//        }

        for(const string &command : shell->getCommands()){
            s->printOutput(command);
        }
        return 0;
    }
};

#endif // FASTRL_SHELL_COMMAND_RESERVED_COMMANDS_COMMAND_HPP
