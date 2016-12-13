// -*- C++ -*-
/*!
 * @file ExtTrigExecutionContext.cpp
 * @brief ExtTrigExecutionContext class
 * @date $Date: 2008-01-14 07:49:14 $
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
 * $Id$
 *
 */

#include <coil/TimeValue.h>
#include <coil/Guard.h>

#include <rtm/ExtTrigExecutionContext.h>
#include <rtm/ECFactory.h>
#include <rtm/RTObjectStateMachine.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  ExtTrigExecutionContext::ExtTrigExecutionContext()
    : ExecutionContextBase("exttrig_async_ec"),
      rtclog("exttrig_async_ec"),
      m_svc(false)
  {
    RTC_TRACE(("ExtTrigExecutionContext()"));

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
  ExtTrigExecutionContext::~ExtTrigExecutionContext()
  {
    RTC_TRACE(("~ExtTrigExecutionContext()"));
    {
      {
        Guard guard(m_svcmutex);
        m_svc = false;
      }
      {
        Guard guard(m_worker.mutex_);
        m_worker.ticked_ = true;
        m_worker.cond_.signal();
      }
    }
    wait();
  }

  /*------------------------------------------------------------
   * Start activity
   * ACE_Task class method over ride.
   *------------------------------------------------------------*/
  /*!
   * @if jp
   * @brief ExecutionContext�ѥ����ƥ��ӥƥ�����åɤ���������
   * @else
   * @brief Generate internal activity thread for ExecutionContext
   * @endif
   */
  int ExtTrigExecutionContext::open(void *args)
  {
    RTC_TRACE(("open()"));
    activate();
    return 0;
  }

  /*!
   * @if jp
   * @brief �� Component �ν�����ƤӽФ���
   * @else
   * @brief Invoke each component's operation
   * @endif
   */
  int ExtTrigExecutionContext::svc(void)
  {
    RTC_TRACE(("svc()"));
    unsigned int count(0);
    do
      {
        {
          Guard gurad(m_worker.mutex_);
          RTC_DEBUG(("Start of worker invocation. ticked = %s",
                     m_worker.ticked_ ? "true" : "false"));
          while (!m_worker.ticked_)
            {
              m_worker.cond_.wait(); // wait for tick
              RTC_DEBUG(("Thread was woken up."));
            }
          if (!m_worker.ticked_) { continue; }
        }
        coil::TimeValue t0(coil::gettimeofday());
        ExecutionContextBase::invokeWorkerPreDo();
        ExecutionContextBase::invokeWorkerDo();
        ExecutionContextBase::invokeWorkerPostDo();
        coil::TimeValue t1(coil::gettimeofday());
        {
          Guard gurad(m_worker.mutex_);
          m_worker.ticked_ = false;
        }
        coil::TimeValue period(getPeriod());
        if (1) //count > 1000)
          {
            RTC_PARANOID(("Period:    %f [s]", (double)period));
            RTC_PARANOID(("Execution: %f [s]", (double)(t1 - t0)));
            RTC_PARANOID(("Sleep:     %f [s]", (double)(period - (t1 - t0))));
          }
        coil::TimeValue t2(coil::gettimeofday());
        if (period > (t1 - t0))
          {
            if (1 /*count > 1000*/) { RTC_PARANOID(("sleeping...")); }
            coil::sleep((coil::TimeValue)(period - (t1 - t0)));
          }
        if (1) //count > 1000)
          {
            coil::TimeValue t3(coil::gettimeofday());
            RTC_PARANOID(("Slept:       %f [s]", (double)(t3 - t2)));
            count = 0;
          }
        ++count;
      } while (threadRunning());

    return 0;
  }

  /*!
   * @if jp
   * @brief ExecutionContext �ѤΥ���åɼ¹Դؿ�
   * @else
   * @brief Thread execution function for ExecutionContext
   * @endif
   */
  int ExtTrigExecutionContext::close(unsigned long flags)
  {
    RTC_TRACE(("close()"));
    // At this point, this component have to be finished.
    // Current state and Next state should be RTC_EXITING.
    return 0;
  }

  //============================================================
  // ExtTrigExecutionContextService
  //============================================================
  /*!
   * @if jp
   * @brief ������1���ƥå׿ʤ��
   * @else
   * @brief Move forward one step of ExecutionContext
   * @endif
   */
  void ExtTrigExecutionContext::tick()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("tick()"));
    if (!isRunning())
      {
        RTC_DEBUG(("EC is not running. do nothing."))
        return;
      }
    Guard guard(m_worker.mutex_);
    m_worker.ticked_ = true;
    m_worker.cond_.signal();
    RTC_PARANOID(("EC was ticked. Signal was sent to worker thread."));
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
  CORBA::Boolean ExtTrigExecutionContext::is_running()
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
  RTC::ReturnCode_t ExtTrigExecutionContext::start()
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
  RTC::ReturnCode_t ExtTrigExecutionContext::stop()
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
  CORBA::Double ExtTrigExecutionContext::get_rate()
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
  RTC::ReturnCode_t ExtTrigExecutionContext::set_rate(CORBA::Double rate)
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
  ExtTrigExecutionContext::add_component(RTC::LightweightRTObject_ptr comp)
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
  RTC::ReturnCode_t ExtTrigExecutionContext::
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
  RTC::ReturnCode_t ExtTrigExecutionContext::
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
  RTC::ReturnCode_t ExtTrigExecutionContext::
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
  RTC::ReturnCode_t ExtTrigExecutionContext::
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
  RTC::LifeCycleState ExtTrigExecutionContext::
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
  RTC::ExecutionKind ExtTrigExecutionContext::get_kind()
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
  RTC::ExecutionContextProfile* ExtTrigExecutionContext::get_profile()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getProfile();
  }

  //============================================================
  // protected functions
  //============================================================
  /*!
   * @brief onStarted() template function
   */
  RTC::ReturnCode_t ExtTrigExecutionContext::onStarted()
  {
    // change EC thread state
    Guard gurad(m_svcmutex);
    if (!m_svc)
      { // If start() is called first time, start the worker thread.
        m_svc = true;
        this->open(0);
      }
    return RTC::RTC_OK;
  }

  /*!
   * @brief onWaitingActivated() template function
   */
  RTC::ReturnCode_t ExtTrigExecutionContext::
  onWaitingActivated(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onWaitingActivated(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    // Now comp's next state must be ACTIVE state
    // If worker thread is stopped, restart worker thread.
    Guard guard(m_worker.mutex_);
    m_worker.ticked_ = true;
    m_worker.cond_.signal();
    return RTC::RTC_OK;
  }


  /*!
   * @brief onWaitingDeactivated() template function
   */
  RTC::ReturnCode_t ExtTrigExecutionContext::
  onWaitingDeactivated(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onWaitingDeactivated(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    Guard guard(m_worker.mutex_);
    m_worker.ticked_ = true;
    m_worker.cond_.signal();
    return RTC::RTC_OK;
  }

  /*!
   * @brief onWaitingReset() template function
   */
  RTC::ReturnCode_t ExtTrigExecutionContext::
  onWaitingReset(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onWaitingReset(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    Guard guard(m_worker.mutex_);
    m_worker.ticked_ = true;
    m_worker.cond_.signal();
    return RTC::RTC_OK;
  }
};


extern "C"
{
  /*!
   * @if jp
   * @brief ���� ExecutionContext ��Factory���饹����Ͽ��
   * @else
   * @brief Register Factory class for this ExecutionContext
   * @endif
   */
  void ExtTrigExecutionContextInit(RTC::Manager* manager)
  {
    RTC::ExecutionContextFactory::
      instance().addFactory("ExtTrigExecutionContext",
                            ::coil::Creator< ::RTC::ExecutionContextBase,
                            ::RTC::ExtTrigExecutionContext>,
                            ::coil::Destructor< ::RTC::ExecutionContextBase,
                            ::RTC::ExtTrigExecutionContext>);
  }
};
