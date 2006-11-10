// -*- C++ -*-
/*!
 * @file NVUtil.h
 * @brief NameValue and NVList utility functions
 * @date $Date: 2006-11-10 04:46:15 $
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
 * $Id: NVUtil.h,v 1.2 2006-11-10 04:46:15 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/10 04:32:46  n-ando
 * NVUtil is SDOPackage::NVList utility.
 *
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
   * @brief NameValue ����������
   *
   * ���Υ��ڥ졼������NameValue��������롣
   * CORBA::Char, CORBA::Boolean, CORBA::Octet �Ϻ����Ǥ��ʤ���
   * �������ͤ� newNVChar(), newNVBool(), newNVOctet() �Ǻ������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
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
   * @brief value �� CORBA::string �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::string �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
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
   * @brief value �� CORBA::Char �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::Char �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
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
   * @brief value �� CORBA::Boolean �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::Boolean �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
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
   * @brief value �� CORBA::Octet �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::Octet �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
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
   * @brief Properties �� NVList �إ��ԡ�����
   *
   * ���Υ��ڥ졼������ Properties �� NVList �إ��ԡ����롣
   * NVList �� value ������ CORBA::string ���Ȥ��ƥ��ԡ����롣
   *
   * @param nv Properties ���ͤ��Ǽ���� NVList
   * @param prop ���ԡ����� Properties
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
   * @brief NVList ���� name �ǻ��ꤵ�줿 value ���֤�
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿 value �� Any �����֤���
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
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
   * @brief ���ꤵ�줿 name �� value �η��� string �Ǥ��뤫�ɤ�����
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿 value �η��� CORBA::string
   * ���ɤ����� bool �ͤ��֤���
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
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
   * @brief ���ꤵ�줿 name �� NVList �� string �Ȥ����֤���
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿 NVList ���ͤ� string ���֤���
   * �⤷��name �ǻ��ꤷ�� value ���ͤ� CORBA::string �Ǥʤ���С�
   * ����ʸ�����string���֤���
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
   * @return name ���б������ͤ�string������
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
