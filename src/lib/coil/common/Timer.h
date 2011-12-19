// -*- C++ -*-
/*!
 * @file Timer.h
 * @brief Timer class
 * @date $Date: 2007-04-26 15:34:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Timer.h 826 2008-08-26 08:13:39Z n-ando $
 *
 */

#ifndef Timer_h
#define Timer_h

#include <coil/TimeValue.h>
#include <coil/Listener.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <coil/Task.h>
#include <vector>

typedef ListenerBase* ListenerId;

namespace coil
{
  /*!
   * @if jp
   * @class Timer
   * @brief Timer���饹
   * 
   * ��Ͽ���줿�ꥹ�ʡ��Υ�����Хå��ؿ������ꤵ�줿���������Ū�˸ƤӽФ���
   *
   * @since 0.4.0
   *
   * @else
   * @class Timer
   * @brief Timer class
   * 
   * Invoke the callback function of registered listener periodically
   * at the set cycle.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class Timer
    : public coil::Task
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param interval �����޵�ư����
     *
     * @else
     * @brief Constructor
     * 
     * Constructor
     *
     * @param interval The interval of timer
     *
     * @endif
     */
    Timer(TimeValue& interval);
    
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
    virtual ~Timer();
    
    //============================================================
    // ACE_Task 
    //============================================================
    /*!
     * @if jp
     * @brief Timer �ѥ���å�����
     *
     * Timer �Ѥ���������åɤ���������ư���롣
     * ����� ACE_Task �����ӥ����饹�᥽�åɤΥ����С��饤�ɡ�
     *
     * @param args �̾��0
     *
     * @return ���������¹Է��
     *
     * @else
     * @brief Create thread for Timer
     *
     * Create an internal thread for Timer and launch it.
     * This is an override of ACE_Task service class method.
     *
     * @param args Usually 0
     *
     * @return Creation processing result
     *
     * @endif
     */     
    virtual int open(void *args);
    
    /*!
     * @if jp
     * @brief Timer �ѤΥ���åɼ¹Դؿ�
     *
     * Timer �ѤΥ���åɼ¹Դؿ���
     * ��Ͽ���줿�ꥹ�ʡ��Υ�����Хå��ؿ���ƤӽФ���
     *
     * @return �¹Է��
     *
     * @else
     * @brief Thread execution function for Timer
     *
     * Thread execution function for Timer.
     * Invoke the callback function of registered listener.
     *
     * @return Execution result
     *
     * @endif
     */     
    virtual int svc(void);
    
    //============================================================
    // public functions
    //============================================================
    /*!
     * @if jp
     * @brief Timer ����������
     *
     * Timer �ѿ�������åɤ��������������򳫻Ϥ��롣
     *
     * @else
     * @brief Start Timer task
     *
     * Create a new theread for Timer and start processing.
     *
     * @endif
     */
    void start();
    
    /*!
     * @if jp
     * @brief Timer ���������
     *
     * Timer ����������ߤ��롣
     *
     * @else
     * @brief Stop Timer task
     *
     * Stop Timer task.
     *
     * @endif
     */
    void stop();
    
    /*!
     * @if jp
     * @brief Timer �������¹�
     *
     * ��Ͽ���줿�ƥꥹ�ʤε�ư�Ԥ����֤��饿���޵�ư�����򸺻����롣
     * ��ư�Ԥ����֤�����Ȥʤä��ꥹ�ʤ�¸�ߤ�����ϡ�
     * ������Хå��ؿ���ƤӽФ���
     *
     * @else
     * @brief Invoke Timer task
     *
     * Subtract the interval of timer from the waiting time for invocation
     * of each registered listener.
     * If the listener whose waiting time reached 0 exists, invoke the
     * callback function.
     *
     * @endif
     */
    void invoke();
    
    /*!
     * @if jp
     * @brief �ꥹ�ʡ���Ͽ
     *
     * �� Timer ���鵯ư���륳����Хå��ؿ��ѤΥꥹ�ʡ���ư��������ꤷ��
     * ��Ͽ���롣
     * Ʊ��ꥹ�ʡ���������Ͽ�Ѥߤξ��ϡ��ꥹ�ʡ��ε�ư��������ꤷ���ͤ�
     * �������롣
     *
     * @param listener ��Ͽ�оݥꥹ�ʡ�
     * @param tm �ꥹ�ʡ���ư����
     *
     * @return ��Ͽ�ꥹ�ʡ�ID
     *
     * @else
     * @brief Register listener
     *
     * Register the listener of callback function invoked from this Timer by
     * specifying the interval.
     * If the same listener has already been regiseterd, the value specified
     * the invocation interval of listener will be updated.
     * 
     *
     * @param listener Listener for the registration
     * @param tm The invocation interval of listener
     *
     * @return ID of the registerd listener
     *
     * @endif
     */
    ListenerId registerListener(ListenerBase* listener, TimeValue tm);
    
    /*!
     * @if jp
     * @brief �ꥹ�ʡ���Ͽ
     *
     * ������Хå��оݥ��֥������ȡ�������Хå��оݥ᥽�åɤ���ӵ�ư������
     * ���ꤷ�ƥꥹ�ʡ�����Ͽ���롣
     *
     * @param obj ������Хå��оݥ��֥�������
     * @param cbf ������Хå��оݥ᥽�å�
     * @param tm �ꥹ�ʡ���ư����
     *
     * @return ��Ͽ�ꥹ�ʡ�ID
     *
     * @else
     * @brief Register listener
     *
     * Register listener by specifying the object for callback, the method
     * for callback and the invocation interval.
     *
     * @param obj Target object for callback
     * @param cbf Target method for callback
     * @param tm The invocation interval of listener
     *
     * @return ID of the registerd listener
     *
     * @endif
     */
    template <class ListenerClass>
    ListenerId registerListenerObj(ListenerClass* obj,
				   void (ListenerClass::*cbf)(),
				   TimeValue tm)
    {
      return registerListener(new ListenerObject<ListenerClass>(obj, cbf), tm);
    }
    
    /*!
     * @if jp
     * @brief �ꥹ�ʡ���Ͽ
     *
     * ������Хå��оݥ᥽�åɤȵ�ư��������ꤷ�ƥꥹ�ʡ�����Ͽ���롣
     *
     * @param cbf ������Хå��оݥ᥽�å�
     * @param tm �ꥹ�ʡ���ư����
     *
     * @return ��Ͽ�ꥹ�ʡ�ID
     *
     * @else
     * @brief Register listener
     *
     * Register listener by specifying the method for callback and the
     * invocation interval.
     *
     * @param cbf Target method for callback
     * @param tm The invocation interval of listener
     *
     * @return ID of the registerd listener
     *
     * @endif
     */
    ListenerId registerListenerFunc(void (*cbf)(), TimeValue tm)
    {
      return registerListener(new ListenerFunc(cbf), tm);
    }
    
    /*!
     * @if jp
     * @brief �ꥹ�ʡ���Ͽ���
     *
     * ���ꤷ��ID�Υꥹ�ʡ�����Ͽ�������롣
     * ���ꤷ��ID�Υꥹ�ʡ���̤��Ͽ�ξ�硢false ���֤���
     *
     * @param id ��Ͽ����оݥꥹ�ʡ�ID
     *
     * @return ��Ͽ������
     *
     * @else
     * @brief Unregister listener
     *
     * Unregister the listener specified by ID.
     * If the listener specified by ID is not registerd, false will be returned.
     *
     * @param id ID of the unregisterd listener
     *
     * @return Unregistration result
     *
     * @endif
     */
    bool unregisterListener(ListenerId id);
    
  private:
    TimeValue m_interval;
    
    Mutex m_runningMutex;
    bool m_running;
    
    struct Task
    {
      Task(ListenerBase* l, TimeValue p)
	: listener(l), period(p), remains(p)
      {
      }
      ListenerBase* listener;
      TimeValue period;
      TimeValue remains;
    };
    
    std::vector<Task> m_tasks;
    Mutex  m_taskMutex;
  };
};
#endif // Timer_h

