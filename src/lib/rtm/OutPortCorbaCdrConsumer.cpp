// -*- C++ -*-
/*!
 * @file  OutPortCorbaCdrConsumer.h
 * @brief OutPortCorbaCdrConsumer class
 * @date  $Date: 2008-01-13 10:28:27 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009-2010
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPortCorbaCdrConsumer.h 1254 2009-04-07 01:09:35Z kurihara $
 *
 */

#include <rtm/Manager.h>
#include <rtm/OutPortCorbaCdrConsumer.h>
#include <rtm/NVUtil.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  OutPortCorbaCdrConsumer::OutPortCorbaCdrConsumer()
  {
    rtclog.setName("OutPortCorbaCdrConsumer");
  }
    
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  OutPortCorbaCdrConsumer::~OutPortCorbaCdrConsumer(void)
  {
  } 

  /*!
   * @if jp
   * @brief ��������
   * @else
   * @brief Initializing configuration
   * @endif
   */
  void OutPortCorbaCdrConsumer::init(coil::Properties& prop)
  {
    RTC_TRACE(("OutPortCorbaCdrConsumer::init()"));
  }

  /*!
   * @if jp
   * @brief �Хåե��򥻥åȤ���
   * @else
   * @brief Setting outside buffer's pointer
   * @endif
   */
  void OutPortCorbaCdrConsumer::setBuffer(CdrBufferBase* buffer)
  {
    RTC_TRACE(("OutPortCorbaCdrConsumer::setBuffer()"));
    m_buffer = buffer;
  }

  /*!
   * @if jp
   * @brief �ꥹ�ʤ����ꤹ�롣
   * @else
   * @brief Set the listener. 
   * @endif
   */
  void OutPortCorbaCdrConsumer::setListener(ConnectorInfo& info,
                                            ConnectorListeners* listeners)
  {
    RTC_TRACE(("OutPortCorbaCdrConsumer::setListener()"));
    m_listeners = listeners;
    m_profile = info;
  }

  /*!
   * @if jp
   * @brief �ǡ������ɤ߽Ф�
   * @else
   * @brief Read data
   * @endif
   */
  OutPortConsumer::ReturnCode
  OutPortCorbaCdrConsumer::get(cdrMemoryStream& data)
  {
    RTC_TRACE(("OutPortCorbaCdrConsumer::get()"));
    ::OpenRTM::CdrData_var cdr_data;

    try
      {
        ::OpenRTM::PortStatus ret(_ptr()->get(cdr_data.out()));

        if (ret == ::OpenRTM::PORT_OK)
          {
            RTC_DEBUG(("get() successful"));
            data.put_octet_array(&(cdr_data[0]), (int)cdr_data->length());
            RTC_PARANOID(("CDR data length: %d", cdr_data->length()));

            onReceived(data);
            onBufferWrite(data);

            if (m_buffer->full())
              {
                RTC_INFO(("InPort buffer is full."));
                onBufferFull(data);
                onReceiverFull(data);
              }
            m_buffer->put(data);
            m_buffer->advanceWptr();
            m_buffer->advanceRptr();

            return PORT_OK;
          }
        return convertReturn(ret, data);
      }
    catch (...)
      {
        RTC_WARN(("Exception caought from OutPort::get()."));
        return CONNECTION_LOST;
      }
    RTC_ERROR(("OutPortCorbaCdrConsumer::get(): Never comes here."));
    return UNKNOWN_ERROR;
  }
    
  /*!
   * @if jp
   * @brief �ǡ����������Τؤ���Ͽ
   * @else
   * @brief Subscribe the data receive notification
   * @endif
   */
  bool OutPortCorbaCdrConsumer::
  subscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("OutPortCorbaCdrConsumer::subscribeInterface()"));
    CORBA::Long index;
    index = NVUtil::find_index(properties,
                               "dataport.corba_cdr.outport_ior");
    if (index < 0)
      {
        RTC_DEBUG(("dataport.corba_cdr.outport_ior not found."));
        return false;
      }
    
    if (NVUtil::isString(properties,
                         "dataport.corba_cdr.outport_ior"))
      {
        RTC_DEBUG(("dataport.corba_cdr.outport_ior found."));
        const char* ior;
        properties[index].value >>= ior;

        CORBA::ORB_ptr orb = ::RTC::Manager::instance().getORB();
        CORBA::Object_var var = orb->string_to_object(ior);
        bool ret(setObject(var.in()));
        if (ret)
          {
            RTC_DEBUG(("CorbaConsumer was set successfully."));
          }
        else
          {
            RTC_ERROR(("Invalid object reference."))
          }
        return ret;
      }
    
    return false;
  }
  
  /*!
   * @if jp
   * @brief �ǡ����������Τ������Ͽ���
   * @else
   * @brief Unsubscribe the data receive notification
   * @endif
   */
  void OutPortCorbaCdrConsumer::
  unsubscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("OutPortCorbaCdrConsumer::unsubscribeInterface()"));
    CORBA::Long index;
    index = NVUtil::find_index(properties,
                               "dataport.corba_cdr.outport_ior");
    if (index < 0)
      {
        RTC_DEBUG(("dataport.corba_cdr.outport_ior not found."));
        return;
      }
    
    const char* ior;
    if (properties[index].value >>= ior)
      {
        RTC_DEBUG(("dataport.corba_cdr.outport_ior found."));
        CORBA::ORB_ptr orb = RTC::Manager::instance().getORB();
        CORBA::Object_var var = orb->string_to_object(ior);
        if (_ptr()->_is_equivalent(var))
          {
            releaseObject();
            RTC_DEBUG(("CorbaConsumer's reference was released."));
            return;
          }
        RTC_ERROR(("hmm. Inconsistent object reference."));
      }
  }

  /*!
   * @if jp
   * @brief �꥿���󥳡����Ѵ� (DataPortStatus -> BufferStatus)
   * @else
   * @brief Return codes conversion
   * @endif
   */
  OutPortConsumer::ReturnCode
  OutPortCorbaCdrConsumer::convertReturn(::OpenRTM::PortStatus status,
                                         const cdrMemoryStream& data)
  {
    switch(status)
      {
      case ::OpenRTM::PORT_OK:
        // never comes here
        return PORT_OK;
        break;
        
      case ::OpenRTM::PORT_ERROR:
        onSenderError();
        return PORT_ERROR;
        break;

      case ::OpenRTM::BUFFER_FULL:
        // never comes here
        return BUFFER_FULL;
        break;

      case ::OpenRTM::BUFFER_EMPTY:
        onSenderEmpty();
        return BUFFER_EMPTY;
        break;

      case ::OpenRTM::BUFFER_TIMEOUT:
        onSenderTimeout();
        return BUFFER_TIMEOUT;
        break;

      case ::OpenRTM::UNKNOWN_ERROR:
        onSenderError();
        return UNKNOWN_ERROR;
        break;

      default:
        onSenderError();
        return UNKNOWN_ERROR;
      }

    onSenderError();
    return UNKNOWN_ERROR;
  }


};     // namespace RTC

extern "C"
{
  /*!
   * @if jp
   * @brief �⥸�塼�������ؿ�
   * @else
   * @brief Module initialization
   * @endif
   */
  void OutPortCorbaCdrConsumerInit(void)
  {
    RTC::OutPortConsumerFactory&
      factory(RTC::OutPortConsumerFactory::instance());
    factory.addFactory("corba_cdr",
                       ::coil::Creator< ::RTC::OutPortConsumer,
                                        ::RTC::OutPortCorbaCdrConsumer>,
                       ::coil::Destructor< ::RTC::OutPortConsumer,
                                           ::RTC::OutPortCorbaCdrConsumer>);
  }
};
