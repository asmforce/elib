#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <stdlib.h>

#include "aliases.hpp"
using namespace elib::aliases;



class udps
{
public:
  enum { ReadError = -1 };

public:
  udps();
  ~udps();

  bool bind( u16 port );
  u32 receive( char *buffer, u32 size );

public:
  static bool initialize();

private:
  SOCKET      mSocket;
  sockaddr_in mAddress;
};


udps::udps()
{
  mSocket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

  bool yes = true;
  setsockopt( mSocket, SOL_SOCKET, SO_BROADCAST, (const char*) &yes, sizeof(yes) );
};

udps::~udps()
{
  closesocket( mSocket );
};

bool udps::bind( u16 port )
{
  mAddress.sin_family = AF_INET;
  mAddress.sin_port = htons( port );
  mAddress.sin_addr.s_addr = htonl( INADDR_ANY );
  if( ::bind(mSocket,(const sockaddr*)&mAddress,sizeof(mAddress)) == SOCKET_ERROR )
    return false;
  return true;
};

u32 udps::receive( char *buffer, u32 size )
{
  int addressSize = sizeof( mAddress );
  int res = recvfrom( mSocket, buffer, size, 0, (SOCKADDR*) &mAddress, &addressSize );
  return res == -1 ? 0UL : static_cast<u32>(res);
};

bool udps::initialize()
{
  static WSADATA wsaData;
  return !WSAStartup( MAKEWORD(2,2), &wsaData );
};













int main( int argc, char **argv )
{
  if( argc < 2 ) {
    std::cout << "usage: udps <port>\n";
    return 0;
  };

  if( udps::initialize() )
  {
    udps sock;
    const u32 size = 8196;
    char data[size];

    if( !sock.bind(atoi(argv[1])) ) {
      std::cout << "error: binding failed\n";
      return 0;
    };

    while( sock.receive(data,size-1) ) {
      data[size-1] = '\0';
      std::cout << data << '\n';
    };
  };

  return 0;
};
