// -*- C++ -*-
/*!
 * @file ModuleManager.h
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
 * $Id: ModuleManager.h 2077 2011-04-29 12:43:34Z n-ando $
 *
 */

#ifndef RTC_MODULEMANAGER_H
#define RTC_MODULEMANAGER_H

// STL includes
#include <string>
#include <vector>
#include <map>

// ACE includes
#include <coil/DynamicLib.h>

// RTC includes
#include <rtm/Manager.h>
#include <coil/Properties.h>
#include <rtm/ObjectManager.h>


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

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class ModuleManager
   * @brief �⥸�塼��ޥ͡����㥯�饹
   *
   * �⥸�塼��Υ��ɡ�������ɤʤɤ�������륯�饹
   *
   * @since 0.4.0
   *
   * @else
   * @class ModuleManager
   * @brief ModuleManager class
   *
   * This is a class to manage for loading and unloading modules.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ModuleManager
  {
    typedef std::vector<coil::Properties> vProperties;
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
     * @brief Constructor
     *
     * Constructor.
     * Initialize based on information in the set Property object.
     *
     * @param prop Properties for initialization
     *
     * @endif
     */
    ModuleManager(coil::Properties& prop);
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief Destructor
     *
     * @endif
     */
    ~ModuleManager(void);
    
    /*!
     * @if jp
     * @brief �ե����롦�����ץ����㳰�����ѹ�¤��
     * @else
     * @brief Structure for exception handling when file open is failed
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
     * @brief Structure for exception handling of unimplemented part
     *        and specified module missing
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
     * @brief Structure for exception handling when specified file
     *        cannot be found
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
     * @brief Structure for exception handling when specified module
     *        cannot be found
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
     * @brief Structure for exception handling when specified symbol
     *        cannot be found
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
     * @brief Structure for exception handling when specified
     *        operation cannot be allowed.
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
     * @brief Structure for exception handling when specified
     *        argument is invalid.
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
     * @brief Structure for exception handling when specified
     *        operation is invalid.
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
     * ���ɤ���⥸�塼������Хѥ��ǻ��ꤹ�뤳�Ȥ��Ǥ��롣<br>
     * Property manager.modules.download_allowed �� yes �ξ�硢
     * ���ɤ���⥸�塼���URL�ǻ��ꤹ�뤳�Ȥ��Ǥ��롣
     *
     * file_name �����Хѥ��ǻ��ꤹ�뤳�Ȥ��Ǥ��롣
     * manager.modules.abs_path_allowd �� no �ξ�硢
     * ����Υ⥸�塼����ɥѥ����顢file_name �Υ⥸�塼���õ�����ɤ��롣
     * 
     * @param file_name �����оݥ⥸�塼��̾
     *
     * @return ���ꤷ�������оݥ⥸�塼��̾
     *
     * @else
     *
     * @brief Load the module
     *
     * Load file_name as DLL or a shared liblary.
     * The file_name is specified by the relative path to default load
     * path (manager.modules.load_path).
     *
     * If Property manager.modules.abs_path_allowed is yes,
     * the load module can be specified by the absolute path.<br>
     * If Property manager.modules.download_allowed is yes,
     * the load module can be specified with URL.
     *
     * The file_name can be specified by the absolute path.
     * If manager.modules.abs_path_allowed is no, module of file_name
     * will be searched from the default module load path and loaded.
     * 
     * @param file_name The target module name for the loading
     *
     * @return Name of module for the specified load
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
     * @brief Load and intialize the module
     *
     * Load the specified file as DLL or a shared library, and execute operation
     * for specified initialization.
     * 
     * @param file_name The target module name for the loading
     * @param init_func Operation for initialization
     *
     * @return Name of module for the specified load
     *
     * @endif
     */
    std::string load(const std::string& file_name,
                     const std::string& init_func);
    
    /*!
     * @if jp
     * @brief �⥸�塼��Υ������
     *
     * ���ꤷ�����ɺѤߥ⥸�塼��򥯥�������������ɤ��롣
     *
     * @param file_name ��������оݥ⥸�塼��̾
     *
     * @else
     * @brief Unload the module
     *
     * Close and unload the specified module that has been loaded.
     *
     * @param file_name Name of module for the unloading
     *
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
     *
     * Unload all modules that have been loaded.
     *
     * @endif
     */
    void unloadAll();
    
    /*!
     * @if jp
     * @brief �⥸�塼��Υ���ܥ�λ���
     * @else
     * @brief Refer to the symbol of the module
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
     * @brief Set the module load path
     * 
     * Specify searching path to find the target module when loading module.
     *
     * @param load_path List of module search path
     *
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
     * @brief Get the module load path
     * 
     * Get the search path of the set module.
     * 
     * @return load_path List of module search path
     *
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
     * @brief Add the module load path
     * 
     * Add specified path list to search path list.
     * 
     * @return load_path List of additional module search path
     *
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
     * @brief Get the module list that has been loaded
     *
     * Get the module list that has been loaded.
     *
     * @return List of module that has been loaded
     *
     * @endif
     */
    std::vector<coil::Properties> getLoadedModules();
    
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
     * @brief Get the loadable module list
     *
     * Get the loadable module list (not implemented).
     *
     * @return Loadable module list
     *
     * @endif
     */
    std::vector<coil::Properties> getLoadableModules();

    /*!
     * @if jp
     * @brief �⥸�塼������Хѥ��������
     *
     * �����оݥ⥸�塼������Хѥ��������Ĥ���褦�����ꤹ�롣
     *
     * @else
     * @brief Allow absolute path when specify module path
     *
     * Set to allow the absolute path when specify the module for the load.
     *
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
     * @brief Disallow absolute path when specify module path
     *
     * Set to disallow the absolute path when specify the module for the load.
     *
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
     * @brief Allow URL when specify module path
     *
     * Allow URL when specify module for the load.
     * When this setup is allowed, downloading and loading the module will
     * be allowed.
     *
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
     * @brief Disallow URL when specify module path
     *
     * Disallow URL when specify module for the load.
     *
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
     * @brief Search the file from the LoadPath
     * 
     * Check whether the specified file exists in the specified path.
     *
     * @param fname Target file name of the search
     * @param load_path Path list for the search
     *
     * @return File name that was found
     *
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
     * @brief Check whether the file exists
     *
     * Check whether the specified file exists.
     *
     * @param filename Name of file existence for checking
     *
     * @return File existence result(File existence:true, Else:false)
     *
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
     * @brief Create initialization function symbol
     *
     * Assemble names of the initialization functions.
     *
     * @param file_path Name of module for initialization
     *
     * @return Assembly result of initialization function name
     *
     * @endif
     */
    std::string getInitFuncName(const std::string& file_path);
    
  protected:
    /*!
     * @if jp
     * @brief ̵���ʥ⥸�塼��ץ�ե������������
     * @else
     * @brief Removing incalid module profiles
     * @endif
     */
    void removeInvalidModules();
    
    /*!
     * @if jp
     * @brief �������ˤ�������ɥѥ���Υ����֥�ʥե�����ꥹ�Ȥ��֤�
     * @else
     * @brief Getting loadable file list on the loadpath for given language
     * @endif
     */
    void getModuleList(const std::string& lang, coil::vstring& modules);

    /*!
     * @if jp
     * @brief ����å����̵���ѥ�����modules���ɲä���
     * @else
     * @brief Adding file path not existing cache
     * @endif
     */
    void addNewFile(const std::string& fpath, coil::vstring& modules);

    /*!
     * @if jp
     * @brief ������졢�ե�����ꥹ�Ȥ���⥸�塼��Υץ�ѥƥ����֤�
     * @else
     * @brief Getting module properties from given language and file list
     * @endif
     */
    void getModuleProfiles(const std::string& lang,
                           const coil::vstring& modules, vProperties& modprops);

    /*!
     * @if jp
     * @brief �������ȥ꡼��
     * @else
     * @brief Logger stream
     * @endif
     */
    Logger rtclog;

    /*!
     * @if jp
     * @brief DLL�����ѹ�¤��
     * @else
     * @brief Structure for DLL management
     * @endif
     */
    struct DLLEntity
    {
      coil::Properties properties;
      coil::DynamicLib dll;
    };
    
    typedef std::vector<std::string>     StringVector;
    typedef StringVector::iterator       StringVectorItr;
    typedef StringVector::const_iterator StringVectorConstItr;
    
    typedef std::vector<DLLEntity>    DllMap;
    typedef DllMap::iterator           DllMapItr;
    typedef DllMap::const_iterator     DllMapConstItr;

    
    /*!
     * @if jp
     * @brief Module Manager �ץ�ѥƥ�
     * @else
     * @brief Module Manager properties
     * @endif
     */
    coil::Properties& m_properties;
    
    /*!
     * @if jp
     * @brief ���ɺѤߥ⥸�塼��ꥹ��
     * @else
     * @brief Module list that has already loaded
     * @endif
     */
    class DllPred
    {
      std::string m_filepath;
    public:
      DllPred(const char* filepath) : m_filepath(filepath) {}
      DllPred(const DLLEntity* dll) : m_filepath(dll->properties["file_path"]) {}
      bool operator()(DLLEntity* dllentity)
      {
        return m_filepath == dllentity->properties.getProperty("file_path");
      }
    };
    /*!
     * @if jp
     * @brief ���ɺѤߥ⥸�塼��ꥹ��
     * @else
     * @brief Module list that has already loaded
     * @endif
     */
    ObjectManager<const char*, DLLEntity, DllPred> m_modules;
    
    /*!
     * @if jp
     * @brief �⥸�塼�롦���ɡ��ѥ����ꥹ��
     * @else
     * @brief Module load path list
     * @endif
     */
    StringVector m_loadPath;
    /*!
     * @if jp
     * @brief ����ե�����졼����󡦥ѥ����ꥹ��
     * @else
     * @brief Configuration path list
     * @endif
     */
    StringVector m_configPath;
    /*!
     * @if jp
     * @brief �⥸�塼��URL������ĥե饰
     * @else
     * @brief Flag of URL when specify module for the load.
     * @endif
     */
    bool m_downloadAllowed;
    /*!
     * @if jp
     * @brief �⥸�塼�����Хѥ�������ĥե饰
     * @else
     * @brief Flag of absolute path when specify module for the load.
     * @endif
     */
    bool m_absoluteAllowed;
    
    /*!
     * @if jp
     * @brief ����¹Դؿ����ե��å���
     * @else
     * @brief Initial execution function suffix
     * @endif
     */
    std::string m_initFuncSuffix;

    /*!
     * @if jp
     * @brief ����¹Դؿ��ץ�ե��å���
     * @else
     * @brief Initial execution function prefix
     * @endif
     */
    std::string m_initFuncPrefix;

    /*!
     * @if jp
     * @brief �⥸�塼�륢����ɥե��󥯥�
     * @else
     * @brief Module unloading functor
     * @endif
     */
    class UnloadPred
    {
    public:
      UnloadPred(){}
      void operator()(DLLEntity* dll)
      {
        dll->dll.close();
        delete dll;
      }
    };

    vProperties m_modprofs;

  };   // class ModuleManager
};     // namespace RTC  

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_MODULEMANAGER_H
