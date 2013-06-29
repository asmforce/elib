#include "sma.hpp"

template< typename T >
sma<T>::sma( T *p ) : d(p)  {
};

template< typename T >
sma<T>::sma( sma<T> &rhs ) : d(rhs.d)  {
  rhs.d = 0;
};

template< typename T >
sma<T>::sma( sma<T> &&rhs ) : d(rhs.d)  {
  rhs.d = 0;
};

template< typename T >
sma<T>::~sma()
{
  if( d )
    delete[] d;
};

template< typename T >
sma<T> &sma<T>::operator = ( T *p )
{
  if( d )
    delete[] d;
  d = p;
  return *this;
};

template< typename T >
sma<T> &sma<T>::operator = ( sma<T> &rhs )
{
  if( d )
    delete[] d;
  d = rhs.d;
  rhs.d = 0;
  return *this;
};

template< typename T >
sma<T> &sma<T>::operator = ( sma<T> &&rhs )
{
  if( d )
    delete[] d;
  d = rhs.d;
  rhs.d = 0;
  return *this;
};

template< typename T >
T *sma<T>::release()
{
  T *res = d;
  d = 0;
  return res;
};

template< typename T >
T *sma<T>::data()  {
  return d;
};

template< typename T >
const T *sma<T>::cdata() const  {
  return d;
};

template< typename T >
sma<T>::operator bool () const  {
  return d;
};

template< typename T >
T &sma<T>::operator [] ( u32 i )  {
  return d[i];
};

template< typename T >
T &sma<T>::operator * ()  {
  return *d;
};

template< typename T >
T *sma<T>::operator -> ()  {
  return d;
};

template< typename T >
const T &sma<T>::operator [] ( u32 i ) const  {
  return d[i];
};

template< typename T >
const T &sma<T>::operator * () const  {
  return *d;
};

template< typename T >
const T *sma<T>::operator -> () const  {
  return d;
};
