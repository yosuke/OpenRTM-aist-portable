// -*- C++ -*-
/*!
 * @file   CorbaPortTests.cpp
 * @brief  CorbaPort test class
 * @date   $Date: 2008/04/04 12:06:09 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: CorbaPortTests.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

/*
 * $Log: CorbaPortTests.cpp,v $
 * Revision 1.2  2008/04/04 12:06:09  arafune
 * Refactored some tests. No new tests were added.
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2007/01/04 00:50:38  n-ando
 * *** empty log message ***
 *
 *
 */

#ifndef CorbaPort_cpp
#define CorbaPort_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/CorbaPort.h>
#include <rtm/CorbaConsumer.h>

#include "MyServiceSkel.h"

class MyService_impl
  : public virtual POA_MyService,
    public virtual PortableServer::RefCountServantBase
{
public:
  MyService_impl() : m_hello_world_called(false)
  {
  };

  virtual ~MyService_impl()
  {
  };
	
  void setName(const char* name)
  {
    m_name = name;
  }
	
  char* name()
  {
    return "MyService";
  }
	
  void hello_world()
  {
    m_hello_world_called = true;
  }
	
  void print_msg(const char* msg)
  {
    std::cout << m_name << ": " << msg << std::endl;
  }

  bool is_hello_world_called()
  {
    return m_hello_world_called;
  }
	
private:
  std::string m_name;
  bool m_hello_world_called;
};


/*!
 * @class CorbaPortMock class
 *
 */
class CorbaPortMock
 : public RTC::CorbaPort
{
  public:
    /*!
     *
     */
    CorbaPortMock(const char* name)
    : RTC::CorbaPort(name)
    {
    }
    /*!
     *
     */
    virtual ~CorbaPortMock(void)
    {
    }
    /*!
     *
     */
    void deactivateInterfaces_public()
    {
        deactivateInterfaces();
    }
    /*!
     *
     */
    void activateInterfaces_public()
    {
        activateInterfaces();
    }
};
/*!
 * @class CorbaPortTests class
 * @brief CorbaPort test
 */
namespace CorbaPort
{
  class CorbaPortTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(CorbaPortTests);
    CPPUNIT_TEST(test_get_port_profile);
    CPPUNIT_TEST(test_connect);
    CPPUNIT_TEST(test_disconnect);
    CPPUNIT_TEST(test_registerProvider);
    CPPUNIT_TEST(test_activateInterfaces_deactivateInterfaces);
    CPPUNIT_TEST_SUITE_END();
		
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
		
  public:
    /*!
     * @brief Constructor
     */
    CorbaPortTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~CorbaPortTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      int argc(0);
      char** argv(NULL);
			
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
					    m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();
    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
      try
	{
	  // m_pPOA->destroy(false, false);
	  // m_pPOA->the_POAManager()->deactivate(false, false);
	  // m_pORB->destroy(); 
	}
      catch (...)
	{
	  // do nothing
	}
    }
		
    /*!
     * @brief get_port_profile()�᥽�åɤΥƥ���
     * 
     * - �ץ�ե�������Ρ��ݡ���̾�Τ������������Ǥ��뤫��
     * - ���󥿥ե������ץ�ե�������Ρ�instance_name�������������Ǥ��뤫��
     * - ���󥿥ե������ץ�ե�������Ρ�type_name�������������Ǥ��뤫��
     * - ���󥿥ե������ץ�ե�������Ρ�polarity�������������Ǥ��뤫��
     */
    void test_get_port_profile()
    {
      // �ƥ����оݤȤʤ�CorbaPort��������
      MyService_impl* pMyServiceImpl
	= new MyService_impl(); // will be deleted automatically
      RTC::CorbaConsumer<MyService>* pMyServiceConsumer
	= new RTC::CorbaConsumer<MyService>(); // will be deleted automatically
			
      RTC::CorbaPort* port = new RTC::CorbaPort("name of port");
      coil::Properties dummy;
      port->init(dummy);
      port->registerProvider("MyService (provided)", "Generic (provided)", *pMyServiceImpl);
      port->registerConsumer("MyService (required)", "Generic (required)", *pMyServiceConsumer);
			
      RTC::PortService_var portRef = port->getPortRef();
      RTC::PortProfile* profile = portRef->get_port_profile();

      // �ݡ���̾�Τ������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(std::string("unknown.name of port"), std::string(profile->name));
			
      // ���󥿥ե������ץ�ե����������������餫�������ꤷ�Ƥ��������ƤȰ��פ��뤳�Ȥ��ǧ����
      RTC::PortInterfaceProfileList& profiles = profile->interfaces;
      for (CORBA::ULong i = 0; i < profile->interfaces.length(); ++i)
	{
	  if (std::string(profiles[i].instance_name)
	      == std::string("MyService (provided)"))
	    {
	      // type_name�������������Ǥ��뤫��
	      CPPUNIT_ASSERT_EQUAL(std::string("Generic (provided)"),
				   std::string(profiles[i].type_name));
					
	      // polarity�������������Ǥ��뤫��
	      CPPUNIT_ASSERT_EQUAL(RTC::PROVIDED, profiles[i].polarity);
	    }
	  else if (std::string(profiles[i].instance_name)
		   == std::string("MyService (required)"))
	    {
	      // type_name�������������Ǥ��뤫��
	      CPPUNIT_ASSERT_EQUAL(std::string("Generic (required)"),
				   std::string(profiles[i].type_name));

	      // polarity�������������Ǥ��뤫��
	      CPPUNIT_ASSERT_EQUAL(RTC::REQUIRED, profiles[i].polarity);
	    }
	  else
	    {
	      // ͽ�����ʤ�instance_name���������줿���
	      std::string msg("Unexpected instance_name:");
	      msg += std::string(profiles[i].instance_name);
	      CPPUNIT_FAIL(msg);
	    }
	}

      delete port;
      delete pMyServiceConsumer;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pMyServiceImpl));
      delete pMyServiceImpl;
    }
		
    /*!
     * connect()�᥽�åɡ�����ӡ���������ƤӽФ�����protected�᥽�åɤΥƥ���
     * 
     * - �ݡ���1�Υ��󥷥塼��¦����᥽�åɤ�ƤӽФ��ȡ��ݡ���0�Υץ�Х���¦���տޤɤ���ƤӽФ���뤫��
     * - �ݡ���0�Υ��󥷥塼��¦����᥽�åɤ�ƤӽФ��ȡ��ݡ���1�Υץ�Х���¦���տޤɤ���ƤӽФ���뤫��
     */
    void test_connect()
    {
      // �ݡ���0��������
      MyService_impl* pMyServiceImplA
	= new MyService_impl(); // will be deleted automatically
      RTC::CorbaConsumer<MyService>* pMyServiceConsumerB
	= new RTC::CorbaConsumer<MyService>(); // will be deleted automatically
			
      CorbaPortMock* port0 = new CorbaPortMock("name of port0");
      port0->registerProvider("MyServiceA", "Generic", *pMyServiceImplA);
      port0->registerConsumer("MyServiceB", "Generic", *pMyServiceConsumerB);

      // �ݡ���1��������
      MyService_impl* pMyServiceImplB
	= new MyService_impl(); // will be deleted automatically
      RTC::CorbaConsumer<MyService>* pMyServiceConsumerA
	= new RTC::CorbaConsumer<MyService>(); // will be deleted automatically
			
      CorbaPortMock* port1 = new CorbaPortMock("name of port1");
      port1->registerProvider("MyServiceB", "Generic", *pMyServiceImplB);
      port1->registerConsumer("MyServiceA", "Generic", *pMyServiceConsumerA);
			
      // ��³�ץ�ե������������
      RTC::ConnectorProfile connProfile;
      connProfile.connector_id = "";
      connProfile.name = CORBA::string_dup("name of connector profile");
      connProfile.ports.length(2);
      connProfile.ports[0] = port0->getPortRef();
      connProfile.ports[1] = port1->getPortRef();

      // ��³����
      port0->getPortRef()->connect(connProfile);

      port0->activateInterfaces_public();
      port1->activateInterfaces_public();

      // �ݡ���1�Υ��󥷥塼��¦����᥽�åɤ�ƤӽФ��ȡ��ݡ���0�Υץ�Х���¦���տޤɤ���ƤӽФ���뤫��
      CPPUNIT_ASSERT(! pMyServiceImplA->is_hello_world_called());
      (*pMyServiceConsumerA)->hello_world();
      CPPUNIT_ASSERT(pMyServiceImplA->is_hello_world_called());

      // �ݡ���0�Υ��󥷥塼��¦����᥽�åɤ�ƤӽФ��ȡ��ݡ���1�Υץ�Х���¦���տޤɤ���ƤӽФ���뤫��
      CPPUNIT_ASSERT(! pMyServiceImplB->is_hello_world_called());
      (*pMyServiceConsumerB)->hello_world();
      CPPUNIT_ASSERT(pMyServiceImplB->is_hello_world_called());

//      delete port1;
      delete port0;
      delete pMyServiceConsumerA;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pMyServiceImplB));
      delete pMyServiceImplB;
      delete pMyServiceConsumerB;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pMyServiceImplA));
      delete pMyServiceImplA;
    }
    
    /*!
     * @brief disconnect()�᥽�åɡ�����ӡ���������ƤӽФ�����protected�᥽�åɤΥƥ���
     * 
     * - ��³����������������Ǥ�Ԥ�����⡼�ȥ᥽�åɤθƽФ����տޤɤ��꼺�Ԥ��뤳�Ȥ��ǧ����
     */
    void test_disconnect()
    {
      // �ݡ���0��������
      MyService_impl* pMyServiceImplA
	= new MyService_impl(); // will be deleted automatically
      RTC::CorbaConsumer<MyService>* pMyServiceConsumerB
	= new RTC::CorbaConsumer<MyService>(); // will be deleted automatically
			
      CorbaPortMock* port0 = new CorbaPortMock("name of port0-1");
      port0->registerProvider("MyServiceA-1", "Generic", *pMyServiceImplA);
      port0->registerConsumer("MyServiceB-1", "Generic", *pMyServiceConsumerB);

      // �ݡ���1��������
      MyService_impl* pMyServiceImplB
	= new MyService_impl(); // will be deleted automatically
      RTC::CorbaConsumer<MyService>* pMyServiceConsumerA
	= new RTC::CorbaConsumer<MyService>(); // will be deleted automatically
			
      CorbaPortMock* port1 = new CorbaPortMock("name of port1-1");
      port1->registerProvider("MyServiceB-1", "Generic", *pMyServiceImplB);
      port1->registerConsumer("MyServiceA-1", "Generic", *pMyServiceConsumerA);
			
      // ��³�ץ�ե������������
      RTC::ConnectorProfile connProfile;
      connProfile.connector_id = "id1";
      connProfile.name = CORBA::string_dup("name of connector profile-1");
      connProfile.ports.length(2);
      connProfile.ports[0] = port0->getPortRef();
      connProfile.ports[1] = port1->getPortRef();

      // ��³����
      port0->getPortRef()->connect(connProfile);

      port0->activateInterfaces_public();
      port1->activateInterfaces_public();

      // �ݡ���1�Υ��󥷥塼��¦����᥽�åɤ�ƤӽФ��ȡ��ݡ���0�Υץ�Х���¦���տޤɤ���ƤӽФ���뤫��
      CPPUNIT_ASSERT(! pMyServiceImplA->is_hello_world_called());
      (*pMyServiceConsumerA)->hello_world();
      CPPUNIT_ASSERT(pMyServiceImplA->is_hello_world_called());
			
      // ���Ǥ���
      port0->getPortRef()->disconnect(connProfile.connector_id);
			
      // �ݡ���0�Υ��󥷥塼��¦����᥽�åɤ�ƤӽФ����ߤ�ȡ��տޤɤ���˼��Ԥ��뤫��
      try
	{
	  CPPUNIT_ASSERT(! pMyServiceImplB->is_hello_world_called());
	  (*pMyServiceConsumerB)->hello_world();
							
	  CPPUNIT_FAIL("Couldn't catch no exceptions. Disconnection failed.");
	}
      catch(...)
	{
	  // Properly disconnected.
	}

//      delete port1;
      delete port0;
      delete pMyServiceConsumerA;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pMyServiceImplB));
      delete pMyServiceImplB;
      delete pMyServiceConsumerB;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pMyServiceImplA));
      delete pMyServiceImplA;
    }
    /*!
     * @brief registerProvider()�᥽�åɤΥƥ���
     * 
     */
    void test_registerProvider(void)
    {
      MyService_impl* pImpl0
	= new MyService_impl();

      MyService_impl* pImpl1
	= new MyService_impl();
			
			
      CorbaPortMock* port0 = new CorbaPortMock("name of port");
      bool ret;
      ret = port0->registerProvider("registerProvider0", "Generic", *pImpl0);
      CPPUNIT_ASSERT_EQUAL(true,ret);

      //������Ͽ���Ƥ��륤�󥹥���̾�ȥ��֥������Ȥ���Ͽ������硢false���֤���
      ret = port0->registerProvider("registerProvider0", "Generic", *pImpl0);
      CPPUNIT_ASSERT_EQUAL(false,ret);

      //������Ͽ���Ƥ��륤�󥹥���̾����Ͽ������硢false���֤���
      ret = port0->registerProvider("registerProvider0", "Generic", *pImpl1);
      CPPUNIT_ASSERT_EQUAL(false,ret);
     
      //�̤ʥ��󥹥���̾�Ǵ�����Ͽ���Ƥ��륪�֥������Ȥ���Ͽ������硢true���֤���
      //   false���֤�����Ͽ����롣
      ret = port0->registerProvider("registerProvider1", "Generic", *pImpl0);
      CPPUNIT_ASSERT_EQUAL(true,ret);

      //��Ͽ���Ƥʤ����󥹥���̾�ȥ��֥������Ȥ���Ͽ������硢true���֤���
      ret = port0->registerProvider("registerProvider2", "Generic", *pImpl1);
      CPPUNIT_ASSERT_EQUAL(true,ret);

      port0->deactivateInterfaces_public();

      delete port0;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pImpl1));
      delete pImpl1;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pImpl0));
      delete pImpl0;
    }
    /*!
     * @brief registerProvider()�᥽�åɤΥƥ���
     * 
     */
    void test_activateInterfaces_deactivateInterfaces(void)
    {
      // �ݡ���0��������
      MyService_impl* pMyServiceImplA
	= new MyService_impl(); // will be deleted automatically
      RTC::CorbaConsumer<MyService>* pMyServiceConsumerB
	= new RTC::CorbaConsumer<MyService>(); // will be deleted automatically
			
      CorbaPortMock* port0 = new CorbaPortMock("name of port0");
      port0->registerProvider("MyServiceAA", "Generic", *pMyServiceImplA);
      port0->registerConsumer("MyServiceBB", "Generic", *pMyServiceConsumerB);

      // �ݡ���1��������
      MyService_impl* pMyServiceImplB
	= new MyService_impl(); // will be deleted automatically
      RTC::CorbaConsumer<MyService>* pMyServiceConsumerA
	= new RTC::CorbaConsumer<MyService>(); // will be deleted automatically
			
      CorbaPortMock* port1 = new CorbaPortMock("name of port1");
      port1->registerProvider("MyServiceBB", "Generic", *pMyServiceImplB);
      port1->registerConsumer("MyServiceAA", "Generic", *pMyServiceConsumerA);
			
      // ��³�ץ�ե������������
      RTC::ConnectorProfile connProfile;
      connProfile.connector_id = "";
      connProfile.name = CORBA::string_dup("name of connector profile");
      connProfile.ports.length(2);
      connProfile.ports[0] = port0->getPortRef();
      connProfile.ports[1] = port1->getPortRef();

      // ��³����
      port0->getPortRef()->connect(connProfile);

      port0->activateInterfaces_public();
      port1->activateInterfaces_public();

      // �ݡ���1�Υ��󥷥塼��¦����᥽�åɤ�ƤӽФ��ȡ��ݡ���0�Υץ�Х���¦���տޤɤ���ƤӽФ���뤫��
      CPPUNIT_ASSERT(! pMyServiceImplA->is_hello_world_called());
      (*pMyServiceConsumerA)->hello_world();
      CPPUNIT_ASSERT(pMyServiceImplA->is_hello_world_called());
			
      // ���Ǥ���
      port0->getPortRef()->disconnect(connProfile.connector_id);

      //����deactivate obuject����
      port0->deactivateInterfaces_public();
      port1->deactivateInterfaces_public();

      port0->getPortRef()->connect(connProfile);

      //deactivate object ���¹Ԥ���Ƥ����ᡢ���顼�Ȥʤ롣
      try
      {
         (*pMyServiceConsumerA)->hello_world();
	  CPPUNIT_FAIL("Couldn't catch no exceptions. Disconnection failed.");
      }
      catch(...)
      {
      }
			
      // ���Ǥ���
      port0->getPortRef()->disconnect(connProfile.connector_id);

      port0->activateInterfaces_public();
      port1->activateInterfaces_public();

      port0->getPortRef()->connect(connProfile);

      //activate object ���¹Ԥ���Ƥ����ᡢ�����ư��� ��
      (*pMyServiceConsumerA)->hello_world();

      // ���Ǥ���
      port0->getPortRef()->disconnect(connProfile.connector_id);

//      delete port1;
      delete port0;
      delete pMyServiceConsumerA;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pMyServiceImplB));
      delete pMyServiceImplB;
      delete pMyServiceConsumerB;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pMyServiceImplA));
      delete pMyServiceImplA;
    }
    
  };
}; // namespace CorbaPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(CorbaPort::CorbaPortTests);

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
#endif // CorbaPort_cpp
