#include <iostream>

/**
struct i128
{
  unsigned a: 32;
  unsigned b: 32;
  unsigned c: 32;
  unsigned d: 32;
};
**/

#pragma pack( push, 1 )
struct u128
{
public:
  u128( int v ) : a(v), b(0UL), c(0UL), d(0UL)  {};
  u128( unsigned long v ) : a(v), b(0UL), c(0UL), d(0UL)  {};
  //u128( const u128 &x ) : a(x.a), b(x.b), c(x.c), d(x.d) {};

public:
  unsigned long a;
  unsigned long b;
  unsigned long c;
  unsigned long d;
};
#pragma pack( pop )


std::ostream &operator << ( std::ostream &stream, u128 &x )
{
  const char hex[] = "0123456789ABCDEF";
  unsigned char *p = (unsigned char*) &x;
  for( unsigned long i = 0UL; i != 16UL; ++i, ++p )
    stream << hex[*p & 0x0F] << hex[*p >> 4];
  return stream;
};

void inc( u128 *x )
{
  __asm__
  (
    "addl $1, (%%eax)           ;"
    "adcl $0, 4(%%eax)          ;"
    "adcl $0, 8(%%eax)          ;"
    "adcl $0, 12(%%eax)         ;"
    :
    : "a" (x)
  );
};

void dec( u128 *x )
{
  __asm__
  (
    "subl $1, (%%eax)           ;"
    "sbbl $0, 4(%%eax)          ;"
    "sbbl $0, 8(%%eax)          ;"
    "sbbl $0, 12(%%eax)         ;"
    :
    : "a" (x)
  );
};

void add( u128 *x, const u128 *y )
{
  __asm__
  (
    "movl (%%ebx), %%edx        ;"
    "addl %%edx, (%%eax)        ;"
    "movl 4(%%ebx), %%edx       ;"
    "adcl %%edx, 4(%%eax)       ;"
    "movl 8(%%ebx), %%edx       ;"
    "adcl %%edx, 8(%%eax)       ;"
    "movl 12(%%ebx), %%edx      ;"
    "adcl %%edx, 12(%%eax)      ;"
    :
    : "a" (x), "b" (y)
  );
};

void sub( u128 *x, const u128 *y )
{
  __asm__
  (
    "movl (%%ebx), %%edx        ;"
    "subl %%edx, (%%eax)        ;"
    "movl 4(%%ebx), %%edx       ;"
    "sbbl %%edx, 4(%%eax)       ;"
    "movl 8(%%ebx), %%edx       ;"
    "sbbl %%edx, 8(%%eax)       ;"
    "movl 12(%%ebx), %%edx      ;"
    "sbbl %%edx, 12(%%eax)      ;"
    :
    : "a" (x), "b" (y)
  );
};











int main( int argc, char **argv )
{
  u128 x0( 0 ), x1( ~0UL );
  std::cout << x0 << " + " << x1 << ": ";
  add( &x0, &x1 );
  std::cout << x0 << '\n';
  std::cout << x0 << " + " << x1 << ": ";
  add( &x0, &x1 );
  std::cout << x0 << '\n';
  std::cout << x0 << " + " << x1 << ": ";
  add( &x0, &x1 );
  std::cout << x0 << '\n';
  std::cout << x0 << " + " << x1 << ": ";
  add( &x0, &x1 );
  std::cout << x0 << '\n';
  std::cout << x0 << " + " << x1 << ": ";
  add( &x0, &x1 );
  std::cout << x0 << '\n';
  return 0;
};
