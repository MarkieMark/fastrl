/**
 * Mark Benjamin 17th January 2019
 */

#ifndef FASTRL_SHELL_ENVIRONMENT_ENVIRONMENT_SHELL_H
#define FASTRL_SHELL_ENVIRONMENT_ENVIRONMENT_SHELL_H

#include <utility>
#include "fastrl_shell.h"
#include "../mdp/singleagent/environment/environment.hpp"
#include "../mdp/singleagent/environment/simulated_environment.h"
#include "command/env/action_command.h"
#include "command/env/observation_command.h"

class EnvironmentShell : public FastRLShell {
private:
    Environment * env;
public:
    EnvironmentShell(Domain * domain_, Environment * env_, StreamWrapper * s_) : FastRLShell(domain_, s_) {
        env = env_;
        welcomeMessage = "Welcome to the FastRL agent environment shell. Type the command 'help' to bring "
                              "up additional information about using this shell.";

        helpText = "Use the command help to bring up this message again. "
                        "Here is a list of standard reserved commands:\n"
                        "cmds - list all known commands.\n"
                        "aliases - list all known command aliases.\n"
                        "alias - set an alias for a command.\n"
                        "quit - terminate this shell.\n\n"
                        "Other useful, but non-reserved, commands are:\n"
                        "obs - print the current observation of the environment\n"
                        "ac - execute an action\n\n"
                        "Usually, you can get help on an individual command by passing it the -h option.";
        vector<ShellCommand *> std = generateStandard();
        for(ShellCommand * c : std){
            addCommand(c);
        }
    }
    EnvironmentShell(Domain * domain_, Environment * env_) : EnvironmentShell(domain_, env_, new StreamWrapper(nullptr)) { }
    EnvironmentShell(SADomain * domain_, State * s_) : EnvironmentShell(domain_,
            static_cast<Environment *>(new SimulatedEnvironment(domain_, s_)), new StreamWrapper(nullptr)) { }
    Environment * getEnv() { return env;}
    void setEnv(Environment * env_) { env = env_;}
    vector<ShellCommand *> generateStandard() override;
};


#endif // FASTRL_SHELL_ENVIRONMENT_ENVIRONMENT_SHELL_H
