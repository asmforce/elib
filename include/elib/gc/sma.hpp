/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (smart array)
**/

#ifndef ELIB_GC_SMA_HPP
#define ELIB_GC_SMA_HPP

#include <elib/aliases.hpp>

namespace elib
{
  namespace gc
  {
    template< typename T >
    class sma
    {
    public:
      template< typename X >
      struct link
      {
        link( X *p ) : data(p)  {}
        X *data;
      };

    public:
      explicit sma( T *p = 0 );
      sma( link<T> rhs );
      sma( sma<T> &rhs );
      ~sma();

      T *release();
      T *address() const;
      T *operator -> () const;
      T &operator * () const;
      T &operator [] ( u32 i ) const;

      operator bool();

      template< typename X >
      operator link<X>();

      template< typename X >
      operator sma<X>();

      sma<T> &operator = ( T *rhs );
      sma<T> &operator = ( sma<T> &rhs );

    private:
      T *data;
    }; // class sma

  }; // namespace gc
}; // namespace elib

#include "imp/sma.cpp"

#endif // ELIB_GC_SMA_HPP
