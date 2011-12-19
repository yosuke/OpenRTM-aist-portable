// -*- C++ -*-
/*!
 * @file   SdoOrganizationTests.cpp
 * @brief  SdoOrganization test class
 * @date   $Date: 2007/12/20 07:50:17 $
 * @author Shinji Kurihara
 *         Noriaki Ando <n-ando@aist.go.jp>
 *
 * * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoOrganizationTests.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

/*
 * $Log: SdoOrganizationTests.cpp,v $
 * Revision 1.1  2007/12/20 07:50:17  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2006/11/27 08:37:43  n-ando
 * TestSuites are devided into each directory.
 *
 *
 */

#ifndef SdoOrganization_cpp
#define SdoOrganization_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <rtm/RTObject.h>
#include <rtm/Manager.h>
#include <rtm/SdoOrganization.h>


/*!
 * @class SdoOrganizationTests class
 * @brief SdoOrganization test
 */
namespace SdoOrganization
{
  using namespace SDOPackage;
  using namespace std;
  
  class SdoOrganizationTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SdoOrganizationTests);

    CPPUNIT_TEST(test_get_organization_id);
    CPPUNIT_TEST(test_set_get_organization_property);
    CPPUNIT_TEST(test_set_get_organization_property_value);
    CPPUNIT_TEST(test_remove_organization_property);
    CPPUNIT_TEST(test_set_get_owner);
    CPPUNIT_TEST(test_set_get_members);
    CPPUNIT_TEST(test_add_remove_members);
    CPPUNIT_TEST(test_set_get_dependency);

    CPPUNIT_TEST_SUITE_END();
    
  private:
    ::RTC::RTObject_impl* rtobj;
    Organization_impl* m_pOi;
    char* m_id;
  public:
    
    /*!
     * @brief Constructor
     */
    SdoOrganizationTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~SdoOrganizationTests()
    {
    }
    
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      ::RTC::Manager& mgr(RTC::Manager::instance());
      rtobj = new ::RTC::RTObject_impl(&mgr);
      m_pOi = new Organization_impl(rtobj->getObjRef());
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    {
      m_pOi->_remove_ref();
      rtobj->_remove_ref();
    }


    /*!
     * @brief get_organization_id()
     */
    void test_get_organization_id() {
//      std::cout << "test_get_organization_id IN" << std::endl;
      m_id = m_pOi->get_organization_id();
      CPPUNIT_ASSERT(m_id != NULL);
//      std::cout << "test_get_organization_id OUT" << std::endl;
    }
    
    
    /*!
     * @brief set_organization_property() and get_organization_property()
     */
    void test_set_get_organization_property() {
//      std::cout << "test_set_get_organization_property IN" << std::endl;
      OrganizationProperty_var get_prop;
      OrganizationProperty set_prop;
      CORBA::Boolean ret;
      CORBA::Short st;
      CORBA::Long lg;
      CORBA::Float ft;
      CORBA::Double db;
      //    char* strg;
      
      CORBA::Short rst;
      CORBA::Long rlg;
      CORBA::Float rft;
      CORBA::Double rdb;
      //    char* rstrg;
      
      NVList nvList;
      NameValue nv;
      string str;
      
      try {
	// �ץ�ѥƥ��μ��� length 0�Υץ�ѥƥ����֤���롣
	get_prop = m_pOi->get_organization_property();
//	cout << endl << "get property length: " << get_prop->properties.length() << endl;
	
	
	// ����OrganizationProperty�򥻥åȤ��롣 OK.
	ret = m_pOi->add_organization_property(set_prop);
	
	
	nv.name = "hoge";
        str = "hoge"; 
	ft = 11.111;
	nv.value <<= ft;
	
	nvList.length(1);
	nvList[0] = nv;
	
	set_prop.properties = nvList;
	// �ץ�ѥƥ��Υ��å�
	ret = m_pOi->add_organization_property(set_prop);
	
	// �ץ�ѥƥ��μ��� length 1�Υץ�ѥƥ��ꥹ�Ȥ����OrganizationProperty���֤���롣
	get_prop = m_pOi->get_organization_property();
//	cout << "get property length: " << get_prop->properties.length() << endl;
	
	str = (get_prop->properties[0]).name;
	(get_prop->properties[0]).value >>= rft;
	CPPUNIT_ASSERT(str == "hoge");
	CPPUNIT_ASSERT(rft == ft);
	
	
	nv.name = "hogehoge";
	ft = 22.2;
	nv.value <<= ft;
	
	nvList.length(1);
	nvList[0] = nv;
	
	set_prop.properties = nvList;
	// �ץ�ѥƥ��Υ��å�
	ret = m_pOi->add_organization_property(set_prop);
	
	// �ץ�ѥƥ��μ���
	get_prop = m_pOi->get_organization_property();
//	cout << "get property length: " << get_prop->properties.length() << endl;
	
	
	str = ((get_prop->properties[0]).name);
	(get_prop->properties[0]).value >>= rft;
	CPPUNIT_ASSERT(str == "hogehoge");
	CPPUNIT_ASSERT(rft == ft);
	
	//      nvList.length(5);
	nvList.length(4);
	
//	cout << "short" << endl;
	nv.name = "short";
	st = 1;
	nv.value <<= st;
	nvList[0] = nv;
	
//	cout << "long" << endl;
	nv.name = "long";
	lg = 2222;
	nv.value <<= lg;
	nvList[1] = nv;
	
//	cout << "float" << endl;
	nv.name = "float";
	ft = 33.3;
	nv.value <<= ft;
	nvList[2] = nv;
	
//	cout << "double" << endl;
	nv.name = "double";
	db = 3.3;
	nv.value <<= db;
	nvList[3] = nv;
	
	//      nv.name = "char";
	//      strg = "STRING";
	//      nv.value <<= CORBA::Any::from_char('C'); // �����ǥ������ȥ��顼ȯ��
	//      cout << "char" << endl;
	//      nvList[4] = nv;
	
	
	//      cout << "string" << endl;
	//      nv.name = "string";
	//      strg = "STRING";
	//      char * p = "STRING";
	//      nv.value <<= CORBA::Any::from_string(p,7); // �����ǥ������ȥ��顼ȯ��
	//      nvList[4] = nv;
	
//	cout << "set_prop.properties" << endl;
	set_prop.properties = nvList;
	
//	cout << "set in" << endl;
	ret = m_pOi->add_organization_property(set_prop);
//	cout << "set out" << endl;
	
	get_prop = m_pOi->get_organization_property();
//	cout << "get property length: " << get_prop->properties.length() << endl;
	
	str = ((get_prop->properties[0]).name);
	(get_prop->properties[0]).value >>= rst;
	CPPUNIT_ASSERT(str == "short");
	CPPUNIT_ASSERT(rst == st);
	
	str = ((get_prop->properties[1]).name);
	(get_prop->properties[1]).value >>= rlg;
	CPPUNIT_ASSERT(str == "long");
	CPPUNIT_ASSERT(rlg == lg);
	
	str = ((get_prop->properties[2]).name);
	(get_prop->properties[2]).value >>= rft;
	CPPUNIT_ASSERT(str == "float");
	CPPUNIT_ASSERT(rft == ft);
	
	str = ((get_prop->properties[3]).name);
	(get_prop->properties[3]).value >>= rdb;
	CPPUNIT_ASSERT(str == "double");
	CPPUNIT_ASSERT(rdb == db);
	
	//      str = ((get_prop->properties[4]).name);
	//      (get_prop->properties[4]).value >>= (CORBA::Any::to_char(rch));
	//      CPPUNIT_ASSERT(str == "char");
	//      CPPUNIT_ASSERT(rch == ch);
	
	//      str = ((get_prop->properties[4]).name);
	//      char * retp;
	//      (get_prop->properties[4]).value >>= CORBA::Any::to_string(retp,7);
	//      CPPUNIT_ASSERT(str == "string");
	//      CPPUNIT_ASSERT(*retp == *p);
	
      }
      catch (InvalidParameter ip) {
	cout << "InvalidParameter exception." << endl;
      }
      catch (NotAvailable na) {
	cout << "NotAvailable exception." << endl;
      }
      catch (InternalError ip) {
	cout << "InternalError exception." << endl;
      }
      catch (...) {
	cout << "othrer exception." << endl;
      }
//      std::cout << "test_set_get_organization_property OUT" << std::endl;
    }

    /*!
     * @brief set_organization_property_value() and get_organization_property_value()
     */
    void test_set_get_organization_property_value() {
//      std::cout << "test_set_get_organization_property_value IN" << std::endl;
      OrganizationProperty_var get_prop;
      OrganizationProperty set_prop;
      CORBA::Boolean ret;
      CORBA::Short st;
//      CORBA::Long lg;
      CORBA::Float ft;
//      CORBA::Double db;
      CORBA::Any any;
      
      CORBA::Short rst;
//      CORBA::Long rlg;
      CORBA::Float rft;
//      CORBA::Double rdb;
      CORBA::Any* rany;

      NVList nvList;
      NameValue nv;
      string str;
      
      try {
	// �ץ�ѥƥ��μ��� length 0�Υץ�ѥƥ����֤���롣
	get_prop = m_pOi->get_organization_property();
//	cout << endl << "get property length: " << get_prop->properties.length() << endl;
	
	// ����OrganizationProperty�򥻥åȤ��롣 OK.
	ret = m_pOi->add_organization_property(set_prop);
	CPPUNIT_ASSERT(ret);
	
	// �ץ�ѥƥ����������true ���֤���뤫��
	ft = 11.111;
	any <<= ft;
	ret = m_pOi->set_organization_property_value("hoge1", any);
	CPPUNIT_ASSERT(ret);

        // �ץ�ѥƥ��������ͼ������� �����ͤ��֤���뤫��
	rany = m_pOi->get_organization_property_value("hoge1");
	(*rany) >>= rft;
	CPPUNIT_ASSERT_EQUAL(ft, rft);


        // �ץ�ѥƥ����������true ���֤���뤫��
	st = 123;
	any <<= st;
	ret = m_pOi->set_organization_property_value("hoge2", any);
	CPPUNIT_ASSERT(ret);

        // �ץ�ѥƥ��������ͼ������� �����ͤ��֤���뤫��
	rany = m_pOi->get_organization_property_value("hoge2");
	(*rany) >>= rst;
	CPPUNIT_ASSERT_EQUAL(st, rst);


        // �ץ�ѥƥ��ι�������true ���֤���뤫��
	st = 456;
	any <<= st;
	ret = m_pOi->set_organization_property_value("hoge2", any);
	CPPUNIT_ASSERT(ret);

        // �ץ�ѥƥ��ι����ͼ������� �����ͤ��֤���뤫��
	rany = m_pOi->get_organization_property_value("hoge2");
	(*rany) >>= rst;
	CPPUNIT_ASSERT_EQUAL(st, rst);

        // �ץ�ѥƥ����������name ̤����ˤ�� InvalidParameter ���֤���뤫��
	short sflg = -1;
	try {
	  ret = m_pOi->set_organization_property_value("", any);
	  sflg = 0;
	}
	catch (InvalidParameter ip) {
//	  cout << "InvalidParameter exception." << endl;
	  sflg = 1;
	}
	CPPUNIT_ASSERT(sflg == 1);

        // �ץ�ѥƥ��������ͼ�������name ̤����ˤ�� InvalidParameter ���֤���뤫��
	sflg = -1;
	try {
	  ret = m_pOi->get_organization_property_value("");
	  sflg = 0;
	}
	catch (InvalidParameter ip) {
//	  cout << "InvalidParameter exception." << endl;
	  sflg = 1;
	}
	CPPUNIT_ASSERT(sflg == 1);

        // �ץ�ѥƥ��������ͼ�������name ̤��Ͽ�ˤ�� InvalidParameter ���֤���뤫��
	sflg = -1;
	try {
	  ret = m_pOi->get_organization_property_value("hoge99");
	  sflg = 0;
	}
	catch (InvalidParameter ip) {
//	  cout << "InvalidParameter exception." << endl;
	  sflg = 1;
	}
	CPPUNIT_ASSERT(sflg == 1);
      }
      catch (InvalidParameter ip) {
	cout << "InvalidParameter exception." << endl;
      }
      catch (NotAvailable na) {
	cout << "NotAvailable exception." << endl;
      }
      catch (InternalError ip) {
	cout << "InternalError exception." << endl;
      }
      catch (...) {
	cout << "othrer exception." << endl;
      }

//      std::cout << "test_set_get_organization_property_value OUT" << std::endl;
    }

    /*!
     * @brief add_organization_property() and remove_organization_property()
     */
    void test_remove_organization_property() {
//      std::cout << "test_remove_organization_property IN" << std::endl;
      OrganizationProperty set_prop;
      CORBA::Boolean ret;
      CORBA::Float ft;
      NVList nvList;
      NameValue nv;
      string str;

      nv.name = "hoge";
      str = "hoge"; 
      ft = 11.111;
      nv.value <<= ft;

      nvList.length(1);
      nvList[0] = nv;

      set_prop.properties = nvList;
      // �ץ�ѥƥ��Υ��å�
      ret = m_pOi->add_organization_property(set_prop);
      CPPUNIT_ASSERT(ret);

      // InvalidParameter exception���ǧ
      short sflg = -1;
      try {
	ret = m_pOi->remove_organization_property("short");
	if (!ret) {
	  cout << "Couldn't remove name: short" << endl;
	}
	sflg = 0;
      }
      catch (InvalidParameter ip) {
//	cout << "InvalidParameter exception." << endl;
	sflg = 1;
      }
      catch (NotAvailable na) {
	cout << "NotAvailable exception." << endl;
	sflg = 2;
      }
      catch (InternalError ip) {
	cout << "InternalError exception." << endl;
	sflg = 3;
      }
      catch (...) {
	cout << "othrer exception." << endl;
	sflg = 4;
      }
      CPPUNIT_ASSERT(sflg == 1);
      
      // �����:true ���ǧ
      sflg = -1;
      try {
	ret = m_pOi->remove_organization_property("hoge");
	if (!ret) {
	  cout << "Couldn't remove name: hoge" << endl;
	}
        CPPUNIT_ASSERT(ret);
        sflg = 0;
      }
      catch (InvalidParameter ip) {
	cout << "InvalidParameter exception." << endl;
	sflg = 1;
      }
      catch (NotAvailable na) {
	cout << "NotAvailable exception." << endl;
	sflg = 2;
      }
      catch (InternalError ip) {
	cout << "InternalError exception." << endl;
	sflg = 3;
      }
      catch (...) {
	cout << "othrer exception." << endl;
	sflg = 4;
      }
      CPPUNIT_ASSERT(sflg == 0);
//      std::cout << "test_remove_organization_property OUT" << std::endl;
    }


    /*!
     * @brief set_owner() and get_owner()
     */
    void test_set_get_owner() {
//      std::cout << "test_set_get_owner IN" << std::endl;
      CORBA::Boolean ret;
      SDOPackage::SDOSystemElement_var varOwner;
      SDOPackage::SDOSystemElement_ptr ptrOwner;

      try {
	// �����ʡ��������Ԥ��뤫��
	varOwner = m_pOi->get_owner();
	CPPUNIT_ASSERT(!::CORBA::is_nil(varOwner));

	// InvalidParameter exception���ǧ
	short sflg = -1;
	try {
	  // �����ʡ��������InvalidParameter ���֤���뤫��
	  ptrOwner = SDOPackage::SDOSystemElement::_nil();
	  ret = m_pOi->set_owner(ptrOwner);
	  CPPUNIT_ASSERT(ret);
	  sflg = 0;
	}
	catch (InvalidParameter ip) {
//	  cout << "InvalidParameter exception." << endl;
	  sflg = 1;
	}
	catch (NotAvailable na) {
	  cout << "NotAvailable exception." << endl;
	  sflg = 2;
	}
	catch (InternalError ip) {
	  cout << "InternalError exception." << endl;
	  sflg = 3;
	}
	catch (...) {
	  cout << "othrer exception." << endl;
	  sflg = 4;
	}
	CPPUNIT_ASSERT(sflg == 1);

	// �����:true ���ǧ
	sflg = -1;
	try {
	  // �����ʡ��������true ���֤���뤫��
	  ::RTC::RTObject_impl* rtobj2;
	  ::RTC::Manager& mgr2(RTC::Manager::instance());
	  rtobj2 = new ::RTC::RTObject_impl(&mgr2);
	  ptrOwner = rtobj2->getObjRef();

	  ret = m_pOi->set_owner(ptrOwner);
	  CPPUNIT_ASSERT(ret);
	  sflg = 0;
          rtobj2->_remove_ref();
	}
	catch (InvalidParameter ip) {
	  cout << "InvalidParameter exception." << endl;
	  sflg = 1;
	}
	catch (NotAvailable na) {
	  cout << "NotAvailable exception." << endl;
	  sflg = 2;
	}
	catch (InternalError ip) {
	  cout << "InternalError exception." << endl;
	  sflg = 3;
	}
	catch (...) {
	  cout << "othrer exception." << endl;
	  sflg = 4;
	}
	CPPUNIT_ASSERT(sflg == 0);
      }
      catch (InvalidParameter ip) {
	cout << "InvalidParameter exception." << endl;
      }
      catch (NotAvailable na) {
	cout << "NotAvailable exception." << endl;
      }
      catch (InternalError ip) {
	cout << "InternalError exception." << endl;
      }
      catch (...) {
	cout << "othrer exception." << endl;
      }
//      std::cout << "test_set_get_owner OUT" << std::endl;
    }


    /*!
     * @brief set_members() and get_members()
     */
    void test_set_get_members() {
//      std::cout << "test_set_get_members IN" << std::endl;
      CORBA::Boolean ret;
      SDOPackage::SDO_var sdo;
      SDOPackage::SDOList slist;
      SDOPackage::SDOList* rslist;

      // SDO �Υ��åȻ���InvalidParameter ������Ǥ��뤫��
      // set_members()�ˡ�NULL �� ���Υꥹ�Ȥ��Ϥ��Ƥ�length()=0�Ȥʤ뤿��
      // InvalidParameter���֤��������Ϥʤ���
      // SDOList �Υ��åȻ������Υꥹ�Ȥ��Ϥ��Ƽ����Ǥ��뤫��
      short sflg = -1;
      try {
	slist = NULL;
	ret = m_pOi->set_members(slist);
	CPPUNIT_ASSERT(ret);
	sflg = 0;
      }
      catch (InvalidParameter ip) {
        cout << "InvalidParameter exception." << endl;
        sflg = 1;
      }
      catch (NotAvailable na) {
        cout << "NotAvailable exception." << endl;
        sflg = 2;
      }
      catch (InternalError ip) {
        cout << "InternalError exception." << endl;
        sflg = 3;
      }
      catch (...) {
        cout << "othrer exception." << endl;
        sflg = 4;
      }
      CPPUNIT_ASSERT(sflg == 0);

      // 0���SDOList�������Ԥ��뤫��
      rslist = m_pOi->get_members();
      CPPUNIT_ASSERT(rslist->length() == 0);


      // SDOList �Υ��åȻ����ꥹ�Ȥ򥻥åȤ��� true ������Ǥ��뤫��
      sflg = -1;
      try {
	RTC::RTObject_impl* rtobj2;
	RTC::Manager& mgr2(RTC::Manager::instance());
	rtobj2 = new ::RTC::RTObject_impl(&mgr2);
	sdo = SDOPackage::SDO::_duplicate(rtobj2->getObjRef());
	CORBA_SeqUtil::push_back(slist, sdo);
	ret = m_pOi->set_members(slist);
	CPPUNIT_ASSERT(ret);
	sflg = 0;
        rtobj2->_remove_ref();
      }
      catch (InvalidParameter ip) {
        cout << "InvalidParameter exception." << endl;
        sflg = 1;
      }
      catch (NotAvailable na) {
        cout << "NotAvailable exception." << endl;
        sflg = 2;
      }
      catch (InternalError ip) {
        cout << "InternalError exception." << endl;
        sflg = 3;
      }
      catch (...) {
        cout << "othrer exception." << endl;
        sflg = 4;
      }
      CPPUNIT_ASSERT(sflg == 0);

      // 1���SDOList�������Ԥ��뤫��
      rslist = m_pOi->get_members();
      CPPUNIT_ASSERT(rslist->length() == 1);
//      std::cout << "test_set_get_members OUT" << std::endl;
    }


    /*!
     * @brief add_members() and remove_member()
     */
    void test_add_remove_members() {
//      std::cout << "test_add_remove_members IN" << std::endl;
      CORBA::Boolean ret;
      SDOPackage::SDO_var sdo;
      SDOPackage::SDOList slist;
      SDOPackage::SDOList* rslist;
      Organization_impl* m_pOi2;
      std::string str;
      CORBA::Any any;

      RTC::RTObject_impl* rtobj2;
      RTC::Manager& mgr2(RTC::Manager::instance());
      mgr2.activateManager();
      rtobj2 = new ::RTC::RTObject_impl(&mgr2);
      m_pOi2 = new Organization_impl(rtobj2->getObjRef());

      // SDO �Υ��åȻ���InvalidParameter ������Ǥ��뤫��
      // add_members()�ˡ�NULL �� ���Υꥹ�Ȥ��Ϥ��Ƥ�length()=0�Ȥʤ뤿��
      // InvalidParameter���֤��������Ϥʤ���
      // SDOList �Υ��åȻ������Υꥹ�Ȥ��Ϥ��� true ������Ǥ��뤫��

      short sflg = -1;
      try {
	slist = NULL;
	ret = m_pOi->add_members(slist);
	CPPUNIT_ASSERT(ret);
	sflg = 0;
      }
      catch (InvalidParameter ip) {
        cout << "InvalidParameter exception." << endl;
        sflg = 1;
      }
      catch (NotAvailable na) {
        cout << "NotAvailable exception." << endl;
        sflg = 2;
      }
      catch (InternalError ip) {
        cout << "InternalError exception." << endl;
        sflg = 3;
      }
      catch (...) {
        cout << "othrer exception." << endl;
        sflg = 4;
      }
      CPPUNIT_ASSERT(sflg == 0);

      // SDOList �Υ��åȻ����ꥹ�Ȥ򥻥åȤ��� true ������Ǥ��뤫��
      sflg = -1;
      try {
	sdo = SDOPackage::SDO::_duplicate(rtobj2->getObjRef());
	CORBA_SeqUtil::push_back(slist, sdo);
	rtobj2->setInstanceName("hoge1");

	// SDO���С����ɲä��������뤫��
	ret = m_pOi2->add_members(slist);
	CPPUNIT_ASSERT(ret);
	sflg = 0;

        str = m_pOi2->get_organization_id(); 
	any <<= str.c_str();
	ret = m_pOi2->set_organization_property_value("instance_name", any);
      }
      catch (InvalidParameter ip) {
        cout << "InvalidParameter exception." << endl;
        sflg = 1;
      }
      catch (NotAvailable na) {
        cout << "NotAvailable exception." << endl;
        sflg = 2;
      }
      catch (InternalError ip) {
        cout << "InternalError exception." << endl;
        sflg = 3;
      }
      catch (...) {
        cout << "othrer exception." << endl;
        sflg = 4;
      }
      CPPUNIT_ASSERT(sflg == 0);

      // 1���SDOList�������Ԥ��뤫��
      rslist = m_pOi2->get_members();
      CPPUNIT_ASSERT(rslist->length() == 1);

      // SDOList�����������̤�����InvalidParameter������Ǥ��뤫��
      sflg = -1;
      try {
	ret = m_pOi2->remove_member("");
	CPPUNIT_ASSERT(ret);
	sflg = 0;
      }
      catch (InvalidParameter ip) {
//        cout << "InvalidParameter exception." << endl;
        sflg = 1;
      }
      catch (NotAvailable na) {
        cout << "NotAvailable exception." << endl;
        sflg = 2;
      }
      catch (InternalError ip) {
        cout << "InternalError exception." << endl;
        sflg = 3;
      }
      catch (...) {
        cout << "othrer exception." << endl;
        sflg = 4;
      }
      CPPUNIT_ASSERT(sflg == 1);

      // SDOList�����������������InvalidParameter������Ǥ��뤫��
      sflg = -1;
      try {
	ret = m_pOi2->remove_member("dummy");
	CPPUNIT_ASSERT(ret);
	sflg = 0;
      }
      catch (InvalidParameter ip) {
//        cout << "InvalidParameter exception." << endl;
        sflg = 1;
      }
      catch (NotAvailable na) {
        cout << "NotAvailable exception." << endl;
        sflg = 2;
      }
      catch (InternalError ip) {
        cout << "InternalError exception." << endl;
        sflg = 3;
      }
      catch (...) {
        cout << "othrer exception." << endl;
        sflg = 4;
      }
      CPPUNIT_ASSERT(sflg == 1);

      // SDOList������������������Ǻ���Ǥ��뤫��
      sflg = -1;
      try {
	ret = m_pOi2->remove_member("hoge1");
	CPPUNIT_ASSERT(ret);
	sflg = 0;
      }
      catch (InvalidParameter ip) {
        cout << "InvalidParameter exception." << endl;
        sflg = 1;
      }
      catch (NotAvailable na) {
        cout << "NotAvailable exception." << endl;
        sflg = 2;
      }
      catch (InternalError ip) {
        cout << "InternalError exception." << endl;
        sflg = 3;
      }
      catch (...) {
        cout << "othrer exception." << endl;
        sflg = 4;
      }
      CPPUNIT_ASSERT(sflg == 0);

      // 0���SDOList�������Ԥ��뤫��
      rslist = m_pOi2->get_members();
      CPPUNIT_ASSERT(rslist->length() == 0);

      if ( !CORBA::is_nil( mgr2.getPOA()) ) {
        if ( !CORBA::is_nil(mgr2.getPOAManager()) ) {
          mgr2.getPOAManager()->deactivate(false, true);
        }
      }
      rtobj2->_remove_ref();
      m_pOi2->_remove_ref();
//      std::cout << "test_add_remove_members OUT" << std::endl;
    }


    /*!
     * @brief set_dependency() and get_dependency()
     */
    void test_set_get_dependency() {
//      std::cout << "test_set_get_dependency IN" << std::endl;
      DependencyType depType;
      
      // Success case.
      // default return value is 0.
      depType = m_pOi->get_dependency();
//      cout << "depType: " << depType << endl;
      CPPUNIT_ASSERT(depType == 0);
      
      m_pOi->set_dependency(NO_DEPENDENCY);
      // returned value is 2.
      depType = m_pOi->get_dependency();
      CPPUNIT_ASSERT(depType == 2);
//      cout << "depType: " << depType << endl;
      
      // Failure case.
      //    m_pOi->set_dependency(0); // ����ѥ��륨�顼
      //    CPPUNIT_ASSERT(depType == 3);
      //    cout << "depType: " << depType << endl;
//      std::cout << "test_set_get_dependency OUT" << std::endl;
    }

  };
}; // namespace SdoOrganization

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SdoOrganization::SdoOrganizationTests);

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
#endif // SdoOrganization_cpp
