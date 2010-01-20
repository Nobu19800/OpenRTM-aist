// -*- C++ -*-
/*!
 * @file ConnectorBase.h
 * @brief Connector base class
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

#ifndef RTC_CONNECTORBASE_H
#define RTC_CONNECTORBASE_H

#include <coil/stringutil.h>
#include <coil/Properties.h>

#include <rtm/RTC.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/DataPortStatus.h>
#include <rtm/SystemLogger.h>

namespace RTC
{
  /*!
   * @if jp
   * @class ConnectorInfo ���饹
   * @brief ConnectorInfo ���饹
   *
   * @class ConnectorInfo class
   * @brief ConnectorInfo class
   *
   * @endif
   */
  class ConnectorInfo
  {
  public:
    ConnectorInfo(const char* name_, const char* id_,
                  coil::vstring ports_, coil::Properties properties_)
      : name(name_), id(id_)
      , ports(ports_), properties(properties_)
    {
    }
    ConnectorInfo()
    {
    }
    std::string name;
    std::string id;
    coil::vstring ports;
    coil::Properties properties;
  };

  typedef std::vector<ConnectorInfo> ConnectorInfoList;

  class ConnectorBase;
  typedef std::vector<ConnectorBase*> ConnectorList;
  

  /*!
   * @if jp
   * @class ConnectorBase
   * @brief Connector ���쥯�饹
   *
   * InPort/OutPort, Push/Pull �Ƽ� Connector �����������뤿���
   * ���쥯�饹��
   *
   * @since 1.0.0
   *
   * @else
   * @class ConnectorBase
   * @brief Connector Base class
   *
   * The base class to derive subclasses for InPort/OutPort,
   * Push/Pull Connectors
   *
   * @since 1.0.0
   *
   * @endif
   */
  class ConnectorBase
    : public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @class Profile
     * @brief Connector profile �����빽¤��
     *
     * ConnectorBase ����Ӥ����������饹�ǰ��� ConnectorProfile ��¤�Ρ�
     *
     * @since 1.0.0
     *
     * @else
     * @class Profile
     * @brief local representation of Connector profile
     *
     * ConnectorProfile struct for ConnectorBase and its subclasses.
     *
     * @since 1.0.0
     *
     * @endif
     */



    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorBase(){};

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
    virtual const ConnectorInfo& profile() = 0;

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
    virtual const char* id() = 0;

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
    virtual const char* name() = 0;

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
    virtual CdrBufferBase* getBuffer() = 0;

    virtual void activate() = 0;
    virtual void deactivate() = 0;

  private:
    // non-copyable class
    //    ConnectorBase(const ConnectorBase& x);
    //    ConnectorBase& operator=(const ConnectorBase& x);
  };
}; // namespace RTC

#endif // RTC_CONNECTORBASE_H
