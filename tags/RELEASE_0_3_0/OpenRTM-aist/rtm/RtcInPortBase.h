// -*- C++ -*-
/*!
 * @file RtcInPortBase.h
 * @brief InPort base class
 * @date $Date: 2005-05-27 07:32:32 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcInPortBase.h,v 1.3 2005-05-27 07:32:32 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2005/05/16 06:12:57  n-ando
 * - RtcInPortBase class was DLL exported for Windows port.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcInPortBase_h
#define RtcInPortBase_h

#include <ace/Thread_Manager.h>
#include "rtm/RTC.h"
#include "rtm/idl/RTCDataTypeSkel.h"
#include "rtm/idl/RTCInPortSkel.h"
#include "rtm/RtcRingBuffer.h"
#include "rtm/RtcSubscriber.h"

namespace RTM
{
  
  /*!
   * @if jp
   *
   * @class InPortBase
   *
   * @brief InPort ���쥯�饹
   * 
   * InPort �μ����Ǥ��� InPort<T> �δ��쥯�饹��
   * CORBA interface �ؤμ������󶡤��롣
   *
   * @else
   *
   * @class InPortBase
   *
   * @brief Input port base class.
   *
   * The base class of InPort<T> s which are implementations of InPort  
   * This class provides CORBA interface implementation.
   *
   * @endif
   */
  class EXPORTS InPortBase :
	public POA_RTM::InPort,
					public PortableServer::RefCountServantBase
  {
  public:
	/*!
	 * @if jp
	 * @brief InPortBase ���饹���󥹥ȥ饯��
	 *
	 * InPortBase �Υ��饹���󥹥ȥ饯����
	 *
	 * @else
	 *
	 * @brief A constructor of InPortBase class.
	 *
	 * Constructor of InPortBase.
	 *
	 * @endif
	 */
	InPortBase()
	{
	  ACE_TRACE("InPortBase::InPortBase(int)");
	  m_Profile.name = _CORBA_String_helper::empty_string;
	};
	
	/*!
	 * @if jp
	 * @brief InPortBase ���饹�ǥ��ȥ饯��
	 *
	 * InPortBase �Υ��饹�ǥ��ȥ饯����
	 *
	 * @else
	 *
	 * @brief A destructor of InPortBase class.
	 *
	 * Destructor of InPortBase.
	 *
	 * @endif
	 */
	virtual ~InPortBase(){};
	
	//------------------------------------------------------------
	// << CORBA interfaces >>
	//------------------------------------------------------------
	/*!------------------------------------------------------------
	 * [CORBA interface] Put initial port value to input port from output port
	 *------------------------------------------------------------*/
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] InPort ���ͤ��Ϥ�
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Put data on InPort
	 * 
	 * @endif
	 */
	virtual void put(const CORBA::Any& value)
	  throw (CORBA::SystemException, RTM::PortBase::Disconnected) = 0;
	//	throw (RTM::InPort::Disconnected, CORBA::SystemException);
	
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] InPort �Υץ�ե�������������
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get InPort profile
	 * 
	 * @endif
	 */
	virtual PortProfile* profile() throw (CORBA::SystemException);
	
    virtual RtmRes subscribe(SubscriptionProfile& subs)
	  throw (CORBA::SystemException, RTM::PortBase::InvalidSubscription);
    virtual RtmRes notify_subscribe(SubscriptionProfile& subs)
	  throw (CORBA::SystemException, RTM::PortBase::InvalidSubscription);
    virtual RtmRes unsubscribe(const char* id)
	  throw (CORBA::SystemException, RTM::PortBase::NoSubscription);
    virtual RtmRes notify_unsubscribe(const char* id)
	  throw (CORBA::SystemException, RTM::PortBase::NoSubscription);
    virtual SubscriptionList* subscriptions();








	//------------------------------------------------------------
	// << Local interfaces >>
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * 
	 * @brief InPort ��̾�����������
	 *
	 * @else
	 *
	 * @brief Get InPort name
	 * 
	 * @endif
	 */
	const char* name(){return m_Profile.name;}
	

	/*!
	 * @if jp
	 *
	 * @brief �Х���ɤ��줿 T �����ѿ��� InPort �Хåե��κǿ��ͤ��ɤ߹���
	 *
	 * ��貾�۴ؿ����������饹�ˤ�ꥪ���С��饤�ɤ���ݥ�⡼�ե��å���
	 * ���Ѥ��������ޤ����᥽�åɡ�
	 *
	 * @else
	 *
	 * @brief Read into bound T-type data from current InPort
	 *
	 * Pure virtual method.
	 *
	 * @endif
	 */
	virtual void read_pm() = 0;

	virtual InPort_ptr getObjRef();
	virtual void setObjRef(InPort_ptr objref);

  protected:
	/*!
	 * @if jp
	 * @brief InPort �Υץ�ե�����
	 * @else
	 * @brief InPort profile
	 * @endif
	 */
	PortProfile m_Profile;

	/*!
	 * @if jp
	 * @brief ���֥����饤�ФΥꥹ��
	 * @else
	 * @brief Subscriber list
	 * @endif
	 */

	typedef std::list<SubsProfileBase*>::iterator Subs_it;	
	struct Subscribers
	{
	  ACE_Thread_Mutex m_Mutex;
	  std::list<SubsProfileBase*> m_List;
	  
	  class eq_id
	  {
	  public:
		const std::string m_id;
		eq_id(const char* id) : m_id(id){};
		bool operator()(SubsProfileBase* subs);
	  };
	  Subs_it findById(const char* id);
	  Subs_it eraseById(const char* id);
	};
	Subscribers m_Subscribers;

	/*!
	 * @if jp
	 * @brief OutPort ���ȤΥ��֥������ȥ�ե����
	 * @else
	 * @brief object reference of OutPort itself
	 * @endif
	 */
	InPort_var m_thisObjRef;
	
  };
  
}; // End of namespace RTM

#endif // RtcInPortBase_h
