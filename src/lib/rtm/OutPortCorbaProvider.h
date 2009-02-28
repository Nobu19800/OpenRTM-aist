// -*- C++ -*-
/*!
 * @file  OutPortCorbaProvider.h
 * @brief OutPortCorbaProvider class
 * @date  $Date: 2008-01-14 07:52:40 $
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

#ifndef OutPortCorbaProvider_h
#define OutPortCorbaProvider_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/OutPortProvider.h>
#include <rtm/CORBA_SeqUtil.h>

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortCorbaProvider
   * @brief OutPortCorbaProvider ���饹
   *
   * �̿����ʤ� CORBA �����Ѥ������ϥݡ��ȥץ�Х������μ������饹��
   *
   * @param DataType �����ץ�Х����˳�����Ƥ��Хåե����ݻ�����ǡ�����
   *
   * @since 0.4.0
   *
   * @else
   * @class OutPortCorbaProvider
   * @brief OutPortCorbaProvider class
   *
   * This is an implementation class of OutPort Provider that uses 
   * CORBA for mean of communication.
   *
   * @param DataType Data type held by the buffer that is assigned to this 
   *        provider
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  class OutPortCorbaProvider
    : public OutPortProvider,
      public virtual POA_RTC::OutPortAny,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param buffer �����ץ�Х����˳�����Ƥ�Хåե����֥�������
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param buffer Buffer object that is assigned to this provider
     *
     * @endif
     */
    OutPortCorbaProvider(BufferBase<DataType>& buffer)
      : m_buffer(buffer)
    {
      CORBA::Any any_var;
      DataType   tmp_var;
      any_var <<= tmp_var;
      
      // PortProfile setting
      setDataType(any_var.type()->name());
      setInterfaceType("CORBA_Any");
      setDataFlowType("Push, Pull");
      setSubscriptionType("Flush, New, Periodic");
      
      // ConnectorProfile setting
      m_objref = this->_this();
      CORBA_SeqUtil::push_back(m_properties,
			       NVUtil::newNV("dataport.corba_any.outport_ref",
					     m_objref));
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
    virtual ~OutPortCorbaProvider(void)
    {}
    
    /*!
     * @if jp
     * @brief �Хåե�����ǡ������������
     *
     * ���ꤵ�줿�����Хåե�����ǡ�����������롣
     *
     * @return �����ǡ���
     *
     * @else
     * @brief Get data from the buffer
     *
     * Get data from the internal buffer.
     *
     * @return Data got from the buffer.
     *
     * @endif
     */
    CORBA::Any* get()
      throw (CORBA::SystemException)
    {
      DataType data;
      m_buffer.read(data);
      m_tmp <<= data;
      return new CORBA::Any(m_tmp);
    }
    
  private:
    BufferBase<DataType>& m_buffer;
    OutPortAny_var m_objref;
    CORBA::Any m_tmp;
  };
};     // namespace RTC
#endif // OutPortCorbaProvider_h
