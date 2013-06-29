#undef __STRICT_ANSI__
#include <iostream>
#include <string.h>

#include "gc/shp.hpp"


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
void use( shp<T> p )
{
  std::cout << "use:" << p.cdata() << '\n';
};








int main( int argc, char **argv )
{
  {
   shp<scope> s0 = new scope;
   shp<scope> s1 = s0;
   shp<scope> s2 = s0;
   shp<scope> s3 = s0;
   shp<scope> s4 = s0;

   use( s0 );
   use( s1 );
   use( s2 );
   use( s3 );
   use( s4 );

   std::cout << "rc: " << s0.rc() << '\n';
  }

  if( scope::instances() )
    std::cout << "fault: <" << scope::instances() << "> instances left;\n";

  return 0;
};
temp`