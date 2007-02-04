// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2007-02-04 17:00:59 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortBase.h,v 1.8 2007-02-04 17:00:59 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.7  2007/01/04 00:43:35  n-ando
 * Now, notify_connect() and notify_disconnect() behavior can be customized
 * publishInterfaces(), subscribeInterfaces() and unsubscribeInterfaces().
 *
 * Revision 1.6  2006/12/02 18:50:22  n-ando
 * A trivial fix.
 *
 * Revision 1.5  2006/11/27 09:57:09  n-ando
 * addProvider() function was added for registration of provider.
 * addConsumer() function was added for registration of consumer.
 *
 * Revision 1.4  2006/11/06 01:46:47  n-ando
 * #include <assert.h> was added.
 *
 * Revision 1.3  2006/11/06 01:16:39  n-ando
 * Now PortBase doesn't depend on PortProfileHelper.
 * Class refference manual has been updated.
 *
 * Revision 1.2  2006/10/17 19:06:45  n-ando
 * connect(), disconnect() and disconnect_all() was implemented.
 *
 * Revision 1.1  2006/10/17 10:22:24  n-ando
 * The first commitment.
 *
 */

#ifndef PortBase_h
#define PortBase_h

#include <string>
#include <vector>
#include <ace/Guard_T.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>

#include <iostream>
namespace RTC
{
  //  class ConsumerBase;

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
   * @else
   *
   *
   * @endif
   */  
  class PortBase
    : public virtual POA_RTC::Port,
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
     * @param name Port ��̾��
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
     * @param name The name of Port 
     *
     * @endif
     */
    PortBase(const char* name = "");


    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief Destructor
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
     * @return ���� Port �� PortProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the PortProfile of the Port
     *
     * This operation returns the PortProfile of the Port.
     * PortProfile struct has the following members,
     *
     * - name              [string ] The name of the Port.
     * - interfaces        [PortInterfaceProfileList ��] The sequence of 
     *                     PortInterfaceProfile owned by the Port
     * - port_ref          [Port Object] The object reference of the Port.
     * - connector_profile [ConnectorProfileList ��] The sequence of 
     *                     ConnectorProfile owned by the Port.
     * - owner             [RTObject Object] The object reference of 
     *                     RTObject that is owner of the Port.
     * - properties        [NVList] The other properties.
     *
     * @return the PortProfile of the Port
     *
     * @endif
     */
    virtual PortProfile* get_port_profile();


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
     * @return ���� Port �� ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfileList of the Port
     *
     * This operation returns a list of the ConnectorProfiles of the Port.
     * ConnectorProfile includes the connection information that describes 
     * relation between (among) Ports, and Ports exchange the ConnectionProfile
     * on connection process and hold the same information in each Port.
     * ConnectionProfile has the following members,
     *
     * - name         [string] The name of the connection.
     * - connector_id [string] Unique identifier.
     * - ports        [Port sequnce] The sequence of Port's object reference
     *                that are related the connection.
     * - properties   [NVList] The other properties.
     *
     * @return the ConnectorProfileList of the Port
     *
     * @endif
     */
    virtual ConnectorProfileList* get_connector_profiles();


    /*!
     * @if jp
     *
     * @brief [CORBA interface] ConnectorProfile ���������
     *
     * connector_id �ǻ��ꤵ�줿 ConnectorProfile ���֤���
     *
     * @param connector_id ConnectorProfile �� ID
     * @return connector_id ����� ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfile
     *
     * This operation returns the ConnectorProfiles specified connector_id.
     *
     * @param connector_id ID of the ConnectorProfile
     * @return the ConnectorProfile identified by the connector_id
     *
     * @endif
     */
    virtual ConnectorProfile* get_connector_profile(const char* connector_id);


    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³��Ԥ�
     *
     * Ϳ����줿 ConnectoionProfile �ˤ������äơ�Port�֤���³���Ω���롣
     * ���ץꥱ�������ץ����¦�ϡ����Ĥ��Υ���ݡ��ͥ�Ȥ�����ʣ����
     * Port ����³��������硢Ŭ�ڤ��ͤ򥻥åȤ��� ConnectorProfile ��
     * connect() �ΰ����Ȥ���Ϳ���ƥ����뤹�뤳�Ȥˤ�ꡢ��Ϣ���� Port ��
     * ��³���Ω���롣
     *
     * connect() ��Ϳ���� ConnectorProfile �Υ��С��Τ�����name, ports, 
     * (properties) ���С����Ф��ƥǡ����򥻥åȤ��ʤ���Фʤ�ʤ���
     *
     * @param connector_profile ConnectorProfile
     * @return ReturnCode_t ���ڥ졼�����Υ꥿���󥳡���
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
     * name, ports, (properties) members of ConnectorProfile should be set
     * valid values before giving to the argument of connect() operation.
     *
     * @param connector_profile The ConnectorProfile.
     * @return ReturnCode_t The return code of this operation.
     *
     * @endif
     */
    virtual ReturnCode_t connect(ConnectorProfile& connector_profile);


    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³���Τ�Ԥ�
     *
     * ���Υ��ڥ졼�����ϡ�Port�֤���³���Ԥ���ݤˡ�Port�֤�����Ū��
     * �ƤФ�륪�ڥ졼�����Ǥ��롣
     *
     * @param connector_profile ConnectorProfile
     * @return ReturnCode_t ���ڥ졼�����Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Notify the Ports connection
     *
     * This operation is invoked between Ports internally when the connection
     * is established.
     *
     * @param connector_profile The ConnectorProfile.
     * @return ReturnCode_t The return code of this operation.
     *
     * @endif
     */
    virtual ReturnCode_t notify_connect(ConnectorProfile& connector_profile);


    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³��������
     *
     * ���Υ��ڥ졼��������³��Ω������³���Ф���Ϳ������ connector_id ��
     * �б�����ԥ� Port �Ȥ���³�������롣
     *
     * @param connector_id ConnectorProfile �� ID
     * @return ReturnCode_t ���ڥ졼�����Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation destroys connection between this port and the peer port
     * according to given id that is given when the connection established.
     *
     * @param connector_id The ID of the ConnectorProfile.
     * @return ReturnCode_t The return code of this operation.
     *
     * @endif
     */
    virtual ReturnCode_t disconnect(const char* connector_id);


    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³������Τ�Ԥ�
     *
     * ���Υ��ڥ졼�����ϡ�Port�֤���³������Ԥ���ݤˡ�Port�֤�����Ū��
     * �ƤФ�륪�ڥ졼�����Ǥ��롣
     *
     * @param connector_id ConnectorProfile �� ID
     * @return ReturnCode_t ���ڥ졼�����Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Notify the Ports disconnection
     *
     * This operation is invoked between Ports internally when the connection
     * is destroied.
     *
     * @param connector_id The ID of the ConnectorProfile.
     * @return ReturnCode_t The return code of this operation.
     *
     * @endif
     */
    virtual ReturnCode_t notify_disconnect(const char* connector_id);


    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ������³��������
     *
     * ���Υ��ڥ졼�����Ϥ��� Port �˴�Ϣ�������Ƥ���³�������롣
     *
     * @return ReturnCode_t ���ڥ졼�����Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation destroys all connection channels owned by the Port.
     *
     * @return ReturnCode_t The return code of this operation.
     *
     * @endif
     */
    virtual ReturnCode_t disconnect_all();


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
     * @return the PortProfile of the Port
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
     * @param ���� Port �Υ��֥������Ȼ���
     *
     * @else
     *
     * @brief Set the object reference of this Port
     *
     * This operation sets the object reference itself
     * to the Port's PortProfile.
     *
     * @param The object reference of this Port.
     *
     * @endif
     */
    void setPortRef(Port_ptr port_ref);


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
    Port_ptr getPortRef();


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
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Publish interface information
     *
     * This operation is pure virutal method that would be called at the
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
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Publish interface information
     *
     * This operation is pure virutal method that would be called at the
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
     * This operation is pure virutal method that would be called at the
     * end of the notify_disconnect() process sequence.
     * In the notify_disconnect(), the following methods would be called.
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
     * @return ������Ϳ����줿 ConnectorProfile �� connector_id �����Ǥ���С�
     *         true�������Ǥʤ���� false ���֤���
     *
     * @else
     *
     * @brief Whether connector_id of ConnectorProfile is empty
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
     * @brief Get the UUID
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
     * @brief Create and set the UUID to the ConnectorProfile
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
     * @else
     *
     * @brief Whether the given id exists in stored ConnectorProfiles
     *
     * This operation returns boolean whether the given id exists in 
     * the Port's ConnectorProfiles.
     *
     * @param id connector_id to be find in Port's ConnectorProfiles
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
     * @return Port �� ConnectorProfile �ꥹ�ȤΥ���ǥå���
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
     * ���Υ��ڥ졼������Ϳ����줿Ϳ����줿 ConnectorProfile ��
     * Port ���ɲä⤷���Ϲ�����¸���롣
     * Ϳ����줿 ConnectorProfile �� connector_id ��Ʊ�� ID �����
     * ConnectorProfile ���ꥹ�Ȥˤʤ���С��ꥹ�Ȥ��ɲä���
     * Ʊ�� ID ��¸�ߤ���� ConnectorProfile ������¸���롣
     *
     * @param coonector_profile �ɲä⤷���Ϲ������� ConnectorProfile
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
     * @else
     *
     * @brief Delete the ConnectorProfile
     *
     * This operation deletes a ConnectorProfile specified by id from
     * ConnectorProfileList owned by PortProfile of this Port.
     *
     * @param id The id of the ConnectorProfile to be deleted.
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
     * ���ξ���ϡ�get_port_profile() ����ä������� PortProfile �Τ���
     * PortInterfaceProfile ���ͤ��ѹ�����ΤߤǤ��ꡢ�ºݤ˥��󥿡��ե�������
     * �󶡤������׵ᤷ���ꤹ����ˤϡ����֥��饹�ǡ�publishInterface(),
     * subscribeInterface() ���δؿ���Ŭ�ڤ˥����С��饤�ɤ����󥿡��ե�������
     * �󶡡��׵������Ԥ�ʤ���Фʤ�ʤ���
     *
     * ���󥿡��ե�����(�Υ��󥹥���)̾�� Port ��ǰ�դǤʤ���Фʤ�ʤ���
     * Ʊ̾�Υ��󥿡��ե����������Ǥ���Ͽ����Ƥ����硢���δؿ��� false ��
     * �֤���
     *
     * @param name ���󥿡��ե������Υ��󥹥��󥹤�̾��
     * @param type_name ���󥿡��ե������η���̾��
     * @param pol ���󥿡��ե�������°�� (RTC::PROVIDED �⤷���� RTC:REQUIRED)
     * @return Ʊ̾�Υ��󥿡��ե�������������Ͽ����Ƥ���� false ���֤���
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
     * @return ���󥿡��ե���������Ͽ����Ƥ��ʤ���� false ���֤���
     *
     * @else
     *
     * @brief Delete an interface from the PortInterfaceProfile
     *
     * This operation deletes interface information from the
     * PortInterfaceProfile that is owned by the Port.
     *
     * @param name The instance name of the interface.
     * @param pol The interface's polarity (RTC::PROVIDED or RTC:REQUIRED)
     * @return false would be returned if the given name is not registered.
     *
     * @endif
     */
    bool deleteInterface(const char* name, PortInterfacePolarity pol);
    

    /*!
     * @if jp
     *
     * @brief PortProfile �� properties �� NameValue �ͤ��ɲä���
     *
     * @param ValueType properties �� value ���ɲä����ͤη�
     * @param key properties �� name
     * @param value properties �� value
     *
     * @else
     *
     * @brief Add NameValue data to PortProfile's properties
     *
     * @param ValueType The type of value
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
    RTC::Port_var m_objref;
    mutable ACE_Recursive_Thread_Mutex m_profile_mutex;
    typedef ACE_Guard<ACE_Recursive_Thread_Mutex> Guard;
    
    //============================================================
    // Functor
    //============================================================
    /*!
     * @if jp
     * @brief instance_name ����� PortInterfaceProfile ��õ�� Functor
     * @else
     * @brief A functor to find a PortInterfaceProfile named instance_name
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
     * @brief A functor to find a ConnectorProfile named id
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
     * @brief A functor to find the object reference that is identical port_ref
     * @endif
     */
    struct find_port_ref
    {
      find_port_ref(Port_ptr port_ref) : m_port(port_ref) {};
      bool operator()(Port_ptr port_ref)
      {
	return m_port->_is_equivalent(port_ref);
      }
      Port_ptr m_port;
    };
	
    
    /*!
     * @if jp
     * @brief Port ����³��Ԥ� Functor
     * @else
     * @brief A functor to connect Ports
     * @endif
     */
    struct connect_func
    {
      Port_var port_ref;
      ConnectorProfile connector_profile;
      ReturnCode_t return_code;
      
      connect_func() {};
      connect_func(Port_ptr p, ConnectorProfile& prof)
	: port_ref(p), connector_profile(prof) {};
      void operator()(Port_ptr p)
      {
	if (!port_ref->_is_equivalent(p))
	  {
	    ReturnCode_t retval;
	    retval = p->notify_connect(connector_profile);
	    if (retval != RTC::OK)
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
     * @brief A functor to disconnect Ports
     * @endif
     */
    struct disconnect_func
    {
      Port_var port_ref;
      ConnectorProfile connector_profile;
      ReturnCode_t return_code;
      
      disconnect_func() : return_code(RTC::OK) {};
      disconnect_func(Port_ptr p, ConnectorProfile& prof)
	: port_ref(p), connector_profile(prof), return_code(RTC::OK) {};
      void operator()(Port_ptr p)
      {
	if (!port_ref->_is_equivalent(p))
	  {
	    ReturnCode_t retval;
	    retval = p->disconnect(connector_profile.connector_id);
	    if (retval != RTC::OK)
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
     * @brief A functor to disconnect all Ports
     * @endif
     */
    struct disconnect_all_func
    {
      ReturnCode_t return_code;
      PortBase* port;
      
      disconnect_all_func() {};
      disconnect_all_func(PortBase* p) 
	: return_code(RTC::OK), port(p) {};
      void operator()(ConnectorProfile& p)
      {
	ReturnCode_t retval;
	retval = port->disconnect(p.connector_id);
	if (retval != RTC::OK)
	  {
	    return_code = retval;
	  }
      }
    };
    

    /*!
     * @if jp
     * @brief name �� polarity ���� interface ��õ�� Functor
     * @else
     * @brief A functor to find interface from name and polarity
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

    friend class disconnect_all_func;
    
  };
};
#endif // PortBase_h
