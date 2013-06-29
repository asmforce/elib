/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: chronos demo
**/

#include <iostream>

#include <elib/chronos.hpp>
#include <elib/aliases.hpp>
using namespace elib::aliases;




static long  ia = 1050L, ib = 2060L, ic = 3070L, id = 4080L;
static float fa = 1050.F, fb = 2060.F, fc = 3070.F, fd = 4080.F;

void test1( u64 i )
{
  ia += ib * ic * id * (ib + ic + id);
/**
  GVASM(
  "mov %2, %%eax         ;"
  "add %3, %%eax         ;"
  "add %4, %%eax         ;"
  "imul %2, %%eax        ;"
  "imul %3, %%eax        ;"
  "imul %4, %%eax        ;"
  "add %1, %%eax         ;"
  "mov %%eax, %0"
  : "=m"(ia)
  : "m"(ia), "m"(ib), "m"(ic), "m"(id)
  );
**/
/**
  int a = 12346, b = 15346;
  int tmp = a;
  a = b;
  b = tmp;
**/
};

void test2( u64 i )
{
  fa += fb * fc * fd * (fb + fc + fd);
/**
  GVASM(
  "flds %2                ;"
  "flds %3                ;"
  "fmulp %%st,%%st(1)     ;"
  "flds %4                ;"
  "fmulp %%st,%%st(1)     ;"
  "flds %2                ;"
  "flds %3                ;"
  "faddp %%st,%%st(1)     ;"
  "flds %4                ;"
  "faddp %%st,%%st(1)     ;"
  "fmulp %%st,%%st(1)     ;"
  "flds %1                ;"
  "faddp %%st,%%st(1)     ;"
  "fstps %0"
  : "=m"(fa)
  : "m"(fa), "m"(fb), "m"(fc), "m"(fd)
  );
**/
/**
  int a = 12346, b = 15346;
  a += b;
  b = a - b;
  a -= b;
**/
};



int main( int argc, char **argv )
{
  namespace chronos = elib::chronos;

  // Function form
  std::cout << "test1:" << chronos::calculate( test1, 100000000 ) << '\n';
  std::cout << "test1:" << chronos::calculate( test1, 100000000 ) << '\n';
  std::cout << "test1:" << chronos::calculate( test1, 100000000 ) << '\n';
  std::cout << "test1:" << chronos::calculate( test1, 100000000 ) << '\n';

  std::cout << "test2:" << chronos::calculate( test2, 100000000 ) << '\n';
  std::cout << "test2:" << chronos::calculate( test2, 100000000 ) << '\n';
  std::cout << "test2:" << chronos::calculate( test2, 100000000 ) << '\n';
  std::cout << "test2:" << chronos::calculate( test2, 100000000 ) << '\n';


  // Macro form
  ELIB_CHRONOS_CREATE( elibChronosBenchmarkTime );

  ELIB_CHRONOS_LOOP( elibChronosBenchmarkStage, 100000000 )
    test1( elibChronosBenchmarkStage );
  ELIB_CHRONOS_REPORT( elibChronosBenchmarkTime );

  ELIB_CHRONOS_LOOP( elibChronosBenchmarkStage, 100000000 )
    test2( elibChronosBenchmarkStage );
  ELIB_CHRONOS_REPORT( elibChronosBenchmarkTime );

  return 0;
};
