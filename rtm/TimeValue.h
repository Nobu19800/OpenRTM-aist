// -*- C++ -*-
/*!
 * @file TimeValue.h
 * @brief TimeValue class
 * @date $Date: 2007-10-06 12:27:35 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: TimeValue.h,v 1.1.2.3 2007-10-06 12:27:35 n-ando Exp $
 *
 */

#ifndef TimeValue_h
#define TimeValue_h

#include <iostream>
#include <ace/OS_NS_time.h>

#define TIMEVALUE_ONE_SECOND_IN_USECS 1000000 // 1 [sec] = 1000000 [usec]


/*!
 * @if jp
 * @class TimeValue
 * @brief ���ַ׻��ѥ��饹
 * 
 * ���ꤷ�������ͤ��ݻ����뤿��Υ��饹��
 * �����ͤ��Ф���Ƽ�׻��ѥ��ڥ졼�������󶡤��롣
 *
 * @since 0.4.0
 *
 * @else
 * @class TimeValue
 * @brief Class for time calculation
 * 
 * This is a class to hold the specified time value.
 * This class provides the operations for various calculations of 
 * the time value.
 *
 * @since 0.4.0
 *
 * @endif
 */
struct TimeValue
  : public timeval
{
  /*!
   * @if jp
   *
   * @brief ���󥹥ȥ饯��
   * 
   * ���󥹥ȥ饯��
   * ���ꤵ�줿�á��ޥ������äǽ�������롣
   *
   * @param sec ��(�ǥե������:����)
   * @param usec �ޥ�������(�ǥե������:����)
   * 
   * @else
   *
   * @brief Constructor
   * 
   * Constructor
   * Initialize with the specified second and micro second.
   *
   * @param sec Second(The default value:0)
   * @param usec Micro second(The default value:0)
   * 
   * @endif
   */
  TimeValue(long sec=0, long usec=0)
  {
    tv_sec = sec;
    tv_usec = usec;
    normalize();
  }
  
  /*!
   * @if jp
   *
   * @brief ���ָ���
   * 
   * ���ꤵ�줿���֤��������Ϳ����줿���֤򸺻����롣
   *
   * @param tm ��������
   * 
   * @return �������
   * 
   * @else
   *
   * @brief Time subtraction
   * 
   * Subtract the time given by the argument from the set time.
   *
   * @param tm Subtracted time
   * 
   * @return Subtraction result
   * 
   
   * @endif
   */
  TimeValue operator-(TimeValue& tm)
  {
    TimeValue res;
    if (tv_sec >= tm.tv_sec) // +
      {
	if (tv_usec >= tm.tv_usec) // ���겼����̵��
	  {
	    res.tv_sec  = tv_sec  - tm.tv_sec;  // -
	    res.tv_usec = tv_usec - tm.tv_usec; // +
	  }
	else // tv_usec < tm.tv_usec ���겼����ͭ��
	  {
	    res.tv_sec  = tv_sec  - tm.tv_sec - 1;
	    res.tv_usec = (tv_usec + 1000000) - tm.tv_usec;
	  }
      }
    else // tv_sec < tm.tv_sec // -
      {
	if (tm.tv_usec >= tv_usec) // ���겼����̵��
	  {
	    res.tv_sec  = - (tm.tv_sec  - tv_sec); // +
	    res.tv_usec = - (tm.tv_usec - tv_usec);  // +
	  }
	else // tm.tv_usec < tv_usec ���겼����ͭ��
	  {
	    res.tv_sec  = - (tm.tv_sec - tv_sec  - 1);
	    res.tv_usec = - (tm.tv_usec + 1000000) + tv_usec;
	  }
      }
    res.normalize();
    return res;
  }
  
  /*!
   * @if jp
   *
   * @brief ���ֲû�
   * 
   * ���ꤵ�줿���֤˰�����Ϳ����줿���֤�û����롣
   *
   * @param tm �û�����
   * 
   * @return �û����
   * 
   * @else
   *
   * @brief Time addition
   * 
   * Add the time given by the argument to the set time.
   *
   * @param tm Added time
   * 
   * @return Addition result
   * 
   * @endif
   */
  TimeValue operator+(TimeValue& tm)
  {
    TimeValue res;
    res.tv_sec  = tv_sec  + tm.tv_sec;
    res.tv_usec = tv_usec + tm.tv_usec;
    if (res.tv_usec >= 1000000)
      {
	++res.tv_sec;
	res.tv_usec -= 1000000;
      }
    res.normalize();
    return res;
  }
  
  /*!
   * @if jp
   *
   * @brief double�������ַ��Ѵ�
   * 
   * ������Ϳ����줿double������ַ����Ѵ����롣
   *
   * @param time �Ѵ�����
   * 
   * @return �Ѵ����
   * 
   * @else
   *
   * @brief Convert double type into time type
   * 
   * Convert double type given by the argument into time type.
   *
   * @param time the original value
   * 
   * @return Conversion result
   * 
   * @endif
   */
  TimeValue operator=(double time)
  {
    tv_sec = (long)time;
    tv_usec = (long)((time - (double)tv_sec)*1000000.0 + 0.5);
    normalize();
    return *this;
  }
  
  /*!
   * @if jp
   *
   * @brief ���ַ���double���Ѵ�
   * 
   * �ݻ����Ƥ������Ƥ�double�����Ѵ����롣
   *
   * @return double���Ѵ����
   * 
   * @else
   *
   * @brief Convert time type into double type
   * 
   * Convert held information into double type.
   *
   * @return Result for conversion of double type
   * 
   * @endif
   */
  double toDouble()
  {
    normalize();
    return (double)tv_sec + ((double)tv_usec/1000000.0);
  }
  
  /*!
   * @if jp
   * 
   * @brief ���Ƚ��
   * 
   * �ݻ����Ƥ������Ƥ�����Ƚ�ꤹ�롣
   * 
   * @return ���ʤ��1����ʤ��-1��0�ʤ��0
   * 
   * @else
   *  
   * @brief Sign judgment
   * 
   * Judge sign of the held contents
   * 
   * @return 1 if the return value is Plus sign, -1 if Minus, and 0 if 0.
   * 
   * @endif
   */
  int sign()
  {
    if (tv_sec > 0) return 1;
    if (tv_sec < 0) return -1;
    if (tv_usec > 0) return 1;
    if (tv_usec < 0) return -1;
    return 0;
  }
  
private:
  
  /*!
   * @if jp
   * 
   * @brief ������
   * 
   * �ͤ�ɽ����������������������롣
   * 
   * @else
   * 
   * @brief Normalize
   * 
   * Normalize the value expression into a canonical form.
   * 
   * @endif
   */
  void normalize()
  {
    if (tv_usec >= TIMEVALUE_ONE_SECOND_IN_USECS)
      {
	do
	  {
	    ++tv_sec;
	    tv_usec -= TIMEVALUE_ONE_SECOND_IN_USECS;
	  }
	while (tv_usec >= TIMEVALUE_ONE_SECOND_IN_USECS);
      }
    else if (tv_usec <= -TIMEVALUE_ONE_SECOND_IN_USECS)
      {
	do
	  {
	    --tv_sec;
	    tv_usec += TIMEVALUE_ONE_SECOND_IN_USECS;
	  }
	while (tv_usec <= -TIMEVALUE_ONE_SECOND_IN_USECS);
      }
    
    if (tv_sec >= 1 && tv_usec < 0)
      {
	--tv_sec;
	tv_usec += TIMEVALUE_ONE_SECOND_IN_USECS;
      }
    else if (tv_sec < 0 && tv_usec > 0)
      {
	++tv_sec;
	tv_usec -= TIMEVALUE_ONE_SECOND_IN_USECS;
      }
  }
  
  //  friend std::ostream& operator<<(std::ostream& lhs, const TimeValue& rhs);
};

/***
    std::ostream& operator<<(std::ostream& lhs, const TimeValue& rhs)
    {
    double res;
    res = (double)rhs.tv_sec + ((double)rhs.tv_usec/1000000.0);
    lhs << res;
    return lhs;
    }
*/

#endif // TimeValue_h
