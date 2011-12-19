// -*- C++ -*-
/*!
 * @file  MyServiceConsumer.h
 * @brief MyService Consumer Sample component
 * @date  $Date: 2008-02-29 04:55:08 $
 *
 * $Id: MyServiceConsumer.h 1562 2009-11-09 05:38:59Z kurihara $
 */

#ifndef MYSERVICECONSUMER_H
#define MYSERVICECONSUMER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <iostream>
#include <coil/Async.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "MyServiceStub.h"

// </rtc-template>

using namespace RTC;

class MyServiceConsumer
  : public RTC::DataFlowComponentBase
{
 public:
  MyServiceConsumer(RTC::Manager* manager);
  ~MyServiceConsumer();

  // The initialize action (on CREATED->ALIVE transition)
  // formaer rtc_init_entry() 
  virtual RTC::ReturnCode_t onInitialize();

  // The finalize action (on ALIVE->END transition)
  // formaer rtc_exiting_entry()
  // virtual RTC::ReturnCode_t onFinalize();

  // The startup action when ExecutionContext startup
  // former rtc_starting_entry()
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  // The shutdown action when ExecutionContext stop
  // former rtc_stopping_entry()
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  // The activated action (Active state entry action)
  // former rtc_active_entry()
  // virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  // The deactivated action (Active state exit action)
  // former rtc_active_exit()
  // virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  // The execution action that is invoked periodically
  // former rtc_active_do()
  virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  // The aborting action when main logic error occurred.
  // former rtc_aborting_entry()
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  // The error action in ERROR state
  // former rtc_error_do()
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  // The reset action that is invoked resetting
  // This is same but different the former rtc_init_entry()
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  // The state update action that is invoked after onExecute() action
  // no corresponding operation exists in OpenRTm-aist-0.2.0
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  // The action that is invoked when execution context's rate is changed
  // no corresponding operation exists in OpenRTm-aist-0.2.0
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  RTC::CorbaPort m_MyServicePort;
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  RTC::CorbaConsumer<SimpleService::MyService> m_myservice0;
  
  // </rtc-template>

  class set_value_functor
  {
  public:
    set_value_functor(CORBA::Float val) : m_val(val) {}

    void operator()(RTC::CorbaConsumer<SimpleService::MyService>* obj)
    {
      try
        {
          if( CORBA::is_nil((*obj).operator->()) )
            {
              std::cout << "No service connected." << std::endl;
            }
          else
            {
              (*obj)->set_value(m_val);
            }
        }
      catch (const CORBA::INV_OBJREF &)
        {
        }
      catch (const CORBA::OBJECT_NOT_EXIST &)
        {
        }
      catch (const CORBA::OBJ_ADAPTER &)
        {
        }
      catch (...)
        {
        }
    }
    CORBA::Float m_val;
  };

  class echo_functor
  {
  public:
    echo_functor(std::string msg, std::string& result)
      : m_msg(msg), m_result(result) {}
    void operator()(RTC::CorbaConsumer<SimpleService::MyService>* obj)
    {
      try
        {
          if( CORBA::is_nil((*obj).operator->()) )
            {
              std::cout << "No service connected." << std::endl;
            }
          else
            {
              m_result = (*obj)->echo(m_msg.c_str());
            }
        }
      catch (const CORBA::INV_OBJREF &)
        {
        }
      catch (const CORBA::OBJECT_NOT_EXIST &)
        {
        }
      catch (const CORBA::OBJ_ADAPTER &)
        {
        }
      catch (...)
        {
        }
    }
    std::string m_msg;
    std::string& m_result;
  };
 private:
  coil::Async* async_set_value;
  coil::Async* async_echo;
  std::string m_result;

  template <class T>
  struct seq_print
  {
    seq_print() : m_cnt(0) {};
    void operator()(T val)
    {
      std::cout << m_cnt << ": " << val << std::endl;
      ++m_cnt;
    }
    int m_cnt;
  };

};


extern "C"
{
  DLL_EXPORT void MyServiceConsumerInit(RTC::Manager* manager);
};

#endif // MYSERVICECONSUMER_H
