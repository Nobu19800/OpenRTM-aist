// -*- C++ -*-
/*!
 * @file ComponentObserverConsumer.h
 * @brief Component observer SDO service consumer implementation
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2016
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */


#ifndef RTC_COMPONENTOBSERVERCONSUMER_H
#define RTC_COMPONENTOBSERVERCONSUMER_H

#include <coil/Mutex.h>
#include <coil/Factory.h>
#include <coil/stringutil.h>
#include <rtm/SdoServiceConsumerBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/ComponentActionListener.h>
#include <rtm/FsmActionListener.h>
#include <rtm/idl/SDOPackageStub.h>
#include "ComponentObserverStub.h"

namespace RTC
{

  /*!
   * @if jp
   * @class ComponentObserverConsumer ���饹
   * @brief ComponentObserver �⥸�塼��
   *
   * ����ݡ��ͥ�ȤγƼ���֤�ComponentObserver�����ӥ����Ф��ƥ�����
   * �Хå����뤿��Υ��饹���ġ�����������ݡ��ͥ�Ȥξ����Ѳ����Τꤿ
   * ������ƥ��ƥ��������ӥ��ץ�Х�������������ݡ��ͥ�Ȥ��Ф��ƥ���
   * �Ȥ���ȡ��б������ܥ��󥷥塼�ޤ������å����졢����ݡ��ͥ�Ȥξ�
   * ���Ѳ��˱����ơ�update_status() ���ڥ졼������STATUS_KIND �ȥҥ�
   * �Ȥ�����˸ƤӽФ����ܵ�ǽ�ϡ�OMG �� FSM4RTC����
   * (formal/16-04-01) 7.2.4.2 ComponentObserver Interface �˵��Ҥ����
   * ���롣
   *
   * STATUS_KIND �ˤϰʲ��μ��ब���롣
   *
   * - COMPONENT_PROFILE: ����ݡ��ͥ�ȤΥץ�ե���������Ѳ�
   * - RTC_STATUS       : ����ݡ��ͥ�Ȥξ��� (Init, Alive) ���Ѳ�
   * - EC_STATUS        : EC�ξ��� (Inavtive, Active, Error) ���Ѳ�
   * - PORT_PROFILE     : �ݡ��ȤΥץ�ե����뤬�Ѳ�
   * - CONFIGURATION    : ����ե�����졼������Ѳ�
   * - RTC_HEARTBEAT    : RTC����¸��ǧ�Υϡ��ȥӡ���
   * - EC_HEARTBEAT     : EC����¸��ǧ�Υϡ��ȥӡ���
   * - FSM_PROFILE      : FSM�Υץ�ե����뤬�Ѳ�
   * - FSM_STATUS       : FSM�ξ��֤��Ѳ�
   * - FSM_STRUCTURE    : FSM�ι�¤���Ѳ�
   * - USER_DEFINED     : �桼�����
   *
   * \subsection COMPONENT_PROFILE COMPONENT_PROFILE
   * ����ݡ��ͥ�ȤΥץ�ե���������Ѳ������ݤˤ��Υ���̾(enum��)��
   * ��1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���롣(̤����)
   *
   * \subsection RTC_STATUS RTC_STATUS
   *
   * ����ݡ��ͥ�Ȥξ��� (Init, Alive) ���Ѳ������ݤˤ��Υ���̾
   * (enum��)����1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���
   * �롣��̩�ˤ�EC�ξ��֤Ǥ��뤬��Inavtive, Active, Error, Finalize ��
   * 4�Ĥξ��֤��Ѳ��������Ȥ��Τ��뤳�Ȥ��Ǥ��롣�ʲ��ξ����Ѳ����ˡ�
   * ���줾��ҥ�ȤȤ��ưʲ���ʸ����ȤȤ�˥�����Хå�����롣
   *
   * - onActivated �ƤӽФ�������:   ACTIVE: <EC id>
   * - onDeactivated �ƤӽФ�������: INACTIVE: <EC id>
   * - onReset �ƤӽФ�������:       INACTIVE: <EC id>
   * - onAborting �ƤӽФ�������:    ERROR: <EC id>
   * - onFinalize �ƤӽФ�������:    FINALIZE: <EC id>
   *
   * \subsection EC_STATUS EC_STATUS
   *
   * EC�ξ��� (Inavtive, Active, Error) ���Ѳ������ݤˤ��Υ���̾(enum��)��
   * ��1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���롣
   *
   * \subsection PORT_PROFILE PORT_PROFILE
   * �ݡ��ȤΥץ�ե����뤬�Ѳ������ݤˤ��Υ���̾(enum��)��
   * ��1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���롣
   *
   * \subsection CONFIGURATION CONFIGURATION
   * ����ե�����졼������Ѳ������ݤˤ��Υ���̾(enum��)��
   * ��1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���롣
   *
   * \subsection RTC_HEARTBEAT RTC_HEARTBEAT
   * RTC����¸��ǧ�Υϡ��ȥӡ��ɤ����ݤˤ��Υ���̾(enum��)��
   * ��1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���롣
   *
   * \subsection EC_HEARTBEAT EC_HEARTBEAT
   * EC����¸��ǧ�Υϡ��ȥӡ��Ȥ����ݤˤ��Υ���̾(enum��)��
   * ��1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���롣
   *
   * \subsection FSM_PROFILE FSM_PROFILE
   * FSM�Υץ�ե����뤬�Ѳ������ݤˤ��Υ���̾(enum��)��
   * ��1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���롣
   *
   * \subsection FSM_STATUS FSM_STATUS
   * FSM�ξ��֤��Ѳ������ݤˤ��Υ���̾(enum��)��
   * ��1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���롣
   *
   * \subsection FSM_STRUCTURE FSM_STRUCTURE
   * FSM�ι�¤���Ѳ������ݤˤ��Υ���̾(enum��)��
   * ��1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���롣
   *
   * \subsection USER_DEFINED USER_DEFINED
   * �桼����������ݤˤ��Υ���̾(enum��)��
   * ��1�����ˤ��� update_status() ���ڥ졼����󤬸ƤӽФ���롣
   *
   *
   *
   * @else
   * @endif
   */
  class ComponentObserverConsumer
    : public SdoServiceConsumerBase
  {
  public:
    /*!
     * @if jp
     * @brief ctor of ComponentObserverConsumer
     * @else
     * @brief ctor of ComponentObserverConsumer
     * @endif
     */
    ComponentObserverConsumer();

    /*!
     * @if jp
     * @brief dtor
     * @else
     * @brief dtor
     * @endif
     */
    virtual ~ComponentObserverConsumer();

    /*!
     * @if jp
     * @brief �����
     * @else
     * @brief Initialization
     * @endif
     */
    virtual bool init(RTObject_impl& rtobj,
                      const SDOPackage::ServiceProfile& profile);

    /*!
     * @if jp
     * @brief �ƽ����
     * @else
     * @brief Re-initialization
     * @endif
     */
    virtual bool reinit(const SDOPackage::ServiceProfile& profile);

    /*!
     * @if jp
     * @brief ServiceProfile ���������
     * @else
     * @brief getting ServiceProfile
     * @endif
     */
    virtual const SDOPackage::ServiceProfile& getProfile() const;
    
    /*!
     * @if jp
     * @brief ��λ����
     * @else
     * @brief Finalization
     * @endif
     */
    virtual void finalize();

  protected:
    /*!
     * @if jp
     * @brief ��⡼�ȥ��֥������ȥ�����
     * @else
     * @brief Calling remote object
     * @endif
     */
    inline void updateStatus(RTC::StatusKind statuskind, const char* msg)
    {
      try
        {
          m_observer->update_status(statuskind, msg);
        }
      catch (...)
        {
          m_rtobj->removeSdoServiceConsumer(m_profile.id);
        }
    }

    /*!
     * @if jp
     * @brief Kind��ʸ������Ѵ�����
     * @else
     * @brief Converting kind to string
     * @endif
     */
    inline const char* toString(RTC::StatusKind kind)
    {
      static const char* kinds[] = 
        {
          "COMPONENT_PROFILE",
          "RTC_STATUS",
          "EC_STATUS",
          "PORT_PROFILE",
          "CONFIGURATION",
          "RTC_HEARTBEAT"
          "EC_HEARTBEAT",
          "FSM_PROFILE",
          "FSM_STATUS",
          "FSM_STRUCTURE",
          "USER_DEFINED"
        };
      return (size_t)kind < sizeof(kind)/sizeof(char*) ? kinds[kind] : "";
    }

    /*!
     * @if jp
     * @brief RTObject�ؤΥꥹ����³����
     * @else
     * @brief Connectiong listeners to RTObject
     * @endif
     */
    void setListeners(coil::Properties& prop);

    /*!
     * @if jp
     * @brief �ꥹ����³�����ǥ����å��󥰽���
     * @else
     * @brief Switching listeners connecting/disconnecting
     * @endif
     */
    void switchListeners(bool& next, bool& pre,
                         void (ComponentObserverConsumer::*setfunc)(), 
                         void (ComponentObserverConsumer::*unsetfunc)());

    //============================================================
    // Heartbeat related functions
    /*!
     * @if jp
     * @brief �ϡ��ȥӡ��Ȥ򥪥֥����Ф�������
     * @else
     * @brief Sending a heartbeart signal to observer
     * @endif
     */
    void rtcHeartbeat();

    /*!
     * @if jp
     * @brief �ϡ��ȥӡ��Ȥ����ꤹ��
     * @else
     * @brief Setting heartbeat
     * @endif
     */
    void setRTCHeartbeat(coil::Properties& prop);

    /*!
     * @if jp
     * @brief �ϡ��ȥӡ��Ȥ�������
     * @else
     * @brief Unsetting heartbeat
     * @endif
     */
    void unsetRTCHeartbeat();

    /*!
     * @if jp
     * @brief �ϡ��ȥӡ��Ȥ򥪥֥����Ф�������
     * @else
     * @brief Sending a heartbeart signal to observer
     * @endif
     */
    void ecHeartbeat();

    /*!
     * @if jp
     * @brief �ϡ��ȥӡ��Ȥ����ꤹ��
     * @else
     * @brief Setting heartbeat
     * @endif
     */
    void setECHeartbeat(coil::Properties& prop);

    /*!
     * @if jp
     * @brief �ϡ��ȥӡ��Ȥ�������
     * @else
     * @brief Unsetting heartbeat
     * @endif
     */
    void unsetECHeartbeat();

    //============================================================
    // Component status related functions
    /*!
     * @if jp
     * @brief RTC�����Ѳ��ꥹ�ʤ��������
     * @else
     * @brief Setting RTC status listeners
     * @endif
     */
    void setComponentStatusListeners();

    /*!
     * @if jp
     * @brief RTC�����Ѳ��ꥹ�ʤβ������
     * @else
     * @brief Unsetting RTC status listeners
     * @endif
     */
    void unsetComponentStatusListeners();

    //============================================================
    // FSM status related functions
    /*!
     * @if jp
     * @brief FSM�����Ѳ��ꥹ�ʤ��������
     * @else
     * @brief Setting FSM status listeners
     * @endif
     */
    void setFSMStatusListeners();

    /*!
     * @if jp
     * @brief FSM�����Ѳ��ꥹ�ʤβ������
     * @else
     * @brief Unsetting FSM status listeners
     * @endif
     */
    void unsetFSMStatusListeners();

    //============================================================
    // Port profile related functions
    /*!
     * @if jp
     * @brief Port�ץ�ե������Ѳ��ꥹ�ʤ��������
     * @else
     * @brief Setting port profile listener
     * @endif
     */
    void setPortProfileListeners();

    /*!
     * @if jp
     * @brief Port�ץ�ե������Ѳ��ꥹ�ʤβ������
     * @else
     * @brief Unsetting port profile listener
     * @endif
     */
    void unsetPortProfileListeners();


    //============================================================
    // EC profile related functions
    /*!
     * @if jp
     * @brief EC�ξ����Ѳ��ꥹ�ʤ�����
     * @else
     * @brief Setting EC status listener
     * @endif
     */
    void setExecutionContextListeners();

    /*!
     * @if jp
     * @brief EC�ξ����Ѳ��ꥹ�ʤβ��
     * @else
     * @brief Unsetting EC status listener
     * @endif
     */
    void unsetExecutionContextListeners();


    //============================================================
    // ComponentProfile related functions
    /*!
     * @if jp
     * @brief ComponentProfile�����Ѳ��ꥹ�ʤ�����
     * @else
     * @brief Setting ComponentProfile listener
     * @endif
     */
    void setComponentProfileListeners();

    /*!
     * @if jp
     * @brief ComponentProfile�����Ѳ��ꥹ�ʤβ��
     * @else
     * @brief Unsetting ComponentProfile listener
     * @endif
     */
    void unsetComponentProfileListeners();

    //============================================================
    // FsmProfile related functions
    /*!
     * @if jp
     * @brief FsmProfile�����Ѳ��ꥹ�ʤ�����
     * @else
     * @brief Setting FsmProfile listener
     * @endif
     */
    void setFSMProfileListeners();

    /*!
     * @if jp
     * @brief FsmProfile�����Ѳ��ꥹ�ʤβ��
     * @else
     * @brief Unsetting FsmProfile listener
     * @endif
     */
    void unsetFSMProfileListeners();

    //============================================================
    // FsmStructure related functions
    /*!
     * @if jp
     * @brief FsmStructure�����Ѳ��ꥹ�ʤ�����
     * @else
     * @brief Setting FsmStructure listener
     * @endif
     */
    void setFSMStructureListeners();

    /*!
     * @if jp
     * @brief FsmStructure�����Ѳ��ꥹ�ʤβ��
     * @else
     * @brief Unsetting FsmStructure listener
     * @endif
     */
    void unsetFSMStructureListeners();

    //============================================================
    // Configuration related functions

    /*!
     * @if jp
     * @brief Configuration�����Ѳ��ꥹ�ʤ�����
     * @else
     * @brief Setting Configuration listener
     * @endif
     */
    void setConfigurationListeners();

    /*!
     * @if jp
     * @brief Configuration�����Ѳ��ꥹ�ʤβ��
     * @else
     * @brief Unsetting Configurationlistener
     * @endif
     */
    void unsetConfigurationListeners();

  private:
    /*!
     * @if jp
     * @brief PostComponentActionListener class
     * @else
     * @brief PostComponentActionListener class
     * @endif
     */
    class CompStatMsg
    {
    public:
      CompStatMsg(ComponentObserverConsumer& coc)
        : activatedListener(NULL), deactivatedListener(NULL),
          resetListener(NULL), abortingListener(NULL),
          finalizeListener(NULL), m_coc(coc) {}
      void onGeneric(const char* msgprefix, UniqueId ec_id, ReturnCode_t ret)
      {
        if (ret == RTC::RTC_OK)
          {
            std::string msg(msgprefix);
            msg += coil::otos(ec_id);
            m_coc.updateStatus(RTC::RTC_STATUS, msg.c_str());
          }
      }
      void onActivated(UniqueId ec_id, ReturnCode_t ret)
      {
        onGeneric("ACTIVE:", ec_id, ret);
      }
      void onDeactivated(UniqueId ec_id, ReturnCode_t ret)
      {
        onGeneric("INACTIVE:", ec_id, ret);
      }
      void onReset(UniqueId ec_id, ReturnCode_t ret)
      {
        onGeneric("INACTIVE:", ec_id, ret);
      }
      void onAborting(UniqueId ec_id, ReturnCode_t ret)
      {
        onGeneric("ERROR:", ec_id, ret);
      }
      void onFinalize(UniqueId ec_id, ReturnCode_t ret)
      {
        onGeneric("FINALIZE:", ec_id, ret);
      }

      PostComponentActionListener* activatedListener;
      PostComponentActionListener* deactivatedListener;
      PostComponentActionListener* resetListener;
      PostComponentActionListener* abortingListener;
      PostComponentActionListener* finalizeListener;
    private:
      ComponentObserverConsumer& m_coc;
    };

    /*!
     * @if jp
     * @brief PortActionListener
     * @else
     * @brief PortActionListener
     * @endif
     */
    class PortAction
    {
    public:
      PortAction(ComponentObserverConsumer& coc)
        : portAddListener(NULL), portRemoveListener(NULL),
          portConnectListener(NULL), portDisconnectListener(NULL),
          m_coc(coc) {}
      void onGeneric(const char* _msg, const char* portname)
      {
        std::string msg(_msg);
        msg += portname;
        m_coc.updateStatus(RTC::PORT_PROFILE, msg.c_str());
      }
      void onAddPort(const ::RTC::PortProfile& pprof)
      {
        onGeneric("ADD:", static_cast<const char*>(pprof.name));
      }
      void onRemovePort(const ::RTC::PortProfile& pprof)
      {
        onGeneric("REMOVE:", static_cast<const char*>(pprof.name));
      }
      void onConnect(const char* portname,
                     ::RTC::ConnectorProfile& pprof, ReturnCode_t ret)
      {
        if (ret == RTC::RTC_OK)
          {
            onGeneric("CONNECT:", portname);
          }
      }
      void onDisconnect(const char* portname,
                        ::RTC::ConnectorProfile& pprof, ReturnCode_t ret)
      {
        if (ret == RTC::RTC_OK)
          {
            onGeneric("DISCONNECT:", portname);
          }
      }

      PortActionListener* portAddListener;
      PortActionListener* portRemoveListener;
      PortConnectRetListener* portConnectListener;
      PortConnectRetListener* portDisconnectListener;

    private:
      ComponentObserverConsumer& m_coc;
    };

    /*!
     * @if jp
     * @brief ExecutionContextActionListener
     * @else
     * @brief ExecutionContextActionListener
     * @endif
     */
    class ECAction
    {
    public:
      ECAction(ComponentObserverConsumer& coc)
        : ecAttached(NULL), ecDetached(NULL), ecRatechanged(NULL),
          ecStartup(NULL), ecShutdown(NULL),
          m_coc(coc) {}
      void onGeneric(const char* _msg, UniqueId ec_id)
      {
        std::string msg(_msg + coil::otos(ec_id));
        m_coc.updateStatus(RTC::EC_STATUS, msg.c_str());
      }
      void onAttached(UniqueId ec_id)
      {
        onGeneric("ATTACHED:", ec_id);
      }
      void onDetached(UniqueId ec_id)
      {
        onGeneric("DETACHED:", ec_id);
      }
      void onRateChanged(UniqueId ec_id, ReturnCode_t ret)
      {
        if (ret == RTC::RTC_OK)
          {
            onGeneric("RATE_CHANGED:", ec_id);
          }
      }
      void onStartup(UniqueId ec_id, ReturnCode_t ret)
      {
        if (ret == RTC::RTC_OK)
          {
            onGeneric("STARTUP:", ec_id);
          }
      }
      void onShutdown(UniqueId ec_id, ReturnCode_t ret)
      {
        if (ret == RTC::RTC_OK)
          {
            onGeneric("SHUTDOWN:", ec_id);
          }
      }
      ExecutionContextActionListener* ecAttached;
      ExecutionContextActionListener* ecDetached;
      PostComponentActionListener* ecRatechanged;
      PostComponentActionListener* ecStartup;
      PostComponentActionListener* ecShutdown;
    private:
      ComponentObserverConsumer& m_coc;
    };

    /*!
     * @if jp
     * @brief ConfigActionListener
     * @else
     * @brief ConfigActionListener
     * @endif
     */
    class ConfigAction
    {
    public:
      ConfigAction(ComponentObserverConsumer& coc)
        : updateConfigParamListener(NULL), setConfigSetListener(NULL),
          addConfigSetListener(NULL), updateConfigSetListener(NULL),
          removeConfigSetListener(NULL), activateConfigSetListener(NULL),
          m_coc(coc) {}
      void updateConfigParam(const char* configsetname,
                             const char* configparamname)
      {
        std::string msg("UPDATE_CONFIG_PARAM: ");
        msg += configsetname;
        msg += ".";
        msg += configparamname;
        m_coc.updateStatus(RTC::CONFIGURATION, msg.c_str());
      }
      void setConfigSet(const coil::Properties& config_set)
      {
        std::string msg("SET_CONFIG_SET: ");
        msg += config_set.getName();
        m_coc.updateStatus(RTC::CONFIGURATION, msg.c_str());
      }
      void addConfigSet(const coil::Properties& config_set)
      {
        std::string msg("ADD_CONFIG_SET: ");
        msg += config_set.getName();
        m_coc.updateStatus(RTC::CONFIGURATION, msg.c_str());
      }
      void updateConfigSet(const char* config_set_name)
      {
        std::string msg("UPDATE_CONFIG_SET: ");
        msg += config_set_name;
        m_coc.updateStatus(RTC::CONFIGURATION, msg.c_str());
      }
      void removeConfigSet(const char* config_set_name)
      {
        std::string msg("REMOVE_CONFIG_SET: ");
        msg += config_set_name;
        m_coc.updateStatus(RTC::CONFIGURATION, msg.c_str());
      }
      void activateConfigSet(const char* config_set_name)
      {
        std::string msg("ACTIVATE_CONFIG_SET: ");
        msg += config_set_name;
        m_coc.updateStatus(RTC::CONFIGURATION, msg.c_str());
      }
      // Listener object's pointer holder
      ConfigurationParamListener*   updateConfigParamListener;
      ConfigurationSetListener*     setConfigSetListener;
      ConfigurationSetListener*     addConfigSetListener;
      ConfigurationSetNameListener* updateConfigSetListener;
      ConfigurationSetNameListener* removeConfigSetListener;
      ConfigurationSetNameListener* activateConfigSetListener;

    private:
      ComponentObserverConsumer& m_coc;
    };

    /*!
     * @if jp
     * @brief ConfigActionListener
     * @else
     * @brief ConfigActionListener
     * @endif
     */
    class FSMAction
    {
    public:
      FSMAction(ComponentObserverConsumer& coc)
        : m_coc(coc) {}
      // Action callback functions here
      void updateFsmStatus(const char* state)
      {
        std::cout << "ComponentObserver::updateFsmStatus(" << state << ")" << std::endl; 
        m_coc.updateStatus(RTC::FSM_STATUS, state);
      }

      void preInit(const char* state)
      {
        std::string msg(state); msg += " PRE_ON_INIT";
        m_coc.updateStatus(RTC::FSM_STATUS, msg.c_str());
      }
      void preEntry(const char* state)
      {
        std::string msg(state); msg += " PRE_ONENTRY";
        m_coc.updateStatus(RTC::FSM_STATUS, msg.c_str());
      }
      void preDo(const char* state)
      {
        std::string msg(state); msg += " PRE_ON_DO";
        m_coc.updateStatus(RTC::FSM_STATUS, msg.c_str());
      }
      void preExit(const char* state)
      {
        std::string msg(state); msg += " PRE_ON_EXIT";
        m_coc.updateStatus(RTC::FSM_STATUS, msg.c_str());
      }
      void preStateChange(const char* state)
      {
        std::string msg(state); msg += " PRE_ON_STATE_CHANGE";
        m_coc.updateStatus(RTC::FSM_STATUS, msg.c_str());
      }

      void postInit(const char* state, ReturnCode_t ret)
      {
        std::string msg(state); msg += " POST_ON_INIT";
        m_coc.updateStatus(RTC::FSM_STATUS, msg.c_str());
      }
      void postEntry(const char* state, ReturnCode_t ret)
      {
        std::string msg(state); msg += " POST_ONENTRY";
        m_coc.updateStatus(RTC::FSM_STATUS, msg.c_str());
      }
      void postDo(const char* state, ReturnCode_t ret)
      {
        std::string msg(state); msg += " POST_ON_DO";
        m_coc.updateStatus(RTC::FSM_STATUS, msg.c_str());
      }
      void postExit(const char* state, ReturnCode_t ret)
      {
        std::string msg(state); msg += " POST_ON_EXIT";
        m_coc.updateStatus(RTC::FSM_STATUS, msg.c_str());
      }
      void postStateChange(const char* state, ReturnCode_t ret)
      {
        std::string msg(state); msg += " POST_ON_STATE_CHNAGE";
        m_coc.updateStatus(RTC::FSM_STATUS, msg.c_str());
      }

      // Listener object's pointer holder
      PreFsmActionListener* preOnFsmInitListener;
      PreFsmActionListener* preOnFsmEntryListener;
      PreFsmActionListener* preOnFsmDoListener;
      PreFsmActionListener* preOnFsmExitListener;
      PreFsmActionListener* preOnFsmStateChangeListener;
      
      PostFsmActionListener* postOnFsmInitListener;
      PostFsmActionListener* postOnFsmEntryListener;
      PostFsmActionListener* postOnFsmDoListener;
      PostFsmActionListener* postOnFsmExitListener;
      PostFsmActionListener* postOnFsmStateChangeListener;

    private:
      ComponentObserverConsumer& m_coc;
    };



    RTC::RTObject_impl* m_rtobj;
    SDOPackage::ServiceProfile m_profile;
    CorbaConsumer<RTC::ComponentObserver> m_observer;

    bool m_observed[RTC::STATUS_KIND_NUM];

    CompStatMsg m_compstat;
    PortAction m_portaction;
    ECAction m_ecaction;
    ConfigAction m_configMsg;
    FSMAction m_fsmaction;

    coil::TimeValue m_rtcInterval;
    bool m_rtcHeartbeat;
    ListenerId m_rtcHblistenerid;
    coil::TimeValue m_ecInterval;
    bool m_ecHeartbeat;
    ListenerId m_ecHblistenerid;

    // ���Υ����ޡ��Ϥ����쥰���Х�ʥ����ޤˤ���������
    coil::Timer m_timer;

  };

}; // namespace RTC

extern "C"
{
  DLL_EXPORT void ComponentObserverConsumerInit();
};

#endif // RTC_COMPONENTOBSERVERCONSUMER_H


