// -*- C++ -*-
/*!
 * @file ModulesManager.h
 * @brief Loadable modules manager class
 * @date $Date: 2006-10-17 10:06:47 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ModuleManager.h,v 1.2 2006-10-17 10:06:47 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
   * @else
   *
   * @biref ModuleManager class
   *
   *
   * @endif
   */
  class ModuleManager
  {
  public:
    ModuleManager(Properties& prop);
    
    ~ModuleManager();
    
    struct Error
    {
      Error(const std::string& _reason)
	: reason(_reason) {}
      std::string reason;
    };
    
    struct NotFound
    {
      NotFound(const std::string& _name)
	: name(_name) {}
      std::string name;
    };
    
    struct FileNotFound
      : public NotFound
    {
      FileNotFound(const std::string& _name)
	: NotFound(_name) {}
    };
    
    struct ModuleNotFound
      : public NotFound
    {
      ModuleNotFound(const std::string& _name)
	: NotFound(_name) {}
    };
    
    struct SymbolNotFound
      : public NotFound
    {
      SymbolNotFound(const std::string& _name)
	: NotFound(_name) {}
    };
    
    struct NotAllowedOperation
      : public Error
    {
      NotAllowedOperation(const std::string& _reason)
	: Error(_reason) {}
    };
    
    struct InvalidArguments
      : public Error
    {
      InvalidArguments(const std::string& _reason)
	: Error(_reason) {}
    };
    
    struct InvalidOperation
      : public Error
    {
      InvalidOperation(const std::string& _reason)
	: Error(_reason) {}
    };
    typedef void (*ModuleInitFunc)(void);
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
     * @else
     *
     * @brief Load module
     *
     *
     * @endif
     */
    std::string load(const std::string& file_name);
    std::string load(const std::string& file_name, const std::string& init_func);
    
    /*!
     * @if jp
     * @brief �⥸�塼��Υ������
     * @else
     * @brief Unload module
     * @endif
     */
    void unload(const std::string& file_name);
    
    
    /*!
     * @if jp
     * @brief ���⥸�塼��Υ������
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
     * @else
     * @brief Set default module load path
     * @endif
     */
    void setLoadpath(const std::vector<std::string>& load_path);
    inline std::vector<std::string> getLoadPath()
    {
      return m_loadPath;
    }
    
    /*!
     * @if jp
     * @brief �⥸�塼����ɥѥ����ɲä���
     * @else
     * @brief Add module load path
     * @endif
     */
    void addLoadpath(const std::vector<std::string>& load_path);
    
    
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
    
    
    /*!
     * @if jp
     * @brief �⥸�塼������Хѥ��������
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
     * @brief �⥸�塼������Хѥ�����ػߤ���
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
     * @brief �⥸�塼��Υ�������ɤ����
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
     * @brief �⥸�塼��Υ�������ɤ�ػߤ���
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
     * @else
     * @brief Search file from load path
     * @endif
     */
    std::string findFile(const std::string& fname,
			 const std::vector<std::string>& load_path);
    
    
    /*!
     * @if jp
     * @brief �ե����뤬¸�ߤ��뤫�ɤ����Υ����å�
     * @else
     * @brief Check file existance
     * @endif
     */
    bool fileExist(const std::string& filename);
    
    
    /*!
     * @if jp
     * @brief ������ؿ�����ܥ����������
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
    
    Properties& m_properties;
    
    DllMap m_modules;
    
    StringVector m_loadPath;
    StringVector m_configPath;
    bool m_downloadAllowed;
    bool m_absoluteAllowed;
    
    std::string m_initFuncSuffix;
    std::string m_initFuncPrefix;
    
  };   // class ModuleManager
};     // namespace RTC  
  
#endif // ModuleManager_h
  
