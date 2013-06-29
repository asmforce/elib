/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: elib test framework
**/

#ifndef ELIB_ETEST_HPP
#define ELIB_ETEST_HPP

#include <elib/aliases.hpp>
#include <iostream>
#include <stdlib.h>

#define ETEST_REPORT_ERROR( MESSAGE )                          \
  std::cerr << '<' << __FILE__ << ">:"                         \
            << __LINE__ << '\n'                                \
            << (MESSAGE) << '\n';                              \
  for( ; ; );

#define ETEST_TRUE( ACTUAL )                                   \
  {                                                            \
    if( (ACTUAL) != true )                                     \
     ETEST_REPORT_ERROR("elib::etest: [true failed]");         \
  }

#define ETEST_FALSE( ACTUAL )                                  \
  {                                                            \
    if( (ACTUAL) != false )                                    \
     ETEST_REPORT_ERROR("elib::etest: [false failed]");        \
  }

#define ETEST_EQUAL( ACTUAL, NEED )                            \
  {                                                            \
    if( (ACTUAL) != (NEED) )                                   \
     ETEST_REPORT_ERROR("elib::etest: [eq failed]");           \
  }

#define ETEST_DIFFERENT( ACTUAL, NOT_NEED )                    \
  {                                                            \
    if( (ACTUAL) == (NOT_NEED) )                               \
     ETEST_REPORT_ERROR("elib::etest: [different failed]");    \
  }

#define ETEST_GREATER( ACTUAL, MUST_BE_LESS )                  \
  {                                                            \
    if( (ACTUAL) <= (MUST_BE_LESS) )                           \
     ETEST_REPORT_ERROR("elib::etest: [greater failed]");      \
  }

#define ETEST_LESS( ACTUAL, MUST_BE_GREATER )                  \
  {                                                            \
    if( (ACTUAL) >= (MUST_BE_GREATER) )                        \
     ETEST_REPORT_ERROR("elib::etest: [less failed]");         \
  }

#endif // ELIB_ETEST_HPP
