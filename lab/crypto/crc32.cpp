#include <iostream>
#include <elib/aliases.hpp>
using namespace elib::aliases;








// name: crc32
// polynome: 0x04C11DB7    x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 
//                     + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
// test: "123456789" -> 0xCBF43926

namespace elib
{
  namespace crypto
  {
    namespace aux
    {
      static u32 crc32table[256];

      // crc32 table initialization
      void crc32init()  {
        static bool called = false;
        if( called )
          return;
        called = true;
        u32 crc;
 
        for ( u16 i = 0; i < 256; i++ )
        {
          crc = i;
          for (u16 j = 0; j < 8; j++)
            crc = (crc & 1) ? (crc >> 1) ^ 0xEDB88320uL : (crc >> 1);
 
          crc32table[i] = crc;
        };
      }; // void crc32init
    }; // namespace aux

    u32 crc32( u8 *data, u32 size )
    {
      u32 crc = 0xFFFFFFFFuL;
      aux::crc32init();
 
      while( size-- )
        crc = aux::crc32table[(crc ^ *data++) & 0xFF] ^ (crc >> 8);
 
      return ~crc;
    }; // u32 crc32
  }; // namespace crypto
}; // namespace elib






int main( int argc, char **argv )
{
  std::cout << std::hex << elib::crypto::crc32((u8*)"123456789", 9) << '\n';
  std::cout << 0xCBF43926uL << '\n';
  std::cin.get();
  return 0;
};
