// -*- C++ -*-
/*!
 * @file  OutPortProvider.h
 * @brief OutPortProvider class
 * @date  $Date: 2007-12-31 03:08:05 $
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
 * $Id: OutPortProvider.h,v 1.2.4.1 2007-12-31 03:08:05 n-ando Exp $
 *
 */

#ifndef OutPortProvider_h
#define OutPortProvider_h

#include <rtm/NVUtil.h>
#include <string>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class OutPortProvider
   * @brief OutPortProvider
   *
   * - Port ���Ф��Ʋ����󶡤��Ƥ��뤫��������롣
   *   PortProfile �� properties �� Provider �˴ؤ��������ɲä��롣
   *
   * (��) OutPort �� Provide ������
   *
   * OutPortCorbaProvider ���ʲ������
   *  - dataport.interface_type = CORBA_Any
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   * 
   * OutPortRawTCPProvider ���ʲ������
   *  - dataport.interface_type = RawTCP
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   * 
   * �ǽ�Ū�� PortProfile::properties ��
   *  - dataport.interface_type = CORBA_Any, RawTCP
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class OutPortProvider
   * @brief OutPortProvider
   *
   * - Declare what is provided to the port.
   *   Add information associated with Provider to the properties of PortProfile.
   *
   * (Example) When OutPort is provided:
   *
   * OutPortCorbaProvider declares the following:
   *  - dataport.interface_type = CORBA_Any
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   * 
   * OutPortRawTCPProvider declares the following:
   *  - dataport.interface_type = RawTCP
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   * 
   * Finally, PortProfile::properties declares the following:
   *  - dataport.interface_type = CORBA_Any, RawTCP
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   *
   * @since 0.4.0
   *
   * @endif
   */
  class OutPortProvider
  {
  public:
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
    virtual ~OutPortProvider(){};
    
    /*!
     * @if jp
     * @brief InterfaceProfile������������
     *
     * InterfaceProfile�����������롣
     * �����ǻ��ꤹ��ץ�ѥƥ�������� NameValue ���֥������Ȥ�
     * dataport.interface_type �ͤ�Ĵ�١������ݡ��Ȥ����ꤵ��Ƥ���
     * ���󥿡��ե����������פȰ��פ�����Τ߾����������롣
     *
     * @param properties InterfaceProfile�����������ץ�ѥƥ�
     *
     * @else
     * @brief Publish InterfaceProfile information
     *
     * Publish interfaceProfile information.
     * Check the dataport.interface_type value of the NameValue object 
     * specified by an argument in property information and get information
     * only when the interface type of the specified port is matched.
     *
     * @param properties Properties to get InterfaceProfile information
     *
     * @endif
     */
    virtual void publishInterfaceProfile(SDOPackage::NVList& properties);
    
    /*!
     * @if jp
     * @brief Interface������������
     *
     * Interface������������
     * �����ǻ��ꤹ��ץ�ѥƥ�������� NameValue ���֥������Ȥ�
     * dataport.interface_type �ͤ�Ĵ�١������ݡ��Ȥ����ꤵ��Ƥ��ʤ����
     * NameValue �˾�����ɲä��롣
     * ���Ǥ�Ʊ�쥤�󥿡��ե���������Ͽ�Ѥߤξ��ϲ���Ԥ�ʤ���
     *
     * @param properties Interface�����������ץ�ѥƥ�
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.
     * Check the dataport.interface_type value of the NameValue object specified 
     * by an argument in the property information, and add the information to the
     * NameValue if this port is not specified.
     * This does not do anything if the same interface is already subscribed.
     *
     * @param properties Properties to receive interface information
     *
     * @endif
     */
    virtual void publishInterface(SDOPackage::NVList& properties);
    
  protected:
    /*!
     * @if jp
     * @brief �ݡ��ȥ����פ����ꤹ��
     *
     * �����ǻ��ꤷ���ݡ��ȥ����פ����ꤹ�롣
     *
     * @param port_type �����оݥݡ��ȥ�����
     *
     * @else
     * @brief Set the port type
     *
     * Set the port type specified by the argument.
     *
     * @param port_type The target port type to set
     *
     * @endif
     */
    void setPortType(const char* port_type);
    
    /*!
     * @if jp
     * @brief �ǡ��������פ����ꤹ��
     *
     * �����ǻ��ꤷ���ǡ��������פ����ꤹ�롣
     *
     * @param data_type �����оݥǡ���������
     *
     * @else
     * @brief Set the data type
     *
     * Set the data type specified by the argument.
     *
     * @param data_type The target data type to set
     *
     * @endif
     */
    void setDataType(const char* data_type);
    
    /*!
     * @if jp
     * @brief ���󥿡��ե����������פ����ꤹ��
     *
     * �����ǻ��ꤷ�����󥿡��ե����������פ����ꤹ�롣
     *
     * @param interface_type �����оݥ��󥿡��ե�����������
     *
     * @else
     * @brief Set the interface type
     *
     * Set theinterface type specified by the argument.
     *
     * @param interface_type The target interface type to set
     *
     * @endif
     */
    void setInterfaceType(const char* interface_type);
    
    /*!
     * @if jp
     * @brief �ǡ����ե������פ����ꤹ��
     *
     * �����ǻ��ꤷ���ǡ����ե������פ����ꤹ�롣
     *
     * @param dataflow_type �����оݥǡ����ե�������
     *
     * @else
     * @brief Set the data flow type
     *
     * Set the data flow type specified by the argument.
     *
     * @param dataflow_type The target data flow type to set
     *
     * @endif
     */
    void setDataFlowType(const char* dataflow_type);
    
    /*!
     * @if jp
     * @brief ���֥�����ץ���󥿥��פ����ꤹ��
     *
     * �����ǻ��ꤷ�����֥�����ץ���󥿥��פ����ꤹ�롣
     *
     * @param subs_type �����оݥ��֥�����ץ���󥿥���
     *
     * @else
     * @brief Set the subscription type
     *
     * Set the subscription type specified by the argument.
     *
     * @param subs_type The target subscription type to set
     *
     * @endif
     */
    void setSubscriptionType(const char* subs_type);
    
    /*!
     * @if jp
     * @brief �ݡ��ȥץ�ե�������ݻ�����ץ�ѥƥ�
     * @else
     * @brief Properties to hold the port profiles
     * @endif
     */
    SDOPackage::NVList m_properties;
    
  private:
    std::string m_portType;
    std::string m_dataType;
    std::string m_interfaceType;
    std::string m_dataflowType;
    std::string m_subscriptionType;
  };
}; // namespace RTC
#endif // OutPortProvider_h
