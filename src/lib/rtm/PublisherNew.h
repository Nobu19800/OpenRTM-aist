// -*- C++ -*-
/*!
 * @file  PublisherNew.h
 * @brief PublisherNew class
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

#ifndef PublisherNew_h
#define PublisherNew_h

#include <coil/Task.h>
#include <coil/Mutex.h>
#include <coil/Condition.h>
#include <coil/PeriodicTask.h>

#include <rtm/RTC.h>
#include <rtm/PublisherBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/DataPortStatus.h>
#include <rtm/SystemLogger.h>
#include <rtm/ConnectorBase.h>
#include <rtm/ConnectorListener.h>

namespace coil
{
  class Properties;
};

namespace RTC
{
  class InPortConsumer;
  /*!
   * @if jp
   * @class PublisherNew
   * @brief PublisherNew ���饹
   *
   * �Хåե���˿����ǡ�������Ǽ���줿�����ߥ󥰤ǡ����ο����ǡ������������롣
   * �ǡ������Х����ߥ󥰤��Ԥĥ��󥷥塼�ޤ����Ф���¦�Ȥϰۤʤ륹��åɤ�
   * ư�������˻��ѡ�
   * Publisher�ζ�ư�ϡ��ǡ������ФΥ����ߥ󥰤ˤʤ�ޤǥ֥�å����졢
   * ���Х����ߥ󥰤����Τ������ȡ�¨�¤˥��󥷥塼�ޤ����н�����ƤӽФ���
   *
   * @else
   * @class PublisherNew
   * @brief PublisherNew class
   *
   * Send new data at timing of when it is stored into the buffer.
   * This class is used when operating Consumer that waits for the data send
   * timing in different thread from one of the send side.
   * Publisher's driven is blocked until the data send timing reaches, if the
   * send timing notification is received, the Consumer's send processing will
   * be invoked immediately.
   *
   * @endif
   */

  class PublisherNew
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
     * �� Publisher �ѿ�������åɤ��������롣
     *
     * @param consumer �ǡ������Ф��Ԥĥ��󥷥塼��
     * @param property ��Publisher�ζ�ư�����������ꤷ��Property���֥�������
     *                 (��Publisher�Ǥ�̤����)
     * @else
     * @brief Constructor
     *
     * Constructor
     * Create new thread for this Publisher.
     *
     * @param consumer Consumer that waits for the data sending
     * @param property Property object that is configured this Publisher's
     *                 control information.(Unused in this Publisher)
     * @endif
     */
    PublisherNew();
    
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
    virtual ~PublisherNew(void);

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
    virtual ReturnCode setListener(ConnectorInfo& info,
                                   ConnectorListeners* listeners);
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
     * �Хåե���Υǡ��������������ޤǥ���åɤ��Ե������롣
     *
     * @return �¹Է��
     *
     * @else
     * @brief Thread execution function
     *
     * ACE_Task::svc() override function.
     * Make thread stand by until data in the buffer is updated.
     *
     * @return Execution result
     *
     * @endif
     */
    virtual int svc(void);
    
    /*!
     * @if jp
     * @brief ����������
     *
     * ACE_Task::open() �Υ����С��饤��
     * �� publisher �ѿ�������åɤ��������롣
     *
     * @param args ����å������Ѱ���(��Publisher�Ǥ�̤����)
     *
     * @return �¹Է��
     *
     * @else
     * @brief Task start function
     *
     * ACE_Task::open() override function.
     * Create newly thread for this Publisher.
     *
     * @param args Thread creation arguments (Unused in this Publisher)
     *
     * @return Execution result
     *
     * @endif
     */
    //    virtual int open(void *args);
    
    /*!
     * @if jp
     * @brief ��������λ�ؿ�
     *
     * ACE_Task::release() �Υ����С��饤��
     * ��ư�ե饰��false�����ꤷ���� Publisher �ζ�ư����ߤ��롣
     * ����������ư����åɤ��֥�å�����Ƥ�����ˤϡ�
     * ���磱�󥳥󥷥塼�ޤ����н������ƤӽФ�����礬���롣
     *
     * @else
     * @brief Task terminate function
     *
     * ACE_Task::release() override function.
     * Set 2driven flag to false, and terminate this Publisher's operation.
     * However, if the driven thread is blocked, Consumer's send
     * processing may be invoked maximum once.
     *
     * @endif
     */
    //    virtual void release();
    
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

    /*!
     * @brief return code conversion (BufferStatus -> DataPortStatus)
     *
     *
     */
    ReturnCode convertReturn(BufferStatus::Enum status, const cdrMemoryStream& data);

    ReturnCode invokeListener(DataPortStatus::Enum status,
                              const cdrMemoryStream& data);
    
    /*!
     * @brief Connector data listener functions
     */
    inline void onBufferWrite(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
    }

    inline void onBufferFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_FULL].notify(m_profile, data);
    }

    inline void onBufferWriteTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE_TIMEOUT].notify(m_profile, data);
    }

    inline void onBufferWriteOverwrite(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_OVERWRITE].notify(m_profile, data);
    }

    inline void onBufferRead(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_READ].notify(m_profile, data);
    }

    inline void onSend(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_SEND].notify(m_profile, data);
    }

    inline void onReceived(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVED].notify(m_profile, data);
    }

    inline void onReceiverFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_FULL].notify(m_profile, data);
    }

    inline void onReceiverTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_TIMEOUT].notify(m_profile, data);
    }

    inline void onReceiverError(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_ERROR].notify(m_profile, data);
    }

    /*!
     * @brief Connector listener functions
     */
//    inline void onBufferEmpty()
//    {
//      m_listeners->
//        connector_[ON_BUFFER_EMPTY].notify(m_profile);
//    }

//    inline void onBufferReadTimeout()
//    {
//      m_listeners->
//        connector_[ON_BUFFER_READ_TIMEOUT].notify(m_profile);
//    }

//    inline void onSenderEmpty()
//    {
//      m_listeners->
//        connector_[ON_SENDER_EMPTY].notify(m_profile);
//    }

//    inline void onSenderTimeout()
//    {
//      m_listeners->
//        connector_[ON_SENDER_TIMEOUT].notify(m_profile);
//    }

    inline void onSenderError()
    {
      m_listeners->
        connector_[ON_SENDER_ERROR].notify(m_profile);
    }


  private:
    Logger rtclog;
    InPortConsumer* m_consumer;
    CdrBufferBase* m_buffer;
    ConnectorInfo m_profile;
    ConnectorListeners* m_listeners;
    coil::PeriodicTaskBase* m_task;
    ReturnCode m_retcode;
    Mutex m_retmutex;
    Policy m_pushPolicy;
    int m_skipn;
    bool m_active;
    int m_leftskip;
  };
};     // namespace RTC

extern "C"
{
  void DLL_EXPORT PublisherNewInit();
};

#endif // PublisherNew_h

