// -*- C++ -*-
/*!
 * @file Task_win32.h
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

#ifndef COIL_TASK_H
#define COIL_TASK_H

#include <windows.h>
#include <process.h>


namespace coil
{
  /*!
   * @if jp
   *
   * @class Task
   * @brief Task �N���X
   *
   * @else
   *
   * @class Task
   * @brief Task class
   *
   * @endif
   */
  class Task
  {
  public:
    /*!
     * @if jp
     *
     * @brief �R���X�g���N�^
     *
     * �R���X�g���N�^
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    Task();

    /*!
     * @if jp
     *
     * @brief �f�X�g���N�^
     *
     * �f�X�g���N�^
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~Task();

    /*!
     * @if jp
     *
     * @brief �^�X�N�I�[�v��
     *
     * �^�X�N�I�[�v��
     *
     * @param args ����
     *
     * @else
     *
     * @brief Task open
     *
     * Task open
     *
     * @param args Arguments
     *
     * @endif
     */
    virtual int open(void* args = 0);

    /*!
     * @if jp
     *
     * @brief �^�X�N�N���[�Y
     *
     * �^�X�N�N���[�Y
     *
     * @param flags �t���O
     *
     * @else
     *
     * @brief Task close
     *
     * Task close
     *
     * @param flags Flags
     *
     * @endif
     */
    virtual int close(unsigned long flags = 0);

    /*!
     * @if jp
     *
     * @brief �X���b�h�����s����
     *
     * �X���b�h�����s����
     *
     * @else
     *
     * @brief Execute thread
     *
     * Execute thread
     *
     * @endif
     */
    virtual int svc();

    /*!
     * @if jp
     *
     * @brief �X���b�h�𐶐�����
     *
     * �X���b�h�𐶐�����
     *
     * @else
     *
     * @brief Create a thread
     *
     * Create a thread
     *
     * @endif
     */
    virtual void activate();

    /*!
     * @if jp
     *
     * @brief �X���b�h�I����҂�
     *
     * �X���b�h�I����҂�
     *
     * @else
     *
     * @brief Waiting for the thread terminate
     *
     * Waiting for the thread terminate
     *
     * @endif
     */
    virtual int wait(void);

    /*!
     * @if jp
     *
     * @brief �^�X�N���s�𒆒f����
     *
     * �^�X�N���s�𒆒f����
     *
     * @else
     *
     * @brief Suspending the task
     *
     * Suspending the task
     *
     * @endif
     */
    virtual int suspend(void);

    /*!
     * @if jp
     *
     * @brief ���f����Ă���^�X�N���ĊJ����
     *
     * ���f����Ă���^�X�N���ĊJ����
     *
     * @else
     *
     * @brief Resuming the suspended task
     *
     * Resuming the suspended task
     *
     * @endif
     */
    virtual int resume(void);

    /*!
     * @if jp
     *
     * @brief �^�X�N�����Z�b�g
     *
     * �^�X�N�����Z�b�g
     *
     * @else
     *
     * @brief Reset of task count
     *
     * Reset of task count
     *
     * @endif
     */
    virtual void reset();

    /*!
     * @if jp
     *
     * @brief �^�X�N���s���I������
     *
     * �^�X�N���s���I������
     *
     * @else
     *
     * @brief Finalizing the task
     *
     * Finalizing the task.
     *
     * @endif
     */
    virtual void finalize();

    /*!
     * @if jp
     *
     * @brief �X���b�h���s���J�n����
     *
     * �X���b�h���s���J�n����
     *
     * @param args �X���b�h����
     *
     * @else
     *
     * @brief Start thread Execution
     *
     * Start thread Execution
     *
     * @param args Thread arguments
     *
     * @endif
     */
    static unsigned int WINAPI svc_run(void* args = 0);

  private:
    int m_count;
    HANDLE m_thread;
  };
};

#endif // COIL_TASK_H
