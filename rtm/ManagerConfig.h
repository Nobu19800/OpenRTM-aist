// -*- C++ -*-
/*!
 * @file ManagerConfig.h
 * @brief RTC manager configuration
 * @date $Date: 2006-11-06 01:26:28 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ManagerConfig.h,v 1.3 2006-11-06 01:26:28 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/10/23 08:38:23  n-ando
 * To get Property after "init()" calling, getConfig() was added.
 *
 * Revision 1.1  2006/10/17 10:21:38  n-ando
 * The first commitment.
 *
 *
 */


#ifndef ManagerConfig_h
#define ManagerConfig_h

#include <rtm/Properties.h>


namespace RTC
{

  
  /*!
   * @if jp
   *
   * @class ManagerConfig
   * @brief Manager configuration ���饹
   *
   * Manager �Υ���ե�����졼������Ԥ������ޥ�ɥ饤������������ꡢ
   * (���뤤�ϰ����ʤ���)���󥹥��󥹲�����롣��Manager �Υץ�ѥƥ���������
   * ��Ԥ�
   *
   * ����(�ե�����)�λ���ζ����ϰʲ��ΤȤ���Ǥ��롣
   * �夬��äȤ⶯����������äȤ�夤��
   * <OL>
   * <LI>���ޥ�ɥ饤�󥪥ץ���� "-f"
   * <LI>�Ķ��ѿ� "RTC_MANAGER_CONFIG"
   * <LI>�ǥե��������ե����� "./rtc.conf"
   * <LI>�ǥե��������ե����� "/etc/rtc.conf"
   * <LI>�ǥե��������ե����� "/etc/rtc/rtc.conf"
   * <LI>�ǥե��������ե����� "/usr/local/etc/rtc.conf"
   * <LI>�ǥե��������ե����� "/usr/local/etc/rtc/rtc.conf"
   * <LI>�����ߥ���ե�����졼�������
   *</OL>
   * �����������ޥ�ɥ饤�󥪥ץ���� "-d" �����ꤵ�줿���ϡ�
   * (���Ȥ� -f ������ե��������ꤷ�Ƥ�)�����ߥ���ե�����졼�������
   * �����Ѥ���롣
   *
   * @else
   *
   * @brief
   *
   * @endif
   */
  class ManagerConfig
  {
  public:
    // The list of default configuration file path.
    static const char* config_file_path[];
    
    // Environment value to specify configuration file
    static const char* config_file_env;


    /*!
     * @if jp
     *
     * @brief ManagerConfig ���󥹥ȥ饯��
     *
     * ���⤷�ʤ����󥹥ȥ饯����
     *
     * @else
     *
     * @brief ManagerConfig constructor
     *
     * Do nothing. 
     *
     * @endif
     */
    ManagerConfig();


    /*!
     * @if jp
     *
     * @brief ManagerConfig ���󥹥ȥ饯��
     *
     * Ϳ����줿�����ˤ��������Ʊ���ˤ��륳�󥹥ȥ饯����
     *
     * @param argc ���ޥ�ɥ饤������ο�
     * @param argv ���ޥ�ɥ饤�����
     *
     * @else
     *
     * @brief ManagerConfig constructor
     *
     * The constructor that performs initialization at the same time with
     * given arguments.
     *
     * @param argc The number of command line arguments
     * @param argv The command line arguments
     *
     * @endif
     */
    ManagerConfig(int argc, char** argv);


    /*!
     * @if jp
     *
     * @brief ManagerConfig �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief ManagerConfig destructor
     *
     * @endif
     */
    virtual ~ManagerConfig();
    

    /*!
     * @if jp
     *
     * @brief �����
     *
     * �ǥե���ȥ������ѥ����饳��ե�����졼�����ե������õ�������
     * ��Ԥ��ȤȤ�˥ץ�ѥƥ����֤����������ѥ��˥���ե�����졼�����
     * �ե����뤬¸�ߤ��ʤ���硢�ǥե���ȤΥ���ե�����졼������
     * �֤���
     *
     * @return ��������줿 Property ��
     *
     * @else
     *
     * @brief Initialization
     *
     * This operation searches the configuration file from default search path,
     * and initialize and return default properties.
     * If there is no configuration file in the default search path,
     * default configuration statically defined is used.
     *
     * @return Initialized Property value.
     *
     * @endif
     */
    Properties init();


    /*!
     * @if jp
     *
     * @brief �����
     *
     * ���ޥ�ɥ饤�������Ϳ���ƽ�������롣���ޥ�ɥ饤�󥪥ץ�����
     * �ʲ��Τ�Τ����Ѳ�ǽ�Ǥ��롣
     *
     * -f file   : ����ե�����졼�����ե��������ꤹ�롣<br>
     * -l module : ���ɤ���⥸�塼�����ꤹ�롣<br>
     * -o options: ����¾���ץ�������ꤹ�롣��<br>
     * -d        : �ǥե���ȤΥ���ե�����졼������Ȥ���<br>
     *
     * @else
     *
     * @brief Initialization
     *
     * Initialize with command line options. The following command options
     * are available.
     *
     * -f file   : Specify a configuration file. <br>
     * -l module : Specify modules to be loaded at the beginning. <br>
     * -o options: Other options. <br>
     * -d        : Use default static configuration. <br>
     *
     * @endif
     */
    Properties init(int argc, char** argv);


    /*!
     * @if jp
     *
     * @brief ����ե�����졼�������������
     *
     * ����ե�����졼������������롣init()�ƤӽФ����˸Ƥ֤ȡ�
     * ��Ū��������줿�ǥե���ȤΥ���ե�����졼�������֤���
     * init() �ƤӽФ���˸Ƥ֤ȡ����ޥ�ɥ饤��������Ķ��ѿ�����
     * ��Ť�����������줿����ե�����졼�������֤���
     *
     * @else
     *
     * @brief Get configuration value.
     *
     * This operation returns default configuration statically defined,
     * when before calling init() function. When after calling init() function,
     * this operation returns initialized configuration value according to
     * command option, environment value and so on.
     *
     * @endif
     */
    Properties getConfig() const;

  protected:
    /*!
     * @if jp
     *
     * @brief ���ޥ�ɰ�����ѡ�������
     *
     * -f file   : ����ե�����졼�����ե��������ꤹ�롣<br>
     * -l module : ���ɤ���⥸�塼�����ꤹ�롣��<br>
     * -o options: ����¾���ץ�������ꤹ�롣��<br>
     * -d        : �ǥե���ȤΥ���ե�����졼������Ȥ���<br>
     *
     * @else
     *
     * @brief Parse command arguments
     *
     * -f file   : Specify a configuration file. <br>
     * -l module : Specify modules to be loaded at the beginning. <br>
     * -o options: Other options. <br>
     * -d        : Use default static configuration. <br>
     *
     * @endif
     */
    void parseArgs(int argc, char** argv);
    
    
    /*!
     * @if jp
     *
     * @brief Configuration file ��õ��
     *
     * Configuration file ��ͥ����
     *
     * ���ޥ�ɥ��ץ��������Ķ��ѿ���ǥե���ȥե������ǥե��������
     *
     * �ǥե���ȶ������ץ����(-d): �ǥե���ȥե����뤬���äƤ�̵�뤷��
     *                               �ǥե���������Ȥ�
     *
     *
     * @else
     *
     * @brief Find configuration file
     *
     * @endif
     */
    bool findConfigFile();

    
    /*!
     * @if jp
     *
     * @brief �����ƥ����򥻥åȤ���
     *
     * �����ƥ�����������ץ�ѥƥ��˥��åȤ��롣���ꤵ��륭���ϰʲ����̤ꡣ
     * manager.os.name    : OS̾
     * manager.os.release : OS��꡼��̾
     * maanger.os.version : OS�С������̾
     * manager.os.arch    : OS�������ƥ�����
     * manager.os.hostname: �ۥ���̾
     * manager.pid        : �ץ���ID
     * 
     * @else
     * 
     * @brief Set system information
     * 
     * Get the following system info and set them to Manager's properties.
     * manager.os.name    : OS name
     * manager.os.release : OS release name
     * maanger.os.version : OS version
     * manager.os.arch    : OS architecture
     * manager.os.hostname: Hostname
     * manager.pid        : process ID
     *
     * @endif
     */
    void setSystemInformation(Properties& prop);


    /*!
     * @if jp
     * @brief �ե����뤬¸�ߤ��뤫�ɤ����Τ����
     * @else
     * @brief Check file existance
     * @endif
     */
    bool fileExist(const std::string& filename);

    std::string m_configFile;
    Properties m_properties;
   
    
  };
  
}; // namespace RTC  
  
  
#endif // ManagerConfig_h
  
