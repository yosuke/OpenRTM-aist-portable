// -*- C++ -*-
/*!
 * @file   CORBA_SeqUtilTests.cpp
 * @brief  CORBA_SeqUtil test class
 * @date   $Date: 2008/01/10 11:02:06 $
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
 * $Id: CORBA_SeqUtilTests.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

/*
 * $Log: CORBA_SeqUtilTests.cpp,v $
 * Revision 1.2  2008/01/10 11:02:06  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2006/11/27 08:26:10  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.1  2006/10/31 13:10:51  kurihara
 *
 * test program for CORBA_SeqUtil.h
 *
 */

#ifndef CORBA_SeqUtil_cpp
#define CORBA_SeqUtil_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/PortAdmin.h>
#include <rtm/ConnectorBase.h>
#include "SeqUtilTestsSkel.h"

/*!
 * @class CORBA_SeqUtilTests class
 * @brief CORBA_SeqUtil test
 */
namespace CORBA_SeqUtil
{

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
    }
    virtual void deactivateInterfaces()
    {
    }
  };


  using namespace std;
  
  class CORBA_SeqUtilTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(CORBA_SeqUtilTests);
		
    CPPUNIT_TEST(test_for_each);
    CPPUNIT_TEST(test_find);
    CPPUNIT_TEST(test_push_back);
    CPPUNIT_TEST(test_push_back_list);
    CPPUNIT_TEST(test_insert);
    CPPUNIT_TEST(test_front);
    CPPUNIT_TEST(test_back);
    CPPUNIT_TEST(test_erase);
    CPPUNIT_TEST(test_erase_if);
    CPPUNIT_TEST(test_clear);
    CPPUNIT_TEST(test_refToVstring);

    CPPUNIT_TEST_SUITE_END();
		
  private:
    NameValue nv;
    NVList nvlist;
    CORBA::Short  st, rst;
    CORBA::Long   lg, rlg;
    CORBA::Float  ft, rft;
    CORBA::Double dl, rdl;
		
  public:
    /*!
     * @brief Constructor
     */
    CORBA_SeqUtilTests()
    {
    }
		    
    /*!
     * @brief Destructor
     */
    ~CORBA_SeqUtilTests()
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
     * @brief test_for_each()�ǻ��Ѥ���ե��󥯥�
     */
    struct functor_for_each
    {
      functor_for_each(vector<NameValue>& receivedNameValues)
	: _receivedNameValues(receivedNameValues) {}
			
      bool operator()(const NameValue& nv) {
	_receivedNameValues.push_back(nv);
	return true;
      }
			
      vector<NameValue>& _receivedNameValues;
    };
		
    /*!
     * @brief for_each()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>�����ǻ��ꤵ�줿NVList��Τ��٤Ƥ����ǤˤĤ��ơ�����������ǥե��󥯥����ƤӽФ���뤫��</li>
     * <li>�ե��󥯥��ƽл��˰������Ϥ����NameValue����������Τ���</li>
     * </ul>
     */
    void test_for_each()
    {
      // �ƥ����Ѥ�NVList���������
      NVList nvlist;
      nvlist.length(4);
			
      NameValue nvShort;
      nvShort.name = "short";
      nvShort.value <<= (CORBA::Short) 123;
      nvlist[0] = nvShort;
			
      NameValue nvLong;
      nvLong.name = "long";
      nvLong.value <<= (CORBA::Long) 123456;
      nvlist[1] = nvLong;
			
      NameValue nvFloat;
      nvFloat.name = "float";
      nvFloat.value <<= (CORBA::Float) 987.654;
      nvlist[2] = nvFloat;
			
      NameValue nvDouble;
      nvDouble.name = "double";
      nvDouble.value <<= (CORBA::Double) 987654.321987;
      nvlist[3] = nvDouble;
			
      // for_each()��ƤӽФ�
      vector<NameValue> receivedNameValues;
      CORBA_SeqUtil::for_each(nvlist, functor_for_each(receivedNameValues));
			
      // �ե��󥯥����ƤӽФ��줿���������˵�Ͽ����NameValue�Υ٥�����������������ͤ���Ӥ���
      CPPUNIT_ASSERT_EQUAL(4, (int) receivedNameValues.size());
      CPPUNIT_ASSERT_EQUAL((string) nvlist[0].name, (string) receivedNameValues[0].name);
      CPPUNIT_ASSERT_EQUAL((string) nvlist[1].name, (string) receivedNameValues[1].name);
      CPPUNIT_ASSERT_EQUAL((string) nvlist[2].name, (string) receivedNameValues[2].name);
      CPPUNIT_ASSERT_EQUAL((string) nvlist[3].name, (string) receivedNameValues[3].name);
			
      CORBA::Short expectedShort, actualShort;
      nvlist[0].value >>= expectedShort;
      receivedNameValues[0].value >>= actualShort;
      CPPUNIT_ASSERT_EQUAL(expectedShort, actualShort);
			
      CORBA::Long expectedLong, actualLong;
      nvlist[1].value >>= expectedLong;
      receivedNameValues[1].value >>= actualLong;
      CPPUNIT_ASSERT_EQUAL(expectedLong, actualLong);

      CORBA::Float expectedFloat, actualFloat;
      nvlist[2].value >>= expectedFloat;
      receivedNameValues[2].value >>= actualFloat;
      CPPUNIT_ASSERT_EQUAL(expectedFloat, actualFloat);

      CORBA::Double expectedDouble, actualDouble;
      nvlist[3].value >>= expectedDouble;
      receivedNameValues[3].value >>= actualDouble;
      CPPUNIT_ASSERT_EQUAL(expectedDouble, actualDouble);
    }
		
    /*!
     * @brief test_find()�ǻ��Ѥ���ե��󥯥�
     */
    struct functor_find
    {
      functor_find(const string& name)
	: _name(name) {}
			
      bool operator()(const NameValue& nv) {
	return _name == string(nv.name);
      }
			
      const string _name;
    };
		
    /*!
     * @brief find()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>�ե��󥯥����Ѥ���NVList������Ǥ������������Ǥ��뤫��</li>
     * </ul>
     */
    void test_find()
    {
      // �ƥ����Ѥ�NVList���������
      NVList nvlist;
      nvlist.length(4);
			
      NameValue nvShort;
      nvShort.name = "short";
      nvShort.value <<= (CORBA::Short) 123;
      nvlist[0] = nvShort;
			
      NameValue nvLong;
      nvLong.name = "long";
      nvLong.value <<= (CORBA::Long) 123456;
      nvlist[1] = nvLong;
			
      NameValue nvFloat;
      nvFloat.name = "float";
      nvFloat.value <<= (CORBA::Float) 987.654;
      nvlist[2] = nvFloat;
			
      NameValue nvDouble;
      nvDouble.name = "double";
      nvDouble.value <<= (CORBA::Double) 987654.321987;
      nvlist[3] = nvDouble;

      // ̾��"short"�����NameValue�Υ���ǥ����������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 0, CORBA_SeqUtil::find(nvlist, functor_find("short")));
			
      // ̾��"long"�����NameValue�Υ���ǥ����������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 1, CORBA_SeqUtil::find(nvlist, functor_find("long")));

      // ̾��"float"�����NameValue�Υ���ǥ����������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 2, CORBA_SeqUtil::find(nvlist, functor_find("float")));
			
      // ̾��"double"�����NameValue�Υ���ǥ����������������Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 3, CORBA_SeqUtil::find(nvlist, functor_find("double")));
    }

    /*!
     * @brief push_back()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>push_back�ˤ���ɲä��������Ǥ����Ƥ������줾����������Ǽ����뤫��</li>
     * </ul>
     */
    void test_push_back()
    {
      NVList nvlist;

      // ���Ĥ�����Ǥ�push_back���ơ����ǿ����������������å�����
      NameValue nvShort;
      nvShort.name = "short";
      nvShort.value <<= (CORBA::Short) 123;
      CORBA_SeqUtil::push_back(nvlist, nvShort);
      CPPUNIT_ASSERT_EQUAL((CORBA::ULong) 1, nvlist.length());
			
      // ���Ĥ�����Ǥ�push_back���ơ����ǿ����������������å�����
      NameValue nvLong;
      nvLong.name = "long";
      nvLong.value <<= (CORBA::Long) 123456;
      CORBA_SeqUtil::push_back(nvlist, nvLong);
      CPPUNIT_ASSERT_EQUAL((CORBA::ULong) 2, nvlist.length());
			
      // ���Ĥ�����Ǥ�push_back���ơ����ǿ����������������å�����
      NameValue nvFloat;
      nvFloat.name = "float";
      nvFloat.value <<= (CORBA::Float) 987.654;
      CORBA_SeqUtil::push_back(nvlist, nvFloat);
      CPPUNIT_ASSERT_EQUAL((CORBA::ULong) 3, nvlist.length());
			
      // ���Ĥ�����Ǥ�push_back���ơ����ǿ����������������å�����
      NameValue nvDouble;
      nvDouble.name = "double";
      nvDouble.value <<= (CORBA::Double) 987654.321987;
      CORBA_SeqUtil::push_back(nvlist, nvDouble);
      CPPUNIT_ASSERT_EQUAL((CORBA::ULong) 4, nvlist.length());
			
      // push_back���������Ǥ����Ƥ���NVList�����������Ǽ����Ƥ��뤳�Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL((string) "short", (string) nvlist[0].name);
      CPPUNIT_ASSERT_EQUAL((string) "long", (string) nvlist[1].name);
      CPPUNIT_ASSERT_EQUAL((string) "float", (string) nvlist[2].name);
      CPPUNIT_ASSERT_EQUAL((string) "double", (string) nvlist[3].name);
			
      CORBA::Short actualShort;
      nvlist[0].value >>= actualShort;
      CPPUNIT_ASSERT_EQUAL((CORBA::Short) 123, actualShort);
			
      CORBA::Long actualLong;
      nvlist[1].value >>= actualLong;
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 123456, actualLong);

      CORBA::Float actualFloat;
      nvlist[2].value >>= actualFloat;
      CPPUNIT_ASSERT_EQUAL((CORBA::Float) 987.654, actualFloat);

      CORBA::Double actualDouble;
      nvlist[3].value >>= actualDouble;
      CPPUNIT_ASSERT_EQUAL((CORBA::Double) 987654.321987, actualDouble);
    }
		
    /*!
     * @brief push_back_list()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>������NVList�����Ƥ�¾����NVList�θ������������ڥ�ɤǤ��뤫��</li>
     * </ul>
     */
    void test_push_back_list()
    {
      // ���Ĥ��NVList���������
      NVList nvlist1;
      nvlist1.length(2);
			
      NameValue nvShort;
      nvShort.name = "short";
      nvShort.value <<= (CORBA::Short) 123;
      nvlist1[0] = nvShort;
			
      NameValue nvLong;
      nvLong.name = "long";
      nvLong.value <<= (CORBA::Long) 123456;
      nvlist1[1] = nvLong;
			
      // ���Ĥ��NVList���������
      NVList nvlist2;
      nvlist2.length(2);
			
      NameValue nvFloat;
      nvFloat.name = "float";
      nvFloat.value <<= (CORBA::Float) 987.654;
      nvlist2[0] = nvFloat;
			
      NameValue nvDouble;
      nvDouble.name = "double";
      nvDouble.value <<= (CORBA::Double) 987654.321987;
      nvlist2[1] = nvDouble;
			
      // push_back_list���ơ����Ĥ��NVList�ˣ��Ĥ��NVList�򥢥ڥ�ɤ���
      CORBA_SeqUtil::push_back_list(nvlist1, nvlist2);
			
      // ���������ڥ�ɤ��줿���Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL((string) "short", (string) nvlist1[0].name);
      CPPUNIT_ASSERT_EQUAL((string) "long", (string) nvlist1[1].name);
      CPPUNIT_ASSERT_EQUAL((string) "float", (string) nvlist1[2].name);
      CPPUNIT_ASSERT_EQUAL((string) "double", (string) nvlist1[3].name);
			
      CORBA::Short actualShort;
      nvlist1[0].value >>= actualShort;
      CPPUNIT_ASSERT_EQUAL((CORBA::Short) 123, actualShort);
			
      CORBA::Long actualLong;
      nvlist1[1].value >>= actualLong;
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 123456, actualLong);

      CORBA::Float actualFloat;
      nvlist1[2].value >>= actualFloat;
      CPPUNIT_ASSERT_EQUAL((CORBA::Float) 987.654, actualFloat);

      CORBA::Double actualDouble;
      nvlist1[3].value >>= actualDouble;
      CPPUNIT_ASSERT_EQUAL((CORBA::Double) 987654.321987, actualDouble);
    }
		
    /*!
     * @brief insert()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>��Ƭ���֤ؤ��������������Ԥ��뤫��</li>
     * <li>�Ǹ������֤ؤ��������������Ԥ��뤫��</li>
     * <li>��ְ��֤ؤ��������������Ԥ��뤫��</li>
     * </ul>
     */
    void test_insert()
    {
      // �����оݤȤʤ�NVList���������
      NVList nvlist;
      nvlist.length(1);

      NameValue nvLong;
      nvLong.name = "long";
      nvLong.value <<= (CORBA::Long) 123456;
      nvlist[0] = nvLong;
			
      // (1) ��Ƭ�ؤ�������Ԥ�
      NameValue nvShort;
      nvShort.name = "short";
      nvShort.value <<= (CORBA::Short) 123;
      CORBA_SeqUtil::insert(nvlist, nvShort, 0);
			
      // (2) �Ǹ����ؤ�������Ԥ�
      NameValue nvDouble;
      nvDouble.name = "double";
      nvDouble.value <<= (CORBA::Double) 987654.321987;
      CORBA_SeqUtil::insert(nvlist, nvDouble, 2);
			
      // (3) ��֤ؤ�������Ԥ�
      NameValue nvFloat;
      nvFloat.name = "float";
      nvFloat.value <<= (CORBA::Float) 987.654;
      CORBA_SeqUtil::insert(nvlist, nvFloat, 2);
			
      // ������̤����������Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL((string) "short", (string) nvlist[0].name);
      CPPUNIT_ASSERT_EQUAL((string) "long", (string) nvlist[1].name);
      CPPUNIT_ASSERT_EQUAL((string) "float", (string) nvlist[2].name);
      CPPUNIT_ASSERT_EQUAL((string) "double", (string) nvlist[3].name);
			
      CORBA::Short actualShort;
      nvlist[0].value >>= actualShort;
      CPPUNIT_ASSERT_EQUAL((CORBA::Short) 123, actualShort);
			
      CORBA::Long actualLong;
      nvlist[1].value >>= actualLong;
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 123456, actualLong);

      CORBA::Float actualFloat;
      nvlist[2].value >>= actualFloat;
      CPPUNIT_ASSERT_EQUAL((CORBA::Float) 987.654, actualFloat);

      CORBA::Double actualDouble;
      nvlist[3].value >>= actualDouble;
      CPPUNIT_ASSERT_EQUAL((CORBA::Double) 987654.321987, actualDouble);
    }
		
    /*!
     * @brief front()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>�����оݤ�NVList�����ǿ������ξ�硢�㳰����������뤫��</li>
     * <li>�����оݤ�NVList�����ǿ������ʾ�ξ�硢��Ƭ�����Ǥ�����Ǥ��뤫��</li>
     * </ul>
     */
    void test_front()
    {
      // (1) �����оݤ�NVList�����ǿ������ξ�硢�㳰����������뤫
      NVList nvlistEmpty;
      try {
	CORBA_SeqUtil::front<NVList, NameValue>(nvlistEmpty);
	CPPUNIT_FAIL("Exception must be thrown.");
      } catch (...) {
	// expected
      }
			
      // (2) �����оݤ�NVList�����ǿ������ʾ�ξ�硢��Ƭ�����Ǥ�����Ǥ��뤫��
      NVList nvlist;
      nvlist.length(4);
			
      NameValue nvShort;
      nvShort.name = "short";
      nvShort.value <<= (CORBA::Short) 123;
      nvlist[0] = nvShort;
			
      NameValue nvLong;
      nvLong.name = "long";
      nvLong.value <<= (CORBA::Long) 123456;
      nvlist[1] = nvLong;
			
      NameValue nvFloat;
      nvFloat.name = "float";
      nvFloat.value <<= (CORBA::Float) 987.654;
      nvlist[2] = nvFloat;
			
      NameValue nvDouble;
      nvDouble.name = "double";
      nvDouble.value <<= (CORBA::Double) 987654.321987;
      nvlist[3] = nvDouble;
			
      // ��Ƭ�����Ǥ�������ơ������ͤ���Ӥ��ƥ����å�����
      NameValue nvFront = CORBA_SeqUtil::front<NVList, NameValue>(nvlist);
			
      CPPUNIT_ASSERT_EQUAL((string) "short", (string) nvFront.name);
			
      CORBA::Short actualValue;
      nvFront.value >>= actualValue;
      CPPUNIT_ASSERT_EQUAL((CORBA::Short) 123, actualValue);
    }
		
    /*!
     * @brief back()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>�����оݤ�NVList�����ǿ������ξ�硢�㳰����������뤫��</li>
     * <li>�����оݤ�NVList�����ǿ������ʾ�ξ�硢�Ǹ��������Ǥ�����Ǥ��뤫��</li>
     * </ul>
     */
    void test_back()
    {
      // (1) �����оݤ�NVList�����ǿ������ξ�硢�㳰����������뤫��
      NVList nvlistEmpty;
      try {
	CORBA_SeqUtil::back<NVList, NameValue>(nvlistEmpty);
	CPPUNIT_FAIL("Exception must be thrown.");
      } catch (...) {
	// expected
      }
			
      // (2) �����оݤ�NVList�����ǿ������ʾ�ξ�硢�Ǹ��������Ǥ�����Ǥ��뤫��
      NVList nvlist;
      nvlist.length(4);
			
      NameValue nvShort;
      nvShort.name = "short";
      nvShort.value <<= (CORBA::Short) 123;
      nvlist[0] = nvShort;
			
      NameValue nvLong;
      nvLong.name = "long";
      nvLong.value <<= (CORBA::Long) 123456;
      nvlist[1] = nvLong;
			
      NameValue nvFloat;
      nvFloat.name = "float";
      nvFloat.value <<= (CORBA::Float) 987.654;
      nvlist[2] = nvFloat;
			
      NameValue nvDouble;
      nvDouble.name = "double";
      nvDouble.value <<= (CORBA::Double) 987654.321987;
      nvlist[3] = nvDouble;

      // �Ǹ�����Ǥ�������ơ������ͤ���Ӥ��ƥ����å�����
      NameValue nvBack = CORBA_SeqUtil::back<NVList, NameValue>(nvlist);
			
      CPPUNIT_ASSERT_EQUAL((string) "double", (string) nvBack.name);
			
      CORBA::Double actualValue;
      nvBack.value >>= actualValue;
      CPPUNIT_ASSERT_EQUAL((CORBA::Double) 987654.321987, actualValue);
    }
		
    /*!
     * @brief erase()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>��Ƭ�����ǤΤߤ���������硢¾���ǤϤ��Τޤ��ݤ���뤫��</li>
     * <li>��֤����ǤΤߤ���������硢¾���ǤϤ��Τޤ��ݤ���뤫��</li>
     * <li>�Ǹ��������ǤΤߤ���������硢¾���ǤϤ��Τޤ��ݤ���뤫��</li>
     * </ul>
     */
    void test_erase()
    {
      // �ƥ����Ѥ�NVList���������
      NVList nvlist1, nvlist2, nvlist3;
      nvlist1.length(4);
      nvlist2.length(4);
      nvlist3.length(4);
			
      NameValue nvShort;
      nvShort.name = "short";
      nvShort.value <<= (CORBA::Short) 123;
      nvlist1[0] = nvShort;
      nvlist2[0] = nvShort;
      nvlist3[0] = nvShort;
			
      NameValue nvLong;
      nvLong.name = "long";
      nvLong.value <<= (CORBA::Long) 123456;
      nvlist1[1] = nvLong;
      nvlist2[1] = nvLong;
      nvlist3[1] = nvLong;
			
      NameValue nvFloat;
      nvFloat.name = "float";
      nvFloat.value <<= (CORBA::Float) 987.654;
      nvlist1[2] = nvFloat;
      nvlist2[2] = nvFloat;
      nvlist3[2] = nvFloat;
			
      NameValue nvDouble;
      nvDouble.name = "double";
      nvDouble.value <<= (CORBA::Double) 987654.321987;
      nvlist1[3] = nvDouble;
      nvlist2[3] = nvDouble;
      nvlist3[3] = nvDouble;
			
      // (1) ��Ƭ�����ǤΤߤ���������硢¾���ǤϤ��Τޤ��ݤ���뤫��
      CORBA_SeqUtil::erase(nvlist1, 0);
      CPPUNIT_ASSERT_EQUAL((CORBA::ULong) 3, nvlist1.length());
      CPPUNIT_ASSERT_EQUAL((string) "long", (string) nvlist1[0].name);
      CPPUNIT_ASSERT_EQUAL((string) "float", (string) nvlist1[1].name);
      CPPUNIT_ASSERT_EQUAL((string) "double", (string) nvlist1[2].name);
			
      CORBA::Long actualLong1;
      nvlist1[0].value >>= actualLong1;
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 123456, actualLong1);

      CORBA::Float actualFloat1;
      nvlist1[1].value >>= actualFloat1;
      CPPUNIT_ASSERT_EQUAL((CORBA::Float) 987.654, actualFloat1);

      CORBA::Double actualDouble1;
      nvlist1[2].value >>= actualDouble1;
      CPPUNIT_ASSERT_EQUAL((CORBA::Double) 987654.321987, actualDouble1);
			
      // (2) ��֤����ǤΤߤ���������硢¾���ǤϤ��Τޤ��ݤ���뤫��
      CORBA_SeqUtil::erase(nvlist2, 1);
      CPPUNIT_ASSERT_EQUAL((CORBA::ULong) 3, nvlist2.length());
      CPPUNIT_ASSERT_EQUAL((string) "short", (string) nvlist2[0].name);
      CPPUNIT_ASSERT_EQUAL((string) "float", (string) nvlist2[1].name);
      CPPUNIT_ASSERT_EQUAL((string) "double", (string) nvlist2[2].name);
			
      CORBA::Short actualShort2;
      nvlist2[0].value >>= actualShort2;
      CPPUNIT_ASSERT_EQUAL((CORBA::Short) 123, actualShort2);

      CORBA::Float actualFloat2;
      nvlist2[1].value >>= actualFloat2;
      CPPUNIT_ASSERT_EQUAL((CORBA::Float) 987.654, actualFloat2);

      CORBA::Double actualDouble2;
      nvlist2[2].value >>= actualDouble2;
      CPPUNIT_ASSERT_EQUAL((CORBA::Double) 987654.321987, actualDouble2);

      // (3) �Ǹ��������ǤΤߤ���������硢¾���ǤϤ��Τޤ��ݤ���뤫��
      CORBA_SeqUtil::erase(nvlist3, 3);
      CPPUNIT_ASSERT_EQUAL((CORBA::ULong) 3, nvlist3.length());
      CPPUNIT_ASSERT_EQUAL((string) "short", (string) nvlist3[0].name);
      CPPUNIT_ASSERT_EQUAL((string) "long", (string) nvlist3[1].name);
      CPPUNIT_ASSERT_EQUAL((string) "float", (string) nvlist3[2].name);
			
      CORBA::Short actualShort3;
      nvlist3[0].value >>= actualShort3;
      CPPUNIT_ASSERT_EQUAL((CORBA::Short) 123, actualShort3);

      CORBA::Long actualLong3;
      nvlist3[1].value >>= actualLong3;
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 123456, actualLong3);

      CORBA::Float actualFloat3;
      nvlist3[2].value >>= actualFloat3;
      CPPUNIT_ASSERT_EQUAL((CORBA::Float) 987.654, actualFloat3);
    }

    /*!
     * @brief test_erase_if()�ǻ��Ѥ���ե��󥯥�
     */
    struct functor_erase_if
    {
      functor_erase_if(const char* name)
	: _name(name) {}
			
      bool operator()(const NameValue& nv)
      {
	return _name == std::string(nv.name);
      }
			
      string _name;
    };
		
    /*!
     * @brief erase_if()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>���˹��פ������Ǥ��ʤ���硢���������줺���ݤ���뤫��</li>
     * <li>���˹��פ������Ǥ������硢�������Ǥ�������졢¾���Ǥ��ݤ���뤫��</li>
     * </ul>
     */
    void test_erase_if()
    {
      NVList nvlist1, nvlist2;
      nvlist1.length(4);
      nvlist2.length(4);
			
      NameValue nvShort;
      nvShort.name = "short";
      nvShort.value <<= (CORBA::Short) 123;
      nvlist1[0] = nvShort;
      nvlist2[0] = nvShort;
			
      NameValue nvLong;
      nvLong.name = "long";
      nvLong.value <<= (CORBA::Long) 123456;
      nvlist1[1] = nvLong;
      nvlist2[1] = nvLong;
			
      NameValue nvFloat;
      nvFloat.name = "float";
      nvFloat.value <<= (CORBA::Float) 987.654;
      nvlist1[2] = nvFloat;
      nvlist2[2] = nvFloat;
			
      NameValue nvDouble;
      nvDouble.name = "double";
      nvDouble.value <<= (CORBA::Double) 987654.321987;
      nvlist1[3] = nvDouble;
      nvlist2[3] = nvDouble;
			
      // (1) ���˹��פ������Ǥ��ʤ���硢���������줺���ݤ���뤫��
      CORBA_SeqUtil::erase_if(nvlist1, functor_erase_if("no-match-name"));
			
      CPPUNIT_ASSERT_EQUAL((string) "short", (string) nvlist1[0].name);
      CPPUNIT_ASSERT_EQUAL((string) "long", (string) nvlist1[1].name);
      CPPUNIT_ASSERT_EQUAL((string) "float", (string) nvlist1[2].name);
      CPPUNIT_ASSERT_EQUAL((string) "double", (string) nvlist1[3].name);
			
      CORBA::Short actualShort1;
      nvlist1[0].value >>= actualShort1;
      CPPUNIT_ASSERT_EQUAL((CORBA::Short) 123, actualShort1);
			
      CORBA::Long actualLong1;
      nvlist1[1].value >>= actualLong1;
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 123456, actualLong1);

      CORBA::Float actualFloat1;
      nvlist1[2].value >>= actualFloat1;
      CPPUNIT_ASSERT_EQUAL((CORBA::Float) 987.654, actualFloat1);

      CORBA::Double actualDouble1;
      nvlist1[3].value >>= actualDouble1;
      CPPUNIT_ASSERT_EQUAL((CORBA::Double) 987654.321987, actualDouble1);
			
      // (2) ���˹��פ������Ǥ������硢�������Ǥ�������졢¾���Ǥ��ݤ���뤫��
      CORBA_SeqUtil::erase_if(nvlist2, functor_erase_if("float"));
			
      CPPUNIT_ASSERT_EQUAL((string) "short", (string) nvlist2[0].name);
      CPPUNIT_ASSERT_EQUAL((string) "long", (string) nvlist2[1].name);
      CPPUNIT_ASSERT_EQUAL((string) "double", (string) nvlist2[2].name);
			
      CORBA::Short actualShort2;
      nvlist2[0].value >>= actualShort2;
      CPPUNIT_ASSERT_EQUAL((CORBA::Short) 123, actualShort2);
			
      CORBA::Long actualLong2;
      nvlist2[1].value >>= actualLong2;
      CPPUNIT_ASSERT_EQUAL((CORBA::Long) 123456, actualLong2);

      CORBA::Double actualDouble2;
      nvlist2[2].value >>= actualDouble2;
      CPPUNIT_ASSERT_EQUAL((CORBA::Double) 987654.321987, actualDouble2);
    }
		
    /*!
     * @brief clear()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>���ꥢ�ˤ�����ǿ������ˤʤ뤫��</li>
     * </ul>
     */
    void test_clear()
    {
      // �ƥ����Ѥ�NVList���������
      NVList nvlist;
      nvlist.length(4);
			
      NameValue nvShort;
      nvShort.name = "short";
      nvShort.value <<= (CORBA::Short) 123;
      nvlist[0] = nvShort;
			
      NameValue nvLong;
      nvLong.name = "long";
      nvLong.value <<= (CORBA::Long) 123456;
      nvlist[1] = nvLong;
			
      NameValue nvFloat;
      nvFloat.name = "float";
      nvFloat.value <<= (CORBA::Float) 987.654;
      nvlist[2] = nvFloat;
			
      NameValue nvDouble;
      nvDouble.name = "double";
      nvDouble.value <<= (CORBA::Double) 987654.321987;
      nvlist[3] = nvDouble;
			
      // clear()��ƽФ������ꥢ���줿���ȡ����ǿ����ˤʤä����ȡˤ��ǧ����
      CORBA_SeqUtil::clear(nvlist);
      CPPUNIT_ASSERT_EQUAL((CORBA::ULong) 0, nvlist.length());
    }
    
    /*!
     * @brief refToVstring()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>���֥������ȥ�ե���󥹤�ʸ�����֤���뤫��</li>
     * </ul>
     */
    void test_refToVstring()
    {
      int argc(0);
      char** argv(NULL);
      CORBA::ORB_ptr m_pORB = CORBA::ORB_init(argc, argv);
      PortableServer::POA_ptr m_pPOA = 
          PortableServer::POA::_narrow(m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();

      RTC::PortAdmin portAdmin(m_pORB, m_pPOA);
      PortMock* port0 = new PortMock();
      port0->setName("port0");
      CPPUNIT_ASSERT_EQUAL(true, portAdmin.addPort(*port0));

      RTC::PortService_var portRef0 = portAdmin.getPortRef("port0");
      RTC::ConnectorProfile cprof;
      cprof.connector_id = "id";
      cprof.name = CORBA::string_dup("Test");

      CORBA_SeqUtil::push_back(cprof.properties,
                               NVUtil::newNV("dataport.interface_type",
					     "corba_cdr"));
      CORBA_SeqUtil::push_back(cprof.properties,
                               NVUtil::newNV("dataport.dataflow_type",
					     "push"));
      CORBA_SeqUtil::push_back(cprof.properties,
                               NVUtil::newNV("dataport.subscription_type",
					     "flush"));
      cprof.ports.length(1);
      cprof.ports[0] = portRef0;
      coil::vstring str;
      str = CORBA_SeqUtil::refToVstring(cprof.ports);
      int len = str.size();
      int pos = str[0].find("IOR", 0);
      CPPUNIT_ASSERT_EQUAL(1, len);
      CPPUNIT_ASSERT(pos != string::npos);

//      delete port0;
      // PortBase �ǥ��ȥ饯���ǡ�deactivate_object ��¹Ԥ��Ƥ��ޤ���
    }
    
  };
}; // namespace CORBA_SeqUtil

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(CORBA_SeqUtil::CORBA_SeqUtilTests);

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
#endif // CORBA_SeqUtil_cpp
