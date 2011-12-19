// -*- C++ -*-
/*!
 * @file NamingManager.h
 * @brief naming Service helper class
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NamingManager.h 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#ifndef RTC_NAMINGMANAGER_H
#define RTC_NAMINGMANAGER_H

#include <rtm/RTC.h>

#include <coil/Task.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/SystemLogger.h>
#include <rtm/ManagerServant.h>

namespace RTC
{
  class Manager;
  /*!
   * @if jp
   *
   * @class NamingBase
   * @brief NamingService ��������ݥ��饹
   *
   * NamingServer ��������ݥ��󥿡��ե��������饹��
   * ��ݴ������饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
   * - bindObject() : ���ꤷ�����֥������Ȥ�NamingService�ؤΥХ����
   * - unbindObject() : ���ꤷ�����֥������Ȥ�NamingService����Υ���Х����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class NamingBase
   * @brief NamingService management abstract class
   *
   * This is the abstract interface class for NamingServer management.
   * Concrete management classes must implement the following pure virtual 
   * functions.
   * - bindObject() : Bind the specified object to NamingService
   * - unbindObject() : Unbind the specified object from NamingService
   *
   * @since 0.4.0
   *
   * @endif
   */
  class NamingBase
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * @else
     *
     * @brief Constructor
     *
     * @endif
     */
    NamingBase() {};
    
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
    virtual ~NamingBase(void) {};
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�����֥������Ȥ�NamingService�إХ���ɤ����貾�۴ؿ�
     *
     * @param name �Х���ɻ���̾��
     * @param rtobj �Х�����оݥ��֥�������
     *
     * @else
     *
     * @brief Pure virtual function to bind the specified objects 
     *        to the NamingService
     *
     * @param name The name to be bound to the NamingService
     * @param rtobj The target objects to be bound to the NamingSerivce
     *
     * @endif
     */
    virtual void bindObject(const char* name, const RTObject_impl* rtobj) = 0;

    /*!
     * @if jp
     *
     * @brief ���ꤷ��ManagerServant��NamingService�إХ���ɤ����貾�۴ؿ�
     *
     * @param name �Х���ɻ���̾��
     * @param rtobj �Х�����о�ManagerServant
     *
     * @else
     *
     * @brief Pure virtual function to bind the specified ManagerServants 
     *        to NamingService
     *
     * @param name The name to be bound to the NamingService
     * @param rtobj The target objects to be bound to the NamingSerivce
     *
     * @endif
     */
    virtual void bindObject(const char* name,
                            const RTM::ManagerServant* mgr) = 0;
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�����֥������Ȥ�NamingService���饢��Х���ɤ��뤿���
     *        ��貾�۴ؿ�
     *
     * @param name ����Х�����оݥ��֥�������
     *
     * @else
     *
     * @brief Pure virtual function to unbind the specified objects from 
     *        NamingService
     *
     * @param name The name of the object released from NamingService
     *
     * @endif
     */
    virtual void unbindObject(const char* name) = 0;

    /*!
     * @if jp
     *
     * @brief �͡��ॵ���Ф���¸���ǧ���롣
     * 
     * @return true:��¸���Ƥ���, false:��¸���Ƥ��ʤ�
     *
     * @else
     *
     * @brief Check if the name service is alive
     * 
     * @return true: alive, false:non not alive
     *
     * @endif
     */
    virtual bool isAlive() = 0;
  };
  

  /*!
   * @if jp
   *
   * @class NamingOnCorba
   * @brief CORBA �� NamingServer �������饹
   *
   * CORBA �� NamingServer �����ѥ��饹��
   * CORBA ����ݡ��ͥ�Ȥ� NamingService �ؤ���Ͽ������ʤɤ�������롣
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class NamingOnCorba
   * @brief NamingServer management class for CORBA
   *
   * NamingServer management class for CORBA.
   * Manage to register and unregister CORBA components to NamingService.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class NamingOnCorba
    : public virtual NamingBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯������2������Ϳ����͡��ॵ���ӥ�̾�ϡ��͡��ॵ����
     * ���Υۥ���̾�ȥݡ����ֹ�� ":" �Ƕ��ڤä���ΤǤ��롣�ݡ����ֹ�
     * ����ά���줿��硢2809�֥ݡ��Ȥ����Ѥ���롣
     *
     * @param orb ORB
     * @param names NamingServer ̾��
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor. Naming service name that is given at the second
     * argument is host name and port number hoined with ":". If the
     * port number is abbreviated, the default port number 2809 is
     * used.
     *
     * @param orb ORB
     * @param names Name of NamingServer
     *
     * @endif
     */
    NamingOnCorba(CORBA::ORB_ptr orb, const char* names);
    
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
    virtual ~NamingOnCorba(void){};
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�� CORBA ���֥������Ȥ�NamingService�إХ����
     * 
     * ���ꤷ�� CORBA ���֥������Ȥ���ꤷ��̾�Τ� CORBA NamingService ��
     * �Х���ɤ��롣
     * 
     * @param name �Х���ɻ���̾��
     * @param rtobj �Х�����оݥ��֥�������
     *
     * @else
     *
     * @brief Bind the specified CORBA objects to NamingService
     * 
     * Bind the specified CORBA objects to CORBA NamingService
     * by specified names.
     * 
     * @param name Names at the binding
     * @param rtobj The target objects for the binding
     *
     * @endif
     */
    virtual void bindObject(const char* name, const RTObject_impl* rtobj);
    /*!
     * @if jp
     *
     * @brief ���ꤷ��ManagerServant��NamingService�إХ����
     *
     * @param name �Х���ɻ���̾��
     * @param rtobj �Х�����о�ManagerServant
     *
     * @else
     *
     * @brief Bind the specified ManagerServants to NamingService
     *
     * @param name Names at the binding
     * @param mgr The target ManagerServants for the binding
     *
     * @endif
     */
    virtual void bindObject(const char* name, const RTM::ManagerServant* mgr);
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�� CORBA ���֥������Ȥ�NamingService���饢��Х����
     * 
     * ���ꤷ�� CORBA ���֥������Ȥ� CORBA NamingService ���饢��Х���ɤ��롣
     * 
     * @param name ����Х�����оݥ��֥�������
     *
     * @else
     *
     * @brief Unbind the specified CORBA objects from NamingService
     * 
     * Unbind the specified CORBA objects from CORBA NamingService.
     * 
     * @param name The target objects for the unbinding
     *
     * @endif
     */
    virtual void unbindObject(const char* name);
    
    /*!
     * @if jp
     *
     * @brief �͡��ॵ���Ф���¸���ǧ���롣
     * 
     * @return true:��¸���Ƥ���, false:��¸���Ƥ��ʤ�
     *
     * @else
     *
     * @brief Check if the name service is alive
     * 
     * @return true: alive, false:non not alive
     *
     * @endif
     */
    virtual bool isAlive();

  private:
    Logger rtclog;
    CorbaNaming m_cosnaming;
    std::string m_endpoint;
    bool m_replaceEndpoint;
    std::map<std::string, RTObject_impl*> m_names;
  };
  
  /*!
   * @if jp
   *
   * @class NamingManager
   * @brief NamingServer �������饹
   *
   * NamingServer �����ѥ��饹��
   * ����ݡ��ͥ�Ȥ�NamingService�ؤ���Ͽ������ʤɤ�������롣
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class NamingManager
   * @brief NamingServer management class
   *
   * NamingServer management class.
   * Manage to register and unregister components to NamingService.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class NamingManager
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param manager �ޥ͡����㥪�֥�������
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param manager Manager object
     *
     * @endif
     */
    NamingManager(Manager* manager);
    
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
    virtual ~NamingManager(void);
    
    /*!
     * @if jp
     *
     * @brief NameServer ����Ͽ
     *
     * ���ꤷ�������� NameServer ����Ͽ���롣
     * ���߻����ǽ�ʷ����� CORBA �Τߡ�
     *
     * @param method NamingService �η���
     * @param name_server ��Ͽ���� NameServer ��̾��
     *
     * @else
     *
     * @brief Regster the NameServer
     *
     * Register NameServer by specified format.
     * Currently. only CORBA can be specified.
     *
     * @param method Format of NamingService
     * @param name_server Name of NameServer for registration
     *
     * @endif
     */
    void registerNameServer(const char* method, const char* name_server);
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�����֥������Ȥ�NamingService�إХ����
     * 
     * ���ꤷ�����֥������Ȥ���ꤷ��̾�Τ� CORBA NamingService �إХ�
     * ��ɤ��롣
     * 
     * @param name �Х���ɻ���̾��
     * @param rtobj �Х�����оݥ��֥�������
     *
     * @else
     *
     * @brief Bind the specified objects to NamingService
     * 
     * Bind the specified objects to CORBA NamingService by specified names.
     * 
     * @param name Names at the binding
     * @param rtobj The target objects for the binding
     *
     * @endif
     */
    void bindObject(const char* name, const RTObject_impl* rtobj);

    /*!
     * @if jp
     *
     * @brief ���ꤷ��ManagerServant��NamingService�إХ����
     * 
     * ���ꤷ��ManagerServant����ꤷ��̾�Τ� CORBA NamingService �إ�
     * ����ɤ��롣
     * 
     * @param name �Х���ɻ���̾��
     * @param mgr �Х�����о�ManagerServant
     *
     * @else
     *
     * @brief Bind the specified ManagerServants to NamingService
     * 
     * Bind the specified ManagerServants to CORBA NamingService 
     * by specified names.
     * 
     * @param name Names at the binding
     * @param mgr The target ManagerServants for the binding
     *
     * @endif
     */
    void bindObject(const char* name, const RTM::ManagerServant* mgr);
    
    /*!
     * @if jp
     *
     * @brief NamingServer �ξ���ι���
     * 
     * ���ꤵ��Ƥ��� NameServer �����Ͽ����Ƥ��륪�֥������Ȥξ����
     * �������롣
     * 
     * @else
     *
     * @brief Update information of NamingServer
     * 
     * Update the object information registered in the specified NameServer.
     * 
     * @endif
     */
    void update();
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�����֥������Ȥ�NamingService���饢��Х����
     * 
     * ���ꤷ�����֥������Ȥ� NamingService ���饢��Х���ɤ��롣
     * 
     * @param name ����Х�����оݥ��֥�������
     *
     * @else
     *
     * @brief Unbind the specified objects from NamingService
     * 
     * Unbind the specified objects from NamingService.
     * 
     * @param name The target objects for the unbinding
     *
     * @endif
     */
    void unbindObject(const char* name);
    
    /*!
     * @if jp
     *
     * @brief ���ƤΥ��֥������Ȥ�NamingService���饢��Х����
     * 
     * ���ƤΥ��֥������Ȥ� CORBA NamingService ���饢��Х���ɤ��롣
     * 
     * @else
     *
     * @brief Unbind all objects from NamingService
     * 
     * Unbind all objects from CORBA NamingService.
     * 
     * @endif
     */
    void unbindAll();
    
    /*!
     * @if jp
     *
     * @brief �Х���ɤ���Ƥ������ƤΥ��֥������Ȥ����
     * 
     * �Х���ɤ���Ƥ������ƤΥ��֥������Ȥ� �������롣
     *
     * @return �Х���ɺѤߥ��֥������� �ꥹ��
     * 
     * @else
     *
     * @brief Get all bound objects
     * 
     * Get all bound objects.
     *
     * @return Bound object list
     * 
     * @endif
     */
    std::vector<RTObject_impl*> getObjects();
    
  protected:
    /*!
     * @if jp
     *
     * @brief NameServer �����ѥ��֥������Ȥ�����
     * 
     * ���ꤷ������NameServer �����ѥ��֥������Ȥ��������롣
     *
     * @param method NamingService ����
     * @param name_server NameServer ̾��
     * 
     * @return �������� NameServer ���֥�������
     * 
     * @else
     *
     * @brief Create objects for NameServer management
     * 
     * Create objects of specified type for NameServer management.
     *
     * @param method NamingService format
     * @param name_server NameServer name
     * 
     * @return Created NameServer objects
     * 
     * @endif
     */
    NamingBase* createNamingObj(const char* method, const char* name_server);
    
    /*!
     * @if jp
     *
     * @brief ����Ѥߥ���ݡ��ͥ�Ȥ� NameServer ����Ͽ
     * 
     * ����Ѥߥ���ݡ��ͥ�Ȥ���ꤷ�� NameServer ����Ͽ���롣
     *
     * @param ns ��Ͽ�о� NameServer
     * 
     * @else
     *
     * @brief Register the configured component to NameServer
     * 
     * Register the already configured components to NameServer.
     *
     * @param ns The target NameServer for the registration
     * 
     * @endif
     */
    void bindCompsTo(NamingBase* ns);
    
    /*!
     * @if jp
     *
     * @brief NameServer ����Ͽ���륳��ݡ��ͥ�Ȥ�����
     * 
     * NameServer ����Ͽ���륳��ݡ��ͥ�Ȥ����ꤹ�롣
     *
     * @param name ����ݡ��ͥ�Ȥ���Ͽ��̾��
     * @param rtobj ��Ͽ�оݥ��֥�������
     * 
     * @else
     *
     * @brief Configure the components that will be registered to NameServer
     * 
     * Configure the components that will be registered to NameServer.
     *
     * @param name Names of components at the registration
     * @param rtobj The target objects for registration
     * 
     * @endif
     */
    void registerCompName(const char* name, const RTObject_impl* rtobj);

    /*!
     * @if jp
     *
     * @brief NameServer ����Ͽ����ManagerServant������
     * 
     * NameServer ����Ͽ����ManagerServant�����ꤹ�롣
     *
     * @param name ManagerServant����Ͽ��̾��
     * @param mgr ��Ͽ�о�ManagerServant
     * 
     * @else
     *
     * @brief Configure the ManagerServants that will be registered 
     * to NameServer
     * 
     * Configure the ManagerServants that will be registered to NameServer.
     *
     * @param name Names of ManagerServants at the registration
     * @param mgr The target ManagerServants for registration
     * 
     * @endif
     */
    void registerMgrName(const char* name, const RTM::ManagerServant* mgr);
    
    /*!
     * @if jp
     *
     * @brief NameServer ����Ͽ���륳��ݡ��ͥ�Ȥ�������
     * 
     * NameServer ����Ͽ���륳��ݡ��ͥ�Ȥ�����������롣
     *
     * @param name �������оݥ���ݡ��ͥ�Ȥ�̾��
     * 
     * @else
     *
     * @brief Unregister the components that will be registered to NameServer
     * 
     * Unregister the components that will be registered to NameServer.
     *
     * @param name Names of the target components for unregistration
     * 
     * @endif
     */
    void unregisterCompName(const char* name);

    /*!
     * @if jp
     *
     * @brief NameServer ����Ͽ����ManagerServant��������
     * 
     * NameServer ����Ͽ����ManagerServant������������롣
     *
     * @param name �������о�ManagerServant��̾��
     * 
     * @else
     *
     * @brief Unregister the ManagerServants that will be registered 
     * to NameServer
     * 
     * Unregister the ManagerServants that will be registered to NameServer.
     *
     * @param name Names of the target ManagerServants for unregistration
     * 
     * @endif
     */
    void unregisterMgrName(const char* name);

    /*!
     * @if jp
     *
     * @brief ����ݥͥ�Ȥ��Х���ɤ���
     * 
     * �͡��ॵ���Ф���³���ƥ���ݥͥ�Ȥ��Х���ɤ��롣
     *
     * @param ns NameServer
     * 
     * @else
     *
     * @brief Rebind the component to NameServer
     * 
     * Connect with the NameServer and rebind the component. 
     *
     * @param ns NameServer
     * 
     * @endif
     */
    class Names;
    void retryConnection(Names* ns);
    
  protected:
    // Name Servers' method/name and object
    /*!
     * @if jp
     * @brief NameServer �����ѹ�¤��
     * @else
     * @brief Structure for NameServer management
     * @endif
     */
    class Names
    {
    public:
      Names(const char* meth, const char* name, NamingBase* naming)
	: method(meth), nsname(name), ns(naming)
      {
      }
      
      ~Names()
      {
        delete ns;
      }
      
      std::string method;
      std::string nsname;
      NamingBase* ns;
    };
    /*!
     * @if jp
     * @brief NameServer �ꥹ��
     * @else
     * @brief NameServer list
     * @endif
     */
    std::vector<Names*> m_names;
    /*!
     * @if jp
     * @brief NameServer �ꥹ�Ȥ�mutex
     * @else
     * @brief Mutex of NameServer list
     * @endif
     */
    Mutex m_namesMutex;
    
    // Components' name and object
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȴ����ѹ�¤��
     * @else
     * @brief Structure for component management
     * @endif
     */
    struct Comps
    {
      Comps(const char* n, const RTObject_impl* obj)
	: name(n), rtobj(obj)
      {}
      std::string name;
      const RTObject_impl* rtobj;
    };
    /*!
     * @if jp
     * @brief ManagerServant�����ѹ�¤��
     * @else
     * @brief Structure for ManagerServant management
     * @endif
     */
    struct Mgr
    {
      Mgr(const char* n, const RTM::ManagerServant* obj)
	: name(n), mgr(obj)
      {}
      std::string name;
      const RTM::ManagerServant* mgr;
    };
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȥꥹ��
     * @else
     * @brief Component list
     * @endif
     */
    std::vector<Comps*> m_compNames;
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȥꥹ�Ȥ�mutex
     * @else
     * @brief Mutex of Component list
     * @endif
     */
    Mutex m_compNamesMutex;
    /*!
     * @if jp
     * @brief ManagerServant�ꥹ��
     * @else
     * @brief ManagerServant list
     * @endif
     */
    std::vector<Mgr*> m_mgrNames;
    /*!
     * @if jp
     * @brief ManagerServant�ꥹ�Ȥ�mutex
     * @else
     * @brief Mutex of ManagerServant list
     * @endif
     */
    Mutex m_mgrNamesMutex;
    
    /*!
     * @if jp
     * @brief �ޥ͡����㥪�֥�������
     * @else
     * @brief Manager object
     * @endif
     */
    Manager* m_manager;
    
    /*!
     * @if jp
     * @brief �������ȥ꡼��
     * @else
     * @brief Logger stream
     * @endif
     */
    Logger rtclog;
  }; // class NamingManager
}; // namespace RTC

#endif // RTC_NAMINGMANAGER_H
