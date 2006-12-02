// -*- C++ -*-
/*!
 * @file BufferBase.h
 * @brief Buffer abstract class
 * @date $Date: 2006-12-02 18:24:15 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: BufferBase.h,v 1.2 2006-12-02 18:24:15 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 09:44:34  n-ando
 * The first commitment.
 *
 */

#ifndef BufferBase_h
#define BufferBase_h

namespace RTC
{
  /*!
   * @if jp
   * @class BufferBase
   * @brief BufferBase ��ݥ��饹
   * 
   * ��ΥХåե��Τ������ݥ��󥿡��ե��������饹��
   * ��ݥХåե����饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
   *
   * public���󥿡��ե������Ȥ��ưʲ��Τ�Τ��󶡤��롣
   * - write(): �Хåե��˽񤭹���
   * - read(): �Хåե������ɤ߽Ф�
   * - length(): �Хåե�Ĺ���֤�
   * - isFull(): �Хåե������դǤ���
   * - isEmpty(): �Хåե������Ǥ���
   *
   * protected���󥿡��ե������Ȥ��ưʲ��Τ�Τ��󶡤��롣
   * - put(): �Хåե��˥ǡ�����񤭹���
   * - get(): �Хåե�����ǡ������ɤ߽Ф�
   *
   *
   *
   * @param DataType �Хåե��˳�Ǽ����ǡ�����
   *
   * @else
   * @class BufferBase
   * @brief BufferBase abstract class
   *
   * This is the abstract interface class for various Buffer.
   *
   * @param DataType Data type to be stored to the buffer.
   *
   * @endif
   */
  template <class DataType>
  class BufferBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * @else
     *
     * @brief virtual destractor
     *
     * @endif
     */
    virtual ~BufferBase(){};

    /*!
     * @if jp
     *
     * @brief �Хåե���Ĺ�����������
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * @endif
     */
    virtual long int length() const = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ�����񤭹���
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual bool write(const DataType& value) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ�����񤭹���
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual bool read(DataType& value) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե���full�Ǥ���
     * 
     * @else
     *
     * @brief True if the buffer is full, else false.
     *
     * @endif
     */
    virtual bool isFull() const = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե���empty�Ǥ���
     * 
     * @else
     *
     * @brief True if the buffer is empty, else false.
     *
     * @endif
     */
    virtual bool isEmpty() const = 0;

  protected:
    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ�����񤭹���
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual void put(const DataType& data) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե�����ǡ������������
     * 
     * @else
     *
     * @brief Get data from the buffer
     *
     * @endif
     */
    virtual const DataType& get() = 0;

    /*!
     * @if jp
     *
     * @brief ���˽񤭹���Хåե��λ��Ȥ��������
     * 
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * @endif
     */
    virtual DataType& getRef() = 0;

  };




  template <class DataType>
  class NullBuffer
    : public BufferBase<DataType>
  {
  public:
    NullBuffer(long int size = 1)
      : m_length(1)
    {
    }

    virtual ~NullBuffer()
    {
    }

    virtual long int length() const
    {
      return 1;
    }

    virtual bool write(const DataType& value)
    {
      m_data = value;
      return true;
    }

    virtual bool read(DataType& value)
    {
      value = m_data;
      return true;
    }

    virtual bool isFull() const
    {
      return false;
    }

    virtual bool isEmpty() const
    {
      return false;
    }
    
  protected:
    virtual void put(const DataType& data)
    {
      m_data = data;
    }

    virtual const DataType& get()
    {
      return m_data;
    }

    virtual DataType& getRef()
    {
      return m_data;
    }

  private:
    DataType m_data;
    long int m_length;
  };


}; // namespace RTC
#endif // BufferBase_h
