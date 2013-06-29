/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (smart pointer)
**/

#include <elib/aliases.hpp>
#include <elib/gc/smp.hpp>

template< typename T >
elib::gc::smp<T>::smp( T *p ) : data(p)
{
};

template< typename T >
elib::gc::smp<T>::smp( link<T> rhs ) : data(rhs.data)
{
};

template< typename T >
elib::gc::smp<T>::smp( smp<T> &rhs ) : data(rhs.data)
{
  rhs.data = 0;
};

template< typename T >
elib::gc::smp<T>::~smp()
{
  if( data )
    delete data;
};

template< typename T >
T *elib::gc::smp<T>::release()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
T *elib::gc::smp<T>::address() const
{
  return data;
};

template< typename T >
T *elib::gc::smp<T>::operator -> () const
{
  return data;
};

template< typename T >
T &elib::gc::smp<T>::operator * () const
{
  return *data;
};

template< typename T >
elib::gc::smp<T>::operator bool()
{
  return (bool) data;
};

template< typename T >
template< typename X >
elib::gc::smp<T>::operator link<X>()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
template< typename X >
elib::gc::smp<T>::operator smp<X>()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
elib::gc::smp<T> &elib::gc::smp<T>::operator = ( T *rhs )
{
  if( data )
    delete data;
  data = rhs;
  return *this;
};

template< typename T >
elib::gc::smp<T> &elib::gc::smp<T>::operator = ( smp<T> &rhs )
{
  if( data )
    delete data;
  data = rhs.data;
  rhs.data = 0;
  return *this;
};
