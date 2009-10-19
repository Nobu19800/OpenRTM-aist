// -*- C++ -*-
/*!
 * @file  InPortCorbaProvider.h
 * @brief InPortCorbaProvider class
 * @date  $Date: 2008-01-14 07:49:59 $
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
 * $Id$
 *
 */

#ifndef InPortCorbaProvider_h
#define InPortCorbaProvider_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/Manager.h>

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

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
   *
   * This is an implementation class of the input port Provider 
   * that uses CORBA for means of communication.
   *
   * @param DataType Data type held by the buffer that attached 
   *                 to this provider.
   *
   * @since 0.4.0
   *
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
     *  - ���󥿡��ե����������� : CORBA_Any
     *  - �ǡ����ե������� : Push, Pull
     *  - ���֥�����ץ���󥿥��� : Any
     *
     * @param buffer �����ץ�Х����˳�����Ƥ�Хåե����֥�������
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     * Set the following items to port properties
     *  - Interface type : CORBA_Any
     *  - Data flow type : Push, Pull
     *  - Subscription type : Any
     *
     * @param buffer Buffer object that is attached to this provider
     *
     * @endif
     */
    InPortCorbaProvider(BufferBase<DataType>& buffer)
      : InPortProvider(), m_buffer(buffer)
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

      // set InPort's reference
      CORBA::ORB_ptr orb = ::RTC::Manager::instance().getORB();
      CORBA::String_var ior = orb->object_to_string(m_objref.in());
      CORBA_SeqUtil::
        push_back(m_properties,
                  NVUtil::newNV("dataport.corba_cdr.inport_ior", ior));
      CORBA_SeqUtil::
        push_back(m_properties,
                  NVUtil::newNV("dataport.corba_cdr.inport_ref", m_objref));
    }
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~InPortCorbaProvider(void)
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
     * @brief Write data into the buffer
     *
     * Write data into the specified buffer.
     *
     * @param data The target data for writing
     *
     * @endif
     */
    virtual void put(const CORBA::Any& data)
      throw (CORBA::SystemException)
    {
      RTC_PARANOID(("put()"));
      const DataType* tmp;
      if (data >>= tmp)
	{
	  m_buffer.write(*tmp);
	}
      return;
    }
    
  private:
    BufferBase<DataType>& m_buffer;
    RTC::InPortAny_var m_objref;
  };  // class InPortCorbaProvider
};     // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // InPortCorbaProvider_h

