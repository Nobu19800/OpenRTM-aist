// -*- C++ -*-
/*!
 * @file FluentBit.h
 * @brief File logger stream class
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

#ifndef RTC_LOGGER_FLUENTBIT_H
#define RTC_LOGGER_FLUENTBIT_H

#include <string>
#include <fstream>
#include <iostream>
#include <fluent-bit.h>

#include <coil/stringutil.h>
#include <rtm/LogstreamBase.h>

#ifndef LINE_MAX
#define LINE_MAX  1024
#endif

#ifndef BUFFER_LEN
#define BUFFER_LEN LINE_MAX
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class FluentbitStream
   *
   * ���Υ��饹�� �����Ϥ� fluent-bit ���������뤿��� logstream_buf
   * ���饹�Ǥ��롣FluentBit ���饹�ˤƥ��󥹥��󥹲����졢
   * SystemLogger �� logstream ���ɲä���롣
   *
   * @else
   * @class FluentbitStream
   *
   * This class is a logstream_buf class to send log output to
   * fluent-bit. This is instantiate in the FluentBit class and it is
   * added to SystemLogger's logstreams.
   *
   * @endif
   */
  class FluentBitStream
    : public StreambufType
  {
  public:
    FluentBitStream();

    virtual ~FluentBitStream();

    bool init(const coil::Properties& prop);

    bool createOutputStream(const coil::Properties& prop);

    bool createInputStream(const coil::Properties& prop);

  protected:
    std::streamsize pushLogger();

    virtual std::streamsize xsputn(const char_type* str,
                                   std::streamsize insize);

  private:
    char m_buf[BUFFER_LEN];
    size_t m_pos;

    typedef int FlbHandler;
    FlbHandler m_fibInLib;

    std::vector<FlbHandler> m_flbIn;
    std::vector<FlbHandler> m_flbOut;

    // Static variables
    /*!
     * @brief Fluent-bit context
     */
    static flb_ctx_t* s_flbContext;
    /*!
     * @brief Fluent-bit instance count
     */
    static int s_instance;
  };

  /*!
   * @if jp
   * @class FluentBit
   *
   * ���Υ��饹�� �����Ϥ� fluent-bit ���������뤿��Υ����ȥ꡼��
   * �ѥץ饰���󥯥饹�Ǥ��롣
   *
   * fluent-bit �ϥ�������ʬ�ۥߥɥ륦���� fluentd ��C��������Ǥ��롣
   * fluent-bit/fluentd ���͡��ʥץ�ȥ���ǥ��μ������ե��륿��󥰡�
   * ������Ԥ����Ȥ��Ǥ��롣���Υ��饹�ϡ������ȥ꡼��Υץ饰�����
   * �������� FluentBit ���饹�� std::stream_buff ���饹�Υ��֥��饹��
   * ���ꡢ�ºݤ� FluentBit �ؤΥ��ν�����ʬ��ô�����饹�Ǥ��롣
   *
   * �ǥե���ȤǤϡ�OpenRTM�Υ����Ϥ����� (input) �Ȥ��Ƽ�ꡢ
   * rtc.conf �����ꤵ�줿���� (output) ���Ф��ƥ������Ф��뤳�Ȥ���
   * ���롣input �� fluent-bit �����ѤǤ���ץ饰����� rtc.conf ����ͭ
   * ���ˤ��뤳�Ȥ��Ǥ���¾�� fluentd/fluent-bit ����Υ����Ϥ������
   * ���ꡢCPU���������̤ʤɤ�����ϤȤ��Ƽ������뤳�Ȥ��ǽ�Ǥ�
   * �롣�¼�Ū�ˡ����ޥ�ɥ饤��ץ����� fluent-bit �Ȥۤ�Ʊ������
   * ���¸���ǽ�ˤʤäƤ��롣
   *
   * ���ץ����ϡ�����Ū�ˤ� fluent-bit �� key-value ���Υץ�ѥƥ���
   * rtc.conf �ǻ��ꤹ�뤳�ȤǤ��٤ƤΥץ饰��������ѤǤ��뤬���ʲ��ˡ�
   * ��ɽŪ�ʥץ饰����Ȥ��Υ��ץ����򼨤���
   *   
   * * Available Output plugins
   * - reference: http://fluentbit.io/documentation/0.8/output/index.html
   *
   * ** forward: fluentd forwarding
   * ______________________________________________________________________
   * |  key   |                  Description                 |   Default  |
   * ----------------------------------------------------------------------
   * | host   | Target host where Fluent-Bit  or Fluentd are |  127.0.0.1 |
   * |        | listening for Forward messages.              |            |
   * ----------------------------------------------------------------------
   * | port   | TCP port of the target service.              |      24224 |
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   * Example:
   * logger.logstream.fluentd.output0.plugin: forward
   * logger.logstream.fluentd.output0.tag:    <tagname>
   * logger.logstream.fluentd.output0.host:   <fluentd_hostname>
   * logger.logstream.fluentd.output0.port:   <fluentd_port>
   *
   * ** es: Elasticsearch
   * ______________________________________________________________________
   * |  key   |                  Description                 |   Default  |
   * ----------------------------------------------------------------------
   * | host   | IP address or hostname of the target         |  127.0.0.1 |
   * |        | Elasticsearch instance.                      |            |
   * ----------------------------------------------------------------------
   * | port   | TCP port of the target Elasticsearch         |       9200 |
   * |        | instance.                                    |            |
   * ----------------------------------------------------------------------
   * | index  | Elastic index.                               | fluentbit  |
   * ----------------------------------------------------------------------
   * | type   | Elastic type.                                | test       |
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   *
   * Example:
   * logger.logstream.fluentd.output0.plugin: es
   * logger.logstream.fluentd.output0.tag:    <tagname>
   * logger.logstream.fluentd.output0.host:   <es_hostname>
   * logger.logstream.fluentd.output0.port:   <es_port>
   * logger.logstream.fluentd.output0.index:  <es_index>
   * logger.logstream.fluentd.output0.type:   <es_type>
   *
   * ** http: HTTP POST request in MessagePack format
   * ______________________________________________________________________
   * |   key  |            Description                       |   Default  |
   * ----------------------------------------------------------------------
   * |  Host  | IP address or hostname of the target HTTP    |  127.0.0.1 |
   * |        | Server.                                      |            |
   * ----------------------------------------------------------------------
   * |  Port  | TCP port of the target HTTP Server.          |         80 |
   * ----------------------------------------------------------------------
   * |  Proxy | Specify an HTTP Proxy. The expected format   |            |
   * |        | of this value is http://host:port.           |            |
   * |        | Note that https is not supported yet.        |            |
   * ----------------------------------------------------------------------
   * |  URI   | Specify an optional HTTP URI for the target  |          / |
   * |        | web server, e.g: /something                  |            |
   * ----------------------------------------------------------------------
   * | Format | Specify the data format to be used in the    |    msgpack |
   * |        | HTTP request body, by default it uses        |            |
   * |        | msgpack, optionally it can be set to json.   |            |
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   *
   * Example:
   * logger.logstream.fluentd.output0.plugin: http
   * logger.logstream.fluentd.output0.tag:    <tagname>
   * logger.logstream.fluentd.output0.host:   127.0.0.1
   * logger.logstream.fluentd.output0.port:   80
   * logger.logstream.fluentd.output0.proxy:
   * logger.logstream.fluentd.output0.uri:     /openrtm/
   * logger.logstream.fluentd.output0.format:  msgpack
   *
   * ** nats: NATS output plugin
   * ______________________________________________________________________
   * |  key   |                  Description                 |   Default  |
   * ----------------------------------------------------------------------
   * | host   | IP address or hostname of the NATS Server.   |  127.0.0.1 |
   * ----------------------------------------------------------------------
   * | port   | TCP port of the target NATS Server.          |       4222 |
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   *
   * Example:
   * logger.logstream.fluentd.output0.plugin: nats
   * logger.logstream.fluentd.output0.tag:    <tagname>
   * logger.logstream.fluentd.output0.host:   <nats_host>
   * logger.logstream.fluentd.output0.port:   <nats_port>
   *
   * * stdout: Standard Output plugin
   *
   * Example:
   * logger.logstream.fluentd.output0.plugin: stdin
   *
   * @else
   * @class FluentbitStream
   *
   * @endif
   */
  class FluentBit
    : public LogstreamBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * @else
     *
     * @brief Constructor
     *
     * @endif
     */
    FluentBit();

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
    virtual ~FluentBit(void);

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
    virtual bool init(const coil::Properties& prop);

    /*!
     * @if jp
     * @brief basic_strembuf �ؤΥݥ��󥿤��֤�
     *
     * Logger�ǻ��Ѥ��� basic_streambuf �ؤΥݥ��󥿤��֤���
     *
     * @return basic_streambuf (coil::LogStreambuf) �ؤΥݥ���
     *
     * @else
     *
     * @brief Returns a pointer to the basic_streambuf 
     *
     * This operation would returns a pointer to the basic_streambuf
     * or its subclass that is kept in this class.
     *
     * @return pointer to the basic_streambuf (coil::LogStreambuf)
     *
     * @endif
     */
    virtual StreambufType* getStreamBuffer();

  protected:
    FluentBitStream m_fbstream;
  };
}; // namespace RTC

extern "C"
{
  void DLL_EXPORT FluentBitInit();
};

#endif // RTC_LOGGER_FLUENTBIT_H
