// -*- C++ -*-
/*!
 * @file Task_posix.cpp
 * @brief Task class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/Task.h>

namespace coil
{

  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  Task::Task()
    : m_count(0)
  {
    ::pthread_attr_init(&m_attr);
  }

  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  Task::~Task()
  {
    m_count = 0;
  }

  /*!
   * @if jp
   * @brief �����������ץ�
   * @else
   * @brief Task open
   * @endif
   */
  int Task::open(void* args)
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief ������������
   * @else
   * @brief Task close
   * @endif
   */
  int Task::close(unsigned long flags)
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief ����åɤ�¹Ԥ���
   * @else
   * @brief Execute thread
   * @endif
   */
  int Task::svc()
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief ����åɤ���������
   * @else
   * @brief Create a thread
   * @endif
   */
  void Task::activate()
  {
    if (m_count == 0)
      {
        ::pthread_create(&m_thread,
                         &m_attr,
                         (void* (*)(void*))Task::svc_run,
                         this);
        ++m_count;
      };
  }

  /*!
   * @if jp
   * @brief ����åɽ�λ���Ԥ�
   * @else
   * @brief Waiting for the thread terminate
   * @endif
   */
  int Task::wait(void)
  {
    if (m_count > 0)
      {
        void* retval;
        ::pthread_join(m_thread, &retval);
      }
    return 0;
  }

  /*!
   * @if jp
   * @brief �������¹Ԥ����Ǥ���
   * @else
   * @brief Suspending the task
   * @endif
   */
  int Task::suspend(void)
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief ���Ǥ���Ƥ��륿������Ƴ�����
   * @else
   * @brief Resuming the suspended task
   * @endif
   */
  int Task::resume(void)
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief ���������ꥻ�å�
   * @else
   * @brief Reset of task count
   * @endif
   */
  void Task::reset()
  {
    m_count = 0;
  }

  /*!
   * @if jp
   * @brief �������¹Ԥ�λ����
   * @else
   * @brief Finalizing the task
   * @endif
   */
  void Task::finalize()
  {
    reset();
  }

  /*!
   * @if jp
   * @brief ����åɼ¹Ԥ򳫻Ϥ���
   * @else
   * @brief Start thread Execution
   * @endif
   */
  void* Task::svc_run(void* args)
  {
    Task* t = (coil::Task*)args;
    int status;
    status = t->svc();
    t->finalize();
    return 0;
  }
};


