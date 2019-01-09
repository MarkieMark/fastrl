/**
 * Mark Benjamin 17th January 2019
 */

#ifndef FASTRL_SHELL_ENVIRONMENT_ENVIRONMENT_SHELL_HPP
#define FASTRL_SHELL_ENVIRONMENT_ENVIRONMENT_SHELL_HPP

#include <utility>
#include "fastrl_shell.h"
#include "../mdp/singleagent/environment/environment.hpp"
#include "../mdp/singleagent/environment/simulated_environment.h"
#include "command/env/execute_action_command.hpp"

class EnvironmentShell : public FastRLShell {
private:
    Environment env;
public:
    EnvironmentShell(Domain domain_, Environment env_, istream * is_, ostream * os_) : FastRLShell(domain_, is_, os_) {
        env = move(env_);
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
                        "ex - execute an action\n\n"
                        "Usually, you can get help on an individual command by passing it the -h option.";
    }
    EnvironmentShell(Domain domain_, Environment env_) : EnvironmentShell(domain_, move(env_), &cin, &cout) { }
    EnvironmentShell(SADomain domain_, State s_) : EnvironmentShell(move(domain_),
            *(static_cast<Environment *>(new SimulatedEnvironment(&domain_, &s_))), &cin, &cout) { }
    Environment getEnv() { return env;}
    void setEnv(Environment env_) { env = move(env_);}
    vector<ShellCommand *> generateStandard() override {
        auto ret = vector<ShellCommand *>();
        ret.push_back(new ExecuteActionCommand(domain));
//        EpisodeRecordingCommands erc = new EpisodeRecordingCommands();
//        return Arrays.asList(new ExecuteActionCommand(domain), new ObservationCommand(), new ResetEnvCommand(),
//                             new AddStateObjectCommand(domain), new RemoveStateObjectCommand(), new SetVarCommand(),
//                             new RewardCommand(), new IsTerminalCommand(),
//                             erc.getRecCommand(), erc.getBrowser(), new ListActionsCommand(), new ListPropFunctions());
        return ret;
    }
};



#endif // FASTRL_SHELL_ENVIRONMENT_ENVIRONMENT_SHELL_HPP