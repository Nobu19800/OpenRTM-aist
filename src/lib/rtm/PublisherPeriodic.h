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
 * $Id$
 *
 */

#ifndef PublisherPeriodic_h
#define PublisherPeriodic_h

#include <rtm/RTC.h>

#include <coil/Task.h>

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
   *
   * Publisher that invokes the consumer's sending process periodically.
   * This is used when the data sending is regularly executed.
   *
   * @endif
   */
  class PublisherPeriodic
    : public PublisherBase,
      public coil::Task
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
     *
     * Constructor.
     * The intervals of invoking send processing needs to be set in
     * dataport.push_rate of Property object. The interval is specified by
     * floating point string in Hz.
     * For example, "1000.0" is set for 1000.0Hz.
     * If the above property is unset, "1000Hz" will be set.
     *
     * @param consumer Consumer which waits for data sending
     * @param property Property objects that are set the control information
     *                 of this Publisher
     *
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
     *
     * Destructor
     *
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
     *
     * Execute nothing in this Publisher.
     *
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
     * ACE_Task::svc() override function.
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
     * @brief Start task
     *
     * ACE_Task::open() override function.
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
     * ACE_Task::release() override function.
     * Set driven flag to false, and terminate the operation of this Publisher.
     * However, the consumer's sending process may be invoked once or less.
     *
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

