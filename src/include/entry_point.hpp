/*
 * Mark Benjamin 08 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_INCLUDE_ENTRY_POINT_HPP
#define FASTRL_INCLUDE_ENTRY_POINT_HPP

#include <stdexcept>

using namespace std;

/*
 * the pattern is to create a non-static main() method for classes that
 * contain/ed a main() method in the Java code; inheriting from this EntryPoint class
 * for the sake of polymorphism, adding Q_REGISTER_METATYPE() for reflection, registering
 * in include/main.cpp::main() with ENTRY(ClassName);
 */

class EntryPoint {
public:
    virtual int main(int argc, char * argv[]) {throw runtime_error("EntryPoint::main() Not Implemented");}
};

#endif //FASTRL_INCLUDE_ENTRY_POINT_HPP
