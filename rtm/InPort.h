// -*- C++ -*-
/*!
 * @file RtcInPort.h
 * @brief InPort template class
 * @date $Date: 2006-11-07 09:26:12 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPort.h,v 1.4 2006-11-07 09:26:12 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2005/05/27 07:29:32  n-ando
 * - InPort/OutPort interface was changed.
 *   Exception RTM::InPort::Disconnected -> RTM:PortBase::Disconnected
 *
 * Revision 1.2  2005/05/16 06:12:15  n-ando
 * - Time variables of "m_Value" were initialized in constructors.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcInPort_h
#define RtcInPort_h

#include "rtm/RtcInPortBase.h"
#include "rtm/idl/RTCDataTypeSkel.h"
#include <iostream>

namespace RTM
{
  /*!
   * @if jp
   *
   * @class InPortAny
   *
   * @brief InPort �ƥ�ץ졼�ȥ��饹
   * 
   * InPort �μ����Ǥ��� InPortAny<T> �Υƥ�ץ졼�ȥ��饹��
   * <T> ��RTCDataType.idl �ˤ��������Ƥ��뷿�ǡ����ФȤ���
   * Time ���� tm , ����� T���� data ����Ĺ�¤�ΤǤʤ��ƤϤʤ�ʤ���
   * InPort �������˥�󥰥Хåե�����������������������줿�ǡ�����缡
   * ���Υ�󥰥Хåե��˳�Ǽ���롣��󥰥Хåե��Υ������ϥǥե���Ȥ�64��
   * �ʤäƤ��뤬�����󥹥ȥ饯�������ˤ�ꥵ��������ꤹ�뤳�Ȥ��Ǥ��롣
   * �ǡ����ϥե饰�ˤ�ä�̤�ɡ����ɾ��֤��������졢isNew(), getNewDataLen()
   * getNewList(), getNewListReverse() ���Υ᥽�åɤˤ��ϥ�ɥ�󥰤��뤳�Ȥ�
   * �Ǥ��롣
   *
   * @else
   *
   * @class InPortAny
   *
   * @brief OutPort template class
   *
   * This class template provides interfaces to input port.
   * Component developer can define input value, which act as input
   * port from other components, using this template.
   * This is class template. This class have to be incarnated class as port
   * value types. This value types are previously define RtComponent IDL.
   * ex. type T: TimedFload, TimedLong etc... 
   *
   * @endif
   */
  template <class T> class InPortAny
	: public InPortBase
  {
  public:
	/*!
	 * @if jp
	 *
	 * @brief InPortAny ���饹���󥹥ȥ饯��
	 *
	 * InPortAny<T> ���饹�Υ��󥹥ȥ饯����
	 * �ѥ�᡼���Ȥ���Ϳ������ T �����ѿ��˥Х���ɤ���롣
	 *
	 * @param name InPort ̾��InPortBase:name() �ˤ�껲�Ȥ���롣
	 * @param value ���� InPort �˥Х���ɤ���� T �����ѿ�
	 * @param bufsize InPort �����Υ�󥰥Хåե��ΥХåե�Ĺ
	 *
	 * @else
	 *
	 * @brief A constructor.
	 *
	 * Setting channel name and registering channel value.
	 *
	 * @param name A name of the InPort. This name is referred by
	 *             InPortBase::name().
	 * @param value A channel value related with the channel.
	 * @param bufsize Buffer length of internal ring buffer of InPort 
	 *
	 * @endif
	 */
	InPortAny(const char* name, T& value, int bufsize=64)
	  : m_Buffer(bufsize), m_Value(value)
	{
	  // Set PortProfile
	  m_Profile.name = CORBA::string_dup(name);
	  CORBA::Any var;
	  var <<= m_Value;
	  m_Profile.port_type = var.type();

	  // Init time of data variable
	  m_Value.tm.sec = 0;
	  m_Value.tm.nsec = 0;
	  
	  // Initializing ring buffer
	  for (int i = 0 ; i <= m_Buffer.buff_length(); i++)
		{
		  m_Buffer.put(value);
		}
	};

	/*!
	 * @if jp
	 *
	 * @brief InPortAny ���饹���󥹥ȥ饯��
	 *
	 * InPortAny<T> ���饹�Υ��󥹥ȥ饯����
	 * 
	 *
	 * @param name InPort ̾��InPortBase:name() �ˤ�껲�Ȥ���롣
	 * @param bufsize InPort �����Υ�󥰥Хåե��ΥХåե�Ĺ
	 *
	 * @else
	 *
	 * @brief A constructor.
	 *
	 * Setting channel name and registering channel value.
	 *
	 * @param name A name of the InPort. This name is referred by
	 *             InPortBase::name().
	 * @param bufsize Buffer length of internal ring buffer of InPort 
	 *
	 * @endif
	 */
	InPortAny(const char* name, int bufsize=64)
	  : m_Buffer(bufsize), m_Value(m_Dummy)
	{
	  // Set PortProfile
	  m_Profile.name = CORBA::string_dup(name);
	  CORBA::Any var;
	  var <<= m_Value;
	  m_Profile.port_type = var.type();

	  // Init time of data variable
	  m_Value.tm.sec = 0;
	  m_Value.tm.nsec = 0;

	  // Initializing ring buffer
	  for (int i = 0 ; i <= m_Buffer.buff_length(); i++)
		{
		  m_Buffer.put(m_Value);
		}
	};
	
	
	/*!
	 * @if jp
	 *
	 * @brief InPortAny ���饹�ǥ��ȥ饯��
	 *
	 * InPortAny<T> ���饹�Υǥ��ȥ饯����
	 *
	 * @else
	 *
	 * @brief A destructor
	 *
	 * @endif
	 */
	virtual ~InPortAny(){};

	/*!
	 * @if jp
	 *
	 * @brief [CORBA interface] InPort ���ͤ�Ϳ����
	 *
	 * InPort ���ͤ� put ���롣
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Put data on InPort
	 *
	 * @endif
	 */
	virtual void put(const CORBA::Any& value)
	  throw (RTM::PortBase::Disconnected, CORBA::SystemException)
	{
	  T* tmp;

	  if (value >>= tmp)
		m_Buffer.put(*tmp);
	  return;
	}
	
	/*!
	 * @if jp
	 *
	 * @brief InPort ��Υ�󥰥Хåե����ͤ�����
	 *
	 * InPort ��Υ�󥰥Хåե����ͤ��������롣
	 *
	 * @else
	 *
	 * @brief Initialize ring buffer value of InPort
	 *
	 * @endif
	 */
	virtual void initBuffer(T& value)
	{
	  for (int i = 0 ; i <= m_Buffer.buff_length(); i++)
		{
		  m_Buffer.put(value);
		}
	}


	/*!
	 * @if jp
	 *
	 * @brief �Х���ɤ��줿 T �����ѿ��� InPort �Хåե��κǿ��ͤ��ɤ߹���
	 *
	 * �Х���ɤ��줿 T ���Υǡ����� InPort �κǿ��ͤ��ɤ߹��ࡣ
	 * ���󥹥ȥ饯���� T �����ѿ��� InPort ���Х���ɤ���Ƥ��ʤ���Фʤ�ʤ���
	 * ���Υ᥽�åɤϥݥ�⡼�ե��å��˻��Ѥ�����������Ȥ��Ƥ��뤿�ᡢ
	 * ���˰�¸���ʤ�����������ͤȤʤäƤ��롣
	 *
	 * @else
	 *
	 * @brief Read into bound T-type data from current InPort
	 *
	 * @endif
	 */
	virtual void read_pm()
	{
	  m_Value = m_Buffer.get_new();
	  return;
	};
	
	/*!
	 * @if jp
	 *
	 * @brief �Х���ɤ��줿 T �����ѿ��� InPort �Хåե��κǿ��ͤ��ɤ߹���
	 *
	 * �Х���ɤ��줿 T ���Υǡ����� InPort �κǿ��ͤ��ɤ߹��ࡣ
	 * ���󥹥ȥ饯���� T �����ѿ��� InPort ���Х���ɤ���Ƥ��ʤ���Фʤ�ʤ���
	 *
	 * @else
	 *
	 * @brief Read into bound T-type data from current InPort
	 *
	 * @endif
	 */
	virtual T read()
	{
	  m_Value = m_Buffer.get_new();
	  return m_Value;
	};
	
	/*!
	 * @if jp
	 *
	 * @brief T ���Υǡ����� InPort �κǿ��ͥǡ������ɤ߹���
	 *
	 * @param rhs InPort �Хåե������ͤ��ɤ߹��� T ���ѿ�
	 *
	 * @else
	 *
	 * @brief Read from InPort buffer to type-T variable
	 *
	 * @param rhs type-T variable which is wrote from InPort buffer
	 *
	 * @endif
	 */
	virtual bool operator>>(T& rhs)
	{
	  rhs = m_Buffer.get_new();
	  return true;
	};

	/*!
	 * @if jp
	 *
	 * @brief �ǿ��ǡ�����̤�ɤο������ǡ������ɤ�����Ĵ�٤�
	 *
	 * @else
	 *
	 * @brief Check the newest data is new data to be read.
	 *
	 * @endif
	 */
	virtual bool isNew()
	{
	  return m_Buffer.is_new();
	}


	/*!
	 * @if jp
	 *
	 * @brief ̤�ɤο������ǡ��������������
	 *
	 * @else
	 *
	 * @brief Get number of new data to be read.
	 *
	 * @endif
	 */
	virtual int getNewDataLen()
	{
	  return m_Buffer.new_data_len();
	}


	/*!
	 * @if jp
	 *
	 * @brief ̤�ɤο������ǡ������������
	 *
	 * @else
	 *
	 * @brief Get new data to be read.
	 *
	 * @endif
	 */
	virtual std::vector<T> getNewList()
	{
	  return m_Buffer.get_new_list();
	}
	

	/*!
	 * @if jp
	 *
	 * @brief ̤�ɤο������ǡ�����ս�(��->��)�Ǽ�������
	 *
	 * @else
	 *
	 * @brief Get new data to be read.
	 *
	 * @endif
	 */
	virtual std::vector<T> getNewListReverse()
	{
	  return m_Buffer.get_new_rlist();
	}
	

  private:
	/*!
	 * @if jp
	 * @brief �Х���ɤ���� T �����ѿ��ؤλ���
	 * @else
	 * @brief reference to type-T value bound this OutPort
	 * @endif
	 */
	T& m_Value;

	/*!
	 * @if jp
	 * @brief T ���Υ��ߡ��ѿ�
	 * @else
	 * @brief Dummy variable of type-T
	 * @endif
	 */
	T  m_Dummy;

	/*!
	 * @if jp
	 * @brief T ���ΰ���ѿ�
	 * @else
	 * @brief Tempolary variable of type-T
	 * @endif
	 */
	T* m_Tmp;

	/*!
	 * @if jp
	 * @brief �Хåե�
	 * @else
	 * @brief Buffer
	 * @endif
	 */
	RingBuffer<T> m_Buffer;

  };
  
}; // End of namesepace RTM

#endif // RtcInPort_h
