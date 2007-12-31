// -*- C++ -*-
/*!
 * @file  PublisherPeriodic.h
 * @brief PublisherPeriodic class
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
 * $Id: PublisherPeriodic.h,v 1.3.2.1 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/26 15:32:52  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.2  2007/01/06 18:01:06  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:51  n-ando
 * The first commitment.
 *
 */

#ifndef PublisherPeriodic_h
#define PublisherPeriodic_h

#include <rtm/RTC.h>

#include <ace/Task.h>
#include <ace/Synch.h>
#include <rtm/PublisherBase.h>

namespace RTC
{
  class InPortConsumer;
  class Properties;
  /*!
   * @if jp
   * @class PublisherPeriodic
   * @brief PublisherPeriodic ���饹
   *
   * ��������ǥ��󥷥塼�ޤ����н�����ƤӽФ� Publisher
   * ���Ū�˥ǡ���������¹Ԥ�����˻��Ѥ��롣
   *
   * @else
   * @class PublisherPeriodic
   * @brief PublisherPeriodic class
   * @endif
   */
  class PublisherPeriodic
    : public PublisherBase,
      public ACE_Task<ACE_MT_SYNCH>
  {
    //    class InPortConsumer;
    
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     * ���н����θƤӽФ��ֳ֤�Property���֥������Ȥ�dataport.push_rate����
     * �����ꤷ�Ƥ���ɬ�פ����롣���дֳ֤ϡ�Hzñ�̤���ư����ʸ����ǻ��ꡣ
     * ���Ȥ��С�1000.0Hz�ξ��ϡ���1000.0�פ����ꡣ
     * �嵭�ץ�ѥƥ���̤����ξ��ϡ���1000Hz�פ����ꡣ
     *
     * @param consumer �ǡ������Ф��Ԥĥ��󥷥塼��
     * @param property ��Publisher�ζ�ư�����������ꤷ��Property���֥�������
     *
     * @else
     * @brief Constructor
     * @endif
     */
    PublisherPeriodic(InPortConsumer* consumer,
		      const Properties& property);
    
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
    virtual ~PublisherPeriodic();
    
    /*!
     * @if jp
     * @brief Observer�ؿ�
     *
     * �� Publisher �Ǥϲ���¹Ԥ��ʤ���
     *
     * @else
     * @brief Observer function
     * @endif
     */
    virtual void update();
    
    /*!
     * @if jp
     * @brief ����åɼ¹Դؿ�
     *
     * ACE_Task::svc() �Υ����С��饤��
     *
     * @else
     * @brief Thread execution function
     *
     * ACE_Task::svc() override function
     *
     * @endif
     */
    virtual int svc(void);
    
    /*!
     * @if jp
     * @brief ����������
     *
     * ACE_Task::open() �Υ����С��饤��
     *
     * @else
     * @brief Task start function
     *
     * ACE_Task::open() override function
     *
     * @endif
     */
    virtual int open(void *args);
    
    /*!
     * @if jp
     * @brief ��������λ�ؿ�
     *
     * ACE_Task::release() �Υ����С��饤��
     * ��ư�ե饰��false�����ꤷ���� Publisher �ζ�ư����ߤ��롣
     * �����������磱�󥳥󥷥塼�ޤ����н������ƤӽФ�����礬���롣
     *
     * @else
     * @brief Task terminate function
     *
     * ACE_Task::release() override function
     *
     * @endif
     */
    virtual void release();
    
  protected:
    
  private:
    InPortConsumer* m_consumer;
    bool m_running;
    unsigned int m_usec;
  };
};     // namespace RTC
#endif // PublisherPeriodic_h
