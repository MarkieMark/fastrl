/**
 * Mark Benjamin 1st June 2017
 */

#ifndef FASTRL_BEHAVIOR_POLICY_SUPPORT_ANNOTATED_ACTION_HPP
#define FASTRL_BEHAVIOR_POLICY_SUPPORT_ANNOTATED_ACTION_HPP

#include "../../../mdp/core/action/action.hpp"

class AnnotatedAction : public Action {
public:
    Action * srcAction;
    string annotation;
    explicit AnnotatedAction(Action *src_action = nullptr, string annotation_ = "") {
        srcAction = src_action;
        annotation = move(annotation_);
    }
    string actionName() override {
        return srcAction->actionName();
    }

    Action * makeCopy() override {
        return new AnnotatedAction(srcAction, annotation);
    }

    bool operator==(AnnotatedAction comp) {
        return (srcAction == comp.srcAction) && (annotation == comp.annotation);
    }

    string to_string() override {
        return "*" + annotation + "--" + srcAction->to_string();
    }
};

#endif // FASTRL_BEHAVIOR_POLICY_SUPPORT_ANNOTATED_ACTION_HPP