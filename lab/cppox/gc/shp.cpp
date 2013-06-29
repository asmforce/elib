#include "shp.hpp"

template< typename T >
shp<T>::shp( T *p ) : d(p), c(new u32(1))
{
};

template< typename T >
shp<T>::shp( shp<T> &rhs ) : d(rhs.d), c(rhs.c)
{
  ++*c;
};

template< typename T >
shp<T>::shp( shp<T> &&rhs ) : d(rhs.d), c(rhs.c)
{
  ++*c;
};

template< typename T >
shp<T>::~shp()
{
  if( !(--*c) )
  {
    delete c;
    if( d )
      delete d;
  };
};

template< typename T >
shp<T> &shp<T>::operator = ( T *p )
{
  if( *c == 1 )
  {
    if( d )
      delete d;
  } else {
    c = new u32( 1 );
  };
  d = p;
  return *this;
};

template< typename T >
shp<T> &shp<T>::operator = ( shp<T> &rhs )
{
  if( *c == 1 )
  {
    delete c;
    if( d )
      delete d;
  };
  d = rhs.d;
  c = rhs.c;
  return *this;
};

template< typename T >
shp<T> &shp<T>::operator = ( shp<T> &&rhs )
{
  if( *c == 1 )
  {
    delete c;
    if( d )
      delete d;
  };
  d = rhs.d;
  c = rhs.c;
  return *this;
};

template< typename T >
u32 shp<T>::rc()
{
  return *c;
};

template< typename T >
T *shp<T>::release()
{
  if( *c == 1 )
  {
    T *res = d;
    d = 0;
    return res;
  } else {
    --*c;
    c = new u32( 1 );
    d = 0;
    return 0;
  };
};

template< typename T >
T *shp<T>::data()
{
  return d;
};

template< typename T >
const T *shp<T>::cdata() const
{
  return d;
};

template< typename T >
shp<T>::operator bool() const
{
  return d;
};

template< typename T >
T &shp<T>::operator * ()
{
  return *d;
};

template< typename T >
T *shp<T>::operator -> ()
{
  return d;
};

template< typename T >
const T &shp<T>::operator * () const
{
  return *d;
};

template< typename T >
const T *shp<T>::operator -> () const
{
  return d;
};
