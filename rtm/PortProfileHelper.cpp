// -*- C++ -*-
/*!
 * @file PortProfileHelper.h
 * @brief RTC's PortProfile helper class
 * @date $Date: 2006-10-17 10:22:52 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortProfileHelper.cpp,v 1.1 2006-10-17 10:22:52 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include "rtm/PortProfileHelper.h"

namespace RTC
{
  PortProfileHelper::PortProfileHelper()
  {
    ;
  }


  PortProfileHelper::~PortProfileHelper()
  {
    ;
  }


  /*!
   * @if jp
   * @brief PortProfile $B$r@_Dj$9$k(B
   * @else
   * @brief Set PortProfile
   * @endif
   */
  void PortProfileHelper::setPortProfile(const PortProfile& profile)
  {
    Guard guard(m_mutex);

    m_name         = profile.name;
    m_ifProfiles   = profile.interfaces;
    m_portRef      = profile.port_ref;
    m_connProfiles = profile.connector_profiles;
    m_owner        = profile.owner;
    m_properties   = profile.properties;

    return;
  }


  /*!
   * @if jp
   * @brief PortProfile $B$r<hF@$9$k(B
   * @else
   * @brief Get PortProfile
   * @endif
   */
  PortProfile* PortProfileHelper::getPortProfile()
  {
    Guard guard(m_mutex);

    PortProfile_var profile(new PortProfile());
    profile->name = CORBA::string_dup(m_name.c_str());
    profile->interfaces = m_ifProfiles;
    profile->port_ref = m_portRef;
    profile->connector_profiles = m_connProfiles;
    profile->owner = m_owner;
    profile->properties = m_properties;
    return profile._retn();
  }


  /*!
   * @if jp
   * @brief PortProfile.name $B$r@_Dj$9$k(B
   * @else
   * @brief Set PortProfile.name
   * @endif
   */
  void PortProfileHelper::setName(const char* name)
  {
    Guard guard(m_mutex);

    m_name = name;
  }


  /*!
   * @if jp
   * @brief PortProfile.name $B$r<hF@$9$k(B
   * @else
   * @brief Get PortProfile.name
   * @endif
   */
  const char* PortProfileHelper::getName() const
  {
    Guard guard(m_mutex);

    return m_name.c_str();
  }
  

  /*!
   * @if jp
   * @brief PortInterfaceProfile $B$rDI2C$9$k(B
   * @else
   * @brief Append PortInterfaceProfile to the PortProfile
   * @endif
   */
  void
  PortProfileHelper::appendPortInterfaceProfile(PortInterfaceProfile if_prof)
  {
    Guard guard(m_mutex);

    m_ifProfiles.push_back(if_prof);
    return;
  }


  /*!
   * @if jp
   * @brief PortInterfaceProfileList $B$r<hF@$9$k(B
   * @else
   * @brief Get PortInterfaceProfileList
   * @endif
   */
  const PortInterfaceProfileList&
  PortProfileHelper::getPortInterfaceProfiles() const
  {
    Guard guard(m_mutex);

    return m_ifProfiles;
  }


  /*!
   * @if jp
   * @brief PortInterfaceProfile $B$r<hF@$9$k(B
   * @else
   * @brief Get PortInterfaceProfile
   * @endif
   */
  const PortInterfaceProfile
  PortProfileHelper::getPortInterfaceProfile(const char* instance_name) const
  {
    Guard guard(m_mutex);

    return m_ifProfiles.find(if_name(instance_name));
  }


  /*!
   * @if jp
   * @brief PortInterfaceProfile $B$r:o=|$9$k(B
   * @else
   * @brief Erase PortInterfaceProfile from the PortProfile
   * @endif
   */
  void PortProfileHelper::erasePortInterfaceProfile(const char* instance_name)
  {
    Guard guard(m_mutex);

    m_ifProfiles.erase_if(if_name(instance_name));
    return;
  }


  /*!
   * @if jp
   * @brief Port $B$N%*%V%8%'%/%H;2>H$r%;%C%H$9$k(B
   * @else
   * @brief Set Port's object reference
   * @endif
   */
  void PortProfileHelper::setPortRef(Port_ptr port)
  {
    Guard guard(m_mutex);

    m_portRef = port;
  }


  /*!
   * @if jp
   * @brief Port $B$N%*%V%8%'%/%H;2>H$r<hF@$9$k(B
   * @else
   * @brief Get Port's object reference
   * @endif
   */
  Port_ptr PortProfileHelper::getPortRef() const
  {
    Guard guard(m_mutex);

    return m_portRef;
  }


  /*!
   * @if jp
   * @brief ConnectorProfile $B$rDI2C$9$k(B
   * @else
   * @brief Append ConnectorProfile
   * @endif
   */
  void PortProfileHelper::appendConnectorProfile(ConnectorProfile conn_profile)
  {
    Guard guard(m_mutex);

    m_connProfiles.push_back(conn_profile);
  }


  /*!
   * @if jp
   * @brief ConnectorProfileList $B$r<hF@$9$k(B
   * @else
   * @brief Get ConnectorProfileList
   * @endif
   */
  const ConnectorProfileList PortProfileHelper::getConnectorProfiles() const
  {
    Guard guard(m_mutex);

    return m_connProfiles;
  }



  /*!
   * @if jp
   * @brief ConnectorProfile $B$r<hF@$9$k(B
   * @else
   * @brief Get ConnectorProfile
   * @endif
   */
  const ConnectorProfile
  PortProfileHelper::getConnectorProfile(const char* name) const
  {
    Guard guard(m_mutex);

    return m_connProfiles.find(conn_name(name));
  }


  /*!
   * @if jp
   * @brief ConnectorProfile $B$r<hF@$9$k(B
   * @else
   * @brief Get ConnectorProfile
   * @endif
   */
  const ConnectorProfile
  PortProfileHelper::getConnectorProfileById(const char* id) const
  {
    Guard guard(m_mutex);

    return m_connProfiles.find(conn_id(id));
  }


  /*!
   * @if jp
   * @brief ConnectorProfile $B$r:o=|$9$k(B
   * @param naem ConnectorProfile $B$NL>A0(B
   * @else
   * @brief Erase ConnectorProfile
   * @endif
   */
  void PortProfileHelper::eraseConnectorProfile(const char* name)
  {
    Guard guard(m_mutex);

    m_connProfiles.erase_if(conn_name(name));
    return;
  }


  /*!
   * @if jp
   * @brief ConnectorProfile $B$r:o=|$9$k(B
   * @else
   * @brief Erase ConnectorProfile
   * @endif
   */
  void PortProfileHelper::eraseConnectorProfileById(const char* id)
  {
    Guard guard(m_mutex);

    m_connProfiles.erase_if(conn_id(id));
    return;
  }


  /*!
   * @if jp
   * @brief PortProfile $B$N(B owner $B$r@_Dj$9$k(B
   * @else
   * @brief Set owner's object reference to the PortProfile
   * @endif
   */
  void PortProfileHelper::setOwner(RTObject_ptr owner)
  {
    Guard guard(m_mutex);

    m_owner = owner;
  }


  /*!
   * @if jp
   * @brief PortProfile $B$N(B owner $B$r<hF@$9$k(B
   * @else
   * @endif
   */
  RTObject_ptr PortProfileHelper::getOwner() const
  {
    Guard guard(m_mutex);

    return m_owner;
  }


  /*!
   * @if jp
   * @brief PortProfile $B$N(B properties $B$r@_Dj$9$k(B
   * @else
   * @brief Set properties to the PortProfile
   * @endif
   */
  void PortProfileHelper::setProperties(NVList& prop)
  {
    Guard guard(m_mutex);

    m_properties = prop;
  }


  /*!
   * @if jp
   * @brief PortProfile $B$N(B properties $B$r<hF@$9$k(B
   * @else
   * @brief Get properties of the PortProfile
   * @endif
   */
  const NVList& PortProfileHelper::getProperties() const
  {
    Guard guard(m_mutex);

    return m_properties;
  }

};
