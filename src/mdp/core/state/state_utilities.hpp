//
// Mark Benjamin 24th January 2019.
// Copyright (c) 2019 Mark Benjamin
//

#ifndef FASTRL_MDP_CORE_STATE_STATE_UTILITIES_HPP
#define FASTRL_MDP_CORE_STATE_STATE_UTILITIES_HPP

#include "state.hpp"

class StateUtilities {
public:
    StateUtilities() = default;

    /**
     * Takes an input object, typically value to which a variable should be set, that is either a String representation of a number, or a
     * {@link Number}, and returns the corresponding {@link Number}. If the input is not a number or string
     * representation of a number, a runtime exception is thrown.
     * @param o the input object that is either a {@link String} or a {@link Number}
     * @return the corresponding {@link Number}.
     */
//    static Number stringOrNumber(Object o){
//        if(o instanceof Number){
//            return (Number)o;
//        }
//        else if(o instanceof String){
//            Double d = Double.parseDouble((String)o);
//            return d;
//        }
//        throw new RuntimeException("Value is neither a Number nor a String.");
//    }

    /**
     * Takes an input object, typically value to which a variable should be set, that is either a String representation of a boolean, or a
     * {@link Boolean}, and returns the corresponding {@link Boolean}. If the input is not a boolean or string
     * representation of a boolean, a runtime exception is thrown.
     * @param o the input object that is either a {@link String} or a {@link Boolean}
     * @return the corresponding {@link Boolean}.
     */
//     static bool stringOrBoolean(Object o){
//        if(o instanceof Boolean){
//            return (Boolean)o;
//        }
//        else if(o instanceof String){
//            return Boolean.parseBoolean((String)o);
//        }
//        throw new RuntimeException("Value is neither a Boolean nor a String.");
//    }


    /**
     * A standard method for turning an arbitrary {@link State} into a {@link String} representation. Often used
     * for the {@link Object#to_string()} implementation of a {@link State}.
     * @param s the input {@link State}
     * @return the {@link String} representation.
     */
    static string stateToString(State * s){
        stringstream buf;
        buf << "{\n";
        vector<KeyContainer *> keys = s->variableKeys();
        for(KeyContainer * key : keys){
            buf << key->to_string() << ": {" << s->getIntValue(key) << "}\n";
        }
        buf << "}";
        return buf.str();
    }
};


#endif //FASTRL_MDP_CORE_STATE_STATE_UTILITIES_HPP
