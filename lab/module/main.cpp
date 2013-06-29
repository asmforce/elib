#include <iostream>
#include <windows.h>

#include <elib/aliases.hpp>
using namespace elib::aliases;




namespace elib
{
  namespace api
  {
    class module
    {
    private:
      typedef HINSTANCE LIBRARY;

    public:
      module();
      ~module();

      bool load( const char *modname );
      bool load( const wchar *modname );
      void unload();

      bool loaded();

      template< typename function >
      function *get( const char *procname );

    private:
      LIBRARY mod;
    }; // class library
  }; // namespace api
}; // namespace elib



elib::api::module::module() : mod(0)  {
};

elib::api::module::~module()  {
  ::FreeLibrary( mod );
};

bool elib::api::module::load( const char *modname )
{
  if( mod )
    ::FreeLibrary( mod );
  mod = ::LoadLibraryA( modname );
  return mod;
};

bool elib::api::module::load( const wchar *modname )  {
  if( mod )
    ::FreeLibrary( mod );
  mod = ::LoadLibraryW( modname );
  return mod;
};

void elib::api::module::unload()
{
  if( mod )
    ::FreeLibrary( mod );
  mod = 0;
};

bool elib::api::module::loaded()  {
  return mod;
};

template< typename function >
function *elib::api::module::get( const char *procname )  {
  return reinterpret_cast<function*>( ::GetProcAddress(mod,procname) );
};









int main( int argc, char **argv )
{
  typedef int copyT( const char*, const char*, int );

  elib::api::module kernel32;

  kernel32.load( "kernel32.dll" );
  if( kernel32.loaded() )  {
    // dangerous
    copyT &copy = *kernel32.get<copyT>( "CopyFileA" );
    copy( "c:\\boot.ini", "c:\\temp\\boot.ini", 0 );
  } else {
    std::cout << "error: library does not loaded\n";
    return -1;
  };
  return 0;
};
