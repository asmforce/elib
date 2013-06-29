#include <iostream>
#include <winsock.h>

#include <elib/aliases.hpp>
using namespace elib::aliases;
//#include <elib/chronos.hpp>





#pragma pack( push, 1 )

namespace elib
{
  namespace ip
  {
    namespace aux
    {
      // eq to htonl
      u32 revbytes( u32 v );

      // eq to htons
      u16 revbytes( u16 v );
    }; // namespace aux


    /**
     * @fn initialize
     * @returns true if success
     * @brief should be called before network using
    **/

    static bool initialize();


    /**
     * @struct ipv4
     * @brief ip address v4 only
     * @note do not use any `winsock` functions
     * Provides public access to all data-members
     * for simple modification, and high performance
    **/

    struct ipv4
    {
    public:
      ipv4();
      ipv4( u32 abcd32 );
      ipv4( u8 a8, u8 b8, u8 c8, u8 d8 );
      ipv4( const char *abcdcs );

    public:
      union {
        u32 abcd;
        struct { u8 a, b, c, d; };
      };
    };

    const ipv4 null( 0UL );
    const ipv4 any( 0UL );
    const ipv4 broadcast( 0xFFFFFFFFUL );
    const ipv4 localhost( 0x7F000001UL );


    /**
     * @struct address
     * @brief endpoint address
     * Provides complete endpoint address
     * ready for using with socket classes
    **/

    struct address
    {
    protected:
      struct sockaddress
      {
        u16 family;
        u16 port;
        ipv4 address;
        u8 reserved[8];
      };

    public:
      address();
      address( ipv4 ipaddress, u16 port );

      void set( ipv4 ipaddress, u16 port );

      ipv4 ip();
      u16 port();

    protected:
      sockaddress msa;
    }; // class address


    /**
     * @class udps
     * @brief user datagram protocol socket
     * Provides datagram exchange between two
     * hosts without connection and delivery
     * confirmation
    **/

    // udp socket
    class udps
    {
    public:
      udps();

      bool bind( const address &source );
      u32 read( void *storage, u32 size );
      u32 write( const void *storage, u32 size );
      bool valid();

    protected:
      SOCKET  msocket;
      address maddress;
    }; // class udps


    // tcp server
    class tcps
    {
    public:
      tcps();
    protected:
      address maddress;
    }; // class tcps


    // tcp client
    class tcpc
    {
    public:
      tcpc();
    protected:
      address maddress;
    }; // class tcpc
  }; // namespace ip
}; // namespace elib



static bool elib::ip::initialize()
{
  static WSADATA wsaData;
  // WinSock v2.2
  return !WSAStartup( 0x0202, &wsaData );
};


u32 elib::ip::aux::revbytes( u32 v )
{
  GASM
  (
    "bswap %%eax        ;"
    : "=a" (v)
    : "a" (v)
  );
  return v;
};

u16 elib::ip::aux::revbytes( u16 v )
{
  GASM
  (
    "xchg %%al, %%ah    ;"
    : "=a" (v)
    : "a" (v)
  );
  return v;
};


elib::ip::ipv4::ipv4()
  : abcd(0UL)
{
};

elib::ip::ipv4::ipv4( u32 abcd32 )
  : abcd(abcd32)
{
};

elib::ip::ipv4::ipv4( u8 a8, u8 b8, u8 c8, u8 d8 )
  : a(a8), b(b8), c(c8), d(d8)
{
};

elib::ip::ipv4::ipv4( const char *abcdcs )
{
  GASM
  (
    "xorw %%cx, %%cx    ;"
    "xorl %%ebx, %%ebx  ;"
    "1:                 ;"
    "  lodsb            ;"
    "  cmp $'.', %%al   ;"
    "  jne 2f           ;"
    "  test %%cl, %%cl  ;"
    "  jz 3f            ;"
    "  shl $8, %%ebx    ;"
    "  xorb %%cl, %%cl  ;"
    "  incb %%ch        ;"
    "  cmpb $4, %%ch    ;"
    "  jb 1b            ;"
    "2:                 ;"
    "  cmp $0, %%al     ;"
    "  je 4f            ;"
    "  cmp $'0', %%al   ;"
    "  jb 3f            ;"
    "  cmp $'9', %%al   ;"
    "  ja 3f            ;"
    "  sub $'0', %%al   ;"
    "  mov %%al, %%dl   ;"
    "  mov $10, %%al    ;"
    "  mul %%bl         ;"
    "  mov %%al, %%bl   ;"
    "  add %%dl, %%bl   ;"
    "  jo 3f            ;"
    "inc %%cl           ;"
    "jmp 1b             ;"
    "3:                 ;"
    "xor %%ebx, %%ebx   ;"
    "4:                 ;"
    : "=b" (abcd)
    : "S" (abcdcs)
  );
};


elib::ip::address::address()  {
  msa.family = AF_INET;
  msa.address = elib::ip::null;
  msa.port = 0;
};

elib::ip::address::address( ipv4 ip, u16 port )  {
  msa.family = AF_INET;
  msa.address.abcd = aux::revbytes(ip.abcd);
  msa.port = aux::revbytes(port);
};

void elib::ip::address::set( ipv4 ip, u16 port )  {
  msa.address.abcd = aux::revbytes(ip.abcd);
  msa.port = aux::revbytes(port);
};

elib::ip::ipv4 elib::ip::address::ip()  {
  return aux::revbytes(msa.address.abcd);
};

u16 elib::ip::address::port()  {
  return aux::revbytes(msa.port);
};



elib::ip::udps::udps()  {
  msocket = ::socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
};

bool elib::ip::udps::bind( const address &source )  {
  return !::bind( msocket, (const SOCKADDR*)&source, sizeof(SOCKADDR) );
};

u32 elib::ip::udps::read( void *storage, u32 size )  {
  int addrlen = sizeof(SOCKADDR);
  int retcode = ::recvfrom( msocket, (char*)storage, size, 0, (SOCKADDR*)&maddress, &addrlen );
  return retcode > 0 ? retcode : 0uL;
};

u32 elib::ip::udps::write( const void *storage, u32 size )  {
  int retcode = ::sendto( msocket, (char*)storage, size, 0, (SOCKADDR*)&maddress, sizeof(SOCKADDR) );
  return retcode > 0 ? retcode : 0uL;
};

bool elib::ip::udps::valid()  {
  return (msocket != INVALID_SOCKET);
};

#pragma pack( pop )
















int main( int argc, char **argv )
{
  if( !elib::ip::initialize() )  {
    std::cout << "error: initialization failed\n";
    return -1;
  };

  // TODO:
  //bool yes = true;
  //setsockopt( sock, SOL_SOCKET, SO_BROADCAST, (const char*) &yes, sizeof(yes) );

  elib::ip::address mask( elib::ip::any, 65000 );
  elib::ip::udps udps;

  const u32 size = 1024;
  char storage[size];

  udps.bind( mask );

  for( u32 bytes = size; ; )
  {
    bytes = udps.read( storage, size );
    std::cout << bytes << " read\n";
    if( bytes )
      udps.write( storage, bytes );
    else
      break;
  };

  return 0;
};
