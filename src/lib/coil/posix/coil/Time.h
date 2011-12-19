// -*- C++ -*-
/*!
 * @file Time_posix.h
 * @brief Time functions
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

#ifndef COIL_TIME_H
#define COIL_TIME_H

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <iostream>
#include <coil/config_coil.h>
#include <coil/TimeValue.h>

namespace coil
{

  /*!
   * @if jp
   * @brief ���ꤵ�줿�ô֤Ͻ�����ٻߤ���
   *
   * ���ꤵ�줿�ô֤Ͻ�����ٻߤ��롣
   *
   * @param seconds �ÿ�
   *
   * @return 0: ����, >0: ����
   *
   * @else
   * @brief Stop a processing at specified second time
   *
   * Stop a processing at specified second time.
   *
   * @param seconds Second time
   *
   * @return 0: successful, >0: failed
   *
   * @endif
   */
  inline unsigned int sleep(unsigned int seconds)
  {
    return ::sleep(seconds);
  }

  /*!
   * @if jp
   * @brief ���ꤵ�줿�ô֤Ͻ�����ٻߤ���
   *
   * ���ꤵ�줿�ô֤Ͻ�����ٻߤ��롣
   *
   * @param interval TimeValue���֥�������
   *
   * @return 0: ����, >0: ����
   *
   * @else
   * @brief Stop a processing at specified second time
   *
   * Stop a processing at specified second time.
   *
   * @param interval TimeValue object
   *
   * @return 0: successful, >0: failed
   *
   * @endif
   */
  inline int sleep(TimeValue interval)
  {
    timeval tv;
    tv.tv_sec = interval.sec();
    tv.tv_usec = interval.usec();
    return ::select(0, 0, 0, 0, &tv);
  }

  /*!
   * @if jp
   * @brief ���ꤵ�줿�ޥ������ô֤Ͻ�����ٻߤ���
   *
   * ���ꤵ�줿�ޥ������ô֤Ͻ�����ٻߤ��롣
   *
   * @param usec �ޥ������ÿ�
   *
   * @return 0: ����, -1: ����
   *
   * @else
   * @brief Stop a processing at specified micro second time
   *
   * Stop a processing at specified micro second time.
   *
   * @param usec Micro second time
   *
   * @return 0: successful, -1: failed
   *
   * @endif
   */
  inline int usleep(useconds_t usec)
  {
    return ::usleep(usec);
  }

  /*!
   * @if jp
   * @brief ����ȥ����ॾ������������
   *
   * ����ȥ����ॾ�����������롣
   *
   * @param tv ���ﹽ¤��
   * @param tz �����ॾ����¤��
   *
   * @return 0: ����, -1: ����
   *
   * @else
   * @brief Get the time and timezone
   *
   * Get the time and timezone
   *
   * @param tv Structure of time
   * @param tz Structure of timezone
   *
   * @return 0: successful, -1: failed
   *
   * @endif
   */
  inline int gettimeofday(struct timeval *tv, struct timezone *tz)
  {
    return ::gettimeofday(tv, tz);
  }

  /*!
   * @if jp
   * @brief ������������
   *
   * �����������롣
   *
   * @return TimeValue���֥�������
   *
   * @else
   * @brief Get the time
   *
   * Get the time
   *
   * @return TimeValue object
   *
   * @endif
   */
  inline TimeValue gettimeofday()
  {
    timeval tv;
    ::gettimeofday(&tv, 0);
    return TimeValue(tv.tv_sec, tv.tv_usec);
  }

  /*!
   * @if jp
   * @brief ����ȥ����ॾ��������ꤹ��
   *
   * ����ȥ����ॾ��������ꤹ�롣
   *
   * @param tv ���ﹽ¤��
   * @param tz �����ॾ����¤��
   *
   * @return 0: ����, -1: ����
   *
   * @else
   * @brief Set the time and timezone
   *
   * Set the time and timezone
   *
   * @param tv Structure of time
   * @param tz Structure of timezone
   *
   * @return 0: successful, -1: failed
   *
   * @endif
   */
  inline int settimeofday(const struct timeval *tv , const struct timezone *tz)
  {
    return ::settimeofday(tv, tz);
  }


};

#endif // COIL_TIME_H
