/*
 * Mark Benjamin 26 February 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_SHELL_COMMAND_ENV_EPISODE_RECORDING_COMMANDS_H
#define FASTRL_SHELL_COMMAND_ENV_EPISODE_RECORDING_COMMANDS_H

#include "../../../mdp/singleagent/environment/extensions/environment_observer.hpp"
#include "../../../behavior/singleagent/episode.h"
#include "../../fastrl_shell.h"

class RecordingCommand : public ShellCommand {

};

class EpisodeBrowserCommand {

};

class EpisodeRecordingCommands : public EnvironmentObserver {
    vector <Episode *> episodes = vector<Episode *>();
    Episode * curEpisode;
    bool finished = false;
    bool autoRecord = false;
    bool recording = false;
    bool recordedLast = false;
    RecordingCommand * recCommand = new RecordingCommand();
    EpisodeBrowserCommand * browser = new EpisodeBrowserCommand();
    RecordingCommand * getRecCommand();
    EpisodeBrowserCommand * getBrowser();
    void observeEnvironmentActionInitiation(State * o, Action * action) override;
    void observeEnvironmentInteraction(EnvironmentOutcome * eo) override;
    void observeEnvironmentReset(Environment * resetEnvironment) override;
};


#endif //FASTRL_SHELL_COMMAND_ENV_EPISODE_RECORDING_COMMANDS_H
