/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: syntax cclass
**/

#include <elib/aliases.hpp>
#include <elib/syntax/cclass.hpp>

#include <algorithm>
#include <string>

elib::syntax::cclass::cclass()
{
  std::fill( data, data + size, false );
};

elib::syntax::cclass::cclass( char c, bool state )
{
  std::fill( data, data + size, !state );
  set( c, state );
};

elib::syntax::cclass::cclass( char lower, char upper, bool state )
{
  std::fill( data, data + size, !state );
  set( lower, upper, state );
};

elib::syntax::cclass::cclass( const std::string &s, bool state )
{
  std::fill( data, data + size, !state );
  set( s, state );
};

elib::syntax::cclass::cclass( elib::syntax::cclass::predicate &pr, bool state )
{
  if( state )
  {
    for( u16 i = 0; i != size; ++i )
      data[i] = pr(i);
  } else {
    for( u16 i = 0; i != size; ++i )
      data[i] = !pr(i);
  };
};

elib::syntax::cclass::cclass( const cclass &rhs )
{
  std::copy( rhs.data, rhs.data + size, data );
};

elib::syntax::cclass &elib::syntax::cclass::set( const cclass &rhs )
{
  std::copy( rhs.data, rhs.data + size, data );
  return *this;
};

elib::syntax::cclass &elib::syntax::cclass::set( char c, bool state )
{
  data[c] = state;
  return *this;
};

elib::syntax::cclass &elib::syntax::cclass::set( char lower, char upper, bool state )
{
  if( lower < upper )
    std::fill( data + lower, data + upper + 1, state );
  else
    std::fill( data + upper, data + lower + 1, state );
  return *this;
};

elib::syntax::cclass &elib::syntax::cclass::set( const std::string &s, bool state )
{
  for( std::string::size_type i = 0; i != s.length(); ++i )
    data[s[i]] = state;
  return *this;
};

bool elib::syntax::cclass::test( char c ) const
{
  return data[c];
};

bool elib::syntax::cclass::test( char lower, char upper ) const
{
  if( lower > upper )
    std::swap( lower, upper );

  for( ; lower < upper; ++lower )
    if( !data[lower] )
      return false;
  return data[lower];
};

bool elib::syntax::cclass::test( const std::string &s ) const
{
  for( std::string::size_type i = 0; i != s.length(); ++i )
    if( !data[s[i]] )
      return false;
  return true;
};

elib::syntax::cclass &elib::syntax::cclass::flip()
{
  for( u16 i = 0; i != size; ++i )
    data[i] = !data[i];
  return *this;
};

bool elib::syntax::cclass::operator == ( const cclass &rhs )
{
  return std::equal( data, data + size, rhs.data );
};

elib::syntax::cclass &elib::syntax::cclass::operator = ( const cclass &rhs )
{
  std::copy( rhs.data, rhs.data + size, data );
  return *this;
};

elib::syntax::cclass &elib::syntax::cclass::operator |= ( const cclass &rhs )
{
  for( u16 i = 0; i != size; ++i )
    data[i] |= rhs.data[i];
  return *this;
};

elib::syntax::cclass &elib::syntax::cclass::operator &= ( const cclass &rhs )
{
  for( u16 i = 0; i != size; ++i )
    data[i] &= rhs.data[i];
  return *this;
};

elib::syntax::cclass &elib::syntax::cclass::operator ^= ( const cclass &rhs )
{
  for( u16 i = 0; i != size; ++i )
    data[i] ^= rhs.data[i];
  return *this;
};

elib::syntax::cclass elib::syntax::cclass::operator | ( const cclass &rhs ) const
{
  elib::syntax::cclass res( *this );
  res.operator |= ( rhs );
  return res;
};

elib::syntax::cclass elib::syntax::cclass::operator & ( const cclass &rhs ) const
{
  elib::syntax::cclass res( *this );
  res.operator &= ( rhs );
  return res;
};

elib::syntax::cclass elib::syntax::cclass::operator ^ ( const cclass &rhs ) const
{
  elib::syntax::cclass res( *this );
  res.operator ^= ( rhs );
  return res;
};
