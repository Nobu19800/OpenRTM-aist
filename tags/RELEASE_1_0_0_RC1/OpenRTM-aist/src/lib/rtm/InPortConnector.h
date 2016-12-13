/*! -*- C++ -*-
 *
 * @file InPortConnector.h
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

#ifndef RTC_INPORTCONNECTOR_H
#define RTC_INPORTCONNECTOR_H

#include <rtm/ConnectorBase.h>

namespace RTC
{
  /*!
   * @if jp
   * @class InPortConnector
   * @brief InPortConnector ���쥯�饹
   *
   * InPort �� Push/Pull �Ƽ� Connector �����������뤿���
   * ���쥯�饹��
   *
   * @since 1.0.0
   *
   * @else
   * @class InPortConnector
   * @brief I��PortConnector base class
   *
   * The base class to derive subclasses for InPort's Push/Pull Connectors
   *
   * @since 1.0.0
   *
   * @endif
   */
  class InPortConnector
    : public ConnectorBase
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
    InPortConnector(ConnectorBase::Profile& profile,
                    CdrBufferBase* buffer);

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortConnector();

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
    virtual const Profile& profile();
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
    virtual const char* id();

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
    virtual const char* name();

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
    virtual ReturnCode disconnect() = 0;

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
    virtual CdrBufferBase* getBuffer();

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
    virtual ReturnCode read(cdrMemoryStream& data) = 0;

  protected:
    Logger rtclog;
    Profile m_profile;
    CdrBufferBase* m_buffer;
  };
}; // namespace RTC

#endif // RTC_INPORTCONNECTOR_H
