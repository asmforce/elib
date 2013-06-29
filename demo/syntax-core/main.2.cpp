/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: syntax-core demo
**/

#include <elib/aliases.hpp>
#include <elib/syntax/core.hpp>
#include <elib/syntax/cclass.hpp>
using namespace elib::aliases;

#include <algorithm>
#include <iostream>
#include <sstream>






char *script = "/**\n"
               " * @author: Vitaliy Krutko\n"
               " * @email: asmforce@ukr.net asmxforce@gmail.com\n"
               " * @project: elib (external library)\n"
               " * @target: test script\n"
               "**/\n"
               "declare x:object;\n"
               "\n"
               "\n"
               "// Declarations:\n"
               "declare a:int;\n"
               "declare b:float\n"
               "declare c:string\n\n";






int main( int argc, char **argv )
{
  namespace syntax = elib::syntax;

  std::stringstream ss( script );
  syntax::cclass lowercc( 'a', 'z' );
  syntax::cclass uppercc( 'A', 'Z' );
  syntax::cclass alphacc( lowercc | uppercc );

  while( ss )
  {
    std::string cs;
    if( !syntax::skipspc(ss,cs) )
    {
      std::cout << "EOF:`" << cs << "`\n";
      return 0;
    };

    if( syntax::match(ss,"/**") )
    {
      /// MULTILINE COMMENT
      std::string comment;
      if( !syntax::find(ss,"**/",comment) )
        return 1;
      std::replace( comment.begin(), comment.end(), '\n', '|' );
      std::cout << "Multiline comment: `" << comment << "`\n";
    } else if( syntax::match(ss,"//") ) {
      /// SINGLELINE COMMENT
      std::string comment;
      if( !syntax::find(ss,'\n',comment) )
        std::cout << "Warning: singleline comment: newline character missing\n";
      std::cout << "Singleline comment: `" << comment << "`\n";
    } else if( syntax::match(ss,alphacc) ) {
      /// INSTRUCTION
      std::string token;
      if( !syntax::skip( ss, alphacc, token ) )
      {
        std::cout << "Error: unexpected EOF\n";
        return 1;
      };
      std::cout << "Token: `" << token << "`\n";
      syntax::find( ss, '\n' );
    } else {
      std::cout << "Error: Syntax error\n";
      return 1;
    };
  };

  return 0;
};
