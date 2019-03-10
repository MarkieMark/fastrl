/**
 * Mark Benjamin 1st June 2017
 */

#include <limits>
#include <iomanip>
#include "Q_learning.h"
#include "../../../valuefunction/constant_value_function.hpp"
#include "../../../policy/epsilon_greedy.h"
#include "../../../learningrate/constant_LR.hpp"
#include "../../../../mdp/singleagent/environment/simulated_environment.h"
#include "../../options/option.h"
#include "../../../../domain/singleagent/gridworld/state/grid_world_state.h"
#include "../../../../mdp/singleagent/model/factored_model.h"
#include "../../../../domain/singleagent/gridworld/grid_world_domain.h"

QLearning::QLearning(SADomain * domain_, double gamma_, double qInitial,
                     double learning_rate) {
    QLInit(domain_, gamma_, new ConstantValueFunction(qInitial), learning_rate,
           new EpsilonGreedy(this, 0.1), numeric_limits<int>::max());
}

QLearning::QLearning(SADomain * domain_, double gamma_, double qInitial,
                     double learning_rate, int max_episode_size) {
    QLInit(domain_, gamma_, new ConstantValueFunction(qInitial), learning_rate,
           new EpsilonGreedy(this, 0.1), max_episode_size);
}

QLearning::QLearning(SADomain * domain_, double gamma_, double qInitial,
                     double learning_rate, Policy * learning_policy,
                     int max_episode_size) {
    QLInit(domain_, gamma_, new ConstantValueFunction(qInitial), learning_rate,
           learning_policy, max_episode_size);
}

QLearning::QLearning(SADomain * domain_, double gamma_, QFunction * qInitial,
                     double learning_rate, Policy *learning_policy,
                     int max_episode_size) {
    QLInit(domain_, gamma_, qInitial, learning_rate, learning_policy, max_episode_size);
}

void QLearning::QLInit(SADomain * domain_, double gamma_, QFunction * qInitial,
                       double learning_rate, Policy * learning_policy, int max_episode_size) {
    solverInit(domain_, gamma_);
//    qFunction = map<State *, QLearningStateNode *>();
    learningRate = new ConstantLR(learning_rate);
    learningPolicy = learning_policy;
    maxEpisodeSize = max_episode_size;
    qInitFunction = qInitial;
    nEpisodesForPlanning = 1;
    maxQChangeForPlanningConvergence = 0.;
}

void QLearning::initializeForPlanning(int n_episodes_for_planning) {
    nEpisodesForPlanning = n_episodes_for_planning;
}

void QLearning::setLearningRateFunction(LearningRate * lr) {
    learningRate = lr;
}

void QLearning::setQInitFunction(QFunction * q_init) {
    qInitFunction = q_init;
}

void QLearning::setLearningPolicy(Policy * p) {
    learningPolicy = p;
}

void QLearning::setMaximumEpisodesForPlanning(int n) {
    if (n > 0) {
        nEpisodesForPlanning = n;
    } else {
        nEpisodesForPlanning = 1;
    }
}

void QLearning::setMaxQChangeForPlanningConvergence(double m) {
    if (m > 0.) {
        maxQChangeForPlanningConvergence = m;
    } else {
        maxQChangeForPlanningConvergence = 0.;
    }
}

int QLearning::getLastEpisodeIterations() {
    return episodeIterationCounter;
}

void QLearning::toggleShouldDecomposeOption(bool active) {
    shouldDecomposeOptions = active;
}

vector<QValue *> QLearning::qValues(State * s) {
    return getQs(s);
}

double QLearning::qValue(State *s, Action * a) {
    return getQ(s, a)->q;
}

vector<QValue *> QLearning::getQs(State * s) {
    QLearningStateNode * node = getStateNode(s);
    return node->qEntry;
}

QValue * QLearning::getQ(State * s, Action * a) {
    QLearningStateNode * node = getStateNode(s);
    for (QValue * qv : node->qEntry) {
        if (qv->a == a) {
            return qv;
        }
    }
    return nullptr;
}

double QLearning::value(State * s) {
    return QProviderHelper::maxQ(this, s);
}

QLearningStateNode * QLearning::getStateNode(State * s) {
    QLearningStateNode *node;
    try {
        node = qFunction.at(s);
    } catch (...) {
        node  = nullptr;
    }
    if (node == nullptr) {
        node = new QLearningStateNode(s);
        vector<Action *> as = applicableActions(s);
        if (as.empty()) {
            throw runtime_error("No Possible Actions From the State");
        }
        for (Action * a : as) {
            node->addQValue(a, qInitFunction->qValue(s, a));
        }
        qFunction.insert(pair<State *, QLearningStateNode *>(s, node));
    }
    return node;
}


double QLearning::getMaxQ(State * s) {
    vector<QValue *> qs = getQs(s);
    double max = numeric_limits<double>::min();
    for (QValue * q : qs) {
        if (q->q > max) {
            max = q->q;
        }
    }
    return max;
}

Policy * QLearning::planFromState(State *initial_state) {
    if (model == nullptr) {
        throw runtime_error("QLearning Needs a Model to planFromState");
    }
    auto *env = new SimulatedEnvironment(domain, initial_state);
    int episodeCount = 0;
    do {
        runLearningEpisode(env, maxEpisodeSize);
        episodeCount++;
    } while ((episodeCount < nEpisodesForPlanning) && (maxQChangeForPlanningConvergence < maxQChangeInMostRecentEpisode));
    return new GreedyQPolicy(this);
}

Episode * QLearning::runLearningEpisode(Environment *env) {
    return runLearningEpisode(env, -1);
}

Episode * QLearning::runLearningEpisode(Environment *env, int max_iterations) {
    State * initialState = env->currentObservation();
    auto * e = new Episode(initialState);
    State * currentState = initialState; // TODO should possibly avoid pointers here
    episodeIterationCounter = 0;
    maxQChangeInMostRecentEpisode = 0.;
    print_grid_q_values();
    while (!(env->isInTerminalState()) && ((episodeIterationCounter < max_iterations) || max_iterations == -1)) {
        Action * action = learningPolicy->action(currentState);
        D("Action " << action->actionName());
        QValue * currentQ = getQ(currentState, action);
        EnvironmentOutcome * eo;
        if(dynamic_cast<Option *>(action) == nullptr) {
            eo = env->act(action);
        } else {
            eo = dynamic_cast<Option *>(action)->control(env, gamma);
        }
        State * sPrime = eo->o_prime;
        double maxQ = 0.;
        if (!eo->done) {
            maxQ = getMaxQ(sPrime);
        }
        double reward = eo->reward;
        double discount = (dynamic_cast<EnvironmentOptionOutcome *>(eo) != nullptr) ?
                          dynamic_cast<EnvironmentOptionOutcome *>(eo)->discount :
                          gamma;
        long increment = (dynamic_cast<EnvironmentOptionOutcome *>(eo) != nullptr) ?
                         dynamic_cast<EnvironmentOptionOutcome *>(eo)->nIterations() :
                         1;
        episodeIterationCounter += increment;
        if ((dynamic_cast<Option *>(action) == nullptr) || (shouldDecomposeOptions)) {
            e->transition(action, sPrime, reward);
        } else {
            e->appendThenMergeEpisode(dynamic_cast<EnvironmentOptionOutcome *>(eo)->episode);
        }
        double oldQ = currentQ->q;
        currentQ->q += learningRate->pollLearningRate(agentIterationCounter, currentState, action) *
                (reward + (discount * maxQ) - currentQ->q);
        double deltaQ = abs(oldQ - currentQ->q);
        if (deltaQ > maxQChangeInMostRecentEpisode) {
            maxQChangeInMostRecentEpisode = deltaQ;
        }
        currentState = env->currentObservation();
        agentIterationCounter++;
        D("agentIterationCounter " << agentIterationCounter);
        print_grid_q_values();
    }
    return e;
}

void QLearning::resetSolver() {
    qFunction.clear();
    episodeIterationCounter = 0;
    maxQChangeInMostRecentEpisode = numeric_limits<double>::max();
}

void QLearning::print_grid_q_values() {
    D("qFunction " << qFunction.size());
//    for (auto el : qFunction) {
//        auto * gws = dynamic_cast<GridWorldState *>(el.first);
//        auto * qln = el.second;
//        if (gws != nullptr) {
//            cout << "(" << gws->agent->x << "," << gws->agent->y << "):";
//            for (QValue * qv : qln->qEntry) {
//                Action * a = qv->a;
//                cout << setprecision(3) << a->actionName() << "=" << qv->q << ",";
//            }
//            cout << endl;
//        } else {
//            cout << el.first << ":" << el.second << endl;
//        }
//    }
    if (dynamic_cast<FactoredModel *>(model) != nullptr &&
        dynamic_cast<GridWorldModel *>(dynamic_cast<FactoredModel *>(model)->getStateModel()) != nullptr) {
        auto gwm = dynamic_cast<GridWorldModel *>(dynamic_cast<FactoredModel *>(model)->getStateModel());
        vector<vector<unsigned int>> map = gwm->map;
        unsigned long d1 = map.size();
        unsigned long d2 = map[0].size();
//            D("map dimensions " << d1 << ", " <<  d2);
        vector<vector<vector<double>>> q_value_map;
        int i, j, k;
        for (i = 0; i < d1; i++) {
            vector<vector<double>> q_value_row;
            for (j = 0; j < d2; j++) {
                vector<double> q_values(4);
                q_value_row.push_back(q_values);
            }
            q_value_map.emplace_back(q_value_row);
        }
//            D("Value Function " << valueFunction.size());
        for (auto p : qFunction) {
            State * s = p.first;
            if (dynamic_cast<GridWorldState *>(s) != nullptr) {
                auto * gws = dynamic_cast<GridWorldState *>(s);
//                    D(s << ":" << gws->agent->x << "," << gws->agent->y);
                for (k = 0; k < 4; k++) {
                    q_value_map[gws->agent->y][gws->agent->x][k] = p.second->qEntry[k]->q;
                }
            } else {
//                    D("non gridworld State " << s);
            }
        }
        for (j = 0; j < d2; j++) {
            for (i = 0; i < d1; i++) {
                for (k = 0; k < 4; k++) {
                    cout << setw(5) << setprecision(2) << q_value_map[d2 - j - 1][i][k] << " ";
                }
                cout << "  ";
            }
            cout << endl;
        }
    }
}
