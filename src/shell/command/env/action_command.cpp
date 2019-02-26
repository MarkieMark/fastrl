/**
 * Mark Benjamin 18th January 2019
 */

#ifndef FASTRL_SHELL_COMMAND_ENV_EXECUTE_ACTION_COMMAND_HPP
#define FASTRL_SHELL_COMMAND_ENV_EXECUTE_ACTION_COMMAND_HPP

#include "action_command.h"

int ActionCommand::call(FastRLShell * shell, string argString, StreamWrapper * s) {
//    return 0;
    Environment * env = (dynamic_cast<EnvironmentShell *>(shell))->getEnv(); // todo shell has observers, env does not
    ShellOptParser sp = ShellOptParser(argString);

    if ((sp.isOpt("h")) || (sp.isOpt("-h"))) {
        s->printOutput("[v|a] args*\nCommand to execute an action or set an action name alias.\n"
                   "If -a is not specified, then executes the action with name args[0] with parameters args[1]*\n"
                   "-v: the resulting reward, termination, and observation from execution is printed.\n"
                   "-a: assigns an action name alias where args[0] is the original action name, and args[1] is the alias.");
        return 0;
    }

    if ((sp.isOpt("a")) || (sp.isOpt("-a"))) {
        vector<string> the_vec;
        vector<string> vec_temp = sp.getOpt("-a", 2);
        if (vec_temp.size() == 2) {
            the_vec = vec_temp;
        } else {
            the_vec = sp.getOpt("a", 2);
        }
        if (the_vec.size() != 2) {
            return  -1;
        }
        action_name_map.insert(pair<string, string>(the_vec[1], the_vec[0]));
        return 0;
    }

    if (sp.tokens.empty()) {
        return -1;
    }

    string action = sp.tokens[0];
    auto * sa_domain = dynamic_cast<SADomain *>(domain);
    ActionType * action_type = sa_domain->getAction(action);
    if(action_type == nullptr) {
        auto action_it = action_name_map.find(action);
        if (action_it != action_name_map.end()) {
            string action_name = action_it->second;
            action_type = sa_domain->getAction(action_name);
        }
    }
    if(action_type != nullptr){
        vector<string> non_opt_args = sp.nonOptArgs();
        string non_option_args;
        for (const string &arg : non_opt_args) {
            if (arg != *(non_opt_args.begin())) {
                non_option_args += " ";
            }
            non_option_args += arg;
        }
        cout << "non_option_args <" << non_option_args << ">" << endl;
        Action * a = action_type->associatedAction(non_option_args);
        EnvironmentOutcome * o = env->act(a);
        if (sp.isOpt("-v")) {
            ostringstream os;
            os << "reward: " << o->reward;
            s->printOutput(os.str());
            if (o->done) {
                s->printOutput("IS terminal");
            }
            else{
                s->printOutput("is NOT terminal");
            }
            os << o->o_prime->to_string();
            s->printOutput(os.str());
        }
        return 1;
    }
    return -1;
};

#endif // FASTRL_SHELL_COMMAND_ENV_EXECUTE_ACTION_COMMAND_HPP
