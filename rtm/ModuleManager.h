// -*- C++ -*-
/*!
 * @file ModuleManager.h
 * @brief Loadable modules manager class
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ModuleManager.h,v 1.2.4.2 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2.4.1  2007/09/22 10:29:38  n-ando
 * The argument of the module init function was modified.
 *
 * Revision 1.2  2006/10/17 10:06:47  n-ando
 * Now class ModuleManager is in RTC namespace.
 *
 * Revision 1.1  2006/09/20 08:47:33  n-ando
 * The first commit of module management class.
 *
 *
 */

#ifndef ModuleManager_h
#define ModuleManager_h

// STL includes
#include <string>
#include <vector>
#include <map>

// ACE includes
#include <ace/DLL.h>

// RTC includes
#include <rtm/Manager.h>
#include <rtm/Properties.h>


#define CONFIG_EXT    "manager.modules.config_ext"
#define CONFIG_PATH   "manager.modules.config_path"
#define DETECT_MOD    "manager.modules.detect_loadable"
#define MOD_LOADPTH   "manager.modules.load_path"
#define INITFUNC_SFX  "manager.modules.init_func_suffix"
#define INITFUNC_PFX  "manager.modules.init_func_prefix"
#define ALLOW_ABSPATH "manager.modules.abs_path_allowed"
#define ALLOW_URL     "manager.modules.download_allowed"
#define MOD_DWNDIR    "manager.modules.download_dir"
#define MOD_DELMOD    "manager.modules.download_cleanup"
#define MOD_PRELOAD   "manager.modules.preload"

namespace RTC
{
  /*!
   * @if jp
   *
   * @brief �⥸�塼��ޥ͡����㥯�饹
   *
   * �⥸�塼��Υ��ɡ�������ɤʤɤ�������륯�饹
   *
   * @since 0.4.0
   *
   * @else
   *
   * @biref ModuleManager class
   *
   * @endif
   */
  class ModuleManager
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     * ���ꤵ�줿 Property ���֥���������ξ�����˽������¹Ԥ��롣
     *
     * @param prop ������ѥץ�ѥƥ�
     *
     * @else
     *
     * @brief constructor
     *
     * @endif
     */
    ModuleManager(Properties& prop);
    
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
    ~ModuleManager();
    
    /*!
     * @if jp
     * @brief �ե����롦�����ץ����㳰�����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct Error
    {
      Error(const std::string& _reason)
	: reason(_reason) {}
      std::string reason;
    };
    
    /*!
     * @if jp
     * @brief ̤������������⥸�塼�������㳰�����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct NotFound
    {
      NotFound(const std::string& _name)
	: name(_name) {}
      std::string name;
    };
    
    /*!
     * @if jp
     * @brief ����ե����������㳰�����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct FileNotFound
      : public NotFound
    {
      FileNotFound(const std::string& _name)
	: NotFound(_name) {}
    };
    
    /*!
     * @if jp
     * @brief ����⥸�塼�������㳰�����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct ModuleNotFound
      : public NotFound
    {
      ModuleNotFound(const std::string& _name)
	: NotFound(_name) {}
    };
    
    /*!
     * @if jp
     * @brief ���ꥷ��ܥ������㳰�����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct SymbolNotFound
      : public NotFound
    {
      SymbolNotFound(const std::string& _name)
	: NotFound(_name) {}
    };
    
    /*!
     * @if jp
     * @brief �������ػ߻��㳰�����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct NotAllowedOperation
      : public Error
    {
      NotAllowedOperation(const std::string& _reason)
	: Error(_reason) {}
    };
    
    /*!
     * @if jp
     * @brief ��������������㳰�����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct InvalidArguments
      : public Error
    {
      InvalidArguments(const std::string& _reason)
	: Error(_reason) {}
    };
    
    /*!
     * @if jp
     * @brief ��������������㳰�����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct InvalidOperation
      : public Error
    {
      InvalidOperation(const std::string& _reason)
	: Error(_reason) {}
    };
    typedef void (*ModuleInitFunc)(Manager*);
    
    /*!
     * @if jp
     *
     * @brief �⥸�塼��Υ���
     *
     * file_name ��DLL �⤷���϶�ͭ�饤�֥��Ȥ��ƥ��ɤ��롣
     * file_name �ϴ���Υ��ɥѥ� (manager.modules.load_path) ���Ф���
     * ���Хѥ��ǻ��ꤹ�롣
     *
     * Property manager.modules.abs_path_allowed �� yes �ξ�硢
     * ���ɤ���⥸�塼������Хѥ��ǻ��ꤹ�뤳�Ȥ��Ǥ��롣
     * Property manager.modules.download_allowed �� yes �ξ�硢
     * ���ɤ���⥸�塼���URL�ǻ��ꤹ�뤳�Ȥ��Ǥ��롣
     *
     * file_name �����Хѥ��ǻ��ꤹ�뤳�Ȥ��Ǥ��롣
     * manager.modules.allowAbsolutePath �� no �ξ�硢
     * ����Υ⥸�塼����ɥѥ����顢file_name �Υ⥸�塼���õ�����ɤ��롣
     * 
     * @param file_name �����оݥ⥸�塼��̾
     *
     * @return ���ꤷ�������оݥ⥸�塼��̾
     *
     * @else
     *
     * @brief Load module
     *
     *
     * @endif
     */
    std::string load(const std::string& file_name);
    
    /*!
     * @if jp
     *
     * @brief �⥸�塼��Υ��ɡ������
     *
     * ���ꤷ���ե������DLL �⤷���϶�ͭ�饤�֥��Ȥ��ƥ��ɤ���ȤȤ�ˡ�
     * ���ꤷ��������ѥ��ڥ졼������¹Ԥ��롣
     * 
     * @param file_name �����оݥ⥸�塼��̾
     * @param init_func ����������ѥ��ڥ졼�����
     *
     * @return ���ꤷ�������оݥ⥸�塼��̾
     *
     * @else
     *
     * @brief Load module
     *
     *
     * @endif
     */
    std::string load(const std::string& file_name, const std::string& init_func);
    
    /*!
     * @if jp
     * @brief �⥸�塼��Υ������
     *
     * ���ꤷ�����ɺѤߥ⥸�塼��򥯥�������������ɤ��롣
     *
     * @param file_name ��������оݥ⥸�塼��̾
     *
     * @else
     * @brief Unload module
     * @endif
     */
    void unload(const std::string& file_name);
    
    /*!
     * @if jp
     * @brief ���⥸�塼��Υ������
     *
     * ���ƤΥ��ɺѤߥ⥸�塼��򥢥���ɤ��롣
     *
     * @else
     * @brief Unload all modules
     * @endif
     */
    void unloadAll();
    
    /*!
     * @if jp
     * @brief �⥸�塼��Υ���ܥ�λ���
     * @else
     * @brief Look up a named symbol in the module
     * @endif
     */
    void* symbol(const std::string& file_name, const std::string& func_name)
      throw (ModuleNotFound, SymbolNotFound);
    
    /*!
     * @if jp
     * @brief �⥸�塼����ɥѥ�����ꤹ��
     * 
     * �⥸�塼����ɻ����оݥ⥸�塼��򸡺�����ѥ�����ꤹ�롣
     *
     * @param load_path �⥸�塼�븡���оݥѥ��ꥹ��
     *
     * @else
     * @brief Set default module load path
     * @endif
     */
    void setLoadpath(const std::vector<std::string>& load_path);
    
    /*!
     * @if jp
     * @brief �⥸�塼����ɥѥ����������
     * 
     * ���ꤵ��Ƥ���⥸�塼��򸡺��оݥѥ��ꥹ�Ȥ�������롣
     * 
     * @return load_path �⥸�塼�븡���оݥѥ��ꥹ��
     *
     * @else
     * @brief Get default module load path
     * @endif
     */
    inline std::vector<std::string> getLoadPath()
    {
      return m_loadPath;
    }
    
    /*!
     * @if jp
     * @brief �⥸�塼����ɥѥ����ɲä���
     * 
     * ���ꤵ�줿�ѥ��ꥹ�Ȥ򸡺��оݥѥ��ꥹ�Ȥ��ɲä��롣
     * 
     * @return load_path �ɲå⥸�塼�븡���оݥѥ��ꥹ��
     *
     * @else
     * @brief Add module load path
     * @endif
     */
    void addLoadpath(const std::vector<std::string>& load_path);
    
    /*!
     * @if jp
     * @brief ���ɺѤߤΥ⥸�塼��ꥹ�Ȥ��������
     *
     * ���˥��ɺѤߤΥ⥸�塼��ꥹ�Ȥ�������롣
     *
     * @return ���ɺѤߥ⥸�塼��ꥹ��
     *
     * @else
     * @brief Get loaded module names
     * @endif
     */
    std::vector<std::string> getLoadedModules();
    
    /*!
     * @if jp
     * @brief ���ɲ�ǽ�⥸�塼��ꥹ�Ȥ��������
     *
     * ���ɲ�ǽ�ʥ⥸�塼��Υꥹ�Ȥ�������롣
     * (̤����)
     *
     * @return ���ɲ�ǽ�⥸�塼��ꥹ��
     *
     * @else
     * @brief Get loadable module names
     * @endif
     */
    std::vector<std::string> getLoadableModules();
    
    /*!
     * @if jp
     * @brief �⥸�塼������Хѥ��������
     *
     * �����оݥ⥸�塼������Хѥ��������Ĥ���褦�����ꤹ�롣
     *
     * @else
     * @brief Allow absolute load path
     * @endif
     */
    inline void allowAbsolutePath()
    {
      m_absoluteAllowed = true;
    }
    
    /*!
     * @if jp
     * @brief �⥸�塼������Хѥ�����ػ�
     *
     * �����оݥ⥸�塼������Хѥ������ػߤ���褦�����ꤹ�롣
     *
     * @else
     * @brief Forbid absolute load path
     * @endif
     */
    inline void disallowAbsolutePath()
    {
      m_absoluteAllowed = false;
    }
    
    /*!
     * @if jp
     * @brief �⥸�塼���URL�������
     *
     * �����оݥ⥸�塼���URL�������Ĥ��롣
     * �����꤬���Ĥ���Ƥ����硢�⥸�塼����������ɤ��ƥ��ɤ��뤳�Ȥ�
     * ���Ĥ���롣
     *
     * @else
     * @brief Allow module download
     * @endif
     */
    inline void allowModuleDownload()
    {
      m_downloadAllowed = true;
    }
    
    /*!
     * @if jp
     * @brief �⥸�塼���URL����ػ�
     *
     * �����оݥ⥸�塼���URL�����ػߤ��롣
     *
     * @else
     * @brief Forbid module download
     * @endif
     */
    inline void disallowModuleDownload()
    {
      m_downloadAllowed = false;
    }
    
    /*!
     * @if jp
     * @brief LoadPath ����Υե�����θ���
     * 
     * ���ꤵ�줿�ѥ���ˡ����ꤵ�줿�ե����뤬¸�ߤ��뤫��ǧ���롣
     *
     * @param fname �����оݥե�����̾
     * @param load_path ������ѥ��ꥹ��
     *
     * @return �������줿�ե�����̾
     *
     * @else
     * @brief Search file from load path
     * @endif
     */
    std::string findFile(const std::string& fname,
			 const std::vector<std::string>& load_path);
    
    /*!
     * @if jp
     * @brief �ե����뤬¸�ߤ��뤫�ɤ����Υ����å�
     *
     * ���ꤵ�줿�ե����뤬¸�ߤ��뤫��ǧ���롣
     *
     * @param filename ¸�߳�ǧ�оݥե�����̾
     *
     * @return �ե�����¸�߳�ǧ���(�ե����뤢��:true���ʤ�:false)
     *
     * @else
     * @brief Check file existance
     * @endif
     */
    bool fileExist(const std::string& filename);
    
    /*!
     * @if jp
     * @brief ������ؿ�����ܥ����������
     *
     * ������ؿ���̾�Τ��Ȥ�Ω�Ƥ롣
     *
     * @param file_path ������оݥ⥸�塼��̾��
     *
     * @return ������ؿ�̾���Ȥ�Ω�Ʒ��
     *
     * @else
     * @brief Create initialize function symbol
     * @endif
     */
    std::string getInitFuncName(const std::string& file_path);
    
  protected:
    struct DLL
    {
      ACE_DLL dll;
    };
    
    typedef std::vector<std::string>     StringVector;
    typedef StringVector::iterator       StringVectorItr;
    typedef StringVector::const_iterator StringVectorConstItr;
    
    typedef std::map<std::string, DLL> DllMap;
    typedef DllMap::iterator           DllMapItr;
    typedef DllMap::const_iterator     DllMapConstItr;
    
    /*!
     * @if jp
     * @brief Module Manager �ץ�ѥƥ�
     * @else
     *
     * @endif
     */
    Properties& m_properties;
    
    /*!
     * @if jp
     * @brief ���ɺѤߥ⥸�塼��ꥹ��
     * @else
     *
     * @endif
     */
    DllMap m_modules;
    
    /*!
     * @if jp
     * @brief �⥸�塼�롦���ɡ��ѥ����ꥹ��
     * @else
     *
     * @endif
     */
    StringVector m_loadPath;
    /*!
     * @if jp
     * @brief ����ե�����졼����󡦥ѥ����ꥹ��
     * @else
     *
     * @endif
     */
    StringVector m_configPath;
    /*!
     * @if jp
     * @brief �⥸�塼��URL������ĥե饰
     * @else
     *
     * @endif
     */
    bool m_downloadAllowed;
    /*!
     * @if jp
     * @brief �⥸�塼�����Хѥ�������ĥե饰
     * @else
     *
     * @endif
     */
    bool m_absoluteAllowed;
    
    /*!
     * @if jp
     * @brief ����¹Դؿ����ե��å���
     * @else
     *
     * @endif
     */
    std::string m_initFuncSuffix;
    /*!
     * @if jp
     * @brief ����¹Դؿ��ץ�ե��å���
     * @else
     *
     * @endif
     */
    std::string m_initFuncPrefix;
    
  };   // class ModuleManager
};     // namespace RTC  

#endif // ModuleManager_h
