// -*- C++ -*-
/*!
 * @file   ManagerConfigTests.cpp
 * @brief  ManagerConfig test class
 * @date   $Date: 2008/05/01 08:01:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: ManagerConfigTests.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

/*
 * $Log: ManagerConfigTests.cpp,v $
 * Revision 1.3  2008/05/01 08:01:03  arafune
 * Modified some tests.
 *
 * Revision 1.2  2008/05/01 07:52:46  arafune
 * Modified some tests.
 *
 *
 * Revision 1.1  2006/11/27 08:25:57  n-ando
 * TestSuites are devided into each directory.
 *
 *
 */

#ifndef ManagerConfig_cpp
#define ManagerConfig_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <fstream>
#include <vector>
#include <string>

#include <rtm/ManagerConfig.h>

/*!
 * @class ManagerConfigTests class
 * @brief ManagerConfig test
 */
namespace ManagerConfig
{
  int g_argc;
  //char* g_argv[10];
  std::vector<std::string> g_argv;
	
  class ManagerConfigMock : public RTC::ManagerConfig
  {
  public:
    void parseArgs(int argc, char** argv)
    {
      ManagerConfig::parseArgs(argc, argv);
    }
		
    bool findConfigFile()
    {
      return ManagerConfig::findConfigFile();
    }
		
    void setSystemInformation(coil::Properties& prop)
    {
      ManagerConfig::setSystemInformation(prop);
    }
		
    bool fileExist(const std::string& filename)
    {
      return ManagerConfig::fileExist(filename);
    }
		
  public:
    std::string& configFile()
    {
      return m_configFile;
    }
  bool m_isMaster;
  };
	
  class ManagerConfigTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ManagerConfigTests);
    CPPUNIT_TEST(test_init_and_configure);
    CPPUNIT_TEST(test_init_default);
    CPPUNIT_TEST_SUITE_END();
	    
  public:
    /*!
     * @brief Constructor
     */
    ManagerConfigTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~ManagerConfigTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
		
    /*!
     * @brief init()�᥽�åɤ�configure()�᥽�åɤΥƥ���
     * 
     * - ���ޥ�ɰ�����-f���ץ����ǻ��ꤷ���ե������������������Ǥ��뤫��
     * - ���ꤵ��Ƥ������Ƥ������������Ǥ��뤫��
     * - �����ƥ����Υץ�ѥƥ������������Ƥ˴ޤޤ�Ƥ��뤫��
     */
    void test_init_and_configure()
    {
      ManagerConfigMock mgrCfg;
      CPPUNIT_ASSERT(mgrCfg.fileExist("./rtc.conf"));

      // ���ޥ�ɰ�����-f���ץ����ǻ��ꤷ���ե������������������Ǥ��뤫��
//      char* argv[] = { "command", "-f", "./rtc.conf" };
      char* argv[] = { "command", "-d", "./rtc.conf" };
      int argc = sizeof(argv) / sizeof(char*);
      mgrCfg.init(argc, argv);
			
      // ���ꤵ��Ƥ������Ƥ������������Ǥ��뤫��
      coil::Properties properties;
      mgrCfg.configure(properties);

      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.COMPONENT.CONF.PATH"),
			   properties.getProperty("rtc.component.conf.path"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.ARCH"),
			   properties.getProperty("rtc.manager.arch"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.DEBUG.LEVEL"),
			   properties.getProperty("rtc.manager.debug.level"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.LANGUAGE"),
			   properties.getProperty("rtc.manager.language"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.NAMESERVER"),
			   properties.getProperty("rtc.manager.nameserver"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.OPENING_MESSAGE"),
			   properties.getProperty("rtc.manager.opening_message"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.ORB"),
			   properties.getProperty("rtc.manager.orb"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.ORB.OPTIONS"),
			   properties.getProperty("rtc.manager.orb.options"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.OS"),
			   properties.getProperty("rtc.manager.os"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.OS.RELEASE"),
			   properties.getProperty("rtc.manager.os.release"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.SUBSYSTEMS"),
			   properties.getProperty("rtc.manager.subsystems"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.OPENRTM.AUTHOR"),
			   properties.getProperty("rtc.openrtm.author"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.OPENRTM.RELEASE"),
			   properties.getProperty("rtc.openrtm.release"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.OPENRTM.VENDOR"),
			   properties.getProperty("rtc.openrtm.vendor"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.OPENRTM.VERSION"),
			   properties.getProperty("rtc.openrtm.version"));
			
      // �����ƥ����Υץ�ѥƥ������������Ƥ˴ޤޤ�Ƥ��뤫��
      // �ʥ����ƥ�����ư��Ķ��˰�¸����Τǡ��ץ�ѥƥ��������Ǥ��Ƥ��뤳�Ȥ������ǧ�����
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.os.name"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.os.release"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.os.version"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.os.arch"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.os.hostname"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.pid"));
      CPPUNIT_ASSERT(std::string("YES")
		     == properties.getProperty("manager.is_master"));

      // ���ޥ�ɰ�����-a���ץ������꤬������ȿ�Ǥ���뤫��
      // corba.corba_servant ����γ�ǧ
      argv[1] = "-a";
      argc = sizeof(argv) / sizeof(char*);
      mgrCfg.init(argc, argv);
      mgrCfg.configure(properties);
      CPPUNIT_ASSERT_EQUAL(std::string("NO"),
			   properties.getProperty("manager.corba_servant"));

      // ���ޥ�ɰ�����-o���ץ������꤬������ȿ�Ǥ���뤫��
      // configuration ��񤭻���γ�ǧ
      argv[1] = "-omanager.is_master:NO";
      argc = sizeof(argv) / sizeof(char*);
      mgrCfg.init(argc, argv);
      mgrCfg.configure(properties);
      CPPUNIT_ASSERT_EQUAL(std::string("NO"),
			   properties.getProperty("manager.is_master"));

      // ���ޥ�ɰ�����-p���ץ������꤬������ȿ�Ǥ���뤫��
      // corba.endpoints �ݡ����ֹ����γ�ǧ
      argv[1] = "-p9876";
      argc = sizeof(argv) / sizeof(char*);
      mgrCfg.init(argc, argv);
      mgrCfg.configure(properties);
      CPPUNIT_ASSERT_EQUAL(std::string(":9876"),
			   properties.getProperty("corba.endpoints"));
    }
		
    /*!
     * @brief init()�᥽�åɤΥƥ���
     * 
     * - ����ե����ե�����λ��ꥪ�ץ����ʤ��ǽ����������硢�ǥե���ȤΥ���ե����졼�����ե���������Ƥǽ��������뤫��
     */
    void test_init_default()
    {

      ManagerConfigMock mgrCfg;

      // ���ץ�������ʤ��ǽ��������
      mgrCfg.init(0, NULL);
			
      // ���ꤵ��Ƥ������Ƥ������������Ǥ��뤫��
      coil::Properties properties;
      mgrCfg.configure(properties);

      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.COMPONENT.CONF.PATH"),
			   properties.getProperty("rtc.component.conf.path"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.ARCH"),
			   properties.getProperty("rtc.manager.arch"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.DEBUG.LEVEL"),
			   properties.getProperty("rtc.manager.debug.level"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.LANGUAGE"),
			   properties.getProperty("rtc.manager.language"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.NAMESERVER"),
			   properties.getProperty("rtc.manager.nameserver"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.OPENING_MESSAGE"),
			   properties.getProperty("rtc.manager.opening_message"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.ORB"),
			   properties.getProperty("rtc.manager.orb"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.ORB.OPTIONS"),
			   properties.getProperty("rtc.manager.orb.options"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.OS"),
			   properties.getProperty("rtc.manager.os"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.OS.RELEASE"),
			   properties.getProperty("rtc.manager.os.release"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.MANAGER.SUBSYSTEMS"),
			   properties.getProperty("rtc.manager.subsystems"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.OPENRTM.AUTHOR"),
			   properties.getProperty("rtc.openrtm.author"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.OPENRTM.RELEASE"),
			   properties.getProperty("rtc.openrtm.release"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.OPENRTM.VENDOR"),
			   properties.getProperty("rtc.openrtm.vendor"));
      CPPUNIT_ASSERT_EQUAL(std::string("DEFAULT.RTC.OPENRTM.VERSION"),
			   properties.getProperty("rtc.openrtm.version"));
			
      // �����ƥ����Υץ�ѥƥ������������Ƥ˴ޤޤ�Ƥ��뤫��
      // �ʥ����ƥ�����ư��Ķ��˰�¸����Τǡ��ץ�ѥƥ��������Ǥ��Ƥ��뤳�Ȥ������ǧ�����
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.os.name"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.os.release"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.os.version"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.os.arch"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.os.hostname"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.pid"));
      CPPUNIT_ASSERT(std::string("")
		     != properties.getProperty("manager.is_master"));
    }
		
  };
}; // namespace ManagerConfig

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ManagerConfig::ManagerConfigTests);

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
#endif // ManagerConfig_cpp
