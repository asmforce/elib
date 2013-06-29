#undef __STRICT_ANSI__
#include <iostream>

#include "gc/smp.hpp"
#include "gc/sma.hpp"


#include <typeinfo>

namespace elib
{
  class variable
  {
  private:
    typedef std::type_info datatype;

    class xdata
    {
    public:
      virtual ~xdata()  {};
      virtual const datatype &type() const = 0;
      virtual xdata *clone() const = 0;
    };

    template< typename T >
    class xwrap : public xdata
    {
    public:
      xwrap( const T &value ) : d(value)  {};

      virtual const datatype &type() const  { return typeid(T); };
      virtual xdata *clone() const  { return new xwrap(d); };

    public:
      T d;
    };

  public:
    variable() : d(0)  {};

    template< typename T >
    variable( const T &value ) : d(new xwrap<T>(value))  {};

    variable( const variable &rhs ) : d(rhs.d ? rhs.d->clone() : 0)  {};

    template< typename T >
    bool is() const  { return d ? d->type() == typeid(T) : false; };

    operator bool() const  { return d; };

    template< typename T >
    T &as()
    {
      if( !d || d->type() != typeid(T) )
        throw "error: elib::variable: type mismatch";
      return dynamic_cast< xwrap<T>* >(d)->d;
    };

    template< typename T >
    const T &as() const
    {
      if( !d || d->type() != typeid(T) )
        throw "error: elib::variable: type mismatch";
      return dynamic_cast< const xwrap<T>* >(d)->d;
    };

  private:
    xdata *d;
  }; // class variable
}; // namespace elib






int main( int argc, char **argv )
{
  elib::variable a = argc;
  elib::variable b = argv[0];

  if( a.is<int>() )
    std::cout << a.as<int>() << '\n';

  if( b.is<char*>() )
    std::cout << b.as<char*>() << '\n';

  try
  {
    std::cout << a.as<char*>() << '\n';
    std::cout << b.as<int>() << '\n';
  } catch( const char *exception ) {
    std::cout << exception << '\n';
  };

  return 0;
};
