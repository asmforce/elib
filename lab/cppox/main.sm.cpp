#undef __STRICT_ANSI__
#include <iostream>
#include <string.h>

#include "gc/smp.hpp"
#include "gc/sma.hpp"


class scope
{
private:
  static unsigned long gc;

public:
  scope()  { i = ++gc; };
  ~scope()  { --gc; };

  static unsigned long instances() { return gc; };

public:
  unsigned long i;
};

unsigned long scope::gc = 0;




template< typename T >
sma<T> create( unsigned long n )
{
  return new T[n];
};

template< typename T >
smp<T> create()
{
  return new T;
};




template< typename T >
void use( T *p )
{
  std::cout << "use:" << p << '\n';
};

template< typename T >
void use( const T *p )
{
  std::cout << "const-use:" << p << '\n';
};







int main( int argc, char **argv )
{
  const unsigned long N = 10;

  // sma (smart array)
  {
    auto sm = create<scope>( N );
    if( !sm )  std::cout << "fault\n";
    use( sm.cdata() );
    if( !sm )  std::cout << "fault\n";
    use( sm.data() );
    if( !sm )  std::cout << "fault\n";

    std::cout << sm->i << '\n';
    std::cout << (*sm).i << '\n';
    for( unsigned long i = 0; i != N; ++i )
      std::cout << sm[i].i << '\t';
  }

  // const sma (smart array)
  {
    const auto sm = create<scope>( N );
    if( !sm )  std::cout << "fault\n";
    use( sm.cdata() );
    if( !sm )  std::cout << "fault\n";
    //use( sm.data() );                    // Isn't accessible for constant sma<scope>
    //if( !sm )  std::cout << "fault\n";

    std::cout << sm->i << '\n';
    std::cout << (*sm).i << '\n';
    for( unsigned long i = 0; i != N; ++i )
      std::cout << sm[i].i << '\t';
  }

  // smp (smart pointer)
  {
    auto sm = create<scope>();
    if( !sm )  std::cout << "fault\n";
    use( sm.cdata() );
    if( !sm )  std::cout << "fault\n";
    use( sm.data() );
    if( !sm )  std::cout << "fault\n";

    std::cout << sm->i << '\n';
    std::cout << (*sm).i << '\n';
    //for( unsigned long i = 0; i != N; ++i )  // Isn't accessible for pointer (but not array)
    //  std::cout << sm[i].i << '\t';
  }

  // const smp (smart pointer)
  {
    const auto sm = create<scope>();
    if( !sm )  std::cout << "fault\n";
    use( sm.cdata() );
    if( !sm )  std::cout << "fault\n";
    //use( sm.data() );                    // Isn't accessible for constant sma<scope>
    //if( !sm )  std::cout << "fault\n";

    std::cout << sm->i << '\n';
    std::cout << (*sm).i << '\n';
    //for( unsigned long i = 0; i != N; ++i )  // Isn't accessible for pointer (but not array)
    //  std::cout << sm[i].i << '\t';
  }

  if( scope::instances() )
    std::cout << "fault: <" << scope::instances() << "> instances left;\n";

  return 0;
};
