/**
 * Mark Benjamin 31st May 2017
 */

#ifndef FASTRL_MDP_SINGLEAGENT_MODEL_TASK_FACTORED_MODEL_HPP
#define FASTRL_MDP_SINGLEAGENT_MODEL_TASK_FACTORED_MODEL_HPP

#include "sample_model.hpp"
#include "reward_function.hpp"
#include "../../core/terminal_function.hpp"

class TaskFactoredModel : virtual public SampleModel {
    virtual void useRewardFunction(RewardFunction * rf) { throw runtime_error("TaskFactoredModel::useRewardFunction() Not Implemented"); }
    virtual void useTerminalFunction(TerminalFunction * tf) { throw runtime_error("TaskFactoredModel::useTerminalFunction() Not Implemented"); }
    virtual RewardFunction * rewardFunction() { throw runtime_error("TaskFactoredModel::rewardFunction() Not Implemented"); }
    virtual TerminalFunction * terminalFunction() { throw runtime_error("TaskFactoredModel::terminalFunction() Not Implemented"); }
};

#endif // FASTRL_MDP_SINGLEAGENT_MODEL_TASK_FACTORED_MODEL_HPP