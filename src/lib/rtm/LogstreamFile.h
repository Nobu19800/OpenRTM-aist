// -*- C++ -*-
/*!
 * @file LogstreamFile.h
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

#ifndef RTC_LOGSTREAMFILE_H
#define RTC_LOGSTREAMFILE_H

#include <string>
#include <fstream>
#include <iostream>
#include <coil/stringutil.h>
#include <rtm/LogstreamBase.h>

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
  class LogstreamFile
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
    LogstreamFile();

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
    virtual ~LogstreamFile(void);

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
    static coil::vstring s_files;
    std::string m_fileName;
    StreambufType* m_stdout;
    std::filebuf* m_fileout;
  };
}; // namespace RTC

extern "C"
{
  void DLL_EXPORT LogstreamFileInit();
};

#endif // RTC_LOGSTREAMFILE_H
