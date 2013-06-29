/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: chronos benchmark
**/

#ifndef ELIB_CHRONOS_HPP
#define ELIB_CHRONOS_HPP

#include <elib/aliases.hpp>
//#define ELIB_CHRONOS_CPUTIME_EAX_EDX

#define ELIB_CHRONOS_CREATE( NAME ) \
  u64 NAME = elib::chronos::cputime();

#define ELIB_CHRONOS_LOOP( COUNTER_NAME, LOOPS ) \
  for( u64 COUNTER_NAME = LOOPS; COUNTER_NAME; --COUNTER_NAME )

#define ELIB_CHRONOS_REPORT( NAME )                                                  \
  std::cout << "elib.chronos.time:" << (elib::chronos::cputime()-(NAME)) << std::endl; \
  NAME = elib::chronos::cputime();

namespace elib
{
  namespace chronos
  {
    typedef void function( u64 i );

    // Warning: `cputime` can not be inline
    static u64 cputime()
    {
#ifdef ELIB_CHRONOS_CPUTIME_EAX_EDX
      GASM( "RDTSC" );
      // GASM( ".byte 0x0F, 0x31" );
      // No return statement because `RDTSC` do it iself
      // through eax:edx registers
#else
      union  {
        u64 eaxedx;
        struct { u32 eax, edx; };
      } res;

      GASM  ( "RDTSC" : "=a" (res.eax), "=d" (res.edx) );
      // GASM  ( ".byte 0x0F, 0x31" : "=a" (res.eax), "=d" (res.edx) );
      return res.eaxedx;
#endif
    };

    static u64 calculate( function &func, u64 loops )
    {
      u64 time = cputime();
      for( u64 i = 0; i != loops; ++i )
        func( i );
      return (cputime() - time);
    };
  }; // namespace chronos
}; // namespace elib

#endif // ELIB_CHRONOS_HPP
