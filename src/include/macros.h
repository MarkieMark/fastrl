/*
 * Mark Benjamin 04 March 2019.
 * Copyright (c) 2019 Mark Benjamin
 */

#ifndef FASTRL_INCLUDE_MACROS_H
#define FASTRL_INCLUDE_MACROS_H

#define DEBUG_FLAG

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-macro-parentheses"

#ifdef DEBUG_FLAG
#define D(a) do {std::cout << __FILE__ << ":" << __FUNCTION__ << "@" << __LINE__ << ":" << a << std::endl;} while (0)
#define D_(a)  do {std::cout << a;} while (0)
#else
#define D(a)
#define D_(a)
#endif // DEBUG_FLAG

#pragma clang diagnostic pop

//#define FF string(__FILE__ + " " + __func__)

#endif //FASTRL_INCLUDE_MACROS_H
