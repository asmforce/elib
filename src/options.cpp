/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: console options
**/

#include <elib/aliases.hpp>
#include <elib/options.hpp>

#include <ostream>
#include <vector>
#include <map>

elib::options::options( const std::string &prefix ) : prefix_(prefix)
{
};

elib::options &elib::options::add( const std::string &name, const std::string &description, bool arg )
{
  rule &r = rules_[name];
  r.description = description;
  r.arg = arg;
  return *this;
};

bool elib::options::parse( int argc, const char * const *argv, variables &vars, values &alone )
{
  // Skips first argument (filename)
  for( int i = 1; i != argc; ++i )
  {
    std::string option = argv[i];
    if( option.compare(0,prefix_.length(),prefix_) )
    {
      // Nonamed value
      alone.push_back( option );
    } else {
      // Named value
      option.erase( 0, prefix_.length() );

      if( !rules_.count(option) )
        return false;

      if( rules_[option].arg )
      {
        if( ++i == argc )
          return false;
        vars[option] = argv[i];
      } else {
        vars[option] = "";
      };
    };
  };
  return true;
};

std::ostream &elib::operator << ( std::ostream &stream, const elib::options &opt )
{
  stream << "Options:\n";
  for( elib::options::rules::const_iterator i = opt.rules_.begin(); i != opt.rules_.end(); ++i )
  {
    const std::pair< std::string, elib::options::rule > &option = *i;
    stream << '\t' << opt.prefix_ << option.first;
    if( option.second.arg )  stream << " <value>";
    stream << "\t\t" << option.second.description << '\n';
  };
  stream << '\n';
  return stream;
};
