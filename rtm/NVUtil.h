// -*- C++ -*-
/*!
 * @file NVUtil.h
 * @brief NameValue and NVList utility functions
 * @date $Date: 2006-11-10 04:32:46 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NVUtil.h,v 1.1 2006-11-10 04:32:46 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */
#include <string>
#include <rtm/idl/SDOPackageSkel.h>
#include <rtm/Properties.h>

namespace NVUtil
{
  /*!
   * @if jp
   *
   * @brief NameValue $B$r@8@.$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O(BNameValue$B$r:n@.$9$k!#(B
   * CORBA::Char, CORBA::Boolean, CORBA::Octet $B$O:n@.$G$-$J$$!#(B
   * $B$3$l$i$NCM$O(B newNVChar(), newNVBool(), newNVOctet() $B$G:n@.$9$k!#(B
   *
   * @param name NameValue $B$N(B name
   * @param value NameValue $B$N(B value
   * @return NameValue
   *
   * @else
   *
   * @brief Create NameVale
   *
   * This operation creates NameVale.
   * CORBA::Char, CORBA::Boolean, CORBA::Octet creation is not supported.
   * These type of NameValue should be created by using 
   * newNVChar(), newNVBool(), newNVOctet() functions.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   * @return NameValue
   *
   * @endif
   */
  template <class Value>
  SDOPackage::NameValue newNV(const char* name, Value value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= value;
    return nv;
  }


  /*!
   * @if jp
   *
   * @brief value $B$,(B CORBA::string $B$N(B NameValue $B$r@8@.$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O(Bf value $B$,(B CORBA::string $B$N(B NameValue$B$r:n@.$9$k!#(B
   *
   * @param name NameValue $B$N(B name
   * @param value NameValue $B$N(B value
   * @return NameValue
   *
   * @else
   *
   * @brief Create CORBA::string value type NameVale
   *
   * This operation creates CORBA::string value type NameVale.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   * @return NameValue
   *
   * @endif
   */
  template <>
  SDOPackage::NameValue newNV(const char* name, const char* value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= value;
    return nv;
  }
    

  /*!
   * @if jp
   *
   * @brief value $B$,(B CORBA::Char $B$N(B NameValue $B$r@8@.$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O(Bf value $B$,(B CORBA::Char $B$N(B NameValue$B$r:n@.$9$k!#(B
   *
   * @param name NameValue $B$N(B name
   * @param value NameValue $B$N(B value
   * @return NameValue
   *
   * @else
   *
   * @brief Create CORBA::Char value type NameVale
   *
   * This operation creates CORBA::Char value type NameVale.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVChar(const char* name, const CORBA::Char value);
    

  /*!
   * @if jp
   *
   * @brief value $B$,(B CORBA::Boolean $B$N(B NameValue $B$r@8@.$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O(Bf value $B$,(B CORBA::Boolean $B$N(B NameValue$B$r:n@.$9$k!#(B
   *
   * @param name NameValue $B$N(B name
   * @param value NameValue $B$N(B value
   * @return NameValue
   *
   * @else
   *
   * @brief Create CORBA::Boolean value type NameVale
   *
   * This operation creates CORBA::Boolean value type NameVale.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVBool(const char* name,
				  const CORBA::Boolean value);

    
  /*!
   * @if jp
   *
   * @brief value $B$,(B CORBA::Octet $B$N(B NameValue $B$r@8@.$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O(Bf value $B$,(B CORBA::Octet $B$N(B NameValue$B$r:n@.$9$k!#(B
   *
   * @param name NameValue $B$N(B name
   * @param value NameValue $B$N(B value
   * @return NameValue
   *
   * @else
   *
   * @brief Create CORBA::Octet value type NameVale
   *
   * This operation creates CORBA::Octet value type NameVale.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVOctet(const char* name, const CORBA::Octet value);


  /*!
   * @if jp
   *
   * @brief Properties $B$r(B NVList $B$X%3%T!<$9$k(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O(B Properties $B$r(B NVList $B$X%3%T!<$9$k!#(B
   * NVList $B$N(B value $B$OA4$F(B CORBA::string $B7?$H$7$F%3%T!<$9$k!#(B
   *
   * @param nv Properties $B$NCM$r3JG<$9$k(B NVList
   * @param prop $B%3%T!<85$N(B Properties
   *
   * @else
   *
   * @brief Copy to NVList from Proeprties
   *
   * This operation copies Properties to NVList.
   * Created NVList's values are CORBA::string.
   *
   * @param nv NVList to store Properties values
   * @param prop Properties that is copies from
   *
   * @endif
   */
  void copy(SDOPackage::NVList& nv, RTC::Properties& prop);


  /*!
   * @if jp
   *
   * @brief NVList $B$+$i(B name $B$G;XDj$5$l$?(B value $B$rJV$9(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O(B name $B$G;XDj$5$l$?(B value $B$r(B Any $B7?$GJV$9!#(B
   *
   * @param nv $B8!:wBP>]$N(B NVList
   * @param name $B8!:w$9$kL>A0(B
   *
   * @else
   *
   * @brief Get value in NVList specified by name
   *
   * This operation returns Any type of value specified by name.
   * Created NVList's values are CORBA::string.
   *
   * @param nv NVList to be searched
   * @param prop name to seartch in NVList
   *
   * @endif
   */
  const CORBA::Any& find(SDOPackage::NVList& nv, const char* name);


  /*!
   * @if jp
   *
   * @brief $B;XDj$5$l$?(B name $B$N(B value $B$N7?$,(B string $B$G$"$k$+$I$&$+!)(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O(B name $B$G;XDj$5$l$?(B value $B$N7?$,(B CORBA::string
   * $B$+$I$&$+$r(B bool $BCM$GJV$9!#(B
   *
   * @param nv $B8!:wBP>]$N(B NVList
   * @param name $B8!:w$9$kL>A0(B
   *
   * @else
   *
   * @brief Whether the name of NVList's value is CORBA::string
   *
   * This operation returns boolean value whether the name of NVList's value
   * is CORBA::string.
   *
   * @param nv NVList to be searched
   * @param prop name to seartch in NVList
   *
   * @endif
   */
  bool isString(SDOPackage::NVList& nv, const char* name);

  /*!
   * @if jp
   *
   * @brief $B;XDj$5$l$?(B name $B$N(B NVList $B$r(B string $B$H$7$FJV$9!#(B
   *
   * $B$3$N%*%Z%l!<%7%g%s$O(B name $B$G;XDj$5$l$?(B NVList $B$NCM$r(B string $B$GJV$9!#(B
   * $B$b$7!"(Bname $B$G;XDj$7$?(B value $B$NCM$,(B CORBA::string $B$G$J$1$l$P!"(B
   * $B6u$NJ8;zNs$N(Bstring$B$rJV$9!#(B
   *
   * @param nv $B8!:wBP>]$N(B NVList
   * @param name $B8!:w$9$kL>A0(B
   * @return name $B$KBP1~$9$kCM$N(Bstring$B7?$NCM(B
   *
   * @else
   *
   * @brief Get string value in NVList specified by name
   *
   * This operation returns string value in NVList specified by name.
   * If the value in NVList specified by name is not CORBA::string type
   * this operation returns empty string value.
   *
   * @param nv NVList to be searched
   * @param name name to to serach
   * @return string value named by name
   *
   * @endif
   */
  std::string toString(SDOPackage::NVList& nv, const char* name);

};
