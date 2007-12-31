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
 * $Id: PublisherNew.h,v 1.3.2.1 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/26 15:32:45  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.2  2007/01/06 18:00:54  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:49  n-ando
 * The first commitment.
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
     * @endif
     */
    PublisherNew(InPortConsumer* consumer,
		 const Properties& property);
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * �ǥ��ȥ饯��
     * @else
     * @brief Destructor
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
     * �� publisher �ѿ�������åɤ��������롣
     *
     * @param args ����å������Ѱ���(��Publisher�Ǥ�̤����)
     *
     * @return �¹Է��
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
     * ����������ư����åɤ��֥�å�����Ƥ�����ˤϡ�
     * ���磱�󥳥󥷥塼�ޤ����н������ƤӽФ�����礬���롣
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

