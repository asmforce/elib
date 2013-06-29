/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: types aliases
**/

#ifndef ELIB_ALIASES_HPP
#define ELIB_ALIASES_HPP

// Elib version 1.0.0.0
#define ELIB_VERSION 1000

// C-style name mangling
#define CMANGLE extern "C"

#define IMPORT __declspec(dllimport)
#define EXPORT __declspec(dllexport)

#if defined(ELIB_BUILD)
#define SHARED EXPORT
#else
#define SHARED IMPORT
#endif

#define INLINE __attribute__((__always_inline__))
#define GASM __asm__
#define GVASM __asm__ __volatile__

// #define ELIB( SUFFIX ) ELIB_##SUFFIX

namespace elib
{
  namespace aliases
  {
    // CHARACTER TYPES:
    typedef unsigned char      ch1;
    typedef unsigned short     ch2;
    typedef unsigned long      ch4;

    // SIGNED INTEGER TYPES:
    typedef signed char        i8;
    typedef signed short       i16;
    typedef signed long        i32;
    typedef signed long long   i64;

    // UNSIGNED INTEGER TYPES:
    typedef unsigned char      u8;
    typedef unsigned short     u16;
    typedef unsigned long      u32;
    typedef unsigned long long u64;

    // FLOATING POINT TYPES:
    typedef long double        xdouble;
  }; // namespace aliases

  using namespace aliases;
}; // namespace elib

#endif // ELIB_ALIASES_HPP
