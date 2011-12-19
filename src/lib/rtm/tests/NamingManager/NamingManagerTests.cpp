// -*- C++ -*-
/*!
 * @file   NamingManagerTests.cpp
 * @brief  NamingManager test class
 * @date   $Date: 2008/04/30 07:55:33 $
 *
 * $Id: NamingManagerTests.cpp,v 1.1 2008/04/30 07:55:33 arafune Exp $
 *
 */

/*
 * $Log: NamingManagerTests.cpp,v $
 * Revision 1.1  2008/04/30 07:55:33  arafune
 * The first commitment.
 *
 *
 */

#ifndef NamingManager_cpp
#define NamingManager_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/RTC.h>
#include <rtm/RTObject.h>
#include <rtm/NamingManager.h>
#include <rtm/Manager.h>

namespace RTC
{
  class CorbaObjectManager
  {
  public:
    CorbaObjectManager(::CORBA::ORB_ptr orb, ::PortableServer::POA_ptr poa)
      : m_orb(orb), m_poa(poa)
    {
    }

    void activate(::PortableServer::ServantBase* servant)
    {
      try 
        {
          m_poa->activate_object(servant);
        }
      catch(const ::PortableServer::POA::ServantAlreadyActive &)
        {
        }
    }

    void deactivate(::PortableServer::ServantBase* servant)
    {
      ::PortableServer::ObjectId_var id;
      id = m_poa->servant_to_id(servant);
      m_poa->deactivate_object(id);
    }
  protected:
    ::CORBA::ORB_ptr m_orb;
    ::PortableServer::POA_ptr m_poa;
  };
};


/*!
 * @class NamingManagerTests class
 * @brief NamingManager test
 */
namespace NamingManager
{
  // protected: �ؿ��Υƥ�����
  class NamingManagerMock : public RTC::NamingManager
  {
  public:
    // ���󥹥ȥ饯��
    NamingManagerMock(RTC::Manager* manager)
      : RTC::NamingManager(manager) {}
    virtual ~NamingManagerMock(void) {}

    // NamingManager::registerMgrName �ϡ�protected: �ΰ٤����������
    void registerMgrName(const char* name,
                         const RTM::ManagerServant* mgr)
    {
//    std::cout << "registerMgrName() in name=" << name << std::endl;
      RTC::NamingManager::registerMgrName(name, mgr);
      mgrNames = RTC::NamingManager::m_mgrNames;
//    std::cout << "registerMgrName() out" << std::endl;
    }

    // NamingManager::unregisterMgrName �ϡ�protected: �ΰ٤����������
    void unregisterMgrName(const char* name)
    {
//    std::cout << "unregisterMgrName() in name=" << name << std::endl;
      RTC::NamingManager::unregisterMgrName(name);
      mgrNames = RTC::NamingManager::m_mgrNames;
//    std::cout << "unregisterMgrName() out" << std::endl;
    }

    std::vector<RTC::NamingManager::Mgr*> mgrNames;
  };

  class NamingOnCorbaTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(NamingOnCorbaTests);

    CPPUNIT_TEST(test_bindObject_and_unbindObject);
    CPPUNIT_TEST(test_bindObject_and_unbindObject3);

    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
	
  private:
    CosNaming::NamingContext_var getRootContext(const std::string& name_server)
    {
      std::string nsName
	= std::string("corbaloc::")
	+ name_server
	+ std::string("/NameService");
			
      CORBA::Object_var obj = m_pORB->string_to_object(nsName.c_str());
      CosNaming::NamingContext_var rootContext = CosNaming::NamingContext::_narrow(obj);
      if (CORBA::is_nil(rootContext))
	{
	  throw std::bad_alloc();
	}
			
      return rootContext;
    }
	
  public:
    /*!
     * @brief Constructor
     */
    NamingOnCorbaTests()
    {
    }
		    
    /*!
     * @brief Destructor
     */
    virtual ~NamingOnCorbaTests()
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
    }
		
    /*!
     * @brief bindObject()�᥽�åɤ����unbindObject()�᥽�åɤΥƥ���
     * 
     * - ���֥������Ȥ��������Х���ɤǤ��뤫��
     * - ���֥������Ȥ�����������Х���ɤǤ��뤫��
     */
    void test_bindObject_and_unbindObject()
    {
//      const char* name_server = "localhost:9876";
      const char* name_server = "localhost:2809";
      RTC::NamingOnCorba noc(m_pORB, name_server);

      // �Х���ɤ��륪�֥������Ȥ�������Ƥ���
      RTC::CorbaObjectManager objMgr(m_pORB, m_pPOA);
      RTC::RTObject_impl* rto = new RTC::RTObject_impl(m_pORB, m_pPOA);
      objMgr.activate(rto);
      CPPUNIT_ASSERT(! CORBA::is_nil(rto->getObjRef()));
			
      // ���֥������Ȥ�Х���ɤǤ��뤫��
      noc.bindObject("id.kind", rto);
			
      // �Х���ɤ������֥������Ȥ�������resolve�Ǥ��뤫��
      CosNaming::NamingContext_var nc = getRootContext(name_server);
      CosNaming::Name name;
      name.length(1);
      name[0].id = "id";
      name[0].kind = "kind";
      CORBA::Object_ptr obj = nc->resolve(name);
      CPPUNIT_ASSERT(! CORBA::is_nil(obj));
			
      // �Х���ɤ������֥������Ȥ򥢥�Х���ɤǤ��뤫��
      noc.unbindObject("id.kind");
			
      // ����Х���ɤ������֥������Ȥ�resolve���տޤɤ��꼺�Ԥ��뤫��
      try
	{
	  nc->resolve(name);
	  CPPUNIT_FAIL("Exception not thrown.");
	}
      catch (CosNaming::NamingContext::NotFound expected) {}
      objMgr.deactivate(rto);

      rto->finalize();
      delete rto;
    }

    /*!
     * @brief bindObject()�᥽�åɤ�unbindObject()�᥽�åɤΥƥ���
     * 
     * - ����ManagerServant�ǡ����֥������Ȥ��������Х���ɤǤ��뤫��
     * - ���֥������Ȥ�����������Х���ɤǤ��뤫��
     */
    void test_bindObject_and_unbindObject3()
    {
//      const char* name_server = "localhost:9876";
      const char* name_server = "localhost:2809";
      RTC::NamingOnCorba noc(m_pORB, name_server);

      // �Х���ɤ��륪�֥������Ȥ�������Ƥ���
      RTC::CorbaObjectManager objMgr(m_pORB, m_pPOA);
      RTM::ManagerServant* mgrs = new RTM::ManagerServant();
      objMgr.activate(mgrs);
      //CPPUNIT_ASSERT(! CORBA::is_nil(mgrs->getObjRef()));

      // ���֥������Ȥ�Х���ɤǤ��뤫��
      noc.bindObject("id.kind", mgrs);

      // �Х���ɤ������֥������Ȥ�������resolve�Ǥ��뤫��
      CosNaming::NamingContext_var nc = getRootContext(name_server);
      CosNaming::Name name;
      name.length(1);
      name[0].id = "id";
      name[0].kind = "kind";
      CORBA::Object_ptr obj = nc->resolve(name);
      //CPPUNIT_ASSERT(! CORBA::is_nil(obj));

      // �Х���ɤ������֥������Ȥ򥢥�Х���ɤǤ��뤫��
      noc.unbindObject("id.kind");

      // ����Х���ɤ������֥������Ȥ�resolve���տޤɤ��꼺�Ԥ��뤫��
      try
	{
	  nc->resolve(name);
	  CPPUNIT_FAIL("Exception not thrown.");
	}
      catch (CosNaming::NamingContext::NotFound expected) {}
      objMgr.deactivate(mgrs);

      delete mgrs;
    }

  };
	
  class NamingManagerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(NamingManagerTests);

    CPPUNIT_TEST(test_registerMgrName_and_unregisterMgrName);
    CPPUNIT_TEST(test_bindObject_and_unbindObject2);
    CPPUNIT_TEST(test_bindObject_and_unbindObject);
    CPPUNIT_TEST(test_unbindAll);
    CPPUNIT_TEST(test_getObjects);
    CPPUNIT_TEST(test_update);

    CPPUNIT_TEST_SUITE_END();
	
  private:
    RTC::Manager* m_mgr;
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
	
  private:
    CosNaming::NamingContext_var getRootContext(const std::string& name_server)
    {
      std::string nsName
	= std::string("corbaloc::")
	+ name_server
	+ std::string("/NameService");
			
      CORBA::Object_var obj = m_mgr->getORB()->string_to_object(nsName.c_str());
      CosNaming::NamingContext_var rootContext = CosNaming::NamingContext::_narrow(obj);
      if (CORBA::is_nil(rootContext))
	{
	  throw std::bad_alloc();
	}
			
      return rootContext;
    }
		
    bool canResolve(const char* name_server, const char* id, const char* kind)
    {
      CosNaming::NamingContext_var nc = getRootContext(name_server);
			
      CosNaming::Name name;
      name.length(1);
      name[0].id = id;
      name[0].kind = kind;
			
      CORBA::Object_ptr obj;
      try
	{
	  obj = nc->resolve(name);
	}
      catch (CosNaming::NamingContext::NotFound e)
	{
	  return false;
	}
			
      return !CORBA::is_nil(obj);
    }
		
  public:
    /*!
     * @brief Constructor
     */
    NamingManagerTests()
    {
    }
		    
    /*!
     * @brief Destructor
     */
    virtual ~NamingManagerTests()
    {
    }
		  
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      m_mgr = RTC::Manager::init(0, NULL);
      m_pORB = m_mgr->getORB();
      m_pPOA = m_mgr->getPOA();
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    {
    }
		
    /*!
     * @brief registerNameServer()�᥽�åɤΥƥ���
     */
    void test_registerNameServer()
    {
      // test_bindObject_and_unbindObject�ǻ��Ѥ��Ƥ���ΤǾ�ά
    }
		
    /*!
     * @brief bindObject()�᥽�åɤ�unbindObject()�᥽�åɤΥƥ���
     * 
     * - ���֥������Ȥ��������Х���ɤǤ��뤫��
     * - ���֥������Ȥ�����������Х���ɤǤ��뤫��
     */
    void test_bindObject_and_unbindObject()
    {
      // �Х���ɤ��륪�֥������Ȥ�������Ƥ���
      RTC::CorbaObjectManager objMgr(m_pORB, m_pPOA);
			
      RTC::RTObject_impl* rto = new RTC::RTObject_impl(m_pORB, m_pPOA);
      objMgr.activate(rto);
      CPPUNIT_ASSERT(! CORBA::is_nil(rto->getObjRef()));

      // NamingManager���������������ϡ�Manager�������������������...��
      RTC::NamingManager nmgr(m_mgr);
//      const char* name_server = "localhost:9876";
      const char* name_server = "localhost:2809";
      nmgr.registerNameServer("corba", name_server);
			
      // ���֥������Ȥ�Х���ɤǤ��뤫��
      nmgr.bindObject("id.kind", rto);
      CPPUNIT_ASSERT(canResolve(name_server, "id", "kind"));
			
      // �Х���ɤ������֥������Ȥ򥢥�Х���ɤǤ��뤫��
      nmgr.unbindObject("id.kind");
			
      // ����Х���ɤ������֥������Ȥ�resolve���տޤɤ��꼺�Ԥ��뤫��
      CPPUNIT_ASSERT(! canResolve(name_server, "id", "kind"));
      objMgr.deactivate(rto);

      rto->finalize();
      delete rto;
    }
		
    /*!
     * @brief unbindAll()�᥽�åɤΥƥ���
     * 
     * - �Х���ɤ���Ƥ��뤹�٤ƤΥ��֥������Ȥ�����˥���Х���ɤǤ��뤫��
     */
    void test_unbindAll()
    {
      // �Х���ɤ��륪�֥������Ȥ�������Ƥ���
      RTC::CorbaObjectManager objMgr(m_pORB, m_pPOA);

      RTC::RTObject_impl* rto1 = new RTC::RTObject_impl(m_pORB, m_pPOA);
      objMgr.activate(rto1);
      CPPUNIT_ASSERT(! CORBA::is_nil(rto1->getObjRef()));

      RTC::RTObject_impl* rto2 = new RTC::RTObject_impl(m_pORB, m_pPOA);
      objMgr.activate(rto2);
      CPPUNIT_ASSERT(! CORBA::is_nil(rto2->getObjRef()));

      // NamingManager���������������ϡ�Manager�������������������...��
      RTC::NamingManager nmgr(m_mgr);
//      const char* name_server = "localhost:9876";
      const char* name_server = "localhost:2809";
      nmgr.registerNameServer("corba", name_server);
			
      // ���֥������Ȥ򣲤ĥХ���ɤ��Ƥ���
      nmgr.bindObject("id1.kind1", rto1);
      CPPUNIT_ASSERT(canResolve(name_server, "id1", "kind1"));

      nmgr.bindObject("id2.kind2", rto2);
      CPPUNIT_ASSERT(canResolve(name_server, "id2", "kind2"));
			
      // unbindAll()��Ԥ�
      nmgr.unbindAll();
			
      // ����Х���ɤ������֥������Ȥ�resolve���տޤɤ��꼺�Ԥ��뤫��
      CPPUNIT_ASSERT(! canResolve(name_server, "id1", "kind1"));
      CPPUNIT_ASSERT(! canResolve(name_server, "id2", "kind2"));
      objMgr.deactivate(rto2);
      objMgr.deactivate(rto1);

      rto2->finalize();
      delete rto2;
      rto1->finalize();
      delete rto1;
    }
		
    /*!
     * @brief getObjects()�᥽�åɤΥƥ���
     * 
     * - �Х���ɤ���Ƥ��뤹�٤ƤΥ��֥������Ȥ������������Ǥ��뤫��
     */
    void test_getObjects()
    {
      // �Х���ɤ��륪�֥������Ȥ�������Ƥ���
      RTC::CorbaObjectManager objMgr(m_pORB, m_pPOA);

      RTC::RTObject_impl* rto1 = new RTC::RTObject_impl(m_pORB, m_pPOA);
      objMgr.activate(rto1);
      CPPUNIT_ASSERT(! CORBA::is_nil(rto1->getObjRef()));

      RTC::RTObject_impl* rto2 = new RTC::RTObject_impl(m_pORB, m_pPOA);
      objMgr.activate(rto2);
      CPPUNIT_ASSERT(! CORBA::is_nil(rto2->getObjRef()));

      // NamingManager���������������ϡ�Manager�������������������...��
      RTC::NamingManager nmgr(m_mgr);
//      const char* name_server = "localhost:9876";
      const char* name_server = "localhost:2809";
      nmgr.registerNameServer("corba", name_server);
			
      // ���֥������Ȥ򣲤ĥХ���ɤ��Ƥ���
      nmgr.bindObject("id1.kind1", rto1);
      CPPUNIT_ASSERT(canResolve(name_server, "id1", "kind1"));

      nmgr.bindObject("id2.kind2", rto2);
      CPPUNIT_ASSERT(canResolve(name_server, "id2", "kind2"));
			
      // getObjects()�ǡ��Х���ɤ���Ƥ��뤹�٤ƤΥ��֥������Ȥμ�����Ԥ�
      std::vector<RTC::RTObject_impl*> objs = nmgr.getObjects();
      CPPUNIT_ASSERT_EQUAL(2, (int) objs.size());
			
      // �����������֥������ȷ������Ƥ�����������
      CPPUNIT_ASSERT(objs.end() != std::find(objs.begin(), objs.end(), rto1));
      CPPUNIT_ASSERT(objs.end() != std::find(objs.begin(), objs.end(), rto2));
      objMgr.deactivate(rto2);
      objMgr.deactivate(rto1);

      rto2->finalize();
      delete rto2;
      rto1->finalize();
      delete rto1;
    }
		
    /*!
     * @brief update()�᥽�åɤΥƥ���
     * 
     * - �͡��ॵ���ӥ�����Ͽ������ǡ�����update()�ƽФ����ϡ��ޤ��͡��ॵ���ӥ��˥Х���ɤ���Ƥ��ʤ����Ȥ��ǧ����
     * - �͡��ॵ���ӥ�����Ͽ������ǡ�����update()�ƽФθ�ϡ��͡��ॵ���ӥ����������Х���ɤ���Ƥ��뤳�Ȥ��ǧ����
     */
    void test_update()
    {
//      const char* name_server = "localhost:9876";
      const char* name_server = "localhost:2809";
      RTC::NamingManager nmgr(m_mgr);

      // �Х���ɤ��륪�֥������Ȥ�������Ƥ���
      RTC::CorbaObjectManager objMgr(m_pORB, m_pPOA);
			
      RTC::RTObject_impl* rto = new RTC::RTObject_impl(m_pORB, m_pPOA);
      objMgr.activate(rto);
      CPPUNIT_ASSERT(! CORBA::is_nil(rto->getObjRef()));

      // registerNameServer()�ƽ����˥��֥������Ȥ���Ͽ������硢
      // ���λ����Ǥϡ��ޤ��͡��ॵ���ӥ��˥Х���ɤ���Ƥ��ʤ��Ϥ�
      nmgr.bindObject("id.kind", rto);
      // Cannot do bind because it is not registered. 
      CPPUNIT_ASSERT(! canResolve(name_server, "id", "kind"));
			
      // �͡��ॵ���ӥ�����Ͽ������ǡ�����update()�ƽФ����ϡ�
      // ��Ϥꡢ�ޤ��͡��ॵ���ӥ��˥Х���ɤ���Ƥ��ʤ��Ϥ�
      nmgr.registerNameServer("corba", name_server);
      // Only registered. 
      CPPUNIT_ASSERT(! canResolve(name_server, "id", "kind"));
			
      // update()�ƽи�ϡ��������͡��ॵ���ӥ��˥Х���ɤ���Ƥ��뤫��
      //
      m_mgr->getConfig()["naming.update.rebind"] = "NO";
      nmgr.update();
      CPPUNIT_ASSERT(! canResolve(name_server, "id", "kind"));

      m_mgr->getConfig()["naming.update.rebind"] = "YES";
      nmgr.update();
      CPPUNIT_ASSERT(canResolve(name_server, "id", "kind"));
      objMgr.deactivate(rto);

      rto->finalize();
      delete rto;
    }

    /*!
     * @brief registerMgrName()�᥽�åɤ�unregisterMgrName()�᥽�åɤΥƥ���
     * 
     * - ����ManagerServant�ǡ��ޥ͡����㡼�����Х�Ȥ�����������Ǥ��뤫��
     */
    void test_registerMgrName_and_unregisterMgrName()
    {
      // �����Х�Ⱥ���
      RTC::CorbaObjectManager objMgr(m_pORB, m_pPOA);
      RTM::ManagerServant* mgrs1 = new RTM::ManagerServant();
      RTM::ManagerServant* mgrs2 = new RTM::ManagerServant();
      RTM::ManagerServant* mgrs3 = new RTM::ManagerServant();
      objMgr.activate(mgrs1);
      objMgr.activate(mgrs2);
      objMgr.activate(mgrs3);
      NamingManagerMock nmm(m_mgr);

      // �ޥ͡����㡼�����Х�Ȥ�����
      nmm.registerMgrName("id.kind", mgrs1);    // �������

      // ������꤬��Ͽ����Ƥ��뤫��
      bool bret(false);
      for (int i(0), len(nmm.mgrNames.size()); i < len; ++i)
        {
          if (nmm.mgrNames[i]->name == "id.kind")
            {
              if (nmm.mgrNames[i]->mgr == mgrs1)
                {
                  bret = true;
                }
            }
        }
      CPPUNIT_ASSERT(bret);

      nmm.registerMgrName("id.kind", mgrs2);   // �������

      // ������꤬��Ͽ����Ƥ��뤫��
      bret = false;
      for (int i(0), len(nmm.mgrNames.size()); i < len; ++i)
        {
          if (nmm.mgrNames[i]->name == "id.kind")
            {
              if (nmm.mgrNames[i]->mgr == mgrs2)
                {
                  bret = true;
                }
            }
        }
      CPPUNIT_ASSERT(bret);

      nmm.registerMgrName("id2.kind2", mgrs3);   // �ɲ�����

      // �ɲ����꤬��Ͽ����Ƥ��뤫��
      bret = false;
      for (int i(0), len(nmm.mgrNames.size()); i < len; ++i)
        {
          if (nmm.mgrNames[i]->name == "id2.kind2")
            {
              if (nmm.mgrNames[i]->mgr == mgrs3)
                {
                  bret = true;
                }
            }
        }
      CPPUNIT_ASSERT(bret);

      // �ޥ͡����㡼�����Х�Ȥ�������
      nmm.unregisterMgrName("id2.kind2");

      // �ɲ������name���������Ƥ��뤫��
      bret = false;
      for (int i(0), len(nmm.mgrNames.size()); i < len; ++i)
        {
          if (nmm.mgrNames[i]->name == "id2.kind2")
            {
              bret = true;
            }
        }
      CPPUNIT_ASSERT(!bret);

      // �ɲ������mgr���������Ƥ��뤫��
      bret = false;
      for (int i(0), len(nmm.mgrNames.size()); i < len; ++i)
        {
          if (nmm.mgrNames[i]->mgr == mgrs3)
            {
              bret = true;
            }
        }
      CPPUNIT_ASSERT(!bret);

      // �ޥ͡����㡼�����Х�Ȥ�������
      nmm.unregisterMgrName("id.kind");

      // ��󡦾�������name���������Ƥ��뤫��
      bret = false;
      for (int i(0), len(nmm.mgrNames.size()); i < len; ++i)
        {
          if (nmm.mgrNames[i]->name == "id.kind")
            {
              bret = true;
            }
        }
      CPPUNIT_ASSERT(!bret);

      // ��󡦾�������mgr���������Ƥ��뤫��
      bret = false;
      for (int i(0), len(nmm.mgrNames.size()); i < len; ++i)
        {
          if ((nmm.mgrNames[i]->mgr == mgrs1) || (nmm.mgrNames[i]->mgr == mgrs2))
            {
              bret = true;
            }
        }
      CPPUNIT_ASSERT(!bret);
      objMgr.deactivate(mgrs3);
      objMgr.deactivate(mgrs2);
      objMgr.deactivate(mgrs1);

      delete mgrs3;
      delete mgrs2;
      delete mgrs1;
    }

    /*!
     * @brief bindObject()�᥽�åɤ�unbindObject()�᥽�åɤΥƥ���
     * 
     * - ����ManagerServant�ǡ����֥������Ȥ��������Х���ɤǤ��뤫��
     * - ���֥������Ȥ�����������Х���ɤǤ��뤫��
     */
    void test_bindObject_and_unbindObject2()
    {
      // �Х���ɤ��륪�֥������Ȥ�������Ƥ���
      RTC::CorbaObjectManager objMgr(m_pORB, m_pPOA);

      RTM::ManagerServant* mgrs = new RTM::ManagerServant();
      objMgr.activate(mgrs);
      //CPPUNIT_ASSERT(! CORBA::is_nil(mgrs->getObjRef()));

      // NamingManager���������������ϡ�Manager�������������������...��
      RTC::NamingManager nmgr(m_mgr);
//      const char* name_server = "localhost:9876";
      const char* name_server = "localhost:2809";
      nmgr.registerNameServer("corba", name_server);

      // ���֥������Ȥ�Х���ɤǤ��뤫��
      nmgr.bindObject("id.kind", mgrs);
      //CPPUNIT_ASSERT(canResolve(name_server, "id", "kind"));

      // �Х���ɤ������֥������Ȥ򥢥�Х���ɤǤ��뤫��
      nmgr.unbindObject("id.kind");

      // ����Х���ɤ������֥������Ȥ�resolve���տޤɤ��꼺�Ԥ��뤫��
      CPPUNIT_ASSERT(! canResolve(name_server, "id", "kind"));
      objMgr.deactivate(mgrs);

      delete mgrs;
    }

  };
}; // namespace NamingManager

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(NamingManager::NamingOnCorbaTests);
CPPUNIT_TEST_SUITE_REGISTRATION(NamingManager::NamingManagerTests);

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
#endif // NamingManager_cpp
