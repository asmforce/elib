/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (shared pointer)
**/

#ifndef ELIB_GC_SHP_HPP
#define ELIB_GC_SHP_HPP

#include <elib/aliases.hpp>

namespace elib
{
  namespace gc
  {
    template< typename T >
    class shp
    {
    private:
      template< typename X >
      struct link
      {
        link( X *p ) : data(p)  {}
        X *data;
      };

    public:
      explicit shp( T *p = 0 );
      shp( link<T> rhs );
      shp( shp<T> &rhs );
      ~shp();

      T *release();
      T *address() const;
      T *operator -> () const;
      T &operator * () const;

      operator bool();

      template< typename X >
      operator link<X>();

      template< typename X >
      operator shp<X>();

      shp<T> &operator = ( T *rhs );
      shp<T> &operator = ( shp<T> &rhs );

    private:
      T *data;
      u32 *linkc;
    }; // class shp

  }; // namespace gc
}; // namespace elib

#include "imp/shp.cpp"

#endif // ELIB_GC_SHP_HPP
