// -*- C++ -*-
/*!
 * @file Timevalue.h
 * @brief Timevalue class
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

#ifndef COIL_TIMEVALUE_H
#define COIL_TIMEVALUE_H

namespace coil
{

#define TIMEVALUE_ONE_SECOND_IN_USECS 1000000 // 1 [sec] = 1000000 [usec]

  /*!
   * @if jp
   *
   * @class TimeValue
   * @brief TimeValue ���饹
   *
   * @else
   *
   * @class TimeValue
   * @brief TimeValue class
   *
   * @endif
   */
  class TimeValue
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     * ���ꤵ�줿�á��ޥ������äǽ�������롣
     *
     * @param sec ��(�ǥե������:����)
     * @param usec �ޥ�������(�ǥե������:����)
     * 
     * @else
     *
     * @brief Constructor
     * 
     * Constructor
     * Initialize with the specified second and micro second.
     *
     * @param sec Second(The default value:0)
     * @param usec Micro second(The default value:0)
     * 
     * @endif
     */
    TimeValue(long sec=0, long usec=0);

    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     * ���ꤵ�줿�á��ޥ������äǽ�������롣
     *
     * @param timeval (�� * 1000000 + �ޥ�������)
     * 
     * @else
     *
     * @brief Constructor
     * 
     * Constructor
     * Initialize with the specified second and micro second.
     *
     * @param timeval (Second * 1000000 + Micro second)
     * 
     * @endif
     */
    TimeValue(double timeval);

    /*!
     * @if jp
     *
     * @brief ��ñ�̤��ͤ��������
     * 
     * ��ñ�̤��ͤ��������
     *
     * @return ��
     *
     * @else
     *
     * @brief Get value of second time scale
     * 
     * Get value of second time scale.
     *
     * @return value
     *
     * @endif
     */
    inline long int sec() const {return m_sec;}

    /*!
     * @if jp
     *
     * @brief �ޥ�������ñ�̤��ͤ��������
     * 
     * �ޥ�������ñ�̤��ͤ��������
     *
     * @return ��
     *
     * @else
     *
     * @brief Get value of micro second time scale
     * 
     * Get value of micro second time scale.
     *
     * @return value
     *
     * @endif
     */
    inline long int usec() const {return m_usec;}
    
    /*!
     * @if jp
     *
     * @brief ���ָ���
     * 
     * ���ꤵ�줿���֤��������Ϳ����줿���֤򸺻����롣
     *
     * @param tm ��������
     * 
     * @return �������
     * 
     * @else
     *
     * @brief Time subtraction
     * 
     * Subtract the time given by the argument from the set time.
     *
     * @param tm Subtracted time
     * 
     * @return Subtraction result
     * 
     
     * @endif
     */
    TimeValue operator-(TimeValue& tm);
    
    /*!
     * @if jp
     *
     * @brief ���ֲû�
     * 
     * ���ꤵ�줿���֤˰�����Ϳ����줿���֤�û����롣
     *
     * @param tm �û�����
     * 
     * @return �û����
     * 
     * @else
     *
     * @brief Time addition
     * 
     * Add the time given by the argument to the set time.
     *
     * @param tm Added time
     * 
     * @return Addition result
     * 
     * @endif
     */
    TimeValue operator+(TimeValue& tm);
    
    /*!
     * @if jp
     *
     * @brief double�������ַ��Ѵ�
     * 
     * ������Ϳ����줿double������ַ����Ѵ����롣
     *
     * @param time �Ѵ�����
     * 
     * @return �Ѵ����
     * 
     * @else
     *
     * @brief Convert double type into time type
     * 
     * Convert double type given by the argument into time type.
     *
     * @param time the original value
     * 
     * @return Conversion result
     * 
     * @endif
     */
    TimeValue operator=(double time);
    
    /*!
     * @if jp
     *
     * @brief ���ַ���double���Ѵ�
     * 
     * �ݻ����Ƥ������Ƥ�double�����Ѵ����롣
     *
     * @return double���Ѵ����
     * 
     * @else
     *
     * @brief Convert time type into double type
     * 
     * Convert held information into double type.
     *
     * @return Result for conversion of double type
     * 
     * @endif
     */
    operator double() const;
    
    /*!
     * @if jp
     * 
     * @brief ���Ƚ��
     * 
     * �ݻ����Ƥ������Ƥ�����Ƚ�ꤹ�롣
     * 
     * @return ���ʤ��1����ʤ��-1��0�ʤ��0
     * 
     * @else
     *  
     * @brief Sign judgment
     * 
     * Judge sign of the held contents
     * 
     * @return 1 if the return value is Plus sign, -1 if Minus, and 0 if 0.
     * 
     * @endif
     */
    int sign() const;
    
    //  private:
    
    /*!
     * @if jp
     * 
     * @brief ������
     * 
     * �ͤ�ɽ����������������������롣
     * 
     * @else
     * 
     * @brief Normalize
     * 
     * Normalize the value expression into a canonical form.
     * 
     * @endif
     */
    void normalize();

  private:
    long int m_sec;
    long int m_usec;
  };
};

#endif // COIL_TIMEVALUE_H
