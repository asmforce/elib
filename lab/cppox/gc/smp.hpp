/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (smart pointer)
**/

#ifndef ELIB_GC_SMP_HPP
#define ELIB_GC_SMP_HPP

template< typename T >
class smp
{
public:
  smp( T *p = 0 );
  smp( smp<T> &rhs );
  smp( smp<T> &&rhs );

  ~smp();

  smp<T> &operator = ( T *p );
  smp<T> &operator = ( smp<T> &rhs );
  smp<T> &operator = ( smp<T> &&rhs );

  T *release();
  T *data();
  const T *cdata() const;

  operator bool () const;
  T &operator * ();
  T *operator -> ();
  const T &operator * () const;
  const T *operator -> () const;

private:
  T *d;
};

#include "smp.cpp"

#endif // ELIB_GC_SMP_HPP
