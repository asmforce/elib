/**
 * @author: Vitaliy Krutko
 * @e-mail: asmforce@ukr.net asmxforce@gmail.com
 * @project: elib (external library)
 * @target: syntax core
**/

#ifndef ELIB_SYNTAX_CORE_HPP
#define ELIB_SYNTAX_CORE_HPP

#include <elib/aliases.hpp>
#include <elib/syntax/cclass.hpp>

#include <istream>
#include <string>

namespace elib
{
  namespace syntax
  {
    /**
     * Описание:
     * Функция возвращает символы строки `cs` в поток `stream`,
     * что позволит считать их из потока (в том порядке, что и
     * в строке).
     *
     * Пример:
     * std::string s1 = "aaabbbccc", s2;
     * elib::syntax::back( std::cin, s1 );
     * std::cin >> s2; // считано s2 == "aaabbbccc"
    **/
    void SHARED back( std::istream &stream, const std::string &cs );

    /**
     * Категория SKIPSPC:
     * Функции данной категории производят пропуск пробельных
     * символов из потока (пробел, таб, перевод строки, и т.д.).
     * Функция с аргументом `std::string &cs` сохраняет все
     * пропущеные символы в cs.
     * Возвращает `false`, если был встречен EOF.
    **/
    bool SHARED skipspc( std::istream &stream );
    bool SHARED skipspc( std::istream &stream, std::string &cs );

    /**
     * Описание:
     * Функция получает символы из потока `stream` до тех пор,
     * пока эти символы принадлежат классу символов `cc`.
     * Встретив EOF она возвращает `false`, a встретив символ,
     * не принадлежащий `cc`, она возвращает `true`.
     * Функция с аргументом `std::string &cs` сохраняет все
     * пропущеные символы в cs.
    **/
    bool SHARED skip( std::istream &stream, const cclass &cc );
    bool SHARED skip( std::istream &stream, const cclass &cc, std::string &cs );


    /**
     * Категория FIND:
     * Функции данной категории производят поиск эталона (char,
     * string, cclass) в потоке и изъятие найденной цели.
     * Внимание: функции поиска cclass не производят изъятие цели.
     *
     * После успешного выполнения функции, строка `cs` содержит
     * участок текста от начала поиска до найденной цели (не включаяя
     * саму цель).
     *
     * Пример:
     * std::stringstream ss( "// Some comment...\n// Other comment." );
     * std::string cs;
     * elib::syntax::find( ss, '\n', cs ); // cs == "// Some comment..."
     * elib::syntax::find( ss, '\n', cs ); // cs == "// Other comment."
    **/

    bool SHARED find( std::istream &stream, char target );
    bool SHARED find( std::istream &stream, char target, std::string &cs );

    bool SHARED find( std::istream &stream, const std::string &target );
    bool SHARED find( std::istream &stream, const std::string &target, std::string &cs );

    bool SHARED find( std::istream &stream, const cclass &cc );
    bool SHARED find( std::istream &stream, const cclass &cc, std::string &cs );


    /**
     * Категория MATCH:
     * Функции данной категории проверяют факт совпадения символов
     * из потока с эталонами: char, string, cclass.
     *
     * Перед сравнением символы из потока не отбрасываются.
     *
     * Функции данной категории восстанавливают исходное содержимое
     * потока (возвращают символы) в случае несовпадения.
     * Функция с аргументом `const cclass &cc`, восстанавливает
     * поток в любом случае (как совпадение, так и несовпадение).
    **/

    bool SHARED match( std::istream &stream, char target );
    bool SHARED match( std::istream &stream, const std::string &target );
    bool SHARED match( std::istream &stream, const cclass &cc );

    /**
     * Описание:
     * Читает символы из потока `stream` в строку `cs`.
     * Встретив символ, не принадлежащий классу `cc`, функция
     * завершается. Возвращает `true`, если считано один и более
     * символов и не встречен EOF, иначе - `false`.
    **/
    bool SHARED read( std::istream &stream, const cclass &cc, std::string &cs );
  }; // namespace syntax
}; // namespace elib

#endif // ELIB_SYNTAX_CORE_HPP
