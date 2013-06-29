/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (shared pointer)
**/

#include <elib/aliases.hpp>
#include <elib/gc/shp.hpp>

template< typename T >
elib::gc::shp<T>::shp( T *p ) : data(p)
{
};

template< typename T >
elib::gc::shp<T>::shp( link<T> rhs ) : data(rhs.data)
{
};

template< typename T >
elib::gc::shp<T>::shp( shp<T> &rhs ) : data(rhs.data)
{
  rhs.data = 0;
};

template< typename T >
elib::gc::shp<T>::~shp()
{
  if( data )
    delete data;
};

template< typename T >
T *elib::gc::shp<T>::release()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
T *elib::gc::shp<T>::address() const
{
  return data;
};

template< typename T >
T *elib::gc::shp<T>::operator -> () const
{
  return data;
};

template< typename T >
T &elib::gc::shp<T>::operator * () const
{
  return *data;
};

template< typename T >
elib::gc::shp<T>::operator bool()
{
  return (bool) data;
};

template< typename T >
template< typename X >
elib::gc::shp<T>::operator link<X>()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
template< typename X >
elib::gc::shp<T>::operator shp<X>()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
elib::gc::shp<T> &elib::gc::shp<T>::operator = ( T *rhs )
{
  if( data )
    delete data;
  data = rhs;
  return *this;
};

template< typename T >
elib::gc::shp<T> &elib::gc::shp<T>::operator = ( shp<T> &rhs )
{
  if( data )
    delete data;
  data = rhs.data;
  rhs.data = 0;
  return *this;
};
