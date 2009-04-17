// -*- C++ -*-
/*!
 * @file Singleton.h
 * @brief Singleton template class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_SINGLETON_H
#define COIL_SINGLETON_H

#include <coil/Mutex.h>
#include <coil/Guard.h>

namespace coil
{
  /*!
   * @if jp
   * @class Singleton �N���X�e���v���[�g
   *
   * ���̃e���v���[�g�́A�C�ӂ̃N���X�� Singleton �ɂ���e���v���[�g�ł���B
   * �ȉ��̂悤�ɂ��Ďg�p����B
   *
   * class A { // };
   * typedef coil::Singleton<A> A_;
   *
   * �C�ӂ̏ꏊ��
   *
   * A& a(A_:instance()); // a �� A �̗B��̃C���X�^���X������
   *
   * �������AA���̂̃R���X�g���N�^�͎g�p�ł���̂ŁA����̃\�[�X�ŁA
   *
   * A* a = new A();
   *
   * �̂悤�ɂ��邱�Ƃ��ł��邽�߁A���ӂ��K�v�ł���B
   * �ΏۂƂ���N���X�� new ���邱�Ƃ��֎~���邽�߂ɂ́A�ȉ��̂悤�ɁA
   * �ΏۃN���X�� Singelton ���p�� (CRTP) �� friend �錾����K�v������B
   *
   * class A
   *  : public coil::Singleton<A>
   * {
   * public:
   * private:
   *   A(){}
   * 
   *   friend class coil::Singelton<A>;
   * };
   *
   * �������邱�ƂŁA
   *
   * A* a = new A(); // �͋֎~�����
   * A& a(A::instance()); // ���B��̃C���X�^���X�𓾂�B��̕��@
   *
   * @else
   * @class Singleton class template
   *
   * This class template makes any classed into Singleton classes.
   * Usage is as follows.
   *
   * class A { // };
   * typedef coil::Singleton<A> A_;
   *
   * In the any places,
   * A& a(A_:instance()); // a has singular instance of A
   *
   * Since the constructor of A is still public, however, user can
   * create other instance of A as follows.
   *
   * A* a = new A();
   *
   * If you want to prohibit user from creating new instance, please
   * inherit Singleton class (CRTP) and declare it as a friend class
   * in the target class.
   *
   * class A
   *  : public coil::Singleton<A>
   * {
   * public:
   * private:
   *   A(){}
   * 
   *   friend class coil::Singelton<A>;
   * };
   *
   * A* a = new A(); // compile error
   * A& a(A::instance()); // This is the only method to get unique instance
   *
   * @endif
   */
  template <class SingletonClass>
  class Singleton
  {
  public:
    static SingletonClass& instance()
    {
      static coil::Mutex mutex;
      static SingletonClass* instance_(0);

      // DLC pattern
      if (!instance_)
      {
        coil::Guard<coil::Mutex> guard(mutex);
	if (!instance_)
	  {
	    instance_ = new SingletonClass();
	  }
      }
      return *instance_;
    }

  protected:
    Singleton(){};
    ~Singleton(){};
    Singleton(const Singleton& x);
    Singleton& operator=(const Singleton& x);
  };
}; // namepsace coil

#endif // COIL_SINGLETON_H
