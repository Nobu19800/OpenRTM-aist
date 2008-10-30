// -*- C++ -*-
/*!
 * @file OutPort.h
 * @brief OutPort class
 * @date $Date: 2007-12-31 03:08:05 $
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
 * $Id$
 *
 */

#ifndef OutPort_h
#define OutPort_h

#include <rtm/BufferBase.h>
#include <rtm/RingBuffer.h>
#include <rtm/OutPortBase.h>
#include <rtm/PortCallBack.h>
#include <rtm/RTC.h>
#include <iostream>
#include <coil/TimeValue.h>
#include <coil/Time.h>
#include <coil/OS.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class OutPort
   *
   * @brief OutPort �ƥ�ץ졼�ȥ��饹
   * 
   * OutPort �ƥ�ץ졼�ȥ��饹���ƥ�ץ졼�Ȥΰ����Ȥ��ơ�OutPort��
   * �����ǡ����� DataType, OutPort�ΥХåե��� BufferType ��Ȥ롣
   *
   * @since 0.2.0
   *
   * @else
   *
   * @brief OutPort template class
   * 
   * This is the OutPort template class. 
   * The data type "DateType" supported by OutPort and the buffer type
   * "BufferType" are used as template arguments.
   *
   * @since 0.2.0
   *
   * @endif
   */
  template <class DataType,
	    template <class DataType> class Buffer = RingBuffer >
  class OutPort
    : public OutPortBase,
      public Buffer<DataType>
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param name �ݡ���̾
     * @param value ���Υݡ��Ȥ˥Х���ɤ����ǡ����ѿ�
     * @param length �Хåե�Ĺ(�ǥե������:8)
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port's name
     * @param value Data variable bound to this port
     * @param length Buffer length (The default value:8)
     *
     * @endif
     */
    OutPort(const char* name, DataType& value, long int length = 8)
      : OutPortBase(name), Buffer<DataType>(length),
	m_value(value),
	m_timeoutTick(1000), // timeout tick: 1ms
	m_readBlock(false), m_readTimeout(0),
	m_writeBlock(false), m_writeTimeout(0),
	m_OnWrite(NULL), m_OnWriteConvert(NULL),
	m_OnRead(NULL),  m_OnReadConvert(NULL),
	m_OnOverflow(NULL), m_OnUnderflow(NULL)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     * 
     * �ǥ��ȥ饯��
     * 
     * @else
     *
     * @brief Destructor
     * 
     * Destructor
     * 
     * @endif
     */
    virtual ~OutPort()
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �ǡ����񤭹���
     *
     * �ݡ��Ȥإǡ�����񤭹��ࡣ
     *
     * - ������Хå��ե��󥯥� OnWrite �����åȤ���Ƥ����硢
     *   OutPort ���ݻ�����Хåե��˽񤭹������� OnWrite ���ƤФ�롣
     * - OutPort ���ݻ�����Хåե��������С��ե��򸡽ФǤ���Хåե��Ǥ��ꡢ
     *   ���ġ��񤭹���ݤ˥Хåե��������С��ե��򸡽Ф�����硢
     *   ������Хå��ե��󥯥� OnOverflow ���ƤФ�롣
     * - ������Хå��ե��󥯥� OnWriteConvert �����åȤ���Ƥ����硢
     *   �Хåե��񤭹��߻��ˡ� OnWriteConvert �� operator() ������ͤ�
     *   �Хåե��˽񤭹��ޤ�롣
     *
     * @param value �񤭹����оݥǡ���
     *
     * @return �񤭹��߽������(�񤭹�������:true���񤭹��߼���:false)
     *
     * @else
     *
     * @brief Write data
     *
     * Write data in the port.
     *
     * - When callback functor OnWrite is already set, OnWrite will be
     *   invoked before writing into the buffer held by OutPort.
     * - When the buffer held by OutPort can detect the overflow,
     *   and when it detected the overflow at writing, callback functor
     *   OnOverflow will be invoked.
     * - When callback functor OnWriteConvert is already set, 
     *   the return value of operator() of OnWriteConvert will be written
     *   into the buffer at the writing.
     *
     * @param value The target data for writing
     *
     * @return Writing result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool write(const DataType& value)
    {
      if (m_OnWrite != NULL)
	{
	  (*m_OnWrite)(value);
	}
      
//      long int timeout = m_writeTimeout;
      double timeout = (double)m_writeTimeout / (double)TIMEVALUE_ONE_SECOND_IN_USECS;
      
      coil::TimeValue tm_cur, tm_pre;
      tm_pre = coil::gettimeofday();
      
      // blocking and timeout wait
      long int count(0);
      while (m_writeBlock && this->isFull())
	{
	  if (m_writeTimeout < 0) 
	    {
              coil::usleep(m_timeoutTick);
	      continue;
	    }
	  
	  // timeout wait
	  tm_cur = coil::gettimeofday();
          timeout -= (double)(tm_cur - tm_pre);
	  if (timeout < 0) break;
	  
	  tm_pre = tm_cur;
          coil::usleep(m_timeoutTick);
	  ++count;
	}
      
      if (this->isFull())
	{
	  if (m_OnOverflow != NULL)
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
      notify();
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief �ǡ����񤭹���
     *
     * �ݡ��Ȥإǡ�����񤭹��ࡣ
     * �Х���ɤ��줿�ѿ������ꤵ�줿�ͤ�ݡ��Ȥ˽񤭹��ࡣ
     *
     * @return �񤭹��߽������(�񤭹�������:true���񤭹��߼���:false)
     *
     * @else
     *
     * @brief Write data
     *
     * Write data to the port.
     * Write the value, which was set to the bound variable, to the port.
     *
     * @return Writing result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool write()
    {
      return write(m_value);
    }
    
    /*!
     * @if jp
     *
     * @brief �ǡ����񤭹���
     *
     * �ݡ��Ȥإǡ�����񤭹��ࡣ
     * ���ꤵ�줿�ͤ�ݡ��Ȥ˽񤭹��ࡣ
     *
     * @param value �񤭹����оݥǡ���
     *
     * @return �񤭹��߽������(�񤭹�������:true���񤭹��߼���:false)
     *
     * @else
     *
     * @brief Write data
     *
     * Write data to the port.
     * Write the set value to the port.
     *
     * @param value The target data for writing
     *
     * @return Writing result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool operator<<(DataType& value)
    {
      return write(value);
    }
    
    /*!
     * @if jp
     *
     * @brief �ǡ����ɤ߽Ф�
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
     *   OnUnderflow �����åȤ���Ƥ���Ф����ƤӽФ������
     *
     * @param value �ɤ߽Ф����ǡ���
     *
     * @return �ɤ߽Ф������¹Է��(�ɤ߽Ф�����:true���ɤ߽Ф�����:false)
     *
     * @else
     *
     * @brief Readout the data
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
     * - When timeout at the time of reading is already set by setReadTimeout(),
     *   it waits for only timeout period until the state of the buffer underflow
     *   is released, and if OnUnderflow is already set, this will be invoked to
     *   return.
     *
     * @param value Readout data
     *
     * @return Readout result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool read(DataType& value)
    {
      if (m_OnRead != NULL) (*m_OnRead)();      
      
//      long int timeout = m_readTimeout;
      double timeout = (double)m_readTimeout / (double)TIMEVALUE_ONE_SECOND_IN_USECS;
      coil::TimeValue tm_cur, tm_pre;
      tm_pre = coil::gettimeofday();
      
      // blocking and timeout wait
      while (m_readBlock && this->isEmpty())
	{
	  if (m_readTimeout < 0)
	    {
              coil::usleep(m_timeoutTick);
	      continue;
	    }
	  
	  // timeout wait
	  tm_cur = coil::gettimeofday();
	  timeout -= (double)(tm_cur - tm_pre);
	  if (timeout < 0) break;
	  
	  tm_pre = tm_cur;
          coil::usleep(m_timeoutTick);
	}
      
      if (this->isEmpty())
	{
	  if (m_OnUnderflow != NULL)
	    {
	      value = (*m_OnUnderflow)();
	      return false;
	    }
	  else
	    {
	      return false;
	    }
	}
      
      if (m_OnReadConvert == NULL) 
	{
	  value = this->get();
	  return true;
	}
      else
	{
	  value = (*m_OnReadConvert)(this->get());
	  return true;
	}
      // never comes here
      return false;
    }
    
    /*!
     * @if jp
     *
     * @brief �ǡ����ɤ߽Ф������Υ֥�å��⡼�ɤ�����
     *
     * �ɤ߽Ф��������Ф��ƥ֥�å��⡼�ɤ����ꤹ�롣
     * �֥�å��⡼�ɤ���ꤷ����硢�ɤ߽Ф���ǡ�����������뤫�����ॢ����
     * ��ȯ������ޤǡ�read() �᥽�åɤθƤӤ������֥�å�����롣
     *
     * @param block �֥�å��⡼�ɥե饰
     *
     * @else
     *
     * @brief Set blocking mode of the data read processing
     *
     * Set the blocking mode for the readout.
     * When the block mode is specified, the invoke of read() method is
     * blocked until the readout data is received or timeout occurs.
     *
     * @param block Flag of blocking mode
     *
     * @endif
     */
    void setReadBlock(bool block)
    {
      m_readBlock = block;
    }
    
    /*!
     * @if jp
     *
     * @brief �ǡ����񤭹��߽����Υ֥�å��⡼�ɤ�����
     *
     * �񤭹��߽������Ф��ƥ֥�å��⡼�ɤ����ꤹ�롣
     * �֥�å��⡼�ɤ���ꤷ����硢�Хåե��˽񤭹����ΰ褬�Ǥ��뤫
     * �����ॢ���Ȥ�ȯ������ޤ� write() �᥽�åɤθƤӤ������֥�å�����롣
     *
     * @param block �֥�å��⡼�ɥե饰
     *
     * @else
     *
     * @brief Set blocking mode of the data writing processing
     *
     * Set the blocking mode for the writing.
     * When the block mode is specified, the invoke of write() method is
     * blocked until the area written into the buffer can be used or timeout
     * occurs.
     *
     * @param block Flag of blocking mode
     *
     * @endif
     */
    void setWriteBlock(bool block)
    {
      m_writeBlock = block;
    }
    
    /*!
     * @if jp
     *
     * @brief �ɤ߽Ф������Υ����ॢ���Ȼ��֤�����
     * 
     * read() �Υ����ॢ���Ȼ��֤� usec �����ꤹ�롣
     * read() �ϥ֥�å��⡼�ɤǤʤ���Фʤ�ʤ���
     *
     * @param timeout �����ॢ���Ȼ��� [usec]
     *
     * @else
     *
     * @brief Set timeout of the data read processing
     * 
     * Set the timeout period of read() with usec.
     * read() must be a block mode.
     *
     * @param timeout Timeout period[usec]
     *
     * @else
     *
     * @endif
     */
    void setReadTimeout(long int timeout)
    {
      m_readTimeout = timeout;
    }
    
    /*!
     * @if jp
     *
     * @brief �񤭹��߽����Υ����ॢ���Ȼ��֤�����
     * 
     * write() �Υ����ॢ���Ȼ��֤� usec �����ꤹ�롣
     * write() �ϥ֥�å��⡼�ɤǤʤ���Фʤ�ʤ���
     *
     * @param timeout �����ॢ���Ȼ��� [usec]
     *
     * @else
     *
     * @brief Set timeout of the data writing processing
     * 
     * Set the timeout period of write() with usec.
     * write() must be a block mode.
     *
     * @param timeout Timeout period[usec]
     *
     * @endif
     */
    void setWriteTimeout(long int timeout)
    {
      m_writeTimeout = timeout;
    }
    
    /*!
     * @if jp
     *
     * @brief OnWrite ������Хå�������
     *
     * �ǡ����񤭹���ľ���˸ƤФ�� OnWrite ������Хå��ե��󥯥������ꤹ�롣
     *
     * @param on_write OnWrite ������Хå��ե��󥯥�
     *
     * @else
     *
     * @brief Set OnWrite callback
     *
     * Set OnWrite callback functor invoked immediately before data is written.
     *
     * @param on_write OnWrite callback functor
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
     * @brief OnWriteConvert ������Хå�������
     *
     * �ǡ����񤭹��߻��˸ƤФ�� OnWriteConvert ������Хå��ե��󥯥�������
     * ���롣
     * ���Υ�����Хå��ؿ��ν�����̤��񤭹��ޤ�롣
     * ���Τ���񤭹��ߥǡ����Υե��륿��󥰤���ǽ�Ȥʤ롣
     *
     * @param on_wconvert OnWriteConvert ������Хå��ե��󥯥�
     *
     * @else
     *
     * @brief Set OnWriteConvert callback
     *
     * Set OnWriteConvert callback functor invoked when data is written.
     * The processing result of this callback function is written.
     * Therefore, filtering of the writing data will be possible.
     *
     * @param on_wconvert OnWriteConvert callback functor
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
     * @brief OnOverflow ������Хå�������
     *
     * �Хåե��ե�ˤ��ǡ����񤭹��ߤ��Ǥ��ʤ����˸ƤӽФ���� OnOverflow
     * ������Хå��ե��󥯥������ꤹ�롣
     *
     * @param on_overflow OnOverflow ������Хå��ե��󥯥�
     *
     * @else
     *
     * @brief Set OnOverflow callback
     *
     * Set OnOverflow callback functor, which is invoked when data cannot be
     * written because of the buffer full.
     *
     * @param on_overflow OnOverflow callback functor
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
     * @brief OnRead ������Хå�������
     *
     * �ǡ����ɤ߽Ф�ľ���˸ƤӽФ���� OnRead ������Хå��ե��󥯥�������
     * ���롣
     *
     * @param on_read OnRead ������Хå��ե��󥯥�
     *
     * @else
     *
     * @brief Set OnRead callback
     *
     * Set OnWrite callback functor invoked immediately before data is readout.
     *
     * @param on_read OnRead callback functor
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
     * @brief OnReadConvert ������Хå�������
     *
     * �ǡ����ɤ߽Ф����˸ƤФ�� OnReadConvert ������Хå��ե��󥯥�������
     * ���롣
     * ���Υ�����Хå��ؿ��ν�����̤��ɤ߹��ޤ�롣
     * ���Τ����ɤ߹��ߥǡ����Υե��륿��󥰤���ǽ�Ȥʤ롣
     *
     * @param on_rconvert OnReadConvert ������Хå��ե��󥯥�
     *
     * @else
     *
     * @brief Set OnReadConvert callback
     *
     * Set OnReadConvert callback functor invoked when data is readout.
     * The processing result of this callback function is readout.
     * Therefore, filtering of the read data will be possible.
     *
     * @param on_rconvert OnReadConvert callback functor
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
     * @brief OnUnderflow ������Хå�������
     *
     * �Хåե�����ץƥ��ˤ���ɤ߽Ф���ǡ������ʤ����˸ƤӽФ����
     * ������Хå��ե��󥯥� OnUnderflow �����ꤹ�롣
     *
     * @param on_underflow OnUnderflow ������Хå��ե��󥯥�
     *
     * @else
     *
     * @brief Set OnUnderflow callback
     *
     * Set OnUnderflow callback functor, which is invoked when data cannot be
     * readout because of the buffer empty.
     *
     * @param on_underflow OnUnderflow callback functor
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
     * @brief �Х���ɤ���� T �����ѿ��ؤλ���
     * @else
     * @brief The reference to type-T variable that is bound.
     * @endif
     */
    DataType& m_value;
    
    /*!
     * @if jp
     * @brief �����ॢ���ȤΥݡ���󥰼��� [usec]
     * @else
     * @brief Polling cycle of time-out [usec]
     * @endif
     */
    long int m_timeoutTick;
    
    /*!
     * @if jp
     * @brief �ɤ߹��߽������Υ֥�å�����֥�å��⡼�ɥե饰
     * @else
     * @brief Flag of read()'s blocking/non-blocking mode
     * @endif
     */
    bool m_readBlock;
    
    /*!
     * @if jp
     * @brief �ɤ߹��߽����Υ����ॢ���Ȼ��� [usec]
     * @else
     * @brief Timeout of read() [usec]
     * @endif
     */
    long int m_readTimeout;
    
    /*!
     * @if jp
     * @brief �񤭹��߽������Υ֥�å�����֥�å��⡼�ɥե饰
     * @else
     * @brief Flag of write()'s blocking/non-blocking mode
     * @endif
     */
    bool m_writeBlock;
    
    /*!
     * @if jp
     * @brief �񤭹��߽����Υ����ॢ���Ȼ��� [usec]
     * @else
     * @brief Timeout of write() [usec]
     * @endif
     */
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
    
    static const long int usec_per_sec = 1000000;
  };
}; // namespace RTC

#endif // OutPort_h
