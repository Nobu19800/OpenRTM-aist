// -*- C++ -*-
/*!
 * @file RtcSubscriber.h
 * @brief Subscriber active object class runs on Output port
 * @date $Date: 2005-05-16 06:39:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcSubscriber.h,v 1.2 2005-05-16 06:39:02 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcSubscriber_h
#define RtcSubscriber_h

#include <ace/Task.h>
#include <ace/Thread.h>
#include <ace/Synch.h>
#include "rtm/RtcOutPortBase.h"
#include "rtm/RtcInPortBase.h"

namespace RTM {
  //============================================================
  /*!
   * @class SubscriberBase
   * 
   * @brief Subscriber object.
   * This is derived from ACE_Task active object and 
   * observer pattern is alos applied.
   */ 
  /*!
   * @if jp
   *
   * @class SubscriberBase
   *
   * @brief Subscriber ���쥯�饹
   * 
   * Subscriber* �δ��쥯�饹 SubscriberBase.
   * �Ƽ� Subscriber �Ϥ��Υ��饹��Ѿ����ƾܺ٤�������롣
   *
   * @else
   *
   * @class SubscriberBase
   *
   * @brief Base class of subscriber.
   *
   * A base class of Subscriber*.
   * Variation of Subscriber* which implements details of subscriber
   * inherits this SubscriberBase class.
   *
   * @endif
   */
  class EXPORTS SubscriberBase
	: public ACE_Task<ACE_MT_SYNCH>
  {
  public:
	/*!
	 * @if jp
	 *
	 * @brief SubscriberBase ���饹���󥹥ȥ饯��
	 *
	 * @param parent Subscriber* �򥤥󥹥��󥹲�����OutPort�Υݥ��󥿡�
	 * @param inport Subscriber ���� InPort �Υ��֥������ȥ�ե���󥹡�
	 * @param id SubscriptionID����ˡ�����UUID��
	 * @param profile Subscription �Υץ�ե����롣
	 *
	 * @else
	 *
	 * @param parent OutPort pointer which instansiate Subscriber*.
	 * @param inport An InPort object reference wihch subscribe parent OutPort.
	 * @param id SubscriptionID��Unique UUID.
	 * @param profile Profile of this subscription.
	 *
	 * @endif
	 */
	SubscriberBase(OutPortBase* parent, InPort_ptr inport,
				   const SubscriptionID id, SubscriberProfile profile);

	/*!
	 * @if jp
	 * @brief SubscriberBase ���饹�ǥ��ȥ饯����
	 * @else
	 * @brief SubscriberBase class destructor.
	 * @endif
	 */
	~SubscriberBase();
	
	/*!
	 * @if jp
	 * @brief SubscriberBase �����ӥ��򳫻Ϥ��롣
	 * @else
	 * @brief Start SubscriberBase service.
	 * @endif
	 */
	virtual int open(void *args);

	/*!
	 * @if jp
	 * @brief SubscriberBase �����ӥ�����ߤ��롣
	 * @else
	 * @brief Stop SubscriberBase service.
	 * @endif
	 */
	virtual int close(unsigned long flags);

	/*!
	 * @if jp
	 * @brief SubscriberBase �����ӥ������� (��貾�۴ؿ�)��
	 * @else
	 * @brief Main part of SubscriberBase service (pure virtual method).
	 * @endif
	 */
	virtual int svc(void) = 0;
	
	/*!
	 * @if jp
	 * @brief Subscriber �ؤΥǡ���������Ԥ� (����۴ؿ�)��
	 * @else
	 * @brief Update data to subscribers. (pure virtual method)
	 * @endif
	 */
	virtual bool update() = 0;
	
	/*!
	 * @if jp
	 * @brief Subscriber �����ӥ���λ���롣
	 * @else
	 * @brief Stop subscriber service.
	 * @endif
	 */
	virtual void release();

	/*!
	 * @if jp
	 * @brief SubscriberProfile �����롣
	 * @else
	 * @brief Get SubscriberProfile.
	 * @endif
	 */
	virtual SubscriberProfile get_profile();

	/*!
	 * @if jp
	 * @brief Subscribe ���Ƥ��� InPort �Υ��֥������ȥ�ե���󥹤����롣
	 * @else
	 * @brief Get InPort's object reference which subscribe this OutPort.
	 * @endif
	 */
	virtual InPort_ptr get_inport();

	/*!
	 * @if jp
	 * @brief SubscSubscribe ���Ƥ��� InPort �Υ��֥������ȥ�ե���󥹤����롣
	 * @else
	 * @brief Get InPort's object reference which subscribe this OutPort.
	 * @endif
	 */
	virtual std::string get_id();

	/*!
	 * @if jp
	 * @brief ����åɤ����äƤ��뤫�ɤ�����Ƚ�ꤹ�롣
	 * @else
	 * @brief Is thread running or not.
	 * @endif
	 */
	inline bool is_running();

	/*!
	 * @if jp
	 * @brief ����åɤ���ߤ����롣�ºݤˤϥ����ѿ� m_Running �� false ��
	 * ���åȤ��롣��߽����ϥ桼������Ǥ������ʤ���Фʤ�ʤ���
	 * @else
	 * @brief Stop this task thread. Actually this method set member variable
	 * "m_Running" to false. User have to implement thread stop logic.
	 * @endif
	 */
	virtual void stop_thread();

  protected:
	//! Request type. once or periodic.
	SubscriberProfile m_Profile;
	
	//! Input port object reference.
	InPort_ptr m_pInPort;
	
	//! Parent outport object reference
	OutPortBase* m_pParent;
	
	//! Subscription ID
	//const SubscriptionID m_Id;
	std::string m_Id;

	//! Thread activity flag (true=running, false=stop)
	bool m_Running;

	struct NewData
	{
	  NewData() : m_Cond(m_Mutex), m_Updated(false) {};
	  bool m_Updated;
	  ACE_Thread_Mutex m_Mutex;
	  ACE_Condition<ACE_Thread_Mutex> m_Cond;
	};

	// A condition variable for data update notification 
	NewData m_NewData;

  };


  //============================================================
  /*!
   * @class SubscriberOnce
   *
   * @brief Subscriber active object who get data once.
   *
   */
  class EXPORTS SubscriberOnce
	: public SubscriberBase 
  {
  public:
	SubscriberOnce(OutPortBase* parent, InPort_ptr inport,
				   const SubscriptionID id, SubscriberProfile profile);
	virtual bool update();
	virtual int svc(void);

  };
  

  /*!
   * @class SubscriberPeriodic
   *
   * @brief Subscriber active object handle subscriber periodic data acquisition
   *
   */
  class EXPORTS SubscriberPeriodic
	: public SubscriberBase
  {
  public:
	SubscriberPeriodic(OutPortBase* parent, InPort_ptr inport,
					   const SubscriptionID id, SubscriberProfile profile);
	virtual bool update();
	virtual int svc(void);
  };


  //============================================================
  /*!
   * @class SubscriberNew
   *
   * @brief Subscriber active object pushes when new data arrived from activity
   *
   */
  class EXPORTS SubscriberNew
	: public SubscriberBase
  {
  public:
	SubscriberNew(OutPortBase* parent, InPort_ptr inport,
				  const SubscriptionID id, SubscriberProfile profile);
	virtual bool update();
	virtual int svc(void);
  };


  //============================================================
  /*!
   * @class SubscriberTriggerd
   *
   * @brief 
   *
   */
  class EXPORTS SubscriberTriggerd
	: public SubscriberBase
  {
  public:
	SubscriberTriggerd(OutPortBase* parent, InPort_ptr inport,
					   const SubscriptionID id, SubscriberProfile profile);
	virtual bool update(){return true;};
	virtual int svc (void){return 0;};
  };


  //============================================================
  /*!
   * @class SubscriberPeriodicNew
   *
   * @brief 
   *
   */
  class EXPORTS SubscriberPeriodicNew
	: public SubscriberBase
  {
  public:
	SubscriberPeriodicNew(OutPortBase* parent, InPort_ptr inport,
						  const SubscriptionID id, SubscriberProfile profile);
	virtual bool update(){return true;};
	virtual int svc (void){return 0;};
  };


  //============================================================
  /*!
   * @class SubscriberNewPeriodic
   *
   * @brief 
   *
   */
  class EXPORTS SubscriberNewPeriodic
	: public SubscriberBase
  {
  public:
	SubscriberNewPeriodic(OutPortBase* parent, InPort_ptr inport,
						  const SubscriptionID id, SubscriberProfile profile);
	virtual bool update(){return true;};
	virtual int svc (void){return 0;};
  };



  //============================================================
  /*!
   * @class SubscriberPeriodicTriggerd
   *
   * @brief 
   *
   */
  class EXPORTS SubscriberPeriodicTriggerd
	: public SubscriberBase
  {
  public:
	SubscriberPeriodicTriggerd(OutPortBase* parent, InPort_ptr inport,
							   const SubscriptionID id, SubscriberProfile profile);
	virtual bool update(){return true;};
	virtual int svc (void){return 0;};
  };



  //============================================================
  /*!
   * @class SubscriberTriggerdPeriodic
   *
   * @brief 
   *
   */
  class EXPORTS SubscriberTriggerdPeriodic
	: public SubscriberBase
  {
  public:
	SubscriberTriggerdPeriodic(OutPortBase* parent, InPort_ptr inport,
							   const SubscriptionID id, SubscriberProfile profile);
	virtual bool update(){return true;};
	virtual int svc (void){return 0;};
  };





}; // end of namespace RTM



#endif // end of __RtcSubscriber_h__
