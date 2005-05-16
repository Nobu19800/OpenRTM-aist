// -*- C++ -*-
/*!
 * @file RtcBase.h
 * @brief RT component base class
 * @date $Date: 2005-05-16 06:02:49 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcBase.h,v 1.2 2005-05-16 06:02:49 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcBase_h
#define RtcBase_h

// CORBA header include
#include "rtm/RTC.h"

// STL includes
#include <list>
#include <string>
#include <algorithm>
#include <functional>

// ACE
#include <ace/Task.h>

// local includes 
#include "rtm/idl/RTCBaseSkel.h"
#include "rtm/idl/RTCBaseStub.h"
#include "rtm/RtcOutPort.h"
#include "rtm/RtcModuleProfile.h"
#include "rtm/RtcSystemLogger.h"

#define USLEEP(x) \
{ \
  ACE_Time_Value tv(0, x);\
  ACE_OS::sleep(tv);\
}

namespace RTM {
  // namespace
  using namespace std;
  
  
  class InPortBase;
  class OutPortBase;
  class RtcManager;
  
  static char* StateString[] =
	{
	  "RTC_UNKNOWN",
	  "RTC_BORN",
	  "RTC_INITIALIZING",
	  "RTC_READY",
	  "RTC_STARTING",
	  "RTC_ACTIVE",
	  "RTC_STOPPING",
	  "RTC_ABORTING",
	  "RTC_ERROR",
	  "RTC_FATAL_ERROR",
	  "RTC_EXITING",
	  "UNKNOWN"
	};

  /*!
   * @if jp
   * @brief RTComponent ���ַ������
   * @else
   * @brief RTComponent state re-declaration
   * @endif
   */
  typedef RTM::RTComponent::ComponentState ComponentState;
  
  const ComponentState RTC_UNKNOWN      = 0; //RTM::RTComponent::RTC_UNKNOWN;
  const ComponentState RTC_BORN         = 1; //RTM::RTComponent::RTC_BORN;
  const ComponentState RTC_INITIALIZING = 2; //RTM::RTComponent::RTC_INITIALIZING;
  const ComponentState RTC_READY        = 3; //RTM::RTComponent::RTC_READY;
  const ComponentState RTC_STARTING     = 4; //RTM::RTComponent::RTC_STARTING;
  const ComponentState RTC_ACTIVE       = 5; //RTM::RTComponent::RTC_ACTIVE;
  const ComponentState RTC_STOPPING     = 6; //RTM::RTComponent::RTC_STOPPING;
  const ComponentState RTC_ABORTING     = 7; //RTM::RTComponent::RTC_ABORTING;
  const ComponentState RTC_ERROR        = 8; //RTM::RTComponent::RTC_ERROR;
  const ComponentState RTC_FATAL_ERROR  = 9; //RTM::RTComponent::RTC_FATAL_ERROR;
  const ComponentState RTC_EXITING      = 10;//RTM::RTComponent::RTC_EXITING;

  typedef enum NamingPolicy {
	UNKNOWN = 0,
	LONGNAME_ENABLE = 1,
	ALIAS_ENABLE = 2
  };

  /*!
   * @if jp
   *
   * @class RtcBase
   *
   * @brief RTComponent ���쥯�饹
   *
   * RTComponent ��ȯ�ԤϿ����˺������륳��ݡ��ͥ�ȤΥ��饹�򤳤�RtcBase��
   * ���֥��饹�Ȥ���������ʤ���Фʤ�ʤ���
   * �����˺������륳��ݡ��ͥ�Ȥˤ����ơ�ɬ�פʥ����ƥ��ӥƥ��ξ��֤��б�����
   * �᥽�å� rtc_active_do() ����Ŭ�������С��饤�ɤ��ơ��ƾ��֤ˤƹԤ�������
   * ���Υ᥽�åɤ˵��Ҥ��롣
   * rtc_xxx_entry(), rtc_xxx_exit() �ǤϤ��ξ��֤�����Ȥ��ȽФ�Ȥ��˰��٤���
   * �����Υ᥽�åɤ��¹Ԥ��졢rtc_xxx_do() �ǤϤ��ξ��֤ˤ�����桢���Υ᥽
   * �åɤ������¹Ԥ���롣
   * �ƥ᥽�å� rtc_xxx_[entry|do|exit]() �Ǥ�����ͤ� RTM_OK, RTM_ERR, 
   * RTM_WARNING, RTM_FATAL_ERR �Τ����줫���֤���
   * RTM_ERR ���֤��� ERROR ���֤ˡ�RTM_FATAL_ERR ���֤��� FATAL_ERROR ���֤�
   * �ܹԤ��롣����¾�ξ������ܤˤĤ��Ƥϥޥ˥奢��򻲾ȡ�
   * 
   * �����˺������륳��ݡ��ͥ�ȤΥ��饹�Ǥϡ� InPort , OutPort �Ȥ����
   * �Х���ɤ���� InPort , OutPort �η����б������ѿ���������롣
   * ����ݡ��ͥ�ȤΥ��饹�Υ��󥹥ȥ饯���Ǥϡ��������ѿ��������Ҥ��Ѥ���
   * ������������󥹥ȥ饯����� registerInPort , registerOutPort ���Ѥ���
   * ���줾�� InPort , OutPort �Ȥ�����Ͽ����ɬ�פ����롣
   *
   * @else
   *
   * @class RtcBase
   *
   * @brief RT component base class.
   *
   * RT-component developer should derive this base class to create own RT
   * component class.
   * Procedure is as follows.
   *
   * In your RT-conponent class, you have to define input variable and output
   * variable. Input channel and output channel also should be defined as 
   * InPort<T> objects or OutPort<T> objects. These variables and channel
   * objects should be bound each other in the constructor.
   *
   * In the constructor of your component class, input channel objects and 
   * output channel objects have to make registration as CORBA objects using
   * registerInPort , registerOutPort method.
   *
   * @endif
   */
  class EXPORTS RtcBase  
	: public virtual POA_RTM::RTCBase, 
      public virtual PortableServer::RefCountServantBase,
      public ACE_Task<ACE_MT_SYNCH>
  {
  public:

	/*!
	 * @if jp
	 * @brief RtcBase ���饹���󥹥ȥ饯��
	 *
	 * RTComponent �����Х�ȼ����δ��쥯�饹 RtcBase �Υ��󥹥ȥ饯����
	 * ���Υ��󥹥ȥ饯������Ѥ����硢�桼����ORB�ؤΥݥ��󥿤�POA�Υݥ���
	 * ���뤤�ϡ��ޥ͡�����ؤΥݥ��󥿤��ǥ��åȤ���ɬ�פ����롣
	 *
	 * @else
	 *
	 * @brief A constructor of RtcBase class.
	 *
	 * Constructor of RtcBase which is RTComponent servant implementation
	 * base classes without arguments.
	 * If use this constructor, user have to set the ORB pointer and a POA
	 * pointer or a pointer to RtcManager.
	 *
	 * @endif
	 */
	RtcBase();
	
	/*!
	 * @if jp
	 * @brief RtcBase ���饹���󥹥ȥ饯��
	 *
	 * RTComponent �����Х�ȼ����δ��쥯�饹 RtcBase �Υ��󥹥ȥ饯����
	 *
	 * ORB �ؤΥݥ��󥿤�POA�ؤΥݥ��󥿤����Ǥ������Ƥ�����ˤϡ�����
	 * ���󥹥ȥ饯������Ѥ��뤳�Ȥ�����롣
	 *
	 * @param orb ORB �ؤΥݥ���
	 * @param poa POA �ؤΥݥ���
	 *
	 * @else
	 *
	 * @brief A constructor of RtcBase class.
	 *
	 * If the ORB pointer and a POA pointer are already available, user can use
	 * this constructor.
	 *
	 * @param orb pointer to ORB
	 * @param poa pointer to POA
	 *
	 * @endif
	 */
	RtcBase(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);

	/*!
	 * @if jp
	 *
	 * @brief RtcBase ���饹���󥹥ȥ饯��
	 *
	 * �̾�ϥޥ͡�������̤��ƥ���ݡ��ͥ�ȥ��饹�򥤥󥹥��󥹲�����
	 * ���Υ��󥹥ȥ饯������Ѥ��뤳�Ȥ�侩���롣
	 *
	 * @param manager ����ݡ��ͥ�ȥޥ͡����� RtcManager �ؤΥݥ���
	 *
	 * @else
	 *
	 * @brief A constructor.
	 *
	 * @param manager pointer to component manager: RtcManager
	 * @endif
	 */
	RtcBase(RtcManager* manager);
	
	/*!
	 * @if jp
	 * 
	 * @brief RtcBase ���饹�ǥ��ȥ饯��
	 *
	 * @else
	 *
	 * @brief A destructor of RtcBase class.
	 *
	 * @endif
	 */
	virtual ~RtcBase();
	
	//============================================================
	//
	// <<< CORBA interfaces >>>
	//
	//============================================================
	
	//============================================================
	// State implementation functions 
	//============================================================
	/*
	 * 
	 *                                   __                      __
	 *                         _________V_ \          __________V_ \
	 *                        |           |/  (any)->|            |/
	 *                        |  Active   |          | FatalError |
	 *                        |___________|--,       |____________|
	 *                            A    |  ___|______      |
	 *                      ______|___ | |          |     |
	 *                     |          || | Aborting |     |
	 *                     | Starting || |__________|     |
	 *                     |__________||     |   __       |
	 *             ____________   |    |   __V__V_ \   ___V_____
	 *   _____    |            |<-+----+--|       |/  |         |    ___
	 *  (Start)-->|Initializing|  |    |  | Error |-->| Exiting |-->(End)
	 *   ~~~~~    |____________|--+----+->|_______|   |_________|    ~~~
	 *                A  |        | ___|______  A         A
	 *                |  |        ||          | |         |
	 *                |  |        || Stopping | |         |
	 *                |  |        ||__________| |         |
	 *                |  |        |    |        |         |
	 *                |  |     ___|____V__      |         |
	 *                |  `--->|           |-----'         |
	 *                `-------|   Ready   |               |
	 *                       /|___________|---------------'
	 *                       \__A
	 *
	 */
	
	//------------------------------------------------------------
	// Transition operation of component activity state
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] ����ݡ��ͥ�ȤΥ����ƥ��ֲ�
	 *
	 * ����ݡ��ͥ�Ȥξ��֤� READY ���� ACTIVE �����ܤ����롣
	 * ���Υ��ڥ졼������ȯ�Ԥ���Ȥ�������ݡ��ͥ�Ȥ� READY ���֤Ǥʤ����
	 * �ʤ�ʤ���¾�ξ��֤ξ��ˤ� IllegalTransition �㳰��ȯ�����롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Activate this components' activity
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_start()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition);
	
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] ����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ�
	 *
	 * ����ݡ��ͥ�Ȥξ��֤� ACTIVE ���� READY �����ܤ����롣
	 * ���Υ��ڥ졼������ȯ�Ԥ���Ȥ�������ݡ��ͥ�Ȥ� ACTIVE ���֤Ǥʤ����
	 * �ʤ�ʤ���¾�ξ��֤ξ��ˤ� IllegalTransition �㳰��ȯ�����롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Stop this component's activity
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_stop()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition);
	
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] ����ݡ��ͥ�ȤΥꥻ�å�
	 *
	 * ����ݡ��ͥ�Ȥξ��֤� ERROR ���� INITIALIZE �����ܤ����롣
	 * INITIALIZE �奨�顼���ʤ���Ф����� READY ���֤����ܤ��롣
	 * ���Υ��ڥ졼������ȯ�Ԥ���Ȥ�������ݡ��ͥ�Ȥ� ERROR ���֤Ǥʤ����
	 * �ʤ�ʤ���¾�ξ��֤ξ��ˤ� IllegalTransition �㳰��ȯ�����롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Go to init() state from error() state
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_reset()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition);
	
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] ����ݡ��ͥ�ȤΥꥻ�å�
	 *
	 * ����ݡ��ͥ�Ȥξ��֤� EXITING �����ܤ����롣
	 * EXITING ���֤����ܤ�������ݡ��ͥ�Ȥ����٤��������뤳�Ȥʤ���λ���롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Go to term() state from anywhere
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_exit()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition);
	
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] ����ݡ��ͥ�Ȥζ�����λ
	 *
	 * FATAL_ERROR ���֤Υ���ݡ��ͥ�Ȥ� EXITING �����ܤ����롣
	 * EXITING ���֤����ܤ�������ݡ��ͥ�Ȥ����٤��������뤳�Ȥʤ���λ���롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Go to exiting() state from active() state 
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_kill();
	
	//------------------------------------------------------------
	// Main activity
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] �ᥤ�󥢥��ƥ��ӥƥ��Υ᥽�å�
	 *
	 * ����ݡ��ͥ�ȤΥ����ƥ��ӥƥ������ΤϤ��Υ᥽�åɤ�����¹Ԥ��뤳�Ȥ�
	 * ����������롣ñ�ΤΥ���ݡ��ͥ�ȤǤ�����Ū�ʥ���åɤˤ�ꤳ�Υ᥽
	 * �åɤ�����ƽФ��뤳�Ȥǽ�����ԤäƤ��롣
	 * ����åɤ���ߤ������������餳�Υ��ڥ졼������ƤӽФ����Ȥˤ�ꡢǤ
	 * �դΥ����ߥ󥰤ǥ����ƥ��ӥƥ���¹Ԥ��뤳�Ȥ����롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Main activity function. 
	 *
	 * Called from activity thread periodically.
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_worker();
	
	
	// ** Steady state **
	//------------------------------------------------------------
	// Ready state methods
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: ready() �᥽�å�
	 *
	 * READY ���֤ؿ�������Ȥ���1�٤����ƤӽФ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: ready() method.
	 *
	 * This method will be called once when component enter
	 * to Ready state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_ready_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] do: ready() �᥽�å�.
	 *
	 * READY ���֤ˤ���ּ����¹Ԥ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] do: ready() method.
	 *
	 * This method will be called repeatedly when component state is Ready.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_ready_do()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] exit: ready() �᥽�å�.
	 *
	 * READY ���֤���Ф�Ȥ���1�٤����¹Ԥ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] exit: ready() method.
	 *
	 * This method will be called once when component exit from Ready state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_ready_exit()
	{USLEEP(1000); return RTM_OK;};
	
	
	//------------------------------------------------------------
	// Active state methods
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: active() �᥽�å�.
	 *
	 * ACTIVE ���֤˿�������Ȥ���1�٤����¹Ԥ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: active() method.
	 *
	 * This method will be called once when component enter to Active state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_active_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] do: active() �᥽�å�.
	 *
	 * ACTIVE ���֤˵��ּ����¹Ԥ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] do: active() method.
	 *
	 * This method will be called repeatedly when component state is Active.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_active_do()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] exit: active() �᥽�å�.
	 *
	 * ACTIVE ���֤���Ф�Ȥ���1�٤����¹Ԥ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] exit: active() method.
	 *
	 * This method will be called once when component exit from Active state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_active_exit()
	{USLEEP(1000); return RTM_OK;};
	
	
	//------------------------------------------------------------
	// Error state methods
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: error() �᥽�å�
	 *
	 * ERROR ���֤ؿ�������Ȥ���1�٤����ƤӽФ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: error() method.
	 *
	 * This method will be called once when component enter to Error state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_error_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] do: error() �᥽�å�.
	 *
	 * ERROR ���֤ˤ���ּ����¹Ԥ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] do: ready() method.
	 *
	 * This method will be called repeatedly when component state is Error.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_error_do()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] exit: error() �᥽�å�.
	 *
	 * ERROR ���֤���Ф�Ȥ���1�٤����¹Ԥ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] exit: error() method.
	 *
	 * This method will be called once when component exit from Error state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_error_exit()
	{USLEEP(1000); return RTM_OK;};
	
	
	//------------------------------------------------------------
	// FatalError state methods
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: fatal() �᥽�å�
	 *
	 * FATAL_ERROR ���֤ؿ�������Ȥ���1�٤����ƤӽФ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: fatal() method.
	 *
	 * This method will be called once when component enter to FATAL_ERROR
	 * state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_fatal_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] do: fatal() �᥽�å�.
	 *
	 * FATAL_ERROR ���֤ˤ���ּ����¹Ԥ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] do: fatal() method.
	 *
	 * This method will be called repeatedly when component state is
	 * FATAL_ERROR state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_fatal_do()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] exit: fatal() �᥽�å�.
	 *
	 * READY ���֤���Ф�Ȥ���1�٤����¹Ԥ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] exit: fatal() method.
	 *
	 * This method will be called once when component exit from FATAL_ERROR
	 * state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_fatal_exit()
	{USLEEP(1000); return RTM_OK;};
	//------------------------------------------------------------
	
	// ** Transient state **
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: init() �᥽�å�
	 *
	 * INITIALIZING ���֤ؿ�������Ȥ���1�٤����ƤӽФ����᥽�åɡ�
	 * ���顼���ʤ���� READY ���֤����ܤ��롣
	 * ����ͤ� RTM_ERR �� ERROR ���֤ء� RTM_FATALERR �� FATAL_ERROR ���֤�
	 * ���ܤ��롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: ready() method.
	 *
	 * This method will be called and move to Ready/Error state immediately.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_init_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: starting() �᥽�å�
	 *
	 * STARTING ���֤ؿ�������Ȥ���1�٤����ƤӽФ����᥽�åɡ�
	 * ���顼���ʤ���� ACTIVE ���֤����ܤ��롣
	 * ����ͤ� RTM_ERR �� ERROR ���֤ء� RTM_FATALERR �� FATAL_ERROR ���֤�
	 * ���ܤ��롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: starting() method.
	 *
	 * This method will be called and move to Active state immediately.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_starting_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: stopping() �᥽�å�
	 *
	 * STOPPING ���֤ؿ�������Ȥ���1�٤����ƤӽФ����᥽�åɡ�
	 * ���顼���ʤ���� READY ���֤����ܤ��롣
	 * ����ͤ� RTM_ERR �� ERROR ���֤ء� RTM_FATALERR �� FATAL_ERROR ���֤�
	 * ���ܤ��롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: stopping() method.
	 *
	 * This method will be called and move to Ready state immediately.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_stopping_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: aborting() �᥽�å�
	 *
	 * ABORTING ���֤ؿ�������Ȥ���1�٤����ƤӽФ����᥽�åɡ�
	 * ���顼���ʤ���� READY ���֤����ܤ��롣
	 * ����ͤ� RTM_ERR �� ERROR ���֤ء� RTM_FATALERR �� FATAL_ERROR ���֤�
	 * ���ܤ��롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: aborting() method.
	 *
	 * This method will be called and move to Error state immediately.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_aborting_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: exiting() �᥽�å�
	 *
	 * EXITING ���֤ؿ�������Ȥ���1�٤����ƤӽФ����᥽�åɡ�
	 * ���顼���ʤ���� READY ���֤����ܤ��롣
	 * ����ͤ� RTM_ERR �� ERROR ���֤ء� RTM_FATALERR �� FATAL_ERROR ���֤�
	 * ���ܤ��롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: exiting() method.
	 *
	 * This method will be called and terminate component.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_exiting_entry()
	{USLEEP(1000); return RTM_OK;};
	
	
	//------------------------------------------------------------
	// Status handling
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] �����ƥ��ӥƥ����ơ�������OutPort�μ���
	 *
	 * �����ƥ��ӥƥ����ơ�������OutPort�Υ��֥������ȥ�ե���󥹤�������롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get activity status OutPort
	 *
	 * @endif
	 */
	virtual OutPort_ptr rtc_state();
	
	//------------------------------------------------------------
	// Get inports and outport object reference
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] InPortList �μ���
	 *
	 * InPort �Υ��֥������ȥ�ե���󥹤Υꥹ�Ȥ�������롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Return input port object reference list
	 *
	 * @endif
	 */
	virtual InPortList* inports() ;

	/*!
	 * @if jp
	 * @brief [CORBA interface] InPort �μ���
	 *
	 * InPort �Υ��֥������ȥ�ե���󥹤�������롣
	 *
	 * @param name InPort ̾
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Return input port object reference
	 *
	 * @param name InPort name
	 *
	 * @endif
	 */
	virtual InPort_ptr get_inport(const char* name)
	  throw (CORBA::SystemException, RTM::RTComponent::NoSuchName); 
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPortList �μ���
	 *
	 * OutPort �Υ��֥������ȥ�ե���󥹤Υꥹ�Ȥ�������롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Return output port object reference list
	 *
	 * @endif
	 */
	virtual OutPortList* outports() ;

	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPort �μ���
	 *
	 * OutPort �Υ��֥������ȥ�ե���󥹤�������롣
	 *
	 * @param name OutPort ̾
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Return output port object reference
	 *
	 * @param name OutPort name
	 *
	 * @endif
	 */
	virtual OutPort_ptr get_outport(const char* name)
	  throw (CORBA::SystemException, RTM::RTComponent::NoSuchName);
	
	//------------------------------------------------------------
	// [CORBA interface] Getting component property
	//------------------------------------------------------------
	//  CORBA::Any* get_property(const char* name) {return NULL;};
	//  char* get_properties_xml() {return NULL;};
	//  virtual char* instance_name() {return "RtcBase0";}
	//  virtual char* class_name() {return "RtcBase";}

	/*!
	 * @if jp
	 * @brief [CORBA interface] instance_id �μ���
	 *
	 * ����ݡ��ͥ�ȤΥ��󥹥���ID��������롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get instance_id
	 *
	 * @endif
	 */
	virtual char* instance_id();

	/*!
	 * @if jp
	 * @brief [CORBA interface] implementation_id �μ���
	 *
	 * ����ݡ��ͥ�ȤΥ���ץ���ơ������ID��������롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get implementation_id
	 *
	 * @endif
	 */
    virtual char* implementation_id();

	/*!
	 * @if jp
	 * @brief [CORBA interface] description �μ���
	 *
	 * ����ݡ��ͥ�Ȥγ���������������롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get description
	 *
	 * @endif
	 */
    virtual char* description();

	/*!
	 * @if jp
	 * @brief [CORBA interface] version �μ���
	 *
	 * ����ݡ��ͥ�ȤΥС�������������롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get version
	 *
	 * @endif
	 */
    virtual char* version();

	/*!
	 * @if jp
	 * @brief [CORBA interface] maker �μ���
	 *
	 * ����ݡ��ͥ�Ȥκ����Ԥ�������롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get maker
	 *
	 * @endif
	 */
    virtual char* maker();

	/*!
	 * @if jp
	 * @brief [CORBA interface] category �μ���
	 *
	 * ����ݡ��ͥ�ȤΥ��ƥ����������롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get category
	 *
	 * @endif
	 */
    virtual char* category();

	/*!
	 * @if jp
	 * @brief [CORBA interface] profile �μ���
	 *
	 * ����ݡ��ͥ�ȤΥץ�ե������������롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get profile
	 *
	 * @endif
	 */
	virtual RTCProfile* profile() ;
	//	virtual RTCConfiguration* configuration() ;

	
	
	//------------------------------------------------------------
	// [CORBA interface] composit component interfaces
	//
	// These interfaces are methods for RTCompositComponet
	// Almost all methods do nothing. Only rtc_components and 
	// rtc_get_componet methods return this component itself.
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] �����ƥ��ӥƥ�����åɤΥ�������
	 *
	 * ����ݡ��ͥ�ȥ����ƥ��ӥƥ�����������åɤ򥹥����Ȥ�����
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Start activity internal thread
	 *
	 * @endif
	 */
	virtual RtmRes rtc_start_thread();

	/*!
	 * @if jp
	 * @brief [CORBA interface] �����ƥ��ӥƥ�����åɤΥ����ڥ��
	 *
	 * ����ݡ��ͥ�ȥ����ƥ��ӥƥ�����������åɤ򥵥��ڥ�ɤ�����
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Suspend activity internal thread
	 *
	 * @endif
	 */
	virtual RtmRes rtc_suspend_thread();

	/*!
	 * @if jp
	 * @brief [CORBA interface] �����ƥ��ӥƥ�����åɤΥ��ȥå�
	 *
	 * ����ݡ��ͥ�ȥ����ƥ��ӥƥ�����������åɤ򥹥ȥåפ�����
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Stop activity internal thread
	 *
	 * @endif
	 */
	virtual RtmRes rtc_stop_thread();

	/*!
	 * @if jp
	 * @brief [CORBA interface] �ƥ���ݡ��ͥ�Ȥ򥻥åȤ���
	 *
	 * �ƥ���ݡ��ͥ�ȤΥ��֥������ȥ�ե���󥹤򥻥åȤ��롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Set parent component
	 *
	 * @endif
	 */
	virtual RtmRes rtc_set_parent(RTCBase_ptr comp);

	/*!
	 * @if jp
	 * @brief [CORBA interface] �ҥ���ݡ��ͥ�Ȥ��ɲä���
	 *
	 * �ҥ���ݡ��ͥ�ȤΥ��֥������ȥ�ե���󥹤򥻥åȤ��롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥ��Υ᥽�åɤ�̤���ѤΤ��ᡢRTM_ERR ���֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Set child component
	 *
	 * @endif
	 */
	virtual RtmRes rtc_add_component(RTCBase_ptr comp)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] �ҥ���ݡ��ͥ�Ȥ�������
	 *
	 * �ҥ���ݡ��ͥ�ȤΥ��֥������ȥ�ե���󥹤������롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥ��Υ᥽�åɤ�̤���ѤΤ��ᡢRTM_ERR ���֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Delete child component
	 *
	 * @endif
	 */
	virtual RtmRes rtc_delete_component(RTCBase_ptr comp)
	{return RTM_ERR;} ;

	/*!
	 * @if jp
	 * @brief [CORBA interface] �ҥ���ݡ��ͥ�Ȥν���������ؤ���
	 *
	 * 2�Ĥλҥ���ݡ��ͥ�Ȥ򥪥֥������ȥ�ե���󥹤���Ѥ��ƽ���������ؤ�
	 * �롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥ��Υ᥽�åɤ�̤���ѤΤ��ᡢRTM_ERR ���֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Replace two child components
	 *
	 * @endif
	 */
	virtual RtmRes rtc_replace_component(RTCBase_ptr comp1, RTCBase_ptr comp2)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] �ҥ���ݡ��ͥ�Ȥν���������ؤ���
	 *
	 * 2�Ĥλҥ���ݡ��ͥ�Ȥν���򥳥�ݡ��ͥ��̾����ꤷ�������ؤ��롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥ��Υ᥽�åɤ�̤���ѤΤ��ᡢRTM_ERR ���֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Replace two child components
	 *
	 * @endif
	 */
	virtual RtmRes rtc_replace_component_by_name(const char* name1, const char* name2)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] �ҥ���ݡ��ͥ�Ȥ�ꥹ�ȤȤ��Ƽ������롣
	 *
	 * �ҥ���ݡ��ͥ�ȤΥꥹ�Ȥ�������롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥϼ�ʬ���ȥ��֥������ȥ�ե���󥹤��֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RTCBaseList* rtc_components()
	{
	  RTCBaseList_var myself = new RTCBaseList();
	  myself->length(1);

#ifdef ORB_IS_TAO
	  (*myself)[0] = RTM::RTCBase::_narrow(m_pPOA->servant_to_reference(this));
#else
	  myself[0] = RTM::RTCBase::_narrow(m_pPOA->servant_to_reference(this));
#endif
	  return myself._retn();
	};

	/*!
	 * @if jp
	 * @brief [CORBA interface] �ҥ���ݡ��ͥ�Ȥ�̾������ꤷ�Ƽ���
	 *
	 * �ҥ���ݡ��ͥ�Ȥ�̾������ꤷ�Ƥ��Υ��֥������ȥ�ե���󥹤�������롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥϼ�ʬ���ȥ��֥������ȥ�ե���󥹤��֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RTCBase_ptr rtc_get_component(const char* name)
	{
	  return dynamic_cast<RTCBase_ptr>(m_pPOA->servant_to_reference(this));
	};

	/*!
	 * @if jp
	 * @brief [CORBA interface] InPort�򥢥��å�����
	 *
	 * �ҥ���ݡ��ͥ�Ȥ�InPort�򤳤Υ���ݡ��ͥ�Ȥ�InPort�˥����å����롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥϼ�ʬ���ȥ��֥������ȥ�ե���󥹤��֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_attach_inport(InPort_ptr in_port)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] InPort�򥢥��å�����
	 *
	 * �ҥ���ݡ��ͥ�Ȥ�InPort̾����ꤷ�ƥ���ݡ��ͥ�Ȥ�InPort�˥����å�
	 * ���롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥϼ�ʬ���ȥ��֥������ȥ�ե���󥹤��֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_attach_inport_by_name(RTCBase_ptr comp, const char* name)
	{return RTM_ERR;};


	/*!
	 * @if jp
	 * @brief [CORBA interface] InPort��ǥ��å�����
	 *
	 * �ҥ���ݡ��ͥ�Ȥ�InPort�򤳤Υ���ݡ��ͥ�Ȥ�InPort����ǥ��å����롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥ� RTM_ERR ���֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_detatch_inport(InPort_ptr in_port)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] InPort��ǥ��å�����
	 *
	 * �ҥ���ݡ��ͥ�Ȥ�InPort��̾������ꤷ�Ƥ��Υ���ݡ��ͥ�Ȥ�InPort����
	 * �ǥ��å����롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥ� RTM_ERR ���֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_detatch_inport_by_name(const char* name)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPort�򥢥��å�����
	 *
	 * �ҥ���ݡ��ͥ�Ȥ�OutPort�򤳤Υ���ݡ��ͥ�Ȥ�OutPort�˥����å����롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥϼ�ʬ���ȥ��֥������ȥ�ե���󥹤��֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_attach_outport(OutPort_ptr out_port)
	{return RTM_ERR;} ;

	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPort�򥢥��å�����
	 *
	 * �ҥ���ݡ��ͥ�Ȥ�OutPort̾����ꤷ�ƥ���ݡ��ͥ�Ȥ�InPort�˥����å�
	 * ���롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥϼ�ʬ���ȥ��֥������ȥ�ե���󥹤��֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_attach_outport_by_name(RTCBase_ptr comp,
											  const char* name)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPort��ǥ��å�����
	 *
	 * �ҥ���ݡ��ͥ�Ȥ�OutPort�򤳤Υ���ݡ��ͥ�Ȥ�OutPort����ǥ��å����롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥ� RTM_ERR ���֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_detatch_outport(OutPort_ptr out_port)
	{return RTM_ERR;}

	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPort��ǥ��å�����
	 *
	 * �ҥ���ݡ��ͥ�Ȥ�OutPort��̾������ꤷ�Ƥ��Υ���ݡ��ͥ�Ȥ�OutPort����
	 * �ǥ��å����롣
	 * ñ�Υ���ݡ��ͥ�Ȥˤ����Ƥ� RTM_ERR ���֤���
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_detatch_outport_by_name(const char* name)
	 {return RTM_ERR;};
	
	// end of CORBA interface definition
	//============================================================
	
	
	
	//============================================================
	//
	// <<< Local interfaces >>>
	//
	//============================================================
	
	/*!
	 * @if jp
	 * @brief ORB, POA �Υݥ��󥿤�Ϳ���ƽ��������
	 *
	 * ����ݡ��ͥ�Ȥ�ORB��POA�Υݥ��󥿤�Ϳ���ƥ���ݡ��ͥ�Ȥ��������롣
	 *
	 * @param orb ORB �ؤΥݥ���
	 * @param poa POA �ؤΥݥ���
	 *
	 * @else
	 *
	 * @brief Initialize this component with ORB and POA pointer
	 *
	 * @param orb pointer to ORB
	 * @param poa pointer to POA
	 *
	 * @endif
	 */
	virtual void init_orb(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
	
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȤΥ����ƥ��ӥƥ�����åɤ���������
	 *
	 * ����ݡ��ͥ�Ȥ����������ƥ��ӥƥ�����åɤ���������ư���롣
	 * ����� ACE_Task �����ӥ����饹�᥽�åɤΥ����С��饤�ɡ�
	 *
	 * @param args �̾��0
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
	 * @brief ����ݡ��ͥ�ȤΥ����ƥ��ӥƥ�����åɴؿ�
	 *
	 * ����ݡ��ͥ�Ȥ����������ƥ��ӥƥ�����åɤμ¹Դؿ���
	 * ����� ACE_Task �����ӥ����饹�᥽�åɤΥ����С��饤�ɡ�
	 *
	 * @else
	 *
	 * @brief Create internal activity thread
	 *
	 * Run by a daemon thread to handle deferred processing.
	 * ACE_Task class method override.
	 *
	 * @endif
	 */	
	virtual int svc(void);
	

	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȤΥ����ƥ��ӥƥ�����åɽ�λ�ؿ�
	 *
	 * ����ݡ��ͥ�Ȥ����������ƥ��ӥƥ�����åɽ�λ���˸ƤФ�롣
	 * ����ݡ��ͥ�ȥ��֥������Ȥ��󥢥��ƥ��ֲ����ޥ͡�����ؤ����Τ�Ԥ���
	 * ����� ACE_Task �����ӥ����饹�᥽�åɤΥ����С��饤�ɡ�
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

	/*!
	 * @if jp
	 *
	 * @brief ����ݡ��ͥ�ȥ��ơ��ȼ���
	 *
	 * ����ݡ��ͥ�Ȥθ��ߤξ��֤�������롣
	 *
	 * @else
	 *
	 * @brief Get current component state
	 *
	 * @endif
	 */
	virtual RTM::RTComponent::ComponentState getState();

	//============================================================
	// Component Property handling methods
	//============================================================
	// @brief Get component class name.

	/*!
	 * @if jp
	 *
	 * @brief ModuleProfile �ν����
	 *
	 * RtcModuleProfile ���饹�Υ��󥹥��󥹤��Ϥ��ơ�����ݡ��ͥ�Ȥ�
	 * �ץ�ե�������������롣
	 *
	 * @param RtcModuleProfSpec �⥸�塼��ץ�ե�����
	 *
	 * @else
	 *
	 * @brief Initialize RtcModuleProfile
	 *
	 * @param RtcModuleProfile module profile
	 *
	 * @endif
	 */
	virtual void initModuleProfile(RtcModuleProfile prof);

	/*!
	 * @if jp
	 *
	 * @brief ModuleProfile �μ���
	 *
	 * ModuleProfile ��������롣
	 *
	 * @else
	 *
	 * @brief Get RtcModuleProfile
	 *
	 * Get RtcModuleProfile
	 *
	 * @endif
	 */
	virtual RtcModuleProfile& getModuleProfile()
	{
	  return m_Profile;
	}
	/*
	virtual RtcComponentProfile& getProfile()
	{
	  return m_Profile;
	}
	*/
	/*
	virtual RtcConfiguration& getConfiguration()
	{
	  return m_Configuration;
	}
	*/
	/*!------------------------------------------------------------
	 * Set component name
	 *------------------------------------------------------------*/  
	/*!
	 * @if jp
	 *
	 * @brief ����ݡ��ͥ��̾�򥻥åȤ���
	 *
	 * ����ݡ��ͥ�ȤΥ⥸�塼��̾�˰�����Ϳ������������ղä���
	 * ����ݡ��ͥ��̾���֤���
	 * �桼���Ϥ��Υ᥽�åɤ򥪡��С��饤�ɤ��ơ�����ݡ��ͥ��̾��̿̾
	 * ��ˡ�򥫥����ޥ������뤳�Ȥ�����롣
	 *
	 * @param num ����ݡ��ͥ�ȤΥ��󥹥����ֹ�
	 *
	 * @else
	 *
	 * @brief Set component name
	 *
	 * @param num instance number of this component
	 *
	 * @endif
	 */
	virtual string setComponentName(int num);

	//============================================================
	// Input port handling
	//============================================================
	/*!
	 * @if jp
	 *
	 * @brief InPort ����Ͽ
	 *
	 * InPort �򥳥�ݡ��ͥ�Ȥ���Ͽ���롣��Ͽ���줿InPort�ϳ�������
	 * ������褦�ˤʤ롣
	 *
	 * @param in_ch InPort object of InPort<T>
	 *
	 * @else
	 *
	 * @brief Registration of input channel.
	 *
	 * Duplication of a name of input channel is not allowed.
	 * "false" will be returned when there is duplication of a name.
	 *
	 * @param in_ch Input channel object of InPort<T>
	 * @return true/false: "false" will be returned if registration goes wrong.
	 *
	 * @endif
	 */
	bool registerInPort(InPortBase& in_ch);

	/*!
	 * @if jp
	 *
	 * @brief InPort ����Ͽ
	 *
	 * InPort �򥳥�ݡ��ͥ�Ȥ���Ͽ���롣��Ͽ���줿InPort�ϳ�������
	 * ������褦�ˤʤ롣
	 *
	 * @param in_ch InPort object of InPort<T>
	 *
	 * @else
	 *
	 * @brief Registration of input channel.
	 *
	 * Duplication of a name of input channel is not allowed.
	 * "false" will be returned when there is duplication of a name.
	 *
	 * @param in_ch Input channel object of InPort<T>
	 * @return true/false: "false" will be returned if registration goes wrong.
	 *
	 * @endif
	 */
	bool registerPort(InPortBase& in_ch)
	{
	  return registerInPort(in_ch);
	};
	
	/*!
	 * @if jp
	 *
	 * @brief InPort ����Ͽ���
	 *
	 * ��Ͽ����Ƥ��� InPort ����Ͽ�������롣
	 *
	 * @param in_ch InPort object of InPort<T>
	 *
	 * @else
	 *
	 * @brief Deletion of InPort
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param in_ch Input channel object of InPort<T>
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deleteInPort(InPortBase& in_ch);

	/*!
	 * @if jp
	 *
	 * @brief InPort ����Ͽ���
	 *
	 * ��Ͽ����Ƥ��� InPort ����Ͽ�������롣
	 *
	 * @param in_ch InPort object of InPort<T>
	 *
	 * @else
	 *
	 * @brief Deletion of InPort
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param in_ch Input channel object of InPort<T>
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deletePort(InPortBase& in_ch)
	{
	  return deleteInPort(in_ch);
	};
	
	/*!
	 * @if jp
	 *
	 * @brief InPort ����Ͽ���
	 *
	 * ��Ͽ����Ƥ��� InPort ����Ͽ��̾������ꤷ�Ʋ�����롣
	 *
	 * @param ch_name InPort ̾
	 *
	 * @else
	 *
	 * @brief Deletion of input channel by channel name.
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param ch_name Input channel name
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deleteInPortByName(const char* ch_name);

	/*!
	 * @if jp
	 *
	 * @brief ���Ƥ� InPort �Υǡ���������
	 *
	 * ���Ƥ�InPort���Ф��� InPort::read() ��¹ԡ�ͽ��Х���ɤ��줿�ѿ���
	 * �ǿ����ͤ���������롣�ѿ��˥Х���ɤ���Ƥ��ʤ�InPort�Ǥϲ���
	 * ������ʤ���
	 *
	 * @else
	 *
	 * @brief Read all data to InPorts and bound variable
	 *
	 * Invoke InPort::read() to all registered InPorts.
	 *
	 * @endif
	 */	
	void readAllInPorts();


	/*!
	 * @if jp
	 *
	 * @brief ���Ƥ� InPort �ν�λ����
	 *
	 * ���Ƥ�InPort���Ф��ƥ��֥������Ȥ� deactivate() ��Ԥ���
	 *
	 * @else
	 *
	 * @brief Finalize all InPorts
	 *
	 * Finalize all registered InPorts and deactivate as a CORBA objects.
	 *
	 * @endif
	 */	
	void finalizeInPorts();

	//============================================================
	// Output channel handling
	//============================================================
	/*!
	 * @if jp
	 *
	 * @brief OutPort ����Ͽ
	 *
	 * OutPort �򥳥�ݡ��ͥ�Ȥ���Ͽ���롣��Ͽ���줿OutPort�ϳ�������
	 * ������褦�ˤʤ롣
	 *
	 * @param out_ch OutPort object of OutPort<T>
	 *
	 * @else
	 *
	 * @brief Registration of output channel
	 *
	 * Duplication of a name of output channel is not allowed.
	 * "false" will be returned when there is duplication of a name.
	 *
	 * @param out_ch Output channel object of OutPort<T>
	 * @return true/false: "false" will be returned if registration goes wrong.
	 *
	 * @endif
	 */
	bool registerOutPort(OutPortBase& out_ch);
	bool registerPort(OutPortBase& out_ch)
	{
	  return registerOutPort(out_ch);
	};
	
	/*!
	 * @if jp
	 *
	 * @brief OutPort ����Ͽ
	 *
	 * OutPort �򥳥�ݡ��ͥ�Ȥ���Ͽ���롣��Ͽ���줿OutPort�ϳ�������
	 * ������褦�ˤʤ롣
	 *
	 * @param out_ch OutPort object of OutPort<T>
	 *
	 * @else
	 *
	 * @brief Deletion of output channel.
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param out_ch Output channel object of OutPort<T>
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deleteOutPort(OutPortBase& out_ch);

	/*!
	 * @if jp
	 *
	 * @brief OutPort ����Ͽ
	 *
	 * OutPort �򥳥�ݡ��ͥ�Ȥ���Ͽ���롣��Ͽ���줿OutPort�ϳ�������
	 * ������褦�ˤʤ롣
	 *
	 * @param out_ch OutPort object of OutPort<T>
	 *
	 * @else
	 *
	 * @brief Deletion of output channel.
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param out_ch Output channel object of OutPort<T>
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deletePort(OutPortBase& out_ch)
	{
	  return deleteOutPort(out_ch);
	};
	
	/*!
	 * @if jp
	 *
	 * @brief OutPort ����Ͽ���
	 *
	 * ��Ͽ����Ƥ��� OutPort ����Ͽ��̾������ꤷ�Ʋ�����롣
	 *
	 * @param ch_name OutPort ̾
	 *
	 * @else
	 *
	 * @brief Deletion of output channel by channel name.
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param ch_name Output channel name
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deleteOutPortByName(const char* ch_name);

	/*!
	 * @if jp
	 *
	 * @brief ���Ƥ� OutPort �Υǡ����񤭽Ф�
	 *
	 * ���Ƥ�OutPort���Ф��� OutPort::write() ��¹ԡ�ͽ��Х���ɤ��줿�ѿ���
	 * �ͤ򥵥֥����饤�Ф˽񤭽Ф�����ΥХåե��˽񤭹��ޤ�롣
	 * �ѿ��˥Х���ɤ���Ƥ��ʤ�InPort�Ǥϲ��ⵯ����ʤ���
	 *
	 * @else
	 *
	 * @brief Write all data to OutPorts from bound variables
	 *
	 * Invoke OutPort::write() to all registered OutPorts.
	 *
	 * @endif
	 */	
	void writeAllOutPorts();

	
	/*!
	 * @if jp
	 *
	 * @brief ���Ƥ� OutPort �ν�λ����
	 *
	 * ���Ƥ�OutPort���Ф��Ƴƥ��֥����饤�Ф����Ǥ������֥������Ȥ�
	 * deactivate() ��Ԥ���
	 *
	 * @else
	 *
	 * @brief Finalize all OutPorts
	 *
	 * Finalize all registered OutPorts and deactivate as a CORBA objects.
	 *
	 * @endif
	 */	
	void finalizeOutPorts();

	
	/*!
	 * @if jp
	 *
	 * @brief ����ݡ��ͥ��̾�� alias ����Ͽ
	 *
	 * ����ݡ��ͥ��̾�� alias ����Ͽ���롣��Ͽ���줿 alias �ϥ͡��ߥ󥰥�����
	 * ����Ͽ����롣
	 * ̾�����դ����� ����ƥ����Ȥζ��ڤ�� "/"�� id �� kind �ζ��ڤ�� "|"
	 * �Ȥ��롣����ƥ����� Manipulator �β��˼�ʬ���Ȥ� MyManipulator0 �Ȥ���
	 * bind ���������ˤϡ�"/Manipualtor/MyManipulator0|rtc" ��ʸ����Ȥ���
	 * �Ϥ����ޥ͡�����ˤ��Ŭ�ڤʥ����ߥ󥰤ǥ͡��ߥ󥰥����Ф���Ͽ����롣
	 *
	 * @param alias ����ݡ��ͥ��̾�� alias
	 *
	 * @else
	 *
	 * @brief Register alias of component name
	 *
	 * This method register alias of component name. Registered alias will
	 * bind to naming server.
	 * Context delimiter is "/", id/kind delimiter is "|".
	 * If you want to bind your component "MyManipulator0" under a context
	 * "Manipulator", you should give an char* argument 
	 * like "/Manipulator/MyManipulator|rtc".
	 * This component will be bound to naming server on this alias.
	 *
	 * @param alias An alias of this component name
	 *
	 * @endif
	 */
	void appendAlias(const char* alias);

	/*!
	 * @if jp
	 *
	 * @brief ����ݡ��ͥ��̾�� alias ����Ͽ
	 *
	 * ����ݡ��ͥ��̾�� alias ����Ͽ���롣��Ͽ���줿 alias �ϥ͡��ߥ󥰥�����
	 * ����Ͽ����롣
	 * ̾�����դ����� ����ƥ����Ȥζ��ڤ�� "/"�� id �� kind �ζ��ڤ�� "|"
	 * �Ȥ��롣����ƥ����� Manipulator �β��˼�ʬ���Ȥ� MyManipulator0 �Ȥ���
	 * bind ���������ˤϡ�"/Manipualtor/MyManipulator0|rtc" ��ʸ����Ȥ���
	 * �Ϥ����ޥ͡�����ˤ��Ŭ�ڤʥ����ߥ󥰤ǥ͡��ߥ󥰥����Ф���Ͽ����롣
	 *
	 * @param alias ����ݡ��ͥ��̾�� alias
	 *
	 * @else
	 *
	 * @brief Register alias of component name
	 *
	 * This method register alias of component name. Registered alias will
	 * bind to naming server.
	 * Context delimiter is "/", id/kind delimiter is "|".
	 * If you want to bind your component "MyManipulator0" under a context
	 * "Manipulator", you should give an char* argument 
	 * like "/Manipulator/MyManipulator|rtc".
	 * This component will be bound to naming server on this alias.
	 *
	 * @param alias An alias of this component name
	 *
	 * @endif
	 */
	void appendAlias(const std::string alias);

	/*!
	 * @if jp
	 *
	 * @brief ����ݡ��ͥ��̾�� alias �����
	 *
	 * ��Ͽ����Ƥ��륳��ݡ��ͥ��̾�� alias ��������롣
	 *
	 * @else
	 *
	 * @brief Get registered aliases of component name
	 *
	 * @endif
	 */
	std::list<string> getAliases();

	void setNamingPolicy(NamingPolicy policy);
	NamingPolicy getNamingPolicy();
	bool isLongNameEnable();
	bool isAliasEnable();

	void forceExit();

	/*!
	 * @if jp
	 *
	 * @brief ����ݡ��ͥ�Ȥν�λ����
	 *
	 * 1.OutPort�ν�λ����+deactivate��2.InPort�ν�λ����+deactivate��
	 * 3.�����ƥ��ӥƥ�����ߡ�4.����ݡ��ͥ�Ȥ�deactivate
	 * 5. 
	 *
	 * @else
	 *
	 * @brief Get registered aliases of component name
	 *
	 * @endif
	 */
	void finalize();
  
	bool isThreadRunning();
	
	

	
  protected:
	/*!
	 * @if jp
	 * @brief ORB �ݥ����ѿ�
	 * @else
	 * @brief pointer to ORB
	 * @endif
	 */
	CORBA::ORB_ptr m_pORB;

	/*!
	 * @if jp
	 * @brief POA �ݥ����ѿ�
	 * @else
	 * @brief pointer to POA
	 * @endif
	 */
	PortableServer::POA_ptr m_pPOA;

	/*!
	 * @if jp
	 * @brief Manager �ݥ����ѿ�
	 * @else
	 * @brief pointer to Manager
	 * @endif
	 */
	RtcManager* m_pManager;

	/*!
	 * @if jp
	 * @brief �ƥ���ݡ��ͥ�ȤΥ��֥������ȥ�ե����
	 * @else
	 * @brief object reference to parent component
	 * @endif
	 */
	RTCBase_var m_Parent;

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ�����åɾ��֥ե饰��¤��
	 * @else
	 * @brief activity thread state structure
	 * @endif
	 */
	typedef enum ThreadStates {
	  UNKNOWN,
	  RUNNING,
	  SUSPEND,
	  STOP
	};
	class ThreadState
	{
	public:
	  ThreadState() : m_Flag(RUNNING){};
	  ThreadStates m_Flag;
	  ACE_Thread_Mutex m_Mutex;
	};
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ�����åɾ����ѿ�
	 * @else
	 * @brief activity thread state variable
	 * @endif
	 */
	ThreadState m_ThreadState;

	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ��̾��� Fanctor ���饹
	 * @else
	 * @brief Component name comparison fanctor class
	 * @endif
	 */
	class eq_name
	{
	public:
	  const string m_name;
	  eq_name(const char* name) : m_name(name){};
	  bool operator()(InPortBase* ch)
	  {
		string ch_name(ch->name());
		return m_name == ch_name;
	  };
	  bool operator()(OutPortBase* ch)
	  {
		string ch_name(ch->name());
		return m_name == ch_name;
	  };
	};

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ������ѿ����饹
	 * @else
	 * @brief activity state varible structure
	 * @endif
	 */
	struct ComponentStateMtx {
	public:
	  /*!
	   * @if jp
	   * @brief �����ƥ��ӥƥ������ѿ����饹���󥹥ȥ饯��
	   * @else
	   * @brief activity state varible structure constructor
	   * @endif
	   */
	  ComponentStateMtx():_state(RTM::RTComponent::RTC_BORN){};

	  /*!
	   * @if jp
	   * @brief �����ƥ��ӥƥ�����
	   * @else
	   * @brief activity state varible structure
	   * @endif
	   */
	  ComponentState _state;
	  
	  /*!
	   * @if jp
	   * @brief �����ƥ��ӥƥ������ѿ�Mutex
	   * @else
	   * @brief activity state varible mutex
	   * @endif
	   */
	  ACE_Thread_Mutex _mutex;
	};

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ��θ��߾����ѿ�
	 * @else
	 * @brief activity current state varible
	 * @endif
	 */
	ComponentStateMtx m_CurrentState;

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ��μ������ѿ�
	 * @else
	 * @brief activity next state varible
	 * @endif
	 */
	ComponentStateMtx m_NextState;
	
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ��ؿ��ݥ������
	 * @else
	 * @brief activity function pointer definition
	 * @endif
	 */
	typedef RtmRes (RtcBase::*StateFunc)();
	
	//------------------------------------------------------------
	// Function pointer tables for state action functions.
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ��� exit �ؿ��ơ��֥�
	 * @else
	 * @brief exit function table of activity
	 * @endif
	 */
	StateFunc _exit_func[11];

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ��� entry �ؿ��ơ��֥�
	 * @else
	 * @brief entry function table of activity
	 * @endif
	 */
	StateFunc _entry_func[11];

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ��� do �ؿ��ơ��֥�
	 * @else
	 * @brief do function table of activity
	 * @endif
	 */
	StateFunc _do_func[11];
	
	//------------------------------------------------------------
	// State action functions
	//------------------------------------------------------------
	// 
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ����顼�����å��ؿ�
	 * @else
	 * @brief activity error check function
	 * @endif
	 */
	RtmRes _check_error(RtmRes result);

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ��ѥ��ߡ��ؿ�
	 * @else
	 * @brief dummy function for activity
	 * @endif
	 */
	RtmRes _nop(){return RTM_OK;}

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_init_entry �¹Դؿ�
	 * @else
	 * @brief rtc_init_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_initializing();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_ready_entry �¹Դؿ�
	 * @else
	 * @brief rtc_ready_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_ready_entry();
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_starting_entry �¹Դؿ�
	 * @else
	 * @brief rtc_starting_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_starting();
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_active_entry �¹Դؿ�
	 * @else
	 * @brief rtc_active_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_active_entry();
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_stippoing_entry �¹Դؿ�
	 * @else
	 * @brief rtc_stopping_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_stopping();
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_aborting_entry �¹Դؿ�
	 * @else
	 * @brief rtc_aborting_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_aborting();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_error_entry �¹Դؿ�
	 * @else
	 * @brief rtc_error_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_error_entry();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_fatal_entry �¹Դؿ�
	 * @else
	 * @brief rtc_fatal_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_fatal_entry();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_exiting_entry �¹Դؿ�
	 * @else
	 * @brief rtc_exiting_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_exiting();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_ready_do �¹Դؿ�
	 * @else
	 * @brief rtc_ready_do execution function for activity
	 * @endif
	 */
	RtmRes _rtc_ready();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_active_do �¹Դؿ�
	 * @else
	 * @brief rtc_active_do execution function for activity
	 * @endif
	 */
	RtmRes _rtc_active();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_error_do �¹Դؿ�
	 * @else
	 * @brief rtc_error_do execution function for activity
	 * @endif
	 */
	RtmRes _rtc_error();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_fatal_do �¹Դؿ�
	 * @else
	 * @brief rtc_fatal_do execution function for activity
	 * @endif
	 */
	RtmRes _rtc_fatal();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_ready_exit �¹Դؿ�
	 * @else
	 * @brief rtc_ready_exit execution function for activity
	 * @endif
	 */
	RtmRes _rtc_ready_exit();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_active_exit �¹Դؿ�
	 * @else
	 * @brief rtc_active_exit execution function for activity
	 * @endif
	 */
	RtmRes _rtc_active_exit();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_error_exit �¹Դؿ�
	 * @else
	 * @brief rtc_error_exit execution function for activity
	 * @endif
	 */
	RtmRes _rtc_error_exit();

	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ� rtc_fatal_exit �¹Դؿ�
	 * @else
	 * @brief rtc_fatal_exit execution function for activity
	 * @endif
	 */
	RtmRes _rtc_fatal_exit();
	
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ��ؿ��ơ��֥�ν����
	 * @else
	 * @brief initialize activity function table
	 * @endif
	 */
	void init_state_func_table();
	

	/*!
	 * @if jp
	 * @brief InPort �ꥹ�ȥ��ƥ졼��
	 * @else
	 * @brief InPort list iterator
	 * @endif
	 */
	typedef list<InPortBase*>::iterator InPorts_it;
	
	/*!
	 * @if jp
	 * @brief OutPort �ꥹ�ȥ��ƥ졼��
	 * @else
	 * @brief OutPort list iterator
	 * @endif
	 */
	typedef list<OutPortBase*>::iterator OutPorts_it;
	
	/*!
	 * @if jp
	 * @brief mutex �դ� InPort �ꥹ�ȹ�¤��
	 * @else
	 * @brief InPort list structure with mutex 
	 * @endif
	 */
	struct InPorts
	{
	  list<InPortBase*> m_List;
	  ACE_Thread_Mutex m_Mutex;
	};
	/*!
	 * @if jp
	 * @brief mutex �դ� InPort �ꥹ��
	 * @else
	 * @brief InPort list with mutex 
	 * @endif
	 */
	InPorts m_InPorts;
	
	/*!
	 * @if jp
	 * @brief mutex �դ� OutPort �ꥹ�ȹ�¤��
	 * @else
	 * @brief OutPort list structure with mutex 
	 * @endif
	 */
	struct OutPorts
	{
	  list<OutPortBase*> m_List;
	  ACE_Thread_Mutex m_Mutex;
	};
	/*!
	 * @if jp
	 * @brief mutex �դ� OutPort �ꥹ��
	 * @else
	 * @brief OutPort list with mutex
	 * @endif
	 */
	OutPorts m_OutPorts;
	
	//! Input port flag list
	//  list<const bool*> m_InFlags;
	
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ������ѿ�
	 * @else
	 * @brief activity state variable
	 * @endif
	 */
	TimedState m_TimedState;
	/*!
	 * @if jp
	 * @brief �����ƥ��ӥƥ�����OutPort
	 * @else
	 * @brief activity state OutPort
	 * @endif
	 */
	OutPortAny<TimedState> m_StatePort;									  

	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥץ�ե�����
	 * @else
	 * @brief component profile
	 * @endif
	 */
	RtcModuleProfile m_Profile;
	//	RtcManagerProfile m_ManagerProfile;
	//	RtcComponentProfile m_Profile;
	//	RtcConfiguration m_Configuration;

	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ��̾��alias
	 * @else
	 * @brief Aliases of component name
	 * @endif
	 */
	std::list<string> m_Alias;

	NamingPolicy m_NamingPolicy;

 	/*!
	 * @if jp
	 * @brief �������Хåե�
	 * @else
	 * @brief Logger mediation buffer
	 * @endif
	 */
	RtcMedLogbuf m_MedLogbuf;

 	/*!
	 * @if jp
	 * @brief �������ȥ꡼��
	 * @else
	 * @brief Logger stream
	 * @endif
	 */
	RtcLogStream rtcout;

  };

  //------------------------------------------------------------
  // RTComponent factory function type
  //------------------------------------------------------------

  class EXPORTS RtcManager;
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ��֥������ȥե����ȥ�ؿ����
	 * @else
	 * @brief component object factory function declaration
	 * @endif
	 */
  typedef RtcBase* (*RtcNewFunc)(RtcManager* manager);

	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ��֥��������Ѵ��ؿ����
	 * @else
	 * @brief component object delete function declaration
	 * @endif
	 */
  typedef void (*RtcDeleteFunc)(RtcBase* rtc);

};  // end of namespace RTM


#endif // __RtcBase_h__
