/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: options demo
**/

#include <elib/aliases.hpp>
#include <elib/options.hpp>
using namespace elib::aliases;

#include <iostream>










int main( int argc, char **argv )
{
  elib::options options( "--" );
  elib::options::variables vars;
  elib::options::values alones;

  options.add( "help", "print help message", false )
      .add( "1", "first argument", true )
      .add( "2", "second argument", true )
      .add( "3", "third argument", true )
      .add( "o", "output specified argument", true );

  bool success = options.parse( argc, argv, vars, alones );

  if( !success || !vars.size() )
  {
    std::cout << "Use '--help' for more information\n";
    return -1;
  };

  if( vars.count("help") )
  {
    std::cout << options;
    return 0;
  } else {
    if( vars.count("1") )
      std::cout << "1:" << vars["1"] << '\n';

    if( vars.count("2") )
      std::cout << "2:" << vars["2"] << '\n';

    if( vars.count("3") )
      std::cout << "3:" << vars["3"] << '\n';

    if( vars.count("o") )
    {
      if( vars.count(vars["o"]) )
      {
        std::cout << vars["o"] << ':' << vars[vars["o"]] << '\n';
      } else {
        std::cout << "Invaid output: `" << vars["o"] << "`\n";
        return -1;
      };
    };
  };
  return 0;
};
