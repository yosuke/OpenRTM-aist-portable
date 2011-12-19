// -*- C++ -*-
/*!
 * @file   RTObjectTests.cpp
 * @brief  RTObject test class
 * @date   $Date: 2008/04/24 08:49:57 $
 *
 * $Id: RTObjectTests.cpp,v 1.1 2008/04/24 08:49:57 arafune Exp $
 *
 */

/*
 * $Log: RTObjectTests.cpp,v $
 * Revision 1.1  2008/04/24 08:49:57  arafune
 * The first commitment.
 *
 */

#ifndef RTObject_cpp
#define RTObject_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/RTC.h>
#include <rtm/PeriodicExecutionContext.h>
#include <rtm/RTObject.h>

/*!
 * @class RTObjectTests class
 * @brief RTObject test
 */
namespace RTObject
{
  class RTObjectMock
    : public RTC::RTObject_impl
  {
  public:
    RTObjectMock(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
      : RTC::RTObject_impl(orb, poa)
    {
    }

    virtual ~RTObjectMock()
    {
    }
		
    virtual RTC::ReturnCode_t on_initialize()
      throw (CORBA::SystemException)
    {
      log("on_initialize");
      return RTC::RTObject_impl::on_initialize();
    }
		
    virtual RTC::ReturnCode_t on_finalize()
      throw (CORBA::SystemException)
    {
      log("on_finalize");
      return RTC::RTObject_impl::on_finalize();
    }

    virtual RTC::UniqueId bindContext(RTC::ExecutionContext_ptr exec_context)
    {
      RTC::UniqueId id;
      id = RTC::RTObject_impl::bindContext(exec_context);
      ecMine = RTC::RTObject_impl::m_ecMine;
      return id;
    }
    RTC::ExecutionContextServiceList ecMine;

    // protected: m_ecMine������
    void set_ecMine()
    {
      RTC::RTObject_impl::m_ecMine = ecMine;
    }

    // protected: m_ecMine��Ƚ��
    bool chk_ecMine(int id, RTC::ExecutionContext_ptr exec_context)
    {
      RTC::ExecutionContextService_var ecs;
      ecs = RTC::ExecutionContextService::_narrow(exec_context);
      if (RTC::RTObject_impl::m_ecMine[id] == ecs)
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    std::vector<RTC::ExecutionContextBase*> eclist;
    // protected: m_eclist�μ���
    int get_eclist()
    {
      int len(RTC::RTObject_impl::m_eclist.size());
      eclist = RTC::RTObject_impl::m_eclist;
      return len;
    }

		
  public: // helper for test
    int countLog(std::string line)
    {
      int count = 0;
      for (int i = 0; i < (int) m_log.size(); ++i)
	{
	  if (m_log[i] == line) ++count;
	}
      return count;
    }
		
    void set_status(const char* name, const CORBA::Any& value)
    {
      CORBA::Long idx = NVUtil::find_index(m_sdoStatus, name);
      if (idx < 0)
	{
	  SDOPackage::NameValue nv = NVUtil::newNVAny(name, value);
	  CORBA_SeqUtil::push_back(m_sdoStatus, nv);
	}
      else
	{
	  m_sdoStatus[idx].value <<= value;
	}
    }
    
    void shutdown() 
    {
      RTObject_impl::shutdown();
    }
    
		
  private:
    void log(const std::string& msg)
    {
      m_log.push_back(msg);
    }
		
  private:
    std::vector<std::string> m_log;
  };
	
  class PortMock
    : public RTC::PortBase
  {
  protected:
    virtual RTC::ReturnCode_t publishInterfaces(RTC::ConnectorProfile& connector_profile)
    {
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t subscribeInterfaces(const RTC::ConnectorProfile& connector_profile)
    {
      return RTC::RTC_OK;
    }
    virtual void unsubscribeInterfaces(const RTC::ConnectorProfile& connector_profile)
    {
    }
    virtual void activateInterfaces()
    {
    }
    virtual void deactivateInterfaces()
    {
    }
  };

  class InPortMock
    : public RTC::InPortBase
  {
  public:
    InPortMock(const char* name, const char* data_type)
      :RTC::InPortBase(name, data_type),
       m_return(true),
       m_cnt(0)
    {
      return;
    }
    
    bool read(){
      ++m_cnt;
      return m_return;
    }

    void set_return(bool ret)
    {
      m_return = ret;
    }

    int get_counter()
    {
      return m_cnt;
    }

  private:
    bool m_return;
    int m_cnt;
  };
	
  class OutPortMock
    : public RTC::OutPortBase
  {
  public:
    OutPortMock(const char* name, const char* data_type)
      : OutPortBase(name, data_type),
       m_return(true),
       m_cnt(0)
    {
      return;
    }
    virtual ~OutPortMock() {}

    bool write() {
      ++m_cnt;
      return m_return;
    }
    void set_return(bool ret)
    {
      m_return = ret;
    }

    int get_counter()
    {
      return m_cnt;
    }
  private:
    bool m_return;
    int m_cnt;
  };
	
  class SDOServiceMock
    : public POA_SDOPackage::SDOService,
      public virtual PortableServer::RefCountServantBase
  {
  };
	
  struct PortFinder
  {
    PortFinder(const RTC::PortService_ptr& port) : m_port(port) {}
    bool operator()(const RTC::PortService_ptr& port)
    {
      return m_port->_is_equivalent(port);
    }
		
    const RTC::PortService_ptr& m_port;
  };
	
  class SDOSystemElementMock
    : public POA_SDOPackage::SDOSystemElement,
      public virtual PortableServer::RefCountServantBase
  {
  };
	
  class OrganizationMock
    : public POA_SDOPackage::Organization,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    OrganizationMock(const char* id) : m_id(id)
    {
    }
		
    virtual char* get_organization_id()
    {
      return CORBA::string_dup(m_id);
    }
		
    virtual SDOPackage::OrganizationProperty* get_organization_property()
    {
      return NULL;
    }
		
    virtual CORBA::Any* get_organization_property_value(const char* name)
    {
      return NULL;
    }
		
    virtual CORBA::Boolean add_organization_property(const SDOPackage::OrganizationProperty& organization_property)
    {
      return false;
    }
		
    virtual CORBA::Boolean set_organization_property_value(const char* name, const CORBA::Any& value)
    {
      return false;
    }
		
    virtual CORBA::Boolean remove_organization_property(const char* name)
    {
      return false;
    }
		
    virtual SDOPackage::SDOSystemElement_ptr get_owner()
    {
      return NULL;
    }
		
    virtual CORBA::Boolean set_owner(SDOPackage::SDOSystemElement_ptr sdo)
    {
      return false;
    }
		
    virtual SDOPackage::SDOList* get_members()
    {
      return NULL;
    }
		
    virtual CORBA::Boolean set_members(const SDOPackage::SDOList& sdos)
    {
      return false;
    }
		
    virtual CORBA::Boolean add_members(const SDOPackage::SDOList& sdo_list)
    {
      return false;
    }
		
    virtual CORBA::Boolean remove_member(const char* id)
    {
      return false;
    }
		
    virtual SDOPackage::DependencyType get_dependency()
    {
      return SDOPackage::NO_DEPENDENCY;
    }
		
    virtual CORBA::Boolean set_dependency(SDOPackage::DependencyType dependency)
    {
      return false;
    }
		
  private:
    const char* m_id;
  };
	
  struct ExecutionContextServiceFinder
  {
    ExecutionContextServiceFinder(const RTC::ExecutionContextService_ptr& ecSvc)
      : m_ecSvc(ecSvc) {}
    bool operator()(const RTC::ExecutionContextService_ptr& ecSvc)
    {
      return m_ecSvc->_is_equivalent(ecSvc);
    }
    const RTC::ExecutionContextService_ptr& m_ecSvc;
  };
	
  struct ServiceProfileFinder
  {
    ServiceProfileFinder(const char* id) : m_id(id) {}
    bool operator()(const SDOPackage::ServiceProfile& svcProf)
    {
      return strcmp(m_id, (const char*)(svcProf.id)) == 0;
    }
    const char* m_id;
  };
	
  struct OrganizationFinder
  {
    OrganizationFinder(const char* id) : m_id(id) {}
    bool operator()(const SDOPackage::Organization_ptr& org)
    {
      return strcmp(m_id, org->get_organization_id()) == 0;
    }
    const char* m_id;
  };
	
  class RTObjectTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(RTObjectTests);

    CPPUNIT_TEST(test_finalizeContexts);
    CPPUNIT_TEST(test_bindContext);
    CPPUNIT_TEST(test_add_removePort);
    CPPUNIT_TEST(test_readAll);
    CPPUNIT_TEST(test_writeAll);
    CPPUNIT_TEST(test_initialize_invoking_on_initialize);
    CPPUNIT_TEST(test_initialize_in_Alive);
    CPPUNIT_TEST(test_finalize_invoking_on_finalize);
    CPPUNIT_TEST(test_finalize_participating_in_execution_context);
    CPPUNIT_TEST(test_finalize_in_Created);
    //		CPPUNIT_TEST(test_is_alive);
    CPPUNIT_TEST(test_exit);
    CPPUNIT_TEST(test_exit_in_Created);
    CPPUNIT_TEST(test_detach_executioncontext);
    CPPUNIT_TEST(test_detach_executioncontext_with_illegal_id);
    CPPUNIT_TEST(test_get_context);
    CPPUNIT_TEST(test_get_contexts);
    CPPUNIT_TEST(test_get_component_profile);
    CPPUNIT_TEST(test_get_ports);
//    CPPUNIT_TEST(test_get_execution_context_services);
    //		CPPUNIT_TEST(test_get_owned_organizations);
    CPPUNIT_TEST(test_get_sdo_id);
    CPPUNIT_TEST(test_get_sdo_type);
    //		CPPUNIT_TEST(test_get_device_profile);
    //		CPPUNIT_TEST(test_get_service_profile);
    CPPUNIT_TEST(test_get_service_profile_with_illegal_arguments);
    CPPUNIT_TEST(test_get_sdo_service);
    CPPUNIT_TEST(test_get_sdo_service_with_illegal_arguments);
    CPPUNIT_TEST(test_get_configuration_and_set_device_profile_and_get_device_profile);
    CPPUNIT_TEST(test_get_configuration_and_set_service_profile_and_get_service_profile);
    CPPUNIT_TEST(test_get_configuration_and_set_service_profile_and_get_service_profiles);
    CPPUNIT_TEST(test_get_configuration_and_set_service_profile_and_get_sdo_service);
    CPPUNIT_TEST(test_get_configuration_and_remove_service_profile);
    CPPUNIT_TEST(test_get_configuration_and_add_organization_and_get_organizations);
    CPPUNIT_TEST(test_get_configuration_and_remove_organization);
    //		CPPUNIT_TEST(test_get_monitoring);
    CPPUNIT_TEST(test_get_status);
    CPPUNIT_TEST(test_get_status_list);

    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
	
  public:
    /*!
     * @brief Constructor
     */
    RTObjectTests()
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
    virtual ~RTObjectTests()
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
     * @brief initialize()�᥽�åɤΥƥ���
     * 
     * - initialize()�᥽�åɸƽФˤ�ꡢon_initialize()������Хå����ƤӽФ���뤫��
     */
    void test_initialize_invoking_on_initialize()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // initialize()�᥽�åɸƽФˤ�ꡢon_initialize()������Хå����ƤӽФ���뤫��
      CPPUNIT_ASSERT_EQUAL(0, rto->countLog("on_initialize"));
      coil::Properties prop;
      prop.setProperty("exec_cxt.periodic.type","PeriodicExecutionContext");
      prop.setProperty("exec_cxt.periodic.rate","1000");
      rto->setProperties(prop);
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->initialize());
      CPPUNIT_ASSERT_EQUAL(1, rto->countLog("on_initialize"));
      rto->exit();
      delete rto;
    }
		
    /*!
     * @brief initialize()�᥽�åɤΥƥ���
     * 
     * - Alive���֤λ���initialize()�᥽�åɤ�ƽФ���硢�����ư��뤫��
     */
    void test_initialize_in_Alive()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // initialize()�᥽�åɸƽФ���Ԥ���Alive���֤����ܤ�����
      coil::Properties prop;
      prop.setProperty("exec_cxt.periodic.type","PeriodicExecutionContext");
      prop.setProperty("exec_cxt.periodic.rate","1000");
      rto->setProperties(prop);
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->initialize());

      RTC::ExecutionContext_ptr ec;
      ec = rto->get_context(0);
      CPPUNIT_ASSERT_EQUAL(true, rto->is_alive(ec));
			
      // Alive���֤�initialize()�᥽�åɸƽФ���Ԥä���硢�����ư��뤫��
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->initialize());
      rto->exit();
      delete rto;
    }
		
    /*!
     * @brief finalize()�᥽�åɤΥƥ���
     * 
     * - finalize()�ƽФˤ�ꡢon_finalize()������Хå����ƤӽФ���뤫��
     */
    void test_finalize_invoking_on_finalize()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // initialize()�᥽�åɸƽФ���Ԥ���Alive���֤����ܤ�����
      coil::Properties prop;
      prop.setProperty("exec_cxt.periodic.type","PeriodicExecutionContext");
      prop.setProperty("exec_cxt.periodic.rate","1000");
      rto->setProperties(prop);
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->initialize());
      RTC::ExecutionContext_ptr ec;
      ec = rto->get_context(0);
      CPPUNIT_ASSERT_EQUAL(true, rto->is_alive(ec));
			
      // finalize()�ƽФ��ˤ�ꡢon_finalize()������Хå����ƤӽФ���뤫��
      CPPUNIT_ASSERT_EQUAL(0, rto->countLog("on_finalize"));
			
      CPPUNIT_ASSERT_EQUAL(true, rto->is_alive(ec));
      // exit()�ƤӽФ��ǡ�finalize()��ͭ���Ȥʤ�¹Ԥ����
      rto->exit();
      CPPUNIT_ASSERT_EQUAL(1, rto->countLog("on_finalize"));
      delete rto;
    }
		
    /*!
     * @brief finalize()�᥽�åɤΥƥ���
     * 
     * - ExecutionContext����Ͽ���줿���֤�finalize()��ƤӽФ�����硢�տޤɤ���Υ��顼���֤�����
     */
    void test_finalize_participating_in_execution_context()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // initialize()�᥽�åɸƽФ���Ԥ���Alive���֤����ܤ�����
      coil::Properties prop;
      prop.setProperty("exec_cxt.periodic.type","PeriodicExecutionContext");
      prop.setProperty("exec_cxt.periodic.rate","1000");
      rto->setProperties(prop);
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->initialize());

      RTC::ExecutionContext_ptr ec;
      ec = rto->get_context(0);
      CPPUNIT_ASSERT_EQUAL(true, rto->is_alive(ec));
			
      // ExecutionContext����Ͽ���Ƥ���
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ExecutionContext����Ͽ���줿���֤�finalize()��ƤӽФ�����硢�տޤɤ���Υ��顼���֤�����
      CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, rto->finalize());

      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->remove_component(rto->_this()));
      rto->exit();
      delete rto;
    }
		
    /*!
     * @brief finalize()�᥽�åɤΥƥ���
     * 
     * - Created���֤�finalize()��ƽФ�����硢�տޤɤ���Υ��顼���֤뤫��
     */
    void test_finalize_in_Created()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // Created���֤�finalize()��ƽФ�����硢�տޤɤ���Υ��顼���֤뤫��
      CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, rto->finalize());
      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief is_alive()�᥽�åɤΥƥ���
     */
    void test_is_alive()
    {
      // test_initialize_in_Alive()�ˤƥƥ��Ȥ��ͤƤ���
    }
		
    /*!
     * @brief exit()�᥽�åɤΥƥ���
     * 
     * - exit()�ƽФ��ˤ�ꡢ��������ݡ��ͥ�Ȥ�finalize()����뤫��
     * - exit()�ƽФ��ˤ�ꡢ��������ݡ��ͥ�Ȥ������֤����ܤ��뤫��
     */
    void test_exit()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
      rto->setObjRef(rto->_this());
			
      // initialize()�᥽�åɸƽФ���Ԥ���Alive���֤����ܤ�����
      coil::Properties prop;
      prop.setProperty("exec_cxt.periodic.type","PeriodicExecutionContext");
      prop.setProperty("exec_cxt.periodic.rate","1000");
      rto->setProperties(prop);
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->initialize());

      RTC::ExecutionContext_ptr ec;
      ec = rto->get_context(0);
      CPPUNIT_ASSERT_EQUAL(true, rto->is_alive(ec));
			
      // ����ݡ��ͥ�Ȥ�ExecutionContext����Ͽ���ƥ����ƥ��ֲ�����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->activate_component(rto->_this()));
      //Call start() for the state machine drive. 
      ec->start();
      coil::sleep(1);
			
      // exit()�ƽФ��ˤ�ꡢ��������ݡ��ͥ�Ȥ�finalize()����뤫��
      // exit()�ƽФ��ˤ�ꡢ��������ݡ��ͥ�Ȥ������֤����ܤ��뤫��
      CPPUNIT_ASSERT_EQUAL(0, rto->countLog("on_finalize"));
      CPPUNIT_ASSERT_EQUAL(RTC::ACTIVE_STATE, ec->get_component_state(rto->_this()));
      ec->stop();
      coil::sleep(1);
      //Call remove_component(),to cancel the registered component.
      ec->remove_component(rto->_this());
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->exit());
      CPPUNIT_ASSERT_EQUAL(1, rto->countLog("on_finalize"));
      CPPUNIT_ASSERT_EQUAL(true, rto->is_alive(ec));

      delete rto;
    }

    /*!
     * @brief exit()�᥽�åɤΥƥ���
     * 
     * - Create���֤�exit()��ƽФ�����硢�տޤɤ���Υ��顼���֤�����
     */
    void test_exit_in_Created()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
      rto->setObjRef(rto->_this());
			
      // Create���֤�exit()��ƽФ�����硢�տޤɤ���Υ��顼���֤�����
      CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, rto->exit());

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief detach_executioncontext()�᥽�åɤΥƥ���
     * 
     * - attach�Ѥߤ�RTC�������detach�Ǥ��뤫��
     */
    void test_detach_executioncontext()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // ExecutionContext��attach���Ƥ���
      RTC::UniqueId id = rto->attach_context(ec->_this());
      CPPUNIT_ASSERT(RTC::UniqueId(-1) != id);
			
      // �����detach�Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->detach_context(id));
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief detach_executioncontext()�᥽�åɤΥƥ���
     * 
     * - ¸�ߤ��ʤ�ID��RTC��detach���ߤ���硢�տޤɤ���Υ��顼���֤�����
     */
    void test_detach_executioncontext_with_illegal_id()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // ¸�ߤ��ʤ�ID��RTC��detach���ߤ���硢�տޤɤ���Υ��顼���֤�����
      CPPUNIT_ASSERT_EQUAL(RTC::BAD_PARAMETER,
			   rto->detach_context(RTC::UniqueId(1)));
      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief get_context()�᥽�åɤΥƥ���
     * 
     * - ���ꤷ��ID��ExecutionContext�������������Ǥ��뤫��
     */
    void test_get_context()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec1
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      RTC::PeriodicExecutionContext* ec2
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // ExecutionContext��attach���Ƥ���
      RTC::UniqueId id1 = rto->attach_context(ec1->_this());
      CPPUNIT_ASSERT(RTC::UniqueId(-1) != id1);
      RTC::UniqueId id2 = rto->attach_context(ec2->_this());
      CPPUNIT_ASSERT(RTC::UniqueId(-1) != id2);
      CPPUNIT_ASSERT(id1 != id2);
			
      // ���ꤷ��ID��ExecutionContext�������������Ǥ��뤫��
      RTC::ExecutionContext_ptr ecPtr1 = rto->get_context(id1);
      CPPUNIT_ASSERT(ecPtr1->_is_equivalent(ec1->_this()));
      RTC::ExecutionContext_ptr ecPtr2 = rto->get_context(id2);
      CPPUNIT_ASSERT(ecPtr2->_is_equivalent(ec2->_this()));

      rto->detach_context(id2);
      rto->detach_context(id1);
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec2));
      delete ec2;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec1));
      delete ec1;

      rto->shutdown();
      delete rto;

    }
		
    /*!
     * @brief get_contexts()�᥽�åɤΥƥ���
     * 
     * - attach����Ƥ���ExecutionContext�򤹤٤������������Ǥ��뤫��
     */
    void test_get_contexts()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec1
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      RTC::PeriodicExecutionContext* ec2
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically

      // ExecutionContext��attach���Ƥ���
      RTC::UniqueId id1 = rto->attach_context(ec1->_this());
      CPPUNIT_ASSERT(RTC::UniqueId(-1) != id1);
      RTC::UniqueId id2 = rto->attach_context(ec2->_this());
      CPPUNIT_ASSERT(RTC::UniqueId(-1) != id2);
			
      // attach����Ƥ���ExecutionContext�򤹤٤������������Ǥ��뤫��
      RTC::ExecutionContextList* ecList = rto->get_participating_contexts();
      CPPUNIT_ASSERT(ecList != NULL);
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2), ecList->length());
      CPPUNIT_ASSERT(! (*ecList)[0]->_is_equivalent((*ecList)[1]));
      CPPUNIT_ASSERT((*ecList)[0]->_is_equivalent(ec1->_this())
		     || (*ecList)[0]->_is_equivalent(ec2->_this()));
      CPPUNIT_ASSERT((*ecList)[1]->_is_equivalent(ec1->_this())
		     || (*ecList)[1]->_is_equivalent(ec2->_this()));


      rto->detach_context(id2);
      rto->detach_context(id1);

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec2));
      delete ec2;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec1));
      delete ec1;

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief get_component_profile()�᥽�åɤΥƥ���
     * 
     * - ComponentProfile�������������Ǥ��뤫��
     */
    void test_get_component_profile()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // ComponentProfile�Ȥ��Ƽ��������٤�����򤢤餫�������ꤷ�Ƥ���
      coil::Properties prop;
      prop.setProperty("instance_name", "INSTANCE_NAME");
      prop.setProperty("type_name", "TYPE_NAME");
      prop.setProperty("description", "DESCRIPTION");
      prop.setProperty("version", "VERSION");
      prop.setProperty("vendor", "VENDOR");
      prop.setProperty("category", "CATEGORY");
      rto->setProperties(prop);
			
      // ComponentProfile�������������Ǥ��뤫��
      RTC::ComponentProfile* compProf = rto->get_component_profile();
      CPPUNIT_ASSERT(compProf != NULL);
			
      CPPUNIT_ASSERT_EQUAL(std::string("INSTANCE_NAME"),
			   std::string(compProf->instance_name));
      CPPUNIT_ASSERT_EQUAL(std::string("TYPE_NAME"),
			   std::string(compProf->type_name));
      CPPUNIT_ASSERT_EQUAL(std::string("DESCRIPTION"),
			   std::string(compProf->description));
      CPPUNIT_ASSERT_EQUAL(std::string("VERSION"),
			   std::string(compProf->version));
      CPPUNIT_ASSERT_EQUAL(std::string("VENDOR"),
			   std::string(compProf->vendor));
      CPPUNIT_ASSERT_EQUAL(std::string("CATEGORY"),
			   std::string(compProf->category));
      rto->shutdown();
      delete rto;
      
    }
		
    /*!
     * @brief add[In/Out]Port(),addPort()�᥽�åɤΥƥ���
     * 
     * - Port����������Ͽ�Ǥ��뤫��
     * - ������Ͽ�ѤߤΥݡ��Ȥ�Ʊ���ݡ���̾��Port����Ͽ���褦�Ȥ������˼��Ԥ��뤫��
     * - ��Ͽ�Ѥߤ�Port������������Ǥ��뤫��
     */
    void test_add_removePort()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically

      PortMock* port0 = new PortMock();
      port0->setName("port0");
      // Port����������Ͽ�Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(true, rto->addPort(*port0));
      // ������Ͽ�ѤߤΥݡ��Ȥ�Ʊ���ݡ���̾��Port����Ͽ���褦�Ȥ������˼��Ԥ��뤫��
      // PortBase::updateConnectors()�⡢Guard guard(m_profile_mutex);�ǥ�å����졢
      // ��������äƤ��ʤ���(�ǥåɥ�å�???)
      // CPPUNIT_ASSERT_EQUAL(false, rto->addPort(*port0));

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      CPPUNIT_ASSERT_EQUAL(true, rto->addPort(*port1));
			
      // ��Ͽ����Port���Ȥ򤹤٤������������Ǥ��뤫��
      RTC::PortServiceList* portList = rto->get_ports();
      CPPUNIT_ASSERT(portList != NULL);
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2), portList->length());

      // ��Ͽ�Ѥߤ�Port������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(true, rto->removePort(*port1));
      CPPUNIT_ASSERT_EQUAL(true, rto->removePort(*port0));

      InPortMock*  inport0  = new InPortMock("in","TimedLong");
      OutPortMock* outport0 = new OutPortMock("out","TimedLong");
      // InPort, OutPort����������Ͽ�Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(true, rto->addInPort("in",*inport0));
      CPPUNIT_ASSERT_EQUAL(true, rto->addOutPort("out", *outport0));
      // ������Ͽ�ѤߤΥݡ��Ȥ�Ʊ���ݡ���̾��Port����Ͽ���褦�Ȥ������˼��Ԥ��뤫��
      // PortBase::updateConnectors()�⡢Guard guard(m_profile_mutex);�ǥ�å����졢
      // ��������äƤ��ʤ���(�ǥåɥ�å�???)
      // CPPUNIT_ASSERT_EQUAL(false, rto->addInPort("in",*inport0));
      // CPPUNIT_ASSERT_EQUAL(false, rto->addOutPort("out", *outport0));

      // ��Ͽ����Port���Ȥ򤹤٤������������Ǥ��뤫��
      portList = rto->get_ports();
      CPPUNIT_ASSERT(portList != NULL);
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2), portList->length());

      // ��Ͽ�Ѥߤ�Port������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(true, rto->removeInPort(*inport0));
      CPPUNIT_ASSERT_EQUAL(true, rto->removeOutPort(*outport0));

      portList = rto->get_ports();
      CPPUNIT_ASSERT(portList != NULL);
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(0), portList->length());

      delete outport0;
      delete inport0;
      delete port1;
      delete port0;

      rto->shutdown();
      delete rto;

    }

    /*!
     * @brief readAll(),setReadAll()�᥽�åɤΥƥ���
     * 
     * - readAll()�����Ƥ�InPort��read()�������뤵��뤫��
     * - setReadAll()�����Ƥ�InPort��read()�������뤵��뤫��
     * - setReadAll()����������ǽ���Ƥ��뤫��
     */
    void test_readAll()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically

      InPortMock*  inport0  = new InPortMock("in","TimedLong");
      InPortMock*  inport1  = new InPortMock("in2","TimedLong");
      OutPortMock* outport0 = new OutPortMock("out","TimedLong");

      rto->addInPort("in",*inport0);
      rto->addInPort("in2",*inport1);
      rto->addOutPort("out", *outport0);

      // readAll()�����Ƥ�InPort��read()�������뤵��뤫��
      CPPUNIT_ASSERT_EQUAL(true, rto->readAll());
      CPPUNIT_ASSERT_EQUAL(1, inport0->get_counter());
      CPPUNIT_ASSERT_EQUAL(1, inport1->get_counter());

      // setReadAll()�����Ƥ�InPort��read()�������뤵��뤫��
      rto->setReadAll();
      rto->on_execute(0);
      CPPUNIT_ASSERT_EQUAL(2, inport0->get_counter());
      CPPUNIT_ASSERT_EQUAL(2, inport1->get_counter());

      // setReadAll(),readAll()����������ǽ���Ƥ��뤫��
      inport0->set_return(false);
      rto->setReadAll(true,false);
      CPPUNIT_ASSERT_EQUAL(false, rto->readAll());
      CPPUNIT_ASSERT_EQUAL(3, inport0->get_counter());
      // Because setReadAll(true,false) was called,
      // inport1.read() was not called.
      // inport0.read() return false.
      CPPUNIT_ASSERT_EQUAL(2, inport1->get_counter());

      rto->setReadAll(true,true);
      CPPUNIT_ASSERT_EQUAL(false, rto->readAll());
      CPPUNIT_ASSERT_EQUAL(4, inport0->get_counter());
      // Because setReadAll(true,true) was called,
      // inport0.read() return false,
      // but inport1.read() was called.
      CPPUNIT_ASSERT_EQUAL(3, inport1->get_counter());

      rto->setReadAll(false,true);
      rto->on_execute(0);
      // Because setReadAll(false,true) was called,
      // inport0.read() and inport1.read() was not called.
      CPPUNIT_ASSERT_EQUAL(4, inport0->get_counter());
      CPPUNIT_ASSERT_EQUAL(3, inport1->get_counter());
      
      rto->setReadAll(false,false);
      rto->on_execute(0);
      // Because setReadAll(false,true) was called,
      // inport0.read() and inport1.read() was not called.
      CPPUNIT_ASSERT_EQUAL(4, inport0->get_counter());
      CPPUNIT_ASSERT_EQUAL(3, inport1->get_counter());
      
      rto->removeInPort(*inport0);
      rto->removeInPort(*inport1);
      rto->removeOutPort(*outport0);
      
      delete outport0;
      delete inport0;
      delete inport1;

      rto->shutdown();
      delete rto;
    }


    /*!
     * @brief writeAll(),setWriteAll()�᥽�åɤΥƥ���
     * 
     * - setWriteAll()�����Ƥ�OutPort��write()�������뤵��뤫��
     * - writeAll()�����Ƥ�OutPort��write()�������뤵��뤫��
     * - setWriteAll()����������ǽ���Ƥ��뤫��
     */
    void test_writeAll()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically

      OutPortMock*  outport0  = new OutPortMock("out","TimedLong");
      OutPortMock*  outport1  = new OutPortMock("out2","TimedLong");
      InPortMock*  inport0 = new InPortMock("in","TimedLong");

      rto->addOutPort("out",*outport0);
      rto->addOutPort("out2",*outport1);
      rto->addInPort("in", *inport0);

      // writeAll()�����Ƥ�OutPort��write()�������뤵��뤫��
      CPPUNIT_ASSERT_EQUAL(true, rto->writeAll());
      CPPUNIT_ASSERT_EQUAL(1, outport0->get_counter());
      CPPUNIT_ASSERT_EQUAL(1, outport1->get_counter());

      // setWriteAll()�����Ƥ�OutPort��write()�������뤵��뤫��
      rto->setWriteAll();
      rto->on_execute(0);
      CPPUNIT_ASSERT_EQUAL(2, outport0->get_counter());
      CPPUNIT_ASSERT_EQUAL(2, outport1->get_counter());

      // setWriteAll(),writeAll()����������ǽ���Ƥ��뤫��
      outport0->set_return(false);
      rto->setWriteAll(true,false);
      CPPUNIT_ASSERT_EQUAL(false, rto->writeAll());
      CPPUNIT_ASSERT_EQUAL(3, outport0->get_counter());
      // Because setWriteAll(true,false) was called,
      // outport1.write() was not called.
      // outport0.write() return false.
      CPPUNIT_ASSERT_EQUAL(2, outport1->get_counter());

      rto->setWriteAll(true,true);
      CPPUNIT_ASSERT_EQUAL(false, rto->writeAll());
      CPPUNIT_ASSERT_EQUAL(4, outport0->get_counter());
      // Because setWriteAll(true,true) was called,
      // outport0.write() return false,
      // but outport1.write() was called.
      CPPUNIT_ASSERT_EQUAL(3, outport1->get_counter());

      rto->setWriteAll(false,true);
      rto->on_execute(0);
      // Because setWriteAll(false,true) was called,
      // outport0.write() and outport1.write() was not called.
      CPPUNIT_ASSERT_EQUAL(4, outport0->get_counter());
      CPPUNIT_ASSERT_EQUAL(3, outport1->get_counter());
      
      rto->setWriteAll(false,false);
      rto->on_execute(0);
      // Because setWriteAll(false,true) was called,
      // outport0.write() and outport1.write() was not called.
      CPPUNIT_ASSERT_EQUAL(4, outport0->get_counter());
      CPPUNIT_ASSERT_EQUAL(3, outport1->get_counter());
      
      rto->removeOutPort(*outport0);
      rto->removeOutPort(*outport1);
      rto->removeInPort(*inport0);
      
      delete outport0;
      delete outport1;
      delete inport0;

      rto->shutdown();
      delete rto;
    }


    /*!
     * @brief get_ports()�᥽�åɤΥƥ���
     * 
     * - ��Ͽ����Port���Ȥ򤹤٤������������Ǥ��뤫��
     */
    void test_get_ports()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically

      // Port����Ͽ���Ƥ���
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      rto->addPort(*port0);

      PortMock* port1 = new PortMock();
      port1->setName("port1");
      rto->addPort(*port1);
			
      // ��Ͽ����Port���Ȥ򤹤٤������������Ǥ��뤫��
      RTC::PortServiceList* portList = rto->get_ports();
      CPPUNIT_ASSERT(portList != NULL);
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2), portList->length());
      CPPUNIT_ASSERT(CORBA::Long(-1)
		     != CORBA_SeqUtil::find(*portList, PortFinder(port0->_this())));
      CPPUNIT_ASSERT(CORBA::Long(-1)
		     != CORBA_SeqUtil::find(*portList, PortFinder(port1->_this())));

      CPPUNIT_ASSERT_EQUAL(true, rto->removePort(*port1));
      CPPUNIT_ASSERT_EQUAL(true, rto->removePort(*port0));

      delete port1;
      delete port0;

      rto->shutdown();
      delete rto;

    }
		
    /*!
     * @brief get_execution_context_services()�᥽�åɤΥƥ���
     * 
     * - ExecutionContextService�򤹤٤������������Ǥ��뤫��
     */
/*
    void test_get_execution_context_services()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec1
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      RTC::PeriodicExecutionContext* ec2
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically

      // ExecutionContext��attach���Ƥ���
      RTC::UniqueId id1 = rto->attach_context(ec1->_this());
      CPPUNIT_ASSERT(RTC::UniqueId(-1) != id1);
      RTC::UniqueId id2 = rto->attach_context(ec2->_this());
      CPPUNIT_ASSERT(RTC::UniqueId(-1) != id2);

      // ExecutionContextService�򤹤٤������������Ǥ��뤫��
      // (��) RTC::PeriodicExecutionContext��ExecutionContextService�Υ��֥��饹�ˤʤäƤ��롣
      RTC::ExecutionContextServiceList* ecSvcList
//	= rto->get_execution_context_services();
	= rto->get_owned_contexts();
      CPPUNIT_ASSERT(ecSvcList != NULL);
      CPPUNIT_ASSERT(CORBA::Long(-1)
		     != CORBA_SeqUtil::find(*ecSvcList, ExecutionContextServiceFinder(ec1->_this())));
      CPPUNIT_ASSERT(CORBA::Long(-1)
		     != CORBA_SeqUtil::find(*ecSvcList, ExecutionContextServiceFinder(ec2->_this())));
    }
*/		
    void test_get_owned_organizations()
    {
      // �ƥ����оݤ�̤�����ˤĤ����ƥ���̤����
    }
		
    /*!
     * @brief get_sdo_id()�᥽�åɤΥƥ���
     * 
     * - SDO ID������Ǥ��뤫��
     * - �������줿SDO ID�ϰ�դ���
     */
    void test_get_sdo_id()
    {
      RTObjectMock* rto1 = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
      rto1->setInstanceName("INSTANCE_NAME 1");
      std::string str1(rto1->getInstanceName());
      CPPUNIT_ASSERT("INSTANCE_NAME 1" == str1);
      RTObjectMock* rto2 = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
      rto2->setInstanceName("INSTANCE_NAME 2");
      std::string str2(rto2->getInstanceName());
      CPPUNIT_ASSERT("INSTANCE_NAME 2" == str2);

      // SDO ID������Ǥ��뤫��
      char* id1 = rto1->get_sdo_id();
      CPPUNIT_ASSERT(id1 != NULL);
      char* id2 = rto2->get_sdo_id();
      CPPUNIT_ASSERT(id2 != NULL);
			
      // �������줿SDO ID�ϰ�դ���
      // (��) instance_name��SDO ID�Ȥ��Ƥ��Τޤ޻��Ѥ���뤳�Ȥ���ա�
      //      �Ĥޤꡢ�����塢SDO ID�ΰ������instance_name�ΰ�����˴�Ť��Ƥ��롣
      //      ���;塢instance_name�ϰ�դǤʤ���Фʤ�ʤ��Τǡ�������Ӥ��Ƥ��롣
      CPPUNIT_ASSERT(id1 != id2);

      rto2->shutdown();
      delete rto2;
      rto1->shutdown();
      delete rto1;
    }
		
    /*!
     * @brief get_sdo_type()�᥽�åɤΥƥ���
     * 
     * - SDO�����פ�����Ǥ��뤫��
     */
    void test_get_sdo_type()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
				
      // �� �����塢type_name��SDO�����פȤ��ƻ��Ѥ���Ƥ��뤿�ᡢ�����ǽ������ꤷ�Ƥ���
      coil::Properties prop;
      prop.setProperty("type_name", "TYPE_NAME");
      rto->setProperties(prop);
			
      // SDO�����פ�����Ǥ��뤫��
      char* sdoType = rto->get_sdo_type();
      CPPUNIT_ASSERT(sdoType != NULL);

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief get_device_profile()�᥽�åɤΥƥ���
     * 
     * - DeviceProfile�������������Ǥ��뤫��
     */
    void test_get_device_profile()
    {
      // test_get_configuration_and_set_device_profile_and_get_device_profile�Ƿ�ͤ�
    }
		
    /*!
     * @brief get_service_profile()�᥽�åɤΥƥ���
     * 
     * - ���ꤷ��ID��ServiceProfile�������������Ǥ��뤫��
     */
    void test_get_service_profile()
    {
      // test_get_configuration_and_set_service_profile_and_get_service_profile�Ƿ�ͤ�
    }
		
    /*!
     * @brief get_service_profile()�᥽�åɤΥƥ���
     * 
     * - ������NULL����ꤷ����硢�տޤɤ�����㳰����������뤫��
     * - ������¸�ߤ��ʤ�ID����ꤷ����硢�տޤɤ�����㳰����������뤫��
     */
    void test_get_service_profile_with_illegal_arguments()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // ������NULL����ꤷ����硢�տޤɤ�����㳰����������뤫��
      try
	{
	  rto->get_service_profile(NULL);
	  CPPUNIT_FAIL("Exception not thrown.");
	}
      catch (SDOPackage::InvalidParameter expected)
	{
	  // �տޤɤ�����㳰�򥭥�å�����
	}
      catch (...)
	{
	  // �տޤ��ʤ��㳰�򥭥�å�����
	  CPPUNIT_FAIL("Unexpected exception caught.");
	}
			
      // ������¸�ߤ��ʤ�ID����ꤷ����硢�տޤɤ�����㳰����������뤫��
      try
	{
	  rto->get_service_profile("INEXIST ID");
	  CPPUNIT_FAIL("Exception not thrown.");
	}
      catch (SDOPackage::InvalidParameter expected)
	{
	  // �տޤɤ�����㳰�򥭥�å�����
	}
      catch (...)
	{
	  // �տޤ��ʤ��㳰�򥭥�å�����
	  CPPUNIT_FAIL("Unexpected exception caught.");
	}
      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief get_sdo_service()�᥽�åɤΥƥ���
     * 
     * - ���ꤷ��ID��SDOService�������������Ǥ��뤫��
     */
    void test_get_sdo_service()
    {
      // test_get_configuration_and_set_service_profile_and_get_sdo_service�Ƿ�ͤ�
    }
		
    void test_get_sdo_service_with_illegal_arguments()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // ������NULL����ꤷ����硢�տޤɤ�����㳰����������뤫��
      try
	{
	  rto->get_sdo_service(NULL);
	  CPPUNIT_FAIL("Exception not thrown.");
	}
      catch (SDOPackage::InvalidParameter expected)
	{
	  // �տޤɤ�����㳰�򥭥�å�����
	}
      catch (...)
	{
	  // �տޤ��ʤ��㳰�򥭥�å�����
	  CPPUNIT_FAIL("Unexpected exception caught.");
	}
			
      // �����ˡ�¸�ߤ��ʤ�ID����ꤷ����硢�տޤɤ�����㳰����������뤫��
      try
	{
	  rto->get_sdo_service("INEXIST ID");
	  CPPUNIT_FAIL("Exception not thrown.");
	}
      catch (SDOPackage::InvalidParameter expected)
	{
	  // �տޤɤ�����㳰�򥭥�å�����
	}
      catch (...)
	{
	  // �տޤ��ʤ��㳰�򥭥�å�����
	  CPPUNIT_FAIL("Unexpected exception caught.");
	}

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief get_configuration()�᥽�åɤΥƥ���
     * 
     * - Configuration::set_device_profile()���̤��ơ�DeviceProfile������������Ǥ��뤫��
     * - ���ꤵ�줿DeviceProfile��get_device_profile()�������������Ǥ��뤫��
     */
    void test_get_configuration_and_set_device_profile_and_get_device_profile()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // DeviceProfile��������Ƥ���
      SDOPackage::DeviceProfile devProf;
      devProf.device_type = "DEVICE_TYPE";
      devProf.manufacturer = "MANUFACTURER";
      devProf.model = "MODEL";
      devProf.version = "VERSION";
      devProf.properties.length(1);
      devProf.properties[0].name = "PROPERTIES NAME";
      devProf.properties[0].value <<= "PROPERTIES VALUE";
			
      // Configuration���󥿥ե��������������DeviceProfile�����ꤹ��
      SDOPackage::Configuration_ptr cfg = rto->get_configuration();
      cfg->set_device_profile(devProf);
      // DeviceProfile��������ơ����������ꤵ�줿���Ȥ��ǧ����
      SDOPackage::DeviceProfile* devProfRet = rto->get_device_profile();
      CPPUNIT_ASSERT_EQUAL(std::string("DEVICE_TYPE"),
			   std::string(devProfRet->device_type));
      CPPUNIT_ASSERT_EQUAL(std::string("MANUFACTURER"),
			   std::string(devProfRet->manufacturer));
      CPPUNIT_ASSERT_EQUAL(std::string("MODEL"),
			   std::string(devProfRet->model));
      CPPUNIT_ASSERT_EQUAL(std::string("VERSION"),
			   std::string(devProfRet->version));
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(1), devProfRet->properties.length());
      CPPUNIT_ASSERT_EQUAL(std::string("PROPERTIES NAME"),
			   std::string(devProfRet->properties[0].name));
      {
	const char* value; devProfRet->properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("PROPERTIES VALUE"), std::string(value));
      }

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief get_configuration()�᥽�åɤ�get_serivce_profile()�᥽�åɤΥƥ���
     * 
     * - Configuration::set_service_profile()���̤��ơ�ServiceProfile������������Ǥ��뤫��
     * - ���ꤵ�줿ServiceProfile��get_service_profile()�������������Ǥ��뤫��
     */
    void test_get_configuration_and_set_service_profile_and_get_service_profile()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically

      // SDOService���������
      SDOServiceMock* sdoSvc1 = new SDOServiceMock();
      SDOServiceMock* sdoSvc2 = new SDOServiceMock();
			
      // ServiceProfile��������Ƥ���
      SDOPackage::ServiceProfile svcProf1;
      svcProf1.id = "ID 1";
      svcProf1.interface_type = "INTERFACE_TYPE 1";
      svcProf1.properties.length(1);
      svcProf1.properties[0].name = "PROPERTIES NAME 1";
      svcProf1.properties[0].value <<= "3.14159";
      svcProf1.service = sdoSvc1->_this();

      SDOPackage::ServiceProfile svcProf2;
      svcProf2.id = "ID 2";
      svcProf2.interface_type = "INTERFACE_TYPE 2";
      svcProf2.properties.length(1);
      svcProf2.properties[0].name = "PROPERTIES NAME 2";
      svcProf2.properties[0].value <<= "2.71828";
      svcProf2.service = sdoSvc2->_this();
			
      // Configuration���󥿥ե��������������ServiceProfile�����ꤹ��
      SDOPackage::Configuration_ptr cfg = rto->get_configuration();
      CPPUNIT_ASSERT(! CORBA::is_nil(cfg));
      cfg->add_service_profile(svcProf1);
      cfg->add_service_profile(svcProf2);
			
      // get_service_profile()���Ѥ���ServiceProfile��������ơ����������ꤵ�줿���Ȥ��ǧ����
      SDOPackage::ServiceProfile* svcProfRet1 = rto->get_service_profile("ID 1");
      CPPUNIT_ASSERT(svcProfRet1 != NULL);
      CPPUNIT_ASSERT_EQUAL(std::string("ID 1"),	std::string(svcProfRet1->id));
      CPPUNIT_ASSERT_EQUAL(std::string("INTERFACE_TYPE 1"),
			   std::string(svcProfRet1->interface_type));
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(1), svcProfRet1->properties.length());
      CPPUNIT_ASSERT_EQUAL(std::string("PROPERTIES NAME 1"),
			   std::string(svcProfRet1->properties[0].name));
      {
	const char* value; svcProfRet1->properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("3.14159"), std::string(value));
      }
			
      SDOPackage::ServiceProfile* svcProfRet2 = rto->get_service_profile("ID 2");
      CPPUNIT_ASSERT(svcProfRet2 != NULL);
      CPPUNIT_ASSERT_EQUAL(std::string("ID 2"), std::string(svcProfRet2->id));
      CPPUNIT_ASSERT_EQUAL(std::string("INTERFACE_TYPE 2"),
			   std::string(svcProfRet2->interface_type));
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(1), svcProfRet2->properties.length());
      CPPUNIT_ASSERT_EQUAL(std::string("PROPERTIES NAME 2"),
			   std::string(svcProfRet2->properties[0].name));
      {
	const char* value; svcProfRet2->properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("2.71828"), std::string(value));
      }

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(sdoSvc2));
      delete sdoSvc2;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(sdoSvc1));
      delete sdoSvc1;

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief get_configuration()�᥽�åɤ�get_service_profiles()�᥽�åɤΥƥ���
     * 
     * - ���ꤵ�줿ServiceProfile��get_service_profiles()�������������Ǥ��뤫��
     */
    void test_get_configuration_and_set_service_profile_and_get_service_profiles()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically

      // SDOService���������
      SDOServiceMock* sdoSvc1 = new SDOServiceMock();
      SDOServiceMock* sdoSvc2 = new SDOServiceMock();
			
      // ServiceProfile��������Ƥ���
      SDOPackage::ServiceProfile svcProf1;
      svcProf1.id = "ID 1";
      svcProf1.interface_type = "INTERFACE_TYPE 1";
      svcProf1.properties.length(1);
      svcProf1.properties[0].name = "PROPERTIES NAME 1";
      svcProf1.properties[0].value <<= "3.14159";
      svcProf1.service = sdoSvc1->_this();

      SDOPackage::ServiceProfile svcProf2;
      svcProf2.id = "ID 2";
      svcProf2.interface_type = "INTERFACE_TYPE 2";
      svcProf2.properties.length(1);
      svcProf2.properties[0].name = "PROPERTIES NAME 2";
      svcProf2.properties[0].value <<= "2.71828";
      svcProf2.service = sdoSvc2->_this();
			
      // Configuration���󥿥ե��������������ServiceProfile�����ꤹ��
      SDOPackage::Configuration_ptr cfg = rto->get_configuration();
      CPPUNIT_ASSERT(! CORBA::is_nil(cfg));
      cfg->add_service_profile(svcProf1);
      cfg->add_service_profile(svcProf2);
			
      // get_service_profiles()��Ȥä�ServiceProfile����������ơ����������ꤵ�줿���Ȥ��ǧ����
      SDOPackage::ServiceProfileList* svcProfList = rto->get_service_profiles();
      CPPUNIT_ASSERT(svcProfList != NULL);
			
      CORBA::Long svcProfIdx1 = CORBA_SeqUtil::find(
						    *svcProfList, ServiceProfileFinder("ID 1"));
      CPPUNIT_ASSERT(CORBA::Long(-1) != svcProfIdx1);
      CPPUNIT_ASSERT_EQUAL(std::string("ID 1"),
			   std::string((*svcProfList)[svcProfIdx1].id));
      CPPUNIT_ASSERT_EQUAL(std::string("INTERFACE_TYPE 1"),
			   std::string((*svcProfList)[svcProfIdx1].interface_type));
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(1),
			   (*svcProfList)[svcProfIdx1].properties.length());
      CPPUNIT_ASSERT_EQUAL(std::string("PROPERTIES NAME 1"),
			   std::string((*svcProfList)[svcProfIdx1].properties[0].name));
      {
	const char* value; (*svcProfList)[svcProfIdx1].properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("3.14159"), std::string(value));
      }
			
      CORBA::Long svcProfIdx2 = CORBA_SeqUtil::find(
						    *svcProfList, ServiceProfileFinder("ID 2"));
      CPPUNIT_ASSERT(CORBA::Long(-1) != svcProfIdx2);
      CPPUNIT_ASSERT_EQUAL(std::string("ID 2"),
			   std::string((*svcProfList)[svcProfIdx2].id));
      CPPUNIT_ASSERT_EQUAL(std::string("INTERFACE_TYPE 2"),
			   std::string((*svcProfList)[svcProfIdx2].interface_type));
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(1),
			   (*svcProfList)[svcProfIdx2].properties.length());
      CPPUNIT_ASSERT_EQUAL(std::string("PROPERTIES NAME 2"),
			   std::string((*svcProfList)[svcProfIdx2].properties[0].name));
      {
	const char* value; (*svcProfList)[svcProfIdx2].properties[0].value >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("2.71828"), std::string(value));
      }
      
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(sdoSvc2));
      delete sdoSvc2;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(sdoSvc1));
      delete sdoSvc1;

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief get_configuration()�᥽�åɤ�get_sdo_service()�᥽�åɤΥƥ���
     * 
     * - Configuration::set_service_profile()���̤��ơ�SDOService������������Ǥ��뤫��
     * - get_sdo_service()���Ѥ��ơ����ꤵ��Ƥ���SDPService�������������Ǥ��뤫��
     */
    void test_get_configuration_and_set_service_profile_and_get_sdo_service()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically

      // SDOService���������
      SDOServiceMock* sdoSvc1 = new SDOServiceMock();
      SDOServiceMock* sdoSvc2 = new SDOServiceMock();
			
      // ServiceProfile��������Ƥ���
      SDOPackage::ServiceProfile svcProf1;
      svcProf1.id = "ID 1";
      svcProf1.interface_type = "INTERFACE_TYPE 1";
      svcProf1.properties.length(1);
      svcProf1.properties[0].name = "PROPERTIES NAME 1";
      svcProf1.properties[0].value <<= "3.14159";
      svcProf1.service = sdoSvc1->_this();

      SDOPackage::ServiceProfile svcProf2;
      svcProf2.id = "ID 2";
      svcProf2.interface_type = "INTERFACE_TYPE 2";
      svcProf2.properties.length(1);
      svcProf2.properties[0].name = "PROPERTIES NAME 2";
      svcProf2.properties[0].value <<= "2.71828";
      svcProf2.service = sdoSvc2->_this();
			
      // Configuration���󥿥ե��������������ServiceProfile�����ꤹ��
      SDOPackage::Configuration_ptr cfg = rto->get_configuration();
      CPPUNIT_ASSERT(! CORBA::is_nil(cfg));
      cfg->add_service_profile(svcProf1);
      cfg->add_service_profile(svcProf2);
			
      // ���ꤷ��ID��SDOService�������������Ǥ��뤫��
      SDOPackage::SDOService_ptr sdoSvcRet1 = rto->get_sdo_service("ID 1");
      CPPUNIT_ASSERT(! CORBA::is_nil(sdoSvcRet1));
      CPPUNIT_ASSERT(sdoSvcRet1->_is_equivalent(sdoSvc1->_this()));

      SDOPackage::SDOService_ptr sdoSvcRet2 = rto->get_sdo_service("ID 2");
      CPPUNIT_ASSERT(! CORBA::is_nil(sdoSvcRet2));
      CPPUNIT_ASSERT(sdoSvcRet2->_is_equivalent(sdoSvc2->_this()));

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(sdoSvc2));
      delete sdoSvc2;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(sdoSvc1));
      delete sdoSvc1;

      rto->shutdown();
      delete rto;

    }
		
    /*!
     * @brief Configuration::remove_service_profile()�᥽�åɤΥƥ���
     * 
     * - ���ꤷ��ID��ServiceProfile������������Ǥ��뤫��
     */
    void test_get_configuration_and_remove_service_profile()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically

      // SDOService���������
      SDOServiceMock* sdoSvc1 = new SDOServiceMock();
      SDOServiceMock* sdoSvc2 = new SDOServiceMock();
			
      // ServiceProfile��������Ƥ���
      SDOPackage::ServiceProfile svcProf1;
      svcProf1.id = "ID 1";
      svcProf1.interface_type = "INTERFACE_TYPE 1";
      svcProf1.properties.length(1);
      svcProf1.properties[0].name = "PROPERTIES NAME 1";
      svcProf1.properties[0].value <<= "3.14159";
      svcProf1.service = sdoSvc1->_this();

      SDOPackage::ServiceProfile svcProf2;
      svcProf2.id = "ID 2";
      svcProf2.interface_type = "INTERFACE_TYPE 2";
      svcProf2.properties.length(1);
      svcProf2.properties[0].name = "PROPERTIES NAME 2";
      svcProf2.properties[0].value <<= "2.71828";
      svcProf2.service = sdoSvc2->_this();
			
      // Configuration���󥿥ե��������������ServiceProfile�����ꤹ��
      SDOPackage::Configuration_ptr cfg = rto->get_configuration();
      CPPUNIT_ASSERT(! CORBA::is_nil(cfg));
      cfg->add_service_profile(svcProf1);
      cfg->add_service_profile(svcProf2);
      CPPUNIT_ASSERT(rto->get_service_profile("ID 1") != NULL);
      CPPUNIT_ASSERT(rto->get_service_profile("ID 2") != NULL);
			
      // ���ꤷ��������������ServiceProfile��remove���ơ�������remove���줿���Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(true, cfg->remove_service_profile("ID 1"));
      try
	{
	  rto->get_service_profile("ID 1");
	  CPPUNIT_FAIL("Expected exception not thrown.");
	}
      catch (SDOPackage::InvalidParameter expected) {}
      CPPUNIT_ASSERT(rto->get_service_profile("ID 2") != NULL);

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(sdoSvc2));
      delete sdoSvc2;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(sdoSvc1));
      delete sdoSvc1;

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief get_configuration()�᥽�åɤ�get_organizations()�᥽�åɤΥƥ���
     * 
     * - Configuration::add_organization()��Organization���������ɲäǤ��뤫��
     * - get_organizations()�ǡ���Ͽ����Ƥ���Organization�������������Ǥ��뤫��
     */
    void test_get_configuration_and_add_organization_and_get_organizations()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // Organization���������
      OrganizationMock* org1 = new OrganizationMock("ORG 1");
      OrganizationMock* org2 = new OrganizationMock("ORG 2");

      // Configuration���󥿥ե��������������Organization���ɲä���
      SDOPackage::Configuration_ptr cfg = rto->get_configuration();
      CPPUNIT_ASSERT(! CORBA::is_nil(cfg));
      CPPUNIT_ASSERT_EQUAL(true, cfg->add_organization(org1->_this()));
      CPPUNIT_ASSERT_EQUAL(true, cfg->add_organization(org2->_this()));
			
      // get_organizations()���Ѥ���Organization���������������Ǥ��뤫��
      SDOPackage::OrganizationList* orgList = rto->get_organizations();
      CPPUNIT_ASSERT(orgList != NULL);
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2), orgList->length());
			
      CORBA::Long orgIdx1 = CORBA_SeqUtil::find(*orgList, OrganizationFinder("ORG 1"));
      CPPUNIT_ASSERT(CORBA::Long(-1) != orgIdx1);
      CPPUNIT_ASSERT_EQUAL(std::string("ORG 1"),
			   std::string((*orgList)[orgIdx1]->get_organization_id()));

      CORBA::Long orgIdx2 = CORBA_SeqUtil::find(*orgList, OrganizationFinder("ORG 2"));
      CPPUNIT_ASSERT(CORBA::Long(-1) != orgIdx2);
      CPPUNIT_ASSERT_EQUAL(std::string("ORG 2"),
			   std::string((*orgList)[orgIdx2]->get_organization_id()));

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(org2));
      delete org2;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(org1));
      delete org1;

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief Configuration::remove_organization()�᥽�åɤΥƥ���
     * 
     * - ���ꤷ��ID��Organization������������Ǥ��뤫��
     */
    void test_get_configuration_and_remove_organization()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // Organization���������
      OrganizationMock* org1 = new OrganizationMock("ORG 1");
      OrganizationMock* org2 = new OrganizationMock("ORG 2");

      // Configuration���󥿥ե��������������Organization���ɲä���
      SDOPackage::Configuration_ptr cfg = rto->get_configuration();
      CPPUNIT_ASSERT(! CORBA::is_nil(cfg));
      CPPUNIT_ASSERT_EQUAL(true, cfg->add_organization(org1->_this()));
      CPPUNIT_ASSERT_EQUAL(true, cfg->add_organization(org2->_this()));
			
      // �ɲä���Ƥ��뤳�Ȥ��ǧ���Ƥ���
      SDOPackage::OrganizationList* orgList = rto->get_organizations();
      CPPUNIT_ASSERT(orgList != NULL);
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2), orgList->length());
			
      // �ɲä���������������Organization��remove����������remove����Ƥ��뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(true, cfg->remove_organization("ORG 1"));
      orgList = rto->get_organizations();
      CPPUNIT_ASSERT(orgList != NULL);
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(1), orgList->length());

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(org2));
      delete org2;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(org1));
      delete org1;

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief get_monitoring()�᥽�åɤΥƥ���
     */
    void test_get_monitoring()
    {
      // �ƥ����оݤ�̤�����ˤĤ����ƥ��Ȥ�̤����
    }
		
    /*!
     * @brief get_status()�᥽�åɤΥƥ���
     * 
     * - ���ꤷ��̾�Τ�status�ͤ������������Ǥ��뤫��
     */
    void test_get_status()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // Mock�ε�ǽ���Ѥ���status�����ꤷ�Ƥ���
      CORBA::Any valueAny1; valueAny1 <<= CORBA::Float(3.14159);
      rto->set_status("STATUS 1", valueAny1);
			
      CORBA::Any valueAny2; valueAny2 <<= CORBA::Float(2.71828);
      rto->set_status("STATUS 2", valueAny2);
			
      // ���ꤷ��status�������������Ǥ��뤫��
      CORBA::Any* valueAnyRet1 = rto->get_status("STATUS 1");
      CPPUNIT_ASSERT(valueAnyRet1 != NULL);
      {
	CORBA::Float value; *valueAnyRet1 >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(3.14159), value);
      }
			
      CORBA::Any* valueAnyRet2 = rto->get_status("STATUS 2");
      CPPUNIT_ASSERT(valueAnyRet2 != NULL);
      {
	CORBA::Float value; *valueAnyRet2 >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(2.71828), value);
      }
      
      rto->shutdown();
      delete rto;

    }
		
    /*!
     * @brief get_status_list()�᥽�åɤΥƥ���
     * 
     * - ���ꤵ��Ƥ��뤹�٤Ƥ�status�������������Ǥ��뤫��
     */
    void test_get_status_list()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA); // will be deleted automatically
			
      // Mock�ε�ǽ���Ѥ���status�����ꤷ�Ƥ���
      CORBA::Any valueAny1; valueAny1 <<= CORBA::Float(3.14159);
      rto->set_status("STATUS 1", valueAny1);
			
      CORBA::Any valueAny2; valueAny2 <<= CORBA::Float(2.71828);
      rto->set_status("STATUS 2", valueAny2);
			
      // ���ꤷ��status�������������Ǥ��뤫��
      SDOPackage::NVList* statusList = rto->get_status_list();
      CPPUNIT_ASSERT(statusList != NULL);
      CPPUNIT_ASSERT_EQUAL(CORBA::ULong(2), statusList->length());
			
      const CORBA::Any& valueAnyRet1 = NVUtil::find(*statusList, "STATUS 1");
      {
	CORBA::Float value; valueAnyRet1 >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(3.14159), value);
      }

      const CORBA::Any& valueAnyRet2 = NVUtil::find(*statusList, "STATUS 2");
      {
	CORBA::Float value; valueAnyRet2 >>= value;
	CPPUNIT_ASSERT_EQUAL(CORBA::Float(2.71828), value);
      }

      rto->shutdown();
      delete rto;
    }
		
    /*!
     * @brief finalizeContexts()�᥽�åɤΥƥ���
     * 
     * - ������ƥ����Ȥ���Ͽ�����Ǥ��뤫��
     */
    void test_finalizeContexts()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA);
      coil::Properties prop;
      prop.setProperty("exec_cxt.periodic.type","PeriodicExecutionContext");
      prop.setProperty("exec_cxt.periodic.rate","1000");
      rto->setProperties(prop);
      // initialize()�ǡ�m_eclist����Ͽ����m_ecMine��start
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->initialize());
      CPPUNIT_ASSERT_EQUAL(1, rto->get_eclist());
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->initialize());
      CPPUNIT_ASSERT_EQUAL(2, rto->get_eclist());
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, rto->initialize());
      CPPUNIT_ASSERT_EQUAL(3, rto->get_eclist());

      RTC::ExecutionContext_ptr ec;
      ec = rto->get_context(0);
      CPPUNIT_ASSERT_EQUAL(true, rto->is_alive(ec));
      rto->finalizeContexts();

      // ������ƥ����Ȥ�������줿����
      CPPUNIT_ASSERT_EQUAL(0, rto->get_eclist());
      rto->exit();
      delete rto;
    }
		
    /*!
     * @brief bindContext()�᥽�åɤΥƥ���
     * 
     * - ExecutionContext������������Ǥ��뤫��
     */
    void test_bindContext()
    {
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA);
      coil::Properties prop;
      prop.setProperty("exec_cxt.periodic.type","PeriodicExecutionContext");
      prop.setProperty("exec_cxt.periodic.rate","1000");
      rto->setProperties(prop);

      RTC::ExecutionContext_ptr ec;

      // nil�����ꤷ����硢-1���֤�����
      ec = RTC::ExecutionContext::_nil();
      int id = (int)(rto->bindContext(ec));
      CPPUNIT_ASSERT_EQUAL(-1, id);

      // m_ecMine ̤��Ͽ�ξ�硢m_ecMine���ֹ���֤�����
      RTC::PeriodicExecutionContext* pec = new RTC::PeriodicExecutionContext();
      ec = pec->getObjRef();
      id = (int)(rto->bindContext(ec));

      // [0]����Ͽ����뤫��
      CPPUNIT_ASSERT_EQUAL(0, id);

      // ��������Ͽ����Ƥ��뤫��
      CPPUNIT_ASSERT(rto->chk_ecMine(id,ec));

      // m_ecMine ��Ͽ�Ѥߤ� nil �ξ�硢m_ecMine���ֹ���֤�����
      rto->ecMine[0] = RTC::ExecutionContextService::_nil();
      rto->set_ecMine();
      RTC::PeriodicExecutionContext* pec2 = new RTC::PeriodicExecutionContext();
      ec = pec2->getObjRef();
      id = (int)(rto->bindContext(ec));

      // [0]����Ͽ����뤫��
      CPPUNIT_ASSERT_EQUAL(0, id);

      // ��������Ͽ����Ƥ��뤫��
      CPPUNIT_ASSERT(rto->chk_ecMine(id,ec));

      rto->exit();

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pec));
      delete pec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(pec2));
      delete pec2;

      rto->shutdown();
      delete rto;

    }
		
  };
}; // namespace RTObject

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(RTObject::RTObjectTests);

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
#endif // RTObject_cpp
