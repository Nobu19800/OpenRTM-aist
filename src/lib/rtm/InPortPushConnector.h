// -*- C++ -*-
/*!
 * @file InPortPushConnector.h
 * @brief Push type connector class
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

#ifndef RTC_INPORTPUSHCONNECTOR_H
#define RTC_INPORTPUSHCONNECTOR_H

#include <rtm/InPortConnector.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherBase.h>

namespace RTC
{
  class InPortProvider;

  class InPortPushConnector
    : public InPortConnector
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * InPortPushConnector �� InPortConsumer �ν�ͭ������ġ�
     * �������äơ�InPortPushConnector ������ˤϡ�InPortConsumer��Ʊ����
     * ���Ρ��������롣
     *
     * @param info ConnectorInfo
     * @param consumer InPortConsumer
     *
     * @else
     * @brief Constructor
     *
     * InPortPushConnector assume ownership of InPortConsumer.
     * Therefore, InPortConsumer will be deleted when InPortPushConnector
     * is destructed.
     *
     * @param info ConnectorInfo
     * @param consumer InPortConsumer
     *
     * @endif
     */
    InPortPushConnector(ConnectorInfo info,
                        InPortProvider* provider,
                        ConnectorListeners& listeners,
                        CdrBufferBase* buffer = 0);

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * disconnect() ���ƤФ졢consumer, publisher, buffer �����Ρ��������롣
     *
     * @else
     *
     * @brief Destructor
     *
     * This operation calls disconnect(), which destructs and deletes
     * the consumer, the publisher and the buffer.
     *
     * @endif
     */
    virtual ~InPortPushConnector();

    /*!
     * @if jp
     * @brief �ǡ������ɤ߽Ф�
     *
     * �Хåե�����ǡ������ɤ߽Ф�
     *
     * @else
     *
     * @brief Reading data
     *
     * Read data from the buffer.
     *
     * @endif
     */
    virtual ReturnCode read(cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief ��³���
     *
     * consumer, publisher, buffer �����Ρ��������롣
     *
     * @else
     *
     * @brief disconnect
     *
     * This operation destruct and delete the consumer, the publisher
     * and the buffer.
     *
     * @endif
     */
    virtual ReturnCode disconnect();

    virtual void activate(){}; // do nothing
    virtual void deactivate(){}; // do nothing
  protected:
    /*!
     * @if jp
     * @brief Buffer������
     * @else
     * @brief create buffer
     * @endif
     */
    virtual CdrBufferBase* createBuffer(ConnectorInfo& info);

    /*!
     * @if jp
     * @brief ��³��Ω���˥�����Хå���Ƥ�
     * @else
     * @brief Invoke callback when connection is established
     * @endif
     */
    void onConnect();

    /*!
     * @if jp
     * @brief ��³���ǻ��˥�����Хå���Ƥ�
     * @else
     * @brief Invoke callback when connection is destroied
     * @endif
     */
    void onDisconnect();

  private:
    /*!
     * @if jp
     * @brief InPortConsumer �ؤΥݥ���
     * @else
     * @brief the pointer to the InPortConsumer
     * @endif
     */
    InPortProvider* m_provider;

    /*!
     * @if jp
     * @brief ConnectorListenrs �ؤλ���
     * @else
     * @brief A reference to a ConnectorListener
     * @endif
     */
    ConnectorListeners& m_listeners;

    bool m_deleteBuffer;
  };
}; // namespace RTC

#endif  // RTC_PUSH_CONNECTOR_H
