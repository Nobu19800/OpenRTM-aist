// -*- C++ -*-
/*!
 * @file PeriodicExecutionContext.cpp
 * @brief PeriodicExecutionContext class
 * @date $Date: 2007-09-19 07:44:37 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PeriodicExecutionContext.cpp,v 1.5.2.2 2007-09-19 07:44:37 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5.2.1  2007/07/20 15:58:50  n-ando
 * Some ineffective expressions were added to suppress compiler's warning.
 *
 * Revision 1.5  2007/04/13 15:52:15  n-ando
 * RTC::OK was changed to RTC::RTC_OK.
 * Initialization function was added to make it an external module.
 *
 * Revision 1.4  2007/02/04 16:56:52  n-ando
 * The bugs around object references count were fixed.
 *
 * Revision 1.3  2007/01/21 10:26:55  n-ando
 * Object reference count related bugs were fixed.
 *
 * Revision 1.2  2007/01/14 19:44:26  n-ando
 * The logic of main activity loop was changed.
 *
 * Revision 1.1  2007/01/09 15:29:25  n-ando
 * PeriodicExecutionContext class
 *
 */

#include <rtm/PeriodicExecutionContext.h>
#include <algorithm>
#include <iostream>

namespace RTC
{
  PeriodicExecutionContext::
  PeriodicExecutionContext()
    : m_running(false), m_nowait(false)
  {
    m_profile.kind = PERIODIC;
    m_profile.rate = 0.0;
    m_usec = (long int)0;
    m_ref = this->_this();
  }


  PeriodicExecutionContext::
  PeriodicExecutionContext(DataFlowComponent_ptr owner,
			   double rate)
    : m_running(false), m_nowait(false)
  {
    m_profile.kind = PERIODIC;
    m_profile.rate = rate;
    if (rate == 0) rate = 0.0000001;
    m_usec = (long int)(1000000/rate);
    if (m_usec == 0) m_nowait = true;
    m_ref = this->_this();
  }


  PeriodicExecutionContext::~PeriodicExecutionContext()
  {
    ;
  }


  

  /*------------------------------------------------------------
   * Start activity
   * ACE_Task class method over ride.
   *------------------------------------------------------------*/
  int PeriodicExecutionContext::open(void *args)
  {
    //    RTC_TRACE(("RtcBase::open()"));
    //    ACE_Guard<ACE_Thread_Mutex> guard_next(m_NextState._mutex);
    //    m_NextState._state = RTC_INITIALIZING;
    activate();
    return 0;
  }
  
  
  /*------------------------------------------------------------
   * Run by a daemon thread to handle deferred processing
   * ACE_Task class method over ride.
   *------------------------------------------------------------*/
  int PeriodicExecutionContext::svc(void)
  {
    //    RTC_TRACE(("RtcBase::svc()"));
    do
      {
	ACE_Time_Value tv(0, m_usec); // (s, us)
	std::for_each(m_comps.begin(), m_comps.end(), invoke_worker());
	while (!m_running) {ACE_OS::sleep(tv);}
	if (!m_nowait) ACE_OS::sleep(tv);
      } while (m_running);
    //    forceExit();
    //    finalize();
    return 0;
  }
  
  
  int PeriodicExecutionContext::close(unsigned long flags)
  {
    //    RTC_TRACE(("RtcBase::close()"));
    
    // At this point, this component have to be finished.
    // Current state and Next state should be RTC_EXITING.
    //    delete this;
    return 0;
  }
  



  //============================================================
  // ExecutionContext
  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContext ���¹��椫�ɤ����Υƥ���
   * @else
   * @brief Test for ExecutionContext running state
   * @endif
   */
  CORBA::Boolean PeriodicExecutionContext::is_running()
  {
    return m_running;
  }


  /*!
   * @if jp
   * @brief ExecutionContext �򥹥����Ȥ�����
   * @else
   * @brief Start the ExecutionContext
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::start()
  {
    if (m_running) return RTC::PRECONDITION_NOT_MET;

    // invoke ComponentAction::on_startup for each comps.
    std::for_each(m_comps.begin(), m_comps.end(), invoke_on_startup());

    // change EC thread state
    m_running = true;
    this->open(0);

    return RTC::RTC_OK;
  }
  

  /*!
   * @if jp
   * @brief ExecutionContext �򥹥ȥåפ�����
   * @else
   * @brief Stop the ExecutionContext
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::stop()
  {
    if (!m_running) return RTC::PRECONDITION_NOT_MET;

    // invoke on_shutdown for each comps.
    std::for_each(m_comps.begin(), m_comps.end(), invoke_on_shutdown());

    // change EC thread state
    m_running = false;

    return RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief �¹Լ���(Hz)���������
   * @else
   * @brief Get executionrate(Hz)
   * @endif
   */
  CORBA::Double PeriodicExecutionContext::get_rate()
  {
    return m_profile.rate;
  }


  /*!
   * @if jp
   * @brief �¹Լ���(Hz)��Ϳ���� 
   * @else
   * @brief Set rate (Hz)
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::set_rate(CORBA::Double rate)
  {
    if (rate > 0.0)
      {
	m_profile.rate = rate;
	m_usec = (long int)(1000000/rate);
	if (m_usec == 0) m_nowait = ture;
	std::for_each(m_comps.begin(), m_comps.end(), invoke_on_rate_changed());
	return RTC::RTC_OK;
      }
    return RTC::BAD_PARAMETER;
  }


  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ򥢥��ƥ��ֲ�����
   * @else
   * @brief Activate a component
   * @endif
   */ 
  ReturnCode_t
  PeriodicExecutionContext::activate_component(LightweightRTObject_ptr comp)
  {
    // ����ݡ��ͥ�Ȥ����üԥꥹ�Ȥ�̵����� BAD_PARAMETER ���֤�
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
    		      find_comp(LightweightRTObject::_duplicate(comp)));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;

    if (!(it->_sm.m_sm.isIn(INACTIVE_STATE)))
      return RTC::PRECONDITION_NOT_MET;

    it->_sm.m_sm.goTo(ACTIVE_STATE);
    return RTC::RTC_OK;
  }
  

  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ�����
   * @else
   * @brief Deactivate a component
   * @endif
   */  
  ReturnCode_t
  PeriodicExecutionContext::deactivate_component(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(RTC::LightweightRTObject::_duplicate(comp)));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;

    if (!(it->_sm.m_sm.isIn(ACTIVE_STATE)))
      return RTC::PRECONDITION_NOT_MET;
    
    it->_sm.m_sm.goTo(INACTIVE_STATE);
    return RTC::RTC_OK;
  }
  
  
  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ�����
   * @else
   * @brief Deactivate a component
   * @endif
   */  
  ReturnCode_t
  PeriodicExecutionContext::reset_component(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(RTC::LightweightRTObject::_duplicate(comp)));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;

    if (!(it->_sm.m_sm.isIn(ERROR_STATE)))
      return RTC::PRECONDITION_NOT_MET;
    
    it->_sm.m_sm.goTo(INACTIVE_STATE);
    return RTC::RTC_OK;
  }
  

  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥξ��֤��������
   * @else
   * @brief Get component's state
   * @endif
   */
  LifeCycleState
  PeriodicExecutionContext::get_component_state(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(RTC::LightweightRTObject::_duplicate(comp)));
    if (it == m_comps.end())
      return RTC::UNKNOWN_STATE;

    return it->_sm.m_sm.getState();
  }

  /*!
   * @if jp
   * @brief ExecutionKind ���������
   * @else
   * @brief Get the ExecutionKind
   * @endif
   */
  ExecutionKind PeriodicExecutionContext::get_kind()
  {
    return m_profile.kind;
  }
  
  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ��ɲä���
   * @else
   * @brief Add a component
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::add(LightweightRTObject_ptr comp)
  {
    if (CORBA::is_nil(comp)) return RTC::BAD_PARAMETER;

    try
      {
	DataFlowComponent_ptr dfp;
	dfp = DataFlowComponent::_narrow(comp);

	UniqueId id;
	id = dfp->attach_executioncontext(m_ref);

	m_comps.push_back(Comp(LightweightRTObject::_duplicate(comp),
			       DataFlowComponent::_duplicate(dfp), id));
	return RTC::RTC_OK;
      }
    catch (CORBA::Exception& e)
      {
	e;
	return RTC::BAD_PARAMETER;
      }
    return RTC::RTC_OK;
  }
  
  
  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ򥳥�ݡ��ͥ�ȥꥹ�Ȥ���������
   * @else
   * @brief Remove the component from component list
   * @endif
   */	
  ReturnCode_t
  PeriodicExecutionContext::remove(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(RTC::LightweightRTObject::_duplicate(comp)));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;

    m_comps.erase(it);

    return RTC::RTC_OK;
  }



  //============================================================
  // ExecutionContextAdmin interfaces
  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContextProfile ���������
   * @else
   * @brief Get the ExecutionContextProfile
   * @endif
   */
  ExecutionContextProfile* PeriodicExecutionContext::get_profile()
  {
    ExecutionContextProfile_var p;
    p = new ExecutionContextProfile(m_profile);
    return p._retn();
  }
}; // namespace RTC  

extern "C"
{
  void PeriodicExecutionContextInit(RTC::Manager* manager)
  {
    manager->registerECFactory("PeriodicExecutionContext",
			       RTC::ECCreate<RTC::PeriodicExecutionContext>,
			       RTC::ECDelete<RTC::PeriodicExecutionContext>);
    
  }
};

