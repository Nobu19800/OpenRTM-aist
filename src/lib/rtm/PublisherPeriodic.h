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

#ifndef RTC_PUBLISHERPERIODIC_H
#define RTC_PUBLISHERPERIODIC_H

#include <coil/Task.h>
#include <coil/Mutex.h>
#include <coil/Condition.h>
#include <coil/PeriodicTask.h>

#include <rtm/RTC.h>
#include <rtm/PublisherBase.h>
#include <rtm/CdrBufferBase.h>
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
     * ���н����θƤӽФ��ֳ֤�Property���֥������Ȥ�
     * dataport.publisher.push_rate���Ф����ꤷ�Ƥ���ɬ�פ����롣����
     * �ֳ֤ϡ�Hzñ�̤���ư����ʸ����ǻ��ꡣ���Ȥ��С�1000.0Hz�ξ��ϡ�
     * ��1000.0�פ����ꡣ�嵭�ץ�ѥƥ���̤����ξ��ϡ���1000Hz�פ���
     * �ꡣ
     *
     * @param consumer �ǡ������Ф��Ԥĥ��󥷥塼��
     * @param property ��Publisher�ζ�ư�����������ꤷ��Property���֥�������
     *
     * @else
     * @brief Constructor
     *
     * The intervals of invoking send processing needs to be set in
     * dataport.publisher.push_rate of Property object. The interval
     * is specified by floating point string in Hz.
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
    /*!
     * @if jp
     * @brief InPort���󥷥塼�ޤΥ��å�
     *
     * @else
     * @brief Store InPort consumer
     * @endif
     */
    virtual ReturnCode setConsumer(InPortConsumer* consumer);
    /*!
     * @if jp
     * @brief �Хåե��Υ��å�
     * @param buffer CDR�Хåե�
     * @return PORT_OK      ���ｪλ
     *         INVALID_ARGS �����ʰ���
     * @else
     * @brief Setting buffer pointer
     * @param buffer CDR buffer
     * @return PORT_OK      ���ｪλ
     *         INVALID_ARGS �����ʰ���
     * @endif
     */
    virtual ReturnCode setBuffer(CdrBufferBase* buffer);
    /*!
     * @if jp
     * @brief �ꥹ�ʤ����ꤹ�롣
     * @param info ConnectorInfo
     * @param listeners ConnectorListeners 
     * @return PORT_OK      ���ｪλ
     *         INVALID_ARGS �����ʰ���
     * @else
     * @brief Set the listener. 
     * @param info ConnectorInfo
     * @param listeners ConnectorListeners 
     * @return PORT_OK      Normal return
     *         INVALID_ARGS Invalid arguments
     * @endif
     */
    virtual ReturnCode setListener(ConnectorInfo& info,
                                   ConnectorListeners* listeners);
    /*!
     * @if jp
     * @brief �ǡ�����񤭹���
     * @param data �񤭹���ǡ��� 
     * @param sec �����ॢ���Ȼ���
     * @param nsec �����ॢ���Ȼ���
     * @return �꥿���󥳡���
     * @else
     * @brief Write data 
     * @param data Data
     * @param sec Timeout period
     * @param nsec Timeout period
     * @return Return code
     * @endif
     */
    virtual ReturnCode write(const cdrMemoryStream& data,
                             unsigned long sec,
                             unsigned long usec);
    /*!
     * @if jp
     *
     * @brief �����ƥ��ֲ���ǧ
     * 
     * �����ƥ��ֲ�����Ƥ��뤫��ǧ���롣
     *
     * @return ���ֳ�ǧ���(�����ƥ��־���:true���󥢥��ƥ��־���:false)
     *
     * @else
     *
     * @brief Confirm to activate
     * 
     * Confirm that has been activated.
     *
     * @return Result of state confirmation
     *         (Active state:true, Inactive state:false)
     *
     * @endif
     */
    virtual bool isActive();
    /*!
     * @if jp
     * @brief �����ƥ��ֲ�
     * @return �꥿���󥳡���
     *
     * @else
     *
     * @brief activation
     * @return Return code
     *
     * @endif
     */
    virtual ReturnCode activate();
    /*!
     * @if jp
     * @brief �󥢥��ƥ��ֲ�
     * @return �꥿���󥳡���
     *
     * @else
     *
     * @brief deactivation
     * @return Return code
     *
     * @endif
     */
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
     * @if jp
     * @brief PushPolicy ������
     * @else
     * @brief Setting PushPolicy
     * @endif
     */
    void setPushPolicy(const coil::Properties& prop);

    /*!
     * @if jp
     * @brief Task ������
     * @else
     * @brief Setting Task
     * @endif
     */
    bool createTask(const coil::Properties& prop);

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
     */
    ReturnCode convertReturn(BufferStatus::Enum status,
                             const cdrMemoryStream& data);


    /*!
     * @if jp
     * @brief DataPortStatus�˽��äƥꥹ�ʤ����Τ���ؿ���ƤӽФ���
     * @param status DataPortStatus
     * @param data cdrMemoryStream
     * @return �꥿���󥳡���
     *
     * @else
     * @brief This method calls the function notified the listener 
     *        according to DataPortStatus.  
     * @param status DataPortStatus
     * @param data cdrMemoryStream
     * @return Return code
     *
     * @endif
     */
    ReturnCode invokeListener(DataPortStatus::Enum status,
                              const cdrMemoryStream& data);

    /*!
     * @brief Connector data listener functions
     */
    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_BUFFER_WRITE. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWrite(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_FULL�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_BUFFER_FULL. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_FULL].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE_TIMEOUT�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_BUFFER_WRITE_TIMEOUT. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWriteTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE_TIMEOUT].notify(m_profile, data);
    }

//    inline void onBufferWriteOverwrite(const cdrMemoryStream& data)
//    {
//      m_listeners->
//        connectorData_[ON_BUFFER_OVERWRITE].notify(m_profile, data);
//    }

    /*!
     * @if jp
     * @brief ON_BUFFER_READ�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_BUFFER_READ.
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferRead(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_READ].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_SEND�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_SEND. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onSend(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_SEND].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVED�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_RECEIVED. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceived(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVED].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_FULL�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_RECEIVER_FULL. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_FULL].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_TIMEOUT�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_RECEIVER_TIMEOUT. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_TIMEOUT].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_ERROR�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_RECEIVER_ERROR.
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverError(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_ERROR].notify(m_profile, data);
    }

    /*!
     * @brief Connector listener functions
     */
    /*!
     * @if jp
     * @brief ON_BUFFER_EMPTY�Υꥹ�ʤ����Τ��롣 
     * @else
     * @brief This method is notified to listeners of ON_BUFFER_EMPTY.
     * @endif
     */
    inline void onBufferEmpty()
    {
      m_listeners->
        connector_[ON_BUFFER_EMPTY].notify(m_profile);
    }

//    inline void onBufferReadTimeout()
//    {
//      m_listeners->
//        connector_[ON_BUFFER_READ_TIMEOUT].notify(m_profile);
//    }

    /*!
     * @if jp
     * @brief ON_SENDER_EMPTY�Υꥹ�ʤ����Τ��롣 
     * @else
     * @brief This method is notified to listeners of ON_SENDER_EMPTY.
     * @endif
     */
    inline void onSenderEmpty()
    {
      m_listeners->
        connector_[ON_SENDER_EMPTY].notify(m_profile);
    }

//    inline void onSenderTimeout()
//    {
//      m_listeners->
//        connector_[ON_SENDER_TIMEOUT].notify(m_profile);
//    }

    /*!
     * @if jp
     * @brief ON_SENDER_ERROR�Υꥹ�ʤ����Τ��롣 
     * @else
     * @brief This method is notified to listeners of ON_SENDER_ERROR.
     * @endif
     */
    inline void onSenderError()
    {
      m_listeners->
        connector_[ON_SENDER_ERROR].notify(m_profile);
    }


  private:
    bool bufferIsEmpty()
    {
      if (m_buffer->empty() && !m_readback)
        {
          RTC_DEBUG(("buffer empty"));
          onBufferEmpty();
          onSenderEmpty();
          return true;
        }
      return false;
    }

    Logger rtclog;
    InPortConsumer* m_consumer;
    CdrBufferBase* m_buffer;
    ConnectorInfo m_profile;
    coil::PeriodicTaskBase* m_task;
    ConnectorListeners* m_listeners;
    ReturnCode m_retcode;
    Mutex m_retmutex;
    Policy m_pushPolicy;
    int m_skipn;
    bool m_active;
    bool m_readback;
    int m_leftskip;
  };
};     // namespace RTC

extern "C"
{
  void DLL_EXPORT PublisherPeriodicInit();
};

#endif // RTC_PUBLISHERPERIODIC_H

