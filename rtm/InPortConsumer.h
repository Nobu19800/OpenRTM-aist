// -*- C++ -*-
/*!
 * @file  InPortConsumer.h
 * @brief InPortConsumer class
 * @date  $Date: 2007-12-31 03:08:03 $
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

#ifndef InPortConsumer_h
#define InPortConsumer_h

#include <rtm/NVUtil.h>
#include <rtm/CorbaConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class InPortConsumer
   *
   * @brief InPortConsumer ��ݥ��饹
   *
   * ���ϥݡ��ȥ��󥷥塼�ޤΤ������ݥ��󥿡��ե��������饹
   * �ƶ�ݥ��饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
   * - push(): �ǡ�������
   * - clone(): �ݡ��ȤΥ��ԡ�
   * - subscribeInterface(): �ǡ����������Τؤ���Ͽ
   * - unsubscribeInterface(): �ǡ����������Τ���Ͽ���
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortConsumer
   *
   * @brief InPortConsumer abstract class
   *
   * This is the abstract interface class for the input port Consumer.
   * Concrete classes must implement the following pure virtual functions.
   * - push(): Send data
   * - clone(): Copy ports
   * - subscribeInterface(): Subscribe the data send notification
   * - unsubscribeInterface(): Unsubscribe the data send notification
   *
   * @since 0.4.0
   *
   * @endif
   *
   */
  class InPortConsumer
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
    //InPortConsumer();
    
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
    virtual ~InPortConsumer(){};
    
    /*!
     * @if jp
     * @brief ��³��ؤΥǡ�������
     *
     * ��³��Υݡ��Ȥإǡ������������뤿��ν�貾�۴ؿ���
     *
     * @else
     * @brief Send data to the destination port
     *
     * Pure virtual function to send data to the destination port.
     *
     * @endif
     */
    virtual void push() = 0;
    
    /*!
     * @if jp
     * @brief �����ݡ��ȤΥ��ԡ�
     *
     * �����ݡ��ȤΥ��ԡ����������뤿��ν�貾�۴ؿ���
     *
     * @return ʣ�����줿 InPortConsumer ���֥�������
     *
     * @else
     * @brief Clone this port
     *
     * Pure virtual function to generate this clone port.
     *
     * @return The clone InPortConsumer object
     *
     * @endif
     */
    virtual InPortConsumer* clone() const = 0;
    
    /*!
     * @if jp
     * @brief �ǡ����������μ������ؤ���Ͽ
     *
     * ���ꤵ�줿�ץ�ѥƥ������Ƥ˴�Ť��ơ��ǡ����������Τμ���������Ͽ����
     * ����ν�貾�۴ؿ���
     *
     * @param properties ��Ͽ���˻��Ȥ���ץ�ѥƥ�
     *
     * @return ��Ͽ�������
     *
     * @else
     * @brief Subscribe the data send notification
     *
     * Pure virtual function to subscribe the data send notification
     * based on specified property information.
     *
     * @param properties Properties for reference when subscribing
     *
     * @return Subscription result
     *
     * @endif
     */
    virtual bool subscribeInterface(const SDOPackage::NVList& properties) = 0;
    
    /*!
     * @if jp
     * @brief �ǡ����������μ�����꤫�����Ͽ���
     *
     * �ǡ����������Τμ�����꤫����Ͽ������뤿��ν�貾�۴ؿ���
     *
     * @param properties ��Ͽ������˻��Ȥ���ץ�ѥƥ�
     *
     * @else
     * @brief Unsubscribe the data send notification
     *
     * Pure virtual function to unsubscribe the data send notification.
     *
     * @param properties Properties for reference when unsubscribing
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties) = 0;
    
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // InPortConsumer_h
