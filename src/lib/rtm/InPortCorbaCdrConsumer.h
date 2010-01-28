// -*- C++ -*-
/*!
 * @file  InPortCorbaCdrConsumer.h
 * @brief InPortCorbaCdrConsumer class
 * @date  $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPortCorbaCdrConsumer.h 1255 2009-04-07 01:09:47Z kurihara $
 *
 */

#ifndef RTC_INPORTCORBACDRCONSUMER_H
#define RTC_INPORTCORBACDRCONSUMER_H


//#include <rtm/BufferBase.h>

#include <rtm/idl/DataPortSkel.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/InPortConsumer.h>
#include <rtm/Manager.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class InPortCorbaCdrConsumer
   *
   * @brief InPortCorbaCdrConsumer ���饹
   *
   * �̿����ʤ� CORBA �����Ѥ������ϥݡ��ȥ��󥷥塼�ޤμ������饹��
   *
   * @param DataType �ܥݡ��Ȥˤư����ǡ�����
   *
   * @since 1.0
   *
   * @else
   * @class InPortCorbaCdrConsumer
   *
   * @brief InPortCorbaCdrConsumer class
   *
   * This is an implementation class of the input port Consumer 
   * that uses CORBA for means of communication.
   *
   * @param DataType Data type for this port
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortCorbaCdrConsumer
    : public InPortConsumer,
      public CorbaConsumer< ::OpenRTM::InPortCdr >
  {
  public:
    DATAPORTSTATUS_ENUM
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param buffer �������󥷥塼�ޤ˳�����Ƥ�Хåե����֥�������
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param buffer The buffer object that is attached to this Consumer
     *
     * @endif
     */
    InPortCorbaCdrConsumer(void);
    
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
    virtual ~InPortCorbaCdrConsumer(void);

    /*!
     * @if jp
     * @brief ��������
     *
     * InPortConsumer�γƼ������Ԥ�
     *
     * @else
     * @brief Initializing configuration
     *
     * This operation would be called to configure this consumer
     * in initialization.
     *
     * @endif
     */
    virtual void init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief ��³��ؤΥǡ�������
     *
     * ��³��Υݡ��Ȥإǡ������������뤿��ν�貾�۴ؿ���
     * 
     * ���δؿ��ϡ��ʲ��Υ꥿���󥳡��ɤ��֤���
     *
     * - PORT_OK:       ���ｪλ��
     * - PORT_ERROR:    �ǡ��������β����ǲ��餫�Υ��顼��ȯ��������
     * - SEND_FULL:     �ǡ��������������������¦�Хåե����ե���ä���
     * - SEND_TIMEOUT:  �ǡ��������������������¦�Хåե��������ॢ���Ȥ�����
     * - UNKNOWN_ERROR: ���������Υ��顼
     *
     * @param data ��������ǡ���
     * @return �꥿���󥳡���
     *
     * @else
     * @brief Send data to the destination port
     *
     * Pure virtual function to send data to the destination port.
     *
     * This function might the following return codes
     *
     * - PORT_OK:       Normal return
     * - PORT_ERROR:    Error occurred in data transfer process
     * - SEND_FULL:     Buffer full although OutPort tried to send data
     * - SEND_TIMEOUT:  Timeout although OutPort tried to send data
     * - UNKNOWN_ERROR: Unknown error
     *
     * @endif
     */
    virtual ReturnCode put(const cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief InterfaceProfile������������
     *
     * InterfaceProfile�����������롣
     * �����ǻ��ꤹ��ץ�ѥƥ�������� NameValue ���֥������Ȥ�
     * dataport.interface_type �ͤ�Ĵ�١������ݡ��Ȥ����ꤵ��Ƥ���
     * ���󥿡��ե����������פȰ��פ�����Τ߾����������롣
     *
     * @param properties InterfaceProfile�����������ץ�ѥƥ�
     *
     * @else
     * @brief Publish InterfaceProfile information
     *
     * Publish interfaceProfile information.
     * Check the dataport.interface_type value of the NameValue object 
     * specified by an argument in property information and get information
     * only when the interface type of the specified port is matched.
     *
     * @param properties Properties to get InterfaceProfile information
     *
     * @endif
     */
    virtual void publishInterfaceProfile(SDOPackage::NVList& properties);

    /*!
     * @if jp
     * @brief �ǡ����������Τؤ���Ͽ
     *
     * ���ꤵ�줿�ץ�ѥƥ��˴�Ť��ơ��ǡ����������Τμ���������Ͽ���롣
     *
     * @param properties ��Ͽ����
     *
     * @return ��Ͽ�������(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     * @brief Subscribe to the data sending notification
     *
     * Subscribe to the data sending notification based on specified 
     * property information.
     *
     * @param properties Information for subscription
     *
     * @return Subscription result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool subscribeInterface(const SDOPackage::NVList& properties);
    
    /*!
     * @if jp
     * @brief �ǡ����������Τ������Ͽ���
     *
     * �ǡ����������Τμ�����꤫����Ͽ�������롣
     *
     * @param properties ��Ͽ�������
     *
     * @else
     * @brief Unsubscribe the data send notification
     *
     * Unsubscribe the data send notification.
     *
     * @param properties Information for unsubscription
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties);

  private:
    /*!
     * @if jp
     * @brief IORʸ���󤫤饪�֥������Ȼ��Ȥ��������
     *
     * @return true: �������, false: ��������
     *
     * @else
     * @brief Getting object reference fromn IOR string
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool subscribeFromIor(const SDOPackage::NVList& properties);

    /*!
     * @if jp
     * @brief Any����ľ�ܥ��֥������Ȼ��Ȥ��������
     *
     * @return true: �������, false: ��������
     *
     * @else
     * @brief Getting object reference fromn Any directry
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool subscribeFromRef(const SDOPackage::NVList& properties);

    /*!
     * @if jp
     * @brief ��³���(IOR��)
     *
     * @return true: �������, false: ��������
     *
     * @else
     * @brief ubsubscribing (IOR version)
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool unsubscribeFromIor(const SDOPackage::NVList& properties);

    /*!
     * @if jp
     * @brief ��³���(Object reference��)
     *
     * @return true: �������, false: ��������
     *
     * @else
     * @brief ubsubscribing (Object reference version)
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool unsubscribeFromRef(const SDOPackage::NVList& properties);
    
  private:
    /*!
     * @if jp
     * @brief �꥿���󥳡����Ѵ�
     * @else
     * @brief Return codes conversion
     * @endif
     */
    InPortConsumer::ReturnCode convertReturnCode(OpenRTM::PortStatus ret);

    mutable Logger rtclog;
    coil::Properties m_properties;
  };
};     // namespace RTC

extern "C"
{
  void InPortCorbaCdrConsumerInit(void);
};

#endif // RTC_INPORTCORBACDRCONSUMER_H

