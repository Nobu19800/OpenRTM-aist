// -*- C++ -*-
/*!
 * @file EventInPort.h
 * @brief EventInPort template class
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

#ifndef RTC_EVENTINPORT_H
#define RTC_EVENTINPORT_H

#include <string>
#include <vector>
#include <iostream>

#include <coil/TimeValue.h>
#include <coil/Time.h>
#include <coil/OS.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>

#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/InPortBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortCallback.h>
#include <rtm/InPortConnector.h>
#include <rtm/Timestamp.h>
#include <rtm/StaticFSM.h>

namespace RTC
{
  template <class FSM, class TOP, class R>
  class EventBinder0
    : public ConnectorDataListener
  {
    USE_CONNLISTENER_STATUS;
  public:
    EventBinder0(FSM& fsm,
                 const char* event_name,
                 R (TOP::*handler)())
      : m_fsm(fsm), m_eventName(event_name), m_handler(handler) {}

    virtual ~EventBinder0() {}

    virtual ReturnCode operator()(ConnectorInfo& info,
                                  cdrMemoryStream& data)
    {
      if (info.properties["fsm_event_name"] == m_eventName ||
          info.name == m_eventName)
        {
          m_fsm.dispatch(Macho::Event(m_handler));
          std::cout << "Event dispatched: " << m_eventName << std::endl;
          return NO_CHANGE;
        }
      return NO_CHANGE;
    }

    FSM& m_fsm;
    std::string m_eventName;
    R (TOP::*m_handler)();
  };

  template <class FSM, class TOP, class R, class P0>
  class EventBinder1
    : public ConnectorDataListenerT<P0>
  {
    USE_CONNLISTENER_STATUS;
  public:
    EventBinder1(FSM& fsm,
                 const char* event_name,
                 R (TOP::*handler)(P0))
      : m_fsm(fsm), m_eventName(event_name), m_handler(handler) {}

    virtual ~EventBinder1() {}

    virtual ReturnCode operator()(ConnectorInfo& info, P0& data)
    {
      if (info.properties["fsm_event_name"] == m_eventName ||
          info.name == m_eventName)
        {
          m_fsm.dispatch(Macho::Event(m_handler, data));
          std::cout << "Event dispatched: " << m_eventName << std::endl;
          return NO_CHANGE;
        }
      return NO_CHANGE;
    }

    FSM& m_fsm;
    std::string m_eventName;
    R (TOP::*m_handler)(P0);
  };


  /*!
   * @if jp
   *
   * @class EventInPort
   *
   * @brief EventInPort �ƥ�ץ졼�ȥ��饹
   * 
   * EventInPort �μ����Ǥ��� EventInPort<T> �Υƥ�ץ졼�ȥ��饹��
   * <T> ��BasicDataType.idl �ˤ��������Ƥ��뷿�ǡ����ФȤ���
   * Time ���� tm , ����� T���� data ����Ĺ�¤�ΤǤʤ��ƤϤʤ�ʤ���
   * EventInPort �������˥�󥰥Хåե�����������������������줿�ǡ�����缡
   * ���Υ�󥰥Хåե��˳�Ǽ���롣��󥰥Хåե��Υ������ϥǥե���Ȥ�64��
   * �ʤäƤ��뤬�����󥹥ȥ饯�������ˤ�ꥵ��������ꤹ�뤳�Ȥ��Ǥ��롣
   * �ǡ����ϥե饰�ˤ�ä�̤�ɡ����ɾ��֤��������졢isNew(), write(), read(),
   * isFull(), isEmpty() ���Υ᥽�åɤˤ��ϥ�ɥ�󥰤��뤳�Ȥ��Ǥ��롣
   *   
   * OnRead�ϥ�����Хå� (�ɤ߽Ф��˵������륤�٥�Ȥˤ�ꥳ���뤵���)
   *
   * - void OnRead::operator(): 
   *     EventInPort::read() ��ƤӽФ��ɤ߽Ф���Ԥ��ݤ˥����뤵��롣
   *
   * - DataType OnReadConvert::operator(DataType): 
   *     EventInPort::read() ��ƤӽФ����ǡ�����Хåե������ɤߤ����ݤ˸ƤФ�
   *     �ǡ������Ѵ���Ԥ��������ˤϥХåե������ɤ߽Ф��줿�ͤ�Ϳ����졢
   *     �Ѵ���Υǡ���������ͤȤ����֤��������ͤ�read()���֤��ͤȤʤ롣
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class EventInPort
   *
   * @brief EventInPort template class
   *
   * This is a template class that implements EventInPort.  <T> is the type
   * defined in BasicDataType.idl and must be the structure which has
   * both Time type tm and type-T data as a member. EventInPort has a ring
   * buffer internally, and stores the received data externally in
   * this buffer one by one. The size of ring buffer can be specified
   * according to the argument of constructor, though the default size
   * is 64. Unread data and data which is already read are managed
   * with the flag, and the data can be handled by the isNew(),
   * write(), read(), isFull() and isEmpty() method etc.
   *
   * @since 0.2.0
   *
   * @endif
   */
  template <class FsmType>
  class EventInPort
    : public InPortBase
  {
  public:
    DATAPORTSTATUS_ENUM
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     * �ѥ�᡼���Ȥ���Ϳ������ T �����ѿ��˥Х���ɤ���롣
     *
     * @param name EventInPort ̾��EventInPortBase:name() �ˤ�껲�Ȥ���롣
     * @param value ���� EventInPort �˥Х���ɤ���� T �����ѿ�
     * @param bufsize EventInPort �����Υ�󥰥Хåե��ΥХåե�Ĺ(�ǥե������:64)
     * @param read_block �ɹ��֥�å��ե饰��
     *        �ǡ����ɹ�����̤�ɥǡ������ʤ���硢���Υǡ��������ޤǥ֥�å�����
     *        ���ɤ���������(�ǥե������:false)
     * @param write_block ����֥�å��ե饰��
     *        �ǡ���������˥Хåե����ե�Ǥ��ä���硢�Хåե��˶������Ǥ���
     *        �ޤǥ֥�å����뤫�ɤ���������(�ǥե������:false)
     * @param read_timeout �ɹ��֥�å�����ꤷ�Ƥ��ʤ����Ρ��ǡ����ɼ西����
     *        �����Ȼ���(�ߥ���)(�ǥե������:0)
     * @param write_timeout ����֥�å�����ꤷ�Ƥ��ʤ����Ρ��ǡ������������
     *        �����Ȼ���(�ߥ���)(�ǥե������:0)
     *
     * @else
     *
     * @brief A constructor.
     *
     * constructor.
     * This is bound to type-T variable given as a parameter.
     *
     * @param name A name of the EventInPort. This name is referred by
     *             EventInPortBase::name().
     * @param value type-T variable that is bound to this EventInPort.
     * @param bufsize Buffer length of internal ring buffer of EventInPort
     *                (The default value:64)
     * @param read_block Flag of reading block.
     *                   When there are not unread data at reading data,
     *                   set whether to block data until receiving the next 
     *                   data. (The default value:false)
     * @param write_block Flag of writing block.
     *                    If the buffer was full at writing data, set whether 
     *                    to block data until the buffer has space. 
     *                    (The default value:false)
     * @param read_timeout Data reading timeout time (millisecond) 
     *                     when not specifying read blocking.
     *                     (The default value:0)
     * @param write_timeout Data writing timeout time (millisecond)
     *                      when not specifying writing block.
     *                      (The default value:0)
     *
     * @endif
     */
    EventInPort(const char* name, FsmType& fsm,
                int bufsize=64,
                bool read_block = false, bool write_block = false,
                int read_timeout = 0, int write_timeout = 0)
      : InPortBase(name, "any"),
        m_name(name), m_fsm(fsm)
    {
    }

    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~EventInPort(void){};

    /*!
     * @if jp
     *
     * @brief �ݡ���̾�Τ�������롣
     *
     * �ݡ���̾�Τ�������롣
     *
     * @return �ݡ���̾��
     *
     * @else
     *
     * @brief Get port name
     *
     * Get port name.
     *
     * @return The port name
     *
     * @endif
     */
    virtual const char* name()
    {
      return m_name.c_str();
    }

    template <class TOP, class R, class P0>
    void bindEvent(const char* name,
                   R (TOP::*handler)(P0))
    {
      this->addConnectorDataListener
        (ON_RECEIVED,
         new EventBinder1<FsmType, TOP, R, P0>(m_fsm, name, handler));
    }
    template <typename TOP, class R>
    void bindEvent(const char* name,
                   R (TOP::*handler)())
    {
      this->addConnectorDataListener
        (ON_RECEIVED,
         new EventBinder0<FsmType, TOP, R>(m_fsm, name, handler));
    }
    virtual bool read() { return true; }
  private:
    /*!
     * @if jp
     * @brief �ݡ���̾
     * @else
     * @berif Port's name
     * @endif
     */
    std::string m_name;
    FsmType& m_fsm;
  };
}; // End of namesepace RTM

#endif // RTC_EVENTINPORT_H
