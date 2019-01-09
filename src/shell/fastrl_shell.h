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
#include "../mdp/core/domain.hpp"
#include "shell_observer.hpp"

using namespace std;

class ShellCommand;

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
    Domain domain;
    FastRLShell(Domain domain_, istream * is_, ostream * os_);
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
    istream * getIs();
    void setIs(istream * is);
    ostream * getOs();
    void setOs(ostream * os);
    ShellCommand * resolveCommand(string commandName);
    string aliasPointer(string alias);
    set<string> getCommands();
    set<pair<string, string>> getAliases();
    Domain getDomain();
    void setDomain(Domain domain);
    // Visualizer getVisualizer();
//    void setVisualizer(Visualizer visualizer);
    void addObservers(vector<ShellObserver> observers);
    void start();
    void executeCommand(string input);

    vector<ShellCommand *> generateReserved();

    virtual vector<ShellCommand *> generateStandard();
private:
    istream * is;
    ostream * os;
    set<string> reserved;
    map<string, string> aliases;;
    map<string, ShellCommand *> commands;
    vector<ShellObserver> observers;
    bool shutting;
};

class ShellCommand {
public:
    virtual string commandName() {throw runtime_error("ShellCommand::commandName Not Implemented");}
    virtual int call(FastRLShell * shell, string argString, istream * is, ostream * os) {throw runtime_error("ShellCommand::call Not Implemented");} // NOLINT(performance-unnecessary-value-param)
};


#endif //FASTRL_FASTRL_SHELL_H
