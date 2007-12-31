// -*- C++ -*-
/*!
 * @file  InPortCorbaProvider.h
 * @brief InPortCorbaProvider class
 * @date  $Date: 2007-12-31 03:08:03 $
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
 * $Id: InPortCorbaProvider.h,v 1.4.4.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2007/01/21 09:48:08  n-ando
 * A method to advertise interface profile was changed.
 *
 * Revision 1.3  2007/01/14 23:01:47  n-ando
 * Now object reference is duplicate to set property.
 *
 * Revision 1.2  2007/01/06 17:52:54  n-ando
 * Interface and its profile publish functions (publishInterfaceProfile()
 * and publishInterface()) are added.
 *
 * Revision 1.1  2006/12/02 18:41:02  n-ando
 * InPortCorbaProvider class is an implementation of InPortAny.
 *
 */

#ifndef InPortCorbaProvider_h
#define InPortCorbaProvider_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>

namespace RTC
{
  /*!
   * @if jp
   * @class InPortCorbaProvider
   * @brief InPortCorbaProvider ���饹
   *
   * �̿����ʤ� CORBA �����Ѥ������ϥݡ��ȥץ�Х������μ������饹��
   *
   * @param DataType �����ץ�Х����˳�����Ƥ��Хåե����ݻ�����ǡ�����
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortCorbaProvider
   * @brief InPortCorbaProvider class
   * @endif
   */
  template <class DataType>
  class InPortCorbaProvider
    : public InPortProvider,
      public virtual POA_RTC::InPortAny,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     * �ݡ��ȥץ�ѥƥ��˰ʲ��ι��ܤ����ꤹ�롣
     * �����󥿡��ե����������� : CORBA_Any
     * ���ǡ����ե������� : Push, Pull
     * �����֥�����ץ���󥿥��� : Any
     *
     * @param buffer �����ץ�Х����˳�����Ƥ�Хåե����֥�������
     *
     * @else
     * @brief Constructor
     * @endif
     */
    InPortCorbaProvider(BufferBase<DataType>& buffer)
      : m_buffer(buffer)
    {
      CORBA::Any any_var;
      DataType   tmp_var;
      any_var <<= tmp_var;
      
      // PortProfile setting
      setDataType(any_var.type()->name());
      setInterfaceType("CORBA_Any");
      setDataFlowType("Push, Pull");
      setSubscriptionType("Any");
      
      // ConnectorProfile setting
      m_objref = this->_this();
      //      CORBA_SeqUtil::push_back(m_properties,
      //	       NVUtil::newNV("dataport.corba_any.inport_ref",
      //		     RTC::InPortAny::_duplicate(m_objref)));
    }
    
    /*!
     * @if jp
     * @brief Interface������������
     *
     * Interface�����������롣
     *
     * @param prop Interface�����������ץ�ѥƥ�
     *
     * @else
     *
     * @endif
     */
    void publishInterface(SDOPackage::NVList& prop)
    {
      if (!NVUtil::isStringValue(prop,
				 "dataport.interface_type",
				 "CORBA_Any"))
	{
	  return;
	}
      SDOPackage::NVList nv(m_properties);
      CORBA_SeqUtil::push_back(nv,
			       NVUtil::newNV("dataport.corba_any.inport_ref",
					     RTC::InPortAny::_duplicate(m_objref)));
      
      NVUtil::append(prop, nv);
    }
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortCorbaProvider()
    {
    }
    
    /*!
     * @if jp
     * @brief �Хåե��˥ǡ�����񤭹���
     *
     * ���ꤵ�줿�Хåե��˥ǡ�����񤭹��ࡣ
     *
     * @param data ����оݥǡ���
     *
     * @else
     *
     * @endif
     */
    virtual void put(const CORBA::Any& data)
    {
      DataType* tmp;
      if (data >>= tmp)
	{
	  m_buffer.write(*tmp);
	}
      return;
    }
    
  private:
    BufferBase<DataType>& m_buffer;
    RTC::InPortAny_var m_objref;
  };
};     // namespace RTC
#endif // InPortCorbaProvider_h

