// -*- C++ -*-
/*!
 * @file  InPortDirectProvider.h
 * @brief InPortDirectProvider class
 * @date  $Date: 2008-01-14 07:49:59 $
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
 * $Id: InPortDirectProvider.h 1244 2009-03-13 07:25:42Z n-ando $
 *
 */

#ifndef RTC_INPORTDIRECTPROVIDER_H
#define RTC_INPORTDIRECTPROVIDER_H

#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/Manager.h>
#include <rtm/ConnectorListener.h>
#include <rtm/ConnectorBase.h>

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class InPortDirectProvider
   * @brief InPortDirectProvider ���饹
   *
   * InPortProvider 
   *
   * �ǡ���ž���� CORBA �� OpenRTM::InPortCdr ���󥿡��ե����������Ѥ�
   * ����push ���ǡ����ե�����¸����� InPort �ץ�Х������饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortDirectProvider
   * @brief InPortDirectProvider class
   *
   * The InPort provider class which uses the OpenRTM::InPortCdr
   * interface in CORBA for data transfer and realizes a push-type
   * dataflow.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortDirectProvider
    : public InPortProvider
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    InPortDirectProvider(void);
    
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
    virtual ~InPortDirectProvider(void);

    /*!
     * @if jp
     * @brief ��������
     *
     * InPortDirectProvider �γƼ������Ԥ���Ϳ����줿
     * Properties����ɬ�פʾ����������ƳƼ������Ԥ������� init() ��
     * ���ϡ�InPortProvider����ľ�太��ӡ���³���ˤ��줾��ƤФ���
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
    virtual void init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief �Хåե��򥻥åȤ���
     *
     * OutPortProvider ���ǡ�������Ф��Хåե��򥻥åȤ��롣
     * ���Ǥ˥��åȤ��줿�Хåե��������硢�����ΥХåե��ؤ�
     * �ݥ��󥿤��Ф��ƾ�񤭤���롣
     * OutPortProvider�ϥХåե��ν�ͭ�����ꤷ�Ƥ��ʤ��Τǡ�
     * �Хåե��κ���ϥ桼������Ǥ�ǹԤ�ʤ���Фʤ�ʤ���
     *
     * @param buffer OutPortProvider���ǡ�������Ф��Хåե��ؤΥݥ���
     *
     * @else
     * @brief Setting outside buffer's pointer
     *
     * A pointer to a buffer from which OutPortProvider retrieve data.
     * If already buffer is set, previous buffer's pointer will be
     * overwritten by the given pointer to a buffer.  Since
     * OutPortProvider does not assume ownership of the buffer
     * pointer, destructor of the buffer should be done by user.
     * 
     * @param buffer A pointer to a data buffer to be used by OutPortProvider
     *
     * @endif
     */
    virtual void setBuffer(BufferBase<cdrMemoryStream>* buffer);

    /*!
     * @if jp
     * @brief �ꥹ�ʤ����ꤹ�롣
     *
     * InPort �ϥǡ������������ˤ�����Ƽ磻�٥�Ȥ��Ф�������Υꥹ��
     * ���֥������Ȥ򥳡��뤹�륳����Хå��������󶡤��롣�ܺ٤�
     * ConnectorListener.h �� ConnectorDataListener, ConnectorListener
     * ���򻲾ȤΤ��ȡ�InPortDirectProvider �Ǥϡ��ʲ��Υ�����Хå�
     * ���󶡤���롣
     * 
     * - ON_BUFFER_WRITE
     * - ON_BUFFER_FULL
     * - ON_BUFFER_WRITE_TIMEOUT
     * - ON_BUFFER_OVERWRITE
     * - ON_RECEIVED
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_TIMEOUT
     * - ON_RECEIVER_ERROR
     *
     * @param info ��³����
     * @param listeners �ꥹ�ʥ��֥�������
     *
     * @else
     * @brief Set the listener. 
     *
     * InPort provides callback functionality that calls specific
     * listener objects according to the events in the data publishing
     * process. For details, see documentation of
     * ConnectorDataListener class and ConnectorListener class in
     * ConnectorListener.h. In this InPortDirectProvider provides
     * the following callbacks.
     * 
     * - ON_BUFFER_WRITE
     * - ON_BUFFER_FULL
     * - ON_BUFFER_WRITE_TIMEOUT
     * - ON_BUFFER_OVERWRITE
     * - ON_RECEIVED
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_TIMEOUT
     * - ON_RECEIVER_ERROR
     *
     * @param info Connector information
     * @param listeners Listener objects
     *
     * @endif
     */
    virtual void setListener(ConnectorInfo& info,
                             ConnectorListeners* listeners);

    /*!
     * @if jp
     * @brief Connector�����ꤹ�롣
     *
     * InPort ����³��Ω���� InPortConnector ���֥������Ȥ�����������
     * ���������֥������ȤΥݥ��󥿤ȶ��ˤ��δؿ���ƤӽФ�����ͭ����
     * InPort ���ݻ�����Τ� InPortProvider �� InPortConnector ���
     * �����ƤϤ����ʤ���
     *
     * @param connector InPortConnector
     *
     * @else
     * @brief set Connector
     *
     * InPort creates InPortConnector object when it establishes
     * connection between InPort and InPort, and it calls this
     * function with a pointer to the connector object. Since the
     * InPort has the ownership of this connector, InPortProvider
     * should not delete it.
     *
     * @param connector InPortConnector
     *
     * @endif
     */
    virtual void setConnector(InPortConnector* connector);

  private:

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE �Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_WRITE event to listeners
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
     * @brief ON_BUFFER_FULL �Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_FULL event to listeners
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
     * @brief ON_BUFFER_WRITE_TIMEOUT �Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_WRITE_TIMEOUT event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWriteTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE_TIMEOUT].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE_OVERWRITE �Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_WRITE_OVERWRITE event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWriteOverwrite(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_OVERWRITE].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVED �Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVED event to listeners
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
     * @brief ON_RECEIVER_FULL �Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVER_FULL event to listeners
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
     * @brief ON_RECEIVER_TIMEOUT �Υꥹ�ʤ����Τ��롣 
     * @else
     * @brief Notify an ON_RECEIVER_TIMEOUT event to listeners
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
     * @else
     * @Brief Notify an ON_RECEIVER_ERROR event to listeners
     * @endif
     */
    inline void onReceiverError(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_ERROR].notify(m_profile, data);
    }

  private:
    CdrBufferBase* m_buffer;
    ConnectorListeners* m_listeners;
    ConnectorInfo m_profile;
    InPortConnector* m_connector;

  };  // class InPortCorCdrbaProvider
};    // namespace RTC

extern "C"
{
  /*!
   * @if jp
   * @brief �⥸�塼�������ؿ�
   *
   * InPortDirectConsumer �Υե����ȥ����Ͽ���������ؿ���
   *
   * @else
   * @brief Module initialization
   *
   * This initialization function registers InPortDirectConsumer's factory.
   *
   * @endif
   */
  void InPortDirectProviderInit(void);
};

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_INPORTDIRECTPROVIDER_H

