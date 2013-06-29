/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (shared array)
**/

#include <elib/aliases.hpp>
#include <elib/gc/sha.hpp>

template< typename T >
elib::gc::sha<T>::sha( T *p ) : data(p)
{
};

template< typename T >
elib::gc::sha<T>::sha( link<T> rhs ) : data(rhs.data)
{
};

template< typename T >
elib::gc::sha<T>::sha( sha<T> &rhs ) : data(rhs.data)
{
  rhs.data = 0;
};

template< typename T >
elib::gc::sha<T>::~sha()
{
  if( data )
    delete[] data;
};

template< typename T >
T *elib::gc::sha<T>::release()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
T *elib::gc::sha<T>::address() const
{
  return data;
};

template< typename T >
T *elib::gc::sha<T>::operator -> () const
{
  return data;
};

template< typename T >
T &elib::gc::sha<T>::operator * () const
{
  return *data;
};

template< typename T >
T &elib::gc::sha<T>::operator [] ( u32 i ) const
{
  return data[i];
};

template< typename T >
elib::gc::sha<T>::operator bool()
{
  return (bool) data;
};

template< typename T >
template< typename X >
elib::gc::sha<T>::operator link<X>()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
template< typename X >
elib::gc::sha<T>::operator sha<X>()
{
  T *p = data;
  data = 0;
  return p;
};

template< typename T >
elib::gc::sha<T> &elib::gc::sha<T>::operator = ( T *rhs )
{
  if( data )
    delete[] data;
  data = rhs;
  return *this;
};

template< typename T >
elib::gc::sha<T> &elib::gc::sha<T>::operator = ( sha<T> &rhs )
{
  if( data )
    delete[] data;
  data = rhs.data;
  rhs.data = 0;
  return *this;
};
