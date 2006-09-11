// -*- C++ -*-
/*!
 * @file Properties.cpp
 * @brief Property list class (derived from Java Properties)
 * @date $Date: 2006-09-11 18:09:42 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Properties.cpp,v 1.1 2006-09-11 18:09:42 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include <iostream>
#include "rtm/Properties.h"

/*!
 * @if jp
 * @brief $B%3%s%9%H%i%/%?(B
 * @else
 * @brief Constructor
 * @endif
 */
Properties::Properties(const std::map<std::string, std::string>& defaults)
{
  m_defaults = defaults;
  
  Itr it    (m_defaults.begin());
  Itr it_end(m_defaults.end());
  
  while (it != it_end)
    {
      (*this)[std::string(it->first)];
      ++it;
    }
  
}


/*!
 * @if jp
 * @brief $B%3%s%9%H%i%/%?(B
 * @else
 * @brief Constructor
 * @endif
 */
Properties::Properties(const char* defaults[], long num)
{
  for (long i = 0; i < num && defaults[i][0] != '\0' ; i += 2)
    {
      std::string key(defaults[i]);
      std::string value(defaults[i + 1]);
      
      replaceEscape(key);
      eraseHeadBlank(key);
      eraseTailBlank(key);
      
      replaceEscape(value);
      eraseHeadBlank(value);
      eraseTailBlank(value);
      
      m_defaults[key] = value;
      (*this)[key];
    }
}


/*!
 * @if jp
 * @brief $B%G%9%H%i%/%?(B
 * @else
 * @brief Destructor
 * @endif
 */
Properties::~Properties()
{
};


/*!
 * @if jp
 * @brief $B;XDj$5$l$?%-!<$r;}$D%W%m%Q%F%#$r!"%W%m%Q%F%#%j%9%H$+$iC5$9(B
 * @else
 * @brief Searches for the property with the specified key in this property
 * @endif
 */
std::string Properties::getProperty(const std::string& key)
{
  return getProperty(key, "");
}


/*!
 * @if jp
 * @brief $B;XDj$5$l$?%-!<$r;}$D%W%m%Q%F%#$r!"%W%m%Q%F%#%j%9%H$+$iC5$9(B
 * @else
 * @brief Searches for the property with the specified key in this property
 * @endif
 */
std::string Properties::getProperty(const std::string& key,
				    const std::string& defaultValue)
{
  std::string s((*this)[key]);
  if (s == "")
    {
      std::string defaults;
      defaults = m_defaults[key];
      if (defaults == "")
	return defaultValue;
      else
	return defaults;
    }
  else
    {
      return s;
    }
}


/*!
 * @if jp
 * @brief $B;XDj$5$l$?=PNO%9%H%j!<%`$K!"%W%m%Q%F%#%j%9%H$r=PNO$9$k(B
 * @else
 * @brief Prints this property list out to the specified output stream
 * @endif
 */
void Properties::list(std::ostream& out)
{
  Itr it    (this->begin());
  Itr it_end(this->end());
  
  while (it != it_end)
    {
      std::string key(it->first);
      std::string value;
      std::string line;
      value = getProperty(it->first);
      recoverEscape(key);
      recoverEscape(value);
      line = key + std::string(" = ") + value;
      out << line.c_str() << std::endl;
      ++it;
    }
}


/*!
 * @if jp
 * @brief $BF~NO%9%H%j!<%`$+$i%-!<$HMWAG$,BP$K$J$C$?%W%m%Q%F%#%j%9%H$rFI$_9~$`(B
 * @else
 * @brief Loads property list consists of key:value from input stream
 * @endif
 */
void Properties::load(std::istream& inStream)
{
  std::string pline;
  while(!inStream.eof())
    {
      std::string tmp;
      getline(inStream, tmp);
      
      // Skip comments
      if (tmp[0] == '#' || tmp[0] == '!' || tmp == "")
	continue;  // Skip comments 
      // Erase blank character
      
      eraseHeadBlank(tmp);
      
      std::string key, value;
      splitKeyValue(tmp, key, value);
      replaceEscape(key);
      eraseHeadBlank(key);
      eraseTailBlank(key);
      
      replaceEscape(value);
      eraseHeadBlank(value);
      eraseTailBlank(value);
      
      (*this)[key] = value;
    }
}


/*!
 * @if jp
 * @brief $B%W%m%Q%F%#$N%-!<$N%j%9%H$r(B vector $B$GJV$9(B
 * @else
 * @brief Returns an vector of all the keys in this property
 * @endif
 */
std::vector<std::string> Properties::propertyNames()
{
  std::vector<std::string> names;
  Itr it    (this->begin());
  Itr it_end(this->end());
  
  while (it != it_end)
    {
      names.push_back(it->first);
      ++it;
    }
  return names;
}


/*!
 * @if jp
 * @brief $B%W%m%Q%F%#%j%9%H$r;XDj$5$l$?%9%H%j!<%`$KJ]B8$9$k(B
 * @else
 * @brief Save the properties list to the stream
 * @endif
 */
void Properties::save(std::ostream& out, const std::string& header)
{
  store(out, header);
  return;
}


/*!
 * @if jp
 * @brief Properties $B$K(B value $B$r(B key $B$K$D$$$FEPO?$9$k(B
 * @else
 * @brief Sets a value associated with key in the property list
 * @endif
 */
std::string Properties::setProperty(const std::string& key,
				    const std::string& value)
{
  std::string old_value(getProperty(key));
  (*this)[key] = value;
  return old_value;
}


/*!
 * @if jp
 * @brief $B%W%m%Q%F%#%j%9%H$r=PNO%9%H%j!<%`$XJ]B8$9$k(B
 * @else
 * @brief Stores property list to the output stream
 * @endif
 */
void Properties::store(std::ostream& out, const std::string& header)
{
  Itr it    (this->begin());
  Itr it_end(this->end());
  
  out << "# " << header << std::endl;
  while (it != it_end)
    {
      std::string key(it->first);
      std::string value;
      
      value = getProperty(it->first);
      recoverEscape(key);
      recoverEscape(value);
      out << key << " = " << value << std::endl;
      ++it;
    }
}


void Properties::eraseHeadBlank(std::string& str)
{
  while (str[0] == ' ' || str[0] == '\t') str.erase(0, 1);
}


void Properties::eraseTailBlank(std::string& str)
{
  while (str[str.size() - 1] == ' ' || str[str.size() - 1] == '\t')
    str.erase(str.size() - 1, 1);
}


void Properties::replaceStr(std::string& str, const std::string from,
			    const std::string to)
{
  std::string::size_type pos(0);
  
  while (pos != std::string::npos)
    {
      pos = str.find(from, pos);
      if (pos == std::string::npos) break;
      str.replace(pos, from.size(), to);
      pos += to.size();
    }
}


void Properties::replaceEscape(std::string& str)
{
  replaceStr(str, "\\t", "\t");
  replaceStr(str, "\\n", "\n");
  replaceStr(str, "\\r", "\r");
  replaceStr(str, "\\\\", "\\");
  replaceStr(str, "\\\"", "\"");
  replaceStr(str, "\\\'", "\'");
}


void Properties::recoverEscape(std::string& str)
{
  replaceStr(str, "\t", "\\\t");
  replaceStr(str, "\n", "\\\n");
  replaceStr(str, "\r", "\\\r");
  replaceStr(str, "\\", "\\\\");
  replaceStr(str, "\"", "\\\"");
  replaceStr(str, "\'", "\\\'");
}


void Properties::splitKeyValue(const std::string& str, std::string& key,
			       std::string& value)
{
  std::string::size_type i(0);
  std::string::size_type len(str.size());
  
  while (i < len)
    {
      if (str[i] == ':' || str[i] == '=' || str[i] == ' ')
	{
	  std::string::size_type j;
	  for (j = 0; (i - 1 - j) > 0 && str[i - 1 - j] == '\\'; ++j);
	  // If the number of \ is even, ':', '=' and ' ' are not escaped.
	  if ((j % 2) == 0) break;
	}
      ++i;
    }
  
  key   = str.substr(0, i);
  value = str.substr(i + 2);
  
  return;
}

