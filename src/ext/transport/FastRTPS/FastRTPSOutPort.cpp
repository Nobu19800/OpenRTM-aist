﻿// -*- C++ -*-
/*!
 * @file  FastRTPSOutPort.cpp
 * @brief FastRTPSOutPort class
 * @date  $Date: 2019-01-31 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2019
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */

#include <rtm/NVUtil.h>
#include <coil/UUID.h>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include "FastRTPSOutPort.h"
#include "FastRTPSManager.h"
#include "FastRTPSMessageInfo.h"






namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @param buffer The buffer object that is attached to this Consumer
   * @endif
   */
  FastRTPSOutPort::FastRTPSOutPort(void)
    : rtclog("FastRTPSOutPort")
  {
    m_start = false;
  }
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  FastRTPSOutPort::~FastRTPSOutPort(void)
  {
    RTC_PARANOID(("~FastRTPSOutPort()"));
    
  }

  /*!
   * @if jp
   * @brief 設定初期化
   * @else
   * @brief Initializing configuration
   * @endif
   */
  void FastRTPSOutPort::init(coil::Properties& prop)
  { 
    RTC_PARANOID(("ROSOutPort::init()"));
    
    if(prop.propertyNames().size() == 0)
    {
      RTC_DEBUG(("Property is empty."));
      return;
    }

    std::string profile_xml = prop.getProperty("QOSXML", "");
    FastRTPSManager& topicmgr = FastRTPSManager::instance(profile_xml);
    eprosima::fastrtps::Participant* participant = topicmgr.getParticipant();

    if (participant == nullptr)
    {
        RTC_ERROR(("Can not initialize Fast-RTPS"));
        return;
    }

    std::string marshaling_type = prop.getProperty("marshaling_type", "corba");
    m_topic = prop.getProperty("fastrtps.topic", "chatter");


    const std::string str_corba = "corba";

    bool compare = (marshaling_type.compare(0, str_corba.size(), str_corba) != 0);

    if (compare)
    {
        FastRTPSMessageInfoBase* info = FastRTPSMessageInfoFactory::instance().createObject(marshaling_type);

        if (!info)
        {
            RTC_ERROR(("Can not find message type(%s)", marshaling_type.c_str()));
            return;
        }

        m_dataType = info->data_type();
        m_topic = info->topic_name(m_topic);

        FastRTPSMessageInfoFactory::instance().deleteObject(info);

    }
    else
    {
        std::string data = prop.getProperty("data_type", "IDL:RTC/CDR_Data:1.0");

        coil::vstring typelist = coil::split(data, ":");
        if (typelist.size() == 3)
        {
            m_dataType = coil::replaceString(std::move(typelist[1]), "/", "::");
        }
        else
        {
            m_dataType = data;
        }
    }

    if (!topicmgr.registeredType(m_dataType.c_str()))
    {
        CORBACdrDataPubSubType* type = new CORBACdrDataPubSubType();
        if (compare)
        {
            type->init(m_dataType, true);
        }
        else
        {
            type->init(m_dataType, false);
        }

        std::string endian_type{coil::normalize(
                prop.getProperty("serializer.cdr.endian", ""))};
        std::vector<std::string> endian(coil::split(endian_type, ","));
        if (endian[0] == "little")
        {
            type->setEndian(true);
        }
        else if (endian[0] == "big")
        {
            type->setEndian(false);
        }

        topicmgr.registerType(type);
    }

    eprosima::fastrtps::PublisherAttributes Wparam;
    Wparam.topic.topicKind = eprosima::fastrtps::rtps::NO_KEY;
    Wparam.topic.topicDataType = m_dataType;
    Wparam.topic.topicName = m_topic;
    Wparam.historyMemoryPolicy = eprosima::fastrtps::rtps::PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    Wparam.qos.m_publishMode.kind = eprosima::fastrtps::ASYNCHRONOUS_PUBLISH_MODE;
    m_publisher = eprosima::fastrtps::Domain::createPublisher(participant, Wparam, (eprosima::fastrtps::PublisherListener*)&m_listener);
    if (m_publisher == nullptr)
    {
        RTC_ERROR(("Publisher initialize failed"));
        return;
    }

  }

  /*!
   * @if jp
   * @brief バッファへのデータ書込
   * @else
   * @brief Write data into the buffer
   * @endif
   */
  DataPortStatus FastRTPSOutPort::put(ByteData& data)
  {
    
    RTC_PARANOID(("put()"));
    RTC_VERBOSE(("Data size:%d", data.getDataLength()));
    if (m_publisher == nullptr)
    {
        RTC_VERBOSE(("Publisher is None"));
        return DataPortStatus::PRECONDITION_NOT_MET;
    }
    if (m_publisher->write(&data))
    {
        RTC_PARANOID(("write:OK"));
        return DataPortStatus::PORT_OK;
    }
    else
    {
        RTC_ERROR(("write:ERROR"));
        return DataPortStatus::PORT_ERROR;
    }
    
  }

  /*!
   * @if jp
   * @brief InterfaceProfile情報を公開する
   * @else
   * @brief Publish InterfaceProfile information
   * @endif
   */
  void FastRTPSOutPort::
  publishInterfaceProfile(SDOPackage::NVList& /*properties*/)
  {
    return;
  }

  /*!
   * @if jp
   * @brief データ送信通知への登録
   * @else
   * @brief Subscribe to the data sending notification
   * @endif
   */
  bool FastRTPSOutPort::
  subscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("subscribeInterface()"));
    RTC_DEBUG_STR((NVUtil::toString(properties)));
    
    
    return true;
  }
  
  /*!
   * @if jp
   * @brief データ送信通知からの登録解除
   * @else
   * @brief Unsubscribe the data send notification
   * @endif
   */
  void FastRTPSOutPort::
  unsubscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("unsubscribeInterface()"));
    RTC_DEBUG_STR((NVUtil::toString(properties)));

    if (m_publisher != nullptr)
    {
    }
  }


  /*!
   * @if jp
   * @brief コンストラクタ
   *
   * コンストラクタ
   *
   *
   * @else
   * @brief Constructor
   *
   * Constructor
   *
   *
   * @endif
   */
  FastRTPSOutPort::PubListener::PubListener()
  {
  }


  /*!
   * @if jp
   * @brief デストラクタ
   *
   * デストラクタ
   *
   * @else
   * @brief Destructor
   *
   * Destructor
   *
   * @endif
   */
  FastRTPSOutPort::PubListener::~PubListener()
  {
  }

  /*!
   * @if jp
   * @brief
   *
   * 同じトピックのPublisherを検出したときのコールバック関数
   *
   * @param sub Subscriber
   * @param info 一致情報
   *
   * @else
   * @brief
   *
   * @param sub
   * @param info
   *
   *
   * @endif
   */
  void FastRTPSOutPort::PubListener::onPublicationMatched(eprosima::fastrtps::Publisher* /*pub*/, eprosima::fastrtps::rtps::MatchingInfo& /*info*/)
  {
  }


  
} // namespace RTC
