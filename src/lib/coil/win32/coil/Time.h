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
//#include <WinSock2.h>
//#pragma comment(lib, "WS2_32.LIB")
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
    auto t = std::chrono::seconds(interval.sec())
             + std::chrono::microseconds(interval.usec());
    std::this_thread::sleep_for(t);
    return 0;
  }

  /*!
   * @if jp
   * @brief 時刻とタイムゾーンを取得する
   *
   * 時刻とタイムゾーンを取得する。
   *
   * @param tv 時刻構造体
   * @param tz タイムゾーン構造体
   *
   * @return 0: 成功
   *
   * @else
   * @brief Get the time and timezone
   *
   * Get the time and timezone
   *
   * @param tv Structure of time
   * @param tz Structure of timezone
   *
   * @return 0: successful
   *
   * @endif
   */
  int gettimeofday(struct timeval *tv, struct timezone *tz);
  /*!
   * @if jp
   * @brief 時刻を取得する
   *
   * 時刻を取得する。
   *
   * @return TimeValueオブジェクト
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
  inline TimeValue gettimeofday()
  {
    timeval tv;
    coil::gettimeofday(&tv, 0);
    return TimeValue(tv.tv_sec, tv.tv_usec);
  }

  /*!
   * @if jp
   * @brief 時刻とタイムゾーンを設定する
   *
   * 時刻とタイムゾーンを設定する。
   *
   * @param tv 時刻構造体
   * @param tz タイムゾーン構造体
   *
   * @return 0: 成功
   *
   * @else
   * @brief Set the time and timezone
   *
   * Set the time and timezone
   *
   * @param tv Structure of time
   * @param tz Structure of timezone
   *
   * @return 0: successful
   *
   * @endif
   */
  int settimeofday(const struct timeval *tv , const struct timezone *tz);


  /*!
  * @if jp
  * @brief 高分解能パフォーマンスカウンタから時間を取得する
  * 高分解能パフォーマンスカウンタが利用できない場合はgettimeofday関数から取得する
  *
  * @param tv 時間
  *
  * @return 0: 成功
  *
  * @else
  * @brief
  *
  *
  * @param tv
  *
  * @return 0: successful
  *
  * @endif
  */
  int clock(TimeValue &tv);

  /*!
   * @if jp
   * @brief 高分解能パフォーマンスカウンタから時間を取得する
   *
   *
   * @return TimeValueオブジェクト
   *
   * @else
   * @brief 
   *
   *
   *
   * @return TimeValue object
   *
   * @endif
   */
  TimeValue clock();



} // namespace coil

#endif  // COIL_TIME_H
