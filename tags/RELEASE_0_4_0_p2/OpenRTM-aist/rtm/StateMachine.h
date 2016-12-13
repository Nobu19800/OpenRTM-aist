// -*- C++ -*-
/*!
 * @file StateMachine.h
 * @brief State machine template class
 * @date $Date: 2007-07-20 16:08:57 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: StateMachine.h,v 1.3.2.1 2007-07-20 16:08:57 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/26 15:33:39  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.2  2007/01/09 15:26:53  n-ando
 * Now StateMachine does not need NOP function.
 * All null function pointer is checked and skipped.
 *
 * Revision 1.1  2006/10/26 08:55:53  n-ando
 * The first commitment.
 *
 *
 */

#ifndef StateMachine_h
#define StateMachine_h

#include <rtm/RTC.h>

#include <ace/Guard_T.h>
#include <ace/Thread_Mutex.h>

template <class State>
struct StateHolder
{
  State curr;
  State prev;
  State next;
};

/*!
 * @if jp
 *
 * @class StateMachine
 *
 * @brief ���֥ޥ��󥯥饹
 *
 * StateMachine ���饹�Ͼ��֥ޥ����¸����륯�饹�Ǥ��롣
 *
 * ��: ActiveObject�Ͼ��֥ޥ������ĥ����ƥ��֥��֥������ȤǤ���Ȥ��롣
 * ���֤�3���� INACTIVE, ACTIVE, ERROR ���ꡢ�ƾ��֤Ǥ�Entry��Exitư���
 * ����������Ȥ���ȡ��ʲ��Τ褦�˼¸�����롣
 * <pre>
 * class ActiveObject 
 * {  
 * public: 
 *   enum MyState { INACTIVE, ACTIVE, ERROR }; 
 *   typedef States<MyState> MyStates; 
 *  
 *   ActiveObject() 
 *     : m_sm(3) 
 *   { 
 *     m_sm.setNOP(&ActiveObject::nullAction); 
 *     m_sm.setListener(this); 
 *  
 *     m_sm.setExitAction(NACTIVE, &ActiveObject::inactiveExit); 
 *       : 
 *     m_sm.setPostDoAction(ERROR, &ActiveObject::errorPostDo); 
 *     m_sm.setTransitionAction(&ActiveObject:tratransitionnsition); 
 *   }; 
 *  
 *   bool nullAction(MyStates st) {}; 
 *   bool inactiveExit(MyStates st) {}; 
 *     : 
 *   bool errorPostDo(MyStates st) {}; 
 *   bool transition(MyStates st) {}; 
 *  
 * private: 
 *   StateMachine<MyState, bool, ActiveObject> m_sm; 
 * }; 
 * </pre>
 * ���֤�������������饹�ϰʲ��ξ����������褦�˼������ʤ���Фʤ�ʤ���
 * <ol>
 * <li> enum �Ǿ��֤����
 * <li> StateMachine �Υƥ�ץ졼�Ȱ����ϡ�<br>
 *   <���֤η�(MyState), ���������ؿ��������(bool), �������֥������Ȥη�>
 * <li> StateMachine �Υ��󥹥ȥ饯�������Ͼ��֤ο�
 * <li> �ʲ��Υ��������ؿ���(Return _function_name_(States)) �δؿ��Ȥ�������
 * <ol>
 *  <li> ���⤷�ʤ��ؿ���ɬ���������setNOP ��Ϳ���ʤ���Фʤ�ʤ�
 *  <li> �ƾ������, set(Entry|PreDo|Do|PostDo|Exit)Action �ǥ�������������
 *  <li> �������ܻ��Υ��������� setTransitionAction() �����ꡣ
 * </ol>
 * <li> ���ܻ��Υ��������ϡ�Ϳ����줿���߾��֡������֡������֤򸵤ˡ�
 *   �桼�����������ʤ���Фʤ�ʤ���
 * <li> ���֤��ѹ��� goTo() �ǡ����֤Υ����å��� isIn(state) �ǹԤ���
 * <li> goTo()�ϼ����֤���Ū�˥��åȤ���ؿ��Ǥ��ꡢ���ܤβ��ݤϡ�
 *   �桼�������߾��֤������Ƚ�Ǥ�����å���������ʤ���Фʤ�ʤ���
 * </ol>
 *
 * ���Υ��饹�ϡ���Ĥξ��֤��Ф��ơ�
 * <ul>
 * <li> Entry action
 * <li> PreDo action
 * <li> Do action
 * <li> PostDo action
 * <li> Exit action
 * </ul>
 * 5�ĤΥ��������������뤳�Ȥ��Ǥ��롣
 * Transition action �Ϥ�������ִ����ܤǸƤӽФ���륢�������ǡ�
 * ���ο����񤤤ϥ桼����������ʤ���Фʤ�ʤ���
 * 
 * ���Υ��饹�ϰʲ��Τ褦�ʥ����ߥ󥰤ǳƥ�������󤬼¹Ԥ���롣
 *
 * <ul>
 * <li> ���֤��ѹ�����(A->B)���֤����ܤ����� <br>
 * (A:Exit)->|(���ֹ���:A->B)->(B:Entry)->(B:PreDo)->(B:Do)->(B:PostDo)
 *
 * <li> ���֤��ѹ����줺��B���֤�ݻ������� (|�ϥ��ƥåפζ��ڤ��ɽ��)<br>
 * (B(n-1):PostDo)->|(B(n):PreDo)->(B(n):Do)->(B(n):PostDo)->|(B(n+1):PreDo)<br>
 * PreDo, Do, PostDo �������֤��¹Ԥ���롣
 *
 * <li> �������ܤ����� <br>
 * (B(n-1):PostDo)->(B(n-1):Exit)->|(B(n):Entry)->(B(n):PreDo) <br>
 * ��ö Exit ���ƤФ줿�塢Entry ���¹Ԥ��졢�ʹߤ������Ʊ��ư��򤹤롣
 * </ul>
 * @else
 *
 * @brief
 *
 * @endif
 */
template <class State, class Result,
	  class Listener,
	  class States = StateHolder<State>, 
	  class Callback = Result (Listener::*)(const States& states)
	  >
class StateMachine
{
public:
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  StateMachine(int num_of_state)
    : m_num(num_of_state),
      m_entry (new Callback[m_num]),
      m_predo (new Callback[m_num]),
      m_do    (new Callback[m_num]),
      m_postdo(new Callback[m_num]),
      m_exit  (new Callback[m_num])
  {
    setNullFunc(m_entry,  NULL);
    setNullFunc(m_do,     NULL);
    setNullFunc(m_exit,   NULL);
    setNullFunc(m_predo,  NULL);
    setNullFunc(m_postdo, NULL);
    m_transit = NULL;
  };


  /*!
   * @if jp
   * @brief NOP�ؿ�����Ͽ����
   * @else
   * @brief Set NOP function
   * @endif
   */
  void setNOP(Callback call_back)
  {
    setNullFunc(m_entry,  call_back);
    setNullFunc(m_do,     call_back);
    setNullFunc(m_exit,   call_back);
    setNullFunc(m_predo,  call_back);
    setNullFunc(m_postdo, call_back);
    m_transit = call_back;
  }


  /*!
   * @if jp
   * @brief Listener ���֥������Ȥ���Ͽ����
   * @else
   * @brief Set Listener Object
   * @endif
   */
  void setListener(Listener* listener)
  {
    m_listener = listener;
  }


  /*!
   * @if jp
   * @brief Entry action �ؿ�����Ͽ����
   * @else
   * @brief Set Entry action function
   * @endif
   */
  bool setEntryAction(State state, Callback call_back)
  {
    m_entry[state] = call_back;
    return true;
  }


  /*!
   * @if jp
   * @brief PreDo action �ؿ�����Ͽ����
   * @else
   * @brief Set PreDo action function
   * @endif
   */
  bool setPreDoAction(State state, Callback call_back)
  {
    m_predo[state] = call_back;
    return true;
  }


  /*!
   * @if jp
   * @brief Do action �ؿ�����Ͽ����
   * @else
   * @brief Set Do action function
   * @endif
   */
  bool setDoAction(State state, Callback call_back)
  {
    m_do[state] = call_back;
    return true;
    
  }


  /*!
   * @if jp
   * @brief Post action �ؿ�����Ͽ����
   * @else
   * @brief Set Post action function
   * @endif
   */
  bool setPostDoAction(State state, Callback call_back)
  {
    m_postdo[state] = call_back;
    return true;
  }


  /*!
   * @if jp
   * @brief Exit action �ؿ�����Ͽ����
   * @else
   * @brief Set Exit action function
   * @endif
   */
  bool setExitAction(State state, Callback call_back)
  {
    m_exit[state] = call_back;
    return true;
  }


  /*!
   * @if jp
   * @brief State transition action �ؿ�����Ͽ����
   * @else
   * @brief Set state transition action function
   * @endif
   */
  bool setTransitionAction(Callback call_back)
  {
    m_transit = call_back;
    return true;
  }


  /*!
   * @if jp
   * @brief ������֤򥻥åȤ���
   * @else
   * @brief Set Exit action function
   * @endif
   */
  void setStartState(States states)
  {
    m_states.curr = states.curr;
    m_states.prev = states.prev;
    m_states.next = states.next;
  }


  /*!
   * @if jp
   * @brief ���֤��������
   * @else
   * @brief Get state machine's status
   * @endif
   */
  States getStates()
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    return m_states;
  }
  
  State getState()
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    return m_states.curr;
  }
  

  /*!
   * @if jp
   * @brief ���߾��֤��ǧ
   * @else
   * @brief Evaluate current status
   * @endif
   */
  bool isIn(State state)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    return m_states.curr == state ? true : false;
  }


  /*!
   * @if jp
   * @brief ���֤��ѹ�
   * @else
   * @brief Change status
   * @endif
   */
  void goTo(State state)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    m_states.next = state;
    if (m_states.curr == state)
      {
	m_selftrans  = true;
      }
  }


  /*!
   * @if jp
   * @brief ��ư�ؿ�
   * @else
   * @brief Worker function
   * @endif
   */
  Result worker()
  {
    Result res = RTC::RTC_OK;
    States state;
    bool selftrans;

    { // lock
      ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
      state = m_states;
      selftrans = m_selftrans;
      m_selftrans = false;
    }

    // Entry ���������
    // ���󤫤���֤��Ѥ�ä�
    // �⤷���ϼ������ܤ��Ԥ�줿�Τ�Entry����������Ԥ�
    if ((state.prev != state.curr) || selftrans)
      {
	// Entry ����������¹�
	if (m_entry[state.curr] != NULL)
	  res = (m_listener->*m_entry[state.curr])(state);
      }

    // ���ζ�֤ǤϾ��֤��ѹ����Τ��ʤ���
    // �����������ѿ� m_states �ϳ��������ѹ�������ǽ�������롣
    // Do ���������Ƚ��ˤϥ������ѿ���Ȥ���

    // Do ���������
    if (state.curr == state.next)
      {
	if (m_predo[state.curr] != NULL)
	  res = (m_listener->*m_predo [state.curr])(state);
	if (m_do[state.curr] != NULL)
	  res = (m_listener->*m_do    [state.curr])(state);
	if (m_postdo[state.curr] != NULL)
	  res = (m_listener->*m_postdo[state.curr])(state);
      }

    // ���ζ�֤Ǥϼ��ξ��֤��ѹ�����Ƥ��뤫�⤷��ʤ���
    // ���֤� m_states.next ��ȿ�Ǥ���Ƥ��롣
    // lock
    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
      // ���֤Υ��ԡ�
      state.next = m_states.next;
      selftrans = m_selftrans;
    }

    // Exit ���������
    if ((state.curr != state.next) || selftrans)
      {
	// Exit action of pre-state
	if (m_exit[state.curr] != NULL)
	  res = (m_listener->*m_exit[state.curr])(state);
	if (m_transit != NULL)
	  res = (m_listener->*m_transit)(state);
      }

    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
      // ���֤򹹿�
      m_states.prev = m_states.curr;
      m_states.curr = m_states.next;
    }

    return res;
  }

protected:
  void setNullFunc(Callback* s, Callback nullfunc)
  {
    for (int i = 0; i < m_num; ++i) s[i] = nullfunc;
  }


  int m_num;
  Listener* m_listener;
  Callback* m_entry;
  Callback* m_predo;
  Callback* m_do;
  Callback* m_postdo;
  Callback* m_exit;
  Callback  m_transit;

  States m_states;
  bool m_selftrans;
  ACE_Thread_Mutex m_mutex;
};

#endif // StateMachine_h
