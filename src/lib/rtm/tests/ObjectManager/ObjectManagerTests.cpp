// -*- C++ -*-
/*!
 * @file   ObjectManagerTests.cpp
 * @brief  ObjectManager test class
 * @date   $Date: 2008/04/18 06:23:58 $
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
 * $Id: ObjectManagerTests.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

/*
 * $Log: ObjectManagerTests.cpp,v $
 * Revision 1.2  2008/04/18 06:23:58  arafune
 * Modified / Added some tests.
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2006/11/27 08:26:00  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.2  2006/10/24 03:08:15  kurihara
 *
 * test program for ObjectManager class
 *
 */

#ifndef ObjectManager_cpp
#define ObjectManager_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <fstream>
#include <string>

#include <rtm/ObjectManager.h>

/*!
 * @class ObjectManagerTests class
 * @brief ObjectManager test
 */
namespace ObjectManagerTests
{
  class ObjectMock
  {
  public:
    ObjectMock(const std::string& id) : m_id(id) {}
    std::string getId() const { return std::string(m_id); }
	
  private:
    std::string m_id;
  };
	
  class PredicateMock
  {
  public:
    PredicateMock(const ObjectMock* obj) : m_id(obj->getId()) {}
    PredicateMock(const std::string& id) : m_id(id) {}
    bool operator()(const ObjectMock* obj) { return (obj->getId() == m_id); }
	
  private:
    const std::string m_id;
  };
	
  class ObjectManagerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ObjectManagerTests);
    CPPUNIT_TEST(test_registerObject);
    CPPUNIT_TEST(test_registerObject_with_overlapped_identifier);
    CPPUNIT_TEST(test_find);
    CPPUNIT_TEST(test_unregisterObject_and_find);
    CPPUNIT_TEST(test_getObjects);
    CPPUNIT_TEST_SUITE_END();
		
  public:    
    /*!
     * @brief Constructor
     */
    ObjectManagerTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~ObjectManagerTests()
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
     * @brief registerObject()�᥽�åɤΥƥ���
     * 
     * - ���֥������Ȥ��������Ͽ�Ǥ��뤫��
     */
    void test_registerObject()
    {
      ::ObjectManager<std::string, ObjectMock, PredicateMock> objMgr;

      // ���֥������Ȥ�������Ƥ���
      ObjectMock obj1("ID 1");
      ObjectMock obj2("ID 2");
			
      // ���֥������Ȥ��������Ͽ�Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(true, objMgr.registerObject(&obj1));
      CPPUNIT_ASSERT_EQUAL(true, objMgr.registerObject(&obj2));
    }
    
    /*!
     * @brief registerObject()�᥽�åɤΥƥ���
     * 
     * - Ʊ��Υ��֥������ȡ����������̻Ҥ�Ʊ���ˤ���Ͽ���ߤơ��տޤɤ��꼺�Ԥ��뤫��
     * - Ʊ��μ��̻Ҥ�����̤Υ��֥������Ȥ���Ͽ���ߤơ��տޤɤ��꼺�Ԥ��뤫��
     */
    void test_registerObject_with_overlapped_identifier()
    {
      ::ObjectManager<std::string, ObjectMock, PredicateMock> objMgr;

      // Ʊ��μ��̻Ҥ���ĥ��֥������Ȥ�������Ƥ���
      ObjectMock obj1("ID");
      ObjectMock obj2("ID");

      // ���֥������Ȥ���Ͽ����
      CPPUNIT_ASSERT_EQUAL(true, objMgr.registerObject(&obj1));
			
      // Ʊ��Υ��֥������ȡ����������̻Ҥ�Ʊ���ˤ���Ͽ���ߤơ��տޤɤ��꼺�Ԥ��뤫��
      CPPUNIT_ASSERT_EQUAL(false, objMgr.registerObject(&obj1));
			
      // Ʊ��μ��̻Ҥ�����̤Υ��֥������Ȥ���Ͽ���ߤơ��տޤɤ��꼺�Ԥ��뤫��
      CPPUNIT_ASSERT_EQUAL(false, objMgr.registerObject(&obj2));
    }
    
    /*!
     * @brief find()�᥽�åɤΥƥ���
     * 
     * - ��Ͽ���줿���֥������Ȥ�find()�������������Ǥ��뤫��
     * - ¸�ߤ��ʤ�ID����ꤷ����硢�տޤɤ���NULL����������뤫��
     */
    void test_find()
    {
      ::ObjectManager<std::string, ObjectMock, PredicateMock> objMgr;
    	
      // ���֥������Ȥ�������Ƥ���
      ObjectMock obj1("ID 1");
      ObjectMock obj2("ID 2");

      // ���֥������Ȥ���Ͽ����
      CPPUNIT_ASSERT_EQUAL(true, objMgr.registerObject(&obj1));
      CPPUNIT_ASSERT_EQUAL(true, objMgr.registerObject(&obj2));
			
      // ��Ͽ���줿���֥������Ȥ�find()�������������Ǥ��뤫��
      ObjectMock* pObjRet1 = objMgr.find("ID 1");
      CPPUNIT_ASSERT(pObjRet1 != NULL);
      CPPUNIT_ASSERT_EQUAL(std::string("ID 1"), pObjRet1->getId());

      ObjectMock* pObjRet2 = objMgr.find("ID 2");
      CPPUNIT_ASSERT(pObjRet2 != NULL);
      CPPUNIT_ASSERT_EQUAL(std::string("ID 2"), pObjRet2->getId());
			
      // ¸�ߤ��ʤ�ID����ꤷ����硢�տޤɤ���NULL����������뤫��
      CPPUNIT_ASSERT_EQUAL((ObjectMock*) NULL, objMgr.find("INEXIST ID"));
    }
    
    /*!
     * @brief unregisterObject()�᥽�åɤ�find()�᥽�åɤΥƥ���
     * 
     * - ���֥������Ȥ�unregisterObject()����Ͽ������ơ����Υ��֥������Ȥ������������Ǥ��뤫��
     * - ��Ͽ����������֥������Ȥ�ID����ꤷ��find()������硢�տޤɤ���NULL�����뤫��
     * - ��Ͽ������Ƥ��ʤ����֥������Ȥϡ������Ȥ���find()�������������Ǥ��뤫��
     */
    void test_unregisterObject_and_find()
    {
      ::ObjectManager<std::string, ObjectMock, PredicateMock> objMgr;
    	
      // ���֥������Ȥ�������Ƥ���
      ObjectMock obj1("ID 1");
      ObjectMock obj2("ID 2");

      // ���֥������Ȥ���Ͽ����
      CPPUNIT_ASSERT_EQUAL(true, objMgr.registerObject(&obj1));
      CPPUNIT_ASSERT_EQUAL(true, objMgr.registerObject(&obj2));
			
      // ���֥������Ȥ���Ͽ������ơ����Υ��֥������Ȥ������������Ǥ��뤫��
      ObjectMock* pObjRet1 = objMgr.unregisterObject("ID 1");
      CPPUNIT_ASSERT(pObjRet1 != NULL);
      CPPUNIT_ASSERT_EQUAL(std::string("ID 1"), pObjRet1->getId());
			
      // ��Ͽ����������֥������Ȥ�ID����ꤷ��find()������硢�տޤɤ���NULL�����뤫��
      CPPUNIT_ASSERT_EQUAL((ObjectMock*) NULL, objMgr.find("ID 1"));
			
      // ��Ͽ������Ƥ��ʤ����֥������Ȥϡ������Ȥ���find()�������������Ǥ��뤫��
      ObjectMock* pObjRet2 = objMgr.find("ID 2");
      CPPUNIT_ASSERT(pObjRet2 != NULL);
      CPPUNIT_ASSERT_EQUAL(std::string("ID 2"), pObjRet2->getId());
    }
    
    /*!
     * @brief getObjects()�᥽�åɤΥƥ���
     * 
     * - getObjects()�ǡ���Ͽ�Ѥߤ������֥������Ȥ������������Ǥ��뤫��
     */
    void test_getObjects()
    {
      ::ObjectManager<std::string, ObjectMock, PredicateMock> objMgr;
    	
      // ���֥������Ȥ�������Ƥ���
      ObjectMock obj1("ID 1");
      ObjectMock obj2("ID 2");

      // ���֥������Ȥ���Ͽ����
      CPPUNIT_ASSERT_EQUAL(true, objMgr.registerObject(&obj1));
      CPPUNIT_ASSERT_EQUAL(true, objMgr.registerObject(&obj2));
			
      // getObjects()�ǡ���Ͽ�Ѥߤ������֥������Ȥ������������Ǥ��뤫��
      std::vector<ObjectMock*> objs = objMgr.getObjects();
      CPPUNIT_ASSERT_EQUAL(2, (int) objs.size());
      CPPUNIT_ASSERT_EQUAL(std::string("ID 1"),
			   (*std::find_if(objs.begin(), objs.end(), PredicateMock("ID 1")))->getId());
      CPPUNIT_ASSERT_EQUAL(std::string("ID 2"),
			   (*std::find_if(objs.begin(), objs.end(), PredicateMock("ID 2")))->getId());
    }
    
  };
}; // namespace ObjectManager

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ObjectManagerTests::ObjectManagerTests);

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
#endif // ObjectManager_cpp
