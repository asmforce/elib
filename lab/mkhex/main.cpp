#include <iostream>
#include <string.h>

namespace elib
{
  namespace data
  {
    char *mkhex( const void *data, unsigned long size );
    char *mkhex( const char *cs );
  };
};



char *elib::data::mkhex( const void *data, unsigned long size )
{
  char *res = new char[(size << 1) + 1];
  __asm__
  (
    "1:                    ;"
    "  test %%ecx, %%ecx   ;"
    "  jz 2f               ;"
    "  dec %%ecx           ;"
    "  lodsb               ;"
    "  mov %%al, %%ah      ;"
    "  mov %%al, %%bl      ;"
    "  and $0xF, %%ebx     ;"
    "  add %%edx, %%ebx    ;"
    "  mov (%%ebx), %%al   ;"
    "  mov %%ah, %%bl      ;"
    "  shr $4, %%bl        ;"
    "  and $0xF, %%ebx     ;"
    "  add %%edx, %%ebx    ;"
    "  mov (%%ebx), %%ah   ;"
    "  stosw               ;"
    "  jmp 1b              ;"
    "2:                    ;"
    "  xor %%al, %%al      ;"
    "  stosb               ;"
    :
    : "S" (data),
      "D" (res),
      "c" (size),
      "d" ("0123456789ABCDEF")
  );
  return res;
};

char *elib::data::mkhex( const char *cs )  {
  return mkhex( (const void*) cs, strlen(cs) );
};








int main( int argc, char **argv )
{
  std::cout << elib::data::mkhex("Hello, World") << '\n';
  return 0;
};
