// -*- C++ -*-
/*!
 * @file Manager.h
 * @brief RTComponent manager class
 * @date $Date: 2007-04-26 15:36:54 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Manager.h,v 1.9 2007-04-26 15:36:54 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.8  2007/04/23 04:53:29  n-ando
 * Component instantiation processes were divided into some functions.
 *
 * Revision 1.7  2007/04/17 09:22:08  n-ando
 * Namespace of Timer class was changed from ::Timer to RTC::Timer.
 *
 * Revision 1.6  2007/04/13 18:02:14  n-ando
 * Some configuration properties handling processes were changed.
 *
 * Revision 1.5  2007/01/21 09:54:30  n-ando
 * A trivial bug fix.
 *
 * Revision 1.4  2007/01/14 19:42:37  n-ando
 * The activate() function now performs POA manager activation and
 * invoking ModuleInitProc.
 * Debugging messages are now output to system logger.
 *
 * Revision 1.3  2006/11/06 01:31:57  n-ando
 * Some Manager's functions has been implemented.
 * - Component creation process
 * - System logger initialization
 *
 * Revision 1.2  2006/10/25 17:28:05  n-ando
 * Component factory registration and relative functions are implemented.
 *
 * Revision 1.1  2006/10/17 10:21:24  n-ando
 * The first commitment.
 *
 *
 */

#ifndef Manager_h
#define Manager_h

#include <rtm/RTC.h>

#include <iostream>
#include <string>
#include <vector>

#include <ace/Synch.h>
#include <ace/Task.h>

#include <rtm/Factory.h>
#include <rtm/ECFactory.h>
#include <rtm/ObjectManager.h>
#include <rtm/RTObject.h>
#include <rtm/SystemLogger.h>

class Properties;

namespace RTC
{
  class CorbaNaming;
  class ModuleManager;
  class NamingManager;
  class CorbaObjectManager;
  class Manager;
  class Timer;

  typedef void (*ModuleInitProc)(Manager* manager);  

  class Manager
  {
  protected:
    /*!
     * @if jp
     * @brief Protected ���󥹥ȥ饯��
     * @else
     * @brief Protected Constructor
     * @endif
     */
    Manager();


    /*!
     * @if jp
     * @brief Protected ���ԡ����󥹥ȥ饯��
     * @else
     * @brief Protected Copy Constructor
     * @endif
     */
    Manager(const Manager& manager);
      //      Manager& operator=(const Manager& manager){return manager;};
    
  public:
    /*!
     * @if jp
     * @brief �ޥ͡�����ν����
     *
     * �ޥ͡�������������� static ���дؿ���
     * �ޥ͡�����򥳥ޥ�ɥ饤�������Ϳ���ƽ�������롣
     * �ޥ͡��������Ѥ�����ϡ�ɬ�����ν�������дؿ� init() ��
     * �ƤФʤ���Фʤ�ʤ���
     * �ޥ͡�����Υ��󥹥��󥹤����������ˡ�Ȥ��ơ�init(), instance() ��
     * 2�Ĥ� static ���дؿ����Ѱդ���Ƥ��뤬���������init()�Ǥ���
     * �Ԥ��ʤ����ᡢManager ����¸���֤ΰ��ֺǽ�ˤ�init()��Ƥ�ɬ�פ����롣
     *
     * ���ޥ͡�����ν��������
     * - initManager: ����������config�ե�������ɤ߹��ߡ����֥����ƥ�����
     * - initLogger: Logger�����
     * - initORB: ORB �����
     * - initNaming: NamingService �����
     * - initExecutionContext: ExecutionContext factory �����
     * - initTimer: Timer �����
     *
     * @param argc ���ޥ�ɥ饤������ο�
     * @param argv ���ޥ�ɥ饤�����
     * 
     * @else
     * @brief Initializa manager
     *
     * This is the static member function to tintialize the Manager.
     * The Manager is initialized by given arguments.
     * At the starting the manager, this static member function "must" be
     * called from application program. The manager has two static functions
     * to get the instance, "init()" and "instance()". Since initializing
     * process is only performed by the "init()" function, the "init()" has
     * to be called at the beginning of the lifecycle of the Manager.
     * function.
     *
     * @param argc The number of command line argument. 
     * @param argv The array of the command line arguments.
     *
     * @endif
     */ 
    static Manager* init(int argc, char** argv);


    /*!
     * @if jp
     * @brief �ޥ͡�����Υ��󥹥��󥹤μ���
     *
     * �ޥ͡�����Υ��󥹥��󥹤�������� static ���дؿ���
     * ���δؿ���Ƥ����ˡ�ɬ�����ν�������дؿ� init() ���ƤФ�Ƥ���
     * ɬ�פ����롣
     *
     * @return Manager ��ͣ��Υ��󥹥��󥹤λ���
     * 
     * @else
     *
     * @brief Get instance of the manager
     *
     * This is the static member function to get the instance of the Manager.
     * Before calling this function, ensure that the initialization function
     * "init()" is called.
     *
     * @return The only instance reference of the manager
     *
     * @endif
     */ 
    static Manager& instance();

    //============================================================
    // Manager
    //============================================================



    void terminate();
    void shutdown();
    void join();
    
    Logbuf& getLogbuf() {return m_Logbuf;}
    Properties& getConfig() { return m_config;}
    
    
    
    
    /*!
     * @if jp
     *
     * @brief ������ץ�������Υ��å�
     *
     * ���Υ��ڥ졼�����ϥ桼�����Ԥ��⥸�塼�����ν�����ץ�������
     * �����ꤹ�롣���������ꤵ�줿�ץ�������ϡ��ޥ͡����㤬��������졢
     * �����ƥ��ֲ����줿�塢Ŭ�ڤʥ����ߥ󥰤Ǽ¹Ԥ���롣
     *
     * @param proc ������ץ�������δؿ��ݥ���
     *
     * @else
     *
     * @brief Run the Manager
     *
     * This operation sets the initial procedure call to process module
     * initialization, other user defined initialization and so on.
     * The given procedure will be called at the proper timing after the 
     * manager initialization, activation and run.
     *
     * @param proc A function pointer to the initial procedure call
     *
     * @endif
     */
    void setModuleInitProc(ModuleInitProc proc);


    /*!
     * @if jp
     *
     * @brief Manager�Υ����ƥ��ֲ�
     *
     * ���Υ��ڥ졼�����ϰʲ��ν�����Ԥ�
     * - CORBA POAManager �Υ����ƥ��ֲ�
     * - �ޥ͡�����CORBA���֥������ȤΥ����ƥ��ֲ�
     * - Manager ���֥������ȤؤΥ��֥������Ȼ��Ȥ���Ͽ
     *
     * ���Υ��ڥ졼�����ϡ��ޥ͡�����ν�����塢runManager()
     * �����˸Ƥ�ɬ�פ����롣
     *
     * @else
     *
     * @brief Activate Manager
     *
     * This operation do the following,
     * - Activate CORBA POAManager
     * - Activate Manager CORBA object
     * - Bind object reference of the Manager to the nameserver
     *
     * This operationo should be invoked after Manager:init(),
     * and before tunManager().
     *
     * @endif
     */
    bool activateManager();

    /*!
     * @if jp
     *
     * @brief Manager�μ¹�
     *
     * ���Υ��ڥ졼�����ϥޥ͡�����Υᥤ��롼�פ�¹Ԥ��롣
     * ���Υᥤ��롼����Ǥϡ�CORBA ORB�Υ��٥�ȥ롼������
     * ��������롣�ǥե���ȤǤϡ����Υ��ڥ졼�����ϥ֥�å�����
     * Manager::destroy() ���ƤФ��ޤǽ������ᤵ�ʤ���
     * ���� no_block �� true �����ꤵ��Ƥ�����ϡ������ǥ��٥�ȥ롼��
     * ��������륹��åɤ�ư�����֥�å������˽������᤹��
     *
     * @param no_block false: �֥�å��󥰥⡼��, true: �Υ�֥�å��󥰥⡼��
     *
     * @else
     *
     * @brief Run the Manager
     *
     * This operation processes the main event loop of the Manager.
     * In this main loop, CORBA's ORB event loop or other processes
     * are performed. As the default behavior, this operation is going to
     * blocking mode and never returns until manager::destroy() is called.
     * When the given argument "no_block" is set to "true", this operation
     * creates a thread to process the event loop internally, and it doesn't
     * block and returns.
     *
     * @param no_block false: Blocking mode, true: non-blocking mode.
     *
     * @endif
     */
    void runManager(bool no_block = false);
    



    //============================================================
    // Module management
    //============================================================
    /*!
     * @if jp
     * @brief [CORBA interface] �⥸�塼��Υ���
     *
     * ����ݡ��ͥ�ȤΥ⥸�塼�����ɤ��ƽ�����ؿ���¹Ԥ��롣
     *
     * @param fname   �⥸�塼��ե�����̾
     * @param initfunc ������ؿ�̾
     * 
     * @else
     *
     * @brief [CORBA interface] Load module
     *
     * Load module (shared library, DLL etc..) by file name,
     * and invoke initialize function.
     *
     * @param fname    The module file name
     * @param initfunc The initialize function name
     *
     * @endif
     */  
    void load(const char* fname, const char* initfunc);


    /*!
     * @if jp
     *
     * @brief �⥸�塼��Υ������
     *
     * �⥸�塼��򥢥���ɤ���
     *
     * @param fname �⥸�塼��Υե�����̾
     * 
     * @else
     *
     * @brief Unload module
     *
     * Unload shared library.
     *
     * @param pathname Module file name
     *
     * @endif
     */ 

    void unload(const char* fname);


    /*!
     * @if jp
     *
     * @brief ���⥸�塼��Υ������
     *
     * �⥸�塼��򤹤٤ƥ�����ɤ���
     *
     * @else
     *
     * @brief Unload module
     *
     * Unload all loaded shared library.
     *
     * @endif
     */ 
    void unloadAll();


    /*!
     * @if jp
     * @brief ���ɺѤߤΥ⥸�塼��ꥹ�Ȥ��������
     * @else
     * @brief Get loaded module names
     * @endif
     */
    std::vector<std::string> getLoadedModules();
    

    /*!
     * @if jp
     * @brief ���ɲ�ǽ�ʥ⥸�塼��ꥹ�Ȥ��������
     * @else
     * @brief Get loadable module names
     * @endif
     */
    std::vector<std::string> getLoadableModules();

    //============================================================
    // Component Factory Management
    //============================================================
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�ȥե����ȥ����Ͽ����
     * @else
     * @brief Register RT-Component Factory
     * @endif
     */
    bool registerFactory(Properties& profile,
			 RtcNewFunc new_func,
			 RtcDeleteFunc delete_func);
    
    bool registerECFactory(const char* name,
			   ECNewFunc new_func,
			   ECDeleteFunc delete_func);
    
    /*!
     * @if jp
     * @brief �ե����ȥ����ꥹ�Ȥ��������
     * @else
     * @brief Get the list of all RT-Component Factory
     * @endif
     */
    std::vector<std::string> getModulesFactories();
    
    //============================================================
    // Component management
    //============================================================
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ���������
     * @else
     * @brief Create RT-Component
     * @endif
     */
    RtcBase* createComponent(const char* module_name);
    void cleanupComponent(RtcBase* comp);
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ�ľ�� Manager ����Ͽ����
     * @else
     * @brief Register RT-Component directly without Factory
     * @endif
     */
    bool registerComponent(RtcBase* comp);
    bool unregisterComponent(RtcBase* comp);


    bool bindExecutionContext(RtcBase* comp);

    /*!
     * @if jp
     * @brief Manager ����Ͽ����Ƥ���RT����ݡ��ͥ�Ȥ�������
     * @else
     * @brief Unregister RT-Component that is registered in the Manager
     * @endif
     */
    void deleteComponent(const char* instance_name);
    
    /*!
     * @if jp
     * @brief Manager ����Ͽ����Ƥ���RT����ݡ��ͥ�Ȥ��������
     * @else
     * @brief Get RT-Component's pointer
     * @endif
     */
    RtcBase* getComponent(const char* instance_name);
    
    /*!
     * @if jp
     * @brief Manager ����Ͽ����Ƥ�����RT����ݡ��ͥ�Ȥ��������
     * @else
     * @brief Get all RT-Component's pointer
     * @endif
     */
    std::vector<RtcBase*> getComponents();
    

    //============================================================
    // CORBA ��Ϣ
    //============================================================
    /*!
     * @if jp
     * @brief ORB �Υݥ��󥿤��������
     * @else
     * @brief Get the pointer to the ORB
     * @endif
     */
    CORBA::ORB_ptr getORB();

    /*!
     * @if jp
     * @brief Manager ������ RootPOA �Υݥ��󥿤��������
     * @else
     * @brief Get the pointer to the RootPOA 
     * @endif
     */
    PortableServer::POA_ptr getPOA();
    PortableServer::POAManager_ptr getPOAManager();


    //============================================================
    // Protected functions
    //============================================================
  protected:
    
    //============================================================
    // Manager initialize and finalization
    //============================================================
    /*!
     * @if jp
     * @brief Manager ���������������
     * @else
     * @brief Manager internal initialization
     * @endif
     */
    void initManager(int argc, char** argv);


    /*!
     * @if jp
     * @brief Manager �ν�λ����
     * @else
     * @brief Manager internal finalization
     * @endif
     */
    void shutdownManager();


    //============================================================
    // Logger initialize and terminator
    //============================================================
    /*!
     * @if jp
     * @brief System logger �ν����
     * @else
     * @brief System logger initialization
     * @endif
     */
    bool initLogger();


    /*!
     * @if jp
     * @brief System Logger �ν�λ����
     * @else
     * @brief System Logger finalization
     * @endif
     */
    void shutdownLogger();


    //============================================================
    // ORB initialization and finalization
    //============================================================
    /*!
     * @if jp
     * @brief CORBA ORB �ν��������
     * @else
     * @brief CORBA ORB initialization
     * @endif
     */
    bool initORB();
    
    
    /*!
     * @if jp
     * @brief ORB �Υ��ޥ�ɥ饤�󥪥ץ�������
     * @else
     * @brief ORB command option creation
     * @endif
     */
    std::string createORBOptions();
    
    
    /*!
     * @if jp
     * @brief ORB �ν�λ����
     * @else
     * @brief ORB finalization
     * @endif
     */
    void shutdownORB();

   
    //============================================================
    // NamingService initialization and finalization
    //============================================================
    /*!
     * @if jp
     * @brief NamingManager �ν����
     * @else
     * @brief NamingManager initialization
     * @endif
     */
    bool initNaming();
    void shutdownNaming();


    //============================================================
    // Component management
    //============================================================
    void shutdownComponents();


    void configureComponent(RtcBase* comp);


    bool initExecContext();

    bool initTimer();

    bool mergeProperty(Properties& prop, const char* file_name);
    std::string formatString(const char* naming_format,
			     Properties& prop);
    
    //============================================================
    // protected �ѿ�
    //============================================================

    //------------------------------------------------------------
    // static var
    //------------------------------------------------------------
    /*!
     * @if jp
     * @brief ͣ��� Manager �ؤΥݥ���
     * @else
     * @brief The pointer to the Manager
     * @endif
     */
    static Manager* manager;

    /*!
     * @if jp
     * @brief ͣ��� Manager �ؤΥݥ��󥿤��Ф��� mutex
     * @else
     * @brief The mutex of the pointer to the Manager 
     * @endif
     */
    static ACE_Thread_Mutex mutex;
    

    //------------------------------------------------------------
    // CORBA var
    //------------------------------------------------------------
    /*!
     * @if jp
     * @brief ORB �ؤΥݥ���
     * @else
     * @brief The pointer to the ORB
     * @endif
     */
    CORBA::ORB_var m_pORB;

    /*!
     * @if jp
     * @brief POA �ؤΥݥ���
     * @else
     * @brief The pointer to the POA
     * @endif
     */
    PortableServer::POA_var m_pPOA;

    /*!
     * @if jp
     * @brief POAManager �ؤΥݥ���
     * @else
     * @brief The pointer to the POAManager
     * @endif
     */
    PortableServer::POAManager_var m_pPOAManager;


    //------------------------------------------------------------
    // Manager's variable
    //------------------------------------------------------------
    /*!
     * @if jp
     * @brief �桼��������ؿ��ؤΥݥ���
     * @else
     * @brief User's initialization function's pointer
     * @endif
     */
    ModuleInitProc m_initProc;

    /*!
     * @if jp
     * @brief Manager �� configuration ���Ǽ���� Properties
     * @else
     * @brief Managaer's configuration Properties
     * @endif
     */
    Properties m_config;

    /*!
     * @if jp
     * @brief ModuleManager �ؤΥݥ���
     * @else
     * @brief The pointer to the ModuleManager
     * @endif
     */
    ModuleManager* m_module;
    
    /*!
     * @if jp
     * @brief ModuleManager �ؤΥݥ���
     * @else
     * @brief The pointer to the ModuleManager
     * @endif
     */
    NamingManager* m_namingManager;

    CorbaObjectManager* m_objManager;

    /*!
     * @if jp
     * @brief Timer Object
     * @else
     * @brief Timer Object
     * @endif
     */
    Timer* m_timer;


    //------------------------------------------------------------
    // Logger
    //------------------------------------------------------------
    /*!
     * @if jp
     * @brief �����Хåե�
     * @else
     * @brief Logger buffer
     * @endif
     */
    Logbuf m_Logbuf;

    /*!
     * @if jp
     * @brief �������Хåե�
     * @else
     * @brief Logger mediation buffer
     * @endif
     */
    MedLogbuf m_MedLogbuf;

    /*!
     * @if jp
     * @brief �������ȥ꡼��
     * @else
     * @brief Logger stream
     * @endif
     */
    LogStream rtcout;
    

    //============================================================
    // ����ݡ��ͥ�ȥޥ͡�����
    //============================================================
    // ObjectManager ���Ϥ��Ҹ쥯�饹
    struct InstanceName
    {
      InstanceName(RtcBase* comp) : m_name(comp->getInstanceName()) {};
      InstanceName(const char* name) : m_name(name) {};
      bool operator()(RtcBase* comp)
      {
	return m_name == comp->getInstanceName();
      }
      std::string m_name;
    };

    typedef ObjectManager<const char*,
			  RtcBase,
			  InstanceName> ComponentManager;
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȥޥ͡�����
     * @else
     * @brief The ComponentManager
     * @endif
     */
    ComponentManager m_compManager;


    //============================================================
    // ����ݡ��ͥ�ȥե����ȥ�
    //============================================================
    // ����ݡ��ͥ�ȥե����ȥ���Ϥ��Ҹ쥯�饹
    struct FactoryPredicate
    {
      FactoryPredicate(const char* name) : m_name(name){};
      FactoryPredicate(FactoryBase* factory)
	: m_name(factory->profile()["implementation_id"]) {};
      bool operator()(FactoryBase* factory)
      {
	return m_name == factory->profile()["implementation_id"];
      }
      std::string m_name;
    };
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȥե����ȥ�
     * @else
     * @brief The ComponentFactory
     * @endif
     */
    typedef ObjectManager<const char*,
			  FactoryBase,
			  FactoryPredicate> FactoryManager;
    /*!
     * @if jp
     * @brief ComponentManager
     * @else
     * @brief The ComponentManager
     * @endif
     */
    FactoryManager m_factory;

    //============================================================
    // ExecutionContext�ե����ȥ�
    //============================================================
    // EC�ե����ȥ���Ϥ��Ҹ쥯�饹
    struct ECFactoryPredicate
    {
      ECFactoryPredicate(const char* name) : m_name(name){};
      ECFactoryPredicate(ECFactoryBase* factory)
	: m_name(factory->name()) {};
      bool operator()(ECFactoryBase* factory)
      {
	return m_name == factory->name();
      }
      std::string m_name;
    };
    typedef ObjectManager<const char*,
			  ECFactoryBase,
			  ECFactoryPredicate> ECFactoryManager;
    ECFactoryManager m_ecfactory;
    std::vector<ExecutionContextBase*> m_ecs;


    // �ե����ȥ�̾��ꥹ�ȥ��åפ��뤿��Υե��󥯥�
    struct ModuleFactories
    {
      void operator()(FactoryBase* f)
      {
	modlist.push_back(f->profile().getProperty("implementation_id"));
      }
      std::vector<std::string> modlist;
    };


    //------------------------------------------------------------
    // ORB runner
    //------------------------------------------------------------
    class OrbRunner
      : public ACE_Task<ACE_MT_SYNCH>
    {
    public:
      OrbRunner(CORBA::ORB_ptr orb) : m_pORB(orb)
      {
	open(0);
      };
      virtual int open(void *args)
      {
	activate();
	return 0;
      }
      virtual int svc(void)
      {
	m_pORB->run();
	Manager::instance().shutdown();
	return 0;
      }
      virtual int close(unsigned long flags)
      {
	return 0;
      }
    private:
      CORBA::ORB_ptr m_pORB;
      
    };
    OrbRunner* m_runner;


    //------------------------------------------------------------
    // Manager Terminator
    //------------------------------------------------------------
    class Terminator
      : public ACE_Task<ACE_MT_SYNCH>
    {
    public:
      Terminator(Manager* manager) : m_manager(manager) {};
      void terminate()
      {
	open(0);
      }
      virtual int open(void *args)
      {
	activate();
	return 0;
      }
      virtual int svc(void)
      {
	Manager::instance().shutdown();
	return 0;
      }
      Manager* m_manager;
    };

    Terminator* m_terminator;

    struct Term
    {
      int waiting;
      ACE_Thread_Mutex mutex;
    };
    Term m_terminate;



  }; // class Manager
}; // namespace RTC

#endif // Manager_h
