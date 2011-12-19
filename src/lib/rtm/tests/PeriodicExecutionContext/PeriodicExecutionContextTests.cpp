// -*- C++ -*-
/*!
 * @file   PeriodicExecutionContextTests.cpp
 * @brief  PeriodicExecutionContext test class
 * @date   $Date: 2008/04/11 13:19:07 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: PeriodicExecutionContextTests.cpp 2015 2010-12-29 11:33:33Z n-ando $
 *
 */

/*
 * $Log: PeriodicExecutionContextTests.cpp,v $
 * Revision 1.3  2008/04/11 13:19:07  arafune
 * Added some new tests.
 *
 * Revision 1.2  2008/04/09 13:10:37  arafune
 * Added attach_executioncontext/detach_executioncontext method to the DFP class.
 *
 * Revision 1.1  2007/12/20 07:50:19  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/04/13 15:04:39  n-ando
 * Now RTC::OK becomes RTC::RTC_OK in RTC.idl.
 *
 * Revision 1.1  2007/01/21 13:07:20  n-ando
 * *** empty log message ***
 *
 *
 */

#ifndef PeriodicExecutionContext_cpp
#define PeriodicExecutionContext_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/RTCSkel.h>
#include <rtm/PeriodicExecutionContext.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/RTObject.h>

/*!
 * @class PeriodicExecutionContextTests class
 * @brief PeriodicExecutionContext test
 */
namespace PeriodicExecutionContext
{
  class LightweightRTObjectMock
    : public virtual POA_RTC::LightweightRTObject,
      public virtual PortableServer::RefCountServantBase
  {
  protected:
    typedef std::map<RTC::UniqueId, RTC::ExecutionContext_ptr> ExecContexts;
    CORBA::Long m_nextUniqueId;
    ExecContexts m_execContexts;
    std::vector<std::string> m_log;
    bool m_alive;
    bool m_error;
	
  public:
    LightweightRTObjectMock()
      : m_alive(true), m_error(false)
    {
    }
		
    // RTC::_impl_ComponentAction
    virtual RTC::UniqueId attach_context(RTC::ExecutionContext_ptr exec_context)
    {
      m_log.push_back("attach_executioncontext");
      m_execContexts.insert(
			    std::pair<RTC::UniqueId, RTC::ExecutionContext_ptr>(m_nextUniqueId++, exec_context));
      return m_nextUniqueId;
    }
    virtual RTC::ReturnCode_t detach_context(RTC::UniqueId ec_id)
    {
      m_log.push_back("detach_executioncontext");
      m_execContexts.erase(ec_id);
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t on_initialize()
    {
      m_log.push_back("on_initialize");
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t on_finalize()
    {
      m_log.push_back("on_finalize");
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t on_startup(RTC::UniqueId ec_id)
    {
      m_log.push_back("on_startup");
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t on_shutdown(RTC::UniqueId ec_id)
    {
      m_log.push_back("on_shutdown");
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t on_activated(RTC::UniqueId ec_id)
    {
      m_log.push_back("on_activated");
      return returnCode(RTC::RTC_OK);
    }
    virtual RTC::ReturnCode_t on_deactivated(RTC::UniqueId ec_id)
    {
      m_log.push_back("on_deactivated");
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t on_aborting(RTC::UniqueId ec_id)
    {
      m_log.push_back("on_aborting");
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t on_error(RTC::UniqueId ec_id)
    {
      m_log.push_back("on_error");
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t on_reset(RTC::UniqueId ec_id)
    {
      m_log.push_back("on_reset");
      return RTC::RTC_OK;
    }
    
    // RTC::_impl_LightweightRTObject
    virtual RTC::ReturnCode_t initialize()
    {
      m_log.push_back("initialize");
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t finalize()
    {
      m_log.push_back("finalize");
      return RTC::RTC_OK;
    }
    virtual RTC::ReturnCode_t exit()
    {
      m_log.push_back("exit");
      return RTC::RTC_OK;
    }
    virtual CORBA::Boolean is_alive(RTC::_objref_ExecutionContext* exec_context)
    { 
      m_log.push_back("is_alive");
      return CORBA::Boolean(m_alive);
    }
    virtual RTC::ExecutionContextList* get_owned_contexts()
    {
      m_log.push_back("get_contexts");
      return 0;
    }
    virtual RTC::ExecutionContextList* get_participating_contexts()
    {
      m_log.push_back("get_context");
      return 0;
//      return m_execContexts[ec_id];
    }

    virtual RTC::_objref_ExecutionContext* get_context(RTC::ExecutionContextHandle_t)
    {
      return 0;
    }
    virtual RTC::ExecutionContextHandle_t get_context_handle(RTC::_objref_ExecutionContext*)
    {
      return 0;
    }
  public: // helper methods
    int countLog(std::string line)
    {
      int count = 0;
      for (int i = 0; i < (int) m_log.size(); ++i)
	{
	  if (m_log[i] == line) ++count;
	}
      return count;
    }
		
    void setAlive(bool alive)
    {
      m_alive = alive;
    }
		
    void setError(bool error)
    {
      m_error = error;
    }
	
  private:
    RTC::ReturnCode_t returnCode(RTC::ReturnCode_t rc)
    {
      return m_error ? RTC::RTC_ERROR : rc;
    }
  };
	
  class DataFlowComponentMock
//    : public virtual POA_RTC::DataFlowComponent,
    : public virtual POA_OpenRTM::DataFlowComponent,
      public virtual LightweightRTObjectMock
  {
  public:
    // SDOPackage::_impl_SDOSystemElement
    virtual SDOPackage::OrganizationList* get_owned_organizations()
      throw (SDOPackage::NotAvailable)
    {
      m_log.push_back("get_owned_organizations");
      return 0; // dummy
    }
    virtual char* get_sdo_id()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_sdo_id");
      return 0; // dummy
    }
    virtual char* get_sdo_type()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_sdo_type");
      return 0; // dummy
    }
    virtual SDOPackage::DeviceProfile* get_device_profile()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_device_profile");
      return 0; // dummy
    }
    virtual SDOPackage::ServiceProfileList* get_service_profiles()
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_service_profiles");
      return 0; // dummy
    }
    virtual SDOPackage::ServiceProfile* get_service_profile(const char* id)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_service_profile");
      return 0; // dummy
    }
    virtual SDOPackage::SDOService_ptr get_sdo_service(const char* id)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_sdo_service");
      return SDOPackage::SDOService::_nil(); // dummy
    }
    virtual SDOPackage::Configuration_ptr get_configuration()
      throw (SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_configuration");
      return SDOPackage::Configuration::_nil(); // dummy
    }
    virtual SDOPackage::Monitoring_ptr get_monitoring()
      throw (SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_monitoring");
      return SDOPackage::Monitoring::_nil(); // dummy
    }
    virtual SDOPackage::OrganizationList* get_organizations()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_organizations");
      return 0; // dummy
    }
    virtual SDOPackage::NVList* get_status_list()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_status_list");
      return 0; // dummy
    }
    virtual CORBA::Any* get_status(const char* name)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      m_log.push_back("get_status");
      return 0; // dummy
    }

    // RTC::_impl_RTObject
    virtual RTC::ComponentProfile* get_component_profile()
    {
      m_log.push_back("get_component_profile");
      // dummy
      RTC::ComponentProfile_var prof(new RTC::ComponentProfile());
      return prof._retn();
    }
    virtual RTC::PortServiceList* get_ports()
    {
      m_log.push_back("get_ports");
      // dummy
      RTC::PortServiceList_var ports(new RTC::PortServiceList());
      ports->length(0);
      return ports._retn();
    }
    virtual RTC::ExecutionContextServiceList* get_execution_context_services()
    {
      m_log.push_back("get_execution_context_services");
      // dummy
      RTC::ExecutionContextServiceList_var ec = new RTC::ExecutionContextServiceList();
      ec->length(0);
      return ec._retn();
    }

    // RTC::_impl_DataFlowComponentAction
    virtual RTC::ReturnCode_t on_execute(RTC::UniqueId ec_id)
    {
      m_log.push_back("on_execute");
      return RTC::RTC_OK; // dummy
    }
    virtual RTC::ReturnCode_t on_state_update(RTC::UniqueId ec_id)
    {
      m_log.push_back("on_state_update");
      return RTC::RTC_OK; // dummy
    }
    virtual RTC::ReturnCode_t on_rate_changed(RTC::UniqueId ec_id)
    {
      m_log.push_back("on_rate_changed");
      return RTC::RTC_OK; // dummy
    }
  };
	
  class RTObjectMock
    : public RTC::RTObject_impl
  {
  public:
    RTObjectMock(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
      : RTC::RTObject_impl(orb, poa)
    {
    }
    virtual ~RTObjectMock(void){}
  };

  class PeriodicExecutionContextMock
    : public RTC::PeriodicExecutionContext
  {
  public:
    PeriodicExecutionContextMock() : RTC::PeriodicExecutionContext() {}
    virtual ~PeriodicExecutionContextMock(void){}

    // protected: �ѿ��򤳤��ǹ���
    void set_m_ref()
      {
        RTC::PeriodicExecutionContext::m_ref = m_refmock;
      }
    void clear_m_comps()
      {
        if (!RTC::PeriodicExecutionContext::m_comps.empty())
          {
            RTC::PeriodicExecutionContext::m_comps.clear();
          }
      }
    RTC::ExecutionContextService_var m_refmock;
  };
	
  class PeriodicExecutionContextTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PeriodicExecutionContextTests);

    CPPUNIT_TEST(test_is_running);
    CPPUNIT_TEST(test_start_invoking_on_startup);
    CPPUNIT_TEST(test_start_with_running);
    CPPUNIT_TEST(test_start_with_not_alive);
    CPPUNIT_TEST(test_stop_invoking_on_shutdown);
    CPPUNIT_TEST(test_stop_with_not_running);
    CPPUNIT_TEST(test_start_and_stop_multiple_times);
    CPPUNIT_TEST(test_set_rate_and_get_rate);
    CPPUNIT_TEST(test_set_rate_with_zero_or_negative_rate);
    CPPUNIT_TEST(test_set_rate_invoking_on_rate_changed);
    CPPUNIT_TEST(test_add_invoking_attach_executioncontext);
    CPPUNIT_TEST(test_add_not_with_data_flow_component);
    CPPUNIT_TEST(test_remove_invoking_detach_executioncontext);
    CPPUNIT_TEST(test_remove_with_not_attached_component);
    CPPUNIT_TEST(test_remove_when_component_is_still_active);
    CPPUNIT_TEST(test_remove_when_component_is_inactive);
    CPPUNIT_TEST(test_activate_component_invoking_on_activated);
    CPPUNIT_TEST(test_activate_component_without_participating);
    CPPUNIT_TEST(test_activate_component_in_Error_state);
    CPPUNIT_TEST(test_activate_component_not_in_Alive_state);
    CPPUNIT_TEST(test_deactivate_component_invoking_on_deactivated);
    CPPUNIT_TEST(test_deactivate_component_without_participating);
    CPPUNIT_TEST(test_deactivate_component_not_in_Alive_state);
    CPPUNIT_TEST(test_reset_component_invoking_on_reset);
    CPPUNIT_TEST(test_reset_component_not_in_Error_state);
    CPPUNIT_TEST(test_reset_component_not_in_Alive_state);
    CPPUNIT_TEST(test_bindComponent);

    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
	
  public:

    /*!
     * @brief Constructor
     */
    PeriodicExecutionContextTests()
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
    virtual ~PeriodicExecutionContextTests()
    {
    }
		  
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      coil::usleep(100000);
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
		
    /*!
     * @brief is_running()�᥽�åɤΥƥ���
     * 
     * - start()�ƽ����ϡ���running���֤���
     * - start()�ƽФ���ϡ�running���֤���
     * - stop()�ƽи�ϡ���running���֤���
     */
    void test_is_running()
    {
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // start()�ƽФ����ϡ���running���֤���
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(false), ec->is_running());
			
      // start()�ƽФ���ϡ�running���֤���
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), ec->is_running());
			
      // stop()�ƽи�ϡ���running���֤���
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->stop());
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(false), ec->is_running());

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
    }
		
    /*!
     * @brief start()�᥽�åɤΥƥ���
     * 
     * - start()�᥽�åɸƽФ��ˤ�ꡢ����ݡ��ͥ�Ȥ�on_startup()���ƤӽФ���뤫��
     */
    void test_start_invoking_on_startup()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
				
      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ���λ����Ǥϡ��ޤ�on_startup()�ϸƤӽФ���Ƥ��ʤ��Ϥ�
      CPPUNIT_ASSERT_EQUAL(0, mock->countLog("on_startup"));
			
      // start()��ƤӽФ�
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());
			
      // ���λ����ǡ�on_startup()��1������ƤӽФ���Ƥ���Ϥ�
      CPPUNIT_ASSERT_EQUAL(1, mock->countLog("on_startup"));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief start()�᥽�åɤΥƥ���
     * 
     * - ���Ǥ�running���֤κݡ�start()�ƽФ��տޤɤ���˼��Ԥ��뤫��
     */
    void test_start_with_running()
    {
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // start()�ƽФ����ϡ���running���֤ΤϤ�
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(false), ec->is_running());
			
      // start()�ƽФ���ϡ�running���֤ΤϤ�
      ec->start();
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), ec->is_running());
			
      // �����start()�ƽФ���Ԥ����տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, ec->start());

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
    }
		
    /*!
     * @brief start()�᥽�åɤΥƥ���
     * 
     * - Alive���֤ˤʤ�����start()�᥽�åɤ�ƽФ��ơ��տޤɤ���˼��Ԥ��뤫��
     */
    void test_start_with_not_alive()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ��Alive���֤ˤ��Ƥ���
      mock->setAlive(false);
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(false), rto->is_alive(NULL));
			
      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief stop()�᥽�åɤΥƥ���
     * 
     * - stop()�᥽�åɸƽФ��ˤ�ꡢ����ݡ��ͥ�Ȥ�on_shutdown()���ƤӽФ���뤫��
     */
    void test_stop_invoking_on_shutdown()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // start()��ƤӽФ�
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());
			
      // ���λ����Ǥϡ��ޤ�on_shutdown()�ϸƤӽФ���Ƥ��ʤ��Ϥ�
      CPPUNIT_ASSERT_EQUAL(0, mock->countLog("on_shutdown"));

      // stop()��ƤӽФ�
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->stop());
			
      // ���λ����ǡ�on_shutdown()��1������ƤӽФ���Ƥ���Ϥ�
      CPPUNIT_ASSERT_EQUAL(1, mock->countLog("on_shutdown"));

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief stop()�᥽�åɤΥƥ���
     * 
     * - ��running���֤�stop()�᥽�åɤ�ƤӽФ�����硢�տޤɤ���˼��Ԥ��뤫��
     */
    void test_stop_with_not_running()
    {
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically

      // �ޤ�start()���Ƥ��ʤ����֤ǡ��Ĥޤ���running�ξ��֤ǡ�
      // stop()��ƤӽФ����տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(false), ec->is_running());
      CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, ec->stop());

      // start()��ƤӽФ�
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());
			
      // stop()��ƤӽФ�
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(true), ec->is_running());
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->stop());
			
      // �����stop()��ƤӽФ����տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(false), ec->is_running());
      CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, ec->stop());

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
    }
		
    /*!
     * @brief start()�᥽�åɤ�stop()�᥽�åɤΥƥ���
     * 
     * - start()��stop()�򷫤��֤�Ϣ³�ǡ�����˸ƽФ��Ǥ��뤫��
     */
    void test_start_and_stop_multiple_times()
    {
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // start(), stop()��Ϣ³��������˸ƤӽФ��뤫��
      for (int i = 0; i < 1000; ++i)
	{
	  // start()��ƤӽФ�
	  CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());

	  // stop()��ƤӽФ�
	  CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->stop());
	}

      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
    }
		
    /*!
     * @brief set_rate()�᥽�åɤ�get_rate()�᥽�åɤΥƥ���
     * 
     * - set_rate()�����ꤷ���졼���ͤ�get_rate()�������������Ǥ��뤫��
     */
    void test_set_rate_and_get_rate()
    {
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // set_rate()�����ꤷ���졼�Ȥ���get_rate()�������������Ǥ��뤫��
      for (int i = 1; i <= 10; ++i)
	{
	  CORBA::Double rate((double) 1.0 * i);
	  CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->set_rate(rate));
	  CPPUNIT_ASSERT_EQUAL(rate, ec->get_rate());
	}

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
    }
		
    /*!
     * @brief set_rate()�᥽�åɤΥƥ���
     * 
     * - �졼���ͤ�0����ꤷ��set_rate()��ƤӽФ�����硢�տޤɤ���˼��Ԥ��뤫��
     * - �졼���ͤ����ͤ���ꤷ��set_rate()��ƤӽФ�����硢�տޤɤ���˼��Ԥ��뤫��
     */
    void test_set_rate_with_zero_or_negative_rate()
    {
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // 0�ޤ�������Υ졼�Ȥ���ꤷ����硢�տޤɤ���Υ��顼�����ɤ���뤫��
      for (int i = 0; i < 10; ++i)
	{
	  CORBA::Double rate((double) - 1.0 * i);
	  CPPUNIT_ASSERT_EQUAL(RTC::BAD_PARAMETER, ec->set_rate(rate));
	}

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
    }
		
    /*!
     * @biref set_rate()�᥽�åɤΥƥ���
     * 
     * - set_rate()�ƽФ��ˤ�ꡢ����ݡ��ͥ�Ȥ�on_rate_changed()���ƤӽФ���뤫��
     */
    void test_set_rate_invoking_on_rate_changed()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::PERIODIC, ec->get_kind());
			
      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ���λ����Ǥϡ�on_rate_changed()��1���ƤӽФ���Ƥ��ʤ��Ϥ�
      CPPUNIT_ASSERT_EQUAL(0, mock->countLog("on_rate_changed"));
			
      RTC::ExecutionContextProfile* ecp;
      ecp = ec->get_profile();
      CPPUNIT_ASSERT_EQUAL(CORBA::Double(1000000), ecp->rate);

      // set_rate()��ƽФ�
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->set_rate(CORBA::Double(1.0)));
      ecp = ec->get_profile();
      CPPUNIT_ASSERT_EQUAL(CORBA::Double(1.0), ecp->rate);
			
      // ���λ����ǡ�on_rate_changed()��1������ƤӽФ���Ƥ���Ϥ�
      CPPUNIT_ASSERT_EQUAL(1, mock->countLog("on_rate_changed"));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief add()�᥽�åɤΥƥ���
     * 
     * - add()�᥽�åɸƽФ��ˤ�ꡢ����ݡ��ͥ�Ȥ�attach_executioncontext()���ƤӽФ���뤫��
     */
    void test_add_invoking_attach_executioncontext()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // ���λ����Ǥϡ�attach_executioncontext()��1���ƤӽФ���Ƥ��ʤ��Ϥ�
      CPPUNIT_ASSERT_EQUAL(0, mock->countLog("attach_executioncontext"));

      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ���λ����ǡ�attach_executioncontext()��1������ƤӽФ���Ƥ���Ϥ�
      CPPUNIT_ASSERT_EQUAL(1, mock->countLog("attach_executioncontext"));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief add()�᥽�åɤΥƥ���
     * 
     * - �ǡ����ե�����ݡ��ͥ�ȤǤϤʤ�LightweightRTObject����ꤷ��add()�᥽�åɤ�ƤӽФ�����硢�տޤɤ���˼��Ԥ��뤫��
     */
    void test_add_not_with_data_flow_component()
    {
      // RTObject����������
//      POA_RTC::LightweightRTObject* rto
      POA_RTC::LightweightRTObject* rto
	= new LightweightRTObjectMock(); // will be deleted automatically

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::PERIODIC, ec->get_kind());
			
      // LightweightRTObject�ǤϤ��뤬��DataFlowComponent�ǤϤʤ�RTObject���Ѥ��ơ�
      // add()�ƽФ����ߤơ��տޤɤ��ꥨ�顼�����ɤ���뤳�Ȥ��ǧ����
      // CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, ec->add(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief remove()�᥽�åɤΥƥ���
     * 
     * - remove()�ƽФ��ˤ�ꡢ����ݡ��ͥ�Ȥ�detach_executioncontext()���ƤӽФ���뤫��
     */
    void test_remove_invoking_detach_executioncontext()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));

      // ���λ����Ǥϡ�attach_executioncontext()��1���ƤӽФ���Ƥ��ʤ��Ϥ�
      CPPUNIT_ASSERT_EQUAL(0, mock->countLog("detach_executioncontext"));
			
      // ExecutionContext�ؤ���Ͽ��������
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->remove_component(rto->_this()));
			
      // ���λ����ǡ�detach_executioncontext()��1������ƤӽФ���Ƥ���Ϥ�
      CPPUNIT_ASSERT_EQUAL(1, mock->countLog("detach_executioncontext"));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief remove()�᥽�åɤΥƥ���
     * 
     * - �ޤ�ExecutionContext����Ͽ���Ƥ��ʤ�����ݡ��ͥ�ȤˤĤ�����Ͽ������ߤơ��տޤɤ���˼��Ԥ��뤫��
     */
    void test_remove_with_not_attached_component()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // �ޤ���Ͽ���Ƥ��ʤ�����ݡ��ͥ�ȤˤĤ���ExecutionContext�������Ͽ������ߤơ�
      // �տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(RTC::BAD_PARAMETER, ec->remove_component(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief remove()�᥽�åɤΥƥ���
     * 
     * - Active���֤Υ���ݡ��ͥ�Ȥ��Ф���remove()���ߤ���硢�տޤɤ���˼��Ԥ��뤫��
     */
    void test_remove_when_component_is_still_active()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());

      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ����ݡ��ͥ�Ȥ�Active�ˤ���
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->activate_component(rto->_this()));
      usleep(100000);
      CPPUNIT_ASSERT_EQUAL(RTC::ACTIVE_STATE, ec->get_component_state(rto->_this()));

      // ����ݡ��ͥ�Ȥ�Active�Τޤޤ�remove()���ߤơ��տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      // CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, ec->remove(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief remove()�᥽�åɤΥƥ���
     * 
     * - Inactive���֤Υ���ݡ��ͥ�Ȥ��Ф��ơ������remove()�Ǥ��뤫��
     */
    void test_remove_when_component_is_inactive()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());

      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ����ݡ��ͥ�Ȥ�Active�ˤ���
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->activate_component(rto->_this()));
      coil::usleep(100000);
      CPPUNIT_ASSERT_EQUAL(RTC::ACTIVE_STATE, ec->get_component_state(rto->_this()));
			
      // ����ݡ��ͥ�Ȥ�Inactive�ˤ���
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->deactivate_component(rto->_this()));
      coil::usleep(100000);
      CPPUNIT_ASSERT_EQUAL(RTC::INACTIVE_STATE, ec->get_component_state(rto->_this()));
			
      // remove()���������뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->remove_component(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief activate()�᥽�åɤΥƥ���
     * 
     * - activate()�ƽФ��ˤ�ꡢ����ݡ��ͥ�Ȥ�on_activated()���ƤӽФ���뤫��
     */
    void test_activate_component_invoking_on_activated()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());

      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ���λ����Ǥϡ��ޤ�on_activated()��1���ƤӽФ���Ƥ��ʤ��Ϥ�
      CPPUNIT_ASSERT_EQUAL(0, mock->countLog("on_activated"));
			
      // ����ݡ��ͥ�Ȥ�Active�ˤ���
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->activate_component(rto->_this()));
			
      coil::usleep(100000);
      // activate_component()����on_activated()�θƽФ���Ʊ���ƽФǤ��ꡢ
      // ���λ����ǡ�on_activated()��1������ƤӽФ���Ƥ���Ϥ�
      CPPUNIT_ASSERT_EQUAL(1, mock->countLog("on_activated"));

      // activate_component()����on_activated()�θƽФ���Ʊ���ƽФǤ��ꡢ
      // ����åɥ���ƥ����Ȥ����ؤ��뤳�Ȥʤ���Active���֤����ܤ��Ƥ��뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(RTC::ACTIVE_STATE, ec->get_component_state(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * activate()�᥽�åɤΥƥ���
     * 
     * - ExecutionContext��̤��Ͽ�Υ���ݡ��ͥ�Ȥ��Ф���activate()�ƽФ���Ԥ����տޤɤ���˼��Ԥ��뤫��
     */
    void test_activate_component_without_participating()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());

      // ExecutionContext�˥���ݡ��ͥ����Ͽ���뤳�Ȥʤ�activate_component()��ƽФ���
      // �տޤɤ���Υ��饳���ɤ���뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(RTC::BAD_PARAMETER, ec->activate_component(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief activate_component()�᥽�åɤΥƥ���
     * 
     * - Error���֤�activate_component()�ƽФ���Ԥ����տޤɤ���˼��Ԥ��뤫��
     */
    void test_activate_component_in_Error_state()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());
			
      // ����ݡ��ͥ�Ȥ�Error���֤ˤޤ����ܤ�����
      mock->setError(true);
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->activate_component(rto->_this()));
      coil::sleep(1); // Error���֤����ܤ���ޤ��Ԥġ����衢���Υ��꡼�פ����;�ɬ�פ��ݤ���
      CPPUNIT_ASSERT_EQUAL(RTC::ERROR_STATE, ec->get_component_state(rto->_this()));
			
      // Error���֤�activate_component()�ƽФ���Ԥ����տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, ec->activate_component(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief activate_component()�᥽�åɤΥƥ���
     * 
     * - ��Alive���֤Υ���ݡ��ͥ�Ȥ��Ф���activate_component()�ƽФ���Ԥ����տޤɤ���˼��Ԥ��뤫��
     */
    void test_activate_component_not_in_Alive_state()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
			
      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ��Alive���֤ˤ��Ƥ���
      mock->setAlive(false);
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(false), rto->is_alive(NULL));
			
      // activate_component()�ƽФ���Ԥ����տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      // CPPUNIT_ASSERT_EQUAL(RTC::BAD_PARAMETER, ec->activate_component(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief deactivate_component()�᥽�åɤΥƥ���
     * 
     * - deactivate_component()�ƽФ��ˤ�ꡢ����ݡ��ͥ�Ȥ�on_deactivated()���ƤӽФ���뤫��
     */
    void test_deactivate_component_invoking_on_deactivated()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());

      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ����ݡ��ͥ�Ȥ�activate����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->activate_component(rto->_this()));
      coil::usleep(100000);
      CPPUNIT_ASSERT_EQUAL(RTC::ACTIVE_STATE, ec->get_component_state(rto->_this()));

      // ���λ����Ǥϡ��ޤ�on_activated()��1���ƤӽФ���Ƥ��ʤ��Ϥ�
      CPPUNIT_ASSERT_EQUAL(0, mock->countLog("on_deactivated"));

      // ����ݡ��ͥ�Ȥ�deactivate����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->deactivate_component(rto->_this()));
      coil::usleep(100000);
      CPPUNIT_ASSERT_EQUAL(RTC::INACTIVE_STATE, ec->get_component_state(rto->_this()));

      // ���λ����ǡ�on_deactivated()��1������ƤӽФ���Ƥ���Ϥ�
      CPPUNIT_ASSERT_EQUAL(1, mock->countLog("on_deactivated"));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief deactivate_component()�᥽�åɤΥƥ���
     * 
     * - ExecutionContext��̤��Ͽ�Υ���ݡ��ͥ�Ȥ��Ф���deactivate_component()��ƽФ����տޤɤ���˼��Ԥ��뤫��
     */
    void test_deactivate_component_without_participating()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());

      // ExecutionContext����Ͽ���Ƥ��ʤ�����ݡ��ͥ�Ȥ��Ф���deactivate���ߤơ�
      // �տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(RTC::BAD_PARAMETER, ec->deactivate_component(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief deactivate_component()�᥽�åɤΥƥ���
     * 
     * - ��Alive���֤Υ���ݡ��ͥ�Ȥ��Ф���deactivate_component()�ƽФ���Ԥ����տޤɤ���˼��Ԥ��뤫��
     */
    void test_deactivate_component_not_in_Alive_state()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically

      ec->start();
			
      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ����ݡ��ͥ�Ȥ�activate����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->activate_component(rto->_this()));
      usleep(100000);
      CPPUNIT_ASSERT_EQUAL(RTC::ACTIVE_STATE, ec->get_component_state(rto->_this()));

      // ��Alive���֤ˤ��Ƥ���
      mock->setAlive(false);
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(false), rto->is_alive(NULL));

      // ��Alive���֤Υ���ݡ��ͥ�Ȥ��Ф���deactivate���ߤơ��տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      // CPPUNIT_ASSERT_EQUAL(RTC::BAD_PARAMETER, ec->deactivate_component(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief reset_component()�᥽�åɤΥƥ���
     * 
     * - reset_component()�ƽФ��ˤ�ꡢ����ݡ��ͥ�Ȥ�on_reset()���ƤӽФ���뤫��
     */
    void test_reset_component_invoking_on_reset()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);

      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());
			
      // ����ݡ��ͥ�Ȥ�Error���֤ˤޤ����ܤ�����
      mock->setError(true);
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->activate_component(rto->_this()));
      coil::sleep(1); // Error���֤����ܤ���ޤ��Ԥġ����衢���Υ��꡼�פ����;�ɬ�פ��ݤ���
      CPPUNIT_ASSERT_EQUAL(RTC::ERROR_STATE, ec->get_component_state(rto->_this()));
			
      // ���λ����Ǥϡ�on_reset()��1���ƤӽФ���Ƥ��ʤ��Ϥ�
      CPPUNIT_ASSERT_EQUAL(0, mock->countLog("on_reset"));

      // reset_component()��ƽФ����������뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->reset_component(rto->_this()));
      coil::usleep(100000);
      // ���λ����ǡ�on_reset()��1������ƤӽФ���Ƥ���Ϥ�
      CPPUNIT_ASSERT_EQUAL(1, mock->countLog("on_reset"));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief reset_component()�᥽�åɤΥƥ���
     * 
     * - ��Error���֤Υ���ݡ��ͥ�Ȥ��Ф���reset_component()�ƽФ���Ԥ����տޤɤ���˼��Ԥ��뤫��
     */
    void test_reset_component_not_in_Error_state()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->start());
			
      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ���ξ���(Inactive)��reset_component()�ƽФ���Ԥ����տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(RTC::INACTIVE_STATE, ec->get_component_state(rto->_this()));
      CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, ec->reset_component(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief reset_component()�᥽�åɤΥƥ���
     * 
     * - ��Alive���֤Υ���ݡ��ͥ�Ȥ��Ф���reset_component()�ƽФ���Ԥ����տޤɤ���˼��Ԥ��뤫��
     */
    void test_reset_component_not_in_Alive_state()
    {
      // RTObject����������
      POA_RTC::LightweightRTObject* rto
	= new DataFlowComponentMock(); // will be deleted automatically
      DataFlowComponentMock* mock
	= dynamic_cast<DataFlowComponentMock*>(rto);

      // ��Alive����(Create����)�ˤ��Ƥ���
      mock->setAlive(false);
      CPPUNIT_ASSERT_EQUAL(CORBA::Boolean(false), rto->is_alive(NULL));
			
      // ExecutionContext����������
      RTC::PeriodicExecutionContext* ec
	= new RTC::PeriodicExecutionContext(); // will be deleted automatically

      // ExecutionContext��RTObject����Ͽ����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->add_component(rto->_this()));
			
      // ���ξ���(Created)��reset_component()�ƽФ���Ԥ����տޤɤ���Υ��顼�����ɤ���뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(RTC::PRECONDITION_NOT_MET, ec->reset_component(rto->_this()));

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }
		
    /*!
     * @brief bindComponent()�᥽�åɤΥƥ���
     * 
     * - ����ݡ��ͥ�Ȥλ��üԥꥹ�Ȥ���������Ͽ����뤫��
     */
    void test_bindComponent()
    {
      // RTObject����������
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA);
      coil::Properties prop;
      prop.setProperty("exec_cxt.periodic.type","PeriodicExecutionContext");
      prop.setProperty("exec_cxt.periodic.rate","1000");
      rto->setProperties(prop);

      // ExecutionContext����������
      PeriodicExecutionContextMock* ec = new PeriodicExecutionContextMock();

      // RTC::BAD_PARAMETER ���֤�����
      CPPUNIT_ASSERT_EQUAL(RTC::BAD_PARAMETER, ec->bindComponent(NULL));

      // RTC::RTC_OK ���֤�����
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK, ec->bindComponent(rto));

      // 1000����Ͽ�塢(id > ECOTHER_OFFSET)Ƚ���RTC::RTC_ERROR ���֤�����
      for (int i = 0; i < 1000; ++i)
        {
          ec->bindComponent(rto);
        }
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_ERROR, ec->bindComponent(rto));

      // m_ref=_nil()�ͤξ�硢(id < 0)Ƚ���RTC::RTC_ERROR ���֤�����
      ec->m_refmock = RTC::ExecutionContextService::_nil();
      ec->set_m_ref();
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_ERROR, ec->bindComponent(rto));

      // ��Ͽ��������ݡ��ͥ�Ȥκ��
      ec->clear_m_comps();

      ec->stop();
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ec));
      delete ec;
      m_pPOA->deactivate_object(*m_pPOA->servant_to_id(rto));
      delete rto;
    }

  };
}; // namespace PeriodicExecutionContext

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PeriodicExecutionContext::PeriodicExecutionContextTests);

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
#endif // PeriodicExecutionContext_cpp
