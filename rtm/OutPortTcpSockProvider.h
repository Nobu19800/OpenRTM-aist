// -*- C++ -*-
/*!
 * @file  OutPortTcpSockProvider.h
 * @brief OutPortTcpSockProvider class
 * @date  $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPortTcpSockProvider.h,v 1.1.2.2 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.2.1  2007/10/06 12:29:48  n-ando
 * OutPort provider for TCP socket data port.
 *
 */

#ifndef OutPortTcpSockProvider_h
#define OutPortTcpSockProvider_h

#include <rtm/BufferBase.h>
#include <rtm/OutPortProvider.h>


namespace RTC
{
  /*!
   * @if jp
   * @class OutPortTcpSockProvider
   * @brief OutPortTcpSockProvider ���饹
   *
   * �̿����ʤ� TCP �����åȤ����Ѥ������ϥݡ��ȥץ�Х������μ������饹
   *
   * @param DataType �����ץ�Х����˳�����Ƥ��Хåե����ݻ�����ǡ�����
   *
   * @else
   * @class OutPortTcpSockProvider
   * @brief OutPortTcpSockProvider class
   * @endif
   */
  template <class DataType>
  class OutPortTcpSockProvider
    : public OutPortProvider
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     * �ݡ��ȥץ�ѥƥ��˰ʲ��ι��ܤ����ꤹ�롣
     * �����󥿡��ե����������� : TCP_Any
     * ���ǡ����ե������� : Push, Pull
     * �����֥�����ץ���󥿥��� : Flush, New, Periodic
     *
     * @param buffer �����ץ�Х����˳�����Ƥ�Хåե����֥�������
     *
     * @else
     * @brief Constructor
     * @endif
     */
    OutPortTcpSockProvider(BufferBase<DataType>& buffer)
      : m_buffer(buffer)
    {
      CORBA::Any any_var;
      DataType   tmp_var;
      any_var <<= tmp_var;
      
      // PortProfile setting
      setDataType(any_var.type()->name());
      setInterfaceType("TCP_Any");
      setDataFlowType("Push, Pull");
      setSubscriptionType("Flush, New, Periodic");
      
      // ConnectorProfile setting
      //      m_objref = this->_this();
      //      CORBA_SeqUtil::push_back(m_properties,
      //	       NVUtil::newNV("dataport.corba_any.outport_ref",
      //		     m_objref));
    }
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~OutPortTcpSockProvider()
    {}
    
    /*
      CORBA::Any* get()
      {
      DataType data;
      CORBA::Any_var tmp = new CORBA::Any();
      m_buffer.read(data);
      tmp <<= data;
      return tmp._retn();
      }
    */
    
  private:
    BufferBase<DataType>& m_buffer;
    //    OutPortAny_var m_objref;
  };
};     // namespace RTC
#endif // OutPortTcpSockProvider_h
