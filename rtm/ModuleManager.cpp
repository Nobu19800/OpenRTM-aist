// -*- C++ -*-
/*!
 * @file ModuleManager.cpp
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
 * $Id: ModuleManager.cpp,v 1.5.2.2 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5.2.1  2007/09/22 10:29:36  n-ando
 * The argument of the module init function was modified.
 *
 * Revision 1.5  2007/04/26 15:30:00  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.4  2007/04/13 18:02:58  n-ando
 * Some configuration properties handling processes were changed.
 *
 * Revision 1.3  2006/10/25 17:29:27  n-ando
 * Bug fix for configuration and load path strings including head blank.
 *
 * Revision 1.2  2006/10/17 10:06:39  n-ando
 * Now class ModuleManager is in RTC namespace.
 *
 * Revision 1.1  2006/09/20 08:47:25  n-ando
 * The first commit of module management class.
 *
 *
 */

#include <rtm/RTC.h>

#include <fstream>
#include <algorithm>
#include <iostream>

// ACE includes
#include <ace/ACE.h>

// RTC includes
#include <rtm/Manager.h>
#include <rtm/ModuleManager.h>
#include <rtm/StringUtil.h>

namespace RTC
{
  
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief constructor
   * @endif
   */
  ModuleManager::ModuleManager(Properties& prop)
    : m_properties(prop)
  {
    m_configPath      = split(prop[CONFIG_PATH], ",");
    for_each(m_configPath.begin(), m_configPath.end(), eraseHeadBlank);
    m_loadPath        = split(prop[MOD_LOADPTH], ",");
    for_each(m_loadPath.begin(), m_loadPath.end(), eraseHeadBlank);
    m_absoluteAllowed = toBool(prop[ALLOW_ABSPATH], "yes", "no", false);
    m_downloadAllowed = toBool(prop[ALLOW_URL], "yes", "no", false);
    m_initFuncSuffix  = prop[INITFUNC_SFX];
    m_initFuncPrefix  = prop[INITFUNC_PFX];
  }
  
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief destructor
   * @endif
   */
  ModuleManager::~ModuleManager()
  {
    unloadAll();
  }
  
  /*!
   * @if jp
   * @brief �⥸�塼��Υ���
   * @else
   * @brief Load module
   * @endif
   */
  std::string ModuleManager::load(const std::string& file_name)
  {
    if (file_name == "") throw InvalidArguments("Invalid file name.");
    
    if (isURL(file_name))
      {
	if (!m_downloadAllowed)
	  {
	    throw NotAllowedOperation("Downloading module is not allowed.");
	  }
	else
	  {
	    throw NotFound("Not implemented.");
	  }
      }
    
    // Find local file from load path or absolute directory
    std::string file_path;
    if (isAbsolutePath(file_name))
      {
	if (!m_absoluteAllowed)
	  {
	    throw NotAllowedOperation("Absolute path is not allowed");
	  }
	else
	  {
	    file_path = file_name;
	  }
      }
    else
      {
	file_path = findFile(file_name, m_loadPath);
      }
    
    // Now file_name is valid full path to module
    if (file_path == "") throw InvalidArguments("Invalid file name.");
    if (!fileExist(file_path)) throw FileNotFound(file_path.c_str());
    
    int retval =  m_modules[file_path].dll.open(file_path.c_str());
    if (retval != 0)
      {
	throw Error("DLL open failed.");
      }
    
    return file_path;
  }
  
  /*!
   * @if jp
   * @brief �⥸�塼��Υ��ɡ������
   * @else
   * @brief Load module
   * @endif
   */
  std::string ModuleManager::load(const std::string& file_name,
				  const std::string& init_func)
  {
    std::string name;
    name = load(file_name);
    
    if (name == "")
      {
	throw InvalidOperation("Invalid file name");
      }
    
    //  if (!init_func)
    
    ModuleInitFunc init;
    
    init = (ModuleInitFunc)this->symbol(name.c_str(), init_func);
    
    init(&(Manager::instance()));
    
    return name;
  }
  
  /*!
   * @if jp
   * @brief �⥸�塼��Υ������
   * @else
   * @brief Unload module
   * @endif
   */
  void ModuleManager::unload(const std::string& file_name)
  {
    if (m_modules.find(file_name) == m_modules.end())
      throw NotFound(file_name.c_str());
    
    m_modules[file_name].dll.close();
    m_modules.erase(file_name);
    
    return;
  }
  
  /*!
   * @if jp
   * @brief ���⥸�塼��Υ������
   * @else
   * @brief Unload all modules
   * @endif
   */
  void ModuleManager::unloadAll()
  {
    DllMapItr it(m_modules.begin());
    DllMapItr it_end(m_modules.end());
    
    // DLL close and clear DLL map
    while (it != it_end)
      {
	it->second.dll.close();
	++it;
      }
    m_modules.clear();
    
    return;
  }
  
  /*!
   * @if jp
   * @brief �⥸�塼��Υ���ܥ�λ���
   * @else
   * @brief Look up a named symbol in the module
   * @endif
   */
  void* ModuleManager::symbol(const std::string& file_name,
			      const std::string& func_name)
    throw (ModuleNotFound, SymbolNotFound)
  {
    // "file_name" should be in modules map.
    if (m_modules.find(file_name) == m_modules.end())
      {
	throw ModuleNotFound(file_name);
      }
    
    void* func;
    func = m_modules[file_name].dll.symbol(func_name.c_str());
    
    if (!func)
      {
	throw SymbolNotFound(func_name);
      }
    
    return func;
  }
  
  /*!
   * @if jp
   * @brief �⥸�塼����ɥѥ�����ꤹ��
   * @else
   * @brief Set default module load path
   * @endif
   */
  void ModuleManager::setLoadpath(const std::vector<std::string>& load_path)
  {
    m_loadPath = load_path;
    return;
  }
  
  /*!
   * @if jp
   * @brief �⥸�塼����ɥѥ����ɲä���
   * @else
   * @brief Add module load path
   * @endif
   */
  void ModuleManager::addLoadpath(const std::vector<std::string>& load_path)
  {
    StringVectorConstItr it(load_path.begin());
    StringVectorConstItr it_end(load_path.end());
    
    while (it != it_end)
      {
	m_loadPath.push_back(*it);
	++it;
      }
    
    return;
  }
  
  /*!
   * @if jp
   * @brief ���ɺѤߤΥ⥸�塼��ꥹ�Ȥ��������
   * @else
   * @brief Get loaded module names
   * @endif
   */
  std::vector<std::string> ModuleManager::getLoadedModules()
  {
    DllMapItr it(m_modules.begin());
    DllMapItr it_end(m_modules.end());
    
    StringVector modules;
    while (it != it_end)
      {
	modules.push_back(it->first);
	++it;
      }
    return modules;
  }
  
  /*!
   * @if jp
   * @brief ���ɲ�ǽ�ʥ⥸�塼��ꥹ�Ȥ��������(̤����)
   * @else
   * @brief Get loadable module names
   * @endif
   */
  std::vector<std::string> ModuleManager::getLoadableModules()
  {
    StringVector modules;
    
    return modules;
  }
  
  /*!
   * @if jp
   * @brief LoadPath ����Υե�����θ���
   * @else
   * @brief Search file from load path
   * @endif
   */
  std::string ModuleManager::findFile(const std::string& fname,
				      const std::vector<std::string>& load_path)
  {
    StringVectorConstItr it, it_end;
    std::string file_name(fname);
    
    it     = load_path.begin();
    it_end = load_path.end();
    
    while (it != it_end)
      {
	std::string f((*it) + "/" + file_name);
	if (fileExist(f))
	  {
	    return f;
	  }
	++it;
      }
    
    return std::string("");
  }
  
  /*!
   * @if jp
   * @brief �ե����뤬¸�ߤ��뤫�ɤ����Υ����å�
   * @else
   * @brief Check file existance
   * @endif
   */
  bool ModuleManager::fileExist(const std::string& filename)
  {
    std::ifstream infile;
    infile.open(filename.c_str(), std::ios::in);
    // fial() 0: ok, !0: fail
    if (infile.fail() != 0) 
      {
	infile.close();
	return false;
      }
    else
      {
	infile.close();
	return true;
      }
    
    return false;
  }
  
  /*!
   * @if jp
   * @brief ������ؿ�����ܥ����������
   * @else
   * @brief Create initialize function symbol
   * @endif
   */
  std::string ModuleManager::getInitFuncName(const std::string& file_path)
  {
    std::string base_name(ACE::basename(file_path.c_str()));
    
    return m_initFuncPrefix + base_name + m_initFuncSuffix;
  }
}; // namespace RTC
