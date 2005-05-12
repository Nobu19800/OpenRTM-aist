// -*- C++ -*-
/*!
 * @file RtcInPortBase.h
 * @brief InPort base class
 * @date $Date: 2005-05-12 09:06:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcInPortBase.h,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcInPortBase_h
#define RtcInPortBase_h

#include <ace/Thread_Manager.h>
#include "rtm/RTC.h"
#include "rtm/idl/RTCDataTypeSkel.h"
#include "rtm/idl/RTCInPortSkel.h"
#include "rtm/RtcRingBuffer.h"

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
  class InPortBase :
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
	  throw (CORBA::SystemException, RTM::InPort::Disconnected) = 0;
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

	
  protected:
	/*!
	 * @if jp
	 * @brief InPort �Υץ�ե�����
	 * @else
	 * @brief InPort profile
	 * @endif
	 */
	PortProfile m_Profile;
	
  };
  
}; // End of namespace RTM

#endif // RtcInPortBase_h
