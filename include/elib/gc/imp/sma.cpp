/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (smart array)
**/

#include <elib/aliases.hpp>
#include <elib/gc/sma.hpp>

template< typename T >
elib::gc::sma<T>::sma( T *p ) : data(p)
{
};

template< typename T >
elib::gc::sma<T>::sma( link<T> rhs ) : data(rhs.data)
{
};

template< typename T >
elib::gc::sma<T>::sma( sma<T> &rhs ) : data(rhs.data)
{
  rhs.data = 0;
};

template< typename T >
elib::gc::sma<T>::~sma()
{
  if( data )
    delete[] data;
};

template< typename T >
T *elib::gc::sma<T>::release()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
T *elib::gc::sma<T>::address() const
{
  return data;
};

template< typename T >
T *elib::gc::sma<T>::operator -> () const
{
  return data;
};

template< typename T >
T &elib::gc::sma<T>::operator * () const
{
  return *data;
};

template< typename T >
T &elib::gc::sma<T>::operator [] ( u32 i ) const
{
  return data[i];
};

template< typename T >
elib::gc::sma<T>::operator bool()
{
  return (bool) data;
};

template< typename T >
template< typename X >
elib::gc::sma<T>::operator link<X>()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
template< typename X >
elib::gc::sma<T>::operator sma<X>()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
elib::gc::sma<T> &elib::gc::sma<T>::operator = ( T *rhs )
{
  if( data )
    delete[] data;
  data = rhs;
  return *this;
};

template< typename T >
elib::gc::sma<T> &elib::gc::sma<T>::operator = ( sma<T> &rhs )
{
  if( data )
    delete[] data;
  data = rhs.data;
  rhs.data = 0;
  return *this;
};
