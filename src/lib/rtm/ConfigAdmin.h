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
 * $Id$
 *
 */

#ifndef ConfigAdmin_h
#define ConfigAdmin_h

#include <coil/Properties.h>
#include <coil/stringutil.h>
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
 * @brief RT-Component
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
   * @class ConfigBase
   * @brief ConfigBase abstract class
   *
   * This is the abstract interface class to hold various configuration 
   * information.
   * Concrete configuration classes must implement the following pure virtual
   * functions.
   *
   * This class provides public interface as follows.
   * - update(): update configuration parameter value
   *
   * @since 0.4.0
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
     * @brief Constructer
     *
     * Constructer
     *
     * @param name_ Configuration name
     * @param def_val Default value in string format
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
     * @brief Virtual Destructor
     *
     * Virtual Destructor
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
     * @brief Pure virtual function to update configuration parameter values
     * 
     * Pure virtual function to update configuration parameter 
     * by the configuration value.
     *
     * @param val The parameter values converted into character string format
     *
     * @return Result of the setup
     *
     * @endif
     */
    virtual bool update(const char* val) = 0;
    
    /*!
     * @if jp
     * @brief  ����ե�����졼�����̾
     * @else
     * @brief  Configuration name
     * @endif
     */
    const char* name;
    
    /*!
     * @if jp
     * @brief  ʸ��������Υǥե������
     * @else
     * @brief  Default value in string format
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
   * @class Config
   * @brief Config class
   * 
   * Class to hold the configuration parameter information.
   * Specify the data type of the configuration as \<VarType\>
   * Specify transformation function to convert data type set as \<TransFunc\>
   * into string format.
   *
   * @param VarType Cariable to hold configuration parameter
   * @param TransFunc Transformation function to transform the stored data 
   * type into string format.
   *
   * @since 0.4.0
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
     * @brief Constructor
     * 
     * Constructor
     *
     * @param name Configuration parameter name
     * @param var Configuration parameter variable
     * @param def_val Default value in string format
     * @param trans Function to transform into string format
     *
     * @endif
     */
    Config(const char* name, VarType& var, const char* def_val,
	   TransFunc trans = coil::stringTo)
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
     * @brief Virtual Destructor
     * 
     * Virtual Destructor.
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
     * @brief Update a bind parameter value
     * 
     * Update configuration paramater by the configuration value.
     *
     * @param val The parameter values converted into character string format
     *
     * @return Update result (Successful:true, Failed:false)
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
     * @brief  Configuration parameter variable
     * @endif
     */
    VarType& m_var;
    
    /*!
     * @if jp
     * @brief  ����ե�����졼�����ѥ�᡼����ʸ�����Ѵ��ؿ�
     * @else
     * @brief  Transformation function to convert configuration parameter type 
     *         into string format.
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
   * @class ConfigAdmin
   * @brief ConfigAdmin class
   * 
   * Class to manage various configuration information.
   *
   * @since 0.4.0
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
     * @brief Constructor
     * 
     * Constructor
     *
     * @param prop The target property name for setup
     *
     * @endif
     */
    ConfigAdmin(coil::Properties& prop);
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     *
     * @else
     *
     * @brief Virtual Destructor
     * 
     * Virtual Destructor
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
     * @brief Setup for configuration parameters
     * 
     * Bind configuration parameter to its variable.
     * Return false, if configuration parameter of specified name has already 
     * existed.
     * Specify the data type of the configuration as \<VarType\>.
     *
     * @param param_name Configuration parameter name
     * @param var Configuration parameter variable
     * @param def_val Default value of configuration parameter
     * @param trans Function to transform configuration parameter type into 
     *        string format
     *
     * @return Setup result (Successful:true, Failed:false)
     *
     * @endif
     */
    template <typename VarType>
    bool bindParameter(const char* param_name, VarType& var,
		       const char* def_val,
		       bool (*trans)(VarType&, const char*) = coil::stringTo)
    {
      if (isExist(param_name)) return false;
      if (!coil::stringTo(var, def_val)) return false;
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
     * @brief Update configuration parameter (By ID)
     * 
     * Update comfiguration parameter value by the value that 
     * set to a configuration set of specified ID.
     * Exit without doing anthing if a configuration set of specified ID 
     * does not exist.
     *
     * @param config_set The target configuration set's ID to setup
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
     * @param config_set ����ե�����졼�����̾�Ρ���.�׶��ڤ�ǺǸ�����Ǥ�
     *                   ������̾��
     * @param config_param ����ե�����졼����󥻥åȤκǸ������̾
     * 
     * @else
     *
     * @brief Update the values of configuration parameters (By name)
     * 
     * Update the configuration value by the value that set to a configuration
     * set value of specified name.
     *
     * @param config_set configuration name. Name that each separates 
     *        by each comma(.) and excludes the last element.
     * @param config_param Last element name of configuration set
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
     * @brief Update the values of configuration parameters
     *        (Active configuration set)
     * 
     * When configuration set is updated, update the configuration parameter 
     * value to the value that is set to the current active configuration.
     * This update will be executed, only when an active configuration set 
     * exists and the content of the configuration set has been updated from 
     * the last update.
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
     * @brief Check the existence of configuration parameters
     * 
     * Check the existence of configuration parameters of specified name.
     *
     * @param name Configuration parameter name
     *
     * @return Result of existance confirmation 
     *         (Parameters exist:true, else:false)
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
     * @brief Confirm to change configuration parameters
     * 
     * Confirm that configuration parameters have changed.
     *
     * @return Result of change confirmation
     *         (There is a change:true��No change:false)
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
     * @brief Get ID of active configuration set
     * 
     * Get ID of the current active configuration set.
     *
     * @return The active configuration set ID
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
     * @brief Check the existence of configuration set
     * 
     * Check the existence of specified configuration set.
     *
     * @param config_id ID of target configuration set for confirmation
     *
     * @return Result of existence confirmation 
     *         (Specified ConfigSet exists:true, else:false)
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
     * @brief Confirm to activate configuration set
     * 
     * Confirm that configuration set has been activated.
     *
     * @return Result of state confirmation
     *         (Active state:true, Inactive state:false)
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
     * @brief Get all configuration sets
     * 
     * Get all specified configuration sets
     *
     * @return All configuration sets
     *
     * @endif
     */
    const std::vector<coil::Properties*>& getConfigurationSets();
    
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
     * @brief Get a configuration set by specified ID
     * 
     * Get a configuration set that was specified by ID
     * Return empty configuration set, if a configuration set of
     * specified ID doesn't exist.
     *
     * @param config_id ID of the target configuration set for getting
     *
     * @return The configuration set
     *
     * @endif
     */
    const coil::Properties& getConfigurationSet(const char* config_id);
    
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
     * @brief Add to configuration set from specified property
     * 
     * Add specified property to configuration set that was specified by ID.
     * Return false if configuration set, that matches specified ID, 
     * doesn't exist.
     *
     * @param config_id ID of the target configuration set for add
     * @param configuration_set Property to add
     *
     * @return Add result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool setConfigurationSetValues(const char* config_id,
				   const coil::Properties& configuration_set);
    
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
     * @brief Get the active configuration set
     * 
     * Get the current active configuration set.
     * Return empty configuration set, if an active configuration set 
     * doesn't exist.
     *
     * @return The active configuration set
     *
     * @endif
     */
    const coil::Properties& getActiveConfigurationSet();
    
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
     * @brief Add the configuration value to configuration set
     * 
     * Add the configuration value to configuration set
     *
     * @param configuration_set Property to add
     *
     * @return Add Result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool addConfigurationSet(const coil::Properties& configuration_set);
    
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
     * @brief Remove the configuration set
     * 
     * Remove the configuration set of specified ID
     * Return empty configuration set, if a configuration set of
     * specified ID doesn't exist.
     *
     * @param config_id ID of the target configuration set for remove
     *
     * @return Remove result (Successful:true, Failed:false)
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
     * @brief Activate the configuration set
     * 
     * Activate the configuration set of specified ID
     * Return empty configuration set, if a configuration set of
     * specified ID doesn't exist.
     *
     * @param config_id ID of the target configuration set for remove
     *
     * @return Activate result (Remove success:true��Remove failure:false)
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
    
    coil::Properties& m_configsets;
    coil::Properties  m_emptyconf;
    std::vector<ConfigBase*> m_params;
    std::string m_activeId;
    bool m_active;
    bool m_changed;
    std::vector<std::string> m_newConfig;
  };
}; // namespace RTC
#endif // ConfigAdmin_h
