// -*- C++ -*-
/*!
 * @file RTCUtil.h
 * @brief RTComponent utils
 * @date $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTCUtil.h 1703 2010-01-20 01:12:01Z fsi-katami $
 *
 */

#ifndef RTCUtil_h
#define RTCUtil_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>

/*!
 * @if jp
 * @namespace RTC_Utils
 *
 * @brief RT����ݡ��ͥ���ѥ桼�ƥ���ƥ��ؿ�
 *
 * RT����ݡ��ͥ�Ȥ��Ф��ưʲ��Υ桼�ƥ���ƥ��ؿ����󶡤��롣
 * 
 * - isDataFlowParticipant
 * - isFsmParticipant
 * - isFsmObject
 * - isMultiModeObject
 *
 * @else
 * @namespace RTC_Utils
 *
 * @brief Utility functions for RT-Component
 *
 * This provides the following utility functions to RT-Component.
 * 
 * - isDataFlowParticipant
 * - isFsmParticipant
 * - isFsmObject
 * - isMultiModeObject
 *
 * @endif
 */
namespace RTC_Utils
{
  /*!
   * @if jp
   *
   * @brief DataFlowComponent �Ǥ��뤫Ƚ�ꤹ��
   *
   * ���ꤵ�줿RT����ݡ��ͥ�Ȥ� DataFlowComponent �Ǥ��뤫Ƚ�ꤹ�롣
   * DataFlowComponent�ϡ� ExecutionContext �� Semantics ��
   * Periodic Sampled Data Processing �ξ������Ѥ����RT����ݡ��ͥ�Ȥη�
   * �Ǥ��롣
   *
   * @param obj Ƚ���оݤ� CORBA ���֥�������
   *
   * @return DataFlowComponent Ƚ����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @brief Confirm whether specified RT-Component is DataFlowComponent
   *
   * Confirm whether specified RT-Component is DataFlowComponent.
   * DataFlowComponent is a type of the RT-Component which is used 
   * when Semantics of ExecutionContext is Periodic Sampled Data Processing.
   *
   * @param obj The target CORBA object for the investigation
   *
   * @return Investigation result of DataFlowComponent
   *
   * @since 0.4.0
   *
   * @endif
   */
  bool isDataFlowComponent(CORBA::Object_ptr obj);
  
  /*!
   * @if jp
   *
   * @brief FsmParticipant �Ǥ��뤫Ƚ�ꤹ��
   *
   * ���ꤵ�줿RT����ݡ��ͥ�Ȥ� FsmParticipant �Ǥ��뤫Ƚ�ꤹ�롣
   * FsmParticipant �ϡ� ExecutionContext �� Semantics ��
   * Stimulus Response Processing �ξ��ˡ�������Υ���������������뤿���
   * ���Ѥ����RT����ݡ��ͥ�Ȥη��Ǥ��롣
   *
   * @param obj Ƚ���оݤ� CORBA ���֥�������
   *
   * @return FsmParticipant Ƚ����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @brief Confirm whether specified RT-Component is FsmParticipant
   *
   * Confirm whether specified RT-Component is FsmParticipant.
   * FsmParticipant is a type of the RT-Component which is used when Semantics
   * of ExecutionContext is Stimulus Response Processing. It is used to define 
   * the actions in the state.
   *
   * @param obj The target CORBA object for the investigation
   *
   * @return Investigation result of FsmParticipant
   *
   * @since 0.4.0
   *
   * @endif
   */
  bool isFsmParticipant(CORBA::Object_ptr obj);
  
  /*!
   * @if jp
   *
   * @brief Fsm �Ǥ��뤫Ƚ�ꤹ��
   *
   * ���ꤵ�줿RT����ݡ��ͥ�Ȥ� Fsm �Ǥ��뤫Ƚ�ꤹ�롣
   * Fsm �ϡ� ExecutionContext �� Semantics �� Stimulus Response Processing ��
   * ���ˡ��������ܤ�������뤿������Ѥ����RT����ݡ��ͥ�Ȥη��Ǥ��롣
   *
   * @param obj Ƚ���оݤ� CORBA ���֥�������
   *
   * @return Fsm Ƚ����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @brief Confirm whether specified RT-Component is Fsm
   *
   * Confirm whether specified RT-Component is Fsm.
   * Fsm is a type of the RT-Component that is used when Semantics of 
   * ExecutionContext is Stimulus Response Processing. It is uset to define the 
   * state transition.
   *
   * @param obj The target CORBA object for the investigation
   *
   * @return Investigation result of Fsm
   *
   * @since 0.4.0
   *
   * @endif
   */
  bool isFsmObject(CORBA::Object_ptr obj);
  
  /*!
   * @if jp
   *
   * @brief multiModeComponent �Ǥ��뤫Ƚ�ꤹ��
   *
   * ���ꤵ�줿RT����ݡ��ͥ�Ȥ� multiModeComponent �Ǥ��뤫Ƚ�ꤹ�롣
   * multiModeComponent �ϡ� ExecutionContext �� Semantics �� Modes of Operation 
   * �ξ��ˡ� Mode ��������뤿������Ѥ����RT����ݡ��ͥ�Ȥη��Ǥ��롣
   *
   * @param obj Ƚ���оݤ� CORBA ���֥�������
   *
   * @return multiModeComponent Ƚ����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @brief Confirm whether specified RT-Component is multiModeComponent
   *
   * Confirm whether specified RT-Component is multiModeComponent.
   * multiModeComponent is a type of the RT-Component which is used when
   * Semantics of ExecutionContext is Modes of Operation. It is used to define
   * Mode.
   *
   * @param obj The target CORBA object for the investigation
   *
   * @return Investigation result of multiModeComponent
   *
   * @since 0.4.0
   *
   * @endif
   */
  bool isMultiModeObject(CORBA::Object_ptr obj);
}; // namespace RTC_Utils
#endif // RTCUtil_h
