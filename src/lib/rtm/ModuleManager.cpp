// -*- C++ -*-
/*!
 * @file ModuleManager.cpp
 * @brief Loadable modules manager class
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2010
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ModuleManager.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#include <rtm/RTC.h>

#include <coil/File.h>
#include <coil/Process.h>

// RTC includes
#include <rtm/Manager.h>
#include <rtm/ModuleManager.h>
#include <coil/stringutil.h>

namespace RTC
{
  
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  ModuleManager::ModuleManager(coil::Properties& prop)
    : rtclog("ModuleManager"), m_properties(prop)
  {
    m_configPath      = coil::split(prop[CONFIG_PATH], ",");
    for_each(m_configPath.begin(), m_configPath.end(), coil::eraseHeadBlank);
    m_loadPath        = coil::split(prop[MOD_LOADPTH], ",");
    for_each(m_loadPath.begin(), m_loadPath.end(), coil::eraseHeadBlank);
    m_absoluteAllowed = coil::toBool(prop[ALLOW_ABSPATH], "yes", "no", false);
    m_downloadAllowed = coil::toBool(prop[ALLOW_URL], "yes", "no", false);
    m_initFuncSuffix  = prop[INITFUNC_SFX];
    m_initFuncPrefix  = prop[INITFUNC_PFX];
  }
  
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
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
   * @brief Load the module
   * @endif
   */
  std::string ModuleManager::load(const std::string& file_name)
  {
    RTC_TRACE(("load(fname = %s)", file_name.c_str()));
    if (file_name == "") throw InvalidArguments("Invalid file name.");
    
    if (coil::isURL(file_name))
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
    if (coil::isAbsolutePath(file_name))
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
    
    DLLEntity* dll(new DLLEntity());
    
    int retval =  dll->dll.open(file_path.c_str());
    if (retval != 0)
      {
        delete dll;
	throw Error("DLL open failed.");
      }
    dll->properties["file_path"] = file_path;
    bool ret = m_modules.registerObject(dll);
    if (!ret) {
      delete dll;
    }
    
    return file_path;
  }
  
  /*!
   * @if jp
   * @brief �⥸�塼��Υ��ɡ������
   * @else
   * @brief Load and initialize the module
   * @endif
   */
  std::string ModuleManager::load(const std::string& file_name,
				  const std::string& init_func)
  {
    RTC_TRACE(("load(fname = %s, init_func = %s)",
               file_name.c_str(), init_func.c_str()));
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
   * @brief Unload the module
   * @endif
   */
  void ModuleManager::unload(const std::string& file_name)
  {
    DLLEntity* dll(m_modules.find(file_name.c_str()));
    if (dll == NULL)
      throw NotFound(file_name.c_str());
    
    dll->dll.close();
    m_modules.unregisterObject(file_name.c_str());
    
    if (dll != NULL) {
      delete dll;
    }
    
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
    std::vector<DLLEntity*> dlls(m_modules.getObjects());
    
    for (int i(0), len(dlls.size()); i < len; ++i)
      {
        std::string ident(dlls[i]->properties["file_path"]);
        DLLEntity* dll(m_modules.unregisterObject(ident.c_str()));
        dll->dll.close();
      }
    return;
  }
  
  /*!
   * @if jp
   * @brief �⥸�塼��Υ���ܥ�λ���
   * @else
   * @brief Refer to the symbol of the module
   * @endif
   */
  void* ModuleManager::symbol(const std::string& file_name,
			      const std::string& func_name)
    throw (ModuleNotFound, SymbolNotFound)
  {
    // "file_name" should be in modules map.
    DLLEntity* dll(m_modules.find(file_name.c_str()));
    if (dll == NULL)
      {
	throw ModuleNotFound(file_name);
      }
    
    void* func;
    func = dll->dll.symbol(func_name.c_str());
    
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
   * @brief Set the module load path
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
   * @brief Add the module load path
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
   * @brief Get the module list that has been loaded
   * @endif
   */
  std::vector<coil::Properties> ModuleManager::getLoadedModules()
  {
    std::vector< DLLEntity* > dlls(m_modules.getObjects());
    std::vector<coil::Properties> modules;
    for (int i(0), len(dlls.size()); i < len; ++i)
      {
        modules.push_back(dlls[i]->properties);
      }
    return modules;
  }
  
  /*!
   * @if jp
   * @brief ���ɲ�ǽ�ʥ⥸�塼��ꥹ�Ȥ��������(̤����)
   * @else
   * @brief Get the loadable module list(not implemented)
   * @endif
   */
  std::vector<coil::Properties> ModuleManager::getLoadableModules()
  {
    RTC_TRACE(("getLoadableModules()"));

    // getting loadable module file path list.
    coil::Properties& gprop(Manager::instance().getConfig());
    coil::vstring langs(coil::split(gprop["manager.supported_languages"], ","));
    RTC_DEBUG(("langs: %s", gprop["manager.supported_languages"].c_str()));

    // for each languages
    for (size_t l(0); l < langs.size(); ++l)
      {
        // 1. getting loadable files list
        coil::vstring modules;
        getModuleList(langs[l], modules);
        RTC_DEBUG(("%s: %s", langs[l].c_str(), coil::flatten(modules).c_str()));

        // 2. getting module properties from loadable modules
        vProperties tmpprops;
        getModuleProfiles(langs[l], modules, tmpprops);
        RTC_DEBUG(("Modile profile size: %d (newly founded modules)",
                   tmpprops.size()));
        m_modprofs.insert(m_modprofs.end(), tmpprops.begin(), tmpprops.end());
      }
    RTC_DEBUG(("Modile profile size: %d", m_modprofs.size()));
    // 3. removing module profiles for which module file does not exist
    removeInvalidModules();
    RTC_DEBUG(("Modile profile size: %d (invalid mod-profiles deleted)",
               m_modprofs.size()));
    return m_modprofs;
  }
  
  /*!
   * @if jp
   * @brief LoadPath ����Υե�����θ���
   * @else
   * @brief Search the file from the LoadPath
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
   * @brief Check whether the file exists
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
   * @brief Create initialization function symbol
   * @endif
   */
  std::string ModuleManager::getInitFuncName(const std::string& file_path)
  {
    std::string base_name(coil::basename(file_path.c_str()));
    
    return m_initFuncPrefix + base_name + m_initFuncSuffix;
  }


  /*!
   * @if jp
   * @brief ̵���ʥ⥸�塼��ץ�ե������������
   * @else
   * @brief Removing incalid module profiles
   * @endif
   */
  void ModuleManager::removeInvalidModules()
  {
    std::vector<coil::Properties>::iterator it(m_modprofs.begin());

    while (it < m_modprofs.end())
      {
        if (!fileExist((*it)["module_file_path"]))
          {
            it = m_modprofs.erase(it);
          }
        ++it;
      }
  }

  /*!
   * @if jp
   * @brief �������ˤ�������ɥѥ���Υ����֥�ʥե�����ꥹ�Ȥ��֤�
   * @else
   * @brief Getting loadable file list on the loadpath for given language
   * @endif
   */
  void ModuleManager::getModuleList(const std::string& lang,
                                    coil::vstring& modules)
  {
    std::string l = "manager.modules." + lang;
    coil::Properties& lprop(Manager::instance().getConfig().getNode(l));

    // load path: manager.modules.<lang>.load_path + manager.modules.load_path
    coil::vstring paths(coil::split(lprop["load_paths"], ","));
    paths.insert(paths.end(), m_loadPath.begin(), m_loadPath.end());

    coil::vstring suffixes(coil::split(lprop["suffixes"], ","));
    RTC_DEBUG(("suffixes: %s", coil::flatten(suffixes).c_str()));

    // for each load path list
    for (size_t i(0); i < paths.size(); ++i)
      {
        if (paths[i].empty())
          {
            RTC_WARN(("Given load path is empty"));
            continue;
          }
        std::string& path(paths[i]);
        RTC_DEBUG(("Module load path: %s", path.c_str()));

        // get file list for each suffixes
        coil::vstring flist;
        for (size_t s(0); s < suffixes.size(); ++s)
          {
            std::string glob("*."); glob += suffixes[s];
            coil::vstring tmp = coil::filelist(path.c_str(), glob.c_str());
            RTC_DEBUG(("File list (path:%s, ext:%s): %s", path.c_str(),
                       suffixes[s].c_str(), coil::flatten(tmp).c_str()));
            flist.insert(flist.end(), tmp.begin(), tmp.end());
          }
        
        // reformat file path and remove cached files
        for (size_t j(0); j < flist.size(); ++j)
          {
            if (*(path.end() - 1) != '/') { path += "/"; }
            std::string fpath(path + flist[j]);
            addNewFile(fpath, modules);
          }
      }
  }

  /*!
   * @if jp
   * @brief ����å����̵���ѥ�����modules���ɲä���
   * @else
   * @brief Adding file path not existing cache
   * @endif
   */
  void ModuleManager::addNewFile(const std::string& fpath,
                                 coil::vstring& modules)
  {
    bool exists(false);
    for (size_t k(0); k < m_modprofs.size(); ++k)
      {
        if (m_modprofs[k]["module_file_path"] == fpath)
          {
            exists = true;
            RTC_DEBUG(("Module %s already exists in cache.",
                       fpath.c_str()));
            break;
          }
      }
    if (!exists)
      {
        RTC_DEBUG(("New module: %s", fpath.c_str()));
        modules.push_back(fpath);
      }
  }

  /*!
   * @if jp
   * @brief ������졢�ե�����ꥹ�Ȥ���⥸�塼��Υץ�ѥƥ����֤�
   * @else
   * @brief Getting module properties from given language and file list
   * @endif
   */
  void ModuleManager::getModuleProfiles(const std::string& lang,
                                        const coil::vstring& modules,
                                        vProperties& modprops)
  {
    std::string l = "manager.modules." + lang;
    coil::Properties& lprop(Manager::instance().getConfig().getNode(l));
    std::vector<coil::Properties> prop;

    for (size_t i(0), len(modules.size()); i < len; ++i)
      {
        std::string cmd(lprop["profile_cmd"]);
        cmd += " \"" + modules[i] + "\"";
        FILE* fd;
        if ((fd = popen(cmd.c_str(), "r")) == NULL)
          {
            std::cerr << "popen faild" << std::endl;
            continue;
          }
        coil::Properties p;
        do
          {
            char str[512];
            fgets(str, 512, fd);
            std::string line(str);
            line.erase(line.size() - 1);
            std::string::size_type pos(line.find(":"));
            if (pos != std::string::npos)
              {
                std::string key(line.substr(0, pos));
                coil::eraseBothEndsBlank(key);
                p[key] = line.substr(pos + 1);
                coil::eraseBothEndsBlank(p[key]);
              }
          } while (!feof(fd));
        pclose(fd);
        RTC_DEBUG(("rtcprof cmd sub process done."));
        if (p["implementation_id"].empty()) { continue; }
        p["module_file_name"] = coil::basename(modules[i].c_str());
        p["module_file_path"] = modules[i].c_str();
        modprops.push_back(p);
      }
  }
}; // namespace RTC
