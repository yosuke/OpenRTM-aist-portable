// -*- C++ -*-
/*!
 * @file RTPreemptEC.h
 * @brief RTPreemptEC class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2010
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef OPENRTM_RTPREEMPTEC_H
#define OPENRTM_RTPREEMPTEC_H

#include <rtm/RTC.h>
#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

namespace OpenRTM
{
  /*!
   * @if jp
   * @class RTPreemptEC
   * @brief RTPreemptEC ���饹
   *
   * RT-Preempt kernel �����Ѥ������ꥢ�륿����¹ԥ���ƥ����ȥ��饹��
   * ���μ¹ԥ���ƥ����Ȥϡ�RT-Preempt Patch ��Ŭ�Ѥ��� Linux kernel��
   * ���ϡ����줬�Ȥ߹��ޤ줿 Linux kernel �ˤ��ꥢ�륿���ॹ�����塼
   * ��󥰵�ǽ�����Ѥ����¹ԥ���ƥ����ȤǤ��롣
   *
   * ���μ¹ԥ���ƥ����Ȥ����Ѥ���ˤϡ�rtc.conf �˲����Τ褦�˵��Ҥ��롣
   * 
   * <pre>
   * exec_cxt.periodic.type: RTPreemptEC
   * exec_cxt.periodic.rate: 1000
   * exec_cxt.priority: 50
   * manager.modules.load_path: <RTPreemptRC.so ��������ؤΥѥ�>
   * manager.modules.preload: RTPreemptEC.so
   * </pre>
   *
   * ����ˡ��¹Ի��ˤ� root ���¤�ɬ�פȤʤ�Τǡ�root �Ȥ��ƥ���ݡ�
   * �ͥ�Ȥ�¹Ԥ���ɬ�פ����롣
   *
   * ����EC����ͭ�ʥ��ץ����ϰʲ��ΤȤ���Ǥ��롣
   *
   * - exec_cxt.periodic.priority: (default: 49) <br>
   * - exec_cxt.periodic.rtpreempt.priority: (default: 49)<br>
   *      ����åɤμ¹�ͥ���� 1 (����) ���� 99 (�ǹ�)<br>
   *      Linux sched_setscheduler(2) �򻲾ȤΤ��ȡ�<br>
   *
   * - exec_cxt.periodic.rtpreempt.sched_policy:  (default: fifo)<br>
   *      �������塼��󥰤Υݥꥷ��<br>
   *      rr: �饦��ɥ�ӥ�, fifo: FIFO �� (default: fifo)<br>
   *      Linux sched_setscheduler(2) �򻲾ȤΤ��ȡ�<br>
   *
   * - exec_cxt.periodic.rtpreempt.wait_offset: (default: -10000)<br>
   *      �������Ȼ��֤Υ��ե��åȡ�[ns] ñ�̤ǻ��ꤹ�롣 <br>
   *      1������������� us ���٤����Ū���٤줬ȯ�������礬����Τǡ�
   *      �����ͤ�Ĵ�����뤳�Ȥǡ�������Τʼ����Ǽ¹Ԥ����뤳�Ȥ��Ǥ��롣
   *
   * ��ջ���: ����EC�����Ū®������ (����ms�ʾ�) �Ǽ¹Ԥ�������ϡ�
   * ����٥�� DEBUG ���Ⲽ (logger.log_level: NORMAL ��) �����ꤷ
   * �Ƽ¹Ԥ���ɬ�פ����롣�ޤ���logger.enable: NO �����ꤵ��Ƥ��Ƥ⡢
   * logger.log_level: PARANOID �����ꤵ��Ƥ�����ˤϡ�onExecute()
   * �μ¹Ԥ˻��֤������ꡢ�ǥåɥ饤�����ʤ��ʤ��ǽ��������Τ���
   * �դ�ɬ�פǤ��롣
   *
   * @since 1.0.1
   *
   * @else
   * @class RTPreemptEC
   * @brief RTPreemptEC ���饹
   *
   * This class is real-time ExecutionContext which utilizes RT-Prempt
   * kernel.  This ExecutionContext is a real-time ExecutionContext
   * which utilizes real-time scheduler functionality of "RT-Preempt"
   * Linux kernel (patched or originally embedded).
   *
   * Give the following configurations in your rtc.conf to use this EC.
   * <pre>
   * exec_cxt.periodic.type: RTPreemptEC
   * exec_cxt.periodic.rate: 1000
   * exec_cxt.priority: 50
   * manager.modules.load_path: <path to RTPreemptRC.so>
   * manager.modules.preload: RTPreemptEC.so
   * </pre>
   *
   * Since this functionality requires root authority, your RTC which
   * uses this EC have to be executed as root.
   *
   * The following RTPreemptEC specific options are available.
   *
   * - exec_cxt.periodic.priority: (default: 49)<br>
   * - exec_cxt.periodic.rtpreempt.priority: (default: 49)<br>
   *      Execution priority of threads from 1 (lowest) to 99 (highest)<br>
   *      See Linux sched_setscheduler(2).
   *
   * - exec_cxt.periodic.rtpreempt.sched_policy:  (default: fifo)<br>
   *      Scheduling policy.<br>
   *      rr: round-robin, fifo: FIFO type scheduling (default: fifo)<br>
   *      See Linux sched_setscheduler(2).
   *
   * - exec_cxt.periodic.rtpreempt.wait_offset: (default: -10000)<br>
   *      Offset time of wait. It can be given [ns] unit. <br> 
   *      Adjusting this value, If dozens micro seconds delay in one
   *      execution cycle constantly, more accurate periodic execution
   *      can be achieved.
   *
   * NOTICE: When performing comparatively quick cycle (tens of ms or
   * more) using this EC, log-level have to be lower than DEBUG
   * (logger.log_level: NORMAL or etc.). Moreover, even if
   * "logger.enable=No" is set, if "logger.log_level=PRANOID" is set,
   * execution of onExecute() takes longer time and it may cause
   * deadline-miss. So caution is needed.
   *
   * @since 1.0.1
   *
   * @endif
   */
  class RTPreemptEC
    : public virtual ::RTC::PeriodicExecutionContext
  {
  public:
    /*!
     * @if jp
     * @brief �ǥե���ȥ��󥹥ȥ饯��
     *
     * �ǥե���ȥ��󥹥ȥ饯��
     *
     * @else
     * @brief Default Constructor
     *
     * Default Constructor
     *
     * @endif
     */
    RTPreemptEC();

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
    virtual ~RTPreemptEC();

    /*!
     * @if jp
     * @brief ExecutionContext �ѤΥ���åɼ¹Դؿ�
     *
     * ExecutionContext �ѤΥ���åɼ¹Դؿ���
     * ��Ͽ���줿����ݡ��ͥ�Ȥν�����ƤӽФ���
     *
     * @return �¹Է��
     *
     * @else
     * @brief Thread execution function for ExecutionContext
     *
     * Thread execution function for ExecutionContext.
     * Invoke the registered components operation.
     *
     * @return The execution result
     *
     * @endif
     */ 
    virtual int svc(void);

    /*!
     * @if jp
     * @brief ���륭������ĥץ�ѥƥ����������
     *
     * @param ExecutionContext �ѤΥ���åɼ¹Դؿ���
     * ��Ͽ���줿����ݡ��ͥ�Ȥν�����ƤӽФ���
     *
     * @return �¹Է��
     *
     * @else
     * @brief Thread execution function for ExecutionContext
     *
     * Thread execution function for ExecutionContext.
     * Invoke the registered components operation.
     *
     * @return The execution result
     *
     * @endif
     */ 
    template <class T>
    void getProperty(coil::Properties& prop, const char* key, T& value)
    {
    if (prop.findNode(key) != 0)
      {
        T tmp;
        if (coil::stringTo(tmp, prop[key].c_str()))
          {
            value = tmp;
          }
      }
    }

  private:
    int m_priority;
    int m_policy;
    int m_waitoffset;
  };
};

extern "C"
{
  /*!
   * @if jp
   * @brief ECFactory�ؤ���Ͽ�Τ���ν�����ؿ�
   * @else
   * @brief Initialization function to register to ECFactory
   * @endif
   */
  void DLL_EXPORT RTPreemptECInit(RTC::Manager* manager);
};

#endif // OPENRTM_RTPREEMPTEC_H

