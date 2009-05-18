// -*- C++ -*-
/*!
 * @file InPortBase.h
 * @brief RTC::Port implementation for InPort
 * @date $Date: 2008-01-13 15:06:40 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
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

#ifndef RTC_INPORTBASE_H
#define RTC_INPORTBASE_H

#include <rtm/PortBase.h>
#include <rtm/DataPortStatus.h>
#include <rtm/CdrBufferBase.h>

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
  class InPortProvider;
  class OutPortConsumer;
  class InPortConnector;

  /*!
   * @if jp
   * @class InPortBase
   * @brief InPort �� Port
   *
   * �ǡ������ϥݡ��Ȥμ������饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortBase
   * @brief Port for InPort
   *
   * This is an implementation class for the data input port.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortBase
    : public PortBase, public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM
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
    InPortBase(const char* name, const char* data_type);
    
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
    virtual ~InPortBase(void);
    
    coil::Properties& properties();

    void init();

    /*!
     * @if jp
     *
     * @brief InPort�� activates ����
     *
     * InPort�� activate ���롣
     *
     * @else
     *
     * @brief Activate all Port interfaces
     *
     * This operation activate all interfaces that is registered in the
     * ports.
     *
     * @endif
     */
    virtual void activateInterfaces();

    /*!
     * @if jp
     *
     * @brief ���Ƥ� Port �Υ��󥿡��ե������� deactivates ����
     *
     * Port ����Ͽ����Ƥ������ƤΥ��󥿡��ե������� deactivate ���롣
     *
     * @else
     *
     * @brief Deactivate all Port interfaces
     *
     * This operation deactivate all interfaces that is registered in the
     * ports.
     *
     * @endif
     */
    virtual void deactivateInterfaces();

  protected:
    /*!
     * @if jp
     * @brief Interface������������
     *
     * Interface�����������롣
     * ������ ConnectorProfile �˳�Ǽ����Ƥ��� dataflow_type �� push ��
     * �ξ��ϡ����ꤵ�줿 interface_type �� InPortProvider �˴ؤ������
     * �� ConnectorProfile::properties �˽���߸ƤӽФ�¦���᤹��
     *
     *  dataport.dataflow_type
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
     * @brief InPort provider �ν����
     * @else
     * @brief InPort provider initialization
     * @endif
     */
    void initProviders();

    /*!
     * @if jp
     * @brief OutPort consumer �ν����
     * @else
     * @brief OutPort consumer initialization
     * @endif
     */
    void initConsumers();

    /*!
     * @if jp
     * @brief InPort provider ������
     * @else
     * @brief InPort provider creation
     * @endif
     */
    InPortProvider* createProvider(const std::string& iface_type);
    
    /*!
     * @if jp
     * @brief InPort provider �κ��
     * @else
     * @brief InPort provider deletion
     * @endif
     */
    void deleteProvider(InPortProvider* provider);
    
  protected:
    bool m_singlebuffer;
    CdrBufferBase* m_thebuffer;

    coil::Properties m_properties;
    std::vector<InPortProvider*> m_providers;
    std::vector<OutPortConsumer*> m_consumers;
    std::vector<InPortConnector*> m_connectors;
    coil::vstring m_consumerTypes;


  };
}; // namespace RTC

#endif // RTC_INPORTBASE_H
