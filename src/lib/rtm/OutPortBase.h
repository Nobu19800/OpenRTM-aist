// -*- C++ -*-
/*!
 * @file OutPortBase.h
 * @brief InPortBase base class
 * @date $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
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

#ifndef OutPortBase_h
#define OutPortBase_h

#include <vector>
#include <string>

#include <coil/Properties.h>
#include <coil/stringutil.h>

#include <rtm/PortBase.h>
#include <rtm/InPortConsumer.h>
#include <rtm/OutPortProvider.h>
#include <rtm/ConnectorBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/SystemLogger.h>

namespace RTC
{
  class PublisherBase;
  class ConnectorBase;
  class OutPortConnector;
  /*!
   * @if jp
   *
   * @class OutPortBase
   *
   * @brief OutPort ���쥯�饹
   * 
   * OutPort �δ��쥯�饹��
   *
   *
   *
   * Properties: port.outport
   * �ץ�ѥƥ���
   *
   * - port.outport
   * - port.outport.[name]
   * ConnectorProfile.properties �ξ���
   * - dataport.outport
   *
   * �ʲ��˻��ꤷ����Τ��Ϥ���롣
   * (port.outport.[name]��ͥ�褵���)
   * ����ˡ������Υץ�ѥƥ�����³���� ConnectorProfile �ˤ��
   * �Ϥ�����礬���ꡢ���ξ��� ConnectorProfile ��ͥ�褵��롣
   *
   * - input.throughput.profile: enable
   * - input.throughput.update_rate: count [n/count]
   * - input.throughput.total_bytes: [bytes]
   * - input.throughput.total_count: [n]
   * - input.throughput.max_size: [bytes]
   * - input.throughput.min_size: [bytes]
   * - input.throughput.avg_size: [bytes]
   * - input.throughput.byte_sec: [bytes/sec]
   *
   * - output.throughput.profile: enable
   * - output.throughput.update_rate: count [n/count]
   * - output.throughput.total_bytes: [bytes]
   * - output.throughput.total_count:[n]
   * - output.throughput.max_size: [bytes]
   * - output.throughput.min_size: [bytes]
   * - output.throughput.avg_size: [bytes]
   * - output.throughput.max_sendtime: [sec]
   * - output.throughput.min_sendtime: [sec]
   * - output.throughput.avg_sendtime: [sec]
   * - output.throughput.byte_sec: [bytes/sec]
   *
   * dataport.dataflow_type
   * dataport.interface_type
   * dataport.subscription_type
   *
   * [buffer]
   *
   * - buffer.type:
   *     ���Ѳ�ǽ�ʥХåե��Υ�����
   *     ConnectorProfile �ξ������Ѥ���Хåե��Υ�����
   *     ̵����ξ��ϥǥե���Ȥ� ringbuffer �����Ѥ���롣
   *     ex. ringbuffer, shmbuffer, doublebuffer, etc.
   *     ������Consumer, Publisher �Υ����פˤ�äƤ�����ΥХåե�����
   *     �׵᤹�뤬���뤿��Ρ����ξ��ϻ����̵���Ȥʤ롣
   *
   * - buffer.length:
   *     �Хåե���Ĺ��
   *
   * - buffer.write.full_policy:
   *     ��񤭤��뤫�ɤ����Υݥꥷ��
   *     overwrite (���), do_nothing (���⤷�ʤ�), block (�֥�å�����)
   *     block ����ꤷ����硢���� timeout �ͤ���ꤹ��С�������ָ�
   *     �񤭹����Բ�ǽ�Ǥ���Х����ॢ���Ȥ��롣
   *
   * - buffer.write.timeout:
   *     �����ॢ���Ȼ��֤� [sec] �ǻ��ꤹ�롣
   *     1 sec -> 1.0, 1 ms -> 0.001, �����ॢ���Ȥ��ʤ� -> 0.0
   *
   * - buffer.read.empty_policy:
   *     �Хåե������ΤȤ����ɤ߽Ф��ݥꥷ��
   *     last (�Ǹ������), do_nothing (���⤷�ʤ�), block (�֥�å�����)
   *     block ����ꤷ����硢���� timeout �ͤ���ꤹ��С�������ָ�
   *     �ɤ߽Ф��Բ�ǽ�Ǥ���Х����ॢ���Ȥ��롣
   *
   * - buffer.read.timeout:
   *     �����ॢ���Ȼ��� [sec] �ǻ��ꤹ�롣
   *     1sec -> 1.0, 1ms -> 0.001, �����ॢ���Ȥ��ʤ� -> 0.0
   *
   * - ����¾�Хåե���˸�ͭ�ʥ��ץ����
   *
   *
   * [publihser]
   *
   * - publisher.types:
   *      ���Ѳ�ǽ�� Publisher �Υ�����
   *      new, periodic, flush, etc..
   *
   * - publisher.push.policy:
   *      InPort�إǡ�������������ݥꥷ��
   *      all: �Хåե��ˤ��ޤäƤ��뤹�٤�����
   *      fifo: �Хåե���FIFO�Ȥߤʤ�������
   *      skip: �Ť��ǡ�������������ְ���������
   *      new: ��˿������ǡ����Τߤ�����
   *
   * - publisher.push.skip_rate:
   *      push.policy=skip �ΤȤ��Υ����å�Ψ
   *      n: n������ˤҤȤ�����
   *
   * - publisher.periodic.rate:
   *
   * - publisher.thread.type:
   *       Publisher �Υ���åɤΥ�����
   * - publisher.thread.measurement.exec_time: yes/no
   * - publisher.thread.measurement.exec_count: number
   * - publisher.thread.measurement.period_time: yes/no
   * - publisher.thread.measurement.period_count: number
   *
   * [interface]
   *
   * - interface.types:
   *     OutPort interface�Υ�����
   *     ex. corba_cdr, corba_any, raw_tcp �ʤɥ���޶��ڤ�ǻ��ꡣ����
   *     ���ꤷ�ʤ�������Ѳ�ǽ�ʤ��٤ƤΥץ�Х��������Ѥ����
   *
   *
   *
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
   * 3. PortBase::connect() �򥳡���
   *    Port����³�δ��ܽ������Ԥ��롣
   * 4. �嵭2.��InPort�Υ�ե���󥹤������Ǥ��ʤ���С�����InPort��
   *    ��Ϣ���� connector �����������롣
   *
   * 5. ConnectorProfile::properties ��Ϳ����줿���󤫤顢
   *    OutPort¦�ν����������Ԥ���
   *
   * - [dataport.interface_type]
   * -- CORBA_Any �ξ��: 
   *    InPortAny ���̤��ƥǡ����򴹤���롣
   *    ConnectorProfile::properties["dataport.corba_any.inport_ref"]��
   *    InPortAny �Υ��֥������ȥ�ե���󥹤򥻥åȤ��롣
   * -- RawTCP �ξ��: Raw TCP socket ���̤��ƥǡ����򴹤���롣
   *    ConnectorProfile::properties["dataport.raw_tcp.server_addr"]
   *    ��InPort¦�Υ����Х��ɥ쥹�򥻥åȤ��롣
   *
   * - [dataport.dataflow_type]
   * -- Push�ξ��: Subscriber���������롣Subscriber�Υ����פϡ�
   *    dataport.subscription_type �����ꤵ��Ƥ��롣
   * -- Pull�ξ��: InPort¦���ǡ�����Pull���Ǽ������뤿�ᡢ
   *    �ä˲��⤹��ɬ�פ�̵����
   *
   * - [dataport.subscription_type]
   * -- Once�ξ��: SubscriberOnce���������롣
   * -- New�ξ��: SubscriberNew���������롣
   * -- Periodic�ξ��: SubscriberPeriodic���������롣
   *
   * - [dataport.push_rate]
   * -- dataport.subscription_type=Periodic�ξ����������ꤹ�롣
   *
   * 6. �嵭�ν����Τ�����ĤǤ⥨�顼�Ǥ���С����顼�꥿���󤹤롣
   *    ����˽������Ԥ�줿����RTC::RTC_OK�ǥ꥿���󤹤롣
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class OutPortBase
   *
   * @brief Output base class.
   *
   * The base class of OutPort<T> which are implementations of OutPort
   *
   * Form a kind of Observer pattern with OutPortBase and PublisherBase.
   * attach(), detach(), notify() of OutPortBase and
   * push() of PublisherBase are methods associated with the Observer pattern.
   *
   * @since 0.2.0
   *
   * @endif
   */
  class OutPortBase
    : public PortBase, public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM

    typedef std::vector<OutPortConnector*> ConnectorList;

    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     *
     * @param name �ݡ���̾
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port name
     *
     * @endif
     */
    OutPortBase(const char* name, const char* data_type);
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     * ��Ͽ���줿���Ƥ� Publisher �������롣
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     * Detach all subscribed Publishers.
     *
     * @endif
     */
    virtual ~OutPortBase(void);
    
    /*!
     * @if jp
     * @brief �ץ�ѥƥ��ν����
     *
     * OutPort�Υץ�ѥƥ�����������
     *
     * @else
     *
     * @brief Initializing properties
     *
     * This operation initializes outport's properties
     *
     * @endif
     */
    void init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief OutPort̾�Τμ���
     *
     * OutPort��̾�Τ�������롣
     *
     * @return �ݡ���̾��
     *
     * @else
     *
     * @brief Retrieve OutPort name
     *
     * Retrieve OutPort name
     *
     * @return the port name
     *
     * @endif
     */
    const char* name() const;

    /*!
     * @if jp
     * @brief �ץ�ѥƥ����������
     *
     * OutPort�Υץ�ѥƥ���������롣
     *
     * @return �ץ�ѥƥ�
     *
     * @else
     *
     * @brief Get properties
     *
     * Getting properties of this OutPort
     *
     * @return OutPort's properties
     *
     * @endif
     */
    coil::Properties& properties();

    /*!
     * @if jp
     * @brief Connector �����
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����������롣
     *
     * @return connector �Υꥹ��
     *
     * @else
     *
     * @brief Connector list
     *
     * This operation returns connector list
     *
     * @return connector list
     *
     * @endif
     */
    const std::vector<OutPortConnector*>& connectors();

    /*!
     * @if jp
     * @brief ConnectorProfile �����
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����Profile��������롣
     *
     * @return ConnectorProfile �Υꥹ��
     *
     * @else
     *
     * @brief ConnectorProfile list
     *
     * This operation returns ConnectorProfile list
     *
     * @return connector list
     *
     * @endif
     */
    ConnectorBase::ProfileList getConnectorProfiles();

    /*!
     * @if jp
     * @brief ConnectorId �����
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����ID��������롣
     *
     * @return ConnectorId �Υꥹ��
     *
     * @else
     *
     * @brief ConnectorId list
     *
     * This operation returns ConnectorId list
     *
     * @return connector list
     *
     * @endif
     */
    coil::vstring getConnectorIds();

    /*!
     * @if jp
     * @brief Connector��̾�������
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����̾����������롣
     *
     * @return Connector̾�Υꥹ��
     *
     * @else
     *
     * @brief Connector name list
     *
     * This operation returns Connector name list
     *
     * @return connector name list
     *
     * @endif
     */
    coil::vstring getConnectorNames();

    /*!
     * @if jp
     * @brief ConnectorProfile��ID�Ǽ���
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����ID�Ǽ������롣
     *
     * @param id Connector ID
     * @param prof ConnectorProfile
     * @return false ���ꤷ��ID���ʤ�
     *
     * @else
     *
     * @brief Getting ConnectorProfile by name
     *
     * This operation returns ConnectorProfile specified by name
     *
     * @param id Connector ID
     * @param prof ConnectorProfile
     * @return false��specified ID does not exist
     *
     * @endif
     */
    bool getConnectorProfileById(const char* id,
                                 ConnectorBase::Profile& prof);

    /*!
     * @if jp
     * @brief ConnectorProfile��̾���Ǽ���
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����̾���Ǽ������롣
     *
     * @param name Connector name
     * @param prof ConnectorProfile
     * @return false ���ꤷ��̾�����ʤ�
     *
     * @else
     *
     * @brief Getting ConnectorProfile by name
     *
     * This operation returns ConnectorProfile specified by name
     *
     * @param id Connector ID
     * @param prof ConnectorProfile
     * @return false specified name does not exist
     *
     * @endif
     */
    bool getConnectorProfileByName(const char* name,
                                   ConnectorBase::Profile& prof);

    /*!
     * @if jp
     * @brief ���󥿡��ե������ץ�ե�������������
     *
     * ���� OutPort ����ͭ���Ƥ��륤�󥿡��ե������Υץ�ե������
     * DataOutPort���Ф��Ƹ������뤿��Υ��ڥ졼�����
     * DataOutPort����ƤФ�뤳�Ȥ�տޤ��Ƥ���
     *
     * @param properties IF�ץ�ե������񤭹���NVList
     *
     * @else
     *
     * @brief Publish interface profile
     *
     * This operation publish interface profiles of this OutPort
     * to DataOutPort. This operation should be called from DataOutPort.
     *
     * @param properties itnerface profile
     *
     * @endif
     */
    bool publishInterfaceProfiles(SDOPackage::NVList& properties);

    /*!
     * @if jp
     * @brief Interface������������
     *
     * Interface�����������롣
     *
     * @param connector_profile Interface�����񤭹��ॳ�ͥ����ץ�ե�����
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.
     *
     * @param connector_profile The connector profile in which
     *                          interface information is written
     *
     * @endif
     */
    //    bool publishInterfaces(ConnectorProfile& connector_profile);

    /*!
     * @if jp
     * @brief Interface������������
     *
     * ���ͥ����ץ�ե������Ϳ����줿���󤫤顢���󥿡��ե����������
     * �������롣
     *
     * @param connector_profile ���󥿡��ե����������������륳�ͥ���
     *                          �ץ�ե�����
     *
     * @return ��Ͽ�������
     *
     * @else
     * @brief Subscribe interface
     *
     * This operation subscribe provided interface in the ConnectorProfile.
     *
     * @param connector_profile The ConnectorProfile that includes
     *                          provided interface information
     *
     * @return Subscription result
     *
     * @endif
     */
    //    bool subscribeInterfaces(const ConnectorProfile& connector_profile);

    /*!
     * @if jp
     * @brief ��Ͽ����Ƥ���Interface�����������
     *
     * ��³�򳫾줹�뤿��ˡ���Ͽ�ѤߤΥ��ͥ����ץ�ե�����������롣
     * �������롣
     *
     * @param connector_profile ���󥿡��ե���������������륳�ͥ���
     *                          �ץ�ե�����
     *
     * @return ��Ͽ�������
     *
     * @else
     * @brief Unsubscribe interface
     *
     * This operation unsubscribe provided interface in the ConnectorProfile.
     *
     * @param connector_profile The ConnectorProfile of unsubscribed connection
     *
     * @return Subscription result
     *
     * @endif
     */
    //    bool unsubscribeInterfaces(const ConnectorProfile& connector_profile);


    virtual void onConnect(const char* id, PublisherBase* publisher){};
    virtual void onDisconnect(const char* id){};
    
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
     * @brief OutPort�������Ԥ�
     *
     * properties�ξ���˴�Ť�OutPort�γƼ������Ԥ�
     *
     * @else
     *
     * @brief Configureing outport
     *
     * This operation configures the outport based on the properties.
     *
     * @endif
     */
    void configure();

    /*!
     * @if jp
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
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*! @if jp
     *
     * @brief Interface ����³����
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
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Subscribe to the interface
     *
     * This operation is pure virutal function that would be called at the
     * middle of the notify_connect() process sequence.
     * In the notify_connect(), the following methods would be called in order.
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
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
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @else
     *
     * @brief Disconnect the interface connection
     *
     * This operation is pure virutal function that would be called at the
     * end of the notify_disconnect() process sequence.
     * In the notify_disconnect(), the following methods would be called.
     * - disconnectNext()
     * - unsubscribeInterfaces()
     * - eraseConnectorProfile() 
     *
     * @param connector_profile The profile information associated with 
     *                          the connection
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);

    /*!
     * @if jp
     * @brief OutPort provider �ν����
     * @else
     * @brief OutPort provider initialization
     * @endif
     */
    void initProviders();

    /*!
     * @if jp
     * @brief InPort consumer �ν����
     * @else
     * @brief InPort consumer initialization
     * @endif
     */
    void initConsumers();

    /*!
     * @if jp
     * @brief OutPort provider ������
     * @else
     * @brief OutPort provider creation
     * @endif
     */
    OutPortProvider* createProvider(ConnectorProfile& cprof,
                                    coil::Properties& prop);
    /*!
     * @if jp
     * @brief InPort consumer ������
     * @else
     * @brief InPort consumer creation
     * @endif
     */
    InPortConsumer* createConsumer(const ConnectorProfile& cprof,
                                   coil::Properties& prop);
    
    /*!
     * @if jp
     * @brief OutPortPushConnector ������
     * @else
     * @brief OutPortPushConnector creation
     * @endif
     */
    OutPortConnector* createConnector(const ConnectorProfile& cprof,
                                      coil::Properties& prop,
                                      InPortConsumer* consumer);
    /*!
     * @if jp
     * @brief OutPortPullConnector ������
     * @else
     * @brief OutPortPullConnector creation
     * @endif
     */
    OutPortConnector* createConnector(const ConnectorProfile& cprof,
                                      coil::Properties& prop,
                                      OutPortProvider* provider);

    protected:
    coil::Properties m_properties;
    std::string m_name;
    std::vector<OutPortConnector*> m_connectors;
    std::vector<InPortConsumer*> m_consumers;
    coil::vstring m_providerTypes;
    coil::vstring m_consumerTypes;
    std::vector<OutPortProvider*> m_providers;
    
    /*!
     * @if jp
     * @brief provider �������뤿��� Functor
     * @else
     * @brief Functor to delete providers
     * @endif
     */
    struct provider_cleanup;

    /*!
     * @if jp
     * @brief connector �������뤿��� Functor
     * @else
     * @brief Functor to delete connectors
     * @endif
     */
    struct connector_cleanup;
  };
}; // End of namespace RTM
#endif // RtcOutPortBase_h
