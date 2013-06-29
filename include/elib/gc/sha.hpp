/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: garbage collect (shared array)
**/

#ifndef ELIB_GC_SHA_HPP
#define ELIB_GC_SHA_HPP

#include <elib/aliases.hpp>

namespace elib
{
  namespace gc
  {
    template< typename T >
    class sha
    {
    public:
      template< typename X >
      struct link
      {
        link( X *p ) : data(p)  {}
        X *data;
      };

    public:
      explicit sha( T *p = 0 );
      sha( link<T> rhs );
      sha( sha<T> &rhs );
      ~sha();

      T *release();
      T *address() const;
      T *operator -> () const;
      T &operator * () const;
      T &operator [] ( u32 i ) const;

      operator bool();

      template< typename X >
      operator link<X>();

      template< typename X >
      operator sha<X>();

      sha<T> &operator = ( T *rhs );
      sha<T> &operator = ( sha<T> &rhs );

    private:
      T *data;
    }; // class sha

  }; // namespace gc
}; // namespace elib

#include "imp/sha.cpp"

#endif // ELIB_GC_SHA_HPP
