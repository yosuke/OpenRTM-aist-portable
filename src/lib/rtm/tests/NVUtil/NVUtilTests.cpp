// -*- C++ -*-
/*!
 * @file   NVUtilTests.cpp
 * @brief  NVUtil test class
 * @date   $Date: 2008/03/03 12:24:24 $
 * @author Shinji Kurihara
 *         Noriaki Ando <n-ando@aist.go.jp>
 * 
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NVUtilTests.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

/*
 * $Log: NVUtilTests.cpp,v $
 * Revision 1.5  2008/03/03 12:24:24  arafune
 * Added some tests.
 *
 * Revision 1.4  2008/01/24 01:51:58  tsakamoto
 * *** empty log message ***
 *
 * Revision 1.3  2007/12/27 10:28:16  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/12/25 12:13:38  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2006/11/27 08:26:13  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.3  2006/11/15 09:47:18  kurihara
 * tests for find(),isString(),toString() are added.
 *
 * Revision 1.1  2006/11/14 07:23:16  kurihara
 * test program for NVUtil module. first commit.
 *
 */

#ifndef NVUtil_cpp
#define NVUtil_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/NVUtil.h>

namespace NVUtil
{
  using namespace NVUtil;
  using namespace std;

  int g_argc;
  vector<string> g_argv;
  
  /*!
   * @class NVUtilTests class
   * @brief NVUtil Test
   */
  class NVUtilTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(NVUtilTests);
    CPPUNIT_TEST(test_newNV_Short);
    CPPUNIT_TEST(test_newNV_Long);
    CPPUNIT_TEST(test_newNV_Float);
    CPPUNIT_TEST(test_newNV_Double);
    CPPUNIT_TEST(test_newNV_Str);
    CPPUNIT_TEST(test_newNVChar);
    CPPUNIT_TEST(test_newNVBool);
    CPPUNIT_TEST(test_newNVOctet);
    CPPUNIT_TEST(test_copy);
    CPPUNIT_TEST(test_toProperties);
    CPPUNIT_TEST(test_copyToProperties);
    CPPUNIT_TEST(test_find);
    CPPUNIT_TEST(test_find_index);
    CPPUNIT_TEST(test_isString);
    CPPUNIT_TEST(test_isStringValue);
    CPPUNIT_TEST(test_toString);
    CPPUNIT_TEST(test_appendStringValue);
    CPPUNIT_TEST(test_append);
    CPPUNIT_TEST(test_dump);
    CPPUNIT_TEST(test_toStringNV);
    CPPUNIT_TEST_SUITE_END();

  private:

  public:
    NVUtilTests()
    {
      CORBA::ORB_var orb;
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }
	      
      orb = CORBA::ORB_init(g_argc, argv);
    }

    ~NVUtilTests()
    {
    }

    virtual void setUp()
    {
    }
    
    virtual void tearDown()
    { 
    }

    /*!
     * @brief newNV(char*,Value)�Υƥ���
     * 
     * - CORBA::Short���ǡ�����NameValue�������������Ǥ��뤫��
     */
    void test_newNV_Short()
    {
      // CORBA::Short���Υǡ��������NameValue�����������ͤ���Ӥ�����������������Ƥ��뤳�Ȥ��ǧ����
      CORBA::Short value = 1;
      string name = "short";
      SDOPackage::NameValue nv = newNV(name.c_str(), value);
      
      string nvName(nv.name);
      CPPUNIT_ASSERT_EQUAL(name, nvName);

      CORBA::Short nvValue;
      nv.value >>= nvValue;
      CPPUNIT_ASSERT_EQUAL(value, nvValue);
    }

    /*!
     * @brief newNV(char*,Value)�Υƥ���
     * 
     * - CORBA::Long���ǡ�����NameValue�������������Ǥ��뤫��
     */
    void test_newNV_Long()
    {
      // CORBA::Long���Υǡ��������NameValue�����������ͤ���Ӥ�����������������Ƥ��뤳�Ȥ��ǧ����
      CORBA::Long value = 999999999;
      string name = "long";
      SDOPackage::NameValue nv = newNV(name.c_str(), value);
      
      string nvName(nv.name);
      CPPUNIT_ASSERT_EQUAL(name, nvName);

      CORBA::Long nvValue;
      nv.value >>= nvValue;
      CPPUNIT_ASSERT_EQUAL(value, nvValue);
    }

    /*!
     * @brief newNV(char*,Value)�Υƥ���
     * 
     *  - CORBA::Float���ǡ�����NameValue�������������Ǥ��뤫��
     */
    void test_newNV_Float()
    {
      // CORBA::Float���Υǡ��������NameValue�����������ͤ���Ӥ�����������������Ƥ��뤳�Ȥ��ǧ����
      CORBA::Float value = 99999.9;
      string name = "float";
      SDOPackage::NameValue nv = newNV(name.c_str(), value);
      
      string nvName(nv.name);
      CPPUNIT_ASSERT_EQUAL(name, nvName);

      CORBA::Float nvValue;
      nv.value >>= nvValue;
      CPPUNIT_ASSERT_EQUAL(value, nvValue);
    }

    /*!
     * @brief newNV(char*,Value)�Υƥ���
     * 
     * - CORBA::Double���ǡ�����NameValue�������������Ǥ��뤫��
     */
    void test_newNV_Double()
    {
      // CORBA::Double���Υǡ��������NameValue�����������ͤ���Ӥ�����������������Ƥ��뤳�Ȥ��ǧ����
      CORBA::Double value = 9999999.999;
      string name = "double";
      SDOPackage::NameValue nv = newNV(name.c_str(), value);
      
      string nvName(nv.name);
      CPPUNIT_ASSERT_EQUAL(name, nvName);

      CORBA::Double nvValue;
      nv.value >>= nvValue;
      CPPUNIT_ASSERT_EQUAL(value, nvValue);
    }
    
    /*!
     * @brief newNV(const char*, const char*)�Υƥ���
     * 
     * - const char*���ǡ�����NameValue�������������Ǥ��뤫��
     */
    void test_newNV_Str()
    {
      // (1) CORBA::String_var����value��char*����name��newNV()���Ϥ���NameValue���������
      string name = "string";
      CORBA::String_var value = CORBA::string_dup("Hello, world!");
      SDOPackage::NameValue nv = newNV(name.c_str(), value);
    	
      // (2) newNV()�˥��åȤ���name�ȡ���������NameValue.name����Ӥ���
      string nvName(nv.name);
      CPPUNIT_ASSERT_EQUAL(name, nvName);
    	
      // (3) newNV()�˥��åȤ���value�ȡ���������NameValue.value����Ӥ���
      //    	CORBA::String_var nvValue;
      const char* nvValue;
      nv.value >>= nvValue;
      CPPUNIT_ASSERT_EQUAL(string("Hello, world!"), string(nvValue));
    }
    
    /*!
     * @brief newNVChar()�Υƥ���
     * 
     * - CORBA::Char���ǡ�����NameValue�������������Ǥ��뤫��
     */
    void test_newNVChar()
    {
      // (1) CORBA::Char����value��char*����name��newNVChar()���Ϥ���NameValue��������롣
      string name = "char";
      CORBA::Char value = 'A';
      SDOPackage::NameValue nv = newNVChar(name.c_str(), value);
      
      // (2) newNVChar()�˥��åȤ���name�ȼ�������NameValue.name����ӡ�
      string nvName(nv.name);
      CPPUNIT_ASSERT_EQUAL(name, nvName);
      
      // (3) newNVChar()�˥��åȤ���value�ȼ�������NameValue.value����ӡ�
      CORBA::Char nvValue;
      nv.value >>= CORBA::Any::to_char(nvValue);
      CPPUNIT_ASSERT_EQUAL(value, nvValue);
    }
    
    /*!
     * @brief newNVBool()�Υƥ���
     * 
     * - CORBA::Boolean���ǡ�����NameValue�������������Ǥ��뤫��
     */
    void test_newNVBool()
    {
      string name = "bool";
      CORBA::Boolean value = false;
      SDOPackage::NameValue nv = newNVBool(name.c_str(), value);
      
      string nvName(nv.name);
      CPPUNIT_ASSERT_EQUAL(name, nvName);
      
      CORBA::Boolean nvValue;
      nv.value >>= CORBA::Any::to_boolean(nvValue);
      CPPUNIT_ASSERT_EQUAL(value, nvValue);
    }

    /*!
     * @brief newNVOctet()�Υƥ���
     * 
     * - CORBA::Octet���ǡ�����NameValue�������������Ǥ��뤫��
     */
    void test_newNVOctet()
    {
      string name = "octet";
      CORBA::Octet value = 030;
      SDOPackage::NameValue nv = newNVOctet(name.c_str(), value);
      
      string nvName(nv.name);
      CPPUNIT_ASSERT_EQUAL(name, nvName);
      
      CORBA::Octet nvValue;
      nv.value >>= CORBA::Any::to_octet(nvValue);
      CPPUNIT_ASSERT_EQUAL(value, nvValue);
    }
    
    /*!
     * @brief copy()�Υƥ���
     * 
     * - RTC::Properties�����Ƥ���������NVList�˥��ԡ��Ǥ��뤫��
     */
    void test_copy()
    {
      // (1) RTC::Properties���֥������Ȥ�����
      // �� Properties�Υ��󥹥ȥ饯���Ǥϰ�����Ϳ����줿map�Υ����ͤ�������¸����롣
      string name = "port-type";
      string value = "port-type-value";
      map<string, string> mProp;
      mProp[name] = value;
      coil::Properties prop(mProp);
      
      // (2��copy()�ˤ�Properties���֥������Ȥ�nvlist�˥��ԡ�
      SDOPackage::NVList nvlist;
      copyFromProperties(nvlist, prop);
      
      // (3) copy()�ˤ�������Ϳ����nvlist���񤭴������Ƥ��뤫���ǧ��
      string nvName(nvlist[0].name);
      CPPUNIT_ASSERT_EQUAL(name, nvName);
      
      const char* getval;
      nvlist[0].value >>= getval;
      string nvValue(getval);
      CPPUNIT_ASSERT_EQUAL(value, nvValue);
    }

    /*!
     * @brief toProperties()�Υƥ���
     * 
     * - NVList�����Ƥ�������RTC::Properties���Ѵ��Ǥ��뤫��
     */
    void test_toProperties()
    {
      // (1) �Ѵ����Ȥʤ�NVList���֥������Ȥ���������
      SDOPackage::NVList nvlist;		    	
      nvlist.length(2);
    	
      string name1 = "testname.test1";
      string value1 = "testval1";
      nvlist[0].name = name1.c_str();
      nvlist[0].value <<= value1.c_str();
			
      string name2 = "testname.test2";
      string value2 = "testval2";
      nvlist[1].name = name2.c_str();
      nvlist[1].value <<= value2.c_str();
			
      // (2) RTC::Properties���Ѵ�����
      coil::Properties prop = toProperties(nvlist);
			
      // (3) �������Ѵ�����Ƥ��뤳�Ȥ��ǧ����
      string propValue1 = prop.getProperty(name1);
      CPPUNIT_ASSERT_EQUAL(value1, propValue1);
			
      string propValue2 = prop.getProperty(name2);
      CPPUNIT_ASSERT_EQUAL(value2, propValue2);
    }

    /*!
     * @brief copyToProperties()�Υƥ���
     * 
     * - NVList�����Ƥ�������RTC::Properties�˥��ԡ��Ǥ��뤫��
     */
    void test_copyToProperties()
    {
      // (1) ���ԡ����Ȥʤ�NVList���֥������Ȥ���������
      SDOPackage::NVList nvlist;
      nvlist.length(2);

      string name1 = "testname.test1";
      string value1 = "testval1";
      nvlist[0].name = name1.c_str();
      nvlist[0].value <<= value1.c_str();
			
      string name2 = "testname.test2";
      string value2 = "testval2";
      nvlist[1].name = name2.c_str();
      nvlist[1].value <<= value2.c_str();

      // (2) RTC::Properties�إ��ԡ�����
      coil::Properties prop;
      copyToProperties(prop, nvlist);
    	
      // (3) �ͤ���Ӥ��ơ����������ԡ�����Ƥ��뤳�Ȥ��ǧ����
      string propValue1 = prop.getProperty(name1);
      CPPUNIT_ASSERT_EQUAL(value1, propValue1);
      string propValue2 = prop.getProperty(name2);
      CPPUNIT_ASSERT_EQUAL(value2, propValue2);
    }
    
    /*!
     * @brief find()�Υƥ���
     * 
     * - ���ꤷ��̾�Τ�NVList����ͤ������������Ǥ��뤫��
     */
    void test_find()
    {
      SDOPackage::NVList nvlist;
      nvlist.length(2);
      
      // (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
      string name1 = "short";
      CORBA::Short value1 = 1;
      nvlist[0].name = name1.c_str();
      nvlist[0].value <<= value1;
      
      // (2) NVList���Ǥ�name��"long",value��long���Υǡ����򥻥åȡ�
      string name2 = "long";
      CORBA::Long value2 = 111;
      nvlist[1].name = name2.c_str();
      nvlist[1].value <<= value2;

      // (3) nvlist���椫��NameValue.name��"long"��NameValue.value�򸡺����ơ��������ͤ�����Ǥ��뤳�Ȥ��ǧ���롣
      CORBA::Short foundValue1;
      (find(nvlist, name1.c_str())) >>= foundValue1;
      CPPUNIT_ASSERT_EQUAL(value1, foundValue1);
      
      // (4) nvlist���椫��NameValue.name��"short"��NameValue.value�򸡺����ơ��������ͤ�����Ǥ��뤳�Ȥ��ǧ���롣
      CORBA::Long foundValue2;
      (find(nvlist, name2.c_str())) >>= foundValue2;
      CPPUNIT_ASSERT_EQUAL(value2, foundValue2);
    }
    
    /*!
     * @brief find_index()�Υƥ���
     * 
     * - ���ꤷ��̾�Τ�NVList��������ֹ�������������Ǥ��뤫��
     */
    void test_find_index()
    {
      SDOPackage::NVList nvlist;
      nvlist.length(2);
      
      // (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
      string name1 = "short";
      CORBA::Short value1 = 1;
      nvlist[0].name = name1.c_str();
      nvlist[0].value <<= value1;
      
      // (2) NVList���Ǥ�name��"long",value��long���Υǡ����򥻥åȡ�
      string name2 = "long";
      CORBA::Long value2 = 111;
      nvlist[1].name = name2.c_str();
      nvlist[1].value <<= value2;

      // (3) nvlist���椫��NameValue.name��"long"��NameValue.value�򸡺����ơ������ֹ������Ǥ��뤳�Ȥ��ǧ���롣
      CORBA::Long ret;
      ret = find_index(nvlist, name1.c_str());
      CPPUNIT_ASSERT_EQUAL((CORBA::Long)0, ret);
      
      // (4) nvlist���椫��NameValue.name��"short"��NameValue.value�򸡺����ơ������ֹ������Ǥ��뤳�Ȥ��ǧ���롣
      ret = find_index(nvlist, name2.c_str());
      CPPUNIT_ASSERT_EQUAL((CORBA::Long)1, ret);
    }
    
    /*!
     * @brief isString()�Υƥ���
     * 
     *  - NVList��λ��ꤷ��̾�Τ�����ͤ�string�����ɤ�����������Ƚ��Ǥ��뤫��
     */
    void test_isString()
    {
      SDOPackage::NVList nvlist;
      nvlist.length(2);
      
      // (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
      string name1 = "short";
      CORBA::Short value1 = 1;
      nvlist[0].name = name1.c_str();
      nvlist[0].value <<= value1;
      
      // (2) NVList���Ǥ�name��"string",value��string���Υǡ����򥻥åȡ�
      string name2 = "string";
      string value2 = "test";
      nvlist[1].name = name2.c_str();
      nvlist[1].value <<= value2.c_str();
      
      // (3) isString(nvlist,name)�ˤ�,���ꤵ�줿name��value�η���string���ɤ�����Ƚ�ꡣ
      CPPUNIT_ASSERT(!isString(nvlist, name1.c_str()));
      CPPUNIT_ASSERT(isString(nvlist, name2.c_str()));
    }

    /*!
     * @brief isStringValue()�Υƥ���
     * 
     *  - NVList��λ��ꤷ��̾�Τ�����ͤ�string�����ɤ�����������Ƚ��Ǥ��뤫��
     */
    void test_isStringValue()
    {
      SDOPackage::NVList nvlist;
      nvlist.length(2);
      
      // (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
      string name1 = "short";
      CORBA::Short value1 = 1;
      nvlist[0].name = name1.c_str();
      nvlist[0].value <<= value1;
      
      // (2) NVList���Ǥ�name��"string",value��string���Υǡ����򥻥åȡ�
      string name2 = "string";
      string value2 = "test";
      nvlist[1].name = name2.c_str();
      nvlist[1].value <<= value2.c_str();
      
      // (3) isString(nvlist,name)�ˤ�,���ꤵ�줿name��value�η���string���ɤ�����Ƚ�ꡣ
      CPPUNIT_ASSERT(!isStringValue(nvlist, name1.c_str(), "1"));
      CPPUNIT_ASSERT(isStringValue(nvlist, name2.c_str(), "test"));
    }

    /*!
     * @brief toString()�Υƥ���
     * 
     * - NVList��λ��ꤷ��̾�Τ�����ͤ�string���Ǥ�����ˡ������ͤ������������Ǥ��뤫��
     */
    void test_toString() {

			
      SDOPackage::NVList nvlist;
      nvlist.length(2);
			
      // (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
      string name1 = "short";
      CORBA::Short value1 = 1;
      nvlist[0].name = name1.c_str();
      nvlist[0].value <<= value1;
			
      // (2) NVList���Ǥ�name��"string",value��string���Υǡ����򥻥åȡ�
      string name2 = "string";
      string value2 = "test";
      nvlist[1].name = name2.c_str();
      nvlist[1].value <<= value2.c_str();
			
      // (3) toString(nvlist,name)�ˤ�,���ꤵ�줿name��value��string���ǰտޤȤ���˼����Ǥ��뤫��
      string empty("");
      CPPUNIT_ASSERT_EQUAL(empty, toString(nvlist, name1.c_str()));
      CPPUNIT_ASSERT_EQUAL(value2, toString(nvlist, name2.c_str()));
    }

    /*!
     * @brief appendStringValue()�Υƥ���
     * 
     * - ���ꤷ��̾�Τ��ͤ����NameValue��NVList���������ɲäǤ��뤫��
     */
    void test_appendStringValue()
    {

      SDOPackage::NVList nvlist;
      nvlist.length(3);
			
      // (1) �ɲ��оݤȤʤ�NVList���������
      string name1 = "language";
      string value1 = "japanese";
      nvlist[0].name = name1.c_str();
      nvlist[0].value <<= value1.c_str();
			
      string name2 = "fruit";
      string value2 = "apple";
      nvlist[1].name = name2.c_str();
      nvlist[1].value <<= value2.c_str();
			
      string name3 = "drink";
      string value3 = "coffee, coke";
      nvlist[2].name = name3.c_str();
      nvlist[2].value <<= value3.c_str();
			
      // (2) ��������NVList�ˡ�̾��"os", ��"unix"��NameValue���������ɲäǤ��뤫��
      string name4 = "os";
      string value4 = "unix";
      CPPUNIT_ASSERT(appendStringValue(nvlist, name4.c_str(), value4.c_str()));
      CPPUNIT_ASSERT_EQUAL(value4, toString(nvlist, name4.c_str()));
			
      // (3) ��¸��̾�ΤǤ���"language"�ˡ���"english"���������ɲäǤ��뤫��
      string name5 = name1;
      string value5 = "english";
      CPPUNIT_ASSERT(appendStringValue(nvlist, name5.c_str(), value5.c_str()));
      string expectedValueLanguage = "japanese,english";
      CPPUNIT_ASSERT_EQUAL(expectedValueLanguage, toString(nvlist, name5.c_str()));
			
      // (4) ��¸��̾�Ρ��ͤ�����Ʊ���NameValue���ɲä��褦�Ȥ����Ȥ��ˡ��տޤɤ��겿���ɲä����˽�λ���뤫��
      string name6 = name2;
      string value6 = value2;
      CPPUNIT_ASSERT(appendStringValue(nvlist, name6.c_str(), value6.c_str()));
      CPPUNIT_ASSERT_EQUAL(value2, toString(nvlist, name6.c_str()));
			
      // (5) �������ͤ�����¸���ͤȽ�ʣ����NameValue���ɲä��褦�Ȥ������ˡ��տޤɤ���˥ޡ�������뤫��
      string name7 = name3;
      string value7 = "coke, beer";
      CPPUNIT_ASSERT(appendStringValue(nvlist, name7.c_str(), value7.c_str()));
      string expectedValueDrink = "coffee, coke,coke, beer";
      CPPUNIT_ASSERT_EQUAL(expectedValueDrink, toString(nvlist, name7.c_str()));
    }

    /*!
     * @brief append()�Υƥ���
     * 
     * - NVList�����Ƥ�¾��NVList���������ɲäǤ��뤫��
     */
    void test_append()
    {
      // (1) 1���ܤ�NVList���������
      SDOPackage::NVList nvlistA;
      nvlistA.length(2);
			
      string nameA1 = "nameA1";
      string valueA1 = "valueA1";
      nvlistA[0].name = nameA1.c_str();
      nvlistA[0].value <<= valueA1.c_str();
			
      string nameA2 = "nameA2";
      string valueA2 = "valueA2";
      nvlistA[1].name = nameA2.c_str();
      nvlistA[1].value <<= valueA2.c_str();
			
      // (2) 2���ܤ�NVList���������
      SDOPackage::NVList nvlistB;
      nvlistB.length(2);
			
      string nameB1 = "nameB1";
      string valueB1 = "valueB1";
      nvlistB[0].name = nameB1.c_str();
      nvlistB[0].value <<= valueB1.c_str();
			
      string nameB2 = "nameB2";
      string valueB2 = "valueB2";
      nvlistB[1].name = nameB2.c_str();
      nvlistB[1].value <<= valueB2.c_str();
			
      // (3) 1���ܤ�NVList�ˡ�2���ܤ�NVList���ɲä���
      append(nvlistA, nvlistB);
			
      // (4) �������ɲä��줿���Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(valueA1, toString(nvlistA, nameA1.c_str()));
      CPPUNIT_ASSERT_EQUAL(valueA2, toString(nvlistA, nameA2.c_str()));
      CPPUNIT_ASSERT_EQUAL(valueB1, toString(nvlistA, nameB1.c_str()));
      CPPUNIT_ASSERT_EQUAL(valueB2, toString(nvlistA, nameB2.c_str()));
    }
    void test_dump()
    { 
      SDOPackage::NVList nvlistC;
      nvlistC.length(3);
			
      string nameC1 = "nameC1";
      string valueC1 = "valueC1";
      nvlistC[0].name = nameC1.c_str();
      nvlistC[0].value <<= valueC1.c_str();
			
      string nameC2 = "nameC2";
      string valueC2 = "valueC2";
      nvlistC[1].name = nameC2.c_str();
      nvlistC[1].value <<= valueC2.c_str();

      string nameC3 = "name_hoge";
      string valueC3 = "value_hoge";
      nvlistC[2].name = nameC3.c_str();
      nvlistC[2].value <<= valueC3.c_str();
     

      dump(nvlistC);
    }	

    // std::string toString(const SDOPackage::NVList& nv);�Υƥ��ȤǤ���
    void test_toStringNV()
    {
      SDOPackage::NVList nvlistD;
      nvlistD.length(2);
			
      string nameD1 = "nameD1";
      string valueD1 = "valueD1";
      nvlistD[0].name = nameD1.c_str();
      nvlistD[0].value <<= valueD1.c_str();
			
      string nameD2 = "nameD2";
      string valueD2 = "valueD2";
      nvlistD[1].name = nameD2.c_str();
      nvlistD[1].value <<= valueD2.c_str();
 
      string strD ="\n\nnameD1: valueD1\nnameD2: valueD2";
//      std::cout << strD << std::endl;

      SDOPackage::NVList nvlistE;
      nvlistE.length(2);
			
      // (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
      string nameE1 = "short";
      CORBA::Short valueE1 = 1;
      nvlistE[0].name = nameE1.c_str();
      nvlistE[0].value <<= valueE1;
			
      // (2) NVList���Ǥ�name��"string",value��string���Υǡ����򥻥åȡ�
      string nameE2 = "string";
      string valueE2 = "test";
      nvlistE[1].name = nameE2.c_str();
      nvlistE[1].value <<= valueE2.c_str();
      			
      // (3) ���ȥ�󥰰ʳ��Υǡ��������åȤ��줿�Ȥ��Υ�å��������ǧ��

      std::string empty = "short: not a string value\nstring: test\n";
      std::string str_nvlistE = toString(nvlistE);
      /*
      if (empty == str_nvlistE)
	{
	  std::cout << "OKK";
	}
      else 
	{
	  std::cout << "not match !!" << std::endl;
	}
      */  
      CPPUNIT_ASSERT(toString(nvlistE) == empty);


    }	
  };
}; // namespace NVUtil

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(NVUtil::NVUtilTests);

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
#endif // NVUtil_cpp
