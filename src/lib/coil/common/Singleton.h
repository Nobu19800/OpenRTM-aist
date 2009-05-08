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
   * @class Singleton ���饹�ƥ�ץ졼��
   *
   * ���Υƥ�ץ졼�Ȥϡ�Ǥ�դΥ��饹�� Singleton �ˤ���ƥ�ץ졼�ȤǤ��롣
   * �ʲ��Τ褦�ˤ��ƻ��Ѥ��롣
   *
   * class A { // };
   * typedef coil::Singleton<A> A_;
   *
   * Ǥ�դξ���
   *
   * A& a(A_:instance()); // a �� A ��ͣ��Υ��󥹥��󥹤�����
   *
   * ��������A���ΤΥ��󥹥ȥ饯���ϻ��ѤǤ���Τǡ�Ʊ��Υ������ǡ�
   *
   * A* a = new A();
   *
   * �Τ褦�ˤ��뤳�Ȥ�Ǥ��뤿�ᡢ��դ�ɬ�פǤ��롣
   * �оݤȤ��륯�饹�� new ���뤳�Ȥ�ػߤ��뤿��ˤϡ��ʲ��Τ褦�ˡ�
   * �оݥ��饹�� Singelton ��Ѿ� (CRTP) �� friend �������ɬ�פ����롣
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
   * �������뤳�Ȥǡ�
   *
   * A* a = new A(); // �϶ػߤ����
   * A& a(A::instance()); // ��ͣ��Υ��󥹥��󥹤�����ͣ�����ˡ
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
// for Windows DLL export
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define DLL_EXPORT __declspec(dllexport)
#   define DLL_IMPORT __declspec(dllimport)
#   ifndef LIBRARY_EXPORTS
#      define SINGLETON_INSTANCE
#   endif
#else 
#   define DLL_EXPORT
#   define DLL_IMPORT
#endif /* Windows */

#ifdef LIBRARY_EXPORTS
#   define SINGLETON_EXPORT DLL_EXPORT
#else
#   define SINGLETON_EXPORT DLL_IMPORT
#endif

  template <class SingletonClass>
  class SINGLETON_EXPORT Singleton
  {
  public:
    typedef SingletonClass* SingletonClassPtr;
#ifdef SINGLETON_INSTANCE
    static SingletonClass& instance();
#else
    static SingletonClass& instance()
    {

      // DLC pattern
      if (!m_instance)
      {
        coil::Guard<coil::Mutex> guard(m_mutex);
	if (!m_instance)
	  {
	    m_instance = new SingletonClass();
	  }
      }
      return *m_instance;
    }
#endif
  protected:
    Singleton(){};
    ~Singleton(){};
    Singleton(const Singleton& x);
    Singleton& operator=(const Singleton& x);

  protected:
    static coil::Mutex m_mutex;
    static SingletonClass* m_instance;
  };

  template <class SingletonClass>
  typename Singleton<SingletonClass>::SingletonClassPtr
  Singleton<SingletonClass>::m_instance;

  template <class SingletonClass>
  typename coil::Mutex Singleton<SingletonClass>::m_mutex;
}; // namepsace coil

#endif // COIL_SINGLETON_H
