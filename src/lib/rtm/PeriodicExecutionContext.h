// -*- C++ -*-
/*!
 * @file PeriodicExecutionContext.h
 * @brief PeriodicExecutionContext class
 * @date $Date: 2008-01-14 07:53:05 $
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
 * $Id: PeriodicExecutionContext.h 2063 2011-03-10 13:55:48Z n-ando $
 *
 */

#ifndef RTC_PERIODICEXECUTIONCONTEXT_H
#define RTC_PERIODICEXECUTIONCONTEXT_H

#include <coil/Task.h>
#include <coil/Mutex.h>
#include <coil/Condition.h>
#include <vector>
#include <iostream>

#include <rtm/RTC.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>
#include <rtm/Manager.h>
#include <rtm/StateMachine.h>
#include <rtm/ExecutionContextBase.h>

#define NUM_OF_LIFECYCLESTATE 4

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class PeriodicExecutionContext
   * @brief PeriodicExecutionContext ���饹
   *
   * Periodic Sampled Data Processing(�����¹���)ExecutionContext���饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class PeriodicExecutionContext
   * @brief PeriodicExecutionContext class
   *
   * Periodic Sampled Data Processing (for the execution cycles)
   * ExecutionContext class
   *
   * @since 0.4.0
   *
   * @endif
   */
  class PeriodicExecutionContext
    : public virtual ExecutionContextBase,
      public coil::Task
  {
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief �ǥե���ȥ��󥹥ȥ饯��
     *
     * �ǥե���ȥ��󥹥ȥ饯��
     * �ץ�ե�����˰ʲ��ι��ܤ����ꤹ�롣
     *  - kind : PERIODIC
     *  - rate : 0.0
     *
     * @else
     * @brief Default Constructor
     *
     * Default Constructor
     * Set the following items to profile.
     *  - kind : PERIODIC
     *  - rate : 0.0
     *
     * @endif
     */
    PeriodicExecutionContext();
    
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     * ���ꤵ�줿�ͤ�ץ�ե���������ꤹ�롣
     *
     * @param owner ���� Executioncontext �� owner
     * @param rate ư�����(Hz)(�ǥե������:1000)
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     * Set the configuration value to profile.
     *
     * @param owner The owner of this Executioncontext
     * @param rate Execution cycle(Hz)(The default value:1000)
     *
     * @endif
     */
    PeriodicExecutionContext(OpenRTM::DataFlowComponent_ptr owner,
			     double rate = 1000.0);
    
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
    virtual ~PeriodicExecutionContext(void);
    
    /*!
     * @if jp
     * @brief CORBA ���֥������Ȼ��Ȥμ���
     *
     * �ܥ��֥������Ȥ� ExecutioncontextService �Ȥ��Ƥ� CORBA ���֥���
     * ���Ȼ��Ȥ�������롣
     *
     * @return CORBA ���֥������Ȼ���
     *
     * @else
     * @brief Get the reference to the CORBA object
     *
     * Get the reference to the CORBA object as
     * ExecutioncontextService of this object.
     *
     * @return The reference to CORBA object
     *
     * @endif
     */
    virtual ExecutionContextService_ptr getObjRef(void) {return m_ref;}
    
    /*!
     * @if jp
     * @brief ExecutionContext�ѥ����ƥ��ӥƥ�����åɤ���������
     *
     * Executioncontext �Ѥ����������ƥ��ӥƥ�����åɤ���������ư���롣
     * ����� coil::Task �����ӥ����饹�᥽�åɤΥ����С��饤�ɡ�
     *
     * @param args �̾��0
     *
     * @return ���������¹Է��
     *
     * @else
     *
     * @brief Generate internal activity thread for ExecutionContext
     *
     * Generate internal activity thread and run.  This is coil::Task
     * class method's override.
     *
     * @param args Usually give 0
     *
     * @return The generation result
     *
     * @endif
     */     
    virtual int open(void *args);
    
    /*!
     * @if jp
     * @brief ExecutionContext �ѤΥ���åɼ¹Դؿ�
     *
     * ExecutionContext �ѤΥ���åɼ¹Դؿ�����Ͽ���줿����ݡ��ͥ��
     * �ν�����ƤӽФ���
     *
     * @return �¹Է��
     *
     * @else
     * @brief Thread execution function for ExecutionContext
     *
     * Thread execution function for ExecutionContext.  Invoke the
     * registered components operation.
     *
     * @return The execution result
     *
     * @endif
     */     
    virtual int svc(void);
    
    /*!
     * @if jp
     * @brief ExecutionContext �ѤΥ���åɼ¹Դؿ�
     *
     * ExecutionContext �ѤΥ���åɽ�λ���˸ƤФ�롣����ݡ��ͥ�ȥ�
     * �֥������Ȥ��󥢥��ƥ��ֲ����ޥ͡�����ؤ����Τ�Ԥ��������
     * coil::Task �����ӥ����饹�᥽�åɤΥ����С��饤�ɡ�
     *
     * @param flags ��λ�����ե饰
     *
     * @return ��λ�������
     *
     * @else
     *
     * @brief Thread execution function for ExecutionContext
     *
     * This function is invoked when activity thread for
     * ExecutionContext exits.  Deactivate the component object and
     * notify it to manager.  This is coil::Task class method's
     * override.
     *
     * @param flags Flag of the close
     *
     * @return The close result
     *
     * @endif
     */     
    virtual int close(unsigned long flags);
    
    //============================================================
    // ExecutionContext
    //============================================================
    /*!
     * @if jp
     * @brief ExecutionContext �¹Ծ��ֳ�ǧ�ؿ�
     *
     * �������� ExecutionContext �� Runnning ���֤ξ��� true ���֤���
     * Executioncontext �� Running �δ֡����� Executioncontext �˻��ä�
     * �Ƥ������ƤΥ����ƥ���RT����ݡ��ͥ�Ȥ���ExecutionContext �μ�
     * �Լ���˱����Ƽ¹Ԥ���롣
     *
     * @return ���ֳ�ǧ�ؿ�(ư����:true�������:false)
     *
     * @else
     *
     * @brief Check for ExecutionContext running state
     *
     * This operation shall return true if the context is in the
     * Running state.  While the context is Running, all Active RTCs
     * participating in the context shall be executed according to the
     * context��s execution kind.
     *
     * @return Check state function (Running:true��Stopping:false)
     *
     * @endif
     */
    virtual CORBA::Boolean is_running(void)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Ԥ򳫻�
     *
     * ExecutionContext �μ¹Ծ��֤� Runnning �Ȥ��뤿��Υꥯ�����Ȥ�
     * ȯ�Ԥ��롣ExecutionContext �ξ��֤����ܤ����
     * ComponentAction::on_startup ���ƤӽФ���롣���ä��Ƥ���RT����ݡ�
     * �ͥ�Ȥ�������������ޤ� ExecutionContext �򳫻Ϥ��뤳�ȤϤǤ�
     * �ʤ���ExecutionContext ��ʣ���󳫻�/��ߤ򷫤��֤����Ȥ��Ǥ��롣
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Start the ExecutionContext
     *
     * Request that the context enter the Running state.  Once the
     * state transition occurs, the ComponentAction::on_startup
     * operation will be invoked.  An execution context may not be
     * started until the RT-Components that participate in it have
     * been initialized.  An execution context may be started and
     * stopped multiple times.
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t start(void)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Ԥ����
     *
     * ExecutionContext �ξ��֤� Stopped �Ȥ��뤿��Υꥯ�����Ȥ�ȯ�Ԥ�
     * �롣���ܤ�ȯ���������ϡ�ComponentAction::on_shutdown ���Ƥӽ�
     * ����롣���ä��Ƥ���RT����ݡ��ͥ�Ȥ���λ��������
     * ExecutionContext ����ߤ���ɬ�פ����롣ExecutionContext ��ʣ����
     * ����/��ߤ򷫤��֤����Ȥ��Ǥ��롣
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Stop the ExecutionContext
     *
     * Request that the context enter the Stopped state.  Once the
     * transition occurs, the ComponentAction::on_shutdown operation
     * will be invoked.  An execution context must be stopped before
     * the RT components that participate in it are finalized.  An
     * execution context may be started and stopped multiple times.
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t stop(void)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Լ���(Hz)���������
     *
     * Active ���֤ˤ�RT����ݡ��ͥ�Ȥ��¹Ԥ�������(ñ��:Hz)�������
     * �롣
     *
     * @return ��������(ñ��:Hz)
     *
     * @else
     *
     * @brief Get execution rate(Hz) of ExecutionContext
     *
     * This operation shall return the rate (in hertz) at which its
     * Active participating RTCs are being invoked.
     *
     * @return Execution cycle(Unit:Hz)
     *
     * @endif
     */
    virtual CORBA::Double get_rate(void)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Լ���(Hz)�����ꤹ��
     *
     * Active ���֤ˤ�RT����ݡ��ͥ�Ȥ��¹Ԥ�������(ñ��:Hz)�����ꤹ
     * �롣�¹Լ������ѹ��ϡ�DataFlowComponentAction ��
     * on_rate_changed �ˤ�äƳ�RT����ݡ��ͥ�Ȥ���ã����롣
     *
     * @param rate ��������(ñ��:Hz)
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Set execution rate(Hz) of ExecutionContext
     *
     * This operation shall set the rate (in hertz) at which this
     * context��s Active participating RTCs are being called.  If the
     * execution kind of the context is PERIODIC, a rate change shall
     * result in the invocation of on_rate_changed on any RTCs
     * realizing DataFlowComponentAction that are registered with any
     * RTCs participating in the context.
     *
     * @param rate Execution cycle(Unit:Hz)
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t  set_rate(CORBA::Double rate)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ򥢥��ƥ��ֲ�����
     *
     * Inactive ���֤ˤ���RT����ݡ��ͥ�Ȥ�Active �����ܤ����������ƥ�
     * �ֲ����롣�������ƤФ줿��̡�on_activate ���ƤӽФ���롣��
     * �ꤷ��RT����ݡ��ͥ�Ȥ����üԥꥹ�Ȥ˴ޤޤ�ʤ����ϡ�
     * BAD_PARAMETER ���֤���롣���ꤷ��RT����ݡ��ͥ�Ȥξ��֤�
     * Inactive �ʳ��ξ��ϡ�PRECONDITION_NOT_MET ���֤���롣
     *
     * @param comp �����ƥ��ֲ��о�RT����ݡ��ͥ��
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Activate an RT-component
     *
     * The given participant RTC is Inactive and is therefore not
     * being invoked according to the execution context��s execution
     * kind. This operation shall cause the RTC to transition to the
     * Active state such that it may subsequently be invoked in this
     * execution context.  The callback on_activate shall be called as
     * a result of calling this operation. This operation shall not
     * return until the callback has returned, and shall result in an
     * error if the callback does.
     *
     * @param comp The target RT-Component for activation
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t activate_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ�����
     *
     * Inactive ���֤ˤ���RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ�����Inactive
     * �����ܤ����롣�������ƤФ줿��̡�on_deactivate ���ƤӽФ���
     * �롣���ꤷ��RT����ݡ��ͥ�Ȥ����üԥꥹ�Ȥ˴ޤޤ�ʤ����ϡ�
     * BAD_PARAMETER ���֤���롣���ꤷ��RT����ݡ��ͥ�Ȥξ��֤�
     * Active �ʳ��ξ��ϡ�PRECONDITION_NOT_MET ���֤���롣
     *
     * @param comp �󥢥��ƥ��ֲ��о�RT����ݡ��ͥ��
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Deactivate an RT-component
     *
     * The given RTC is Active in the execution context. Cause it to
     * transition to the Inactive state such that it will not be
     * subsequently invoked from the context unless and until it is
     * activated again.  The callback on_deactivate shall be called as
     * a result of calling this operation. This operation shall not
     * return until the callback has returned, and shall result in an
     * error if the callback does.
     *
     * @param comp The target RT-Component for deactivate
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t deactivate_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ�ꥻ�åȤ���
     *
     * Error ���֤�RT����ݡ��ͥ�Ȥ��������ߤ롣�������ƤФ줿��
     * �̡�on_reset ���ƤӽФ���롣���ꤷ��RT����ݡ��ͥ�Ȥ����üԥ�
     * ���Ȥ˴ޤޤ�ʤ����ϡ�BAD_PARAMETER ���֤���롣���ꤷ��RT����
     * �ݡ��ͥ�Ȥξ��֤� Error �ʳ��ξ��ϡ�PRECONDITION_NOT_MET ����
     * ����롣
     *
     * @param comp �ꥻ�å��о�RT����ݡ��ͥ��
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Reset the RT-component
     *
     * Attempt to recover the RTC when it is in Error.  The
     * ComponentAction::on_reset callback shall be invoked. This
     * operation shall not return until the callback has returned, and
     * shall result in an error if the callback does. If possible, the
     * RTC developer should implement that callback such that the RTC
     * may be returned to a valid state.
     *
     * @param comp The target RT-Component for reset
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t reset_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥξ��֤��������
     *
     * ���ꤷ��RT����ݡ��ͥ�Ȥξ���(LifeCycleState)��������롣���ꤷ
     * ��RT����ݡ��ͥ�Ȥ����üԥꥹ�Ȥ˴ޤޤ�ʤ����ϡ�
     * UNKNOWN_STATE ���֤���롣
     *
     * @param comp ���ּ����о�RT����ݡ��ͥ��
     *
     * @return ���ߤξ���(LifeCycleState)
     *
     * @else
     *
     * @brief Get RT-component's state
     *
     * This operation shall report the LifeCycleState of the given
     * participant RTC.  UNKNOWN_STATE will be returned, if the given
     * RT-Component is not inclued in the participant list.
     *
     * @param comp The target RT-Component to get the state
     *
     * @return The current state of the target RT-Component(LifeCycleState)
     *
     * @endif
     */
    virtual LifeCycleState get_component_state(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionKind ���������
     *
     * �� ExecutionContext �� ExecutionKind ���������
     *
     * @return ExecutionKind
     *
     * @else
     *
     * @brief Get the ExecutionKind
     *
     * This operation shall report the execution kind of the execution
     * context.
     *
     * @return ExecutionKind
     *
     * @endif
     */
    virtual ExecutionKind get_kind(void)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ��ɲä���
     *
     * ���ꤷ��RT����ݡ��ͥ�Ȥ򻲲üԥꥹ�Ȥ��ɲä��롣�ɲä��줿RT��
     * ��ݡ��ͥ�Ȥ� attach_context ���ƤФ졢Inactive ���֤����ܤ��롣
     * ���ꤵ�줿RT����ݡ��ͥ�Ȥ�null�ξ��ϡ�BAD_PARAMETER ���֤���
     * �롣���ꤵ�줿RT����ݡ��ͥ�Ȥ� DataFlowComponent �ʳ��ξ��ϡ�
     * BAD_PARAMETER ���֤���롣
     *
     * @param comp �ɲ��о�RT����ݡ��ͥ��
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Add an RT-component
     *
     * The operation causes the given RTC to begin participating in
     * the execution context.  The newly added RTC will receive a call
     * to LightweightRTComponent::attach_context and then enter the
     * Inactive state.  BAD_PARAMETER will be invoked, if the given
     * RT-Component is null or if the given RT-Component is other than
     * DataFlowComponent.
     *
     * @param comp The target RT-Component for add
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t add_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);

    /*!
     * @if jp
     * @brief ����ݡ��ͥ�Ȥ�Х���ɤ��롣
     *
     * ����ݡ��ͥ�Ȥ�Х���ɤ��롣
     *
     * @param rtc RT����ݡ��ͥ��
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * @else
     * @brief Bind the component.
     *
     * Bind the component.
     *
     * @param rtc RT-Component's instances
     * @return The return code of ReturnCode_t type
     * @endif
     */
    virtual RTC::ReturnCode_t bindComponent(RTObject_impl* rtc);
    
    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ򻲲üԥꥹ�Ȥ���������
     *
     * ���ꤷ��RT����ݡ��ͥ�Ȥ򻲲üԥꥹ�Ȥ��������롣������줿
     * RT����ݡ��ͥ�Ȥ� detach_context ���ƤФ�롣���ꤵ�줿RT����ݡ�
     * �ͥ�Ȥ����üԥꥹ�Ȥ���Ͽ����Ƥ��ʤ����ϡ�BAD_PARAMETER ����
     * ����롣
     *
     * @param comp ����о�RT����ݡ��ͥ��
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Remove the RT-Component from participant list
     *
     * This operation causes a participant RTC to stop participating in the
     * execution context.
     * The removed RTC will receive a call to
     * LightweightRTComponent::detach_context.
     * BAD_PARAMETER will be returned, if the given RT-Component is not 
     * participating in the participant list.
     *
     * @param comp The target RT-Component for delete
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t remove_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContextProfile ���������
     *
     * �� ExecutionContext �Υץ�ե������������롣
     *
     * @return ExecutionContextProfile
     *
     * @else
     *
     * @brief Get the ExecutionContextProfile
     *
     * This operation provides a profile ��descriptor�� for the execution 
     * context.
     *
     * @return ExecutionContextProfile
     *
     * @endif
     */
    virtual ExecutionContextProfile* get_profile(void)
      throw (CORBA::SystemException);
    
  protected:
    //============================================================
    // DFPBase
    //============================================================
    typedef LifeCycleState ExecContextState;
    /*
      enum ExecContextState
      {
        INACTIVE_STATE,
        ACTIVE_STATE,
        ERROR_STATE,
      };
    */
    typedef RTC_Utils::StateHolder<ExecContextState> ECStates;
    
    /*!
     * @if jp
     * @class DFPBase
     * @brief DFPBase ���饹
     *
     * ���üԥꥹ�Ȥ���Ͽ���줿 DataFlowParticipant ��������뤿�����ݥ��饹��
     *
     * @since 0.4.0
     *
     * @else
     * @class DFPBase
     * @brief DFPBase class
     *
     * The abstract class to manage DataFlowParticipant registered in 
     * tha participant list.
     *
     * @since 0.4.0
     *
     * @endif
     */
    class DFPBase
    {
    public:
      
      /*!
       * @if jp
       * @brief ���󥹥ȥ饯��
       *
       * ���󥹥ȥ饯��
       *
       * @param id ��°���� ExecutionContext ��ID
       *
       * @else
       * @brief Constructor
       *
       * Constructor
       *
       * @param id ID of participating ExecutionContext
       *
       * @endif
       */
      DFPBase(RTC::ExecutionContextHandle_t id)
	: ec_id(id), m_sm(NUM_OF_LIFECYCLESTATE)
      {
	m_sm.setListener(this);
	m_sm.setEntryAction (ACTIVE_STATE, &DFPBase::on_activated);
	m_sm.setDoAction    (ACTIVE_STATE, &DFPBase::on_execute);
	m_sm.setPostDoAction(ACTIVE_STATE, &DFPBase::on_state_update);
	m_sm.setExitAction  (ACTIVE_STATE, &DFPBase::on_deactivated);
	m_sm.setEntryAction (ERROR_STATE,  &DFPBase::on_aborting);
	m_sm.setDoAction    (ERROR_STATE,  &DFPBase::on_error);
	m_sm.setExitAction  (ERROR_STATE,  &DFPBase::on_reset);
	
	ECStates st;
	st.prev = INACTIVE_STATE;
	st.curr = INACTIVE_STATE;
	st.next = INACTIVE_STATE;
	m_sm.setStartState(st);
	m_sm.goTo(INACTIVE_STATE);
      }	
      
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
      virtual ~DFPBase(void){}
      
      /*!
       * @if jp
       * @brief ExecutionContext �¹Գ��ϻ��˸ƤФ���貾�۴ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext ���¹Ԥ򳫻Ϥ����(Running���֤����ܻ�)
       * �˸ƤФ���貾�۴ؿ���
       *
       * @else
       *
       * @brief Pure virtual function to be invoked when ExecutionContext starts
       *
       * Pure virtual function to be invoked when given execution context, in
       * which the RTC is participating, has transited from Stopped to Running.
       *
       * @endif
       */
      virtual void on_startup(void) = 0;
      
      /*!
       * @if jp
       * @brief ExecutionContext ��߻��˸ƤФ���貾�۴ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext ���¹Ԥ���ߤ����(Stopped���֤����ܻ�)
       * �˸ƤФ���貾�۴ؿ���
       *
       * @else
       *
       * @brief Pure virtual function to be invoked when ExecutionContext stops
       *
       * Pure virtual function to be invoked when given execution context, in
       * which the RTC is participating, has transited from Running to Stopped.
       *
       * @endif
       */
      virtual void on_shutdown(void) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ������ƥ��ֲ����줿���˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ������ƥ��ֲ����줿��
       * (Active���֤����ܻ�)�˸ƤФ���貾�۴ؿ���
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief Pure virtual function to be invoked when RT-Component is 
       *        activated
       *
       * Pure virtual function to be invoked when the RTC has been activated
       * in the given execution context.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      virtual void on_activated(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ����줿���˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ����줿��
       * (Deactive���֤����ܻ�)�˸ƤФ���貾�۴ؿ���
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief Pure virtual function to be invoked when RT-Component is 
       *        deactivated
       *
       * Pure virtual function to be invoked when the RTC has been deactivated
       * in the given execution context.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      virtual void on_deactivated(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥǥ��顼��ȯ���������˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ˥��顼��ȯ��������(Error���֤����ܻ�)
       * �˸ƤФ���貾�۴ؿ���
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief Pure virtual function to be invoked when RT-Component occurs 
       *        error
       *
       * Pure virtual function to be invoked when the RTC is transiting from
       * the Active state to the Error state in some execution context.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      virtual void on_aborting(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ����顼���֤λ��˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ����顼���֤ˤ���֡�on_execute ��
       * on_state_update ���ؤ�ä����Ū�˸ƤӽФ�����貾�۴ؿ���
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief Pure virtual function to be invoked while RT-Component
       * is in the error state
       *
       * If the RTC is in the Error state relative to some execution context
       * when it would otherwise be invoked from that context.
       * This operation shall be invoked in sorted order at the rate of the
       * context instead of DataFlowComponentAction::on_execute and 
       * on_state_update.The RTC is transitioning from the Active state to 
       * the Error state in some execution context.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      virtual void on_error(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ�ꥻ�åȤ�����˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ�ꥻ�åȤ���ݤ˸ƤФ���貾�۴ؿ���
       * ���δؿ�������˽�λ����ȡ�RTC�� Inactive ���֤��������롣
       * ���δؿ�������˽�λ���ʤ��ä����ϡ� Error ���֤�α�ޤ롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief Pure virtual function to be invoked when RT-Component resets.
       *
       * The RTC is in the Error state. An attempt is being made to recover it 
       * such that it can return to the Inactive state.
       * If the RTC was successfully recovered and can safely return to 
       * the Inactive state, this method shall complete with ReturnCode_t::OK.
       * Any other result shall indicate that the RTC should remain in the 
       * Error state.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      virtual void on_reset(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�ȼ¹Ի������Ū�˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ� Active ���֤Ǥ���ȤȤ�ˡ�
       * ExecutionContext �� Running ���֤ξ��ˡ����ꤵ�줿ư����������Ū��
       * �ƤӽФ�����貾�۴ؿ���
       * Two-Pass Execution �κǽ�μ¹ԤǸƤФ�롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief Pure virtual function to be periodically invoked while 
       *        RT-Component is running
       *
       * This operation will be invoked periodically at the rate of the given
       * execution context as long as the following conditions hold:
       *  - The RTC is Active.
       *  - The given execution context is Running.
       * This callback occurs during the first execution pass.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      virtual void on_execute(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�ȼ¹Ի������Ū�˸ƤФ���貾�۴ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ� Active ���֤Ǥ���ȤȤ�ˡ�
       * ExecutionContext �� Running ���֤ξ��ˡ����ꤵ�줿ư����������Ū��
       * �ƤӽФ�����貾�۴ؿ���
       * Two-Pass Execution �Σ����ܤμ¹ԤǸƤФ�롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       *
       * @brief Pure virtual function to be periodically invoked while 
       *        RT-Component is running
       *
       * This operation will be invoked periodically at the rate of the given
       * execution context as long as the following conditions hold:
       *  - The RTC is Active.
       *  - The given execution context is Running.
       * This callback occurs during the second execution pass.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      virtual void on_state_update(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief ExecutionContext �μ¹Լ����ѹ����˸ƤФ���貾�۴ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext �μ¹Լ������ѹ��Ȥʤä����ˡ�
       * �����ѹ�����ã���뤿��˸ƤӽФ�����貾�۴ؿ���
       *
       * @else
       *
       * @brief Pure virtual function to be invoked when when the execution 
       *        cycles of ExecutionContext is changed.
       *
       * This operation is a notification that the rate of the indicated
       * execution context has changed.
       *
       * @endif
       */
      virtual void on_rate_changed(void) = 0;
      
      /*!
       * @if jp
       * @brief �������ܤ�¹Ԥ����������������
       *
       * �����о�RT����ݡ��ͥ�Ȥξ������ܤ�¹Ԥ���������������롣
       *
       * @return �����
       *
       * @else
       * @brief Get the worker to execute the state transition
       *
       * Get the worker that executes the state transition of the target
       * component to manage.
       *
       * @return The worker
       *
       * @endif
       */
      virtual void worker(void) {return m_sm.worker();}
      
      /*!
       * @if jp
       * @brief ���ߤξ��֤��������
       *
       * �����о�RT����ݡ��ͥ�Ȥθ��ߤξ��֤�������롣
       *
       * @return ���߾���
       *
       * @else
       * @brief Get the current state of the target component
       *
       * Get the current state of the target component to manage
       *
       * @return The current state of the target RT-Component
       *
       * @endif
       */
      virtual ExecContextState get_state(void){ return m_sm.getState();}
      
      /*!
       * @if jp
       * @brief ���ä��Ƥ��� ExecutionContext �� ID
       * @else
       * @brief ID of participating ExecutionContext
       * @endif
       */
      ExecutionContextHandle_t ec_id;
      
      /*!
       * @if jp
       * @brief �����о�RT����ݡ��ͥ�ȤΥ��ơ��ȥޥ���
       * @else
       * @brief The state machine of the target RT-Component to manage
       * @endif
       */
      RTC_Utils::StateMachine<ExecContextState, DFPBase> m_sm;
    };
    
    //============================================================
    // DFP
    //============================================================
    /*!
     * @if jp
     * @class DFP
     * @brief DFP ���饹
     *
     * ���üԥꥹ�Ȥ���Ͽ���줿 DataFlowParticipant �δؿ���ư���뤿���
     * �ƥ�ץ졼�ȥ��饹��
     *
     * @param Object �����оݥ���ݡ��ͥ�Ȥη�
     *
     * @since 0.4.0
     *
     * @else
     * @class DFP
     * @brief DFP class
     *
     * Template class to invoke DataFlowParticipant registered
     * in the participant list.
     *
     * @param Object Type of the target component to manage
     *
     * @since 0.4.0
     *
     * @endif
     */
    template <class Object>
    class DFP
      : public DFPBase
    {
    public:
      /*!
       * @if jp
       * @brief �ǥե���ȥ��󥹥ȥ饯��
       *
       * �ǥե���ȥ��󥹥ȥ饯��
       *
       * @param obj �����оݥ���ݡ��ͥ��
       * @param id ��°���� ExecutionContext ��ID
       *
       * @else
       * @brief Default constructor
       *
       * Default constructor
       *
       * @param obj The target component to manage
       * @param id ID of participating ExecutionContext
       *
       * @endif
       */
      DFP(Object obj, ExecutionContextHandle_t id)
	: DFPBase(id), m_obj(obj), m_active(true)
      {
      }
      
      /*!
       * @if jp
       * @brief ExecutionContext �¹Գ��ϻ��˸ƤФ��ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext ���¹Ԥ򳫻Ϥ����(Running���֤����ܻ�)
       * �ˡ������оݥ���ݡ��ͥ�Ȥ� on_startup ��ƤӤ�����
       *
       * @else
       * @brief Function to be invoked when ExecutionContext starts
       *
       * When the given ExecutionContext transits from Stopped to Running,
       * on_startup of the participation component will be invoked.
       *
       * @endif
       */
      void on_startup(void)
      {
	m_obj->on_startup(ec_id);
      }
      
      /*!
       * @if jp
       * @brief ExecutionContext ��߻��˸ƤФ��ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext ���¹Ԥ���ߤ����(Stopped���֤����ܻ�)
       * �ˡ������оݥ���ݡ��ͥ�Ȥ� on_shutdown ��ƤӤ�����
       *
       * @else
       * @brief Function to be invoked when ExecutionContext stops
       *
       * When the given ExecutionContext transits from Running to Stopped,
       * on_shutdown of the participation component will be invoked.
       *
       * @endif
       */
      void on_shutdown(void)
      {
	m_obj->on_shutdown(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ������ƥ��ֲ����줿���˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ������ƥ��ֲ����줿��(Active���֤����ܻ�)
       * �ˡ������оݥ���ݡ��ͥ�Ȥ� on_activated ��ƤӤ�����
       * �����оݥ���ݡ��ͥ�ȤΥ����ƥ��ֲ������Ԥ������ˤϡ����ơ��ȥޥ���
       * �� Error ���֤����ܤ����롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       * @brief Function to be invoked when RT-Component was activated
       *
       * When the given ExecutionContext transits to the Active state,
       * on_activated of the participation component will be invoked.
       * If it fails, the state machine transits to the Errot state.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      void on_activated(const ECStates& st)
      {
	if (m_obj->on_activated(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }
	return;
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ����줿���˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ����줿��
       * (Deactive���֤����ܻ�)�ˡ������оݥ���ݡ��ͥ�Ȥ� on_deactivated ��
       * �ƤӤ�����
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       * @brief Function to be invoked when RT-Component was deactivated
       *
       * When the given ExecutionContext transits the Deactivate state,
       * on_deactivated of the participation component will be invoked.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      void on_deactivated(const ECStates& st)
      {
	m_obj->on_deactivated(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥǥ��顼��ȯ���������˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ˥��顼��ȯ��������(Error���֤����ܻ�)
       * �˴����оݥ���ݡ��ͥ�Ȥ� on_aborting ��ƤӤ�����
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       * @brief Function to be invoked when RT-Component occured error
       *
       * When the given ExecutionContext transits the Error state,
       * on_aborting of the participation component will be invoked.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      void on_aborting(const ECStates& st)
      {
	m_obj->on_aborting(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ����顼���֤λ��˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ����顼���֤ˤ���֡�
       * �����оݥ���ݡ��ͥ�Ȥ� on_aborting �����Ū�˸ƤӤ�����
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       * @brief Function to be invoked while RT-Component is in the error state
       *
       * While the given RT-Component is in the Error state,
       * its on_aborting will be periodically invoked.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      void on_error(const ECStates& st)
      {
	m_obj->on_error(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�Ȥ�ꥻ�åȤ�����˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ�ꥻ�åȤ���ݤˡ������оݥ���ݡ��ͥ��
       * �� on_reset ��ƤӤ�����
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       * @brief Function to be invoked when RT-Component is reset.
       *
       * When the target RT-Component is reset,
       * invoke on_reset of the target component to manage.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      void on_reset(const ECStates& st)
      {
	if (m_obj->on_reset(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }
	return;
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�ȼ¹Ի������Ū�˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ� Active ���֤Ǥ���ȤȤ�ˡ�
       * ExecutionContext �� Running ���֤ξ��ˡ����ꤵ�줿ư�������
       * ���Ū�˴����оݥ���ݡ��ͥ�Ȥ� on_execute ��ƤӤ������ؿ���
       * �¹Ԥ˼��Ԥ������(���ͤ� RTC_OK �ʳ�)�������оݥ���ݡ��ͥ��
       * �ξ��֤� Error ���֤����ܤ����롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       * @brief Periodic exection function while running RT-Component
       *
       * If the given RT-Component is in the Active state and
       * ExecutionContext is in the Running state, on_execute of the
       * given component will be invoked periodically at the specified
       * execution cycle.  If it fails (the return value is other than
       * RTC_OK), its state transits to the Errot state.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      void on_execute(const ECStates& st)
      {
	if (m_obj->on_execute(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }  
	return;
      }
      
      /*!
       * @if jp
       * @brief RT����ݡ��ͥ�ȼ¹Ի������Ū�˸ƤФ��ؿ�
       *
       * �����оݤ�RT����ݡ��ͥ�Ȥ� Active ���֤Ǥ���ȤȤ�ˡ�
       * ExecutionContext �� Running ���֤ξ��ˡ����ꤵ�줿ư�������
       * ���Ū�˴����оݥ���ݡ��ͥ�Ȥ� on_state_update ��ƤӤ�����
       * �ؿ��μ¹Ԥ˼��Ԥ������(���ͤ� RTC_OK �ʳ�)�������оݥ���ݡ�
       * �ͥ�Ȥξ��֤� Error ���֤����ܤ����롣
       *
       * @param st �о�RT����ݡ��ͥ�Ȥθ��ߤξ���
       *
       * @else
       * @brief Function to be invoked periodically while RT-Component executes
       *
       * When the target RT-Component to manage is in the Active state
       * and ExecutionContext is the Running, invoke on_state_update
       * of the target component to manage periodically in specified
       * execution cycle.  If it fails (the return value is other than
       * RTC_OK), its state transits to the Errot state.
       *
       * @param st The current state of the target RT-Component
       *
       * @endif
       */
      void on_state_update(const ECStates& st)
      {
	if (m_obj->on_state_update(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }
	return;
      }
      
      /*!
       * @if jp
       * @brief ExecutionContext �μ¹Լ����ѹ����˸ƤФ��ؿ�
       *
       * ���ä��Ƥ��� ExecutionContext �μ¹Լ������ѹ��Ȥʤä����ˡ�
       * �����оݥ���ݡ��ͥ�Ȥ� on_rate_changed ��ƤӤ�����
       *
       * @else
       * @brief Function to be invoked when the execution cycles of
       *        ExecutionContext is changed
       *
       * When the execution cycle of the participating
       * ExecutionContext is changed, invoke on_rate_changed of the
       * target component will be invoked.
       *
       * @endif
       */
      void on_rate_changed(void)
      {
	m_obj->on_rate_changed(ec_id);
      }
      
      /*!
       * @if jp
       * @brief �����оݥ���ݡ��ͥ��
       * @else
       * @brief The target component to manage
       * @endif
       */
      Object m_obj;
      
      /*!
       * @if jp
       * @brief �����оݥ���ݡ��ͥ�Ȥ�ư����֥ե饰
       * @else
       * @brief State flag of the target component to manage
       * @endif
       */
      bool m_active;
    };
    
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȴ����ѹ�¤��
     * @else
     * @brief The structure for the component management
     * @endif
     */
    struct Comp
    {
      Comp(LightweightRTObject_ptr ref, OpenRTM::DataFlowComponent_ptr dfp,
	   ExecutionContextHandle_t id)
	: _ref(LightweightRTObject::_duplicate(ref)),
	  _sm(OpenRTM::DataFlowComponent::_duplicate(dfp), id)
      {
      }
      ~Comp(void)
      {
      }
      Comp(const Comp& comp)
	: _ref(comp._ref), _sm(comp._sm.m_obj, comp._sm.ec_id)
      {
      }
      Comp& operator=(const Comp& comp)
      {
	_ref = comp._ref;
	_sm.m_obj = comp._sm.m_obj;
	_sm.ec_id = comp._sm.ec_id;
	return *this;
      }
      LightweightRTObject_var _ref;
      DFP<OpenRTM::DataFlowComponent_var> _sm;
    };

    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȸ����ѥե��󥯥�
     * @else
     * @brief Functor to find the component
     * @endif
     */
    struct find_comp
    {
      LightweightRTObject_var m_comp;
      find_comp(LightweightRTObject_ptr comp)
        : m_comp(LightweightRTObject::_duplicate(comp)) {}
      bool operator()(Comp& comp)
      {
	return comp._ref->_is_equivalent(m_comp);
      }
    };
    
    /*!
     * @if jp
     * @brief on_startup ��ư�ѥե��󥯥�
     * @else
     * @brief Functor to invoke on_startup
     * @endif
     */
    struct invoke_on_startup
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_startup();
      }
    };
    
    /*!
     * @if jp
     * @brief on_shutdown ��ư�ѥե��󥯥�
     * @else
     * @brief Functor to invoke on_shutdown
     * @endif
     */
    struct invoke_on_shutdown
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_shutdown();
      }
    };
    
    /*!
     * @if jp
     * @brief on_rate_changed ��ư�ѥե��󥯥�
     * @else
     * @brief Functor to invoke on_rate_changed
     * @endif
     */
    struct invoke_on_rate_changed
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_rate_changed();
      }
    };
    
    /*!
     * @if jp
     * @brief ������¹��ѥե��󥯥�
     * @else
     * @brief Functor to invoke worker
     * @endif
     */
    struct invoke_worker
    {
      void operator()(Comp& comp)
      {
	comp._sm.worker();
      }
    };
    
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�Ȥλ��üԥꥹ��
     * @else
     * @brief List of the participating component
     * @endif
     */
    std::vector<Comp> m_comps;
    typedef std::vector<Comp>::iterator CompItr;
    
    /*!
     * @if jp
     * @brief �������ȥ꡼��
     * @else
     * @brief Logger stream
     * @endif
     */
    Logger rtclog;

    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Ծ���
     * true: running, false: stopped
     * @else
     * @brief The running state of ExecutionContext
     * true: running, false: stopped
     * @endif
     */
    bool m_running;

    /*!
     * @if jp
     * @brief ExecutionContext �Υ���åɼ¹ԥե饰
     * @else
     * @brief The thread running flag of ExecutionContext
     * @endif
     */
    bool m_svc;

    /*!
     * @if jp
     * @brief worker �Ѿ����ѿ����饹
     * @else
     * @brief Condition variable class for worker
     * @endif
     */
    struct Worker
    {
      Worker() : cond_(mutex_), running_(false) {};
      coil::Mutex mutex_;
      coil::Condition<coil::Mutex> cond_;
      bool running_;
    };

    /*!
     * @if jp
     * @brief svn�Ѥξ����ѿ� 
     * @else
     * @brief A condition variable for external triggered worker
     * @endif
     */
    Worker m_worker;
    
    /*!
     * @if jp
     * @brief ExecutionContextProfile
     * @else
     * @brief ExecutionContextProfile
     * @endif
     */
    ExecutionContextProfile m_profile;
    coil::Mutex m_profileMutex;
    
    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Լ���
     * @else
     * @brief Execution cycle of ExecutionContext
     * @endif
     */
    coil::TimeValue m_period;
    
    /*!
     * @if jp
     * @brief ExecutionContextService ���֥������Ȥؤλ���
     * @else
     * @brief Reference to ExecutionContextService object
     * @endif
     */
    ExecutionContextService_var m_ref;
    
    /*!
     * @if jp
     * @brief ExecutionContext ¨���¹�(wait̵���¹�)�ե饰
     * @else
     * @brief Flag of ExecutionContext to run immediately
     *        (to run without waiting)
     * @endif
     */
    bool m_nowait;

    class find_participant
    {
      RTObject_var m_comp;
    public:      
      find_participant(RTObject_ptr comp)
        : m_comp(RTObject::_duplicate(comp)) {}
      bool operator()(RTObject_ptr comp)
      {
        return m_comp->_is_equivalent(comp);
      }
    };
  }; // class PeriodicExecutionContext
}; // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif


extern "C"
{
  /*!
   * @if jp
   * @brief ECFactory�ؤ���Ͽ�Τ���ν�����ؿ�
   * @else
   * @brief Initialization function to register to ECFactory
   * @endif
   */
  void PeriodicExecutionContextInit(RTC::Manager* manager);
};

#endif // RTC_PERIODICEXECUTIONCONTEXT_H
