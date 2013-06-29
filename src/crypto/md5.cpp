/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: md5 implementation
**/

#include <elib/aliases.hpp>
using namespace elib::aliases;

#include <string.h>
#include <string>

#include <elib/crypto/md5.hpp>
#define ELIB_CRYPTO_MD5_ASM_TRANSFORM

#ifdef ELIB_CRYPTO_MD5_ASM_TRANSFORM
#define MD5_TRANSFORM1( w, x, y, z, data, datai, ti, s )   \
  __asm__                                                  \
  (                                                        \
      "movl %%ebx, %%edi            ;"                     \
      "andl %%ecx, %%edi            ;"                     \
      "pushl %%ebx                  ;"                     \
      "notl %%ebx                   ;"                     \
      "andl %%edx, %%ebx            ;"                     \
      "orl %%ebx, %%edi             ;"                     \
      "popl %%ebx                   ;"                     \
      "add %%eax, %%edi             ;"                     \
      "add " #datai "(%%esi), %%edi ;"                     \
      "add $" #ti ", %%edi          ;"                     \
      "rol $" #s ", %%edi           ;"                     \
      "add %%ebx, %%edi             ;"                     \
      : "=D" (w)                                           \
      : "a" (w), "b" (x), "c" (y), "d" (z), "S" (data)     \
  );

#define MD5_TRANSFORM2( w, x, y, z, data, datai, ti, s )   \
  __asm__                                                  \
  (                                                        \
      "movl %%ebx, %%edi            ;"                     \
      "andl %%edx, %%edi            ;"                     \
      "notl %%edx                   ;"                     \
      "andl %%ecx, %%edx            ;"                     \
      "orl %%edx, %%edi             ;"                     \
      "add %%eax, %%edi             ;"                     \
      "add " #datai "(%%esi), %%edi ;"                     \
      "add $" #ti ", %%edi          ;"                     \
      "rol $" #s ", %%edi           ;"                     \
      "add %%ebx, %%edi             ;"                     \
      : "=D" (w)                                           \
      : "a" (w), "b" (x), "c" (y), "d" (z), "S" (data)     \
  );

#define MD5_TRANSFORM3( w, x, y, z, data, datai, ti, s )   \
  __asm__                                                  \
  (                                                        \
      "movl %%ebx, %%edi            ;"                     \
      "xorl %%ecx, %%edi            ;"                     \
      "xorl %%edx, %%edi            ;"                     \
      "add %%eax, %%edi             ;"                     \
      "add " #datai "(%%esi), %%edi ;"                     \
      "add $" #ti ", %%edi          ;"                     \
      "rol $" #s ", %%edi           ;"                     \
      "add %%ebx, %%edi             ;"                     \
      : "=D" (w)                                           \
      : "a" (w), "b" (x), "c" (y), "d" (z), "S" (data)     \
  );

#define MD5_TRANSFORM4( w, x, y, z, data, datai, ti, s )   \
  __asm__                                                  \
  (                                                        \
      "notl %%edx                   ;"                     \
      "orl %%ebx, %%edx             ;"                     \
      "xorl %%ecx, %%edx            ;"                     \
      "movl %%edx, %%edi            ;"                     \
      "add %%eax, %%edi             ;"                     \
      "add " #datai "(%%esi), %%edi ;"                     \
      "add $" #ti ", %%edi          ;"                     \
      "rol $" #s ", %%edi           ;"                     \
      "add %%ebx, %%edi             ;"                     \
      : "=D" (w)                                           \
      : "a" (w), "b" (x), "c" (y), "d" (z), "S" (data)     \
  );

#else

#define MD5_TR1( x, y, z ) ((x & y) | (~x & z))
#define MD5_TR2( x, y, z ) ((x & z) | (y & ~z))
#define MD5_TR3( x, y, z ) (x ^ y ^ z)
#define MD5_TR4( x, y, z ) (y ^ (x | ~z))

#define ROL( x, n )  ((x << n) | (x >> (32 - n)))

#define MD5_TRANSFORM( tmp, tr, data, ti, s, w, x, y, z ) \
  tmp = w + tr(x,y,z) + data + ti;                        \
  w = x + ROL( tmp, s );
#endif

elib::crypto::md5::md5()
{
  reset();
};

void elib::crypto::md5::accumulate( const char *data )
{
  accumulate( (const u8*) data, strlen(data) );
};

void elib::crypto::md5::accumulate( const u8 *data, u32 size )
{
  totalsize += size;

  // Если в `end` что-то оставили в прошлый раз,
  // дополняем тот блок из `data`
  if( endsize )
  {
    // BlockSize-endsize -> не хватает для заполнения блока в `end`
    // Новопоступивших данных может не хватить для заполнения `end`
    u32 n = std::min( BlockSize-endsize, size );
    // Дописываем из `data` в `end`
    memcpy( end + endsize, data, n );
    size -= n;
    data += n;
    endsize += n;
    // Если блок `end` заполнен
    if( endsize == BlockSize )
    {
      transform( end );
      endsize = 0;
    } else {
      // Если данных не хватило, чтобы заполнить `end`
      // значит дальше нет смысла идти
      return;
    };
  };

  // Все целые блоки обрабатываем сразу
  while( size >= BlockSize )
  {
    transform( data );
    size -= BlockSize;
    data += BlockSize;
  };

  // Если size != 0, значит `end` пуст
  if( size )
  {
    // Остальное сохраняем в `end`
    memcpy( end, data, size );
    endsize = size;
  };
};

void elib::crypto::md5::reset()
{
  state[0] = 0x67452301;
  state[1] = 0xEFCDAB89;
  state[2] = 0x98BADCFE;
  state[3] = 0x10325476;
  totalsize = 0;
  endsize = 0;
};

void elib::crypto::md5::get( u8 hash[16] )
{
  // В `totalsize` число байт во входящем сообщении
  // Переводим в количество битов
  totalsize <<= 3;

  // Первый выравнивающий байт - 0x80
  // Это безопасно, потому что в `end` всегда остаётся хотя бы один байт
  // В функции `accumulate` необходимо не допустить endsize == BlockSize
  end[endsize] = 0x80;
  endsize++;
  if( (BlockSize - endsize) < TotalSizeSize )
  {
    // В оставшемся блоке не хватает места,
    // для поля `длины сообщения`
    // Заполняем нулями для выравнивания
    memset( end + endsize, 0, BlockSize - endsize );
    transform( end );
    // Заполняем нулями для выравнивания
    memset( end, 0, BlockSize - TotalSizeSize );
  } else {
    // Заполняем нулями для выравнивания
    memset( end + endsize, 0, BlockSize - endsize );
  };
  // Добавляем `длину сообщения в конец`
  memcpy( end + BlockSize - TotalSizeSize, &totalsize, TotalSizeSize );
  transform( end );
  memcpy( hash, state, 16 );
  reset();
};

std::string elib::crypto::md5::get()
{
  const char hex[] = "0123456789abcdef";
  std::string res;
  u8 hash[16];

  get( hash );
  for( u32 i = 0; i != 16; ++i )
  {
    res += hex[ hash[i] >> 4 ];
    res += hex[ hash[i] & 0x0F ];
  };

  return res;
};

//#include <iostream>
void elib::crypto::md5::transform( const u8 *data )
{
  u32 a = state[0];
  u32 b = state[1];
  u32 c = state[2];
  u32 d = state[3];

#ifdef ELIB_CRYPTO_MD5_ASM_TRANSFORM
  MD5_TRANSFORM1( a, b, c, d, data,  0, 0xD76AA478,  7 );
  MD5_TRANSFORM1( d, a, b, c, data,  4, 0xE8C7B756, 12 );
  MD5_TRANSFORM1( c, d, a, b, data,  8, 0x242070DB, 17 );
  MD5_TRANSFORM1( b, c, d, a, data, 12, 0xC1BDCEEE, 22 );
  MD5_TRANSFORM1( a, b, c, d, data, 16, 0xF57C0FAF,  7 );
  MD5_TRANSFORM1( d, a, b, c, data, 20, 0x4787C62A, 12 );
  MD5_TRANSFORM1( c, d, a, b, data, 24, 0xA8304613, 17 );
  MD5_TRANSFORM1( b, c, d, a, data, 28, 0xFD469501, 22 );
  MD5_TRANSFORM1( a, b, c, d, data, 32, 0x698098D8,  7 );
  MD5_TRANSFORM1( d, a, b, c, data, 36, 0x8B44F7AF, 12 );
  MD5_TRANSFORM1( c, d, a, b, data, 40, 0xFFFF5BB1, 17 );
  MD5_TRANSFORM1( b, c, d, a, data, 44, 0x895CD7BE, 22 );
  MD5_TRANSFORM1( a, b, c, d, data, 48, 0x6B901122,  7 );
  MD5_TRANSFORM1( d, a, b, c, data, 52, 0xFD987193, 12 );
  MD5_TRANSFORM1( c, d, a, b, data, 56, 0xA679438E, 17 );
  MD5_TRANSFORM1( b, c, d, a, data, 60, 0x49B40821, 22 );

  MD5_TRANSFORM2( a, b, c, d, data,  4, 0xF61E2562,  5 );
  MD5_TRANSFORM2( d, a, b, c, data, 24, 0xC040B340,  9 );
  MD5_TRANSFORM2( c, d, a, b, data, 44, 0x265E5A51, 14 );
  MD5_TRANSFORM2( b, c, d, a, data,  0, 0xE9B6C7AA, 20 );
  MD5_TRANSFORM2( a, b, c, d, data, 20, 0xD62F105D,  5 );
  MD5_TRANSFORM2( d, a, b, c, data, 40, 0x02441453,  9 );
  MD5_TRANSFORM2( c, d, a, b, data, 60, 0xD8A1E681, 14 );
  MD5_TRANSFORM2( b, c, d, a, data, 16, 0xE7D3FBC8, 20 );
  MD5_TRANSFORM2( a, b, c, d, data, 36, 0x21E1CDE6,  5 );
  MD5_TRANSFORM2( d, a, b, c, data, 56, 0xC33707D6,  9 );
  MD5_TRANSFORM2( c, d, a, b, data, 12, 0xF4D50D87, 14 );
  MD5_TRANSFORM2( b, c, d, a, data, 32, 0x455A14ED, 20 );
  MD5_TRANSFORM2( a, b, c, d, data, 52, 0xA9E3E905,  5 );
  MD5_TRANSFORM2( d, a, b, c, data,  8, 0xFCEFA3F8,  9 );
  MD5_TRANSFORM2( c, d, a, b, data, 28, 0x676F02D9, 14 );
  MD5_TRANSFORM2( b, c, d, a, data, 48, 0x8D2A4C8A, 20 );

  MD5_TRANSFORM3( a, b, c, d, data, 20, 0xFFFA3942,  4 );
  MD5_TRANSFORM3( d, a, b, c, data, 32, 0x8771F681, 11 );
  MD5_TRANSFORM3( c, d, a, b, data, 44, 0x6D9D6122, 16 );
  MD5_TRANSFORM3( b, c, d, a, data, 56, 0xFDE5380C, 23 );
  MD5_TRANSFORM3( a, b, c, d, data,  4, 0xA4BEEA44,  4 );
  MD5_TRANSFORM3( d, a, b, c, data, 16, 0x4BDECFA9, 11 );
  MD5_TRANSFORM3( c, d, a, b, data, 28, 0xF6BB4B60, 16 );
  MD5_TRANSFORM3( b, c, d, a, data, 40, 0xBEBFBC70, 23 );
  MD5_TRANSFORM3( a, b, c, d, data, 52, 0x289B7EC6,  4 );
  MD5_TRANSFORM3( d, a, b, c, data,  0, 0xEAA127FA, 11 );
  MD5_TRANSFORM3( c, d, a, b, data, 12, 0xD4EF3085, 16 );
  MD5_TRANSFORM3( b, c, d, a, data, 24, 0x04881D05, 23 );
  MD5_TRANSFORM3( a, b, c, d, data, 36, 0xD9D4D039,  4 );
  MD5_TRANSFORM3( d, a, b, c, data, 48, 0xE6DB99E5, 11 );
  MD5_TRANSFORM3( c, d, a, b, data, 60, 0x1FA27CF8, 16 );
  MD5_TRANSFORM3( b, c, d, a, data,  8, 0xC4AC5665, 23 );

  MD5_TRANSFORM4( a, b, c, d, data,  0, 0xF4292244,  6 );
  MD5_TRANSFORM4( d, a, b, c, data, 28, 0x432AFF97, 10 );
  MD5_TRANSFORM4( c, d, a, b, data, 56, 0xAB9423A7, 15 );
  MD5_TRANSFORM4( b, c, d, a, data, 20, 0xFC93A039, 21 );
  MD5_TRANSFORM4( a, b, c, d, data, 48, 0x655B59C3,  6 );
  MD5_TRANSFORM4( d, a, b, c, data, 12, 0x8F0CCC92, 10 );
  MD5_TRANSFORM4( c, d, a, b, data, 40, 0xFFEFF47D, 15 );
  MD5_TRANSFORM4( b, c, d, a, data,  4, 0x85845DD1, 21 );
  MD5_TRANSFORM4( a, b, c, d, data, 32, 0x6FA87E4F,  6 );
  MD5_TRANSFORM4( d, a, b, c, data, 60, 0xFE2CE6E0, 10 );
  MD5_TRANSFORM4( c, d, a, b, data, 24, 0xA3014314, 15 );
  MD5_TRANSFORM4( b, c, d, a, data, 52, 0x4E0811A1, 21 );
  MD5_TRANSFORM4( a, b, c, d, data, 16, 0xF7537E82,  6 );
  MD5_TRANSFORM4( d, a, b, c, data, 44, 0xBD3AF235, 10 );
  MD5_TRANSFORM4( c, d, a, b, data,  8, 0x2AD7D2BB, 15 );
  MD5_TRANSFORM4( b, c, d, a, data, 36, 0xEB86D391, 21 );
#else
  u32 tmp;
  const u32 *X = (const u32*) data;

  MD5_TRANSFORM( tmp, MD5_TR1, X[ 0], 0xD76AA478UL,  7, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR1, X[ 1], 0xE8C7B756UL, 12, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR1, X[ 2], 0x242070DBUL, 17, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR1, X[ 3], 0xC1BDCEEEUL, 22, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR1, X[ 4], 0xF57C0FAFUL,  7, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR1, X[ 5], 0x4787C62AUL, 12, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR1, X[ 6], 0xA8304613UL, 17, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR1, X[ 7], 0xFD469501UL, 22, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR1, X[ 8], 0x698098D8UL,  7, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR1, X[ 9], 0x8B44F7AFUL, 12, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR1, X[10], 0xFFFF5BB1UL, 17, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR1, X[11], 0x895CD7BEUL, 22, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR1, X[12], 0x6B901122UL,  7, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR1, X[13], 0xFD987193UL, 12, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR1, X[14], 0xA679438EUL, 17, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR1, X[15], 0x49B40821UL, 22, b, c, d, a );

  MD5_TRANSFORM( tmp, MD5_TR2, X[ 1], 0xF61E2562UL,  5, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR2, X[ 6], 0xC040B340UL,  9, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR2, X[11], 0x265E5A51UL, 14, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR2, X[ 0], 0xE9B6C7AAUL, 20, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR2, X[ 5], 0xD62F105DUL,  5, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR2, X[10], 0x02441453UL,  9, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR2, X[15], 0xD8A1E681UL, 14, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR2, X[ 4], 0xE7D3FBC8UL, 20, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR2, X[ 9], 0x21E1CDE6UL,  5, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR2, X[14], 0xC33707D6UL,  9, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR2, X[ 3], 0xF4D50D87UL, 14, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR2, X[ 8], 0x455A14EDUL, 20, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR2, X[13], 0xA9E3E905UL,  5, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR2, X[ 2], 0xFCEFA3F8UL,  9, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR2, X[ 7], 0x676F02D9UL, 14, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR2, X[12], 0x8D2A4C8AUL, 20, b, c, d, a );

  MD5_TRANSFORM( tmp, MD5_TR3, X[ 5], 0xFFFA3942UL,  4, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR3, X[ 8], 0x8771F681UL, 11, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR3, X[11], 0x6D9D6122UL, 16, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR3, X[14], 0xFDE5380CUL, 23, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR3, X[ 1], 0xA4BEEA44UL,  4, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR3, X[ 4], 0x4BDECFA9UL, 11, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR3, X[ 7], 0xF6BB4B60UL, 16, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR3, X[10], 0xBEBFBC70UL, 23, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR3, X[13], 0x289B7EC6UL,  4, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR3, X[ 0], 0xEAA127FAUL, 11, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR3, X[ 3], 0xD4EF3085UL, 16, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR3, X[ 6], 0x04881D05UL, 23, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR3, X[ 9], 0xD9D4D039UL,  4, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR3, X[12], 0xE6DB99E5UL, 11, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR3, X[15], 0x1FA27CF8UL, 16, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR3, X[ 2], 0xC4AC5665UL, 23, b, c, d, a );

  MD5_TRANSFORM( tmp, MD5_TR4, X[ 0], 0xF4292244UL,  6, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR4, X[ 7], 0x432AFF97UL, 10, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR4, X[14], 0xAB9423A7UL, 15, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR4, X[ 5], 0xFC93A039UL, 21, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR4, X[12], 0x655B59C3UL,  6, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR4, X[ 3], 0x8F0CCC92UL, 10, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR4, X[10], 0xFFEFF47DUL, 15, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR4, X[ 1], 0x85845DD1UL, 21, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR4, X[ 8], 0x6FA87E4FUL,  6, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR4, X[15], 0xFE2CE6E0UL, 10, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR4, X[ 6], 0xA3014314UL, 15, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR4, X[13], 0x4E0811A1UL, 21, b, c, d, a );
  MD5_TRANSFORM( tmp, MD5_TR4, X[ 4], 0xF7537E82UL,  6, a, b, c, d );
  MD5_TRANSFORM( tmp, MD5_TR4, X[11], 0xBD3AF235UL, 10, d, a, b, c );
  MD5_TRANSFORM( tmp, MD5_TR4, X[ 2], 0x2AD7D2BBUL, 15, c, d, a, b );
  MD5_TRANSFORM( tmp, MD5_TR4, X[ 9], 0xEB86D391UL, 21, b, c, d, a );
#endif

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
};
