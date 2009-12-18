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
 * $Id$
 *
 */

#ifndef RTC_CORBAPORT_H
#define RTC_CORBAPORT_H

#include <rtm/PortBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/NVUtil.h>
#include <list>

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
   * CorbaPort �� RT ����ݡ��ͥ�Ȥˤ����ơ��桼������� CORBA ���֥���
   * ���ȥ����ӥ�����ӥ��󥷥塼�ޤ��󶡤��� Port �����Ǥ��롣
   *
   * <p>
   * RT ����ݡ��ͥ�Ȥϡ�Port ��𤷤ƥ桼����������� CORBA �����ӥ�
   * ���󶡤��뤳�Ȥ��Ǥ�������� RT Service (Provider) �ȸƤ֡��ޤ���
   * ¾�� RT ����ݡ��ͥ�ȤΥ����ӥ������Ѥ��뤿��� CORBA ���֥�����
   * �ȤΥץ졼���ۥ�����󶡤��뤳�Ȥ��Ǥ�������� RT Service
   * Consumer �ȸƤ֡�
   * <p>
   * CorbaPort ��Ǥ�դο��� Provider ����� Consumer ��������뤳�Ȥ���
   * ����Port Ʊ�Τ���³����ݤ��б����� Provider �� Consumer ��Ŭ�ڤ�
   * ��Ϣ�դ��뤳�Ȥ��Ǥ��롣
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
   * ���Τ褦�ˡ��󶡤����� Service Provider �� registerProvider() ����
   * Ͽ���뤳�Ȥˤ�ꡢ¾�Υ���ݡ��ͥ�Ȥ������Ѳ�ǽ�ˤ���¾�������Ѥ�
   * ���� Service Consumer �� registerConsumer() ����Ͽ���뤳�Ȥˤ��¾
   * �Υ���ݡ��ͥ�Ȥ� Service �򥳥�ݡ��ͥ��������Ѳ�ǽ�ˤ��뤳��
   * ���Ǥ��롣
   *
   * PortInterfaceProfile �� Port �˽�°����ץ�Х����⤷���ϥ��󥷥塼
   * �ޥ��󥿡��ե������ˤĤ��Ƥξ���򵭽Ҥ��뤿��Υץ�ե�����Ǥ��롣
   * ��³��Ԥ��ġ������ϡ������ξ���˴�Ť� ConnectorProfile ��Ŭ��
   * ������������³�������� Port �Τ���Ǥ�դΰ�Ĥ��Ф��ư�����
   * ConnectorProfile ��Ϳ���� Port::connect() ��ƤӽФ�ɬ�פ����롣
   *
   * �ʤ���PortInterfaceProfile �Υ��󥹥���̾ "*" ���ü�ʥ��󥹥���
   * ����ɽ����
   *
   * PROVIDED���ʤ���ץ�Х����Υ��󥹥���̾�� "*" �ξ��ϡ���³��
   * �ϻ����Ǥϥ��󥹥��󥹤�¸�ߤ��������󥷥塼�ޤ��׵�˱�����ưŪ��
   * ���󥹥��󥹤��������륿���פΥץ�Х����Ǥ��뤳�Ȥ�ɽ������������
   * �ơ���³���ϻ����Ǥϥ��󥹥���̾��¸�ߤ��ʤ�������³����������
   * �Υ��󥿡��ե��������������ץ����ˤ����ơ��ץ�Х�������������
   * ���󥹥��󥹤��б��������һҤ� COnnectorProfile ��Ŭ�������ꤹ���
   * �ΤȤ��롣
   *
   * REQUIRED���ʤ�����󥷥塼�ޤΥ��󥹥���̾�� "*" �ξ��ϡ����
   * �Υ��󥷥塼�ޤ�ʣ���Υץ�Х�������³��ǽ�ʥ����פΥ��󥷥塼�ޤ�
   * ���뤳�Ȥ򼨤���(̤����)
   *
   * �ʲ��ϡ�Port�֤Υ��󥿡��ե���������³���뤿��� ConnectorProfile ��
   * �ޥåԥ󥰤򵭽Ҥ��뤿��Υ롼��򼨤���
   *
   * Port����°���륤�󥿡��ե������λ���ҤΥե����ޥåȤ�ʲ��Τ褦��
   * ���롣���󥿡��ե������˴ؤ���ץ�ѥƥ����ʲ��ξ��
   *
   * - RTC���󥹥���̾:              rtc_iname
   * - �ݡ���̾:                       port_name
   * - ���󥿡��ե���������:           if_polarity
   * - ���󥿡��ե�������̾:           if_tname
   * - ���󥿡��ե��������󥹥���̾: if_iname
   * 
   * ���󥿡��ե������λ���Ҥ�ʲ���ʸ����̾�Τǻ��ꤹ���ΤȤ��롣
   *
   * <rtc_iname>.port.<port_name>.<if_polarity>.<if_tname>.<if_iname>
   *
   * PROVIDED(��)�����ʤ���ץ�Х����Υ��󥿥ե������Υץ�ѥƥ�����
   * ���ξ�硢
   *
   * - rtc_iname   = MyComp0
   * - port_name   = myservice
   * - if_polarity = provided
   * - if_tname    = echo_interface
   * - if_iname    = echo_interface2
   *
   * ���󥿡��ե���������Ҥ�
   *
   * MyComp0.port.myservice.provided.echo_interface.echo_interface2
   *
   * �Τ褦�˵��Ҥ���롣�ޤ���Ʊ�ͤ�REQUIRED(�׵�)�����ʤ�����󥷥塼
   * �ޤΥ��󥿡��ե������Υץ�ѥƥ����ʲ��ξ�硢
   *
   * - rtc_iname   = YourComp0
   * - port_name   = yourservice
   * - if_polarity = required
   * - if_tname    = hoge_interface
   * - if_iname    = hoge_interface1
   *
   * ���󥿡��ե���������Ҥϡ�
   * 
   * YourComp0.port.myservice.required.hoge_interface.hoge_inteface1
   *
   * �Τ褦�˵��Ҥ��뤳�Ȥ��Ǥ��롣
   * 
   * �ʤ���������ưŪ�������󥿡��ե������Υ��󥹥��󥹤Τ�����ü�ʥ�
   * ���פΥ��󥹥���̾���һ�
   *
   * - <type_name>*: ưŪ���������󥹥���̾���һ�
   * - <type_name>+: ���󥯥��󥿥����������󥹥���̾���һ�
   *
   * ��������롣ưŪ�������󥿡��ե������Ȥϡ���³���˥��󥹥��󥹤���
   * ������륿���פΥ��󥿡��ե������Ǥ��롣(̤����)
   *
   * ưŪ���������󥹥���̾���һ� "<type_name>*" �Ǥϡ����󥿡��ե���
   * ���Υ��󥹥��󥹤ϡ����󥷥塼�ޤ�����׵᤬1�İʾ�¸�ߤ����硢
   * ���󥹥��󥹤�1�Ŀ������������ơ��ƥ��󥷥塼�ޤ���³����롣����
   * �����<type_name>* �ε��һҤ���äƥץ�Х������׵᤹�� n �ĤΥ���
   * ���塼�ޤ�¸�ߤ����硢����餫����׵�(���ڥ졼����󥳡���)��1
   * �ĤΥץ�Х����ˤ���������ط����ۤ���(����)��
   *
   * consumer0 ]---<
   * consumer1 ]---<  O----[ provider0
   * consumer2 ]---<
   *  
   * ������Ф������󥯥��󥿥����������󥹥���̾���һ�
   * "<type_name>+" �Ǥϡ����󥿡��ե������Υ��󥹥��󥹤ϡ����󥷥塼
   * �ޤ�����׵᤬ n ��¸�ߤ����硢n �ĤΥ��󥹥��󥹤�ưŪ��������
   * �ơ��ƥ��󥷥塼�ޤ��Ť�°���롣���ʤ����<type_name>* �ε��һҤ�
   * ���äƥץ�Х������׵᤹�� n �ĤΥ��󥷥塼�ޤ�¸�ߤ����硢����
   * �餫����׵�(���ڥ졼����󥳡���)���б����뤽�줾��Υץ�Х���
   * �ˤ���������ط����ۤ���(����)��
   *
   * consumer0 ]---<  O----[ provider0
   * consumer1 ]---<  O----[ provider1
   * consumer2 ]---<  O----[ provider2
   *
   *
   * ��³�˺ݤ��ơ��ġ��������� ConnectorProfile::properties ��Ŭ�ڤʥ�
   * �󥿡��ե������ޥåԥ󥰻���򵭽Ҥ��뤳�Ȥǡ���ߤ���/�׵ᥤ��
   * �����ե�������ͳ����³���뤳�Ȥ��Ǥ��롣����������³�˴ؤ��RTC
   * ����ˡ��ۤʤ륤�󥹥��󥹤Ǥ���ʤ��顢Ʊ��Υ��󥹥���̾��¸��
   * �����硢���󥿡��ե��������һҤΰ�������ݾڤǤ��ʤ��Τǡ�������
   * ˡ�ˤ����³�����ݾڤ���ʤ���
   *
   * �����ǥ��󥿡��ե��������һҤ��ñ�Τ���� <if_desc0>,
   * <if_desc1>, ...  �Ȥ��롣�ޤ���ConnectorProfile::properties ��
   * NVList�� key �� value �� key: value �Τ褦�˵��Ҥ����ΤȤ��롣
   *
   * ���ޡ�2�ĤΥ���ݡ��ͥ�ȤΥ����ӥ��ݡ��Ȥ���³�������ͤ��롣
   * ���줾��Υ���ݡ��ͥ�ȤΥ����ӥ��ݡ��Ȥ��ʲ��ξ�硢
   *
   * - rtc_iname: MyComp0
   *   port_name: mycomp_service
   *   interfaces:
   *   - if_polarity: provided
   *     if_iname: echo0
   *     if_tname: Echo
   *   - if_polarity: required
   *     if_iname: add0
   *     if_tname: add
   *
   * - rtc_iname: YourComp0
   *   port_name: yourcomp_service
   *   interfaces:
   *   - if_polarity: required
   *     if_iname: echo9
   *     if_tname: Echo
   *   - if_polarity: provided
   *     if_iname: add9
   *     if_tname: add
   *
   *      MyComp0                                 YourComp0
   *     _______ mycomp_service   yourcomp_service ______
   *            |                                 |
   *          |~~~|---O echo0         echo9 >---|~~~|
   *          |   |---< add0          add9  O---|   |
   *           ~T~                               ~T~
   *            |                                 |
   *
   * MyComp0 �� echo0 (�ץ�Х���) �� YourComp0 �� echo9 (���󥷥塼��)��
   * MyComp0 �� add0 (���󥷥塼��) �� YourComp0 �� echo9 (�ץ�Х���)
   * �򤽤줾���Фˤ�����³�������ΤȲ��ꤹ�롣���ξ�硢
   * ConnectorProfile �ϰʲ��Τ褦�����ꤹ�롣
   * 
   * ConnectorProfile:
   *   name: Ǥ�դΥ��ͥ���̾
   *   connector_id: ��ʸ��
   *   ports[]: mycomp_service �λ���, yourcomp_service �λ���
   *   properties:
   *     <add0>: <add9>
   *     <echo9>: <echo0>
   *
   * �����������줾��
   * 
   * <add0> �� MyComp0.port.mycomp_service.required.add.add0
   * <add9> �� YourComp0.port.yourcomp_service.provided.add.add9
   * <echo0> �� MyComp0.port.mycomp_service.provided.echo.echo0
   * <echo9> �� YourComp0.port.yourcomp_service.required.echo.echo9
   *
   * �Ǥ��롣��³�ץ����ˤ����ơ��ƥݡ��ȤΥץ�Х�������ӥ��󥷥塼
   * �ޤϡ����줾��ʲ��κ�Ȥ�CorbaPort::publishInterfaces(),
   * Corba::PortsubscribeInterfaces() ���۴ؿ��ˤ����ƹԤ���
   *
   * �ץ�Х����ϡ�publishInterfaces() �ؿ��ˤ����ơ���ʬ�Υ��󥿡��ե���
   * �����һҤ򥭡��Ȥ����ͤ�IOR��ʸ����ɽ��������Τ�
   * ConnectorProfile::properties �����ꤹ�롣����Ȥ��ơ����Υ��󥿡�
   * �ե��������һҤϺ��Ԥ����Ȥ��Ƥ��륳�ͥ����ˤ����Ƥϰ�դǤ��뤿�ᡢ
   * Ʊ��������1�Ĥ���¸�ߤ��ƤϤ����ʤ���
   *
   * [������ʬ�ε��Ҥ�̤�����ε�ǽ] �ʤ���ưŪ�������󥿡��ե������ˤ�
   * ���Ƥϡ��ʲ��μ�³���˽����������뤳�ȤȤʤ롣publishInterface()
   * �ؿ��ˤ����ơ�ưŪ�������󥹥���̾���һ� "<type_name>*" �ޤ��ϡ�
   * ���󥯥��󥿥����������󥹥���̾���һ� "<type_name>+" ��¸�ߤ�
   * �뤫�ɤ������������롣ưŪ�������󥹥���̾���һ� "<type_name>*"
   * ��¸�ߤ����硢�ץ�Х����Υ��󥹥��󥹤�1�������������Υ��󥿡�
   * �ե���������Ҥ� key �ˡ�IORʸ����� value �����ꤹ��ȤȤ�ˡ�ư
   * Ū�������󥹥���̾���һ� "<type_name>*" �� value �˴ޤह�٤Ƥ�
   * value ��Υ��󥿡��ե���������Ҥ򡢤����������������󥿡��ե�����
   * ����Ҥ��֤������롣���󥯥��󥿥����������󥹥���̾���һ�
   * "<type_name>+" ��¸�ߤ����硢���󥹥���̾���һҤο������ץ��
   * �����Υ��󥹥��󥹤������������줾��Υ��󥿡��ե���������Ҥ�
   * key �ˡ�IORʸ����� value �����ꤹ��ȤȤ�ˡ����󥯥��󥿥�����
   * �����󥹥���̾���һ� "<type_name>+" �� value �ޤह�٤Ƥ� value
   * ��Υ��󥿡��ե���������Ҥ��Ф��ƽ�ˡ������������������줾��Υ�
   * �󥿡��ե���������Ҥ��֤������롣
   *
   * �ץ�Х����� subscribeInterfaces() �Ǥ��ä����ϹԤ�ʤ���
   *
   * ���󥷥塼�ޤϡ�publishInterfaces() �ˤ����Ƥ��ä�����Ԥ�ʤ���
   *
   * ������subscribeInterfaces() �Ǥϡ���ʬ�ε��һҤ� key �Ȥ���
   * key-value �ڥ� ��¸�ߤ��뤫�ɤ���Ĵ�١��⤷¸�ߤ���С����� value
   * �����ꤵ�줿�ץ�Х����Υ��󥿡��ե���������Ҥǻ��ꤵ��뻲�Ȥ�
   * ����� ConnectorProfile::properties ����õ��������򥳥󥷥塼�ޤ�
   * ��³��Ȥ������ꤹ�롣�ʤ����տ�Ū�˥��󥷥塼�ޤ˥ץ�Х����λ���
   * �����ꤷ�ʤ����ϡ�ͽ��ʸ���� "nil" �����ꤹ���ΤȤ��롣
   *
   * ���󥷥塼�ޤϡ��⤷��ʬ�ε��һҤ�¸�ߤ��ʤ���硢�ޤ��ϥץ�Х���
   * �λ��Ȥ� Connector::properties ��¸�ߤ��ʤ���硢���󥷥塼�ޤϡ�
   * ��ʬ�Υ��󥹥���̾����ӷ�̾��Ʊ��Υץ�Х�����õ�������λ��Ȥ�
   * ��ʬ���Ȥ����ꤹ�롣����ϡ�OpenRTM-aist-0.4 �Ȥθߴ������ݻ�����
   * ����Υ롼��Ǥ��ꡢ1.0�ʹߤǤϿ侩����ʤ���
   *
   * �ץ�Х����Х��󥷥塼�ޤ��б��ϰ��а�Ǥ���ɬ�פϤʤ����ץ�Х���
   * 1 ���Ф��ơ����󥷥塼�� n���ޤ��ϥ��󥷥塼�� 1 ���Ф��ƥץ�Х�
   * �� n �Υ������������롣�ץ�Х��� 1 ���Ф��ơ����󥷥塼�� n ��
   * �������Ǥϡ�����ץ�Х����λ���Ҥ���ʣ���Υ��󥷥塼�ޤ��Ф��ơ�
   * �嵭����ˡ�ǻ��ꤵ��뤳�Ȥˤ�ꡢ�¸�����롣���������󥷥塼��
   * 1 ���Ф��ƥץ�Х��� n �Υ������Ǥϡ����󥷥塼�޻���Ҥ� key ����
   * ���ơ�ʣ���Υץ�Х����λ���Ҥ�����޶��ڤ����󤵤������Ȥʤ�
   * ��ΤȤ��롣
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
    virtual ~CorbaPort(void);
    
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

    //============================================================
    // Local operations
    //============================================================
    /*!
     * @if jp
     *
     * @brief Port �����ƤΥ��󥿡��ե������� activates ����
     *
     * Port ����Ͽ����Ƥ������ƤΥ��󥿡��ե������� activate ���롣
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

  private:
    /*!
     * @if jp
     * @class CorbaProviderHolder
     * CORBA Provider �Υۥ�����饹
     * @else
     * @class CorbaProviderHolder
     * CORBA Provider holder class
     * @endif
     */
    class CorbaProviderHolder
    {
    public:
      CorbaProviderHolder(const char* type_name,
                          const char* instance_name,
                          PortableServer::RefCountServantBase* servant)
        : m_typeName(type_name),
          m_instanceName(instance_name),
          m_servant(servant),
          m_ior()
      {  
        m_oid = Manager::instance().getPOA()->servant_to_id(m_servant);
        try
          {
            Manager::instance().
              getPOA()->activate_object_with_id(m_oid, m_servant);
          }
        catch(const ::PortableServer::POA::ServantAlreadyActive &)
          {
            ;
          }
        catch(const ::PortableServer::POA::ObjectAlreadyActive &)
          {
            ;
          }
        CORBA::Object_var obj;
        obj = Manager::instance().getPOA()->id_to_reference(m_oid);
        CORBA::ORB_ptr orb = Manager::instance().getORB();
        CORBA::String_var ior_var = orb->object_to_string(obj);
        m_ior = ior_var;
        deactivate();
      }

      std::string instanceName() { return m_instanceName; }
      std::string typeName() { return m_typeName; }
      std::string ior() { return m_ior; }
      std::string descriptor() { return m_typeName + "." + m_instanceName; }

      void activate()
      {
        try
          {
            Manager::instance().
              getPOA()->activate_object_with_id(m_oid, m_servant);
          }
        catch(const ::PortableServer::POA::ServantAlreadyActive &)
          {
            ; // do nothing
          }
        catch(const ::PortableServer::POA::ObjectAlreadyActive &)
          {
            ; // do nothing
          }
      }
      void deactivate()
      {
        try
          {
            Manager::instance().getPOA()->deactivate_object(m_oid);
          }
        catch(const ::PortableServer::POA::ObjectNotActive&)
          {
            ; // do nothing
          }
      }
    private:
      std::string m_typeName;
      std::string m_instanceName;
      PortableServer::RefCountServantBase* m_servant;
      PortableServer::ObjectId_var m_oid;
      std::string m_ior;
    };

    /*!
     * @if jp
     * @brief Provider �ξ�����Ǽ���� vector
     * @else
     * @brief vector to stored Providers' information
     * @endif
     */
    typedef std::vector<CorbaProvider> CorbaProviderList;
    CorbaProviderList m_providers;

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
#endif // RTC_CORBAPORT_H
