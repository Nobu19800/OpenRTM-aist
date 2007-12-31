// -*- C++ -*-
/*!
 * @file ManagerConfig.h
 * @brief RTC manager configuration
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ManagerConfig.h,v 1.4.2.1 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2007/04/13 18:02:28  n-ando
 * Some configuration properties handling processes were changed.
 *
 * Revision 1.3  2006/11/06 01:26:28  n-ando
 * Some trivial fixes.
 *
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
   * (���뤤�ϰ����ʤ���)���󥹥��󥹲�����롣
   * ���ޥ�ɥ饤������ǻ��ꤵ�줿����ե����롢�Ķ��ѿ��ʤɤ��� Manager ��
   * �ץ�ѥƥ���������ꤹ�롣
   *
   * �������ͥ���٤ϰʲ��ΤȤ���Ǥ��롣
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
   * @since 0.4.0
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
    /*!
     * @if jp
     * @brief Manager ����ե�����졼�����Υǥե���ȡ��ե����롦�ѥ�
     * @else
     * @endif
     */
    static const char* config_file_path[];
    
    // Environment value to specify configuration file
    /*!
     * @if jp
     * @brief �ǥե���ȡ�����ե�����졼�����Υե����롦�ѥ����̤���
     *        �Ķ��ѿ�
     * @else
     * @endif
     */
    static const char* config_file_env;
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����(���⤷�ʤ�)
     *
     * @else
     *
     * @brief constructor
     *
     * Do nothing. 
     *
     * @endif
     */
    ManagerConfig();
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * Ϳ����줿�����ˤ�ꥳ��ե�����졼��������ν������Ԥ���
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
     * @brief �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief destructor
     *
     * @endif
     */
    virtual ~ManagerConfig();
    
    /*!
     * @if jp
     *
     * @brief �����
     *
     * ���ޥ�ɥ饤������˱����ƽ������¹Ԥ��롣���ޥ�ɥ饤�󥪥ץ�����
     * �ʲ��Τ�Τ����Ѳ�ǽ�Ǥ��롣
     *
     * -f file   : ����ե�����졼�����ե��������ꤹ�롣<br>
     * -l module : ���ɤ���⥸�塼�����ꤹ�롣(̤����)<br>
     * -o options: ����¾���ץ�������ꤹ�롣(̤����)<br>
     * -d        : �ǥե���ȤΥ���ե�����졼������Ȥ���(̤����)<br>
     *
     * @param argc ���ޥ�ɥ饤������ο�
     * @param argv ���ޥ�ɥ饤�����
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
    void init(int argc, char** argv);
    
    /*!
     * @if jp
     * @brief Configuration ����� Property �����ꤹ��
     * 
     * Manager ��Configuration �������ꤵ�줿 Property �����ꤹ�롣
     *
     * @param prop Configuration �����о� Property
     * 
     * @else
     * @brief Apply configuration results to Property
     * @endif
     */
    void configure(Properties& prop);
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�������������
     *
     * ����ե�����졼������������롣init()�ƤӽФ����˸Ƥ֤ȡ�
     * ��Ū��������줿�ǥե���ȤΥ���ե�����졼�������֤���
     * init() �ƤӽФ���˸Ƥ֤ȡ����ޥ�ɥ饤��������Ķ��ѿ�����
     * ��Ť�����������줿����ե�����졼�������֤���
     * (̤����)
     *
     * @return Manager �Υ���ե�����졼��������
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
     * -l module : ���ɤ���⥸�塼�����ꤹ�롣(̤����)<br>
     * -o options: ����¾���ץ�������ꤹ�롣(̤����)<br>
     * -d        : �ǥե���ȤΥ���ե�����졼������Ȥ���(̤����)<br>
     *
     * @param argc ���ޥ�ɥ饤������ο�
     * @param argv ���ޥ�ɥ饤�����
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
     * @brief Configuration file �θ���
     *
     * Configuration file �򸡺��������ꤹ�롣
     * ���� Configuration file ������Ѥߤξ��ϡ��ե������¸�߳�ǧ��Ԥ���
     *
     * Configuration file ��ͥ����
     * ���ޥ�ɥ��ץ��������Ķ��ѿ���ǥե���ȥե������ǥե��������
     *
     * �ǥե���ȶ������ץ����(-d): �ǥե���ȥե����뤬���äƤ�̵�뤷��
     *                               �ǥե���������Ȥ�
     *
     * @return Configuration file �������
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
     * @brief �����ƥ��������ꤹ��
     *
     * �����ƥ�����������ץ�ѥƥ��˥��åȤ��롣���ꤵ��륭���ϰʲ����̤ꡣ
     * manager.os.name    : OS̾
     * manager.os.release : OS��꡼��̾
     * maanger.os.version : OS�С������̾
     * manager.os.arch    : OS�������ƥ�����
     * manager.os.hostname: �ۥ���̾
     * manager.pid        : �ץ���ID
     * 
     * @param prop �����ƥ��������ꤷ���ץ�ѥƥ�
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
     * @brief �ե������¸�߳�ǧ
     *
     * ���ꤵ�줿�ե����뤬¸�ߤ��뤫��ǧ���롣
     *
     * @param filename ��ǧ�оݥե�����̾��
     *
     * @return �оݥե������ǧ���(¸�ߤ������true)
     *
     * @else
     * @brief Check file existance
     * @endif
     */
    bool fileExist(const std::string& filename);
    
    /*!
     * @if jp
     * @brief Manager ����ե�����졼����󡦥ե�����Υѥ�
     * @else
     * @endif
     */
    std::string m_configFile;
  };
}; // namespace RTC  
#endif // ManagerConfig_h
