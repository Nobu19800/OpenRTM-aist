// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2006-10-17 19:06:45 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortBase.h,v 1.2 2006-10-17 19:06:45 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/10/17 10:22:24  n-ando
 * The first commitment.
 *
 */

#ifndef PortBase_h
#define PortBase_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/PortProfileHelper.h>

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
     * @brief PortProfile���������
     *
     * Port���ݻ�����PortProfile���֤���
     *
     * @return ���� Port �� PortProfile
     *
     * @else
     *
     * @brief Get the PortProfile of the Port
     *
     * This operation returns the PortProfile of the Port.
     *
     * @return the PortProfile of the Port
     *
     * @endif
     */
    const PortProfile& getProfile() const;
    PortProfileHelper& getProfileHelper();

    /*!
     * @if jp
     *
     * @brief Port �� PortProfile �����ꤹ��
     *
     * PortProfile�����ꤹ�롣
     *
     * @param profile Port ��Ϳ���� PortProfile
     *
     * @else
     *
     * @brief Set the PortProfile of the Port
     *
     * This operation sets the PortProfile of the Port.
     *
     * @param profile The PortProfile to be set to the Port
     *
     * @endif
     */
    void setProfile(const PortProfile& profile);

    const std::string getUUID() const;
    
  protected:
    /*
      struct PortProfile {
      string name;
      PortInterfaceProfileList interfaces;
      Port port_ref;
      ConnectorProfileList connector_profiles;
      RTObject owner;
      NVList properties;
      };
    */

    PortProfileHelper m_profile;

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
	    retval = p->connect(connector_profile);
	    if (retval != RTC::OK)
	      {
		return_code = retval;
	      }
	  }
      }
    };

    struct disconnect_func
    {
      Port_var port_ref;
      ConnectorProfile connector_profile;
      ReturnCode_t return_code;

      disconnect_func() {};
      disconnect_func(Port_ptr p, ConnectorProfile& prof)
	: port_ref(p), connector_profile(prof) {};
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
	port->m_profile.eraseConnectorProfileById(p.connector_id);
	if (retval != RTC::OK)
	  {
	    return_code = retval;
	  }
      }
    };
    friend class disconnect_all_func;

  };
};
#endif // PortBase_h
