// -*- C++ -*-
/*!
 * @file NVUtil.h
 * @brief NameValue and NVList utility functions
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2010
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NVUtil.h 2019 2011-01-06 17:02:23Z n-ando $
 *
 */

#ifndef NVUTIL_NVUTIL_H
#define NVUTIL_NVUTIL_H

#include <string>
#include <iostream>
#include <coil/Properties.h>
#include <rtm/idl/SDOPackageSkel.h>

/*!
 * @if jp
 * @namespace NVUtil
 *
 * @brief NameValue �ѥ桼�ƥ���ƥ�
 *
 * NameValue ���Ф��ƤΥ桼�ƥ���ƥ��ؿ����󶡤��롣
 *
 * @else
 *
 * @namespace NVUtil
 *
 * @brief Utility for NameValue
 *
 * This class provides the utility function of NameValue. 
 *
 * @endif
 */
namespace NVUtil
{
  /*!
   * @if jp
   *
   * @brief NameValue ����������
   *
   * ���Υ��ڥ졼������NameValue��������롣
   * CORBA::Char, CORBA::Boolean, CORBA::Octet �Ϻ����Ǥ��ʤ���
   * �������ͤ� newNVChar(), newNVBool(), newNVOctet() �Ǻ������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
   *
   * @return NameValue
   *
   * @else
   *
   * @brief Create NameValue
   *
   * This operation creates NameValue.
   * CORBA::Char, CORBA::Boolean, CORBA::Octet creation is not supported.
   * These type of NameValue should be created by using 
   * newNVChar(), newNVBool(), newNVOctet() functions.
   *
   * @param name Name of NameValue
   * @param value The value of NameValue
   *
   * @return NameValue
   *
   * @endif
   */
  template <class Value>
  SDOPackage::NameValue newNV(const char* name, Value value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= value;
    return nv;
  }
  
  /***
   * @if jp
   *
   * @brief value �� CORBA::string �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::string �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
   *
   * @return NameValue
   *
   * @else
   *
   * @brief Create NameValue typed CORBA::string
   *
   * This operation creates NameValue typed CORBA::string.
   *
   * @param name Name of NameValue
   * @param value The value of NameValue
   *
   * @return NameValue
   *
   * @endif
   */
  /*
    template <>
    SDOPackage::NameValue newNV(const char* name, const char* value)
    {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= value;
    return nv;
    }
  */ 
  
  /*!
   * @if jp
   *
   * @brief value �� CORBA::Char �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::Char �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
   *
   * @return NameValue
   *
   * @else
   *
   * @brief Create NameValue typed CORBA::Char
   *
   * This operation creates NameValue typed CORBA::Char.
   *
   * @param name Name of NameValue
   * @param value The value of NameValue
   *
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVChar(const char* name, const CORBA::Char value);
  
  /*!
   * @if jp
   *
   * @brief value �� CORBA::Boolean �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::Boolean �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
   *
   * @return NameValue
   *
   * @else
   *
   * @brief Create NameValue typed CORBA::Boolean
   *
   * This operation creates NameValue typed CORBA::Boolean.
   *
   * @param name Name of NameValue
   * @param value The value of NameValue
   *
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVBool(const char* name,
				  const CORBA::Boolean value);
  
  /*!
   * @if jp
   *
   * @brief value �� CORBA::Octet �� NameValue ����������
   *
   * ���Υ��ڥ졼������ value �� CORBA::Octet �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
   *
   * @return NameValue
   *
   * @else
   *
   * @brief Create NameValue typed CORBA::Octet
   *
   * This operation creates NameValue typed CORBA::Octet.
   *
   * @param name Name of NameValue
   * @param value The value of NameValue
   *
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVOctet(const char* name, const CORBA::Octet value);
  
  /*!
   * @if jp
   *
   * @brief value �� CORBA::Any �� NameValue ����������
   *
   * ���Υ��ڥ졼������f value �� CORBA::Any �� NameValue��������롣
   *
   * @param name NameValue �� name
   * @param value NameValue �� value
   *
   * @return NameValue
   *
   * @else
   *
   * @brief Create NameValue typed CORBA::Any
   *
   * This operation creates NameValue typed CORBA::Any.
   *
   * @param name Name of NameValue
   * @param value The value of NameValue
   *
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVAny(const char* name, const CORBA::Any& value);
  
  /*!
   * @if jp
   *
   * @brief Properties �� NVList �إ��ԡ�����
   *
   * ���Υ��ڥ졼������ Properties �� NVList �إ��ԡ����롣
   * NVList �� value ������ CORBA::string ���Ȥ��ƥ��ԡ����롣
   *
   * @param nv Properties ���ͤ��Ǽ���� NVList
   * @param prop ���ԡ����� Properties
   *
   * @else
   *
   * @brief Copy the properties to NVList
   *
   * This operation copies the properties to NVList.
   * All NVList's values are copied as CORBA::string.
   *
   * @param nv NVList to store properties values
   * @param prop Properties that is copies from
   *
   * @endif
   */
#ifndef ORB_IS_RTORB
  void copyFromProperties(SDOPackage::NVList& nv, const coil::Properties& prop);
#else // ORB_IS_RTORB
  void copyFromProperties(SDOPackage_NVList& nv, const coil::Properties& prop);
#endif // ORB_IS_RTORB
  
  /*!
   * @if jp
   *
   * @brief NVList �� Properties �إ��ԡ�����
   *
   * ���Υ��ڥ졼������ NVList �� Properties �إ��ԡ����롣
   *
   * @param prop NVList ���ͤ��Ǽ���� Properties
   * @param nv ���ԡ����� NVList
   *
   * @else
   *
   * @brief Copy NVList to the Proeprties
   *
   * This operation copies NVList to properties.
   *
   * @param prop Properties to store NVList values
   * @param nv NVList of copy source
   *
   * @endif
   */
  void copyToProperties(coil::Properties& prop, const SDOPackage::NVList& nv);
  
  /*!
   * @if jp
   *
   * @brief NVList �� Properties ���Ѵ�����
   *
   * ���Υ��ڥ졼������ NVList �� Properties ���Ѵ����롣
   *
   * @param nv �Ѵ����� NVList
   *
   * @return �Ѵ����Property
   *
   * @else
   *
   * @brief Transform NVList to the properties
   *
   * This operation transforms NVList to properties
   *
   * @param nv NVList of tranformation source
   *
   * @return Transformation result Property
   *
   * @endif
   */
  coil::Properties toProperties(const SDOPackage::NVList& nv);
  
  /*!
   * @if jp
   *
   * @brief NVList ���� name �ǻ��ꤵ�줿 value ���֤�
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿 value �� Any �����֤���
   * ���ꤷ��̾�Τ����Ǥ�¸�ߤ��ʤ������㳰��ȯ�������롣
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
   *
   * @return �������
   *
   * @else
   *
   * @brief Return the value specified by name from NVList
   *
   * This operation returns Any type of value specified by name.
   * When an element of specified name doesn't exist, the exception will occur.
   *
   * @param nv The target NVList for the find
   * @param name  Name for the find
   *
   * @return Find result
   *
   * @endif
   */
  const CORBA::Any& find(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief name �ǻ��ꤵ�줿���ǤΥ���ǥå������֤�
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿���Ǥ���Ǽ����Ƥ�����֤�
   * ����ǥå������֤���
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
   *
   * @return �����оݤΥ���ǥå���
   *
   * @else
   *
   * @brief Return the index of element specified by name from NVList
   *
   * This operation returns the index at the position where the element
   * specified by name is stored.
   *
   * @param nv The target NVList for the find
   * @param name  Name for the find
   *
   * @return Index of target object for the find
   *
   * @endif
   */
  const CORBA::Long find_index(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief ���ꤵ�줿 name �� value �η��� string �Ǥ��뤫���ڤ���
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿 value �η��� CORBA::string
   * ���ɤ����� bool �ͤ��֤���
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
   *
   * @return string���ڷ��(string:true������ʳ�:false)
   *
   * @else
   *
   * @brief Validate whether value type specified by name is string type
   *
   * This operation returns the bool value by checking whether the type of
   * value specified with name is CORBA::string.
   *
   * @param nv The target NVList for the search
   * @param name Name for the search
   *
   * @return String validation result (String:true, Else:false)
   *
   * @endif
   */
  bool isString(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief ���ꤵ�줿 name �� value ���ͤ����ꤷ��ʸ����Ȱ��פ��뤫���ڤ���
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿 value �η��� CORBA::string
   * ���ɤ�����Ƚ�Ǥ���  CORBA::string �Ǥ�����ˤϻ��ꤷ��ʸ����Ȱ��פ��뤫
   * ��bool �ͤ��֤���
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
   * @param value ����о�ʸ����
   *
   * @return ���ڷ��(ʸ����Ȱ���:true�������:false)
   *
   * @else
   *
   * @brief Check whether the value of specified name matches the specified
   *        string
   *
   * This operation checks whether the value specified with name is 
   * CORBA::string and returns the bool value which matches spcified string.
   *
   * @param nv The target NVList for the search
   * @param name Name for the search
   * @param value String value to compare
   *
   * @return Check result (Match:true, Unmatch:false)
   *
   * @endif
   */
  bool isStringValue(const SDOPackage::NVList& nv, const char* name,
		     const char* value);
  
  /*!
   * @if jp
   *
   * @brief ���ꤵ�줿 name �� NVList �� string �Ȥ����֤���
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿 NVList ���ͤ� string ���֤���
   * �⤷��name �ǻ��ꤷ�� value ���ͤ� CORBA::string �Ǥʤ���С�
   * ����ʸ�����string���֤���
   *
   * @param nv �����оݤ� NVList
   * @param name ��������̾��
   *
   * @return name ���б������ͤ�string������
   *
   * @else
   *
   * @brief Get NVList of specifid name as string
   *
   * This operation returns string value in NVList specified by name.
   * If the value in NVList specified by name is not CORBA::string type
   * this operation returns empty string value.
   *
   * @param nv The target NVList for the search
   * @param name Name for the search
   *
   * @return String value corresponding to name
   *
   * @endif
   */
  std::string toString(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief ���ꤵ�줿ʸ����� NVList �����Ǥ��ɲä��롣
   *
   * ���Υ��ڥ졼������ name �ǻ��ꤵ�줿���Ǥ� value �ǻ��ꤵ�줿ʸ�����
   * �ɲä��롣
   * name �ǻ��ꤷ�����Ǥ˴��� value ���ͤ����ꤵ��Ƥ�����ˤϲ��⤷�ʤ���
   * name �ǻ��ꤷ�����Ǥ� value ���ͤ����ꤵ��Ƥ��ʤ����ϡ� ","���ڤ��
   * value ���ͤ��ɲä��롣
   * ���ꤵ�줿�ͤ����ꤹ�롣
   * name �ǻ��ꤷ�����Ǥ�¸�ߤ��ʤ����ϡ� NVList �κǸ�˿��������Ǥ��ɲä���
   * ���ꤵ�줿�ͤ����ꤹ�롣
   *
   * @param nv �����оݤ� NVList
   * @param name �ɲ��о�����̾
   * @param value �ɲä���ʸ����
   *
   * @return �ɲ������
   *
   * @else
   *
   * @brief Append the specified string to element of NVList
   *
   * This operation appends the string value specified by value to the element
   * specified by name.
   * Operate nothing when the 'value' value has already been set to the
   * element specified by name.
   * Add the 'value' value each separating by a comma "," when the 'value'
   * value is not set to the element specified by name.
   * Set the specified value.
   * Add a new element at the end of NVList, and set the specified value,
   * when the element specified by name does not exist.
   *
   * @param nv The target NVList for the search
   * @param name The target element name for the appending
   * @param value String to append
   *
   * @return Append operation result
   *
   * @endif
   */
#ifndef ORB_IS_RTORB
  bool appendStringValue(SDOPackage::NVList& nv, const char* name,
                         const char* value);
#else // ORB_IS_RTORB
  bool appendStringValue(SDOPackage_NVList& nv, const char* name,
                         const char* value);
#endif // ORB_IS_RTORB
  
  /*!
   * @if jp
   *
   * @brief NVList �����Ǥ��ɲä��롣
   *
   * ���Υ��ڥ졼������ dest �ǻ��ꤵ�줿 NVList �� src �ǻ��ꤵ�줿���Ǥ�
   * �ɲä��롣
   *
   * @param dest �ɲä���� NVList
   * @param src �ɲä��� NVList
   *
   * @else
   *
   * @brief Append an element to NVList
   *
   * This operation appends elements specified by src to NVList specified
   * by dest.
   *
   * @param dest NVList to be appended
   * @param src NVList to append
   *
   * @endif
   */
  void append(SDOPackage::NVList& dest, const SDOPackage::NVList& src);
  
  /*!
   * @if jp
   *
   * @brief NVList �����ꤵ��Ƥ������Ƥ�ʸ����Ȥ��ƽ��Ϥ��롣
   *
   * ���ꤵ�줿 NVList �����ꤵ�줿���Ƥ�ʸ����Ȥ��ƽ��Ϥ��롣
   * �ʤ������ꤵ��Ƥ������Ǥ�ʸ���󷿰ʳ��ξ��ˤϡ����λ�(ʸ����ǤϤʤ�)��
   * ���Ϥ��롣
   *
   * @param nv �����о� NVList
   *
   * @else
   *
   * @brief Print information configured in NVList as string type
   *
   * Print configured information as string type in specified NVList.
   * Also, print the reason (this is not string type) if the configured
   * element is other than string type.
   *
   * @param nv The target NVList for the print
   *
   * @endif
   */
  std::ostream& dump(std::ostream& out, const SDOPackage::NVList& nv);

  /*!
   * @if jp
   * @brief NVList �����ꤵ��Ƥ������Ƥ�ʸ����Ȥ���ɸ����Ϥ��롣
   *
   * @param nv �����о� NVList
   *
   * @else
   * @brief Print information configured in NVList as a string type 
   *        to Standard Outport.
   *
   * @param nv The target NVList for the print
   *
   * @endif
   */
  void dump(const SDOPackage::NVList& nv);

  /*!
   * @if jp
   * @brief NVList �����ꤵ��Ƥ������Ƥ�ʸ����ˤ���
   *
   * @param nv �����о� NVList
   *
   * @else
   * @brief Get information configured in NVList as a string type.
   *
   * @param nv The target NVList for the print
   *
   * @endif
   */
  std::string toString(const SDOPackage::NVList& nv);
  

};
#endif // NVUTIL_NVUTIL_H
