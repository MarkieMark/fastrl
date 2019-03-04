/*
 * Mark Benjamin 01 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#include <QVBoxLayout>
#include <QHBoxLayout>
#include "episode_sequence_visualizer.h"
#include "../../../mdp/core/oo/OO_domain.h"
#include "../../../mdp/core/oo/propositional/grounded_prop.h"

EpisodeSequenceVisualizer::EpisodeSequenceVisualizer(Visualizer * v, Domain * d, string experimentDirectory) {
    init(v, d, std::move(experimentDirectory), 800, 800);
}

EpisodeSequenceVisualizer::EpisodeSequenceVisualizer(Visualizer * v, Domain * d, string experimentDirectory,
        int w, int h) {
    init(v, d, std::move(experimentDirectory), w, h);
}

EpisodeSequenceVisualizer::EpisodeSequenceVisualizer(Visualizer * v, Domain * d, vector<Episode *> episodes) {
    initWithDirectEpisodes(v, d, std::move(episodes), 800, 800);
}

EpisodeSequenceVisualizer::EpisodeSequenceVisualizer(Visualizer * v, Domain * d, vector<Episode *> episodes,
        int w, int h){
    initWithDirectEpisodes(v, d, std::move(episodes), w, h);
}

void EpisodeSequenceVisualizer::init(Visualizer * v, Domain * d, string experimentDirectory, int w, int h) {
    painter = v;
    domain = d;
    //get rid of trailing / and pull out the file paths
    if (experimentDirectory[experimentDirectory.size() - 1] == '/') {
        experimentDirectory = experimentDirectory.substr(0, experimentDirectory.length());
    }
    parseEpisodeFiles(experimentDirectory);
    canvas_width = w;
    canvas_height = h;
    initGUI();
}

void EpisodeSequenceVisualizer::initWithDirectEpisodes(Visualizer * v, Domain * d, vector<Episode *> episodes,
        int w, int h){
    painter = v;
    domain = d;

    directEpisodes = std::move(episodes);
    episodesListModel = new QStringListModel();
    int c = 0;
    auto * string_list = new QStringList();
    for(Episode * ea : directEpisodes) {
        stringstream os;
        os << "episode" << c;
        string_list->append(QString::fromStdString(os.str()));
        c++;
    }
    episodesListModel->setStringList(*string_list);
    canvas_width = w;
    canvas_height = h;
    initGUI();
}

void EpisodeSequenceVisualizer::initGUI() {
    if (alreadyInitedGUI) {
        return;
    }
    alreadyInitedGUI = true;
    //set viewer components
    propViewer = new QTextEdit();
    propViewer->setReadOnly(true);
    painter->resize(canvas_width, canvas_height);
    propViewer->resize(canvas_width, 100);
    auto * qvl = new QVBoxLayout();
    auto * qhl = new QHBoxLayout();
    auto * qhc = new QWidget();
    qvl->addWidget(painter);
    qvl->addWidget(propViewer);
    //set episode component
    episodeList = new QListView();
    episodeList->setModel(episodesListModel);
    // todo connect signal/slot for list selection, item change, etcetera;
//    episodeList->setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
//    episodeList->setLayoutOrientation(JList.VERTICAL);
//    episodeList->setVisibleRowCount(-1);
//    episodeList->addListSelectionListener(new ListSelectionListener(){
//        @Override
//        public void valueChanged(ListSelectionEvent e) {
//            handleEpisodeSelection(e);
//        }
//    });
    episodeList->resize(100, 600);
    //set iteration component
    iterationListModel = new QStringListModel();
    iterationList = new QListView();
    iterationList->setModel(iterationListModel);
    // todo connect signal/slot for list selection, item change, etcetera;
//    iterationList->setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
//    iterationList->setLayoutOrientation(JList.VERTICAL);
//    iterationList->setVisibleRowCount(-1);
//    iterationList->addListSelectionListener(new ListSelectionListener(){
//        public void valueChanged(ListSelectionEvent e){
//            handleIterationSelection(e);
//        }
//    });
    iterationList->resize(150, 600);
    //add episode-iteration lists to window
//    controlContainer = new Container();
//    controlContainer.setLayout(new BorderLayout());
//    controlContainer.add(episodeScroller, BorderLayout.WEST);
//    controlContainer.add(iterationScroller, BorderLayout.EAST);
    /*
    //add render movie button
    JButton renderButton = new JButton("Render Episode Movie");
    renderButton.addActionListener(new ActionListener() {

        @Override
        public void actionPerformed(ActionEvent arg0) {
            //ExperimentVisualizer.this.handleEpisodeRender();

        }
    });
    controlContainer.add(renderButton, BorderLayout.SOUTH);*/
//    getContentPane().add(controlContainer, BorderLayout.EAST);
    qhl->addWidget(episodeList);
    qhl->addWidget(iterationList);
    qhc->setLayout(qhl);
    qhc->setMaximumHeight(100);
    qvl->addWidget(qhc);
    //display the window
//    pack();
    setVisible(true);
    show();
}

void EpisodeSequenceVisualizer::parseEpisodeFiles(string directory) {
//    File dir = new File(directory);
//    final String ext = ".episode";
//
//    FilenameFilter filter = new FilenameFilter() {
//        public boolean accept(File dir, String name) {
//            if(name.endsWith(ext)){
//                return true;
//            }
//            return false;
//        }
//    };
//    String[] children = dir.list(filter);
//    Arrays.sort(children, new AlphanumericSorting());
//
//    episodeFiles = new ArrayList<String>(children.length);
//    episodesListModel = new DefaultListModel();
//
//    for(int i = 0; i < children.length; i++){
//    episodeFiles.add(directory + "/" + children[i]);
//    episodesListModel.addElement(children[i].substring(0, children[i].indexOf(ext)));
//    //System.out.println(files.get(i));
//    }
}


void EpisodeSequenceVisualizer::setIterationListData() {
    //clear the old contents
//    iterationListModel->clear();
//    //add each action (that is taken in the state being rendered)
//    for(burlap.mdp.core.action.Action ga : curEA.actionSequence){
//        iterationListModel.addElement(ga.toString());
//    }
//    //add the final state
//    iterationListModel.addElement("final state");
}

//void EpisodeSequenceVisualizer::handleEpisodeSelection(ListSelectionEvent * e) {
//    if (!e.getValueIsAdjusting()) {
//        int ind = episodeList.getSelectedIndex();
//        //System.out.println("episode id: " + ind);
//        if (ind != -1) {
//            //System.out.println("Loading Episode File...");
//            if(this.directEpisodes == null) {
//                curEA = Episode.read(episodeFiles.get(ind));
//            } else {
//                curEA = this.directEpisodes.get(ind);
//            }
//            //curEA = EpisodeAnalysis.readEpisodeFromFile(episodeFiles.get(ind));
//            //System.out.println("Finished Loading Episode File.");
//
//            painter.updateState(NullState.instance); //clear screen
//            this.setIterationListData();
//        } else {
//            //System.out.println("canceled selection");
//        }
//    }
//}

//void EpisodeSequenceVisualizer::handleIterationSelection(ListSelectionEvent * e) {
//    if (!e.getValueIsAdjusting()) {
//        if (iterationList.getSelectedIndex() != -1) {
//            //System.out.println("Changing visualization...");
//            int index = iterationList.getSelectedIndex();
//            State curState = curEA.state(index);
//            //draw it and update prop list
//            //System.out.println(curState.getCompleteStateDescription()); //uncomment to print to terminal
//            painter.updateState(curState);
//            this.updatePropTextArea(curState);
//            //System.out.println("Finished updating visualization.");
//        } else {
//            //System.out.println("canceled selection");
//        }
//    }
//}

void EpisodeSequenceVisualizer::updatePropTextArea(State * s) {
    if(dynamic_cast<OODomain *>(domain) == nullptr || dynamic_cast<OOState *>(s) == nullptr) {
        return ;
    }
    string buf;
    vector<PropositionalFunction *> props = dynamic_cast<OODomain *>(domain)->propFunctions();
    for(PropositionalFunction * pf : props){
        //List<GroundedProp> gps = s.getAllGroundedPropsFor(pf);
        vector<GroundedProp *> gps = pf->allGroundings(dynamic_cast<OOState *>(s));
        for (GroundedProp * gp : gps) {
            if (gp->isTrue(dynamic_cast<OOState *>(s))) {
                buf += gp->to_string() + "\n";
            }
        }
    }
    propViewer->setText(QString::fromStdString(buf));
}
