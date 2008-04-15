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
   * <T> ��BasicDataType.idl �ˤ��������Ƥ��뷿�ǡ����ФȤ���
   * Time ���� tm , ����� T���� data ����Ĺ�¤�ΤǤʤ��ƤϤʤ�ʤ���
   * InPort �������˥�󥰥Хåե�����������������������줿�ǡ�����缡
   * ���Υ�󥰥Хåե��˳�Ǽ���롣��󥰥Хåե��Υ������ϥǥե���Ȥ�64��
   * �ʤäƤ��뤬�����󥹥ȥ饯�������ˤ�ꥵ��������ꤹ�뤳�Ȥ��Ǥ��롣
   * �ǡ����ϥե饰�ˤ�ä�̤�ɡ����ɾ��֤��������졢isNew(), write(), read(),
   * isFull(), isEmpty() ���Υ᥽�åɤˤ��ϥ�ɥ�󥰤��뤳�Ȥ��Ǥ��롣
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class InPort
   *
   * @brief InPort template class
   *
   * This is a template class that implements InPort.
   * <T> is the type defined in BasicDataType.idl and must be the structure which
   * has both Time type tm and type-T data as a member. InPort has a ring
   * buffer internally, and stores the received data externally in this buffer
   * one by one. The size of ring buffer can be specified according to 
   * the argument of constructor, though the default size is 64. Unread
   * data and data which is already read are managed with the flag, and the
   * data can be handled by the isNew(), write(), read(), isFull() and isEmpty()
   * method etc. 
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
     * constructor.
     * This is bound to type-T variable given as a parameter.
     *
     * @param name A name of the InPort. This name is referred by
     *             InPortBase::name().
     * @param value type-T variable that is bound to this InPort.
     * @param bufsize Buffer length of internal ring buffer of InPort
     *                (The default value:64)
     * @param read_block Flag of reading block.
     *                   When there are not unread data at reading data,
     *                   set whether to block data until receiving the next 
     *                   data. (The default value:false)
     * @param write_block Flag of writing block.
     *                    If the buffer was full at writing data, set whether 
     *                    to block data until the buffer has space. 
     *                    (The default value:false)
     * @param read_timeout Data reading timeout time (millisecond) 
     *                     when not specifying read blocking.
     *                     (The default value:0)
     * @param write_timeout Data writing timeout time (millisecond)
     *                      when not specifying writing block.
     *                      (The default value:0)
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
     * @brief Destructor
     *
     * Destructor
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
     * @brief Get port name
     *
     * Get port name.
     *
     * @return The port name
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
     *   �Хåե��񤭹��߻��ˡ�OnWriteConvert �� operator() ������ͤ�
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
     * @brief  Write the value to DataPort
     *
     * Write the value to DataPort
     *
     * - When callback functor OnWrite is already set, OnWrite will be
     *   invoked before writing into the buffer held by InPort.
     * - When the buffer held by InPort can detect the overflow,
     *   and when it detected the overflow at writing, callback functor
     *   OnOverflow will be invoked.
     * - When callback functor OnWriteConvert is set, the return value of
     *   operator() of OnWriteConvert will be written into the buffer 
     *   at the writing.
     * - When timeout of writing time is already set by setWriteTimeout(),
     *   it will wait for only timeout time until the state of the buffer full
     *   is reset, if OnOverflow is already set this will be invoked to 
     *   return.
     *
     * @param value The target data for the writing
     *
     * @return Writing result (Successful:true, Failed:false)
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
     *   �Хåե��񤭹��߻��ˡ�OnReadConvert �� operator() ������ͤ�
     *   read()������ͤȤʤ롣
     * - setReadTimeout() �ˤ���ɤ߽Ф����Υ����ॢ���Ȥ����ꤵ��Ƥ����硢
     *   �Хåե���������ե����֤���������ޤǥ����ॢ���Ȼ��֤����Ԥ���
     *   OnUnderflow�����åȤ���Ƥ���Ф����ƤӽФ������
     *
     * @return �ɤ߽Ф����ǡ���
     *
     * @else
     *
     * @brief Readout the value from DataPort
     *
     * Readout the value from DataPort
     *
     * - When Callback functor OnRead is already set, OnRead will be invoked
     *   before reading from the buffer held by DataPort.
     * - When the buffer held by DataPort can detect the underflow,
     *   and when it detected the underflow at reading, callback functor
     *   OnUnderflow will be invoked.
     * - When callback functor OnReadConvert is already set, the return value of
     *   operator() of OnReadConvert will be the return value of read().
     * - When timeout of reading is already set by setReadTimeout(),
     *   it waits for only timeout time until the state of the buffer underflow
     *   is reset, and if OnUnderflow is already set, this will be invoked to 
     *   return.
     *
     * @return Readout data
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
     * @brief Initialize the ring buffer value in InPort
     *
     * Initialize the ring buffer in InPort by specified value.
     * (Currently, commented out)
     *
     * @param value The target initialization data
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
     * @brief Read the newly value to type-T variable which is bound to InPort's
     *        buffer.
     *
     * Read the newly value to type-T data which is bound to InPort's buffer.
     * The type-T variable must be bound to InPort in constructor.
     * Since this method assumes to be used for polymorphic,
     * its argument and the return value do not depend on type.
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
     * @brief Read the newly value data in InPort to type-T variable
     *
     * Read the newly data set in InPort and set to specified data variable.
     *
     * @param rhs The type-T variable to read from InPort's buffer
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
     * @brief Write the type-T data to DataPort
     *
     * Write the given type-T data to DataPort.
     *
     * @param value The type-T variable to write to DaraPort
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
     * @brief Get number of new unread data
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
     * @brief Get new unread data
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
     * @brief Get new unread data backwards by date (new->old)
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
     * @brief Set callback for inputting data into the InPort buffer.
     *
     * Set the callback object invoked when data was put in the InPort's buffer.
     * The callback object which was set inherits InPort<DataType>::OnPut class,
     * and the method operator(), which has the argument "const DataType&"
     * and the return value "void", need to be implemented.
     *
     * Callback object should be implemented as follow:<br>
     * struct MyOnPutCallback : public InPort<DataType> {<br>
     *   void operator()(const DataType data) {<br>
     *     Operation<br>
     *   }<br>
     * };<br>
     * and should be set as follow:
     * <br> 
     * m_inport.setOnPut(new MyOnPutCallback());<br>
     *
     * @param on_write OnWrite&lt;DataType&gt; type object
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
     * @brief Set callback when data is written into the InPort buffer
     *
     * Set the callback object that is invoked when data is written into 
     * the InPort's buffer. The return value of the callback object is set to
     * the buffer.
     * 
     * @param on_wconvert OnWriteConvert&lt;DataType&gt; type object
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
     * @brief Set callback when data is read from the InPort buffer
     *
     * Set the callback object that is invoked right before data is read from 
     * the InPort's buffer
     * 
     * @param on_read OnRead&lt;DataType&gt; type object
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
     * @brief Set callback when data is readout to the InPort buffer
     *
     * Set the callback object that is invoked when data is readout to
     * the InPort's buffer. The return value of callback object is the return
     * result of the read() method.
     * 
     * @param on_rconvert OnReadConvert&lt;DataType&gt; type object
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
     * @brief Set callback when the InPort buffer occurs overflow
     *
     * Set the callback object that is invoked when the buffer overflow was
     * detected in the InPort's buffer.
     * 
     * @param on_overflow OnOverflow&lt;DataType&gt; type object
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
     * @brief Set callback when the InPort buffer occurs underflow.
     *
     * Set the callback object that is invoked when the buffer underflow was
     * detected in the InPort's buffer.
     * 
     * @param on_underflow OnUnderflow&lt;DataType&gt; type object
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
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief �Х���ɤ���� T �����ѿ��ؤλ���
     * @else
     * @brief The reference to type-T value bound this OutPort
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
     * @brief Pointer to OnWrite callback functor
     * @endif
     */
    OnWrite<DataType>* m_OnWrite;
    
    /*!
     * @if jp
     * @brief OnWriteConvert ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnWriteConvert callback functor
     * @endif
     */
    OnWriteConvert<DataType>* m_OnWriteConvert;
    
    /*!
     * @if jp
     * @brief OnRead ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnRead callback functor
     * @endif
     */
    OnRead<DataType>* m_OnRead;
    
    /*!
     * @if jp
     * @brief OnReadConvert ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnReadConvert callback functor
     * @endif
     */
    OnReadConvert<DataType>* m_OnReadConvert;
    
    /*!
     * @if jp
     * @brief OnOverflow ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnOverflow callback functor
     * @endif
     */
    OnOverflow<DataType>* m_OnOverflow;
    
    /*!
     * @if jp
     * @brief OnUnderflow ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnUnderflow callback functor
     *
     * @endif
     */
    OnUnderflow<DataType>* m_OnUnderflow;
  };
}; // End of namesepace RTM

#endif // RtcInPort_h
