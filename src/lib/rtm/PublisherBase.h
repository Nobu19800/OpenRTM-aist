// -*- C++ -*-
/*!
 * @file PublisherBase.h
 * @brief Publisher base class
 * @date $Date: 2007-12-31 03:08:06 $
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

#ifndef RTC_PUBLISHERBASE_H
#define RTC_PUBLISHERBASE_H

#include <coil/Properties.h>
#include <coil/Factory.h>
#include <rtm/RTC.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/DataPortStatus.h>

namespace coil
{
  class Properties;
}
namespace RTC
{
  class InPortConsumer;
  class ConnectorListeners;
  class ConnectorInfo;

  /*!
   * @if jp
   *
   * @class PublisherBase
   *
   * @brief Publisher ���쥯�饹
   * 
   * �ǡ������Х����ߥ󥰤�����������Ф��ư����Publisher* �δ��쥯�饹��
   * �Ƽ� Publisher �Ϥ��Υ��饹��Ѿ����ƾܺ٤�������롣
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class PublisherBase
   *
   * @brief Base class of Publisher.
   *
   * This is a base class of Publisher*. This class manages data send timing.
   * Variation of Publisher* which implements details of Publisher inherits
   * this PublisherBase class.
   *
   * @endif
   */
  class PublisherBase
    : public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief Destructor
     *
     * @endif
     */
    virtual ~PublisherBase(void){};

    /*!
     * @if jp
     * @brief ��������
     *
     * InPortConsumer�γƼ������Ԥ����������饹�Ǥϡ�Ϳ����줿
     * Properties����ɬ�פʾ����������ƳƼ������Ԥ������� init() ��
     * ���ϡ�OutPortProvider����ľ�太��ӡ���³���ˤ��줾��ƤФ���
     * ǽ�������롣�������äơ����δؿ���ʣ����ƤФ�뤳�Ȥ����ꤷ�Ƶ�
     * �Ҥ����٤��Ǥ��롣
     * 
     * @param prop �������
     *
     * @else
     *
     * @brief Initializing configuration
     *
     * This operation would be called to configure in initialization.
     * In the concrete class, configuration should be performed
     * getting appropriate information from the given Properties data.
     * This function might be called right after instantiation and
     * connection sequence respectivly.  Therefore, this function
     * should be implemented assuming multiple call.
     *
     * @param prop Configuration information
     *
     * @endif
     */
    virtual ReturnCode init(coil::Properties& prop) = 0;
    virtual ReturnCode setConsumer(InPortConsumer* consumer) = 0;
    virtual ReturnCode setBuffer(BufferBase<cdrMemoryStream>* buffer) = 0;
    virtual ReturnCode setListener(ConnectorInfo& info,
                                   ConnectorListeners* listeners) = 0;
    virtual ReturnCode write(const cdrMemoryStream& data,
                             unsigned long sec,
                             unsigned long usec) = 0;

    virtual bool isActive() = 0;
    virtual ReturnCode activate() = 0;
    virtual ReturnCode deactivate() = 0;


    

    /*!
     * @if jp
     *
     * @brief Publisher ���˴����롣
     *
     * ���� Publisher ���˴����롣
     * ���� Publisher �����פˤʤä����� PublisherFactory ����ƤӽФ���롣
     *
     * @else
     *
     * @brief Release the Publisher
     *
     * Release this Publisher.
     * When Publisher becomes unnecessary, this is invoked from
     * PublisherFactory. 
     *
     * @endif
     */
    virtual void release(){}
  };

  typedef coil::GlobalFactory<PublisherBase> PublisherFactory;

};
#endif // RTC_PUBLISHERBASE_H
