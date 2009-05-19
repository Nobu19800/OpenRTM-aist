// -*- C++ -*-
/*!
 * @file  PublisherPeriodic.h
 * @brief PublisherPeriodic class
 * @date  $Date: 2007-12-31 03:08:06 $
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

#ifndef PublisherPeriodic_h
#define PublisherPeriodic_h

#include <coil/Task.h>
#include <coil/Mutex.h>
#include <coil/Condition.h>
#include <coil/PeriodicTask.h>

#include <rtm/RTC.h>
#include <rtm/PublisherBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/SystemLogger.h>

namespace coil
{
  class Properties;
};

namespace RTC
{
  class InPortConsumer;
  /*!
   * @if jp
   * @class PublisherPeriodic
   * @brief PublisherPeriodic ���饹
   *
   * ��������ǥ��󥷥塼�ޤ����н�����ƤӽФ� Publisher
   * ���Ū�˥ǡ���������¹Ԥ�����˻��Ѥ��롣
   *
   * @else
   * @class PublisherPeriodic
   * @brief PublisherPeriodic class
   *
   * Publisher that invokes the consumer's sending process periodically.
   * This is used when the data sending is regularly executed.
   *
   * @endif
   */
  class PublisherPeriodic
    : public PublisherBase
  {
  public: 
    typedef coil::Mutex Mutex;
    typedef coil::Condition<Mutex> Condition;
    typedef coil::Guard<coil::Mutex> Guard;
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     * ���н����θƤӽФ��ֳ֤�Property���֥������Ȥ�dataport.push_rate����
     * �����ꤷ�Ƥ���ɬ�פ����롣���дֳ֤ϡ�Hzñ�̤���ư����ʸ����ǻ��ꡣ
     * ���Ȥ��С�1000.0Hz�ξ��ϡ���1000.0�פ����ꡣ
     * �嵭�ץ�ѥƥ���̤����ξ��ϡ���1000Hz�פ����ꡣ
     *
     * @param consumer �ǡ������Ф��Ԥĥ��󥷥塼��
     * @param property ��Publisher�ζ�ư�����������ꤷ��Property���֥�������
     *
     * @else
     * @brief Constructor
     *
     * Constructor.
     * The intervals of invoking send processing needs to be set in
     * dataport.push_rate of Property object. The interval is specified by
     * floating point string in Hz.
     * For example, "1000.0" is set for 1000.0Hz.
     * If the above property is unset, "1000Hz" will be set.
     *
     * @param consumer Consumer which waits for data sending
     * @param property Property objects that are set the control information
     *                 of this Publisher
     *
     * @endif
     */
    PublisherPeriodic();
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~PublisherPeriodic(void);
    
    /*!
     * @if jp
     * @brief �����
     * @else
     * @brief initialization
     * @endif
     */
    virtual ReturnCode init(coil::Properties& prop);
    virtual ReturnCode setConsumer(InPortConsumer* consumer);
    virtual ReturnCode setBuffer(CdrBufferBase* buffer);
    virtual ReturnCode write(const cdrMemoryStream& data,
                             unsigned long sec,
                             unsigned long usec);
    virtual bool isActive();
    virtual ReturnCode activate();
    virtual ReturnCode deactivate();
    
    /*!
     * @if jp
     * @brief ����åɼ¹Դؿ�
     *
     * ACE_Task::svc() �Υ����С��饤��
     *
     * @else
     * @brief Thread execution function
     *
     * ACE_Task::svc() override function.
     *
     * @endif
     */
    virtual int svc(void);
    
  protected:
    enum Policy
      {
        ALL,
        FIFO,
        SKIP,
        NEW
      };

    /*!
     * @brief push "all" policy
     */
    ReturnCode pushAll();
    /*!
     * @brief push "fifo" policy
     */
    ReturnCode pushFifo();
    /*!
     * @brief push "skip" policy
     */
    ReturnCode pushSkip();
    /*!
     * @brief push "new" policy
     */
    ReturnCode pushNew();

    ReturnCode convertReturn(BufferStatus::Enum status);
    
  private:
    Logger rtclog;
    InPortConsumer* m_consumer;
    CdrBufferBase* m_buffer;
    coil::PeriodicTaskBase* m_task;
    ReturnCode m_retcode;
    Mutex m_retmutex;
    Policy m_pushPolicy;
    int m_skipn;
    bool m_active;
    bool m_readback;
  };
};     // namespace RTC

extern "C"
{
  void DLL_EXPORT PublisherPeriodicInit();
};

#endif // PublisherPeriodic_h

