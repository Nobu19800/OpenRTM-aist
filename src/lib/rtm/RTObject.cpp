// -*- C++ -*-
/*!
 * @file RTObject.cpp
 * @brief RT component base class
 * @date $Date: 2008-01-14 07:57:15 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <assert.h>
#include <rtm/RTObject.h>
#include <rtm/SdoConfiguration.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/Manager.h>
#include <coil/stringutil.h>
#include <iostream>
#include <typeinfo>

namespace RTC
{
  /*!
   * @if jp
   * @brief RTコンポーネントのデフォルトプロファイル
   * @else
   * @brief RT-Component default profile
   * @endif
   */
  static const char* default_conf[] =
    {
      "implementation_id", "",
      "type_name",         "",
      "description",       "",
      "version",           "",
      "vendor",            "",
      "category",          "",
      "activity_type",     "",
      "max_instance",      "",
      "language",          "",
      "lang_type",         "",
      "conf",              "",
      ""
    };
  
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  RTObject_impl::RTObject_impl(Manager* manager)
    : m_pManager(manager),
      m_pORB(CORBA::ORB::_duplicate(manager->getORB())),
      m_pPOA(PortableServer::POA::_duplicate(manager->getPOA())),
      m_portAdmin(manager->getORB(), manager->getPOA()),
      m_created(true), m_exiting(false),
      m_properties(default_conf), m_configsets(m_properties.getNode("conf")),
      m_sdoservice(*this),
      m_readAll(false),m_writeAll(false),
      m_readAllCompletion(false),m_writeAllCompletion(false)
  {
    m_objref = this->_this();
    m_pSdoConfigImpl = new SDOPackage::Configuration_impl(m_configsets,
                                                          m_sdoservice);
    m_pSdoConfig = SDOPackage::Configuration::
      _duplicate(m_pSdoConfigImpl->getObjRef());
  }
  
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  RTObject_impl::RTObject_impl(CORBA::ORB_ptr orb,
			       PortableServer::POA_ptr poa)
    : m_pManager(NULL),
      m_pORB(CORBA::ORB::_duplicate(orb)),
      m_pPOA(PortableServer::POA::_duplicate(poa)),
      m_portAdmin(orb, poa),
      m_created(true), m_exiting(false),
      m_properties(default_conf), m_configsets(m_properties.getNode("conf")),
      m_sdoservice(*this),
      m_readAll(false),m_writeAll(false),
      m_readAllCompletion(false),m_writeAllCompletion(false)
  {
    m_objref = this->_this();
    m_pSdoConfigImpl = new SDOPackage::Configuration_impl(m_configsets,
                                                          m_sdoservice);
    m_pSdoConfig = SDOPackage::Configuration::
      _duplicate(m_pSdoConfigImpl->getObjRef());
  }
  
  /*!
   * @if jp
   * @brief 仮想デストラクタ
   * @else
   * @brief Virtual destructor
   * @endif
   */
  RTObject_impl::~RTObject_impl()
  {
    RTC_TRACE(("~RTObject_impl()"));
    m_pSdoConfigImpl->_remove_ref();
  }
  
  //============================================================
  // Overridden functions
  //============================================================
  /*!
   * @if jp
   * @brief 初期化処理用コールバック関数
   * @else
   * @brief Callback function to initialize
   * @endif
   */
  // The initialize action (on CREATED->ALIVE transition)
  // former rtc_init_entry() 
  ReturnCode_t RTObject_impl::onInitialize()
  {
    RTC_TRACE(("onInitialize()"));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 終了処理用コールバック関数
   * @else
   * @brief Callback function to finalize
   * @endif
   */
  // The finalize action (on ALIVE->END transition)
  // former rtc_exiting_entry()
  ReturnCode_t RTObject_impl::onFinalize()
  {
    RTC_TRACE(("onFinalize()"));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 開始処理用コールバック関数
   * @else
   * @brief Callback function for startup action
   * @endif
   */
  // The startup action when ExecutionContext startup
  // former rtc_starting_entry()
  ReturnCode_t RTObject_impl::onStartup(RTC::UniqueId ec_id)
  {
    RTC_TRACE(("onStartup(%d)", ec_id));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 停止処理用コールバック関数
   * @else
   * @brief Callback function for shutdown action
   * @endif
   */
  // The shutdown action when ExecutionContext stop
  // former rtc_stopping_entry()
  ReturnCode_t RTObject_impl::onShutdown(RTC::UniqueId ec_id)
  {
    RTC_TRACE(("onShutdown(%d)", ec_id));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 活性化処理用コールバック関数
   * @else
   * @brief Callback function to activate
   * @endif
   */
  // The activated action (Active state entry action)
  // former rtc_active_entry()
  ReturnCode_t RTObject_impl::onActivated(RTC::UniqueId ec_id)
  {
    RTC_TRACE(("onActivated(%d)", ec_id));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 非活性化処理用コールバック関数
   * @else
   * @brief Callback function to deactivate
   * @endif
   */
  // The deactivated action (Active state exit action)
  // former rtc_active_exit()
  ReturnCode_t RTObject_impl::onDeactivated(RTC::UniqueId ec_id)
  {
    RTC_TRACE(("onDeactivated(%d)", ec_id));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 周期処理用コールバック関数
   * @else
   * @brief Callback function to execute periodically
   * @endif
   */
  // The execution action that is invoked periodically
  // former rtc_active_do()
  ReturnCode_t RTObject_impl::onExecute(RTC::UniqueId ec_id)
  {
    RTC_PARANOID(("onExecute(%d)", ec_id));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 中断処理用コールバック関数
   * @else
   * @brief Callback function to abort
   * @endif
   */
  // The aborting action when main logic error occurred.
  // former rtc_aborting_entry()
  ReturnCode_t RTObject_impl::onAborting(RTC::UniqueId ec_id)
  {
    RTC_TRACE(("onAborting(%d)", ec_id));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief エラー処理用コールバック関数
   * @else
   * @brief Callback function for error handling
   * @endif
   */
  // The error action in ERROR state
  // former rtc_error_do()
  ReturnCode_t RTObject_impl::onError(RTC::UniqueId ec_id)
  {
    RTC_TRACE(("onError(%d)", ec_id));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief リセット処理用コールバック関数
   * @else
   * @brief Callback function to reset
   * @endif
   */
  // The reset action that is invoked resetting
  // This is same but different the former rtc_init_entry()
  ReturnCode_t RTObject_impl::onReset(RTC::UniqueId ec_id)
  {
    RTC_TRACE(("onReset(%d)", ec_id));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 状態変更処理用コールバック関数
   * @else
   * @brief Callback function to update the state
   * @endif
   */
  // The state update action that is invoked after onExecute() action
  // no corresponding operation exists in OpenRTm-aist-0.2.0
  ReturnCode_t RTObject_impl::onStateUpdate(RTC::UniqueId ec_id)
  {
    RTC_PARANOID(("onStateUpdate(%d)", ec_id));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 動作周期変更通知用コールバック関数
   * @else
   * @brief Callback function to change execution cycle
   * @endif
   */
  // The action that is invoked when execution context's rate is changed
  // no corresponding operation exists in OpenRTm-aist-0.2.0
  ReturnCode_t RTObject_impl::onRateChanged(RTC::UniqueId ec_id)
  {
    RTC_TRACE(("onRatechanged(%d)", ec_id));
    return RTC::RTC_OK;
  }
  
  //============================================================
  // RTC::LightweightRTObject
  //============================================================
  /*!
   * @if jp
   * @brief [CORBA interface] RTCを初期化する
   * @else
   * @brief [CORBA interface] IInitialize the RTC that realizes this interface.
   * @endif
   */
  ReturnCode_t RTObject_impl::initialize()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("initialize()"));
    std::string ec_args;

    ec_args += m_properties["exec_cxt.periodic.type"];
    ec_args += "?";
    ec_args += "rate=" + m_properties["exec_cxt.periodic.rate"];

    RTC::ExecutionContextBase* ec;
    ec = RTC::Manager::instance().createContext(ec_args.c_str());
    if (ec == NULL) return RTC::RTC_ERROR;

    ec->set_rate(atof(m_properties["exec_cxt.periodic.rate"].c_str()));
    m_eclist.push_back(ec);
    ExecutionContextService_var ecv;
    ecv = RTC::ExecutionContextService::_duplicate(ec->getObjRef());
    if (CORBA::is_nil(ecv)) return RTC::RTC_ERROR;

    ec->bindComponent(this);
    // -- entering alive state --
    // at least one EC must be attached
    if (m_ecMine.length() == 0) return RTC::PRECONDITION_NOT_MET;

    ReturnCode_t ret;
    ret = on_initialize();
    if (ret != RTC::RTC_OK) return ret;
    m_created = false;

    for (::CORBA::ULong i(0), len(m_ecMine.length()); i < len; ++i)
      {
        RTC_DEBUG(("EC[%d] starting.", i));
        m_ecMine[i]->start();
      }

    // ret must be RTC_OK
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] RTC を終了する
   * @else
   * @brief [CORBA interface] Finalize the RTC for preparing it for destruction
   * @endif
   */
  ReturnCode_t RTObject_impl::finalize()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("finalize()"));
    if (m_created) return RTC::PRECONDITION_NOT_MET;
    if (!m_exiting) return RTC::PRECONDITION_NOT_MET;
    // Return RTC::PRECONDITION_NOT_MET,
    // When the component is registered in ExecutionContext.
    // m_ecMine.length() != 0 || 
    if(m_ecOther.length() != 0)
    {

        for (CORBA::ULong ic(0), len(m_ecOther.length()); ic < len; ++ic)
          {
            if(! CORBA::is_nil(m_ecOther[ic]))
              {
                return RTC::PRECONDITION_NOT_MET;
              }
          }
        CORBA_SeqUtil::clear(m_ecOther);
    }
    
    ReturnCode_t ret(on_finalize());

    shutdown();
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] RTC がオーナーである ExecutionContext を
   *        停止させ、そのコンテンツと共に終了させる
   * @else
   * @brief [CORBA interface] RTC stops ExecutionContext of RTC's owner
   *        and finalize it with its contents
   * @endif
   */
  ReturnCode_t RTObject_impl::exit()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("exit()"));
    if (m_created) return RTC::PRECONDITION_NOT_MET;

    // deactivate myself on owned EC
    CORBA_SeqUtil::for_each(m_ecMine,
			    deactivate_comps(m_objref));
    // deactivate myself on other EC
    CORBA_SeqUtil::for_each(m_ecOther,
			    deactivate_comps(m_objref));

    // owned EC will be finalised later in finalizeContext().

    // detach myself from other EC
    for (CORBA::ULong ic(0), len(m_ecOther.length()); ic < len; ++ic)
      {
        //        m_ecOther[ic]->stop();
	RTC::LightweightRTObject_var comp(this->_this());
        if (! ::CORBA::is_nil(m_ecOther[ic]))
          {
            m_ecOther[ic]->remove_component(comp.in());
          }
      }
    m_exiting = true;
    ReturnCode_t ret(finalize());

    return ret;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] RTC が Alive 状態であるかどうか確認する。
   * @else
   * @brief [CORBA interface] Confirm whether RTC is the alive state
   * @endif
   */
  CORBA::Boolean RTObject_impl::is_alive(ExecutionContext_ptr exec_context)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("is_alive()"));
    for (::CORBA::ULong i(0), len(m_ecMine.length()); i < len; ++i)
      {
        if (exec_context->_is_equivalent(m_ecMine[i]))
          return true;
      }

    for (::CORBA::ULong i(0), len(m_ecOther.length()); i < len; ++i)
      {
        if (! ::CORBA::is_nil(m_ecOther[i]))
          {
            if (exec_context->_is_equivalent(m_ecOther[i]))
                return true;
          }
      }
    return false;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] ExecutionContextを取得する
   * @else
   * @brief [CORBA interface] Get ExecutionContext
   * @endif
   */
  ExecutionContext_ptr RTObject_impl::get_context(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_context(%d)", ec_id));
    // owned EC
    if (ec_id < ECOTHER_OFFSET)
      {
        if ((::CORBA::ULong)ec_id < m_ecMine.length())
          {
            return ExecutionContext::_duplicate(m_ecMine[ec_id]);
          }
        else
          {
            return ExecutionContext::_nil();
          }
      }

    // participating EC
    ::CORBA::ULong index(ec_id - ECOTHER_OFFSET);

    if (index < m_ecOther.length())
      {
        if (! ::CORBA::is_nil(m_ecOther[index]))
          {
            return ExecutionContext::_duplicate(m_ecOther[index]);
          }
      }

    return ExecutionContext::_nil();
  }
    
  /*!
   * @if jp
   * @brief [CORBA interface] ExecutionContextListを取得する
   * @else
   * @brief [CORBA interface] Get ExecutionContextList
   * @endif
   */
  ExecutionContextList* RTObject_impl::get_owned_contexts()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_owned_context()"));

#ifndef ORB_IS_RTORB
    ExecutionContextList_var execlist;
    execlist = new ExecutionContextList();
    
    CORBA_SeqUtil::for_each(m_ecMine, ec_copy(execlist));
#else // ORB_IS_RTORB
    ExecutionContextList_var execlist;
    execlist = new ExecutionContextList();

    int n = m_ecMine.length();
    for(int i(0), j(0); i < n ; ++i)
      {
        RTC_ExecutionContext ec_mine = m_ecMine.cobj()->_buffer[i];

        if (ec_mine)
          {
            execlist.length(j+1);
            execlist->cobj()->_buffer[j] = CORBA_Object_dup(ec_mine);
            ++j;
          }
      }
#endif // ORB_IS_RTORB 
    return execlist._retn();
  }

  /*!
   * @if jp
   * @brief [CORBA interface] 参加している ExecutionContextList を取得する
   * @else
   * @brief [CORBA interface] Get participating ExecutionContextList.
   * @endif
   */
  ExecutionContextList* RTObject_impl::get_participating_contexts()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_participating_contexts()"));
    ExecutionContextList_var execlist;
    execlist = new ExecutionContextList();
    
    CORBA_SeqUtil::for_each(m_ecOther, ec_copy(execlist));
    
    return execlist._retn();
  }


  /*!
   * @if jp
   * @brief [CORBA interface] ExecutionContext のハンドルを返す
   * @else
   * @brief [CORBA interface] Return a handle of a ExecutionContext
   * @endif
   */
  ExecutionContextHandle_t
  RTObject_impl::get_context_handle(ExecutionContext_ptr cxt)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_context_handle()"));
    CORBA::Long num;
    num = CORBA_SeqUtil::find(m_ecMine, ec_find(cxt));
    if (num != -1)
      { 
        return (ExecutionContextHandle_t)num;
      }
    num = CORBA_SeqUtil::find(m_ecOther, ec_find(cxt));
    if (num != -1)
      { 
        return (ExecutionContextHandle_t)(ECOTHER_OFFSET + num);
      }
    return (ExecutionContextHandle_t)(-1);
  }


  /*!
   * @if jp
   * @brief [CORBA interface] ExecutionContextをattachする
   * @else
   * @brief [CORBA interface] Attach ExecutionContext
   * @endif
   */
  UniqueId RTObject_impl::attach_context(ExecutionContext_ptr exec_context)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("attach_context()"));
    // ID: 0 - (offset-1) : owned ec
    // ID: offset -       : participating ec
    // owned       ec index = ID
    // participate ec index = ID - offset
    ExecutionContextService_var ecs;
    ecs = ExecutionContextService::_narrow(exec_context);
    if (CORBA::is_nil(ecs))
      {
	return -1;
      }
    
    // if m_ecOther has nil element, insert attached ec to there.
    for (::CORBA::ULong i(0), len(m_ecOther.length()); i < len; ++i)
      {
        if (::CORBA::is_nil(m_ecOther[i]))
          {
            m_ecOther[i] = ExecutionContextService::_duplicate(ecs);
            UniqueId ec_id(i + ECOTHER_OFFSET);
            onAttachExecutionContext(ec_id);
            return ec_id;
          }
      }

    // no space in the list, push back ec to the last.
    CORBA_SeqUtil::
      push_back(m_ecOther, ExecutionContextService::_duplicate(ecs));
    
    UniqueId ec_id((m_ecOther.length() - 1) + ECOTHER_OFFSET);
    onAttachExecutionContext(ec_id);
    return ec_id;
  }
  
  UniqueId
  RTObject_impl::bindContext(ExecutionContext_ptr exec_context)
  {
    RTC_TRACE(("bindContext()"));
    // ID: 0 - (offset-1) : owned ec
    // ID: offset -       : participating ec
    // owned       ec index = ID
    // participate ec index = ID - offset
    ExecutionContextService_var ecs;
    ecs = ExecutionContextService::_narrow(exec_context);
    if (CORBA::is_nil(ecs))
      {
	return -1;
      }
    
    // if m_ecMine has nil element, insert attached ec to there.
    for (::CORBA::ULong i(0), len(m_ecMine.length()); i < len; ++i)
      {
        if (::CORBA::is_nil(m_ecMine[i]))
          {
            m_ecMine[i] = ExecutionContextService::_duplicate(ecs);
            onAttachExecutionContext(i);
            return i;
          }
      }

    // no space in the list, push back ec to the last.
    CORBA_SeqUtil::
      push_back(m_ecMine, ExecutionContextService::_duplicate(ecs));
    
    UniqueId ec_id(m_ecMine.length() - 1);
    onDetachExecutionContext(ec_id);
    return ec_id;
  }

  /*!
   * @if jp
   * @brief [CORBA interface] ExecutionContextをdetachする
   * @else
   * @brief [CORBA interface] Detach ExecutionContext
   * @endif
   */
  ReturnCode_t RTObject_impl::detach_context(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("detach_context(%d)", ec_id));
    ::CORBA::ULong len(m_ecOther.length());

    // ID: 0 - (offset-1) : owned ec
    // ID: offset -       : participating ec
    // owned       ec index = ID
    // participate ec index = ID - offset
    if ((CORBA::ULong)ec_id < ECOTHER_OFFSET || 
        (CORBA::ULong)(ec_id - ECOTHER_OFFSET) > len)
      {
	return RTC::BAD_PARAMETER;
      }
    ::CORBA::ULong index(ec_id - ECOTHER_OFFSET);

    if (CORBA::is_nil(m_ecOther[index]))
      {
	return RTC::BAD_PARAMETER;
      }
    
    m_ecOther[index] = ::RTC::ExecutionContextService::_nil();

    return RTC::RTC_OK;
  }
  
  //============================================================
  // RTC::RTObject
  //============================================================
  
  /*!
   * @if jp
   * @brief [RTObject CORBA interface] コンポーネントプロファイルを取得する
   * @else
   * @brief [RTCObject CORBA interface] Get RTC's profile
   * @endif
   */
  ComponentProfile* RTObject_impl::get_component_profile()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_component_profile()"));
    try
      {
	ComponentProfile_var profile
	  = new ComponentProfile();
#ifndef ORB_IS_RTORB
        profile->instance_name = 
          CORBA::string_dup(m_properties["instance_name"].c_str());
        profile->type_name     = 
          CORBA::string_dup(m_properties["type_name"].c_str());
        profile->description   = 
          CORBA::string_dup(m_properties["description"].c_str());
        profile->version       = 
          CORBA::string_dup(m_properties["version"].c_str());
        profile->vendor        = 
          CORBA::string_dup(m_properties["vendor"].c_str());
        profile->category      = 
          CORBA::string_dup(m_properties["category"].c_str());
        profile->port_profiles = m_portAdmin.getPortProfileList();
#else // ORB_IS_RTORB
        profile->instance_name = (char *)m_properties["instance_name"].c_str();
        profile->type_name     = (char *)m_properties["type_name"].c_str();
        profile->description   = (char *)m_properties["description"].c_str();
        profile->version       = (char *)m_properties["version"].c_str();
        profile->vendor        = (char *)m_properties["vendor"].c_str();
        profile->category      = (char *)m_properties["category"].c_str();
        PortProfileList ppl    = m_portAdmin.getPortProfileList();
        profile->port_profiles = ppl._retn();
#endif // ORB_IS_RTORB
	return profile._retn();
      }
    catch (...)
      {
	; // This operation throws no exception.
      }
    assert(false);
    return 0;
  }
  
  /*!
   * @if jp
   * @brief [RTObject CORBA interface] ポートを取得する
   * @else
   * @brief [RTCObject CORBA interface] Get Ports
   * @endif
   */
  PortServiceList* RTObject_impl::get_ports()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_ports()"));
    try
      {
	return m_portAdmin.getPortServiceList();
      }
    catch (...)
      {
	; // This operation throws no exception.
      }
    assert(false);
    return 0;
  }
  
  
  //============================================================
  // RTC::ComponentAction
  //============================================================
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の初期化
   * @else
   * @brief [ComponentAction CORBA interface] Initialize RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_initialize()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("on_initialize()"));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnInitialize(0);
        ret = onInitialize();
        postOnInitialize(0, ret);
        std::string active_set;
        active_set = m_properties.getProperty("configuration.active_config",
                                              "default");
        if (m_configsets.haveConfig(active_set.c_str()))
          {
            m_configsets.update(active_set.c_str());
          }
        else
          {
            m_configsets.update("default");
          }
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の終了
   * @else
   * @brief [ComponentAction CORBA interface] Finalize RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_finalize()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("on_finalize()"));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnFinalize(0);
	ret = onFinalize();
        postOnFinalize(0, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の開始
   * @else
   * @brief [ComponentAction CORBA interface] Startup RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_startup(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("on_startup(%d)", ec_id));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnStartup(ec_id);
	ret = onStartup(ec_id);
        postOnStartup(ec_id, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の停止
   * @else
   * @brief [ComponentAction CORBA interface] Shutdown RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_shutdown(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("on_shutdown(%d)", ec_id));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnShutdown(ec_id);
	ret = onShutdown(ec_id);
        postOnShutdown(ec_id, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の活性化
   * @else
   * @brief [ComponentAction CORBA interface] Activate RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_activated(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("on_activated(%d)", ec_id));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnActivated(ec_id);
	m_configsets.update();
	ret = onActivated(ec_id);
        m_portAdmin.activatePorts();
        postOnActivated(ec_id, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の非活性化
   * @else
   * @brief [ComponentAction CORBA interface] Deactivate RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_deactivated(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("on_deactivated(%d)", ec_id));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnDeactivated(ec_id);
        m_portAdmin.deactivatePorts();
	ret = onDeactivated(ec_id);
        postOnDeactivated(ec_id, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC のエラー状態への遷移
   * @else
   * @brief [ComponentAction interface] Transition to the error state
   * @endif
   */
  ReturnCode_t RTObject_impl::on_aborting(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("on_aborting(%d)", ec_id));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnAborting(ec_id);
	ret = onAborting(ec_id);
        postOnAborting(ec_id, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC のエラー処理
   * @else
   * @brief [ComponentAction CORBA interface] Error Processing of RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_error(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("on_error(%d)", ec_id));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnError(ec_id);
	ret = onError(ec_id);
	m_configsets.update();
        postOnError(ec_id, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC のリセット
   * @else
   * @brief [ComponentAction CORBA interface] Resetting RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_reset(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("on_reset(%d)", ec_id));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnReset(ec_id);
	ret = onReset(ec_id);
        postOnReset(ec_id, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [DataFlowComponentAction CORBA interface] RTC の定常処理(第一周期)
   * @else
   * @brief [DataFlowComponentAction CORBA interface] Primary Periodic 
   *        Operation of RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_execute(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_PARANOID(("on_execute(%d)", ec_id));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnExecute(ec_id);
	if (m_readAll) {readAll(); }
	ret = onExecute(ec_id);
	if (m_writeAll) { writeAll();}
        postOnExecute(ec_id, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [DataFlowComponentAction CORBA interface] RTC の定常処理(第二周期)
   * @else
   * @brief [DataFlowComponentAction CORBA interface] Secondary Periodic 
   *        Operation of RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_state_update(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_PARANOID(("on_state_update(%d)", ec_id));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnStateUpdate(ec_id);
	ret = onStateUpdate(ec_id);
	m_configsets.update();
        postOnStateUpdate(ec_id, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [DataFlowComponentAction CORBA interface] 実行周期変更通知
   * @else
   * @brief [DataFlowComponentAction CORBA interface] Notify rate changed
   * @endif
   */
  ReturnCode_t RTObject_impl::on_rate_changed(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("on_rate_changed(%d)", ec_id));
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
        preOnRateChanged(ec_id);
	ret = onRateChanged(ec_id);
        postOnRateChanged(ec_id, ret);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  //============================================================
  // SDO interfaces
  //============================================================
  /*!
   * @if jp
   * @brief [SDO interface] Organization リストの取得 
   * @else
   * @brief [SDO interface] Get Organization list
   * @endif
   */
  SDOPackage::OrganizationList* RTObject_impl::get_owned_organizations()
    throw (CORBA::SystemException,
           SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    RTC_TRACE(("get_owned_organizations()"));
    try
      {
	SDOPackage::OrganizationList_var org_list;
	org_list = new SDOPackage::OrganizationList(m_sdoOwnedOrganizations);
	return org_list._retn();
      }
    catch (...)
      {
	throw SDOPackage::NotAvailable();
      }
    return new SDOPackage::OrganizationList();
  }
  
  // SDOPackage::SDO
  /*!
   * @if jp
   * @brief [SDO interface] SDO ID の取得
   * @else
   * @brief [SDO interface] Get the SDO ID
   * @endif
   */
  char* RTObject_impl::get_sdo_id()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    RTC_TRACE(("get_sdo_id()"));
    try
      {
	CORBA::String_var sdo_id;
	sdo_id = CORBA::string_dup(m_profile.instance_name);
	return sdo_id._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_sdo_id()");
      }
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] SDO タイプの取得
   * @else
   * @brief [SDO interface] Get SDO type
   * @endif
   */
  char* RTObject_impl::get_sdo_type()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    RTC_TRACE(("get_sdo_type()"));
    CORBA::String_var sdo_type;
    try
      {
	sdo_type = CORBA::string_dup(m_profile.description);
	return sdo_type._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_sdo_type()");
      }
    sdo_type = "";
    return sdo_type._retn();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] SDO DeviceProfile リストの取得 
   * @else
   * @brief [SDO interface] Get SDO DeviceProfile list
   * @endif
   */
  SDOPackage::DeviceProfile* RTObject_impl::get_device_profile()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    RTC_TRACE(("get_device_profile()"));
    try
      {
	SDOPackage::DeviceProfile_var dprofile;
	dprofile =
          new SDOPackage::DeviceProfile(m_pSdoConfigImpl->getDeviceProfile());
	return dprofile._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_device_profile()");
      }
    return new SDOPackage::DeviceProfile();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] SDO ServiceProfile の取得 
   * @else
   * @brief [SDO interface] Get SDO ServiceProfile
   * @endif
   */
  SDOPackage::ServiceProfileList* RTObject_impl::get_service_profiles()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    RTC_TRACE(("get_service_profiles()"));
    m_sdoSvcProfiles = m_pSdoConfigImpl->getServiceProfiles();
    try
      {
	SDOPackage::ServiceProfileList_var sprofiles;
	sprofiles = new SDOPackage::ServiceProfileList(m_sdoSvcProfiles);
	return sprofiles._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_service_profiles()");
      }
    return new SDOPackage::ServiceProfileList();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] 特定のServiceProfileの取得 
   * @else
   * @brief [SDO interface] Get specified ServiceProfile
   * @endif
   */
  SDOPackage::ServiceProfile*
  RTObject_impl::get_service_profile(const char* id)
    throw (CORBA::SystemException, 
	   SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	   SDOPackage::InternalError)
  {
    RTC_TRACE(("get_service_profile(%s))", id));
    m_sdoSvcProfiles = m_pSdoConfigImpl->getServiceProfiles();
    if (!id)
      throw SDOPackage::InvalidParameter("get_service_profile(): Empty name.");
    
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_sdoSvcProfiles, svc_name(id));
    if(index < 0)
    {
      throw SDOPackage::InvalidParameter("get_service_profile():"
                                         "Name is not found.");
    }
    try
      {
	SDOPackage::ServiceProfile_var sprofile;
	sprofile = new SDOPackage::ServiceProfile(m_sdoSvcProfiles[index]);
	return sprofile._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_service_profile()");
      }
    return new SDOPackage::ServiceProfile();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] 指定された SDO Service の取得
   * @else
   * @brief [SDO interface] Get specified SDO Service's reference
   * @endif
   */
  SDOPackage::SDOService_ptr RTObject_impl::get_sdo_service(const char* id)
    throw (CORBA::SystemException, 
	   SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	   SDOPackage::InternalError)
  {
    RTC_TRACE(("get_sdo_service(%s))", id));
    m_sdoSvcProfiles = m_pSdoConfigImpl->getServiceProfiles();
    if (!id)
      throw SDOPackage::InvalidParameter("get_service(): Empty name.");
    
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_sdoSvcProfiles, svc_name(id));
    if (index <0)
    {
      throw SDOPackage::InvalidParameter("get_service(): Name is not found.");
    }
    try
      {
	SDOPackage::SDOService_var service;
	service = m_sdoSvcProfiles[index].service;
	return service._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_service()");
      }
    return SDOPackage::SDOService::_nil();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] Configuration オブジェクトの取得 
   * @else
   * @brief [SDO interface] Get Configuration object
   * @endif
   */
  SDOPackage::Configuration_ptr RTObject_impl::get_configuration()
    throw (CORBA::SystemException, 
	   SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	   SDOPackage::InternalError)
  {
    RTC_TRACE(("get_configuration()"));
    if (m_pSdoConfig == NULL)
      throw SDOPackage::InterfaceNotImplemented();
    try
      {
#ifdef ORB_IS_RTORB
	SDOPackage::Configuration_ptr config;
	config = m_pSdoConfig;
	return config;
#else // ORB_IS_RTORB
	SDOPackage::Configuration_var config;
	config = m_pSdoConfig;
	return config._retn();
#endif // ORB_IS_RTORB
      }
    catch (...)
      {
	SDOPackage::InternalError("get_configuration()");
      }
    return SDOPackage::Configuration::_nil();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] Monitoring オブジェクトの取得 
   * @else
   * @brief [SDO interface] Get Monitoring object
   * @endif
   */
  SDOPackage::Monitoring_ptr RTObject_impl::get_monitoring()
    throw (CORBA::SystemException, 
	   SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	   SDOPackage::InternalError)
  {
    RTC_TRACE(("get_monitoring()"));
    throw SDOPackage::InterfaceNotImplemented();
    return SDOPackage::Monitoring::_nil();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] Organization リストの取得 
   * @else
   * @brief [SDO interface] Get Organization list
   * @endif
   */
  SDOPackage::OrganizationList* RTObject_impl::get_organizations()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    RTC_TRACE(("get_organizations()"));
    m_sdoOrganizations = m_pSdoConfigImpl->getOrganizations();
    try
      {
	SDOPackage::OrganizationList_var org;
	org = new SDOPackage::OrganizationList(m_sdoOrganizations);
	return org._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_organizations()");
      }
    return new SDOPackage::OrganizationList(0);
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] SDO Status リストの取得 
   * @else
   * @brief [SDO interface] Get SDO Status list
   * @endif
   */
  SDOPackage::NVList* RTObject_impl::get_status_list()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    RTC_TRACE(("get_status_list()"));
    try
      {
	NVList_var status;
	status = new NVList(m_sdoStatus);
	return status._retn();
      }
    catch (...)
      {
	SDOPackage::InternalError("get_status_list()");
      }
    return new SDOPackage::NVList(0);
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] SDO Status の取得 
   * @else
   * @brief [SDO interface] Get SDO Status
   * @endif
   */
  CORBA::Any* RTObject_impl::get_status(const char* name)
    throw (CORBA::SystemException, 
	   SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	   SDOPackage::InternalError)
  {
    RTC_TRACE(("get_status(%s)", name));
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_sdoStatus, nv_name(name));
    if (index < 0)
      throw SDOPackage::InvalidParameter("get_status(): Not found");
    try
      {
	CORBA::Any_var status;
	status = new CORBA::Any(m_sdoStatus[index].value);
	return status._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_status()");
      }
    return new CORBA::Any();
  }
  
  //============================================================
  // Local methods
  //============================================================
  /*!
   * @if jp
   * @brief [local interface] インスタンス名の設定
   * @else
   * @brief [local interface] Set instance name
   * @endif
   */
  void RTObject_impl::setInstanceName(const char* instance_name)
  {
    rtclog.setName(instance_name);
    RTC_TRACE(("setInstanceName(%s)", instance_name));

    m_properties["instance_name"] = instance_name;
#ifndef ORB_IS_RTORB
    m_profile.instance_name = m_properties["instance_name"].c_str();
#else // ORB_IS_RTORB
    m_profile.instance_name = (char *)m_properties["instance_name"].c_str();
#endif // ORB_IS_RTORB
  }
  
  /*!
   * @if jp
   * @brief [local interface] Naming Server 情報の取得
   * @else
   * @brief [local interface] Get Naming Server information
   * @endif
   */
  std::vector<std::string> RTObject_impl::getNamingNames()
  {
    RTC_TRACE(("getNamingNames()"));
    return coil::split(m_properties["naming.names"], ",");
  }
  
  /*!
   * @if jp
   * @brief [local interface] オブジェクトリファレンスの設定
   * @else
   * @brief [local interface] Set the object reference
   * @endif
   */
  void RTObject_impl::setObjRef(const RTObject_ptr rtobj)
  {
    RTC_TRACE(("setObjRef()"));
    m_objref = RTC::RTObject::_duplicate(rtobj);
  }
  
  /*!
   * @if jp
   * @brief [local interface] オブジェクトリファレンスの取得
   * @else
   * @brief [local interface] Get the object reference
   * @endif
   */
  RTObject_ptr RTObject_impl::getObjRef() const
  {
    RTC_TRACE(("getObjRef()"));

    return m_objref;
  }
  
  /*!
   * @if jp
   * @brief [local interface] RTC のプロパティを設定する
   * @else
   * @brief [local interface] Set RTC property
   * @endif
   */
  void RTObject_impl::setProperties(const coil::Properties& prop)
  {
    RTC_TRACE(("setProperties()"));
    m_properties << prop;
#ifndef ORB_IS_RTORB
    m_profile.instance_name = m_properties["instance_name"].c_str();
    m_profile.type_name     = m_properties["type_name"].c_str();
    m_profile.description   = m_properties["description"].c_str();
    m_profile.version       = m_properties["version"].c_str();
    m_profile.vendor        = m_properties["vendor"].c_str();
    m_profile.category      = m_properties["category"].c_str();
#else // ORB_IS_RTORB
    m_profile.instance_name = (char*)m_properties["instance_name"].c_str();
    m_profile.type_name     = (char*)m_properties["type_name"].c_str();
    m_profile.description   = (char*)m_properties["description"].c_str();
    m_profile.version       = (char*)m_properties["version"].c_str();
    m_profile.vendor        = (char*)m_properties["vendor"].c_str();
    m_profile.category      = (char*)m_properties["category"].c_str();
#endif //ORB_IS_RTORB
  }
  
  /*!
   * @if jp
   * @brief [local interface] RTC のプロパティを取得する
   * @else
   * @brief [local interface] Get RTC property
   * @endif
   */
  coil::Properties& RTObject_impl::getProperties()
  {
    RTC_TRACE(("getProperties()"));
    return m_properties;
  }
  
  /*!
   * @if jp
   * @brief コンフィギュレーションパラメータの更新(ID指定)
   * @else
   * @brief Update configuration parameters (by ID)
   * @endif
   */
  void RTObject_impl::updateParameters(const char* config_set)
  {
    RTC_TRACE(("updateParameters(%s)", config_set));
    m_configsets.update(config_set);
    return;
  }
  
  /*!
   * @if jp
   * @brief [local interface] Port を登録する
   * @else
   * @brief [local interface] Register Port
   * @endif
   */
  void RTObject_impl::registerPort(PortBase& port)
  {
    RTC_TRACE(("registerPort(PortBase&)"));
    if (!addPort(port))
      RTC_ERROR(("addPort(PortBase&) failed."));
  }
  bool RTObject_impl::addPort(PortBase& port)
  {
    RTC_TRACE(("addPort(PortBase&)"));
    port.setOwner(this->getObjRef());
    onAddPort(port.getPortProfile());
    return m_portAdmin.addPort(port);
  }
  
  void RTObject_impl::registerPort(PortService_ptr port)
  {
    RTC_TRACE(("registerPort(PortBase&)"));
    if (!addPort(port))
      RTC_ERROR(("addPort(PortBase&) failed."));
  }
  bool RTObject_impl::addPort(PortService_ptr port)
  {
    RTC_TRACE(("addPort(PortService_ptr)"));
    return m_portAdmin.addPort(port);
  }

  void RTObject_impl::registerPort(CorbaPort& port)
  {
    RTC_TRACE(("registerPort(CorbaPort&)"));
    if (!addPort(port))
      RTC_ERROR(("addPort(CorbaPort&) failed."));
  }

  bool RTObject_impl::addPort(CorbaPort& port)
  {
    RTC_TRACE(("addPort(CrobaPort)"));
    std::string propkey("port.corbaport.");
    m_properties.getNode(propkey) 
      << m_properties.getNode("port.corba");
    
    port.init(m_properties.getNode(propkey));
    return addPort((PortBase&)port);
  }

  /*!
   * @if jp
   * @brief [local interface] DataInPort を登録する
   * @else
   * @brief [local interface] Register DataInPort
   * @endif
   */
  bool RTObject_impl::addInPort(const char* name,
				InPortBase& inport)
  {
    RTC_TRACE(("addInPort(%s)", name));

    std::string propkey("port.inport.");
    propkey += name;
    m_properties.getNode(propkey)
      << m_properties.getNode("port.inport.dataport");

    bool ret(addPort(inport));
    
    if (!ret) {
      RTC_ERROR(("addInPort() failed."));
      return ret;
    }

    inport.init(m_properties.getNode(propkey));
    m_inports.push_back(&inport);
    return ret;
  }

  void RTObject_impl::registerInPort(const char* name,
                                     InPortBase& inport)
  {
    RTC_TRACE(("registerInPort(%s)", name));

    if (!addInPort(name, inport))
      RTC_ERROR(("addInPort(%s) failed.", name));
  }

  /*!
   * @if jp
   * @brief [local interface] DataOutPort を登録する
   * @else
   * @brief [local interface] Register DataOutPort
   * @endif
   */
  bool RTObject_impl::addOutPort(const char* name,
				 OutPortBase& outport)
  {
    RTC_TRACE(("addOutPort(%s)", name));
    
    std::string propkey("port.outport.");
    propkey += name;
    m_properties.getNode(propkey) 
      << m_properties.getNode("port.outport.dataport");
    
    bool ret(addPort(outport));
    
    if (!ret) {
      RTC_ERROR(("addOutPort() failed."));
      return ret;
    }

    outport.init(m_properties.getNode(propkey));
    m_outports.push_back(&outport);
    return ret;
  }
  
  void RTObject_impl::registerOutPort(const char* name,
				      OutPortBase& outport)
  {
    RTC_TRACE(("registerOutPort(%s)", name));

    if (!addOutPort(name, outport))
      RTC_ERROR(("addOutPort(%s) failed.", name));

  }
  
  /*!
   * @if jp
   * @brief [local interface] DataInPort を削除する
   * @else
   * @brief [local interface] Unregister DataInPort
   * @endif
   */
  bool RTObject_impl::removeInPort(InPortBase& inport)
  {
    RTC_TRACE(("removeInPort()"));
    bool ret(removePort(inport));

    std::vector<InPortBase*>::iterator it = m_inports.begin();

    if (ret)
      {
	while (it != m_inports.end())
	  {
	    if ( (*it) == &inport )
	      {
		m_inports.erase(it);
		return true;
	      }
	    ++it;
	  }
      }

    return false;
  }

  /*!
   * @if jp
   * @brief [local interface] DataOutPort を削除する
   * @else
   * @brief [local interface] Unregister DataOutPort
   * @endif
   */
  bool RTObject_impl::removeOutPort(OutPortBase& outport)
  {
    RTC_TRACE(("removeOutPort()"));

    bool ret(removePort(outport));

    if (ret)
      {
	std::vector<OutPortBase*>::iterator it = m_outports.begin();
	while (it != m_outports.end())
	  {
	    if ( (*it) == &outport )
	      {
		m_outports.erase(it);
		return true;
	      }
	    ++it;
	  }
      }

    return false;
  }

  /*!
   * @if jp
   * @brief [local interface] Port の登録を削除する
   * @else
   * @brief [local interface] Unregister Port
   * @endif
   */
  bool RTObject_impl::removePort(PortBase& port)
  {
    RTC_TRACE(("removePort(PortBase&)"));
    onRemovePort(port.getPortProfile());
    return m_portAdmin.removePort(port);
  }
  bool RTObject_impl::removePort(PortService_ptr port)
  {
    RTC_TRACE(("removePort(PortService_pt)"));
    return m_portAdmin.removePort(port);
  }
  bool RTObject_impl::removePort(CorbaPort& port)
  {
    RTC_TRACE(("removePort(PortBase&)"));
    onRemovePort(port.getPortProfile());
    return m_portAdmin.removePort((PortBase&)port);
  }

  void RTObject_impl::deletePort(PortBase& port)
  {
    RTC_TRACE(("deletePort(PortBase&)"));
    if (!removePort(port))
      RTC_ERROR(("removePort(PortBase&) failed."));
    return;
  }
  void RTObject_impl::deletePort(PortService_ptr port)
  {
    RTC_TRACE(("deletePort(PortService_pt)"));
    if (!removePort(port))
      RTC_ERROR(("removePort(PortService_pt) failed."));
    return;
  }
  void RTObject_impl::deletePort(CorbaPort& port)
  {
    RTC_TRACE(("deletePort(CorbaPort)"));
    if (!removePort(port))
      RTC_ERROR(("removePort(CorbaPort) failed."));
    return;
  }

  /*!
   * @if jp
   * @brief [local interface] 名前指定により Port の登録を削除する
   * @else
   * @brief [local interface] Delete Port by specifying its name
   * @endif
   */
  void RTObject_impl::deletePortByName(const char* port_name)
  {
    RTC_TRACE(("deletePortByName(%s)", port_name));
    m_portAdmin.deletePortByName(port_name);
    return;
  }

   
  /*!
   * @if jp
   *
   * @brief [local interface] SDOサービスを追加する
   * @else
   * @brief [local interface] Add SDO service
   * @endif
   */
  ReturnCode_t
  RTObject_impl::addSdoService(const SDOPackage::ServiceProfile& profile)
  {
    CORBA::Boolean ret = m_pSdoConfigImpl->add_service_profile(profile);
    if (ret) { return RTC::RTC_OK; }
    return RTC::RTC_ERROR;
    /*
    std::string id(profile.id);
    for (CORBA::ULong i(0), len(m_sdoSvcProfiles.length()); i < len; ++i)
      {
        if (id == m_sdoSvcProfiles[i].id)
          {
            return RTC::PRECONDITION_NOT_MET;
          }
      }
    CORBA_SeqUtil::push_back(m_sdoSvcProfiles, profile);
    return RTC::RTC_OK;
    */
  }
  
  /*!
   * @if jp
   * @brief [local interface] SDOサービスを削除する
   * @else
   * @brief [local interface] Remove SDO service
   * @endif
   */
  SDOPackage::SDOService_var
  RTObject_impl::removeSdoService(const char* service_id)
  {
    SDOPackage::SDOService_var service;
    try
      {
        service = get_sdo_service(service_id);
        m_pSdoConfigImpl->remove_service_profile(service_id);
      }
    catch (SDOPackage::InvalidParameter& e)
      {
      }
    catch (SDOPackage::NotAvailable& e)
      {
      }
    catch (SDOPackage::InternalError& e)
      {
      }
    catch (...)
      {
      }
    return service._retn();
    /*
    std::string id(service_id);
    SDOPackage::ServiceProfile_var profile;
    for (CORBA::ULong i(0), len(m_sdoSvcProfiles.length()); i < len; ++i)
      {
        if (id == m_sdoSvcProfiles[i].id)
          {
            profile = m_sdoSvcProfiles[i];
            CORBA_SeqUtil::erase(m_sdoSvcProfile, id);
          }
      }
    return profile._retn();
    */
  }
 
  /*!
   * @if jp
   * @brief 全 InPort のデータを読み込む。
   * @return 読み込み結果(全ポートの読み込み成功:true，失敗:false)
   * @else
   * @brief Readout the value from All InPorts.
   * @return result (Successful:true, Failed:false) 
  * @endif
   */
  bool RTObject_impl::readAll()
  {
    RTC_TRACE(("readAll()"));
    std::vector<InPortBase*>::iterator it     = m_inports.begin(); 
    std::vector<InPortBase*>::iterator it_end = m_inports.end(); 
    bool ret(true);

    while( it != it_end )
      {

	if (!((*it)->read()))
	  {
	    RTC_DEBUG(("The error occurred in readAll()."));
	    ret = false;
	    if (!m_readAllCompletion)
	      return false;
	  }
	++it;
      }

    return ret;
  }

  /*!
   * @if jp
   * @brief 全 OutPort のwrite()メソッドをコールする。
   * @return 読み込み結果(全ポートへの書き込み成功:true，失敗:false)
   * @else
   * @brief The write() method of all OutPort is called. 
   * @return result (Successful:true, Failed:false)
   * @endif
   */
  bool RTObject_impl::writeAll()
  {
    RTC_TRACE(("writeAll()"));
    std::vector<OutPortBase*>::iterator it     = m_outports.begin(); 
    std::vector<OutPortBase*>::iterator it_end = m_outports.end(); 

    bool ret(true);

    while( it != it_end )
      {
	if (!((*it)->write()))
	  {
	    RTC_DEBUG(("The error occurred in writeAll()."));
	    ret = false;
	    if (!m_writeAllCompletion)
	      return false;
	  }
	++it;
      }
    return ret;
  }

  /*!
   * @if jp
   *
   * @brief onExecute()実行前でのreadAll()メソッドの呼出を有効または無効にする。
   *
   * このメソッドをパラメータをtrueとして呼ぶ事により、onExecute()実行前に
   * readAll()が呼出されるようになる。
   * パラメータがfalseの場合は、readAll()呼出を無効にする。
   *
   * @param read(default:true) 
   *        (readAll()メソッド呼出あり:true, readAll()メソッド呼出なし:false)
   *
   * @else
   *
   * @brief Set whether to execute the readAll() method. 
   *
   * Set whether to execute the readAll() method. 
   *
   * @param read(default:true)
   *        (readAll() is called:true, readAll() isn't called:false)
   * @param completion(default:false)
   *
   * @endif
   */
  void RTObject_impl::setReadAll(bool read, bool completion)
  {
    m_readAll = read;
    m_readAllCompletion = completion;
  }

  /*!
   * @if jp
   *
   * @brief onExecute()実行後にwriteAll()メソッドの呼出を有効または無効にする。
   *
   * このメソッドをパラメータをtrueとして呼ぶ事により、onExecute()実行後に
   * writeAll()が呼出されるようになる。
   * パラメータがfalseの場合は、writeAll()呼出を無効にする。
   *
   * @param write(default:true) 
   *        (writeAll()メソッド呼出あり:true, writeAll()メソッド呼出なし:false)
   *
   * @else
   *
   * @brief Set whether to execute the writeAll() method. 
   *
   * Set whether to execute the writeAll() method. 
   *
   * @param write(default:true)
   *        (writeAll() is called:true, writeAll() isn't called:false)
   * @param completion(default:false)
   *
   * @endif
   */
  void RTObject_impl::setWriteAll(bool write, bool completion)
  {
    m_writeAll = write;
    m_writeAllCompletion = completion;
  }

  /*!
   * @if jp
   * @brief 全 Port の登録を削除する
   * @else
   * @brief Unregister All Ports
   * @endif
   */
  void RTObject_impl::finalizePorts()
  {
    RTC_TRACE(("finalizePorts()"));
    m_portAdmin.finalizePorts();
    m_inports.clear();
    m_outports.clear();
  }

  void RTObject_impl::finalizeContexts()
  {
    RTC_TRACE(("finalizeContexts()"));
    for (int i(0), len(m_eclist.size()); i < len; ++i)
      {
        m_eclist[i]->stop();
        try
          {
            PortableServer::ObjectId_var oid
              = m_pPOA->servant_to_id(m_eclist[i]);
            m_pPOA->deactivate_object(oid);
          }
        catch (PortableServer::POA::ServantNotActive &e)
          {
            RTC_ERROR(("%s", e._name()));
          }
        catch (PortableServer::POA::WrongPolicy &e)
          {
            RTC_ERROR(("%s", e._name()));
          }
        catch (...)
          {
            // never throws exception
            RTC_ERROR(("Unknown exception caught."));
          }
        delete m_eclist[i];
      }
    if (!m_eclist.empty())
      {
        m_eclist.clear();
      }
  }
  
  /*!
   * @if jp
   * @brief PreComponentActionListener リスナを追加する
   *
   * @else
   * @brief Adding PreComponentAction type listener
   *
   * @endif
   */
  void RTObject_impl::
  addPreComponentActionListener(PreComponentActionListenerType listener_type,
                                PreComponentActionListener* listener,
                                bool autoclean)
  {
    m_actionListeners.
      preaction_[listener_type].addListener(listener, autoclean);
  }
  
  
  /*!
   * @if jp
   * @brief PreComponentActionListener リスナを削除する
   *
   * @else
   * @brief Removing PreComponentAction type listener
   *
   * @endif
   */
  void RTObject_impl::
  removePreComponentActionListener(
                                   PreComponentActionListenerType listener_type,
                                   PreComponentActionListener* listener)
  {
    m_actionListeners.
      preaction_[listener_type].removeListener(listener);
  }


  /*!
   * @if jp
   * @brief PostComponentActionListener リスナを追加する
   *
   * @else
   * @brief Adding PostComponentAction type listener
   *
   * @endif
   */
  void RTObject_impl::
  addPostComponentActionListener(
                                 PostComponentActionListenerType listener_type,
                                 PostComponentActionListener* listener,
                                 bool autoclean)
  {
    m_actionListeners.
      postaction_[listener_type].addListener(listener, autoclean);
  }


  /*!
   * @if jp
   * @brief PostComponentActionListener リスナを削除する
   *
   * @else
   * @brief Removing PostComponentAction type listener
   *
   * @endif
   */
  void RTObject_impl::
  removePostComponentActionListener(
                                PostComponentActionListenerType listener_type,
                                PostComponentActionListener* listener)
  {
    m_actionListeners.
      postaction_[listener_type].removeListener(listener);
  }

  /*!
   * @if jp
   * @brief PortActionListener リスナを追加する
   *
   * @else
   * @brief Adding PortAction type listener
   *
   * @endif
   */
  void RTObject_impl::
  addPortActionListener(PortActionListenerType listener_type,
                        PortActionListener* listener,
                        bool autoclean)
  {
    m_actionListeners.
      portaction_[listener_type].addListener(listener, autoclean);
  }


  /*!
   * @if jp
   * @brief PortActionListener リスナを削除する
   *
   * @else
   * @brief Removing PortAction type listener
   *
   * @endif
   */
  void RTObject_impl::
  removePortActionListener(PortActionListenerType listener_type,
                           PortActionListener* listener)
  {
    m_actionListeners.
      portaction_[listener_type].removeListener(listener);
  }


  /*!
   * @if jp
   * @brief ExectionContextActionListener リスナを追加する
   *
   * @else
   * @brief Adding ExecutionContextAction type listener
   *
   * @endif
   */
  void RTObject_impl::
  addExecutionContextActionListener(ECActionListenerType listener_type,
                                    ECActionListener* listener,
                                    bool autoclean)
  {
    m_actionListeners.
      ecaction_[listener_type].addListener(listener, autoclean);
  }


  /*!
   * @if jp
   * @brief ExecutionContextActionListener リスナを削除する
   *
   * @else
   * @brief Removing ExecutionContextAction type listener
   *
   * @endif
   */
  void RTObject_impl::
  removeExecutionContextActionListener(ECActionListenerType listener_type,
                                       ECActionListener* listener)
  {
    m_actionListeners.
      ecaction_[listener_type].removeListener(listener);
  }

  
  /*!
   * @if jp
   * @brief ConfigurationParamListener を追加する
   * @else
   * @brief Adding ConfigurationParamListener 
   * @endif
   */
  void RTObject_impl::
  addConfigurationParamListener(ConfigurationParamListenerType type,
                                ConfigurationParamListener* listener,
                                bool autoclean)
  {
    m_configsets.addConfigurationParamListener(type, listener, autoclean);
  }

  /*!
   * @if jp
   * @brief ConfigurationParamListener を削除する
   * @else
   * @brief Removing ConfigurationParamListener 
   * @endif
   */
  void RTObject_impl::
  removeConfigurationParamListener(ConfigurationParamListenerType type,
                                   ConfigurationParamListener* listener)
  {
    m_configsets.removeConfigurationParamListener(type, listener);
  }

  /*!
   * @if jp
   * @brief ConfigurationSetListener を追加する
   * @else
   * @brief Adding ConfigurationSetListener 
   * @endif
   */
  void RTObject_impl::
  addConfigurationSetListener(ConfigurationSetListenerType type,
                              ConfigurationSetListener* listener,
                              bool autoclean)
  {
    m_configsets.addConfigurationSetListener(type, listener, autoclean);
  }
  
  /*!
   * @if jp
   * @brief ConfigurationSetListener を削除する
   * @else
   * @brief Removing ConfigurationSetListener 
   * @endif
   */
  void RTObject_impl::
  removeConfigurationSetListener(ConfigurationSetListenerType type,
                                 ConfigurationSetListener* listener)
  {
    m_configsets.removeConfigurationSetListener(type, listener);
  }
  
  /*!
   * @if jp
   * @brief ConfigurationSetNameListener を追加する
   * @else
   * @brief Adding ConfigurationSetNameListener 
   * @endif
   */
  void RTObject_impl::
  addConfigurationSetNameListener(ConfigurationSetNameListenerType type,
                                  ConfigurationSetNameListener* listener,
                                  bool autoclean)
  {
    m_configsets.addConfigurationSetNameListener(type, listener, autoclean);
  }
  
  /*!
   * @if jp
   * @brief ConfigurationSetNameListener を削除する
   * @else
   * @brief Removing ConfigurationSetNameListener 
   * @endif
   */
  void RTObject_impl::
  removeConfigurationSetNameListener(ConfigurationSetNameListenerType type,
                                     ConfigurationSetNameListener* listener)
  {
    m_configsets.removeConfigurationSetNameListener(type, listener);
  }
  
  
  /*!
   * @if jp
   * @brief RTC を終了する
   * @else
   * @brief Shutdown RTC
   * @endif
   */
  void RTObject_impl::shutdown()
  {
    RTC_TRACE(("shutdown()"));
    try
      {
	finalizePorts();
        finalizeContexts();
        PortableServer::ObjectId_var oid1;
        oid1 = m_pPOA->servant_to_id(m_pSdoConfigImpl);
        PortableServer::ObjectId_var oid2;
        oid2 = m_pPOA->servant_to_id(this);
	m_pPOA->deactivate_object(oid1);
	m_pPOA->deactivate_object(oid2);
      }
    catch (PortableServer::POA::ServantNotActive &e)
      {
        RTC_ERROR(("%s", e._name()));
      }
    catch (PortableServer::POA::WrongPolicy &e)
      {
        RTC_ERROR(("%s", e._name()));
      }
    catch (...)
      {
        // never throws exception
        RTC_ERROR(("Unknown exception caught."));
      }
    
    if (m_pManager != NULL)
      {
        RTC_DEBUG(("Cleanup on Manager"));
        m_pManager->notifyFinalized(this);
      }
  }



}
