#include "smp.hpp"

template< typename T >
smp<T>::smp( T *p ) : d(p)  {
};

template< typename T >
smp<T>::smp( smp<T> &rhs ) : d(rhs.d)  {
  rhs.d = 0;
};

template< typename T >
smp<T>::smp( smp<T> &&rhs ) : d(rhs.d)  {
  rhs.d = 0;
};

template< typename T >
smp<T>::~smp()
{
  if( d )
    delete d;
};

template< typename T >
smp<T> &smp<T>::operator = ( T *p )
{
  if( d )
    delete d;
  d = p;
  return *this;
};

template< typename T >
smp<T> &smp<T>::operator = ( smp<T> &rhs )
{
  if( d )
    delete d;
  d = rhs.d;
  rhs.d = 0;
  return *this;
};

template< typename T >
smp<T> &smp<T>::operator = ( smp<T> &&rhs )
{
  if( d )
    delete d;
  d = rhs.d;
  rhs.d = 0;
  return *this;
};

template< typename T >
T *smp<T>::release()
{
  T *res = d;
  d = 0;
  return res;
};

template< typename T >
T *smp<T>::data()  {
  return d;
};

template< typename T >
const T *smp<T>::cdata() const  {
  return d;
};

template< typename T >
smp<T>::operator bool() const  {
  return d;
};

template< typename T >
T &smp<T>::operator * ()  {
  return *d;
};

template< typename T >
T *smp<T>::operator -> ()  {
  return d;
};

template< typename T >
const T &smp<T>::operator * () const  {
  return *d;
};

template< typename T >
const T *smp<T>::operator -> () const  {
  return d;
};
