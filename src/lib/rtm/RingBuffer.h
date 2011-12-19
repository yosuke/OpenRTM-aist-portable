// -*- C++ -*-
/*!
 * @file RingBuffer.h
 * @brief Defautl Buffer class
 * @date $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RingBuffer.h 2015 2010-12-29 11:33:33Z n-ando $
 *
 */

#ifndef RTC_RINGBUFFER_H
#define RTC_RINGBUFFER_H

#include <vector>
#include <algorithm>
#include <iostream>

#include <coil/TimeValue.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <coil/Condition.h>
#include <coil/stringutil.h>

#include <rtm/BufferBase.h>
#include <rtm/BufferStatus.h>

#define RINGBUFFER_DEFAULT_LENGTH 8
/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RT����ݡ��ͥ��
 *
 * @else
 *
 * @namespace RTC
 *
 * @brief RT-Component
 *
 * @endif
 */
namespace RTC
{
  /*!
   * @if jp
   * @class RingBuffer
   * @brief ��󥰥Хåե��������饹
   * 
   * ���ꤷ��Ĺ���Υ�󥰾��Хåե�����ĥХåե��������饹��
   * �Хåե����Τ˥ǡ�������Ǽ���줿��硢�ʹߤΥǡ����ϸŤ��ǡ�������
   * �缡��񤭤���롣
   * ���äơ��Хåե���ˤ�ľ��ΥХåե�Ĺʬ�Υǡ����Τ��ݻ�����롣
   *
   * ��)���ߤμ����Ǥϡ����ֺǸ�˳�Ǽ�����ǡ����ΤߥХåե������ɤ߽Ф���ǽ
   *
   * @param DataType �Хåե��˳�Ǽ����ǡ�����
   *
   * @since 0.4.0
   *
   * @else
   * @class RingBuffer
   * @brief Ring buffer implementation class
   * 
   * This is the buffer implementation class with ring shaped buffer of
   * specified length.
   * If data is stored in the entire buffer, data from now on will be
   * overwritten from old data one by one.
   * Therefore, only the length of latest data is stored in the buffer.
   *
   * Note: In the current implementation, only last stored data can be read
   *       from the buffer.
   *
   * @param DataType Data type to store in the buffer
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  class RingBuffer
    : public BufferBase<DataType>
  {
  public:
    BUFFERSTATUS_ENUM
    typedef coil::Guard<coil::Mutex> Guard;
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     * ���ꤵ�줿�Хåե�Ĺ�ǥХåե����������롣
     *
     * @param length �Хåե�Ĺ
     * 
     * @else
     *
     * @brief Constructor
     * 
     * Constructor.
     * Initialize the buffer by specified buffer length.
     * However, if the specified length is less than two, the buffer should
     * be initialized by two in length.
     *
     * @param length Buffer length
     * 
     * @endif
     */
    RingBuffer(long int length = RINGBUFFER_DEFAULT_LENGTH)
      : m_overwrite(true), m_readback(true),
        m_timedwrite(false), m_timedread(false),
        m_wtimeout(1, 0), m_rtimeout(1, 0),
        m_length(length),
        m_wpos(0), m_rpos(0), m_fillcount(0), m_wcount(0),
        m_buffer(m_length)
    {
      this->reset();
    }
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     * 
     * @else
     *
     * @brief Virtual destractor
     * 
     * Virtual destractor
     * 
     * @endif
     */
    virtual ~RingBuffer(void)
    {
    }
    
    /*!
     * @if jp
     * @brief �Хåե�������
     *
     * coil::Properties ��Ϳ������ץ�ѥƥ��ˤ�ꡢ
     * �Хåե���������������롣
     * ���ѤǤ��륪�ץ����Ȱ�̣�ϰʲ����̤�
     *
     * - buffer.length:
     *     �Хåե���Ĺ�����������ʳ��ο��ͤ����ꤵ��Ƥ�̵�뤵��롣��
     *     �Ǥ˥Хåե������Ѿ��֤Ǥ⡢Ĺ���������ꤵ�줿�Τ������٤Ƥ�
     *     �ݥ��󥿤����������롣
     *
     * - buffer.write.full_policy:
     *     ��񤭤��뤫�ɤ����Υݥꥷ����
     *     overwrite (���), do_nothing (���⤷�ʤ�), block (�֥�å�����)
     *     block ����ꤷ����硢���� timeout �ͤ���ꤹ��С�������ָ�
     *     �񤭹����Բ�ǽ�Ǥ���Х����ॢ���Ȥ��롣
     *     �ǥե���Ȥ�  overwrite (���)��
     *
     * - buffer.write.timeout:
     *     �����ॢ���Ȼ��֤� [sec] �ǻ��ꤹ�롣�ǥե���Ȥ� 1.0 [sec]��
     *     1 sec -> 1.0, 1 ms -> 0.001, �����ॢ���Ȥ��ʤ� -> 0.0
     *
     * - buffer.read.empty_policy:
     *     �Хåե������ΤȤ����ɤ߽Ф��ݥꥷ����
     *     readback (�Ǹ������), do_nothing (���⤷�ʤ�), block (�֥�å�����)
     *     block ����ꤷ����硢���� timeout �ͤ���ꤹ��С�������ָ�
     *     �ɤ߽Ф��Բ�ǽ�Ǥ���Х����ॢ���Ȥ��롣
     *     �ǥե���Ȥ� readback (�Ǹ������)��
     *
     * - buffer.read.timeout:
     *     �����ॢ���Ȼ��� [sec] �ǻ��ꤹ�롣�ǥե���Ȥ� 1.0 [sec]��
     *     1sec -> 1.0, 1ms -> 0.001, �����ॢ���Ȥ��ʤ� -> 0.0
     *
     * @else
     *
     * @endif
     */
    virtual void init(const coil::Properties& prop)
    {
      initLength(prop);
      initWritePolicy(prop);
      initReadPolicy(prop);
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�Ĺ���������
     * 
     * �Хåե�Ĺ��������롣
     * 
     * @return �Хåե�Ĺ
     * 
     * @else
     *
     * @brief Get the buffer length
     * 
     * Get the buffer length.
     * 
     * @return Buffer length
     * 
     *
     * @endif
     */
    virtual size_t length(void) const
    {
      Guard guard(m_posmutex);
      return m_length;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե���Ĺ���򥻥åȤ���
     * 
     * �Хåե�Ĺ�����ꤹ�롣�����ԲĤʾ���NOT_SUPPORTED���֤롣
     * ���μ����Ǥ� BUFFER_OK �����֤��ʤ���
     * 
     * @return BUFFER_OK: ���ｪλ
     *         NOT_SUPPORTED: �Хåե�Ĺ�ѹ��Բ�
     *         BUFFER_ERROR: �۾ｪλ
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * Pure virtual function to get the buffer length.
     *
     * @return buffer length
     * 
     * @endif
     */
    virtual ReturnCode length(size_t n)
    {
      m_buffer.resize(n);
      m_length = n;
      this->reset();
      return ::RTC::BufferStatus::BUFFER_OK; //BUFFER_OK;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե��ξ��֤�ꥻ�åȤ���
     * 
     * �Хåե����ɤ߽Ф��ݥ��󥿤Ƚ񤭹��ߥݥ��󥿤ΰ��֤�ꥻ�åȤ��롣
     * ���μ����Ǥ� BUFFER_OK �����֤��ʤ���
     * 
     * @return BUFFER_OK: ���ｪλ
     *         NOT_SUPPORTED: �ꥻ�å��Բ�ǽ
     *         BUFFER_ERROR: �۾ｪλ
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * Pure virtual function to get the buffer length.
     *
     * @return buffer length
     * 
     * @endif
     */ 
    virtual ReturnCode reset()
    {
      Guard guard(m_posmutex);
      m_fillcount = 0;
      m_wcount = 0;
      m_wpos = 0;
      m_rpos = 0;
      return ::RTC::BufferStatus::BUFFER_OK;
    }
    
    
    
    //----------------------------------------------------------------------
    /*!
     * @if jp
     *
     * @brief �Хåե��θ��ߤν�������ǤΥݥ���
     * 
     * �Хåե��θ��ߤν�������ǤΥݥ��󥿤ޤ��ϡ�n����Υݥ��󥿤��֤�
     * 
     * @param  n ����ߥݥ��� + n �ΰ��֤Υݥ��� 
     * @return ����߰��֤Υݥ���
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * Pure virtual function to get the buffer length.
     *
     * @return buffer length
     * 
     * @endif
     */ 
    virtual DataType* wptr(long int n = 0) 
    {
      Guard guard(m_posmutex);
      return &m_buffer[(m_wpos + n + m_length) % m_length];
    }
    
    /*!
     * @if jp
     *
     * @brief ����ߥݥ��󥿤�ʤ��
     * 
     * ���ߤν񤭹��߰��֤Υݥ��󥿤� n �Ŀʤ�롣
     * �񤭹��߲�ǽ�����ǿ��ʾ�ο��ͤ���ꤷ����硢PRECONDITION_NOT_MET
     * ���֤���
     * 
     * @param  n ����ߥݥ��� + n �ΰ��֤Υݥ��� 
     * @return BUFFER_OK:            ���ｪλ
     *         PRECONDITION_NOT_MET: n > writable()
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * Pure virtual function to get the buffer length.
     *
     * @return buffer length
     * 
     * @endif
     */ 
    virtual ReturnCode advanceWptr(long int n = 1)
    {
      // n > 0 :
      //     n satisfies n <= writable elements
      //                 n <= m_length - m_fillcout
      // n < 0 : -n = n'
      //     n satisfies n'<= readable elements
      //                 n'<= m_fillcount
      //                 n >= - m_fillcount
      Guard guard(m_posmutex);
      if ((n > 0 && n > static_cast<long int>(m_length - m_fillcount)) ||
          (n < 0 && n < static_cast<long int>(-m_fillcount)))
        {
          return ::RTC::BufferStatus::PRECONDITION_NOT_MET;
        }

      m_wpos = (m_wpos + n + m_length) % m_length;
      m_fillcount += n;
      m_wcount += n;
      return ::RTC::BufferStatus::BUFFER_OK;
    }
    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ�����񤭹���
     * 
     * �Хåե��˥ǡ�����񤭹��ࡣ�񤭹��ߥݥ��󥿤ΰ��֤��ѹ�����ʤ���
     * ���μ����ǤϾ�� BUFFER_OK ���֤���
     * 
     * @param value �񤭹����оݥǡ���
     *
     * @return BUFFER_OK: ���ｪλ
     *         BUFFER_ERROR: �۾ｪλ
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * Pure virtual function to write data into the buffer.
     * Always BUFFER_OK will be returned in this implementation.
     *
     * @param value Target data to write.
     *
     * @return BUFFER_OK:    Successful
     *         BUFFER_ERROR: Failed
     *
     * @endif
     */
    virtual ReturnCode put(const DataType& value)
    {
      Guard guard(m_posmutex);
      m_buffer[m_wpos] = value;
      return ::RTC::BufferStatus::BUFFER_OK;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե��˽񤭹���
     * 
     * ������Ϳ����줿�ǡ�����Хåե��˽񤭹��ࡣ
     *
     * ��2����(sec)����3����(nsec)�����ꤵ��Ƥ��ʤ���硢�Хåե��ե�
     * ���ν���ߥ⡼�� (overwrite, do_nothing, block) �� init() ������
     * ���줿�⡼�ɤ˽�����
     *
     * ��2����(sec) �˰��������ꤵ�줿���ϡ�init() �����ꤵ�줿�⡼��
     * �˴ؤ�餺��block �⡼�ɤȤʤꡢ�Хåե����ե���֤Ǥ���л����
     * �֤ޤ��������ॢ���Ȥ��롣��3����(nsec)�ϻ��ꤵ��ʤ����0�Ȥ���
     * �����롣�����ॢ�����Ԥ���ˡ��ɤ߽Ф�����å�¦�ǥХåե�����
     * �ɤ߽Ф��С��֥�å��󥰤ϲ������ǡ������񤭹��ޤ�롣
     *
     * �񤭹��߻��˥Хåե�����(empty)���֤ǡ��̤Υ���åɤ�block�⡼��
     * ���ɤ߽Ф��Ԥ��򤷤Ƥ����硢signal��ȯ�Ԥ����ɤ߽Ф�¦�Υ֥��
     * ���󥰤��������롣
     * 
     * @param value �񤭹����оݥǡ���
     * @param sec   �����ॢ���Ȼ��� sec  (default -1: ̵��)
     * @param nsec  �����ॢ���Ȼ��� nsec (default 0)
     * @return BUFFER_OK            ���ｪλ
     *         BUFFER_FULL          �Хåե����ե����
     *         TIMEOUT              ����ߤ������ॢ���Ȥ���
     *         PRECONDITION_NOT_MET ����۾�
     * 
     * @else
     *
     * @brief Write data into the buffer
     * 
     * Write data which is given argument into the buffer.
     *
     * @param value Target data for writing
     *
     * @return Writing result (Always true: writing success is returned)
     * 
     * @endif
     */
    virtual ReturnCode write(const DataType& value,
                             long int sec = -1, long int nsec = 0)
    {
      {
      Guard guard(m_full.mutex);
        
      if (full())
        {
          
          bool timedwrite(m_timedwrite);
          bool overwrite(m_overwrite);

          if (!(sec < 0)) // if second arg is set -> block mode
            {
              timedwrite = true;
              overwrite  = false;
            }

          if (overwrite && !timedwrite)       // "overwrite" mode
            {
              advanceRptr();
            }
          else if (!overwrite && !timedwrite) // "do_nothing" mode
            {
              return ::RTC::BufferStatus::BUFFER_FULL;
            }
          else if (!overwrite && timedwrite)  // "block" mode
            {
              if (sec < 0)
                {
                  sec = m_wtimeout.sec();
                  nsec = m_wtimeout.usec() * 1000;
                }
              //  true: signaled, false: timeout
              if (!m_full.cond.wait(sec, nsec))
                {
                  return ::RTC::BufferStatus::TIMEOUT;
                }
            }
          else                                    // unknown condition
            {
              return ::RTC::BufferStatus::PRECONDITION_NOT_MET;
            }
        }
      }      
    
      put(value);

	  {
		Guard eguard(m_empty.mutex);
		if (empty())
		  {
			// Guard eguard(m_empty.mutex);
			advanceWptr(1);
			m_empty.cond.signal();
		  }
		else
		  {
			advanceWptr(1);
		  }
	  }
      return ::RTC::BufferStatus::BUFFER_OK;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե��˽���߲�ǽ�����ǿ�
     * 
     * �Хåե��˽���߲�ǽ�����ǿ����֤���
     * 
     * @return �񤭹��߲�ǽ�����ǿ�
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * Pure virtual function to write data into the buffer.
     *
     * @param value Target data to write.
     *
     * @return Result of having written in data (true:Successful, false:Failed)
     *
     * @endif
     */
    virtual size_t writable() const
    {
      Guard guard(m_posmutex);
      return m_length - m_fillcount;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�full�����å�
     * 
     * �Хåե�full�����å��ѽ�貾�۴ؿ�
     *
     * @return full�����å����(true:�Хåե�full��false:�Хåե���������)
     * 
     * @else
     *
     * @brief Check on whether the buffer is full.
     *
     * Pure virtual function to check on whether the buffer is full.
     *
     * @return True if the buffer is full, else false.
     *
     * @endif
     */
    virtual bool full(void) const
    {
      Guard guard(m_posmutex);
      return m_length == m_fillcount;
    }
    
    //----------------------------------------------------------------------
    /*!
     * @if jp
     *
     * @brief �Хåե��θ��ߤ��ɤ߽Ф����ǤΥݥ���
     * 
     * �Хåե��θ��ߤ��ɤ߽Ф����ǤΥݥ��󥿤ޤ��ϡ�n����Υݥ��󥿤��֤�
     * 
     * @param  n �ɤ߽Ф��ݥ��� + n �ΰ��֤Υݥ��� 
     * @return �ɤ߽Ф����֤Υݥ���
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * Pure virtual function to get the buffer length.
     *
     * @return buffer length
     * 
     * @endif
     */ 
    virtual DataType* rptr(long int n = 0)
    {
      Guard guard(m_posmutex);
      return &(m_buffer[(m_rpos + n + m_length) % m_length]);
    }
    
    /*!
     * @if jp
     *
     * @brief �ɤ߽Ф��ݥ��󥿤�ʤ��
     * 
     * ���ߤ��ɤ߽Ф����֤Υݥ��󥿤� n �Ŀʤ�롣
     * 
     * @param  n �ɤ߽Ф��ݥ��� + n �ΰ��֤Υݥ��� 
     * @return BUFFER_OK: ���ｪλ
     *         BUFFER_ERROR: �۾ｪλ
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * Pure virtual function to get the buffer length.
     *
     * @return buffer length
     * 
     * @endif
     */ 
    virtual ReturnCode advanceRptr(long int n = 1)
    {
      // n > 0 :
      //     n satisfies n <= readable elements
      //                 n <= m_fillcout 
      // n < 0 : -n = n'
      //     n satisfies n'<= m_length - m_fillcount
      //                 n >= m_fillcount - m_length
      Guard guard(m_posmutex);
      if ((n > 0 && n > static_cast<long int>(m_fillcount)) ||
          (n < 0 && n < static_cast<long int>(m_fillcount - m_length)))
        {
          return ::RTC::BufferStatus::PRECONDITION_NOT_MET;
        }

      m_rpos = (m_rpos + n + m_length) % m_length;
      m_fillcount -= n;
      return ::RTC::BufferStatus::BUFFER_OK;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�����ǡ������ɤ߽Ф�
     * 
     * �Хåե�����ǡ������ɤߤ������ɤ߽Ф��ݥ��󥿤ΰ��֤��ѹ�����ʤ���
     * 
     * @param value �ɤ߽Ф��ǡ���
     *
     * @return BUFFER_OK: ���ｪλ
     *         BUFFER_ERROR: �۾ｪλ
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * Pure virtual function to write data into the buffer.
     *
     * @param value Target data to write.
     *
     * @return Result of having written in data (true:Successful, false:Failed)
     *
     * @endif
     */
    virtual ReturnCode get(DataType& value)
    {
      Guard gaurd(m_posmutex);
      value = m_buffer[m_rpos];
      return ::RTC::BufferStatus::BUFFER_OK;
    }
    
    
    /*!
     * @if jp
     *
     * @brief �Хåե�����ǡ������ɤ߽Ф�
     * 
     * �Хåե�����ǡ������ɤߤ������ɤ߽Ф��ݥ��󥿤ΰ��֤��ѹ�����ʤ���
     *
     * @return �ɤ߽Ф��ǡ���
     * 
     * @else
     *
     * @brief Reading data from the buffer
     *
     * @return Read data
     *
     * @endif
     */
    virtual DataType& get()
    {
      Guard gaurd(m_posmutex);
      return m_buffer[m_rpos];
    }
    
    
    /*!
     * @if jp
     *
     * @brief �Хåե������ɤ߽Ф�
     * 
     * �Хåե��˳�Ǽ���줿�ǡ������ɤ߽Ф���
     *
     * ��2����(sec)����3����(nsec)�����ꤵ��Ƥ��ʤ���硢�Хåե�����
     * �֤Ǥ��ɤ߽Ф��⡼�� (readback, do_nothing, block) �� init() ����
     * �ꤵ�줿�⡼�ɤ˽�����
     *
     * ��2����(sec) �˰��������ꤵ�줿���ϡ�init() �����ꤵ�줿�⡼��
     * �˴ؤ�餺��block �⡼�ɤȤʤꡢ�Хåե��������֤Ǥ���л������
     * �Ԥ��������ॢ���Ȥ��롣��3����(nsec)�ϻ��ꤵ��ʤ����0�Ȥ��ư�
     * ���롣�����ॢ�����Ԥ���ˡ�����ߥ���å�¦�ǥХåե��ؽ����
     * ������С��֥�å��󥰤ϲ������ǡ������ɤߤ�����롣
     *
     * �ɤ߽Ф����˥Хåե�����(empty)���֤ǡ��̤Υ���åɤ�block�⡼��
     * �ǽ�����Ԥ��򤷤Ƥ����硢signal��ȯ�Ԥ��ƽ����¦�Υ֥�å���
     * �����������롣
     * 
     * @param value �ɤ߽Ф��оݥǡ���
     * @param sec   �����ॢ���Ȼ��� sec  (default -1: ̵��)
     * @param nsec  �����ॢ���Ȼ��� nsec (default 0)
     * @return BUFFER_OK            ���ｪλ
     *         BUFFER_EMPTY         �Хåե���������
     *         TIMEOUT              ����ߤ������ॢ���Ȥ���
     *         PRECONDITION_NOT_MET ����۾�
     * 
     * @else
     *
     * @brief Readout data from the buffer
     * 
     * Readout data stored into the buffer.
     * 
     * @param value Readout data
     *
     * @return Readout result (Always true: readout success is returned)
     * 
     * @endif
     */
    virtual ReturnCode read(DataType& value,
                            long int sec = -1, long int nsec = 0)
    {
      {
      Guard gaurd(m_empty.mutex);
      
      if (empty())
        {
          bool timedread(m_timedread);
          bool readback(m_readback);

          if (!(sec < 0)) // if second arg is set -> block mode
            {
              timedread = true;
              readback  = false;
              sec = m_rtimeout.sec();
              nsec = m_rtimeout.usec() * 1000;
            }

          if (readback && !timedread)       // "readback" mode
            {
              if (!(m_wcount > 0))
                {
                  return ::RTC::BufferStatus::BUFFER_EMPTY;
                }
              advanceRptr(-1);
            }
          else if (!readback && !timedread) // "do_nothing" mode
            {
              return ::RTC::BufferStatus::BUFFER_EMPTY;
            }
          else if (!readback && timedread)  // "block" mode
            {
              if (sec < 0)
                {
                  sec = m_rtimeout.sec();
                  nsec = m_rtimeout.usec() * 1000;
                }
              //  true: signaled, false: timeout
              if (!m_empty.cond.wait(sec, nsec))
                {
                  return ::RTC::BufferStatus::TIMEOUT;
                }
            }
          else                                    // unknown condition
            {
              return ::RTC::BufferStatus::PRECONDITION_NOT_MET;
            }
        }
      }
      
      get(value);

	  {
		Guard fguard(m_full.mutex);
		if (full())
		  {
			// Guard fguard(m_full.mutex);
			advanceRptr(1);
			m_full.cond.signal();
		  }
		else
		  {
			advanceRptr(1);
		  }
	  }
      return ::RTC::BufferStatus::BUFFER_OK;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե������ɤ߽Ф���ǽ�����ǿ�
     * 
     * �Хåե������ɤ߽Ф���ǽ�����ǿ����֤���
     * 
     * @return �ɤ߽Ф���ǽ�����ǿ�
     *
     * @return BUFFER_OK: ���ｪλ
     *         BUFFER_ERROR: �۾ｪλ
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * Pure virtual function to write data into the buffer.
     *
     * @param value Target data to write.
     *
     * @return Result of having written in data (true:Successful, false:Failed)
     *
     * @endif
     */
    virtual size_t readable() const
    {
      Guard guard(m_posmutex);
      return m_fillcount;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�empty�����å�
     * 
     * �Хåե�empty�����å��ѽ�貾�۴ؿ�
     *
     * @return empty�����å����(true:�Хåե�empty��false:�Хåե��ǡ�������)
     * 
     * @else
     *
     * @brief Check on whether the buffer is empty.
     *
     * Pure virtual function to check on whether the buffer is empty.
     *
     * @return True if the buffer is empty, else false.
     *
     * @endif
     */
    virtual bool empty(void) const
    {
      Guard guard(m_posmutex);
      return m_fillcount == 0;
    }
    
  private:
    inline void initLength(const coil::Properties& prop)
    {
      if (!prop["length"].empty())
        {
          size_t n;
          if (coil::stringTo(n, prop["length"].c_str()))
            {
              if (n > 0)
                {
                  this->length(n);
                }
            }
        }
    }
    
    inline void initWritePolicy(const coil::Properties& prop)
    {
      std::string policy(prop["write.full_policy"]);
      coil::normalize(policy);
      if (policy == "overwrite")
        {
          m_overwrite = true;
          m_timedwrite = false;
        }
      else if (policy == "do_nothing")
        {
          m_overwrite = false;
          m_timedwrite = false;
        }
      else if (policy == "block")
        {
          m_overwrite = false;
          m_timedwrite = true;
          
          double tm;
          if (coil::stringTo(tm, prop["write.timeout"].c_str()))
            {
              if (!(tm < 0))
                {
                  m_wtimeout = tm;
                }
            }
        }
    }
    
    inline void initReadPolicy(const coil::Properties& prop)
    {
      std::string policy(prop["read.empty_policy"]);
      if (policy == "readback")
        {
          m_readback = true;
          m_timedread = false;
        }
      else if (policy == "do_nothing")
        {
          m_readback = false;
          m_timedread = false;
        }
      else if (policy == "block")
        {
          m_readback = false;
          m_timedread = true;
          double tm;
          if (coil::stringTo(tm, prop["read.timeout"].c_str()))
            {
              m_rtimeout = tm;
            }
        }
    }
    
  private:
    /*!
     * @if jp
     * @brief ��񤭥ե饰
     * @else
     * @brief Overwrite flag
     * @endif
     */
    bool m_overwrite;

    /*!
     * @if jp
     * @brief �ɤ��ᤷ�ե饰
     * @else
     * @brief Readback flag
     * @endif
     */
    bool m_readback;

    /*!
     * @if jp
     * @brief �����ॢ�����դ��񤭹��ߥե饰
     * @else
     * @brief Timedwrite flag
     * @endif
     */
    bool m_timedwrite;
    /*!
     * @if jp
     * @brief �����ॢ�����դ��ɤ߽Ф��ե饰
     * @else
     * @brief Timedread flag
     * @endif
     */
    bool m_timedread;

    /*!
     * @if jp
     * @brief �񤭹��߻������ॢ����
     * @else
     * @brief Timeout time for writing
     * @endif
     */
    coil::TimeValue m_wtimeout;

    /*!
     * @if jp
     * @brief �ɤ߽Ф��������ॢ����
     * @else
     * @brief Timeout time of reading
     * @endif
     */
    coil::TimeValue m_rtimeout;

    /*!
     * @if jp
     * @brief �Хåե�Ĺ
     * @else
     * @brief Buffer length
     * @endif
     */
    size_t m_length;

    /*!
     * @if jp
     * @brief �񤭹��ߥݥ���
     * @else
     * @brief pointer to write
     * @endif
     */
    size_t m_wpos;

    /*!
     * @if jp
     * @brief �ɤ߽Ф��ݥ���
     * @else
     * @brief poitner to read
     * @endif
     */
    size_t m_rpos;

    /*!
     * @if jp
     * @brief Fill�������
     * @else
     * @brief Fill count
     * @endif
     */
    size_t m_fillcount;

    /*!
     * @if jp
     * @brief �񤭹��ߥ������
     * @else
     * @brief Counter for writing
     * @endif
     */
    size_t m_wcount;

    /*!
     * @if jp
     * @brief �Хåե�����
     * @else
     * @brief baffer array
     * @endif
     */
    std::vector<DataType> m_buffer;
    
    /*!
     * @if jp
     * @brief ����ѿ���¤��
     * @else
     * @brief struct for condition variable
     * @endif
     */
    struct condition
    {
      condition() : cond(mutex) {}
      coil::Condition<coil::Mutex> cond;
      coil::Mutex mutex;
    };
    
    /*!
     * @if jp
     * @brief �����ѿ��ߥ塼�ƥå���
     * @else
     * @brief mutex for position variable
     * @endif
     */
    mutable coil::Mutex m_posmutex;

    /*!
     * @if jp
     * @brief ������ѿ�
     * @else
     * @brief empty condition variable
     * @endif
     */
    condition m_empty;

    /*!
     * @if jp
     * @brief ���վ���ѿ�
     * @else
     * @brief full condition variable
     * @endif
     */
    condition m_full;
  };
}; // namespace RTC

#endif // RTC_RINGBUFFER_H
