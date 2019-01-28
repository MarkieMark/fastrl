//
// Mark Benjamin 5/30/17.
// Copyright (c) 2017 Mark Benjamin
//

#ifndef FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_GRID_WORLD_DOMAIN_H
#define FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_GRID_WORLD_DOMAIN_H

#include <string>
#include <vector>
#include <thread>
#include "../../../mdp/singleagent/model/reward_function.hpp"
#include "../../../mdp/core/terminal_function.hpp"
#include "../../../mdp/core/oo/propositional/propositional_function.h"
#include "../../../mdp/core/oo/state/OO_state.hpp"
#include "../../../mdp/singleagent/oo/OOSA_domain.hpp"
#include "../../../mdp/singleagent/model/statemodel/full_state_model.h"
#include "../../../mdp/singleagent/common/uniform_cost_RF.h"
#include "../../../mdp/auxiliary/common/null_termination.hpp"
#include "../../../mdp/singleagent/model/factored_model.h"
#include "../../../mdp/core/action/universal_action_type.hpp"
#include "../../../mdp/singleagent/environment/environment.hpp"
#include "../../../shell/environment_shell.h"
#include "../../../mdp/singleagent/environment/simulated_environment.h"
#include "../../../behavior/singleagent/learning/tdmethods/Q_learning.h"
#include "../../../visualizer/visualizer.h"
#include "state/grid_agent.h"
#include "state/grid_location.h"
#include "state/grid_world_state.h"
#include "grid_world_terminal_function.h"
#include "grid_world_visualizer.h"

class GridWorldModel;
class WallToPF;


class GridWorldDomain {
private:
    // grid world dimensions
    // width
    unsigned int width;
    // height
    unsigned int height;
    // number of location types
    unsigned int numLocationTypes;
    // 2-d array wall map; 1 for wall present, 0 for wall absent
    vector<vector<unsigned int>> map;
    // 2-d array transition dynamics; for every action, probability of actual result
    vector<vector<double>> transitionDynamics;

    RewardFunction* rf = nullptr;
    TerminalFunction* tf = nullptr;

public:
    // variable keys
    // x
    static const std::string& VAR_X()
    {
        static const std::string str = "x";
        return str;
    }
    // y
    static const std::string& VAR_Y()
    {
        static const std::string str = "y";
        return str;
    }
    // location type
    static const std::string& VAR_TYPE()
    {
        static const std::string str = "type";
        return str;
    }
    // OO-MDP class names
    // agent
    static const std::string& CLASS_AGENT()
    {
        static const std::string str = "agent";
        return str;
    }
    // location
    static const std::string& CLASS_LOCATION()
    {
        static const std::string str = "location";
        return str;
    }
    // actions
    // north
    static const std::string& ACTION_NORTH()
    {
        static const std::string str = "north";
        return str;
    }
    // south
    static const std::string& ACTION_SOUTH()
    {
        static const std::string str = "south";
        return str;
    }
    // east
    static const std::string& ACTION_EAST()
    {
        static const std::string str = "east";
        return str;
    }
    // west
    static const std::string& ACTION_WEST()
    {
        static const std::string str = "west";
        return str;
    }
    // propositional functions
    // at location
    static const std::string& PF_AT_LOCATION()
    {
        static const std::string str = "atLocation";
        return str;
    }
    // wall to north
    static const std::string& PF_WALL_NORTH()
    {
        static const std::string str = "wallToNorth";
        return str;
    }
    // wall to south
    static const std::string& PF_WALL_SOUTH()
    {
        static const std::string str = "wallToSouth";
        return str;
    }
    // wall to east
    static const std::string& PF_WALL_EAST()
    {
        static const std::string str = "wallToEast";
        return str;
    }
    // wall to west
    static const std::string& PF_WALL_WEST()
    {
        static const std::string str = "wallToWest";
        return str;
    }

    GridWorldDomain();
    GridWorldDomain(unsigned int height_, unsigned int width_);
    explicit GridWorldDomain(vector<vector<unsigned int>> map_);

    void setNumberOfLocationTypes(unsigned int num_location_types);
    void setDeterministicTransitionDynamics();
    void setProbSucceedTransitionDynamics(double prob_succeed);
    void setTransitionDynamics(vector<vector<double>> transition_dynamics);
    vector<vector<double>> getTransitionDynamics();
    void makeEmptyMap();
    void setMap(vector<vector<unsigned int>> map_);
    void setMapToFourRooms();
    void horizontalWall(int xi, int xf, int y);
    void verticalWall(int yi, int yf, int x);
    void horizontal1DNorthWall(int xi, int xf, int y);
    void vertical1DEastWall(int yi, int yf, int x);
    void setObstacleInCell(int x, int y);
    void set1DNorthWall(int x, int y);
    void set1DEastWall(int x, int y);
    void clearLocationOfWalls(int x, int y);
    void setCellWallState(int x, int y, unsigned int wallType);
    vector<vector<unsigned int>> getMap();
    unsigned int getWidth();
    unsigned int getHeight();
    RewardFunction* getRf();
    void setRf(RewardFunction* rf_);
    TerminalFunction* getTf();
    void setTf(TerminalFunction* tf_);
    vector<PropositionalFunction *> generatePfs();
    OOSADomain * generateDomain();
    static vector<int> movementDirectionFromIndex(int i);
    string stringMap();
    string stringMap(vector<vector<int>> specials);
    void printMap();

    static int main(int argc, char * argv[]);
    static int main1(int argc, char * argv[]);
    static int main2(int argc, char * argv[]);

    friend GridWorldModel;
    friend WallToPF;
};

//string GridWorldDomain::VAR_X = "x";
//VAR_Y = "y";
//VAR_TYPE = "type";
//CLASS_AGENT = "agent";
//CLASS_LOCATION = "location";

class GridWorldModel : public FullStateModel{
private:
    vector<vector<double>> transitionDynamics;
    GridWorldDomain * parent;
    State * move(State * s, int xd, int yd);
public:
    vector<vector<unsigned int>> map;
//        Random rand = RandomFactory.getMapped(0);

    GridWorldModel(GridWorldDomain * parent_, vector<vector<unsigned int>> map_,
                   vector<vector<double>> transition_dynamics);
    vector<StateTransitionProb *> stateTransitions(State * s, Action * a) override;
    State * sample(State * s, Action * a) override;
    int actionInd(string name);
};

class AtLocationPF : public PropositionalFunction {
public:
    AtLocationPF(string name, vector<string> parameterClasses);
    bool isTrue(OOState * st, vector<string> params) override;
};

class WallToPF : public PropositionalFunction {
private:
    int xdelta;
    int ydelta;
    GridWorldDomain * parent;
public:
    WallToPF(GridWorldDomain * parent_, string name, vector<string> parameterClasses, int direction);
    bool isTrue(OOState * st, vector<string> params) override;
};

#endif // FASTRL_DOMAIN_SINGLEAGENT_GRIDWORLD_GRID_WORLD_DOMAIN_H
