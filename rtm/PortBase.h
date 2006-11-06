// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2006-11-06 01:16:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortBase.h,v 1.3 2006-11-06 01:16:39 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/10/17 19:06:45  n-ando
 * connect(), disconnect() and disconnect_all() was implemented.
 *
 * Revision 1.1  2006/10/17 10:22:24  n-ando
 * The first commitment.
 *
 */

#ifndef PortBase_h
#define PortBase_h

#include <rtm/idl/RTCSkel.h>
#include <string>
#include <ace/Guard_T.h>
#include <ace/Recursive_Thread_Mutex.h>

namespace RTC
{
  /*
    1. RTC��ǥ��󥹥������
    2. RTC���󥹥ȥ饯���ǽ����
     - name
     - properties ����
    3. regsiterPort��activate����ӥꥹ�Ȥ���Ͽ
     - port_ref ����
     - owner ����
    4. 

   */  
  class PortBase
    : public virtual POA_RTC::Port,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    PortBase(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa){};

    /*!
     * @if jp
     *
     * @brief [CORBA interface] PortProfile���������
     *
     * Port���ݻ�����PortProfile���֤���
     *
     * @return ���� Port �� PortProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the PortProfile of the Port
     *
     * This operation returns the PortProfile of the Port.
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
     * Port���ݻ����� ConnectorProfileList ���֤���
     *
     * @return ���� Port �� ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfileList of the Port
     *
     * This operation returns a list of the ConnectorProfiles of the Port.
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
     * Ϳ����줿 ConnectoionProfile �ˤ�äƤ���Port���б�����ԥ�Port��
     * ��³���Ω���롣
     * ConnectorProfile �� Port ���ȤΥ������󥹤���ġ�
     * Port �� ConnectionProfile ���ݻ�����ȤȤ�ˡ��ԥ� Port �� connect()
     * �� ConnectionProfile ������Ȥ���Ϳ���ƸƤӽФ�����������Ϣ���Ω���롣
     *
     * @param connector_profile ConnectorProfile
     * @return ReturnCode_t ���ڥ졼�����Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation establishes connection between this port and the peer
     * ports according to given ConnectionProfile.
     * A ConnectorProfile has a sequence of port references.
     * This port stores the ConnectorProfile and calls the peer ports'
     * "connect()" operation with the ConnectorProfile to make a
     * bidirectional association.
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
     * @brief [CORBA interface] Port ����³��������
     *
     * ���Υ��ڥ졼��������³��Ω������³���Ф���Ϳ������ connector_id ��
     * �б�����ԥ� Port �Ȥ���³�������롣
     * Port ����³��������줿���Ȥ�ԥ� Port ���Ф��� "disconnect()" ��
     * �ƤӽФ����Ȥ����Τ��롣���Υ��ڥ졼����������� ReturnCode_t ���֤���
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
     * The port notifies that connection is destroyed to call peer ports
     * disconnect operation. This operation returns ReturnCode_t return codes.
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
     *
     * @brief PortProfile�����ꤹ��
     *
     * Port���ݻ�����PortProfile���񤭤��ƿ�����PortProfile��Ϳ���롣
     * ��¸��PortProfile�Ͼ�񤭤������Ƥ��˴�����롣
     * ������ PortProfile �����Ƥ�Ŭ�ڤ����ꤵ��Ƥ��ʤ���Фʤ�ʤ���
     *
     * @param profile Ϳ���� Port �� PortProfile
     *
     * @else
     *
     * @brief Set a PortProfile to the Port
     *
     * This operation sets a PortProfile to the Port.
     * Existing PortProfile will be overwritten and deleted.
     * Given PortProfile to the Port should be configured in advance properly.
     *
     * @param profile The PortProfile to be set this Port
     *
     * @endif
     */
    void setProfile(const PortProfile& profile);


    /*!
     * @if jp
     *
     * @brief PortProfile���������
     *
     * Port���ݻ����� PortProfile �� const ���Ȥ��֤���
     *
     * @return ���� Port �� PortProfile
     *
     * @else
     *
     * @brief Get the PortProfile of the Port
     *
     * This operation returns const reference of the PortProfile.
     *
     * @return the PortProfile of the Port
     *
     * @endif
     */
    const PortProfile& getProfile();
    

    /*!
     * @if jp
     *
     * @brief Port ��̾�������ꤹ��
     *
     * Port ��̾�������ꤹ�롣����̾���� Port ���ݻ����� PortProfile.name
     * ��ȿ�Ǥ���롣
     *
     * @param name Port ��̾��
     *
     * @else
     *
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
     *
     * @brief Port ��̾�����������
     *
     * Port ��̾����������롣
     * ����̾���� Port ���ݻ����� PortProfile.name �Ǥ��롣
     *
     * @return Port ��̾��
     *
     * @else
     *
     * @brief Get the name of this Port
     *
     * This operation returns the name of this Port.
     * The returned Port's name is same as PortProfile.name.
     *
     * @return The name of this Port.
     *
     * @endif
     */
    const char* getName();


    /*!
     * @if jp
     *
     * @brief Port �� PortInterfaceProfileList �����ꤹ��
     *
     * PortProfile �� Port ����ͭ���륤�󥿡��ե������Υץ�ե�����Υꥹ��
     * PortInterfaceProfileList ���ݻ����Ƥ��롣
     * ���Υ��ڥ졼�����Ϥ��� Port �� PortInterfaceProfileList �����ꤹ�롣
     * ���ꤵ��� PortInterfaceProfileList �ϻ�����Ŭ�ڤ����ꤵ��Ƥ��ʤ����
     * �ʤ�ʤ���
     * ��¸�� PortProfile ����ͭ���� PortInterfaceProfileList ���˴�����롣
     *
     * @param if_profiles Port �� PortInterfaceProfileList
     *
     * @else
     *
     * @brief Set the PortInterfaceProfileList of this Port
     *
     * PortProfile has a list of profile information of interfaces that are
     * owned by the Port as PortInterfaceProfileList.
     * This operation sets the PortInterfaceProfileList of this Port.
     * The given PortInterfaceProfileList should be configured in advance properly.
     * The existing PortInterfaceProfileList of the PortProfile will be deleted.
     *
     * @param if_profiles The PortInterfaceProfileList of this Port
     *
     * @endif
     */
    void setInterfaceProfiles(PortInterfaceProfileList& if_profiles);


    /*!
     * @if jp
     *
     * @brief Port �� PortInterfaceProfile ���ɲä���
     *
     * ���Υ��ڥ졼�����Ϥ��� Port �� PortInterfaceProfile ���ɲä��롣
     * ���ꤵ��� PortInterfaceProfile �ϻ�����Ŭ�ڤ����ꤵ��Ƥ��ʤ���Фʤ�ʤ���
     * Ϳ����줿 PortInterfaceProfile �� PortProfile �� PortInterfaceProfileList ��
     * �Ǹ���ɲä���롣
     *
     * @param if_profile Port �� PortInterfaceProfile 
     *
     * @else
     *
     * @brief Add the PortInterfaceProfile of this Port
     *
     * This operation sets the PortInterfaceProfile of this Port.
     * The given PortInterfaceProfile should be configured in advance properly.
     * The given PortInterfaceProfile will be added to the end of the
     * IntefaceProfileList that is owned by the PortProfile.
     *
     * @param if_profile The PortInterfaceProfile of this Port
     *
     * @endif
     */
    void addInterfaceProfile(PortInterfaceProfile& if_profile);


    /*!
     * @if jp
     *
     * @brief Port �� PortInterfaceProfileList ���������
     *
     * ���Υ��ڥ졼�����Ϥ��� Port �� PortProfile ���ݻ����� 
     * PortInterfaceProfile �Υꥹ�� PortInterfaceProfileList ���֤���
     *
     * @return ���� Port ��PortProfile ���ݻ����� PortInterfaceProfileList
     *
     * @else
     *
     * @brief get the InterfaceprofileList of this Port
     *
     * This operation return the PortInterfaceProfileList of the PortProfile
     * that is owned by this Port.
     *
     * @return The PortInterfaceProfileList of this Port's PortProfile
     *
     * @endif
     */
    PortInterfaceProfileList getInterfaceProfiles();


    /*!
     * @if jp
     *
     * @brief Port �� PortInterfaceProfile ���������
     *
     * ���Υ��ڥ졼������ Port �� PortProfile ���ݻ����� PortInterfaceProfile
     * ���椫�顢Ϳ����줿 name ����� PortInterfaceProfile ���֤���
     *
     * @return ̾�� name ����� PortInterfaceProfile
     *
     * @else
     *
     * @brief Get the Interfaceprofile of this Port
     *
     * This operation returns the PortInterfaceProfile that is specified by the
     * given name from PortProfile of this Port.
     *
     * @return The PortInterfaceProfile named "name".
     *
     * @endif
     */
    PortInterfaceProfile getInterfaceProfile(const char* name);


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
     * @brief ConnectorProfile ���ɲä���
     *
     * ���Υ��ڥ졼������ Port �� PortProfile ���ݻ����Ƥ���
     * ConnectorProfileList ��Ϳ����줿 ConnectorProfile ���ɲä��롣
     *
     * @param PortProfile �� ConnectorProfileList ���ɲä��� ConnectorProfile
     *
     * @else
     *
     * @brief Set the ConnectorProfile to PortProfile
     *
     * This operation sets the ConnectorProfile to the ConnectorProfileList
     * that is owned by the PortProfile.
     *
     * @param The ConnectorProfile to be added to ConnectorProfileList.
     *
     * @endif
     */
    void addConnectorProfile(ConnectorProfile conn_prof);

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
    void eraseConnectorProfile(const char* id);


    /*!
     * @if jp
     *
     * @brief ConnectorProfileList ���������
     *
     * ���Υ��ڥ졼������ Port �� PortProfile ���ݻ����Ƥ���
     * ConnectorProfileList �� const ���Ȥ�������롣
     *
     * @return ConnectorProfileList
     *
     * @else
     *
     * @brief Get ConnectorProfileList
     *
     * This operation returns the ConnectorProfileList owned by
     * PortProfile of this Port.
     *
     * @return ConnectorProfileList
     *
     * @endif
     */
    const ConnectorProfileList& getConnectorProfileList();


    /*!
     * @if jp
     *
     * @brief ConnectorProfile ���������
     *
     * ���Υ��ڥ졼������ Port �� PortProfile ���ݻ����Ƥ���
     * ConnectorProfile �Τ��� id ����Ĥ�Τ��֤���
     *
     * @return ConnectorProfile
     *
     * @else
     *
     * @brief Get ConnectorProfile
     *
     * This operation returns the ConnectorProfile specified by given id
     * from PortProfile of this Port.
     *
     * @return ConnectorProfileList
     *
     * @endif
     */
    const ConnectorProfile& getConnectorProfile(const char* id);


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


    /*!
     * @if jp
     *
     * @brief Port �� owner �� RTObject ���������
     *
     * ���Υ��ڥ졼������ Port �� PortProfile.owner ��������롣
     *
     * @return ���� Port ���ͭ���� RTObject �λ���
     *
     * @else
     *
     * @brief Get the owner RTObject of the Port
     *
     * This operation gets the owner RTObject of this Port.
     *
     * @return The owner RTObject's reference of this Port
     *
     * @endif
     */
    RTObject_ptr getOwner();


    /*!
     * @if jp
     *
     * @brief PortProfile �� property �����ꤹ��
     *
     * ���Υ��ڥ졼������ Port �� PortProfile.properties �����ꤹ�롣
     *
     * @param properties PortProfile.properties
     *
     * @else
     *
     * @brief Set the properties of the PortProfile
     *
     * This operation sets the properties of the PortProfile.properties.
     *
     * @param The properties to be set to the PortProfile.properties.
     *
     * @endif
     */
    void setProperties(const NVList& properties);


    /*!
     * @if jp
     *
     * @brief PortProfile �� property ���������
     *
     * ���Υ��ڥ졼������ Port �� PortProfile.properties ���֤���
     *
     * @return PortProfile.properties
     *
     * @else
     *
     * @brief Get the properties of the PortProfile
     *
     * This operation returns the properties of the PortProfile.properties.
     *
     * @return The properties of the PortProfile.properties.
     *
     * @endif
     */
    const NVList& getProperties();

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
    
  protected:
    PortProfile m_profile;
    ACE_Recursive_Thread_Mutex m_profile_mutex;
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
    struct if_name;


    /*!
     * @if jp
     * @brief id ����� ConnectorProfile ��õ�� Functor
     * @else
     * @brief A functor to find a ConnectorProfile named id
     * @endif
     */
    struct find_conn_id;


    /*!
     * @if jp
     * @brief Port ����³��Ԥ� Functor
     * @else
     * @brief A functor to connect Ports
     * @endif
     */
    struct connect_func;


    /*!
     * @if jp
     * @brief Port ����³�����Ԥ� Functor
     * @else
     * @brief A functor to disconnect Ports
     * @endif
     */
    struct disconnect_func;
 

    /*!
     * @if jp
     * @brief Port ������³�����Ԥ� Functor
     * @else
     * @brief A functor to disconnect all Ports
     * @endif
     */
    struct disconnect_all_func;

    friend class disconnect_all_func;

  };
};
#endif // PortBase_h
