/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: syntax core
**/

#include <elib/aliases.hpp>
#include <elib/syntax/core.hpp>
#include <elib/syntax/cclass.hpp>
using namespace elib::aliases;

#include <istream>
#include <string>
#include <ctype.h>

void elib::syntax::back( std::istream &stream, const std::string &cs )
{
  for( std::string::size_type i = cs.length(); i--; )
    stream.putback( cs[i] );
};

bool elib::syntax::skipspc( std::istream &stream )
{
  return stream >> std::ws;
};

bool elib::syntax::skipspc( std::istream &stream, std::string &cs )
{
  char tmp;
  cs.clear();
  while( stream.get(tmp) )
  {
    if( isspace(tmp) )
    {
      cs += tmp;
    } else {
      stream.unget();
      return true;
    };
  };
  return false;
};

bool elib::syntax::skip( std::istream &stream, const elib::syntax::cclass &cc )
{
  char tmp;
  while( stream.get(tmp) )
  {
    if( !cc.test(tmp) )
    {
      stream.unget();
      return true;
    };
  };
  return false;
};

bool elib::syntax::skip( std::istream &stream, const elib::syntax::cclass &cc, std::string &cs )
{
  char tmp;
  cs.clear();
  while( stream.get(tmp) )
  {
    if( cc.test(tmp) )
    {
      cs += tmp;
    } else {
      stream.unget();
      return true;
    };
  };
  return false;
};

bool elib::syntax::find( std::istream &stream, char target )
{
  char tmp;
  while( stream.get(tmp) )
  {
    if( tmp == target )
      return true;
  };
  return false;
};

bool elib::syntax::find( std::istream &stream, char target, std::string &cs )
{
  char tmp;
  cs.clear();
  while( stream.get(tmp) )
  {
    if( tmp == target )
      return true;
    cs += tmp;
  };
  return false;
};

bool elib::syntax::find( std::istream &stream, const std::string &target )
{
  std::string cs;
  std::string::size_type n = target.length(), i = 0;
  char tmp;

  if( !n )  return false;

  while( i != n )
  {
    if( stream.get(tmp) )
      cs += tmp;
    else
      return false;
    ++i;
  };

  i = 0;
  while( cs.compare(i,n,target) )
  {
    if( stream.get(tmp) )
    {
      cs += tmp;
      ++i;
      // Следующий блок необходим для экономии памяти,
      // иначе, при обработке потока, строка `cs` может
      // заметно увеличиться.
      if( i == 128 )
      {
        cs.erase( 0, i );
        i = 0;
      };
    } else {
      return false;
    };
  };
  return true;
};

bool elib::syntax::find( std::istream &stream, const std::string &target, std::string &cs )
{
  std::string::size_type n = target.length(), i = 0;
  char tmp;

  cs.clear();
  if( !n )  return false;

  while( i != n )
  {
    if( stream.get(tmp) )
      cs += tmp;
    else
      return false;
    ++i;
  };

  i = 0;
  while( cs.compare(i,n,target) )
  {
    if( stream.get(tmp) )
    {
      cs += tmp;
      ++i;
    } else {
      return false;
    };
  };

  cs.erase( i, n );
  return true;
};

bool elib::syntax::find( std::istream &stream, const elib::syntax::cclass &cc )
{
  char tmp;
  while( stream.get(tmp) )
  {
    if( cc.test(tmp) )
    {
      stream.unget();
      return true;
    };
  };
  return false;
};

bool elib::syntax::find( std::istream &stream, const elib::syntax::cclass &cc, std::string &cs )
{
  char tmp;
  cs.clear();
  while( stream.get(tmp) )
  {
    if( cc.test(tmp) )
    {
      stream.unget();
      return true;
    } else {
      cs += tmp;
    };
  };
  return false;
};

bool elib::syntax::match( std::istream &stream, char target )
{
  char tmp;

  if( stream.get(tmp) )
  {
    if( tmp == target )
      return true;
    stream.unget();
  };
  return false;
};

bool elib::syntax::match( std::istream &stream, const std::string &target )
{
  std::string::size_type n = target.length(), i = 0;
  std::string cs;
  char tmp;

  if( !n )
    return false;

  while( stream.get(tmp) )
  {
    cs += tmp;
    if( target[i] != tmp )
      break;
    ++i;
    if( i == n )
      return true;
  };

  back( stream, cs );
  return false;
};

bool elib::syntax::match( std::istream &stream, const elib::syntax::cclass &cc )
{
  char tmp;

  if( stream.get(tmp) )
  {
    stream.unget();
    if( cc.test(tmp) )
      return true;
  };

  return false;
};

bool elib::syntax::read( std::istream &stream, const elib::syntax::cclass &cc, std::string &cs )
{
  char tmp;

  cs.clear();
  while( stream.get(tmp) )
  {
    if( cc.test(tmp) )
    {
      cs += tmp;
    } else {
      stream.unget();
      return cs.length();
    };
  };
  return false;
};
