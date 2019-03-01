/*
 * Mark Benjamin 01 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_EPISODE_SEQUENCE_VISUALIZER_H
#define FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_EPISODE_SEQUENCE_VISUALIZER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QListView>
#include <QStringListModel>
#include "../episode.h"
#include "../../../visualizer/visualizer.h"
#include "../../../mdp/core/domain.hpp"

using namespace std;

class EpisodeSequenceVisualizer : public QWidget {

public:
    //Frontend GUI
    Visualizer *painter;
    QTextEdit *propViewer;
    QListView *episodeList;
    QListView *iterationList;
    QWidget *controlContainer;
    int canvas_width;
    int canvas_height;
    //Backend
    vector<string> episodeFiles;
    QStringListModel *episodesListModel;
    vector<Episode *> directEpisodes;
    Episode curEA;
    QStringListModel *iterationListModel;
    Domain *domain;
    bool alreadyInitedGUI = false;

    EpisodeSequenceVisualizer(Visualizer *v, Domain *d, string experimentDirectory);

    EpisodeSequenceVisualizer(Visualizer *v, Domain *d, string experimentDirectory, int w, int h);

    EpisodeSequenceVisualizer(Visualizer *v, Domain *d, vector<Episode *> episodes);

    EpisodeSequenceVisualizer(Visualizer *v, Domain *d, vector<Episode *> episodes, int w, int h);

    void init(Visualizer *v, Domain *d, string experimentDirectory, int w, int h);

    void initWithDirectEpisodes(Visualizer *v, Domain *d, vector<Episode *> episodes, int w, int h);

    void initGUI();

    void parseEpisodeFiles(string directory);

    void setIterationListData();

//    void handleEpisodeSelection(ListSelectionEvent * e);
//    void handleIterationSelection(ListSelectionEvent e);
    void updatePropTextArea(State *s);
};

#endif //FASTRL_BEHAVIOR_SINGLEAGENT_AUXILIARY_EPISODE_SEQUENCE_VISUALIZER_H
