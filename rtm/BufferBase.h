// -*- C++ -*-
/*!
 * @file BufferBase.h
 * @brief Buffer abstract class
 * @date $Date: 2007-08-20 05:11:15 $
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
 * $Id: BufferBase.h,v 1.2.4.1 2007-08-20 05:11:15 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/12/02 18:24:15  n-ando
 * BufferBase's interfaces were changed.
 *
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
   * ��ΥХåե���������뤿�����ݥ��󥿡��ե��������饹��
   * ��ݥХåե����饹�ϡ��ʲ��ν�貾�۴ؿ���������ʤ���Фʤ�ʤ���
   *
   * public���󥿡��ե������Ȥ��ưʲ��Τ�Τ��󶡤��롣
   * - init(): �Хåե�����������
   * - clear(): �Хåե��򥯥ꥢ����
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
   * ��ݥХåե����饹�ϥХåե��ξ��֤��֤��ؿ� isFull(), isEmpty() ��ͳ��
   * �������Ƥ��ɤ�����(���false���֤�������) ξ�Ԥ�Ʊ����true���֤��ƤϤʤ�
   * �ʤ����ޤ��������δؿ��� true ���֤����Ȥ���������ʤ�С�Ʊ����write()
   * read()�μ�����Хåե����֤�ȿ�Ǥ��������Ǥ���ɬ�פ����롣
   *
   * ���ʤ����
   * - isFull() = true �ʤ�� isEmpty() = flase
   * - isFull() = flase �ʤ�� isEmpty() = true
   * - isFull() = true �ʤ�� write() = false
   * - isEmpty() = true �ʤ�� read() = false
   * �Ǥʤ���Фʤ�ʤ���
   * 
   * @param DataType �Хåե��˳�Ǽ����ǡ�����
   *
   * @else
   *
   * @class BufferBase
   * @brief BufferBase abstract class
   *
   * This is the abstract interface class for various Buffer classes.
   * The conclete Buffer classes responsible to implement the following
   * virtual functions.
   *
   * The following functions should be provided as public interfaces.
   * - init(): Initializes the buffer.
   * - clear(): clears the buffer.
   * - length(): Returns the buffer length.
   * - write(): Writes a data to the buffer.
   * - read(): Reads a data from the buffer.
   * - isFull(): Returns if the buffer is full.
   * - isEmpty(): Returns if the buffer is empty.
   *
   * The following functions should be provided as protected interfaces.
   * - put(): puts data to the buffer
   * - get(): gets data from the buffer
   *
   * "isFull" and "isEmpty" functions of the concrete classes can be
   * implemented as non-effective functions that return always "false".
   * However, these functions never return "true" value at the same time.
   * And, if these functions return "true" value, write() and read() functions
   * should return appropriate values according to the buffer status.
   *
   * Therefore, the following constraints should be guaranteed.
   * - isFull() = true when isEmpty() = flase
   * - isFull() = flase when isEmpty() = true
   * - isFull() = true when write() = false
   * - isEmpty() = true when read() = false 
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
     * @brief �Хåե�����������
     * 
     * �Хåե�������Ƥ����Ǥ�Ϳ����줿�ͤǽ��������롣������ˤ�ꡢ
     * ľ��ΥХåե����ɤ߽Ф���ǽ�Ȥʤꡢ�ɤ߽Ф�����ͤϡ���������Ѥ���
     * �ͤ���������
     *
     * @pre    �ʤ�
     * @post   isEmpty() == false ���� read() == true �Ǥ��ꡢread(data) ��
     *         ����ͤϽ�����˻��Ѥ����ͤǤ���
     * @param  data �Хåե��ν�����˻��Ѥ���ǡ���
     *
     * @else
     *
     * @brief Get the buffer length
     *
     * All of the buffer elements are initilized by the given data value.
     * As a consequence of initialization, the buffer can be readable and the
     * value to be read is equal to initialized value.
     *
     * @pre    None
     * @post   isEmpty() == false and read() == true, and return value of
     *         read(data) should return initialized data.
     * @param  data Data to be used to initialize the buffer.
     *
     * @endif
     */
    virutal void init(const DataType& data) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե��򥯥ꥢ����
     * 
     * �Хåե�������Ƥ����Ǥ򥯥ꥢ���롣�Хåե��ϥ��ꥢ����뤳�Ȥˤ�ꡢ
     * ����߲�ǽ�Ȥʤ롣
     *
     * @pre    �ʤ�
     * @post   isFull() == false ���� write() == true �Ǥ��롣
     * 
     * @else
     *
     * @brief Clear the buffer
     *
     * All of the buffer elements are cleared. As a consequence of clear
     * operation, the buffer can be writable.
     *
     * @pre    None
     * @post   isFull() == false and write() == true.
     *
     * @endif
     */
    virutal void clear() = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե���Ĺ�����������
     *
     * �ݻ����Ƥ���Хåե��Υ��������֤���
     *
     * @pre    �ʤ�
     * @post   �ʤ�
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * This operation returns the buffer length.
     *
     * @pre    �ʤ�
     * @post   �ʤ�
     *
     * @endif
     */
    virtual long int length() const = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ�����񤭹���
     *
     * �Хåե��˥ǡ�����񤭹��ࡣ�Хåե��˲��餫����ͳ�ǽ񤭹���ʤ����
     * false ���֤����ޤ� isFull() == true �ξ��ˤ� false ���֤���
     * 
     * @pre    �ʤ�
     * @pre    isEmpty() == false
     * @value  value �Хåե��˽񤭹�����
     * @return �Хåե��˽񤭹���ʤ����ϵ����֤�
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * This operation writes data to the buffer. This operation returns false,
     * if it cannot write to the buffer for any reason. This operation also
     * returns false if isFull() returns true.
     *
     * @pre    None
     * @post   isEmpty == false
     * @param  value Data to be written to the buffer
     * @return false would be returned when data writing to the buffer fails.
     *
     * @endif
     */
    virtual bool write(const DataType& value) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե�����ǡ������ɤ߽Ф�
     * 
     * �Хåե�����ǡ������ɤ߽Ф����Хåե����鲿�餫����ͳ���ɤ߽Ф��ʤ����
     * false ���֤����ޤ� isEmpty() == true �ξ��ˤ� false ���֤���
     *
     * @pre    �ʤ�
     * @post   isFull() == false
     * @param  value
     * @return �Хåե������ɤ߽Ф��ʤ����ϵ����֤�
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * This operation reads data from the buffer. This operation returns false,
     * if it cannot read from the buffer for any reason. This operation also
     * returns false if isEmpty() returns true.
     *
     * @pre    None
     * @post   isFull() == false
     * @param  value Variable to be read from the buffer
     * @return false would be returned when data reading from the buffer fails.
     *
     * @endif
     */
    virtual bool read(DataType& value) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե��� full �Ǥ��뤫�ɤ���
     *
     * �Хåե��� full ���ɤ����֤����Хåե��� full �Ǥ���� true ��
     * �����Ǥʤ���� false ���֤���
     * �Хåե��� full �Ǥ��뤫�ɤ���������϶�ݥ��饹�μ����˰�¸���롣
     * �����ʤ���� full �ˤʤ�ʤ��Хåե���������Ƥ�褤�����ξ�硢
     * ���δؿ��Ͼ�� false ���֤���
     *
     * @pre    �ʤ�
     * @post   isFull() == true �ʤ�� isEmpty() == false
     * @return �Хåե��� full �Ǥ���� true �򡢤����Ǥʤ���� false ���֤���
     * 
     * @else
     *
     * @brief True if the buffer is full, else false.
     *
     * This operation returns boolean whether the buffer is full or not.
     * If the buffer is full it returns true, if it is not full it returns
     * false.
     * The definition of the "buffer full" depends on the concrete class's
     * implementation. The buffer that is never filled can be implemented.
     * In this case, this operation always returns false.
     *
     * @pre    None
     * @post   isEmpty() == false when isFull() == true
     * @return If the buffer is full, true is returned. Otherwise false is
     *         returned.
     *
     * @endif
     */
    virtual bool isFull() const = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե��� empty �Ǥ��뤫�ɤ���
     *
     * �Хåե��� empty ���ɤ����֤����Хåե��� empty �Ǥ���� true ��
     * �����Ǥʤ���� false ���֤���
     * �Хåե��� empty �Ǥ��뤫�ɤ���������϶�ݥ��饹�μ����˰�¸���롣
     * �����ʤ���� empty �ˤʤ�ʤ��Хåե���������Ƥ�褤�����ξ�硢
     * ���δؿ��Ͼ�� false ���֤���
     *
     * @pre    �ʤ�
     * @post   isEmpty() == true �ʤ�� isFull() == false
     * @return �Хåե��� empty �Ǥ���� true �򡢤����Ǥʤ���� false ���֤���
     * 
     * @else
     *
     * @brief True if the buffer is empty, else false.
     *
     * This operation returns boolean whether the buffer is empty or not.
     * If the buffer is empty it returns true, if it is not empty it returns
     * false.
     * The definition of the "buffer empty" depends on the concrete class's
     * implementation. The buffer that is never emptied can be implemented.
     * In this case, this operation always returns false.
     *
     * @pre    None
     * @post   isFull() == false when isEmpty() == true
     * @return If the buffer is empty, true is returned. Otherwise false is
     *         returned.
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
     * �Хåե��˥ǡ�����񤭹��ि��Υץ�ߥƥ��֤ʴؿ���
     * ���δؿ��ϡ�BufferBase���饹��Ѿ�������ݥ��饹��ǡ��Хåե��ؤν����
     * ������Ū�˶��̲����뤿��Υ��󥿡��ե������Ȥ���¸�ߤ��롣
     *
     * ���δؿ��ϥХåե�������߲�ǽ�ʾ��ˤΤ߸ƤӽФ���ǽ�Ǥ��롣
     * ���������Хåե�������߲�ǽ�Ǥ��뤫�ɤ���������������write()�ؿ�
     * ��ǽ���߲�ǽ�Ǥ��뤫�ɤ��������å��ϡ���ݥ��饹�����Ԥ���Ǥ�Ǥ��롣
     *
     * @pre   isFull() == false
     * @post  isEmpty() == false
     * @param data �Хåե��˽񤭹��ޤ��ǡ���
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * This operation is primitive function to write data to the buffer.
     * This operation is used to unify writing method to the buffer internally
     * in the concrete classes which inherit this class.
     *
     * This operation can be called only when the buffer is writable.
     * The definition of the "writable" depends on each implementation.
     * The developer of the concrete class is responsible for checking whether
     * the buffer is writable in the "write()" function.
     *
     * @pre   isFull() == false
     * @post  isEmpty() == false
     * @param data Data to be written to the buffer
     *
     * @endif
     */
    virtual void put(const DataType& data) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե�����ǡ������ɤߤ���
     * 
     * �Хåե�����ǡ������ɤ߽Ф�����Υץ�ߥƥ��֤ʴؿ���
     * ���δؿ��ϡ�BufferBase���饹��Ѿ�������ݥ��饹��ǡ��Хåե������
     * �ɤ߹��ߤ�����Ū�˶��̲����뤿��Υ��󥿡��ե������Ȥ���¸�ߤ��롣
     *
     * ���δؿ��ϥХåե����ɽФ���ǽ�ʾ��ˤΤ߸ƤӽФ���ǽ�Ǥ��롣
     * ���������Хåե����ɽФ���ǽ�Ǥ��뤫�ɤ���������������read()�ؿ�
     * ����ɽФ���ǽ�Ǥ��뤫�ɤ��������å��ϡ���ݥ��饹�����Ԥ���Ǥ�Ǥ��롣
     *
     * @pre   isEmpty() == false
     * @post  isFull() == false
     * @param data �Хåե������ɤ߽Ф����ǡ���
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * This operation is primitive function to read data from the buffer.
     * This operation is used to unify reading method to the buffer internally
     * in the concrete classes which inherit this class.
     *
     * This operation can be called only when the buffer is readable.
     * The definition of the "readable" depends on each implementation.
     * The developer of the concrete class is responsible for checking whether
     * the buffer is readable in the "read()" function.
     *
     * @pre   isEmpty() == false
     * @post  isFull() == false
     * @param data Data to be read from the buffer
     *
     * @endif
     */
    virtual const DataType& get() = 0;

    /*!
     * @if jp
     *
     * @brief ���˽񤭹���Хåե��λ��Ȥ��������
     *
     * ��ݥ��饹�ǳ��ݤ����Хåե��ΰ�Τ�����put()�ǽ񤭹��ޤ���ΰ��
     * ���Ȥ��֤���
     *
     * @pre    �ʤ�
     * @post   �ʤ�
     * @return put()�ǽ񤭹��ޤ���ΰ�λ���
     * 
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * @pre    None
     * @post   None
     * @return The reference to the element to be written by put()
     *
     * @endif
     */
    virtual DataType& getRef() = 0;

  };



  //============================================================
  /*!
   * @if jp
   * @class NullBuffer
   * @brief NullBuffer ���饹
   *
   * NullBuffer ���饹�ϰ�ĤΥХåե��ΰ����ĥХåե���ݥ��饹�Ǥ��롣
   * ���Υ��饹��full���֤�empty���֤⸡�Ф��ʤ��Хåե��Ǥ��롣
   * 
   * ���äƾ��
   * - write() == true
   * - read()  == true
   * - isFull() == false
   * - isEmpty() == false
   * �Ǥ��롣
   *
   * ̤����ߤξ��֤� read() ���֤��ͤ�����Ǥ��롣
   * ���ΥХåե����饹��BufferBase�ζ�ݥ��饹��ñ�����Ȥ����������Ƥ��ꡢ
   * ����Ū�����Ӥˤ�������ѤϿ侩����ʤ���
   * 
   * @param DataType �Хåե��˳�Ǽ����ǡ�����
   *
   * @else
   *
   * @class NullBuffer
   * @brief NullBuffer class
   *
   * NullBuffer is concrete class that has only one element in the buffer.
   * This buffer class does not detect full status and empty status.
   *
   * Therefore this class methods always return the following
   * - write() == true
   * - read()  == true
   * - isFull() == false
   * - isEmpty() == false
   *
   * read() function returns undefined value before writing to the buffer.
   * Since this buffer class is defined as an example of a concrete class of
   * BufferBase, using it in practical purpose is not recommended.
   *
   * @param DataType Data type to be stored to the buffer.
   *
   * @endif
   */
  template <class DataType>
  class NullBuffer
    : public BufferBase<DataType>
  {
  public:
    NullBuffer(long int size = 1)
      : m_length(1), m_empty(true)
    {
    }

    virtual ~NullBuffer()
    {
    }

    /*!
     * @if jp
     *
     * @brief �Хåե�����������
     * 
     * �Хåե�������Ƥ����Ǥ�Ϳ����줿�ͤǽ��������롣
     *
     * @pre    �ʤ�
     * @post   isEmpty() == false ���� read() == true �Ǥ��ꡢread(data) ��
     *         ����ͤϽ�����˻��Ѥ����ͤǤ���
     * @param  data �Хåե��ν�����˻��Ѥ���ǡ���
     *
     * @else
     *
     * @brief Get the buffer length
     *
     * All of the buffer elements are initilized by the given data value.
     *
     * @pre    None
     * @post   isEmpty() == false and read() == true, and return value of
     *         read(data) should return initialized data.
     * @param  data Data to be used to initialize the buffer.
     *
     * @endif
     */
    virtual void init(const DataType& data)
    {
      put(data);
    }

    /*!
     * @if jp
     *
     * @brief �Хåե��򥯥ꥢ����
     * 
     * �Хåե�������Ƥ����Ǥ򥯥ꥢ���롣
     *
     * @pre    �ʤ�
     * @post   �ʤ�
     * 
     * @else
     *
     * @brief Clear the buffer
     *
     * All of the buffer elements are cleared.
     *
     * @pre    None
     * @post   None
     *
     * @endif
     */
    virtual void clear()
    {
      m_empty = true;
    }

    /*!
     * @if jp
     *
     * @brief �Хåե���Ĺ�����������
     *
     * �ݻ����Ƥ���Хåե��Υ��������֤���
     *
     * @pre    �ʤ�
     * @post   �ʤ�
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * This operation returns the buffer length.
     *
     * @pre    �ʤ�
     * @post   �ʤ�
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
     * �Хåե��˥ǡ�����񤭹��ࡣ
     * ���δؿ��Ͼ�� true ���֤���
     * 
     * @pre    �ʤ�
     * @pre    isEmpty() == false
     * @value  value �Хåե��˽񤭹�����
     * @return ��� true ���֤�
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * This operation writes data to the buffer.
     * This operation always returns true.
     *
     * @pre    None
     * @post   isEmpty == false
     * @param  value Data to be written to the buffer
     * @return true is returned always
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
     * @brief �Хåե�����ǡ������ɤ߽Ф�
     * 
     * �Хåե�����ǡ������ɤ߽Ф���
     * ���δؿ��Ͼ�� true ���֤���
     *
     * @pre    �ʤ�
     * @post   isFull() == false
     * @param  value
     * @return ��� true ���֤�
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * This operation reads data from the buffer.
     * This operation always returns true.
     *
     * @pre    None
     * @post   isFull() == false
     * @param  value Variable to be read from the buffer
     * @return true is returned always
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
     * @brief �Хåե��� full �Ǥ��뤫�ɤ���
     *
     * �Хåե��� full ���ɤ����֤���
     * ���δؿ��Ͼ��false ���֤���
     *
     * @pre    �ʤ�
     * @post   �ʤ�
     * @return ��� false ���֤���
     * 
     * @else
     *
     * @brief True if the buffer is full, else false.
     *
     * This operation returns boolean whether the buffer is full or not.
     * This operation always returns false.
     *
     * @pre    None
     * @post   isEmpty() == false when isFull() == true
     * @return false is returned always
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
     * @brief �Хåե��� empty �Ǥ��뤫�ɤ���
     *
     * �Хåե��� empty ���ɤ����֤���
     * ���δؿ��Ͼ�� false ���֤���
     *
     * @pre    �ʤ�
     * @post   �ʤ�
     * @return ��� false ���֤���
     * 
     * @else
     *
     * @brief True if the buffer is empty, else false.
     *
     * This operation returns boolean whether the buffer is empty or not.
     * If the buffer is empty it returns true, if it is not empty it returns
     * false.
     * The definition of the "buffer empty" depends on the concrete class's
     * implementation. The buffer that is never emptied can be implemented.
     * In this case, this operation always returns false.
     *
     * @pre    None
     * @post   isFull() == false when isEmpty() == true
     * @return false is returned always
     *
     * @endif
     */
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
