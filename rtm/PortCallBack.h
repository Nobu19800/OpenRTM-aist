// -*- C++ -*-
/*!
 * @file PortCallBack.h
 * @brief PortCallBack class
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
 * $Id: PortCallBack.h,v 1.2.4.2 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2.4.1  2007/09/19 07:41:28  n-ando
 * Timeout callbacks were added.
 *
 * Revision 1.2  2007/01/21 12:56:35  n-ando
 * virtual dtors were defined.
 *
 * Revision 1.1  2006/12/02 18:51:18  n-ando
 * The first commitment.
 *
 *
 */

#ifndef PortCallBack_h
#define PortCallBack_h

namespace RTC
{
  //============================================================
  // callback functor base classes
  /*!
   * @if jp
   * @class OnWrite
   * @brief write() ���Υ�����Хå���ݥ��饹
   *
   * DataPort�ΥХåե��˥ǡ�����write()�����ľ���˸ƤӽФ���륳����Хå���
   * ���󥿡��ե�������
   *
   * @param DataType �Хåե��˽񤭹���ǡ�����
   *
   * @since 0.4.0
   *
   * @else
   * @class OnPut
   * @brief OnPut abstract class
   *
   * @endif
   */
  template <class DataType>
  struct OnWrite
  {
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
    virtual ~OnWrite(){}
    
    /*!
     * @if jp
     *
     * @brief ������Хå��᥽�å�
     *
     * �Хåե��˥ǡ������񤭹��ޤ��ľ���˸ƤӽФ���륳����Хå��᥽�å�
     *
     * @param value �Хåե��˽񤭹��ޤ��ǡ���
     *
     * @else
     *
     * @endif
     */
    virtual void operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnWriteConvert
   * @brief write() ���Υǡ����Ѵ�������Хå���ݥ��饹
   *
   * InPort/OutPort�ΥХåե��˥ǡ����� write()�������˸ƤӽФ����
   * ������Хå��ѥ��󥿡��ե�������
   * ���Υ�����Хå�������ͤ��Хåե��˳�Ǽ����롣
   *
   * @since 0.4.0
   *
   * @else
   * @class OnWriteConvert
   * @brief OnWriteConvert abstract class
   *
   * @endif
   */
  template <class DataType>
  struct OnWriteConvert
  {
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
    virtual ~OnWriteConvert(){}
    
    /*!
     * @if jp
     *
     * @brief ������Хå��᥽�å�
     *
     * �Хåե��˥ǡ������񤭹��ޤ��ݤ˸ƤӽФ���륳����Хå��᥽�å�
     *
     * @param value �Ѵ����ǡ���
     *
     * @return �Ѵ���ǡ���
     *
     * @else
     *
     * @endif
     */
    virtual DataType operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnRead
   * @brief read() ���Υ�����Хå���ݥ��饹
   *
   * InPort/OutPort�ΥХåե�����ǡ����� read()�����ľ���˸ƤӽФ����
   * ������Хå��ѥ��󥿡��ե�������
   *
   * @since 0.4.0
   *
   * @else
   * @class OnRead
   * @brief OnRead abstract class
   *
   * @endif
   */
  template <class DataType>
  struct OnRead
  {
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
    virtual ~OnRead(){}
    
    /*!
     * @if jp
     *
     * @brief ������Хå��᥽�å�
     *
     * �Хåե�����ǡ������ɤ߽Ф����ľ���˸ƤӽФ���륳����Хå��᥽�å�
     *
     * @else
     *
     * @endif
     */
    virtual void operator()() = 0;
  };
  
  /*!
   * @if jp
   * @class OnReadConvert
   * @brief read() ���Υǡ����Ѵ�������Хå���ݥ��饹
   *
   * InPort/OutPort�ΥХåե�����ǡ����� read()�����ݤ˸ƤӽФ����
   * ������Хå��ѥ��󥿡��ե�������
   * ���Υ�����Хå�������ͤ�read()������ͤȤʤ롣
   *
   * @since 0.4.0
   *
   * @else
   * @class OnReadConvert
   * @brief OnReadConvert abstract class
   *
   * @endif
   */
  template <class DataType>
  struct OnReadConvert
  {
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
    virtual ~OnReadConvert(){}
    
    /*!
     * @if jp
     *
     * @brief ������Хå��᥽�å�
     *
     * �Хåե�����ǡ������ɤ߽Ф����ݤ˸ƤӽФ���륳����Хå��᥽�å�
     *
     * @else
     *
     * @endif
     */
    virtual DataType operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnOverflow
   * @brief �Хåե������С��ե����Υ�����Хå���ݥ��饹
   *
   * InPort/OutPort�ΥХåե��˥ǡ�����put()���������Хåե������С��ե���
   * ���������˸ƤФ�륳����Хå��᥽�åɡ�
   *
   * @since 0.4.0
   *
   * @else
   * @class OnOverflow
   * @brief OnOverflow abstract class
   *
   * @endif
   */
  template <class DataType>
  struct OnOverflow
  {
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
    virtual ~OnOverflow(){}
    
    /*!
     * @if jp
     *
     * @brief ������Хå��᥽�å�
     *
     * �Хåե������С��ե����˸ƤӽФ���륳����Хå��᥽�å�
     *
     * @param value �Хåե��ؽ񤭹���ǡ���
     *
     * @else
     *
     * @endif
     */
    virtual void operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnUnderflow
   * @brief Underflow ���Υ�����Хå���ݥ��饹
   *
   * @since 0.4.0
   *
   * InPort/OutPort�ΥХåե��˥ǡ�����read()�������ˡ��ɤ߽Ф��٤��ǡ�����
   * �ʤ����˸ƤӽФ���륳����Хå����󥿥ե�������
   * ���Υ�����Хå�������ͤ�read()������ͤȤʤ롣
   *
   * @else
   * @class OnUnderflow
   * @brief OnUnderflow abstract class
   *
   * @endif
   */
  template <class DataType>
  struct OnUnderflow
  {
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
    virtual ~OnUnderflow(){}
    
    /*!
     * @if jp
     *
     * @brief ������Хå��᥽�å�
     *
     * �Хåե���������ե����˸ƤӽФ���륳����Хå��᥽�å�
     *
     * @return ���ؤȤʤ��ɤ߽Ф��ǡ���
     *
     * @else
     *
     * @endif
     */
    virtual DataType operator()() = 0;
  };
  
  /*!
   * @if jp
   * @class OnWriteTimeout
   * @brief �����ॢ���Ȼ��Υ�����Хå���ݥ��饹
   *
   * InPort/OutPort�ΥХåե��˥ǡ�����write()����ݤˡ������ॢ���Ȥ�ȯ������
   * ���˸ƤӽФ���륳����Хå����󥿥ե�������
   *
   * @since 0.4.0
   *
   * @else
   * @class OnWriteTimeout
   * @brief OnWriteTimeout abstract class
   *
   * @endif
   */
  template <class DataType>
  struct OnWriteTimeout
  {
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
    virtual ~OnWriteTimeout(){}
    
    /*!
     * @if jp
     *
     * @brief ������Хå��᥽�å�
     *
     * �����ॢ����ȯ�����˸ƤӽФ���륳����Хå��᥽�å�
     *
     * @param value �Хåե��ؽ񤭹���ǡ���
     *
     * @else
     *
     * @endif
     */
    virtual void operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnReadTimeout
   * @brief �����ॢ���Ȼ��Υ�����Хå���ݥ��饹
   *
   * InPort/OutPort�ΥХåե��˥ǡ�����read()����ݤˡ������ॢ���Ȥ�ȯ������
   * ���˸ƤӽФ���륳����Хå����󥿥ե�������
   *
   * @since 0.4.0
   *
   * @else
   * @class OnReadTimeout
   * @brief OnReadTimeout abstract class
   *
   * @endif
   */
  template <class DataType>
  struct OnReadTimeout
  {
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
    virtual ~OnReadTimeout(){}
    
    /*!
     * @if jp
     *
     * @brief ������Хå��᥽�å�
     *
     * �����ॢ����ȯ�����˸ƤӽФ���륳����Хå��᥽�å�
     *
     * @return ���ؤȤʤ��ɤ߽Ф��ǡ���
     *
     * @else
     *
     * @endif
     */
    virtual DataType operator()() = 0;
  };
};
#endif // PortCallBack_h
