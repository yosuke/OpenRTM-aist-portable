// -*- C++ -*-
/*!
 * @file TimeMeasure.h
 * @brief Periodic time measurement class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
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

#ifndef COIL_TIMEMEASURE_H
#define COIL_TIMEMEASURE_H

#include <vector>
#include <coil/TimeValue.h>

namespace coil
{
  
  /*!
   * @if jp
   *
   * @class TimeMeasure
   * @brief TimeMeasure ���饹
   *
   * ���Υ��饹�ϡ������ɼ¹Ի��֤����פ���٤˻��Ѥ��ޤ���
   * get_stat ����Ѥ��ƥ����ɼ¹Ԥκ��硦�Ǿ���ʿ�ѡ�ɸ���к����֤��¬�Ǥ��ޤ���
   *
   * @else
   *
   * @class TimeMeasure
   * @brief TimeMeasure class
   *
   * This class is used for getting statistics of code execution time. 
   * Using get_stat you can get maximum, minimum, mean and standard
   * deviation time for code execution.
   *
   * @endif
   */
  class TimeMeasure
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���������ѹ�¤��
     *
     * @else
     *
     * @brief Structure for time statistics
     *
     * @endif
     */
    struct Statistics
    {
      double max_interval;
      double min_interval;
      double mean_interval;
      double std_deviation;
    };

    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * �������פΥץ�ե������
     *
     * @else
     *
     * @brief Constructor
     *
     * Time Statistics object for profiling.
     *
     * @endif
     */
    TimeMeasure(int buflen = 100);

    /*!
     * @if jp
     *
     * @brief �������פη�¬�򳫻Ϥ���
     *
     * �������פη�¬�򳫻Ϥ���
     *
     * @else
     *
     * @brief Begin time measurement for time statistics
     *
     * Begin time measurement for time statistics.
     *
     * @endif
     */
    void tick();

    /*!
     * @if jp
     *
     * @brief �������פη�¬��λ����
     *
     * �������פη�¬��λ����
     *
     * @else
     *
     * @brief Finish time measurement for time statistics
     *
     * End of time measurement for time statistics.
     *
     * @endif
     */
    void tack();

    /*!
     * @if jp
     *
     * @brief �в���֤��������
     *
     * �в���֤��������
     *
     * @return TimeValue ���֥�������
     *
     * @else
     *
     * @brief Get a interval time
     *
     * Get a interval time.
     *
     * @return TimeValue object
     *
     * @endif
     */
    coil::TimeValue& interval();

    /*!
     * @if jp
     *
     * @brief ���״�Ϣ�ǡ����ν����
     *
     * ���״�Ϣ�ǡ����ν����
     *
     * @else
     *
     * @brief Initialize for statistics related data
     *
     * Initialize for statistics related data.
     *
     * @endif
     */
    void reset();

    /*!
     * @if jp
     *
     * @brief �������ץХåե����������������
     *
     * �������ץХåե����������������
     *
     * @return ��¬���
     *
     * @else
     *
     * @brief Get number of time measurement buffer
     *
     * Get number of time measurement buffer.
     *
     * @return Measurement count
     *
     * @endif
     */
    unsigned long int count() const;

    /*!
     * @if jp
     *
     * @brief ���ץǡ�������פ��������
     *
     * ���ץǡ�������פ��������
     *
     * @param max_interval ������ [ns]
     * @param min_interval �Ǿ��� [ns]
     * @param mean_interval ʿ���� [ns]
     * @param stddev ɸ���к���
     *
     * @return true: �ǡ�������, false: �ǡ����ʤ�
     *
     * @else
     *
     * @brief Get total statistics
     *
     * Get total statistics.
     *
     * @param max_interval Max value [ns]
     * @param min_interval Min value [ns]
     * @param mean_interval Mean value [ns]
     * @param stddev Standard deviation value
     *
     * @return true: Data found, false: Data not found
     *
     * @endif
     */
    bool getStatistics(double &max_interval,
                       double &min_interval,
                       double &mean_interval,
                       double &stddev);

    /*!
     * @if jp
     *
     * @brief ���׷�̤��������
     *
     * ���׷�̤��������
     *
     * @return ���׷��
     *
     * @else
     *
     * @brief Get statistics result
     *
     * Get statistics result.
     *
     * @return Statistics result
     *
     * @endif
     */
    Statistics getStatistics();

  private:
    std::vector<coil::TimeValue> m_record;
    coil::TimeValue m_begin;
    coil::TimeValue m_interval;

    unsigned long int m_count;
    const unsigned long int m_countMax;
    unsigned long long int m_cpuClock;

    bool m_recurred;
  };
}; // namespace coil
#endif // COIL_TIMEMEASURE_H
