// -*- C++ -*-
/*!
 *
 * @file BufferBase.h
 * @brief Buffer abstract class
 * @date $Date: 2007-12-31 03:06:12 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: BufferBase.h 1704 2010-01-20 02:30:54Z fsi-katami $
 */

#ifndef RTC_BUFFERBASE_H
#define RTC_BUFFERBASE_H

#include <stddef.h>
#include <coil/Properties.h>
#include <rtm/BufferStatus.h>

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
   * @class BufferBase
   * @brief BufferBase ��ݥ��饹
   * 
   * ��ΥХåե��Τ������ݥ��󥿡��ե��������饹��
   * ��ݥХåե����饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
   * \<DataType\>�Ȥ��ƥХåե�����ݻ�����ǡ���������ꤹ�롣
   *
   * public���󥿡��ե������Ȥ��ưʲ��Τ�Τ��󶡤��롣
   * - length(): �Хåե���Ĺ�����֤�
   * - length(n): �Хåե�Ĺ��n�˥��åȤ���
   * - reset(): �Хåե��Υݥ��󥿤�ꥻ�åȤ���
   *
   * ����ߴ�Ϣ
   * - wptr(n=0): ���ߤν񤭹����оݤ����Ǥ�n����Υݥ��󥿤��֤���
   * - advanceWptr(n=1): ����ߥݥ��󥿤�n�ʤ�롣
   * - put(): ���ߤν񤭹��߰��֤˽񤭹��ࡢ�ݥ��󥿤Ͽʤ�ʤ���
   * - write(): �Хåե��˽񤭹��ࡣ�ݥ��󥿤�1�Ĥ����ࡣ
   * - writable(): ����߲�ǽ�����ǿ����֤���
   * - full(): �Хåե����ե���֡�
   *
   * �ɤ߽Ф���Ϣ
   * - rptr(n=0): ���ߤ��ɤ߽Ф��оݤ�n����Υݥ��󥿤��֤���
   * - advanceRptr(n=1): �ɤ߽Ф��ݥ��󥿤�n�ʤ�롣
   * - get(): ���ߤ��ɤ߽Ф����֤����ɤࡣ�ݥ��󥿤Ͽʤ�ʤ���
   * - read(): �Хåե������ɤ߽Ф����ݥ��󥿤�1�Ĥ����ࡣ
   * - readable(): �ɤ߽Ф���ǽ���ǿ����֤���
   * - empty(): �Хåե��������֡�
   *
   * @param DataType �Хåե��˳�Ǽ����ǡ�����
   *
   * @since 0.4.0
   *
   * @else
   * @class BufferBase
   * @brief BufferBase abstract class
   *
   * This is the abstract interface class for various Buffer.
   * Concrete buffer classes must implement the following pure virtual
   * functions.
   * The users specify data type to hold it in a buffer as \<DataType\>.
   *
   * This class provides public interface as follows.
   * - write(): Write data into the buffer.
   * - read(): Read data from the buffer.
   * - length(): Get the buffer length.
   * - isFull(): Check on whether the buffer is full.
   * - isEmpty(): Check on whether the buffer is empty.
   *
   * This class provides protected interface as follows.
   * - put(): Store data into the buffer.
   * - get(): Get data from the buffer.
   *
   * @param DataType Data type to be stored to the buffer.
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  class BufferBase
    : public BufferStatus
  {
  public:
    BUFFERSTATUS_ENUM

    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * @else
     *
     * @brief Virtual destructor
     *
     * @endif
     */
    virtual ~BufferBase(void)
    {
    };
    
    /*!
     * @if jp
     *
     * @brief �Хåե�������
     *
     * @else
     *
     * @brief Set the buffer
     *
     * @endif
     */
    virtual void init(const coil::Properties& prop) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե���Ĺ�����������
     * 
     * �Хåե�Ĺ��������뤿��ν�貾�۴ؿ�
     * 
     * @return �Хåե�Ĺ
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
    virtual size_t length(void) const = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե���Ĺ���򥻥åȤ���
     * 
     * �Хåե�Ĺ�����ꤹ�롣�����ԲĤʾ���NOT_SUPPORTED���֤롣
     * 
     * @return BUFFER_OK: ���ｪλ
     *         NOT_SUPPORTED: �Хåե�Ĺ�ѹ��Բ�
     *         BUFFER_ERROR: �۾ｪλ
     * 
     * @else
     *
     * @brief Set the buffer length
     *
     * Pure virtual function to set the buffer length.
     *
     * @return BUFFER_OK: Successful
     *         NOT_SUPPORTED: The buffer length cannot be set.
     *         BUFFER_ERROR: Failed
     *         
     * 
     * @endif
     */    
    virtual ReturnCode length(size_t n) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե��ξ��֤�ꥻ�åȤ���
     * 
     * �Хåե����ɤ߽Ф��ݥ��󥿤Ƚ񤭹��ߥݥ��󥿤ΰ��֤�ꥻ�åȤ��롣
     * 
     * @return BUFFER_OK: ���ｪλ
     *         NOT_SUPPORTED: �ꥻ�å��Բ�ǽ
     *         BUFFER_ERROR: �۾ｪλ
     * 
     * @else
     *
     * @brief Reset the buffer status
     *
     * Pure virtual function to reset the buffer status.
     *
     * @return BUFFER_OK: Successful
     *         NOT_SUPPORTED: The buffer status cannot be reset.
     *         BUFFER_ERROR: Failed
     * 
     * @endif
     */ 
    virtual ReturnCode reset() = 0;


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
     * @brief Get the writing pointer
     *
     * Pure virtual function to get the writing pointer.
     *
     * @param writeing pinter or n previous pointer
     * @return writing pointer
     * 
     * @endif
     */ 
    virtual DataType* wptr(long int n = 0) = 0;

    /*!
     * @if jp
     *
     * @brief ����ߥݥ��󥿤�ʤ��
     * 
     * ���ߤν񤭹��߰��֤Υݥ��󥿤� n �Ŀʤ�롣
     * 
     * @param  n ����ߥݥ��� + n �ΰ��֤Υݥ��� 
     * @return BUFFER_OK: ���ｪλ
     *         BUFFER_ERROR: �۾ｪλ
     * 
     * @else
     *
     * @brief Forward n writing pointers.
     *
     * Pure virtual function to forward n writing pointers.
     *
     * @return BUFFER_OK: Successful
     *         BUFFER_ERROR: Failed
     * 
     * @endif
     */ 
    virtual ReturnCode advanceWptr(long int n = 1) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ�����񤭹���
     * 
     * �Хåե��˥ǡ�����񤭹��ࡣ�񤭹��ߥݥ��󥿤ΰ��֤��ѹ�����ʤ���
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
     *
     * @param value Target data to write.
     *
     * @return BUFFER_OK: Successful
     *         BUFFER_ERROR: Failed
     *
     * @endif
     */
    virtual ReturnCode put(const DataType& value) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ�����񤭹���
     * 
     * �Хåե��˥ǡ�����񤭹��ࡣ�񤭹��ߥݥ��󥿤ΰ��֤�1�Ĥ����ࡣ
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
     *
     * @param value Target data to write.
     *
     * @return BUFFER_OK: Successful
     *         BUFFER_ERROR: Failed
     *
     * @endif
     */
    virtual ReturnCode write(const DataType& value,
                             long int sec = -1, long int nsec = -1) = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե��˽���߲�ǽ�����ǿ�
     * 
     * �Хåե��˽���߲�ǽ�����ǿ����֤���
     * 
     * @return �񤭹��߲�ǽ�����ǿ�
     *
     * 
     * @else
     *
     * @brief Get a writable number. 
     *
     * Pure virtual function to get a writable number.
     *
     * @return value writable number
     *
     *
     * @endif
     */
    virtual size_t writable() const = 0;

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
    virtual bool full(void) const = 0;

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
     * @brief Get the reading pointer
     *
     * Pure virtual function to get the reading pointer.
     *
     * @return reading pointer
     * 
     * @endif
     */ 
    virtual DataType* rptr(long int n = 0) = 0;

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
     * @brief Forward n reading pointers.
     *
     * Pure virtual function to forward n reading pointers.
     *
     * @return BUFFER_OK: Successful
     *         BUFFER_ERROR: Failed
     * 
     * @endif
     */ 
    virtual ReturnCode advanceRptr(long int n = 1) = 0;

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
     * @brief Read data from the buffer
     *
     * Pure virtual function to read data form the buffer.
     *
     * @param value Data to read.
     *
     * @return BUFFER_OK: Successful
     *         BUFFER_ERROR: Failed
     *
     * @endif
     */
    virtual ReturnCode get(DataType& value) = 0;

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
     * @brief Read data from the buffer
     *
     * Pure virtual function to read data from the buffer.
     *
     * @return Data got from buffer.
     *
     * @endif
     */
    virtual DataType&  get() = 0;

    /*!
     * @if jp
     *
     * @brief �Хåե�����ǡ������ɤ߽Ф�
     * 
     * �Хåե�����ǡ������ɤ߽Ф�����ν�貾�۴ؿ�
     * 
     * @param value �ɤ߽Ф��ǡ���
     *
     * @return �ǡ����ɤ߽Ф����(true:�ɤ߽Ф�������false:�ɤ߽Ф�����)
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * Pure virtual function to read data from the buffer.
     *
     * @param value Read data.
     *
     * @return Result of having read (true:Successful, false:Failed)
     *
     * @endif
     */
    virtual ReturnCode read(DataType& value,
                            long int sec = -1, long int nsec = -1) = 0;
    
    /*!
     * @if jp
     *
     * @brief �Хåե������ɤ߽Ф���ǽ�����ǿ�
     * 
     * �Хåե������ɤ߽Ф���ǽ�����ǿ����֤���
     * 
     * @return �ɤ߽Ф���ǽ�����ǿ�
     *
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * Pure virtual function to get a reading number.
     *
     *
     * @return readable number
     *
     * @endif
     */
    virtual size_t readable() const = 0;

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
    virtual bool empty(void) const = 0;

  };
  
  /*!
   * @if jp
   * @class NullBuffer
   * @brief ���ߡ��Хåե��������饹
   * 
   * �Хåե�Ĺ��������Υ��ߡ��Хåե��������饹��
   * \<DataType\>�Ȥ��ƥХåե�����ݻ�����ǡ���������ꤹ�롣
   *
   * @param DataType �Хåե��˳�Ǽ����ǡ�����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class NullBuffer
   * @brief Concrete buffer class for dummy
   * 
   * Concrete buffer class for dummy. Buffer length is fixed to 1.
   * The users specify data type to hold it in a buffer as \<DataType\>.
   *
   * @param DataType Data type to hold in a buffer
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  class NullBuffer
    : public BufferBase<DataType>
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     * �Хåե�Ĺ��1(����)�ǽ�������롣
     *
     * @param size �Хåե�Ĺ(������̵��)
     * 
     * @else
     *
     * @brief Constructer
     * 
     * Constructer.
     * Initialize buffer length to always 1.
     *
     * @param size Buffer length(Not use)
     * 
     * @endif
     */
    NullBuffer(long int size = 1)
      : m_length(1)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     * 
     * �ǥ��ȥ饯����
     *
     * @else
     *
     * @brief Destructor
     *
     * Destractor
     *
     * @endif
     */
    virtual ~NullBuffer(void)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�Ĺ(1����)���������
     * 
     * �Хåե�Ĺ��������롣(���1���֤���)
     * 
     * @return �Хåե�Ĺ(1����)
     * 
     * @else
     *
     * @brief Get the buffer length (always 1)
     *
     * Get the buffer length. (Return always 1.)
     *
     * @return buffer length(always 1)
     * 
     * @endif
     */
    virtual long int length(void) const
    {
      return 1;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ�����񤭹���
     * 
     * ������Ϳ����줿�ǡ�����Хåե��˽񤭹��ࡣ
     * 
     * @param value �񤭹����оݥǡ���
     *
     * @return �ǡ����񤭹��߷��(true:�񤭹���������false:�񤭹��߼���)
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * Write data which were given with an argument into the buffer.
     *
     * @param value Target data to write.
     *
     * @return Result of having written in data (true:Successful, false:Failed)
     *
     * @endif
     */
    virtual bool write(const DataType& value)
    {
      m_data = value;
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�����ǡ������ɤ߽Ф�
     * 
     * �Хåե��˳�Ǽ���줿�ǡ������ɤ߽Ф���
     * 
     * @param value �ɤ߽Ф����ǡ���
     *
     * @return �ǡ����ɤ߽Ф����(true:�ɤ߽Ф�������false:�ɤ߽Ф�����)
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * Read data stored in the buffer.
     *
     * @param value Read data.
     *
     * @return Result of having read (true:Successful, false:Failed)
     *
     * @endif
     */
    virtual bool read(DataType& value)
    {
      value = m_data;
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�full�����å�
     * 
     * �Хåե�full������å����롣(���false���֤���)
     *
     * @return full�����å����(���false)
     * 
     * @else
     *
     * @brief Check on whether the buffer is full.
     *
     * Check on whether the buffer is full. (Always false.)
     *
     * @return Always false.
     *
     * @endif
     */
    virtual bool isFull(void) const
    {
      return false;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�empty�����å�
     * 
     * �Хåե�empty������å����롣(���false���֤���)
     *
     * @return empty�����å����(���false)
     * 
     * @else
     *
     * @brief Check on whether the buffer is empty.
     *
     * Check on whether the buffer is empty. (Always false.)
     *
     * @return Always false.
     *
     * @endif
     */
    virtual bool isEmpty(void) const
    {
      return false;
    }
    
  protected:
    /*!
     * @if jp
     *
     * @brief �Хåե��˥ǡ������Ǽ
     * 
     * ������Ϳ����줿�ǡ�����Хåե��˳�Ǽ���롣
     * 
     * @param data �оݥǡ���
     * 
     * @else
     *
     * @brief Store data into the buffer
     *
     * Store data which were given with an argument into the buffer.
     *
     * @param data Target data to store.
     *
     * @endif
     */
    virtual void put(const DataType& data)
    {
      m_data = data;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�����ǡ������������
     * 
     * �Хåե��˳�Ǽ���줿�ǡ�����������롣
     *
     * @return �����ǡ���
     * 
     * @else
     *
     * @brief Get data from the buffer
     *
     * Get data from the buffer.
     *
     * @return Data got from buffer.
     *
     * @endif
     */
    virtual const DataType& get(void)
    {
      return m_data;
    }
    
    /*!
     * @if jp
     *
     * @brief ���˽񤭹���Хåե��ؤλ��Ȥ��������
     * 
     * �񤭹��ߥХåե��ؤλ��Ȥ�������롣
     * �ܥХåե������ǤϥХåե�Ĺ�ϸ���ǣ��Ǥ��뤿�ᡤ
     * ���Ʊ�����֤ؤλ��Ȥ��֤���
     *
     * @return ���ν񤭹����оݥХåե��ؤλ���(����)
     * 
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * Get the reference to be written buffer.
     * Return always same position because this buffer's length is always 1.
     *
     * @return Reference to be written the next(always same)
     *
     * @endif
     */
    virtual DataType& getRef(void)
    {
      return m_data;
    }
    
  private:
    DataType m_data;
    long int m_length;
  };
}; // namespace RTC
#endif // BufferBase_h
