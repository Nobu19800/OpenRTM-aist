﻿// -*- C++ -*-
/*!
 * @file Time_win32.h
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


#include <Windows.h>
#ifdef WITH_ACE
#include <WinSock2.h>
#else
#include <winsock.h>
#endif
#include <time.h>
#include <coil/config_coil.h>
#include <coil/TimeValue.h>
#include <chrono>
#include <thread>

namespace coil
{
#define EPOCHFILETIME (116444736000000000i64)
  struct timezone
  {
    int tz_minuteswest;
    int tz_dsttime;
  };

/*!
   * @if jp
   * @brief 指定された秒間は処理を休止する
   *
   * 指定された秒間は処理を休止する。
   *
   * @param interval TimeValueオブジェクト
   *
   * @return 0: 成功, != 0: 失敗
   *
   * @else
   * @brief Stop a processing at specified second time
   *
   * Stop a processing at specified second time.
   *
   * @param interval TimeValue object
   *
   * @return 0: successful, != 0: failed
   *
   * @endif
   */
  inline int sleep(TimeValue interval)
  {
    std::this_thread::sleep_for(interval.microseconds());
    return 0;
  }
} // namespace coil

#endif  // COIL_TIME_H
