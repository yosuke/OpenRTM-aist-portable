// -*- C++ -*-
/*!
 * @file ConfigAdmin.h
 * @brief Configuration Administration classes
 * @date $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2011
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ConfigAdmin.h 2237 2011-10-25 01:25:37Z n-ando $
 *
 */

#ifndef RTC_CONFIGADMIN_H
#define RTC_CONFIGADMIN_H

#include <string>
#include <vector>
#include <iostream>
#include <coil/Properties.h>
#include <coil/stringutil.h>
#include <rtm/ConfigurationListener.h>

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
  /*!
   * @if jp
   * @class OnUpdateCallback
   * @brief OnUpdate ������Хå���ݥ��饹
   *
   * @else
   * @class OnUpdateCallback
   * @brief Callback functor abstract for OnUpdate
   *
   * @endif
   */
  typedef ConfigurationSetNameListener OnUpdateCallback;

  /*!
   * @if jp
   * @class OnUpdateParamCallback
   * @brief OnUpdateParam ������Хå���ݥ��饹
   *
   * @else
   * @class OnUpdateParamCallback
   * @brief Callback functor abstract for OnUpdateParam
   *
   * @endif
   */
  typedef ConfigurationParamListener OnUpdateParamCallback;

  /*!
   * @if jp
   * @class OnSetConfigurationSetCallback
   * @brief OnSetConfigurationSet ������Хå���ݥ��饹
   *
   * @else
   * @class OnSetConfigurationSetCallback
   * @brief Callback functor abstract for OnSetConfigurationSet
   *
   * @endif
   */
  typedef ConfigurationSetListener OnSetConfigurationSetCallback;

  /*!
   * @if jp
   * @class OnAddConfigurationAddCallback
   * @brief OnAddConfigurationAdd ������Хå���ݥ��饹
   *
   * @else
   * @class OnAddConfigurationAddCallback
   * @brief callback functor abstract for OnAddConfigurationAdd
   *
   * @endif
   */
  typedef ConfigurationSetListener OnAddConfigurationAddCallback;

  /*!
   * @if jp
   * @class OnRemoveConfigurationSetCallback
   * @brief OnRemoveConfigurationSet ������Хå���ݥ��饹
   *
   * @else
   * @class OnRemoveConfigurationSetCallback
   * @brief Callback functor abstract for OnRemoveConfigurationSet
   *
   * @endif
   */
  typedef ConfigurationSetNameListener OnRemoveConfigurationSetCallback;

  /*!
   * @if jp
   * @class OnActivateSetCallback
   * @brief OnActivateSet ������Хå���ݥ��饹
   *
   * @else
   * @class OnActivateSetCallback
   * @brief Callback functor abstract for OnActivateSet
   *
   * @endif
   */
  typedef ConfigurationSetNameListener OnActivateSetCallback;

  // forward decl
  class ConfigAdmin;

  //============================================================
  // ConfigBase class
  //============================================================
  /*!
   * @if jp
   * @class ConfigBase
   * @brief ConfigBase ��ݥ��饹
   * 
   * �Ƽ拾��ե�����졼����������ݻ����뤿�����ݥ��饹����ݥ���
   * �ե�����졼����󥯥饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���
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
  struct ConfigBase
  {
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
      : name(name_), default_value(def_val),
        string_value(""), m_admin(NULL), m_callback(NULL)
    {}
    
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
    virtual ~ConfigBase(void){};

    // typedef of ConfigAdmin's member function
    typedef void (ConfigAdmin::*CallbackFunc)(const char*, const char*);

    /*!
     * @if jp
     *
     * @brief ������Хå��Υ��å�
     * 
     * �ѿ��ѹ����˥����뤵��륳����Хå��ؿ��򥻥åȤ���.
     *
     * @else
     *
     * @brief Setting callback
     *
     * This member function sets callback function which is called
     * when variable is changed.
     *
     * @endif
     */
    void setCallback(ConfigAdmin* cadmin, CallbackFunc cbf);

    /*!
     * @if jp
     *
     * @brief �ѿ��ѹ����Τ餻�륪�֥����дؿ�
     * 
     * �ѿ��ѹ����Τ餻�륪�֥����дؿ�.
     *
     * @else
     *
     * @brief Observer function to notify variable changed
     *
     * This function notifies variable has been changed.
     *
     * @endif
     */
    void notifyUpdate(const char* key, const char* val);
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���͹����ѽ�貾�۴ؿ�
     * 
     * ����ե�����졼����������ͤǥ���ե�����졼�����ѥ�᡼����
     * �������뤿��ν�貾�۴ؿ���
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

  protected:
    /*!
     * @if jp
     * @brief  ʸ��������θ�����
     * @else
     * @brief  Current value in string format
     * @endif
     */
    std::string string_value;
    /*!
     * @if jp
     * @brief  ConfigAdmin���֥������ȤؤΥݥ���
     * @else
     * @brief  A pointer to the ConfigAdmin object
     * @endif
     */
    ConfigAdmin* m_admin;
    /*!
     * @if jp
     * @brief  ������Хå��Υ��дؿ��ݥ���
     * @else
     * @brief  A member function pointer to the callback function.
     * @endif
     */
    CallbackFunc m_callback;
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
   * \<TransFunc\>�Ȥ������ꤵ�줿�ǡ�������ʸ������Ѵ������Ѵ��ؿ���
   * ���ꤹ�롣
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
    virtual ~Config(void){}
    
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
      if (string_value == val) { return true; }
      string_value = val;
      // value changed
      if ((*m_trans)(m_var, val))
        {
          notifyUpdate(name, val);
          return true;
        }
      (*m_trans)(m_var, default_value);
      notifyUpdate(name, val);
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
   * �Ѹ��ʲ��Τ褦��������롣
   *
   * - ����ե�����졼�����: ����ݡ��ͥ�Ȥ��������
   *
   * - (����ե�����졼�����)�ѥ�᡼���� key-value ����ʤ��������
   *   coil::Properties �ѿ��Ȥ��ư���졢key��value ����ʸ����Ȥ�����
   *   ������롣key �򥳥�ե�����졼�����ѥ�᡼��̾��value �򥳥�
   *   �ե�����졼�����ѥ�᡼���ͤȸƤ֡�
   *
   * - ����ե�����졼����󥻥åȡ� ����ե�����졼�����ѥ�᡼��
   *   �Υꥹ�Ȥǡ�̾�� (ID) �ˤ�äƶ��̤���롣ID�򥳥�ե�����졼����
   *   �󥻥å�ID�ȸƤ֡�
   *
   * - (����ե�����졼�����)�ѥ�᡼���ѿ�������ե�����졼������
   *   ��᡼����RTC�Υ����ƥ��ӥƥ���Ǽºݤ����Ѥ���ݤ˻��Ȥ������
   *   �����ѥ�᡼�����Ȥ˸�ͭ�η�����ġ�
   *
   * - �����ƥ���(����ե�����졼�����)���åȡ�����ͭ���ʥ���ե�����
   *   �졼����󥻥åȤΤ��ȤǤ��ꡢͣ���¸�ߤ��롣��§�Ȥ��ơ������ƥ�
   *   �֥���ե�����졼����󥻥åȤΥѥ�᡼��������ե�����졼����
   *   ��ѥ�᡼���ѿ���ȿ�Ǥ���롣
   *
   * ���Υ��饹�Ǥϡ�����ե�����졼�����Τ���ΰʲ���2�Ĥξ������
   * �����Ƥ��롣
   *
   * -# ����ե�����졼����󥻥åȤΥꥹ��
   * -# �ѥ�᡼���ѿ��Υꥹ��
   *
   * ����Ū�ˤϡ�(1) �Υ���ե�����졼����󥻥åȤΥꥹ�ȤΤ�����Ĥ�
   * (2) �Υѥ�᡼���ѿ���ȿ�Ǥ����롢�Τ��ܥ��饹����Ū�Ǥ��롣�̾
   * �ѥ�᡼���ѿ����ѹ����ϡ�����ե�����졼����󥻥åȤ��ѹ��ȥ�
   * ��᡼���ѿ��ؤ�ȿ�Ǥ�2�ʳ��ǹԤ��롣
   *
   * ����ե�����졼����󥻥åȤΥꥹ�Ȥ����ˤϡ��ʲ��δؿ����Ѥ��롣
   *
   * - getConfigurationSets()
   * - getConfigurationSet()
   * - setConfigurationSetValues()
   * - getActiveConfigurationSet()
   * - addConfigurationSet()
   * - removeConfigurationSet()
   * - activateConfigurationSet()
   *
   * �����δؿ��ˤ�ꡢ����ե�����졼����󥻥åȤ��ѹ����ɲá������
   * �����������ƥ��ֲ���Ԥ������������ˤ���ѹ����줿����ե�����
   * �졼����󥻥åȤ�RTC�Υ����ƥ��ӥƥ�������Ѥ���ѥ�᡼���ѿ�
   * ��ȿ�Ǥ�����ˤϡ��ʲ��� update() �ؿ����Ѥ��롣
   *
   * - update(void)
   * - update(const char* config_set)
   * - update(const char* config_set, const char* config_param)
   *
   * ����ե�����졼���������եå����뤿��˥�����Хå��ե��󥯥�
   * ��Ϳ���뤳�Ȥ��Ǥ��롣�եå��Ǥ������ϰʲ����̤ꡣ
   *
   * - ON_UPDATE                   : update() �������
   * - ON_UPDATE_PARAM             : update(param) �������
   * - ON_SET_CONFIGURATIONSET     : setConfigurationSet() �������
   * - ON_ADD_CONFIGURATIONSET     : addConfigurationSet() �������
   * - ON_REMOVE_CONFIGURATIONSET  : removeConfigurationSet() �������
   * - ON_ACTIVATE_CONFIGURATIONSET: activateConfigurationSet() �������
   *
   * @since 0.4.0
   *
   * @else
   * @class ConfigAdmin
   * @brief ConfigAdmin class
   * 
   * Class to manage various configuration information.
   * Now terms for this class are defined as follows.
   *
   * - Configurations: The configuration information for the RTCs.
   *
   * - (Configuration) parameters: Configuration information that
   *   consists of a key-value pair. The "key" and the "value" are
   *   both stored as character string values in a coil::Properties
   *   variable in this class. The "key" is called the "configuration
   *   parameter name", and the "value" is called the "configuration
   *   parameter value".
   *
   * - Configuration-sets: This is a list of configuration parameters,
   *   and it is distinguished by name (ID). The ID is called
   *   configuration-set ID.
   *
   * - (Configuration) parameter variables: The variables to be
   *   referred when configuration parameters are actually used within
   *   the activity of an RTC. Each variable has each type.
   *
   * - Active (configuration) set: This is the only configuration-set
   *   that is currently active. The parameter values of the active
   *    configuration-set are substituted into configuration variables
   *   in principle.
   *
   * The following two configuration informations are stored in this class.
   *
   * -# A list of configuration-set
   * -# A list of configuration parameter variables
   *
   * Basically, the purpose of this class is to set one of the
   * configuration-set in the list of (1) into parameter variables of
   * (2). Usually, configuration parameter variables manipulation is
   * performed with two-phases of configuration-set setting and
   * parameter variables setting.
   *
   * The configuration-set manipulations are performed by the
   * following functions.
   *
   * - getConfigurationSets()
   * - getConfigurationSet()
   * - setConfigurationSetValues()
   * - getActiveConfigurationSet()
   * - addConfigurationSet()
   * - removeConfigurationSet()
   * - activateConfigurationSet()
   *
   * Modification, addition, deletion, acquisition and activation of
   * configuration-set are performed by these functions. In order to
   * reflect configuration-set, which is manipulated by these
   * functions, on parameter variables that are used from RTC
   * activities, the following update() functions are used .
   *
   * - update(void)
   * - update(const char* config_set)
   * - update(const char* config_set, const char* config_param)
   *
   * Callback functors can be given to hook configuration
   * operation. Operations to be hooked are as follows.
   *
   * - ON_UPDATE                   : when update() is called
   * - ON_UPDATE_PARAM             : when update(param) is called
   * - ON_SET_CONFIGURATIONSET     : when setConfigurationSet() is called
   * - ON_ADD_CONFIGURATIONSET     : when addConfigurationSet() is called
   * - ON_REMOVE_CONFIGURATIONSET  : when removeConfigurationSet() is called
   * - ON_ACTIVATE_CONFIGURATIONSET: when activateConfigurationSet() is called
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
    ~ConfigAdmin(void);
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼��������
     * 
     * ����ե�����졼�����ѥ�᡼�����ѿ���Х���ɤ���
     * ���ꤷ��̾�ΤΥ���ե�����졼�����ѥ�᡼��������¸�ߤ������
     * false���֤���
     * \<VarType\>�Ȥ��ƥ���ե�����졼�����ѥ�᡼���Υǡ���������ꤹ�롣
     * �ʤ������Υ��дؿ����ƤФ줿�塢���ߥ����ƥ��֤ʥ���ե�����졼
     * ����󥻥åȤ��ͤ��ѿ��˥��åȤ���롣
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
     * After calling this function, configuration variable would be
     * updated by the active configuration parameter.
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
      if (param_name == 0) { return false; }
      if (def_val == 0) { return false; }
      if (isExist(param_name)) { return false; }
      if (!trans(var, def_val)) { return false; }
      Config<VarType>* c = new Config<VarType>(param_name, var, def_val, trans);
      m_params.push_back(c);
      c->setCallback(this, &RTC::ConfigAdmin::onUpdateParam);
      update(getActiveId(), param_name);
      return true;
    }

    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���β��
     * 
     * ����ե�����졼�����ѥ�᡼�����ѿ��ΥХ���ɤ������롣
     * ���ꤷ��̾�ΤΥ���ե�����졼�����ѥ�᡼����¸�ߤ��ʤ�����
     * false���֤���
     *
     * @param param_name ����ե�����졼�����ѥ�᡼��̾
     * @return ������(��������:true�����꼺��:false)
     * 
     * @else
     *
     * @brief Unbinding configuration parameters
     * 
     * Unbind configuration parameter from its variable. It returns
     * false, if configuration parameter of specified name has already
     * existed.
     *
     * @param param_name Configuration parameter name
     * @return Setup result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool unbindParameter(const char* param_name);
        
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���ι���
     *        (�����ƥ��֥���ե�����졼����󥻥å�)
     * 
     * ����ե�����졼����󥻥åȤ���������Ƥ�����ˡ����ߥ����ƥ�
     * �֤ˤʤäƤ��륳��ե�����졼���������ꤷ���ͤǡ�����ե�����
     * �졼�����ѥ�᡼�����ͤ򹹿����롣���ν����Ǥι����ϡ������ƥ�
     * �֤ȤʤäƤ��륳��ե�����졼����󥻥åȤ�¸�ߤ��Ƥ����硢��
     * ��ι������饳��ե�����졼����󥻥åȤ����Ƥ���������Ƥ����
     * ��Τ߼¹Ԥ���롣
     *
     * @else
     *
     * @brief Update the values of configuration parameters
     *        (Active configuration set)
     * 
     * When configuration set is updated, update the configuration
     * parameter value to the value that is set to the current active
     * configuration.  This update will be executed, only when an
     * active configuration set exists and the content of the
     * configuration set has been updated from the last update.
     *
     * @endif
     */
    void update(void);

    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���ι���(ID����)
     * 
     * ����ե�����졼������ѿ����ͤ򡢻��ꤷ��ID����ĥ���ե�����졼
     * ����󥻥åȤ��ͤǹ������롣����ˤ�ꡢ�����ƥ��֤ʥ���ե�����
     * �졼����󥻥åȤ��ѹ�����ʤ����������äơ������ƥ��֥���ե�����
     * �졼����󥻥åȤȥѥ�᡼���ѿ��δ֤�̷�⤬ȯ�������ǽ��������
     * �Τ���դ�ɬ�פǤ��롣
     *
     * ���ꤷ��ID�Υ���ե�����졼����󥻥åȤ�¸�ߤ��ʤ����ϡ�����
     * �����˽�λ���롣
     *
     * @param config_set �����оݤΥ���ե�����졼����󥻥å�ID
     * 
     * @else
     *
     * @brief Update configuration parameter (By ID)
     * 
     * This operation updates configuration variables by the
     * configuration-set with specified ID. This operation does not
     * change current active configuration-set. Since this operation
     * causes inconsistency between current active configuration set
     * and actual values of configuration variables, user should
     * carefully use it.
     *
     * This operation ends without doing anything, if the
     * configuration-set does not exist.
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
     * ����Υ���ե�����졼������ѿ����ͤ򡢻��ꤷ��ID����ĥ���ե�
     * ����졼����󥻥åȤ��ͤǹ������롣����ˤ�ꡢ�����ƥ��֤ʥ���
     * �ե�����졼����󥻥åȤ��ѹ�����ʤ����������äơ������ƥ��֥�
     * ��ե�����졼����󥻥åȤȥѥ�᡼���ѿ��δ֤�̷�⤬ȯ�������
     * ǽ��������Τ���դ�ɬ�פǤ��롣
     *
     * ���ꤷ��ID�Υ���ե�����졼����󥻥åȤ䡢���ꤷ��̾�ΤΥѥ�᡼
     * ����¸�ߤ��ʤ����ϡ����⤻���˽�λ���롣
     *
     * @param config_set ����ե�����졼�����ID
     * @param config_param ����ե�����졼�����ѥ�᡼��̾
     * 
     * @else
     *
     * @brief Update the values of configuration parameters (By name)
     * 
     * This operation updates a configuration variable by the
     * specified configuration parameter in the
     * configuration-set. This operation does not change current
     * active configuration-set. Since this operation causes
     * inconsistency between current active configuration set and
     * actual values of configuration variables, user should carefully
     * use it.
     *
     * This operation ends without doing anything, if the
     * configuration-set or the configuration parameter do not exist.
     *
     * @param config_set configuration-set ID.
     * @param config_param configuration parameter name.
     *
     * @endif
     */
    void update(const char* config_set, const char* config_param);
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼����¸�߳�ǧ
     * 
     * ���ꤷ��̾�Τ���ĥ���ե�����졼�����ѥ�᡼���ѿ���¸�ߤ���
     * ����ǧ���롣������¸�߳�ǧ��Ԥ��ѥ�᡼���ѿ��Ȥϡ�
     * bindParameter() �ˤ�ä���Ͽ����롢�ѿ�����ĥѥ�᡼���Ǥ��롣
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
    bool isChanged(void) {return m_changed;}

    /*!
     * @if jp
     *
     * @brief �ѹ����줿�ѥ�᡼���Υꥹ��
     * 
     * ����ե�����졼�����ѥ�᡼���Τ����ѹ����줿��ΤΥꥹ�Ȥ��֤���
     *
     * @return �ѹ����줿�ѥ�᡼��̾�ꥹ��
     *
     * @else
     *
     * @brief Changed parameters list
     * 
     * This operation returns parameter list which are changed.
     *
     * @return Changed parameters list
     *
     * @endif
     */
    coil::vstring& changedParameters() { return m_changedParam; }
    
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
    const char* getActiveId(void) {return m_activeId.c_str();}
    
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
    bool isActive(void)
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
    const std::vector<coil::Properties*>& getConfigurationSets(void);
    
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
    bool setConfigurationSetValues(const coil::Properties& configuration_set);
    
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
    const coil::Properties& getActiveConfigurationSet(void);
    
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
     *
     * ���ꤷ��ID�Υ���ե�����졼����󥻥åȤ�¸�ߤ��ʤ����ϡ�
     * false���֤��������ǽ�ʥ���ե�����졼����󥻥åȤϡ�
     * addConfigruationSet() �ˤ�ä��ɲä�������ե�����졼����󥻥�
     * �ȤΤߤǤ��ꡢ�ǥե���ȥ���ե�����졼����󥻥åȡ�����ݡ���
     * ��ȵ�ư���˥ե����뤫���ɤ߹��ޤ�륳��ե�����졼����󥻥å�
     * �Ϻ�����뤳�Ȥ��Ǥ��ʤ���
     *
     * �ޤ������ꤷ������ե�����졼����󥻥åȤ����ߥ����ƥ��֤Ǥ���
     * ���ˤϡ������ʤ륳��ե�����졼����󥻥åȤǤ����Ǥ��ʤ���
     *
     * ���δؿ��ˤ��ºݤ˥���ե�����졼����󥻥åȤ�������줿��硢
     * setOnRemoveConfigurationSet() �ǥ��åȤ��줿������Хå��ؿ�����
     * �ӽФ���롣
     *
     * @param config_id ����оݥ���ե�����졼����󥻥åȤ�ID
     *
     * @return ����������(�������:true���������:false)
     *
     * @else
     *
     * @brief Remove the configuration set
     * 
     * Remove the configuration set of specified ID Return empty
     * configuration set, if a configuration set of specified ID
     * doesn't exist.
     *
     * The configuration-sets that can be removed by this function are
     * only configuration-sets newly added by the
     * addConfigurationSet() function. The configuration that can be
     * removed by this function is only newly added configuration-set
     * by addConfigurationSet() function.  The "default"
     * configuration-set and configurationi-sets that is loaded from
     * configuration file cannot be removed.
     *
     * If the specified configuration is active currently, any
     * configurations are not deleted.
     *
     * Callback functions that are set by
     * addOnRemovedConfigurationSet() will be called if a
     * configuration-set is deleted actually by this function.
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

    //------------------------------------------------------------
    // obsolete functions
    //
    void setOnUpdate(OnUpdateCallback* cb);
    
    void setOnUpdateParam(OnUpdateParamCallback* cb);
    
    void setOnSetConfigurationSet(OnSetConfigurationSetCallback* cb);

    void setOnAddConfigurationSet(OnAddConfigurationAddCallback* cb);

    void setOnRemoveConfigurationSet(OnRemoveConfigurationSetCallback* cb);

    void setOnActivateSet(OnActivateSetCallback* cb);
    //
    // end of obsolete functions
    //------------------------------------------------------------

    /*!
     * @if jp
     *
     * @brief ConfigurationParamListener ���ɲä���
     *
     * update(const char* config_set, const char* config_param) ���ƤФ줿�ݤ�
     * �����뤵���ꥹ�� ConfigurationParamListener ���ɲä��롣
     * type �ˤϸ��ߤΤȤ��� ON_UPDATE_CONFIG_PARAM �Τߤ����롣
     *
     * @param type ConfigurationParamListenerType�����͡�
     *             ON_UPDATE_CONFIG_PARAM �����롣
     *
     * @param listener ConfigurationParamListener ���Υꥹ�ʥ��֥������ȡ�
     * @param autoclean �ꥹ�ʥ��֥������Ȥ�ư�Ǻ�����뤫�ɤ����Υե饰
     * 
     * @else
     *
     * @brief Adding ConfigurationParamListener 
     * 
     * This function adds a listener object which is called when
     * update(const char* config_set, const char* config_param) is
     * called. In the type argument, currently only
     * ON_UPDATE_CONFIG_PARAM is allowed.
     *
     * @param type ConfigurationParamListenerType value
     *             ON_UPDATE_CONFIG_PARAM is only allowed.
     *
     * @param listener ConfigurationParamListener listener object.
     * @param autoclean a flag whether if the listener object autocleaned.
     *
     * @endif
     */
    void addConfigurationParamListener(ConfigurationParamListenerType type,
                                       ConfigurationParamListener* listener,
                                       bool autoclean = true);

    /*!
     * @if jp
     *
     * @brief ConfigurationParamListener ��������
     *
     * addConfigurationParamListener ���ɲä��줿�ꥹ�ʥ��֥������Ȥ������롣
     *
     * @param type ConfigurationParamListenerType�����͡�
     *             ON_UPDATE_CONFIG_PARAM �����롣
     * @param listener Ϳ�����ꥹ�ʥ��֥������ȤؤΥݥ���
     * 
     * @else
     *
     * @brief Removing ConfigurationParamListener 
     * 
     * This function removes a listener object which is added by
     * addConfigurationParamListener() function.
     *
     * @param type ConfigurationParamListenerType value
     *             ON_UPDATE_CONFIG_PARAM is only allowed.
     * @param listener a pointer to ConfigurationParamListener listener object.
     *
     * @endif
     */
    void removeConfigurationParamListener(ConfigurationParamListenerType type,
                                          ConfigurationParamListener* listener);
    
    /*!
     * @if jp
     *
     * @brief ConfigurationSetListener ���ɲä���
     *
     * ConfigurationSet ���������줿�Ȥ��ʤɤ˸ƤФ��ꥹ��
     * ConfigurationSetListener ���ɲä��롣�����ǽ�ʥ��٥�Ȥϰʲ���
     * 2���ब���롣
     *
     * - ON_SET_CONFIG_SET: setConfigurationSetValues() ��
     *                      ConfigurationSet ���ͤ����ꤵ�줿��硣
     * - ON_ADD_CONFIG_SET: addConfigurationSet() �ǿ�����
     *                      ConfigurationSet ���ɲä��줿��硣
     *
     * @param type ConfigurationSetListenerType�����͡�
     * @param listener ConfigurationSetListener ���Υꥹ�ʥ��֥������ȡ�
     * @param autoclean �ꥹ�ʥ��֥������Ȥ�ư�Ǻ�����뤫�ɤ����Υե饰
     * 
     * @else
     *
     * @brief Adding ConfigurationSetListener 
     * 
     * This function add a listener object which is called when
     * ConfigurationSet is updated. Available events are the followings.
     *
     * @param type ConfigurationSetListenerType value
     * @param listener ConfigurationSetListener listener object.
     * @param autoclean a flag whether if the listener object autocleaned.
     *
     * @endif
     */
    void addConfigurationSetListener(ConfigurationSetListenerType type,
                                     ConfigurationSetListener* listener,
                                     bool autoclean = true);

    /*!
     * @if jp
     *
     * @brief ConfigurationSetListener ��������
     *
     * addConfigurationSetListener ���ɲä��줿�ꥹ�ʥ��֥������Ȥ������롣
     *
     * @param type ConfigurationSetListenerType�����͡�
     * @param listener Ϳ�����ꥹ�ʥ��֥������ȤؤΥݥ���
     * 
     * @else
     *
     * @brief Removing ConfigurationSetListener 
     * 
     * This function removes a listener object which is added by
     * addConfigurationSetListener() function.
     *
     * @param type ConfigurationSetListenerType value
     * @param listener a pointer to ConfigurationSetListener listener object.
     *
     * @endif
     */
    void removeConfigurationSetListener(ConfigurationSetListenerType type,
                                        ConfigurationSetListener* listener);
    
    /*!
     * @if jp
     *
     * @brief ConfigurationSetNameListener ���ɲä���
     *
     * ConfigurationSetName ���������줿�Ȥ��ʤɤ˸ƤФ��ꥹ��
     * ConfigurationSetNameListener ���ɲä��롣�����ǽ�ʥ��٥�Ȥϰʲ���
     * 3���ब���롣
     *
     * - ON_UPDATE_CONFIG_SET: ���� ConfigurationSet �����åץǡ��Ȥ��줿
     * - ON_REMOVE_CONFIG_SET: ���� ConfigurationSet ��������줿
     * - ON_ACTIVATE_CONFIG_SET: ���� ConfigurationSet �������ƥ��ֲ����줿
     *
     * @param type ConfigurationSetNameListenerType�����͡�
     * @param listener ConfigurationSetNameListener ���Υꥹ�ʥ��֥������ȡ�
     * @param autoclean �ꥹ�ʥ��֥������Ȥ�ư�Ǻ�����뤫�ɤ����Υե饰
     * 
     * @else
     *
     * @brief Adding ConfigurationSetNameListener 
     * 
     * This function add a listener object which is called when
     * ConfigurationSetName is updated. Available events are the followings.
     *
     * - ON_UPDATE_CONFIG_SET: A ConfigurationSet has been updated.
     * - ON_REMOVE_CONFIG_SET: A ConfigurationSet has been deleted.
     * - ON_ACTIVATE_CONFIG_SET: A ConfigurationSet has been activated.
     *
     * @param type ConfigurationSetNameListenerType value
     * @param listener ConfigurationSetNameListener listener object.
     * @param autoclean a flag whether if the listener object autocleaned.
     *
     * @endif
     */
    void 
    addConfigurationSetNameListener(ConfigurationSetNameListenerType type,
                                    ConfigurationSetNameListener* listener,
                                    bool autoclean = true);

    /*!
     * @if jp
     *
     * @brief ConfigurationSetNameListener ��������
     *
     * addConfigurationSetNameListener ���ɲä��줿�ꥹ�ʥ��֥������Ȥ�
     * ������롣
     *
     * @param type ConfigurationSetNameListenerType�����͡�
     *             ON_UPDATE_CONFIG_PARAM �����롣
     * @param listener Ϳ�����ꥹ�ʥ��֥������ȤؤΥݥ���
     * 
     * @else
     *
     * @brief Removing ConfigurationSetNameListener 
     * 
     * This function removes a listener object which is added by
     * addConfigurationSetNameListener() function.
     *
     * @param type ConfigurationSetNameListenerType value
     *             ON_UPDATE_CONFIG_PARAM is only allowed.
     * @param listener a pointer to ConfigurationSetNameListener
     *             listener object.
     *
     * @endif
     */
    void
    removeConfigurationSetNameListener(ConfigurationSetNameListenerType type,
                                       ConfigurationSetNameListener* listener);
    
  protected:
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���ι���(ID����)���˥����뤵���
     *
     * ���ꤵ��Ƥ륳����Хå����֥������Ȥ�ƤӽФ���
     *
     * @param config_set �����оݤΥ���ե�����졼����󥻥å�ID
     *
     * @else
     *
     * @brief When the configuration parameter is updated, it is called. 
     *
     * Call the set callback object.
     * 
     * @param config_set The target configuration set's ID to setup
     *
     * @endif
     */
    void onUpdate(const char* config_set);

    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���ι���(̾�λ���)���˥����뤵���
     *
     * ���ꤵ��Ƥ륳����Хå����֥������Ȥ�ƤӽФ���
     *
     * @param config_set ����ե�����졼�����ID
     * @param config_param ����ե�����졼�����ѥ�᡼��̾
     *
     * @else
     *
     * @brief When the configuration parameter is updated, it is called. 
     *
     * Call the set callback object.
     * 
     * @param config_set configuration-set ID.
     * @param config_param configuration parameter name.
     *
     * @endif
     */
    void onUpdateParam(const char* config_set, const char* config_param);

    /*!
     * @if jp
     *
     * @brief ����ե�����졼����󥻥åȤؤ��ɲû��˥����뤵���
     *
     * ���ꤵ��Ƥ륳����Хå����֥������Ȥ�ƤӽФ���
     *
     * @param configuration_set �ץ�ѥƥ�
     *
     * @else
     *
     * @brief Called when the property is added to the configuration set
     *
     * Call the set callback object.
     * 
     * @param configuration_set property
     *
     * @endif
     */
    void onSetConfigurationSet(const coil::Properties& config_set);

    /*!
     * @if jp
     *
     * @brief �����ͤ��ɲä��줿�Ȥ��˥����뤵��롣
     *
     * ���ꤵ��Ƥ륳����Хå����֥������Ȥ�ƤӽФ���
     *
     * @param configuration_set �ץ�ѥƥ�
     *
     * @else
     *
     * @brief Called when a set value is added to the configuration set
     *
     * Call the set callback object.
     * 
     * @param configuration_set property
     *
     * @endif
     */
    void onAddConfigurationSet(const coil::Properties& config_set);

    /*!
     * @if jp
     *
     * @brief ���åȤ��������Ƥ�Ȥ��˥����뤵��롣
     *
     * ���ꤵ��Ƥ륳����Хå����֥������Ȥ�ƤӽФ���
     *
     * @param config_id �ץ�ѥƥ�
     *
     * @else
     *
     * @brief Called when the configuration set has been deleted
     *
     * Call the set callback object.
     * 
     * @param config_id property
     *
     * @endif
     */
    void onRemoveConfigurationSet(const char* config_id);

    /*!
     * @if jp
     *
     * @brief ���åȤ������ƥ��ֲ����줿�Ȥ��˥����뤵��롣
     *
     * ���ꤵ��Ƥ륳����Хå����֥������Ȥ�ƤӽФ���
     *
     * @param config_id �ץ�ѥƥ�
     *
     * @else
     *
     * @brief Called when the configuration set is made active
     *
     * Call the set callback object.
     * 
     * @param config_id property
     *
     * @endif
     */
    void onActivateSet(const char* config_id);
    
  private:
    ConfigAdmin(const ConfigAdmin& ca);
    ConfigAdmin& operator=(const ConfigAdmin& ca);
    
    struct find_conf
    {
      std::string m_name;
      find_conf(const char* name) : m_name(name) {};
      bool operator()(ConfigBase* conf)
      {
        if (conf == 0) { return false; }
	return (m_name == conf->name);
      }
    };
    
    coil::Properties& m_configsets;
    coil::Properties  m_emptyconf;
    std::vector<ConfigBase*> m_params;
    std::string m_activeId;
    bool m_active;
    bool m_changed;
    coil::vstring m_changedParam;
    coil::vstring m_newConfig;
    ConfigurationListeners m_listeners;

  };
}; // namespace RTC
#endif // RTC_CONFIGADMIN_H
