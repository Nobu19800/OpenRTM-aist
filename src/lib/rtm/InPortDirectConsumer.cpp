// -*- C++ -*-
/*!
 * @file  InPortDirectConsumer.h
 * @brief InPortDirectConsumer class
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2015
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

#include <rtm/NVUtil.h>
#include <rtm/InPortDirectConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @param buffer The buffer object that is attached to this Consumer
   * @endif
   */
  InPortDirectConsumer::InPortDirectConsumer(void)
    : rtclog("InPortDirectConsumer")
  {
  }
  
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  InPortDirectConsumer::~InPortDirectConsumer(void)
  {
    RTC_PARANOID(("~InPortDirectConsumer()"));
  }

  /*!
   * @if jp
   * @brief ��āE鴁E�
   * @else
   * @brief Initializing configuration
   * @endif
   */
  void InPortDirectConsumer::init(coil::Properties& prop)
  {
    m_properties = prop;
  }

  /*!
   * @if jp
   * @brief �Хåե��ؤΥǡ������
   * @else
   * @brief Write data into the buffer
   * @endif
   */
  InPortConsumer::ReturnCode InPortDirectConsumer::
  put(cdrMemoryStream& data)
  {
    RTC_PARANOID(("put(): never called."));
    return UNKNOWN_ERROR;
  }

  /*!
   * @if jp
   * @brief InterfaceProfile������������E   * @else
   * @brief Publish InterfaceProfile information
   * @endif
   */
  void InPortDirectConsumer::
  publishInterfaceProfile(SDOPackage::NVList& properties)
  {
    return;
  }

  /*!
   * @if jp
   * @brief �ǡ����������Τؤ���Ͽ
   * @else
   * @brief Subscribe to the data sending notification
   * @endif
   */
  bool InPortDirectConsumer::
  subscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("subscribeInterface(): do nothing"));
    return true;
  }
  
  /*!
   * @if jp
   * @brief �ǡ����������Τ������Ͽ��E   * @else
   * @brief Unsubscribe the data send notification
   * @endif
   */
  void InPortDirectConsumer::
  unsubscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("unsubscribeInterface(): do nothing"));
  }
};     // namespace RTC

extern "C"
{
  /*!
   * @if jp
   * @brief �⥸�塼��E鴁E��ؿ�E   * @else
   * @brief Module initialization
   * @endif
   */
  void InPortDirectConsumerInit(void)
  {
    RTC::InPortConsumerFactory& factory(RTC::InPortConsumerFactory::instance());
    factory.addFactory("direct",
                       ::coil::Creator< ::RTC::InPortConsumer,
                                        ::RTC::InPortDirectConsumer>,
                       ::coil::Destructor< ::RTC::InPortConsumer,
                                           ::RTC::InPortDirectConsumer>);
  }
};
