// -*- C++ -*-
/*!
 * @file ExtTrigExecutionContext.cpp
 * @brief ExtTrigExecutionContext class
 * @date $Date: 2008-01-14 07:49:14 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ExtTrigExecutionContext.cpp 1220 2009-02-27 06:49:20Z n-ando $
 *
 */

#include <coil/TimeValue.h>
#include <rtm/ExtTrigExecutionContext.h>
#include <rtm/ECFactory.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  ExtTrigExecutionContext::ExtTrigExecutionContext()
    : PeriodicExecutionContext()
  {
    rtclog.setName("exttrig_ec");
  }
  
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  ExtTrigExecutionContext::~ExtTrigExecutionContext()
  {
  }
  
  /*!
   * @if jp
   * @brief ������1���ƥå׿ʤ��
   * @else
   * @brief Move forward one step of ExecutionContext
   * @endif
   */
  void ExtTrigExecutionContext::tick()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("tick()"));
    m_worker._mutex.lock();
    m_worker._called = true;
    m_worker._cond.signal();
    m_worker._mutex.unlock();
    return;
  }
  
  /*!
   * @if jp
   * @brief �� Component �ν�����ƤӽФ���
   * @else
   * @brief Invoke each component's operation
   * @endif
   */
  int ExtTrigExecutionContext::svc(void)
  {
    RTC_TRACE(("svc()"));
    do
      {
	m_worker._mutex.lock();
	while (!m_worker._called && m_running)
	  {
	    m_worker._cond.wait();
	  }
	if (m_worker._called)
	  {
	    m_worker._called = false;
	    std::for_each(m_comps.begin(), m_comps.end(), invoke_worker());
	  }
	m_worker._mutex.unlock();
      } while (m_running);
    
    return 0;
  }
};


extern "C"
{
  /*!
   * @if jp
   * @brief ���� ExecutionContext ��Factory���饹����Ͽ��
   * @else
   * @brief Register Factory class for this ExecutionContext
   * @endif
   */
  void ExtTrigExecutionContextInit(RTC::Manager* manager)
  {
    manager->registerECFactory("ExtTrigExecutionContext",
			       RTC::ECCreate<RTC::ExtTrigExecutionContext>,
			       RTC::ECDelete<RTC::ExtTrigExecutionContext>);
  }
};
