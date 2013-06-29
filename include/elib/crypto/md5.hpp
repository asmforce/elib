/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: md5 implementation
**/

#ifndef ELIB_CRYPTO_MD5_HPP
#define ELIB_CRYPTO_MD5_HPP

#include <elib/aliases.hpp>
#include <string>

namespace elib
{
  namespace crypto
  {
    class SHARED md5
    {
    private:
      enum { BlockSize = 64, TotalSizeSize = 8 };

    public:
      md5();
      void accumulate( const char *data );
      void accumulate( const u8 *data, u32 size );
      void reset();

      void get( u8 hash[16] );
      std::string get();

    private:
      void transform( const u8 *data );

    private:
      u32 state[4];
      u64 totalsize;
      u32 endsize;
      u8 end[BlockSize];
    }; // class md5
  }; // namespace crypto
}; // namespace elib

#endif // ELIB_CRYPTO_MD5_HPP
