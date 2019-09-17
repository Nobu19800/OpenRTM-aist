﻿// -*- C++ -*-
/*!
 * @file InPortPullConnector.cpp
 * @brief InPortPull type connector class
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

#include <rtm/InPortPullConnector.h>
#include <rtm/OutPortConsumer.h>
#include <rtm/ConnectorListener.h>

#include <string>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  InPortPullConnector::InPortPullConnector(ConnectorInfo info,
                                           OutPortConsumer* consumer,
                                           ConnectorListeners* listeners,
                                           CdrBufferBase* buffer)
    : InPortConnector(info, listeners, buffer), m_consumer(consumer),
      m_listeners(listeners)
  {
    if (buffer == nullptr)
      {
        m_buffer = createBuffer(m_profile);
      }
    if (m_buffer == nullptr || m_consumer == nullptr)
      {
        throw std::bad_alloc();
      }
    m_buffer->init(info.properties.getNode("buffer"));
    m_consumer->setBuffer(m_buffer);
    m_consumer->setListener(info, m_listeners);

    std::string type{info.properties.getProperty("marshaling_type", "corba")};
    m_marshaling_type = coil::eraseBothEndsBlank(
      info.properties.getProperty("in.marshaling_type", type));

    onConnect();
  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  InPortPullConnector::~InPortPullConnector()
  {
    onDisconnect();
    disconnect();
  }

  /*!
   * @if jp
   * @brief read 関数
   * @else
   * @brief Destructor
   * @endif
   */
  DataPortStatus
  InPortPullConnector::read(ByteDataStreamBase* data)
  {
    RTC_TRACE(("InPortPullConnector::read()"));
    if (m_consumer == nullptr)
      {
        return DataPortStatus::PORT_ERROR;
      }
    
    DataPortStatus ret = m_consumer->get(m_data);
    data->writeData(m_data.getBuffer(), m_data.getDataLength());
    return ret;
  }

  /*!
   * @if jp
   * @brief 接続解除関数
   * @else
   * @brief Disconnect connection
   * @endif
   */
  DataPortStatus InPortPullConnector::disconnect()
  {
    RTC_TRACE(("disconnect()"));
    // delete consumer
    if (m_consumer != nullptr)
      {
        OutPortConsumerFactory& cfactory(OutPortConsumerFactory::instance());
        cfactory.deleteObject(m_consumer);
      }
    m_consumer = nullptr;

    return DataPortStatus::PORT_OK;
  }

  /*!
   * @if jp
   * @brief Bufferの生成
   * @else
   * @brief create buffer
   * @endif
   */
  CdrBufferBase* InPortPullConnector::createBuffer(ConnectorInfo& info)
  {
    std::string buf_type;
    buf_type = info.properties.getProperty("buffer_type",
                                              "ring_buffer");
    return CdrBufferFactory::instance().createObject(buf_type);
  }

  /*!
   * @if jp
   * @brief 接続確立時にコールバックを呼ぶ
   * @else
   * @brief Invoke callback when connection is established
   * @endif
   */
  void InPortPullConnector::onConnect()
  {
    m_listeners->connector_[ON_CONNECT].notify(m_profile);
  }

  /*!
   * @if jp
   * @brief 接続切断時にコールバックを呼ぶ
   * @else
   * @brief Invoke callback when connection is destroied
   * @endif
   */
  void InPortPullConnector::onDisconnect()
  {
    m_listeners->connector_[ON_DISCONNECT].notify(m_profile);
  }

  void InPortPullConnector::unsubscribeInterface(const coil::Properties& prop)
  {
      if (m_consumer != nullptr)
      {
          SDOPackage::NVList nv;
          NVUtil::copyFromProperties(nv, prop);
          m_consumer->unsubscribeInterface(nv);
      }
  }
} // namespace RTC

