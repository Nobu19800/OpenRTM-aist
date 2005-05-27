// -*- C++ -*-
/*!
 * @file RtcOutPortBase.h
 * @brief InPortBase base class
 * @date $Date: 2005-05-27 07:34:21 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcOutPortBase.h,v 1.3 2005-05-27 07:34:21 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2005/05/16 06:37:11  n-ando
 * - OutPortBase class was DLL exported for Windows port.
 * - m_Profile.name should be initialized with empty string.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcOutPortBase_h
#define RtcOutPortBase_h

#include <list>
#include <ace/Task.h>

#include "rtm/RTC.h"
#include "rtm/idl/RTCDataTypeSkel.h"
#include "rtm/idl/RTCOutPortSkel.h"
#include "rtm/idl/RTCOutPortStub.h"
#include "rtm/RtcInPortBase.h"
#include "rtm/RtcRingBuffer.h"
#include "rtm/RtcSubscriber.h"


namespace RTM {
  class SubscriberBase;

  /*!
   * @if jp
   *
   * @class OutPortBase
   *
   * @brief OutPort ���쥯�饹
   * 
   * OutPort �μ����Ǥ��� OutPort<T> �δ��쥯�饹��
   * CORBA interface �ؤμ������󶡤��롣
   *
   * @else
   *
   * @class OutPortBase
   *
   * @brief Output port base class.
   *
   * The base class of OutPort<T> s which are implementations of OutPort  
   * This class provides CORBA interface implementation.
   *
   * @endif
   */
  class EXPORTS OutPortBase :
	public POA_RTM::OutPort,
	public PortableServer::RefCountServantBase
  {
  public:
	/*!
	 * @if jp
	 * @brief OutPortBase ���饹���󥹥ȥ饯��
	 *
	 * OutPortBase �Υ��饹���󥹥ȥ饯����
	 *
	 * @else
	 *
	 * @brief A constructor of OutPortBase class.
	 *
	 * Constructor of OutPortBase.
	 *
	 * @endif
	 */
	OutPortBase()
	{
	  m_Profile.name = _CORBA_String_helper::empty_string;
	};

	/*!
	 * @if jp
	 * @brief OutPortBase ���饹�ǥ��ȥ饯��
	 *
	 * OutPortBase �Υ��饹�ǥ��ȥ饯����
	 *
	 * @else
	 *
	 * @brief A destructor of OutPortBase class.
	 *
	 * Destructor of OutPortBase.
	 *
	 * @endif
	 */
	virtual ~OutPortBase(){};

	//============================================================
	// CORBA interfaces.
	//============================================================
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] OutPort �θ����ͤ��������
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get OutPort current value
	 * 
	 * @endif
	 */
	virtual CORBA::Any* get() throw (CORBA::SystemException) = 0;

	//! CORBA interface Return type code of port value.
	//	virtual CORBA::TypeCode_ptr port_type();

	//------------------------------------------------------------
	// RTCPortBase interfaces
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * 
	 * @brief OutPort �򥵥֥����饤�֤���
	 *
	 * @else
	 *
	 * @brief Subscribe this OutPort
	 * 
	 * @endif
	 */
	virtual RtmRes subscribe(SubscriptionProfile &subs)
	  throw (CORBA::SystemException, RTM::PortBase::InvalidSubscription);

	/*!
	 * @if jp
	 * 
	 * @brief OutPort �򥵥֥����饤�֤���
	 *
	 * @else
	 *
	 * @brief Subscribe this OutPort
	 * 
	 * @endif
	 */
	virtual RtmRes notify_subscribe(SubscriptionProfile &subs)
	  throw (CORBA::SystemException, RTM::PortBase::InvalidSubscription);

	/*!
	 * @if jp
	 * 
	 * @brief OutPort �Υ��֥����饤�֤�������
	 *
	 * @else
	 *
	 * @brief Unsubscribe this OutPort
	 * 
	 * @endif
	 */
	virtual RtmRes unsubscribe(const char* id)
	  throw (CORBA::SystemException, RTM::PortBase::NoSubscription);

	/*!
	 * @if jp
	 * 
	 * @brief OutPort �Υ��֥����饤�֤�������
	 *
	 * @else
	 *
	 * @brief Unsubscribe this OutPort
	 * 
	 * @endif
	 */
	virtual RtmRes notify_unsubscribe(const char* id)
	  throw (CORBA::SystemException, RTM::PortBase::NoSubscription);

	/*!
	 * @if jp
	 * 
	 * @brief ���ߥ��֥����饤�֤��Ƥ��� InPort �Υꥹ�Ȥ��������
	 *
	 * @else
	 *
	 * @brief Get InPort list of current subscriber
	 * 
	 * @endif
	 */
	//	virtual InPortList* inports() throw (CORBA::SystemException);

	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] OutPort �Υץ�ե�������������
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get OutPort profile
	 * 
	 * @endif
	 */
	virtual PortProfile* profile() throw (CORBA::SystemException);

	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] Subscription �Υꥹ�Ȥ��������
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get Subscription list
	 * 
	 * @endif
	 */
	virtual SubscriptionList* subscriptions();



	// End of CORBA interfaces
	//============================================================
	bool createSubscriber(SubscriptionProfile& subscription);
	/*!
	 * @if jp
	 * 
	 * @brief ���ߤ� OutPort ���ͤ򥵥֥����饤�Ф�push����
	 *
	 * @else
	 *
	 * @brief Push current OutPort value to subscriber
	 * 
	 * @endif
	 */
	//	virtual RtmRes push(const InPort_ptr& inport, std::string& subsid) = 0;
	virtual RtmRes push(InPort_ptr inport, std::string subsid) = 0;

	/*!
	 * @if jp
	 * 
	 * @brief ���ߤ� OutPort ���ͤ򥵥֥����饤�Ф��Ф��ƹ���
	 *
	 * @else
	 *
	 * @brief Update current OutPort to to subscriber
	 * 
	 * @endif
	 */
	virtual void updateall();

	/*!
	 * @if jp
	 * 
	 * @brief ���ߤΥ��֥����饤�Ф���������
	 *
	 * @else
	 *
	 * @brief Disconnect all subscribers
	 * 
	 * @endif
	 */
	virtual void disconnect_all();

	/*!
	 * @if jp
	 * 
	 * @brief OutPort ��̾�����������
	 *
	 * @else
	 *
	 * @brief Get OutPort name
	 * 
	 * @endif
	 */
	virtual const char* name() {return m_Profile.name;};

	/*!
	 * @if jp
	 *
	 * @brief �Х���ɤ��줿 T ���Υǡ����� OutPort �κǿ��ͤȤ��ƽ񤭹���
	 *
	 * ��貾�۴ؿ����������饹�ˤ�ꥪ���С��饤�ɤ���ݥ�⡼�ե��å���
	 * ���Ѥ��������ޤ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief Write into current OutPort from bound T-type data
	 *
	 * Pure virtual method.
	 *
	 * @endif
	 */
	virtual void write_pm() = 0;

	virtual OutPort_ptr getObjRef();
	virtual void setObjRef(OutPort_ptr objref);


  protected:
	virtual RtmRes unsubscribeNoLocked(const char* id)
	  throw (CORBA::SystemException, RTM::PortBase::NoSubscription);

	/*!
	 * @if jp
	 * @brief ���֥����饤�ФΥꥹ��
	 * @else
	 * @brief Subscriber list
	 * @endif
	 */

	typedef std::list<SubscriberBase*>::iterator Subs_it;	
	struct Subscribers
	{
	  ACE_Thread_Mutex m_Mutex;
	  std::list<SubscriberBase*> m_List;
	  
	  class eq_id
	  {
	  public:
		const std::string m_id;
		eq_id(const char* id) : m_id(id){};
		bool operator()(SubscriberBase* subs);
	  };
	  Subs_it findById(const char* id);
	  Subs_it eraseById(const char* id);
	};
	Subscribers m_Subscribers;


	/*!
	 * @if jp
	 * @brief OutPort �Υץ�ե�����
	 * @else
	 * @brief OutPort profile
	 * @endif
	 */
	PortProfile m_Profile;

	/*!
	 * @if jp
	 * @brief OutPort ���ȤΥ��֥������ȥ�ե����
	 * @else
	 * @brief object reference of OutPort itself
	 * @endif
	 */
	OutPort_var m_thisObjRef;



  };


  
}; // End of namespace RTM

#endif // RtcOutPortBase_h
