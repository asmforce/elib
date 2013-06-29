/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: syntax cclass
**/

#ifndef ELIB_SYNTAX_CCLASS_HPP
#define ELIB_SYNTAX_CCLASS_HPP

#include <elib/aliases.hpp>
#include <string>

namespace elib
{
  namespace syntax
  {
    class SHARED cclass
    {
    public:
      typedef bool (predicate)( char );
      enum { size = 256 };

    public:
      cclass();
      explicit cclass( char c, bool state = true );
      explicit cclass( char lower, char upper, bool state = true );
      explicit cclass( const std::string &s, bool state = true );
      explicit cclass( predicate &pr, bool state = true );
      cclass( const cclass &rhs );

      cclass &set( const cclass &rhs );
      cclass &set( char c, bool state = true );
      cclass &set( char lower, char upper, bool state = true );
      cclass &set( const std::string &s, bool state = true );

      bool test( char c ) const;
      bool test( char lower, char upper ) const;
      bool test( const std::string &s ) const;

      cclass &flip();

      bool operator == ( const cclass &rhs );
      cclass &operator = ( const cclass &rhs );

      cclass &operator |= ( const cclass &rhs );
      cclass &operator &= ( const cclass &rhs );
      cclass &operator ^= ( const cclass &rhs );

      cclass operator | ( const cclass &rhs ) const;
      cclass operator & ( const cclass &rhs ) const;
      cclass operator ^ ( const cclass &rhs ) const;

    private:
      bool data[size];
    }; // class cclass
  }; // namespace syntax
}; // namespace elib

#endif // ELIB_SYNTAX_CCLASS_HPP
