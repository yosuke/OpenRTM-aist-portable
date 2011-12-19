// -*- C++ -*-
/*!
 * @file PortBase.cpp
 * @brief RTC's Port base class
 * @date $Date: 2008-01-14 10:19:42 $
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
 * $Id: PortBase.cpp 2048 2011-02-22 21:20:51Z n-ando $
 *
 */

#include <assert.h>
#include <memory>
#include <coil/UUID.h>
#include <rtm/PortBase.h>
#include <rtm/PortCallback.h>

namespace RTC
{
  //============================================================
  // class PortBase 
  //============================================================
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  PortBase::PortBase(const char* name)
    : rtclog(name),
      m_ownerInstanceName("unknown"),
      m_connectionLimit(-1),
      m_onPublishInterfaces(0),
      m_onSubscribeInterfaces(0),
      m_onConnected(0),
      m_onUnsubscribeInterfaces(0),
      m_onDisconnected(0),
      m_onConnectionLost(0),
      m_portconnListeners(NULL)
  {
    m_objref = this->_this();
    // Now Port name is <instance_name>.<port_name>. r1648
    std::string portname(m_ownerInstanceName);
    portname += ".";
    portname += name;

    m_profile.name = CORBA::string_dup(portname.c_str());
    m_profile.interfaces.length(0);
    m_profile.port_ref = m_objref;
    m_profile.connector_profiles.length(0);
    m_profile.owner = RTC::RTObject::_nil();
    m_profile.properties.length(0);
  }
  
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  PortBase::~PortBase()
  {
    RTC_TRACE(("~PortBase()"));
    try
      {
        PortableServer::ObjectId_var oid = _default_POA()->servant_to_id(this);
        _default_POA()->deactivate_object(oid);
      }
    catch (PortableServer::POA::ServantNotActive &e)
      {
        RTC_ERROR(("%s", e._name()));
      }
    catch (PortableServer::POA::WrongPolicy &e)
      {
        RTC_ERROR(("%s", e._name()));
      }
    catch (...)
      {
        RTC_ERROR(("Unknown exception caught."));
      }
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] PortProfile���������
   * @else
   * @brief [CORBA interface] Get the PortProfile of the Port
   * @endif
   */
  PortProfile* PortBase::get_port_profile()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_port_profile()"));

    updateConnectors();
    Guard gaurd(m_profile_mutex);
    PortProfile_var prof;
    prof = new PortProfile(m_profile);
    return prof._retn();
  }
  
  /*!
   * @if jp
   * @brief [Local interface] PortProfile ��������롣
   * @else
   * @brief Get the PortProfile of the Port
   * @endif
   */
  const PortProfile& PortBase::getPortProfile() const
  {
    RTC_TRACE(("getPortProfile()"));

    return m_profile;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] ConnectorProfileList���������
   * @else
   * @brief [CORBA interface] Get the ConnectorProfileList of the Port
   * @endif
   */
  ConnectorProfileList* PortBase::get_connector_profiles()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_connector_profiles()"));

    updateConnectors();

    Guard gaurd(m_profile_mutex);
    ConnectorProfileList_var conn_prof;
    conn_prof = new ConnectorProfileList(m_profile.connector_profiles);
    return conn_prof._retn();
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] ConnectorProfile ���������
   * @else
   * @brief [CORBA interface] Get the ConnectorProfile
   * @endif
   */
  ConnectorProfile* PortBase::get_connector_profile(const char* connector_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_connector_profile(%s)", connector_id));

    updateConnectors();

    Guard gaurd(m_profile_mutex);
    CORBA::Long index(findConnProfileIndex(connector_id));

    if (index < 0)
      {
	ConnectorProfile_var conn_prof;
	conn_prof = new ConnectorProfile();
	return conn_prof._retn();
      }
    ConnectorProfile_var conn_prof;
    conn_prof = new ConnectorProfile(m_profile.connector_profiles[index]);
    return conn_prof._retn();
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Port ����³��Ԥ�
   * @else
   * @brief [CORBA interface] Connect the Port
   * @endif
   */
  ReturnCode_t PortBase::connect(ConnectorProfile& connector_profile)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("connect()"));
    if (isEmptyId(connector_profile))
      {
        Guard gurad(m_profile_mutex);
	// "connector_id" stores UUID which is generated at the initial Port
	// in connection process.
	setUUID(connector_profile);
	assert(!isExistingConnId(connector_profile.connector_id));
      }
    else
      {
        Guard gurad(m_profile_mutex);
	if (isExistingConnId(connector_profile.connector_id))
	  {
            RTC_ERROR(("Connection already exists."));
	    return RTC::PRECONDITION_NOT_MET;
	  }
      }

    try
      {
	RTC::PortService_ptr p;
	p = connector_profile.ports[(CORBA::ULong)0];
	ReturnCode_t ret = p->notify_connect(connector_profile);
        if (ret != RTC::RTC_OK)
          {
            RTC_ERROR(("Connection failed. cleanup."));
            disconnect(connector_profile.connector_id);
          }
        return ret;
      }
    catch (...)
      {
	return RTC::BAD_PARAMETER;
      }
    return RTC::RTC_ERROR;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Port ����³���Τ�Ԥ�
   * @else
   * @brief [CORBA interface] Notify the Ports connection
   * @endif
   */
  ReturnCode_t PortBase::notify_connect(ConnectorProfile& connector_profile)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("notify_connect()"));
    Guard guard(m_connectorsMutex);
    ReturnCode_t retval[] = {RTC::RTC_OK, RTC::RTC_OK, RTC::RTC_OK};

    onNotifyConnect(getName(), connector_profile);

    // publish owned interface information to the ConnectorProfile
    retval[0] = publishInterfaces(connector_profile);
    if (retval[0] != RTC::RTC_OK)
      {
        RTC_ERROR(("publishInterfaces() in notify_connect() failed."));
      }
    onPublishInterfaces(getName(), connector_profile, retval[0]);
    if (m_onPublishInterfaces != 0)
      {
        (*m_onPublishInterfaces)(connector_profile);
      }


    // call notify_connect() of the next Port
    retval[1] = connectNext(connector_profile);
    if (retval[1] != RTC::RTC_OK)
      {
        RTC_ERROR(("connectNext() in notify_connect() failed."));
      }
    onConnectNextport(getName(), connector_profile, retval[1]);

    // subscribe interface from the ConnectorProfile's information

    if (m_onSubscribeInterfaces != 0)
      {
        (*m_onSubscribeInterfaces)(connector_profile);
      }

    retval[2] = subscribeInterfaces(connector_profile);
    if (retval[2] != RTC::RTC_OK) 
      {
        RTC_ERROR(("subscribeInterfaces() in notify_connect() failed."));
      }
    onSubscribeInterfaces(getName(), connector_profile, retval[2]);

    RTC_PARANOID(("%d connectors are existing",
                  m_profile.connector_profiles.length()));

    Guard gurad(m_profile_mutex);
    CORBA::Long index(findConnProfileIndex(connector_profile.connector_id));
    if (index < 0)
      {
        CORBA_SeqUtil::push_back(m_profile.connector_profiles,
                                 connector_profile);
        RTC_PARANOID(("New connector_id. Push backed."));
      }
    else
      {
	m_profile.connector_profiles[index] = connector_profile;
        RTC_PARANOID(("Existing connector_id. Updated."));
      }

    for (int i(0), len(sizeof(retval)/sizeof(ReturnCode_t)); i < len; ++i)
      {
        if (retval[i] != RTC::RTC_OK)
          {
            onConnected(getName(), connector_profile, retval[i]);
            return retval[i];
          }
      }

    // connection established without errors
    if (m_onConnected != 0)
      {
        (*m_onConnected)(connector_profile);
      }
    onConnected(getName(), connector_profile, RTC::RTC_OK);
    return RTC::RTC_OK;
  }
 
  /*!
   * @if jp
   * @brief Interface������������
   * @else
   * @brief Publish interface information
   * @endif
   */
  ReturnCode_t PortBase::_publishInterfaces(void)
  {
    if(!(m_connectionLimit < 0))
      {
        if((::CORBA::ULong)m_connectionLimit<=m_profile.connector_profiles.length())
          {
            RTC_PARANOID(("Connected number has reached the limitation."));
            RTC_PARANOID(("Can connect the port up to %d ports.",
                      m_connectionLimit));
            RTC_PARANOID(("%d connectors are existing",
                      m_profile.connector_profiles.length()));
            return RTC::RTC_ERROR;
          }
      }
    return RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief [CORBA interface] Port ����³��������
   * @else
   * @brief [CORBA interface] Disconnect the Port
   * @endif
   */
  ReturnCode_t PortBase::disconnect(const char* connector_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("disconnect(%s)", connector_id));

    CORBA::Long index(findConnProfileIndex(connector_id));
    if (index < 0)
      {
        RTC_ERROR(("Invalid connector id: %s", connector_id));
	return RTC::BAD_PARAMETER;
      }

    ConnectorProfile prof;
    { // lock and copy profile
      Guard guard(m_profile_mutex);
      prof = m_profile.connector_profiles[index];
    }

    if (prof.ports.length() < 1)
      {
        RTC_FATAL(("ConnectorProfile has empty port list."));
        return RTC::PRECONDITION_NOT_MET;
      }

    for (CORBA::ULong i(0), len(prof.ports.length()); i < len; ++i)
      {
        RTC::PortService_var p(prof.ports[i]);
        try
          {
            return p->notify_disconnect(connector_id);
          }
        catch (CORBA::SystemException &e)
          {
#ifndef ORB_IS_RTORB
            RTC_WARN(("Exception caught: minor code(%d).", e.minor()));;
#else // ORB_IS_RTORB
            RTC_WARN(("Exception caught"));
#endif // ORB_IS_RTORB
            continue;
          }
        catch (...)
          {
            RTC_WARN(("Unknown exception caught."));;
            continue;
          }
      }
    RTC_ERROR(("notify_disconnect() for all ports failed."));
    return RTC::RTC_ERROR;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Port ����³������Τ�Ԥ�
   * @else
   * @brief [CORBA interface] Notify the Ports disconnection
   * @endif
   */
  ReturnCode_t PortBase::notify_disconnect(const char* connector_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("notify_disconnect(%s)", connector_id));
    Guard guard(m_connectorsMutex);
    Guard gaurd(m_profile_mutex);

    // find connector_profile
    CORBA::Long index(findConnProfileIndex(connector_id));
    if (index < 0) 
      {
        RTC_ERROR(("Invalid connector id: %s", connector_id));
	return RTC::BAD_PARAMETER;
      }
    
    ConnectorProfile& prof(m_profile.connector_profiles[(CORBA::ULong)index]);
    onNotifyDisconnect(getName(), prof);

    ReturnCode_t retval(disconnectNext(prof));
    onDisconnectNextport(getName(), prof, retval);

    if (m_onUnsubscribeInterfaces != 0)
      {
        (*m_onUnsubscribeInterfaces)(prof);
      }
    onUnsubscribeInterfaces(getName(), prof);
    unsubscribeInterfaces(prof);
 
    if (m_onDisconnected != 0)
      {
        (*m_onDisconnected)(prof);
      }
// Why RtORB does not use CORBA_SeqUtil?
#ifndef ORB_IS_RTORB
    CORBA_SeqUtil::erase(m_profile.connector_profiles, index);
#else // ORB_IS_RTORB
    CORBA::ULong len(m_profile.connector_profiles.length());
    if (index < (CORBA::Long)len)
      {
        for (CORBA::ULong i(index); i < len - 1; ++i)
          {
            m_profile.connector_profiles[i] = 
              m_profile.connector_profiles[i + 1] ;
          }
        m_profile.connector_profiles._length=len-1;
      }
#endif // ORB_IS_RTORB
    onDisconnected(getName(), prof, retval);
    return retval;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Port ������³��������
   * @else
   * @brief [CORBA interface] Disconnect the All Ports
   * @endif
   */
  ReturnCode_t PortBase::disconnect_all()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("disconnect_all()"));

    ::RTC::ConnectorProfileList plist;
    {
      Guard gaurd(m_profile_mutex);
      plist = m_profile.connector_profiles;
    }

    RTC::ReturnCode_t retcode(::RTC::RTC_OK);
    CORBA::ULong len(plist.length());
    RTC_DEBUG(("disconnecting %d connections.", len));
    for (CORBA::ULong i(0); i < len; ++i)
      {
        ReturnCode_t tmpret;
        tmpret =this->disconnect(plist[i].connector_id);
        if (tmpret != RTC::RTC_OK) retcode = tmpret;
      }
    
    return retcode;
  }
  
  //============================================================
  // Local operations
  //============================================================
  /*!
   * @if jp
   * @brief Port ��̾�������ꤹ��
   * @else
   * @brief Set the name of this Port
   * @endif
   */
  void PortBase::setName(const char* name)
  {
    RTC_TRACE(("setName(%s)", name));
    Guard guard(m_profile_mutex);
    m_profile.name = CORBA::string_dup(name);
    rtclog.setName(name);
  }

  /*!
   * @if jp
   * @brief Port ��̾�����������
   * @else
   * @brief Get the name of this Port
   * @return The name of this Port.
   * @endif
   */
  const char* PortBase::getName() const
  {
    RTC_TRACE(("getName() = %s", (const char*)m_profile.name));
    return m_profile.name;
  }
  
  /*!
   * @if jp
   * @brief PortProfile���������
   * @else
   * @brief Get the PortProfile of the Port
   * @endif
   */
  const PortProfile& PortBase::getProfile() const
  {
    RTC_TRACE(("getProfile()"));
    Guard guard(m_profile_mutex);
    return m_profile;
  }
  
  /*!
   * @if jp
   * @brief Port �Υ��֥������Ȼ��Ȥ����ꤹ��
   * @else
   * @brief Set the object reference of the Port
   * @endif
   */
  void PortBase::setPortRef(PortService_ptr port_ref)
  {
    RTC_TRACE(("setPortRef()"));
    Guard gurad(m_profile_mutex);
    m_profile.port_ref = port_ref;
  }
  
  /*!
   * @if jp
   * @brief Port �Υ��֥������Ȼ��Ȥ��������
   * @else
   * @brief Get the object reference of the Port
   * @endif
   */
  PortService_ptr PortBase::getPortRef()
  {
    RTC_TRACE(("getPortRef()"));
    Guard gurad(m_profile_mutex);
    return m_profile.port_ref;
  }
  
  /*!
   * @if jp
   * @brief Port �� owner �� RTObject ����ꤹ��
   * @else
   * @brief Set the owner RTObject of the Port
   * @endif
   */
  void PortBase::setOwner(RTObject_ptr owner)
  {
    RTC::ComponentProfile_var prof = owner->get_component_profile();

    m_ownerInstanceName = prof->instance_name;
    RTC_TRACE(("setOwner(%s)", m_ownerInstanceName.c_str()));

    {
      Guard gurad(m_profile_mutex); 
      std::string portname((const char*)m_profile.name);
      coil::vstring p(coil::split(portname, "."));
      // Now Port name is <instance_name>.<port_name>. r1648
      portname = m_ownerInstanceName +"."+ p.back();

      m_profile.owner = RTC::RTObject::_duplicate(owner);
      m_profile.name = CORBA::string_dup(portname.c_str());
    }
  }

  // OnConnect�ϥ�����Хå� (��³�˵������륤�٥�Ȥˤ�ꥳ���뤵���)
  void PortBase::setOnPublishInterfaces(ConnectionCallback* on_publish)
  {
    m_onPublishInterfaces = on_publish;
  }

  void PortBase::setOnSubscribeInterfaces(ConnectionCallback* on_subscribe)
  {
    m_onSubscribeInterfaces = on_subscribe;
  }

  void PortBase::setOnConnected(ConnectionCallback* on_connected)
  {
    m_onConnected = on_connected;
  }
  
  void PortBase::setOnUnsubscribeInterfaces(ConnectionCallback* on_unsubscribe)
  {
    m_onUnsubscribeInterfaces = on_unsubscribe;
  }

  void PortBase::setOnDisconnected(ConnectionCallback* on_disconnected)
  {
    m_onDisconnected = on_disconnected;
  }
  
  void PortBase::setOnConnectionLost(ConnectionCallback* on_connection_lost)
  {
    m_onConnectionLost = on_connection_lost;
  }  

  void PortBase::
  setPortConnectListenerHolder(PortConnectListeners* portconnListeners)
  {
    m_portconnListeners = portconnListeners;
  }


  //============================================================
  // protected operations
  //============================================================
  /*!
   * @if jp
   * @brief ���� Port ���Ф��� notify_connect() �򥳡��뤹��
   * @else
   * @brief Call notify_connect() for the next Port
   * @endif
   */
  ReturnCode_t PortBase::connectNext(ConnectorProfile& connector_profile)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(connector_profile.ports,
				find_port_ref(m_profile.port_ref));
    
    if (index < 0) return RTC::BAD_PARAMETER;
    
    if (++index < static_cast<CORBA::Long>(connector_profile.ports.length()))
      {
	RTC::PortService_ptr p;
	p = connector_profile.ports[index];
	return p->notify_connect(connector_profile);
      }
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief ���� Port ���Ф��� notify_disconnect() �򥳡��뤹��
   * @else
   * @brief Call notify_disconnect() for the next Port
   * @endif
   */
  ReturnCode_t PortBase::disconnectNext(ConnectorProfile& cprof)
  {
    CORBA::ULong index;
    index = CORBA_SeqUtil::find(cprof.ports,
				find_port_ref(m_profile.port_ref));
    if (index < 0)
      {
        return RTC::BAD_PARAMETER;
      }
    if (index == cprof.ports.length() - 1)
      {
        return RTC::RTC_OK;
      }
    
    CORBA::ULong len = cprof.ports.length();
    
    ++index;
    for (CORBA::ULong i(index); i < len; ++i)
      {
        RTC::PortService_var p;
        p = cprof.ports[i];
        try
          {
            return p->notify_disconnect(cprof.connector_id);
          }
        catch (CORBA::SystemException& e)
          {
#ifndef ORB_IS_RTORB
            RTC_WARN(("Exception caught: minor code.", e.minor()));
#else // ORB_IS_RTORB
            RTC_WARN(("Exception caught"));
#endif // ORB_IS_RTORB
            continue;
          } 
        catch (...)
          {
            RTC_WARN(("Unknown exception caught."));
            continue;
          }
      }
        
    return RTC::RTC_ERROR;
  }
  /*!
   * @if jp
   * @brief ��³�κ���������ꤹ�롣
   * @else
   * @brief Set the maximum number of connections
   * @endif
   */
  void PortBase::setConnectionLimit(int limit_value)
  {
    m_connectionLimit = limit_value;
  }
  
  //============================================================
  // protected utility functions
  //============================================================
  /*!
   * @if jp
   * @brief ConnectorProfile �� connector_id �ե�����ɤ������ɤ���Ƚ��
   * @else
   * @brief Check whether connector_id of ConnectorProfile is empty
   * @endif
   */
  bool PortBase::isEmptyId(const ConnectorProfile& connector_profile) const
  {
    return connector_profile.connector_id[(CORBA::ULong)0] == 0;
  }
  
  
  /*!
   * @if jp
   * @brief UUID����������
   * @else
   * @brief Generate the UUID
   * @endif
   */
  const std::string PortBase::getUUID() const
  {
    coil::UUID_Generator uugen;
    uugen.init();
    std::auto_ptr<coil::UUID> uuid(uugen.generateUUID(2,0x01));
    
    return std::string((const char*)uuid->to_string());
  }
  
  /*!
   * @if jp
   * @brief UUID�������� ConnectorProfile �˥��åȤ���
   * @else
   * @brief Generate the UUID and set it to the ConnectorProfile
   * @endif
   */
  void PortBase::setUUID(ConnectorProfile& connector_profile) const
  {
    connector_profile.connector_id = CORBA::string_dup(getUUID().c_str());
    assert(connector_profile.connector_id[(CORBA::ULong)0] != 0);
  }
  
  /*!
   * @if jp
   * @brief id ����¸�� ConnectorProfile �Τ�Τ��ɤ���Ƚ�ꤹ��
   * @else
   * @brief Check whether the given id exists in stored ConnectorProfiles
   * @endif
   */
  bool PortBase::isExistingConnId(const char* id)
  {
    return CORBA_SeqUtil::find(m_profile.connector_profiles,
			       find_conn_id(id)) >= 0;
  }
  
  /*!
   * @if jp
   * @brief id ����� ConnectorProfile ��õ��
   * @else
   * @brief Find ConnectorProfile with id
   * @endif
   */
  ConnectorProfile PortBase::findConnProfile(const char* id)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.connector_profiles,
				find_conn_id(id));
    return m_profile.connector_profiles[index];
  }
  
  /*!
   * @if jp
   * @brief id ����� ConnectorProfile ��õ��
   * @else
   * @brief Find ConnectorProfile with id
   * @endif
   */
  CORBA::Long PortBase::findConnProfileIndex(const char* id)
  {
    return CORBA_SeqUtil::find(m_profile.connector_profiles,
			       find_conn_id(id));
  }
  
  /*!
   * @if jp
   * @brief ConnectorProfile ���ɲä⤷���Ϲ���
   * @else
   * @brief Append or update the ConnectorProfile list
   * @endif
   */
  void
  PortBase::updateConnectorProfile(const ConnectorProfile& connector_profile)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.connector_profiles,
				find_conn_id(connector_profile.connector_id));
    
    if (index < 0)
      {
	CORBA_SeqUtil::push_back(m_profile.connector_profiles,
				 connector_profile);
      }
    else
      {
	m_profile.connector_profiles[index] = connector_profile;
      }
  }
  
  /*!
   * @if jp
   * @brief ConnectorProfile ��������
   * @else
   * @brief Delete the ConnectorProfile
   * @endif
   */
  bool PortBase::eraseConnectorProfile(const char* id)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.connector_profiles,
				find_conn_id(id));
    if (index < 0) return false;
    
    CORBA_SeqUtil::erase(m_profile.connector_profiles, index);
    return true;
  }
  
  /*!
   * @if jp
   * @brief PortInterfaceProfile �� ���󥿡��ե���������Ͽ����
   * @else
   * @brief Append an interface to the PortInterfaceProfile
   * @endif
   */
  bool PortBase::appendInterface(const char* instance_name,
				 const char* type_name,
				 PortInterfacePolarity pol)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.interfaces,
				find_interface(instance_name, pol));
    
    if (index >= 0) return false;
    // setup PortInterfaceProfile
    PortInterfaceProfile prof;
    prof.instance_name = CORBA::string_dup(instance_name);
    prof.type_name     = CORBA::string_dup(type_name);
    prof.polarity      = pol;
    CORBA_SeqUtil::push_back(m_profile.interfaces, prof);
    
    return true;
  }
  
  /*!
   * @if jp
   * @brief PortInterfaceProfile ���饤�󥿡��ե�������Ͽ��������
   * @else
   * @brief Delete the interface registration from the PortInterfaceProfile
   * @endif
   */
  bool PortBase::deleteInterface(const char* name, PortInterfacePolarity pol)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.interfaces,
				find_interface(name, pol));
    
    if (index < 0) return false;
    
    CORBA_SeqUtil::erase(m_profile.interfaces, index);
    return true;
  }

  /*!
   * @if jp
   * @brief ¸�ߤ��ʤ��ݡ��Ȥ�disconnect���롣
   * @else
   * @brief Disconnect ports that doesn't exist. 
   * @endif
   */
  void PortBase::updateConnectors()
  {
    std::vector<std::string> connector_ids;
    {
// Why RtORB copies ConnectorProfile?
#ifndef ORB_IS_RTORB
      Guard guard(m_profile_mutex);
      ConnectorProfileList& clist(m_profile.connector_profiles);

      for (CORBA::ULong i(0); i < clist.length(); ++i)
        {
          if (!checkPorts(clist[i].ports))
            {
              const char* id(clist[i].connector_id);
              connector_ids.push_back(id);
              RTC_WARN(("Dead connection: %s", id));
            }
        }
#else // ORB_IS_RTORB
      ConnectorProfileList* clist;
      clist = new ConnectorProfileList(m_profile.connector_profiles);

      for (CORBA::ULong i(0); i < clist->length(); ++i)
        {
          if (!checkPorts((*clist)[i].ports))
            {
              const char* id((*clist)[i].connector_id);
              connector_ids.push_back(id);
              RTC_WARN(("Dead connection: %s", id));
            }
        }
      delete clist;
#endif // ORB_IS_RTORB
    }
    std::vector<std::string>::iterator it, it_end;

    for (std::vector<std::string>::iterator it(connector_ids.begin());
         it != connector_ids.end(); ++it)
      {
        this->disconnect((*it).c_str());
      }
  }
  
  /*!
   * @if jp
   * @brief �ݡ��Ȥ�¸�ߤ��ǧ���롣
   * @else
   * @brief Existence of ports
   * @endif
   */
#ifndef ORB_IS_RTORB
  bool PortBase::checkPorts(::RTC::PortServiceList& ports)
#else // ORB_IS_RTORB
  bool PortBase::checkPorts(RTC_PortServiceList& ports)
#endif // ORB_IS_RTORB
  {
    for (CORBA::ULong i(0), len(ports.length()); i < len; ++i)
      {
        try
          {
            if (ports[i]->_non_existent())
              {
                RTC_WARN(("Dead Port reference detected."));
                return false;
              }
          }
        catch (...)
          {
            return false;
          }
      }
    return true;
  }

}; // namespace RTC
