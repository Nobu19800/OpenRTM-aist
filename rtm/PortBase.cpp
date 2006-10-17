// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2006-10-17 10:22:07 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortBase.cpp,v 1.1 2006-10-17 10:22:07 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <rtm/PortBase.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief [CORBA interface] PortProfile���������
   * @else
   * @brief [CORBA interface] Get the PortProfile of the Port
   * @endif
   */
  PortProfile* PortBase::get_port_profile()
  {
    PortProfile_var prof(m_profile.getPortProfile());
    return prof._retn();
  }


  /*!
   * @if jp
   * @brief [CORBA interface] ConnectorProfileList���������
   * @else
   * @brief [CORBA interface] Get the ConnectorProfileList of the Port
   * @endif
   */
  ConnectorProfileList* PortBase::get_connector_profiles()
  {
    ConnectorProfileList tmp;
    tmp = m_profile.getConnectorProfiles();
    ConnectorProfileList_var conn_prof(&tmp);
    return conn_prof._retn();
  }


  /*!
   * @if jp
   * @brief [CORBA interface] ConnectorProfile ���������
   * @else
   * @brief [CORBA interface] Get the ConnectorProfile
   * @endif
   */
  ConnectorProfile* PortBase::get_connector_profile(const char* connector_id)
  {
    ConnectorProfile tmp;
    tmp = m_profile.getConnectorProfileById(connector_id);
    ConnectorProfile_var conn_prof(&tmp);
    return conn_prof._retn();
  }


  /*!
   * @if jp
   * @brief [CORBA interface] Port ����³��Ԥ�
   * @else
   * @brief [CORBA interface] Connect the Port
   * @endif
   */
  ReturnCode_t PortBase::connect(const ConnectorProfile& connector_profile)
  {
    // ### Do connection process
    m_profile.appendConnectorProfile(connector_profile);
    return RTC::OK;
  }


  /*!
   * @if jp
   * @brief [CORBA interface] Port ����³��������
   * @else
   * @brief [CORBA interface] Connect the Port
   * @endif
   */
  ReturnCode_t PortBase::disconnect(const char* connector_id)
  {
    // ### Do disconnection process
    try
      {
	m_profile.eraseConnectorProfileById(connector_id);
	return RTC::OK;
      }
    catch (...)
      {
	return RTC::ERROR;
      }
  }


  /*!
   * @if jp
   * @brief [CORBA interface] Port ������³��������
   * @else
   * @brief [CORBA interface] Connect the Port
   * @endif
   */
  ReturnCode_t PortBase::disconnect_all()
  {
    // disable all connections
    // for_each(disconnect)
    // m_profile.eraseConnectorProfileById(id);
    return RTC::OK;
  }

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
    PortProfile& getProfile() const
    {
      return m_profile;
    }

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
    void setProfile(const PortProfile& profile)
    {
      m_profile = profile;
    }

}; // namespace RTC
