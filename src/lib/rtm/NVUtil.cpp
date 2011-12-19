// -*- C++ -*-
/*!
 * @file NVUtil.cpp
 * @brief NameValue and NVList utility functions
 * @date $Date: 2008-01-13 07:41:08 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NVUtil.cpp 2019 2011-01-06 17:02:23Z n-ando $
 *
 */

#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4290 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#endif // WIN32

#include <map>
#include <algorithm>
#include <coil/stringutil.h>
#include <rtm/NVUtil.h>
#include <rtm/CORBA_SeqUtil.h>

#ifdef WIN32
#pragma warning( pop )
#endif // WIN32

namespace NVUtil
{
  /*!
   * @if jp
   * @brief value �� CORBA::Char �� NameValue ����������
   * @else
   * @brief Create NameValue typed CORBA::Char
   * @endif
   */
  SDOPackage::NameValue newNVChar(const char* name, const CORBA::Char value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= CORBA::Any::from_char(value);
    return nv;
  }
  
  /*!
   * @if jp
   * @brief value �� CORBA::Boolean �� NameValue ����������
   * @else
   * @brief This operation creates NameValue typed CORBA::Boolean.
   * @endif
   */
  SDOPackage::NameValue newNVBool(const char* name, const CORBA::Boolean value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= CORBA::Any::from_boolean(value);
    return nv;
  }
  
  /*!
   * @if jp
   * @brief value �� CORBA::Octet �� NameValue ����������
   * @else
   * @brief Create NameValue typed CORBA::Octet
   * @endif
   */
  SDOPackage::NameValue newNVOctet(const char* name, const CORBA::Octet value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= CORBA::Any::from_octet(value);
    return nv;
  }
  
  /*!
   * @if jp
   * @brief value �� CORBA::Any �� NameValue ����������
   * @else
   * @brief Create NameValue typed CORBA::Any
   * @endif
   */
  SDOPackage::NameValue newNVAny(const char* name, const CORBA::Any& value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value = value;
    return nv;
  }
  
  /*!
   * @if jp
   * @brief Properties �� NVList �إ��ԡ�����
   * @else
   * @brief Copy the properties to NVList
   * @endif
   */
#ifndef ORB_IS_RTORB
  void copyFromProperties(SDOPackage::NVList& nv, const coil::Properties& prop)
#else // ORB_IS_RTORB
    void copyFromProperties(SDOPackage_NVList& nv, const coil::Properties& prop)
#endif // ORB_IS_RTORB
  {
    std::vector<std::string> keys;
    keys = prop.propertyNames();
    CORBA::ULong len((CORBA::ULong)keys.size());
    nv.length(len);
    
    for (CORBA::ULong i = 0; i < len; ++i)
      {
// Why RtORB does not copy string to Properties.
#ifndef ORB_IS_RTORB
        nv[i].name = CORBA::string_dup(keys[i].c_str());
#else // ORB_IS_RTORB
        nv[i].name = (char *)keys[i].c_str();
#endif // ORB_IS_RTORB
	nv[i].value <<= prop[keys[i]].c_str();
      }
  }
  
  /*!
   * @if jp
   * @brief NVList �� Properties �إ��ԡ�����
   * @else
   * @brief Copy NVList to the Proeprties
   * @endif
   */
  void copyToProperties(coil::Properties& prop, const SDOPackage::NVList& nv)
  {
    for (CORBA::ULong i(0), len(nv.length()); i < len; ++i)
      {
	const char* value;
	if (nv[i].value >>= value)
	  {
	    const char* name(nv[i].name);
	    prop[name] = value;
	  };
      }
  }
  
  /*!
   * @if jp
   * @brief NVList �� Properties ���Ѵ����뤿��Υե��󥯥�
   * @else
   * @brief Functor to transform NVList into the properties
   * @endif
   */
  struct to_prop
  {
    to_prop()
    {
    };
    void operator()(const SDOPackage::NameValue& nv)
    {
      const char* value;
      if (nv.value >>= value)
	{
	  m_prop.setProperty(CORBA::string_dup(nv.name), value);
	};
    }
    coil::Properties m_prop;
  };
  
  /*!
   * @if jp
   * @brief NVList �� Properties ���Ѵ�����
   * @else
   * @brief Transform NVList to the properties
   * @endif
   */
  coil::Properties toProperties(const SDOPackage::NVList& nv)
  {
    to_prop p;
    p = CORBA_SeqUtil::for_each(nv, p);
    return p.m_prop;
  }
  
  /*!
   * @if jp
   * @brief NVList �򸡺����뤿��Υե��󥯥�
   * @else
   * @brief Functor to find a NVList
   * @endif
   */
  struct nv_find
  {
    nv_find(const char* name) : m_name(name) {};
    bool operator()(const SDOPackage::NameValue& nv)
    {
      std::string name(nv.name);
      return m_name == name;
    }
    std::string m_name;
  };
  
  /*!
   * @if jp
   * @brief NVList ���� name �ǻ��ꤵ�줿 value ���֤�
   * @else
   * @brief Return the value specified by name from NVList
   * @endif
   */
  const CORBA::Any& find(const SDOPackage::NVList& nv, const char* name)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(nv, NVUtil::nv_find(name));
    if (index < 0) throw std::string("Not found");
    return nv[index].value;
  }
  
  /*!
   * @if jp
   * @brief name �ǻ��ꤵ�줿���ǤΥ���ǥå������֤�
   * @else
   * @brief Return the index of element specified by name from NVList
   * @endif
   */
  const CORBA::Long find_index(const SDOPackage::NVList& nv, const char* name)
  {
    return  CORBA_SeqUtil::find(nv, NVUtil::nv_find(name));
  }
  
  /*!
   * @if jp
   * @brief ���ꤵ�줿 name �� value �η��� string �Ǥ��뤫���ڤ���
   * @else
   * @brief Validate whether value type specified by name is string type
   * @endif
   */
  bool isString(const SDOPackage::NVList& nv, const char* name)
  {
    try
      {
	CORBA::Any value;
	value = find(nv, name);
	const char* str_value;
	return value >>= str_value;
      }
    catch (...)
      {
	return false;
      }
  }
  
  /*!
   * @if jp
   * @brief ���ꤵ�줿 name �� value ���ͤ����ꤷ��ʸ����Ȱ��פ��뤫���ڤ���
   * @else
   * @brief Check whether the value of specified name specified matches
   *        the specified string
   * @endif
   */
  bool isStringValue(const SDOPackage::NVList& nv,
		     const char* name, const char* value)
  {
    if (isString(nv, name))
      {
	if (toString(nv, name) == value)
	  {
	    return true;
	  }
      }
    return false;
  }
  
  /*!
   * @if jp
   * @brief ���ꤵ�줿 name �� NVList �� string �Ȥ����֤���
   * @else
   * @brief Get NVList of specifid name as string
   * @endif
   */
  std::string toString(const SDOPackage::NVList& nv, const char* name)
  {
    const char* str_value;
    try
      {
	if(!(find(nv, name) >>= str_value))
          {
	    str_value = "";
          }
      }
    catch (...)
      {
	str_value = "";
      }

    if (str_value == NULL)
      {
	str_value = "";
      }
    
    return str_value;
  }
  
  /*!
   * @if jp
   * @brief ���ꤵ�줿ʸ����� NVList �����Ǥ��ɲä��롣
   * @else
   * @brief Append the specified string to element of NVList
   * @endif
   */
#ifndef ORB_IS_RTORB
  bool appendStringValue(SDOPackage::NVList& nv, const char* name,
                         const char* value)
#else // ORB_IS_RTORB
  bool appendStringValue(SDOPackage_NVList& nv, const char* name,
                         const char* value)
#endif // ORB_IS_RTORB
  {
    //    if (!isString(nv, name)) return false;
    
    CORBA::Long index;
    index = find_index(nv, name);
    
    if (index < 0)
      {
	CORBA_SeqUtil::push_back(nv, newNV(name, value));
      }
    else
      {
	const char* tmp_char;
	nv[index].value >>= tmp_char;
	std::string tmp_str(tmp_char);
	
	std::vector<std::string> values;
	values = coil::split(tmp_str, ",");
	if (values.end() == std::find(values.begin(), values.end(), value))
	  {
	    tmp_str.append(",");
	    tmp_str.append(value);
	    nv[index].value <<= tmp_str.c_str();
	  }
      }
    return true;
  }
  
  /*!
   * @if jp
   * @brief NVList �����Ǥ��ɲä��롣
   * @else
   * @brief Append an element to NVList
   * @endif
   */
  void append(SDOPackage::NVList& dest, const SDOPackage::NVList& src)
  {
    for (CORBA::ULong i = 0, len = src.length(); i < len; ++i)
      {
	CORBA_SeqUtil::push_back(dest, src[i]);
      }
  }
  
  /*!
   * @if jp
   * @brief NVList �����ꤵ��Ƥ������Ƥ�ʸ����Ȥ��ƽ��Ϥ��롣
   * @else
   * @brief Print information configured in NVList as a string type
   * @endif
   */
  std::ostream& dump_to_stream(std::ostream& out, const SDOPackage::NVList& nv)
  {
    for (CORBA::ULong i(0), n(nv.length()); i < n; ++i)
      {
	const char* str_value;
	if (nv[i].value >>= str_value)
	  {
	    out << nv[i].name << ": " << str_value << std::endl;
	  }
	else
	  {
	    out << nv[i].name << ": not a string value" << std::endl;
	  }
      }
    return out;
  }

  /*!
   * @if jp
   * @brief NVList �����ꤵ��Ƥ������Ƥ�ʸ����Ȥ���ɸ����Ϥ��롣
   * @else
   * @brief Print information configured in NVList as a string type 
   *        to Standard Outport.
   * @endif
   */
  void dump(const SDOPackage::NVList& nv)
  {
    dump_to_stream(std::cout, nv);
  }

  /*!
   * @if jp
   * @brief NVList �����ꤵ��Ƥ������Ƥ�ʸ����ˤ���
   * @else
   * @brief Get information configured in NVList as a string type
   * @endif
   */
  std::string toString(const SDOPackage::NVList& nv)
  {
    std::stringstream s;
    dump_to_stream(s, nv);
    return s.str();
  }
};
