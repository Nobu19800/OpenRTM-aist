// -*- C++ -*-
/*!
 * @file NVUtil.h
 * @brief NameValue and NVList utility functions
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NVUtil.h,v 1.6.2.1 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6  2007/04/23 04:54:32  n-ando
 * Conversion functions between Properties and NVList were added.
 *
 * Revision 1.5  2007/01/12 14:33:57  n-ando
 * The dump() function was added to dump NVList entries.
 *
 * Revision 1.4  2007/01/06 17:55:35  n-ando
 * toProperties()'s argument was changed to const.
 * Some functions were added.
 * - isStringValue()
 * - appendStringValue()
 * - append()
 *
 * Revision 1.3  2006/11/27 09:54:48  n-ando
 * Conversion function from NVList to Properties: toProperties() was added.
 *
 * Revision 1.2  2006/11/10 04:46:15  n-ando
 * Kanji-code was changed to EUC.
 *
 * Revision 1.1  2006/11/10 04:32:46  n-ando
 * NVUtil is SDOPackage::NVList utility.
 *
 *
 */

#ifndef NVUtil_h
#define NVUtil_h

#include <string>
#include <iostream>
#include <rtm/idl/SDOPackageSkel.h>
#include <rtm/Properties.h>

/*!
 * @if jp
 * @namespace NVUtil
 *
 * @brief NameValue �ѥ桼�ƥ���ƥ�
 *
 * @else
 *
 * @namespace NVUtil
 *
 * @endif
 */
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
   *
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
   *
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
  
  /***
   * @if jp
   *
   * @brief value �� CORBA::string �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::string �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
   *
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
   *
   * @return NameValue
   *
   * @endif
   */
  /*
    template <>
    SDOPackage::NameValue newNV(const char* name, const char* value)
    {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= value;
    return nv;
    }
  */ 
  
  /*!
   * @if jp
   *
   * @brief value �� CORBA::Char �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::Char �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
   *
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
   *
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
   *
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
   *
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
   *
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
   *
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVOctet(const char* name, const CORBA::Octet value);
  
  /*!
   * @if jp
   *
   * @brief value �� CORBA::Any �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::Any �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
   *
   * @return NameValue
   *
   * @else
   *
   * @brief Create CORBA::Any value type NameVale
   *
   * This operation creates CORBA::any value type NameVale.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   *
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVAny(const char* name, const CORBA::Any& value);
  
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
  void copyFromProperties(SDOPackage::NVList& nv, const RTC::Properties& prop);
  
  /*!
   * @if jp
   *
   * @brief NVList �� Properties �إ��ԡ�����
   *
   * ���Υ��ڥ졼������ NVList �� Properties �إ��ԡ����롣
   *
   * @param prop NVList ���ͤ��Ǽ���� Properties
   * @param nv ���ԡ����� NVList
   *
   * @else
   *
   * @brief Copy to Proeprties from NVList
   *
   * This operation copies NVList to Properties.
   *
   * @param prop Properties to store NVList values
   * @param nv NVList that is copies from
   *
   * @endif
   */
  void copyToProperties(RTC::Properties& prop, const SDOPackage::NVList& nv);
  
  /*!
   * @if jp
   *
   * @brief NVList �� Properties ���Ѵ�����
   *
   * ���Υ��ڥ졼������ NVList �� Properties ���Ѵ����롣
   *
   * @param nv �Ѵ����� NVList
   *
   * @return �Ѵ����Property
   *
   * @else
   *
   * @endif
   */
  RTC::Properties toProperties(const SDOPackage::NVList& nv);
  
  /*!
   * @if jp
   *
   * @brief NVList ���� name �ǻ��ꤵ�줿 value ���֤�
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿 value �� Any �����֤���
   * ���ꤷ��̾�Τ����Ǥ�¸�ߤ��ʤ������㳰��ȯ�������롣
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
   *
   * @return �������
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
  const CORBA::Any& find(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief name �ǻ��ꤵ�줿���ǤΥ���ǥå������֤�
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿���Ǥ���Ǽ����Ƥ�����֤�
   * ����ǥå������֤���
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
   *
   * @return �����оݤΥ���ǥå���
   *
   * @else
   *
   * @endif
   */
  const CORBA::Long find_index(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief ���ꤵ�줿 name �� value �η��� string �Ǥ��뤫���ڤ���
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿 value �η��� CORBA::string
   * ���ɤ����� bool �ͤ��֤���
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
   *
   * @return string���ڷ��(string:true������ʳ�:false)
   *
   * @else
   *
   * @endif
   */
  bool isString(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief ���ꤵ�줿 name �� value �η������ꤷ��ʸ����Ȱ��פ��뤫���ڤ���
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿 value �η��� CORBA::string
   * ���ɤ�����Ƚ�Ǥ���  CORBA::string �Ǥ�����ˤϻ��ꤷ��ʸ����Ȱ��פ��뤫
   * ��bool �ͤ��֤���
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
   * @param value ����о�ʸ����
   *
   * @return ���ڷ��(ʸ����Ȱ���:true�������:false)
   *
   * @else
   *
   * @endif
   */
  bool isStringValue(const SDOPackage::NVList& nv, const char* name,
		     const char* value);
  
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
   *
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
   *
   * @return string value named by name
   *
   * @endif
   */
  std::string toString(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief ���ꤵ�줿ʸ����� NVList �����Ǥ��ɲä��롣
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿���Ǥ� value �ǻ��ꤵ�줿ʸ�����
   * �ɲä��롣
   * name �ǻ��ꤷ�����Ǥ˴��� value ���ͤ����ꤵ��Ƥ�����ˤϲ��⤷�ʤ���
   * name �ǻ��ꤷ�����Ǥ� value ���ͤ����ꤵ��Ƥ��ʤ����ϡ� ","���ڤ��
   * value ���ͤ��ɲä��롣
   * ���ꤵ�줿�ͤ����ꤹ�롣
   * name �ǻ��ꤷ�����Ǥ�¸�ߤ��ʤ����ϡ� NVList �κǸ�˿��������Ǥ��ɲä���
   * ���ꤵ�줿�ͤ����ꤹ�롣
   *
   * @param nv �����оݤ� NVList
   * @param name �ɲ��о�����̾
   * @param value �ɲä���ʸ����
   *
   * @return �ɲ������
   *
   * @else
   *
   * @endif
   */
  bool appendStringValue(SDOPackage::NVList& nv, const char* name,
			 const char* value);
  
  /*!
   * @if jp
   *
   * @brief NVList �����Ǥ��ɲä��롣
   *
   * ���Υ��ڥ졼������ dest �ǻ��ꤵ�줿 NVList �� src �ǻ��ꤵ�줿���Ǥ�
   * �ɲä��롣
   *
   * @param dest �ɲä���� NVList
   * @param src �ɲä��� NVList
   *
   * @else
   *
   * @endif
   */
  void append(SDOPackage::NVList& dest, const SDOPackage::NVList& src);
  
  /*!
   * @if jp
   *
   * @brief NVList �����ꤵ��Ƥ������Ƥ�ʸ����Ȥ��ƽ��Ϥ��롣
   *
   * ���ꤵ�줿 NVList �����ꤵ�줿���Ƥ�ʸ����Ȥ��ƽ��Ϥ��롣
   * �ʤ������ꤵ��Ƥ������Ǥ�ʸ���󷿰ʳ��ξ��ˤϡ����λ�(ʸ����ǤϤʤ�)��
   * ���Ϥ��롣
   *
   * @param nv �����о� NVList
   *
   * @else
   *
   * @endif
   */
  void dump(SDOPackage::NVList& nv);
};
#endif // NVUtil_h
