// -*- C++ -*-
/*!
 * @file DataInPort.h
 * @brief RTC::Port implementation for Data InPort
 * @date $Date: 2008-01-13 15:06:40 $
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
 * $Id$
 *
 */

#ifndef DataInPort_h
#define DataInPort_h

#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortCorbaProvider.h>
#include <rtm/OutPortCorbaConsumer.h>
#include <rtm/NVUtil.h>
#include <rtm/InPort.h>

#ifdef RTC_SOCK_DATAPORT
#include <rtm/InPortTcpSockProvider.h>
#endif

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RT����ݡ��ͥ��
 *
 * @else
 *
 * @namespace RTC
 *
 * @brief RT-Component
 *
 * @endif
 */
namespace RTC
{
  /*!
   * @if jp
   * @class DataInPort
   * @brief InPort �� Port
   *
   * �ǡ������ϥݡ��Ȥμ������饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class DataInPort
   * @brief Port for InPort
   *
   * This is an implementation class for the data input port.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class DataInPort
    : public virtual PortBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param name �ݡ���̾��
     * @param inport �����ǡ������ϥݡ��Ȥ˴�Ϣ�դ���InPort���֥�������
     *               InPort���֥������Ȥǰ����ǡ��������Хåե������פ���ꤹ��
     * @param prop �ݡ��������ѥץ�ѥƥ�
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port name
     * @param inport InPort object that is associated with this data input port.
     *               Specify also the data type and the buffer type used in 
     *               the InPort object.
     * @param prop Property for setting ports
     *
     * @endif
     */
    template <class DataType, template <class DataType> class Buffer>
//    DataInPort(const char* name, InPort<DataType, Buffer>& inport,
//	       Properties& prop)
    DataInPort(const char* name, InPort<DataType, Buffer>& inport,
	       coil::Properties& prop)
      : PortBase(name)
    {
      // PortProfile::properties ������
      addProperty("port.port_type", "DataInPort");
      
      // CORBA InPort Provider
      m_providers.push_back(new InPortCorbaProvider<DataType>(inport));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
      
      // TCP Socket InPort Provider
#ifdef RTC_SOCK_DATAPORT
      m_providers.push_back(new InPortTcpSockProvider<DataType>(inport, prop));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
#endif
      
      // CORBA OutPort Consumer
      m_consumers.push_back(new OutPortCorbaConsumer<DataType>(inport));
      
      // dummy var
      m_dummy.push_back(1);
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
    virtual ~DataInPort(void);
    
  protected:
    /*!
     * @if jp
     * @brief Interface������������
     *
     * Interface�����������롣
     * ����Port����ͭ���Ƥ���ץ�Х���(Provider)�˴ؤ�������
     * ConnectorProfile#properties���������롣
     *
     * @param connector_profile ���ͥ����ץ�ե�����
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.
     * Assign the Provider information that owned by this port
     * to ConnectorProfile#properties
     *
     * @param connector_profile The connector profile
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interface����³����
     *
     * Interface����³���롣
     * Port����ͭ����Consumer��Ŭ�礹��Provider�˴ؤ������� 
     * ConnectorProfile#properties ������Ф���
     * Consumer��CORBA���֥������Ȼ��Ȥ����ꤹ�롣
     *
     * @param connector_profile ���ͥ������ץ�ե�����
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     * @brief Subscribe to the interface
     *
     * Subscribe to interface.
     * Derive Provider information that matches Consumer owned by the Port 
     * from ConnectorProfile#properties and 
     * set the Consumer to the reference of the CORBA object.
     *
     * @param connector_profile The connector profile
     *
     * @return ReturnCode_t The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interface�ؤ���³��������
     *
     * Interface�ؤ���³�������롣
     * Ϳ����줿ConnectorProfile�˴�Ϣ����Consumer�����ꤵ�줿���Ƥ�Object��
     * ��������³�������롣
     *
     * @param connector_profile ���ͥ������ץ�ե�����
     *
     * @else
     * @brief Disconnect the interface connection
     *
     * Disconnect the interface connection.
     * Release all objects set in Consumer associated with 
     * given ConnectorProfile and unscribe the interface.
     *
     * @param connector_profile The connector profile
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interface������Functor
     *
     * Interface����������¹Ԥ��뤿���Functor��
     *
     * @else
     * @brief Functor to publish the interface
     *
     * Functor to publish the interface
     *
     * @endif
     */
    struct publish;
    
    /*!
     * @if jp
     * @brief Interface��³��Functor
     *
     * Interface��³������¹Ԥ��뤿���Functor��
     *
     * @else
     * @brief Functor to subscribe the interface
     *
     * Functor to subscribe the interface
     *
     * @endif
     */
    struct subscribe;
    
    /*!
     * @if jp
     * @brief Interface��³�����Functor
     *
     * Interface��³���������¹Ԥ��뤿���Functor��
     *
     * @else
     * @brief Functor to unsubscribe the interface
     *
     * Functor to unsubscribe the interface
     *
     * @endif
     */
    struct unsubscribe;
    
  private:
    /*
     * Bug
     *
     * Fedora5/gcc4.1.1. �ˤ� DataInPort ����Ƭ�ΰ�Υ����˲���
     * �����äƤ������͡�
     * (gdb�Ǥ��ʤ�Ǵ�ä��ɤäƤߤ�����ǰ)
     * ��Ȥ�Ȥ�� std::vector<InPortProvider*> m_providers ����Ƭ
     * ���Τޤޤ��ȡ�
     * $vec->_M_impl._M_start:  begin() ��������
     * $vec->_M_impl._M_finish: end() ��������
     * �ˤ����Ƥ� _M_start ���ԲĲ�ʰ��֤�ؤ����ᡢ
     * m_providers ���Ф��� for_each ��Ŭ�Ѥ����Segv������롣
     *
     * FreeBSD6.0/gcc3.4.4�ǤϤ��θ��ݤ�ȯ��������
     */
    std::vector<int> m_dummy;
    std::vector<InPortProvider*> m_providers;
    std::vector<OutPortConsumer*> m_consumers;
  };
}; // namespace RTC

#endif // DataInPort_h
