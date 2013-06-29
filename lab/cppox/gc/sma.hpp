/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (smart array)
**/

#ifndef ELIB_GC_SMA_HPP
#define ELIB_GC_SMA_HPP

typedef unsigned long u32;

template< typename T >
class sma
{
public:
  sma( T *p = 0 );
  sma( sma<T> &rhs );
  sma( sma<T> &&rhs );

  ~sma();

  sma<T> &operator = ( T *p );
  sma<T> &operator = ( sma<T> &rhs );
  sma<T> &operator = ( sma<T> &&rhs );

  T *release();
  T *data();
  const T *cdata() const;

  operator bool () const;

  T &operator [] ( u32 i );
  T &operator * ();
  T *operator -> ();

  const T &operator [] ( u32 i ) const;
  const T &operator * () const;
  const T *operator -> () const;

private:
  T *d;
};

#include "sma.cpp"

#endif // ELIB_GC_SMA_HPP
