/*! -*- C++ -*-
 *
 * @file InPortConnector.cpp
 * @brief InPortConnector base class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
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

#include <rtm/InPortConnector.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  InPortConnector::InPortConnector(InPortConnector::Profile& profile,
                                   CdrBufferBase* buffer)
    : rtclog("InPortConnector"), m_profile(profile), m_buffer(buffer)
  {
  }

  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  InPortConnector::~InPortConnector()
  {
  }

  /*!
   * @if jp
   * @brief Profile ����
   *
   * Connector Profile ���������
   *
   * @else
   * @brief Getting Profile
   *
   * This operation returns Connector Profile
   *
   * @endif
   */
  const InPortConnector::Profile& InPortConnector::profile()
  {
    RTC_TRACE(("profile()"));
    return m_profile;
  }

  /*!
   * @if jp
   * @brief Connector ID ����
   *
   * Connector ID ���������
   *
   * @else
   * @brief Getting Connector ID
   *
   * This operation returns Connector ID
   *
   * @endif
   */
  const char* InPortConnector::id()
  {
    RTC_TRACE(("id() = %s", profile().id.c_str()));
    return profile().id.c_str();
  }

  /*!
   * @if jp
   * @brief Connector ̾����
   *
   * Connector ̾���������
   *
   * @else
   * @brief Getting Connector name
   *
   * This operation returns Connector name
   *
   * @endif
   */
  const char* InPortConnector::name()
  {
    RTC_TRACE(("name() = %s", profile().name.c_str()));
    return profile().name.c_str();
  }

  /*!
   * @if jp
   * @brief Buffer ���������
   *
   * Connector ���ݻ����Ƥ��� Buffer ���֤�
   *
   * @else
   * @brief Getting Buffer
   *
   * This operation returns this connector's buffer
   *
   * @endif
   */
  CdrBufferBase* InPortConnector::getBuffer()
  {
    return m_buffer;
  }
}; // namespace RTC
