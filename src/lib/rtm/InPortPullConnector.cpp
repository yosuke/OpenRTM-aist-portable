// -*- C++ -*-
/*!
 * @file InPortPullConnector.cpp
 * @brief InPortPull type connector class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPortPullConnector.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#include <rtm/InPortPullConnector.h>
#include <rtm/OutPortConsumer.h>
#include <rtm/ConnectorListener.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  InPortPullConnector::InPortPullConnector(ConnectorInfo info,
                                           OutPortConsumer* consumer,
                                           ConnectorListeners& listeners,
                                           CdrBufferBase* buffer)
    : InPortConnector(info, buffer), m_consumer(consumer),
      m_listeners(listeners)
  {
    if (buffer == 0)
      {
        m_buffer = createBuffer(m_profile);
      }
    if (m_buffer == 0 || m_consumer == 0)
      {
        throw std::bad_alloc();
        return;
      }
    m_buffer->init(info.properties.getNode("buffer"));
    m_consumer->setBuffer(m_buffer);
    m_consumer->setListener(info, &m_listeners);

    onConnect();
  }
  
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  InPortPullConnector::~InPortPullConnector()
  {
    onDisconnect();
    disconnect();
  }
  
  /*!
   * @if jp
   * @brief read �ؿ�
   * @else
   * @brief Destructor
   * @endif
   */
  ConnectorBase::ReturnCode
  InPortPullConnector::read(cdrMemoryStream& data)
  {
    RTC_TRACE(("InPortPullConnector::read()"));
    if (m_consumer == 0)
      {
        return PORT_ERROR;
      }
    return m_consumer->get(data);
  }
  
  /*!
   * @if jp
   * @brief ��³����ؿ�
   * @else
   * @brief Disconnect connection
   * @endif
   */
  ConnectorBase::ReturnCode InPortPullConnector::disconnect()
  {
    RTC_TRACE(("disconnect()"));
    // delete consumer
    if (m_consumer != 0)
      {
        OutPortConsumerFactory& cfactory(OutPortConsumerFactory::instance());
        cfactory.deleteObject(m_consumer);
      }
    m_consumer = 0;

    return PORT_OK;
  }
  
  /*!
   * @if jp
   * @brief Buffer������
   * @else
   * @brief create buffer
   * @endif
   */
  CdrBufferBase* InPortPullConnector::createBuffer(ConnectorInfo& info)
  {
    std::string buf_type;
    buf_type = info.properties.getProperty("buffer_type",
                                              "ring_buffer");
    return CdrBufferFactory::instance().createObject(buf_type);
  }

  /*!
   * @if jp
   * @brief ��³��Ω���˥�����Хå���Ƥ�
   * @else
   * @brief Invoke callback when connection is established
   * @endif
   */
  void InPortPullConnector::onConnect()
  {
    m_listeners.connector_[ON_CONNECT].notify(m_profile);
  }

  /*!
   * @if jp
   * @brief ��³���ǻ��˥�����Хå���Ƥ�
   * @else
   * @brief Invoke callback when connection is destroied
   * @endif
   */
  void InPortPullConnector::onDisconnect()
  {
    m_listeners.connector_[ON_DISCONNECT].notify(m_profile);
  }
};

