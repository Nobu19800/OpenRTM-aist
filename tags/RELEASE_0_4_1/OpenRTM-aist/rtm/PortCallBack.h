// -*- C++ -*-
/*!
 * @file PortCallBack.h
 * @brief PortCallBack class
 * @date $Date: 2007-09-19 07:41:28 $
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
 * $Id: PortCallBack.h,v 1.2.4.1 2007-09-19 07:41:28 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
   * DataPort�ΥХåե��˥ǡ�����write()��������
   * ���Υ�����Хå����ƤФ�롣
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
    virtual ~OnWrite(){}
    virtual void operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnWriteConvert
   * @brief write() ���Υǡ����Ѵ�������Хå���ݥ��饹
   *
   * InPort�ΥХåե��˥ǡ����� write()�������ˤ��Υ�����Хå����ƤФ졢
   * ���Υ�����Хå�������ͤ��Хåե��˳�Ǽ����롣
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
    virtual ~OnWriteConvert(){}
    virtual DataType operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnRead
   * @brief read() ���Υ�����Хå���ݥ��饹
   *
   * DataPort�ΥХåե�����ǡ�����read()��������
   * ���Υ�����Хå����ƤФ�롣
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
    virtual ~OnRead(){}
    virtual void operator()() = 0;
  };
  
  /*!
   * @if jp
   * @class OnReadConvert
   * @brief read() ���Υǡ����Ѵ�������Хå���ݥ��饹
   *
   * InPort�ΥХåե�����ǡ����� read()�������ˤ��Υ�����Хå����ƤФ졢
   * ���Υ�����Хå�������ͤ�read()������ͤȤʤ롣
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
    virtual ~OnReadConvert(){}
    virtual DataType operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnOverflow
   * @brief �Хåե������С��ե����Υ�����Хå���ݥ��饹
   *
   * �Хåե��˥ǡ�����put()���������Хåե������С��ե���
   * ���������ˤ��Υ�����Хå����ƤФ�롣
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
    virtual ~OnOverflow(){}
    virtual void operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnUnderflow
   * @brief Underflow ���Υ�����Хå���ݥ��饹
   *
   * InPort�ΥХåե��˥ǡ�����put()�������ˤ��Υ�����Хå����ƤФ�롣
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
    virtual ~OnUnderflow(){}
    virtual DataType operator()() = 0;
  };


  template <class DataType>
  struct OnWriteTimeout
  {
    virtual ~OnWriteTimeout(){}
    virtual void operator()(const DataType& value) = 0;
  };

  template <class DataType>
  struct OnReadTimeout
  {
    virtual ~OnReadTimeout(){}
    virtual DataType operator()() = 0;
  };


  
};
#endif // PortCallBack_h
