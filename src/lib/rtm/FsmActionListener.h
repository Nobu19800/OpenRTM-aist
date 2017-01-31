// -*- C++ -*-
/*!
 * @file FsmActionListener.h
 * @brief component action listener class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2016-2017
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_FSMACTIONLISTENER_H
#define RTC_FSMACTIONLISTENER_H

#include <vector>
#include <utility>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <rtm/RTC.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/ConnectorBase.h>
#include <rtm/idl/ExtendedFsmServiceStub.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * FSM����ݡ��ͥ�Ȥ˴ؤ����ο����񤤤�եå����뤿��Υꥹ����
   * �����ꥹ�ʤˤ��礭��ʬ����ȡ�
   *
   * - FSM���Τ�Τ�ư���եå����뤿��Υꥹ��
   * - FSM�˴ؤ���᥿�ǡ����ѹ�����ư���եå����뤿��Υꥹ��
   *
   * ��2�����ʬ�����롣��������Ԥϡ�FSM�ξ����������Υ�����������
   * �夽�줾���եå����뤿��� PreFsmActionListener ��
   * PostFsmActionListener ����Ĥ����ꡢ��Ԥϡ�FSM��Profile���ѹ���ե�
   * ������ FsmProfileListener �� FSM�ι�¤ (Structure) ���ѹ���եå�
   * ���� FsmStructureListener ����Ĥ�ʬ�����롣�ʾ塢�ʲ���FSM�˴�
   * ����ʲ���4����Υꥹ�ʡ����饹�����󶡤���Ƥ��롣
   *
   * - PreFsmActionListener
   * - PostFsmActionListener
   * - FsmProfileListner
   * - FsmStructureListener
   *
   * @else
   *
   *
   * @endif
   */

  //============================================================
  /*!
   * @if jp
   * @brief PreFsmActionListener �Υ�����
   *
   * PreFsmActionListener �ˤϰʲ��Υեå��ݥ���Ȥ��������Ƥ��롣��
   * ��餬�ƤӽФ���뤫�ɤ����ϡ�FSM�μ����˰�¸���롣
   *
   * - PRE_ON_INIT:          init ľ��
   * - PRE_ON_ENTRY:         entry ľ��
   * - PRE_ON_DO:            do ľ��
   * - PRE_ON_EXIT:          exit ľ��
   * - PRE_ON_STATE_CHANGE:  ��������ľ��
   *
   * @else
   * @brief The types of ConnectorDataListener
   *
   * PreFsmActionListener has the following hook points. If these
   * listeners are actually called or not called are depends on FSM
   * implementations.
   *
   * - PRE_ON_INIT:          just before "init" action
   * - PRE_ON_ENTRY:         just before "entry" action
   * - PRE_ON_DO:            just before "do" action
   * - PRE_ON_EXIT:          just before "exit" action
   * - PRE_ON_STATE_CHANGE:  just before state transition action
   *
   * @endif
   */
  enum PreFsmActionListenerType
    {
      PRE_ON_INIT,
      PRE_ON_ENTRY,
      PRE_ON_DO,
      PRE_ON_EXIT,
      PRE_ON_STATE_CHANGE,
      PRE_FSM_ACTION_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class PreFsmActionListener ���饹
   * @brief PreFsmActionListener ���饹
   *
   * PreFsmActionListener ���饹�ϡ�Fsm�Υ��������˴ؤ��륳����Хå�
   * ��¸�����ꥹ�ʡ����֥������Ȥδ��쥯�饹�Ǥ��롣FSM�Υ��������
   * ��ľ����ư���եå���������硢�ʲ�����Τ褦�ˡ����Υ��饹��Ѿ�
   * ����������Хå����֥������Ȥ��������Ŭ�ڤʥ�����Хå�����ؿ���
   * ��RTObject���Ф��ƥ�����Хå����֥������Ȥ򥻥åȤ���ɬ�פ����롣
   *
   * <pre>
   * class MyListener
   *   : public PreFsmActionListener
   * {
   *   std::string m_name;
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *
   *   virtual void operator()(const char* state_name)
   *   {
   *     std::cout << "Listner name:  " m_name << std::endl;
   *     std::cout << "Current state: " state_name << std::endl;
   *   };
   * };
   * </pre>
   *
   * ���Τ褦�ˤ���������줿�ꥹ�ʥ��饹�ϡ��ʲ��Τ褦��RTObject���Ф�
   * �ơ����åȤ���롣
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     addPreFsmActionListener(PRE_ON_STATE_CHANGE,
   *                             new MyListener("init listener"),
   *                             true);
   *    :
   * </pre>
   *
   * ��1������ "PRE_ON_STATE_CHANGE" �ϡ�������Хå���եå�����ݥ���
   * �ȤǤ��ꡢ�ʲ����ͤ��뤳�Ȥ���ǽ�Ǥ��롣�ʤ������٤ƤΥ�����Х�
   * ���ݥ���Ȥ���������Ƥ���Ȥϸ¤餺������餬�ƤӽФ���뤫�ɤ���
   * �ϡ�FSM�μ����˰�¸���롣
   *
   * - PRE_ON_INIT:          init ľ��
   * - PRE_ON_ENTRY:         entry ľ��
   * - PRE_ON_DO:            do ľ��
   * - PRE_ON_EXIT:          exit ľ��
   * - PRE_ON_STATE_CHANGE:  ��������ľ��
   *
   * ��2�����ϥꥹ�ʥ��֥������ȤΥݥ��󥿤Ǥ��롣��3�����ϥ��֥�������
   * ��ư����ե饰�Ǥ��ꡢtrue �ξ��ϡ�RTObject������˼�ưŪ�˥ꥹ
   * �ʥ��֥������Ȥ��������롣false�ξ��ϡ����֥������Ȥν�ͭ����
   * �ƤӽФ�¦�˻Ĥꡢ����ϸƤӽФ�¦����Ǥ�ǹԤ�ʤ���Фʤ�ʤ���
   * RTObject �Υ饤�ե���������˥�����Хå���ɬ�פʤ�о嵭�Τ褦��
   * �ƤӽФ�������3������ true �Ȥ��Ƥ����Ȥ褤���դˡ�������Хå���
   * �������˱����ƥ��åȤ����ꥢ�󥻥åȤ����ꤹ��ɬ�פ��������
   * false�Ȥ����֤����ꥹ�ʥ��֥������ȤΥݥ��󥿤�����ѿ��ʤɤ���
   * �����Ƥ�����
   * RTObject_impl::addPreFsmActionListener()/removePreFsmActionListener()
   * �ˤ�ꡢ���åȤȥ��󥻥åȤ��������Ȥ��ä��Ȥ������ǽ�Ǥ��롣
   *
   * @else
   * @class PreFsmActionListener class
   * @brief PreFsmActionListener class
   *
   * PreFsmActionListener class is a base class for the listener
   * objects which realize callback to hook FSM related pre-actions.
   * To hook execution just before a FSM action, the callback object
   * should be defined as follows, and set to RTObject through
   * appropriate callback set function.
   *
   * <pre>
   * class MyListener
   *   : public PreFsmActionListener
   * {
   *   std::string m_name;
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *
   *   virtual void operator()(const char* state_name)
   *   {
   *     std::cout << "Listner name:  " m_name << std::endl;
   *     std::cout << "Current state: " state_name << std::endl;
   *   };
   * };
   * </pre>
   *
   * The listener class defined above is set to RTObject as follows.
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     addPreFsmActionListener(PRE_ON_STATE_CHANGE,
   *                             new MyListener("init listener"),
   *                             true);
   *    :
   * </pre>
   *
   * The first argument "PRE_ON_STATE_CHANGE" specifies callback hook
   * point, and the following values are available. Not all the
   * callback points are implemented. It depends on the FSM
   * implementations.
   *
   * - PRE_ON_INIT:          just before "init" action
   * - PRE_ON_ENTRY:         just before "entry" action
   * - PRE_ON_DO:            just before "do" action
   * - PRE_ON_EXIT:          just before "exit" action
   * - PRE_ON_STATE_CHANGE:  just before state transition action
   *
   * The second argument is a pointers to the listener object. The
   * third argument is a flag for automatic object destruction. When
   * "true" is given to the third argument, the given object in second
   * argument is automatically destructed with RTObject. In the "false
   * " case, the ownership of the object is left in the caller side,
   * and then destruction of the object must be done by users'
   * responsibility.
   *
   * It is good for setting "true" as third argument, if the listener
   * object life span is equals to the RTObject's life cycle.  On the
   * otehr hand, if callbacks are required to set/unset depending on
   * its situation, the third argument could be "false".  In that
   * case, listener objects pointers must be stored to member
   * variables, and set/unset of the listener objects shoud be
   * paerformed throguh
   * RTObject_impl::addPreFsmActionListener()/removePreFsmActionListener()
   * functions.
   *
   * @endif
   */
  class PreFsmActionListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PreFsmActionListenerType ��ʸ������Ѵ�
     *
     * PreFsmActionListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� PreFsmActionListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert PreFsmActionListenerType into the string.
     *
     * Convert PreFsmActionListenerType into the string.
     *
     * @param type The target PreFsmActionListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PreFsmActionListenerType type)
    {
      static const char* typeString[] =
        {
          "PRE_ON_INIT",
          "PRE_ON_ENTRY",
          "PRE_ON_DO",
          "PRE_ON_EXIT",
          "PRE_ON_STATE_CHANGE",
          "PRE_FSM_ACTION_LISTENER_NUM"
        };
      if (type < PRE_FSM_ACTION_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PreFsmActionListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��ؿ�
     *
     * PreFsmActionListener �Υ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PreFsmActionListener.
     *
     * @endif
     */
    virtual void operator()(const char*) = 0;
  };


  //============================================================
  /*!
   * @if jp
   * @brief PreFsmActionListener �Υ�����
   *
   * PreFsmActionListener �ˤϰʲ��Υեå��ݥ���Ȥ��������Ƥ��롣��
   * ��餬�ƤӽФ���뤫�ɤ����ϡ�FSM�μ����˰�¸���롣
   *
   * - POST_ON_INIT:          init ľ��
   * - POST_ON_ENTRY:         entry ľ��
   * - POST_ON_DO:            do ľ��
   * - POST_ON_EXIT:          exit ľ��
   * - POST_ON_STATE_CHANGE:  ��������ľ��
   *
   * @else
   * @brief The types of ConnectorDataListener
   *
   * PreFsmActionListener has the following hook points. If these
   * listeners are actually called or not called are depends on FSM
   * implementations.
   *
   * - POST_ON_INIT:          just after "init" action
   * - POST_ON_ENTRY:         just after "entry" action
   * - POST_ON_DO:            just after "do" action
   * - POST_ON_EXIT:          just after "exit" action
   * - POST_ON_STATE_CHANGE:  just after state transition action
   *
   * @endif
   */
  enum PostFsmActionListenerType
    {
      POST_ON_INIT,
      POST_ON_ENTRY,
      POST_ON_DO,
      POST_ON_EXIT,
      POST_ON_STATE_CHANGE,
      POST_FSM_ACTION_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class PostFsmActionListener ���饹
   * @brief PostFsmActionListener ���饹
   *
   * PostFsmActionListener ���饹�ϡ�Fsm�Υ��������˴ؤ��륳����Хå�
   * ��¸�����ꥹ�ʡ����֥������Ȥδ��쥯�饹�Ǥ��롣FSM�Υ��������
   * ��ľ���ư���եå���������硢�ʲ�����Τ褦�ˡ����Υ��饹��Ѿ�
   * ����������Хå����֥������Ȥ��������Ŭ�ڤʥ�����Хå�����ؿ���
   * ��RTObject���Ф��ƥ�����Хå����֥������Ȥ򥻥åȤ���ɬ�פ����롣
   *
   * <pre>
   * class MyListener
   *   : public PostFsmActionListener
   * {
   *   std::string m_name;
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *
   *   virtual void operator()(const char* state_name, ReturnCode_t ret)
   *   {
   *     std::cout << "Listner name:  " m_name << std::endl;
   *     std::cout << "Current state: " state_name << std::endl;
   *   };
   * };
   * </pre>
   *
   * ���Τ褦�ˤ���������줿�ꥹ�ʥ��饹�ϡ��ʲ��Τ褦��RTObject���Ф�
   * �ơ����åȤ���롣
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     addPostFsmActionListener(POST_ON_STATE_CHANGE,
   *                             new MyListener("init listener"),
   *                             true);
   *    :
   * </pre>
   *
   * ��1������ "POST_ON_STATE_CHANGE" �ϡ�������Хå���եå�����ݥ���
   * �ȤǤ��ꡢ�ʲ����ͤ��뤳�Ȥ���ǽ�Ǥ��롣�ʤ������٤ƤΥ�����Х�
   * ���ݥ���Ȥ���������Ƥ���Ȥϸ¤餺������餬�ƤӽФ���뤫�ɤ���
   * �ϡ�FSM�μ����˰�¸���롣
   *
   * - POST_ON_INIT:          init ľ��
   * - POST_ON_ENTRY:         entry ľ��
   * - POST_ON_DO:            do ľ��
   * - POST_ON_EXIT:          exit ľ��
   * - POST_ON_STATE_CHANGE:  ��������ľ��
   *
   * ��2�����ϥꥹ�ʥ��֥������ȤΥݥ��󥿤Ǥ��롣��3�����ϥ��֥�������
   * ��ư����ե饰�Ǥ��ꡢtrue �ξ��ϡ�RTObject������˼�ưŪ�˥ꥹ
   * �ʥ��֥������Ȥ��������롣false�ξ��ϡ����֥������Ȥν�ͭ����
   * �ƤӽФ�¦�˻Ĥꡢ����ϸƤӽФ�¦����Ǥ�ǹԤ�ʤ���Фʤ�ʤ���
   * RTObject �Υ饤�ե���������˥�����Хå���ɬ�פʤ�о嵭�Τ褦��
   * �ƤӽФ�������3������ true �Ȥ��Ƥ����Ȥ褤���դˡ�������Хå���
   * �������˱����ƥ��åȤ����ꥢ�󥻥åȤ����ꤹ��ɬ�פ��������
   * false�Ȥ����֤����ꥹ�ʥ��֥������ȤΥݥ��󥿤�����ѿ��ʤɤ���
   * �����Ƥ�����
   * RTObject_impl::addPostFsmActionListener()/removePostFsmActionListener()
   * �ˤ�ꡢ���åȤȥ��󥻥åȤ��������Ȥ��ä��Ȥ������ǽ�Ǥ��롣
   *
   * @else
   * @class PostFsmActionListener class
   * @brief PostFsmActionListener class
   *
   * PostFsmActionListener class is a base class for the listener
   * objects which realize callback to hook FSM related post-actions.
   * To hook execution just before a FSM action, the callback object
   * should be defined as follows, and set to RTObject through
   * appropriate callback set function.
   *
   * <pre>
   * class MyListener
   *   : public PostFsmActionListener
   * {
   *   std::string m_name;
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *
   *   virtual void operator()(const char* state_name, ReturnCode\t ret)
   *   {
   *     std::cout << "Listner name:  " m_name << std::endl;
   *     std::cout << "Current state: " state_name << std::endl;
   *   };
   * };
   * </pre>
   *
   * The listener class defined above is set to RTObject as follows.
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     addPostFsmActionListener(POST_ON_STATE_CHANGE,
   *                             new MyListener("init listener"),
   *                             true);
   *    :
   * </pre>
   *
   * The first argument "POST_ON_STATE_CHANGE" specifies callback hook
   * point, and the following values are available. Not all the
   * callback points are implemented. It depends on the FSM
   * implementations.
   *
   * - POST_ON_INIT:          just after "init" action
   * - POST_ON_ENTRY:         just after "entry" action
   * - POST_ON_DO:            just after "do" action
   * - POST_ON_EXIT:          just after "exit" action
   * - POST_ON_STATE_CHANGE:  just after state transition action
   *
   * The second argument is a pointers to the listener object. The
   * third argument is a flag for automatic object destruction. When
   * "true" is given to the third argument, the given object in second
   * argument is automatically destructed with RTObject. In the "false
   * " case, the ownership of the object is left in the caller side,
   * and then destruction of the object must be done by users'
   * responsibility.
   *
   * It is good for setting "true" as third argument, if the listener
   * object life span is equals to the RTObject's life cycle.  On the
   * otehr hand, if callbacks are required to set/unset depending on
   * its situation, the third argument could be "false".  In that
   * case, listener objects pointers must be stored to member
   * variables, and set/unset of the listener objects shoud be
   * paerformed throguh
   * RTObject_impl::addPostFsmActionListener()/removePostFsmActionListener()
   * functions.
   *
   * @endif
   */
  class PostFsmActionListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PostFsmActionListenerType ��ʸ������Ѵ�
     *
     * PostFsmActionListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� PostFsmActionListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert PostFsmActionListenerType into the string.
     *
     * Convert PostFsmActionListenerType into the string.
     *
     * @param type The target PostFsmActionListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PostFsmActionListenerType type)
    {
      static const char* typeString[] =
        {
          "POST_ON_INIT",
          "POST_ON_ENTRY",
          "POST_ON_DO",
          "POST_ON_EXIT",
          "POST_ON_STATE_CHANGE",
          "POST_FSM_ACTION_LISTENER_NUM"
        };
      if (type < POST_FSM_ACTION_LISTENER_NUM)
        {
          return typeString[type];
        }
      return "";
    }

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PostFsmActionListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��ؿ�
     *
     * PostFsmActionListener �Υ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PostFsmActionListener.
     *
     * @endif
     */
    virtual void operator()(const char* state,
                            ReturnCode_t ret) = 0;
  };

  //============================================================
  /*!
   * @if jp
   * @brief FsmProfileListener �Υ�����
   *
   * - SET_FSM_PROFILE       : FSM Profile�����
   * - GET_FSM_PROFILE       : FSM Profile������
   * - ADD_FSM_STATE         : FSM��State���ɲä��줿
   * - REMOVE_FSM_STATE      : FSM����State��������줿
   * - ADD_FSM_TRANSITION    : FSM�����ܤ��ɲä��줿
   * - REMOVE_FSM_TRANSITION : FSM�������ܤ�������줿
   * - BIND_FSM_EVENT        : FSM�˥��٥�Ȥ��Х���ɤ��줿
   * - UNBIND_FSM_EVENT      : FSM�˥��٥�Ȥ�����Х���ɤ��줿
   *
   * @else
   * @brief The types of FsmProfileListener
   *
   * - SET_FSM_PROFILE       : Setting FSM Profile
   * - GET_FSM_PROFILE       : Getting FSM Profile
   * - ADD_FSM_STATE         : A State added to the FSM
   * - REMOVE_FSM_STATE      : A State removed from FSM
   * - ADD_FSM_TRANSITION    : A transition added to the FSM
   * - REMOVE_FSM_TRANSITION : A transition removed from FSM
   * - BIND_FSM_EVENT        : An event bounded to the FSM
   * - UNBIND_FSM_EVENT      : An event unbounded to the FSM
   *
   * @endif
   */
  enum FsmProfileListenerType
    {
      SET_FSM_PROFILE,
      GET_FSM_PROFILE,
      ADD_FSM_STATE,
      REMOVE_FSM_STATE,
      ADD_FSM_TRANSITION,
      REMOVE_FSM_TRANSITION,
      BIND_FSM_EVENT,
      UNBIND_FSM_EVENT,
      FSM_PROFILE_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class FsmProfileListener ���饹
   * @brief FsmProfileListener ���饹
   *
   * FsmProfileListener ���饹�ϡ�FSM��Profile�˴�Ϣ�������������Υ���
   * ��Хå���¸�����ꥹ�ʡ����֥������Ȥδ��쥯�饹�Ǥ��롣FSM
   * Profile�Υ���������ư���եå���������硢�ʲ�����Τ褦�ˡ���
   * �Υ��饹��Ѿ�����������Хå����֥������Ȥ��������Ŭ�ڤʥ�����Х�
   * ������ؿ�����RTObject���Ф��ƥ�����Хå����֥������Ȥ򥻥åȤ���
   * ɬ�פ����롣
   *
   * <pre>
   * class MyListener
   *   : public FsmProfileListener
   * {
   *   std::string m_name;
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *
   *   virtual void operator()(const ::RTC::FsmProfile& fsmprof)
   *   {
   *     std::cout << "Listner name:  " m_name << std::endl;
   *   };
   * };
   * </pre>
   *
   * ���Τ褦�ˤ���������줿�ꥹ�ʥ��饹�ϡ��ʲ��Τ褦��RTObject���Ф�
   * �ơ����åȤ���롣
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     addFsmProfileListener(SET_FSM_PROFILE,
   *                           new MyListener("prof listener"),
   *                           true);
   *    :
   * </pre>
   *
   * ��1������ "SET_FSM_PROFILE" �ϡ�������Хå���եå�����ݥ���
   * �ȤǤ��ꡢ�ʲ����ͤ��뤳�Ȥ���ǽ�Ǥ��롣�ʤ������٤ƤΥ�����Х�
   * ���ݥ���Ȥ���������Ƥ���Ȥϸ¤餺������餬�ƤӽФ���뤫�ɤ���
   * �ϡ�FSM�����ӥ��μ����˰�¸���롣
   *
   * - SET_FSM_PROFILE       : FSM Profile�����
   * - GET_FSM_PROFILE       : FSM Profile������
   * - ADD_FSM_STATE         : FSM��State���ɲä��줿
   * - REMOVE_FSM_STATE      : FSM����State��������줿
   * - ADD_FSM_TRANSITION    : FSM�����ܤ��ɲä��줿
   * - REMOVE_FSM_TRANSITION : FSM�������ܤ�������줿
   * - BIND_FSM_EVENT        : FSM�˥��٥�Ȥ��Х���ɤ��줿
   * - UNBIND_FSM_EVENT      : FSM�˥��٥�Ȥ�����Х���ɤ��줿
   *
   * ��2�����ϥꥹ�ʥ��֥������ȤΥݥ��󥿤Ǥ��롣��3�����ϥ��֥�������
   * ��ư����ե饰�Ǥ��ꡢtrue �ξ��ϡ�RTObject������˼�ưŪ�˥ꥹ
   * �ʥ��֥������Ȥ��������롣false�ξ��ϡ����֥������Ȥν�ͭ����
   * �ƤӽФ�¦�˻Ĥꡢ����ϸƤӽФ�¦����Ǥ�ǹԤ�ʤ���Фʤ�ʤ���
   * RTObject �Υ饤�ե���������˥�����Хå���ɬ�פʤ�о嵭�Τ褦��
   * �ƤӽФ�������3������ true �Ȥ��Ƥ����Ȥ褤���դˡ�������Хå���
   * �������˱����ƥ��åȤ����ꥢ�󥻥åȤ����ꤹ��ɬ�פ��������
   * false�Ȥ����֤����ꥹ�ʥ��֥������ȤΥݥ��󥿤�����ѿ��ʤɤ���
   * �����Ƥ�����addFsmProfileListener()/removeFsmProfileListener() ��
   * ��ꡢ���åȤȥ��󥻥åȤ��������Ȥ��ä��Ȥ������ǽ�Ǥ��롣
   *
   * @else
   * @class FsmProfileListener class
   * @brief FsmProfileListener class
   *
   * FsmProfileListener class is a base class for the listener
   * objects which realize callback to hook FSM Profile related actions.
   * To hook execution just before a FSM profile action, the callback object
   * should be defined as follows, and set to RTObject through
   * appropriate callback set function.
   *
   * <pre>
   * class MyListener
   *   : public FsmProfileListener
   * {
   *   std::string m_name;
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *
   *   virtual void operator()(const ::RTC::FsmProfile& fsmprof)
   *   {
   *     std::cout << "Listner name:  " m_name << std::endl;
   *   };
   * };
   * </pre>
   *
   * The listener class defined above is set to RTObject as follows.
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     addFsmProfileListener(SET_FSM_PROFILE,
   *                           new MyListener("prof listener"),
   *                           true);
   *    :
   * </pre>
   *
   * The first argument "SET_FSM_PROFILE" specifies callback hook
   * point, and the following values are available. Not all the
   * callback points are implemented. It depends on the FSM service
   * implementations.
   *
   * - SET_FSM_PROFILE       : Setting FSM Profile
   * - GET_FSM_PROFILE       : Getting FSM Profile
   * - ADD_FSM_STATE         : A State added to the FSM
   * - REMOVE_FSM_STATE      : A State removed from FSM
   * - ADD_FSM_TRANSITION    : A transition added to the FSM
   * - REMOVE_FSM_TRANSITION : A transition removed from FSM
   * - BIND_FSM_EVENT        : An event bounded to the FSM
   * - UNBIND_FSM_EVENT      : An event unbounded to the FSM
   *
   * The second argument is a pointers to the listener object. The
   * third argument is a flag for automatic object destruction. When
   * "true" is given to the third argument, the given object in second
   * argument is automatically destructed with RTObject. In the "false
   * " case, the ownership of the object is left in the caller side,
   * and then destruction of the object must be done by users'
   * responsibility.
   *
   * It is good for setting "true" as third argument, if the listener
   * object life span is equals to the RTObject's life cycle.  On the
   * otehr hand, if callbacks are required to set/unset depending on
   * its situation, the third argument could be "false".  In that
   * case, listener objects pointers must be stored to member
   * variables, and set/unset of the listener objects shoud be
   * paerformed throguh
   * addFsmProfileListener()/removeFsmProfileListener() functions.
   *
   * @endif
   */
  class FsmProfileListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief FsmProfileListenerType ��ʸ������Ѵ�
     *
     * FsmProfileListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� FsmProfileListenerType
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert FsmProfileListenerType into the string.
     *
     * Convert FsmProfileListenerType into the string.
     *
     * @param type The target FsmProfileListenerType for transformation
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(FsmProfileListenerType type)
    {
      static const char* typeString[] =
        {
          "SET_FSM_PROFILE",
          "GET_FSM_PROFILE",
          "ADD_FSM_STATE",
          "REMOVE_FSM_STATE",
          "ADD_FSM_TRANSITION",
          "REMOVE_FSM_TRANSITION",
          "BIND_FSM_EVENT",
          "UNBIND_FSM_EVENT",
          "FSM_PROFILE_LISTENER_NUM"
        };
      if (type < FSM_PROFILE_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~FsmProfileListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��ؿ�
     *
     * FsmProfileListener �Υ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for FsmProfileListener
     *
     * @endif
     */
    virtual void operator()(const ::RTC::FsmProfile& fsmprof) = 0;
  };


  //============================================================
  /*!
   * @if jp
   * @brief FsmStructureListener �Υ�����
   *
   * - SET_FSM_STRUCTURE: FSM��¤������
   * - GET_FSM_STRUCTURE: FSM��¤�μ���
   *
   * @else
   * @brief The types of FsmStructureListener
   *
   * - SET_FSM_STRUCTURE: Setting FSM structure
   * - GET_FSM_STRUCTURE: Getting FSM structure
   *
   * @endif
   */
  enum FsmStructureListenerType
    {
      SET_FSM_STRUCTURE,
      GET_FSM_STRUCTURE,
      FSM_STRUCTURE_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class FsmStructureListener ���饹
   * @brief FsmStructureListener ���饹
   *
   * FsmStructureListener ���饹�ϡ�FSM Structure�Υ��������˴ؤ��륳��
   * ��Хå���¸�����ꥹ�ʡ����֥������Ȥδ��쥯�饹�Ǥ��롣FSM
   * Structure �Υ���������ľ���ư���եå���������硢�ʲ�����Τ�
   * ���ˡ����Υ��饹��Ѿ�����������Хå����֥������Ȥ��������Ŭ�ڤ�
   * ������Хå�����ؿ�����RTObject���Ф��ƥ�����Хå����֥������Ȥ�
   * ���åȤ���ɬ�פ����롣
   *
   * <pre>
   * class MyListener
   *   : public FsmStructureListener
   * {
   *   std::string m_name;
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *   virtual void operator()(::RTC::FsmStructure& pprof)
   *   {
   *     std::cout << "Listner name:  " m_name << std::endl;
   *   };
   * };
   * </pre>
   *
   * ���Τ褦�ˤ���������줿�ꥹ�ʥ��饹�ϡ��ʲ��Τ褦��RTObject���Ф�
   * �ơ����åȤ���롣
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     addFsmStructureListener(SET_FSM_STRUCTURE,
   *                             new MyListener("set structure listener"),
   *                             true);
   *    :
   * </pre>
   *
   * ��1������ "SET_FSM_STRUCTURE" �ϡ�������Хå���եå�����ݥ���
   * �ȤǤ��ꡢ�ʲ����ͤ��뤳�Ȥ���ǽ�Ǥ��롣�ʤ������٤ƤΥ�����Х�
   * ���ݥ���Ȥ���������Ƥ���Ȥϸ¤餺������餬�ƤӽФ���뤫�ɤ���
   * �ϡ�FSM�μ����˰�¸���롣
   *
   * - SET_FSM_STRUCTURE: FSM��¤������
   * - GET_FSM_STRUCTURE: FSM��¤�μ���
   *
   * ��2�����ϥꥹ�ʥ��֥������ȤΥݥ��󥿤Ǥ��롣��3�����ϥ��֥�������
   * ��ư����ե饰�Ǥ��ꡢtrue �ξ��ϡ�RTObject������˼�ưŪ�˥ꥹ
   * �ʥ��֥������Ȥ��������롣false�ξ��ϡ����֥������Ȥν�ͭ����
   * �ƤӽФ�¦�˻Ĥꡢ����ϸƤӽФ�¦����Ǥ�ǹԤ�ʤ���Фʤ�ʤ���
   * RTObject �Υ饤�ե���������˥�����Хå���ɬ�פʤ�о嵭�Τ褦��
   * �ƤӽФ�������3������ true �Ȥ��Ƥ����Ȥ褤���դˡ�������Хå���
   * �������˱����ƥ��åȤ����ꥢ�󥻥åȤ����ꤹ��ɬ�פ��������
   * false�Ȥ����֤����ꥹ�ʥ��֥������ȤΥݥ��󥿤�����ѿ��ʤɤ���
   * �����Ƥ�����
   * RTObject_impl::addPostFsmActionListener()/removePostFsmActionListener()
   * �ˤ�ꡢ���åȤȥ��󥻥åȤ��������Ȥ��ä��Ȥ������ǽ�Ǥ��롣
   *
   * @else
   * @class FsmStructureListener class
   * @brief FsmStructureListener class
   *
   * PostFsmActionListener class is a base class for the listener
   * objects which realize callback to hook FSM structure profile
   * related actions. To hook execution just before a FSM action, the
   * callback object should be defined as follows, and set to RTObject
   * through appropriate callback set function.
   *
   * <pre>
   * class MyListener
   *   : public FsmStructureListener
   * {
   *   std::string m_name;
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *   virtual void operator()(::RTC::FsmStructure& pprof)
   *   {
   *     std::cout << "Listner name:  " m_name << std::endl;
   *   };
   * };
   * </pre>
   *
   * The listener class defined above is set to RTObject as follows.
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     addFsmStructureListener(SET_FSM_STRUCTURE,
   *                             new MyListener("set structure listener"),
   *                             true);
   *    :
   * </pre>
   *
   * The first argument "SET_FSM_STRUCTURE" specifies callback hook
   * point, and the following values are available. Not all the
   * callback points are implemented. It depends on the FSM
   * implementations.
   *
   * - SET_FSM_STRUCTURE: Setting FSM structure
   * - GET_FSM_STRUCTURE: Getting FSM structure
   *
   * The second argument is a pointers to the listener object. The
   * third argument is a flag for automatic object destruction. When
   * "true" is given to the third argument, the given object in second
   * argument is automatically destructed with RTObject. In the "false
   * " case, the ownership of the object is left in the caller side,
   * and then destruction of the object must be done by users'
   * responsibility.
   *
   * It is good for setting "true" as third argument, if the listener
   * object life span is equals to the RTObject's life cycle.  On the
   * otehr hand, if callbacks are required to set/unset depending on
   * its situation, the third argument could be "false".  In that
   * case, listener objects pointers must be stored to member
   * variables, and set/unset of the listener objects shoud be
   * paerformed throguh
   * RTObject_impl::addPostFsmActionListener()/removePostFsmActionListener()
   * functions.
   *
   * @endif
   */
  class FsmStructureListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief FsmStructureListenerType ��ʸ������Ѵ�
     *
     * FsmStructureListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� FsmStructureListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert FsmStructureListenerType into the string.
     *
     * Convert FsmStructureListenerType into the string.
     *
     * @param type The target FsmStructureListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(FsmStructureListenerType type)
    {
      static const char* typeString[] =
        {
          "SET_FSM_STRUCTURE",
          "GET_FSM_STRUCTURE",
          "FSM_STRUCTURE_LISTENER_NUM"
        };
      if (type < FSM_STRUCTURE_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~FsmStructureListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��ؿ�
     *
     * FsmStructureListener �Υ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for FsmStructureListener
     *
     * @endif
     */
    virtual void operator()(::RTC::FsmStructure& pprof) = 0;
  };

  //============================================================
  // Holder classes
  //============================================================
  /*!
   * @if jp
   * @class PreFsmActionListenerHolder
   * @brief PreFsmActionListener �ۥ�����饹
   *
   * ʣ���� PreFsmActionListener ���ݻ����������륯�饹��
   *
   * @else
   * @class PreFsmActionListenerHolder
   * @brief PreFsmActionListener holder class
   *
   * This class manages one ore more instances of
   * PreFsmActionListener class.
   *
   * @endif
   */
  class PreFsmActionListenerHolder
  {
    typedef std::pair<PreFsmActionListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    PreFsmActionListenerHolder();
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PreFsmActionListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ����ɲ�
     *
     * �ꥹ�ʡ����ɲä��롣
     *
     * @param listener �ɲä���ꥹ��
     * @param autoclean true:�ǥ��ȥ饯���Ǻ������,
     *                  false:�ǥ��ȥ饯���Ǻ�����ʤ�
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener. 
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor. 
     * @endif
     */
    void addListener(PreFsmActionListener* listener, bool autoclean);
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ��κ��
     *
     * �ꥹ�ʤ������롣
     *
     * @param listener �������ꥹ��
     * @else
     *
     * @brief Remove the listener. 
     *
     * This method removes the listener. 
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(PreFsmActionListener* listener);

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ������Τ���
     *
     * ��Ͽ����Ƥ���ꥹ�ʤΥ�����Хå��᥽�åɤ�ƤӽФ���
     *
     * @param info ConnectorInfo
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectorInfo
     * @endif
     */
    void notify(const char* state);
      
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  /*!
   * @if jp
   * @class PostFsmActionListenerHolder
   * @brief PostFsmActionListener �ۥ�����饹
   *
   * ʣ���� PostFsmActionListener ���ݻ����������륯�饹��
   *
   * @else
   * @class PostFsmActionListenerHolder
   * @brief PostFsmActionListener holder class
   *
   * This class manages one ore more instances of
   * PostFsmActionListener class.
   *
   * @endif
   */
  class PostFsmActionListenerHolder
  {
    typedef std::pair<PostFsmActionListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    PostFsmActionListenerHolder();
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PostFsmActionListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ����ɲ�
     *
     * �ꥹ�ʡ����ɲä��롣
     *
     * @param listener �ɲä���ꥹ��
     * @param autoclean true:�ǥ��ȥ饯���Ǻ������,
     *                  false:�ǥ��ȥ饯���Ǻ�����ʤ�
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener. 
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor. 
     * @endif
     */
    void addListener(PostFsmActionListener* listener, bool autoclean);
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ��κ��
     *
     * �ꥹ�ʤ������롣
     *
     * @param listener �������ꥹ��
     * @else
     *
     * @brief Remove the listener. 
     *
     * This method removes the listener. 
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(PostFsmActionListener* listener);
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ������Τ���
     *
     * ��Ͽ����Ƥ���ꥹ�ʤΥ�����Хå��᥽�åɤ�ƤӽФ���
     *
     * @param info ConnectorInfo
     * @param cdrdata �ǡ���
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectorInfo
     * @param cdrdata Data
     * @endif
     */
    void notify(const char* state, ReturnCode_t ret);
    
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  //============================================================
  /*!
   * @if jp
   * @class FsmProfileListenerHolder
   * @brief FsmProfileListener �ۥ�����饹
   *
   * ʣ���� FsmProfileListener ���ݻ����������륯�饹��
   *
   * @else
   * @class FsmProfileListenerHolder
   * @brief FsmProfileListener holder class
   *
   * This class manages one ore more instances of
   * FsmProfileListener class.
   *
   * @endif
   */
  class FsmProfileListenerHolder
  {
    typedef std::pair<FsmProfileListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    FsmProfileListenerHolder();
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~FsmProfileListenerHolder();

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ����ɲ�
     *
     * �ꥹ�ʡ����ɲä��롣
     *
     * @param listener �ɲä���ꥹ��
     * @param autoclean true:�ǥ��ȥ饯���Ǻ������,
     *                  false:�ǥ��ȥ饯���Ǻ�����ʤ�
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener.
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor.
     * @endif
     */
    void addListener(FsmProfileListener* listener, bool autoclean);

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ��κ��
     *
     * �ꥹ�ʤ������롣
     *
     * @param listener �������ꥹ��
     * @else
     *
     * @brief Remove the listener.
     *
     * This method removes the listener.
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(FsmProfileListener* listener);

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ������Τ���
     *
     * ��Ͽ����Ƥ���ꥹ�ʤΥ�����Хå��᥽�åɤ�ƤӽФ���
     *
     * @param info ConnectorInfo
     * @param cdrdata �ǡ���
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectorInfo
     * @param cdrdata Data
     * @endif
     */
    void notify(RTC::FsmProfile& profile);

  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };

  /*!
   * @if jp
   * @class FsmStructureListenerHolder
   * @brief FsmStructureListener �ۥ�����饹
   *
   * ʣ���� FsmStructureListener ���ݻ����������륯�饹��
   *
   * @else
   * @class FsmStructureListenerHolder
   * @brief FsmStructureListener holder class
   *
   * This class manages one ore more instances of
   * FsmStructureListener class.
   *
   * @endif
   */
  class FsmStructureListenerHolder
  {
    typedef std::pair<FsmStructureListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    FsmStructureListenerHolder();
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~FsmStructureListenerHolder();

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ����ɲ�
     *
     * �ꥹ�ʡ����ɲä��롣
     *
     * @param listener �ɲä���ꥹ��
     * @param autoclean true:�ǥ��ȥ饯���Ǻ������,
     *                  false:�ǥ��ȥ饯���Ǻ�����ʤ�
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener.
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor.
     * @endif
     */
    void addListener(FsmStructureListener* listener, bool autoclean);

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ��κ��
     *
     * �ꥹ�ʤ������롣
     *
     * @param listener �������ꥹ��
     * @else
     *
     * @brief Remove the listener.
     *
     * This method removes the listener.
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(FsmStructureListener* listener);

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ������Τ���
     *
     * ��Ͽ����Ƥ���ꥹ�ʤΥ�����Хå��᥽�åɤ�ƤӽФ���
     *
     * @param info ConnectorInfo
     * @param cdrdata �ǡ���
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectorInfo
     * @param cdrdata Data
     * @endif
     */
    void notify(RTC::FsmStructure& structure);

  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };

  //============================================================
  /*!
   * @if jp
   * @class FsmActionListeners
   * @brief FsmActionListeners ���饹
   *
   *
   * @else
   * @class FsmActionListeners
   * @brief FsmActionListeners class
   *
   *
   * @endif
   */
  class FsmActionListeners
  {
  public:
    /*!
     * @if jp
     * @brief PreFsmActionListenerType�ꥹ������
     * PreFsmActionListenerType�ꥹ�ʤ��Ǽ
     * @else
     * @brief PreFsmActionListenerType listener array
     * The PreFsmActionListenerType listener is stored. 
     * @endif
     */
    PreFsmActionListenerHolder 
    preaction_[PRE_FSM_ACTION_LISTENER_NUM];
    /*!
     * @if jp
     * @brief PostFsmActionType�ꥹ������
     * PostFsmActionType�ꥹ�ʤ��Ǽ
     * @else
     * @brief PostFsmActionType listener array
     * The PostFsmActionType listener is stored.
     * @endif
     */
    PostFsmActionListenerHolder 
    postaction_[POST_FSM_ACTION_LISTENER_NUM];
    /*!
     * @if jp
     * @brief FsmProfileType�ꥹ������
     * FsmProfileType�ꥹ�ʤ��Ǽ
     * @else
     * @brief FsmProfileType listener array
     * The FsmProfileType listener is stored.
     * @endif
     */
    FsmProfileListenerHolder
    profile_[FSM_PROFILE_LISTENER_NUM];
    /*!
     * @if jp
     * @brief FsmStructureType�ꥹ������
     * FsmStructureType�ꥹ�ʤ��Ǽ
     * @else
     * @brief FsmStructureType listener array
     * The FsmStructureType listener is stored.
     * @endif
     */
    FsmStructureListenerHolder
    structure_[FSM_STRUCTURE_LISTENER_NUM];
  };

}; // namespace RTC

#endif // RTC_FSMACTIONLISTENER_H
