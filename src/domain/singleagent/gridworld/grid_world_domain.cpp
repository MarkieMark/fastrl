/**
 * Mark Benjamin 30th May 2017
 */
#include <iostream>
#include <QApplication>
#include "grid_world_domain.h"
#include "../../../shell/visual/visual_explorer.h"
#include "../../../main.h"

//Q_DECLARE_METATYPE(GridWorldDomain)

GridWorldDomain::GridWorldDomain() = default;

GridWorldDomain::GridWorldDomain(unsigned int height_, unsigned int width_)
    : GridWorldDomain()
{
    height = height_;
    width = width_;
    setDeterministicTransitionDynamics();
    makeEmptyMap();
}

GridWorldDomain::GridWorldDomain(vector<vector<unsigned int>> map_)
    : GridWorldDomain()
{
    map = std::move(map_);
    setDeterministicTransitionDynamics();
}

void GridWorldDomain::setNumberOfLocationTypes(unsigned int num_location_types) {
    numLocationTypes = num_location_types;
}

void GridWorldDomain::setDeterministicTransitionDynamics() {
    unsigned int n_actions = 4;
    transitionDynamics = vector<vector<double>>(n_actions);
    for (int i = 0; i < n_actions; i++) {
        transitionDynamics[i] = vector<double>(n_actions);
        for (int j = 0; j < n_actions; j++) {
            if (i != j) {
                transitionDynamics[i][j] = 0.;
            } else {
                transitionDynamics[i][j] = 1.;
            }
        }
    }
}

void GridWorldDomain::setProbSucceedTransitionDynamics(double prob_succeed) {
    unsigned int n_actions = 4;
    double pAlternative = (1. - prob_succeed) / 3.;
    transitionDynamics = vector<vector<double>>(n_actions);
    for (int i = 0; i < n_actions; i++) {
        transitionDynamics[i] = vector<double>(n_actions);
        for (int j = 0; j < n_actions; j++) {
            if (i != j) {
                transitionDynamics[i][j] = pAlternative;
            } else {
                transitionDynamics[i][j] = prob_succeed;
            }
        }
    }
}

void GridWorldDomain::setTransitionDynamics(vector<vector<double>> transition_dynamics) {
    unsigned int n_actions = 4;
    transitionDynamics = vector<vector<double>>(n_actions);
    for (int i = 0; i < n_actions; i++) {
        transitionDynamics[i] = vector<double>(n_actions);
        for (int j = 0; j < n_actions; j++) {
            transitionDynamics[i][j] = transition_dynamics[i][j];
        }
    }
}

vector<vector<double>> GridWorldDomain::getTransitionDynamics() {
    vector<vector<double>> ret = vector<vector<double>>(transitionDynamics.size());
    for (int i = 0; i < transitionDynamics.size(); i++) {
        ret[i] = transitionDynamics[i];
    }
    return ret;
}

void GridWorldDomain::makeEmptyMap() {
    map = vector<vector<unsigned int>>(width);
    for (int i = 0; i < width; i++) {
        map[i] = vector<unsigned int>(height);
        for (int j = 0; j < height; j++) {
            map[i][j] = 0;
        }
    }
}

void GridWorldDomain::setMap(vector<vector<unsigned int>> map_) {
    map = vector<vector<unsigned int>>(map_.size());
    for (int i = 0; i < map_.size(); i++) {
        map[i] = map_[i];
    }
}

void GridWorldDomain::setMapToFourRooms() {
    width = 11;
    height = 11;
    makeEmptyMap();
    horizontalWall(0, 0, 5);
    horizontalWall(2, 4, 5);
    horizontalWall(6, 7, 4);
    horizontalWall(9, 10, 4);
    verticalWall(0, 0, 5);
    verticalWall(2, 7, 5);
    verticalWall(9, 10, 5);
}

/**
 * Creates a sequence of 'complete' walls spanning the specified start to end
 * inclusive x coordinates.
 * @param xi The starting x coordinate of the wall
 * @param xf The ending x coordinate of the wall
 * @param y The y coordinate of the wall
 */
void GridWorldDomain::horizontalWall(int xi, int xf, int y) {
    for (int x = xi; x <= xf; x++) {
        map[x][y] = 1;
    }
}
/**
 * Creates a sequence of 'complete' walls spanning the specified start to end
 * inclusive y coordinates
 * @param yi The stating y coordinate of the wall
 * @param yf The ending y coordinate of the wall
 * @param x	The x coordinate of the wall
 */
void GridWorldDomain::verticalWall(int yi, int yf, int x) {
    for (int y = yi; y <= yf; y++) {
        map[x][y] = 1;
    }
}

/**
 * Creates a sequence of 1D north walls spanning the specified start to end
 * inclusive x coordinates.
 * If any of the cells spanned already have a east wall set in that location, then the cell
 * is set to have both an east wall & a north wall.
 * @param xi The starting x coordinate of the wall
 * @param xf The ending x coordinate of the wall
 * @param y The y coordinate of the wall
 */
void GridWorldDomain::horizontal1DNorthWall(int xi, int xf, int y){
    for(int x = xi; x <= xf; x++){
        int cur = map[x][y];
        if(cur != 3 && cur != 4){
            map[x][y] = 2;
        }
        else{
            map[x][y] = 4;
        }
    }
}

/**
 * Creates a sequence of 1D east walls spanning the specified start to end
 * inclusive y coordinates.
 * If any of the cells spanned already have a 1D north wall set in that location, then the cell
 * is set to have both a north wall & an east wall.
 * @param yi The stating y coordinate of the wall
 * @param yf The ending y coordinate of the wall
 * @param x	The x coordinate of the wall
 */
void GridWorldDomain::vertical1DEastWall(int yi, int yf, int x) {
    for(int y = yi; y <= yf; y++){
        int cur = map[x][y];
        if(cur != 2 && cur != 4){
            map[x][y] = 3;
        }
        else{
            map[x][y] = 4;
        }
    }
}

/**
 * Sets a complete cell obstacle in the designated location.
 * @param x the x coordinate of the obstacle
 * @param y the y coordinate of the obstacle
 */
void GridWorldDomain::setObstacleInCell(int x, int y){
    map[x][y] = 1;
}

/**
 * Sets a specified location to have a 1D north wall.
 * If the specified cell already has a 1D east wall set in that location, then the cell
 * is set to have both an east wall & a north wall.
 * @param x the x coordinate of the location to have the north wall
 * @param y the y coordinate of the location to have the north wall
 */
void GridWorldDomain::set1DNorthWall(int x, int y) {
    int cur = map[x][y];
    if(cur != 3 && cur != 4){
        map[x][y] = 2;
    }
    else{
        map[x][y] = 4;
    }
}

/**
 * Sets a specified location to have a 1D east wall.
 * If the specified cell already has a 1D north wall set in that location, then the cell
 * is set to have both a north wall & an east wall.
 * @param x the x coordinate of the location to have the east wall
 * @param y the y coordinate of the location to have the east wall
 */
void GridWorldDomain::set1DEastWall(int x, int y) {
    int cur = map[x][y];
    if(cur != 2 && cur != 4){
        map[x][y] = 3;
    }
    else{
        map[x][y] = 4;
    }
}

/**
 * Removes any obstacles or walls at the specified location.
 * @param x the x coordinate of the location
 * @param y the y coordinate of the location
 */
void GridWorldDomain::clearLocationOfWalls(int x, int y) {
    map[x][y] = 0;
}

/**
 * Sets the map at the specified location to have the specified wall configuration.
 * @param x the x coordinate of the location
 * @param y the y coordinate of the location
 * @param wallType the wall configuration for this location. 0 = no walls; 1 = complete wall/obstacle;
 * 2 = 1D north wall; 3 = 1D east wall; 4 = 1D north & east walls
 */
void GridWorldDomain::setCellWallState(int x, int y, unsigned int wallType){
    map[x][y] = wallType;
}

vector<vector<unsigned int>> GridWorldDomain::getMap() {
    vector<vector<unsigned int>> ret = vector<vector<unsigned int>>();
    for (const vector<unsigned int> &map_element : map) {
        auto ret_element = vector<unsigned int>();
        for (const unsigned int map_el : map_element) {
            ret_element.push_back(map_el);
        }
        ret.push_back(ret_element);
    }
//    cout << &ret << endl;
    return ret;
}

unsigned int GridWorldDomain::getWidth() { return width; }

unsigned int GridWorldDomain::getHeight() { return height; }

RewardFunction* GridWorldDomain::getRf() {
    return rf;
}

void GridWorldDomain::setRf(RewardFunction* rf_) {
    rf = rf_;
}

TerminalFunction* GridWorldDomain::getTf() {
    return tf;
}

void GridWorldDomain::setTf(TerminalFunction* tf_) {
    tf = tf_;
}

vector<PropositionalFunction *> GridWorldDomain::generatePfs(){
    vector<PropositionalFunction *> pfs = vector<PropositionalFunction *>();
    vector<string> vs1 = vector<string>();
    vector<string> vs2 = vector<string>();
    vs1.emplace_back(CLASS_AGENT());
    vs2.emplace_back(CLASS_AGENT());
    vs2.emplace_back(CLASS_LOCATION());
    pfs.push_back(new AtLocationPF(PF_AT_LOCATION(), vs2));
    pfs.push_back(new WallToPF(this, PF_WALL_NORTH(), vs1, 0));
    pfs.push_back(new WallToPF(this, PF_WALL_SOUTH(), vs1, 1));
    pfs.push_back(new WallToPF(this, PF_WALL_EAST(), vs1, 2));
    pfs.push_back(new WallToPF(this, PF_WALL_WEST(), vs1, 3));
    return pfs;
}

OOSADomain * GridWorldDomain::generateDomain() {
    auto * domain = new OOSADomain();
    vector<vector<unsigned int>> cmap = getMap();
    domain->addStateClass(CLASS_AGENT(), GridAgent::staticMetaObject);
    domain->addStateClass(CLASS_LOCATION(), GridLocation::staticMetaObject);
    GridWorldModel * smodel = new GridWorldModel(this, cmap, getTransitionDynamics());
//    RewardFunction* rf_ = rf;
//    TerminalFunction* tf_ = tf;
    if(rf == nullptr){
        rf = new UniformCostRF();
    }
    if(tf == nullptr){
        tf = new NullTermination();
    }
    auto * model = new FactoredModel(smodel, rf, tf);
    domain->setModel(model);

    domain->addActionTypes(
            vector<ActionType *>({
            new UniversalActionType(ACTION_NORTH()),
            new UniversalActionType(ACTION_SOUTH()),
            new UniversalActionType(ACTION_EAST()),
            new UniversalActionType(ACTION_WEST())}));
    OODomainHelper::addPfsToDomain(domain, generatePfs());
    return domain;
}

/**
 * Creates and returns a {@link fastrl.behavior.singleagent.auxiliary.valuefunctionvis.ValueFunctionVisualizerGUI}
 * object for a grid world. The value of states
 * will be represented by colored cells from red (lowest value) to blue (highest value). North-south-east-west
 * actions will be rendered with arrows using {@link burlap.behavior.singleagent.auxiliary.valuefunctionvis.common.ArrowActionGlyph}
 * objects. The GUI will not be launched by default; call the
 * {@link fastrl.behavior.singleagent.auxiliary.valuefunctionvis.ValueFunctionVisualizerGUI#initGUI()}
 * on the returned object to start it.
 * @param states the states whose value should be rendered.
 * @param maxX the maximum value in the x dimension
 * @param maxY the maximum value in the y dimension
 * @param valueFunction the value Function that can return the state values.
 * @param p the policy to render
 * @return a gridworld-based {@link burlap.behavior.singleagent.auxiliary.valuefunctionvis.ValueFunctionVisualizerGUI} object.
 */
//ValueFunctionVisualizerGUI getGridWorldValueFunctionVisualization(
//        List <State> states, int maxX, int maxY,
//        ValueFunction valueFunction, Policy p){
//    return ValueFunctionVisualizerGUI.createGridWorldBasedValueFunctionVisualizerGUI(
//            states, valueFunction, p, new OOVariableKey(
//                    CLASS_AGENT, VAR_X), new OOVariableKey(
//                    CLASS_AGENT, VAR_Y), new VariableDomain(0, maxX),
//            new VariableDomain(0, maxY), 1, 1, ACTION_NORTH, ACTION_SOUTH, ACTION_EAST, ACTION_WEST);
//}

/**
 * Returns the change in x and y position for a given direction number.
 * @param i the direction number (0,1,2,3 indicates north,south,east,west, respectively)
 * @return the change in direction for x and y; the first index of the returned double is change in x, the second index is change in y.
 */
vector<int> GridWorldDomain::movementDirectionFromIndex(int i) {
    vector<int> result;
    switch (i) {
        case 0:
            result = vector<int>{0,1};
            break;
        case 1:
            result = vector<int>{0,-1};
            break;
        case 2:
            result = vector<int>{1,0};
            break;
        case 3:
            result = vector<int>{-1,0};
            break;
        default:
            break;
    }
    return result;
}

string GridWorldDomain::stringMap(vector<vector<int>> specials) { // vector of values {x, y, code[, reward]}, code < 0 for an agent
    stringstream ret;
    for (int v_ind = height - 1; v_ind >= 0; v_ind--) {
        for (int h_ind = 0; h_ind < width; h_ind++) {
            int code = 0;
            stringstream repr;
            for (const vector<int> &special : specials) {
                if (special[0] == h_ind && special[1] == v_ind) {
                    code = special[2];
                    if (code > 0) {
                        repr << special[3];
                    }
                }
            }
            if (code == 0) {
                ret << map[h_ind][v_ind] << " ";
            } else {
                string r = (code < 0) ? "*" : repr.str();
            }
        }
        ret << endl;
    }
    return ret.str();
}

string GridWorldDomain::stringMap() {
    stringstream ret;
    for (int v_ind = height - 1; v_ind >= 0; v_ind--) {
        for (int h_ind = 0; h_ind < width; h_ind++) {
            ret << map[h_ind][v_ind] << " ";
        }
        ret << endl;
    }
    return ret.str();
}

void GridWorldDomain::printMap() {
    cout << stringMap();
}

GridWorldModel::GridWorldModel(GridWorldDomain * parent_, vector<vector<unsigned int>> map_,
               vector<vector<double>> transition_dynamics)
   : parent(parent_), map(std::move(map_)), transitionDynamics(std::move(transition_dynamics)) {
//    cout << &map << endl;
//    cout << "GridWorldModel()" << endl;
}

vector<StateTransitionProb *> GridWorldModel::stateTransitions(State * s, Action * a) {

    vector<double> directionProbs = transitionDynamics[actionInd(a->actionName())];

    vector<StateTransitionProb *> transitions = vector<StateTransitionProb *>();
    for(int i = 0; i < directionProbs.size(); i++){
        double p = directionProbs[i];
        if(p == 0.){
            continue; //cannot transition in this direction
        }
        State * ns = s->makeCopy();
        vector<int> dcomps = parent->movementDirectionFromIndex(i);
        ns = move(ns, dcomps[0], dcomps[1]);

        //make sure this direction doesn't actually stay in the same place and replicate another no-op
        bool isNew = true;
        for(StateTransitionProb * tp : transitions){
            if(*(tp->s) == *(ns)){
                isNew = false;
                tp->p += p;
                break;
            }
        }

        if(isNew){
            auto * tp = new StateTransitionProb(ns, p);
            transitions.push_back(tp);
        }
    }
    return transitions;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc30-c"
State * GridWorldModel::sample(State * s, Action * a) {
    s = s->makeCopy();
    vector<double> directionProbs = transitionDynamics[actionInd(a->actionName())];
    double roll = static_cast<double>(rand()) / RAND_MAX;
    double curSum = 0.;
    int dir = 0;
    for(int i = 0; i < directionProbs.size(); i++){
        curSum += directionProbs[i];
        if(roll < curSum){
            dir = i;
            break;
        }
    }

    vector<int> dcomps = parent->movementDirectionFromIndex(dir);
    return move(s, dcomps[0], dcomps[1]);

}
#pragma clang diagnostic pop

/**
 * Attempts to move the agent into the given position, taking into account walls and blocks
 * @param s the current state
 * @param xd the attempted new X position of the agent
 * @param yd the attempted new Y position of the agent
 * @return input state s, after modification
 */
State * GridWorldModel::move(State * s, int xd, int yd){

    auto *gws = dynamic_cast<GridWorldState *>(s);

    int ax = gws->agent->x;
    int ay = gws->agent->y;

    int nx = ax + xd;
    int ny = ay + yd;

//    hit wall, so do not change position
    unsigned long map_width = map[0].size();
    unsigned long map_height = map.size();
    bool solid_wall = false;
    bool thin_wall = false;
//    for (const vector<unsigned int> &row : map) {
//        if (row.empty() || row.size() < map[0].size()) {
//            cout << "map row wonky" << endl;
//        }
//    }
    if (nx < 0 || nx >= map_width || ny < 0 || ny >= map_height || map[nx][ny] == 1) {
        solid_wall = true;
    }
    if ((xd > 0 && (map[ax][ay] == 3 || map[ax][ay] == 4)) || (xd < 0 && (map[nx][ny] == 3 || map[nx][ny] == 4)) ||
       (yd > 0 && (map[ax][ay] == 2 || map[ax][ay] == 4)) || (yd < 0 && (map[nx][ny] == 2 || map[nx][ny] == 4))) {
        thin_wall = true;
    }
    if (solid_wall || thin_wall) {
        nx = ax;
        ny = ay;
    }

    GridAgent * newAgent = gws->agent;
    newAgent->x = nx;
    newAgent->y = ny;

    return s;
}

int GridWorldModel::actionInd(string name){
    if(name == GridWorldDomain::ACTION_NORTH()){
        return 0;
    }
    else if(name == GridWorldDomain::ACTION_SOUTH()){
        return 1;
    }
    else if(name == GridWorldDomain::ACTION_EAST()){
        return 2;
    }
    else if(name == GridWorldDomain::ACTION_WEST()){
        return 3;
    }
    throw runtime_error("Unknown action " + name);
}

/**
 * Propositional function for determining if the agent is at the same position as a given location object
 * @author James MacGlashan
 *
 * @param name name of function
 * @param parameterClasses the object class types for the parameters
 */

AtLocationPF::AtLocationPF(string name, vector<string> parameterClasses) :
    PropositionalFunction(std::move(name), std::move(parameterClasses)) {
    }

bool AtLocationPF::isTrue(OOState * st, vector<string> params) {
    ObjectInstance* agent = st->object(params[0]);
    ObjectInstance* location = st->object(params[1]);
    int ax = agent->getIntValue(new KeyContainer("x"));
    int ay = agent->getIntValue(new KeyContainer("y"));
    int lx = location->getIntValue(new KeyContainer("x"));
    int ly = location->getIntValue(new KeyContainer("y"));
    return ax == lx && ay == ly;
}

/**
 * Propositional function for indicating if a wall is in a given position relative to the agent position
 * @author James MacGlashan
 *
 */

/**
 * Initializes the function.
 * @param name the name of the function
 * @param parameterClasses the object class parameter types
 * @param direction the unit distance direction from the agent to check for a wall (0,1,2,3 corresponds to north,south,east,west).
 */
WallToPF::WallToPF(GridWorldDomain * parent_, string name, vector<string> parameterClasses, int direction) :
            PropositionalFunction(std::move(name), std::move(parameterClasses)), parent(parent_) {
    vector<int> dcomps = parent->movementDirectionFromIndex(direction);
    xdelta = dcomps[0];
    ydelta = dcomps[1];
}

bool WallToPF::isTrue(OOState * st, vector<string> params) {

    ObjectInstance * agent = st->object(params[0]);

    int ax = agent->getIntValue(new KeyContainer("x"));
    int ay = agent->getIntValue(new KeyContainer("y"));

    int cx = ax + xdelta;
    int cy = ay + ydelta;
    vector<vector<unsigned int>> m = parent->getMap();

    return cx < 0 || cx >= parent->getWidth() || cy < 0 ||
            cy >= parent->getHeight() || parent->getMap()[cx][cy] == 1 ||
           (xdelta > 0 && (m[ax][ay] == 3 || m[ax][ay] == 4)) ||
           (xdelta < 0 && (m[cx][cy] == 3 || m[cx][cy] == 4)) ||
           (ydelta > 0 && (m[ax][ay] == 2 || m[ax][ay] == 4)) ||
           (ydelta < 0 && (m[cx][cy] == 2 || m[cx][cy] == 4));
}

/**
 * Creates a visual explorer or terminal explorer. By default a visual explorer is presented; use the "t" argument
 * to create terminal explorer. Will create a 4 rooms grid world with the agent in lower left corner and a location in
 * the upper right. Use w-a-s-d to move.
 * @param args command line args
 */
int GridWorldDomain::main(int argc, char * argv[]) {
//    cout << "GridWorldDomain::main()" << endl;
//    cout << "option " << args[args.size() - 1] << endl;
    if (string(argv[argc - 2]) == string("2")) {
        return GridWorldDomain::main2(argc, argv);
    } else {
        return GridWorldDomain::main1(argc, argv);
    }
}

int GridWorldDomain::main1(int argc, char * argv[]) {
    cout << "GridWorldDomain::main1()" << endl;
    auto * gwdg = new GridWorldDomain(11, 11);
    gwdg->setMapToFourRooms();
    gwdg->setProbSucceedTransitionDynamics(0.75);
    gwdg->printMap();

    OOSADomain * d = gwdg->generateDomain();
    GridWorldState * s = new GridWorldState(
            new GridAgent(0, 0), vector<GridLocation *>({new GridLocation(10, 10, -1, "loc0")}));

    int expMode = 0;
    if (argc > 4) {
        string st = string(argv[4]);
        cout << "checking args[4] " << st << endl;
        if (st == string("v")) { // TODO adjust indices
            expMode = 1;
        } else if (st == string("t")) {
            expMode = 0;
        }
    }
    if (expMode == 0) {
//        cout << "making shell" << endl;
        auto * shell = new EnvironmentShell(d, static_cast<State *>(s));
//        cout << "shell made" << endl;
        dynamic_cast<FastRLShell *>(shell)->start_main_thread();
        return 0;
    }
    else if (expMode == 1) {
        QApplication app(argc, argv);

        Visualizer * v = GridWorldVisualizer::getVisualizer(gwdg->getMap());
        auto * ve = new VisualExplorer(d, v, s);

        //use w-s-a-d-x
        ve->addKeyAction("W", ACTION_NORTH(), "");
        ve->addKeyAction("S", ACTION_SOUTH(), "");
        ve->addKeyAction("A", ACTION_WEST(), "");
        ve->addKeyAction("D", ACTION_EAST(), "");

        ve->initGUI();
        int ret = QApplication::exec();
//        if (ve->getShell()->shell_thread != nullptr && ve->getShell()->shell_thread->joinable())
//        delete ve->getShell()->shell_thread;
        ve->shell->thread_join();
        return ret;
    }
    return -1;
}

int GridWorldDomain::main2(int argc, char * argv[]) {
    cout << "GridWorldDomain::main2()" << endl;
    auto * gwd = new GridWorldDomain(11, 11);
    gwd->setMapToFourRooms();
    gwd->setTf(new GridWorldTerminalFunction(10, 10));
    SADomain * domain = gwd->generateDomain();
    Environment * env = new SimulatedEnvironment(domain, new GridWorldState(0, 0, vector<GridLocation *>()));

//create a Q-learning agent
    auto * agent = new QLearning(domain, 0.99/*, new SimpleHashableStateFactory()*/, 1.0, 1.0);

////run 100 learning episode and save the episode results
    vector<Episode *> episodes = vector<Episode *>();
    for(int i = 0; i < 100; i++){
        episodes.push_back(agent->runLearningEpisode(env));
        env->resetEnvironment();
    }
////visualize the completed learning episodes
//    new EpisodeSequenceVisualizer(GridWorldVisualizer.getVisualizer(gwd->getMap()), domain, episodes);
    return 0;

}
