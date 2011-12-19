// -*- C++ -*-
/*!
 * @file  InPortProvider.h
 * @brief InPortProvider class
 * @date  $Date: 2007-12-31 03:08:03 $
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
 * $Id: InPortProvider.cpp 2019 2011-01-06 17:02:23Z n-ando $
 *
 */

#include <rtm/RTC.h>
#include <rtm/InPortProvider.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  InPortProvider::InPortProvider()
    : rtclog("InPortProvier")
  {
  }
  
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  InPortProvider::~InPortProvider()
  {
  }
  
  /*!
   * @if jp
   * @brief InterfaceProfile������������
   * @else
   * @brief Publish InterfaceProfile information
   * @endif
   */
  void InPortProvider::publishInterfaceProfile(SDOPackage::NVList& prop)
  {
    RTC_TRACE(("publishInterfaceProfile()"));

#ifdef ORB_IS_RTORB
    NVUtil::appendStringValue(*prop.cobj(), "dataport.interface_type",
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
   * @brief Publish Interface information
   * @endif
   */
  bool InPortProvider::publishInterface(SDOPackage::NVList& prop)
  {
    RTC_TRACE(("publishInterface()"));
    RTC_DEBUG_STR((NVUtil::toString(prop)));
    if (!NVUtil::isStringValue(prop,
			       "dataport.interface_type",
			       m_interfaceType.c_str()))
      {
	return false;
      }
    
    NVUtil::append(prop, m_properties);
    //    NVUtil::dump(m_properties);
    return true;
  }

  //----------------------------------------------------------------------
  // protected functions
  
  /*!
   * @if jp
   * @brief ���󥿡��ե����������פ����ꤹ��
   * @else
   * @brief Set the interface type
   * @endif
   */
  void InPortProvider::setInterfaceType(const char* interface_type)
  {
    RTC_TRACE(("setInterfaceType(%s)", interface_type));
    m_interfaceType = interface_type;
  }
  
  /*!
   * @if jp
   * @brief �ǡ����ե������פ����ꤹ��
   * @else
   * @brief Set the dataflow type
   * @endif
   */
  void InPortProvider::setDataFlowType(const char* dataflow_type)
  {
    RTC_TRACE(("setDataFlowType(%s)", dataflow_type));
    m_dataflowType = dataflow_type;
  }
  
  /*!
   * @if jp
   * @brief ���֥�����ץ���󥿥��פ����ꤹ��
   * @else
   * @brief Set the subscription type
   * @endif
   */
  void InPortProvider::setSubscriptionType(const char* subs_type)
  {
    RTC_TRACE(("setSubscriptionType(%s)", subs_type));
    m_subscriptionType = subs_type;
  }
}; // namespace RTC
