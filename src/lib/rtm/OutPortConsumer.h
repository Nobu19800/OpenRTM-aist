// -*- C++ -*-
/*!
 * @file  OutPortConsumer.h
 * @brief OutPortConsumer class
 * @date  $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
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

#ifndef RTC_OUTPORTCONSUMER_H
#define RTC_OUTPORTCONSUMER_H

#include <coil/Factory.h>
#include <rtm/DataPortStatus.h>
#include <rtm/CdrBufferBase.h>

namespace SDOPackage
{
  class NVList;
};

namespace coil
{
  class Properties;
};

namespace RTC
{
  class ConnectorListeners;
  class ConnectorInfo;

  /*!
   * @if jp
   *
   * @class OutPortConsumer
   *
   * @brief OutPortConsumer ��ݥ��饹
   *
   * ���ϥݡ��ȥ��󥷥塼�ޤΤ������ݥ��󥿡��ե��������饹
   * �ƶ�ݥ��饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
   * - pull(): �ǡ�������
   * - subscribeInterface(): �ǡ����������Τؤ���Ͽ
   * - unsubscribeInterface(): �ǡ����������Τ���Ͽ���
   *
   * @since 0.4.0
   *
   * @else
   * @class OutPortConsumer
   *
   * @brief OutPortConsumer abstract class
   *
   * This is the abstract interface class for the output port Consumer.
   * Concrete classes must implement the following pure virtual functions.
   * - pull(): Receive data
   * - subscribeInterface(): Subscribe to the data receive notification
   * - unsubscribeInterface(): Unsubscribe the data receive notification
   *
   * @since 0.4.0
   *
   * @endif
   */
  class OutPortConsumer
    : public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~OutPortConsumer(void){};

    /*!
     * @if jp
     * @brief ��������
     *
     * OutPortConsumer�γƼ������Ԥ����������饹�Ǥϡ�Ϳ����줿
     * Properties����ɬ�פʾ����������ƳƼ������Ԥ������� init() ��
     * ���ϡ�OutPortProvider����ľ�太��ӡ���³���ˤ��줾��ƤФ���
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
    virtual void init(coil::Properties& prop) = 0;

    /*!
     * @if jp
     * @brief �Хåե��򥻥åȤ���
     *
     * OutPortConsumer���ǡ�������Ф��Хåե��򥻥åȤ��롣
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
    virtual void setBuffer(CdrBufferBase* buffer) = 0;
    virtual void setListener(ConnectorInfo& info,
                             ConnectorListeners* listeners) = 0;

    /*!
     * @if jp
     *
     * @brief �ǡ������������
     *
     * �ǡ���������¹Ԥ��뤿��ν�貾�۴ؿ���
     * ��ݥ��饹�Ǥϡ����줾�����ˡ�ǥ�⡼�Ȥ�OutPort����ǡ�����
     * ����������å���������롣
     * �����˴ؤ�����֤˱����ưʲ�������ͤ��֤���
     *
     * @param data �����ǡ���
     * @return PORT_OK         ���ｪλ
     *         BUFFER_TIMEOUT  �����ॢ���Ȥ���
     *         RECV_EMPTY      ������ΥХåե������Ǥ��롣
     *         CONNECTION_LOST ��³�����Ǥ��줿
     *         PORT_ERROR      ���顼
     *         UNKNOWN_ERROR   ���褢�ꤨ�ʤ����顼
     *
     * @else
     *
     * @brief Receive data
     *
     * Pure virtual function to receive data.
     *
     * @endif
     */
    virtual ReturnCode get(cdrMemoryStream& data) = 0;

    /*!
     * @if jp
     *
     * @brief �ǡ����������Τؤ���Ͽ
     *
     * ���ꤵ�줿�ץ�ѥƥ�����˴�Ť��ơ��ǡ����������Τ���Ͽ���뤿���
     * ��貾�۴ؿ���
     *
     * @param properties ��Ͽ�ѥץ�ѥƥ�
     *
     * @return ��Ͽ�������(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     *
     * @brief Subscribe the data receive notification
     *
     * Pure virtual function to subscribe the data receive notification
     * based on specified property information.
     *
     * @param properties Properties for subscription
     *
     * @return Subscription result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool subscribeInterface(const SDOPackage::NVList& properties) = 0;
    
    /*!
     * @if jp
     *
     * @brief �ǡ����������Τ������Ͽ���
     *
     * �ǡ����������Τ������Ͽ�������뤿��ν�貾�۴ؿ���
     *
     * @param properties ��Ͽ����ѥץ�ѥƥ�
     *
     * @return ��Ͽ����������(��Ͽ�������:true����Ͽ�������:false)
     *
     * @else
     *
     * @brief Unsubscribe the data receive notification
     *
     * Pure virtual function to unsubscribe the data receive notification.
     *
     * @param properties Properties for unsubscription
     *
     * @return Unsubscription result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties) = 0;

    /*!
     * @if jp
     * @brief Interface��³��Functor
     * @else
     * @brief Functor to subscribe the interface
     * @endif
     */
    struct subscribe
    {
      subscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortConsumer* consumer)
      {
        consumer->subscribeInterface(m_prop);
      }
      const SDOPackage::NVList& m_prop;
    };
    
    /*!
     * @if jp
     * @brief Interface��³�����Functor
     * @else
     * @brief Functor to unsubscribe the interface
     * @endif
     */
    struct unsubscribe
    {
      unsubscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortConsumer* consumer)
      {
        consumer->unsubscribeInterface(m_prop);
      }
      const SDOPackage::NVList& m_prop;
    };
  };

  typedef ::coil::GlobalFactory<OutPortConsumer> OutPortConsumerFactory;

};     // namespace RTC
#endif // OutPortConsumer_h

