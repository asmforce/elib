#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <stdlib.h>

#include "aliases.hpp"
using namespace elib::aliases;



class udpc
{
public:
  enum { ReadError = -1 };

public:
  udpc();
  ~udpc();

  void settarget( const char *ipaddress, u16 port );
  u32 send( char *buffer, u32 size );

public:
  static bool initialize();

private:
  SOCKET      mSocket;
  sockaddr_in mAddress;
};


udpc::udpc()
{
  mSocket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

  bool yes = true;
  setsockopt( mSocket, SOL_SOCKET, SO_BROADCAST, (const char*) &yes, sizeof(yes) );
  mAddress.sin_family = AF_INET;
};

udpc::~udpc()
{
  closesocket( mSocket );
};

void udpc::settarget( const char *ipaddress, u16 port )
{
  mAddress.sin_port = htons( port );
  mAddress.sin_addr.s_addr = inet_addr(ipaddress);
};

u32 udpc::send( char *buffer, u32 size )
{
  return sendto( mSocket, buffer, size, 0, (sockaddr*)&mAddress, sizeof(mAddress) );
};

bool udpc::initialize()
{
  static WSADATA wsaData;
  return !WSAStartup( MAKEWORD(2,2), &wsaData );
};













int main( int argc, char **argv )
{
  if( argc < 3 ) {
    std::cout << "usage: udpc <target-ip> <port>\n";
    return 0;
  };

  if( udpc::initialize() )
  {
    udpc sock;
    const u32 size = 8196;
    char data[size];

    sock.settarget( argv[1], atoi(argv[2]) );
    while( std::cin.getline(data,size) )
      sock.send( data, size-1 );
    /// sock.send( data, 0UL );
  };

  return 0;
};
