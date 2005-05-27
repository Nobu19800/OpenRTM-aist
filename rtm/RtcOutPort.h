// -*- C++ -*-
/*!
 * @file RtcOutPort.h
 * @brief OutPort template class
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
 * $Id: RtcOutPort.h,v 1.3 2005-05-27 07:34:21 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2005/05/16 06:32:42  n-ando
 * - ACE_OS::clock_gettime() was replaced with getFileTime() function.
 *   High resolution ACE_OS::clock_gettime() function is not implemented
 *   in Windows. By using file time access functions, high resolution time
 *   can be obtained.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcOutPort_h
#define RtcOutPort_h

#define ACE_HAS_CLOCK_GETTIME

#include "rtm/RtcOutPortBase.h"
#include "rtm/idl/RTCDataTypeSkel.h"
#include <ace/OS.h>
#include <ace/Time_Value.h>
#include <iostream>

#define DEFAULT_BUFFER_SIZE 64
#ifdef WIN32
#include <atltime.h>
#endif //WIN32

namespace RTM {
  /*!
   * @if jp
   *
   * @class OutPortAny
   *
   * @brief OutPort �ƥ�ץ졼�ȥ��饹
   * 
   * OutPort �μ����Ǥ��� OutPortAny<T> �Υƥ�ץ졼�ȥ��饹��
   * <T> ��RTCDataType.idl �ˤ��������Ƥ��뷿�ǡ����ФȤ���
   * Time ���� tm , ����� T���� data ����Ĺ�¤�ΤǤʤ��ƤϤʤ�ʤ���
   *
   * @else
   *
   * @class InPortAny
   *
   * @brief OutPort template class
   *
   * This class: OutPortAny<T> which is a implementations of OutPort
   * This class template provides interfaces to output channel.
   * Component developer can define output value, which act as output
   * channel to other components, using this template.
   * This is class template. This class have to be incarnated class as channel
   * value types. This value types are previously define RtComponent IDL.
   * ex. type T: TimedFload, TimedLong etc... 
   *
   * @endif
   */
  template <class T> class OutPortAny
	: public OutPortBase
  {
  public:
	/*!
	 * @if jp
	 *
	 * @brief OutPortAny ���饹���󥹥ȥ饯��
	 *
	 * OutPortAny<T> ���饹�Υ��󥹥ȥ饯����
	 * �ѥ�᡼���Ȥ���Ϳ������ T �����ѿ��˥Х���ɤ���롣
	 *
	 * @param name OutPort ̾��OutPortBase:name() �ˤ�껲�Ȥ���롣
	 * @param value ���� OutPort �˥Х���ɤ���� T �����ѿ�
	 * @param bufsize OutPort �����Υ�󥰥Хåե��ΥХåե�Ĺ
	 *
	 * @else
	 *
	 * @brief A constructor.
	 *
	 * Setting channel name and registering channel value.
	 *
	 * @param name A name of the OutPort. This name is referred by
	 *             OutPortBase::name().
	 * @param value A channel value related with the channel.
	 * @param bufsize Buffer length of internal ring buffer of OutPort 
	 *
	 * @endif
	 */
	OutPortAny(const char* name, T& value, int bufsize=DEFAULT_BUFFER_SIZE)
	  : m_Buffer(bufsize, value), m_Value(value)
	{
	  // Set PortProfile
	  m_Profile.name = CORBA::string_dup(name);
	  CORBA::Any var;
	  var <<= m_Value;
	  m_Profile.port_type = var.type();
	  
	  // Initializing ring buffer
	  for (int i = 0 ; i < m_Buffer.buff_length(); i++)
		{
		  m_Buffer.put(m_Value);
		}
	}
	
	/*!
	 * @if jp
	 *
	 * @brief OutPortAny ���饹���󥹥ȥ饯��
	 *
	 * OutPortAny<T> ���饹�Υ��󥹥ȥ饯����
	 * 
	 *
	 * @param name OutPort ̾��OutPortBase:name() �ˤ�껲�Ȥ���롣
	 * @param bufsize OutPort �����Υ�󥰥Хåե��ΥХåե�Ĺ
	 *
	 * @else
	 *
	 * @brief A constructor.
	 *
	 * Setting channel name and registering channel value.
	 *
	 * @param name A name of the OutPort. This name is referred by
	 *             OutPortBase::name().
	 * @param bufsize Buffer length of internal ring buffer of OutPort 
	 *
	 * @endif
	 */
	OutPortAny(const char* name, int bufsize=DEFAULT_BUFFER_SIZE)
	  : m_Buffer(bufsize, m_Dummy), m_Value(m_Dummy)
	{
	  // Set PortProfile
	  m_Profile.name = CORBA::string_dup(name);
	  CORBA::Any var;
	  var <<= m_Value;
	  m_Profile.port_type = var.type();
	  
	  // Initializing ring buffer
	  for (int i = 0 ; i < m_Buffer.buff_length(); i++)
		{
		  m_Buffer.put(m_Value);
		}
	}
	
	
	/*!
	 * @if jp
	 *
	 * @brief OutPortAny ���饹�ǥ��ȥ饯��
	 *
	 * OutPortAny<T> ���饹�Υǥ��ȥ饯����
	 *
	 * @else
	 *
	 * @brief A destructor
	 *
	 * @endif
	 */
	virtual ~OutPortAny(){};
	
	/*!
	 * @if jp
	 *
	 * @brief [CORBA interface] ���ߤ� OutPort �κǿ����ͤ����
	 *
	 * ���ߤ� OutPort �κǿ����ͤ��������
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get current data of OutPort
	 *
	 * @endif
	 */
	CORBA::Any* get()
	  throw (CORBA::SystemException)
	{
	  ACE_TRACE("OutPortBase::get()");
	  CORBA::Any_var tmp = new CORBA::Any();
	  tmp <<= m_Buffer.get_new();
	  return tmp._retn();
	}
	
	/*!
	 * @if jp
	 *
	 * @brief ���ߤ� OutPort ���ͤ򥵥֥����饤�Ф�ž��
	 *
	 * ���ߤ� OutPort ���ͤ򥵥֥����饤�Ф�ž������
	 *
	 * @else
	 *
	 * @brief Push current data to subscribers
	 *
	 * @endif
	 */
	//	RtmRes push(const InPort_ptr& inport, SubscriptionID subsid)
	RtmRes push(InPort_ptr inport, std::string subsid)
	{
	  ACE_TRACE("OutPortBase::push()");
	  
	  if (CORBA::is_nil(inport)) 
		{
		  ACE_DEBUG((LM_DEBUG, "Invalid object reference: inport"));
		  return RTM_ERR;
		}

	  try
		{
		  CORBA::Any val;
		  val <<= m_Buffer.get_new();
		  
		  if (inport != NULL)
			{
			  inport->put(val);
			}
		}
	  catch(CORBA::SystemException& se)
		{
		  // std::cout << "push(): CORBA System Exception." << e << endl;
		  se;
		  // Subscribers already locked
		  unsubscribeNoLocked(subsid.c_str());
		  return RTM_ERR;
		}
	  catch(RTM::PortBase::Disconnected& dce)
		{
		  //		  ACE_DEBUG((LM_DEBUG, "Disconnected."));
		  dce;
		  // Subscribers already locked
		  unsubscribeNoLocked(subsid.c_str());
		  return RTM_ERR;
		}
	  return RTM_OK;
	}
	
	
	
	/*!
	 * @if jp
	 *
	 * @brief OutPort ��Υ�󥰥Хåե����ͤ�����
	 *
	 * OutPort ��Υ�󥰥Хåե����ͤ��������롣
	 *
	 * @else
	 *
	 * @brief Initialize ring buffer value of OutPort
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
	

#ifdef WIN32
	void getFileTime(struct timespec &ts) {
	  ULARGE_INTEGER tmpbuf;
	  CFileTime  myFT;
	  ULONGLONG  s1;
	  ULONGLONG  s2;
	  ULONGLONG  s3;
	  SYSTEMTIME time1970;
	  FILETIME   file1970;
	  
	  time1970.wYear = 1970;
	  time1970.wMonth = 1;
	  time1970.wDayOfWeek = 0;
	  time1970.wDay = 1;
	  time1970.wHour = 0;
	  time1970.wMinute = 0;
	  time1970.wSecond = 0;
	  time1970.wMilliseconds = 0;
	  SystemTimeToFileTime(&time1970,&file1970);
	  CFileTime  oldFT(file1970);
	  
	  myFT = CFileTime::GetCurrentTime();
	  tmpbuf.LowPart = myFT.dwLowDateTime;
	  tmpbuf.HighPart = myFT.dwHighDateTime;
	  s1 = s2 = tmpbuf.QuadPart;
	  tmpbuf.LowPart = oldFT.dwLowDateTime;
	  tmpbuf.HighPart = oldFT.dwHighDateTime;
	  s3 = tmpbuf.QuadPart;
	  s1 = s2 = s1 - s3;
	  s1 = (s1 / CFileTime::Second )*CFileTime::Second;
	  s2 = (s2 - s1)*100;
	  s1 = (s1 / CFileTime::Second);
	  
	  ts.tv_sec = (long) s1;
	  ts.tv_nsec = (long) s2;
	};
#endif

	/*!
	 * @if jp
	 *
	 * @brief �Х���ɤ��줿 T ���Υǡ����� OutPort �κǿ��ͤȤ��ƽ񤭹���
	 *
	 * �Х���ɤ��줿 T ���Υǡ����� OutPort �κǿ��ͤȤ��ƽ񤭹��ࡣ
	 * ���󥹥ȥ饯���� T �����ѿ��� OutPort ���Х���ɤ���Ƥ���ɬ�פ����롣
	 *
	 * @else
	 *
	 * @brief Write into current OutPort from bound T-type data
	 *
	 * @endif
	 */
	virtual void write()
	{
	  struct timespec ts;
#ifdef WIN32
	  getFileTime(ts);
#else // WIN32
	  ACE_OS::clock_gettime(CLOCK_REALTIME, &ts);
#endif // WIN32
	  m_Value.tm.sec = ts.tv_sec;
	  m_Value.tm.nsec = ts.tv_nsec;
	  m_Buffer.put(m_Value);
	  updateall();
	};


	/*!
	 * @if jp
	 *
	 * @brief �Х���ɤ��줿 T ���Υǡ����� OutPort �κǿ��ͤȤ��ƽ񤭹���
	 *
	 * �Х���ɤ��줿 T ���Υǡ����� OutPort �κǿ��ͤȤ��ƽ񤭹��ࡣ
	 * ���󥹥ȥ饯���� T �����ѿ��� OutPort ���Х���ɤ���Ƥ���ɬ�פ����롣
	 * ���Υ᥽�åɤϥݥ�⡼�ե��å��˻��Ѥ�����������Ȥ��Ƥ��뤿�ᡢ
	 * ���˰�¸���ʤ�����������ͤȤʤäƤ��롣
	 *
	 * @else
	 *
	 * @brief Write into current OutPort from bound T-type data
	 *
	 * @endif
	 */
	virtual void write_pm()
	{
	  write();
	};
	
	
	/*!
	 * @if jp
	 *
	 * @brief T ���Υǡ����� OutPort �κǿ��ͤȤ��ƽ񤭹���
	 *
	 * �����Ȥ���Ϳ����줿 T ���Υǡ����� OutPort �κǿ��ͤȤ��ƽ񤭹��ࡣ
	 *
	 * @param value OutPort �Хåե��˽񤭹��� T ������
	 *
	 * @else
	 *
	 * @brief Writing a argument value to OutPort buffer
	 *
	 * Calling this method, argument value "T& value" is transferred to OutPort.
	 *
	 * @param value type-T value write into OutPort buffer
	 *
	 * @endif
	 */
	virtual void write(T value)
	{
	  struct timespec ts;
#ifdef WIN32
	  getFileTime(ts);
#else // WIN32
	  ACE_OS::clock_gettime(CLOCK_REALTIME, &ts);
#endif // WIN32
	  value.tm.sec = ts.tv_sec;
	  value.tm.nsec = ts.tv_nsec;
	  m_Buffer.put(value);
	  updateall();
	};
	
	
	/*!
	 * @if jp
	 *
	 * @brief T ���Υǡ����� OutPort �κǿ��ͤȤ��ƽ񤭹���
	 *
	 * �����Ȥ���Ϳ����줿 T ���Υǡ����� OutPort �κǿ��ͤȤ��ƽ񤭹��ࡣ
	 *
	 * @param value OutPort �Хåե��˽񤭹��� T ������
	 *
	 * @else
	 *
	 * @brief Writing a argument value to OutPort buffer
	 *
	 * Calling this method, argument value "T& value" is transferred to OutPort.
	 *
	 * @param value type-T value write into OutPort buffer
	 *
	 * @endif
	 */
	virtual void operator<<(T& value)
	{
	  struct timespec ts;
#ifdef WIN32
	  getFileTime(ts);
#else // WIN32
	  ACE_OS::clock_gettime(CLOCK_REALTIME, &ts);
#endif // WIN32
	  value.tm.sec = ts.tv_sec;
	  value.tm.nsec = ts.tv_nsec;
	  m_Buffer.put(value);
	  updateall();
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
	T m_Dummy;
	
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

#endif // RtcOutputChannel_h
