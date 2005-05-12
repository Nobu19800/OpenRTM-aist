// -*- C++ -*-
/*!
 * @file RtcConfig.h
 * @brief RtcConfig class
 * @date $Date: 2005-05-12 09:06:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcConfig.h,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcConfig_h
#define RtcConfig_h

#include <string>
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include "rtm/RTC.h"


namespace RTM
{
  
  using namespace std;
  
#ifdef ORB_IS_OMNIORB
  static const char* config_map[][3] = 
	{{"IIOPAddrPort", "-ORBendPoint", "giop:tcp:"},
	 {"", "", ""},
	 {"NameServer", "-ORBInitRef", "NameService=corbaname::"},
	 {0,0,0}};
#endif // omniORB
  
#ifdef ORB_IS_MICO
  static const char* config_map[][3] = 
	{{"NameServer", "-ORBNamingAddr", ""},
	 {"IIOPAddrPort", "-ORBIIOPAddr", "inet:"},
	 {"", "", ""},
	 {0,0,0}};
#endif // MICO
  
  static const char* config_file_path[] = 
	{"./rtc.conf",
	 "/etc/rtc.conf",
	 "/etc/rtc/rtc.conf",
	 "/usr/local/etc/rtc.conf",
	 NULL};
  
  static const char* config_file_env = "RTC_CONFIG";

  /*!
   * @if jp
   *
   * @class RtcConfig
   *
   * @brief RtcManager ����ե�����졼����󥯥饹
   * 
   * ����ե�����졼�����ե�������ɤ߹��� RtcManager �Υ���ե�����졼��
   * ����Ԥ���
   *
   * @else
   *
   * @class RtcConfig
   *
   * @brief Rtcmanager configuration class
   *
   * Read configuration information from rtc.conf configuration file 
   * for RtcManager.
   *
   * @endif
   */
  class RtcConfig
  {
  public:
	/*!
	 * @if jp
	 *
	 * @brief RtcConfig ���饹���󥹥ȥ饯��
	 *
	 * RtcConfig ���饹�Υ��󥹥ȥ饯����
	 *
	 * @else
	 *
	 * @brief RtcConfig class constructor
	 *
	 * A constructor of RtcConfig.
	 *
	 * @endif
	 */
	RtcConfig(): m_DebugMode(false){};

	/*!
	 * @if jp
	 *
	 * @brief RtcConfig ���饹���󥹥ȥ饯��
	 *
	 * RtcConfig ���饹�Υ��󥹥ȥ饯����
	 *
	 * @param argc ���ޥ�ɥ饤������ο�
	 * @param argv ���ޥ�ɥ饤�����������
	 *
	 * @else
	 *
	 * @brief RtcConfig class constructor
	 *
	 * A constructor of RtcConfig.
	 *
	 * @param argc number of command line arguments
	 * @param argv sequence of command line arguments
	 *
	 * @endif
	 */
	RtcConfig(int argc, char** argv);

	/*!
	 * @if jp
	 *
	 * @brief RtcConfig ���饹�ǥ��ȥ饯��
	 *
	 * @else
	 *
	 * @brief RtcConfig class destructor
	 *
	 * @endif
	 */
	virtual ~RtcConfig();
	
	/*!
	 * @if jp
	 *
	 * @brief RtcConfig ���饹�ν����
	 *
	 * RtcConfig ���饹�򥳥ޥ�ɥ饤������ǽ��������
	 *
	 * @param argc ���ޥ�ɥ饤������ο�
	 * @param argv ���ޥ�ɥ饤�����������
	 *
	 * @else
	 *
	 * @brief Initialize RtcConfig class
	 *
	 * Initialize RtcConfig with command line arguments.
	 *
	 * @param argc number of command line arguments
	 * @param argv sequence of command line arguments
	 *
	 * @endif
	 */
	bool initConfig(int argc, char** argv);
	
	/*!
	 * @if jp
	 *
	 * @brief ORB_init() ���Ϥ��������������
	 *
	 * ����ե�����졼�����ե����뤫����������ե�����졼�����������
	 * ORB �ν������ɬ�פʾ���� ORB_init() ���Ϥ������Ȥ��Ƽ������롣
	 *
	 * @else
	 *
	 * @brief Get arguments to give ORB_init()
	 *
	 * Get configuration information to give to ORB_init() given by 
	 * configuration file as a sequence data.
	 *
	 * @endif
	 */
	char** getOrbInitArgv() const
	{
	  //	  for (int i = 0; i < m_Argc; i++) cerr << m_Argv[i] << endl;
	  return m_Argv;
	};
	
	/*!
	 * @if jp
	 *
	 * @brief ORB_init() ���Ϥ������ο����������
	 *
	 * ORB_init() ���Ϥ������ο���������롣
	 *
	 * @else
	 *
	 * @brief Get number of arguments to give ORB_init()
	 *
	 * Get number of argument to give ORB_init().
	 *
	 * @endif
	 */
	int getOrbInitArgc() const {return m_Argc;};
	
	/*!
	 * @if jp
	 *
	 * @brief �͡��ॵ����̾�����
	 *
	 * ����ե�����졼�����ե����뤫�������͡��ॵ����̾��������롣
	 *
	 * @else
	 *
	 * @brief Get name of CORBA name server
	 *
	 * Get name of CORBA name server gived by configuration file.
	 *
	 * @endif
	 */
	string getNameServer() const {return m_NameServer;};
	
	/*!
	 * @if jp
	 *
	 * @brief ����ݡ��ͥ�ȥ��ɥѥ������
	 *
	 * ����ե�����졼�����ե����뤫����������ݡ��ͥ�ȥ��ɥѥ���
	 * �������롣
	 *
	 * @else
	 *
	 * @brief Get component load path
	 *
	 * Get component load path gived by configuration file.
	 *
	 * @endif
	 */
	list<string>& getComponentLoadPath() {return m_ComponentLoadPath;};
	
	/*!
	 * @if jp
	 * @brief ���ߤμ¹ԥե�����̾�����
	 * @else
	 * @brief Get current executable name
	 * @endif
	 */
	string getBinName() const {return m_BinName;};
	
	/*!
	 * @if jp
	 * @brief ���ߤ�OS̾�����
	 * @else
	 * @brief Get current OS name
	 * @endif
	 */
	string getOSname() const {return m_OSname;};
	
	/*!
	 * @if jp
	 * @brief ���ߤ�host̾�����
	 * @else
	 * @brief Get current host name
	 * @endif
	 */
	string getHostname() const {return m_Hostname;};
	
	/*!
	 * @if jp
	 * @brief ���ߤ� OS release level �����
	 * @else
	 * @brief Get current OS release level
	 * @endif
	 */
	string getOSrelease() const {return m_OSrelease;};
	
	/*!
	 * @if jp
	 * @brief ���ߤ� OS version �����
	 * @else
	 * @brief Get current OS version
	 * @endif
	 */
	string getOSversion() const {return m_OSversion;};
	
	/*!
	 * @if jp
	 * @brief ���ߤ� machien architecture �����
	 * @else
	 * @brief Get current machine architecture
	 * @endif
	 */
	string getArch() const {return m_Arch;};
	
	/*!
	 * @if jp
	 * @brief ���ߤΥץ���ID�����
	 * @else
	 * @brief Get current process id
	 * @endif
	 */
	string getPid() const {return m_Pid;};

	string getLogFileName();
	string getErrorLogFileName();
	int getLogLevel();
	int getLogLock();
	std::string getLogTimeFormat();
	
  protected:
	/*!
	 * @if jp
	 * @brief ���ޥ�ɥ饤�������ѡ�������
	 * @else
	 * @brief Parse command line arguments
	 * @endif
	 */
	bool parseCommandArgs(int argc, char** argv);
	
	/*!
	 * @if jp
	 * @brief ����ե�����졼�����ե������ǥե���ȥѥ�����õ��
	 * @else
	 * @brief Find configuration file from default given path
	 * @endif
	 */
	bool findConfigFile();
	
	/*!
	 * @if jp
	 * @brief ����ե�����졼�����ե������ѡ�������
	 * @else
	 * @brief Parse configuration file
	 * @endif
	 */
	bool parseConfigFile();
	
	/*!
	 * @if jp
	 * @brief �����ƥ������������
	 * @else
	 * @brief Get system information
	 * @endif
	 */
	bool collectSysInfo();
	
	/*!
	 * @if jp
	 * @brief �إ�פ�ɽ������
	 * @else
	 * @brief Print usage
	 * @endif
	 */
	void printUsage(char* arg);
	
	/*!
	 * @if jp
	 * @brief �����������Ѵ�����
	 * @else
	 * @brief Convert command line argument from std::list to char**
	 * @endif
	 */
	void argsToArgv();

	/*!
	 * @if jp
	 * @brief �ե�����¸�ߥ����å�
	 * @else
	 * @brief Check file existance
	 * @endif
	 */
	bool fileExist(const char *filename);
	/*!
	 * @if jp
	 * @brief ʸ�����ʬ��
	 * @else
	 * @brief Split string with delimter
	 * @endif
	 */
	bool split(const string& input, const string& delimiter, list<string>& results);
  private:
	/*!
	 * @if jp
	 * @brief �¹ԥե�����̾
	 * @else
	 * @brief Current executable name
	 * @endif
	 */
	string m_BinName;
	string m_ArgConfigFile;
	string m_ConfigFile;
	map<string, string> m_Config;
	vector<string> m_Args;
	char** m_Argv;
	int m_Argc;
	string m_NameServer;
	std::list<string> m_ComponentLoadPath;
	string m_OSname;
	string m_Hostname;
	string m_OSrelease;
	string m_OSversion;
	string m_Arch;
	string m_Pid;
	bool m_DebugMode;
  };
  
}; // end of namespace RTM

#endif // end of __RtcConfig_h__
