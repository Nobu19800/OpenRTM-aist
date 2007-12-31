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
 * $Id: InPortConsumer.h,v 1.4.4.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2007/01/09 09:56:01  n-ando
 * Include order has changed.
 *
 * Revision 1.3  2007/01/06 17:50:22  n-ando
 * Interface subscription/unsubscription functions (subscribeInterface()
 * and unsubscribeInterface()) are added.
 * The clone() function to clone the instance is added.
 *
 * Revision 1.2  2006/12/02 18:39:06  n-ando
 * InPortCorbaConsumer class moved to InPortCorbaConsumer.h
 *
 * Revision 1.1  2006/11/27 09:44:39  n-ando
 * The first commitment.
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
   * @brief InPortConsumer class
   * @endif
   */
  class InPortConsumer
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
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties) = 0;
    
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // InPortConsumer_h
