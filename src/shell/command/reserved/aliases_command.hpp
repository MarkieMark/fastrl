/**
 * Mark Benjamin 9th January 2019
 */

#ifndef FASTRL_SHELL_COMMAND_RESERVED_ALIASES_COMMAND_HPP
#define FASTRL_SHELL_COMMAND_RESERVED_ALIASES_COMMAND_HPP

#include "../../fastrl_shell.h"

class AliasesCommand : public ShellCommand {
//protected OptionParser parser = new OptionParser("h*");
//
public:
    string commandName() override {
        return "aliases";
    }
//
//    @Override
//public int call(BurlapShell shell, String argString, Scanner is, PrintStream os) {
//
//        OptionSet oset = parser.parse(argString.split(" "));
//        if(oset.has("h")){
//            os.println("This command will list all known command aliases in the form a -> c, where a is the command" +
//                       "alias you can use to call the command, c");
//            return 0;
//        }
//
//        Set<Map.Entry<String, String>> aliases = shell.getAliases();
//        for(Map.Entry<String, String> e : aliases){
//            os.println(e.getKey() + " -> " + e.getValue());
//        }
//        return 0;
//    }
};

#endif // FASTRL_SHELL_COMMAND_RESERVED_ALIASES_COMMAND_HPP
