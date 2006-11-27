// -*- C++ -*-
/*!
 * @file BufferBase.h
 * @brief Buffer abstract class
 * @date $Date: 2006-11-27 09:44:34 $
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
 * $Id: BufferBase.h,v 1.1 2006-11-27 09:44:34 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
     * @brief �Хåե��˥ǡ�����񤭹���
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual void write(const DataType& value) = 0;

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
    virtual DataType read() = 0;

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
    virtual int length() const = 0;

    /*!
     * @if jp
     *
     * @brief ��������٤��������ǡ���������
     * 
     * @else
     *
     * @brief New data is exist to be get
     *
     * @endif
     */
    virtual bool isNew() const = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե���full�Ǥ���
     * 
     * @else
     *
     * @brief The buffer is full
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
     * @brief The buffer is empty
     *
     * @endif
     */
    virtual bool isEmpty() const = 0;
  };


  template <class DataType>
  class NullBuffer
    : public BufferBase<DataType>
  {
  public:
    NullBuffer(int size)
    {
    }

    virtual ~NullBuffer()
    {
    }

    inline void put(const DataType& data)
    {
      m_data = data;
    }

    inline const DataType& get()
    {
      return m_data;
    }

    inline DataType& getRef()
    {
      return m_data;
    }

    inline int length()
    {
      return 1;
    }

    inline bool isNew()
    {
      return true;
    }

    inline bool isFull()
    {
      return false;
    }

    inline bool isEmpty()
    {
      return false;
    }

  private:
    DataType m_data;
  };


}; // namespace RTC
#endif // BufferBase_h
