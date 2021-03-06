/*
 * Mark Benjamin 9th January 2019.
 */

#ifndef FASTRL_FASTRL_SHELL_H
#define FASTRL_FASTRL_SHELL_H

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "../mdp/core/domain.hpp"
#include "../visualizer/visualizer.h"
#include "shell_observer.hpp"
#include "stream_wrapper.h"
#include "../include/classes.h"

using namespace std;

class FastRLShell {
public:
    string welcomeMessage = "Welcome to the FastRL shell. Type the command 'help' to bring "
                            "up additional information about using this shell";
    string helpText = "Use the command help to bring up this message again. "
                      "Here is a list of standard reserved commands:\n"
                      "cmds - list all known commands.\n"
                      "aliases - list all known command aliases.\n"
                      "alias - set an alias for a command.\n"
                      "quit - close the shell";
    Domain * domain;
    Visualizer * visualizer;
    thread * shell_thread;
    mutex m_is;
    condition_variable cv_is;
    bool input_ready = false;
    FastRLShell(Domain * domain_, StreamWrapper * s_);
    void addCommand(ShellCommand * command);
    void addCommandAs(ShellCommand * command, string as);
    void setAlias(string commandName, string alias);
    void setAlias(string commandName, string alias, bool force);
    void removeAlias(string alias);
    void removeCommand(string command);
    string getHelpText();
    void setHelpText(string helpText);
    string getWelcomeMessage();
    void setWelcomeMessage(string welcomeMessage);
    void close();
    StreamWrapper * getStreams();
    void setStreams(StreamWrapper * s);
    ShellCommand * resolveCommand(string commandName);
    string aliasPointer(string alias);
    set<string> getCommands();
    set<pair<string, string>> getAliases();
    Domain * getDomain();
    void setDomain(Domain * domain);
    Visualizer * getVisualizer();
    void setVisualizer(Visualizer * visualizer);
    void addObservers(vector<ShellObserver *> observers);
    void start_main_thread();
    void thread_start();
    void thread_join();
    void the_loop();
    void actionCommand(string input);

    vector<ShellCommand *> generateReserved();

    virtual vector<ShellCommand *> generateStandard();
private:
    StreamWrapper * streams;
    set<string> reserved;
    map<string, string> aliases;;
    map<string, ShellCommand *> commands;
    vector<ShellObserver *> observers;
    bool shutting;
};

class ShellCommand {
public:
    virtual string commandName() {throw runtime_error("ShellCommand::commandName Not Implemented");}
    virtual int call(FastRLShell * shell, string argString, StreamWrapper * s) {throw runtime_error("ShellCommand::call Not Implemented");} // NOLINT(performance-unnecessary-value-param)
};

class ShellOptParser {
public:
    vector<string> tokens;
    const string empty_string;
    const vector<string> empty_vector;
    explicit ShellOptParser(string &s) {
        istringstream i(s);
        tokens = vector<string>{istream_iterator<string>{i}, istream_iterator<string>{}};
//        for (const string &st : tokens) {
//            cout << st << endl;
//        }
    }
    const string & getOpt(const string &opt) const {
        auto it = find(tokens.begin(), tokens.end(), opt);
        if (it != tokens.end() && ++it != tokens.end()) {
            return *it;
        }
        return empty_string;
    }

    const vector<string> & getOpt(const string &opt, int n_opt) const {
        auto it = find(tokens.begin(), tokens.end(), opt);
        if (it == tokens.end()) {
            return empty_vector;
        }
        it++;
        auto * ret = new vector<string>();
        for (int ind = 0; (ind < n_opt) && (it != tokens.end()); ind++, it++) {
            ret->push_back(*it);
        }
        if (ret->size() < n_opt) {
            return empty_vector;
        }
        return *ret;
    }

    bool isOpt(const string &opt) const {
        return (find(tokens.begin(), tokens.end(), opt) != tokens.end());
    }

    const vector<string> nonOptArgs() const {
        auto * ret = new vector<string>;
        for (const auto &token : tokens) {
            if (token[0] == '-') {
                continue;
            }
            ret->push_back(token);
        }
        return *ret;
    }
};


#endif //FASTRL_FASTRL_SHELL_H
