// -*- C++ -*-
/*!
 * @file LogstreamBase.h
 * @brief Logger stream buffer base class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Noriaki Ando
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_LOGSTREAMBASE_H
#define RTC_LOGSTREAMBASE_H

#include <coil/Properties.h>
#include <coil/Factory.h>
#include <coil/Logger.h>

#include <rtm/RTC.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/DataPortStatus.h>

namespace RTC
{
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
  typedef std::basic_streambuf<char> StreambufType;
  class LogstreamBase
  {
  public:
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
    virtual ~LogstreamBase(void){};

    /*!
     * @if jp
     * @brief ��������
     *
     * Logstream���饹�γƼ������Ԥ����������饹�Ǥϡ�Ϳ����줿
     * Properties����ɬ�פʾ����������ƳƼ������Ԥ���
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
     *
     * @param prop Configuration information
     *
     * @endif
     */
    virtual bool init(const coil::Properties& prop) = 0;
    
    virtual StreambufType* getStreamBuffer() = 0;

  };

  typedef coil::GlobalFactory<LogstreamBase> LogstreamFactory;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  EXTERN template class DLL_PLUGIN coil::GlobalFactory<LogstreamBase>;
#endif
};
#endif // RTC_LOGSTREAMBASE_H
