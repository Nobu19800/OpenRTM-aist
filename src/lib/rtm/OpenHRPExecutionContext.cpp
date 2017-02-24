// -*- C++ -*-
/*!
 * @file OpenHRPExecutionContext.cpp
 * @brief OpenHRPExecutionContext class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008,2012
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <rtm/OpenHRPExecutionContext.h>
#include <rtm/ECFactory.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  OpenHRPExecutionContext::OpenHRPExecutionContext()
    :  ExecutionContextBase("exttrig_sync_ec"),
       rtclog("exttrig_sync_ec"), m_count(0)
  {
    RTC_TRACE(("OpenHRPExecutionContext()"));

    // getting my reference
    setObjRef(this->_this());

    // profile initialization
    setKind(RTC::PERIODIC);
    setRate(DEFAULT_EXECUTION_RATE);

    RTC_DEBUG(("Actual period: %d [sec], %d [usec]",
               m_profile.getPeriod().sec(), m_profile.getPeriod().usec()));

  }

  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor 
   * @endif
   */
  OpenHRPExecutionContext::~OpenHRPExecutionContext()
  {
    RTC_TRACE(("~OpenHRPExecutionContext()"));
    Guard guard(m_tickmutex);
  }

  //============================================================
  // OpenHRPExecutionContextService
  //============================================================
  /*!
   * @if jp
   * @brief ������1���ƥå׿ʤ��
   * @else
   * @brief Move forward one step of ExecutionContext
   * @endif
   */
  void OpenHRPExecutionContext::tick()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("tick()"));
    if (!isRunning()) { return; }
    Guard guard(m_tickmutex);

    ExecutionContextBase::invokeWorkerPreDo(); // update state
    coil::TimeValue t0(coil::gettimeofday());
    ExecutionContextBase::invokeWorkerDo();
    coil::TimeValue t1(coil::gettimeofday());
    ExecutionContextBase::invokeWorkerPostDo();
    coil::TimeValue t2(coil::gettimeofday());

    coil::TimeValue period(getPeriod());
    if (m_count > 1000)
      {
        RTC_PARANOID(("Period:      %f [s]", (double)period));
        RTC_PARANOID(("Exec-Do:     %f [s]", (double)(t1 - t0)));
        RTC_PARANOID(("Exec-PostDo: %f [s]", (double)(t2 - t1)));
        RTC_PARANOID(("Sleep:       %f [s]", (double)(period - (t2 - t0))));
      }
    coil::TimeValue t3(coil::gettimeofday());
    if (period > (t2 - t0))
      {
        if (m_count > 1000) { RTC_PARANOID(("sleeping...")); }
        coil::sleep((coil::TimeValue)(period - (t2 - t0)));
      }
    if (m_count > 1000)
      {
        coil::TimeValue t4(coil::gettimeofday());
        RTC_PARANOID(("Slept:       %f [s]", (double)(t4 - t3)));
        m_count = 0;
      }
    ++m_count;
    return;
  }

  //============================================================
  // ExecutionContextService
  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContext �¹Ծ��ֳ�ǧ�ؿ�
   * @else
   * @brief Check for ExecutionContext running state
   * @endif
   */
  CORBA::Boolean OpenHRPExecutionContext::is_running()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::isRunning();
  }

  /*!
   * @if jp
   * @brief ExecutionContext �μ¹Ԥ򳫻�
   * @else
   * @brief Start the ExecutionContext
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::start()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::start();
  }

  /*!
   * @if jp
   * @brief ExecutionContext �μ¹Ԥ����
   * @else
   * @brief Stop the ExecutionContext
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::stop()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::stop();
  }



  /*!
   * @if jp
   * @brief ExecutionContext �μ¹Լ���(Hz)���������
   * @else
   * @brief Get execution rate(Hz) of ExecutionContext
   * @endif
   */
  CORBA::Double OpenHRPExecutionContext::get_rate()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getRate();
  }

  /*!
   * @if jp
   * @brief ExecutionContext �μ¹Լ���(Hz)�����ꤹ��
   * @else
   * @brief Set execution rate(Hz) of ExecutionContext
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::set_rate(CORBA::Double rate)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::setRate(rate);
  }

  /*!
   * @if jp
   * @brief RT����ݡ��ͥ�Ȥ��ɲä���
   * @else
   * @brief Add an RT-Component
   * @endif
   */
  RTC::ReturnCode_t
  OpenHRPExecutionContext::add_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::addComponent(comp);
  }

  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ򥳥�ݡ��ͥ�ȥꥹ�Ȥ���������
   * @else
   * @brief Remove the RT-Component from participant list
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::
  remove_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::removeComponent(comp);
  }

  /*!
   * @if jp
   * @brief RT����ݡ��ͥ�Ȥ򥢥��ƥ��ֲ�����
   * @else
   * @brief Activate an RT-Component
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::
  activate_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::activateComponent(comp);
  }

  /*!
   * @if jp
   * @brief RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ�����
   * @else
   * @brief Deactivate an RT-Component
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::
  deactivate_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::deactivateComponent(comp);
  }

  /*!
   * @if jp
   * @brief RT����ݡ��ͥ�Ȥ�ꥻ�åȤ���
   * @else
   * @brief Reset the RT-Component
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::
  reset_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::resetComponent(comp);
  }

  /*!
   * @if jp
   * @brief RT����ݡ��ͥ�Ȥξ��֤��������
   * @else
   * @brief Get RT-Component's state
   * @endif
   */
  RTC::LifeCycleState OpenHRPExecutionContext::
  get_component_state(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getComponentState(comp);
  }

  /*!
   * @if jp
   * @brief ExecutionKind ���������
   * @else
   * @brief Get the ExecutionKind
   * @endif
   */
  RTC::ExecutionKind OpenHRPExecutionContext::get_kind()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getKind();
  }

  //------------------------------------------------------------
  // ExecutionContextService interfaces
  //------------------------------------------------------------
  /*!
   * @if jp
   * @brief ExecutionContextProfile ���������
   * @else
   * @brief Get the ExecutionContextProfile
   * @endif
   */
  RTC::ExecutionContextProfile* OpenHRPExecutionContext::get_profile()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getProfile();
  }


  // template virtual functions adding/removing component
  /*!
  * @brief onAddedComponent() template function
  */
  RTC::ReturnCode_t OpenHRPExecutionContext::
	  onAddedComponent(RTC::LightweightRTObject_ptr rtobj)
  {
	  Guard guard(m_tickmutex);

	  ExecutionContextBase::m_worker.updateComponentList();

	  return RTC::RTC_OK;
  }
  /*!
  * @brief onRemovedComponent() template function
  */
  RTC::ReturnCode_t OpenHRPExecutionContext::
	  onRemovedComponent(RTC::LightweightRTObject_ptr rtobj)
  {
	  Guard guard(m_tickmutex);

	  ExecutionContextBase::m_worker.updateComponentList();

	  return RTC::RTC_OK;
  }
};


extern "C"
{
  /*!
   * @if jp
   * @brief ECFactory�ؤ���Ͽ�Τ���ν�����ؿ�
   * @else
   * @brief Initialization function to register to ECFactory
   * @endif
   */
  void OpenHRPExecutionContextInit(RTC::Manager* manager)
  {
    RTC::ExecutionContextFactory::
      instance().addFactory("SynchExtTriggerEC",
                            ::coil::Creator< ::RTC::ExecutionContextBase,
                            ::RTC::OpenHRPExecutionContext>,
                            ::coil::Destructor< ::RTC::ExecutionContextBase,
                            ::RTC::OpenHRPExecutionContext>);
  }
};
