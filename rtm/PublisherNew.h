// -*- C++ -*-
/*!
 * @file  PublisherNew.h
 * @brief PublisherNew class
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

#ifndef PublisherNew_h
#define PublisherNew_h

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
   * @class PublisherNew
   * @brief PublisherNew ���饹
   *
   * �Хåե���˿����ǡ�������Ǽ���줿�����ߥ󥰤ǡ����ο����ǡ������������롣
   * �ǡ������Х����ߥ󥰤��Ԥĥ��󥷥塼�ޤ����Ф���¦�Ȥϰۤʤ륹��åɤ�
   * ư�������˻��ѡ�
   * Publisher�ζ�ư�ϡ��ǡ������ФΥ����ߥ󥰤ˤʤ�ޤǥ֥�å����졢
   * ���Х����ߥ󥰤����Τ������ȡ�¨�¤˥��󥷥塼�ޤ����н�����ƤӽФ���
   *
   * @else
   * @class PublisherNew
   * @brief PublisherNew class
   *
   * Send new data at timing of when it is stored into the buffer.
   * This class is used when operating Consumer that waits for the data send
   * timing in different thread from one of the send side.
   * Publisher's driven is blocked until the data send timing reaches, if the
   * send timing notification is received, the Consumer's send processing will
   * be invoked immediately.
   *
   * @endif
   */
  class PublisherNew
    : public PublisherBase,
      public ACE_Task<ACE_MT_SYNCH>
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     * �� Publisher �ѿ�������åɤ��������롣
     *
     * @param consumer �ǡ������Ф��Ԥĥ��󥷥塼��
     * @param property ��Publisher�ζ�ư�����������ꤷ��Property���֥�������
     *                 (��Publisher�Ǥ�̤����)
     * @else
     * @brief Constructor
     *
     * Constructor
     * Create new thread for this Publisher.
     *
     * @param consumer Consumer that waits for the data sending
     * @param property Property object that is configured this Publisher's
     *                 control information.(Unused in this Publisher)
     * @endif
     */
    PublisherNew(InPortConsumer* consumer,
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
    virtual ~PublisherNew();
    
    /*!
     * @if jp
     * @brief Observer�ؿ�
     *
     * ���Х����ߥ󥰻��˸ƤӽФ���
     * �֥�å����Ƥ�������Publisher�ζ�ư�����Ϥ��졢���󥷥塼�ޤؤ����н�����
     * �Ԥ��롣
     *
     * @else
     * @brief Observer function
     *
     * Invoke at send timing.
     * Start this Publisher's control that has been blocked and do the send
     * processing to Consumer.
     *
     * @endif
     */
    virtual void update();
    
    /*!
     * @if jp
     * @brief ����åɼ¹Դؿ�
     *
     * ACE_Task::svc() �Υ����С��饤��
     * �Хåե���Υǡ��������������ޤǥ���åɤ��Ե������롣
     *
     * @return �¹Է��
     *
     * @else
     * @brief Thread execution function
     *
     * ACE_Task::svc() override function.
     * Make thread stand by until data in the buffer is updated.
     *
     * @return Execution result
     *
     * @endif
     */
    virtual int svc(void);
    
    /*!
     * @if jp
     * @brief ����������
     *
     * ACE_Task::open() �Υ����С��饤��
     * �� publisher �ѿ�������åɤ��������롣
     *
     * @param args ����å������Ѱ���(��Publisher�Ǥ�̤����)
     *
     * @return �¹Է��
     *
     * @else
     * @brief Task start function
     *
     * ACE_Task::open() override function.
     * Create newly thread for this Publisher.
     *
     * @param args Thread creation arguments (Unused in this Publisher)
     *
     * @return Execution result
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
     * ����������ư����åɤ��֥�å�����Ƥ�����ˤϡ�
     * ���磱�󥳥󥷥塼�ޤ����н������ƤӽФ�����礬���롣
     *
     * @else
     * @brief Task terminate function
     *
     * ACE_Task::release() override function.
     * Set driven flag to false, and terminate this Publisher's operation.
     * However, if the driven thread is blocked, Consumer's send
     * processing may be invoked maximum once.
     *
     * @endif
     */
    virtual void release();
    
  protected:
    
  private:
    InPortConsumer* m_consumer;
    bool m_running;
    unsigned long m_usec;
    
    // NewData condition struct
    struct NewData
    {
      NewData() : _cond(_mutex), _updated(false) {};
      ACE_Thread_Mutex _mutex;
      ACE_Condition<ACE_Thread_Mutex> _cond;
      bool _updated;
    };
    
    // A condition variable for data update notification 
    NewData m_data;
  };
};     // namespace RTC
#endif // PublisherNew_h

