// -*- C++ -*-
/*!
 * @file PeriodicExecutionContext.h
 * @brief PeriodicExecutionContext class
 * @date $Date: 2008-01-14 07:53:05 $
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
 * $Id: PeriodicExecutionContext.h,v 1.4.2.5 2008-01-14 07:53:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4.2.4  2007/12/31 03:08:05  n-ando
 * Class reference by doxygen comment was revised.
 *
 * Revision 1.4.2.3  2007/09/20 11:22:08  n-ando
 * Some fixes.
 * - Template parameter "Result" is deleted.
 *   Now listener return type is void instead of the Result.
 *
 * Revision 1.4.2.2  2007/09/19 07:44:35  n-ando
 * The usleep() in the execution loop will be skipped, if wait-time is 0.
 *
 * Revision 1.4.2.1  2007/07/20 15:59:18  n-ando
 * ACE header include was added.
 *
 * Revision 1.4  2007/04/26 15:30:46  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.3  2007/04/13 15:52:34  n-ando
 * RTC::OK was changed to RTC::RTC_OK.
 * Initialization function was added to make it an external module.
 *
 * Revision 1.2  2007/01/21 10:27:00  n-ando
 * Object reference count related bugs were fixed.
 *
 * Revision 1.1  2007/01/09 15:29:35  n-ando
 * PeriodicExecutionContext class
 *
 */

#ifndef PeriodicExecutionContext_h
#define PeriodicExecutionContext_h

#include <rtm/RTC.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>
#include <rtm/Manager.h>
#include <rtm/StateMachine.h>
#include <rtm/ExecutionContextBase.h>

// ACE
#include <ace/Task.h>
#include <ace/OS_NS_unistd.h>
#include <vector>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   * @class PeriodicExecutionContext
   * @brief PeriodicExecutionContext ���饹
   *
   * Periodic Sampled Data Processing(�����¹���)ExecutionContext���饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class PeriodicExecutionContext
   * @brief PeriodicExecutionContext class
   * @endif
   */
  class PeriodicExecutionContext
    : public virtual ExecutionContextBase,
      public ACE_Task<ACE_MT_SYNCH>
  {
  public:
    /*!
     * @if jp
     * @brief �ǥե���ȥ��󥹥ȥ饯��
     *
     * �ǥե���ȥ��󥹥ȥ饯��
     * �ץ�ե�����˰ʲ��ι��ܤ����ꤹ�롣
     * ��kind : PERIODIC
     * ��rate : 0.0
     *
     * @else
     * @brief Constructor
     * @endif
     */
    PeriodicExecutionContext();
    
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     * ���ꤵ�줿�ͤ�ץ�ե���������ꤹ�롣
     *
     * @param owner ���� Executioncontext �� owner
     * @param rate ư�����(Hz)(�ǥե������:1000)
     *
     * @else
     * @brief Constructor
     * @endif
     */
    PeriodicExecutionContext(DataFlowComponent_ptr owner,
			     double rate = 1000.0);
    
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
    virtual ~PeriodicExecutionContext();
    
    /*!
     * @if jp
     * @brief CORBA ���֥������Ȼ��Ȥμ���
     *
     * �ܥ��֥������Ȥ� ExecutioncontextService �Ȥ��Ƥ� CORBA ���֥������Ȼ���
     * ��������롣
     *
     * @return CORBA ���֥������Ȼ���
     *
     * @else
     *
     * @endif
     */
    ExecutionContextService_ptr getRef() {return m_ref;}
    
    /*!
     * @if jp
     * @brief ExecutionContext�ѥ����ƥ��ӥƥ�����åɤ���������
     *
     * Executioncontext �Ѥ����������ƥ��ӥƥ�����åɤ���������ư���롣
     * ����� ACE_Task �����ӥ����饹�᥽�åɤΥ����С��饤�ɡ�
     *
     * @param args �̾��0
     *
     * @return ���������¹Է��
     *
     * @else
     *
     * @brief Create internal activity thread
     *
     * Create internal activity thread. This is ACE_Task class method over ride.
     *
     * @param args usually give 0
     *
     * @endif
     */     
    virtual int open(void *args);
    
    /*!
     * @if jp
     * @brief ExecutionContext �ѤΥ���åɼ¹Դؿ�
     *
     * ExecutionContext �ѤΥ���åɼ¹Դؿ���
     * ��Ͽ���줿����ݡ��ͥ�Ȥν�����ƤӽФ���
     *
     * @return �¹Է��
     *
     * @else
     *
     * Run by a daemon thread to handle deferred processing.
     * ACE_Task class method override.
     *
     * @endif
     */     
    virtual int svc(void);
    
    /*!
     * @if jp
     * @brief ExecutionContext �ѤΥ���åɽ�λ�ؿ�
     *
     * ExecutionContext �ѤΥ���åɽ�λ���˸ƤФ�롣
     * ����ݡ��ͥ�ȥ��֥������Ȥ��󥢥��ƥ��ֲ����ޥ͡�����ؤ����Τ�Ԥ���
     * ����� ACE_Task �����ӥ����饹�᥽�åɤΥ����С��饤�ɡ�
     *
     * @param flags ��λ�����ե饰
     *
     * @return ��λ�������
     *
     * @else
     *
     * @brief Close activity thread
     *
     * close() method is called when activity thread svc() is returned.
     * This method deactivate this object and notify it to manager.
     * ACE_Task class method override.
     *
     * @endif
     */     
    virtual int close(unsigned long flags);
    
    //============================================================
    // ExecutionContext
    //============================================================
    /*!
     * @if jp
     * @brief ExecutionContext �¹Ծ��ֳ�ǧ�ؿ�
     *
     * �������� ExecutionContext �� Runnning ���֤ξ��� true ���֤���
     * Executioncontext �� Running �δ֡����� Executioncontext �˻��ä��Ƥ���
     * ���ƤΥ����ƥ���RT����ݡ��ͥ�Ȥ��� ExecutionContext �μ¹Լ���˱�����
     * �¹Ԥ���롣
     *
     * @return ���ֳ�ǧ�ؿ�(ư����:true�������:false)
     *
     * @else
     *
     * @brief Check for ExecutionContext running state
     *
     * This operation shall return true if the context is in the Running state.
     * While the context is Running, all Active RTCs participating
     * in the context shall be executed according to the context��s execution
     * kind.
     *
     * @endif
     */
    virtual CORBA::Boolean is_running()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Ԥ򳫻�
     *
     * ExecutionContext �μ¹Ծ��֤� Runnning �Ȥ��뤿��Υꥯ�����Ȥ�ȯ�Ԥ��롣			 * ExecutionContext �ξ��֤����ܤ���� ComponentAction::on_startup ��
     * �ƤӽФ���롣
     * ���ä��Ƥ���RT����ݡ��ͥ�Ȥ�������������ޤ� ExecutionContext �򳫻�
     * ���뤳�ȤϤǤ��ʤ���
     * ExecutionContext ��ʣ���󳫻�/��ߤ򷫤��֤����Ȥ��Ǥ��롣
     *
     * @return �����¹Է��
     *
     * @else
     *
     * @brief Start ExecutionContext
     *
     * Request that the context enter the Running state. 
     * Once the state transition occurs, the ComponentAction::on_startup 
     * operation will be invoked.
     * An execution context may not be started until the RT components that
     * participate in it have been initialized.
     * An execution context may be started and stopped multiple times.
     *
     * @endif
     */
    virtual ReturnCode_t start()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Ԥ����
     *
     * ExecutionContext �ξ��֤� Stopped �Ȥ��뤿��Υꥯ�����Ȥ�ȯ�Ԥ��롣
     * ���ܤ�ȯ���������ϡ� ComponentAction::on_shutdown ���ƤӽФ���롣
     * ���ä��Ƥ���RT����ݡ��ͥ�Ȥ���λ�������� ExecutionContext ����ߤ���
     * ɬ�פ����롣
     * ExecutionContext ��ʣ���󳫻�/��ߤ򷫤��֤����Ȥ��Ǥ��롣
     *
     * @return �����¹Է��
     *
     * @else
     *
     * @brief Stop ExecutionContext
     *
     * Request that the context enter the Stopped state. 
     * Once the transition occurs, the ComponentAction::on_shutdown operation
     * will be invoked.
     * An execution context must be stopped before the RT components that
     * participate in it are finalized.
     * An execution context may be started and stopped multiple times.
     *
     * @endif
     */
    virtual ReturnCode_t stop()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Լ��������
     *
     * Active ���֤ˤ�RT����ݡ��ͥ�Ȥ��¹Ԥ�������(ñ��:Hz)��������롣
     *
     * @return ��������(ñ��:Hz)
     *
     * @else
     *
     * @brief Get ExecutionRate
     *
     * This operation shall return the rate (in hertz) at which its Active
     * participating RTCs are being invoked.
     *
     * @endif
     */
    virtual CORBA::Double get_rate()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Լ���������
     *
     * Active ���֤ˤ�RT����ݡ��ͥ�Ȥ��¹Ԥ�������(ñ��:Hz)�����ꤹ�롣
     * �¹Լ������ѹ��ϡ� DataFlowComponentAction �� on_rate_changed �ˤ�ä�
     * ��RT����ݡ��ͥ�Ȥ���ã����롣
     *
     * @param rate ��������(ñ��:Hz)
     *
     * @return �����¹Է��
     *
     * @else
     *
     * @brief Set ExecutionRate
     *
     * This operation shall set the rate (in hertz) at which this context��s 
     * Active participating RTCs are being called.
     * If the execution kind of the context is PERIODIC, a rate change shall
     * result in the invocation of on_rate_changed on any RTCs realizing
     * DataFlowComponentAction that are registered with any RTCs participating
     * in the context.
     *
     * @endif
     */
    virtual ReturnCode_t  set_rate(CORBA::Double rate)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ򥢥��ƥ��ֲ�����
     *
     * Inactive ���֤ˤ���RT����ݡ��ͥ�Ȥ�Active �����ܤ�����
     * �����ƥ��ֲ����롣
     * �������ƤФ줿��̡� on_activate ���ƤӽФ���롣
     * ���ꤷ��RT����ݡ��ͥ�Ȥ����üԥꥹ�Ȥ˴ޤޤ�ʤ����ϡ�BAD_PARAMETER��			 * �֤���롣
     * ���ꤷ��RT����ݡ��ͥ�Ȥξ��֤� Inactive �ʳ��ξ��ϡ�
     * PRECONDITION_NOT_MET���֤���롣
     *
     * @param comp �����ƥ��ֲ��о�RT����ݡ��ͥ��
     *
     * @return �����¹Է��
     *
     * @else
     *
     * @brief Activate a RT-component
     *
     * The given participant RTC is Inactive and is therefore not being invoked
     * according to the execution context��s execution kind. This operation
     * shall cause the RTC to transition to the Active state such that it may
     * subsequently be invoked in this execution context.
     * The callback on_activate shall be called as a result of calling this
     * operation. This operation shall not return until the callback has
     * returned, and shall result in an error if the callback does.
     *
     * @endif
     */
    virtual ReturnCode_t activate_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ�����
     *
     * Inactive ���֤ˤ���RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ�����
     * Inactive �����ܤ����롣
     * �������ƤФ줿��̡� on_deactivate ���ƤӽФ���롣
     * ���ꤷ��RT����ݡ��ͥ�Ȥ����üԥꥹ�Ȥ˴ޤޤ�ʤ����ϡ�BAD_PARAMETER��			 * �֤���롣
     * ���ꤷ��RT����ݡ��ͥ�Ȥξ��֤� Active �ʳ��ξ��ϡ�
     * PRECONDITION_NOT_MET���֤���롣
     *
     * @param comp �󥢥��ƥ��ֲ��о�RT����ݡ��ͥ��
     *
     * @return �����¹Է��
     *
     * @else
     *
     * @brief Deactivate a RT-component
     *
     * The given RTC is Active in the execution context. Cause it to transition 
     * to the Inactive state such that it will not be subsequently invoked from
     * the context unless and until it is activated again.
     * The callback on_deactivate shall be called as a result of calling this
     * operation. This operation shall not return until the callback has 
     * returned, and shall result in an error if the callback does.
     *
     * @endif
     */
    virtual ReturnCode_t deactivate_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ�ꥻ�åȤ���
     *
     * Error ���֤�RT����ݡ��ͥ�Ȥ��������ߤ롣
     * �������ƤФ줿��̡� on_reset ���ƤӽФ���롣
     * ���ꤷ��RT����ݡ��ͥ�Ȥ����üԥꥹ�Ȥ˴ޤޤ�ʤ����ϡ�BAD_PARAMETER��
     * �֤���롣
     * ���ꤷ��RT����ݡ��ͥ�Ȥξ��֤� Error �ʳ��ξ��ϡ�PRECONDITION_NOT_MET
     * ���֤���롣
     *
     * @param comp �ꥻ�å��о�RT����ݡ��ͥ��
     *
     * @return �����¹Է��
     *
     * @else
     *
     * @brief Reset a RT-component
     *
     * Attempt to recover the RTC when it is in Error.
     * The ComponentAction::on_reset callback shall be invoked. This operation
     * shall not return until the callback has returned, and shall result in an
     * error if the callback does. If possible, the RTC developer should
     * implement that callback such that the RTC may be returned to a valid
     * state.
     *
     * @endif
     */
    virtual ReturnCode_t reset_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥξ��֤��������
     *
     * ���ꤷ��RT����ݡ��ͥ�Ȥξ���(LifeCycleState)��������롣
     * ���ꤷ��RT����ݡ��ͥ�Ȥ����üԥꥹ�Ȥ˴ޤޤ�ʤ����ϡ�UNKNOWN_STATE��
     * �֤���롣
     *
     * @param comp ���ּ����о�RT����ݡ��ͥ��
     *
     * @return ���ߤξ���(LifeCycleState)
     *
     * @else
     *
     * @brief Get RT-component's state
     *
     * This operation shall report the LifeCycleState of the given participant
     * RTC.
     *
     * @endif
     */
    virtual LifeCycleState get_component_state(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionKind ���������
     *
     * �� ExecutionContext �� ExecutionKind ���������
     *
     * @return ExecutionKind
     *
     * @else
     *
     * @brief Get the ExecutionKind
     *
     * This operation shall report the execution kind of the execution context.
     *
     * @endif
     */
    virtual ExecutionKind get_kind()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ��ɲä���
     *
     * ���ꤷ��RT����ݡ��ͥ�Ȥ򻲲üԥꥹ�Ȥ��ɲä��롣
     * �ɲä��줿RT����ݡ��ͥ�Ȥ� attach_context ���ƤФ졢Inactive ���֤�����
     * ���롣
     * ���ꤵ�줿RT����ݡ��ͥ�Ȥ�null�ξ��ϡ�BAD_PARAMETER ���֤���롣
     * ���ꤵ�줿RT����ݡ��ͥ�Ȥ�DataFlowComponent�ʳ��ξ��ϡ�
     * BAD_PARAMETER ���֤���롣
     *
     * @param comp �ɲ��о�RT����ݡ��ͥ��
     *
     * @return �����¹Է��
     *
     * @else
     *
     * @brief Add a RT-component
     *
     * The operation causes the given RTC to begin participating in the
     * execution context.
     * The newly added RTC will receive a call to 
     * LightweightRTComponent::attach_context and then enter the Inactive state.
     *
     * @endif
     */
    virtual ReturnCode_t add(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ򻲲üԥꥹ�Ȥ���������
     *
     * ���ꤷ��RT����ݡ��ͥ�Ȥ򻲲üԥꥹ�Ȥ��������롣
     * ������줿RT����ݡ��ͥ�Ȥ� detach_context ���ƤФ�롣
     * ���ꤵ�줿RT����ݡ��ͥ�Ȥ����üԥꥹ�Ȥ���Ͽ����Ƥ��ʤ����ϡ�
     * BAD_PARAMETER ���֤���롣
     *
     * @param comp ����о�RT����ݡ��ͥ��
     *
     * @return �����¹Է��
     *
     * @else
     *
     * @brief Remove the RT-component from participant list
     *
     * This operation causes a participant RTC to stop participating in the
     * execution context.
     * The removed RTC will receive a call to
     * LightweightRTComponent::detach_context.
     *
     * @endif
     */
    virtual ReturnCode_t remove(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContextProfile ���������
     *
     * �� ExecutionContext �Υץ�ե������������롣
     *
     * @return ExecutionContextProfile
     *
     * @else
     *
     * @brief Get the ExecutionContextProfile
     *
     * This operation provides a profile ��descriptor�� for the execution 
     * context.
     *
     * @endif
     */
    virtual ExecutionContextProfile* get_profile()
      throw (CORBA::SystemException);
    
  protected:
    //============================================================
    // DFPBase
    //============================================================
    typedef LifeCycleState ExecContextState;
    /***
	enum ExecContextState
	{
	INACTIVE_STATE,
	ACTIVE_STATE,
	ERROR_STATE,
	};
    */
    typedef StateHolder<ExecContextState> ECStates;
    
    /*!
     * @if jp
     * @class DFPBase
     * @brief DFPBase ���饹
     *
     * ���üԥꥹ�Ȥ���Ͽ���줿 DataFlowParticipant ��������뤿�����ݥ��饹��
     *
     * @since 0.4.0
     *
     * @else
     *
     * @endif
     */
    class DFPBase
    {
    public:
      
      /*!
       * @if jp
       * @brief ���󥹥ȥ饯��
       *
       * ���󥹥ȥ饯��
       *
       * @param id ��°���� ExecutionContext ��ID
       *
       * @else
       * @brief Constructor
       * @endif
       */
      DFPBase(UniqueId id)
	: ec_id(id), m_sm(3)
      {
	m_sm.setListener(this);
	m_sm.setEntryAction (ACTIVE_STATE, &DFPBase::on_activated);
	m_sm.setDoAction    (ACTIVE_STATE, &DFPBase::on_execute);
	m_sm.setPostDoAction(ACTIVE_STATE, &DFPBase::on_state_update);
	m_sm.setExitAction  (ACTIVE_STATE, &DFPBase::on_deactivated);
	m_sm.setEntryAction (ERROR_STATE,  &DFPBase::on_aborting);
	m_sm.setDoAction    (ERROR_STATE,  &DFPBase::on_error);
	m_sm.setExitAction  (ERROR_STATE,  &DFPBase::on_reset);
	
	ECStates st;
	st.prev = INACTIVE_STATE;
	st.curr = INACTIVE_STATE;
	st.next = INACTIVE_STATE;
	m_sm.setStartState(st);
	m_sm.goTo(INACTIVE_STATE);
      }	
      
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
      virtual ~DFPBase(){}
      
      /*!
       * @if jp
       * @brief ExecutionContext �¹Գ��ϻ��˸ƤФ���貾�۴ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext ���¹Ԥ򳫻Ϥ����(Running���֤����ܻ�)
       * �˸ƤФ���貾�۴ؿ���
       *
       * @else
       *
       * @brief
       *
       * The given execution context, in which the RTC is participating, has 
       * transitioned from Stopped to Running.
       *
       * @endif
       */
      virtual void on_startup() = 0;
      
      /*!
       * @if jp
       * @brief ExecutionContext ��߻��˸ƤФ���貾�۴ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext ���¹Ԥ���ߤ����(Stopped���֤����ܻ�)
       * �˸ƤФ���貾�۴ؿ���
       *
       * @else
       *
       * @brief
       *
       * The given execution context, in which the RTC is participating, has 
       * transitioned from Running to Stopped.
       *
       * @endif
       */
      virtual void on_shutdown() = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ������ƥ��ֲ����줿���˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ������ƥ��ֲ����줿��
       * (Active���֤����ܻ�)�˸ƤФ���貾�۴ؿ���
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief
       *
       * The RTC has been activated in the given execution context.
       *
       * @endif
       */
      virtual void on_activated(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ����줿���˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ����줿��
       * (Deactive���֤����ܻ�)�˸ƤФ���貾�۴ؿ���
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief
       *
       * The RTC has been deactivated in the given execution context.
       *
       * @endif
       */
      virtual void on_deactivated(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥǥ��顼��ȯ���������˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ˥��顼��ȯ��������(Error���֤����ܻ�)
       * �˸ƤФ���貾�۴ؿ���
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief
       *
       * The RTC is transitioning from the Active state to the Error state 
       * in some execution context.
       *
       * @endif
       */
      virtual void on_aborting(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ����顼���֤λ��˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ����顼���֤ˤ���֡� on_execute ��
       * on_state_update ���ؤ�ä����Ū�˸ƤӽФ�����貾�۴ؿ���
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief
       *
       * If the RTC is in the Error state relative to some execution context
       * when it would otherwise be invoked from that context.
       * This operation shall be invoked in sorted order at the rate of the
       * context instead of DataFlowComponentAction::on_execute and 
       * on_state_update.The RTC is transitioning from the Active state to 
       * the Error state in some execution context.
       *
       * @endif
       */
      virtual void on_error(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ�ꥻ�åȤ�����˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ�ꥻ�åȤ���ݤ˸ƤФ���貾�۴ؿ���
       * ���δؿ�������˽�λ����ȡ�RTC�� Inactive ���֤��������롣
       * ���δؿ�������˽�λ���ʤ��ä����ϡ� Error ���֤�α�ޤ롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief
       *
       * The RTC is in the Error state. An attempt is being made to recover it 
       * such that it can return to the Inactive state.
       * If the RTC was successfully recovered and can safely return to 
       * the Inactive state, this method shall complete with ReturnCode_t::OK.
       * Any other result shall indicate that the RTC should remain in the 
       * Error state.
       *
       * @endif
       */
      virtual void on_reset(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�ȼ¹Ի������Ū�˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ� Active ���֤Ǥ���ȤȤ�ˡ�
       * ExecutionContext �� Running ���֤ξ��ˡ����ꤵ�줿ư����������Ū��
       * �ƤӽФ�����貾�۴ؿ���
       * Two-Pass Execution �κǽ�μ¹ԤǸƤФ�롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief
       *
       * This operation will be invoked periodically at the rate of the given
       * execution context as long as the following conditions hold:
       *  - The RTC is Active.
       *  - The given execution context is Running.
       * This callback occurs during the first execution pass.
       *
       * @endif
       */
      virtual void on_execute(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�ȼ¹Ի������Ū�˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ� Active ���֤Ǥ���ȤȤ�ˡ�
       * ExecutionContext �� Running ���֤ξ��ˡ����ꤵ�줿ư����������Ū��
       * �ƤӽФ�����貾�۴ؿ���
       * Two-Pass Execution �Σ����ܤμ¹ԤǸƤФ�롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief
       *
       * This operation will be invoked periodically at the rate of the given
       * execution context as long as the following conditions hold:
       *  - The RTC is Active.
       *  - The given execution context is Running.
       * This callback occurs during the second execution pass.
       *
       * @endif
       */
      virtual void on_state_update(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief ExecutionContext �μ¹Լ����ѹ����˸ƤФ���貾�۴ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext �μ¹Լ������ѹ��Ȥʤä����ˡ�
       * �����ѹ�����ã���뤿��˸ƤӽФ�����貾�۴ؿ���
       *
       * @else
       *
       * @brief
       *
       * This operation is a notification that the rate of the indicated
       * execution context has changed.
       *
       * @endif
       */
      virtual void on_rate_changed() = 0;
      
      /*!
       * @if jp
       * @brief �������ܤ�¹Ԥ����������������
       *
       * �����о�RT����ݡ��ͥ�Ȥξ������ܤ�¹Ԥ���������������롣
       *
       * @return �����
       *
       * @else
       *
       * @brief
       *
       * @endif
       */
      virtual void worker() {return m_sm.worker();}
      
      /*!
       * @if jp
       * @brief ���ߤξ��֤��������
       *
       * �����о�RT����ݡ��ͥ�Ȥθ��ߤξ��֤�������롣
       *
       * @return ���߾���
       *
       * @else
       *
       * @brief
       *
       * @endif
       */
      virtual ExecContextState get_state(){ return m_sm.getState();}
      
      /*!
       * @if jp
       * @brief ���ä��Ƥ��� ExecutionContext �� ID
       * @else
       *
       * @endif
       */
      UniqueId ec_id;
      
      /*!
       * @if jp
       * @brief �����о�RT����ݡ��ͥ�ȤΥ��ơ��ȥޥ���
       * @else
       *
       * @endif
       */
      StateMachine<ExecContextState, DFPBase> m_sm;
    };
    
    //============================================================
    // DFP
    //============================================================
    /*!
     * @if jp
     * @class DFP
     * @brief DFP ���饹
     *
     * ���üԥꥹ�Ȥ���Ͽ���줿 DataFlowParticipant �δؿ���ư���뤿���
     * �ƥ�ץ졼�ȥ��饹��
     *
     * @param Object �����оݥ���ݡ��ͥ�Ȥη�
     *
     * @since 0.4.0
     *
     * @else
     *
     * @endif
     */
    template <class Object>
    class DFP
      : public DFPBase
    {
    public:
      /*!
       * @if jp
       * @brief �ǥե���ȥ��󥹥ȥ饯��
       *
       * �ǥե���ȥ��󥹥ȥ饯��
       *
       * @param obj �����оݥ���ݡ��ͥ��
       * @param id ��°���� ExecutionContext ��ID
       *
       * @else
       * @brief Constructor
       * @endif
       */
      DFP(Object obj, UniqueId id)
	: DFPBase(id), m_obj(obj), m_active(true)
      {
      }
      
      /*!
       * @if jp
       * @brief ExecutionContext �¹Գ��ϻ��˸ƤФ��ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext ���¹Ԥ򳫻Ϥ����(Running���֤����ܻ�)
       * �ˡ������оݥ���ݡ��ͥ�Ȥ� on_startup ��ƤӤ�����
       *
       * @else
       *
       * @brief
       *
       * @endif
       */
      void on_startup()
      {
	m_obj->on_startup(ec_id);
      }
      
      /*!
       * @if jp
       * @brief ExecutionContext ��߻��˸ƤФ��ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext ���¹Ԥ���ߤ����(Stopped���֤����ܻ�)
       * �ˡ������оݥ���ݡ��ͥ�Ȥ� on_shutdown ��ƤӤ�����
       *
       * @else
       *
       * @endif
       */
      void on_shutdown()
      {
	m_obj->on_shutdown(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ������ƥ��ֲ����줿���˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ������ƥ��ֲ����줿��(Active���֤����ܻ�)
       * �ˡ������оݥ���ݡ��ͥ�Ȥ� on_activated ��ƤӤ�����
       * �����оݥ���ݡ��ͥ�ȤΥ����ƥ��ֲ������Ԥ������ˤϡ����ơ��ȥޥ���
       * �� Error ���֤����ܤ����롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @endif
       */
      void on_activated(const ECStates& st)
      {
	if (m_obj->on_activated(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }
	return;
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ����줿���˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ����줿��
       * (Deactive���֤����ܻ�)�ˡ������оݥ���ݡ��ͥ�Ȥ� on_deactivated ��
       * �ƤӤ�����
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @endif
       */
      void on_deactivated(const ECStates& st)
      {
	m_obj->on_deactivated(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥǥ��顼��ȯ���������˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ˥��顼��ȯ��������(Error���֤����ܻ�)
       * �˴����оݥ���ݡ��ͥ�Ȥ� on_aborting ��ƤӤ�����
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief
       *
       * @endif
       */
      void on_aborting(const ECStates& st)
      {
	m_obj->on_aborting(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ����顼���֤λ��˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ����顼���֤ˤ���֡� 
       * �����оݥ���ݡ��ͥ�Ȥ� on_aborting �����Ū�˸ƤӤ�����
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief
       *
       * @endif
       */
      void on_error(const ECStates& st)
      {
	m_obj->on_error(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ�ꥻ�åȤ�����˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ�ꥻ�åȤ���ݤˡ������оݥ���ݡ��ͥ��
       * �� on_reset ��ƤӤ�����
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @endif
       */
      void on_reset(const ECStates& st)
      {
	if (m_obj->on_reset(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }
	return;
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�ȼ¹Ի������Ū�˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ� Active ���֤Ǥ���ȤȤ�ˡ�
       * ExecutionContext �� Running ���֤ξ��ˡ����ꤵ�줿ư����������Ū��
       * �����оݥ���ݡ��ͥ�Ȥ� on_execute ��ƤӤ�����
       * �ؿ��μ¹Ԥ˼��Ԥ������(���ͤ� RTC_OK �ʳ�)�������оݥ���ݡ��ͥ�Ȥ�
       * ���֤� Error ���֤����ܤ����롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @endif
       */
      void on_execute(const ECStates& st)
      {
	if (m_obj->on_execute(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }  
	return;
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�ȼ¹Ի������Ū�˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ� Active ���֤Ǥ���ȤȤ�ˡ�
       * ExecutionContext �� Running ���֤ξ��ˡ����ꤵ�줿ư����������Ū��
       * �����оݥ���ݡ��ͥ�Ȥ� on_state_update ��ƤӤ�����
       * �ؿ��μ¹Ԥ˼��Ԥ������(���ͤ� RTC_OK �ʳ�)�������оݥ���ݡ��ͥ�Ȥ�
       * ���֤� Error ���֤����ܤ����롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @endif
       */
      void on_state_update(const ECStates& st)
      {
	if (m_obj->on_state_update(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }
	return;
      }
      
      /*!
       * @if jp
       * @brief ExecutionContext �μ¹Լ����ѹ����˸ƤФ��ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext �μ¹Լ������ѹ��Ȥʤä����ˡ�
       * �����оݥ���ݡ��ͥ�Ȥ� on_rate_changed ��ƤӤ�����
       *
       * @else
       *
       * @endif
       */
      void on_rate_changed()
      {
	m_obj->on_rate_changed(ec_id);
      }
      
      /*!
       * @if jp
       * @brief �����оݥ���ݡ��ͥ��
       * @else
       *
       * @endif
       */
      Object m_obj;
      
      /*!
       * @if jp
       * @brief �����оݥ���ݡ��ͥ�Ȥ�ư����֥ե饰
       * @else
       *
       * @endif
       */
      bool m_active;
    };
    
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȴ����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct Comp
    {
      Comp(LightweightRTObject_ptr ref, DataFlowComponent_ptr dfp,
	   UniqueId id)
	: _ref(ref), _sm(dfp, id)
      {
      }
      Comp(const Comp& comp)
	: _ref(comp._ref), _sm(comp._sm.m_obj, comp._sm.ec_id)
      {
      }
      Comp& operator=(const Comp& comp)
      {
	_ref = comp._ref;
	_sm.m_obj = comp._sm.m_obj;
	_sm.ec_id = comp._sm.ec_id;
	return *this;
      }
      LightweightRTObject_var _ref;
      DFP<DataFlowComponent_var> _sm;
    };
    
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȸ����ѥե��󥯥�
     * @else
     *
     * @endif
     */
    struct find_comp
    {
      LightweightRTObject_var m_comp;
      find_comp(LightweightRTObject_ptr comp) : m_comp(comp) {}
      bool operator()(Comp& comp)
      {
	return comp._ref->_is_equivalent(m_comp);
      }
    };
    
    /*!
     * @if jp
     * @brief on_startup ��ư�ѥե��󥯥�
     * @else
     *
     * @endif
     */
    struct invoke_on_startup
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_startup();
      }
    };
    
    /*!
     * @if jp
     * @brief on_shutdown ��ư�ѥե��󥯥�
     * @else
     *
     * @endif
     */
    struct invoke_on_shutdown
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_shutdown();
      }
    };
    
    /*!
     * @if jp
     * @brief on_rate_changed ��ư�ѥե��󥯥�
     * @else
     *
     * @endif
     */
    struct invoke_on_rate_changed
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_rate_changed();
      }
    };
    
    /*!
     * @if jp
     * @brief ������¹��ѥե��󥯥�
     * @else
     *
     * @endif
     */
    struct invoke_worker
    {
      void operator()(Comp& comp)
      {
	comp._sm.worker();
      }
    };
    
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�Ȥλ��üԥꥹ��
     * @else
     *
     * @endif
     */
    std::vector<Comp> m_comps;
    typedef std::vector<Comp>::iterator CompItr;
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Ծ���
     * @else
     *
     * @endif
     */
    bool m_running;
    
    /*!
     * @if jp
     * @brief ExecutionContextProfile
     * @else
     *
     * @endif
     */
    ExecutionContextProfile m_profile;
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Լ���
     * @else
     *
     * @endif
     */
    long int m_usec;
    
    /*!
     * @if jp
     * @brief ExecutionContextService ���֥������Ȥؤλ���
     * @else
     *
     * @endif
     */
    ExecutionContextService_var m_ref;
    
    /*!
     * @if jp
     * @brief ExecutionContext ¨���¹�(wait̵���¹�)�ե饰
     * @else
     *
     * @endif
     */
    bool m_nowait;
  }; // class PeriodicExecutionContext
}; // namespace RTC

extern "C"
{
  void PeriodicExecutionContextInit(RTC::Manager* manager);
};

#endif
