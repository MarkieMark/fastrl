/**
 * Mark Benjamin 9th January 2019
 */

#include "fastrl_shell.h"
#include "command/reserved/alias_command.hpp"
#include "command/reserved/quit_command.hpp"
#include "command/reserved/commands_command.hpp"
#include "command/reserved/aliases_command.hpp"
#include "command/reserved/help_command.hpp"

using namespace std;

FastRLShell::FastRLShell(Domain * domain_, StreamWrapper * s_) : streams(s_), domain(domain_)
{
//    this.scanner = new Scanner(is);
    vector<ShellCommand *> res = generateReserved();
    reserved = set<string>(); // (res.size());
    commands = map<string, ShellCommand *>();
    for (ShellCommand * c : res) {
        addCommand(c);
        reserved.insert(c->commandName());
    }
}

void FastRLShell::addCommand(ShellCommand * command){
//    cout << "FastRLShell::addCommand " << typeid(*command).name() << " " << command->commandName() << endl;
    if (reserved.count(command->commandName()) > 0) {
        streams->printOutput("Cannot add command " + command->commandName() + " because that is a reserved name. " +
            "Consider using addCommand(ShellCommand command, String as); to add it under a different name");
    } else {
        commands.insert(pair<string, ShellCommand *>(command->commandName(), command));
    }
}

void FastRLShell::addCommandAs(ShellCommand * command, string as) {
    if(reserved.count(as) > 0) {
        streams->printOutput("Cannot add command " + command->commandName() + " as " + as +
            " because that is a reserved name. " + "Please add it as a different name.");
    } else {
        commands.insert(pair<string, ShellCommand *>(as, command));
    }
}

void FastRLShell::setAlias(string commandName, string alias) {
    setAlias(move(commandName), move(alias), false);
}

void FastRLShell::setAlias(string commandName, string alias, bool force){

    if (reserved.count(alias) > 0) {
        streams->printOutput("Cannot give " + commandName + " the alias " + alias + " because that name is reserved.");
    } else if ((commands.count(alias) > 0) && !force) {
        streams->printOutput("Cannot give " + commandName + " the alias " + alias + " because that name is already assigned" +
           "to a command. If you wish to override, use the force option");
    } else {
        aliases.insert(pair<string, string>(alias, commandName));
        if ((commands.count(alias) > 0) && !(alias == commandName)) {
            commands.erase(alias);
        }
    }

}

void FastRLShell::removeAlias(string alias){
    aliases.erase(alias);
}

void FastRLShell::removeCommand(string command){
    if (reserved.count(command) == 0) {
        commands.erase(command);
    } else {
        streams->printOutput("Cannot remove command " + command + " because it is a reserved command.");
    }
}

string FastRLShell::getHelpText() {
    return helpText;
}

void FastRLShell::setHelpText(string help_text) {
    helpText = move(help_text);
}

string FastRLShell::getWelcomeMessage() {
    return welcomeMessage;
}

void FastRLShell::setWelcomeMessage(string welcome_message) {
    welcomeMessage = move(welcome_message);
}

void FastRLShell::close(){
    shutting = true;
}

StreamWrapper * FastRLShell::getStreams() {
    return streams;
}

void FastRLShell::setStreams(StreamWrapper * s_) {
    streams = s_;
//    this.scanner = new Scanner(is);
}

ShellCommand * FastRLShell::resolveCommand(string commandName){
//    cout << "FastRLShell::resolveCommand " << commandName << endl;
    if (aliases.count(commandName) > 0) {
        commandName = aliasPointer(commandName);
    }
    auto ret = commands.find(commandName);
    return ret == commands.end() ? nullptr : ret->second;
}

string FastRLShell::aliasPointer(string alias) {
    while (aliases.count(alias) > 0) {
        alias = aliases.find(alias)->second;
    }
    return alias;
}

set<string> FastRLShell::getCommands() {
    set<string> ret = set<string>();
    for (pair<string, ShellCommand *> command_pair : commands) {
        ret.insert(command_pair.first); // todo check semantics
    }
//    ret.insert(commands.begin(), commands.end());
    return ret;
}

set<pair<string, string>> FastRLShell::getAliases() {
    set<pair<string, string>> ret = set<pair<string, string>>();
    ret.insert(aliases.begin(), aliases.end());
    return ret;
}

Domain * FastRLShell::getDomain() {
    return domain;
}

void FastRLShell::setDomain(Domain * domain_) {
    domain = domain_;
}

//public Visualizer getVisualizer() {
//    return visualizer;
//}
//
//public void setVisualizer(Visualizer visualizer) {
//    this.visualizer = visualizer;
//}

void FastRLShell::addObservers(vector<ShellObserver *> observers_){
    for(ShellObserver * observer : observers_){
        observers.push_back(observer);
    }
}

void FastRLShell::start_main_thread() {
    shutting = false;
    the_loop();
}


void FastRLShell::thread_start() {
    shutting = false;
    shell_thread = new thread(&FastRLShell::the_loop, this);
//    shell_thread->detach();
}

void FastRLShell::thread_join() {
    shell_thread->join();
}

void FastRLShell::the_loop() {
    streams->printOutput(welcomeMessage);
//    cout << "printed '" << welcomeMessage << "' to " << os << endl;
    string input;
    while(!shutting){
        streams->printOutput("\n> ", false);
//        cout << "printed '> ' to " << os << endl;
        // get lock
//        cout << "locking unique lock in the loop" << endl;
        unique_lock<mutex> lck(m_is);
//        cout << "waiting for input ready cv in the loop" << endl;
        while (!input_ready) {
            cv_is.wait(lck);
        }
//        cout << "input ready cv in the loop; calling getInput()" << endl;
        input = streams->getInput();
        input_ready = false;
//        cout << "unlocking unique lock in the loop" << endl;
        lck.unlock();
//        cout << "retrieved '" << input << "' from " << streams << endl;
        actionCommand(input);
    }
}

void FastRLShell::actionCommand(string input) {
//    cout << "FastRLShell::actionCommand " << input << endl;
    unsigned long first_space = input.find(' ');
    string command_word = input;
    if (first_space != -1) {
        command_word = input.substr(0, first_space);
    }
//    cout << "command_word " << command_word << endl;
    ShellCommand * command = resolveCommand(command_word);
    if(command == nullptr) {
        streams->printOutput("Unknown command: " + command_word);
        return;
    }
    string arg_string;
    if ((first_space != -1) && (input.length() > first_space + 1)) {
        arg_string = input.substr(first_space + 1);
        // todo trim whitespace
    }
    streams->printOutput("command <" + command_word + "> arg <" + arg_string + ">");
    try {
        int status_code = command->call(this, arg_string, streams);
        if(status_code == -1){
            streams->printOutput(command->commandName() + " could not parse input args");
        }
        for(ShellObserver * observer : observers){
            observer->observeCommand(this, new ShellCommandEvent(input, command, status_code));
        }
    } catch (exception &e){
        streams->printOutput(string("Exception in command completion:\n") + string(e.what()));
    }
}


vector<ShellCommand *> FastRLShell::generateReserved(){
    vector<ShellCommand *> ret = vector<ShellCommand *>();
    auto * ac = new AliasCommand();
    auto * qc = new QuitCommand();
    auto * cc = new CommandsCommand();
    auto * asc = new AliasesCommand();
    auto * hc = new HelpCommand();
    ret.push_back(ac);
//    cout << "adding " << ac->commandName() << endl;
    ret.push_back(qc);
//    cout << "adding " << qc->commandName() << endl;
    ret.push_back(cc);
//    cout << "adding " << cc->commandName() << endl;
    ret.push_back(asc);
//    cout << "adding " << asc->commandName() << endl;
    ret.push_back(hc);
//    cout << "adding " << hc->commandName() << endl;
    return ret;
}

vector<ShellCommand *> FastRLShell::generateStandard(){
    return vector<ShellCommand *>();
}

Visualizer * FastRLShell::getVisualizer() {
    return visualizer;
}

void FastRLShell::setVisualizer(Visualizer * visualizer_) {
    visualizer = visualizer_;
}
