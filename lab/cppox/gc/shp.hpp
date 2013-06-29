/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (shared pointer)
**/

#ifndef ELIB_GC_SHP_HPP
#define ELIB_GC_SHP_HPP

typedef unsigned long u32;

template< typename T >
class shp
{
public:
  shp( T *p = 0 );
  shp( shp<T> &rhs );
  shp( shp<T> &&rhs );

  ~shp();

  shp<T> &operator = ( T *p );
  shp<T> &operator = ( shp<T> &rhs );
  shp<T> &operator = ( shp<T> &&rhs );

  u32 rc();
  T *release();
  T *data();
  const T *cdata() const;

  operator bool () const;
  T &operator * ();
  T *operator -> ();
  const T &operator * () const;
  const T *operator -> () const;

private:
  T   *d;
  u32 *c;
};

#include "shp.cpp"

#endif // ELIB_GC_SHP_HPP
