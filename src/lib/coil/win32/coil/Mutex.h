// -*- C++ -*-
/*!
 * @file  Mutex_win32.h
 * @brief mutex class
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_MUTEX_H
#define COIL_MUTEX_H

#include <windows.h>

namespace coil
{
  typedef HANDLE pthread_mutex_t;
  
  /*!
   * @if jp
   *
   * @class Mutex
   * @brief Mutex �N���X
   *
   * @else
   *
   * @class Mutex
   * @brief Mutex class
   *
   * @endif
   */
  class Mutex
  {
  public:
    /*!
     * @if jp
     *
     * @brief �R���X�g���N�^
     *
     * �R���X�g���N�^�B
     *
     * @param name �I�u�W�F�N�g��
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Object name
     *
     * @endif
     */
    Mutex(const char * const name = 0)
    {
        SECURITY_DESCRIPTOR sd_buffer;
        ::InitializeSecurityDescriptor(&sd_buffer, 
                                       SECURITY_DESCRIPTOR_REVISION);
        ::SetSecurityDescriptorDacl (&sd_buffer, TRUE, 0, FALSE);
		m_Security_attr.nLength = sizeof(SECURITY_ATTRIBUTES);
		m_Security_attr.lpSecurityDescriptor = &sd_buffer;
		m_Security_attr.bInheritHandle = TRUE;
		mutex_ = ::CreateMutexA( &m_Security_attr,
		                         FALSE,
                                         name );


    }

    /*!
     * @if jp
     *
     * @brief �f�X�g���N�^
     *
     * �f�X�g���N�^�B
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    ~Mutex()
    {
		::CloseHandle(mutex_);
		
    }

    /*!
     * @if jp
     *
     * @brief �r������̃��b�N
     *
     * �r������̃��b�N���s���B
     *
     * @else
     *
     * @brief Mutual exclusion lock
     *
     * Lock the Mutual exclusion.
     *
     * @endif
     */
    inline void lock()
    {
		::WaitForSingleObject(mutex_,INFINITE);
    }

    /*!
     * @if jp
     *
     * @brief �r������̃m���u���b�L���O���b�N
     *
     * �r������̃��b�N���m���u���b�L���O�ōs���B
     *
     * @else
     *
     * @brief Mutual exclusion non-blocking lock
     *
     * Lock the Mutual exclusion by non-blocking.
     *
     * @endif
     */
    inline bool trylock()
    {
        unsigned long dwret;
		dwret = ::WaitForSingleObject(mutex_,0);
        switch(dwret)
		{
		  case WAIT_ABANDONED:
			  return true;
			  break;
		  case WAIT_OBJECT_0:
			  return false;
		  case WAIT_TIMEOUT:
			  return true;
		  default:
			  return true;
		}
    }

    /*!
     * @if jp
     *
     * @brief �r������̃��b�N����
     *
     * �r������̃��b�N�������s���B
     *
     * @else
     *
     * @brief Mutual exclusion unlock
     *
     * Unlock the Mutual exclusion.
     *
     * @endif
     */
    inline void unlock()
    {
		::ReleaseMutex(mutex_);
    }
    HANDLE mutex_;
    
  private:
    SECURITY_ATTRIBUTES m_Security_attr;

	Mutex(const Mutex&);
    Mutex& operator=(const Mutex &);
  };
};
#endif // COIL_MUTEX_H
