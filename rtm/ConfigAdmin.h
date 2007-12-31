// -*- C++ -*-
/*!
 * @file ConfigAdmin.h
 * @brief Configuration Administration classes
 * @date $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ConfigAdmin.h,v 1.3.2.1 2007-12-31 03:08:02 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/24 01:27:22  n-ando
 * Bug fix.
 *
 * Revision 1.2  2007/04/23 07:28:08  n-ando
 * Some functions were added.
 *
 * Revision 1.1  2007/04/23 04:51:21  n-ando
 * COnfiguration Admin class.
 *
 */

#ifndef ConfigAdmin_h
#define ConfigAdmin_h

#include <rtm/Properties.h>
#include <rtm/StringUtil.h>
#include <string>
#include <vector>
#include <iostream>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RT����ݡ��ͥ��
 *
 * @else
 *
 * @namespace RTC
 *
 * @endif
 */
namespace RTC
{
  //============================================================
  // ConfigBase class
  //============================================================
  /*!
   * @if jp
   * @class ConfigBase
   * @brief ConfigBase ��ݥ��饹
   * 
   * �Ƽ拾��ե�����졼����������ݻ����뤿�����ݥ��饹��
   * ��ݥ���ե�����졼����󥯥饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���
   * �Фʤ�ʤ���
   *
   * public���󥿡��ե������Ȥ��ưʲ��Τ�Τ��󶡤��롣
   * - update(): ����ե�����졼�����ѥ�᡼���ͤι���
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  class ConfigBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param name_ ����ե�����졼�����̾
     * @param def_val ʸ��������Υǥե������
     * 
     * @else
     *
     * @endif
     */
    ConfigBase(const char* name_, const char* def_val)
      : name(name_), default_value(def_val) {}
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     *
     * @else
     *
     * @endif
     */
    virtual ~ConfigBase(){};
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���͹����ѽ�貾�۴ؿ�
     * 
     * ����ե�����졼����������ͤǥ���ե�����졼�����ѥ�᡼���򹹿�����
     * ����ν�貾�۴ؿ���
     *
     * @param val �ѥ�᡼���ͤ�ʸ����ɽ��
     *
     * @return ������
     * 
     * @else
     *
     * @endif
     */
    virtual bool update(const char* val) = 0;
    
    /*!
     * @if jp
     * @brief  ����ե�����졼�����̾
     * @else
     * @endif
     */
    const char* name;
    
    /*!
     * @if jp
     * @brief  ʸ��������Υǥե������
     * @else
     * @endif
     */
    const char* default_value;
  };
  
  //============================================================
  // Config template class
  //============================================================
  /*!
   * @if jp
   * @class Config
   * @brief Config ���饹
   * 
   * ����ե�����졼�����ѥ�᡼���ξ�����ݻ����륯�饹��
   * \<VarType\>�Ȥ��ƥ���ե�����졼�����Υǡ���������ꤹ�롣
   * \<TransFunc\>�Ȥ������ꤵ�줿�ǡ�������ʸ������Ѵ������Ѵ��ؿ�����ꤹ�롣
   *
   * @param VarType ����ե�����졼�����ѥ�᡼����Ǽ���ѿ�
   * @param TransFunc ��Ǽ�����ǡ�������ʸ������Ѵ������Ѵ��ؿ�
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  template <typename VarType,
	    typename TransFunc = bool (*)(VarType&, const char*)>
  class Config
    : public ConfigBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param name ����ե�����졼�����ѥ�᡼��̾
     * @param var ����ե�����졼�����ѥ�᡼����Ǽ���ѿ�
     * @param def_val ʸ��������Υǥե������
     * @param trans ʸ��������Ѵ��ؿ�
     * 
     * @else
     *
     * @endif
     */
    Config(const char* name, VarType& var, const char* def_val,
	   TransFunc trans = stringTo)
      : ConfigBase(name, def_val), m_var(var), m_trans(trans)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     *
     * @else
     *
     * @endif
     */
    virtual ~Config(){}
    
    /*!
     * @if jp
     *
     * @brief �Х���ɥѥ�᡼���ͤ򹹿�
     * 
     * ����ե�����졼����������ͤǥ���ե�����졼�����ѥ�᡼���򹹿�����
     *
     * @param val �ѥ�᡼���ͤ�ʸ����ɽ��
     *
     * @return �����������(��������:true����������:false)
     * 
     * @else
     *
     * @endif
     */
    virtual bool update(const char* val)
    {
      if ((*m_trans)(m_var, val)) return true;
      (*m_trans)(m_var, default_value);
      return false;
    }
    
  protected:
    /*!
     * @if jp
     * @brief  ����ե�����졼�����ѥ�᡼����Ǽ���ѿ�
     * @else
     * @endif
     */
    VarType& m_var;
    
    /*!
     * @if jp
     * @brief  ����ե�����졼�����ѥ�᡼����ʸ�����Ѵ��ؿ�
     * @else
     * @endif
     */
    TransFunc m_trans;
  };
  
  //============================================================
  // ConfigAdmin class
  //============================================================
  /*!
   * @if jp
   * @class ConfigAdmin
   * @brief ConfigAdmin ���饹
   * 
   * �Ƽ拾��ե�����졼���������������륯�饹��
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  class ConfigAdmin
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param prop �����оݥץ�ѥƥ�̾
     * 
     * @else
     *
     * @endif
     */
    ConfigAdmin(RTC::Properties& prop);
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     *
     * @else
     *
     * @endif
     */
    ~ConfigAdmin();
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼��������
     * 
     * ����ե�����졼�����ѥ�᡼�����ѿ���Х���ɤ���
     * ���ꤷ��̾�ΤΥ���ե�����졼�����ѥ�᡼��������¸�ߤ������
     * false���֤���
     * \<VarType\>�Ȥ��ƥ���ե�����졼�����ѥ�᡼���Υǡ���������ꤹ�롣
     *
     * @param param_name ����ե�����졼�����ѥ�᡼��̾
     * @param var ����ե�����졼�����ѥ�᡼����Ǽ���ѿ�
     * @param def_val ����ե�����졼�����ѥ�᡼���ǥե������
     * @param trans ����ե�����졼�����ѥ�᡼��ʸ�����Ѵ��Ѵؿ�
     *
     * @return ������(��������:true�����꼺��:false)
     * 
     * @else
     *
     * @endif
     */
    template <typename VarType>
    bool bindParameter(const char* param_name, VarType& var,
		       const char* def_val,
		       bool (*trans)(VarType&, const char*) = ::stringTo)
    {
      if (isExist(param_name)) return false;
      if (!::stringTo(var, def_val)) return false;
      m_params.push_back(new Config<VarType>(param_name, var, def_val, trans));
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���ι���(ID����)
     * 
     * ���ꤷ��ID�Υ���ե�����졼����󥻥åȤ����ꤷ���ͤǡ�
     * ����ե�����졼�����ѥ�᡼�����ͤ򹹿�����
     * ���ꤷ��ID�Υ���ե�����졼����󥻥åȤ�¸�ߤ��ʤ����ϡ�
     * ���⤻���˽�λ���롣
     *
     * @param config_set �����оݤΥ���ե�����졼����󥻥å�ID
     * 
     * @else
     *
     * @endif
     */
    void update(const char* config_set);
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���ι���(̾�λ���)
     * 
     * ���ꤷ���ѥ��Υ���ե�����졼���������ꤷ���ͤǡ�
     * ����ե�����졼�����ѥ�᡼�����ͤ򹹿�����
     *
     * @param config_set ����ե�����졼�����̾�Ρ���.�����ڤ�ǺǸ�����Ǥ�
     *                   ������̾��
     * @param config_param ����ե�����졼����󥻥åȤκǸ������̾
     * 
     * @else
     *
     * @endif
     */
    void update(const char* config_set, const char* config_param);
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���ι���
     *        (�����ƥ��֥���ե�����졼����󥻥å�)
     * 
     * ����ե�����졼����󥻥åȤ���������Ƥ�����ˡ�
     * ���ߥ����ƥ��֤ˤʤäƤ��륳��ե�����졼���������ꤷ���ͤǡ�
     * ����ե�����졼�����ѥ�᡼�����ͤ򹹿����롣
     * ���ν����Ǥι����ϡ������ƥ��֤ȤʤäƤ��륳��ե�����졼����󥻥åȤ�
     * ¸�ߤ��Ƥ����硢����ι������饳��ե�����졼����󥻥åȤ����Ƥ�
     * ��������Ƥ�����Τ߼¹Ԥ���롣
     *
     * @else
     *
     * @endif
     */
    void update();
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼����¸�߳�ǧ
     * 
     * ���ꤷ��̾�Τ���ĥ���ե�����졼�����ѥ�᡼����¸�ߤ��뤫��ǧ���롣
     *
     * @param name ����ե�����졼�����ѥ�᡼��̾�Ρ�
     *
     * @return ¸�߳�ǧ���(�ѥ�᡼������:true���ѥ�᡼���ʤ�:false)
     *
     * @else
     *
     * @endif
     */
    bool isExist(const char* name);
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼�����ѹ���ǧ
     * 
     * ����ե�����졼�����ѥ�᡼�����ѹ����줿����ǧ���롣
     *
     * @return �ѹ���ǧ���(�ѹ�����:true���ѹ��ʤ�:false)
     *
     * @else
     *
     * @endif
     */
    bool isChanged() {return m_changed;}
    
    /*!
     * @if jp
     *
     * @brief �����ƥ��֡�����ե�����졼����󥻥å�ID�μ���
     * 
     * ���ߥ����ƥ��֤ʥ���ե�����졼����󥻥åȤ�ID��������롣
     *
     * @return �����ƥ��֡�����ե�����졼����󥻥å�ID
     *
     * @else
     *
     * @endif
     */
    const char* getActiveId() {return m_activeId.c_str();}
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼����󥻥åȤ�¸�߳�ǧ
     * 
     * ���ꤷ������ե�����졼����󥻥åȤ�¸�ߤ��뤫��ǧ���롣
     *
     * @param config_id ��ǧ�оݥ���ե�����졼����󥻥å�ID
     *
     * @return ¸�߳�ǧ���(���ꤷ��ConfigSet����:true���ʤ�:false)
     *
     * @else
     *
     * @endif
     */
    bool haveConfig(const char* config_id)
    {
      return (m_configsets.hasKey(config_id) == NULL) ? false : true;
    }
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼����󥻥åȤΥ����ƥ��ֲ���ǧ
     * 
     * ����ե�����졼����󥻥åȤ������ƥ��ֲ�����Ƥ��뤫��ǧ���롣
     *
     * @return ���ֳ�ǧ���(�����ƥ��־���:true���󥢥��ƥ��־���:false)
     *
     * @else
     *
     * @endif
     */
    bool isActive()
    {
      return m_active;
    }
    //    const std::vector<Properties*>* getConfigurationParameterValues();
    //    const Properties* getConfigurationParameterValue(const char* name);
    //    bool setConfigurationParameter(const char* name, const char* value);
    
    /*!
     * @if jp
     *
     * @brief ������ե�����졼����󥻥åȤμ���
     * 
     * ���ꤵ��Ƥ���������ե�����졼����󥻥åȤ�������롣
     *
     * @return ������ե�����졼����󥻥å�
     *
     * @else
     *
     * @endif
     */
    const std::vector<Properties*>& getConfigurationSets();
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ��ID�Υ���ե�����졼����󥻥åȤμ���
     * 
     * ID�ǻ��ꤷ������ե�����졼����󥻥åȤ�������롣
     * ���ꤷ������ե�����졼����󥻥åȤ�¸�ߤ��ʤ����ϡ�
     * ���Υ���ե�����졼����󥻥åȤ��֤���
     *
     * @param config_id �����оݥ���ե�����졼����󥻥åȤ�ID
     *
     * @return ����ե�����졼����󥻥å�
     *
     * @else
     *
     * @endif
     */
    const Properties& getConfigurationSet(const char* config_id);
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ���ץ�ѥƥ��Υ���ե�����졼����󥻥åȤؤ��ɲ�
     * 
     * ���ꤷ���ץ�ѥƥ���ID�ǻ��ꤷ������ե�����졼����󥻥åȤ��ɲä��롣
     * ���ꤷ��ID�Ȱ��פ��륳��ե�����졼����󥻥åȤ�¸�ߤ��ʤ����ϡ�
     * false ���֤���
     *
     * @param config_id �ɲ��оݥ���ե�����졼����󥻥åȤ�ID
     * @param configuration_set �ɲä���ץ�ѥƥ�
     *
     * @return �ɲý����¹Է��(�ɲ�����:true���ɲü���:false)
     *
     * @else
     *
     * @endif
     */
    bool setConfigurationSetValues(const char* config_id,
				   const RTC::Properties& configuration_set);
    
    /*!
     * @if jp
     *
     * @brief �����ƥ��֡�����ե�����졼����󥻥åȤ����
     * 
     * ���ߥ����ƥ��֤ȤʤäƤ��륳��ե�����졼����󥻥åȤ�������롣
     * �����ƥ��֤ȤʤäƤ��륳��ե�����졼����󥻥åȤ�¸�ߤ��ʤ����ϡ�
     * ���Υ���ե�����졼����󥻥å� ���֤���
     *
     * @return �����ƥ��֡�����ե�����졼����󥻥å�
     *
     * @else
     *
     * @endif
     */
    const Properties& getActiveConfigurationSet();
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼����󥻥åȤ������ͤ��ɲ�
     * 
     * ����ե�����졼����󥻥åȤ������ͤ��ɲä��롣
     *
     * @param configuration_set �ɲä���ץ�ѥƥ�
     *
     * @return �ɲý������(�ɲ�����:true���ɲü���:false)
     *
     * @else
     *
     * @endif
     */
    bool addConfigurationSet(const Properties& configuration_set);
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼����󥻥åȤκ��
     * 
     * ���ꤷ��ID�Υ���ե�����졼����󥻥åȤ������롣
     * ���ꤷ��ID�Υ���ե�����졼����󥻥åȤ�¸�ߤ��ʤ����ϡ�
     * false���֤���
     *
     * @param config_id ����оݥ���ե�����졼����󥻥åȤ�ID
     *
     * @return ����������(�������:true���������:false)
     *
     * @else
     *
     * @endif
     */
    bool removeConfigurationSet(const char* config_id);
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼����󥻥åȤΥ����ƥ��ֲ�
     * 
     * ���ꤷ��ID�Υ���ե�����졼����󥻥åȤ򥢥��ƥ��ֲ����롣
     * ���ꤷ��ID�Υ���ե�����졼����󥻥åȤ�¸�ߤ��ʤ����ϡ�
     * false���֤���
     *
     * @param config_id ����оݥ���ե�����졼����󥻥åȤ�ID
     *
     * @return �����ƥ��ֽ������(����:true������:false)
     *
     * @else
     *
     * @endif
     */
    bool activateConfigurationSet(const char* config_id);
    
  private:
    ConfigAdmin(const ConfigAdmin& ca) : m_configsets(ca.m_configsets) {};
    ConfigAdmin& operator=(const ConfigAdmin& ca){return *this;};
    
    struct find_conf
    {
      std::string m_name;
      find_conf(const char* name) : m_name(name) {};
      bool operator()(ConfigBase* conf)
      {
	return m_name == conf->name;
      }
    };

    RTC::Properties& m_configsets;
    RTC::Properties  m_emptyconf;
    std::vector<ConfigBase*> m_params;
    std::string m_activeId;
    bool m_active;
    bool m_changed;
    std::vector<std::string> m_newConfig;
  };
}; // namespace RTC
#endif // ConfigAdmin_h
