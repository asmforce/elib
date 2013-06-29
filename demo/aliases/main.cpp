/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: aliases demo
**/

#include <elib/aliases.hpp>
using namespace elib::aliases;

#include <iostream>











int main( int argc, char **argv )
{
  for( u32 i0 = 0; i0 != 10; ++i0 )
  {
    for( u32 i1 = 0; i1 != 7; ++i1 )
      std::cout << '|';
    std::cout << '\n';
  };
  std::cout << '\n';

  return 0;
};
