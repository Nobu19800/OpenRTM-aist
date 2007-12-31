// -*- C++ -*-
/*!
 * @file ExtTrigExecutionContext.h
 * @brief ExtTrigExecutionContext class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ExtTrigExecutionContext.h,v 1.2.2.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/04/26 15:29:39  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.1  2007/04/13 16:08:24  n-ando
 * External Triggered ExecutionContext class.
 *
 */

#ifndef ExtTrigExecutionContext_h
#define ExtTrigExecutionContext_h

#include <rtm/RTC.h>

#include <ace/Task.h>
#include <ace/Synch.h>

#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

namespace RTC
{
  /*!
   * @if jp
   * @class ExtTrigExecutionContext
   * @brief ���ƥå׼¹Ԥ���ǽ�� ExecutionContext ���饹
   *
   * 1������μ¹Ԥ���ǽ��Periodic Sampled Data Processing(�����¹���)
   * ExecutionContext���饹��
   * ��������Υ᥽�åɸƤӤ����ˤ�äƻ��֤��������ŤĿʤࡣ
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  class ExtTrigExecutionContext
    : public virtual PeriodicExecutionContext
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
     * @endif
     */
    ExtTrigExecutionContext();
    
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
    virtual ~ExtTrigExecutionContext();
    
    /*!
     * @if jp
     * @brief ������1���ƥå׿ʤ��
     *
     * ExecutionContext�ν����򣱼���ʬ�ʤ�롣
     *
     * @else
     *
     * @endif
     */
    virtual void tick();
    
    /*!
     * @if jp
     * @brief �� Component �ν�����ƤӽФ���
     *
     * ExecutionContext �� attach ����Ƥ���� Component �ν�����ƤӽФ���
     * �� Component �ν�����ƤӽФ����塢���θƽФ�ȯ������ޤǵٻߤ��롣
     *
     * @return �������
     *
     * @else
     *
     * @endif
     */
    virtual int svc(void);
    
  private:
    struct Worker
    {
      Worker() : _cond(_mutex), _called(false) {};
      ACE_Thread_Mutex _mutex;
      ACE_Condition<ACE_Thread_Mutex> _cond;
      bool _called;
    };
    // A condition variable for external triggered worker
    Worker m_worker;
  };
};

extern "C"
{
  /*!
   * @if jp
   * @brief ���� ExecutionContext ��Factory���饹����Ͽ��
   *
   * ����ExecutionContext����������Factory���饹��
   * ExecutionContext������ObjectManager����Ͽ���롣
   *
   * @else
   *
   * @endif
   */
  void ExtTrigExecutionContextInit(RTC::Manager* manager);
};

#endif // ExtTrigExecutionContext_h
