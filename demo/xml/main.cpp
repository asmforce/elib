/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: syntax-core demo
**/

#include <iostream>

#include <elib/syntax/cclass.hpp>
#include <elib/syntax/core.hpp>
#include <elib/aliases.hpp>
using namespace elib::aliases;

#include <string>
#include <stack>


namespace elib
{
  namespace xml
  {
    namespace sax
    {
      class callback;
      bool exec( std::istream &stream, callback &calls );

      class callback
      {
        friend bool exec( std::istream &stream, callback &calls );
      public:
        // callback();
      protected:
        virtual void doc() = 0;
        virtual void docend() = 0;
        virtual void failed() = 0;
        virtual bool tag( std::string &name ) = 0;
        virtual bool tagend( std::string &name ) = 0;
        virtual bool attribute( std::string &name, std::string &value ) = 0;
        virtual bool text( std::string &value ) = 0;
      }; // class callback
    }; // namespace sax
    namespace dom
    {
    }; // namespace dom
  }; // namespace xml
}; // namespace elib




static bool wordcc( char c )
{
  return isalpha(c);
};

bool elib::xml::sax::exec( std::istream &stream, callback &calls )
{
  std::stack<std::string> tagtree;
  std::string text;
  char c;
  // namecc is tag-name and attribute-name characters
  elib::syntax::cclass namecc( wordcc );
  calls.doc();

  if( !elib::syntax::skipspc(stream) )
  {
    calls.docend();
    return true;
  };

  while( elib::syntax::skipspc(stream,text) )
  {
    if( elib::syntax::match(stream,'<') )
    {
      if( elib::syntax::match(stream,"!--") )
      {
        //
        // Comment
        //
        if( elib::syntax::find(stream,"-->") )
        {
          continue;
        } else {
          calls.failed();
          return false;
        };
      };

      //
      // Tag
      //
      bool tagclose = elib::syntax::match( stream, '/' );
      if( elib::syntax::read(stream,namecc,text) )
      {
        if( tagclose )
        {
          if( text != tagtree.top() )  {
            calls.failed();
            return false;
          };
          tagtree.pop();
          calls.tagend( text );
        } else {
          tagtree.push( text );
          calls.tag( text );

          //
          // Attributes
          //
          std::string name, value;

          elib::syntax::skipspc( stream );
          while( elib::syntax::read(stream,namecc,name) )
          {
            if( stream >> c && c == '=' &&
                stream >> c && (c == '\'' || c == '\"')
                && elib::syntax::find(stream,c,value) )
            {
              calls.attribute( name, value );
              elib::syntax::skipspc( stream );
            } else {
              calls.failed();
              return false;
            };
          };

          // Alone tag sign
          if( elib::syntax::match(stream,'/') )  {
            tagtree.pop();
            calls.tagend( text );
          };
        };
        if( !elib::syntax::match(stream,'>') )
        {
          calls.failed();
          return false;
        };
      } else {
        calls.failed();
        return false;
      };
    } else {
      //
      // Text
      //
      std::string value( text );
      if( elib::syntax::find(stream,'<',text) )
      {
        value.append( text );
        calls.text( value );
        stream.putback( '<' );
      } else {
        calls.failed();
        return false;
      };
    };
  };

  calls.docend();
  return true;
};



class xml : public elib::xml::sax::callback
{
public:
  // xml();
protected:
  void doc();
  void docend();
  void failed();
  bool tag( std::string &name );
  bool tagend( std::string &name );
  bool attribute( std::string &name, std::string &value );
  bool text( std::string &value );
}; // class xml


void xml::doc()  {
  std::cout << "xml::doc();\n";
};

void xml::docend()  {
  std::cout << "xml::docend();\n";
};

void xml::failed()  {
  std::cout << "xml::failed();\n";
};

bool xml::tag( std::string &name )  {
  std::cout << "xml::tag( `" << name << "` );\n";
  return true;
};

bool xml::tagend( std::string &name )  {
  std::cout << "xml::tagend( `" << name << "` );\n";
  return true;
};

bool xml::attribute( std::string &name, std::string &value )  {
  std::cout << "xml::attribute( `" << name << "`, `" << value << "` );\n";
  return true;
};

bool xml::text( std::string &value )  {
  std::cout << "xml::text( `" << value << "` );\n";
  return true;
};






int main( int argc, char **argv )
{
  xml calls;
  elib::xml::sax::exec( std::cin, calls );
  return 0;
};
