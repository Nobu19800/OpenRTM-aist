// -*- C++ -*-
/*!
 * @file StringUtil.h
 * @brief String operation utility
 * @date $Date: 2007-12-31 03:08:07 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: StringUtil.h 826 2008-08-26 08:13:39Z n-ando $
 *
 */

#ifndef COIL_STRINGUTIL_H
#define COIL_STRINGUTIL_H

#include <string>
#include <vector>
#include <sstream>

#if defined (_MSC_VER) && (_MSC_VER <=1500) // VC2008(VC9.0) or before
#else
#include <stdint.h>
#endif
// Cygwin's gcc does not provide wstring type
#if defined(Cygwin) && ( __GNUC__ < 4 )
namespace std
{
  typedef basic_string<wchar_t> wstring;
}
#endif

namespace coil
{
  typedef std::vector<std::string> vstring;

  /*!
   * @if jp
   * @brief string ����Ewstring �ؤ��Ѵ�
   *
   * Ϳ���餁E� string ʸ����Ewstring ʸ������Ѵ�
   *
   * @param str std::string ��������ʸ��΁E   * @return std::wstring ���ν���ʸ��΁E   *
   * @else
   * @brief string to wstring conversion
   *
   * This function convert from a string to a wstring.
   * 
   * @param str The input std::string type string
   * @return Converted std::wstring type string
   *
   * @endif
   */
  std::wstring string2wstring(std::string str);

  /*!
   * @if jp
   * @brief wstring ����Estring �ؤ��Ѵ�
   *
   * Ϳ���餁E� wstring ʸ����Estring ʸ������Ѵ�
   *
   * @param str std::wstring ��������ʸ��΁E   * @return std::string ���ν���ʸ��΁E   *
   * @else
   * @brief wstring to string conversion
   *
   * This function convert from a wstring to a string.
   * 
   * @param str The input std::wstring type string
   * @return Converted std::string type string
   *
   * @endif
   */
  std::string wstring2string(std::wstring wstr);

  /*!
   * @if jp
   * @brief ��ʸ���ؤ��Ѵ�
   *
   * Ϳ���餁E�ʸ�������ʸ�����Ѵ�
   *
   * @param str ����ʸ��΁E   *
   * @else
   * @brief Uppercase String Transformation
   *
   * This function transforms a given string to uppercase letters
   * 
   * @param str The input string
   *
   * @endif
   */
  void toUpper(std::string& str);

  /*!
   * @if jp
   * @brief ��ʸ���ؤ��Ѵ�
   *
   * Ϳ���餁E�ʸ�����ʸ�����Ѵ�
   *
   * @param str ����ʸ��΁E   *
   * @else
   * @brief Lowercase String Transformation
   *
   * This function transforms a given string to lowercase letters
   * 
   * @param str The input string
   *
   * @endif
   */
  void toLower(std::string& str);

  /*!
   * @if jp
   * @brief ���ϥ��ȥ꡼�फ��E���ɤ߹���E   *
   * ���ϥ��ȥ꡼�फ��E���ɤ߹��ࡣ
   * ���ϥ��ȥ꡼��Ϥβ��ԥ����ɤ�UNIX, Windows�β��ԥ����ɤΤ�����E���
   * �⤷���Ϻ��ߤ��Ƥ��Ƥ�褤��
   *
   * @param istr ���ϥ��ȥ꡼��E   * @param line �ɤ߹����ʸ������Ǽ����Eѿ�E   *
   * @return ����ʸ����E��ɤ߹����ʸ�����Ĺ��
   *
   * @else
   * @brief Read a line from input stream
   *
   * This function reads a line from input stream.
   * UNIX, Windows or mixed line feed code is acceptable.
   *
   * @param istr The input stream.
   * @param line The output variable to store string to be read.
   *
   * @return The length of read string except line feed character.
   *
   * @endif
   */
  int getlinePortable(std::istream& istr, std::string& line);
  
  /*!
   * @if jp
   * @brief ʸ���󤬥��������פ���EƤ���E�Ƚ�Ǥ���E   *
   * ���ꤵ��E�ʸ�������������פ���EƤ���E��ɤ�����Ƚ�Ǥ���E�
   *
   * @param str ���������פ���EƤ���E��ɤ���Ƚ�Ǥ���E�����ޤ�ʸ��΁E   * @param pos ���������פ���EƤ���E��ɤ���Ƚ�Ǥ���E����ΰ���
   *
   * @return ���ꤷ��ʸ�������������פ���EƤ���E� true, ����Eʳ��� false
   *
   * @else
   * @brief Check whether the character is escaped or not
   *
   * Check whether the specified character is escaped or not
   *
   * @param str The string that includes the character to be investigated.
   * @param pos The position of the character to be investigated.
   *
   * @return True if the specified character is escaped, else False.
   *
   * @endif
   */
  bool isEscaped(const std::string& str, std::string::size_type pos);
  
  /*!
   * @if jp
   * @brief ʸ����򥨥������פ���E   *
   * ����ʸ���򥨥������ץ������󥹤��Ѵ�����E�<br>
   * HT -> "\t" <br>
   * LF -> "\n" <br>
   * CR -> "\r" <br>
   * FF -> "\f" <br>
   * ���󥰥�E������ȡ����֥�E������ȤˤĤ��ƤϤȤ��˽����Ϥ��ʤ���
   *
   * @param str ���������׽����о�ʸ��΁E   *
   * @return ���������׽�����E�ʸ��΁E   *
   * @else
   *
   * @brief Escape string
   *
   * The following characters are converted. <br>
   * HT -> "\t" <br>
   * LF -> "\n" <br>
   * CR -> "\r" <br>
   * FF -> "\f" <br>
   * Single quote and double quote are not processed.
   *
   * @param str The target string for the escape
   *
   * @return Result string of the escape
   *
   * @endif
   */
  std::string escape(const std::string str);
  
  /*!
   * @if jp
   * @brief ʸ����Υ��������פ��᤹
   *
   * ���Υ��������ץ������󥹤�ʸ�����Ѵ�����E�<br>
   * "\t" -> HT <br>
   * "\n" -> LF <br>
   * "\r" -> CR <br>
   * "\f" -> FF <br>
   * "\"" -> "  <br>
   * "\'" -> '  <br>
   * �����������׽����δ����ʵ��Ѵ��ˤϤʤäƤ��ʤ����ᡢ���դ�ɬ�ס�
   *
   * @param str ���󥨥������׽����о�ʸ��΁E   *
   * @return ���󥨥������׽�����E�ʸ��΁E   *
   * @else
   *
   * @brief Unescape string
   *
   * The following characters are converted. <br>
   * "\t" -> HT <br>
   * "\n" -> LF <br>
   * "\r" -> CR <br>
   * "\f" -> FF <br>
   * "\"" -> "  <br>
   * "\'" -> '  <br>
   * Note: This is not complete inversion of the escape processing.
   *
   * @param str The target string for the unescape
   *
   * @return Result string of the unescape
   *
   * @endif
   */
  std::string unescape(const std::string str);

  /*!
   * @if jp
   * @brief ʸ����ζ���ʸ����E�E���E   *
   * Ϳ���餁E�ʸ����ζ���ʸ����E�E���E�
   * ����ʸ���Ȥ��ư����Τ�' '(���ڡ���)��'\\t'(����)��
   *
   * @param str ����ʸ����E�E���ʸ��΁E   *
   * @else
   * @brief Erase blank characters of string
   *
   * Erase blank characters that exist at the head of the given string.
   * Space ' 'and tab '\\t' are supported as the blank character.
   *
   * @param str The target blank characters of string for the erase
   *
   * @endif
   */
  void eraseBlank(std::string& str);

  /*!
   * @if jp
   * @brief ʸ�������Ƭ�ζ���ʸ����E�E���E   *
   * Ϳ���餁E�ʸ�������Ƭ��¸�ߤ���E���ʸ����E�E���E�
   * ����ʸ���Ȥ��ư����Τ�' '(���ڡ���)��'\\t'(����)��
   *
   * @param str ��Ƭ����ʸ����E�E���ʸ��΁E   *
   * @else
   * @brief Erase the head blank characters of string
   *
   * Erase the blank characters that exist at the head of the given string.
   * Space ' 'and tab '\\t' are supported as the blank character.
   *
   * @param str The target head blank characters of string for the erase
   *
   * @endif
   */
  void eraseHeadBlank(std::string& str);
  
  /*!
   * @if jp
   * @brief ʸ����������ζ���ʸ����E�E���E   *
   * Ϳ���餁E�ʸ�����������¸�ߤ���E���ʸ����E�E���E�
   * ����ʸ���Ȥ��ư����Τ�' '(���ڡ���)��'\\t'(����)��
   *
   * @param str ��������ʸ����E�E���ʸ��΁E   *
   * @else
   * @brief Erase the tail blank characters of string
   *
   * Erase the blank characters that exist at the tail of the given
   * string.  Space ' 'and tab '\\t' are supported as the blank
   * character.
   *
   * @param str The target tail blank characters of string for the erase
   *
   * @endif
   */
  void eraseTailBlank(std::string& str);

  /*!
   * @if jp
   * @brief ʸ�������Ƭ�������ζ���ʸ����E�E���E   *
   * Ϳ���餁E�ʸ�������Ƭ�����������¸�ߤ���E���ʸ����E�E���E�
   * ����ʸ���Ȥ��ư����Τ�' '(���ڡ���)��'\\t'(����)��
   *
   * @param str ��Ƭ��������ʸ����E�E���ʸ��΁E   *
   * @else
   * @brief Erase the head blank and the tail blank characters of string
   *
   * Erase the head blank characters and the blank characters that
   * exist at the tail of the given string.  Space ' 'and tab '\\t'
   * are supported as the blank character.
   *
   * @param str The target tail blank characters of string for the erase
   *
   * @endif
   */
  void eraseBothEndsBlank(std::string& str);

  /*!
   * @if jp
   * @brief ʸ���������������E   *
   * Ϳ���餁E�ʸ�������Ƭ�����������¸�ߤ���E���ʸ����E�E���
   * �ѻ��򤹤٤ƾ�ʸ�����Ѵ�����E�
   *
   * @param str �����о�ʸ��΁E   *
   * @else
   * @brief Erase the head/tail blank and replace upper case to lower case
   *
   * Erase the head blank characters and the blank characters that
   * exist at the tail of the given string.  Space ' 'and tab '\\t'
   * are supported as the blank character.
   * And all upper case cahracters are converted into lower case.
   *
   * @param str The target string for the erase
   *
   * @endif
   */
  std::string normalize(std::string& str);
  
  /*!
   * @if jp
   * @brief ʸ������֤�������E   *
   * Ϳ���餁E�ʸ������Ф��ơ����ꤷ��ʸ�����֤�������Ԥ���
   *
   * @param str �֤����������о�ʸ��΁E   * @param from �ִ���ʸ��E   * @param to �ִ���ʸ��E   *
   * @else
   * @brief Replace string
   *
   * Replace the given string with the specified characters.
   *
   * @param str The target characters of string for replacement processing
   * @param from Characters of replacement source
   * @param to Characters of replacement destination
   *
   * @endif
   */
  unsigned int replaceString(std::string& str, const std::string from,
                             const std::string to);
  
  /*!
   * @if jp
   * @brief ʸ�����ʬ��ʸ����ʬ�䤹��E   * 
   * ���ꤵ��E�ʸ�����Ϳ���餁E��ǥ�Eߥ���ʬ�䤹��E�
   *
   * @param input ʬ���о�ʸ��΁E   * @param delimiter ʬ��ʸ��΁E�ǥ�Eߥ�)
   *
   * @return ʸ����ʬ�䷁E̥�E���
   *
   * @else
   * @brief Split string by delimiter
   * 
   * Split the set string by the given delimiter
   *
   * @param input The target characters of string for split
   * @param delimiter Split string (delimiter)
   *
   * @return Split string result list
   *
   * @endif
   */
  vstring split(const std::string& input,
                const std::string& delimiter,
                bool ignore_empty = false);
  
  /*!
   * @if jp
   * @brief Ϳ���餁E�ʸ�����bool�ͤ��Ѵ�����E   * 
   * ���ꤵ��E�ʸ�����trueɽ��ʸ����falseɽ��ʸ�������Ӥ������η�E̤�E   * bool�ͤȤ����֤���
   * ��Ӥη�E̡�trueɽ��ʸ����falseɽ��ʸ����Τɤ���ȤⰁEפ��ʤ���E�ϡ�
   * Ϳ���餁E��ǥե���E��ͤ��֤���
   *
   * @param str Ƚ���о�ʸ��΁E   * @param yes trueɽ��ʸ��΁E   * @param no falseɽ��ʸ��΁E   * @param default_value �ǥե���E���(�ǥե���E���:true)
   * @else
   * @brief Convert given string into bool value
   * 
   * Compare the specified string with the true representation string and
   * the false representation string, and return the result as bool value.
   * If it matches neither the true representation string nor the false
   * representation string as a result of the comparison, the given default
   * value will be return.
   *
   * @param str The target string for investigation
   * @param yes The true representation string
   * @param no The false representation string
   * @param default_value The default value (The default value:true)
   * @endif
   */
  bool toBool(std::string str, std::string yes, std::string no, 
              bool default_value = true);
  /*!
   * @if jp
   * @brief ʸ����E�����ˤ���E����󤬴ޤޤ�E�E��ɤ�����Ƚ�Ǥ���E   * 
   * E�����˥���޶��ڤ�Υ�E��Ȥ�E������õ���о�ʸ�������ꤷ��
   * ����ʸ����E��������˴ޤޤ�E�E���Ƚ�Ǥ���E�
   *
   * @param list �оݥ�E���
   * @param value õ��ʸ��΁E   * @return true: �ޤޤ�E�E�false: �ޤޤ�Eʤ�
   *
   * @else
   * @brief Include if a string is included in string list
   * 
   * if the second argument is included in the comma separated string
   * list of the first argument, This operation returns "true value".
   *
   * @param list The target comma separated string
   * @param value The searched string
   * @return true: included, false: not included
   *
   * @endif
   */
  bool includes(const vstring& list, std::string value,
                bool ignore_case = true);

  /*!
   * @if jp
   * @brief ʸ����E�����ˤ���E����󤬴ޤޤ�E�E��ɤ�����Ƚ�Ǥ���E   * 
   * E�����˥���޶��ڤ�Υ�E��Ȥ�E������õ���о�ʸ�������ꤷ��
   * ����ʸ����E��������˴ޤޤ�E�E���Ƚ�Ǥ���E�
   *
   * @param list �о�ʸ��΁E   * @param value õ��ʸ��΁E   * @return true: �ޤޤ�E�E�false: �ޤޤ�Eʤ�
   *
   * @else
   * @brief Include if a string is included in string list
   * 
   * if the second argument is included in the comma separated string
   * list of the first argument, This operation returns "true value".
   *
   * @param list The target comma separated string
   * @param value The searched string
   * @return true: included, false: not included
   *
   * @endif
   */
  bool includes(const std::string& list, std::string value,
                bool ignore_case = true);
  
  /*!
   * @if jp
   * @brief Ϳ���餁E�ʸ�������Хѥ����ɤ�����Ƚ�Ǥ���E   *
   * Ϳ���餁E�ʸ�������Хѥ�ɽ���Ǥ���E��ɤ�����Ƚ�Ǥ���E�
   * ʸ���󤬰ʲ��ξ�E�ˤ����Хѥ��Ȥ���Ƚ�Ǥ���E�
   *  - ��Ƭʸ����'/' (UNIX�ξ�E�E
   *  - ��Ƭ��ʸ��������Eե��٥åȡ�'/'��'\\' (Windows�ξ�E�E
   *  - ��Ƭ��ʸ����'\\\\' (Windows�ͥåȥ�E����ѥ��ξ�E�E
   *
   * @param str ȽāEо�ʸ��΁E   *
   * @return ���Хѥ�ȽāE�E�
   *
   * @else
   * @brief Investigate whether the given string is absolute path or not
   *
   * Investigate whether the given string is absolute path or not.
   * Investigate it as an absolute path, if the string is as follows:
   *  - The first character '/' (UNIX)
   *  - The first 3 characters are alphabet ��'/'��'\\' (Windows)
   *  - The first 2 characters are '\\\\' (Windows network path)
   *
   * @param str The target string for the investigation
   *
   * @return Investigation result of absolute path
   *
   * @endif
   */
  bool isAbsolutePath(const std::string& str);
  
  /*!
   * @if jp
   * @brief Ϳ���餁E�ʸ����URL���ɤ�����Ƚ�Ǥ���E   *
   * Ϳ���餁E�ʸ����URLɽ�����ɤ�����Ƚ�Ǥ���E�
   * Ϳ���餁E�ʸ������ˡ�'://'�Ȥ���ʸ���󤬴ޤޤ�EƤ���E�E�ˤ�
   * URLɽ���Ȥ���Ƚ�Ǥ���E�
   *
   * @param str ȽāEо�ʸ��΁E   *
   * @return URLȽāE�E�
   *
   * @else
   * @brief Investigate whether the given string is URL or not
   *
   * Investigate whether the given string is URL or not.
   * When the string '://' is included in the given character string,
   * make it of URL representation.
   *
   * @param str The target string for investigation
   *
   * @return URL investigation result
   *
   * @endif
   */
  bool isURL(const std::string& str);
  
  /*!
   * @if jp
   * @brief Ϳ���餁E����֥������Ȥ�std::string���Ѵ�
   *
   * �����ǻ��ꤵ��E����֥������Ȥ�ʸ������Ѵ�����E�
   *
   * @param n �Ѵ��оݥ��֥�������
   *
   * @return ʸ�����Ѵ���E�
   *
   * @else
   * @brief Convert the given object to std::string
   *
   * Convert the object specified by the argument to string.
   *
   * @param n The target object for conversion
   *
   * @return String conversion result
   *
   * @endif
   */
  template <class Printable>
  std::string otos(Printable n)
  {
    std::stringstream str_stream;
    str_stream << n;
    return str_stream.str();
  };
  
  /*!
   * @if jp
   * @brief Ϳ���餁E�std::string�򥪥֥������Ȥ��Ѵ�
   *
   * ������Ϳ���餁E�ʸ�������ꤵ��E����֥������Ȥ��Ѵ�����E�
   *
   * @param val �Ѵ��襪�֥�������
   * @param str �Ѵ���ʸ��΁E   *
   * @return true: ����E false: ����
   *
   * @else
   * @brief Convert the given std::string to object.
   *
   * Convert string given by the argument to specified object.
   *
   * @param val The object of conversion destination
   * @param str String of conversion source
   *
   * @return true: successful, false: failed
   *
   * @endif
   */
  template <typename To>
  bool stringTo(To& val, const char* str)
  {
    if (str == 0) { return false; }

    std::stringstream s;
    if ((s << str).fail()) { return false; }
    if ((s >> val).fail()) { return false; }
    return true;
  }
  
  /*!
   * @if jp
   * @brief Ϳ���餁E�ʸ�����std::string���Ѵ�
   *
   * ������Ϳ���餁E�ʸ�����std::string���Ѵ�����E�
   *
   * @param val �Ѵ���ʸ��΁E   * @param str �Ѵ���ʸ��΁E   *
   * @return true: ����E false: ����
   *
   * @else
   * @brief Convert the given string to std::string.
   *
   * Convert string given by the argument to std::string.
   *
   * @param val String of conversion destination
   * @param str String of conversion source
   *
   * @return true: successful, false: failed
   *
   * @endif
   */
  template<>
  bool stringTo<std::string>(std::string& val, const char* str);

  /*!
   * @if jp
   * @brief Ϳ���餁E�ʸ����E��Ȥ����ʣ��E�E   *
   * ������Ϳ���餁E�ʸ����E��Ȥ����ʣ��E�E�����E��Ȥ��ܮ����E�
   *
   * @param sv ��ǧ��ʸ����E���
   *
   * @return ��ʣ��E�E�����E̥�E���
   *
   * @else
   * @brief Eliminate duplication from the given string list
   *
   * Create a list of eliminating duplication from the string list
   * given by the argument.
   *
   * @param sv The string list for confirmation source
   *
   * @return Eliminating duplication result list
   *
   * @endif
   */
  vstring unique_sv(vstring sv);
  
  /*!
   * @if jp
   * @brief Ϳ���餁E�ʸ����E��Ȥ���CSV������
   *
   * ������Ϳ���餁E�ʸ����E��Ȥγ����Ǥ��¤٤�CSV����������E�
   * ʸ����E��Ȥ����ξ�E�ˤ϶���ʸ�����֤���
   *
   * @param sv CSV�Ѵ��о�ʸ����E���
   *
   * @return CSV�Ѵ���E�ʸ��΁E   *
   * @else
   * @brief Create CSV file from the given string list
   *
   * Create CSV that arranged each element of the character string
   * list given by the argument.
   * If the string list is empty, the null will be returned.
   *
   * @param sv The target string list for creating CSV
   *
   * @return String of CSV creating result
   *
   * @endif
   */
  std::string flatten(vstring sv);
  
  /*!
   * @if jp
   * @brief Ϳ���餁E�ʸ����E��Ȥ������E��Ȥ��Ѵ�
   *
   * ������Ϳ���餁E�ʸ����E��Ȥγ�����������'\\0'��ä���������E���
   * ���Ѵ�����E�
   *
   * @param args �Ѵ��о�ʸ����E���
   *
   * @return �����Ѵ���E�ʸ��΁E   *
   * @else
   * @brief Convert the given string list into the argument list
   *
   * Convert the string list into the argument list by adding '\\0' to
   * each element at the end of the string list given by the argument
   *
   * @param args The target string list for conversion
   *
   * @return String of argument conversion result
   *
   * @endif
   */
  char** toArgv(const vstring& args); 


  /*!
   * @if jp
   * @brief ���ꤵ��E��񼰤��Ѵ�
   *
   * ������Ϳ���餁E��񼰤��Ѵ������֤���
   *
   * @param fmt ��
   *
   * @return �Ѵ���E�ʸ��΁E   *
   * @else
   * @brief Convert it into a format given with an argumen
   *
   * Convert it into a format given with an argument and return it.
   *
   * @param fmt Format
   *
   * @return String of conversion result
   *
   * @endif
   */
