// -*- C++ -*-
/*!
 * @file RtcManager.h
 * @brief RTComponent manager class
 * @date $Date: 2005-05-16 06:19:56 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcManager.h,v 1.2 2005-05-16 06:19:56 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcManager_h
#define RtcManager_h


// CORBA includes
//#include <RTC.h>

// STL includes
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <fstream>

// ACE includes
#include <ace/DLL.h>
#include <ace/Signal.h>

// Boost includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// CORBA stub include
#include "rtm/idl/RTCManagerSkel.h"
#include "rtm/idl/RTCManagerStub.h"
#include "rtm/RtcModuleProfile.h"
#include "rtm/RtcBase.h"
#include "rtm/RtcFactory.h"
#include "rtm/RtcSystemLogger.h"

// RTM includes

namespace RTM
{
  
  // Use std:: namespace
  using namespace std;
  
  // Pre-declaration of classes
  
  class RtcManager;
  class RtcNaming;
  class RtcConfig;
  
#define RtcMgrCmd boost::function2<bool, vector<string>&, vector<string>& > 
  
  typedef void (*RtcModuleInitProc)(RtcManager* manager);  
  
  /*!
   * @if jp
   *
   * @class RtcManager
   *
   * @brief RTComponent �ޥ͡����㥯�饹
   *
   * RtcManager �ϥ���ݡ��ͥ�ȤΥ��ɡ��������˴��ʤɤΥ饤�ե�����������
   * ���롣�ޤ�����ݡ��ͥ�Ȥ��Ф��ƳƼ掠���ӥ����󶡤��롣
   *
   * @else
   *
   * @class RtcManager
   *
   * @brief RTComponent manager class.
   *
   * RtcManager manages life cycle of RTComponent for example, loading
   * component library, creating component, deleting component etc.
   * This manager also provide some services for RTComponents.
   *
   * @endif
   */
  class EXPORTS RtcManager :
    public virtual POA_RTM::RTCManager, 
							public virtual PortableServer::RefCountServantBase,
														   public ACE_Task<ACE_MT_SYNCH>
  {
	
  public:
	/*!
	 * @if jp
	 * @brief RtcManager ���饹���󥹥ȥ饯��
	 *
	 * �̾拾�ޥ�ɥ饤�����������Ȥ��ƤȤ롣
	 *
	 * @else
	 *
	 * @brief A constructor of Rtcmanager class.
	 *
	 * Usually constructor is given command line arguments.
	 *
	 * @endif
	 */
    RtcManager(int argc, char** argv);
	void shutdown();
	/*!
	 * @if jp
	 * @brief RtcManager ���饹�ǥ��ȥ饯��
	 * @else
	 * @brief A destructor of Rtcmanager class.
	 * @endif
	 */    
    virtual ~RtcManager();
	
	/*!
	 * @if jp
	 * @brief �ޥ͡����㥿�����򥹥����Ȥ�����
	 * @else
	 * @brief Start manager task.
	 * @endif
	 */    
	int open(void *args);
	
	/*!
	 * @if jp
	 * @brief �����ӥ��Υ���åɴؿ�
	 * @else
	 * @brief Thread function of service
	 * @endif
	 */    
	int svc(void);

	int close(unsigned long flags);
	
    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================
	
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] �⥸�塼��Υ���
	 *
	 * ����ݡ��ͥ�ȤΥ⥸�塼�����ɤ��ƽ�����ؿ���¹Ԥ��롣
	 *
	 * @param pathname ����ݡ��ͥ�ȥ⥸�塼��ե�����̾
	 * @param initfunc ������ؿ�̾
	 * 
	 * @else
	 * @brief [CORBA interface] Load module
	 *
     * Load shared library of a component by path name, and invoke initialize
	 * function.
	 *
	 * @param pathname Component module file name
	 * @param initfunc Initialize function name
	 *
	 * @endif
	 */  
    virtual RtmRes load(const char* pathname, const char* initfunc);
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] �⥸�塼��Υ������
	 *
	 * ����ݡ��ͥ�ȤΥ⥸�塼��򥢥���ɤ���
	 *
	 * @param pathnae ����ݡ��ͥ�ȥ⥸�塼��Υե�����̾
	 * 
	 * @else
	 * @brief [CORBA interface] Unload module
	 *
     * Unload shared library of a component module.
	 *
	 * @param pathname Component module file name
	 *
	 * @endif
	 */  
    virtual RtmRes unload(const char* pathname);
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] ����ݡ��ͥ�Ȥ�����
	 *
	 * ����ݡ��ͥ�ȤΥ��󥹥��󥹤���������
	 *
	 * @param comp_name ����ݡ��ͥ�ȥ⥸�塼��̾
	 * @param comp_name ���󥹥���̾ (����)
	 * 
	 * @else
	 * @brief [CORBA interface] Create component instance
	 *
     * Create component instance with component module name.
	 *
	 * @param comp_name Component module name
	 * @param comp_name Instance name (return value)
	 *
	 * @endif
	 */  
    virtual RTCBase_ptr create_component(const char* module_name,
										 const char* category_name,
										 CORBA::String_out instance_name);
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] ����ݡ��ͥ�Ȥκ��
	 *
	 * ����ݡ��ͥ�ȤΥ��󥹥��󥹤�������
	 *
	 * @param instance_name ���󥹥���̾
	 * @param category_name ���ƥ���̾
	 * 
	 * @else
	 * @brief [CORBA interface] Delete component instance
	 *
     * Delete component instance with instance name
	 *
	 * @param instance_name Instance name
	 * @param category_name Category name
	 *
	 * @endif
	 */  
    virtual RtmRes delete_component(const char* instance_name,
									const char* category_name);
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] ����ݡ��ͥ�� Factory �ꥹ�Ȥμ���
	 *
	 * ����ݡ��ͥ�� Factory �Υꥹ�Ȥ��������
	 *
	 * @else
	 * @brief [CORBA interface] Get component factory list
	 *
     * Get component factory list.
	 *
	 * @endif
	 */  
    virtual RTCFactoryList* factory_list();
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] ����ݡ��ͥ�ȥꥹ�Ȥμ���
	 *
	 * ����ݡ��ͥ�ȤΥꥹ�Ȥ��������
	 *
	 * @else
	 * @brief [CORBA interface] Get component list
	 *
     * Get component list.
	 *
	 * @endif
	 */  
    virtual RTCBaseList* component_list();
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] �ʰץ��󥿥ץ꥿
	 *
	 * �ޥ͡�����δʰץ��󥿥ץ꥿���ޥ�ɤμ¹�
	 *
	 * @else
	 * @brief [CORBA interface] Simple interpreter
	 *
     * Execute simple interpreter.
	 *
	 * @endif
	 */  
    virtual RtmRes command(const char* cmd, CORBA::String_out ret);
	
    // end of CORBA interface definition
    //============================================================
	
	
	
    //============================================================
    //
    // <<< Local interfaces >>>
    //
    //============================================================
	/*!
	 * @if jp
	 * @brief �ޥ͡�����ν����
	 *
	 * @else
	 * @brief Initialize manager
	 *
	 * @endif
	 */ 
    void initManager();
	
	/*!
	 * @if jp
	 * @brief �ޥ͡�����μ¹�
	 *
	 * @else
	 * @brief Run manager
	 *
	 * @endif
	 */ 
    void runManager();
	
	/*!
	 * @if jp
	 * @brief �ޥ͡�����μ¹�(��֥�å��⡼��)
	 *
	 * @else
	 * @brief Run manager (No blocking mode)
	 *
	 * @endif
	 */ 
    void runManagerNoBlocking();
	
	/*!
	 * @if jp
	 * @brief �ޥ͡����㥵���Х�ȤΥ����ƥ��ֲ�
	 *
	 * @else
	 * @brief Activate manager servant
	 *
	 * @endif
	 */ 
    bool activateManager();
	
	/*!
	 * @if jp
	 * @brief �⥸�塼�������롼����μ¹�
	 *
	 * @else
	 * @brief Invoke module initialize routine
	 *
	 * @endif
	 */ 
	void initModuleProc(RtcModuleInitProc proc);
	
	/*!
	 * @if jp
	 * @brief �ʰץ��󥿥ץ꥿���ޥ�ɤ���Ͽ
	 *
	 * @else
	 * @brief Register simple interpreter command function
	 *
	 * @endif
	 */ 
    bool createCommand(string cmd,
					   boost::function2<bool,
					   vector<string>&, vector<string>&>  func);
	
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥե����ȥ����Ͽ
	 *
	 * @else
	 * @brief Register component factory
	 *
	 * @endif
	 */ 
    bool registerComponent(RtcModuleProfile& profile,
						   RtcNewFunc new_func,
						   RtcDeleteFunc delete_func);
	
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥե����ȥ����Ͽ
	 *
	 * @else
	 * @brief Register component factory
	 *
	 * @endif
	 */ 
	bool registerComponent(RtcFactoryBase* factory);
	
	
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ������
	 *
	 * @else
	 * @brief Create component
	 *
	 * @endif
	 */ 
    RtcBase* createComponent(const string& module_name,
							 const string& category_name,
							 string& comp_name);
	
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ������
	 *
	 * @else
	 * @brief Create component
	 *
	 * @endif
	 */ 
    RtcBase* createComponent(const string& module_name,
							 const string& category_name);

	
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�Ⱥ���Τ���ν���
	 *
	 * @else
	 * @brief Creanup component
	 *
	 * @endif
	 */ 
    void cleanupComponent(const string& instance_name,
						  const string& category_name);
	
	
	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȸ���
	 *
	 * @else
	 * @brief find component
	 *
	 * @endif
	 */ 
    std::vector<RTCBase_ptr> findComponents(const string& comp_name);
	
	/*!
	 * @if jp
	 * @brief InPort �� OutPort ����³
	 *
	 * @else
	 * @brief Bind InPort with OutPort
	 *
	 * @endif
	 */ 
    std::string bindInOut(RTCBase_ptr comp_in,
						  const std::string& inp_name,
						  RTCBase_ptr comp_out,
						  const std::string& outp_name,
						  RTM::SubscriptionType sub_type = RTM::OPS_NEW);
	/*!
	 * @if jp
	 * @brief InPort �� OutPort ��̾���ˤ����³
	 *
	 * @else
	 * @brief Bind InPort with OutPort by name
	 *
	 * @endif
	 */ 
    std::string bindInOutByName(const std::string& comp_name_in,
								const std::string& inp_name,
								const std::string& comp_name_out,
								const std::string& outp_name,
								RTM::SubscriptionType sub_type = RTM::OPS_NEW);
	
	/*!
	 * @if jp
	 * @brief ORB �Υݥ��󥿤����
	 *
	 * @else
	 * @brief Get pointer to ORB
	 *
	 * @endif
	 */ 
    CORBA::ORB_var getORB();
	
	/*!
	 * @if jp
	 * @brief POA �Υݥ��󥿤����
	 *
	 * @else
	 * @brief Get pointer to POA
	 *
	 * @endif
	 */ 
    PortableServer::POA_var getPOA();

	RtcLogbuf& getLogbuf() {return m_Logbuf;}
	RtcConfig& getConfig() {return (*m_apConfig);}


	
    //============================================================
    // Commands
	
    bool loadCmd(const vector<string>& cmd, vector<string>& retval);
    bool unloadCmd(const vector<string>& cmd, vector<string>& retval);
    bool createComponentCmd(const vector<string>& cmd, vector<string>& retval);
    bool listComponent(const vector<string>& cmd, vector<string>& retval);
    bool listModule(const vector<string>& cmd, vector<string>& retval);
    bool commandListCmd(const vector<string>& cmd, vector<string>& retval);

  private:
    /*!
     * Initialize ORB and store ORB's reference
     */
    bool initORB();
	
    /*!
     * Initialize POA and POA manager
     */
    bool initPOA();

	bool initLogger();
	bool initMasterLogger();
	void loadMasterLogger();

	
    /*!
     * Find library path
     */
    bool findPath(string path, string &full_path);
	
    /*!
     * Make initialize function name from libname
     */
    bool libnameToInitFunc(const char* libname,
						   const char* initfunc,
						   string &initfunc_name);
	
	void shutdownAllComponents();
	
  private:
	/*!
	 * @if jp
	 * @brief RtcConfig �ؤΥݥ���
	 * @else
	 * @brief Pointer to RtcConfig
	 * @endif
	 */
    auto_ptr<RtcConfig> m_apConfig;
	
	/*!
	 * @if jp
	 * @brief RtcNaming �ؤΥݥ���
	 * @else
	 * @brief Pointer to RtcNaming
	 * @endif
	 */
    auto_ptr<RtcNaming> m_apNaming;
	
	/*!
	 * @if jp
	 * @brief ORB �ؤΥݥ���
	 * @else
	 * @brief Pointer to ORB
	 * @endif
	 */
    CORBA::ORB_var m_pORB;
	
	/*!
	 * @if jp
	 * @brief POA �ؤΥݥ���
	 * @else
	 * @brief Pointer to POA
	 * @endif
	 */
    PortableServer::POA_var m_pPOA;
	
	/*!
	 * @if jp
	 * @brief POAManager �ؤΥݥ���
	 * @else
	 * @brief Pointer to POAManager
	 * @endif
	 */
    PortableServer::POAManager_var m_pPOAManager;
	
  	/*!
	 * @if jp
	 * @brief �ʰץ��󥿥ץ꥿�Υ��ޥ�ɥޥå�
	 * @else
	 * @brief Command map for simple interpreter
	 * @endif
	 */
    map<string, boost::function2<bool, vector<string>&, vector<string>&> > m_CmdMap;
	
  	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ⥸�塼����ɥѥ�
	 * @else
	 * @brief Component module load path
	 * @endif
	 */
    list<string> m_LibraryLoadPath;
	
    //! Component factory and destructor map
	/*    struct Factory {
		  
	RtcModuleProfile _profile;
	RtcNewFunc _new;
	RtcDeleteFunc _delete;
	int _num;
    };
	*/
	
 	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥե����ȥ�ޥå׹�¤��
	 * @else
	 * @brief Component factory map
	 * @endif
	 */
	struct FactoryMap {
	  //! Mutex
      ACE_Thread_Mutex _mutex;
	  //! Moulde name <=> Factory
	  std::map<std::string, std::map<std::string, RtcFactoryBase*> > _map;
	};
	
 	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥե����ȥ�ޥå�
	 * @else
	 * @brief Component factory map
	 * @endif
	 */
	FactoryMap m_FactoryMap;
	
 	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ⥸�塼�빽¤��
	 * @else
	 * @brief Component module structre
	 * @endif
	 */
    struct DLL {
      int _refCount;
      ACE_DLL _dll;
    };
	
 	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ⥸�塼��ޥå�
	 * @else
	 * @brief Component module map
	 * @endif
	 */
    map<string, DLL> m_Lib; // Library name <=> DLL manager

	ACE_Sig_Action* m_SigAction;
	ACE_Sig_Action* m_SigHupAction;
	ACE_Sig_Action* m_SigIntAction;
	ACE_Sig_Action* m_SigKillAction;
	ACE_Sig_Action* m_SigSegvAction;
	ACE_Sig_Action* m_SigBusAction;

  public:
 	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ��󥹥��󥹥ǡ����١�����¤��
	 * @else
	 * @brief Component instance database
	 * @endif
	 */
    struct ComponentMap {
	  //! Mutex
      ACE_Thread_Mutex _mutex;
      std::map<string, std::map<string, RtcBase*> > _map;
    };
 	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ��󥹥��󥹥ǡ����١����ޥå�
	 *
	 * m_Components._map[_category_name_][_instance_name_]
	 *
	 * @else
	 * @brief Component instance database map
	 * @endif
	 */
    ComponentMap m_Components;
	
 	/*!
	 * @if jp
	 * @brief ����ݡ��ͥ�ȥ⥸�塼�������ؿ�
	 * @else
	 * @brief Component module initialization function
	 * @endif
	 */
    typedef bool (*RtcComponentInit)(RtcManager* manager);
	
 	/*!
	 * @if jp
	 * @brief �ޥ͡�����̾
	 * @else
	 * @brief Manager name
	 * @endif
	 */
    string m_ManagerName;

 	/*!
	 * @if jp
	 * @brief �����Хåե�
	 * @else
	 * @brief Logger buffer
	 * @endif
	 */
	RtcLogbuf m_Logbuf;
 	/*!
	 * @if jp
	 * @brief �������Хåե�
	 * @else
	 * @brief Logger mediation buffer
	 * @endif
	 */
	RtcMedLogbuf m_MedLogbuf;
 	/*!
	 * @if jp
	 * @brief �������ȥ꡼��
	 * @else
	 * @brief Logger stream
	 * @endif
	 */
	RtcLogStream rtcout;

	TimedString m_LoggerOut;
	typedef OutPortAny<TimedString> LogOutPort;
	LogOutPort* m_pLoggerOutPort;

	class LogEmitter
	  : public RtcSyncCallback
	{
	public:
	  LogEmitter(OutPortAny<TimedString>& port, TimedString& var)
		: m_OutPort(port), m_Var(var)
	  {
	  }
	  virtual int operator()(const char* s)
	  {
		m_Var.data = CORBA::string_dup(s);
		m_OutPort.write();
		return true;
	  }
	protected:
	  OutPortAny<TimedString>& m_OutPort;
	  TimedString& m_Var;
	};
	
	LogEmitter* m_pLogEmitter;
	RTCBase_var m_pMasterLogger; 	
  };


}; // end of namespace RTM

#endif // RtcManager_h
