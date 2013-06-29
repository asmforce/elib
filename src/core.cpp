/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: elib core
**/

#include <iostream>
#include <elib/core.hpp>
#include <elib/chronos.hpp>
#include <elib/aliases.hpp>
using namespace elib::aliases;


void elib::core::diagnostic()
{
  if( sizeof(i8) != 1 )  std::cout << "\n!Failed:\n";
  std::cout << "sizeof(  i8 )\n\t\t" << (sizeof( i8)<<3) << '\n';

  if( sizeof(u8) != 1 )  std::cout << "\n!Failed:\n";
  std::cout << "sizeof(  u8 )\n\t\t" << (sizeof( u8)<<3) << '\n';

  if( sizeof(i16) != 2 )  std::cout << "\n!Failed:\n";
  std::cout << "sizeof( i16 )\n\t\t" << (sizeof(i16)<<3) << '\n';

  if( sizeof(u16) != 2 )  std::cout << "\n!Failed:\n";
  std::cout << "sizeof( u16 )\n\t\t" << (sizeof(u16)<<3) << '\n';

  if( sizeof(i32) != 4 )  std::cout << "\n!Failed:\n";
  std::cout << "sizeof( i32 )\n\t\t" << (sizeof(i32)<<3) << '\n';

  if( sizeof(u32) != 4 )  std::cout << "\n!Failed:\n";
  std::cout << "sizeof( u32 )\n\t\t" << (sizeof(u32)<<3) << '\n';

  if( sizeof(i64) != 8 )  std::cout << "\n!Failed:\n";
  std::cout << "sizeof( i64 )\n\t\t" << (sizeof(i64)<<3) << '\n';

  if( sizeof(u64) != 8 )  std::cout << "\n!Failed:\n";
  std::cout << "sizeof( u64 )\n\t\t" << (sizeof(u64)<<3) << '\n';

  char unsignedc = '\0';
  --unsignedc;
  if( unsignedc < '\0' )
  {
    std::cout << "\n!Failed:\n";
    std::cout << "char\n\t\tsigned\n";
  } else {
    std::cout << "char\n\t\tunsigned\n";
  };

  u64 time = elib::chronos::cputime();
  if( time == elib::chronos::cputime() )
  {
    std::cout << "\n!Failed:\n";
    std::cout << "Function must return value through eax:edx\n";
    std::cout << "Try to remove `#define ELIB_CHRONOS_CPUTIME_EAX_EDX` line in file <chronos.hpp>\n";
  } else {
    std::cout << "test elib::chronos::cputime() ok\n";
  };
};
