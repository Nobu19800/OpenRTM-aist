// -*- C++ -*-
/*!
 * @file  Mutex_vxworks.h
 * @brief coil VxWorks mutex class
 * @date  $Date$
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */


#ifndef COIL_MUTEX_H
#define COIL_MUTEX_H


#include <pthread.h>
#include <semLib.h>
/*
#ifdef __RTP__
#include <semLib.h>
#endif
*/

namespace coil
{
  /*!
   * @if jp
   *
   * @class Mutex
   * @brief Mutex ���饹
   *
   * @else
   *
   * @class Mutex
   * @brief Mutex class
   *
   * @endif
   */
  class Mutex
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     *
     * @param name ���֥�������̾
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Object name
     *
     * @endif
     */
    Mutex(const char * const name = 0)
    {
      mutex_ = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
/*
#ifdef __RTP__
      mutex_ = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
#else
      ::pthread_mutex_init(&mutex_, 0);
#endif
*/
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
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    ~Mutex()
    {
      semDelete(mutex_);
/*
#ifdef __RTP__
      semDelete(mutex_);
#else
      ::pthread_mutex_destroy(&mutex_);
#endif
*/
    }

    /*!
     * @if jp
     *
     * @brief ��¾����Υ�å�
     *
     * ��¾����Υ�å���Ԥ���
     *
     * @else
     *
     * @brief Mutual exclusion lock
     *
     * Lock the Mutual exclusion.
     *
     * @endif
     */
    inline void lock()
    {
      semTake(mutex_, WAIT_FOREVER);
/*
#ifdef __RTP__
      semTake(mutex_, WAIT_FOREVER);
#else
      ::pthread_mutex_lock(&mutex_);
#endif
*/
    }

    /*!
     * @if jp
     *
     * @brief ��¾����ΥΥ�֥�å��󥰥�å�
     *
     * ��¾����Υ�å���Υ�֥�å��󥰤ǹԤ���
     *
     * @else
     *
     * @brief Mutual exclusion non-blocking lock
     *
     * Lock the Mutual exclusion by non-blocking.
     *
     * @endif
     */
    inline bool trylock()
    {
      STATUS status = semTake(mutex_, NO_WAIT);
      return (status == OK);
/*
#ifdef __RTP__
      STATUS status = semTake(mutex_, NO_WAIT);
      return (status == OK);
#else
      return ::pthread_mutex_trylock(&mutex_);
#endif
*/
    }

    /*!
     * @if jp
     *
     * @brief ��¾����Υ�å����
     *
     * ��¾����Υ�å������Ԥ���
     *
     * @else
     *
     * @brief Mutual exclusion unlock
     *
     * Unlock the Mutual exclusion.
     *
     * @endif
     */
    inline void unlock()
    {
      semGive(mutex_);
/*
#ifdef __RTP__
      semGive(mutex_);
#else
      ::pthread_mutex_unlock(&mutex_);
#endif
*/
    }

    /*!
     * @if jp
     *
     * @brief ��¾���楪�֥�������
     *
     * @else
     *
     * @brief Mutual exclusion object
     *
     * @endif
     */
    SEM_ID mutex_;
/*
#ifdef __RTP__
    SEM_ID mutex_;
#else
    pthread_mutex_t mutex_;
#endif
*/

  private:
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex &);
  };
};
#endif // COIL_MUTEX_H
