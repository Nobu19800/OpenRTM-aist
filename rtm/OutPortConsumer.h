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
 * $Id: OutPortConsumer.h,v 1.3.4.1 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/01/06 17:57:14  n-ando
 * Interface subscription/unsubscription functions (subscribeInterface()
 * and unsubscribeInterface()) are added.
 *
 * Revision 1.2  2006/12/02 18:46:55  n-ando
 * OutPortCorbaConsumer class was moved to OutPortCorbaConsumer.h
 *
 * Revision 1.1  2006/11/27 09:44:41  n-ando
 * The first commitment.
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
   * @brief OutPortConsumer class
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
     * @endif
     */
    virtual ~OutPortConsumer(){};
    
    /*!
     * @if jp
     *
     * @brief �ǡ������������
     *
     * �ǡ���������¹Ԥ��뤿��ν�貾�۴ؿ���
     *
     * @else
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
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties) = 0;
    
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // OutPortConsumer_h

