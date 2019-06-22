// -*- C++ -*-
/*!
 * @file Time_posix.h
 * @brief Time functions
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_TIME_H
#define COIL_TIME_H

#include <coil/config_coil.h>
#include <coil/TimeValue.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include <thread>

namespace coil
{
  /*!
   * @if jp
   * @brief ���ꤵ�줿�ô֤Ͻ�����ٻߤ���
   *
   * ���ꤵ�줿�ô֤Ͻ�����ٻߤ��롣
   *
   * @param interval TimeValue���֥�������
   *
   * @return 0: ����, >0: ����
   *
   * @else
   * @brief Stop a processing at specified second time
   *
   * Stop a processing at specified second time.
   *
   * @param interval TimeValue object
   *
   * @return 0: successful, >0: failed
   *
   * @endif
   */
  inline int sleep(TimeValue interval)
  {
    std::this_thread::sleep_for(interval.microseconds());
    return 0;
  }

  /*!
   * @if jp
   * @brief ����ȥ����ॾ������������
   *
   * ����ȥ����ॾ�����������롣
   *
   * @param tv ���ﹽ¤��
   * @param tz �����ॾ����¤��
   *
   * @return 0: ����, -1: ����
   *
   * @else
   * @brief Get the time and timezone
   *
   * Get the time and timezone
   *
   * @param tv Structure of time
   * @param tz Structure of timezone
   *
   * @return 0: successful, -1: failed
   *
   * @endif
   */
  inline int gettimeofday(struct timeval *tv, struct timezone *tz)
  {
    return ::gettimeofday(tv, tz);
  }

  /*!
   * @if jp
   * @brief ������������
   *
   * �����������롣
   *
   * @return TimeValue���֥�������
   *
   * @else
   * @brief Get the time
   *
   * Get the time
   *
   * @return TimeValue object
   *
   * @endif
   */
  TimeValue gettimeofday();

  /*!
   * @if jp
   * @brief ����ȥ����ॾ��������ꤹ��
   *
   * ����ȥ����ॾ��������ꤹ�롣
   *
   * @param tv ���ﹽ¤��
   * @param tz �����ॾ����¤��
   *
   * @return 0: ����, -1: ����
   *
   * @else
   * @brief Set the time and timezone
   *
   * Set the time and timezone
   *
   * @param tv Structure of time
   * @param tz Structure of timezone
   *
   * @return 0: successful, -1: failed
   *
   * @endif
   */
  inline int settimeofday(const struct timeval *tv , const struct timezone *tz)
  {
    return ::settimeofday(tv, tz);
  }
} // namespace coil

#endif  // COIL_TIME_H
