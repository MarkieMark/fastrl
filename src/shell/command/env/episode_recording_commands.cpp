/*
 * Mark Benjamin 26th February 2019
 * (c) 2019 Mark Benjamin
 */

#include "episode_recording_commands.h"

RecordingCommand * EpisodeRecordingCommands::getRecCommand() {
    return recCommand;
}

EpisodeBrowserCommand * EpisodeRecordingCommands::getBrowser() {
    return browser;
}

void EpisodeRecordingCommands::observeEnvironmentActionInitiation(State * o, Action * action) {

}

void EpisodeRecordingCommands::observeEnvironmentInteraction(EnvironmentOutcome * eo) {
    if ((finished || curEpisode == nullptr) && recording) {
        curEpisode = new Episode(eo->o);
        curEpisode->transition(eo->a, eo->o_prime, eo->reward);
        finished = false;
    } else if (recording) {
        curEpisode->transition(eo->a, eo->o_prime, eo->reward);
    }
    recordedLast = false;
}

void EpisodeRecordingCommands::observeEnvironmentReset(Environment * resetEnvironment) {
    finished = true;
    if(autoRecord && recording && !recordedLast){
        episodes.push_back(curEpisode);
        recordedLast = true;
    }
}

