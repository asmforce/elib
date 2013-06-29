/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: syntax-cclass demo
**/

#include <elib/syntax/cclass.hpp>
using elib::syntax::cclass;

#include <elib/aliases.hpp>
using namespace elib::aliases;

#include <iostream>
#include <string>
#include <vector>




/**
struct TokenStreamNode;
struct TokenStream;
struct TokenTreeNode;
struct TokenTree;
**/

#define TOKEN(X) (TOKEN_##X)
#define TOKEN_UNKNOWN    0
#define TOKEN_ID         1
#define TOKEN_NUMBER     2
#define TOKEN_DELIM      3
#define TOKEN_SPACE      4





bool predicateSpace( char c )  {
  return (c == ' ' ||
          c == '\n' ||
          c == '\t' ||
          c == '\r' ||
          c == '\x0C');
};

bool predicateId( char c )  {
  return (c >= 'a' && c <= 'z') ||
      (c >= 'A' && c <= 'Z') ||
      (c >= '0' && c <= '9') ||
      c == '_';
};

bool predicateDigits( char c )  {
  return (c >= '0' && c <= '9');
};

bool predicateInvalid( char c )  {
  return (c >= 0x7F && c <= 0xFF) ||
      (c >= '\0' &&
       c < ' ' &&
       c != '\n' &&
       c != '\t' &&
       c != '\r');
};


int main( int argc, char **argv )
{
  elib::syntax::cclass ccSpace( predicateSpace );
  elib::syntax::cclass ccId( predicateId );
  elib::syntax::cclass ccDigits( predicateDigits );
  elib::syntax::cclass ccInvalids( predicateInvalid );

  char c;
  std::string cs;

  while( std::cin.get(c) )
  {
    if( ccSpace.test(c) )  {
      while( std::cin.get(c) )
      {
        if( !ccSpace.test(c) )
        {
          std::cout << "SPACE\n";
          std::cin.putback( c );
          goto continue_;
        };
      };
      goto break_;
    };

    if( ccDigits.test(c) )  {
      cs.clear();
      cs += c;
      while( std::cin.get(c) )
      {
        if( ccDigits.test(c) )
        {
          cs += c;
        } else {
          std::cout << "NUMBER <" << cs.data() << ">\n";
          std::cin.putback( c );
          goto continue_;
        };
      };
      goto break_;
    };

    if( ccId.test(c) )  {
      cs.clear();
      cs += c;
      while( std::cin.get(c) )
      {
        if( ccId.test(c) )
        {
          cs += c;
        } else {
          std::cout << "ID <" << cs.data() << ">\n";
          std::cin.putback( c );
          goto continue_;
        };
      };
      goto break_;
    };

    if( ccInvalids.test(c) )  {
      std::cerr << "error: invalid character 0x" << std::hex << (unsigned)c << std::endl;
      goto break_;
    };

    std::cout << "DELIM <" << c << ">\n";

    continue_:
    continue;
  };
  break_:

  return 0;
};
