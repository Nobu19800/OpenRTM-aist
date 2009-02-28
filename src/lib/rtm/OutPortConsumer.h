// -*- C++ -*-
/*!
 * @file  OutPortConsumer.h
 * @brief OutPortConsumer class
 * @date  $Date: 2007-12-31 03:08:05 $
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

#ifndef OutPortConsumer_h
#define OutPortConsumer_h

#include <rtm/CorbaConsumer.h>
#include <rtm/NVUtil.h>

namespace RTC
{
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
  {
  public:
    /***
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
    //    OutPortConsumer(){};
    
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
     *
     * @brief �ǡ������������
     *
     * �ǡ���������¹Ԥ��뤿��ν�貾�۴ؿ���
     *
     * @else
     *
     * @brief Receive data
     *
     * Pure virtual function to receive data.
     *
     * @endif
     */
    virtual void pull() = 0;
    
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
    
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // OutPortConsumer_h

