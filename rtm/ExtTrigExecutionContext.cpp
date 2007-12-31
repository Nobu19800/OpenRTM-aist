// -*- C++ -*-
/*!
 * @file ExtTrigExecutionContext.cpp
 * @brief ExtTrigExecutionContext class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ExtTrigExecutionContext.cpp,v 1.1.2.3 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.2.2  2007/09/21 09:17:21  n-ando
 * The mutex acquisition was changed from "tryacquire" to "acquire".
 *
 * Revision 1.1.2.1  2007/09/19 07:48:47  n-ando
 * A trivial fix.
 *
 * Revision 1.1  2007/04/13 16:08:18  n-ando
 * External Triggered ExecutionContext class.
 *
 */

#include <rtm/ExtTrigExecutionContext.h>
#include <rtm/ECFactory.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   *
   * @endif
   */
  ExtTrigExecutionContext::ExtTrigExecutionContext()
    : PeriodicExecutionContext()
  {
  }
  
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   *
   * @endif
   */
  ExtTrigExecutionContext::~ExtTrigExecutionContext()
  {
  }
  
  /*!
   * @if jp
   * @brief ������1���ƥå׿ʤ��
   * @else
   *
   * @endif
   */
  void ExtTrigExecutionContext::tick()
  {
    m_worker._mutex.acquire();
    m_worker._called = true;
    m_worker._cond.signal();
    m_worker._mutex.release();
    return;
  }
  
  /*!
   * @if jp
   * @brief �� Component �ν�����ƤӽФ���
   * @else
   *
   * @endif
   */
  int ExtTrigExecutionContext::svc(void)
  {
    do
      {
	ACE_Time_Value tv(0, m_usec); // (s, us)
	
	m_worker._mutex.acquire();
	while (!m_worker._called && m_running)
	  {
	    m_worker._cond.wait();
	  }
	if (m_worker._called)
	  {
	    m_worker._called = false;
	    std::for_each(m_comps.begin(), m_comps.end(), invoke_worker());
	  }
	m_worker._mutex.release();
      } while (m_running);
    
    return 0;
  }
};


extern "C"
{
  /*!
   * @if jp
   * @brief ���� ExecutionContext ��Factory���饹����Ͽ��
   * @else
   *
   * @endif
   */
  void ExtTrigExecutionContextInit(RTC::Manager* manager)
  {
    manager->registerECFactory("ExtTrigExecutionContext",
			       RTC::ECCreate<RTC::ExtTrigExecutionContext>,
			       RTC::ECDelete<RTC::ExtTrigExecutionContext>);
  }
};
