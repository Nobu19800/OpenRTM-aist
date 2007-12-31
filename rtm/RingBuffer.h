// -*- C++ -*-
/*!
 * @file RingBuffer.h
 * @brief Defautl Buffer class
 * @date $Date: 2007-12-31 03:08:06 $
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
 * $Id: RingBuffer.h,v 1.5.2.2 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5.2.1  2007/07/20 16:07:58  n-ando
 * Shimizu's patch to modify vector access violation.
 *
 * Revision 1.5  2007/04/26 15:32:56  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.4  2007/01/06 18:02:49  n-ando
 * The RingBuffer has been completely re-implemented.
 *
 *
 */

#ifndef RingBuffer_h
#define RingBuffer_h

#include <rtm/RTC.h>

#include <vector>
#include <algorithm>
//#include <ace/Synch.h>
#include <rtm/BufferBase.h>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RT����ݡ��ͥ��
 *
 * @else
 *
 * @namespace RTC
 *
 * @endif
 */
namespace RTC
{
  /*!
   * @if jp
   * @class RingBuffer
   * @brief ��󥰥Хåե��������饹
   * 
   * ���ꤷ��Ĺ���Υ�󥰾��Хåե�����ĥХåե��������饹��
   * �Хåե����Τ˥ǡ�������Ǽ���줿��硢�ʹߤΥǡ����ϸŤ��ǡ�������
   * �缡��񤭤���롣
   * ���äơ��Хåե���ˤ�ľ��ΥХåե�Ĺʬ�Υǡ����Τ��ݻ�����롣
   * ��)���ߤμ����Ǥϡ����ֺǸ�˳�Ǽ�����ǡ����ΤߥХåե������ɤ߽Ф���ǽ
   *
   * @param DataType �Хåե��˳�Ǽ����ǡ�����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  template <class DataType>
  class RingBuffer
    : public BufferBase<DataType>
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     * ���ꤵ�줿�Хåե�Ĺ�ǥХåե����������롣
     * �����������ꤵ�줿Ĺ������̤���ξ�硢Ĺ�����ǥХåե����������롣
     *
     * @param length �Хåե�Ĺ
     * 
     * @else
     *
     * @endif
     */
    RingBuffer(long int length)
      : m_length(length < 2 ? 2 : length),
	m_oldPtr(0),
	m_newPtr(length < 2 ? 1 : length - 1)
    {
      m_buffer.resize(m_length);
    }
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     * 
     * @else
     *
     * @brief virtual destractor
     *
     * @endif
     */
    virtual ~RingBuffer(){};
    
    /*!
     * @if jp
     *
     * @brief �����
     * 
     * �Хåե��ν����
     * ���ꤵ�줿�ͤ�Хåե����Τ˳�Ǽ���롣
     *
     * @param data ������ѥǡ���
     * 
     * @else
     *
     * @endif
     */
    void init(DataType& data)
    {
      for (long int i = 0; i < m_length; ++i)
	{
	  put(data);
	}
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�Ĺ���������
     * 
     * �Хåե�Ĺ��������롣
     * 
     * @return �Хåե�Ĺ
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * @endif
     */
    virtual long int length() const
    {
      return m_length;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե��˽񤭹���
     * 
     * ������Ϳ����줿�ǡ�����Хåե��˽񤭹��ࡣ
     * 
     * @param value �񤭹����оݥǡ���
     *
     * @return �ǡ����񤭹��߷��(���true:�񤭹����������֤�)
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual bool write(const DataType& value)
    {
      put(value);
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե������ɤ߽Ф�
     * 
     * �Хåե��˳�Ǽ���줿�ǡ������ɤ߽Ф���
     * 
     * @param value �ɤ߽Ф����ǡ���
     *
     * @return �ǡ����ɤ߽Ф����(��� true:�ɤ߽Ф����� ���֤�)
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual bool read(DataType& value)
    {
      value = get();
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե������դǤ��뤫��ǧ����
     * 
     * �Хåե����դ��ǧ���롣(���false���֤���)
     *
     * @return ���ճ�ǧ���(���false)
     * 
     * @else
     *
     * @brief True if the buffer is full, else false.
     *
     * @endif
     */
    virtual bool isFull() const
    {
      return false;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե������Ǥ��뤫��ǧ����
     * 
     * �Хåե������ǧ���롣
     * ��)���ߤμ����Ǥϡ����ߤΥХåե����֤˳�Ǽ���줿�ǡ������ɤ߽Ф��줿��
     * �ɤ������֤���( true:�ǡ����ɤ߽Ф��ѡ�false:�ǡ���̤�ɤ߽Ф�)
     *
     * @return ����ǧ���
     * 
     * @else
     *
     * @brief True if the buffer is empty, else false.
     *
     * @endif
     */
    virtual bool isEmpty() const
    {
      return !(this->isNew());
    }
    
    /*!
     * @if jp
     *
     * @brief �ǿ��ǡ�������ǧ����
     * 
     * ���ߤΥХåե����֤˳�Ǽ����Ƥ���ǡ������ǿ��ǡ�������ǧ���롣
     *
     * @return �ǿ��ǡ�����ǧ���
     *           ( true:�ǿ��ǡ������ǡ����Ϥޤ��ɤ߽Ф���Ƥ��ʤ�
     *            false:���Υǡ������ǡ����ϴ����ɤ߽Ф���Ƥ���)
     * 
     * @else
     *
     * @endif
     */
    bool isNew() const
    {
      return m_buffer[m_newPtr].isNew();
    }
    
  protected:
    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ������Ǽ����
     * 
     * ������Ϳ����줿�ǡ�����Хåե��˳�Ǽ���롣
     * ��)���ߤμ����Ǥϥǡ������Ǽ�����Ʊ���ˡ��ǡ������ɤ߽Ф����֤�
     * ��Ǽ�����ǡ������֤����ꤷ�Ƥ��롣���Τ��ᡢ���ľ��˳�Ǽ�����ǡ�����
     * ����������ȤʤäƤ��롣
     * 
     * @param data ��Ǽ�оݥǡ���
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual void put(const DataType& data)
    {
      m_buffer[m_oldPtr].write(data);
      //      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      m_newPtr = m_oldPtr;
      m_oldPtr = (++m_oldPtr) % m_length;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�����ǡ������������
     * 
     * �Хåե��˳�Ǽ���줿�ǡ�����������롣
     *
     * @return �����ǡ���
     * 
     * @else
     *
     * @brief Get data from the buffer
     *
     * @endif
     */
    virtual const DataType& get()
    {
      return m_buffer[m_newPtr].read();
    }
    
    /*!
     * @if jp
     *
     * @brief ���˽񤭹���Хåե��ؤλ��Ȥ��������
     * 
     * �񤭹��ߥХåե��ؤλ��Ȥ�������롣
     * 
     * @return ���ν񤭹����оݥХåե��ؤλ���
     *
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * @endif
     */
    virtual DataType& getRef()
    {
      return m_buffer[m_newPtr].data;
    }
    
  private:
    long int m_length;
    long int m_oldPtr;
    long int m_newPtr;
    
    /*!
     * @if jp
     * @class Data
     * @brief �Хåե�����
     * 
     * �Хåե��ǡ�����Ǽ�����󥯥饹��
     *
     * @param D �Хåե��˳�Ǽ����ǡ����η�
     *
     * @since 0.4.0
     *
     * @else
     * @brief Buffer sequence
     * @endif
     */
    template <class D>
    class Data
    {
    public:
      Data() : data(), is_new(false){;}
      inline Data& operator=(const D& other)
      {
	this->data = other;
	this->is_new = true;
	return *this;
      }
      inline void write(const D& other)
      {
	this->is_new = true;
	this->data = other;
      }
      inline D& read()
      {
	this->is_new = false;
	return this->data;
      }
      inline bool isNew() const
      {
	return is_new;
      }
      D    data;
      bool is_new;
    };
    
    std::vector<Data<DataType> > m_buffer;
    
  };
}; // namespace RTC

#endif // RingBuffer_h
