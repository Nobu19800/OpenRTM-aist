// -*- C++ -*-
/*!
 * @file Task_vxworks.cpp
 * @brief Task class
 * @date $Date$
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/Task.h>

#ifdef __RTP__
#define DEFAULT_PRIORITY 110
#define DEFAULT_STACKSIZE 60000
#endif

namespace coil
{

  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  Task::Task()
    : m_count(0)
#ifdef __RTP__
    ,m_priority(DEFAULT_PRIORITY)
    ,m_stacksize(DEFAULT_STACKSIZE)
#endif
  {
#ifdef __RTP__
#else
    ::pthread_attr_init(&m_attr);
#endif
  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  Task::~Task()
  {
    m_count = 0;
  }

  /*!
   * @if jp
   * @brief タスクオープン
   * @else
   * @brief Task open
   * @endif
   */
  int Task::open(void* args)
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief タスククローズ
   * @else
   * @brief Task close
   * @endif
   */
  int Task::close(unsigned long flags)
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief スレッドを実行する
   * @else
   * @brief Execute thread
   * @endif
   */
  int Task::svc()
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief スレッドを生成する
   * @else
   * @brief Create a thread
   * @endif
   */
  void Task::activate()
  {
    if (m_count == 0)
      {
#ifdef __RTP__
        m_tid = taskSpawn(
                         0,
                         m_priority,
                         VX_FP_TASK | VX_NO_STACK_FILL,
                         m_stacksize,
                         (FUNCPTR)Task::svc_run,
                         (int)this,
                         0,0,0,0,0,0,0,0,0
                         );
#else
        ::pthread_create(&m_thread,
                         &m_attr,
                         (void* (*)(void*))Task::svc_run,
                         this);
#endif
        ++m_count;
      };
  }

  /*!
   * @if jp
   * @brief スレッド終了を待つ
   * @else
   * @brief Waiting for the thread terminate
   * @endif
   */
  int Task::wait(void)
  {
    if (m_count > 0)
      {
#ifdef __RTP__
        Guard guard(m_waitmutex);
        //taskExit(0);
#else
        void* retval;
        ::pthread_join(m_thread, &retval);
#endif
      }
    return 0;
  }

  /*!
   * @if jp
   * @brief タスク実行を中断する
   * @else
   * @brief Suspending the task
   * @endif
   */
  int Task::suspend(void)
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief 中断されているタスクを再開する
   * @else
   * @brief Resuming the suspended task
   * @endif
   */
  int Task::resume(void)
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief タスク数リセット
   * @else
   * @brief Reset of task count
   * @endif
   */
  void Task::reset()
  {
    m_count = 0;
  }

  /*!
   * @if jp
   * @brief タスク実行を終了する
   * @else
   * @brief Finalizing the task
   * @endif
   */
  void Task::finalize()
  {
    reset();
  }

  /*!
   * @if jp
   * @brief スレッド実行を開始する
   * @else
   * @brief Start thread Execution
   * @endif
   */
#ifdef __RTP__
  extern "C" void* Task::svc_run(void* args)
#else
  void* Task::svc_run(void* args)
#endif
  {
    Task* t = (coil::Task*)args;
#ifdef __RTP__
    Guard guard(t->m_waitmutex);
#endif
    int status;
    status = t->svc();
    t->finalize();
    return 0;
  }


#ifdef __RTP__
  /*!
   * @if jp
   *
   * @brief タスクの優先度を設定
   *
   *
   * @param priority 優先度
   *
   * @else
   *
   * @brief 
   *
   *
   * @param priority 
   *
   * @endif
   */
  void Task::set_priority(int priority)
  {
    m_priority = priority;
  }
  /*!
   * @if jp
   *
   * @brief スタックサイズの設定
   *
   *
   * @param stacksize スタックサイズ
   *
   * @else
   *
   * @brief 
   *
   *
   * @param stacksize 
   *
   * @endif
   */
  void Task::set_stacksize(int stacksize)
  {
    m_stacksize = stacksize;
  }
#endif
};


