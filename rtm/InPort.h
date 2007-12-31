// -*- C++ -*-
/*!
 * @file InPort.h
 * @brief InPort template class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPort.h,v 1.6.4.4 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6.4.3  2007/09/21 09:15:16  n-ando
 * Now InPort's default buffer is RingBuffer.
 *
 * Revision 1.6.4.2  2007/08/20 05:15:39  n-ando
 * Now default buffer is RingBuffer instead of NullBuffer.
 *
 * Revision 1.6.4.1  2007/07/20 15:54:50  n-ando
 * Now ACE_OS::gettimeofday() is used for win32 porting.
 *
 * Revision 1.6  2007/01/06 17:47:51  n-ando
 * Some changes.
 * - Callback declarations are changed.
 * - Return value of write().
 *
 * Revision 1.5  2006/12/02 18:37:29  n-ando
 * A trivial fix.
 *
 * Revision 1.4  2006/11/07 09:26:12  n-ando
 * Renamed RtcInPort.h to InPort.h.
 *
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

#include <string>
#include <vector>
#include <iostream>
#include <rtm/BufferBase.h>
#include <rtm/RingBuffer.h>
#include <rtm/PortCallBack.h>
#include <rtm/RTC.h>

#define TIMEOUT_TICK_USEC 10
#define USEC_PER_SEC 1000000

namespace RTC
{
  /*!
   * @if jp
   *
   * @class InPort
   *
   * @brief InPort �ƥ�ץ졼�ȥ��饹
   * 
   * InPort �μ����Ǥ��� InPort<T> �Υƥ�ץ졼�ȥ��饹��
   * <T> ��RTCDataType.idl �ˤ��������Ƥ��뷿�ǡ����ФȤ���
   * Time ���� tm , ����� T���� data ����Ĺ�¤�ΤǤʤ��ƤϤʤ�ʤ���
   * InPort �������˥�󥰥Хåե�����������������������줿�ǡ�����缡
   * ���Υ�󥰥Хåե��˳�Ǽ���롣��󥰥Хåե��Υ������ϥǥե���Ȥ�64��
   * �ʤäƤ��뤬�����󥹥ȥ饯�������ˤ�ꥵ��������ꤹ�뤳�Ȥ��Ǥ��롣
   * �ǡ����ϥե饰�ˤ�ä�̤�ɡ����ɾ��֤��������졢isNew(), getNewDataLen()
   * getNewList(), getNewListReverse() ���Υ᥽�åɤˤ��ϥ�ɥ�󥰤��뤳�Ȥ�
   * �Ǥ��롣
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class InPort
   *
   * @brief InPort template class
   *
   * This class template provides interfaces to input port.
   * Component developer can define input value, which act as input
   * port from other components, using this template.
   * This is class template. This class have to be incarnated class as port
   * value types. This value types are previously define RtComponent IDL.
   * ex. type T: TimedFload, TimedLong etc... 
   *
   * @since 0.2.0
   *
   * @endif
   */
  template <class DataType,
	    template <class DataType> class Buffer = RingBuffer >
  class InPort
    : public Buffer<DataType>
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     * �ѥ�᡼���Ȥ���Ϳ������ T �����ѿ��˥Х���ɤ���롣
     *
     * @param name InPort ̾��InPortBase:name() �ˤ�껲�Ȥ���롣
     * @param value ���� InPort �˥Х���ɤ���� T �����ѿ�
     * @param bufsize InPort �����Υ�󥰥Хåե��ΥХåե�Ĺ(�ǥե������:64)
     * @param read_block �ɹ��֥�å��ե饰��
     *        �ǡ����ɹ�����̤�ɥǡ������ʤ���硢���Υǡ��������ޤǥ֥�å�����
     *        ���ɤ���������(�ǥե������:false)
     * @param write_block ����֥�å��ե饰��
     *        �ǡ���������˥Хåե����ե�Ǥ��ä���硢�Хåե��˶������Ǥ���
     *        �ޤǥ֥�å����뤫�ɤ���������(�ǥե������:false)
     * @param read_timeout �ɹ��֥�å�����ꤷ�Ƥ��ʤ����Ρ��ǡ����ɼ西����
     *        �����Ȼ���(�ߥ���)(�ǥե������:0)
     * @param write_timeout ����֥�å�����ꤷ�Ƥ��ʤ����Ρ��ǡ������������
     *        �����Ȼ���(�ߥ���)(�ǥե������:0)
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
    InPort(const char* name, DataType& value,
	   int bufsize=64, 
	   bool read_block = false, bool write_block = false,
	   int read_timeout = 0, int write_timeout = 0)
      : Buffer<DataType>(bufsize),
	m_name(name), m_value(value),
	m_readBlock(read_block),   m_readTimeout(read_timeout),
	m_writeBlock(write_block), m_writeTimeout(write_timeout),
	m_OnWrite(NULL), m_OnWriteConvert(NULL),
	m_OnRead(NULL),  m_OnReadConvert(NULL),
	m_OnOverflow(NULL), m_OnUnderflow(NULL)
    {
    };
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     *
     * @else
     *
     * @brief A destructor
     *
     * @endif
     */
    virtual ~InPort(){};
    
    /*!
     * @if jp
     *
     * @brief �ݡ���̾�Τ�������롣
     *
     * �ݡ���̾�Τ�������롣
     *
     * @return �ݡ���̾��
     *
     * @else
     *
     * @endif
     */
    virtual const char* name()
    {
      return m_name.c_str();
    }
    
    /*!
     * @if jp
     *
     * @brief DataPort ���ͤ�񤭹���
     *
     * DataPort ���ͤ�񤭹��ࡣ
     *
     * - ������Хå��ե��󥯥� OnWrite �����åȤ���Ƥ����硢
     *   InPort ���ݻ�����Хåե��˽񤭹������� OnWrite ���ƤФ�롣
     * - InPort ���ݻ�����Хåե��������С��ե��򸡽ФǤ���Хåե��Ǥ��ꡢ
     *   ���ġ��񤭹���ݤ˥Хåե��������С��ե��򸡽Ф�����硢
     *   ������Хå��ե��󥯥� OnOverflow ���ƤФ�롣
     * - ������Хå��ե��󥯥� OnWriteConvert �����åȤ���Ƥ����硢
     *   �Хåե��񤭹��߻��ˡ�OnWriteConvert �� operator()() ������ͤ�
     *   �Хåե��˽񤭹��ޤ�롣
     * - setWriteTimeout() �ˤ��񤭹��߻��Υ����ॢ���Ȥ����ꤵ��Ƥ����硢
     *   �����ॢ���Ȼ��֤����Хåե��ե���֤��������Τ��Ԥ���
     *   OnOverflow�����åȤ���Ƥ���Ф����ƤӽФ�����롣
     *
     * @param value ����оݥǡ���
     *
     * @return ����������(�������:true���������:false)
     *
     * @else
     *
     * @brief 
     *
     * @endif
     */
    bool write(const DataType& value)
    {
      if (m_OnWrite != NULL) (*m_OnWrite)(value);      
      
      long int timeout = m_writeTimeout;
      
      timeval tm_cur, tm_pre;
      ACE_Time_Value tt;
      tt = ACE_OS::gettimeofday();
      tm_pre = tt.operator timeval();
      
      // blocking and timeout wait
      while (m_writeBlock && this->isFull())
	{
	  if (m_writeTimeout < 0) 
	    {
	      usleep(TIMEOUT_TICK_USEC);
	      continue;
	    }
	  
	  // timeout wait
	  ACE_Time_Value tt;
	  tt = ACE_OS::gettimeofday();
	  tm_cur = tt.operator timeval();
	  long int sec (tm_cur.tv_sec  - tm_pre.tv_sec);
	  long int usec(tm_cur.tv_usec - tm_pre.tv_usec);
	  
	  timeout -= (sec * USEC_PER_SEC + usec);
	  if (timeout < 0) break;
	  
	  tm_pre = tm_cur;
	  usleep(TIMEOUT_TICK_USEC);
	}
      
      if (this->isFull() && m_OnOverflow != NULL)
	{
	  (*m_OnOverflow)(value);
	  return false;
	}
      
      if (m_OnWriteConvert == NULL) 
	{
	  this->put(value);
	}
      else
	{
	  this->put((*m_OnWriteConvert)(value));
	}
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief DataPort �����ͤ��ɤ߽Ф�
     *
     * DataPort �����ͤ��ɤ߽Ф�
     *
     * - ������Хå��ե��󥯥� OnRead �����åȤ���Ƥ����硢
     *   DataPort ���ݻ�����Хåե������ɤ߽Ф����� OnRead ���ƤФ�롣
     * - DataPort ���ݻ�����Хåե�����������ե��򸡽ФǤ���Хåե��ǡ�
     *   ���ġ��ɤ߽Ф��ݤ˥Хåե�����������ե��򸡽Ф�����硢
     *   ������Хå��ե��󥯥� OnUnderflow ���ƤФ�롣
     * - ������Хå��ե��󥯥� OnReadConvert �����åȤ���Ƥ����硢
     *   �Хåե��񤭹��߻��ˡ�OnReadConvert �� operator()() ������ͤ�
     *   read()������ͤȤʤ롣
     * - setReadTimeout() �ˤ���ɤ߽Ф����Υ����ॢ���Ȥ����ꤵ��Ƥ����硢
     *   �Хåե���������ե����֤���������ޤǥ����ॢ���Ȼ��֤����Ԥ���
     *   OnUnderflow�����åȤ���Ƥ���Ф����ƤӽФ������
     *
     * @return �ɤ߽Ф����ǡ���
     *
     * @else
     *
     * @brief [CORBA interface] Put data on InPort
     *
     * @endif
     */
    DataType read()
    {
      if (m_OnRead != NULL) (*m_OnRead)();
      
      long int timeout = m_readTimeout;
      
      timeval tm_cur, tm_pre;
      ACE_Time_Value tt;
      tt = ACE_OS::gettimeofday();
      tm_pre = tt.operator timeval();
      
      // blocking and timeout wait
      while (m_readBlock && this->isEmpty())
	{
	  if (m_readTimeout < 0)
	    {
	      usleep(TIMEOUT_TICK_USEC);
	      continue;
	    }
	  
	  // timeout wait
	  ACE_Time_Value tt;
	  tt = ACE_OS::gettimeofday();
	  tm_cur = tt.operator timeval();
	  long int sec (tm_cur.tv_sec  - tm_pre.tv_sec);
	  long int usec(tm_cur.tv_usec - tm_pre.tv_usec);
	  
	  timeout -= (sec * USEC_PER_SEC + usec);
	  if (timeout < 0) break;
	  
	  tm_pre = tm_cur;
	  usleep(TIMEOUT_TICK_USEC);
	}
      
      if (this->isEmpty() && m_OnUnderflow != NULL)
	{
	  m_value = (*m_OnUnderflow)();
	  return m_value;
	}
      
      if (m_OnReadConvert == NULL) 
	{
	  m_value = this->get();
	  return m_value;
	}
      else
	{
	  m_value = (*m_OnReadConvert)(this->get());
	  return m_value;
	}
      // never comes here
      return m_value;
    }
    
    /*!
     * @if jp
     *
     * @brief InPort ��Υ�󥰥Хåե����ͤ�����
     *
     * InPort ��Υ�󥰥Хåե����ͤ���ꤷ���ͤǽ�������롣
     * (�����Ǥϥ����ȥ�����)
     *
     * @param value ������оݥǡ���
     *
     * @else
     *
     * @brief Initialize ring buffer value of InPort
     *
     * @endif
     */
    virtual void init(DataType& value)
    {
      //      m_buffer.init(value);
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
    void update()
    {
      try
	{
	  m_value = this->get();
	}
      catch (...)
	{
	  if (m_OnUnderflow != NULL) (*m_OnUnderflow)();
	}
      return;
    };
    
    /*!
     * @if jp
     *
     * @brief T ���Υǡ����� InPort �κǿ��ͥǡ������ɤ߹���
     *
     * InPort �����ꤵ��Ƥ���ǿ��ǡ������ɤ߹��ߡ�
     * ���ꤵ�줿�ǡ����ѿ������ꤹ�롣
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
    void operator>>(DataType& rhs)
    {
      rhs = read();
      return;
    }
    
    /*!
     * @if jp
     *
     * @brief T ���Υǡ����� DataPort �ؽ񤭹���
     *
     * ���ꤵ�줿 T ���Υǡ�����DataPort�˽񤭹��ࡣ
     *
     * @param value DaraPort �ؽ񤭹��� T ���ѿ�
     *
     * @else
     *
     * @endif
     */
    void operator<<(DataType& value)
    {
      write(value);
      return;
    }
    
    /***
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
    /*
      virtual int getNewDataLen()
      {
      return m_buffer->new_data_len();
      }
    */
    
    /***
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
    /*
      virtual std::vector<T> getNewList()
      {
      return m_buffer.get_new_list();
      }
    */
    
    /***
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
    /*
      virtual std::vector<T> getNewListReverse()
      {
      return m_buffer.get_new_rlist();
      }
    */
    
    /*!
     * @if jp
     *
     * @brief InPort �Хåե��إǡ������ϻ��Υ�����Хå�������
     *
     * InPort �����ĥХåե��˥ǡ�����put���줿�Ȥ��˸ƤФ�륳����Хå�
     * ���֥������Ȥ����ꤹ�롣���ꤵ��륳����Хå����֥������Ȥ�
     * InPort<DataType>::OnPut���饹��Ѿ��������� const DataType& ��
     * ����� void �� operator() �ؿ�����������Ƥ���ɬ�פ����롣
     *
     * struct MyOnPutCallback : public InPort<DataType> {<br>
     *   void operator()(const DataType data) {<br>
     *     ����<br>
     *   }<br>
     * };<br>
     * �Τ褦�˥�����Хå����֥������Ȥ��������<br>
     * <br> 
     * m_inport.setOnPut(new MyOnPutCallback());<br>
     * �Τ褦�˥�����Хå����֥������Ȥ򥻥åȤ��롣
     *
     * @param on_write OnWrite&lt;DataType&gt;���Υ��֥�������
     *
     * @else
     *
     * @brief Get new data to be read.
     *
     * @endif
     */
    inline void setOnWrite(OnWrite<DataType>* on_write)
    {
      m_OnWrite = on_write;
    }
    
    /*!
     * @if jp
     *
     * @brief InPort �Хåե��إǡ����񤭹��߻��Υ�����Хå�������
     *
     * InPort �����ĥХåե��˥ǡ����񤭹��ޤ����˸ƤФ�륳����Хå�
     * ���֥������Ȥ����ꤹ�롣�Хåե��ˤϥ�����Хå����֥������Ȥ�
     * ����ͤ����ꤵ��롣
     * 
     * @param on_wconvert OnWriteConvert&lt;DataType&gt;���Υ��֥�������
     *
     * @else
     *
     * @endif
     */
    inline void setOnWriteConvert(OnWriteConvert<DataType>* on_wconvert)
    {
      m_OnWriteConvert = on_wconvert;
    }
    
    /*!
     * @if jp
     *
     * @brief InPort �Хåե��إǡ����ɤ߹��߻��Υ�����Хå�������
     *
     * InPort �����ĥХåե�����ǡ������ɤ߹��ޤ��ľ���˸ƤФ�륳����Хå�
     * ���֥������Ȥ����ꤹ�롣
     * 
     * @param on_read OnRead&lt;DataType&gt;���Υ��֥�������
     *
     * @else
     *
     * @endif
     */
    inline void setOnRead(OnRead<DataType>* on_read)
    {
      m_OnRead = on_read;
    }
    
    /*!
     * @if jp
     *
     * @brief InPort �Хåե��إǡ����ɤ߽Ф����Υ�����Хå�������
     *
     * InPort �����ĥХåե�����ǡ������ɤ߽Ф����ݤ˸ƤФ�륳����Хå�
     * ���֥������Ȥ����ꤹ�롣������Хå����֥������Ȥ�����ͤ�read()�᥽�å�
     * �θƽз�̤Ȥʤ롣
     * 
     * @param on_rconvert OnReadConvert&lt;DataType&gt;���Υ��֥�������
     *
     * @else
     *
     * @endif
     */
    inline void setOnReadConvert(OnReadConvert<DataType>* on_rconvert)
    {
      m_OnReadConvert = on_rconvert;
    }
    
    /*!
     * @if jp
     *
     * @brief InPort �Хåե��إХåե������С��ե����Υ�����Хå�������
     *
     * InPort �����ĥХåե��ǥХåե������С��ե������Ф��줿�ݤ˸ƤӽФ����
     * ������Хå����֥������Ȥ����ꤹ�롣
     * 
     * @param on_overflow OnOverflow&lt;DataType&gt;���Υ��֥�������
     *
     * @else
     *
     * @endif
     */
    inline void setOnOverflow(OnOverflow<DataType>* on_overflow)
    {
      m_OnOverflow = on_overflow;
    }
    
    /*!
     * @if jp
     *
     * @brief InPort �Хåե��إХåե���������ե����Υ�����Хå�������
     *
     * InPort �����ĥХåե��ǥХåե���������ե������Ф��줿�ݤ˸ƤӽФ����
     * ������Хå����֥������Ȥ����ꤹ�롣
     * 
     * @param on_underflow OnUnderflow&lt;DataType&gt;���Υ��֥�������
     *
     * @else
     *
     * @endif
     */
    inline void setOnUnderflow(OnUnderflow<DataType>* on_underflow)
    {
      m_OnUnderflow = on_underflow;
    }
    
  private:
    /*!
     * @if jp
     * @brief �ݡ���̾
     * @else
     * @berif Port's name
     * @else
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief �Х���ɤ���� T �����ѿ��ؤλ���
     * @else
     * @brief reference to type-T value bound this OutPort
     * @endif
     */
    DataType& m_value;
    
    /*!
     * @if jp
     * @brief �Хåե�
     * @else
     * @brief Buffer
     * @endif
     */
    //    Buffer<DataType> m_buffer;
    
    bool m_readBlock;
    long int m_readTimeout;
    bool m_writeBlock;
    long int m_writeTimeout;
    
    /*!
     * @if jp
     * @brief OnWrite ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief OnWrite callback functor pointer
     * @endif
     */
    OnWrite<DataType>* m_OnWrite;
    
    /*!
     * @if jp
     * @brief OnWriteConvert ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief OnWriteConvert callback functor pointer
     * @endif
     */
    OnWriteConvert<DataType>* m_OnWriteConvert;
    
    /*!
     * @if jp
     * @brief OnRead ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief OnRead callback functor pointer
     * @endif
     */
    OnRead<DataType>* m_OnRead;
    
    /*!
     * @if jp
     * @brief OnReadConvert ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief OnReadConvert callback functor pointer
     * @endif
     */
    OnReadConvert<DataType>* m_OnReadConvert;
    
    /*!
     * @if jp
     * @brief OnOverflow ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief OnOverflow callback functor pointer
     * @endif
     */
    OnOverflow<DataType>* m_OnOverflow;
    
    /*!
     * @if jp
     * @brief OnUnderflow ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief OnUnderflow callback functor pointer
     *
     * @endif
     */
    OnUnderflow<DataType>* m_OnUnderflow;
  };
}; // End of namesepace RTM

#endif // RtcInPort_h
