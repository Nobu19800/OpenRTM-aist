// -*- C++ -*-
/*!
 * @file ComponentActionListener.h
 * @brief component action listener class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
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

#ifndef RTC_CONNECTORLISTENER_H
#define RTC_CONNECTORLISTENER_H

#include <vector>
#include <utility>
#include <rtm/RTC.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/ConnectorBase.h>

namespace RTC
{
  typedef ExecutionContextHandle_t UniqueId;
  /*!
   * @if jp
   * @brief PreComponentActionListener �̃^�C�v
   *
   * - PRE_ON_INITIALIZE:
   * - PRE_ON_FINALIZE:
   * - PRE_ON_STARTUP:
   * - PRE_ON_SHUTDOWN:
   * - PRE_ON_ACTIVATED:
   * - PRE_ON_DEACTIVATED:
   * - PRE_ON_ABORTED:
   * - PRE_ON_ERROR:
   * - PRE_ON_RESET:
   * - PRE_ON_EXECUTE:
   * - PRE_ON_STATE_UPDATE:
   *
   * @else
   * @brief The types of ConnectorDataListener
   * 
   * @endif
   */

  enum PreComponentActionListenerType
    {
      PRE_ON_INITIALIZE,
      PRE_ON_FINALIZE,
      PRE_ON_STARTUP,
      PRE_ON_SHUTDOWN,
      PRE_ON_ACTIVATED,
      PRE_ON_DEACTIVATED,
      PRE_ON_ABORTED,
      PRE_ON_ERROR,
      PRE_ON_RESET,
      PRE_ON_EXECUTE,
      PRE_ON_STATE_UPDATE,
      PRE_COMPONENT_ACTION_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class PreComponentActionListener �N���X
   * @brief PreComponentActionListener �N���X
   *
   * OMG RTC�d�l�Œ�`����Ă���ȉ��̃R���|�[�l���g�A�N�V�����g�ɂ�
   * �āA
   *
   * - on_initialize()
   * - on_finalize()
   * - on_startup()
   * - on_shutdown()
   * - on_activated
   * - on_deactivated()
   * - on_aborted()
   * - on_error()
   * - on_reset()
   * - on_execute()
   * - on_state_update()
   *
   * �e�A�N�V�����ɑΉ����郆�[�U�[�R�[�h���Ă΂�钼�O�̃^�C�~���O
   * �ŃR�[������郊�X�ȃN���X�̊��N���X�B
   *
   * - PRE_ON_INITIALIZE:
   * - PRE_ON_FINALIZE:
   * - PRE_ON_STARTUP:
   * - PRE_ON_SHUTDOWN:
   * - PRE_ON_ACTIVATED:
   * - PRE_ON_DEACTIVATED:
   * - PRE_ON_ABORTED:
   * - PRE_ON_ERROR:
   * - PRE_ON_RESET:
   *
   * @else
   * @class PreComponentActionListener class
   * @brief PreComponentActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class PreComponentActionListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PreComponentActionListenerType �𕶎���ɕϊ�
     *
     * PreComponentActionListenerType �𕶎���ɕϊ�����
     *
     * @param type �ϊ��Ώ� PreComponentActionListenerType
     *
     * @return ������ϊ�����
     *
     * @else
     *
     * @brief Convert PreComponentActionListenerType into the string.
     *
     * Convert PreComponentActionListenerType into the string.
     *
     * @param type The target PreComponentActionListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PreComponentActionListenerType type)
    {
      static const char* typeString[] =
        {
          "PRE_ON_INITIALIZE",
          "PRE_ON_FINALIZE",
          "PRE_ON_STARTUP",
          "PRE_ON_SHUTDOWN",
          "PRE_ON_ACTIVATED",
          "PRE_ON_DEACTIVATED",
          "PRE_ON_ABORTED",
          "PRE_ON_ERROR",
          "PRE_ON_RESET",
          "PRE_ON_EXECUTE",
          "PRE_ON_STATE_UPDATE",
          "PRE_COMPONENT_ACTION_LISTENER_NUM"
        };
      if (type < PRE_COMPONENT_ACTION_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief �f�X�g���N�^
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PreComponentActionListener();

    /*!
     * @if jp
     *
     * @brief ���z�R�[���o�b�N�֐�
     *
     * PreComponentActionListener �̃R�[���o�b�N�֐�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PreComponentActionListener.
     *
     * @endif
     */
    virtual void operator()(UniqueId ec_id) = 0;
  };


  /*!
   * @if jp
   * @brief PostCompoenntActionListener �̃^�C�v
   *
   * - POST_ON_INITIALIZE:
   * - POST_ON_FINALIZE:
   * - POST_ON_STARTUP:
   * - POST_ON_SHUTDOWN:
   * - POST_ON_ACTIVATED:
   * - POST_ON_DEACTIVATED:
   * - POST_ON_ABORTED:
   * - POST_ON_ERROR:
   * - POST_ON_RESET:
   * - POST_ON_EXECUTE:
   * - POST_ON_STATE_UPDATE:
   *
   * @else
   * @brief The types of ConnectorDataListener
   * 
   * @endif
   */
  enum PostComponentActionListenerType
    {
      POST_ON_INITIALIZE,
      POST_ON_FINALIZE,
      POST_ON_STARTUP,
      POST_ON_SHUTDOWN,
      POST_ON_ACTIVATED,
      POST_ON_DEACTIVATED,
      POST_ON_ABORTED,
      POST_ON_ERROR,
      POST_ON_RESET,
      POST_ON_EXECUTE,
      POST_ON_STATE_UPDATE,
      POST_COMPONENT_ACTION_LISTENER_NUM
    };


  /*!
   * @if jp
   * @class PostComponentActionListener �N���X
   * @brief PostComponentActionListener �N���X
   *
   * OMG RTC�d�l�Œ�`����Ă���ȉ��̃R���|�[�l���g�A�N�V�����g�ɂ�
   * �āA
   *
   * - on_initialize()
   * - on_finalize()
   * - on_startup()
   * - on_shutdown()
   * - on_activated
   * - on_deactivated()
   * - on_aborted()
   * - on_error()
   * - on_reset()
   * - on_execute()
   * - on_state_update()
   *
   * �e�A�N�V�����ɑΉ����郆�[�U�[�R�[�h���Ă΂�钼�O�̃^�C�~���O
   * �ŃR�[������郊�X�ȃN���X�̊��N���X�B
   *
   * - POST_ON_INITIALIZE:
   * - POST_ON_FINALIZE:
   * - POST_ON_STARTUP:
   * - POST_ON_SHUTDOWN:
   * - POST_ON_ACTIVATED:
   * - POST_ON_DEACTIVATED:
   * - POST_ON_ABORTED:
   * - POST_ON_ERROR:
   * - POST_ON_RESET:
   *
   * @else
   * @class PostComponentActionListener class
   * @brief PostComponentActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class PostComponentActionListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PostComponentActionListenerType �𕶎���ɕϊ�
     *
     * PostComponentActionListenerType �𕶎���ɕϊ�����
     *
     * @param type �ϊ��Ώ� PostComponentActionListenerType
     *
     * @return ������ϊ�����
     *
     * @else
     *
     * @brief Convert PostComponentActionListenerType into the string.
     *
     * Convert PostComponentActionListenerType into the string.
     *
     * @param type The target PostComponentActionListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PostComponentActionListenerType type)
    {
      static const char* typeString[] =
        {
          "POST_ON_INITIALIZE",
          "POST_ON_FINALIZE",
          "POST_ON_STARTUP",
          "POST_ON_SHUTDOWN",
          "POST_ON_ACTIVATED",
          "POST_ON_DEACTIVATED",
          "POST_ON_ABORTED",
          "POST_ON_ERROR",
          "POST_ON_RESET",
          "POST_ON_EXECUTE",
          "POST_ON_STATE_UPDATE",
          "POST_COMPONENT_ACTION_LISTENER_NUM"
        };
      if (type < POST_COMPONENT_ACTION_LISTENER_NUM)
        {
          return typeString[type];
        }
      return "";
    }

    /*!
     * @if jp
     * @brief �f�X�g���N�^
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PostComponentActionListener();

    /*!
     * @if jp
     *
     * @brief ���z�R�[���o�b�N�֐�
     *
     * PostComponentActionListener �̃R�[���o�b�N�֐�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PostComponentActionListener.
     *
     * @endif
     */
    virtual void operator()(UniqueId ec_id,
                            ReturnCode_t ret) = 0;
  };


  /*!
   * @if jp
   * @class PreComponentActionListenerHolder 
   * @brief PreComponentActionListener �z���_�N���X
   *
   * ������ PreComponentActionListener ��ێ����Ǘ�����N���X�B
   *
   * @else
   * @class PreComponentActionListenerHolder
   * @brief PreComponentActionListener holder class
   *
   * This class manages one ore more instances of PreComponentActionListener class.
   *
   * @endif
   */
  class PreComponentActionListenerHolder
  {
    typedef std::pair<PreComponentActionListener*, bool> Entry;
  public:
    /*!
     * @if jp
     * @brief �R���X�g���N�^
     * @else
     * @brief Constructor
     * @endif
     */
    PreComponentActionListenerHolder();
    
    /*!
     * @if jp
     * @brief �f�X�g���N�^
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PreComponentActionListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief ���X�i�[�̒ǉ�
     *
     * ���X�i�[��ǉ�����B
     *
     * @param listener �ǉ����郊�X�i
     * @param autoclean true:�f�X�g���N�^�ō폜����,
     *                  false:�f�X�g���N�^�ō폜���Ȃ�
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
    void addListener(PreComponentActionListener* listener, bool autoclean);
    
    /*!
     * @if jp
     *
     * @brief ���X�i�[�̍폜
     *
     * ���X�i���폜����B
     *
     * @param listener �폜���郊�X�i
     * @else
     *
     * @brief Remove the listener. 
     *
     * This method removes the listener. 
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(PreComponentActionListener* listener);

    /*!
     * @if jp
     *
     * @brief ���X�i�[�֒ʒm����
     *
     * �o�^����Ă��郊�X�i�̃R�[���o�b�N���\�b�h���Ăяo���B
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
    void notify(UniqueId ec_id);
      
  private:
    std::vector<Entry> m_listeners;
  };


  /*!
   * @if jp
   * @class PostComponentActionListenerHolder
   * @brief PostComponentActionListener �z���_�N���X
   *
   * ������ PostComponentActionListener ��ێ����Ǘ�����N���X�B
   *
   * @else
   * @class PostComponentActionListenerHolder
   * @brief PostComponentActionListener holder class
   *
   * This class manages one ore more instances of
   * PostComponentActionListener class.
   *
   * @endif
   */
  class PostComponentActionListenerHolder
  {
    typedef std::pair<PostComponentActionListener*, bool> Entry;
  public:
    /*!
     * @if jp
     * @brief �R���X�g���N�^
     * @else
     * @brief Constructor
     * @endif
     */
    PostComponentActionListenerHolder();
    /*!
     * @if jp
     * @brief �f�X�g���N�^
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PostComponentActionListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief ���X�i�[�̒ǉ�
     *
     * ���X�i�[��ǉ�����B
     *
     * @param listener �ǉ����郊�X�i
     * @param autoclean true:�f�X�g���N�^�ō폜����,
     *                  false:�f�X�g���N�^�ō폜���Ȃ�
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
    void addListener(PostComponentActionListener* listener, bool autoclean);
    
    /*!
     * @if jp
     *
     * @brief ���X�i�[�̍폜
     *
     * ���X�i���폜����B
     *
     * @param listener �폜���郊�X�i
     * @else
     *
     * @brief Remove the listener. 
     *
     * This method removes the listener. 
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(PostComponentActionListener* listener);
    
    /*!
     * @if jp
     *
     * @brief ���X�i�[�֒ʒm����
     *
     * �o�^����Ă��郊�X�i�̃R�[���o�b�N���\�b�h���Ăяo���B
     *
     * @param info ConnectorInfo
     * @param cdrdata �f�[�^
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
    void notify(UniqueId ec_id, ReturnCode_t ret);
    
  private:
    std::vector<Entry> m_listeners;
  };


  /*!
   * @if jp
   * @class ComponentActionListeners
   * @brief ComponentActionListeners �N���X
   *
   *
   * @else
   * @class ComponentActionListeners
   * @brief ComponentActionListeners class
   *
   *
   * @endif
   */
  class ComponentActionListeners
  {
  public:
    /*!
     * @if jp
     * @brief PreComponentActionListenerType���X�i�z��
     * PreComponentActionListenerType���X�i���i�[
     * @else
     * @brief PreComponentActionListenerType listener array
     * The PreComponentActionListenerType listener is stored. 
     * @endif
     */
    PreComponentActionListenerHolder 
    preaction_[PRE_COMPONENT_ACTION_LISTENER_NUM];
    /*!
     * @if jp
     * @brief PostComponentActionType���X�i�z��
     * PostComponentActionType���X�i���i�[
     * @else
     * @brief PostComponentActionType listener array
     * The PostComponentActionType listener is stored.
     * @endif
     */
    PostComponentActionListenerHolder 
    postaction_[POST_COMPONENT_ACTION_LISTENER_NUM];
  };


}; // namespace RTC

#endif // RTC_CONNECTORLISTENER_H
