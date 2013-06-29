/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: elib structs
**/

#ifndef ELIB_STRUCTS_HPP
#define ELIB_STRUCTS_HPP

#include <elib/aliases.hpp>
#pragma pack( push, 1 )

namespace elib
{
  namespace structs
  {
    template< typename aT, typename bT >
    struct duo  {
      duo( aT aV, bT bV )
        : a(aV), b(bV)  {}
    // public data-members
      aT a;
      bT b;
    };

    template< typename stateT >
    struct status  {
      status( bool successV, stateT stateV )
        : success(successV), state(stateV)  {}

      operator bool()  {
        return success;
      }
    // public data-members
      bool success;
      stateT state;
    };
  }; // namespace structs
}; // namespace elib

#pragma pack( pop )
#endif // ELIB_STRUCTS_HPP
