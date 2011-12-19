// -*- C++ -*-
/*!
 * @file   PortBaseTests.cpp
 * @brief  PortBase test class
 * @date   $Date: 2008/02/08 10:57:23 $
 * @author Shinji Kurihara
 *         Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortBaseTests.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

/*
 * $Log: PortBaseTests.cpp,v $
 * Revision 1.2  2008/02/08 10:57:23  arafune
 * Some tests were added.
 *
 * Revision 1.1  2007/12/20 07:50:17  arafune
 * *** empty log message ***
 *
 * Revision 1.3  2007/04/13 15:05:10  n-ando
 * Now RTC::OK becomes RTC::RTC_OK in RTC.idl.
 *
 * Revision 1.2  2007/01/12 14:44:43  n-ando
 * Some fixes for distribution control.
 *
 * Revision 1.1  2006/11/27 08:35:12  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.2  2006/11/13 12:30:06  kurihara
 *
 * document is added.
 *
 * Revision 1.1  2006/11/08 01:19:07  kurihara
 *
 * test program for PortBase class.
 *
 */

#ifndef PortBase_cpp
#define PortBase_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <vector>
#include <string>
#include <rtm/RTC.h>
#include <rtm/PortBase.h>
#include <rtm/RTObject.h>
#include <rtm/PortCallback.h>

/*!
 * @class PortBaseTests class
 * @brief PortBase test
 */

namespace PortBase
{

  class ConnectionCallbackMock : public RTC::ConnectionCallback
  {
  public:
    ConnectionCallbackMock(const char* name) : m_name(name) {}
    virtual ~ConnectionCallbackMock()
    {
      //std::cout << "dtor of " << m_name << std::endl;
    }

    virtual void operator()(RTC::ConnectorProfile& profile)
    {
      std::cout << "---------------------------------------------"   << std::endl;
      std::cout << "Connection Callback: " << m_name                 << std::endl;
      std::cout << "Profile::name: " << profile.name           << std::endl;
      std::cout << "---------------------------------------------"   << std::endl;
    };
    std::string m_name;
  };


  class PortBaseMock : public RTC::PortBase
  {
  public:
		
    PortBaseMock(const RTC::PortProfile& profile)
    {
      this->m_profile = profile;
      this->m_profile.connector_profiles[0].ports.length(1);
      this->m_profile.connector_profiles[0].ports[0] = this->m_objref;
      this->m_profile.port_ref = this->m_objref;
    }

    const std::string getUUID() const
    {
      return RTC::PortBase::getUUID();
    }
		
    virtual RTC::ReturnCode_t notify_connect(RTC::ConnectorProfile& connector_profile)
      throw (CORBA::SystemException)
    {
      _notifyConnectTimes.push_back(getNow());
      return PortBase::notify_connect(connector_profile);
    }
		
    virtual RTC::ReturnCode_t notify_disconnect(const char* connector_id)
      throw (CORBA::SystemException)
    {
      _notifyDisconnectTimes.push_back(getNow());
      return PortBase::notify_disconnect(connector_id);
    }
    void erase_m_profile(void) 
    {
      CORBA_SeqUtil::erase(this->m_profile.connector_profiles, 0);
    }
		
  protected:
	
    virtual RTC::ReturnCode_t publishInterfaces(RTC::ConnectorProfile& connector_profile)
    {
      _publishIfsTimes.push_back(getNow());
      return RTC::RTC_OK;
    }
		
    virtual RTC::ReturnCode_t subscribeInterfaces(const RTC::ConnectorProfile& connector_profile)
    {
      _subscribeIfsTimes.push_back(getNow());
      return RTC::RTC_OK;
    }
		
    virtual void unsubscribeInterfaces(const RTC::ConnectorProfile& connector_profile)
    {
      _unsubscribeIfsTimes.push_back(getNow());
    }
    virtual void activateInterfaces()
    {
    }
    virtual void deactivateInterfaces()
    {
    }
	
  private:
	
    std::vector<timeval> _notifyConnectTimes;
    std::vector<timeval> _notifyDisconnectTimes;
    std::vector<timeval> _publishIfsTimes;
    std::vector<timeval> _subscribeIfsTimes;
    std::vector<timeval> _unsubscribeIfsTimes;
	
  private:
	
    timeval getNow() const
    {
      timeval now;
      gettimeofday(&now, 0);
      return now;
    }
		
  public:
	
    const std::vector<timeval>& getNotifyConnectTimes() const
    {
      return _notifyConnectTimes;
    }
		
    const std::vector<timeval>& getNotifyDisconnectTimes() const
    {
      return _notifyDisconnectTimes;
    }
		
    const std::vector<timeval>& getPublishIfsTimes() const
    {
      return _publishIfsTimes;
    }
		
    const std::vector<timeval>& getSubscribeIfsTimes() const
    {
      return _subscribeIfsTimes;
    }
		
    const std::vector<timeval>& getUnsubscribeIfsTimes() const
    {
      return _unsubscribeIfsTimes;
    }
  };

  
  int g_argc;
  std::vector<std::string> g_argv;

  class PortBaseTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PortBaseTests);
		
    CPPUNIT_TEST(test_get_port_profile);
    CPPUNIT_TEST(test_getPortProfile);
    CPPUNIT_TEST(test_get_connector_profiles);
    CPPUNIT_TEST(test_get_connector_profile);
    CPPUNIT_TEST(test_connect);
    CPPUNIT_TEST(test_notify_connect);
    CPPUNIT_TEST(test_disconnect);
    CPPUNIT_TEST(test_setName);
    CPPUNIT_TEST(test_getProfile);
    CPPUNIT_TEST(test_setPortRef);
    CPPUNIT_TEST(test_getPortRef);
    CPPUNIT_TEST(test_getUUID);
    CPPUNIT_TEST(test_disconnect_all);
    CPPUNIT_TEST(test_setOwner);
		
    CPPUNIT_TEST_SUITE_END();
		
  private:
	
    CORBA::ORB_ptr m_orb;
    RTC::PortBase* m_pPortBase;
    RTC::PortBase* m_pPortBase_2;
    RTC::PortBase* m_pPortBase_3;

  public:
    ConnectionCallbackMock* m_on_publish;
    ConnectionCallbackMock* m_on_subscribe;
    ConnectionCallbackMock* m_on_connected;
    ConnectionCallbackMock* m_on_unsubscribe;
    ConnectionCallbackMock* m_on_disconnected;
    ConnectionCallbackMock* m_on_connection_lost;
	
    /*!
     * @brief Constructor
     */
    PortBaseTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~PortBaseTests()
    {
    }
		
    /*!
     * @brief �����
     *    (1) ORB�ν����,POA��activate
     *    (2) PortBase�Υ��󥹥�������
     *    (3) PortInterfaceProfile���֥����������ǤΥ��å�
     *    (4) PortInterfaceProfileList���֥�����������
     *        (PortProfile������)�Υ��å�
     *    (5) ConnectorProfile���֥����������ǤΥ��å�
     *    (6) ConnectorProfileList���֥�����������(PortProfile������)�Υ��å�
     *    (7) PortProfile���֥����������ǤΥ��å�
     *    (8) PortProfile���֥������ȤΥ��å�
     */
    virtual void setUp()
    {
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }

      // ORB�ν����
      m_orb = CORBA::ORB_init(g_argc, argv);
      PortableServer::POA_ptr poa = PortableServer::POA::_narrow(
				m_orb->resolve_initial_references("RootPOA"));
			
      // PortProfile.interfaces�ι��۽���
      RTC::PortInterfaceProfile portIfProfile;
      portIfProfile.instance_name = "PortInterfaceProfile-instance_name";
      portIfProfile.type_name = "PortInterfaceProfile-type_name";
      portIfProfile.polarity = RTC::REQUIRED;

      RTC::PortInterfaceProfileList portIfProfiles;
      portIfProfiles.length(1);
      portIfProfiles[0] = portIfProfile;

      // PortProfile.connector_profiles�ι��۽���
      SDOPackage::NameValue connProfileProperty;
      connProfileProperty.name = "ConnectorProfile-properties0-name";
      connProfileProperty.value <<= CORBA::Float(1.1);
			
      SDOPackage::NVList connProfileProperties;
      connProfileProperties.length(1);
      connProfileProperties[0] = connProfileProperty;
      RTC::ConnectorProfile connProfile;
      connProfile.name = "ConnectorProfile-name";
      connProfile.connector_id = "connect_id0";
      connProfile.properties = connProfileProperties;

      RTC::ConnectorProfileList connProfiles;
      connProfiles.length(1);
      connProfiles[0] = connProfile;

      // PortProfile.properties�ι��۽���
      SDOPackage::NameValue portProfileProperty;
      portProfileProperty.name = "PortProfile-properties0-name";
      portProfileProperty.value <<= CORBA::Float(2.2);
      SDOPackage::NVList portProfileProperties;
      portProfileProperties.length(1);
      portProfileProperties[0] = portProfileProperty;

      // PortProfile���ۤ���
      RTC::PortProfile portProfile;
      portProfile.name = "inport0";
      portProfile.interfaces = portIfProfiles;
      portProfile.connector_profiles = connProfiles;
      portProfile.properties = portProfileProperties;

      // PortBase�Υ��󥹥��󥹤���������
      m_pPortBase = new PortBaseMock(portProfile);
      m_pPortBase_2 = new PortBaseMock(portProfile);
      m_pPortBase_3 = new PortBaseMock(portProfile);

      // POA�����������			
      PortableServer::POAManager_var poaMgr = poa->the_POAManager();
      poaMgr->activate();

      m_on_publish = new ConnectionCallbackMock("OnPublishInterfaces");
      m_on_subscribe = new ConnectionCallbackMock("OnSubscribeInterfaces");
      m_on_connected = new ConnectionCallbackMock("OnConnected");
      m_on_unsubscribe = new ConnectionCallbackMock("OnUnsubscribeInterfaces");
      m_on_disconnected = new ConnectionCallbackMock("OnDisconnected");
      m_on_connection_lost = new ConnectionCallbackMock("OnConnectionLost");

      m_pPortBase->setOnPublishInterfaces(m_on_publish);
      m_pPortBase->setOnSubscribeInterfaces(m_on_subscribe);
      m_pPortBase->setOnConnected(m_on_connected);
      m_pPortBase->setOnUnsubscribeInterfaces(m_on_unsubscribe);
      m_pPortBase->setOnDisconnected(m_on_disconnected);
      m_pPortBase->setOnConnectionLost(m_on_connection_lost);

    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    {
/*
      delete m_on_connection_lost;
      delete m_on_disconnected;
      delete m_on_unsubscribe;
      delete m_on_connected;
      delete m_on_subscribe;
      delete m_on_publish;
      delete m_pPortBase_3;
      delete m_pPortBase_2;
      delete m_pPortBase;
*/
      //if (m_orb != 0) {
      // m_orb->destroy();
      // m_orb = 0;
      // m_pPortBase = 0;
      // }
    }
		
    /*!
     * @brief get_port_profile()�᥽�åɤΥƥ���
     * 
     * - ���֥������Ȼ��ȷ�ͳ�ǡ�get_port_profile()�����������������Ǥ��뤫��
     * - PortProfile.name�������������Ǥ��뤫��
     * - PortProfile.interface�������������Ǥ��뤫��
     * - PortProfile.connector_profiles�������������Ǥ��뤫��
     * - PortProfile.properties�������������Ǥ��뤫��
     */
    void test_get_port_profile()
    {
      // (1) ���֥������Ȼ��ȷ�ͳ�ǡ�get_port_profile()�����������������Ǥ��뤫��
      // get_port_profile()��CORBA���󥿥ե������ʤΤǡ����֥������Ȼ��ȷ�ͳ�ǥ�����������
      // CORBA���󥿥ե������Ȥ��Ƶ�ǽ���Ƥ��뤳�Ȥ��ǧ����
      const RTC::PortService_ptr portRef = m_pPortBase->getPortRef();
      const RTC::PortProfile* pPortProfile = portRef->get_port_profile();
			
      // (2) PortProfile.name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("inport0"),
			   std::string(pPortProfile->name));

      // (3) PortProfile.interface�������������Ǥ��뤫��
      const RTC::PortInterfaceProfile& portIfProfile = pPortProfile->interfaces[0];
      // (3-a) PortInterfaceProfile.instance_name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("PortInterfaceProfile-instance_name"),
			   std::string(portIfProfile.instance_name));

      // (3-b) PortInterfaceProfile.type_name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("PortInterfaceProfile-type_name"),
			   std::string(portIfProfile.type_name));

      // (3-c) PortInterfaceProfile.polarity�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(RTC::REQUIRED, portIfProfile.polarity);

      // (4) PortProfile.connector_profiles�������������Ǥ��뤫��
      const RTC::ConnectorProfile& connProfile = pPortProfile->connector_profiles[0];
      // (4-a) ConnectorProfile.name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("ConnectorProfile-name"),
			   std::string(connProfile.name));
      
      // (4-b) ConnectorProfile.connector_id�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("connect_id0"),
			   std::string(connProfile.connector_id));
			
      // (4-c) ConnectorProfile.properties�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("ConnectorProfile-properties0-name"),
			   std::string(connProfile.properties[0].name));
			
      {
	CORBA::Float value;
	connProfile.properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(1.1), value);
      }
			
      // (5) PortProfile.properties�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("PortProfile-properties0-name"),
			   std::string(pPortProfile->properties[0].name));

      {
	CORBA::Float value;
	pPortProfile->properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(2.2), value);
      }
    }
		
    /*!
     * @brief getPortProfile()�᥽�åɤΥƥ���
     * 
     * - PortProfile.name�������������Ǥ��뤫��
     * - PortProfile.interface�������������Ǥ��뤫��
     * - PortProfile.connector_profiles�������������Ǥ��뤫��
     * - PortProfile.properties�������������Ǥ��뤫��
     */
    void test_getPortProfile()
    {
      const RTC::PortProfile& portProfile = m_pPortBase->getPortProfile();
			
      // (1) PortProfile.name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("inport0"),
			   std::string(portProfile.name));

      // (2) PortProfile.interface�������������Ǥ��뤫��
      const RTC::PortInterfaceProfile& portIfProfile = portProfile.interfaces[0];
      // (2-a) PortInterfaceProfile.instance_name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("PortInterfaceProfile-instance_name"),
			   std::string(portIfProfile.instance_name));

      // (2-b) PortInterfaceProfile.type_name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("PortInterfaceProfile-type_name"),
			   std::string(portIfProfile.type_name));

      // (2-c) PortInterfaceProfile.polarity�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(RTC::REQUIRED, portIfProfile.polarity);

      // (3) PortProfile.connector_profiles�������������Ǥ��뤫��
      const RTC::ConnectorProfile& connProfile = portProfile.connector_profiles[0];
      // (3-a) ConnectorProfile.name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("ConnectorProfile-name"),
			   std::string(connProfile.name));
      
      // (3-b) ConnectorProfile.connector_id�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("connect_id0"),
			   std::string(connProfile.connector_id));
			
      // (3-c) ConnectorProfile.properties�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("ConnectorProfile-properties0-name"),
			   std::string(connProfile.properties[0].name));
			
      {
	CORBA::Float value;
	connProfile.properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(1.1), value);
      }
			
      // (4) PortProfile.properties�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("PortProfile-properties0-name"),
			   std::string(portProfile.properties[0].name));

      {
	CORBA::Float value;
	portProfile.properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(2.2), value);
      }
    }
		
    /*!
     * @brief get_connector_profiles()�᥽�åɤΥƥ���
     * 
     * - ���֥������Ȼ��ȷ�ͳ�ǡ�get_connector_profiles()�����������������Ǥ��뤫��
     * - ConnectorProfile.name�������������Ǥ��뤫��
     * - ConnectorProfile.connector_id�������������Ǥ��뤫��
     * - ConnectorProfile.properties�������������Ǥ��뤫��
     */
    void test_get_connector_profiles()
    {
      // (1) ���֥������Ȼ��ȷ�ͳ�ǡ�get_connector_profiles()�����������������Ǥ��뤫��
      // get_connector_profiles()��CORBA���󥿥ե������ʤΤǡ����֥������Ȼ��ȷ�ͳ�ǥ�����������
      // CORBA���󥿥ե������Ȥ��Ƶ�ǽ���Ƥ��뤳�Ȥ��ǧ����
      const RTC::PortService_ptr portRef = m_pPortBase->getPortRef();
      const RTC::ConnectorProfileList* pConnProfList = portRef->get_connector_profiles();

      // ConnectorProfileList���ConnectorProfile�Υ����å�
      const RTC::ConnectorProfile& connProfile = (*pConnProfList)[0];
      // (2) ConnectorProfile.name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("ConnectorProfile-name"),
			   std::string(connProfile.name));
			
      // (3) ConnectorProfile.connector_id�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("connect_id0"),
			   std::string(connProfile.connector_id));

      // (4) ConnectorProfile.properties�������������Ǥ��뤫��
      const SDOPackage::NameValue& property = connProfile.properties[0];
      // (4-a) name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("ConnectorProfile-properties0-name"),
			   std::string(property.name));
			
      // (4-b) value�������������Ǥ��뤫��
      {
	CORBA::Float value;
	property.value >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(1.1), value);
      }
    }
		
    /*!
     * @brief get_connector_profile()�᥽�åɤΥƥ���
     * 
     * - ���֥������Ȼ��ȷ�ͳ�ǡ�get_connector_profile()�����������������Ǥ��뤫��
     * - ConnectorProfile.name�������������Ǥ��뤫��
     * - ConnectorProfile.connector_id�������������Ǥ��뤫��
     * - ConnectorProfile.properties�������������Ǥ��뤫��
     */
    void test_get_connector_profile()
    {
      // (1) ���֥������Ȼ��ȷ�ͳ�ǡ�get_connector_profile()�����������������Ǥ��뤫��
      // get_connector_profile()��CORBA���󥿥ե������ʤΤǡ����֥������Ȼ��ȷ�ͳ�ǥ�����������
      // CORBA���󥿥ե������Ȥ��Ƶ�ǽ���Ƥ��뤳�Ȥ��ǧ����
      const RTC::PortService_ptr portRef = m_pPortBase->getPortRef();
      const RTC::ConnectorProfile* pConnProfile = portRef->get_connector_profile("connect_id0");

      // (2) ConnectorProfile.name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("ConnectorProfile-name"),
			   std::string(pConnProfile->name));

      // (3) ConnectorProfile.connector_id�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("connect_id0"),
			   std::string(pConnProfile->connector_id));

      // (4) ConnectorProfile.properties�������������Ǥ��뤫��
      const SDOPackage::NameValue& property = pConnProfile->properties[0];
      // (4-a) name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("ConnectorProfile-properties0-name"),
			   std::string(property.name));

      // (4-b) value�������������Ǥ��뤫��
      {
	CORBA::Float value;
	property.value >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(1.1), value);
      }
    }
		
    /*!
     * @brief connect()�᥽�åɤΥƥ���
     * 
     * - ���֥������Ȼ��ȷ�ͳ�ǡ�connect()�����������������Ǥ��뤫��
     * - ��³���������뤫��
     * - ��³����notify_connect()���տޤɤ���ˣ�������ƤӽФ��줿����
     */
    void test_connect()
    {
      // (1) ���֥������Ȼ��ȷ�ͳ�ǡ�connect()�����������������Ǥ��뤫��
      // connect()��CORBA���󥿥ե������ʤΤǡ����֥������Ȼ��ȷ�ͳ�ǥ�����������
      // CORBA���󥿥ե������Ȥ��Ƶ�ǽ���Ƥ��뤳�Ȥ��ǧ����
      RTC::PortService_ptr portRef = m_pPortBase->getPortRef();
			
      // ��³����ɬ�פȤʤ�ConnectorProfile���ۤ���
      RTC::ConnectorProfile connProfile;
      connProfile.name = "ConnectorProfile-name";
      connProfile.connector_id = "connect_id1";
      connProfile.ports.length(1);
      connProfile.ports[0] = portRef;

      // (2) ��³���������뤫��
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, portRef->connect(connProfile));
      
      // (3) ��³����notify_connect()���տޤɤ���ˣ�������ƤӽФ��줿����
      const PortBaseMock* pPortBaseMock = dynamic_cast<const PortBaseMock*>(m_pPortBase);
      CPPUNIT_ASSERT(pPortBaseMock != 0);
      CPPUNIT_ASSERT_EQUAL(1, (int) pPortBaseMock->getNotifyConnectTimes().size());
    }
		
    /*!
     * @brief notify_connect()�᥽�åɤΥƥ���
     */
    void test_notify_connect()
    {
      // notify_connect()�᥽�åɤϡ�test_connect�ˤƴ���Ū�˥ƥ��Ȥ���Ƥ���Τǡ������Ǥϥƥ������פǤ���
    }
		
    /*!
     * @brief disconnect()�᥽�åɤΥƥ���
     * 
     * - ���֥������Ȼ��ȷ�ͳ�ǡ�disconnect()�����������������Ǥ��뤫��
     * - ���Ǥ��������뤫��
     * - ���ǻ���notify_disconnect()�����տޤɤ��꣱������ƤӽФ���Ƥ��뤫��
     */
    void test_disconnect()
    {
      // (1) ���֥������Ȼ��ȷ�ͳ�ǡ�disconnect()�����������������Ǥ��뤫��
      // disconnect()��CORBA���󥿥ե������ʤΤǡ����֥������Ȼ��ȷ�ͳ�ǥ�����������
      // CORBA���󥿥ե������Ȥ��Ƶ�ǽ���Ƥ��뤳�Ȥ��ǧ����
      RTC::PortService_ptr portRef = m_pPortBase->getPortRef();
			
      // ��³����ɬ�פȤʤ�ConnectorProfile���ۤ���
      RTC::ConnectorProfile connProfile;
      connProfile.name = "ConnectorProfile-name";
      connProfile.connector_id = "connect_id2";
      connProfile.ports.length(1);
      connProfile.ports[0] = portRef;

      // �ޤ�����³����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, portRef->connect(connProfile));
      
      // (2) ���Ǥ��������뤫��
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, portRef->disconnect(connProfile.connector_id));
      
      // (3) ���ǻ���notify_disconnect()�����տޤɤ��꣱������ƤӽФ���Ƥ��뤫��
      const PortBaseMock* pPortBaseMock = dynamic_cast<const PortBaseMock*>(m_pPortBase);
      CPPUNIT_ASSERT(pPortBaseMock != 0);
      CPPUNIT_ASSERT_EQUAL(1, (int) pPortBaseMock->getNotifyDisconnectTimes().size());
    }
		
    void test_disconnect_all()
    {
      RTC::PortService_ptr portRef_1 = m_pPortBase->getPortRef();
      RTC::PortService_ptr portRef_2 = m_pPortBase_2->getPortRef();
      RTC::PortService_ptr portRef_3 = m_pPortBase_3->getPortRef();

      // �����Ǥϡ�  setUp() �� PortBaseMock�Υ��󥹥ȥ饯�����
      // �ƥ��Ȥΰ����ꤵ��Ƥ��� connect_id0 �����פʤ���������
      // connect_id0 ��
      //  get_port_profile(),getPortProfile(),get_connector_profiles() 
      // �Υƥ��Ȥǻ��Ѥ��Ƥ���
      PortBaseMock* pPBMock
                 = dynamic_cast<PortBaseMock*>(m_pPortBase);
      pPBMock->erase_m_profile();


      RTC::ConnectorProfile connProfile;
      connProfile.name = "ConnectorProfile-name";
      connProfile.connector_id = "connect_id3";
      connProfile.ports.length(3);
      connProfile.ports[0] = portRef_1;
      connProfile.ports[1] = portRef_2;
      connProfile.ports[2] = portRef_3;
      
      const PortBaseMock* pPortBaseMock_1 = dynamic_cast<const PortBaseMock*>(m_pPortBase);
      CPPUNIT_ASSERT(pPortBaseMock_1 != 0);
      CPPUNIT_ASSERT_EQUAL(0, (int) pPortBaseMock_1->getNotifyDisconnectTimes().size());
      const PortBaseMock* pPortBaseMock_2 = dynamic_cast<const PortBaseMock*>(m_pPortBase_2);
      CPPUNIT_ASSERT(pPortBaseMock_2 != 0);
      CPPUNIT_ASSERT_EQUAL(0, (int) pPortBaseMock_2->getNotifyDisconnectTimes().size());
      const PortBaseMock* pPortBaseMock_3 = dynamic_cast<const PortBaseMock*>(m_pPortBase_3);
      CPPUNIT_ASSERT(pPortBaseMock_3 != 0);
      CPPUNIT_ASSERT_EQUAL(0, (int) pPortBaseMock_3->getNotifyDisconnectTimes().size());
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, portRef_1->connect(connProfile));
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, portRef_1->disconnect_all());
      CPPUNIT_ASSERT_EQUAL(1, (int) pPortBaseMock_1->getNotifyDisconnectTimes().size());
      CPPUNIT_ASSERT_EQUAL(1, (int) pPortBaseMock_2->getNotifyDisconnectTimes().size());
      CPPUNIT_ASSERT_EQUAL(1, (int) pPortBaseMock_3->getNotifyDisconnectTimes().size());

    }
		
    /*!
     * @brief setName()�᥽�åɤΥƥ���
     * 
     * - setName()�ˤ�ꡢ�տޤɤ����PortProfile.name���񤭴������Ƥ��뤫��
     */
    void test_setName()
    {
      // setName()���Ѥ��ơ�PortProfile.name��񤭴�����
      m_pPortBase->setName("inport0-changed");
			
      // setName()���Ѥ��ơ�PortProfile.name��񤭴�����
      std::string str(m_pPortBase->getName());
      CPPUNIT_ASSERT_EQUAL(std::string("inport0-changed"), str);
			
      // setName()�ˤ�ꡢ�տޤɤ����PortProfile.name���񤭴������Ƥ��뤫��
      const RTC::PortProfile& portProfile = m_pPortBase->getPortProfile();
      CPPUNIT_ASSERT_EQUAL(std::string("inport0-changed"), std::string(portProfile.name));
    }
		
    /*!
     * @brief getProfile()�᥽�åɤΥƥ���
     * 
     * - PortProfile.name�������������Ǥ��뤫��
     * - PortProfile.interfaces�������������Ǥ��뤫��
     * - PortProfile.connector_profiles�������������Ǥ��뤫��
     * - PortProfile.properties�������������Ǥ��뤫��
     */
    void test_getProfile()
    {
      const RTC::PortProfile& portProfile = m_pPortBase->getProfile();

      // (1) PortProfile.name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(std::string("inport0"), std::string(portProfile.name));

      // (2) PortProfile.interfaces�������������Ǥ��뤫��
      const RTC::PortInterfaceProfile& portIfProfile = portProfile.interfaces[0];
      // (2-a) PortInterfaceProfile.instance_name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("PortInterfaceProfile-instance_name"),
			   std::string(portIfProfile.instance_name));

      // (2-b) PortInterfaceProfile.type_name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("PortInterfaceProfile-type_name"),
			   std::string(portIfProfile.type_name));
			
      // (2-c) PortInterfaceProfile.polarity�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(RTC::REQUIRED, portIfProfile.polarity);

      // (3) PortProfile.connector_profiles�������������Ǥ��뤫��
      const RTC::ConnectorProfile& connProfile = portProfile.connector_profiles[0];
      // (3-a) ConnectorProfile.name�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("ConnectorProfile-name"),
			   std::string(connProfile.name));
			
      // (3-b) ConnectorProfile.connector_id�������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(
			   std::string("connect_id0"),
			   std::string(connProfile.connector_id));

      // (3-c) ConnectorPofile.properties�������������Ǥ��뤫��
      {
	const SDOPackage::NameValue& property = connProfile.properties[0];
	// (3-c-1) name�������������Ǥ��뤫��
	CPPUNIT_ASSERT_EQUAL(
			     std::string("ConnectorProfile-properties0-name"),
			     std::string(property.name));
			
	// (3-c-2) value�������������Ǥ��뤫��
	{
	  CORBA::Float value;
	  property.value >>= value;
	  CPPUNIT_ASSERT_EQUAL(CORBA::Float(1.1), value);
	}
      }

      // (4) PortProfile.properties�������������Ǥ��뤫��
      {
	const SDOPackage::NameValue& property = portProfile.properties[0];
	// (4-a) name�������������Ǥ��뤫��
	CPPUNIT_ASSERT_EQUAL(
			     std::string("PortProfile-properties0-name"),
			     std::string(property.name));
				
	// (4-b) value�������������Ǥ��뤫��
	{
	  CORBA::Float value;
	  property.value >>= value;
	  CPPUNIT_ASSERT_EQUAL(CORBA::Float(2.2), value);
	}
      }
    }
		
    /*!
     * @brief setPortRef()�᥽�åɤΥƥ���
     * 
     * - setPortRef()���Ѥ��ơ�PortBase���֥������Ȼ��Ȥ�����������Ǥ��뤫��
     */
    void test_setPortRef()
    {
      // ��ö������Ѥߤ�PortBase���֥������Ȼ��Ȥ�ꥻ�åȤ��Ƥ���
      m_pPortBase->_remove_ref();

      // setPortRef()���Ѥ��ơ�PortBase���֥������Ȼ��Ȥ�����������Ǥ��뤫��
      // (getPortRef()���Ѥ��ơ�Port���󥿥ե������Υ��֥������Ȼ��Ȥ��������
      // �����������Ȥ������餫�������ꤷ�����ȤȰ��פ��뤳�Ȥ��ǧ����)
      RTC::PortService_var port = m_pPortBase->_this();
      RTC::PortService_ptr portRef = port._retn();
      m_pPortBase->setPortRef(portRef);

      CPPUNIT_ASSERT_EQUAL(portRef, m_pPortBase->getPortRef());
    }

    /*!
     * @brief getPortRef()�᥽�åɤΥƥ���
     */
    void test_getPortRef()
    {
      // test_setPortRef()�ˤ��ƥ��Ȥ���Ƥ���
    }
		
    /*!
     * @brief getUUID()�᥽�åɤΥƥ���
     * 
     * - UUID������Ǥ��뤫���ʶ�ʸ����Ǥʤ����ɤ����Τߤǥ����å���
     */
    void test_getUUID()
    {
      // getUUID()�᥽�åɤ�protected�Ǥ��뤿�ᡢPortBaseMock�˥����󥭥㥹�Ȥ��Ƥ��饢����������
      PortBaseMock* pPortBase = dynamic_cast<PortBaseMock*>(m_pPortBase);
      CPPUNIT_ASSERT(pPortBase != 0);
			
      // UUID������Ǥ��뤫���ʶ�ʸ����Ǥʤ����ɤ����Τߤǥ����å���
      std::string uuid = pPortBase->getUUID();
      CPPUNIT_ASSERT(uuid.length() > 0);
      //std::cout << std::endl << "uuid: " << uuid << std::endl;
    }
    /*!
     * @brief setOwner()�᥽�åɤΥƥ���
     * 
     */
    void test_setOwner()
    {
        PortableServer::POA_ptr poa = PortableServer::POA::_narrow(
				m_orb->resolve_initial_references("RootPOA"));
        RTC::RTObject_impl* obj = new RTC::RTObject_impl(m_orb,poa);
        RTC::RTObject_ptr owner = obj->getObjRef();
        RTC::PortProfile  portprofile = m_pPortBase->getProfile();
        CPPUNIT_ASSERT(CORBA::is_nil(portprofile.owner));
        m_pPortBase->setOwner(owner);
        portprofile = m_pPortBase->getProfile();
        CPPUNIT_ASSERT(!CORBA::is_nil(portprofile.owner));

        poa->the_POAManager()->deactivate(false, true);
        obj->finalize();
        delete obj;
    }
  };
}; // namespace PortBase

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PortBase::PortBaseTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{

  FORMAT format = TEXT_OUT;
  int target = 0;
  std::string xsl;
  std::string ns;
  std::string fname;
  std::ofstream ofs;

  int i(1);
  while (i < argc)
    {
      std::string arg(argv[i]);
      std::string next_arg;
      if (i + 1 < argc) next_arg = argv[i + 1];
      else              next_arg = "";

      if (arg == "--text") { format = TEXT_OUT; break; }
      if (arg == "--xml")
	{
	  if (next_arg == "")
	    {
	      fname = argv[0];
	      fname += ".xml";
	    }
	  else
	    {
	      fname = next_arg;
	    }
	  format = XML_OUT;
	  ofs.open(fname.c_str());
	}
      if ( arg == "--compiler"  ) { format = COMPILER_OUT; break; }
      if ( arg == "--cerr"      ) { target = 1; break; }
      if ( arg == "--xsl"       )
	{
	  if (next_arg == "") xsl = "default.xsl"; 
	  else                xsl = next_arg;
	}
      if ( arg == "--namespace" )
	{
	  if (next_arg == "")
	    {
	      std::cerr << "no namespace specified" << std::endl;
	      exit(1); 
	    }
	  else
	    {
	      xsl = next_arg;
	    }
	}
      ++i;
    }
  CppUnit::TextUi::TestRunner runner;
  if ( ns.empty() )
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  else
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry(ns).makeTest());
  CppUnit::Outputter* outputter = 0;
  std::ostream* stream = target ? &std::cerr : &std::cout;
  switch ( format )
    {
    case TEXT_OUT :
      outputter = new CppUnit::TextOutputter(&runner.result(),*stream);
      break;
    case XML_OUT :
      std::cout << "XML_OUT" << std::endl;
      outputter = new CppUnit::XmlOutputter(&runner.result(),
					    ofs, "shift_jis");
      static_cast<CppUnit::XmlOutputter*>(outputter)->setStyleSheet(xsl);
      break;
    case COMPILER_OUT :
      outputter = new CppUnit::CompilerOutputter(&runner.result(),*stream);
      break;
    }
  runner.setOutputter(outputter);
  runner.run();
  return 0; // runner.run() ? 0 : 1;
}
#endif // MAIN
#endif // PortBase_cpp
