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
 * $Id$
 *
 */

#ifndef RTC_OUTPORTPROVIDER_H
#define RTC_OUTPORTPROVIDER_H

#include <string>

#include <coil/Factory.h>
#include <rtm/BufferBase.h>
#include <rtm/NVUtil.h>
#include <rtm/SystemLogger.h>
#include <rtm/DataPortStatus.h>

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
    : public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM
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
    virtual ~OutPortProvider(void);

    /*!
     * @if jp
     * @brief ��������
     *
     * InPortConsumer�γƼ������Ԥ����������饹�Ǥϡ�Ϳ����줿
     * Properties����ɬ�פʾ����������ƳƼ������Ԥ������� init() ��
     * ���ϡ�OutPortProvider����ľ�太��ӡ���³���ˤ��줾��ƤФ���
     * ǽ�������롣�������äơ����δؿ���ʣ����ƤФ�뤳�Ȥ����ꤷ�Ƶ�
     * �Ҥ����٤��Ǥ��롣
     * 
     * @param prop �������
     *
     * @else
     *
     * @brief Initializing configuration
     *
     * This operation would be called to configure in initialization.
     * In the concrete class, configuration should be performed
     * getting appropriate information from the given Properties data.
     * This function might be called right after instantiation and
     * connection sequence respectivly.  Therefore, this function
     * should be implemented assuming multiple call.
     *
     * @param prop Configuration information
     *
     * @endif
     */
    virtual void init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief �Хåե��򥻥åȤ���
     *
     * OutPortProvider���ǡ�������Ф��Хåե��򥻥åȤ��롣
     * ���Ǥ˥��åȤ��줿�Хåե��������硢�����ΥХåե��ؤ�
     * �ݥ��󥿤��Ф��ƾ�񤭤���롣
     * OutPortProvider�ϥХåե��ν�ͭ�����ꤷ�Ƥ��ʤ��Τǡ�
     * �Хåե��κ���ϥ桼������Ǥ�ǹԤ�ʤ���Фʤ�ʤ���
     *
     * @param buffer OutPortProvider���ǡ�������Ф��Хåե��ؤΥݥ���
     *
     * @else
     * @brief Setting outside buffer's pointer
     *
     * A pointer to a buffer from which OutPortProvider retrieve data.
     * If already buffer is set, previous buffer's pointer will be
     * overwritten by the given pointer to a buffer.  Since
     * OutPortProvider does not assume ownership of the buffer
     * pointer, destructor of the buffer should be done by user.
     * 
     * @param buffer A pointer to a data buffer to be used by OutPortProvider
     *
     * @endif
     */
    virtual void setBuffer(BufferBase<cdrMemoryStream>* buffer);
    
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
     * Interface�����������롣�����ǻ��ꤹ��ץ�ѥƥ��������
     * NameValue ���֥������Ȥ�dataport.interface_type �ͤ�Ĵ�١������ݡ�
     * �Ȥ����ꤵ��Ƥ��ʤ����NameValue �˾�����ɲä��롣���Ǥ�Ʊ�쥤
     * �󥿡��ե���������Ͽ�Ѥߤξ��ϲ���Ԥ�ʤ���
     *
     * @param properties Interface�����������ץ�ѥƥ�
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.  Check the
     * dataport.interface_type value of the NameValue object specified
     * by an argument in the property information, and add the
     * information to the NameValue if this port is not specified.
     * This does not do anything if the same interface is already
     * subscribed.
     *
     * @param properties Properties to receive interface information
     *
     * @endif
     */
    virtual bool publishInterface(SDOPackage::NVList& properties);
    
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
    
  protected:
    /*!
     * @if jp
     * @brief �ݡ��ȥץ�ե�������ݻ�����ץ�ѥƥ�
     * @else
     * @brief Properties to hold the port profiles
     * @endif
     */
    SDOPackage::NVList m_properties;
    mutable Logger rtclog;
    
  private:
    std::string m_portType;
    std::string m_dataType;
    std::string m_interfaceType;
    std::string m_dataflowType;
    std::string m_subscriptionType;


  public:
    // functors
    /*!
     * @if jp
     * @brief ���󥿡��ե������ץ�ե������������뤿�Υե��󥯥�
     * @else
     * @brief Functor to publish interface profile
     * @endif
     */
    struct publishInterfaceProfileFunc
    {
      publishInterfaceProfileFunc(SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortProvider* provider)
      {
	provider->publishInterfaceProfile(m_prop);
      }
      SDOPackage::NVList& m_prop;
    };

    /*!
     * @if jp
     * @brief ���󥿡��ե������ץ�ե������������뤿�Υե��󥯥�
     * @else
     * @brief Functor to publish interface profile
     * @endif
     */
    struct publishInterfaceFunc
    {
      publishInterfaceFunc(SDOPackage::NVList& prop)
        : m_prop(prop), provider_(0) {}
      void operator()(OutPortProvider* provider)
      {
	if (provider->publishInterface(m_prop))
          {
            provider_ = provider;
          }
      }
      SDOPackage::NVList& m_prop;
      OutPortProvider* provider_;
    };
  };

  typedef ::coil::GlobalFactory<OutPortProvider> OutPortProviderFactory;

}; // namespace RTC
#endif // RTC_OUTPORTPROVIDER_H
