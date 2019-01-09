/**
 * Mark Benjamin 9th January 2019
 */

#ifndef FASTRL_SHELL_COMMAND_RESERVED_ALIAS_COMMAND_HPP
#define FASTRL_SHELL_COMMAND_RESERVED_ALIAS_COMMAND_HPP

#include "../../fastrl_shell.h"

class AliasCommand : public ShellCommand {
//protected OptionParser parser = new OptionParser("fh*");
//
public:
    string commandName() override {
        return "alias";
    }

//    @Override
//public int call(BurlapShell shell, String argString, Scanner is, PrintStream os) {
//        OptionSet oset = parser.parse(argString.split(" "));
//        List<String> arguments = (List<String>)oset.nonOptionArguments();
//
//        if(oset.has("h")){
//            os.println("[-f] commandName alias\n-f: force assignment of alias even if existing command has the name of the alias.");
//        }
//
//        if(arguments.size() != 2){
//            return -2;
//        }
//
//        if(oset.has("f")){
//            shell.setAlias(arguments.get(0), arguments.get(1));
//        }
//        else{
//            shell.setAlias(arguments.get(0), arguments.get(1), true);
//        }
//
//        return 0;
//    }
};

#endif // FASTRL_SHELL_COMMAND_RESERVED_ALIAS_COMMAND_HPP
