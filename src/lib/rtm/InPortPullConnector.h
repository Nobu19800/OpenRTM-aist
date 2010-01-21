// -*- C++ -*-
/*!
 * @file InPortPullConnector.h
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

#ifndef RTC_OUTPORTPULLCONNECTOR_H
#define RTC_OUTPORTPULLCONNECTOR_H

#include <rtm/InPortConnector.h>
#include <rtm/InPortProvider.h>
#include <rtm/PublisherBase.h>
#include <rtm/DataPortStatus.h>

namespace RTC
{
  class OutPortConsumer;
  class ConnectorListeners;

  /*!
   * @if jp
   * @class InPortPullConnector
   * @brief InPortPullConnector ���쥯�饹
   *
   * InPort �� Push ���ǡ����ե��Τ���� Connector
   *
   * @since 1.0.0
   *
   * @else
   * @class InPortPullConnector
   * @brief InPortPullConnector base class
   *
   * A connector class for pull type dataflow of InPort
   *
   * @since 1.0.0
   *
   * @endif
   */
  class InPortPullConnector
    : public InPortConnector
  {
  public:
    DATAPORTSTATUS_ENUM
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    InPortPullConnector(ConnectorInfo info,
                        OutPortConsumer* consumer,
                        ConnectorListeners& listeners,
                        CdrBufferBase* buffer = 0);

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortPullConnector();

    /*!
     * @if jp
     * @brief read �ؿ�
     *
     * Buffer ����ǡ����� InPort �� read ����ؿ�
     *
     * @else
     * @brief Destructor
     *
     * The read function to read data from buffer to InPort
     *
     * @endif
     */
    virtual ReturnCode read(cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief ��³����ؿ�
     *
     * Connector ���ݻ����Ƥ�����³��������
     *
     * @else
     * @brief Disconnect connection
     *
     * This operation disconnect this connection
     *
     * @endif
     */
    virtual ReturnCode disconnect();

    /*!
     * @if jp
     * @brief �����ƥ��ֲ�
     *
     * ���Υ��ͥ����򥢥��ƥ��ֲ�����
     *
     * @else
     *
     * @brief Connector activation
     *
     * This operation activates this connector
     *
     * @endif
     */
    virtual void activate(){}; // do nothing

    /*!
     * @if jp
     * @brief �󥢥��ƥ��ֲ�
     *
     * ���Υ��ͥ������󥢥��ƥ��ֲ�����
     *
     * @else
     *
     * @brief Connector deactivation
     *
     * This operation deactivates this connector
     *
     * @endif
     */
    virtual void deactivate(){}; // do nothing

  protected:
    /*!
     * @if jp
     * @brief Buffer������
     * @else
     * @brief create buffer
     * @endif
     */
    CdrBufferBase* createBuffer(ConnectorInfo& info);

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
     * @brief OutPortConsumer �ؤΥݥ���
     * @else
     * @brief the pointer to the OutPortConsumer
     * @endif
     */
    OutPortConsumer* m_consumer;
    
    /*!
     * @if jp
     * @brief ConnectorListenrs �ؤλ���
     * @else
     * @brief A reference to a ConnectorListener
     * @endif
     */
    ConnectorListeners& m_listeners;
  };
}; // namespace RTC

#endif  // RTC_PULL_CONNECTOR_H
