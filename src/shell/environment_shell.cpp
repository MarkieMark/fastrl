//
// Created by mark on 1/18/19.
//

#include "environment_shell.h"

vector<ShellCommand *> EnvironmentShell::generateStandard() {
    auto ret = vector<ShellCommand *>();
    ret.push_back(new ActionCommand(domain));
    ret.push_back(new ObservationCommand());

//        EpisodeRecordingCommands erc = new EpisodeRecordingCommands();
//        return Arrays.asList(new ActionCommand(oosa_domain), new ObservationCommand(), new ResetEnvCommand(),
//                             new AddStateObjectCommand(oosa_domain), new RemoveStateObjectCommand(), new SetVarCommand(),
//                             new RewardCommand(), new IsTerminalCommand(),
//                             erc.getRecCommand(), erc.getBrowser(), new ListActionsCommand(), new ListPropFunctions());
    return ret;
}
