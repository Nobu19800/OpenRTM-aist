// -*- C++ -*-
/*!
 * @file Async.h
 * @brief Asynchronous function invocation helper class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_ASYNC_H
#define COIL_ASYNC_H

#include <coil/Task.h>
#include <coil/Guard.h>
#include <iostream>

namespace coil
{
  class Async
    : public coil::Task
  {
  public:
    Async() {}
    virtual ~Async(){}
    virtual void invoke() = 0;
    virtual bool finished() = 0;
  };
  
  template <typename Object, typename Func>
  class Async_t
    : public Async
  {
  public:
    Async_t(Object* obj, Func func, bool auto_delete = false)
      : m_obj(obj), m_func(func), m_finished(false), m_autodelete(auto_delete)
    {
    }
    virtual ~Async_t()
    {
    }
    
    virtual int svc()
    {
      m_func(m_obj);
      {
        Guard<Mutex> guard(m_mutex);
        m_finished = true;
      }
      
      return 0;
    }
    virtual void finalize()
    {
      Task::finalize();
      if (m_autodelete) delete this;
    }
    virtual void invoke()
    {
      activate();
    }
    virtual bool finished()
    {
      Guard<Mutex> guard(m_mutex);
      return m_finished;
    }
  private:
    Object* m_obj;
    Func m_func;
    bool m_finished;
    const bool m_autodelete;
    Mutex m_mutex;
  };
  
  template <typename Object, typename Func>
  class Async_ref_t
    : public Async
  {
  public:
    Async_ref_t(Object* obj, Func& func, bool auto_delete = false)
      : m_obj(obj), m_func(func), m_finished(false), m_autodelete(auto_delete)
    {
    }
    virtual ~Async_ref_t()
    {
    }
    
    virtual int svc()
    {
      m_func(m_obj);
      m_finished = true;
      return 0;
    }
    virtual void invoke()
    {
      activate();
    }
    virtual bool finished()
    {
      return m_finished;
    }
    virtual void finalize()
    {
      Task::finalize();
      if (m_autodelete) delete this;
    }
  private:
    Object* m_obj;
    Func& m_func;
    bool m_finished;
    bool m_autodelete;
    
  };
  
  /*!
   * @if jp
   * @brief ��Ʊ�����С��ؿ��ƤӽФ��إ�ѡ��ؿ�
   *
   * ���С��ؿ�����Ʊ���˸Ƥ֤���Υإ�ѡ��ؿ�
   * ��
   *
   *  class A
   *  {
   *  public:
   *    // ���֤Τ�����ؿ�
   *    void hoge() {
   *      for (int i(0); i < 5; ++i) {
   *        std::cout << "hoge" << std::endl;
   *        sleep(1);
   *      }
   *    }
   *    // ���֤Τ�����ؿ�
   *    void munya(const char* msg) {
   *      for (int i(0); i < 10; ++i) {
   *        std::cout << "message is: " << msg << std::endl;
   *        sleep(1);
   *      }
   *    }
   *    int add_one(int val) {
   *      return val + 1;
   *    }
   *  };
   * �����ͤʥ��饹�Υ��֥������Ȥ��Ф��ơ�
   *
   *  A a;
   *  Async* invoker0(AsyncInvoker(&a,
   *                               std::mem_fun(&A::hoge)));
   *  Async* invoker1(AsyncInvoker(&a,
   *                               std::bind2nd(std::mem_fun(&A::munya),
   *                                            "�ۤ�")));
   *  invoker0->invoke(); // ���������
   *  invoker1->invoke(); // ���������
   *
   *  delete invoker0; // ɬ��������뤳��
   *  delete invoker1; // ɬ��������뤳��
   *
   * �Τ褦����Ʊ���θƤӽФ����Ǥ��롣
   * �ƤӽФ�������ͤ�������������ϡ������δؿ����֥������Ȥ��Ѱդ��롣
   *
   *  class add_one_functor
   *  {
   *    int m_val, m_ret;
   *  public:
   *    add_one_functor(int val) : m_val(val), m_ret(0) {}
   *    void operaotr(A* obj) {
   *      m_ret = obj->add_one(m_val);
   *    }
   *    int get_ret() {
   *      return m_ret;
   *    }
   *  };
   *
   * �嵭�δؿ����֥������ȤΥ��󥹥��󥹤�����������Υݥ��󥿤��Ϥ���
   *
   *  add_one_functor aof(100);
   *  Async* invoker2(AsyncInvoker(&a, &aof));
   *  invoker2->invoke();
   *  invoker2->wait();
   *  std::cout << "result: " << aof.get_ret() << std::endl;
   *  delete invoker2;
   *
   * �̾AsyncInvoker ���֤����֥������Ȥ�����Ū�˺�����ʤ����
   * �ʤ�ʤ������軰������ true ���Ϥ����Ȥǡ���Ʊ���¹Ԥ���λ�����Ʊ����
   * ��ưŪ�˥��󥹥��󥹤��������롣
   *
   * // invoker3 �Ϻ�� (delete invoker3) ���ƤϤ����ʤ�
   * Async* invoker3(AsyncInvoker(&a, std::mem_fun(&A::hoge), true));
   *
   * // ���󥹥���������Ʊ���˼¹Ԥ��뤳�Ȥ�Ǥ��롣
   * AsyncInvoker(&a, std::mem_fun(&A::hoge))->invoke();
   *
   * @else
   *
   * @endif
   */
  template <typename Object, typename Func>
  inline Async_t<Object, Func>*
  AsyncInvoker(Object* obj, Func func, bool auto_delete = false)
  {
    return new Async_t<Object, Func>(obj, func, auto_delete);
  }

  template <typename Object, typename Func>
  inline Async_ref_t<Object, Func>*
  AsyncInvoker(Object* obj, Func* func, bool auto_delete = false)
  {
    return new Async_ref_t<Object, Func>(obj, *func, auto_delete);
  }


};

#endif // COIL_ASYNC_H
