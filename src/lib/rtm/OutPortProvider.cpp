// -*- C++ -*-
/*!
 * @file  OutPortProvider.cpp
 * @brief OutPortProvider class
 * @date  $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPortProvider.cpp 2019 2011-01-06 17:02:23Z n-ando $
 *
 */

#include <rtm/RTC.h>
#include <rtm/OutPortProvider.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  OutPortProvider::~OutPortProvider(void)
  {
  }
  
  /*!
   * @if jp
   * @brief ��������
   * @else
   * @brief Initializing configuration
   * @endif
   */
  void OutPortProvider::init(coil::Properties& prop)
  {
  }

  /*!
   * @if jp
   * @brief InterfaceProfile������������
   * @else
   * @brief Publish InterfaceProfile information
   * @endif
   */
  void OutPortProvider::publishInterfaceProfile(SDOPackage::NVList& prop)
  {
#ifdef ORB_IS_RTORB
    SDOPackage_NVList prop_ptr(*prop.cobj());
    NVUtil::appendStringValue(prop_ptr, "dataport.interface_type",
                              m_interfaceType.c_str());
#else // ORB_IS_RTORB
    NVUtil::appendStringValue(prop, "dataport.interface_type",
                             m_interfaceType.c_str());
#endif // ORB_IS_RTORB
    NVUtil::append(prop, m_properties);
  }
  
  /*!
   * @if jp
   * @brief Interface������������
   * @else
   * @brief Publish interface information
   * @endif
   */
  bool OutPortProvider::publishInterface(SDOPackage::NVList& prop)
  {
    if (!NVUtil::isStringValue(prop,
			       "dataport.interface_type",
			       m_interfaceType.c_str()))
      {
	return false;
      }
    
    NVUtil::append(prop, m_properties);
    return true;
  }
  
  /*!
   * @if jp
   * @brief �ݡ��ȥ����פ����ꤹ��
   * @else
   * @brief Set the port type
   * @endif
   */
  void OutPortProvider::setPortType(const char* port_type)
  {
    m_portType = port_type;
  }
  
  /*!
   * @if jp
   * @brief �ǡ��������פ����ꤹ��
   * @else
   * @brief Set the data type
   * @endif
   */
  void OutPortProvider::setDataType(const char* data_type)
  {
    m_dataType = data_type;
  }
  
  /*!
   * @if jp
   * @brief ���󥿡��ե����������פ����ꤹ��
   * @else
   * @brief Set the interface type
   * @endif
   */
  void OutPortProvider::setInterfaceType(const char* interface_type)
  {
    m_interfaceType = interface_type;
  }
  
  /*!
   * @if jp
   * @brief �ǡ����ե������פ����ꤹ��
   * @else
   * @brief Set the data flow type
   * @endif
   */
  void OutPortProvider::setDataFlowType(const char* dataflow_type)
  {
    m_dataflowType = dataflow_type;
  }
  
  /*!
   * @if jp
   * @brief ���֥�����ץ���󥿥��פ����ꤹ��
   * @else
   * @brief Set the subscription type
   * @endif
   */
  void OutPortProvider::setSubscriptionType(const char* subs_type)
  {
    m_subscriptionType = subs_type;
  }
}; // namespace RTC
