// -*- C++ -*-
/*!
 * @file Timer.cpp
 * @brief Timer class
 * @date $Date: 2007-07-20 16:12:58 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Timer.cpp 826 2008-08-26 08:13:39Z n-ando $
 *
 */

#include <coil/Listener.h>
#include <coil/Timer.h>
#include <coil/Time.h>
namespace coil
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  Timer::Timer(TimeValue& interval)
    : m_interval(interval), m_running(false)
  {
  }
  
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  Timer::~Timer()
  {
    stop();
    wait();
  }
  
  /*!
   * @if jp
   * @brief Timer �ѥ���å�����
   * @else
   * @brief Generate thread for Timer
   * @endif
   */
  int Timer::open(void *args)
  {
    activate();
    return 0;
  }
  
  /*!
   * @if jp
   * @brief Timer �ѥ���åɼ¹Դؿ�
   * @else
   * @brief Thread execution function for Timer
   * @endif
   */
  int Timer::svc(void)
  {
    TimeValue t_curr, t_pre, tm;;
    while (m_running)
      {
	invoke();
        coil::sleep(m_interval);
      }
    return 0;
  }
  
  //============================================================
  // public functions
  //============================================================
  /*!
   * @if jp
   * @brief Timer ����������
   * @else
   * @brief Start Timer task
   * @endif
   */
  void Timer::start()
  {
    Guard guard(m_runningMutex);
    if (!m_running) 
      {
	m_running = true;
	open(0);
      }
  }
  
  /*!
   * @if jp
   * @brief Timer ���������
   * @else
   * @brief Stop Timer tast
   * @endif
   */
  void Timer::stop()
  {
    Guard guard(m_runningMutex);
    m_running = false;
  }
  
  /*!
   * @if jp
   * @brief Timer �������¹�
   * @else
   * @brief Invoke Timer task
   * @endif
   */
  void Timer::invoke()
  {
    Guard guard(m_taskMutex);
    for (size_t i(0), len(m_tasks.size()); i < len; ++i)
      {
	m_tasks[i].remains = m_tasks[i].remains - m_interval;
	if (m_tasks[i].remains.sign() <= 0)
	  {
	    m_tasks[i].listener->invoke();
	    m_tasks[i].remains = m_tasks[i].period;
	  }
      }
  }
  
  /*!
   * @if jp
   * @brief �ꥹ�ʡ���Ͽ
   * @else
   * @brief Register listener
   * @endif
   */
  ListenerId Timer::registerListener(ListenerBase* listener, TimeValue tm)
  {
    Guard guard(m_taskMutex);
    
    for (size_t i(0), len(m_tasks.size()); i < len; ++i)
      {
	if (m_tasks[i].listener == listener)
	  {
	    m_tasks[i].period = tm;
	    m_tasks[i].remains = tm;
	    return listener;
	  }
      }
    m_tasks.push_back(Task(listener, tm));
    return listener;
  }
  
  /*!
   * @if jp
   * @brief �ꥹ�ʡ���Ͽ���
   * @else
   * @brief Unregister listener
   * @endif
   */
  bool Timer::unregisterListener(ListenerId id)
  {
    Guard guard(m_taskMutex);
    std::vector<Task>::iterator it;
    it = m_tasks.begin();
    
    for (size_t i(0), len(m_tasks.size()); i < len; ++i, ++it)
      {
	if (m_tasks[i].listener == id)
	  {
	    m_tasks.erase(it);
	    return true;
	  }
      }
    return false;
  }
}; // namespace RTC
