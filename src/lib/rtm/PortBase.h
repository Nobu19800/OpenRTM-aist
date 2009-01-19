// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2008-01-14 07:56:44 $
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

#ifndef PortBase_h
#define PortBase_h

#include <rtm/RTC.h>

#include <string>
#include <vector>
#include <coil/Guard.h>
#include <coil/Mutex.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>

#include <iostream>
namespace RTC
{
  /*!
   * @if jp
   * @class PortBase
   * @brief Port �δ��쥯�饹
   *
   * RTC::Port �δ���Ȥʤ륯�饹��
   * RTC::Port �Ϥۤ� UML Port �γ�ǰ��Ѿ����Ƥ��ꡢ�ۤ�Ʊ���Τ�ΤȤߤʤ�
   * ���Ȥ��Ǥ��롣RT ����ݡ��ͥ�ȤΥ��󥻥ץȤˤ����Ƥϡ�
   * Port �ϥ���ݡ��ͥ�Ȥ���°��������ݡ��ͥ�Ȥ�¾�Υ���ݡ��ͥ�Ȥ���ߺ���
   * ��Ԥ������Ǥ��ꡢ�̾���Ĥ��Υ��󥿡��ե������ȴ�Ϣ�դ����롣
   * ����ݡ��ͥ�Ȥ� Port ���̤��Ƴ������Ф����󥿡��ե��������󶡤ޤ����׵�
   * ���뤳�Ȥ��Ǥ���Port�Ϥ�����³�������������ô����
   * <p>
   * Port �ζ�ݥ��饹�ϡ��̾� RT ����ݡ��ͥ�ȥ��󥹥�����������Ʊ����
   * �������졢�󶡡��׵ᥤ�󥿡��ե���������Ͽ�����塢RT ����ݡ��ͥ�Ȥ�
   * ��Ͽ���졢�������饢��������ǽ�� Port �Ȥ��Ƶ�ǽ���뤳�Ȥ����ꤷ�Ƥ��롣
   * <p>
   * RTC::Port �� CORBA ���󥿡��ե������Ȥ��ưʲ��Υ��ڥ졼�������󶡤��롣
   *
   * - get_port_profile()
   * - get_connector_profiles()
   * - get_connector_profile()
   * - connect()
   * - notify_connect()
   * - disconnect()
   * - notify_disconnect()
   * - disconnect_all()
   *
   * ���Υ��饹�Ǥϡ������Υ��ڥ졼�����μ������󶡤��롣
   * <p>
   * �����Υ��ڥ졼�����Τ�����get_port_profile(), get_connector_profiles(),
   * get_connector_profile(), connect(), disconnect(), disconnect_all() �ϡ�
   * ���֥��饹�ˤ������ä˿����񤤤��ѹ�����ɬ�פ��ʤ����ᡢ�����С��饤��
   * ���뤳�ȤϿ侩����ʤ���
   * <p>
   * notify_connect(), notify_disconnect() �ˤĤ��Ƥϡ����֥��饹���󶡡��׵�
   * ���륤�󥿡��ե������μ���˱����ơ������񤤤��ѹ�����ɬ�פ�������
   * ���⤷��ʤ�����������ľ�ܥ����С��饤�ɤ��뤳�ȤϿ侩���줺��
   * ��Ҥ� notify_connect(), notify_disconnect() �ι�ˤ����Ƥ�Ҥ٤����̤�
   * �����δؿ��˴�Ϣ���� protected �ؿ��򥪡��С��饤�ɤ��뤳�Ȥˤ��
   * �����񤤤��ѹ����뤳�Ȥ��侩����롣
   *
   * @since 0.4.0
   *
   * @else
   * @class PortBase
   * @brief Port base class
   *
   * This class is a base class of RTC::Port.
   * RTC::Port inherits a concept of RT-Component, and can be regarded as almost
   * the same as it. In the concept of RT-Component, Port is attached to the
   * component, can mediate interaction between other components and usually is
   * associated with some interfaces.
   * Component can provide or require interface for outside via Port, and the
   * Port plays a role to manage the connection.
   * <p>
   * Concrete class of Port assumes to be usually created at the same time that
   * RT-Component's instance is created, be registerd to RT-Component after
   * provided and required interfaces are registerd, and function as accessible
   * Port from outside.
   * <p>
   * RTC::Port provides the following operations as CORBA interface:
   *
   * - get_port_profile()
   * - get_connector_profiles()
   * - get_connector_profile()
   * - connect()
   * - notify_connect()
   * - disconnect()
   * - notify_disconnect()
   * - disconnect_all()
   *
   * This class provides implementations of these operations.
   * <p>
   * In these operations, as for get_port_profile(), get_connector_profiles(),
   * get_connector_profile(), connect(), disconnect() and disconnect_all(),
   * since their behaviors especially need not to be change in subclass, 
   * overriding is not recommended.
   * <p>
   * As for notify_connect() and notify_disconnect(), you may have to modify
   * behavior according to the kind of interfaces that subclass provides and
   * requires, however it is not recommended these are overriden directly.
   * In the section of notify_connect() and notify_disconnect() as described
   * below, it is recommended that you modify behavior by overriding the
   * protected function related to these functions.
   *
   * @since 0.4.0
   *
   * @endif
   */  
  class PortBase
    : public virtual POA_RTC::PortService,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * PortBase �Υ��󥹥ȥ饯���� Port ̾ name ������˼��������Ԥ�
     * ��Ʊ���ˡ���ʬ���Ȥ� CORBA Object �Ȥ��Ƴ������������Ȥ� PortProfile
     * �� port_ref �˼��ȤΥ��֥������ȥ�ե���󥹤��Ǽ���롣
     *
     * @param name Port ��̾��(�ǥե������:"")
     *
     * @else
     *
     * @brief Constructor
     *
     * The constructor of the ProtBase class is given the name of this Port
     * and initialized. At the same time, the PortBase activates itself
     * as CORBA object and stores its object reference to the PortProfile's 
     * port_ref member.
     *
     * @param name The name of Port (The default value:"")
     *
     * @endif
     */
    PortBase(const char* name = "");
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~PortBase();
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] PortProfile���������
     *
     * Port���ݻ�����PortProfile���֤���
     * PortProfile ��¤�Τϰʲ��Υ��С�����ġ�
     *
     * - name              [string ��] Port ��̾����
     * - interfaces        [PortInterfaceProfileList ��] Port ���ݻ�����
     *                     PortInterfaceProfile �Υ�������
     * - port_ref          [Port Object ��] Port ���ȤΥ��֥������ȥ�ե����
     * - connector_profile [ConnectorProfileList ��] Port �������ݻ�����
     *                     ConnectorProfile �Υ�������
     * - owner             [RTObject Object ��] ���� Port ���ͭ����
     *                     RTObject�Υ�ե����
     * - properties        [NVList ��] ����¾�Υץ�ѥƥ���
     *
     * @return PortProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the PortProfile of the Port
     *
     * This operation returns the PortProfile of the Port.
     * PortProfile struct has the following members:
     *
     * - name              [string type] The name of the Port.
     * - interfaces        [PortInterfaceProfileList type] The sequence of 
     *                     PortInterfaceProfile owned by the Port
     * - port_ref          [Port Object type] The object reference of the Port.
     * - connector_profile [ConnectorProfileList type] The sequence of 
     *                     ConnectorProfile owned by the Port.
     * - owner             [RTObject Object type] The object reference of 
     *                     RTObject that is owner of the Port.
     * - properties        [NVList type] The other properties.
     *
     * @return PortProfile of the Port
     *
     * @endif
     */
    virtual PortProfile* get_port_profile()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief PortProfile ��������롣
     *
     * �ܥݡ��Ȥ� PortProfile ��������롣
     *
     * @return PortProfile
     *
     * @else
     *
     * @brief Get the PortProfile of the Port
     *
     * Get the PortProfile of this Port.
     *
     * @return PortProfile
     *
     * @endif
     */
    const PortProfile& getPortProfile() const;
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] ConnectorProfileList���������
     *
     * Port���ݻ����� ConnectorProfile �� sequence ���֤���
     * ConnectorProfile �� Port �֤���³�ץ�ե����������ݻ����빽¤�ΤǤ��ꡢ
     * ��³����Port�֤Ǿ���򴹤�Ԥ�����Ϣ���뤹�٤Ƥ� Port ��Ʊ����ͤ�
     * �ݻ�����롣
     * ConnectorProfile �ϰʲ��Υ��С����ݻ����Ƥ��롣
     *
     * - name         [string ��] ���Υ��ͥ�����̾����
     * - connector_id [string ��] ��ˡ�����ID
     * - ports        [Port sequnce] ���Υ��ͥ����˴�Ϣ���� Port �Υ��֥�������
     *                ��ե���󥹤Υ������󥹡�
     * - properties   [NVList ��] ����¾�Υץ�ѥƥ���
     *
     * @return ���� Port ���ݻ����� ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfileList of the Port
     *
     * This operation returns a list of the ConnectorProfiles of the Port.
     * ConnectorProfile includes the connection information that describes 
     * relation between (among) Ports, and Ports exchange the ConnectionProfile
     * on connection process and hold the same information in every Port.
     * ConnectionProfile has the following members:
     *
     * - name         [string type] The name of the connection.
     * - connector_id [string type] Unique identifier.
     * - ports        [Port sequnce] The sequence of Port's object reference
     *                that are related the connection.
     * - properties   [NVList type] The other properties.
     *
     * @return ConnectorProfileList of the Port
     *
     * @endif
     */
    virtual ConnectorProfileList* get_connector_profiles()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] ConnectorProfile ���������
     *
     * connector_id �ǻ��ꤵ�줿 ConnectorProfile ���֤���
     * ���ꤷ�� connector_id ����� ConnectorProfile ���ݻ����Ƥ��ʤ����ϡ�
     * ���� ConnectorProfile ���֤���
     *
     * @param connector_id ConnectorProfile �� ID
     *
     * @return connector_id �ǻ��ꤵ�줿 ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfile
     *
     * This operation returns the ConnectorProfiles specified connector_id.
     * If ConnectorProfile with specified connector_id is not included,
     * empty ConnectorProfile is returned.
     *
     * @param connector_id ID of the ConnectorProfile
     *
     * @return the ConnectorProfile identified by the connector_id
     *
     * @endif
     */
    virtual ConnectorProfile* get_connector_profile(const char* connector_id)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³��Ԥ�
     *
     * Ϳ����줿 ConnectoionProfile �ξ�����ˡ�Port�֤���³���Ω���롣
     * ���ץꥱ�������ץ����¦�ϡ����Ĥ��Υ���ݡ��ͥ�Ȥ�����ʣ����
     * Port ����³��������硢Ŭ�ڤ��ͤ򥻥åȤ��� ConnectorProfile ��
     * connect() �ΰ����Ȥ���Ϳ���ƥ����뤹�뤳�Ȥˤ�ꡢ��Ϣ���� Port ��
     * ��³���Ω���롣
     *
     * connect() ��Ϳ���� ConnectorProfile �Υ��С��Τ�����name, ports, 
     * properties ���С����Ф��ƥǡ����򥻥åȤ��ʤ���Фʤ�ʤ���
     *
     * OutPort ¦�� connect() �Ǥϰʲ��Υ������󥹤ǽ������Ԥ��롣
     *
     * 1. OutPort �˴�Ϣ���� connector �������������ӥ��å�
     *
     * 2. InPort�˴�Ϣ���� connector ����μ���
     *  - ConnectorProfile::properties["dataport.corba_any.inport_ref"]��
     *    OutPortAny �Υ��֥������ȥ�ե���󥹤����ꤵ��Ƥ����硢
     *    ��ե���󥹤��������Consumer���֥������Ȥ˥��åȤ��롣
     *    ��ե���󥹤����åȤ���Ƥ��ʤ����̵�뤷�Ʒ�³��
     *    (OutPort��connect() �ƤӽФ��Υ���ȥ�ݥ���Ȥξ��ϡ�
     *    InPort�Υ��֥������ȥ�ե���󥹤ϥ��åȤ���Ƥ��ʤ��Ϥ��Ǥ��롣)
     *
     * 3. PortBase::connect() �򥳡���
     *    Port����³�δ��ܽ������Ԥ��롣
     *
     * 4. �嵭2.��InPort�Υ�ե���󥹤������Ǥ��ʤ���С�����InPort��
     *    ��Ϣ���� connector �����������롣
     *
     * 5. ConnectorProfile::properties ��Ϳ����줿���󤫤顢
     *    OutPort¦�ν����������Ԥ���
     *
     * - [dataport.interface_type]<BR>
     * -- CORBA_Any �ξ��: 
     *    InPortAny ���̤��ƥǡ����򴹤���롣
     *    ConnectorProfile::properties["dataport.corba_any.inport_ref"]��
     *    InPortAny �Υ��֥������ȥ�ե���󥹤򥻥åȤ��롣<BR>
     * -- RawTCP �ξ��: Raw TCP socket ���̤��ƥǡ����򴹤���롣
     *    ConnectorProfile::properties["dataport.raw_tcp.server_addr"]
     *    ��InPort¦�Υ����Х��ɥ쥹�򥻥åȤ��롣
     *
     * - [dataport.dataflow_type]<BR>
     * -- Push�ξ��: Subscriber���������롣Subscriber�Υ����פϡ�
     *    dataport.subscription_type �����ꤵ��Ƥ��롣<BR>
     * -- Pull�ξ��: InPort¦���ǡ�����Pull���Ǽ������뤿�ᡢ
     *    �ä˲��⤹��ɬ�פ�̵����
     *
     * - [dataport.subscription_type]<BR>
     * -- Once�ξ��: SubscriberOnce���������롣<BR>
     * -- New�ξ��: SubscriberNew���������롣<BR>
     * -- Periodic�ξ��: SubscriberPeriodic���������롣
     *
     * - [dataport.push_interval]<BR>
     * -- dataport.subscription_type=Periodic�ξ����������ꤹ�롣
     *
     * 6. �嵭�ν����Τ�����ĤǤ⥨�顼�Ǥ���С����顼�꥿���󤹤롣
     *    ����˽������Ԥ�줿���� RTC::RTC_OK �ǥ꥿���󤹤롣
     *  
     * @param connector_profile ConnectorProfile
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation establishes connection according to the given 
     * ConnectionProfile inforamtion. 
     * Application programs, which is going to establish the connection 
     * among Ports owned by RT-Components, have to set valid values to the 
     * ConnectorProfile and give it to the argument of connect() operation.
     * 
     * name, ports and properties which are members of ConnectorProfile,
     * should be set valid values before giving to the argument of connect()
     * operation.
     *
     * The following sequences are executed in connect() of OutPort side.
     *
     * 1. Create and set connector information associated with OutPort.
     *
     * 2. Get connector information associated with InPort.
     *  - If the object reference of OutPortAny is set in 
     *    ConnectorProfile::properties["dataport.corba_any.inport_ref"],
     *    get its reference and set to Consumer object.
     *    If the object reference of OutPortAny is not set, 
     *    it ignores and continues.
     *    (If OutPort is an entry point of connect call, the object reference
     *    of InPort sure not to be set.)
     *
     * 3. Invoke PortBase::connect().
     *    Execute the basic processing of Port's connection.
     *
     * 4. If the reference of InPort cannot be got (by step2), get connector
     *    information associated with InPort again.
     *
     * 5. Initialize on OutPort side from information given by
     *    ConnectorProfile::properties.
     *
     * - [dataport.interface_type]<BR>
     * -- For CORBA_Any: 
     *    Exchange data via InPortAny.
     *    Set the object reference of InPortAny to
     *    ConnectorProfile::properties["dataport.corba_any.inport_ref"].
     * -- For RawTCP:
     *    Exechange data via Raw TCP socket.
     *    Set server address of InPort to
     *    ConnectorProfile::properties["dataport.raw_tcp.server_addr"].
     *
     * - [dataport.dataflow_type]<BR>
     * -- For Push: Create Subscriber. Type of Subscriber is set to
     *    dataport.subscription_type.<BR>
     * -- For Pull: Operate nothing since InPort side gets data in Pull type.
     *
     * - [dataport.subscription_type]<BR>
     * -- For Once: Create SubscriberOnce.<BR>
     * -- For New: Create SubscriberNew.<BR>
     * -- For Periodic: Create SubscriberPeriodic.
     *
     * - [dataport.push_interval]<BR>
     * -- For dataport.subscription_type=Periodic, the cycle is set.
     *
     * 6. If error occurs in one of the above processings, return error.
     *    If processing has completed successfully, return RTC::RTC_OK.
     *  
     * @param connector_profile The ConnectorProfile.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t connect(ConnectorProfile& connector_profile)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³���Τ�Ԥ�
     *
     * ���Υ��ڥ졼�����ϡ�Port�֤���³���Ԥ���ݤˡ�Port�֤�����Ū��
     * �ƤФ�륪�ڥ졼�����Ǥ��롣
     * ConnectorProfile �ˤ���³�о� Port �Υꥹ�Ⱦ����ݻ�����Ƥ��롣Port ��
     * ConnectorProfile ���ݻ�����ȤȤ�ˡ��ꥹ����μ� Port �� notify_connect 
     * ��ƤӽФ��������ơ��ݡ��Ȥ򥳥ͥ������ɲä����塢ConnectorProfile ��
     * �ƤӤ������ Port �����ꤷ���ƤӤ��������֤������Τ褦�� ConnectorProfile
     * ����Ѥ�����³���Τ���ã����Ƥ�����
     *
     * @param connector_profile ConnectorProfile
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Notify the Ports connection
     *
     * This operation is invoked between Ports internally when the connection
     * is established.
     * A ConnectorProfile has a sequence of port references. This Port 
     * stores the ConnectorProfile and invokes the notify_connect operation of 
     * the next Port in the sequence. As ports are added to the connector, 
     * Port references are added to the ConnectorProfile and provided to 
     * the caller. In this way, notification of connection is propagated with
     * the ConnectorProfile.
     *
     * @param connector_profile The ConnectorProfile.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t notify_connect(ConnectorProfile& connector_profile)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³��������
     *
     * ���Υ��ڥ졼��������³��Ω������³���Ф���Ϳ������ connector_id ��
     * �б�����ԥ� Port �Ȥ���³�������롣
     * Port �� ConnectorProfile ��Υݡ��ȥꥹ�Ȥ˴ޤޤ�룱�ĤΥݡ��Ȥ�
     * notify_disconnect ��ƤӤ�������³��������Τ� notify_disconnect �ˤ�ä�
     * �¹Ԥ���롣
     *
     * @param connector_id ConnectorProfile �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Disconnect the Port
     *
     * This operation destroys connection between this port and the peer port
     * according to given connector_id when the connection established.
     * This port invokes the notify_disconnect of one of the ports included
     * a port list in ConnectorProfile stored when the connection was
     * established. The notification of disconnection is executed by
     * the notify_disconnect.
     *
     * @param connector_id The ID of the ConnectorProfile.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t disconnect(const char* connector_id)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³������Τ�Ԥ�
     *
     * ���Υ��ڥ졼�����ϡ�Port�֤���³������Ԥ���ݤˡ�Port�֤�����Ū��
     * �ƤФ�륪�ڥ졼�����Ǥ��롣
     * ���Υ��ڥ졼�����ϡ��������� Port ����³����Ƥ���¾�� Port ����³���
     * �����Τ��롣��³����оݤ� Port ��ID�ˤ�äƻ��ꤵ��롣Port ��
     * ConnectorProfile ��Υݡ��ȥꥹ����μ� Port �� notify_disconnect ��Ƥ�
     * �Ф����ݡ��Ȥ���³����������� ConnectorProfile ���鳺������ Port ��
     * ���󤬺������롣���Τ褦�� notify_disconnect ����Ѥ�����³������Τ�
     * ��ã����Ƥ�����
     *
     * @param connector_id ConnectorProfile �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Notify the Ports disconnection
     *
     * This operation is invoked between Ports internally when the connection
     * is destroied.
     * This operation notifies a disconnection between corresponding port and
     * the other ports. The disconnected Port is identified by the given ID.
     * This port invokes the notify_disconnect operation of the next Port
     * in the sequence of the ConnectorProfile that was stored when the 
     * connection was established. As ports are disconnected, corresponding port
     * information are removed from the ConnectorProfile. In this way, the
     * notification of disconnection is propagated by the notify_disconnect
     * operation.
     *
     * @param connector_id The ID of the ConnectorProfile.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t notify_disconnect(const char* connector_id)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ������³��������
     *
     * ���Υ��ڥ졼�����Ϥ��� Port �˴�Ϣ�������Ƥ���³�������롣
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Disconnect the All Ports
     *
     * This operation destroys all connections associated with this Port.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t disconnect_all()
      throw (CORBA::SystemException);
    
    //============================================================
    // Local operations
    //============================================================
    /*!
     * @if jp
     * @brief Port ��̾�������ꤹ��
     *
     * Port ��̾�������ꤹ�롣����̾���� Port ���ݻ����� PortProfile.name
     * ��ȿ�Ǥ���롣
     *
     * @param name Port ��̾��
     *
     * @else
     * @brief Set the name of this Port
     *
     * This operation sets the name of this Port. The given Port's name is
     * applied to Port's PortProfile.name.
     *
     * @param name The name of this Port.
     *
     * @endif
     */
    void setName(const char* name);
    
    /*!
     * @if jp
     * @brief PortProfile���������
     *
     * Port���ݻ����� PortProfile �� const ���Ȥ��֤���
     *
     * @return ���� Port �� PortProfile
     *
     * @else
     * @brief Get the PortProfile of the Port
     *
     * This operation returns const reference of the PortProfile.
     *
     * @return PortProfile of the Port
     *
     * @endif
     */
    const PortProfile& getProfile() const;
    
    /*!
     * @if jp
     *
     * @brief Port �Υ��֥������Ȼ��Ȥ����ꤹ��
     *
     * ���Υ��ڥ졼������ Port �� PortProfile �ˤ��� Port ���Ȥ�
     * ���֥������Ȼ��Ȥ����ꤹ�롣
     *
     * @param port_ref ���� Port �Υ��֥������Ȼ���
     *
     * @else
     *
     * @brief Set the object reference of this Port
     *
     * This operation sets the object reference itself
     * to the Port's PortProfile.
     *
     * @param port_ref The object reference of this Port.
     *
     * @endif
     */
    void setPortRef(PortService_ptr port_ref);
    
    /*!
     * @if jp
     *
     * @brief Port �Υ��֥������Ȼ��Ȥ��������
     *
     * ���Υ��ڥ졼������ Port �� PortProfile ���ݻ����Ƥ���
     * ���� Port ���ȤΥ��֥������Ȼ��Ȥ�������롣
     *
     * @return ���� Port �Υ��֥������Ȼ���
     *
     * @else
     *
     * @brief Get the object reference of this Port
     *
     * This operation returns the object reference
     * that is stored in the Port's PortProfile.
     *
     * @return The object reference of this Port.
     *
     * @endif
     */
    PortService_ptr getPortRef();
    
    /*!
     * @if jp
     *
     * @brief Port �� owner �� RTObject ����ꤹ��
     *
     * ���Υ��ڥ졼������ Port �� PortProfile.owner �����ꤹ�롣
     *
     * @param owner ���� Port ���ͭ���� RTObject �λ���
     *
     * @else
     *
     * @brief Set the owner RTObject of the Port
     *
     * This operation sets the owner RTObject of this Port.
     *
     * @param owner The owner RTObject's reference of this Port
     *
     * @endif
     */
    void setOwner(RTObject_ptr owner);
    
    //============================================================
    // protected operations
    //============================================================
  protected:
    /*! @if jp
     *
     * @brief Interface ������������
     *
     * ���Υ��ڥ졼�����ϡ�notify_connect() �����������󥹤λϤ�˥�����
     * ������貾�۴ؿ��Ǥ��롣
     * notify_connect() �Ǥϡ�
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * �ν�� protected �ؿ��������뤵����³�������Ԥ��롣
     * <br>
     * ��� Port �ǤϤ��Υ��ڥ졼�����򥪡��С��饤�ɤ��������Ȥ���
     * Ϳ����줿 ConnectorProfile �˽���������Ԥ����ѥ�᡼������Ŭ��
     * �Ǥ���С�RteurnCode_t ���Υ��顼�����ɤ��֤���
     * �̾� publishInterafaces() ��ˤ����Ƥϡ����� Port ��°����
     * ���󥿡��ե������˴ؤ������� ConnectorProfile ���Ф���Ŭ�ڤ����ꤷ
     * ¾�� Port �����Τ��ʤ���Фʤ�ʤ���
     * <br>
     * �ޤ������δؿ��������뤵����ʳ��Ǥϡ�¾�� Port �� Interface �˴ؤ���
     * ����Ϥ��٤ƴޤޤ�Ƥ��ʤ��Τǡ�¾�� Port �� Interface ������������
     * �� subscribeInterfaces() ��ǹԤ���٤��Ǥ��롣
     * <br>
     * ���Υ��ڥ졼�����ϡ������� connector_id ���Ф��Ƥ���³��������
     * ��¸�� connector_id ���Ф��ƤϹ�����Ŭ�ڤ˹Ԥ���ɬ�פ����롣
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Publish interface information
     *
     * This operation is pure virutal function that would be called at the
     * beginning of the notify_connect() process sequence.
     * In the notify_connect(), the following methods would be called in order.
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile() 
     *
     * In the concrete Port, this method should be overridden. This method
     * processes the given ConnectorProfile argument and if the given parameter
     * is invalid, it would return error code of ReturnCode_t.
     * Usually, publishInterfaces() method should set interfaces information
     * owned by this Port, and publish it to the other Ports.
     * <br>
     * When this method is called, other Ports' interfaces information may not
     * be completed. Therefore, the process to obtain other Port's interfaces
     * information should be done in the subscribeInterfaces() method.
     * <br>
     * This operation should create the new connection for the new
     * connector_id, and should update the connection for the existing
     * connection_id.
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile) = 0;
    
    /*!
     * @if jp
     *
     * @brief ���� Port ���Ф��� notify_connect() �򥳡��뤹��
     *
     * ConnectorProfile �� port_ref ��˳�Ǽ����Ƥ��� Port �Υ��֥�������
     * ��ե���󥹤Υ������󥹤��椫�顢���Ȥ� Port �μ��� Port ���Ф���
     * notify_connect() �򥳡��뤹�롣
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Call notify_connect() of the next Port
     *
     * This operation calls the notify_connect() of the next Port's 
     * that stored in ConnectorProfile's port_ref sequence.
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t connectNext(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief ���� Port ���Ф��� notify_disconnect() �򥳡��뤹��
     *
     * ConnectorProfile �� port_ref ��˳�Ǽ����Ƥ��� Port �Υ��֥�������
     * ��ե���󥹤Υ������󥹤��椫�顢���Ȥ� Port �μ��� Port ���Ф���
     * notify_disconnect() �򥳡��뤹�롣
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Call notify_disconnect() of the next Port
     *
     * This operation calls the notify_disconnect() of the next Port's 
     * that stored in ConnectorProfile's port_ref sequence.
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t disconnectNext(ConnectorProfile& connector_profile);
    
    /*! @if jp
     *
     * @brief Interface ������������
     *
     * ���Υ��ڥ졼�����ϡ�notify_connect() �����������󥹤���֤˥�����
     * ������貾�۴ؿ��Ǥ��롣
     * notify_connect() �Ǥϡ�
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * �ν�� protected �ؿ��������뤵����³�������Ԥ��롣
     * <br>
     * ��� Port �ǤϤ��Υ��ڥ졼�����򥪡��С��饤�ɤ��������Ȥ���
     * Ϳ����줿 ConnectorProfile �˽���������Ԥ����ѥ�᡼������Ŭ��
     * �Ǥ���С�RteurnCode_t ���Υ��顼�����ɤ��֤���
     * ���� ConnectorProfile �ˤ�¾�� Port �� Interface �˴ؤ������
     * ���ƴޤޤ�Ƥ��롣
     * �̾� subscribeInterafaces() ��ˤ����Ƥϡ����� Port �����Ѥ���
     * Interface �˴ؤ���������������׵�¦�Υ��󥿡��ե��������Ф���
     * ��������ꤷ�ʤ���Фʤ�ʤ���
     * <br>
     * ���Υ��ڥ졼�����ϡ������� connector_id ���Ф��Ƥ���³��������
     * ��¸�� connector_id ���Ф��ƤϹ�����Ŭ�ڤ˹Ԥ���ɬ�פ����롣
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Publish interface information
     *
     * This operation is pure virutal function that would be called at the
     * mid-flow of the notify_connect() process sequence.
     * In the notify_connect(), the following methods would be called in order.
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * In the concrete Port, this method should be overridden. This method
     * processes the given ConnectorProfile argument and if the given parameter
     * is invalid, it would return error code of ReturnCode_t.
     * The given argument ConnectorProfile includes all the interfaces
     * information in it.
     * Usually, subscribeInterafaces() method obtains information of interfaces
     * from ConnectorProfile, and should set it to the interfaces that require
     * them.
     * <br>
     * This operation should create the new connection for the new
     * connector_id, and should update the connection for the existing
     * connection_id.
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile) = 0;
    
    /*! @if jp
     *
     * @brief Interface ����³��������
     *
     * ���Υ��ڥ졼�����ϡ�notify_disconnect() �����������󥹤ν����˥�����
     * ������貾�۴ؿ��Ǥ��롣
     * notify_disconnect() �Ǥϡ�
     * - disconnectNext()
     * - unsubscribeInterfaces()
     * - eraseConnectorProfile()
     * �ν�� protected �ؿ��������뤵����³����������Ԥ��롣
     * <br>
     * ��� Port �ǤϤ��Υ��ڥ졼�����򥪡��С��饤�ɤ��������Ȥ���
     * Ϳ����줿 ConnectorProfile �˽�����³���������Ԥ���
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @else
     *
     * @brief Disconnect interface connection
     *
     * This operation is pure virutal function that would be called at the
     * end of the notify_disconnect() process sequence.
     * In the notify_disconnect(), the following methods would be called
     * in order to disconnect.
     * - disconnectNext()
     * - unsubscribeInterfaces()
     * - eraseConnectorProfile() 
     *  <br>
     * In the concrete Port, this method should be overridden. This method
     * processes the given ConnectorProfile argument and disconnect interface
     * connection.
     *
     * @param connector_profile The connection profile information
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile) = 0;
    
    //============================================================
    // protected utility functions
    //============================================================
    /*!
     * @if jp
     *
     * @brief ConnectorProfile �� connector_id �ե�����ɤ������ɤ���Ƚ��
     *
     * ���ꤵ�줿 ConnectorProfile �� connector_id �����Ǥ��뤫�ɤ�����Ƚ���
     * �Ԥ���
     *
     * @param connector_profile Ƚ���оݥ��ͥ����ץ�ե�����
     *
     * @return ������Ϳ����줿 ConnectorProfile �� connector_id �����Ǥ���С�
     *         true�������Ǥʤ���� false ���֤���
     *
     * @else
     *
     * @brief Check whether connector_id of ConnectorProfile is empty
     *
     * Check whether connector_id of specified ConnectorProfile is empty.
     * 
     * @param connector_profile Target ConnectorProfile for the check
     *
     * @return If the given ConnectorProfile's connector_id is empty string,
     *         it returns true.
     *
     * @endif
     */
    bool isEmptyId(const ConnectorProfile& connector_profile) const;
    
    /*!
     * @if jp
     *
     * @brief UUID����������
     *
     * ���Υ��ڥ졼������ UUID ���������롣
     *
     * @return uuid
     *
     * @else
     *
     * @brief Generate the UUID
     *
     * This operation generates UUID.
     *
     * @return uuid
     *
     * @endif
     */
    const std::string getUUID() const;
    
    /*!
     * @if jp
     *
     * @brief UUID�������� ConnectorProfile �˥��åȤ���
     *
     * ���Υ��ڥ졼������ UUID ����������ConnectorProfile �˥��åȤ��롣
     *
     * @param connector_profile connector_id �򥻥åȤ��� ConnectorProfile
     *
     * @else
     *
     * @brief Generate and set the UUID to the ConnectorProfile
     *
     * This operation generates and set UUID to the ConnectorProfile.
     *
     * @param connector_profile ConnectorProfile to be set connector_id
     *
     * @endif
     */
    void setUUID(ConnectorProfile& connector_profile) const;
    
    /*!
     * @if jp
     *
     * @brief id ����¸�� ConnectorProfile �Τ�Τ��ɤ���Ƚ�ꤹ��
     *
     * ���Υ��ڥ졼������Ϳ����줿 ID ����¸�� ConnectorProfile �Υꥹ�����
     * ¸�ߤ��뤫�ɤ���Ƚ�ꤹ�롣
     *
     * @param id Ƚ�ꤹ�� connector_id
     *
     * @return id ��¸��Ƚ����
     *
     * @else
     *
     * @brief Check whether the given id exists in stored ConnectorProfiles
     *
     * This operation returns boolean whether the given id exists in 
     * the Port's ConnectorProfiles.
     *
     * @param id connector_id to be find in Port's ConnectorProfiles
     *
     * @return id exestance resutl
     *
     * @endif
     */
    bool isExistingConnId(const char* id);
    
    /*!
     * @if jp
     *
     * @brief id ����� ConnectorProfile ��õ��
     *
     * ���Υ��ڥ졼������Ϳ����줿 ID ����� ConnectorProfile �� Port ��
     * ��� ConnectorProfile �Υꥹ���椫��õ����
     * �⤷��Ʊ��� id ����� ConnectorProfile ���ʤ���С����� ConnectorProfile
     * ���֤���롣
     *
     * @param id �������� connector_id
     *
     * @return connector_id ����� ConnectorProfile
     *
     * @else
     *
     * @brief Find ConnectorProfile with id
     *
     * This operation returns ConnectorProfile with the given id from Port's
     * ConnectorProfiles' list.
     * If the ConnectorProfile with connector id that is identical with the
     * given id does not exist, empty ConnectorProfile is returned.
     *
     * @param id the connector_id to be searched in Port's ConnectorProfiles
     *
     * @return CoonectorProfile with connector_id
     *
     * @endif
     */
    ConnectorProfile findConnProfile(const char* id);
    
    /*!
     * @if jp
     *
     * @brief id ����� ConnectorProfile ��õ��
     *
     * ���Υ��ڥ졼������Ϳ����줿 ID ����� ConnectorProfile �� Port ��
     * ��� ConnectorProfile �Υꥹ���椫��õ������ǥå������֤���
     * �⤷��Ʊ��� id ����� ConnectorProfile ���ʤ���С�-1 ���֤���
     *
     * @param id �������� connector_id
     *
     * @return Port �� ConnectorProfile �ꥹ�ȤΥ���ǥå���
     *
     * @else
     *
     * @brief Find ConnectorProfile with id
     *
     * This operation returns ConnectorProfile with the given id from Port's
     * ConnectorProfiles' list.
     * If the ConnectorProfile with connector id that is identical with the
     * given id does not exist, -1 is returned.
     *
     * @param id the connector_id to be searched
     *
     * @return The index of ConnectorProfile of the Port
     *
     * @endif
     */
    CORBA::Long findConnProfileIndex(const char* id);
    
    /*!
     * @if jp
     *
     * @brief ConnectorProfile ���ɲä⤷���Ϲ���
     *
     * ���Υ��ڥ졼������Ϳ����줿 ConnectorProfile �� Port ���ɲä⤷����
     * ������¸���롣
     * Ϳ����줿 ConnectorProfile �� connector_id ��Ʊ�� ID �����
     * ConnectorProfile ���ꥹ�Ȥˤʤ���С��ꥹ�Ȥ��ɲä���
     * Ʊ�� ID ��¸�ߤ���� ConnectorProfile ������¸���롣
     *
     * @param connector_profile �ɲä⤷���Ϲ������� ConnectorProfile
     *
     * @else
     *
     * @brief Append or update the ConnectorProfile list
     *
     * This operation appends or updates ConnectorProfile of the Port
     * by the given ConnectorProfile.
     * If the connector_id of the given ConnectorProfile does not exist
     * in the Port's ConnectorProfile list, the given ConnectorProfile would be
     * append to the list. If the same id exists, the list would be updated.
     *
     * @param connector_profile the ConnectorProfile to be appended or updated
     *
     * @endif
     */
    void updateConnectorProfile(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief ConnectorProfile ��������
     *
     * ���Υ��ڥ졼������ Port �� PortProfile ���ݻ����Ƥ���
     * ConnectorProfileList �Τ���Ϳ����줿 id ����� ConnectorProfile
     * �������롣
     *
     * @param id ������� ConnectorProfile �� id
     *
     * @return ����˺���Ǥ������� true��
     *         ���ꤷ�� ConnectorProfile �����Ĥ���ʤ����� false ���֤�
     *
     * @else
     *
     * @brief Delete the ConnectorProfile
     *
     * This operation deletes a ConnectorProfile specified by id from
     * ConnectorProfileList owned by PortProfile of this Port.
     *
     * @param id The id of the ConnectorProfile to be deleted.
     *
     * @return true would be returned if it deleted correctly.
     *         false woluld be returned if specified ConnectorProfile
     *         cannot be found.
     *
     * @endif
     */
    bool eraseConnectorProfile(const char* id);
    
    /*!
     * @if jp
     *
     * @brief PortInterfaceProfile �� ���󥿡��ե���������Ͽ����
     *
     * ���Υ��ڥ졼������ Port ������ PortProfile �Ρ�PortInterfaceProfile
     * �˥��󥿡��ե������ξ�����ɲä��롣
     * ���ξ���ϡ�get_port_profile() �ˤ�ä������� PortProfile �Τ���
     * PortInterfaceProfile ���ͤ��ѹ�����ΤߤǤ��ꡢ�ºݤ˥��󥿡��ե�������
     * �󶡤������׵ᤷ���ꤹ����ˤϡ����֥��饹�ǡ� publishInterface() ,
     *  subscribeInterface() ���δؿ���Ŭ�ڤ˥����С��饤�ɤ����󥿡��ե�������
     * �󶡡��׵������Ԥ�ʤ���Фʤ�ʤ���
     *
     * ���󥿡��ե�����(�Υ��󥹥���)̾�� Port ��ǰ�դǤʤ���Фʤ�ʤ���
     * Ʊ̾�Υ��󥿡��ե����������Ǥ���Ͽ����Ƥ����硢���δؿ��� false ��
     * �֤���
     *
     * @param name ���󥿡��ե������Υ��󥹥��󥹤�̾��
     * @param type_name ���󥿡��ե������η���̾��
     * @param pol ���󥿡��ե�������°�� (RTC::PROVIDED �⤷���� RTC:REQUIRED)
     *
     * @return ���󥿡��ե�������Ͽ������̡�
     *         Ʊ̾�Υ��󥿡��ե�������������Ͽ����Ƥ���� false ���֤���
     *
     * @else
     *
     * @brief Append an interface to the PortInterfaceProfile
     *
     * This operation appends interface information to the PortInterfaceProfile
     * that is owned by the Port.
     * The given interfaces information only updates PortInterfaceProfile of
     * PortProfile that is obtained through get_port_profile().
     * In order to provide and require interfaces, proper functions (for
     * example publishInterface(), subscribeInterface() and so on) should be
     * overridden in subclasses, and these functions provide concrete interface
     * connection and disconnection functionality.
     *
     * The interface (instance) name have to be unique in the Port.
     * If the given interface name is identical with stored interface name,
     * this function returns false.
     *
     * @param name The instance name of the interface.
     * @param type_name The type name of the interface.
     * @param pol The interface's polarity (RTC::PROVIDED or RTC:REQUIRED)
     *
     * @return false would be returned if the same name is already registered.
     *
     * @endif
     */
    bool appendInterface(const char* name, const char* type_name,
			 PortInterfacePolarity pol);
    
    /*!
     * @if jp
     *
     * @brief PortInterfaceProfile ���饤�󥿡��ե�������Ͽ��������
     *
     * ���Υ��ڥ졼������ Port ������ PortProfile �Ρ�PortInterfaceProfile
     * ���饤�󥿡��ե������ξ���������롣
     *
     * @param name ���󥿡��ե������Υ��󥹥��󥹤�̾��
     * @param pol ���󥿡��ե�������°�� (RTC::PROVIDED �⤷���� RTC:REQUIRED)
     *
     * @return ���󥿡��ե��������������̡�
     *         ���󥿡��ե���������Ͽ����Ƥ��ʤ���� false ���֤���
     *
     * @else
     *
     * @brief Delete the interface registration from the PortInterfaceProfile
     *
     * This operation deletes interface information from the
     * PortInterfaceProfile that is owned by the Port.
     *
     * @param name The instance name of the interface.
     * @param pol The interface's polarity (RTC::PROVIDED or RTC:REQUIRED)
     *
     * @return Delete processing result of interface.
     *         false would be returned if the given name is not registered.
     *
     * @endif
     */
    bool deleteInterface(const char* name, PortInterfacePolarity pol);
    
    /*!
     * @if jp
     *
     * @brief PortProfile �� properties �� NameValue �ͤ��ɲä���
     *
     * PortProfile �� properties �� NameValue �ͤ��ɲä��롣
     * �ɲä���ǡ����η���ValueType�ǻ��ꤹ�롣
     *
     * @param key properties �� name
     * @param value properties �� value
     *
     * @else
     *
     * @brief Add NameValue data to PortProfile's properties
     *
     * Add NameValue data to PortProfile's properties.
     * Type of additional data is specified by ValueType.
     *
     * @param key The name of properties
     * @param value The value of properties
     *
     * @endif
     */
    template <class ValueType>
    void addProperty(const char* key, ValueType value)
    {
      CORBA_SeqUtil::push_back(m_profile.properties,
			       NVUtil::newNV(key, value));
    }
    
  protected:
    /*!
     * @if jp
     * @brief Port �� PortProfile
     * @else
     * @brief PortProfile of the Port
     * @endif
     */
    PortProfile m_profile;
    
    /*!
     * @if jp
     * @brief Port �� ���֥������Ȼ���
     * @else
     * @brief Object Reference of the Port
     * @endif
     */
    RTC::PortService_var m_objref;
    mutable coil::Mutex m_profile_mutex;
    typedef coil::Guard<coil::Mutex> Guard;
    
    //============================================================
    // Functor
    //============================================================
    /*!
     * @if jp
     * @brief instance_name ����� PortInterfaceProfile ��õ�� Functor
     * @else
     * @brief Functor to find a PortInterfaceProfile named instance_name
     * @endif
     */
    struct if_name
    {
      if_name(const char* name) : m_name(name) {};
      bool operator()(const PortInterfaceProfile& prof)
      {
	return m_name == std::string(prof.instance_name);
      }
      std::string m_name;
    };
    
    /*!
     * @if jp
     * @brief id ����� ConnectorProfile ��õ�� Functor
     * @else
     * @brief Functor to find a ConnectorProfile named id
     * @endif
     */
    struct find_conn_id
    {
      find_conn_id(const char* id) : m_id(id) {};
      bool operator()(const ConnectorProfile& cprof)
      {
	return m_id == std::string(cprof.connector_id);
      }
      std::string m_id;
    };
    
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯������ port_ref ��Ʊ�����֥������Ȼ��Ȥ�õ�� Functor
     * @else
     * @brief Functor to find the object reference that is identical port_ref
     * @endif
     */
    struct find_port_ref
    {
      find_port_ref(PortService_ptr port_ref) : m_port(port_ref) {};
      bool operator()(PortService_ptr port_ref)
      {
	return m_port->_is_equivalent(port_ref);
      }
      PortService_ptr m_port;
    };
    
    /*!
     * @if jp
     * @brief Port ����³��Ԥ� Functor
     * @else
     * @brief Functor to connect Ports
     * @endif
     */
    struct connect_func
    {
      PortService_var port_ref;
      ConnectorProfile connector_profile;
      ReturnCode_t return_code;
      
      connect_func() {};
      connect_func(PortService_ptr p, ConnectorProfile& prof)
	: port_ref(p), connector_profile(prof), return_code(RTC::RTC_OK) {};
      void operator()(PortService_ptr p)
      {
	if (!port_ref->_is_equivalent(p))
	  {
	    ReturnCode_t retval;
	    retval = p->notify_connect(connector_profile);
	    if (retval != RTC::RTC_OK)
	      {
		return_code = retval;
	      }
	  }
      }
    };
    
    /*!
     * @if jp
     * @brief Port ����³�����Ԥ� Functor
     * @else
     * @brief Functor to disconnect Ports
     * @endif
     */
    struct disconnect_func
    {
      PortService_var port_ref;
      ConnectorProfile connector_profile;
      ReturnCode_t return_code;
      
      disconnect_func() : return_code(RTC::RTC_OK) {};
      disconnect_func(PortService_ptr p, ConnectorProfile& prof)
	: port_ref(p), connector_profile(prof), return_code(RTC::RTC_OK) {};
      void operator()(PortService_ptr p)
      {
	if (!port_ref->_is_equivalent(p))
	  {
	    ReturnCode_t retval;
	    retval = p->disconnect(connector_profile.connector_id);
	    if (retval != RTC::RTC_OK)
	      {
		return_code = retval;
	      }
	  }
      }
    };
    
    /*!
     * @if jp
     * @brief Port ������³�����Ԥ� Functor
     * @else
     * @brief Functor to disconnect all Ports
     * @endif
     */
    struct disconnect_all_func
    {
      ReturnCode_t return_code;
      PortBase* port;
      
      disconnect_all_func() {};
      disconnect_all_func(PortBase* p) 
	: return_code(RTC::RTC_OK), port(p) {};
      void operator()(ConnectorProfile& p)
      {
	ReturnCode_t retval;
	retval = port->disconnect(p.connector_id);
	if (retval != RTC::RTC_OK)
	  {
	    return_code = retval;
	  }
      }
    };
    
    /*!
     * @if jp
     * @brief name �� polarity ���� interface ��õ�� Functor
     * @else
     * @brief Functor to find interface from name and polarity
     * @endif
     */
    struct find_interface
    {
      find_interface(const char* name, PortInterfacePolarity pol)
	: m_name(name), m_pol(pol)
      {}
      
      bool operator()(const PortInterfaceProfile& prof)
      {
	std::string name(CORBA::string_dup(prof.instance_name));
	return ((m_name == name) && (m_pol == prof.polarity));
      }
      std::string m_name;
      PortInterfacePolarity m_pol;
    };
  };
};
#endif // PortBase_h
