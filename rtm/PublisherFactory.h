// -*- C++ -*-
/*!
 * @file  PublisherFactory.h
 * @brief PublisherFactory class
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
 * $Id: PublisherFactory.h,v 1.2.4.2 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2.4.1  2007/06/22 10:55:11  n-ando
 * The bug of OutPort's disconnect operation was fixed.
 *
 * Revision 1.2  2007/01/06 18:00:31  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:45  n-ando
 * The first commitment.
 *
 */

#ifndef PublisherFactory_h
#define PublisherFactory_h

#include <rtm/Properties.h>

namespace RTC
{
  class PublisherBase;
  class InPortConsumer;
  class Properties;
  
  /*!
   * @if jp
   * @class PublisherFactory
   * @brief PublisherFactory ���饹
   *
   * �Ƽ�Publisher���֥������Ȥ��������˴����������ե����ȥꥯ�饹
   * ���ƥ�ݥ��ʼ���
   *   ����Ū�ˤ�Ǥ�դ�Publisher�������Ǥ���褦�ˤ��롣
   *
   * @else
   * @class PublisherFactory
   * @brief PublisherFactory class
   * @endif
   */
  class PublisherFactory
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * �ǥե���ȥ��󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     * @endif
     */
    PublisherFactory(){};
    
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
    virtual ~PublisherFactory(){};
    
    /*!
     * @if jp
     * @brief Publisher������
     *
     * Publisher���֥������Ȥ��������롣
     * ���ꤵ�줿�����˱�����Ŭ�ڤ�Publisher�����Υ��֥������Ȥ���������롣
     * ��������Publisher�μ��̤򡢻��ꤵ�줿Property���֥������Ȥ�
     * dataport.subscription_type���Ф����ꤷ�Ƥ���ɬ�פ����롣
     * �ޤ������̤ˤ�äƤϡ�Publisher�ζ�ư�����椹�����򤵤�����ꤹ��ɬ�פ�
     * ���롣
     * �����ζ���Ū�����Ƥϡ����줾���Publisher�����򻲾ȤΤ��ȡ�
     *
     * @param consumer Publisher�ˤ�äƥǡ������Ф��ư����륳�󥷥塼��
     * @param property �������٤�Publisher�����ꤹ�뤿��ξ���䡢Publisher��
     *                 ��ư�����椹�뤿��ξ������ꤵ��Ƥ���Property���֥���
     *                 ����
     *
     * @return ��������Publisher���֥������ȡ������˼��Ԥ�������Null���֤���
     *
     * @else
     * @brief Create Publisher
     * @endif
     */
    PublisherBase* create(InPortConsumer* consumer, Properties& property);
    
    /*!
     * @if jp
     * @brief Publisher���˴�
     *
     * ���ꤵ�줿Publisher���֥������Ȥ��˴����롣
     *
     * @param publisher �˴��о�Publisher���֥�������
     *
     * @else
     * @brief Destroy Publisher
     * @endif
     */
    void destroy(PublisherBase *publisher);
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // PublisherFactory_h
