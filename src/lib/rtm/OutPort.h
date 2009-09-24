// -*- C++ -*-
/*!
 * @file OutPort.h
 * @brief OutPort class
 * @date $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
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

#include <iostream>
#include <string>

#include <coil/TimeValue.h>
#include <coil/Time.h>
#include <coil/TimeMeasure.h>
#include <coil/OS.h>

#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/OutPortBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortCallBack.h>
#include <rtm/OutPortConnector.h>

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
   * �����ǡ����� DataType ��Ȥ롣
   *
   *
   *
   * OnWrite�ϥ�����Хå� (����ߤ˵������륤�٥�Ȥˤ�ꥳ���뤵���)
   *
   * - void OnWrite<DataType>::operator()(const DataType): 
   *     OutPort::write() ��ƤӽФ��񤭹��ߤ�Ԥ��ݤ˥����뤵��롣
   *
   * - DataType OnWriteConvert<DataType>::operator()(const DataType): 
   *     OutPort::write() ��ƤӽФ����ǡ�����Хåե��˽񤭹������˸ƤФ�
   *     �ǡ������Ѵ���Ԥ���operator()()������ͤ����ꥢ�饤������Хåե���
   *     �񤭹��ޤ�롣
   *
   *
   * OnBuffer�ϥ�����Хå� (�Хåե��˵������륤�٥�Ȥˤ�ꥳ���뤵���)
   *
   * 2����Υ�����Хå��ե��󥯥��Υ����˥���
   * BufferCallback::operator()(ConnectorId, cdrStream)
   * BufferReadCallback::operator()(ConnectorId)
   *
   * - void OnBufferWrite::operator()(ConnectorId, cdrStream):
   *     BufferBase::write() ���������ñ��˸ƤӽФ���륳����Хå���
   *     �����ˤ�write()����륷�ꥢ�饤���ѤߤΥǡ�����Ϳ�����롣        
   *   
   * - void OnBufferFull::operator()(ConnectorId, cdrStream):
   *     BufferBase::write() ��������ˡ��Хåե������äѤ��ξ���
   *     �ƤӽФ���륳����Хå������ͥ�����ID����ӽ񤭹���ʤ��ä��ǡ���
   *     ��������Ϳ�����롣
   *
   * - void OnBufferWriteTimeout::operator()(ConnectorId, cdrStream):
   *     ConnectorBase::write() ��������ˡ��Хåե������äѤ��ǽ���ߤ�
   *     �����ॢ���Ȥ������˸ƤӽФ���륳����Хå������ͥ�����ID
   *     ����ӽ񤭹���ʤ��ä��ǡ�����������Ϳ�����롣
   *
   * - void OnBufferOverwrite::operator()(ConnectorId, cdrStream):
   *     BufferBase::write() ��������ˡ��Хåե�����񤭥⡼�ɤ�����
   *     ����Ƥ��ꡢ�Хåե������äѤ��ξ��˸ƤӽФ���륳����Хå���
   *     ���ͥ�����ID��������Ϳ�����롣
   *
   *
   * - void OnBufferRead::operator()(ConnectorId, cdrStream):
   *     BufferBase::read() ���������ñ��˸ƤӽФ���륳����Хå���
   *     �����ˤ� read() ���֤���륷�ꥢ�饤���ѤߤΥǡ�����Ϳ�����롣
   *
   * - void OnBufferEmpty::operator()(ConnectorId): 
   *     ���ͥ������Хåե����ɤߤ����ݤˡ��Хåե������ξ��˸ƤӽФ���롣
   *     ���ͥ�����ID��������Ϳ�����롣
   *
   * - void OnBufferReadTimeout::operator()(ConnectorId):
   *     ���ͥ������Хåե����ɤߤ����ݤˡ��Хåե������Ǥ��ġ��ɤ߽Ф���
   *     �����ॢ���Ȥ������˸ƤӽФ���륳����Хå������ͥ�����ID
   *     ��������Ϳ�����롣
   *
   *
   * OnConnect�ϥ�����Хå� (��³�˵������륤�٥�Ȥˤ�ꥳ���뤵���)
   *
   * 2����Υ�����Хå��ե��󥯥��Υ����˥���
   * ConnectCallback::operator()(ConnectorProfile)
   * DisconnectCallback::operator()(ConnectorId)
   * 
   * - void OnConnect::operator()(ConnectorProfile):
   *     �ݡ��Ȥ���³���˸ƤӽФ���륳����Хå���������ConnectorProfile
   *     ��Ϳ�����롣
   *
   * - void OnDisconnect::operator()(ConnectorId):
   *     �ݡ��Ȥ���³���ǻ��˸ƤӽФ���륳����Хå��������˥��ͥ���ID
   *     ��Ϳ�����롣  
   *
   * - void OnConnectionLost::operator()(ConnectorId):
   *     �ݡ��Ȥ���³�����Ȥ������˸ƤӽФ���륳����Хå���
   *     �����˥��ͥ���ID��Ϳ�����롣OutPort�ϡ����¦InPort�Ȥ�
   *     ��³����Ȥ�����硢��³����Ū�����Ǥ���Τǡ�
   *     ����³�� OnDisconnect ������Хå����ƤӽФ���롣
   *

   *
   *
   * - void OnSend:operator()(ConnectorId, cdrStream):
   *     �ǡ�����InPort���Ф���������ݤ˸ƤӽФ���륳����Хå���
   *     �����˥��ͥ���ID��Ϳ�����롣
   *
   * - void OnReceived::operator()(ConnectorId, cdrStream):
   *     �ǡ�������������Ӽ�������λ�����ݤ˸ƤӽФ���륳����Хå���
   *     �����ˤϡ����ͥ���ID��Ϳ�����롣
   *

   *
   *
   * OnSender�ϥ�����Хå� (����¦�˵������륤�٥�Ȥˤ�ꥳ���뤵���)
   *   �ʲ��ϡ��ѥ֥�å��㤬¸�ߤ�����³�����ʤ�� dataflow type = push 
   *   �ΤȤ��Τ�ͭ����
   *
   * - void OnSenderTimeout::operator()(ConnectorId, cdrStream):
   *     �ǡ�����InPort���Ф�������줿���������������ॢ���Ȥ����ݤ�
   *     �ƤӽФ���륳����Хå��������˥��ͥ���ID��Ϳ�����롣
   *     InPort�Υץ�Х�������ӥ��󥷥塼�ޤ��б����Ƥ�����˸¤�ͭ����
   *
   * - void OnSenderError::operator()(ConnectorId, cdrStream):
   *     �ǡ�����InPort���Ф�������줿�������餫�Υ��顼��InPort¦��
   *     �֤������˸ƤӽФ���륳����Хå���
   *     �����ˤϡ����ͥ���ID��Ϳ�����롣
   *
   *
   * OnReceiver�ϥ�����Хå� (����¦�˵������륤�٥�Ȥˤ�ꥳ���뤵���)
   *   �ʲ��ϡ��ѥ֥�å��㤬¸�ߤ�����³�����ʤ�� dataflow type = push 
   *   �ΤȤ��Τ�ͭ����
   * 
   * - void OnReceiverFull::operator()(ConnectorId, cdrStream):
   *     �ǡ�����InPort���������ΤΡ�InPort¦�ΥХåե������äѤ��ξ���
   *     ��������Τ��뤿��˸ƤФ�륳����Хå���
   *     �����ˤϡ����ͥ���ID��Ϳ�����롣
   *
   * - void OnReceiverTimeout::operator()(ConnectorId, cdrStream):
   *     �ǡ�����InPort���������ΤΡ�InPort¦�ΥХåե������äѤ���
   *     �����ॢ���Ȥ������ˤ�������Τ��뤿��˸ƤФ�륳����Хå���
   *     �����ˤϡ����ͥ���ID��Ϳ�����롣
   *
   * - void OnReceiverError::operator()(ConnectorId, cdrStream):
   *     �ǡ�����InPort���������ΤΡ�InPort¦�ǲ��餫�Υ��顼���֤���
   *     ���˸ƤӽФ���륳����Хå���
   *     �����ˤϡ����ͥ���ID��Ϳ�����롣
   *
   *
   *
   *
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
  template <class DataType>
  class OutPort
    : public OutPortBase
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
    OutPort(const char* name, DataType& value)
      : OutPortBase(name, toTypename<DataType>()), m_value(value),
        //	m_timeoutTick(1000), // timeout tick: 1ms
        //	m_readBlock(false), m_readTimeout(0),
        //	m_writeBlock(false), m_writeTimeout(0),
	m_onWrite(0), m_onWriteConvert(0)
        //	m_OnRead(NULL),  m_OnReadConvert(NULL),
        //	m_OnOverflow(NULL), m_OnUnderflow(NULL)
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
    virtual ~OutPort(void)
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
    virtual bool write(DataType& value)
    {
      if (m_onWrite != NULL)
	{
	  (*m_onWrite)(value);
	}

      // check number of connectors
      size_t conn_size(m_connectors.size());
      if (!(conn_size > 0)) { return true; }
        
      // set timestamp
      coil::TimeValue tm(coil::gettimeofday());
      value.tm.sec  = tm.sec();
      value.tm.nsec = tm.usec() * 1000;

      // data -> (conversion) -> CDR stream
      m_cdr.rewindPtrs();
      if (m_onWriteConvert != NULL)
        {
          ((*m_onWriteConvert)(value)) >>= m_cdr;
        }
      else
        {
          value >>= m_cdr;
        }

      bool result(true);
      for (size_t i(0), len(conn_size); i < len; ++i)
        {
          ReturnCode ret;
          ret = m_connectors[i]->write(m_cdr);
          if (ret != PORT_OK)
            {
              result = false;
              if (ret == CONNECTION_LOST)
                {
                  disconnect(m_connectors[i]->id());
                }
            }
        }
      return result;
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
//    void setReadBlock(bool block)
//    {
//      m_readBlock = block;
//    }
    
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
//    void setWriteBlock(bool block)
//    {
//      m_writeBlock = block;
//    }
    
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
//    void setReadTimeout(long int timeout)
//    {
//      m_readTimeout = timeout;
//    }
    
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
//    void setWriteTimeout(long int timeout)
//    {
//      m_writeTimeout = timeout;
//    }
    
    /*!
     * @if jp
     *
     * @brief OnWrite ������Хå�������
     *
     * write() �ƤӽФ����ˡ��ƥ��ͥ������Ф��ƥǡ�����񤭹���ľ���˸�
     * �Ф�� OnWrite ������Хå��ե��󥯥������ꤹ�롣���δؿ��ˤ��
     * ���ꤵ�줿�ե��󥯥����֥������Ȥν�ͭ���ϡ��ƤӽФ�¦�����ġ���
     * ������ const �ơ����Υե��󥯥����֥������Ȥβ�����Ǥ�ϸƤӽФ�¦�ˤ��롣
     * �ե��󥯥����������������ˤϰ����� 0 ���Ϥ����Ȥǡ�������
     * �Хå���̵���Ȥʤ롣
     *
     * @param on_write OnWrite ������Хå��ե��󥯥�
     *
     * @else
     *
     * @brief Set OnWrite callback
     *
     * This operation sets the OnWrite callback functor that is called
     * just before write() operation call.  The ownership of the
     * functor object is owned by caller of this operation.  Therefore
     * caller have to destruct the callback functor object by itself.
     * Giving 0 as an argument for this operation, callback will be
     * disabled.
     *
     * @param on_write OnWrite callback functor
     *
     * @endif
     */
    inline void setOnWrite(OnWrite<DataType>* on_write)
    {
      m_onWrite = on_write;
    }
    
    /*!
     * @if jp
     *
     * @brief OnWriteConvert ������Хå�������
     *
     * write() �ƤӽФ����ˡ��ƥ��ͥ������Ф��ƥǡ�����񤭹���ľ���˸�
     * �Ф졢�ǡ����Ѵ���Ԥ� OnWriteConvert ������Хå��ե��󥯥�����
     * �ꤹ�롣������ľ��ǽ񤭹��ޤ줿�ǡ�����Ϳ����졢����ͤ˼ºݤ�
     * ���ͥ����ޤ��ϥХåե��˽񤭹��ޤ��ǡ������֤��ե��󥯥�������
     * ���롣���δؿ��ˤ�����ꤵ�줿�ե��󥯥����֥������Ȥν�ͭ���ϡ�
     * �ƤӽФ�¦�����ġ��������� const �ơ����Υե��󥯥����֥�������
     * �β�����Ǥ�ϸƤӽФ�¦�ˤ��롣�ե��󥯥����������������ˤ�
     * ������ 0 ���Ϥ����Ȥǡ�������Хå���̵���Ȥʤ롣 �ǡ����񤭹���
     * ���˸ƤФ�� OnWriteConvert ������Хå��ե��󥯥������ꤹ�롣��
     * �Υ�����Хå��ؿ��ν�����̤��񤭹��ޤ�롣���Τ���񤭹��ߥǡ�
     * ���Υե��륿��󥰤���ǽ�Ȥʤ롣
     *
     * @param on_wconvert OnWriteConvert ������Хå��ե��󥯥�
     *
     * @else
     *
     * @brief Set OnWriteConvert callback
     *
     * This operation sets the OnWriteConvert callback functor that
     * converts given data and is called just before write() operation
     * call. A recent data is given to argument and return data will
     * be written into connector or its buffer. The ownership of the
     * functor object is owned by caller of this operation.  Therefore
     * caller have to destruct the callback functor object by itself.
     * Giving 0 as an argument for this operation, callback will be
     * disabled.
     *
     * @param on_wconvert OnWriteConvert callback functor
     *
     * @endif
     */
    inline void setOnWriteConvert(OnWriteConvert<DataType>* on_wconvert)
    {
      m_onWriteConvert = on_wconvert;
    }
    
  private:
    std::string m_typename;
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
    //    long int m_timeoutTick;
    
    /*!
     * @if jp
     * @brief �ɤ߹��߽������Υ֥�å�����֥�å��⡼�ɥե饰
     * @else
     * @brief Flag of read()'s blocking/non-blocking mode
     * @endif
     */
    //    bool m_readBlock;
    
    /*!
     * @if jp
     * @brief �ɤ߹��߽����Υ����ॢ���Ȼ��� [usec]
     * @else
     * @brief Timeout of read() [usec]
     * @endif
     */
    //    long int m_readTimeout;
    
    /*!
     * @if jp
     * @brief �񤭹��߽������Υ֥�å�����֥�å��⡼�ɥե饰
     * @else
     * @brief Flag of write()'s blocking/non-blocking mode
     * @endif
     */
    //    bool m_writeBlock;
    
    /*!
     * @if jp
     * @brief �񤭹��߽����Υ����ॢ���Ȼ��� [usec]
     * @else
     * @brief Timeout of write() [usec]
     * @endif
     */
    //    long int m_writeTimeout;
    
    /*!
     * @if jp
     * @brief OnWrite ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnWrite callback functor
     * @endif
     */
    OnWrite<DataType>* m_onWrite;
    
    /*!
     * @if jp
     * @brief OnWriteConvert ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnWriteConvert callback functor
     * @endif
     */
    OnWriteConvert<DataType>* m_onWriteConvert;


    coil::TimeMeasure m_cdrtime;
    static const long int usec_per_sec = 1000000;
    cdrMemoryStream m_cdr;
  };
}; // namespace RTC

#endif // OutPort_h
