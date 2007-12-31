// -*- C++ -*-
/*!
 *
 * @file BufferBase.h
 * @brief Buffer abstract class
 * @date $Date: 2007-12-31 03:06:12 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2007
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: BufferBase.h,v 1.2.4.3 2007-12-31 03:06:12 n-ando Exp $
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2.4.2  2007/09/21 09:18:12  n-ando
 * Documentation was modified.
 *
 * Revision 1.2  2006/12/02 18:24:15  n-ando
 * BufferBase's interfaces were changed.
 *
 * Revision 1.1  2006/11/27 09:44:34  n-ando
 * The first commitment.
 *
 */

#ifndef BufferBase_h
#define BufferBase_h

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
   * @class BufferBase
   * @brief BufferBase ��ݥ��饹
   * 
   * ��ΥХåե��Τ������ݥ��󥿡��ե��������饹��
   * ��ݥХåե����饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
   * \<DataType\>�Ȥ��ƥХåե�����ݻ�����ǡ���������ꤹ�롣
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
   * @param DataType �Хåե��˳�Ǽ����ǡ�����
   *
   * @since 0.4.0
   *
   * @else
   * @class BufferBase
   * @brief BufferBase abstract class
   *
   * This is the abstract interface class for various Buffer.
   *
   * @param DataType Data type to be stored to the buffer.
   *
   * @since 0.4.0
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
     * �Хåե�Ĺ��������뤿��ν�貾�۴ؿ�
     * 
     * @return �Хåե�Ĺ
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * @return buffer length
     * 
     * @endif
     */
    virtual long int length() const = 0;
    
    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ�����񤭹���
     * 
     * �Хåե��˥ǡ�����񤭹��ि��ν�貾�۴ؿ�
     * 
     * @param value �񤭹����оݥǡ���
     *
     * @return �ǡ����񤭹��߷��(true:�񤭹���������false:�񤭹��߼���)
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
     * @brief �Хåե�����ǡ������ɤ߽Ф�
     * 
     * �Хåե�����ǡ������ɤ߽Ф�����ν�貾�۴ؿ�
     * 
     * @param value �ɤ߽Ф��ǡ���
     *
     * @return �ǡ����ɤ߽Ф����(true:�ɤ߽Ф�������false:�ɤ߽Ф�����)
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * @endif
     */
    virtual bool read(DataType& value) = 0;
    
    /*!
     * @if jp
     *
     * @brief �Хåե�full�����å�
     * 
     * �Хåե�full�����å��ѽ�貾�۴ؿ�
     *
     * @return full�����å����(true:�Хåե�full��false:�Хåե���������)
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
     * @brief �Хåե�empty�����å�
     * 
     * �Хåե�empty�����å��ѽ�貾�۴ؿ�
     *
     * @return empty�����å����(true:�Хåե�empty��false:�Хåե��ǡ�������)
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
     * @brief �Хåե��˥ǡ������Ǽ����
     * 
     * �Хåե��ؤΥǡ�����Ǽ�ѽ�貾�۴ؿ�
     * 
     * @param data �оݥǡ���
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
     * �Хåե��˳�Ǽ���줿�ǡ��������ѽ�貾�۴ؿ�
     *
     * @return �����ǡ���
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
     * @brief ���˽񤭹���Хåե��ؤλ��Ȥ��������
     * 
     * �񤭹��ߥХåե��ؤλ��ȼ����ѽ�貾�۴ؿ�
     *
     * @return ���ν񤭹����оݥХåե��ؤλ���
     * 
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * @endif
     */
    virtual DataType& getRef() = 0;
  };
  
  /*!
   * @if jp
   * @class NullBuffer
   * @brief ���ߡ��Хåե��������饹
   * 
   * �Хåե�Ĺ��������Υ��ߡ��Хåե��������饹��
   * \<DataType\>�Ȥ��ƥХåե�����ݻ�����ǡ���������ꤹ�롣
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
  class NullBuffer
    : public BufferBase<DataType>
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     * �Хåե�Ĺ��(����)�ǽ�������롣
     *
     * @param size �Хåե�Ĺ(������̵��)
     * 
     * @else
     *
     * @endif
     */
    NullBuffer(long int size = 1)
      : m_length(1)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     * 
     * �ǥ��ȥ饯����
     *
     * @else
     *
     * @endif
     */
    virtual ~NullBuffer()
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�Ĺ(������)���������
     * 
     * �Хåե�Ĺ��������롣(��ˣ����֤���)
     * 
     * @return �Хåե�Ĺ(������)
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * @return buffer length(always 1)
     * 
     * @endif
     */
    virtual long int length() const
    {
      return 1;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ�����񤭹���
     * 
     * ������Ϳ����줿�ǡ�����Хåե��˽񤭹��ࡣ
     * 
     * @param value �񤭹����оݥǡ���
     *
     * @return �ǡ����񤭹��߷��(true:�񤭹���������false:�񤭹��߼���)
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual bool write(const DataType& value)
    {
      m_data = value;
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�����ǡ������ɤ߽Ф�
     * 
     * �Хåե��˳�Ǽ���줿�ǡ������ɤ߽Ф���
     * 
     * @param value �ɤ߽Ф����ǡ���
     *
     * @return �ǡ����ɤ߽Ф����(true:�ɤ߽Ф�������false:�ɤ߽Ф�����)
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * @endif
     */
    virtual bool read(DataType& value)
    {
      value = m_data;
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�full�����å�
     * 
     * �Хåե�full������å����롣(���false���֤���)
     *
     * @return full�����å����(���false)
     * 
     * @else
     *
     * @brief Always false.
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
     * @brief �Хåե�empty�����å�
     * 
     * �Хåե�empty������å����롣(���false���֤���)
     *
     * @return empty�����å����(���false)
     * 
     * @else
     *
     * @brief Always false.
     *
     * @endif
     */
    virtual bool isEmpty() const
    {
      return false;
    }
    
  protected:
    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ������Ǽ
     * 
     * ������Ϳ����줿�ǡ�����Хåե��˳�Ǽ���롣
     * 
     * @param data �оݥǡ���
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual void put(const DataType& data)
    {
      m_data = data;
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
      return m_data;
    }
    
    /*!
     * @if jp
     *
     * @brief ���˽񤭹���Хåե��ؤλ��Ȥ��������
     * 
     * �񤭹��ߥХåե��ؤλ��Ȥ�������롣
     * �ܥХåե������ǤϥХåե�Ĺ�ϸ���ǣ��Ǥ��뤿�ᡤ
     * ���Ʊ�����֤ؤλ��Ȥ��֤���
     *
     * @return ���ν񤭹����оݥХåե��ؤλ���(����)
     * 
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * @endif
     */
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
