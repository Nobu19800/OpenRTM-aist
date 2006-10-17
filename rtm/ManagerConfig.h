// -*- C++ -*-
/*!
 * @file ManagerConfig.h
 * @brief RTC manager configuration
 * @date $Date: 2006-10-17 10:21:38 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ManagerConfig.h,v 1.1 2006-10-17 10:21:38 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */


#ifndef ManagerConfig_h
#define ManagerConfig_h

#include <rtm/Properties.h>


namespace RTC
{
  // The list of default configuration file path.
  static const char* config_file_path[] = 
    {
      "./rtc.conf",
      "/etc/rtc.conf",
      "/etc/rtc/rtc.conf",
      "/usr/local/etc/rtc.conf",
      "/usr/local/etc/rtc/rtc.conf",
      NULL
    };
  
  // Environment value to specify configuration file
  static const char* config_file_env = "RTC_MANAGER_CONFIG";
  
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
    /*!
     * @if jp
     *
     * @brief ManagerConfig ���󥹥ȥ饯��
     *
     * @else
     *
     * @brief ManagerConfig constructor
     *
     * @endif
     */
    ManagerConfig();
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
     * @brief ManagerConfig �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief ManagerConfig destructor
     *
     * @endif
     */
    Properties init();
    Properties init(int argc, char** argv);

  protected:
    /*!
     * @if jp
     *
     * @brief ���ޥ�ɰ�����ѡ�������
     *
     * -f file   : ����ե�����졼�����ե��������ꤹ�롣
     * -l module : ���ɤ���⥸�塼�����ꤹ�롣
     * -o options: ����¾���ץ�������ꤹ�롣
     * -d        : �ǥե���ȤΥ���ե�����졼������Ȥ�
     *
     * @else
     *
     * @brief Parse command arguments
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
   
    
  };
  
}; // namespace RTC  
  
  
#endif // ManagerConfig_h
  
