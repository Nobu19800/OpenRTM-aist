// -*- C++ -*-
/*!
 * @file  PublisherFlush.h
 * @brief PublisherFlush class
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

#ifndef PublisherFlush_h
#define PublisherFlush_h

#include <coil/Condition.h>
#include <rtm/PublisherBase.h>
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
   * @class PublisherFlush
   * @brief PublisherFlush ���饹
   *
   * Flush �� Publisher ���饹
   * �Хåե���˳�Ǽ����Ƥ���̤�����ǡ������������롣
   * �ǡ������Ф��Ԥĥ��󥷥塼�ޤ����Ф���¦��Ʊ������åɤ�ư����롣
   *
   * @else
   * @class PublisherFlush
   * @brief PublisherFlush class
   *
   * This is a Publisher class of Flush type.
   * This class sends unsend data that has been stored in the buffer.
   * This executes Consumer that waits for the data send timing in the same 
   * thread as its send side.
   *
   * @endif
   */
  class PublisherFlush
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
     *
     * @param consumer �ǡ������Ф��Ԥĥ��󥷥塼��
     * @param property ��Publisher�ζ�ư�����������ꤷ��Property���֥�������
     *
     * @else
     * @brief Constructor
     *
     * Consrtuctor.
     *
     * @param consumer Consumer to wait for the data sending
     * @param property Property object that have been set the control
     *                 information of this Publisher
     *
     * @endif
     */
    PublisherFlush();
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     * ����Publisher���˴�����ݤˡ�PublisherFactory�ˤ��ƤӽФ���롣
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     * This is invoked by PublisherFactory when this Publisher is destoroyed.
     *
     * @endif
     */
    virtual ~PublisherFlush(void);

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
    virtual ::RTC::DataPortStatus::Enum
    setListener(ConnectorInfo& profile,
                RTC::ConnectorListeners* listeners);
    virtual ReturnCode write(const cdrMemoryStream& data,
                             unsigned long sec,
                             unsigned long usec);
    virtual bool isActive();
    virtual ReturnCode activate();
    virtual ReturnCode deactivate();

  protected:
    /*!
     * @brief Connector data listener functions
     */
    //    inline void onBufferWrite(const cdrMemoryStream& data)
    //    {
    //      m_listeners->
    //        connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
    //    }

    //    inline void onBufferFull(const cdrMemoryStream& data)
    //    {
    //      m_listeners->
    //        connectorData_[ON_BUFFER_FULL].notify(m_profile, data);
    //    }

    //    inline void onBufferWriteTimeout(const cdrMemoryStream& data)
    //    {
    //      m_listeners->
    //        connectorData_[ON_BUFFER_WRITE_TIMEOUT].notify(m_profile, data);
    //    }

    //    inline void onBufferWriteOverwrite(const cdrMemoryStream& data)
    //    {
    //      m_listeners->
    //        connectorData_[ON_BUFFER_OVERWRITE].notify(m_profile, data);
    //    }

    //    inline void onBufferRead(const cdrMemoryStream& data)
    //    {
    //      m_listeners->
    //        connectorData_[ON_BUFFER_READ].notify(m_profile, data);
    //    }

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

    //    inline void onSenderError()
    //    {
    //      m_listeners->
    //        connector_[ON_SENDER_ERROR].notify(m_profile);
    //    }
    
    
  private:
    Logger rtclog;
    InPortConsumer* m_consumer;
    ConnectorInfo m_profile;
    ConnectorListeners* m_listeners;
    ReturnCode m_retcode;
    Mutex m_retmutex;
    bool m_active;
  };

};     // namespace RTC

extern "C"
{
  void DLL_EXPORT PublisherFlushInit();
};

#endif // PublisherFlush_h

