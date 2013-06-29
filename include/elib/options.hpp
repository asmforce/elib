/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: console options
**/

#ifndef ELIB_OPTIONS_HPP
#define ELIB_OPTIONS_HPP

#include <elib/aliases.hpp>

#include <ostream>
#include <vector>
#include <map>

namespace elib
{
  class options;
  std::ostream & SHARED operator << ( std::ostream &stream, const options &opt );

  class SHARED options
  {
  private:
    friend std::ostream & SHARED operator << ( std::ostream &stream, const options &opt );

    struct rule
    {
      std::string description;
      bool        arg;
    };
    typedef std::map< std::string, rule > rules;

  public:
    typedef std::map< std::string, std::string > variables;
    typedef std::vector< std::string >           values;

  public:
    explicit options( const std::string &prefix );

    options &add( const std::string &name, const std::string &description, bool arg = false );
    bool parse( int argc, const char * const *argv, variables &vars, values &alone );

  private:
    rules       rules_;
    std::string prefix_;
  }; // class options
}; // namespace elib


#endif // ELIB_OPTIONS_HPP
