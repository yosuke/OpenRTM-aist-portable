// -*- C++ -*-
/*!
 * @file   PortAdminTests.cpp
 * @brief  PortAdmin test class
 * @date   $Date: 2008/04/21 04:01:01 $
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
 * $Id: PortAdminTests.cpp 2015 2010-12-29 11:33:33Z n-ando $
 *
 */

/*
 * $Log: PortAdminTests.cpp,v $
 * Revision 1.2  2008/04/21 04:01:01  arafune
 * Modified some tests.
 *
 * Revision 1.1  2007/12/20 07:50:16  arafune
 * *** empty log message ***
 *
 * Revision 1.3  2007/04/13 15:05:03  n-ando
 * Now RTC::OK becomes RTC::RTC_OK in RTC.idl.
 *
 * Revision 1.2  2007/01/12 14:44:36  n-ando
 * Some fixes for distribution control.
 *
 * Revision 1.1  2006/11/27 08:34:18  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.2  2006/11/14 02:21:09  kurihara
 *
 * test_deletePortByName() and test_finalizePorts() were added.
 *
 * Revision 1.1  2006/11/13 04:18:45  kurihara
 *
 * test program for PortAdmin class.
 *
 */

#ifndef PortAdmin_cpp
#define PortAdmin_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <vector>
#include <string>

#include <rtm/PortAdmin.h>

/*!
 * @class PortAdminTests class
 * @brief PortAdmin test
 */
namespace PortAdmin
{
  int g_argc;
  std::vector<std::string> g_argv;
	
  /*!
   * 
   * 
   *
   */
  class Logger
  {
  public:
    void log(const std::string& msg)
    {
      m_log.push_back(msg);
    }

    int countLog(const std::string& msg)
    {
      int count = 0;
      for (int i = 0; i < (int) m_log.size(); ++i)
        {
          if (m_log[i] == msg) ++count;
        }
      return count;
    }
		
    void clearLog(void)
    {
        m_log.clear();
    }
  private:
    std::vector<std::string> m_log;
  };
  /*!
   * 
   * 
   *
   */
  class PortMock
    : public RTC::PortBase
  {
  protected:
    virtual RTC::ReturnCode_t publishInterfaces(RTC::ConnectorProfile&)
    {
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t subscribeInterfaces(const RTC::ConnectorProfile&)
    {
      return RTC::RTC_OK;
    }
    virtual void unsubscribeInterfaces(const RTC::ConnectorProfile&)
    {
    }
    virtual void activateInterfaces()
    {
          if (m_logger != NULL)
          {
              m_logger->log("PortMock::activateInterfaces");
          }
    }
    virtual void deactivateInterfaces()
    {
          if (m_logger != NULL)
          {
              m_logger->log("PortMock::deactivateInterfaces");
          }
    }
  public:
      PortMock()
      {
          m_logger = NULL;
      }
      /*!
       *
       *
       */
      void setLogger(Logger* logger)
      {
          m_logger = logger;
      }
  private:
    Logger* m_logger;

  };

  class PortAdminTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PortAdminTests);
    CPPUNIT_TEST(test_getPortList);
    CPPUNIT_TEST(test_getPortRef);
    CPPUNIT_TEST(test_getPort);
    CPPUNIT_TEST(test_addPort);
    CPPUNIT_TEST(test_registerPort);
    CPPUNIT_TEST(test_removePort);
    CPPUNIT_TEST(test_deletePortByName);
    CPPUNIT_TEST(test_finalizePorts);
    CPPUNIT_TEST(test_activatePorts);
    CPPUNIT_TEST(test_deactivatePorts);
    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr          m_orb;
    PortableServer::POA_ptr m_poa;
	
  public:
    PortAdminTests()
    {
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }
			
      m_orb = CORBA::ORB_init(g_argc, argv);
      CORBA::Object_var  obj = m_orb->resolve_initial_references("RootPOA");
      m_poa = PortableServer::POA::_narrow(obj);
      PortableServer::POAManager_var pman = m_poa->the_POAManager();
      pman->activate();
    }
		
    ~PortAdminTests()
    {
    }
		
    virtual void setUp()
    {
      sleep(1);
    }
		
    virtual void tearDown()
    { 
    }
		
    /*!
     * @brief getPortList()�᥽�åɤΥƥ���
     * 
     * - �������줿Port�������餫������Ͽ������ΤȰ��פ��뤫��
     */
    void test_getPortList()
    {
      RTC::PortAdmin portAdmin(m_orb, m_poa);
			
      // Port����Ͽ���Ƥ���
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      CPPUNIT_ASSERT_EQUAL(true, portAdmin.addPort(*port0));

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      CPPUNIT_ASSERT_EQUAL(true, portAdmin.addPort(*port1));
			
      // getPortList()����Ͽ����Ƥ�����Port���������
      RTC::PortServiceList* portList = portAdmin.getPortServiceList();
			
      // �������줿Port�������餫������Ͽ������ΤȰ��פ��뤫��
      RTC::PortProfile* portProf0 = (*portList)[0]->get_port_profile();
      CPPUNIT_ASSERT(portProf0 != NULL);
      CPPUNIT_ASSERT_EQUAL(std::string("port0"), std::string(portProf0->name));
			
      RTC::PortProfile* portProf1 = (*portList)[1]->get_port_profile();
      CPPUNIT_ASSERT(portProf1 != NULL);
      CPPUNIT_ASSERT_EQUAL(std::string("port1"), std::string(portProf1->name));
      portAdmin.removePort(*port1);
      portAdmin.removePort(*port0);
      delete port1;
      delete port0;
    }
		
    /*!
     * @brief getPortRef()�᥽�åɤΥƥ���
     * 
     * - ��Ͽ����Ƥ���Port�λ��Ȥ������������Ǥ��뤫��
     * - ��Ͽ����Ƥ��ʤ�Port��̾�Τ���ꤷ����硢�տޤɤ���nil���Ȥ������뤫��
     */
    void test_getPortRef()
    {
      RTC::PortAdmin portAdmin(m_orb, m_poa);
			
      // Port����Ͽ���Ƥ���
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      CPPUNIT_ASSERT_EQUAL(true, portAdmin.addPort(*port0));

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      CPPUNIT_ASSERT_EQUAL(true, portAdmin.addPort(*port1));
			
      // ��Ͽ����Ƥ���Port�λ��Ȥ������������Ǥ��뤫��
      RTC::PortService_var portRef0 = portAdmin.getPortRef("port0");
      CPPUNIT_ASSERT(! CORBA::is_nil(portRef0));
      RTC::PortProfile* portProf0 = portRef0->get_port_profile();
      CPPUNIT_ASSERT_EQUAL(std::string("port0"), std::string(portProf0->name));

      RTC::PortService_var portRef1 = portAdmin.getPortRef("port1");
      CPPUNIT_ASSERT(! CORBA::is_nil(portRef1));
      RTC::PortProfile* portProf1 = portRef1->get_port_profile();
      CPPUNIT_ASSERT_EQUAL(std::string("port1"), std::string(portProf1->name));
			
      // ��Ͽ����Ƥ��ʤ�Port��̾�Τ���ꤷ����硢�տޤɤ���nil���Ȥ������뤫��
      CPPUNIT_ASSERT(CORBA::is_nil(portAdmin.getPortRef("inexist")));
      delete port1;
      delete port0;
    }
		
    /*!
     * @brief getPort()�᥽�åɤΥƥ���
     * 
     * - �ݡ���̾�Τ���ꤷ�ơ���Ͽ����Ƥ���Port���֥������Ȥ������������Ǥ��뤫��
     */
    void test_getPort()
    {
      RTC::PortAdmin portAdmin(m_orb, m_poa);
			
      // Port����Ͽ���Ƥ���
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      CPPUNIT_ASSERT_EQUAL(true, portAdmin.addPort(*port0));

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      CPPUNIT_ASSERT_EQUAL(true, portAdmin.addPort(*port1));

      // �ݡ���̾�Τ���ꤷ�ơ���Ͽ����Ƥ���Port���֥������Ȥ������������Ǥ��뤫��
      RTC::PortBase* portRet0 = portAdmin.getPort("port0");
      RTC::PortProfile* portProf0 = portRet0->get_port_profile();
      CPPUNIT_ASSERT_EQUAL(std::string("port0"), std::string(portProf0->name));

      RTC::PortBase* portRet1 = portAdmin.getPort("port1");
      RTC::PortProfile* portProf1 = portRet1->get_port_profile();
      CPPUNIT_ASSERT_EQUAL(std::string("port1"), std::string(portProf1->name));
      delete port1;
      delete port0;
    }
		
    /*!
     * @brief addPort()�᥽�åɤΥƥ���
     */
    void test_addPort()
    {
      RTC::PortAdmin portAdmin(m_orb, m_poa);
			
      // Port����Ͽ���Ƥ���
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      // test for addPort(PortBase&)
      CPPUNIT_ASSERT_EQUAL(true, portAdmin.addPort(*port0));
      CPPUNIT_ASSERT_EQUAL(false, portAdmin.addPort(*port0));

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      // test for addPort(PortService_ptr)
      CPPUNIT_ASSERT_EQUAL(true, portAdmin.addPort(port1->getPortRef()));
      CPPUNIT_ASSERT_EQUAL(false, portAdmin.addPort(port1->getPortRef()));
      delete port1;
      delete port0;
    }

    /*!
     * @brief registerPort(),deletePort()�᥽�åɤΥƥ���
     */
    void test_registerPort()
    {
      RTC::PortAdmin portAdmin(m_orb, m_poa);
			
      // Port����Ͽ���Ƥ���
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      // test for registerPort(PortBase&)
      portAdmin.registerPort(*port0);

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      // test for registerPort(PortService_ptr)
      portAdmin.registerPort(port1->getPortRef());

      // ��Ͽ����Ƥ��뤦�������Ĥ�Port��������
      portAdmin.deletePort(*port0);

      // getPortList()�ˤơ���Ͽ����Ƥ�����Port���������
      RTC::PortServiceList* portList = portAdmin.getPortServiceList();
			
      // �������Port������������PortList��˴ޤޤ�Ƥ��ʤ����Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(1), portList->length());
      RTC::PortProfile* portProf1 = (*portList)[0]->get_port_profile();
      CPPUNIT_ASSERT_EQUAL(std::string("port1"), std::string(portProf1->name));
			
      // �������Port��Profile�Υ�ե���󥹤�nil�ˤʤäƤ��뤫��
      const RTC::PortProfile& portProf0 = port0->getProfile();
      CPPUNIT_ASSERT(CORBA::is_nil(portProf0.port_ref));
      delete port1;
      delete port0;
    }

		
    /*!
     * @brief removePort()�Υƥ���
     * 
     * - Port������������Ǥ��뤫��
     * - �������Port��Profile�Υ�ե���󥹤�nil�ˤʤäƤ��뤫��
     */
    void test_removePort()
    {
      RTC::PortAdmin portAdmin(m_orb, m_poa);
			
      // Port����Ͽ���Ƥ���
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      portAdmin.addPort(*port0);

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      portAdmin.addPort(*port1);

      // ��Ͽ����Ƥ��뤦�������Ĥ�Port��������
      CPPUNIT_ASSERT_EQUAL(true, portAdmin.removePort(*port0));
      CPPUNIT_ASSERT_EQUAL(false, portAdmin.removePort(*port0));
			
      // getPortList()�ˤơ���Ͽ����Ƥ�����Port���������
      RTC::PortServiceList* portList = portAdmin.getPortServiceList();
			
      // �������Port������������PortList��˴ޤޤ�Ƥ��ʤ����Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(1), portList->length());
      RTC::PortProfile* portProf1 = (*portList)[0]->get_port_profile();
      CPPUNIT_ASSERT_EQUAL(std::string("port1"), std::string(portProf1->name));
			
      // �������Port��Profile�Υ�ե���󥹤�nil�ˤʤäƤ��뤫��
      const RTC::PortProfile& portProf0 = port0->getProfile();
      CPPUNIT_ASSERT(CORBA::is_nil(portProf0.port_ref));
      delete port1;
      delete port0;
    }
		
    /*!
     * @brief deletePortByName()�᥽�åɤΥƥ���
     * 
     * - ���ꤷ��̾�Τ����Port������������Ǥ��뤫��
     * - �������Port��Profile�Υ�ե���󥹤�nil�ˤʤäƤ��뤫��
     */
    void test_deletePortByName()
    {
      RTC::PortAdmin portAdmin(m_orb, m_poa);
			
      // Port����Ͽ���Ƥ���
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      portAdmin.addPort(*port0);

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      portAdmin.addPort(*port1);

      // ��Ͽ����Ƥ��뤦�������Ĥ�Port��������
      portAdmin.deletePortByName("port0");
			
      // getPortList()�ˤơ���Ͽ����Ƥ�����Port���������
      RTC::PortServiceList* portList = portAdmin.getPortServiceList();
			
      // �������Port������������PortList��˴ޤޤ�Ƥ��ʤ����Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(1), portList->length());
      RTC::PortProfile* portProf1 = (*portList)[0]->get_port_profile();
      CPPUNIT_ASSERT_EQUAL(std::string("port1"), std::string(portProf1->name));
			
      // �������Port��Profile�Υ�ե���󥹤�nil�ˤʤäƤ��뤫��
      const RTC::PortProfile& portProf0 = port0->getProfile();
      CPPUNIT_ASSERT(CORBA::is_nil(portProf0.port_ref));
      delete port1;
      delete port0;
    }
		
    /*!
     * @brief finalizePorts()�᥽�åɤΥƥ���
     * 
     * - ��Ͽ����Ƥ��뤹�٤Ƥ�Port��PortAdmin�������Ǥ��뤫��
     * - ���٤Ƥ�Port��Profile�Υ�ե���󥹤�nil�ˤʤäƤ��뤫��
     */
    void test_finalizePorts()
    {
      RTC::PortAdmin portAdmin(m_orb, m_poa);
			
      // Port����Ͽ���Ƥ���
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      portAdmin.addPort(*port0);

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      portAdmin.addPort(*port1);

      // finalizePorts()��ƽФ�
      portAdmin.finalizePorts();
			
      // getPortList()�ˤơ���Ͽ����Ƥ�����Port���������
      RTC::PortServiceList* portList = portAdmin.getPortServiceList();
			
      // ��������PortList�����Ǥ��뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(0), portList->length());
			
      // ���٤Ƥ�Port��Profile�Υ�ե���󥹤�nil�ˤʤäƤ��뤫��
      const RTC::PortProfile& portProf0 = port0->getProfile();
      CPPUNIT_ASSERT(CORBA::is_nil(portProf0.port_ref));
      const RTC::PortProfile& portProf1 = port1->getProfile();
      CPPUNIT_ASSERT(CORBA::is_nil(portProf1.port_ref));
      delete port1;
      delete port0;
    }
    /*!
     * 
     *
     *
     */
    void test_activatePorts(void)
    {
      RTC::PortAdmin portAdmin(m_orb, m_poa);

      Logger logger;
			
      // Port����Ͽ���Ƥ���
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      port0->setLogger(&logger);
      portAdmin.addPort(*port0);

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      port1->setLogger(&logger);
      portAdmin.addPort(*port1);

      CPPUNIT_ASSERT_EQUAL(0,logger.countLog("PortMock::activateInterfaces"));
      portAdmin.activatePorts();
      CPPUNIT_ASSERT_EQUAL(2,logger.countLog("PortMock::activateInterfaces"));

      CPPUNIT_ASSERT_EQUAL(0,logger.countLog("PortMock::deactivateInterfaces"));
      portAdmin.deactivatePorts();
      CPPUNIT_ASSERT_EQUAL(2,logger.countLog("PortMock::deactivateInterfaces"));

      m_poa->deactivate_object(*m_poa->servant_to_id(port0));
      m_poa->deactivate_object(*m_poa->servant_to_id(port1));
      delete port1;
      delete port0;
    }
    /*!
     * 
     *
     *
     */
    void test_deactivatePorts(void)
    {
    }
		
  };
}; // namespace PortAdmin

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PortAdmin::PortAdminTests);

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
#endif // PortAdmin_cpp
