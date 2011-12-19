// -*- C++ -*-
/*!
 * @file  CorbaPort.h
 * @brief CorbaPort class
 * @date  $Date: 2007-12-31 03:08:02 $
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
 * $Id: CorbaPort.cpp 2019 2011-01-06 17:02:23Z n-ando $
 *
 */

#include <rtm/SystemLogger.h>
#include <rtm/CorbaPort.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/Manager.h>
#include <string>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  CorbaPort::CorbaPort(const char* name)
    : PortBase(name)
  {
    addProperty("port.port_type", "CorbaPort");
  }
  
  /*!
   * @if jp
   * @brief ���ۥǥ��ȥ饯��
   * @else
   * @brief Virtual destructor
   * @endif
   */
  CorbaPort::~CorbaPort()
  {
  }

  /*!
   * @if jp
   * @brief �ץ�ѥƥ��ν����
   * @else
   * @brief Initializing properties
   * @endif
   */
  void CorbaPort::init(coil::Properties& prop)
  {
    RTC_TRACE(("init()"));
    RTC_PARANOID(("given properties:"));
    RTC_DEBUG_STR((prop));

    m_properties << prop;

    RTC_PARANOID(("updated properties:"));
    RTC_DEBUG_STR((m_properties));

    int num(-1);
    if (!coil::stringTo(num, m_properties.getProperty("connection_limit",
                                                      "-1").c_str()))
      {
        RTC_ERROR(("invalid connection_limit value: %s", 
                   m_properties.getProperty("connection_limit").c_str()));
      }

    setConnectionLimit(num);
  }
  
  /*!
   * @if jp
   * @brief Provider ����Ͽ����
   * @else
   * @brief Register the provider
   * @endif
   */
  bool
  CorbaPort::registerProvider(const char* instance_name,
			      const char* type_name,
			      PortableServer::RefCountServantBase& provider)
  {
    RTC_TRACE(("registerProvider(instance=%s, type_name=%s)",
               instance_name, type_name));

    try
      {
        CorbaProviderHolder providerholder(type_name, instance_name, &provider);
        m_providers.push_back(providerholder);
      }
    catch (...)
      {
        RTC_ERROR(("appending provider interface failed"));
        return false;
      }

    if (!appendInterface(instance_name, type_name, RTC::PROVIDED))
      {
        RTC_ERROR(("appending provider interface failed"));
	return false;
      }
    
    return true;
  };
  
  /*!
   * @if jp
   * @brief Consumer ����Ͽ����
   * @else
   * @brief Register the consumer
   * @endif
   */
  bool
  CorbaPort::registerConsumer(const char* instance_name,
			      const char* type_name,
			      CorbaConsumerBase& consumer)
  {
    RTC_TRACE(("registerConsumer()"));

    if (!appendInterface(instance_name, type_name, RTC::REQUIRED))
      {
	return false;
      }
    
    m_consumers.push_back(CorbaConsumerHolder(type_name,
                                              instance_name,
                                              &consumer));
    
    return true;
  }

  //============================================================
  // Local operations
  //============================================================

  /*!
   * @if jp
   * @brief Port �����ƤΥ��󥿡��ե������� activates ����
   * @else
   * @brief Activate all Port interfaces
   * @endif
   */
  void CorbaPort::activateInterfaces()
  {
    CorbaProviderList::iterator it(m_providers.begin());
    while(it != m_providers.end())
      {
        it->activate();
	++it;
      }
  }
  
  /*!
   * @if jp
   * @brief ���Ƥ� Port �Υ��󥿡��ե������� deactivates ����
   * @else
   * @brief Deactivate all Port interfaces
   * @endif
   */
  void CorbaPort::deactivateInterfaces()
  {
    CorbaProviderList::iterator it(m_providers.begin());
    while(it != m_providers.end())
      {
        it->deactivate();
	++it;
      }
  }
  
  //============================================================
  // protected functions
  //============================================================
  /*!
   * @if jp
   * @brief Interface ������������
   * @else
   * @brief Publish interface information
   * @endif
   */
  ReturnCode_t
  CorbaPort::publishInterfaces(ConnectorProfile& connector_profile)
  {
    RTC_TRACE(("publishInterfaces()"));

    ReturnCode_t returnvalue = _publishInterfaces();
    if(returnvalue != RTC::RTC_OK)
      {
        return returnvalue;
      }

    NVList properties;
    CorbaProviderList::iterator it(m_providers.begin());
    while (it != m_providers.end())
      {
        //------------------------------------------------------------
        // new version descriptor
        // <comp_iname>.port.<port_name>.provided.<type_name>.<instance_name>
        std::string newdesc((const char*)m_profile.name);
        newdesc.insert(m_ownerInstanceName.size(), ".port");
        newdesc += ".provided." + it->descriptor();
        CORBA_SeqUtil::
          push_back(properties,
                    NVUtil::newNV(newdesc.c_str(), it->ior().c_str()));

        //------------------------------------------------------------
        // old version descriptor
        // port.<type_name>.<instance_name>
        std::string olddesc;
        olddesc += "port." + it->descriptor();
        CORBA_SeqUtil::
          push_back(properties,
                    NVUtil::newNV(olddesc.c_str(), it->ior().c_str()));
        ++it;
      }

#ifdef ORB_IS_RTORB
    {
      CORBA::ULong len1(connector_profile.properties.length());
      CORBA::ULong len2(properties.length());
      CORBA::ULong len(len1 + len2);
      connector_profile.properties.length(len);
      
      for (CORBA::ULong i = 0; i < len2; ++i)
        {
          connector_profile.properties[len1 + i] = properties[i];
        }
    }
#else // ORB_IS_RTORB
    CORBA_SeqUtil::push_back_list(connector_profile.properties, properties);
#endif
    
    RTC_DEBUG_STR((NVUtil::toString(properties)));                         

    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interface ����³����
   * @else
   * @brief Subscribe to interfaces
   * @endif
   */
  ReturnCode_t
  CorbaPort::subscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    RTC_TRACE(("subscribeInterfaces()"));

    const NVList& nv(connector_profile.properties);
    RTC_DEBUG_STR((NVUtil::toString(nv)));

    bool strict(false); // default is "best_effort"
    CORBA::Long index(NVUtil::find_index(nv, "port.connection.strictness"));
    if (index >=  0)
      {
        const char* strictness;
        nv[index].value >>= strictness;
        if (std::string("best_effort") == strictness) { strict = false; }
        else if (std::string("strict") == strictness) { strict = true; }
        RTC_DEBUG(("Connetion strictness is: %s",
                   strict ? "strict" : "best_effort"))
      }

    for (CorbaConsumerList::iterator it(m_consumers.begin());
         it != m_consumers.end(); ++it)
      {
        std::string ior;
        if (findProvider(nv, *it, ior))
          {
            setObject(ior, *it);
            continue;
          }
        if (findProviderOld(nv, *it, ior))
          {
            setObject(ior, *it);
            continue;
          }

        // never come here without error
        // if strict connection option is set, error is returned.
        if (strict)
          {
            RTC_ERROR(("subscribeInterfaces() failed."));
            return RTC::RTC_ERROR; 
          }
      }

    RTC_TRACE(("subscribeInterfaces() successfully finished."));

    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interface �ؤ���³��������
   * @else
   * @brief Unsubscribe interfaces
   * @endif
   */
  void
  CorbaPort::unsubscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    RTC_TRACE(("unsubscribeInterfaces()"));

    const NVList& nv(connector_profile.properties);
    RTC_DEBUG_STR((NVUtil::toString(nv)));

    for (CorbaConsumerList::iterator it(m_consumers.begin());
         it != m_consumers.end(); ++it)
      {
        std::string ior;
        if (findProvider(nv, *it, ior))
          {
            RTC_DEBUG(("Correspoinding consumer found."));
            releaseObject(ior, *it);
            continue;
          }
        if (findProviderOld(nv, *it, ior))
          {
            RTC_DEBUG(("Correspoinding consumer found."));
            releaseObject(ior, *it);
            continue;
          }
      }
  }
  
  /*!
   * @if jp
   * @brief Consumer �˹��פ��� Provider �� NVList ���椫�鸫�Ĥ���
   * @else
   * @brief Find out a provider corresponding to the consumer from NVList
   * @endif
   */
  bool CorbaPort::findProvider(const NVList& nv, CorbaConsumerHolder& cons,
                               std::string& iorstr)
  {
    // new consumer interface descriptor
    std::string newdesc((const char*)m_profile.name);
    newdesc.insert(m_ownerInstanceName.size(), ".port");
    newdesc += ".required." + cons.descriptor();

    // find a NameValue of the consumer
    CORBA::Long cons_index(NVUtil::find_index(nv, newdesc.c_str()));
    if (cons_index < 0) { return false; }

    const char* provider;
    if (!(nv[cons_index].value >>= provider))
      {
        RTC_WARN(("Cannot extract Provider interface descriptor"));
        return false;
      }

    // find a NameValue of the provider
    CORBA::Long prov_index(NVUtil::find_index(nv, provider));
    if (prov_index < 0) { return false; }

    const char* ior;
    if (!(nv[prov_index].value >>= ior))
      {
        RTC_WARN(("Cannot extract Provider IOR string"));
        return false;
      }
    iorstr = ior;
    RTC_DEBUG(("interface matched with new descriptor: %s", newdesc.c_str()));
    return true;
  }

  /*!
   * @if jp
   * @brief Consumer �˹��פ��� Provider �� NVList ���椫�鸫�Ĥ���
   * @else
   * @brief Find out a provider corresponding to the consumer from NVList
   * @endif
   */
  bool CorbaPort::findProviderOld(const NVList&nv, CorbaConsumerHolder& cons,
                                  std::string& iorstr)
  {
    // old consumer interface descriptor
    std::string olddesc("port."); olddesc += cons.descriptor();

    // find a NameValue of the provider same as olddesc
    CORBA::Long index(NVUtil::find_index(nv, olddesc.c_str()));
    if (index < 0) { return false; }

    const char* ior;
    if (!(nv[index].value >>= ior))
      {
        RTC_WARN(("Cannot extract Provider IOR string"));
        return false;
      }
    iorstr = ior;
    RTC_INFO(("interface matched with old descriptor: %s", olddesc.c_str()));
    return true;
  }

  /*!
   * @if jp
   * @brief Consumer �� IOR �򥻥åȤ���
   * @else
   * @brief Setting IOR to Consumer
   * @endif
   */
  bool CorbaPort::setObject(const std::string& ior, CorbaConsumerHolder& cons)
  {
    // if ior string is "null" or "nil", ignore it.
    if (std::string("null") == ior) { return true; }
    if (std::string("nil")  == ior) { return true; }
    // IOR should be started by "IOR:"
    if (std::string("IOR:").compare(0, 4, ior.c_str(), 4) != 0)
      {
        return false;
      }

    // set IOR to the consumer
    if (!cons.setObject(ior.c_str()))
      {
        RTC_ERROR(("Cannot narrow reference"));
        return false;
      }
    RTC_TRACE(("setObject() done"));
    return true;
  }

  /*!
   * @if jp
   * @brief Consumer �Υ��֥������Ȥ��꡼������
   * @else
   * @brief Releasing Consumer Object
   * @endif
   */
  bool CorbaPort::releaseObject(const std::string& ior,
                                CorbaConsumerHolder& cons)
  {
    if (ior == cons.getIor())
      {
        cons.releaseObject();
        RTC_DEBUG(("Consumer %s released.", cons.descriptor().c_str()));
        return true;
      }
    RTC_WARN(("IORs between Consumer and Connector are different."));
    return false;
  }
  
};
