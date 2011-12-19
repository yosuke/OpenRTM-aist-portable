// -*- C++ -*-
/*!
 * @file Task_win32.cpp
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
   * @brief �R���X�g���N�^
   * @else
   * @brief Constructor
   * @endif
   */
  Task::Task()
    : m_count(0)
  {
  }

  /*!
   * @if jp
   * @brief �f�X�g���N�^
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
   * @brief �^�X�N�I�[�v��
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
   * @brief �^�X�N�N���[�Y
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
   * @brief �X���b�h�����s����
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
   * @brief �X���b�h�𐶐�����
   * @else
   * @brief Create a thread
   * @endif
   */
  void Task::activate()
  {
    if (m_count == 0)
      {
		  m_thread =
			  (HANDLE)::_beginthreadex(NULL, // security
			  0, //stuck size
			  Task::svc_run, // func
			  (void*)this, // argument
			  0, // flag (0 or CREATE_SUSPEND)
			  NULL); //thread descripter
		  ++m_count;
      };
  }

  /*!
   * @if jp
   * @brief �X���b�h�I����҂�
   * @else
   * @brief Waiting for the thread terminate
   * @endif
   */
  int Task::wait(void)
  {
    if (m_count > 0)
      {
        DWORD retval;
	retval = ::WaitForSingleObject(m_thread, INFINITE);
      }
    return 0;
  }

  /*!
   * @if jp
   * @brief �^�X�N���s�𒆒f����
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
   * @brief ���f����Ă���^�X�N���ĊJ����
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
   * @brief �^�X�N�����Z�b�g
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
   * @brief �^�X�N���s���I������
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
   * @brief �X���b�h���s���J�n����
   * @else
   * @brief Start thread Execution
   * @endif
   */
  unsigned int WINAPI Task::svc_run(void* args)
  {
    Task* t = (coil::Task*)args;
    int status;
    status = t->svc();
    t->finalize();
    return 0;
  }
};


