// -*- C++ -*-
/*!
 * @file  CorbaPort.h
 * @brief CorbaPort class
 * @date  $Date: 2007-12-31 03:08:02 $
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
 * $Id: CorbaPort.h,v 1.1.4.1 2007-12-31 03:08:02 n-ando Exp $
 *
 */

#ifndef CorbaPort_h
#define CorbaPort_h

#include <rtm/PortBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/NVUtil.h>

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
   * @class CorbaPort
   * @brief RT ����ݡ��ͥ�� CORBA provider/consumer �� Port
   *
   * CorbaPort �� RT ����ݡ��ͥ�Ȥˤ����ơ��桼������� CORBA ���֥�������
   * �����ӥ�����ӥ��󥷥塼�ޤ��󶡤��� Port �����Ǥ��롣
   * <p>
   * RT ����ݡ��ͥ�Ȥϡ�Port ��𤷤ƥ桼����������� CORBA �����ӥ�����
   * ���뤳�Ȥ��Ǥ�������� RT Service (Provider) �ȸƤ֡�
   * �ޤ���¾�� RT ����ݡ��ͥ�ȤΥ����ӥ������Ѥ��뤿��� CORBA ���֥�������
   * �Υץ졼���ۥ�����󶡤��뤳�Ȥ��Ǥ�������� RT Service Consumer �ȸƤ֡�
   * <p>
   * CorbaPort ��Ǥ�դο��� Provider ����� Consumer ��������뤳�Ȥ��Ǥ���
   * Port Ʊ�Τ���³����ݤ��б����� Provider �� Consumer ��Ŭ�ڤ˴�Ϣ�դ���
   * ���Ȥ��Ǥ��롣
   * <p>
   * CorbaPort ���̾�ʲ��Τ褦�����Ѥ���롣
   *
   * <pre>
   * RTC::CorbaPort m_port0; // Port �����
   *
   * MyService_impl m_mysvc0; // ���� Port ���󶡤��� Serivce Provider
   * RTC::CorbaConsumer<YourService> m_cons0; // ���� Port �� Consumer
   *
   * // Service Provider �� Port ����Ͽ
   * m_port0.registerProvider("MyService0", "Generic", m_mysvc0);
   * // Service Consumer �� Port ����Ͽ
   * m_port0.registerConsumer("YourService0", "Generic", m_cons0 );
   *
   * // connect ���Ԥ�줿��
   *
   * m_cons0->your_service_function(); // YourService �δؿ��򥳡���
   *
   * // connect ���줿 �̤Υ���ݡ��ͥ�Ȥˤ�����
   * m_cons1->my_service_function(); // MyService �δؿ��򥳡���
   * </pre>
   *
   * ���Τ褦�ˡ��󶡤����� Service Provider �� registerProvider() ����Ͽ
   * ���뤳�Ȥˤ�ꡢ¾�Υ���ݡ��ͥ�Ȥ������Ѳ�ǽ�ˤ���¾����
   * ���Ѥ����� Service Consumer �� registerConsumer() ����Ͽ���뤳�Ȥˤ��
   * ¾�Υ���ݡ��ͥ�Ȥ� Service �򥳥�ݡ��ͥ��������Ѳ�ǽ�ˤ��뤳�Ȥ�
   * �Ǥ��롣
   *
   * @since 0.4.0
   *
   * @else
   * @class CorbaPort
   * @brief RT Conponent CORBA service/consumer Port
   *
   * CorbaPort is an implementation of the Port of RT-Component's that provides
   * user-defined CORBA Object Service and Consumer.
   * <p>
   * RT-Component can provide user-defined CORBA serivces, which is called
   * RT-Serivce (Provider), through the Ports.
   * RT-Component can also provide place-holder, which is called RT-Serivce
   * Consumer, to use other RT-Component's service.
   * <p>
   * The CorbaPort can manage any number of Providers and Consumers, can
   * associate Consumers with correspondent Providers when establishing
   * connection among Ports.
   * <p>
   * Usually, CorbaPort is used like the following.
   *
   * <pre>
   * RTC::CorbaPort m_port0; // declaration of Port
   *
   * MyService_impl m_mysvc0; // Serivce Provider that is provided by the Port
   * RTC::CorbaConsumer<YourService> m_cons0; // Consumer of the Port
   *
   * // register Service Provider to the Port
   * m_port0.registerProvider("MyService0", "Generic", m_mysvc0);
   * // register Service Consumer to the Port
   * m_port0.registerConsumer("YourService0", "Generic", m_cons0 );
   *
   * // after connect established
   *
   * m_cons0->your_service_function(); // call a YourService's function
   *
   * // in another component that is connected with the Port
   * m_cons1->my_service_function(); // call a MyService's function
   * </pre>
   *
   * Registering Service Provider by registerProvider(), it can be used from
   * other RT-Components.
   * Registering Service Consumer by registerConsumer(), other RT-Component's
   * services can be used through the consumer object.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class CorbaPort
    : public PortBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * @param name Port ��̾��
     *
     * @else
     *
     * @brief Constructor
     *
     * @param name The name of Port 
     *
     * @endif
     */
    CorbaPort(const char* name);
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     *
     * @else
     *
     * @brief Virtual destructor
     *
     * @endif
     */
    virtual ~CorbaPort();
    
    /*!
     * @if jp
     *
     * @brief Provider ����Ͽ����
     *
     * ���� Port �ˤ������󶡤����������Х�Ȥ򤳤� Port ���Ф�����Ͽ���롣
     * �����Х�Ȥϡ�������Ϳ������ instance_name, type_name ��
     * �����Х�ȼ��ȤΥ��󥹥���̾����ӥ�����̾�Ȥ��ơ������Х�Ȥ�
     * ��Ϣ�դ����롣
     *
     * @param instance_name �����Х�ȤΥ��󥹥���̾
     * @param type_name �����Х�ȤΥ�����̾
     * @param provider CORBA �����Х��
     *
     * @return ����Ʊ̾�� instance_name ����Ͽ����Ƥ���� false ���֤���
     *
     * @else
     *
     * @brief Register the provider
     *
     * This operation registers a servant, which is provided in this Port,
     * to the Port. The servant is associated with "instance_name" and
     * "type_name" as the instance name of the servant and as the type name
     * of the servant.
     *
     * @param instance_name Instance name of servant
     * @param type_name Type name of the servant
     * @param provider CORBA servant
     *
     * @return Return false if the same name of instance_name is already 
     *         registered.
     *
     * @endif
     */
    bool registerProvider(const char* instance_name, const char* type_name,
			  PortableServer::RefCountServantBase& provider);
    
    /*!
     * @if jp
     *
     * @brief Consumer ����Ͽ����
     *
     * ���� Port ���׵᤹�륵���ӥ��Υץ졼���ۥ���Ǥ��륳�󥷥塼��
     * (Consumer) ����Ͽ���롣
     * Consumer ����Ϣ�դ����륵���ӥ��Υ��󥹥���̾����ӥ�����̾�Ȥ��ơ�
     * ������ instance_name, type_name ����� Consumer ���Ȥ�Ϳ���뤳�Ȥˤ�ꡢ
     * �����Ǥ���餬��Ϣ�դ����롣
     * Port �֤���³ (connect) �� �ˤϡ�Ʊ��� instance_name, type_name �����
     * �����ӥ���¾�� Port ������ (Provide) ����Ƥ����硢���Υ����ӥ���
     * ���֥������Ȼ��Ȥ���ưŪ�� Consumer �˥��åȤ���롣
     *
     * @param instance_name Consumer ���׵᤹�륵���ӥ��Υ��󥹥���̾
     * @param type_name Consumer ���׵᤹�륵���ӥ��Υ�����̾
     * @param consumer CORBA �����ӥ����󥷥塼��
     *
     * @return ����Ʊ̾�� instance_name ����Ͽ����Ƥ���� false ���֤���
     *
     * @else
     *
     * @brief Register the consumer
     *
     * This operation registers a consumer, which is a service placeholder
     * this port requires. These are associated internally by specified 
     * instance_name, type_name and Consumer itself to the argument as
     * service's instance name and its type name associated with Consumer.
     * If the service with the same instance_name and type_name is provided
     * by the other port when connecting between ports, its service object
     * reference will be set automatically.
     *
     * @param instance_name Instance name of the service Consumer requires
     * @param type_name Type name of the service Consumer requires
     * @param consumer CORBA service consumer
     *
     * @return False would be returned if the same instance_name was registered
     *
     * @endif
     */
    bool registerConsumer(const char* instance_name, const char* type_name,
			  CorbaConsumerBase& consumer);
    
  protected:
    /*!
     * @if jp
     *
     * @brief Interface ������������
     *
     * ���� Port����ͭ���� Provider �˴ؤ������� ConnectorProfile::properties
     * ���������롣
     * �����������ϡ�NVList�� name �� value �Ȥ��ưʲ��Τ�Τ���Ǽ����롣
     *
     * - port.<type_name>.<instance_name>: <CORBA::Object_ptr>
     *
     * �����ǡ�
     * - <type_name>: PortInterfaceProfile::type_name
     * - <instance_name>: PortInterfaceProfile::instance_name
     *
     * �Ǥ��롣
     * ConnectorProfile::properties �Ǥϡ������� .(�ɥå�)ɽ���ǡ�
     * NameValue �Υ����Ȥ��Ƥ��롣�������äơ�
     *
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = PROVIDED;
     *  }
     *</pre>
     *
     * �ʤ�С�
     *
     * <pre>
     * NameValue = { "port.Manipulator.PA10_0": <Object reference> }
     * </pre>
     *
     * �Ȥ��ä��ͤ� ConnectorProfile::properties �˳�Ǽ���졢¾�Υݡ��Ȥ��Ф���
     * ��ã����롣¾�� Port �Ǥ��Υ��󥿡��ե���������Ѥ��� Consumer ��
     * ¸�ߤ���С�ConnectorProfile ���餳�Υ������饪�֥������ȥ�ե���󥹤�
     * ���������餫�η��ǻ��Ѥ���롣
     *
     * @param connector_profile ���ͥ����ץ�ե�����
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Publish interface information
     *
     * Assign information associated with Provider owned by this Port
     * to ConnectorProfile::properties.
     * In assignment information, the following is stored as NVList name and 
     * its value.
     *
     * - port.<type_name>.<instance_name>: <CORBA::Object_ptr>
     *
     * Here,
     * - <type_name>: PortInterfaceProfile::type_name
     * - <instance_name>: PortInterfaceProfile::instance_name<br>
     * <br>
     * In ConnectorProfile::properties, these are keys of NameValue written 
     * with .(dot) notation. Therefore,
     *
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = PROVIDED;
     *  }
     *</pre>
     *
     * so,
     *
     * <pre>
     * NameValue = { "port.Manipulator.PA10_0": <Object reference> }
     * </pre>
     *
     * The above value is set to ConnectorProfile::properties and sent to other
     * ports. If Consumer that uses this interface in other Port exists,
     * the object references will be got and use from the key of 
     * ConnectorProfile.
     *
     * @param connector_profile Connector profile
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief Interface ����³����
     *
     * ���� Port����ͭ���� Consumer ��Ŭ�礹�� Provider �˴ؤ�������
     * ConnectorProfile::properties ������Ф� Consumer �˥��֥������Ȼ���
     * �򥻥åȤ��롣
     *
     * ����Consumer ��
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = REQUIRED;
     *  }
     *</pre>
     * �Ȥ�����Ͽ����Ƥ���С�¾�� Port ��
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = PROVIDED;
     *  }
     * </pre> 
     * �Ȥ�����Ͽ����Ƥ��� Serivce Provider �Υ��֥������Ȼ��Ȥ�õ����
     * Consumer �˥��åȤ��롣
     * �ºݤˤϡ�ConnectorProfile::properties ��
     * <pre>
     * NameValue = { "port.Manipulator.PA10_0": <Object reference> }
     * </pre>
     * �Ȥ�����Ͽ����Ƥ��� NameValue ��õ�������Υ��֥������Ȼ��Ȥ�
     * Consumer �˥��åȤ��롣
     *
     * @param connector_profile ���ͥ����ץ�ե�����
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Subscribe to interface
     *
     * Retrieve information associated with Provider matches Consumer
     * owned by this port and set the object reference to Consumer.
     *
     * Now, Consumer is registered as the following:
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = REQUIRED;
     *  }
     *</pre>
     * Find the object reference of Serivce Provider that is registered as
     * the following of other ports:
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = PROVIDED;
     *  }
     * </pre> 
     * and set to Consumer.
     * In fact, find NameValue that is registered as the following to 
     * ConnectorProfile::properties:
     * <pre>
     * NameValue = { "port.Manipulator.PA10_0": <Object reference> }
     * </pre>
     * and set the object reference to Consumer.
     *
     * @param connector_profile Connector profile
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief Interface �ؤ���³��������
     *
     * Ϳ����줿 ConnectorProfile �˴�Ϣ���� Consumer �˥��åȤ��줿
     * ���٤Ƥ� Object ���������³�������롣
     *
     * @param connector_profile ���ͥ����ץ�ե�����
     *
     * @else
     *
     * @brief Unsubscribe interfaces
     *
     * Release all Objects that was set in Consumer associated with the given 
     * ConnectorProfile.
     *
     * @param connector_profile Connector profile
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);
    
  private:
    /*!
     * @if jp
     * @brief Provider �ξ�����Ǽ���� NVList
     * @else
     * @brief NVList to be stored Providers' information
     * @endif
     */
    NVList m_providers;
    
    /*!
     * @if jp
     * @brief Consumer �ξ�����Ǽ���빽¤��
     * @else
     * @brief The structure to be stored Consumer information.
     * @endif
     */
    struct Consumer
    {
      Consumer(const char* _instance_name, const char* _type_name,
	       CorbaConsumerBase& _cons)
	: name(std::string("port.")
	       + _type_name
	       + std::string(".")
	       + _instance_name),
	  consumer(_cons)
      {}
      Consumer(const Consumer& cons)
	: name(cons.name), consumer(cons.consumer)
      {	
      }
      Consumer operator=(const Consumer& _cons)
      {
	Consumer cons(_cons);
	return cons;
      }
      std::string name;
      CorbaConsumerBase& consumer;
    };
    std::vector<Consumer> m_consumers;
    
    // functors
    /*!
     * @if jp
     * @brief ConnectorProfile �� Consuemr ����Ӥ򤷥��֥������Ȼ��Ȥ�
     *        ���åȤ��뤿��� Functor
     * @else
     * @brief Functor to compare ConnectorProfile and Consuemr, to set object 
     *        reference
     * @endif
     */
    struct subscribe
    {
      subscribe(std::vector<Consumer>& cons)
	: m_cons(cons), m_len(cons.size())
      {
      }
      
      void operator()(const SDOPackage::NameValue& nv)
      {
	for (CORBA::ULong i = 0; i < m_len; ++i)
	  {
	    std::string name(nv.name);
	    if (m_cons[i].name == name)
	      {
		CORBA::Object_ptr obj;
		if (nv.value >>= CORBA::Any::to_object(obj))
		  {
		    m_cons[i].consumer.setObject(obj);
		  }
	      }
	  }
      }
      std::vector<Consumer> m_cons;
      CORBA::ULong m_len;
    };
    
    /*!
     * @if jp
     * @brief Consumer �Υ��֥������Ȥ�������뤿��� Functor
     * @else
     * @brief Functor to release Consumer's object
     * @endif
     */
    struct unsubscribe
    {
      unsubscribe(std::vector<Consumer>& cons)
	: m_cons(cons), m_len(cons.size())
      {
      }
      
      void operator()(const SDOPackage::NameValue& nv)
      {
	for (CORBA::ULong i = 0; i < m_len; ++i)
	  {
	    std::string name(nv.name);
	    if (m_cons[i].name == name)
	      {
		m_cons[i].consumer.releaseObject();
	      }
	  }
      }
      std::vector<Consumer> m_cons;
      CORBA::ULong m_len;
    };
  };
};
#endif // CorbaPort_h
