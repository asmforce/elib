/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: syntax-core demo
**/

#include <iostream>

#include <elib/syntax/core.hpp>
#include <elib/syntax/cclass.hpp>
namespace syntax = elib::syntax;

#include <elib/aliases.hpp>
using namespace elib::aliases;



namespace cclass
{
  bool a( char c )  {
    return isalpha(c);
  };

  bool d( char c )  {
    return isdigit(c);
  };

  bool w( char c )  {
    return a(c) || d(c) || c == '-' || c == '_';
  };
};





bool exec( std::istream &stream )
{
  // <some-name,some-name2,some-name3:some-value,some-name4:some-vale2>
  syntax::cclass ccname(cclass::a), ccvalue(cclass::w);

  std::string name, value;
///  bool allowed; // value:(yes|no)
  char c;

  if( stream >> c && c == '<' )
  {
    while( syntax::skipspc(stream) && syntax::read(stream,ccname,name) )
    {
      if( stream >> c && c == ':' )
      {
        if( syntax::skipspc(stream) && syntax::read(stream,ccvalue,value) )
        {
          std::cout << name << ':' << value << '\n';
          if( stream >> c )  {
            if( c == ',' )  {
              continue;
            } else if( c == '>' )  {
              return true;
            };
          } else {
            return false;
          };
        } else {
          return false;
        };
      } else {
        return false;
      };
    };

    if( stream >> c && c == '>' )
      return true;
  };
  return false;
};




/**
// #include <sstream>
std::stringstream ss( "abcabcdabcdeabcdef" );
// abc abcd abcde abcdef

std::cout << syntax::find( ss, "abcde" ) << '\n';
std::cout << ss.tellg() << '\n';
**/


int main( int argc, char **argv )
{
  std::cout << "type> ";
  std::cout << (exec(std::cin) ? "[ ok ]\n" : "[ fail ]\n");
  return 0;
};
