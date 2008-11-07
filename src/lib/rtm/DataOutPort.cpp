// -*- C++ -*-
/*!
 * @file DataOutPort.cpp
 * @brief Base class of OutPort
 * @date $Date: 2007-12-31 03:08:02 $
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

#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4290 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#endif // WIN32

#include <rtm/DataOutPort.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/PublisherBase.h>
#include <iostream>

#ifdef WIN32
#pragma warning( pop )
#endif // WIN32

namespace RTC
{
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  DataOutPort::~DataOutPort()
  {
  };
  
  //============================================================
  // protected functions
  //============================================================
  /*!
   * @if jp
   * @brief Interface ������������
   * @else
   * @brief Publish interface information
   * @endif
   */
  ReturnCode_t
  DataOutPort::publishInterfaces(ConnectorProfile& connector_profile)
  {
    std::for_each(m_providers.begin(), m_providers.end(),
		  publish(connector_profile.properties));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interface ����³����
   * @else
   * @brief Subscribe to the interface
   * @endif
   */
  ReturnCode_t
  DataOutPort::subscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    subscribe s(connector_profile);
    s = std::for_each(m_consumers.begin(), m_consumers.end(), s);
    if (s._consumer == NULL) return RTC::RTC_OK;
    
    // Pubslihser ������
    PublisherBase* publisher;
    coil::Properties prop(NVUtil::toProperties(connector_profile.properties));
    
    publisher = m_pf.create(s._consumer->clone(), prop);
    
    // Publisher �� OutPort �˥����å�
    m_outport.attach(connector_profile.connector_id, publisher);
    
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interface ����³��������
   * @else
   * @brief Disconnect the interface connection
   * @endif
   */
  void
  DataOutPort::unsubscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    PublisherBase* publisher;
    publisher = m_outport.detach(connector_profile.connector_id);
    m_pf.destroy(publisher);
    return;
  }
};
