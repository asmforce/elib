/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (smart pointer)
**/

#ifndef ELIB_GC_SMP_HPP
#define ELIB_GC_SMP_HPP

#include <elib/aliases.hpp>

namespace elib
{
  namespace gc
  {
    template< typename T >
    class smp
    {
    private:
      template< typename X >
      struct link
      {
        link( X *p ) : data(p)  {}
        X *data;
      };

    public:
      explicit smp( T *p = 0 );
      smp( link<T> rhs );
      smp( smp<T> &rhs );
      ~smp();

      T *release();
      T *address() const;
      T *operator -> () const;
      T &operator * () const;

      operator bool();

      template< typename X >
      operator link<X>();

      template< typename X >
      operator smp<X>();

      smp<T> &operator = ( T *rhs );
      smp<T> &operator = ( smp<T> &rhs );

    private:
      T *data;
    }; // class smp

  }; // namespace gc
}; // namespace elib

#include "imp/smp.cpp"

#endif // ELIB_GC_SMP_HPP
