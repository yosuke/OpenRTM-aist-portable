// -*- C++ -*-
/*!
 * @file ExtTrigExecutionContext.h
 * @brief ExtTrigExecutionContext class
 * @date $Date: 2008-01-14 07:49:16 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ExtTrigExecutionContext.h 1569 2009-11-12 14:36:47Z n-ando $
 *
 */

#ifndef RTC_EXTTRIGEXECUTIONCONTEXT_H
#define RTC_EXTTRIGEXECUTIONCONTEXT_H

#include <rtm/RTC.h>

#include <coil/Mutex.h>
#include <coil/Condition.h>
#include <coil/Task.h>

#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class ExtTrigExecutionContext
   * @brief ���ƥå׼¹Ԥ���ǽ�� ExecutionContext ���饹
   *
   * 1������μ¹Ԥ���ǽ��Periodic Sampled Data Processing(�����¹���)
   * ExecutionContext���饹��
   * ��������Υ᥽�åɸƤӤ����ˤ�äƻ��֤�1�����ŤĿʤࡣ
   *
   * @since 0.4.0
   *
   * @else
   * @brief ExecutionContext class that enables one step execution
   *
   * ExecutionContext class that can execute every one cycle for Periodic
   * Sampled Data Processing.
   * Time(Tick) advances one cycle by invoking method externally.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ExtTrigExecutionContext
    : public virtual PeriodicExecutionContext
  {
    typedef coil::Mutex Mutex;
    typedef coil::Condition<Mutex> Condition;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    ExtTrigExecutionContext();
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~ExtTrigExecutionContext(void);
    
    /*!
     * @if jp
     * @brief ������1���ƥå׿ʤ��
     *
     * ExecutionContext�ν�����1����ʬ�ʤ�롣
     *
     * @else
     * @brief Move forward one step of ExecutionContext
     *
     * Move forward one step of the ExecutionContext processing.
     *
     * @endif
     */
    virtual void tick()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief �� Component �ν�����ƤӽФ���
     *
     * ExecutionContext �� attach ����Ƥ���� Component �ν�����ƤӽФ���
     * �� Component �ν�����ƤӽФ����塢���θƽФ�ȯ������ޤǵٻߤ��롣
     *
     * @return �������
     *
     * @else
     * @brief Invoke each component's operation
     *
     * Invoke each component's operation which is attached this ExecutionContext.
     * Stop until the next operation is invoked after all component operations
     * are invoked.
     *
     * @return Operation result
     *
     * @endif
     */
    virtual int svc(void);
    
  private:
    struct Worker
    {
      Worker() : _cond(_mutex), _called(false) {};
      Mutex _mutex;
      Condition _cond;
      bool _called;
    };
    // A condition variable for external triggered worker
    Worker m_worker;
  };  // class ExtTrigExecutionContext
};  // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif


extern "C"
{
  /*!
   * @if jp
   * @brief ���� ExecutionContext ��Factory���饹����Ͽ��
   *
   * ����ExecutionContext����������Factory���饹��
   * ExecutionContext������ObjectManager����Ͽ���롣
   *
   * @else
   * @brief Register Factory class for this ExecutionContext
   *
   * Register the Factory class to create this ExecutionContext
   * to the ObjectManager for management ExecutionContext
   *
   * @endif
   */
  void ExtTrigExecutionContextInit(RTC::Manager* manager);
};

#endif // RTC_EXTTRIGEXECUTIONCONTEXT_H
