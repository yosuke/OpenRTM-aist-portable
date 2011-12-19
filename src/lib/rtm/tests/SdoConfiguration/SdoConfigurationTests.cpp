// -*- C++ -*-
/*!
 * @file   SdoConfigurationTests.cpp
 * @brief  SdoConfiguration test class
 * @date   $Date: 2008/04/23 10:43:41 $
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
 * $Id: SdoConfigurationTests.cpp 2015 2010-12-29 11:33:33Z n-ando $
 *
 */

/*
 * $Log: SdoConfigurationTests.cpp,v $
 * Revision 1.3  2008/04/23 10:43:41  arafune
 * Modified / Added some tests.
 *
 * Revision 1.2  2008/04/17 13:21:45  arafune
 * Modified some tests, and added new tests.
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/24 16:04:18  n-ando
 * The SdoConfiguration's ctor. was changed.
 *
 * Revision 1.1  2006/11/27 08:26:07  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.3  2006/11/10 07:13:44  kurihara
 * A test after SdoConfiguration class revision.
 *
 * Revision 1.2  2006/11/09 09:29:47  kurihara
 * A test after SdoConfiguration class revision.
 *
 * Revision 1.1  2006/11/01 11:23:35  kurihara
 * test program for SdoConfiguration class.
 *
 */

#ifndef SdoConfiguration_cpp
#define SdoConfiguration_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <vector>
#include <string>

#include <rtm/CORBA_SeqUtil.h>
#include <rtm/SdoConfiguration.h>
#include <rtm/RTObject.h>
#include <rtm/Manager.h>
#include <rtm/SdoOrganization.h>

/*!
 * @class SdoConfigurationTests class
 * @brief SdoConfiguration test
 */
namespace SdoConfiguration
{
  using namespace SDOPackage;
  using namespace std;
	
  struct ServiceProfileFinder
  {
    ServiceProfileFinder(const std::string& id) : _id(id) { }
			
    bool operator()(const ServiceProfile& svcProf)
    {
      return (_id == std::string(svcProf.id));
    }
			
    std::string _id;
  };

  class SdoConfigurationTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SdoConfigurationTests);

    CPPUNIT_TEST(test_set_device_profile_and_getDeviceProfile);
    CPPUNIT_TEST(test_set_service_profile_and_getServiceProfile);
    CPPUNIT_TEST(test_getServiceProfiles);
    CPPUNIT_TEST(test_remove_service_profile);
    CPPUNIT_TEST(test_add_organization_and_getOrganizations);
    CPPUNIT_TEST(test_remove_organization);
    CPPUNIT_TEST(test_add_configuration_set_and_get_configuration_set);
    CPPUNIT_TEST(test_remove_configuration_set);
    CPPUNIT_TEST(test_set_configuration_set_values);
    CPPUNIT_TEST(test_activate_configuration_set_and_get_active_configuration_set);
	//CPPUNIT_TEST(test_get_configuration_parameters);       //̤�����Τ���̤�ƥ���
	//CPPUNIT_TEST(test_get_configuration_parameter_values); //̤�����Τ���̤�ƥ���
	//CPPUNIT_TEST(test_get_configuration_parameter_value);  //̤�����Τ���̤�ƥ���
	//CPPUNIT_TEST(test_set_configuration_parameter);        //̤�����Τ���̤�ƥ���

    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
		
  public:
    /*!
     * @brief Constructor
     */
    SdoConfigurationTests()
    {
      int argc(0);
      char** argv(NULL);
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
		    m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();
    }
    
    /*!
     * @brief Destructor
     */
    ~SdoConfigurationTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      usleep(100000);
    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
		
    /*!
     * set_device_profile()�᥽�åɤ�getDeviceProfile()�᥽�åɤΥƥ���
     * 
     * - set_device_profile()�����ꤷ��DeviceProfile��getDeviceProfile()�������������Ǥ��뤫��
     */
    void test_set_device_profile_and_getDeviceProfile()
    {
//      std::cout << "test_set_device_profile_and_getDeviceProfile() IN" << std::endl;
      coil::Properties cfgAdminProp;
      RTC::ConfigAdmin cfgAdmin(cfgAdminProp);
      SDOPackage::Configuration_impl* sdoCfg = new Configuration_impl(cfgAdmin);
			
      // DeviceProfile���������
      SDOPackage::DeviceProfile devProf;
      devProf.device_type = "DEVICE_TYPE";
      devProf.manufacturer = "MANUFACTURER";
      devProf.model = "MODEL";
      devProf.version = "VERSION";
      {
	SDOPackage::NVList properties;
	properties.length(2);
	properties[0].name = "name 0";
	properties[0].value <<= CORBA::Float(3.14159);
	properties[1].name = "name 1";
	properties[1].value <<= CORBA::Float(2.71828);
	devProf.properties = properties;
      }
			
      // set_device_profile()��ƽФ��ơ���������DeviceProfile�����ꤹ��
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->set_device_profile(devProf));
			
      // getDeviceProfile()�����ꤵ��Ƥ���DeviceProfile����Ф������ꤷ����ΤȰ��פ��뤳�Ȥ��ǧ����
      const SDOPackage::DeviceProfile devProfRet = sdoCfg->getDeviceProfile();
      CPPUNIT_ASSERT_EQUAL(std::string("DEVICE_TYPE"),
			   std::string(devProfRet.device_type));
      CPPUNIT_ASSERT_EQUAL(std::string("MANUFACTURER"),
			   std::string(devProfRet.manufacturer));
      CPPUNIT_ASSERT_EQUAL(std::string("MODEL"),
			   std::string(devProfRet.model));
      CPPUNIT_ASSERT_EQUAL(std::string("VERSION"),
			   std::string(devProfRet.version));
      CPPUNIT_ASSERT_EQUAL(std::string("name 0"),
			   std::string(devProfRet.properties[0].name));
      {
	CORBA::Float value; devProfRet.properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(3.14159), value);
      }
      CPPUNIT_ASSERT_EQUAL(std::string("name 1"),
			   std::string(devProfRet.properties[1].name));
      {
	CORBA::Float value; devProfRet.properties[1].value >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(2.71828), value);
      }
      sdoCfg->_remove_ref();
//      std::cout << "test_set_device_profile_and_getDeviceProfile() OUT" << std::endl;
    }
		
    /*!
     * @brief set_service_profile()�᥽�åɤ�getServiceProfile()�᥽�åɤΥƥ���
     * 
     * - set_service_profile()�����ꤷ��ServiceProfile��getServiceProfile()�������������Ǥ��뤫��
     */
    void test_set_service_profile_and_getServiceProfile()
    {
//      std::cout << "test_set_service_profile_and_getServiceProfile() IN" << std::endl;
      coil::Properties cfgAdminProp;
      RTC::ConfigAdmin cfgAdmin(cfgAdminProp);
      SDOPackage::Configuration_impl* sdoCfg = new Configuration_impl(cfgAdmin);
			
      // ServiceProfile���������
      SDOPackage::ServiceProfile svcProf;
      svcProf.id = "ID";
      svcProf.interface_type = "INTERFACE_TYPE";
      {
	SDOPackage::NVList properties;
	properties.length(2);
	properties[0].name = "name 0";
	properties[0].value <<= CORBA::Float(3.14159);
	properties[1].name = "name 1";
	properties[1].value <<= CORBA::Float(2.71828);
	svcProf.properties = properties;
      }
			
      // ServiceProfile�����ꤹ��
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_service_profile(svcProf));
			
      // getServiceProfile()��ServiceProfile������������ꤷ����ΤȰ��פ��Ƥ��뤫��ǧ����
      const SDOPackage::ServiceProfile svcProfRet = sdoCfg->getServiceProfile("ID");
      CPPUNIT_ASSERT_EQUAL(std::string("ID"), std::string(svcProfRet.id));
      CPPUNIT_ASSERT_EQUAL(std::string("INTERFACE_TYPE"),
			   std::string(svcProfRet.interface_type));
      CPPUNIT_ASSERT_EQUAL(std::string("name 0"),
			   std::string(svcProfRet.properties[0].name));
      {
	CORBA::Float value; svcProfRet.properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(3.14159), value);
      }
      CPPUNIT_ASSERT_EQUAL(std::string("name 1"),
			   std::string(svcProfRet.properties[1].name));
      {
	CORBA::Float value; svcProfRet.properties[1].value >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(2.71828), value);
      }
      sdoCfg->_remove_ref();
//      std::cout << "test_set_service_profile_and_getServiceProfile() OUT" << std::endl;
    }
		
    /*!
     * @brief getServiceProfiles()�᥽�åɤΥƥ���
     * 
     * - ��Ͽ����Ƥ���ʣ����ServiceProfile��getServiceProfiles()�������������Ǥ��뤫��
     */
    void test_getServiceProfiles()
    {
//      std::cout << "test_getServiceProfiles() IN" << std::endl;
      coil::Properties cfgAdminProp;
      RTC::ConfigAdmin cfgAdmin(cfgAdminProp);
      SDOPackage::Configuration_impl* sdoCfg = new Configuration_impl(cfgAdmin);
			
      // ServiceProfile���������
      SDOPackage::ServiceProfile svcProf0;
      svcProf0.id = "ID 0";
      svcProf0.interface_type = "INTERFACE_TYPE 0";
      {
	SDOPackage::NVList properties;
	properties.length(2);
	properties[0].name = "name 0-0";
	properties[0].value <<= CORBA::Float(3.14159);
	properties[1].name = "name 0-1";
	properties[1].value <<= CORBA::Float(2.71828);
	svcProf0.properties = properties;
      }
    	
      SDOPackage::ServiceProfile svcProf1;
      svcProf1.id = "ID 1";
      svcProf1.interface_type = "INTERFACE_TYPE 1";
      {
	SDOPackage::NVList properties;
	properties.length(2);
	properties[0].name = "name 1-0";
	properties[0].value <<= CORBA::Float(1.41421356);
	properties[1].name = "name 1-1";
	properties[1].value <<= CORBA::Float(1.7320508);
	svcProf1.properties = properties;
      }
			
      // ServiceProfile�����ꤹ��
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_service_profile(svcProf0));
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_service_profile(svcProf1));
			
      // getServiceProfiles()�����ꤵ��Ƥ���ServiceProfile�����������
      const SDOPackage::ServiceProfileList svcProfList = sdoCfg->getServiceProfiles();
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2), svcProfList.length());
			
      // ���ꤷ��ServiceProfile�Ȱ��פ��Ƥ��뤫��
      {
	CORBA::ULong idx = CORBA_SeqUtil::find(svcProfList, ServiceProfileFinder("ID 0"));
				
	CPPUNIT_ASSERT_EQUAL(std::string("ID 0"),
			     std::string(svcProfList[idx].id));
	CPPUNIT_ASSERT_EQUAL(std::string("INTERFACE_TYPE 0"),
			     std::string(svcProfList[idx].interface_type));
	CPPUNIT_ASSERT_EQUAL(std::string("name 0-0"),
			     std::string(svcProfList[idx].properties[0].name));
	{
	  CORBA::Float value; svcProfList[idx].properties[0].value >>= value;
	  CPPUNIT_ASSERT_EQUAL(CORBA::Float(3.14159), value);
	}
	CPPUNIT_ASSERT_EQUAL(std::string("name 0-1"),
			     std::string(svcProfList[idx].properties[1].name));
	{
	  CORBA::Float value; svcProfList[idx].properties[1].value >>= value;
	  CPPUNIT_ASSERT_EQUAL(CORBA::Float(2.71828), value);
	}
      }

      {
	CORBA::ULong idx = CORBA_SeqUtil::find(svcProfList, ServiceProfileFinder("ID 1"));
				
	CPPUNIT_ASSERT_EQUAL(std::string("ID 1"),
			     std::string(svcProfList[idx].id));
	CPPUNIT_ASSERT_EQUAL(std::string("INTERFACE_TYPE 1"),
			     std::string(svcProfList[idx].interface_type));
	CPPUNIT_ASSERT_EQUAL(std::string("name 1-0"),
			     std::string(svcProfList[idx].properties[0].name));
	{
	  CORBA::Float value; svcProfList[idx].properties[0].value >>= value;
	  CPPUNIT_ASSERT_EQUAL(CORBA::Float(1.41421356), value);
	}
	CPPUNIT_ASSERT_EQUAL(std::string("name 1-1"),
			     std::string(svcProfList[idx].properties[1].name));
	{
	  CORBA::Float value; svcProfList[idx].properties[1].value >>= value;
	  CPPUNIT_ASSERT_EQUAL(CORBA::Float(1.7320508), value);
	}
      }
      sdoCfg->_remove_ref();
//      std::cout << "test_getServiceProfiles() OUT" << std::endl;
    }
    
    /*!
     * @brief remove_service_profile()�᥽�åɤΥƥ���
     * 
     * - ���ꤷ��ID�����ServiceProfile����������Ͽ����Ǥ��뤫��
     */
    void test_remove_service_profile()
    {
//      std::cout << "test_remove_service_profile() IN" << std::endl;
      coil::Properties cfgAdminProp;
      RTC::ConfigAdmin cfgAdmin(cfgAdminProp);
      SDOPackage::Configuration_impl* sdoCfg = new Configuration_impl(cfgAdmin);
			
      // ServiceProfile���������
      SDOPackage::ServiceProfile svcProf0;
      svcProf0.id = "ID 0";
      svcProf0.interface_type = "INTERFACE_TYPE 0";
      {
	SDOPackage::NVList properties;
	properties.length(2);
	properties[0].name = "name 0-0";
	properties[0].value <<= CORBA::Float(3.14159);
	properties[1].name = "name 0-1";
	properties[1].value <<= CORBA::Float(2.71828);
	svcProf0.properties = properties;
      }
    	
      SDOPackage::ServiceProfile svcProf1;
      svcProf1.id = "ID 1";
      svcProf1.interface_type = "INTERFACE_TYPE 1";
      {
	SDOPackage::NVList properties;
	properties.length(2);
	properties[0].name = "name 1-0";
	properties[0].value <<= CORBA::Float(1.41421356);
	properties[1].name = "name 1-1";
	properties[1].value <<= CORBA::Float(1.7320508);
	svcProf1.properties = properties;
      }
			
      // ServiceProfile�����ꤹ��
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_service_profile(svcProf0));
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_service_profile(svcProf1));
			
      // ���ꤷ��ServiceProfile�Τ�������������Ͽ�������
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->remove_service_profile("ID 0"));
			
      // getServiceProfiles()����ServiceProfile�����������Ͽ���������Τ��ޤޤ�ʤ����Ȥ��ǧ����
      const SDOPackage::ServiceProfileList svcProfList = sdoCfg->getServiceProfiles();
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(1), svcProfList.length());
      CPPUNIT_ASSERT_EQUAL(CORBA::Long(-1),
			   CORBA_SeqUtil::find(svcProfList, ServiceProfileFinder("ID 0")));
			
      // ��Ͽ������Ƥ��ʤ���Τϡ������Ȥ��ƴޤޤ�Ƥ��뤫��
      CPPUNIT_ASSERT_EQUAL(CORBA::Long(0),
			   CORBA_SeqUtil::find(svcProfList, ServiceProfileFinder("ID 1")));

      sdoCfg->_remove_ref();
//      std::cout << "test_remove_service_profile() OUT" << std::endl;
    }
    
    /* 
     * @brief add_organization()�᥽�åɤ�getOrganizations()�᥽�åɤΥƥ���
     * 
     * - add_organization()��Organization_ptr���󥹥��󥹤���Ͽ�Ǥ��뤫��
     * - getOrganizations()����Ͽ����Ƥ���Organization_ptr���󥹥��󥹷�������Ǥ��뤫��
     */
    void test_add_organization_and_getOrganizations()
    {
//      std::cout << "test_add_organization_and_getOrganizations() IN" << std::endl;
      coil::Properties cfgAdminProp;
      RTC::ConfigAdmin cfgAdmin(cfgAdminProp);
      SDOPackage::Configuration_impl* sdoCfg = new Configuration_impl(cfgAdmin);
			
      // Organization��2����Ͽ����
      SDOPackage::Organization_var org1;
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true),
			   sdoCfg->add_organization(org1._retn()));

      SDOPackage::Organization_var org2;
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true),
			   sdoCfg->add_organization(org2._retn()));
      
      // ���������Organization�ο��ϡ��տޤɤ���2�Ĥ���
      SDOPackage::OrganizationList orgList = sdoCfg->getOrganizations();
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2), orgList.length());

      sdoCfg->_remove_ref();
//      std::cout << "test_add_organization_and_getOrganizations() OUT" << std::endl;
    }
    
    /*
     * @brief remove_organization()�Υƥ���
     * - add_organization()����Ͽ����remove_organization()������������Ǥ��뤫��
     */
    void test_remove_organization()
    {
//      std::cout << "test_remove_organization() IN" << std::endl;
      coil::Properties cfgAdminProp;
      RTC::ConfigAdmin cfgAdmin(cfgAdminProp);
      SDOPackage::Configuration_impl* sdoCfg = new Configuration_impl(cfgAdmin);
      RTC::RTObject_impl* rtobj;
      SDOPackage::Organization_impl* m_pOi;
      RTC::Manager& mgr(RTC::Manager::instance());
      rtobj = new ::RTC::RTObject_impl(&mgr);
      m_pOi = new Organization_impl(rtobj->getObjRef());
			
      // Organization����Ͽ����
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true),
			   sdoCfg->add_organization(m_pOi->getObjRef()));

      // organization_id���������
      std::string id(m_pOi->get_organization_id());

      // ��Ͽ����Organization��������
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true),
			   sdoCfg->remove_organization(id.c_str()));

      // ���������Organization�ο��ϡ��տޤɤ���0�狼��
      SDOPackage::OrganizationList orgList = sdoCfg->getOrganizations();
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(0), orgList.length());

      m_pOi->_remove_ref();
      rtobj->_remove_ref();
      sdoCfg->_remove_ref();
//      std::cout << "test_remove_organization() OUT" << std::endl;
    }
				
    /*
     * @brief get_configuration_parameters()�Υƥ���
     */
    void test_get_configuration_parameters()
    {
      // �ƥ����оݤǤ���SDOPackage::Confirutaion_impl::get_configuration_parameters()��
      // ̤�����Ǥ��뤿�ᡢ�ܥƥ��Ȥ�̤�����Ǥ��롣
//      std::cout << "test_get_configuration_parameters() IN" << std::endl;
//      std::cout << "test_get_configuration_parameters() OUT" << std::endl;
    }
		
    /*!
     * @brief get_configuration_parameter_values()�Υƥ���
     */
    void test_get_configuration_parameter_values()
    {
      // �ƥ����оݤǤ���SDOPackage::Confirutaion_impl::get_configuration_parameter_values()��
      // ̤�����Ǥ��뤿�ᡢ�ܥƥ��Ȥ�̤�����Ǥ��롣
//      std::cout << "test_get_configuration_parameter_values() IN" << std::endl;
//      std::cout << "test_get_configuration_parameter_values() OUT" << std::endl;
    }
		
    /*!
     * @brief get_configuration_parameter_value()�Υƥ���
     */
    void test_get_configuration_parameter_value()
    {
      // �ƥ����оݤǤ���SDOPackage::Confirutaion_impl::get_configuration_parameter_value()��
      // ̤�����Ǥ��뤿�ᡢ�ܥƥ��Ȥ�̤�����Ǥ��롣
//      std::cout << "test_get_configuration_parameter_value() IN" << std::endl;
//      std::cout << "test_get_configuration_parameter_value() OUT" << std::endl;
    }
		
    /*!
     * @brief set_configuration_parameter()�Υƥ���
     */
    void test_set_configuration_parameter()
    {
      // �ƥ����оݤǤ���SDOPackage::Confirutaion_impl::set_configuration_parameter()��
      // ̤�����Ǥ��뤿�ᡢ�ܥƥ��Ȥ�̤�����Ǥ��롣
//      std::cout << "test_set_configuration_parameter() IN" << std::endl;
//      std::cout << "test_set_configuration_parameter() OUT" << std::endl;
    }
		
    /*!
     * @brief add/get_configuration_set()�᥽�åɤΥƥ���
     * 
     * - ConfigurationSet��add_configuration_set()���������Ͽ�Ǥ��뤫��
     * - add_configuration_set()����Ͽ����ConfigurationSet��get_configuration_set()�������������Ǥ��뤫��
     */
    void test_add_configuration_set_and_get_configuration_set()
    {
//      std::cout << "test_add_configuration_set_and_get_configuration_set() IN" << std::endl;
      coil::Properties cfgAdminProp;
      RTC::ConfigAdmin cfgAdmin(cfgAdminProp);
      SDOPackage::Configuration_impl* sdoCfg = new Configuration_impl(cfgAdmin);
			
      // ConfigurationSet���������
      SDOPackage::ConfigurationSet cfgSet0;
      cfgSet0.id = "ID 0";
      cfgSet0.description = "DESCRIPTION 0";
      cfgSet0.configuration_data.length(2);
      cfgSet0.configuration_data[0].name = "NAME 0-0";
      cfgSet0.configuration_data[0].value <<= "3.14159";
      cfgSet0.configuration_data[1].name = "NAME 0-1";
      cfgSet0.configuration_data[1].value <<= "2.71828";
			
      SDOPackage::ConfigurationSet cfgSet1;
      cfgSet1.id = "ID 1";
      cfgSet1.description = "DESCRIPTION 1";
      cfgSet1.configuration_data.length(2);
      cfgSet1.configuration_data[0].name = "NAME 1-0";
      cfgSet1.configuration_data[0].value <<= "1.41421356";
      cfgSet1.configuration_data[1].name = "NAME 1-1";
      cfgSet1.configuration_data[1].value <<= "1.7320508";
			
      // ��������ConfigurationSet����Ͽ����
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_configuration_set(cfgSet0));
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_configuration_set(cfgSet1));
			
      // ��Ͽ����ConfigurationSet�������������Ǥ��뤫��
      SDOPackage::ConfigurationSet* cfgSetRet0 = sdoCfg->get_configuration_set("ID 0");
      CPPUNIT_ASSERT_EQUAL(std::string("ID 0"),
			   std::string(cfgSetRet0->id));
//Deleted this test, because description was not used.
//      CPPUNIT_ASSERT_EQUAL(std::string("DESCRIPTION 0"),
//			   std::string(cfgSetRet0->description));
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2),
			   cfgSetRet0->configuration_data.length());
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 0-0"),
			   std::string(cfgSetRet0->configuration_data[0].name));
      {
	const char* value; cfgSetRet0->configuration_data[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("3.14159"), std::string(value));
      }
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 0-1"),
			   std::string(cfgSetRet0->configuration_data[1].name));
      {
	const char* value; cfgSetRet0->configuration_data[1].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("2.71828"), std::string(value));
      }

      SDOPackage::ConfigurationSet* cfgSetRet1 = sdoCfg->get_configuration_set("ID 1");
      CPPUNIT_ASSERT_EQUAL(std::string("ID 1"),
			   std::string(cfgSetRet1->id));
//Deleted this test, because description was not used.
//      CPPUNIT_ASSERT_EQUAL(std::string("DESCRIPTION 1"),
//			   std::string(cfgSetRet1->description));
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2),
			   cfgSetRet1->configuration_data.length());
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 1-0"),
			   std::string(cfgSetRet1->configuration_data[0].name));
      {
	const char* value; cfgSetRet1->configuration_data[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("1.41421356"), std::string(value));
      }
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 1-1"),
			   std::string(cfgSetRet1->configuration_data[1].name));
      {
	const char* value; cfgSetRet1->configuration_data[1].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("1.7320508"), std::string(value));
      }

      sdoCfg->_remove_ref();
//      std::cout << "test_add_configuration_set_and_get_configuration_set() OUT" << std::endl;
    }
		
    /*!
     * @brief remove_configuration_set()�᥽�åɤΥƥ���
     * 
     * - ��Ͽ�Ѥߤ�ConfigurationSet����������Ͽ����Ǥ��뤫��
     * - ��Ͽ����Ƥ��ʤ�ID����ꤷ����硢�տޤɤ����㳰����������뤫��
     */
    void test_remove_configuration_set()
    {
//      std::cout << "test_remove_configuration_set() IN" << std::endl;
      coil::Properties cfgAdminProp;
      RTC::ConfigAdmin cfgAdmin(cfgAdminProp);
      SDOPackage::Configuration_impl* sdoCfg = new Configuration_impl(cfgAdmin);
			
      // ConfigurationSet���������
      SDOPackage::ConfigurationSet cfgSet0;
      cfgSet0.id = "ID 0";
      cfgSet0.description = "DESCRIPTION 0";
      cfgSet0.configuration_data.length(2);
      cfgSet0.configuration_data[0].name = "NAME 0-0";
      cfgSet0.configuration_data[0].value <<= "3.14159";
      cfgSet0.configuration_data[1].name = "NAME 0-1";
      cfgSet0.configuration_data[1].value <<= "2.71828";
			
      SDOPackage::ConfigurationSet cfgSet1;
      cfgSet1.id = "ID 1";
      cfgSet1.description = "DESCRIPTION 1";
      cfgSet1.configuration_data.length(2);
      cfgSet1.configuration_data[0].name = "NAME 1-0";
      cfgSet1.configuration_data[0].value <<= "1.41421356";
      cfgSet1.configuration_data[1].name = "NAME 1-1";
      cfgSet1.configuration_data[1].value <<= "1.7320508";
			
      // ��������ConfigurationSet����Ͽ����
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_configuration_set(cfgSet0));
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_configuration_set(cfgSet1));
			
      // ��Ͽ����������������ConfigurationSet����Ͽ�������
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->remove_configuration_set("ID 0"));
			
      // ��Ͽ�������ConfigurationSet����ꤷ�ơ�get_configuration_set()�ƽФ��ߤơ�
      // �տޤɤ�����㳰����������뤫��
      try
	{
	  sdoCfg->get_configuration_set("ID 0");
	  CPPUNIT_FAIL("ID 0 was not removed.");
	}
      catch (SDOPackage::InvalidParameter expected) {}
      catch (...) {}
			
      // ����id����ꤷ�ơ�get_configuration_set()�ƽФ��ߤơ�
      // �տޤɤ�����㳰����������뤫��
      try
	{
	  sdoCfg->get_configuration_set("");
	  CPPUNIT_FAIL("ID Not set.");
	}
      catch (SDOPackage::InvalidParameter expected) {}
      catch (...) {}
			
      // ��Ͽ������Ƥ��ʤ�ConfigurationSet�ϡ������Ȥ��Ƽ����Ǥ��뤫��
      SDOPackage::ConfigurationSet* cfgSetRet = sdoCfg->get_configuration_set("ID 1");
      CPPUNIT_ASSERT_EQUAL(std::string("ID 1"), std::string(cfgSetRet->id));
			
      // ¸�ߤ��ʤ�ID����ꤷ����Ͽ������ߤ����ˡ��տޤɤ�����㳰����������뤫��
      try
	{
	  sdoCfg->remove_configuration_set("inexist ID");
	  CPPUNIT_FAIL("Exception not thrown.");
	}
      catch (SDOPackage::InvalidParameter expected) {}
      catch (...) {}

      sdoCfg->_remove_ref();
//      std::cout << "test_remove_configuration_set() OUT" << std::endl;
    }
		
    /*!
     * @brief set_configuration_set_values()�᥽�åɤΥƥ���
     * 
     * - ��Ͽ�Ѥߤ�ConfigurationSet��ID����ꤷ�ơ�������ConfigurationSet�򹹿��Ǥ��뤫��
     * - ¸�ߤ��ʤ�ID����ꤷ�����ˡ��տޤɤ�����㳰����������뤫��
     */
    void test_set_configuration_set_values()
    {
//      std::cout << "test_set_configuration_set_values() IN" << std::endl;
      coil::Properties cfgAdminProp;
      RTC::ConfigAdmin cfgAdmin(cfgAdminProp);
      SDOPackage::Configuration_impl* sdoCfg = new Configuration_impl(cfgAdmin);
			
      // ConfigurationSet���������
      SDOPackage::ConfigurationSet cfgSet0;
      cfgSet0.id = "ID 0";
      cfgSet0.description = "DESCRIPTION 0";
      cfgSet0.configuration_data.length(2);
      cfgSet0.configuration_data[0].name = "NAME 0-0";
      cfgSet0.configuration_data[0].value <<= "3.14159";
      cfgSet0.configuration_data[1].name = "NAME 0-1";
      cfgSet0.configuration_data[1].value <<= "2.71828";
			
      SDOPackage::ConfigurationSet cfgSet1;
      cfgSet1.id = "ID 1";
      cfgSet1.description = "DESCRIPTION 1";
      cfgSet1.configuration_data.length(2);
      cfgSet1.configuration_data[0].name = "NAME 1-0";
      cfgSet1.configuration_data[0].value <<= "1.41421356";
      cfgSet1.configuration_data[1].name = "NAME 1-1";
      cfgSet1.configuration_data[1].value <<= "1.7320508";

      SDOPackage::ConfigurationSet cfgSet1_Modified;
      cfgSet1_Modified.id = "ID 1";
      cfgSet1_Modified.description = "DESCRIPTION 1 M";
      cfgSet1_Modified.configuration_data.length(2);
      cfgSet1_Modified.configuration_data[0].name = "NAME 1-0";
      cfgSet1_Modified.configuration_data[0].value <<= "2.23620679";
      cfgSet1_Modified.configuration_data[1].name = "NAME 1-1";
      cfgSet1_Modified.configuration_data[1].value <<= "2.44948974";

      // ��������ConfigurationSet����Ͽ����
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_configuration_set(cfgSet0));
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_configuration_set(cfgSet1));
			
      // ��Ͽ����ConfigurationSet�Τ���������set_configuration_set_values()�ǹ�������
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true),
			   sdoCfg->set_configuration_set_values(cfgSet1_Modified));
			
      // ��������ConfigurationSet�������������Ǥ��뤫��
      SDOPackage::ConfigurationSet* cfgSetRet = sdoCfg->get_configuration_set("ID 1");
      CPPUNIT_ASSERT_EQUAL(std::string("ID 1"), std::string(cfgSetRet->id));

//Deleted this test, because description was not used.
//      CPPUNIT_ASSERT_EQUAL(std::string("DESCRIPTION 1 M"),
//			   std::string(cfgSetRet->description));
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2),
			   cfgSetRet->configuration_data.length());

      {
	const char* value; cfgSetRet->configuration_data[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("2.23620679"), std::string(value));
      }
      {
	const char* value; cfgSetRet->configuration_data[1].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("2.44948974"), std::string(value));
      }
			
      // ����ID����ꤷ��set_configuration_set_values()��ƽФ���
      // �տޤɤ����㳰����������뤫��
      try
	{
	  cfgSet1_Modified.id = "";
	  sdoCfg->set_configuration_set_values(cfgSet1_Modified);
	  CPPUNIT_FAIL("Exception not thrown.");
	}
      catch (SDOPackage::InvalidParameter expected) {
	}

      sdoCfg->_remove_ref();
//      std::cout << "test_set_configuration_set_values() OUT" << std::endl;
    }
		
    /*!
     * @brief activate_configuration_set()�᥽�åɡ�get_active_configuration_set()�᥽�åɡ�
     * get_configuration_sets()�᥽�åɤΥƥ���
     * 
     */
    void test_activate_configuration_set_and_get_active_configuration_set()
    {
//      std::cout << "test_activate_configuration_set_and_get_active_configuration_set() IN" << std::endl;
      coil::Properties cfgAdminProp;
      RTC::ConfigAdmin cfgAdmin(cfgAdminProp);
      SDOPackage::Configuration_impl* sdoCfg = new Configuration_impl(cfgAdmin);
	
      // ConfigurationSet���������
      SDOPackage::ConfigurationSet cfgSet0;
      cfgSet0.id = "ID 0";
      cfgSet0.description = "DESCRIPTION 0";
      cfgSet0.configuration_data.length(2);
      cfgSet0.configuration_data[0].name = "NAME 0-0";
      cfgSet0.configuration_data[0].value <<= "3.14159";
      cfgSet0.configuration_data[1].name = "NAME 0-1";
      cfgSet0.configuration_data[1].value <<= "2.71828";
			
      SDOPackage::ConfigurationSet cfgSet1;
      cfgSet1.id = "ID 1";
      cfgSet1.description = "DESCRIPTION 1";
      cfgSet1.configuration_data.length(2);
      cfgSet1.configuration_data[0].name = "NAME 1-0";
      cfgSet1.configuration_data[0].value <<= "1.41421356";
      cfgSet1.configuration_data[1].name = "NAME 1-1";
      cfgSet1.configuration_data[1].value <<= "1.7320508";

      // ��������ConfigurationSet����Ͽ����
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_configuration_set(cfgSet0));
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->add_configuration_set(cfgSet1));
			
      // ConfigurationSet �ꥹ�Ȥ��������
      ConfigurationSetList_var config_sets(sdoCfg->get_configuration_sets());

      // ����������������Ƥ����פ��Ƥ��뤫��
      CPPUNIT_ASSERT(config_sets->length() == 2);
      CPPUNIT_ASSERT_EQUAL(std::string("ID 0"),
			   std::string(config_sets[0].id));
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 0-0"),
			   std::string(config_sets[0].configuration_data[0].name));
      {
	const char* value; config_sets[0].configuration_data[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("3.14159"), std::string(value));
      }
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 0-1"),
			   std::string(config_sets[0].configuration_data[1].name));
      {
	const char* value; config_sets[0].configuration_data[1].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("2.71828"), std::string(value));
      }

      CPPUNIT_ASSERT_EQUAL(std::string("ID 1"),
			   std::string(config_sets[1].id));
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 1-0"),
			   std::string(config_sets[1].configuration_data[0].name));
      {
	const char* value; config_sets[1].configuration_data[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("1.41421356"), std::string(value));
      }
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 1-1"),
			   std::string(config_sets[1].configuration_data[1].name));
      {
	const char* value; config_sets[1].configuration_data[1].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("1.7320508"), std::string(value));
      }

      // "ID 0"�Τۤ��򥢥��ƥ��ֲ�����
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->activate_configuration_set("ID 0"));
			
      // �����ƥ��֤�ConfigurationSet������������줬�����ƥ��ֲ�������ΤȰ��פ��뤫��
      SDOPackage::ConfigurationSet* cfgSetRet0 = sdoCfg->get_active_configuration_set();
      CPPUNIT_ASSERT_EQUAL(std::string("ID 0"), std::string(cfgSetRet0->id));

//Deleted this test, because description was not used.
//      CPPUNIT_ASSERT_EQUAL(std::string("DESCRIPTION 0"),
//			   std::string(cfgSetRet0->description));
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2),
			   cfgSetRet0->configuration_data.length());
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 0-0"),
			   std::string(cfgSetRet0->configuration_data[0].name));
      {
	const char* value; cfgSetRet0->configuration_data[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("3.14159"), std::string(value));
      }
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 0-1"),
			   std::string(cfgSetRet0->configuration_data[1].name));
      {
	const char* value; cfgSetRet0->configuration_data[1].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("2.71828"), std::string(value));
      }

      // "ID 1"�Τۤ��򥢥��ƥ��ֲ�����
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), sdoCfg->activate_configuration_set("ID 1"));
			
      // �����ƥ��֤�ConfigurationSet������������줬�����ƥ��ֲ�������ΤȰ��פ��뤫��
      SDOPackage::ConfigurationSet* cfgSetRet1 = sdoCfg->get_active_configuration_set();
      CPPUNIT_ASSERT_EQUAL(std::string("ID 1"), std::string(cfgSetRet1->id));

//Deleted this test, because description was not used.
//      CPPUNIT_ASSERT_EQUAL(std::string("DESCRIPTION 1"),
//			   std::string(cfgSetRet1->description));
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2),
			   cfgSetRet1->configuration_data.length());
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 1-0"),
			   std::string(cfgSetRet1->configuration_data[0].name));
      {
	const char* value; cfgSetRet1->configuration_data[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("1.41421356"), std::string(value));
      }
      CPPUNIT_ASSERT_EQUAL(std::string("NAME 1-1"),
			   std::string(cfgSetRet1->configuration_data[1].name));
      {
	const char* value; cfgSetRet1->configuration_data[1].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("1.7320508"), std::string(value));
      }
			
      // ¸�ߤ��ʤ�ID����ꤷ��activate_configuration_set()��ƽФ����տޤɤ�����㳰����������뤫��
      try
	{
	  sdoCfg->activate_configuration_set("inexist ID");
	  CPPUNIT_FAIL("Exception not thrown.");
	}
      catch (SDOPackage::InvalidParameter expected) {}

      sdoCfg->_remove_ref();
//      std::cout << "test_activate_configuration_set_and_get_active_configuration_set() OUT" << std::endl;
    }

  };
}; // namespace SdoConfiguration

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SdoConfiguration::SdoConfigurationTests);

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
#endif // SdoConfiguration_cpp
