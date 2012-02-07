// -*- C++ -*-
/*!
 * @file ClockManager.h
 * @brief Global clock management class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2012
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_CLOCKMANAGER_H
#define COIL_CLOCKMANAGER_H

#include <string>
#include <coil/Singleton.h>
#include <coil/TimeValue.h>
#include <coil/Mutex.h>

namespace coil
{
  /*!
   * @if jp
   * @class �����ݒ�E�擾�I�u�W�F�N�g�̃C���^�[�t�F�[�X
   *
   * ���̃N���X�� ClockManager �ɂ���ĊǗ������N���b�N�I�u�W�F�N�g��
   * ���߂̃C���^�[�t�F�[�X�ł���BClockManager �͕����̃N���b�N�I�u�W�F
   * �N�g���Ǘ����A�K�v�ɉ����ēK�؂ȃN���b�N�I�u�W�F�N�g�� IClock �C��
   * �^�[�t�F�[�X�����I�u�W�F�N�g�Ƃ��ĕԂ��B�N���b�N�I�u�W�F�N�g�͒P
   * �ɃV�X�e��������Ԃ����̂�A�Ǝ��̘_�����������N���b�N�I�u�W�F�N
   * �g�����l������B
   *
   * @else
   * @brief An interface to set and get time
   *
   * This class is a interface for clock objects managed by
   * ClockManager. ClockManager manages one or more clocks, and it
   * returns appropriate clock objects according to demands. The clock
   * object might be clock which just returns system time, or a clock
   * which returns individual logical time.
   *
   * @endif
   */
  class IClock
  {
  public:
    virtual ~IClock() {}
    /*!
     * @if jp
     * @brief �������擾����
     * @return ���݂̎���
     * @else
     * @brief Getting time
     * @return Current time
     * @endif
     */
    virtual coil::TimeValue gettime() const = 0;
    /*!
     * @if jp
     * @brief ������ݒ肷��
     * @param clocktime ���݂̎���
     * @else
     * @brief Setting time
     * @param clocktime Current time
     * @endif
     */
    virtual bool settime(coil::TimeValue clocktime) = 0;
  };

  /*!
   * @if jp
   * @class �V�X�e�������������N���b�N�I�u�W�F�N�g
   *
   * ���̃N���X�̓V�X�e���N���b�N��ݒ�܂��͎擾����N���X�ł���B
   *
   * @else
   * @brief clock object to handle system clock
   *
   * This class sets and gets system clock.
   *
   * @endif
   */
  class SystemClock
    : public IClock
  {
  public:
    virtual ~SystemClock();
    virtual coil::TimeValue gettime() const;
    virtual bool settime(coil::TimeValue clocktime);
  };

  /*!
   * @if jp
   * @class �_�����Ԃ������N���b�N�I�u�W�F�N�g
   *
   * ���̃N���X�͘_�����Ԃ�ݒ�܂��͎擾����N���X�ł���B
   * �P���� settime() �ɂ���Đݒ肳�ꂽ������ gettime() �ɂ���Ď擾���邷�B
   *
   * @else
   * @brief Clock object to handle logical clock
   *
   * This class sets and gets system clock.
   * It just sets time by settime() and gets time by gettime().
   *
   * @endif
   */
  class LogicalClock
    : public IClock
  {
  public:
    LogicalClock();
    virtual ~LogicalClock();
    virtual coil::TimeValue gettime() const;
    virtual bool settime(coil::TimeValue clocktime);
  private:
    coil::TimeValue m_currentTime;
    mutable coil::Mutex m_currentTimeMutex;
  };

  /*!
   * @if jp
   * @class �����ςݎ����������N���b�N�I�u�W�F�N�g
   *
   * settime() �Ăяo�����Ɍ��ݎ����Ƃ̍����I�t�Z�b�g�Ƃ��ĕێ����A
   * gettime() �ɂ���ăI�t�Z�b�g�����ς݂̎�����Ԃ��B
   *
   * @else
   * @brief Clock object to handle adjusted clock
   *
   * This class stores a offset time with current system clock when
   * settime(), and gettime() returns adjusted clock by the offset.
   *
   * @endif
   */
  class AdjustedClock
    : public IClock
  {
  public:
    AdjustedClock();
    virtual ~AdjustedClock();
    virtual coil::TimeValue gettime() const;
    virtual bool settime(coil::TimeValue clocktime);
  private:
    coil::TimeValue m_offset;
    mutable coil::Mutex m_offsetMutex;
  };

  /*!
   * @if jp
   * @class �O���[�o���ȃN���b�N�Ǘ��N���X�B
   *
   * ���̃N���X�̓O���[�o���ɃN���b�N�I�u�W�F�N�g��񋟂���V���O���g��
   * �N���X�ł���BgetClocK(�N���b�N��) �ɂ�� IClock �^�̃N���b�N�I�u
   * �W�F�N�g��Ԃ��B���p�\�ȃN���b�N�� "system", "logical" �����
   * "adjusted" �̂R��ނł���B
   *
   * @else
   * @brief A global clock management class
   *
   * This class is a singleton class that provides clock objects
   * globally. It provides a IClock object by getClock(<clock
   * type>). As clock types, "system", "logical" and "adjusted" are
   * available.
   *
   * @endif
   */
  class ClockManager
    : public coil::Singleton<ClockManager>
  {
  public:
    IClock& getClock(std::string clocktype);
  private:
    SystemClock   m_systemClock;
    LogicalClock  m_logicalClock;
    AdjustedClock m_adjustedClock;
  };
}; // namespace coil
#endif // COIL_CLOCKMANAGER_H
