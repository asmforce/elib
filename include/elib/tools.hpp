/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: aux tools
**/

#ifndef ELIB_TOOLS_HPP
#define ELIB_TOOLS_HPP

#include <elib/aliases.hpp>

#include <typeinfo>

namespace elib
{
  typedef std::type_info datatype;

  namespace tools
  {
    class capsule
    {
    public:
    public:
      virtual const datatype &type() = 0;
      virtual capsule *clone() = 0;
    }; // class capsule

    template<typename T>
    class datum : public capsule
    {
    public:
    private:
      // must be inaccessible
      datum &operator = ( const datum & );

    public:
      datum( const T &v );

      virtual const datatype &type();
      virtual capsule *clone();

    public:
      T value;
    };  // class datum

    class any
    {
    public:
    public:
      any();
      template< typename T >
      any( const T &v );
      any( const any &rhs );
      ~any();

    public:
      bool null() const;
      const datatype& type() const;

      any &swap( any &rhs );
      template<typename T>
      any &operator = ( const T &v );
      any &operator = ( const any &rhs );

      template< typename T >
      T &as()  {
        return dynamic_cast< datum<T>* >(data)->value;
      };

    private:
      capsule *data;
    };  // class any
  }; // namespace tools
}; // namespace elib


template<typename T>
elib::tools::datum<T>::datum( const T &v ) : value(v)  {
};

template<typename T>
const elib::datatype &elib::tools::datum<T>::type()  {
  return typeid(T);
};

template<typename T>
elib::tools::capsule *elib::tools::datum<T>::clone()  {
  return new datum<T>(value);
};


elib::tools::any::any() : data(0)  {
};

template< typename T >
elib::tools::any::any( const T &v )  {
  data = new datum<T>(v);
};

elib::tools::any::any( const any &rhs )  {
  data = rhs.data->clone();
};

elib::tools::any::~any()  {
  if( data )  delete data;
};

elib::tools::any &elib::tools::any::swap( elib::tools::any &rhs )  {
  capsule *tmp = data;
  data = rhs.data;
  rhs.data = tmp;
  return *this;
};

template<typename T>
elib::tools::any &elib::tools::any::operator = ( const T &v )  {
  if( data )  delete data;
  data = new datum<T>(v);
  return *this;
};

elib::tools::any &elib::tools::any::operator = ( const elib::tools::any &rhs )  {
  if( data )  delete data;
  if( rhs.data )
    data = rhs.data->clone();
  else
    data = 0;
  return *this;
};

bool elib::tools::any::null() const  {
  return !data;
};

const elib::datatype& elib::tools::any::type() const  {
  return data ? data->type() : typeid(void);
};

#endif // ELIB_TOOLS_HPP
