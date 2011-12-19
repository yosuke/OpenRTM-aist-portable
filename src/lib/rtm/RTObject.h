// -*- C++ -*-
/*!
 * @file RTObject.h
 * @brief RT component base class
 * @date $Date: 2008-01-14 07:57:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2010
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTObject.h 2232 2011-10-10 16:17:08Z n-ando $
 *
 */

#ifndef RTC_RTOBJECT_H
#define RTC_RTOBJECT_H

// CORBA header include
#include <coil/Properties.h>

#include <rtm/RTC.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>
#include <rtm/PortBase.h>
#include <rtm/PortAdmin.h>
#include <rtm/InPortBase.h>
#include <rtm/OutPortBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/ConfigAdmin.h>
#include <rtm/SystemLogger.h>
#include <rtm/ComponentActionListener.h>
#include <rtm/SdoServiceAdmin.h>
#include <rtm/PortConnectListener.h>

#define ECOTHER_OFFSET 1000

namespace SDOPackage
{
  class Configuration_impl;
};

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  class Manager;
  class ExecutionContextBase;
  typedef ExecutionContextHandle_t UniqueId;

  /*!
   * @if jp
   * @brief RT����ݡ��ͥ�ȥ��饹
   *
   * ��RT����ݡ��ͥ�ȤΥ١����Ȥʤ륯�饹��
   * Robotic Technology Component ������� lightweightRTComponent�μ������饹��
   * ����ݡ��ͥ�Ȥε�ǽ���󶡤��� ComponentAction ���󥿡��ե�������
   * ����ݡ��ͥ�ȤΥ饤�ե������������Ԥ������ LightweightRTObject �μ�����
   * �󶡤��롣
   * �ºݤ˥桼��������ݡ��ͥ�Ȥ����������ˤϡ�Execution Semantics ���б�
   * �����ƥ��֥��饹�����Ѥ��롣<BR>
   * (�����μ����Ǥ� Periodic Sampled Data Processing �Τߥ��ݡ��Ȥ��Ƥ��뤿�ᡢ
   *  dataFlowComponent ��ľ�ܷѾ����Ƥ���)
   *
   * @since 0.2.0
   *
   * @else
   * @brief RT-Component class
   *
   * This is a class to be a base of each RT-Component.
   * This is a implementation class of lightweightRTComponent in Robotic
   * Technology Component specification.
   * This provides a implementation of ComponentAction interface that offers
   * the the component's function and the implementation of LightweightRTObject
   * for management of the component's lifecycle.
   * When users actually create the components, they should use each subclass
   * corresponding to Execution Semantics.<BR>
   * (In current implementation, since only Periodic Sampled Data Processing is
   * supported, this class inherits dataFlowComponent directly.)
   *
   * @since 0.2.0
   *
   * @endif
   */
  class RTObject_impl
    : public virtual POA_OpenRTM::DataFlowComponent, 
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param manager �ޥ͡����㥪�֥�������
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param manager Manager object
     *
     * @endif
     */
    RTObject_impl(Manager* manager);
    
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param orb ORB
     * @param poa POA
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param orb ORB
     * @param poa POA
     *
     * @endif
     */
    RTObject_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    
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
    virtual ~RTObject_impl(void);
    
  protected:
    //============================================================
    // Overridden functions
    //============================================================
    /*!
     * @if jp
     *
     * @brief ����������ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_initialize ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå�
     * �ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�Ȥμºݤν���������ϡ��ܴؿ��򥪡��С��饤�ɤ��Ƽ�������
     * ɬ�פ����롣
     * 
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function to initialize
     * 
     * This is a callback function that is executed when
     * ComponentAction::on_initialize was invoked.<BR>
     * As for actual initialization of each component, since this function is
     * dummy-implemented to return RTC::RTC_OK unconditionally, you need to
     * implement this function by overriding it.
     * 
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The initialize action (on CREATED->ALIVE transition)
    // formaer rtc_init_entry() 
    virtual ReturnCode_t onInitialize();
    
    /*!
     * @if jp
     *
     * @brief ��λ�����ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_finalize ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå�
     * �ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�Ȥμºݤν�λ�����ϡ��ܴؿ��򥪡��С��饤�ɤ��Ƽ�������
     * ɬ�פ����롣
     * 
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function to finalize
     * 
     * This is a callback function that is executed when
     * ComponentAction::on_finalize was invoked.<BR>
     * As for actual finalization of each component, since this function is
     * dummy-implemented to return RTC::RTC_OK unconditionally, you need to
     * implement this function by overriding it.
     * 
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The finalize action (on ALIVE->END transition)
    // formaer rtc_exiting_entry()
    virtual ReturnCode_t onFinalize();
    
    /*!
     * @if jp
     *
     * @brief ���Ͻ����ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_startup ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå�
     * �ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�Ȥμºݤγ��Ͻ����ϡ��ܴؿ��򥪡��С��饤�ɤ��Ƽ�������
     * ɬ�פ����롣
     * 
     * @param exec_handle ���ä��Ƥ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function for startup action
     * 
     * Callback function that is executed when
     * ComponentAction::on_startup was invoked.<BR>
     * As for actual startup of each component, since this function is
     * dummy-implemented to return RTC::RTC_OK unconditionally, you need to
     * implement this function by overriding it.
     * 
     * @param exec_handle ID of the participant ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The startup action when ExecutionContext startup
    // former rtc_starting_entry()
    virtual ReturnCode_t onStartup(RTC::UniqueId exec_handle);
    
    /*!
     * @if jp
     *
     * @brief ��߽����ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_shutdown ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå�
     * �ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�Ȥμºݤ���߽����ϡ��ܴؿ��򥪡��С��饤�ɤ��Ƽ�������
     * ɬ�פ����롣
     * 
     * @param exec_handle ���ä��Ƥ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function for shutdown action
     * 
     * Callback function that is executed when
     * ComponentAction::on_shutdown was invoked.<BR>
     * As for actual shutdown of each component, since this function is
     * dummy-implemented to return RTC::RTC_OK unconditionally, you need to
     * implement this function by overriding it.
     * 
     * @param exec_handle ID of the participant ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The shutdown action when ExecutionContext stop
    // former rtc_stopping_entry()
    virtual ReturnCode_t onShutdown(RTC::UniqueId exec_handle);
    
    /*!
     * @if jp
     *
     * @brief �����������ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_activated ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå�
     * �ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�Ȥμºݤγ����������ϡ��ܴؿ��򥪡��С��饤�ɤ��Ƽ�������
     * ɬ�פ����롣
     * 
     * @param exec_handle ���ä��Ƥ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function to activate
     * 
     * This is a callback function that is executed when
     * ComponentAction::on_activated was invoked.<BR>
     * As for actual activation of each component, since this function is
     * dummy-implemented to return RTC::RTC_OK unconditionally, you need to
     * implement this function by overriding it.
     * 
     * @param exec_handle ID of the participant ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The activated action (Active state entry action)
    // former rtc_active_entry()
    virtual ReturnCode_t onActivated(RTC::UniqueId exec_handle);
    
    /*!
     * @if jp
     *
     * @brief ������������ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_deactivated ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå�
     * �ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ����
     * �ǡ��ƥ���ݡ��ͥ�Ȥμºݤ�������������ϡ��ܴؿ��򥪡��С��饤
     * �ɤ��Ƽ�������ɬ�פ����롣
     * 
     * @param exec_handle ���ä��Ƥ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function to deactivate
     * 
     * This is a callback function that is executed when
     * ComponentAction::on_deactivated was invoked.<BR>
     * As for actual deactivation of each component, since this function is
     * dummy-implemented to return RTC::RTC_OK unconditionally, you need to
     * implement this function by overriding it.
     * 
     * @param exec_handle ID of the participant ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The deactivated action (Active state exit action)
    // former rtc_active_exit()
    virtual ReturnCode_t onDeactivated(RTC::UniqueId exec_handle);
    
    /*!
     * @if jp
     *
     * @brief ���������ѥ�����Хå��ؿ�
     * 
     * DataFlowComponentAction::on_execute ���ƤФ줿�ݤ˼¹Ԥ����
     * ������Хå��ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�Ȥμºݤμ��������ϡ��ܴؿ��򥪡��С��饤�ɤ��Ƽ�������
     * ɬ�פ����롣<BR>
     * �ܴؿ��� Periodic Sampled Data Processing �ˤ����� Two-Pass Execution��
     * �����ܤμ¹ԥѥ��Ȥ������Ū�˸ƤӽФ���롣
     * 
     * @param exec_handle ���ä��Ƥ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function to execute periodically
     * 
     * This is a callback function that is executed when
     * DataFlowComponentAction::on_execute is invoked.<BR>
     * As for actual periodic execution of each component, since this
     * function is dummy-implemented to return RTC::RTC_OK
     * unconditionally, you need to implement this function by
     * overriding it.  This function is invoked periodically as the
     * first execution pass of Two-Pass Execution in Periodic Sampled
     * Data Processing.
     * 
     * @param exec_handle ID of the participant ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The execution action that is invoked periodically
    // former rtc_active_do()
    virtual ReturnCode_t onExecute(RTC::UniqueId exec_handle);
    
    /*!
     * @if jp
     *
     * @brief ���ǽ����ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_aborting ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå�
     * �ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�Ȥμºݤ����ǽ����ϡ��ܴؿ��򥪡��С��饤�ɤ��Ƽ�������
     * ɬ�פ����롣
     * 
     * @param exec_handle ���ä��Ƥ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function to abort
     * 
     * This is a callback function that is executed when
     * ComponentAction::on_aborting was invoked.<BR>
     * As for actual abortion of each component, since this function is
     * dummy-implemented to return RTC::RTC_OK unconditionally, you need to
     * implement this function by overriding it.
     * 
     * @param exec_handle ID of the participant ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The aborting action when main logic error occurred.
    // former rtc_aborting_entry()
    virtual ReturnCode_t onAborting(RTC::UniqueId exec_handle);
    
    /*!
     * @if jp
     *
     * @brief ���顼�����ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_error ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå��ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�ȤμºݤΥ��顼�����ϡ��ܴؿ��򥪡��С��饤�ɤ��Ƽ�������
     * ɬ�פ����롣
     * 
     * @param exec_handle ���ä��Ƥ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function for error handling
     * 
     * This is a callback function that is executed when
     * ComponentAction::on_error was invoked.<BR>
     * As for actual error handling of each component, since this function is
     * dummy-implemented to return RTC::RTC_OK unconditionally, you need to
     * implement this function by overriding it.
     * 
     * @param exec_handle ID of the participant ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The error action in ERROR state
    // former rtc_error_do()
    virtual ReturnCode_t onError(RTC::UniqueId exec_handle);
    
    /*!
     * @if jp
     *
     * @brief �ꥻ�åȽ����ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_reset ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå��ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�ȤμºݤΥꥻ�åȽ����ϡ��ܴؿ��򥪡��С��饤�ɤ�
     * �Ƽ�������ɬ�פ����롣
     * 
     * @param exec_handle ���ä��Ƥ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function to reset
     * 
     * This is a callback function that is executed when
     * ComponentAction::on_reset was invoked.<BR>
     * As for actual reset of each component, since this function is
     * dummy-implemented to return RTC::RTC_OK unconditionally, you need to
     * implement this function by overriding it.
     * 
     * @param exec_handle ID of the participant ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The reset action that is invoked resetting
    // This is same but different the former rtc_init_entry()
    virtual ReturnCode_t onReset(RTC::UniqueId exec_handle);
    
    /*!
     * @if jp
     *
     * @brief �����ѹ������ѥ�����Хå��ؿ�
     * 
     * DataFlowComponentAction::on_state_update ���ƤФ줿�ݤ˼¹Ԥ����
     * ������Хå��ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�Ȥμºݤξ����ѹ������ϡ��ܴؿ��򥪡��С��饤�ɤ�
     * �Ƽ�������ɬ�פ����롣<BR> �ܴؿ��� Periodic Sampled Data
     * Processing �ˤ����� Two-Pass Execution�Σ����ܤμ¹ԥѥ��Ȥ�����
     * ��Ū�˸ƤӽФ���롣
     *
     * @param exec_handle ���ä��Ƥ��� ExecutionContext �� ID
     * 
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function to update the state
     * 
     * This is a callback function that is executed when
     * DataFlowComponentAction::on_state_update was invoked.<BR>
     * As for actual updating the state of each component, since this
     * function is dummy-implemented to return RTC::RTC_OK
     * unconditionally, you need to implement this function by
     * overriding it.<BR> This function is invoked periodically as the
     * second execution pass of Two-Pass Execution in Periodic Sampled
     * Data Processing.
     *
     * @param exec_handle ID of the participant ExecutionContext
     * 
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The state update action that is invoked after onExecute() action
    // no corresponding operation exists in OpenRTm-aist-0.2.0
    virtual ReturnCode_t onStateUpdate(RTC::UniqueId exec_handle);
    
    /*!
     * @if jp
     *
     * @brief ư������ѹ������ѥ�����Хå��ؿ�
     * 
     * DataFlowComponentAction::on_rate_changed ���ƤФ줿�ݤ˼¹Ԥ����
     * ������Хå��ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�Ȥμºݤξ����ѹ������ϡ��ܴؿ��򥪡��С��饤�ɤ�
     * �Ƽ�������ɬ�פ����롣<BR> �ܴؿ��� Periodic Sampled Data
     * Processing �ˤ����� ExecutionContext �μ¹Ԥ��������줿�ݤ˸Ƥ�
     * �Ф���롣
     *
     * @param exec_handle ���ä��Ƥ��� ExecutionContext �� ID
     * 
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief Callback function to change execution cycle
     * 
     * This is a callback function that is executed when
     * DataFlowComponentAction::on_rate_changed was invoked.<BR>
     * As for actual changing execution cycle of each component, since this 
     * function is dummy-implemented to return RTC::RTC_OK unconditionally,
     * you need to implement this function by overriding it.<BR>
     * This function is invoked when the execution of ExecutionContext 
     * was updated in Periodic Sampled Data Processing.
     *
     * @param exec_handle ID of the participant ExecutionContext
     * 
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    // The action that is invoked when execution context's rate is changed
    // no corresponding operation exists in OpenRTm-aist-0.2.0
    virtual ReturnCode_t onRateChanged(RTC::UniqueId exec_handle);
    
  public:
    //============================================================
    // RTC::LightweightRTObject
    //============================================================
    /*!
     * @if jp
     *
     * @brief [CORBA interface] RTC����������
     *
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��ơ�ComponentAction::on_initialize
     * ������Хå��ؿ����ƤФ�롣
     * 
     * ����
     * - RTC �� Created���֤ξ��߽�������Ԥ��롣¾�ξ��֤ˤ�����ˤ�
     *   ReturnCode_t::PRECONDITION_NOT_MET ���֤���ƤӽФ��ϼ��Ԥ��롣
     * - ���Υ��ڥ졼������ RTC �Υߥɥ륦��������ƤФ�뤳�Ȥ����ꤷ�Ƥ��ꡢ
     *   ���ץꥱ�������ȯ�Ԥ�ľ�ܤ��Υ��ڥ졼������Ƥ֤��Ȥ�����
     *   ����Ƥ��ʤ���
     * 
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief [CORBA interface] Initialize the RTC that realizes this interface.
     *
     * The invocation of this operation shall result in the invocation of the
     * callback ComponentAction::on_initialize.
     *
     * Constraints
     * - An RTC may be initialized only while it is in the Created state. Any
     *   attempt to invoke this operation while in another state shall fail
     *   with ReturnCode_t::PRECONDITION_NOT_MET.
     * - Application developers are not expected to call this operation
     *   directly; it exists for use by the RTC infrastructure.
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    virtual ReturnCode_t initialize()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] RTC ��λ����
     *
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� ComponentAction::on_finalize()
     * ��ƤӽФ���
     *
     * ����
     * - RTC �� ExecutionContext �˽�°���Ƥ���֤Ͻ�λ����ʤ������ξ��ϡ�
     *   �ޤ��ǽ�� ExecutionContextOperations::remove �ˤ�äƻ��ä�
     *   ������ʤ���Фʤ�ʤ�������ʳ��ξ��ϡ����Υ��ڥ졼�����ƤӽФ���
     *   �����ʤ���� ReturnCode_t::PRECONDITION_NOT_ME �Ǽ��Ԥ��롣
     * - RTC �� Created ���֤Ǥ����硢��λ�����ϹԤ��ʤ���
     *   ���ξ�硢���Υ��ڥ졼�����ƤӽФ��Ϥ����ʤ����
     *   ReturnCode_t::PRECONDITION_NOT_MET �Ǽ��Ԥ��롣
     * - ���Υ��ڥ졼������RTC�Υߥɥ륦��������ƤФ�뤳�Ȥ����ꤷ�Ƥ��ꡢ
     *   ���ץꥱ�������ȯ�Ԥ�ľ�ܤ��Υ��ڥ졼������Ƥ֤��Ȥ�����
     *   ����Ƥ��ʤ���
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief [CORBA interface] Finalize the RTC for destruction
     * 
     * This invocation of this operation shall result in the invocation of the
     * callback ComponentAction::on_finalize.
     *
     * Constraints
     * - An RTC may not be finalized while it is participating in any execution
     *   context. It must first be removed with 
     *   ExecutionContextOperations::remove. Otherwise, this operation
     *   shall fail with ReturnCode_t::PRECONDITION_NOT_MET. 
     * - An RTC may not be finalized while it is in the Created state. Any 
     *   attempt to invoke this operation while in that state shall fail with 
     *   ReturnCode_t::PRECONDITION_NOT_MET.
     * - Application developers are not expected to call this
     *   operation directly; it exists for use by the RTC
     *   infrastructure.
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    virtual ReturnCode_t finalize()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] RTC �������ʡ��Ǥ��� ExecutionContext ��
     *        ��ߤ��������Υ���ƥ�Ĥȶ��˽�λ������
     *
     * ���� RTC �������ʡ��Ǥ��뤹�٤Ƥμ¹ԥ���ƥ����Ȥ���ߤ��롣
     * ���� RTC ��¾�μ¹ԥ���ƥ����Ȥ��ͭ���� RTC ��°����¹ԥ���ƥ�����
     * (i.e. �¹ԥ���ƥ����Ȥ��ͭ���� RTC �Ϥ��ʤ�����μ¹ԥ���ƥ����Ȥ�
     * �����ʡ��Ǥ��롣)�˻��ä��Ƥ����硢���� RTC �Ϥ����Υ���ƥ����Ⱦ�
     * �������������ʤ���Фʤ�ʤ���
     * RTC ���¹���Τɤ� ExecutionContext �Ǥ� Active ���֤ǤϤʤ��ʤä��塢
     * ���� RTC �Ȥ���˴ޤޤ�� RTC ����λ���롣
     * 
     * ����
     * - RTC �����������Ƥ��ʤ���С���λ�����뤳�ȤϤǤ��ʤ���
     *   Created ���֤ˤ��� RTC �� exit() ��ƤӽФ�����硢
     *   ReturnCode_t::PRECONDITION_NOT_MET �Ǽ��Ԥ��롣
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * 
     * @else
     *
     * @brief [CORBA interface]top the RTC's execution context(s) and finalize
     *        it along with its contents.
     * 
     * Any execution contexts for which the RTC is the owner shall be stopped. 
     * If the RTC participates in any execution contexts belonging to another
     * RTC that contains it, directly or indirectly (i.e. the containing RTC
     * is the owner of the ExecutionContext), it shall be deactivated in those
     * contexts.
     * After the RTC is no longer Active in any Running execution context, it
     * and any RTCs contained transitively within it shall be finalized.
     *
     * Constraints
     * - An RTC cannot be exited if it has not yet been initialized. Any
     *   attempt to exit an RTC that is in the Created state shall fail with
     *   ReturnCode_t::PRECONDITION_NOT_MET.
     *
     * @return The return code of ReturnCode_t type
     * 
     * @endif
     */
    virtual ReturnCode_t exit()
      throw (CORBA::SystemException); 
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] RTC �� Alive ���֤Ǥ��뤫�ɤ�����ǧ���롣
     *
     * RTC �����ꤷ�� ExecutionContext ���Ф��� Alive���֤Ǥ��뤫�ɤ���
     * ��ǧ���롣RTC �ξ��֤� Active �Ǥ��뤫��Inactive �Ǥ��뤫��
     * Error �Ǥ��뤫�ϼ¹����ExecutionContext �˰�¸���롣���ʤ����
     * ���� ExecutionContext ���Ф��Ƥ�Active ���֤Ǥ��äƤ⡢¾��
     * ExecutionContext ���Ф��Ƥ� Inactive ���֤Ȥʤ���⤢�ꤨ�롣
     * ���äơ����Υ��ڥ졼�����ϻ��ꤵ�줿ExecutionContext ���䤤��
     * �碌�ơ����� RTC �ξ��֤� Active��Inactive��Error �ξ��ˤ�
     * Alive ���֤Ȥ����֤���
     *
     * @return Alive ���ֳ�ǧ���
     *
     * @else
     *
     * @brief [CORBA interface] Confirm whether RTC is the alive state
     *
     * A component is alive or not regardless of the execution context from
     * which it is observed. However, whether or not it is Active, Inactive,
     * or in Error is dependent on the execution context(s) in which it is
     * running. That is, it may be Active in one context but Inactive in
     * another. Therefore, this operation shall report whether this RTC is
     * either Active, Inactive or in Error; which of those states a component
     * is in with respect to a particular context may be queried from the
     * context itself.
     *
     * @return Result of Alive state confirmation
     *
     * @endif
     */
    virtual CORBA::Boolean is_alive(ExecutionContext_ptr exec_context)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief [CORBA interface] ExecutionContext���������
     *
     * ���ꤷ���ϥ�ɥ�� ExecutionContext ��������롣
     * �ϥ�ɥ뤫�� ExecutionContext �ؤΥޥåԥ󥰤ϡ������ RTC ���󥹥��󥹤�
     * ��ͭ�Ǥ��롣�ϥ�ɥ�Ϥ��� RTC �� attach_context �����ݤ˼����Ǥ��롣
     *
     * @param exec_handle �����о� ExecutionContext �ϥ�ɥ�
     *
     * @return ExecutionContext
     *
     * @else
     * @brief [CORBA interface] Get ExecutionContext.
     *
     * Obtain a reference to the execution context represented by the given 
     * handle.
     * The mapping from handle to context is specific to a particular RTC 
     * instance. The given handle must have been obtained by a previous call to 
     * attach_context on this RTC.
     *
     * @param exec_handle ExecutionContext handle
     *
     * @return ExecutionContext
     *
     * @endif
     */
    virtual ExecutionContext_ptr get_context(UniqueId exec_handle)
      throw (CORBA::SystemException);

    /*!
     * @if jp
     * @brief [CORBA interface] ��ͭ���� ExecutionContextList�� ��������
     *
     * ���� RTC ����ͭ���� ExecutionContext �Υꥹ�Ȥ�������롣
     *
     * @return ExecutionContext �ꥹ��
     *
     * @else
     * @brief [CORBA interface] Get ExecutionContextList.
     *
     * This operation returns a list of all execution contexts owned by this
     * RTC.
     *
     * @return ExecutionContext List
     *
     * @endif
     */
    virtual ExecutionContextList* get_owned_contexts()
      throw (CORBA::SystemException);

    /*!
     * @if jp
     * @brief [CORBA interface] ���ä��Ƥ��� ExecutionContextList ���������
     *
     * ���� RTC �����ä��Ƥ��� ExecutionContext �Υꥹ�Ȥ�������롣
     *
     * @return ExecutionContext �ꥹ��
     *
     * @else
     * @brief [CORBA interface] Get participating ExecutionContextList.
     *
     * This operation returns a list of all execution contexts in
     * which this RTC participates.
     *
     * @return ExecutionContext List
     *
     * @endif
     */
    virtual ExecutionContextList* get_participating_contexts()
      throw (CORBA::SystemException);

    /*!
     * @if jp
     * @brief [CORBA interface] ExecutionContext �Υϥ�ɥ���֤�
     *
     * Ϳ����줿�¹ԥ���ƥ����Ȥ˴�Ϣ�դ���줿�ϥ�ɥ���֤���
     *
     * @else
     * @brief [CORBA interface] Return a handle of a ExecutionContext
     *
     * This operation returns a handle that is associated with the given
     * execution context.
     *
     * @endif
     */
    virtual ExecutionContextHandle_t
    get_context_handle(ExecutionContext_ptr cxt)
      throw (CORBA::SystemException);

    /*!
     * @if jp
     * @brief [CORBA interface] ExecutionContext��attach����
     *
     * ���ꤷ�� ExecutionContext �ˤ��� RTC ���°�����롣���� RTC �ȴ�Ϣ���� 
     * ExecutionContext �Υϥ�ɥ���֤���
     * ���Υ��ڥ졼�����ϡ�ExecutionContextOperations::add_component
     * ���ƤФ줿�ݤ˸ƤӽФ���롣�֤��줿�ϥ�ɥ��¾�Υ��饤����Ȥ�
     * ���Ѥ��뤳�Ȥ����ꤷ�Ƥ��ʤ���
     *
     * @param exec_context ��°�� ExecutionContext
     *
     * @return ExecutionContext �ϥ�ɥ�
     *
     * @else
     * @brief [CORBA interface] Attach ExecutionContext
     *
     * Inform this RTC that it is participating in the given execution context. 
     * Return a handle that represents the association of this RTC with the 
     * context.
     * This operation is intended to be invoked by 
     * ExecutionContextOperations::add_component. It is not intended for use by 
     * other clients.
     *
     * @param exec_context Participating ExecutionContext
     *
     * @return ExecutionContext Handle
     *
     * @endif
     */
    UniqueId attach_context(ExecutionContext_ptr exec_context)
      throw (CORBA::SystemException);

    UniqueId bindContext(ExecutionContext_ptr exec_context);
    
    /*!
     * @if jp
     * @brief [CORBA interface] ExecutionContext��detach����
     *
     * ���ꤷ�� ExecutionContext ���餳�� RTC �ν�°�������롣
     * ���Υ��ڥ졼�����ϡ�ExecutionContextOperations::remove ���Ƥ�
     * �줿�ݤ˸ƤӽФ���롣�֤��줿�ϥ�ɥ��¾�Υ��饤����Ȥǻ��Ѥ��뤳�Ȥ�
     * ���ꤷ�Ƥ��ʤ���
     * 
     * ����
     * - ���ꤵ�줿 ExecutionContext �� RTC �����Ǥ˽�°���Ƥ��ʤ����ˤϡ�
     *   ReturnCode_t::PRECONDITION_NOT_MET ���֤���롣
     * - ���ꤵ�줿 ExecutionContext �ˤ��������Ф��� RTC ��Active ���֤Ǥ����
     *   ��ˤϡ� ReturnCode_t::PRECONDITION_NOT_MET ���֤���롣
     *
     * @param exec_handle ����о� ExecutionContext�ϥ�ɥ�
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     * @brief [CORBA interface] Detach ExecutionContext.
     *
     * Inform this RTC that it is no longer participating in the given
     * execution context.
     * This operation is intended to be invoked by 
     * ExecutionContextOperations::remove. It is not intended for use 
     * by other clients.
     * Constraints
     * - This operation may not be invoked if this RTC is not already 
     *   participating in the execution context. Such a call shall fail with 
     *   ReturnCode_t::PRECONDITION_NOT_MET.
     * - This operation may not be invoked if this RTC is Active in
     *   the indicated execution context. Otherwise, it shall fail
     *   with ReturnCode_t::PRECONDITION_NOT_MET.
     *
     * @param exec_handle Detaching ExecutionContext Handle
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    ReturnCode_t detach_context(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    //============================================================
    // RTC::RTObject
    //============================================================
    /*!
     * @if jp
     *
     * @brief [RTObject CORBA interface] ����ݡ��ͥ�ȥץ�ե�������������
     *
     * ��������ݡ��ͥ�ȤΥץ�ե����������֤��� 
     *
     * @return ����ݡ��ͥ�ȥץ�ե�����
     *
     * @else
     *
     * @brief [RTObject CORBA interface] Get RTC's profile
     *
     * This operation returns the ComponentProfile of the RTC.
     *
     * @return ComponentProfile
     *
     * @endif
     */
    virtual ComponentProfile* get_component_profile()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [RTObject CORBA interface] �ݡ��Ȥ��������
     *
     * ��������ݡ��ͥ�Ȥ���ͭ����ݡ��Ȥλ��Ȥ��֤���
     *
     * @return �ݡ��ȥꥹ��
     *
     * @else
     *
     * @brief [RTObject CORBA interface] Get Ports
     *
     * This operation returns the reference of ports held by RTC.
     *
     * @return PortServiceList
     *
     * @endif
     */
    virtual PortServiceList* get_ports()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [RTObject CORBA interface] ExecutionContextAdmin ���������
     *
     * ���Υ��ڥ졼���������� RTC ����°���� ExecutionContext�˴�Ϣ����
     * ExecutionContextService �Υꥹ�Ȥ��֤���
     *
     * @return ExecutionContextService �ꥹ��
     *
     * @else
     *
     * @brief [RTObject CORBA interface] Get ExecutionContextAdmin
     *
     * This operation returns a list containing an ExecutionContextAdmin for
     * every ExecutionContext owned by the RTC.	
     *
     * @return ExecutionContextService List
     *
     * @endif
     */
    //    virtual ExecutionContextServiceList* get_execution_context_services()
    //      throw (CORBA::SystemException);
    
    //============================================================
    // RTC::ComponentAction
    //============================================================
    /*!
     * @if jp
     *
     * @brief [ComponentAction CORBA interface] RTC �ν����
     *
     * RTC ����������졢Alive ���֤����ܤ��롣
     * RTC ��ͭ�ν���������Ϥ����Ǽ¹Ԥ��롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onInitialize() ������Хå��ؿ���
     * �ƤӽФ���롣
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [ComponentAction CORBA interface] Initialize RTC
     *
     * The RTC has been initialized and entered the Alive state.
     * Any RTC-specific initialization logic should be performed here.
     * As a result of this operation, onInitialize() callback function
     * is called.
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_initialize()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [ComponentAction CORBA interface] RTC �ν�λ
     *
     * RTC ���˴�����롣
     * RTC ��ͭ�ν�λ�����Ϥ����Ǽ¹Ԥ��롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onFinalize() ������Хå��ؿ���
     * �ƤӽФ���롣
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [ComponentAction CORBA interface] Finalize RTC
     *
     * The RTC is being destroyed.
     * Any final RTC-specific tear-down logic should be performed here.
     * As a result of this operation, onFinalize() callback function is called.
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_finalize()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [ComponentAction CORBA interface] RTC �γ���
     *
     * RTC ����°���� ExecutionContext �� Stopped ���֤��� Running ���֤�����
     * �������˸ƤӽФ���롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onStartup() ������Хå��ؿ���
     * �ƤӽФ���롣
     *
     * @param exec_handle �������ܤ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [ComponentAction CORBA interface] Startup RTC
     *
     * The given execution context, in which the RTC is participating, has 
     * transitioned from Stopped to Running.
     * As a result of this operation, onStartup() callback function is called.
     *
     * @param exec_handle ID of ExecutionContext that transited to the state
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_startup(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [ComponentAction CORBA interface] RTC �����
     *
     * RTC ����°���� ExecutionContext �� Running ���֤��� Stopped ���֤�����
     * �������˸ƤӽФ���롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onShutdown() ������Хå��ؿ���
     * �ƤӽФ���롣
     *
     * @param exec_handle �������ܤ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [ComponentAction CORBA interface] Shutdown RTC
     *
     * The given execution context, in which the RTC is participating, has 
     * transitioned from Running to Stopped.
     * As a result of this operation, onShutdown() callback function is called.
     *
     * @param exec_handle ID of ExecutionContext that transited to the state
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_shutdown(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [ComponentAction CORBA interface] RTC �γ�����
     *
     * ��°���� ExecutionContext ���� RTC �����������줿�ݤ˸ƤӽФ���롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onActivated() ������Хå��ؿ���
     * �ƤӽФ���롣
     *
     * @param exec_handle ������ ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [ComponentAction CORBA interface] Activate RTC
     *
     * The RTC has been activated in the given execution context.
     * As a result of this operation, onActivated() callback function is called.
     *
     * @param exec_handle ID of activation ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_activated(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [ComponentAction CORBA interface] RTC ���������
     *
     * ��°���� ExecutionContext ���� RTC ������������줿�ݤ˸ƤӽФ���롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onDeactivated() ������Хå��ؿ���
     * �ƤӽФ���롣
     *
     * @param exec_handle ������� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [ComponentAction CORBA interface] Deactivate RTC
     *
     * The RTC has been deactivated in the given execution context.
     * As a result of this operation, onDeactivated() callback function
     * is called.
     *
     * @param exec_handle ID of deactivation ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_deactivated(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [ComponentAction CORBA interface] RTC �Υ��顼���֤ؤ�����
     *
     * RTC ����°���� ExecutionContext �� Active ���֤��� Error ���֤����ܤ���
     * ���˸ƤӽФ���롣
     * ���Υ��ڥ졼������ RTC �� Error ���֤����ܤ����ݤ˰��٤����Ƥ�
     * �Ф���롣���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onAborting() ����
     * ��Хå��ؿ����ƤӽФ���롣
     *
     * @param exec_handle �������ܤ��� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [ComponentAction CORBA interface] Transition to Error State
     *
     * The RTC is transitioning from the Active state to the Error state in some
     * execution context.
     * This callback is invoked only a single time for time that the RTC 
     * transitions into the Error state from another state. This behavior is in 
     * contrast to that of on_error.
     * As a result of this operation, onAborting() callback function is invoked.
     *
     * @param exec_handle ID of ExecutionContext that transited to the state
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_aborting(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [ComponentAction CORBA interface] RTC �Υ��顼����
     *
     * RTC �����顼���֤ˤ���ݤ˸ƤӽФ���롣
     * RTC �����顼���֤ξ��ˡ��оݤȤʤ� ExecutionContext ��ExecutionKind ��
     * �����������ߥ󥰤ǸƤӽФ���롣�㤨�С�
     * - ExecutionKind �� PERIODIC �ξ�硢�ܥ��ڥ졼������
     *   DataFlowComponentAction::on_execute �� on_state_update ���ؤ��ˡ�
     *   ���ꤵ�줿���֡����ꤵ�줿�����ǸƤӽФ���롣
     * - ExecutionKind �� EVENT_DRIVEN �ξ�硢�ܥ��ڥ졼������
     *   FsmParticipantAction::on_action ���ƤФ줿�ݤˡ��ؤ��˸ƤӽФ���롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onError() ������Хå��ؿ����Ƥӽ�
     * ����롣
     *
     * @param exec_handle �о� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [ComponentAction CORBA interface] Error Processing of RTC
     *
     * The RTC remains in the Error state.
     * If the RTC is in the Error state relative to some execution context when
     * it would otherwise be invoked from that context (according to the 
     * context��s ExecutionKind), this callback shall be invoked instead. 
     * For example,
     * - If the ExecutionKind is PERIODIC, this operation shall be invoked in 
     *   sorted order at the rate of the context instead of 
     *   DataFlowComponentAction::on_execute and on_state_update.
     * - If the ExecutionKind is EVENT_DRIVEN, this operation shall be invoked 
     *   whenever FsmParticipantAction::on_action would otherwise have been 
     *   invoked.
     * As a result of this operation, onError() callback function is invoked.
     *
     * @param exec_handle ID of target ExecutionContext
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_error(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [ComponentAction CORBA interface] RTC �Υꥻ�å�
     *
     * Error ���֤ˤ��� RTC �Υꥫ�Х������¹Ԥ���Inactive ���֤�����������
     * ���˸ƤӽФ���롣
     * RTC �Υꥫ�Х������������������ Inactive ���֤��������뤬������ʳ���
     * ���ˤ� Error ���֤�α�ޤ롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onReset() ������Хå��ؿ����Ƥ�
     * �Ф���롣
     *
     * @param exec_handle �ꥻ�å��о� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [ComponentAction CORBA interface] Resetting RTC
     *
     * The RTC is in the Error state. An attempt is being made to
     * recover it such that it can return to the Inactive state.
     * If the RTC was successfully recovered and can safely return to
     * the Inactive state, this method shall complete with
     * ReturnCode_t::OK. Any other result shall indicate that the RTC
     * should remain in the Error state.  As a result of this
     * operation, onReset() callback function is invoked.
     *
     * @param exec_handle ID of target ExecutionContext for the reset
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_reset(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    //============================================================
    // RTC::DataFlowComponentAction
    //============================================================
    /*!
     * @if jp
     *
     * @brief [DataFlowComponentAction CORBA interface] RTC ��������(������)
     *
     * �ʲ��ξ��֤��ݻ�����Ƥ�����ˡ����ꤵ�줿���������Ū�˸ƤӽФ���롣
     * - RTC �� Alive ���֤Ǥ��롣
     * - ���ꤵ�줿 ExecutionContext �� Running ���֤Ǥ��롣
     * �ܥ��ڥ졼�����ϡ�Two-Pass Execution ���������Ǽ¹Ԥ���롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onExecute() ������Хå��ؿ����Ƥ�
     * �Ф���롣
     *
     * ����
     * - ���ꤵ�줿 ExecutionContext �� ExecutionKind �ϡ� PERIODIC �Ǥʤ���Ф�
     *   ��ʤ�
     *
     * @param exec_handle �������о� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [DataFlowComponentAction CORBA interface] Primary Periodic 
     *        Operation of RTC
     *
     * This operation will be invoked periodically at the rate of the given
     * execution context as long as the following conditions hold:
     * - The RTC is Active.
     * - The given execution context is Running
     * This callback occurs during the first execution pass.
     * As a result of this operation, onExecute() callback function is invoked.
     *
     * Constraints
     * - The execution context of the given context shall be PERIODIC.
     *
     * @param exec_handle ID of target ExecutionContext for Primary
     *                    Periodic Operation
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_execute(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [DataFlowComponentAction CORBA interface] RTC ��������(�������)
     *
     * �ʲ��ξ��֤��ݻ�����Ƥ�����ˡ����ꤵ�줿���������Ū�˸ƤӽФ���롣
     * - RTC �� Alive ���֤Ǥ��롣
     * - ���ꤵ�줿 ExecutionContext �� Running ���֤Ǥ��롣
     * �ܥ��ڥ졼�����ϡ�Two-Pass Execution ����������Ǽ¹Ԥ���롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onStateUpdate() ������Хå��ؿ���
     * �ƤӽФ���롣
     *
     * ����
     * - ���ꤵ�줿 ExecutionContext �� ExecutionKind �ϡ� PERIODIC �Ǥʤ���Ф�
     *   ��ʤ�
     *
     * @param exec_handle �������о� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [DataFlowComponentAction CORBA interface] Secondary Periodic 
     *        Operation of RTC
     *
     * This operation will be invoked periodically at the rate of the given
     * execution context as long as the following conditions hold:
     * - The RTC is Active.
     * - The given execution context is Running
     * This callback occurs during the second execution pass.
     * As a result of this operation, onStateUpdate() callback function is
     * invoked.
     *
     * Constraints
     * - The execution context of the given context shall be PERIODIC.
     *
     * @param exec_handle ID of target ExecutionContext for 
     *              Secondary Periodic Operation
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_state_update(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [DataFlowComponentAction CORBA interface] �¹Լ����ѹ�����
     *
     * �ܥ��ڥ졼�����ϡ�ExecutionContext �μ¹Լ������ѹ����줿���Ȥ����Τ���
     * �ݤ˸ƤӽФ���롣
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��� onRateChanged() ������Хå��ؿ���
     * �ƤӽФ���롣
     *
     * ����
     * - ���ꤵ�줿 ExecutionContext �� ExecutionKind �ϡ� PERIODIC �Ǥʤ���Ф�
     *   ��ʤ�
     *
     * @param exec_handle �������о� ExecutionContext �� ID
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [DataFlowComponentAction CORBA interface] Notify rate changed
     *
     * This operation is a notification that the rate of the indicated execution 
     * context has changed.
     * As a result of this operation, onRateChanged() callback function is 
     * called.
     *
     * Constraints
     * - The execution context of the given context shall be PERIODIC.
     *
     * @param exec_handle ID of target ExecutionContext for Operation
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t on_rate_changed(UniqueId exec_handle)
      throw (CORBA::SystemException);
    
    //============================================================
    // SDOPackage::SdoSystemElement
    //============================================================
    /*!
     * @if jp
     * 
     * @brief [SDO interface] Organization �ꥹ�Ȥμ��� 
     *
     * SDOSystemElement ��0�Ĥ⤷���Ϥ���ʾ�� Organization ���ͭ���뤳�Ȥ�
     * ����롣 SDOSystemElement ��1�İʾ�� Organization ���ͭ���Ƥ�����
     * �ˤϡ����Υ��ڥ졼�����Ͻ�ͭ���� Organization �Υꥹ�Ȥ��֤���
     * �⤷Organization���Ĥ��ͭ���Ƥ��ʤ�����ж��Υꥹ�Ȥ��֤���
     *
     * @return ��ͭ���Ƥ��� Organization �ꥹ��
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [SDO interface] Get Organization list
     *
     * SDOSystemElement can be the owner of zero or more organizations.
     * If the SDOSystemElement owns one or more Organizations, this operation
     * returns the list of Organizations that the SDOSystemElement owns.
     * If it does not own any Organization, it returns empty list.
     *
     * @return Owned Organization List
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual SDOPackage::OrganizationList* get_owned_organizations()
      throw (CORBA::SystemException,
             SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    //============================================================
    // SDOPackage::SDO
    //============================================================
    /*!
     * @if jp
     * 
     * @brief [SDO interface] SDO ID �μ���
     *
     * SDO ID ���֤����ڥ졼�����
     * ���Υ��ڥ졼�����ϰʲ��η����㳰��ȯ�������롣
     * 
     * @return    �꥽�����ǡ�����ǥ���������Ƥ��� SDO �� ID
     * 
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [SDO interface] Get the SDO ID
     *
     * This operation returns id of the SDO.
     * This operation throws SDOException with one of the following types.
     *
     * @return    id of the SDO defined in the resource data model.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual char* get_sdo_id()
      throw (CORBA::SystemException,
	     SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [SDO interface] SDO �����פμ���
     * 
     * SDO Type ���֤����ڥ졼�����
     * ���Υ��ڥ졼�����ϰʲ��η����㳰��ȯ�������롣
     *
     * @return    �꥽�����ǡ�����ǥ���������Ƥ��� SDO �� Type
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [SDO interface] Get SDO type
     *
     * This operation returns sdoType of the SDO.
     * This operation throws SDOException with one of the following types.
     *
     * @return    Type of the SDO defined in the resource data model.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual char* get_sdo_type()
      throw (CORBA::SystemException, 
	     SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [SDO interface] SDO DeviceProfile �ꥹ�Ȥμ��� 
     *
     * SDO �� DeviceProfile ���֤����ڥ졼����� SDO ���ϡ��ɥ������ǥХ���
     * �˴�Ϣ�դ����Ƥ��ʤ����ˤϡ����� DeviceProfile ���֤���롣
     * ���Υ��ڥ졼�����ϰʲ��η����㳰��ȯ�������롣
     *
     * @return    SDO DeviceProfile
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [SDO interface] Get SDO DeviceProfile list
     *
     * This operation returns the DeviceProfile of the SDO. If the SDO does not
     * represent any hardware device, then a DeviceProfile with empty values
     * are returned.
     * This operation throws SDOException with one of the following types.
     *
     * @return    The DeviceProfile of the SDO.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual SDOPackage::DeviceProfile* get_device_profile()
      throw (CORBA::SystemException, 
	     SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [SDO interface] SDO ServiceProfile �μ��� 
     *
     * SDO ����ͭ���Ƥ��� Service �� ServiceProfile ���֤����ڥ졼�����
     * SDO �������ӥ����Ĥ��ͭ���Ƥ��ʤ����ˤϡ����Υꥹ�Ȥ��֤���
     * ���Υ��ڥ졼�����ϰʲ��η����㳰��ȯ�������롣
     * 
     * @return    SDO ���󶡤������Ƥ� Service �� ServiceProfile��
     * 
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [SDO interface] Get SDO ServiceProfile
     * 
     * This operation returns a list of ServiceProfiles that the SDO has.
     * If the SDO does not provide any service, then an empty list is returned.
     * This operation throws SDOException with one of the following types.
     * 
     * @return    List of ServiceProfiles of all the services the SDO is
     *            providing.
     * 
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual SDOPackage::ServiceProfileList* get_service_profiles()
      throw (CORBA::SystemException, 
	     SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [SDO interface] �����ServiceProfile�μ��� 
     *
     * ���� "id" �ǻ��ꤵ�줿̾���Υ����ӥ��� ServiceProfile ���֤���
     * 
     * @param     id SDO Service �� ServiceProfile �˴�Ϣ�դ���줿���̻ҡ�
     * 
     * @return    ���ꤵ�줿 SDO Service �� ServiceProfile��
     * 
     * @exception InvalidParameter "id" �ǻ��ꤷ�� ServiceProfile ��¸�ߤ��ʤ���
     *                             "id" �� null��
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [SDO interface] Get specified ServiceProfile
     *
     * This operation returns the ServiceProfile that is specified by the
     * argument "id."
     * 
     * @param     id The identifier referring to one of the ServiceProfiles.
     * 
     * @return    The profile of the specified service.
     * 
     * @exception InvalidParameter The ServiceProfile that is specified by 
     *                             the argument 'id' does not exist or if 'id'
     *                             is 'null.'
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual SDOPackage::ServiceProfile* get_service_profile(const char* id)
      throw (CORBA::SystemException, 
	     SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [SDO interface] ���ꤵ�줿 SDO Service �μ���
     *
     * ���Υ��ڥ졼�����ϰ��� "id" �ǻ��ꤵ�줿̾���ˤ�äƶ��̤����
     * SDO �� Service �ؤΥ��֥������Ȼ��Ȥ��֤��� SDO �ˤ���󶡤����
     * Service �Ϥ��줾���դμ��̻Ҥˤ����̤���롣
     *
     * @param id SDO Service �˴�Ϣ�դ���줿���̻ҡ�
     *
     * @return �׵ᤵ�줿 SDO Service �ؤλ��ȡ�
     *
     * 
     * @exception InvalidParameter "id" �ǻ��ꤷ�� ServiceProfile ��¸�ߤ��ʤ���
     *                             "id" �� null��
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [SDO interface] Get specified SDO Service's reference
     *
     * This operation returns an object implementing an SDO's service that
     * is identified by the identifier specified as an argument. Different
     * services provided by an SDO are distinguished with different
     * identifiers. See OMG SDO specification Section 2.2.8, "ServiceProfile,"
     * on page 2-12 for more details.
     *
     * @param id The identifier referring to one of the SDO Service
     *
     * @return The reference requested to SDO Service.
     *
     * @exception InvalidParameter Argument ��id�� is null, or if the 
     *                             ServiceProfile that is specified by argument
     *                            ��id�� does not exist.
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual SDOPackage::SDOService_ptr get_sdo_service(const char* id)
      throw (CORBA::SystemException, 
	     SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [SDO interface] Configuration ���֥������Ȥμ��� 
     *
     * ���Υ��ڥ졼������ Configuration interface �ؤλ��Ȥ��֤���
     * Configuration interface �ϳ� SDO ��������뤿��Υ��󥿡��ե�������
     * �ҤȤĤǤ��롣���Υ��󥿡��ե������� DeviceProfile, ServiceProfile,
     * Organization ��������줿 SDO ��°���ͤ����ꤹ�뤿��˻��Ѥ���롣
     * Configuration ���󥿡��ե������ξܺ٤ˤĤ��Ƥϡ�OMG SDO specification
     * �� 2.3.5��, p.2-24 �򻲾ȤΤ��ȡ�
     *
     * @return SDO �� Configuration ���󥿡��ե������ؤλ���
     *
     * @exception InterfaceNotImplemented SDO��Configuration���󥿡��ե�������
     *                                    �����ʤ���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [SDO interface] Get Configuration object
     *
     * This operation returns an object implementing the Configuration
     * interface. The Configuration interface is one of the interfaces that
     * each SDO maintains. The interface is used to configure the attributes
     * defined in DeviceProfile, ServiceProfile, and Organization.
     * See OMG SDO specification Section 2.3.5, "Configuration Interface,"
     * on page 2-24 for more details about the Configuration interface.
     *
     * @return The Configuration interface of an SDO.
     *
     * @exception InterfaceNotImplemented The target SDO has no Configuration
     *                                    interface.
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual SDOPackage::Configuration_ptr get_configuration()
      throw (CORBA::SystemException, 
	     SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [SDO interface] Monitoring ���֥������Ȥμ��� 
     *
     * ���Υ��ڥ졼������ Monitoring interface �ؤλ��Ȥ��֤���
     * Monitoring interface �� SDO ���������륤�󥿡��ե������ΰ�ĤǤ��롣
     * ���Υ��󥿡��ե������� SDO �Υץ�ѥƥ����˥���󥰤��뤿���
     * ���Ѥ���롣
     * Monitoring interface �ξܺ٤ˤĤ��Ƥ� OMG SDO specification ��
     * 2.3.7�� "Monitoring Interface" p.2-35 �򻲾ȤΤ��ȡ�
     *
     * @return SDO �� Monitoring interface �ؤλ���
     *
     * @exception InterfaceNotImplemented SDO��Configuration���󥿡��ե�������
     *                                    �����ʤ���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [SDO interface] Get Monitoring object
     *
     * This operation returns an object implementing the Monitoring interface.
     * The Monitoring interface is one of the interfaces that each SDO
     * maintains. The interface is used to monitor the properties of an SDO.
     * See OMG SDO specification Section 2.3.7, "Monitoring Interface," on
     * page 2-35 for more details about the Monitoring interface.
     *
     * @return The Monitoring interface of an SDO.
     *
     * @exception InterfaceNotImplemented The target SDO has no Configuration
     *                                    interface.
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual SDOPackage::Monitoring_ptr get_monitoring()
      throw (CORBA::SystemException, 
	     SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [SDO interface] Organization �ꥹ�Ȥμ��� 
     *
     * SDO ��0�İʾ�� Organization (�ȿ�)�˽�°���뤳�Ȥ��Ǥ��롣 �⤷ SDO ��
     * 1�İʾ�� Organization �˽�°���Ƥ����硢���Υ��ڥ졼�����Ͻ�°����
     * Organization �Υꥹ�Ȥ��֤���SDO �� �ɤ� Organization �ˤ��°���Ƥ��ʤ�
     * ���ˤϡ����Υꥹ�Ȥ��֤���롣
     *
     * @return SDO ����°���� Organization �Υꥹ�ȡ�
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [SDO interface] Get Organization list
     *
     * An SDO belongs to zero or more organizations. If the SDO belongs to one
     * or more organizations, this operation returns the list of organizations
     * that the SDO belongs to. An empty list is returned if the SDO does not
     * belong to any Organizations.
     *
     * @return The list of Organizations that the SDO belong to.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual SDOPackage::OrganizationList* get_organizations()
      throw (CORBA::SystemException, 
	     SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [SDO interface] SDO Status �ꥹ�Ȥμ��� 
     *
     * ���Υ��ڥ졼������ SDO �Υ��ơ�������ɽ�� NVList ���֤���
     *
     * @return SDO �Υ��ơ�������
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [SDO interface] Get SDO Status list
     *
     * This operation returns an NVlist describing the status of an SDO.
     *
     * @return The actual status of an SDO.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual SDOPackage::NVList* get_status_list()
      throw (CORBA::SystemException, 
	     SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [SDO interface] SDO Status �μ��� 
     *
     * This operation returns the value of the specified status parameter.
     * 
     * @param name SDO �Υ��ơ��������������ѥ�᡼����
     * 
     * @return ���ꤵ�줿�ѥ�᡼���Υ��ơ������͡�
     * 
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InvalidParameter ���� "name" �� null ���뤤��¸�ߤ��ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [SDO interface] Get SDO Status
     *
     * @param name One of the parameters defining the "status" of an SDO.
     *
     * @return The value of the specified status parameter.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The parameter defined by "name" is null or
     *                             does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     *
     * @endif
     */
    virtual CORBA::Any* get_status(const char* name)
      throw (CORBA::SystemException, 
	     SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
    //============================================================
    // Local interfaces
    //============================================================
    /*!
     * @if jp
     *
     * @brief [local interface] ���󥹥���̾�μ���
     * 
     * ComponentProfile �����ꤵ�줿���󥹥���̾���֤���
     * 
     * @return ���󥹥���̾
     * 
     * @else
     *
     * @brief [local interface] Get instance name
     * 
     * Return the instance name that has been set in ComponentProfile.
     * 
     * @return Instance name
     * 
     * @endif
     */
    const char* getInstanceName()
    {
      RTC_TRACE(("getInstanceName()"));
      return m_profile.instance_name;
    }
    
    /*!
     * @if jp
     *
     * @brief [local interface] ���󥹥���̾������
     * 
     * ComponentProfile �˻��ꤵ�줿���󥹥���̾�����ꤹ�롣
     * 
     * @param instance_name ���󥹥���̾
     * 
     * @else
     *
     * @brief [local interface] Set instance name
     * 
     * Set the instance name specified in ComponentProfile.
     * 
     * @param instance_name Instance name
     * 
     * @endif
     */
    void setInstanceName(const char* instance_name);
    
    /*!
     * @if jp
     *
     * @brief [local interface] ��̾�μ���
     * 
     * ComponentProfile �����ꤵ�줿��̾���֤���
     * 
     * @return ��̾
     * 
     * @else
     *
     * @brief [local interface] Get type name
     * 
     * Get the type name has been set in ComponentProfile.
     * 
     * @return Type name
     * 
     * @endif
     */
    const char* getTypeName()
    {
      RTC_TRACE(("getTypeName()"));
      return m_profile.type_name;
    }
    
    /*!
     * @if jp
     *
     * @brief [local interface] Description �μ���
     * 
     * ComponentProfile �����ꤵ�줿 Description ���֤���
     * 
     * @return Description
     * 
     * @else
     *
     * @brief [local interface] GetDescription
     * 
     * Get the Description has been set in ComponentProfile.
     * 
     * @return Description
     * 
     * @endif
     */
    const char* getDescription()
    {
      RTC_TRACE(("getDescription()"));
      return m_profile.description;
    }
    
    /*!
     * @if jp
     *
     * @brief [local interface] �С���������μ���
     * 
     * ComponentProfile �����ꤵ�줿�С�����������֤���
     * 
     * @return �С���������
     * 
     * @else
     *
     * @brief [local interface] Get version information
     * 
     * Get the version information that has been set in
     * ComponentProfile.
     * 
     * @return Version information
     * 
     * @endif
     */
    const char* getVersion()
    {
      RTC_TRACE(("getVersion()"));
      return m_profile.version;
    }
    
    /*!
     * @if jp
     *
     * @brief [local interface] �٥��������μ���
     * 
     * ComponentProfile �����ꤵ�줿�٥����������֤���
     * 
     * @return �٥��������
     * 
     * @else
     *
     * @brief [local interface] Get vendor
     * 
     * Get the vendor information that has been set in ComponentProfile.
     * 
     * @return Vendor information
     * 
     * @endif
     */
    const char* getVendor()
    {
      RTC_TRACE(("getVendor()"));
      return m_profile.vendor;
    }
    
    /*!
     * @if jp
     *
     * @brief [local interface] ���ƥ������μ���
     * 
     * ComponentProfile �����ꤵ�줿���ƥ��������֤���
     * 
     * @return ���ƥ������
     * 
     * @else
     *
     * @brief [local interface] Get category information
     * 
     * Get the category information that has been set in ComponentProfile.
     * 
     * @return Category information
     * 
     * @endif
     */
    const char* getCategory()
    {
      RTC_TRACE(("getCategory()"));
      return m_profile.category;
    }
    
    /*!
     * @if jp
     *
     * @brief [local interface] Naming Server ����μ���
     * 
     * ���ꤵ�줿 Naming Server ������֤���
     * 
     * @return Naming Server �ꥹ��
     * 
     * @else
     *
     * @brief [local interface] Get Naming Server information
     * 
     * Get Naming Server information that has been set.
     * 
     * @return Naming Server list
     * 
     * @endif
     */
    std::vector<std::string> getNamingNames();
    
    /*!
     * @if jp
     *
     * @brief [local interface] ���֥������ȥ�ե���󥹤�����
     * 
     * RTC �� CORBA ���֥������ȥ�ե���󥹤����ꤹ�롣
     * 
     * @param rtobj ���֥������ȥ�ե����
     * 
     * @else
     *
     * @brief [local interface] Set the object reference
     * 
     * Set RTC's CORBA object reference.
     * 
     * @param rtobj The object reference
     * 
     * @endif
     */
    void setObjRef(const RTObject_ptr rtobj);
    
    /*!
     * @if jp
     *
     * @brief [local interface] ���֥������ȥ�ե���󥹤μ���
     * 
     * ���ꤵ�줿 CORBA ���֥������ȥ�ե���󥹤�������롣
     * 
     * @return ���֥������ȥ�ե����
     * 
     * @else
     *
     * @brief [local interface] Get the object reference
     * 
     * Get CORBA object reference that has been set
     * 
     * @return The object reference
     *
     * @endif
     */
    RTObject_ptr getObjRef() const;
    
    /*!
     * @if jp
     * 
     * @brief [local interface] RTC �Υץ�ѥƥ������ꤹ��
     *
     * RTC ���ݻ����٤��ץ�ѥƥ������ꤹ�롣Ϳ������ץ�ѥƥ��ϡ�
     * ComponentProfile �������ꤵ���٤����������ʤ���Фʤ�ʤ���
     * ���Υ��ڥ졼�������̾� RTC ������������ݤ� Manager ����
     * �ƤФ�뤳�Ȥ�տޤ��Ƥ��롣
     * 
     * @param prop RTC �Υץ�ѥƥ�
     *
     * @else
     *
     * @brief [local interface] Set RTC property
     *
     * This operation sets the properties to the RTC. The given property
     * values should include information for ComponentProfile.
     * Generally, this operation is designed to be called from Manager, when
     * RTC is initialized
     *
     * @param prop Property for RTC.
     *
     * @endif
     */
    void setProperties(const coil::Properties& prop);
    
    /*!
     * @if jp
     * 
     * @brief [local interface] RTC �Υץ�ѥƥ����������
     *
     * RTC ���ݻ����Ƥ���ץ�ѥƥ����֤���
     * RTC���ץ�ѥƥ�������ʤ����϶��Υץ�ѥƥ����֤���롣
     * 
     * @return RTC �Υץ�ѥƥ�
     *
     * @else
     *
     * @brief [local interface] Get RTC property
     *
     * This operation returns the properties of the RTC.
     * Empty property would be returned, if RTC has no property.
     *
     * @return Property for RTC.
     *
     * @endif
     */
    coil::Properties& getProperties();
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼��������
     * 
     * ����ե�����졼�����ѥ�᡼�����ѿ���Х���ɤ���
     * \<VarType\>�Ȥ��ƥ���ե�����졼�����ѥ�᡼���Υǡ���������ꤹ�롣
     *
     * @param param_name ����ե�����졼�����ѥ�᡼��̾
     * @param var ����ե�����졼�����ѥ�᡼����Ǽ���ѿ�
     * @param def_val ����ե�����졼�����ѥ�᡼���ǥե������
     * @param trans ����ե�����졼�����ѥ�᡼��ʸ�����Ѵ��Ѵؿ�
     *
     * @return ������(��������:true�����꼺��:false)
     * 
     * @else
     *
     * @brief Setup for configuration parameters
     * 
     * Bind configuration parameter to its variable.
     * Specify the data type of configuration parameter as \<VarType\>.
     *
     * @param param_name Configuration parameter name
     * @param var Variables to store configuration parameter
     * @param def_val Default value of configuration parameter
     * @param trans Function to transform configuration parameter type into 
     *        string format
     *
     * @return Setup result (Successful:true, Failed:false)
     * 
     * @endif
     */
    template <typename VarType>
    bool bindParameter(const char* param_name, VarType& var,
		       const char* def_val,
		       bool (*trans)(VarType&, const char*) = coil::stringTo)
    {
      RTC_TRACE(("bindParameter(%s (default: %s))", param_name, def_val));
      m_configsets.bindParameter(param_name, var, def_val, trans);
      return true;
    }

    /*!
     * @if jp
     *
     * @brief ����ե�����졼����󥵡��ӥ����������
     * 
     * ����ե�����졼����󥵡��ӥ����֥������Ȥ�������롣���Υ�����
     * �����֥������Ȥ����Ѥ��ơ�����ե�����졼�����ѥ�᡼�������
     * ��Ԥ����Ȥ��Ǥ��롣������Ȥ��Ƥϡ�
     *
     * - unbindParameter(): �ѥ�᡼���Υ���Х����
     * - update(): �ѥ�᡼���ι���
     * - update(set_name): ����Υ��åȤι���
     * - update(set_name, param_name): ����Υ��åȤΥѥ�᡼���ι���
     * - isExist(): �ѥ�᡼����¸�߳�ǧ
     * - isChanged(): �ѥ�᡼�����ѹ����줿���γ�ǧ
     * - changedParameters(): �ѹ��������ѥ�᡼���Υꥹ��
     * - getActiveId(): �����ƥ��֥��å�̾�μ���
     * - haveConfig(config_id): ����ե������åȤ���äƤ��뤫�ɤ���
     * - getConfigurationSets(): ������ե�����졼����󥻥åȤμ���
     * - getConfigurationSet(set_id): ���ꥻ�åȤ����
     *
     * ������Хå���Ϣ 
     * - addConfigurationParamListener(): �ꥹ�ʤ��ɲ�
     * - removeConfigurationParamListener(): �ꥹ�ʤκ��
     * - addConfigurationSetListener(): �ꥹ�ʤ��ɲ�
     * - removeConfigurationSetListener(): �ꥹ�ʤκ��
     * - addConfigurationSetNameListener(): �ꥹ�ʤ��ɲ�
     * - removeConfigurationSetNameListener(): �ꥹ�ʤκ��
     *
     * �ܺ٤�ConfigAdmin���饹��ե���󥹤򻲾ȤΤ��ȡ�
     *
     * @return ConfigAdmin object
     * 
     * @else
     *
     * @brief Getting configuration service
     * 
     * This operation returns configuration service object. By using
     * this service, user can manipulate configuration
     * parameters. Mainly the following operations are supported.
     *
     * - unbindParameter(): Unbinding parameters
     * - update(): Updateing parameters
     * - update(set_name): Updating a specific configuration set
     * - update(set_name, param_name): Updating specific parameter in a set
     * - isExist(): Checking existence of a parameter
     * - isChanged(): Check if a parameter was updated
     * - changedParameters(): Getting changed parameter list
     * - getActiveId(): Getting active configuration set name
     * - haveConfig(config_id): Checking if having a specified configuration set
     * - getConfigurationSets(): getting all the configuration sets
     * - getConfigurationSet(set_id): Getting a configuration set
     *
     * Callback related member functions
     * - addConfigurationParamListener(): Adding listener
     * - removeConfigurationParamListener(): Removing listener
     * - addConfigurationSetListener(): Adding listener
     * - removeConfigurationSetListener(): Removing listener
     * - addConfigurationSetNameListener(): Adding listener
     * - removeConfigurationSetNameListener(): Removing listener
     *
     * See details in the ConfigAdmin class reference
     *
     * @return ConfigAdmin object
     *
     * @endif
     */
    ConfigAdmin& getConfigService() { return m_configsets; }
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�����ѥ�᡼���ι���(ID����)
     * 
     * ���ꤷ��ID�Υ���ե�����졼����󥻥åȤ����ꤷ���ͤǡ�
     * ����ե�����졼�����ѥ�᡼�����ͤ򹹿�����
     *
     * @param config_set �����оݤΥ���ե�����졼����󥻥å�ID
     * 
     * @else
     *
     * @brief Update configuration parameters (by ID)
     * 
     * Update configuration parameter value by the value that 
     * set to a configuration set of specified ID.
     *
     * @param config_set The target configuration set's ID for setup
     * 
     * @endif
     */
    void updateParameters(const char* config_set);
    
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ����
     *
     * RTC ���ݻ�����Port����Ͽ���롣
     * Port �������饢��������ǽ�ˤ��뤿��ˤϡ����Υ��ڥ졼�����ˤ��
     * ��Ͽ����Ƥ��ʤ���Фʤ�ʤ�����Ͽ����� Port �Ϥ��� RTC �����ˤ�����
     * PortProfile.name �ˤ����̤���롣�������äơ�Port �� RTC ��ˤ����ơ�
     * ��ˡ����� PortProfile.name ������ʤ���Фʤ�ʤ���
     * ��Ͽ���줿 Port ��������Ŭ�ڤ˥����ƥ��ֲ����줿�塢���λ��Ȥ�
     * ���֥������Ȼ��Ȥ��ꥹ�������¸����롣
     * 
     * @param port RTC ����Ͽ���� Port
     * @return ��Ͽ���(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     *
     * @brief [local interface] Register Port
     *
     * This operation registers a Port held by this RTC.
     * In order to enable access to the Port from outside of RTC, the Port
     * must be registered by this operation. The Port that is registered by
     * this operation would be identified by PortProfile.name in the inside of
     * RTC. Therefore, the Port should have unique PortProfile.name in the RTC.
     * The registering Port would be activated properly, and the reference
     * and the object reference would be stored in lists in RTC.
     *
     * @param port Port which is registered to the RTC
     * @return Register result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool addPort(PortBase& port);
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ����
     *
     * RTC ���ݻ�����Port����Ͽ���롣
     * Port �������饢��������ǽ�ˤ��뤿��ˤϡ����Υ��ڥ졼�����ˤ��
     * ��Ͽ����Ƥ��ʤ���Фʤ�ʤ�����Ͽ����� Port �Ϥ��� RTC �����ˤ�����
     * PortProfile.name �ˤ����̤���롣�������äơ�Port �� RTC ��ˤ����ơ�
     * ��ˡ����� PortProfile.name ������ʤ���Фʤ�ʤ���
     * ��Ͽ���줿 Port ��������Ŭ�ڤ˥����ƥ��ֲ����줿�塢���λ��Ȥ�
     * ���֥������Ȼ��Ȥ��ꥹ�������¸����롣
     * 
     * @param port RTC ����Ͽ���� Port
     * @return ��Ͽ���(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     *
     * @brief [local interface] Register Port
     *
     * This operation registers a Port held by this RTC.
     * In order to enable access to the Port from outside of RTC, the Port
     * must be registered by this operation. The Port that is registered by
     * this operation would be identified by PortProfile.name in the inside of
     * RTC. Therefore, the Port should have unique PortProfile.name in the RTC.
     * The registering Port would be activated properly, and the reference
     * and the object reference would be stored in lists in RTC.
     *
     * @param port Port which is registered to the RTC
     * @return Register result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool addPort(PortService_ptr port);
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ����
     *
     * RTC ���ݻ�����Port����Ͽ���롣
     * Port �������饢��������ǽ�ˤ��뤿��ˤϡ����Υ��ڥ졼�����ˤ��
     * ��Ͽ����Ƥ��ʤ���Фʤ�ʤ�����Ͽ����� Port �Ϥ��� RTC �����ˤ�����
     * PortProfile.name �ˤ����̤���롣�������äơ�Port �� RTC ��ˤ����ơ�
     * ��ˡ����� PortProfile.name ������ʤ���Фʤ�ʤ���
     * ��Ͽ���줿 Port ��������Ŭ�ڤ˥����ƥ��ֲ����줿�塢���λ��Ȥ�
     * ���֥������Ȼ��Ȥ��ꥹ�������¸����롣
     * 
     * @param port RTC ����Ͽ���� Port
     * @return ��Ͽ���(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     *
     * @brief [local interface] Register Port
     *
     * This operation registers a Port held by this RTC.
     * In order to enable access to the Port from outside of RTC, the Port
     * must be registered by this operation. The Port that is registered by
     * this operation would be identified by PortProfile.name in the inside of
     * RTC. Therefore, the Port should have unique PortProfile.name in the RTC.
     * The registering Port would be activated properly, and the reference
     * and the object reference would be stored in lists in RTC.
     *
     * @param port Port which is registered to the RTC
     * @return Register result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool addPort(CorbaPort& port);
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ����
     *
     * RTC ���ݻ�����Port����Ͽ���롣
     * Port �������饢��������ǽ�ˤ��뤿��ˤϡ����Υ��ڥ졼�����ˤ��
     * ��Ͽ����Ƥ��ʤ���Фʤ�ʤ�����Ͽ����� Port �Ϥ��� RTC �����ˤ�����
     * PortProfile.name �ˤ����̤���롣�������äơ�Port �� RTC ��ˤ����ơ�
     * ��ˡ����� PortProfile.name ������ʤ���Фʤ�ʤ���
     * ��Ͽ���줿 Port ��������Ŭ�ڤ˥����ƥ��ֲ����줿�塢���λ��Ȥ�
     * ���֥������Ȼ��Ȥ��ꥹ�������¸����롣
     * 
     * @param port RTC ����Ͽ���� Port
     *
     * @else
     *
     * @brief [local interface] Register Port
     *
     * This operation registers a Port held by this RTC.
     * In order to enable access to the Port from outside of RTC, the Port
     * must be registered by this operation. The Port that is registered by
     * this operation would be identified by PortProfile.name in the inside of
     * RTC. Therefore, the Port should have unique PortProfile.name in the RTC.
     * The registering Port would be activated properly, and the reference
     * and the object reference would be stored in lists in RTC.
     *
     * @param port Port which is registered to the RTC
     *
     * @endif
     */
    void registerPort(PortBase& port);
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ����
     *
     * RTC ���ݻ�����Port����Ͽ���롣
     * Port �������饢��������ǽ�ˤ��뤿��ˤϡ����Υ��ڥ졼�����ˤ��
     * ��Ͽ����Ƥ��ʤ���Фʤ�ʤ�����Ͽ����� Port �Ϥ��� RTC �����ˤ�����
     * PortProfile.name �ˤ����̤���롣�������äơ�Port �� RTC ��ˤ����ơ�
     * ��ˡ����� PortProfile.name ������ʤ���Фʤ�ʤ���
     * ��Ͽ���줿 Port ��������Ŭ�ڤ˥����ƥ��ֲ����줿�塢���λ��Ȥ�
     * ���֥������Ȼ��Ȥ��ꥹ�������¸����롣
     * 
     * @param port RTC ����Ͽ���� Port
     *
     * @else
     *
     * @brief [local interface] Register Port
     *
     * This operation registers a Port held by this RTC.
     * In order to enable access to the Port from outside of RTC, the Port
     * must be registered by this operation. The Port that is registered by
     * this operation would be identified by PortProfile.name in the inside of
     * RTC. Therefore, the Port should have unique PortProfile.name in the RTC.
     * The registering Port would be activated properly, and the reference
     * and the object reference would be stored in lists in RTC.
     *
     * @param port Port which is registered to the RTC
     *
     * @endif
     */
    void registerPort(PortService_ptr port);
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ����
     *
     * RTC ���ݻ�����Port����Ͽ���롣
     * Port �������饢��������ǽ�ˤ��뤿��ˤϡ����Υ��ڥ졼�����ˤ��
     * ��Ͽ����Ƥ��ʤ���Фʤ�ʤ�����Ͽ����� Port �Ϥ��� RTC �����ˤ�����
     * PortProfile.name �ˤ����̤���롣�������äơ�Port �� RTC ��ˤ����ơ�
     * ��ˡ����� PortProfile.name ������ʤ���Фʤ�ʤ���
     * ��Ͽ���줿 Port ��������Ŭ�ڤ˥����ƥ��ֲ����줿�塢���λ��Ȥ�
     * ���֥������Ȼ��Ȥ��ꥹ�������¸����롣
     * 
     * @param port RTC ����Ͽ���� Port
     *
     * @else
     *
     * @brief [local interface] Register Port
     *
     * This operation registers a Port held by this RTC.
     * In order to enable access to the Port from outside of RTC, the Port
     * must be registered by this operation. The Port that is registered by
     * this operation would be identified by PortProfile.name in the inside of
     * RTC. Therefore, the Port should have unique PortProfile.name in the RTC.
     * The registering Port would be activated properly, and the reference
     * and the object reference would be stored in lists in RTC.
     *
     * @param port Port which is registered to the RTC
     *
     * @endif
     */
    void registerPort(CorbaPort& port);

    /*!
     * @if jp
     * 
     * @brief [local interface] DataInPort ����Ͽ����
     *
     * RTC ���ݻ����� DataInPort ����Ͽ���롣
     * Port �Υץ�ѥƥ��˥ǡ����ݡ��ȤǤ��뤳��("port.dataport")��
     * TCP����Ѥ��뤳��("tcp_any")�����ꤹ��ȤȤ�ˡ� DataInPort ��
     * ���󥹥��󥹤�����������Ͽ���롣
     * 
     * @param name port ̾��
     * @param inport ��Ͽ�о� DataInPort
     * @return ��Ͽ���(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     * 
     * @brief [local interface] Register DataInPort
     *
     * This operation registers DataInPort held by this RTC.
     * Set "port.dataport" and "tcp_any" to property of Port, and
     * create instances of DataInPort and register it.
     * 
     * @param name Port name
     * @param inport DataInPort which is registered to the RTC
     * @return Register result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool addInPort(const char* name, InPortBase& inport);
    /*!
     * @if jp
     * 
     * @brief [local interface] DataInPort ����Ͽ����
     *
     * RTC ���ݻ����� DataInPort ����Ͽ���롣
     * Port �Υץ�ѥƥ��˥ǡ����ݡ��ȤǤ��뤳��("port.dataport")��
     * TCP����Ѥ��뤳��("tcp_any")�����ꤹ��ȤȤ�ˡ� DataInPort ��
     * ���󥹥��󥹤�����������Ͽ���롣
     * 
     * @param name port ̾��
     * @param inport ��Ͽ�о� DataInPort
     *
     * @else
     * 
     * @brief [local interface] Register DataInPort
     *
     * This operation registers DataInPort held by this RTC.
     * Set "port.dataport" and "tcp_any" to property of Port, and
     * create instances of DataInPort and register it.
     * 
     * @param name Port name
     * @param inport DataInPort which is registered to the RTC
     *
     * @endif
     */
    void registerInPort(const char* name, InPortBase& inport);
    
    /*!
     * @if jp
     * 
     * @brief [local interface] DataOutPort ����Ͽ����
     *
     * RTC ���ݻ����� DataOutPort����Ͽ���롣
     * Port �Υץ�ѥƥ��˥ǡ����ݡ��ȤǤ��뤳��("port.dataport")��
     * TCP����Ѥ��뤳��("tcp_any")�����ꤹ��ȤȤ�ˡ� DataOutPort ��
     * ���󥹥��󥹤�����������Ͽ���롣
     * 
     * @param name port ̾��
     * @param outport ��Ͽ�о� DataOutPort
     * @return ��Ͽ���(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     * 
     * @brief [local interface] Register DataOutPort
     *
     * This operation registers DataOutPor held by this RTC.
     * Set "port.dataport" and "tcp_any" to property of Port, and then
     * create instances of DataOutPort and register it.
     * 
     * @param name Port name
     * @param outport DataOutPort which is registered to the RTC
     * @return Register result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool addOutPort(const char* name, OutPortBase& outport);
    /*!
     * @if jp
     * 
     * @brief [local interface] DataOutPort ����Ͽ����
     *
     * RTC ���ݻ����� DataOutPort����Ͽ���롣
     * Port �Υץ�ѥƥ��˥ǡ����ݡ��ȤǤ��뤳��("port.dataport")��
     * TCP����Ѥ��뤳��("tcp_any")�����ꤹ��ȤȤ�ˡ� DataOutPort ��
     * ���󥹥��󥹤�����������Ͽ���롣
     * 
     * @param name port ̾��
     * @param outport ��Ͽ�о� DataOutPort
     *
     * @else
     * 
     * @brief [local interface] Register DataOutPort
     *
     * This operation registers DataOutPor held by this RTC.
     * Set "port.dataport" and "tcp_any" to property of Port, and then
     * create instances of DataOutPort and register it.
     * 
     * @param name Port name
     * @param outport DataOutPort which is registered to the RTC
     *
     * @endif
     */
    void registerOutPort(const char* name, OutPortBase& outport);
    
    /*!
     * @if jp
     * 
     * @brief [local interface] InPort ����Ͽ��������
     *
     * RTC ���ݻ�����InPort����Ͽ�������롣
     * 
     * @param port ����о� Port
     * @return ������(�������:true���������:false)
     *
     * @else
     *
     * @brief [local interface] Unregister InPort
     *
     * This operation unregisters a InPort held by this RTC.
     *
     * @param port Port which is unregistered
     * @return Unregister result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool removeInPort(InPortBase& port);

    /*!
     * @if jp
     * 
     * @brief [local interface] OutPort ����Ͽ��������
     *
     * RTC ���ݻ�����OutPort����Ͽ�������롣
     * 
     * @param port ����о� Port
     * @return ������(�������:true���������:false)
     *
     * @else
     *
     * @brief [local interface] Unregister OutPort
     *
     * This operation unregisters a OutPort held by this RTC.
     *
     * @param port Port which is unregistered
     * @return Unregister result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool removeOutPort(OutPortBase& port);

    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ��������
     *
     * RTC ���ݻ�����Port����Ͽ�������롣
     * 
     * @param port ����о� Port
     * @return ������(�������:true���������:false)
     *
     * @else
     *
     * @brief [local interface] Unregister Port
     *
     * This operation unregisters a Port held by this RTC.
     *
     * @param port Port which is unregistered
     * @return Unregister result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool removePort(PortBase& port);
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ��������
     *
     * RTC ���ݻ�����Port����Ͽ�������롣
     * 
     * @param port ����о� Port
     * @return ������(�������:true���������:false)
     *
     * @else
     *
     * @brief [local interface] Unregister Port
     *
     * This operation unregisters a Port held by this RTC.
     *
     * @param port Port which is unregistered
     * @return Unregister result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool removePort(PortService_ptr port);
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ��������
     *
     * RTC ���ݻ�����Port����Ͽ�������롣
     * 
     * @param port ����о� Port
     * @return ������(�������:true���������:false)
     *
     * @else
     *
     * @brief [local interface] Unregister Port
     *
     * This operation unregisters a Port held by this RTC.
     *
     * @param port Port which is unregistered
     * @return Unregister result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool removePort(CorbaPort& port);
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ��������
     *
     * RTC ���ݻ�����Port����Ͽ�������롣
     * 
     * @param port ����о� Port
     *
     * @else
     *
     * @brief [local interface] Unregister Port
     *
     * This operation unregisters a Port held by this RTC.
     *
     * @param port Port which is unregistered
     *
     * @endif
     */
    void deletePort(PortBase& port);
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ��������
     *
     * RTC ���ݻ�����Port����Ͽ�������롣
     * 
     * @param port ����о� Port
     *
     * @else
     *
     * @brief [local interface] Unregister Port
     *
     * This operation unregisters a Port held by this RTC.
     *
     * @param port Port which is unregistered
     *
     * @endif
     */
    void deletePort(PortService_ptr port);
    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ��������
     *
     * RTC ���ݻ�����Port����Ͽ�������롣
     * 
     * @param port ����о� Port
     *
     * @else
     *
     * @brief [local interface] Unregister Port
     *
     * This operation unregisters a Port held by this RTC.
     *
     * @param port Port which is unregistered
     *
     * @endif
     */
    void deletePort(CorbaPort& port);
    
    /*!
     * @if jp
     * 
     * @brief [local interface] ̾������ˤ�� Port ����Ͽ��������
     *
     * ̾�Τ���ꤷ�� RTC ���ݻ�����Port����Ͽ�������롣
     * 
     * @param port_name ����о� Port ̾
     *
     * @else
     * 
     * @brief [local interface] Delete Port by specifying its name
     *
     * Delete Port which RTC has by specifying its name.
     * 
     * @param port_name Name of Port which is deleted
     *
     * @endif
     */
    void deletePortByName(const char* port_name);
    
    /*!
     * @if jp
     * 
     * @brief [local interface] �¹ԥ���ƥ����Ȥ��������
     *
     * get_context() ��Ʊ����ǽ�Υ������ǡ��㤤�Ϥʤ���
     * ���δؿ��ϰʲ��δؿ���ǸƤФ�뤳�Ȥ�����Ȥ��Ƥ��롣
     *
     * - onStartup()
     * - onShutdown()
     * - onActivated()
     * - onDeactivated()
     * - onExecute()
     * - onAborting()
     * - onError()
     * - onReset()
     * - onStateUpdate()
     * - onRateChanged()
     *
     * ���δؿ��ΰ����Ϥ����δؿ��ΰ��� UniquieID exec_handle �Ǥʤ�
     * ��Фʤ�ʤ���
     *
     * @param ec_id �嵭�ؿ�����1���� exec_handle ���Ϥ�ɬ�פ����롣
     *
     * @else
     * 
     * @brief [local interface] Getting current execution context
     *
     * This function is the local version of get_context(). completely
     * same as get_context() function. This function is assumed to be
     * called from the following functions.
     *
     * - onStartup()
     * - onShutdown()
     * - onActivated()
     * - onDeactivated()
     * - onExecute()
     * - onAborting()
     * - onError()
     * - onReset()
     * - onStateUpdate()
     * - onRateChanged()
     *
     * The argument of this function should be the first argument
     * (UniqueId ec_id) of the above functions.
     *
     * @param ec_id The above functions' first argument "exec_handle."
     *
     * @endif
     */
    ExecutionContext_ptr getExecutionContext(RTC::UniqueId ec_id);

    /*!
     * @if jp
     * 
     * @brief [local interface] �¹ԥ���ƥ����Ȥμ¹ԥ졼�Ȥ��������
     *
     * ���߼¹���μ¹ԥ���ƥ����Ȥμ¹ԥ졼�Ȥ�������롣�¹ԥ���ƥ�
     * ���Ȥ�Kind��PERIODIC�ʳ��ξ���ư���̤����Ǥ��롣���δؿ��ϰ�
     * ���δؿ���ǸƤФ�뤳�Ȥ�����Ȥ��Ƥ��롣
     *
     * - onStartup()
     * - onShutdown()
     * - onActivated()
     * - onDeactivated()
     * - onExecute()
     * - onAborting()
     * - onError()
     * - onReset()
     * - onStateUpdate()
     * - onRateChanged()
     *
     * ���δؿ��ΰ����Ϥ����δؿ��ΰ��� UniquieID exec_handle �Ǥʤ�
     * ��Фʤ�ʤ���
     *
     * @param ec_id �嵭�ؿ�����1���� exec_handle ���Ϥ�ɬ�פ����롣
     *
     * @else
     * 
     * @brief [local interface] Getting current context' execution rate
     *
     * This function returns current execution rate in this
     * context. If this context's kind is not PERIODC, behavior is not
     * defined. This function is assumed to be called from the
     * following functions.
     *
     * - onStartup()
     * - onShutdown()
     * - onActivated()
     * - onDeactivated()
     * - onExecute()
     * - onAborting()
     * - onError()
     * - onReset()
     * - onStateUpdate()
     * - onRateChanged()
     *
     * The argument of this function should be the first argument
     * (UniqueId ec_id) of the above functions.
     *
     * @param ec_id The above functions' first argument "exec_handle."
     *
     * @endif
     */
    double getExecutionRate(RTC::UniqueId ec_id);

    /*!
     * @if jp
     * 
     * @brief [local interface] �¹ԥ���ƥ����Ȥμ¹ԥ졼�Ȥ����ꤹ��
     *
     * ���߼¹���μ¹ԥ���ƥ����Ȥμ¹ԥ졼�Ȥ����ꤹ�롣�¹ԥ���ƥ�
     * ���Ȥ�Kind��PERIODIC�ʳ��ξ���ư���̤����Ǥ��롣���δؿ��ϰ�
     * ���δؿ���ǸƤФ�뤳�Ȥ�����Ȥ��Ƥ��롣
     *
     * - onStartup()
     * - onShutdown()
     * - onActivated()
     * - onDeactivated()
     * - onExecute()
     * - onAborting()
     * - onError()
     * - onReset()
     * - onStateUpdate()
     * - onRateChanged()
     *
     * ���δؿ��ΰ����Ϥ����δؿ��ΰ��� UniquieID exec_handle �Ǥʤ�
     * ��Фʤ�ʤ���
     *
     * @param ec_id �嵭�ؿ�����1���� exec_handle ���Ϥ�ɬ�פ����롣
     * @param rate �¹ԥ졼�Ȥ� [Hz] ��Ϳ����
     *
     * @else
     * 
     * @brief [local interface] Setting current context' execution rate
     *
     * This function sets a execution rate in the context. If this
     * context's kind is not PERIODC, behavior is not defined. This
     * function is assumed to be called from the following functions.
     *
     * - onStartup()
     * - onShutdown()
     * - onActivated()
     * - onDeactivated()
     * - onExecute()
     * - onAborting()
     * - onError()
     * - onReset()
     * - onStateUpdate()
     * - onRateChanged()
     *
     * The argument of this function should be the first argument
     * (UniqueId ec_id) of the above functions.
     *
     * @param ec_id The above functions' first argument "exec_handle."
     * @param rate Execution rate in [Hz].
     *
     * @endif
     */
    ReturnCode_t setExecutionRate(RTC::UniqueId ec_id, double rate);

    /*!
     * @if jp
     * 
     * @brief [local interface] �¹ԥ���ƥ����Ȥν�ͭ����Ĵ�٤�
     *
     * ���߼¹���μ¹ԥ���ƥ����Ȥν�ͭ����Ĵ�٤롣���δؿ��ϰʲ��δ�
     * ����ǸƤФ�뤳�Ȥ�����Ȥ��Ƥ��롣
     *
     * - onStartup()
     * - onShutdown()
     * - onActivated()
     * - onDeactivated()
     * - onExecute()
     * - onAborting()
     * - onError()
     * - onReset()
     * - onStateUpdate()
     * - onRateChanged()
     *
     * ���δؿ��ΰ����Ϥ����δؿ��ΰ��� UniquieID exec_handle �Ǥʤ�
     * ��Фʤ�ʤ���
     *
     * @param ec_id �嵭�ؿ�����1���� exec_handle ���Ϥ�ɬ�פ����롣
     * @return true: ���Ȥμ¹ԥ���ƥ����ȡ�false: ¾�μ¹ԥ���ƥ�����
     *
     * @else
     * 
     * @brief [local interface] Checking if the current context is own context
     *
     * This function checks if the current context is own execution
     * context. This function is assumed to be called from the
     * following functions.
     *
     * - onStartup()
     * - onShutdown()
     * - onActivated()
     * - onDeactivated()
     * - onExecute()
     * - onAborting()
     * - onError()
     * - onReset()
     * - onStateUpdate()
     * - onRateChanged()
     *
     * The argument of this function should be the first argument
     * (UniqueId ec_id) of the above functions.
     *
     * @param ec_id The above functions' first argument "exec_handle."
     * @return true: Own context, false: other's context
     *
     * @endif
     */
    bool isOwnExecutionContext(RTC::UniqueId ec_id);

    /*!
     * @if jp
     * 
     * @brief [local interface] ���֤� Inactive �����ܤ�����
     *
     * ���֤� Active ���� Inactive �����ܤ����롣���δؿ��ϰʲ��δ�
     * ����ǸƤФ�뤳�Ȥ�����Ȥ��Ƥ��롣
     *
     * - onActivated()
     * - onExecute()
     * - onStateUpdate()
     *
     * ���δؿ��ΰ����Ͼ嵭�δؿ��ΰ��� UniquieID exec_handle �Ǥʤ�
     * ��Фʤ�ʤ���
     *
     * @param ec_id �嵭�ؿ�����1���� exec_handle ���Ϥ�ɬ�פ����롣
     * @return �꥿���󥳡���
     *
     * @else
     * 
     * @brief [local interface] Make transition to Inactive state
     *
     * This function makes transition from Active to Inactive
     * state. This function is assumed to be called from the following
     * functions.
     *
     * - onActivated()
     * - onExecute()
     * - onStateUpdate()
     *
     * The argument of this function should be the first argument
     * (UniqueId ec_id) of the above function.
     *
     * @param ec_id The above functions' first argument "exec_handle."
     * @return Return code
     *
     * @endif
     */
    ReturnCode_t deactivate(RTC::UniqueId ec_id);

    /*!
     * @if jp
     * 
     * @brief [local interface] ���֤� Active �����ܤ�����
     *
     * ���֤� Inactive ���� Active �����ܤ����롣���δؿ��ϰʲ��δ�
     * ����ǸƤФ�뤳�Ȥ�����Ȥ��Ƥ��롣
     *
     * - onStartup()
     * - onDeactivated()
     *
     * ���δؿ��ΰ����Ͼ嵭�δؿ��ΰ��� UniquieID exec_handle �Ǥʤ�
     * ��Фʤ�ʤ���
     *
     * @param ec_id �嵭�ؿ�����1���� exec_handle ���Ϥ�ɬ�פ����롣
     * @return �꥿���󥳡���
     *
     * @else
     * 
     * @brief [local interface] Make transition to Active state
     *
     * This function makes transition from Inactive to Active
     * state. This function is assumed to be called from the following
     * functions.
     *
     * - onStartup()
     * - onDeactivated()
     *
     * The argument of this function should be the first argument
     * (UniqueId ec_id) of the above function.
     *
     * @param ec_id The above functions' first argument "exec_handle."
     * @return Return code
     *
     * @endif
     */
    ReturnCode_t activate(RTC::UniqueId ec_id);

    /*!
     * @if jp
     * 
     * @brief [local interface] ���֤�ꥻ�åȤ� Inactive �����ܤ�����
     *
     * ���֤� Error ���� Inactive �����ܤ����롣���δؿ��ϰʲ��δ�
     * ����ǸƤФ�뤳�Ȥ�����Ȥ��Ƥ��롣
     *
     * - onError()
     *
     * ���δؿ��ΰ����Ͼ嵭�δؿ��ΰ��� UniquieID exec_handle �Ǥʤ�
     * ��Фʤ�ʤ���
     *
     * @param ec_id �嵭�ؿ�����1���� exec_handle ���Ϥ�ɬ�פ����롣
     * @return �꥿���󥳡���
     *
     * @else
     * 
     * @brief [local interface] Resetting and go to Inactive state
     *
     * This function reset RTC and makes transition from Error to Inactive
     * state. This function is assumed to be called from the following
     * functions.
     *
     * - onError()
     *
     * The argument of this function should be the first argument
     * (UniqueId ec_id) of the above function.
     *
     * @param ec_id The above functions' first argument "exec_handle."
     * @return Return code
     *
     * @endif
     */
    ReturnCode_t reset(RTC::UniqueId ec_id);

    /*!
     * @if jp
     * @brief [local interface] SDO service provider �򥻥åȤ���
     * @else
     * @brief [local interface] Set a SDO service provider
     * @endif
     */
    bool addSdoServiceProvider(const SDOPackage::ServiceProfile& prof,
                               SdoServiceProviderBase* provider);

    /*!
     * @if jp
     * @brief [local interface] SDO service provider ��������
     * @else
     * @brief [local interface] Remove a SDO service provider
     * @endif
     */
    bool removeSdoServiceProvider(const char* id);

    /*!
     * @if jp
     * @brief [local interface] SDO service provider �򥻥åȤ���
     * @else
     * @brief [local interface] Set a SDO service provider
     * @endif
     */
    bool addSdoServiceConsumer(const SDOPackage::ServiceProfile& prof);

    /*!
     * @if jp
     * @brief [local interface] SDO service provider ��������
     * @else
     * @brief [local interface] Remove a SDO service provider
     * @endif
     */
    bool removeSdoServiceConsumer(const char* id);

    /*!
     * @if jp
     *
     * @brief �� InPort �Υǡ������ɤ߹��ࡣ
     *
     * RTC ���ݻ��������Ƥ� InPort �Υǡ������ɤ߹��ࡣ
     *
     * @return �ɤ߹��߷��(���ݡ��Ȥ��ɤ߹�������:true������:false)
     *
     * @else
     *
     * @brief Readout the value from All InPorts.
     *
     * This operation read the value from all InPort
     * registered in the RTC.
     *
     * @return result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool readAll();

    /*!
     * @if jp
     *
     * @brief �� OutPort ��write()�᥽�åɤ򥳡��뤹�롣
     *
     * RTC ���ݻ��������Ƥ� OutPort ��write()�᥽�åɤ򥳡��뤹�롣
     *
     * @return �ɤ߹��߷��(���ݡ��Ȥؤν񤭹�������:true������:false)
     *
     * @else
     *
     * @brief The write() method of all OutPort is called. 
     *
     * This operation call the write() method of all OutPort
     * registered in the RTC.
     *
     * @return result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool writeAll();

    /*!
     * @if jp
     *
     * @brief onExecute()�¹����Ǥ�readAll()�᥽�åɤθƽФ�ͭ���ޤ���̵���ˤ��롣
     *
     * ���Υ᥽�åɤ�ѥ�᡼����true�Ȥ��ƸƤֻ��ˤ�ꡢonExecute()�¹�����
     * readAll()���ƽФ����褦�ˤʤ롣
     * �ѥ�᡼����false�ξ��ϡ�readAll()�ƽФ�̵���ˤ��롣
     *
     * @param read(default:true) 
     *        (readAll()�᥽�åɸƽФ���:true, readAll()�᥽�åɸƽФʤ�:false)
     *
     * @param completion(default:false) 
     *    readAll()�ˤơ��ɤ줫�ΰ�Ĥ�InPort��read()�����Ԥ��Ƥ����Ƥ�
     *    InPort��read()��ƤӽФ�:true, readAll()�ˤơ��ɤ줫�ΰ�Ĥ�
     *    InPort��read()�����Ԥ�����硢������false��ȴ����:false
     *
     * @else
     *
     * @brief Set whether to execute the readAll() method. 
     *
     * Set whether to execute the readAll() method. 
     *
     * @param read(default:true)
     *        (readAll() is called:true, readAll() isn't called:false)
     *
     * @param completion(default:false)
     *     All InPort::read() calls are completed.:true,
     *     If one InPort::read() is False, return false.:false
     *
     * @param completion(default:false)
     *
     * @endif
     */
    void setReadAll(bool read=true, bool completion=false);

    /*!
     * @if jp
     *
     * @brief onExecute()�¹Ը��writeAll()�᥽�åɤθƽФ�ͭ���ޤ���̵���ˤ��롣
     *
     * ���Υ᥽�åɤ�ѥ�᡼����true�Ȥ��ƸƤֻ��ˤ�ꡢonExecute()�¹Ը��
     * writeAll()���ƽФ����褦�ˤʤ롣
     * �ѥ�᡼����false�ξ��ϡ�writeAll()�ƽФ�̵���ˤ��롣
     *
     * @param write(default:true) 
     *        (writeAll()�᥽�åɸƽФ���:true, writeAll()�᥽�åɸƽ�
     *        �ʤ�:false)
     *
     * @param completion(default:false) 
     *    writeAll()�ˤơ��ɤ줫�ΰ�Ĥ�OutPort��write()�����Ԥ��Ƥ���
     *    �Ƥ�OutPort��write()��ƤӽФ���Ԥ�:true, writeAll()�ˤơ���
     *    �줫�ΰ�Ĥ�OutPort��write()�����Ԥ�����硢������false��ȴ��
     *    ��:false
     *
     * @else
     *
     * @brief Set whether to execute the writeAll() method. 
     *
     * Set whether to execute the writeAll() method. 
     *
     * @param write(default:true)
     *        (writeAll() is called:true, writeAll() isn't called:false)
     *
     * @param completion(default:false)
     *     All OutPort::write() calls are completed.:true,
     *     If one OutPort::write() is False, return false.:false
     *
     * @endif
     */
    void setWriteAll(bool write=true, bool completion=false);


    /*!
     * @if jp
     *
     * @brief �� Port ����Ͽ��������
     *
     * RTC ���ݻ��������Ƥ� Port �������롣
     *
     * @else
     *
     * @brief Unregister All Ports
     *
     * This operation deactivates the all Ports and deletes the all Port's
     * registrations in the RTC
     *
     * @endif
     */
    void finalizePorts();


    /*!
     * @if jp
     *
     * @brief ExecutionContextBase�ꥹ�Ȥ���Ͽ�������� 
     *
     * @else
     *
     * @brief The ExecutionContextBase list is deleted. 
     *
     * @endif
     */
    void finalizeContexts();


    /*!
     * @if jp
     * @brief PreComponentActionListener �ꥹ�ʤ��ɲä���
     *
     * ComponentAction �����ؿ��θƤӽФ�ľ���Υ��٥�Ȥ˴�Ϣ����Ƽ��
     * ���ʤ����ꤹ�롣
     *
     * ����Ǥ���ꥹ�ʤΥ����פȥ�����Хå����٥�Ȥϰʲ����̤�
     *
     * - PRE_ON_INITIALIZE:    onInitialize ľ��
     * - PRE_ON_FINALIZE:      onFinalize ľ��
     * - PRE_ON_STARTUP:       onStartup ľ��
     * - PRE_ON_SHUTDOWN:      onShutdown ľ��
     * - PRE_ON_ACTIVATED:     onActivated ľ��
     * - PRE_ON_DEACTIVATED:   onDeactivated ľ��
     * - PRE_ON_ABORTED:       onAborted ľ��
     * - PRE_ON_ERROR:         onError ľ��
     * - PRE_ON_RESET:         onReset ľ��
     * - PRE_ON_EXECUTE:       onExecute ľ��
     * - PRE_ON_STATE_UPDATE:  onStateUpdate ľ��
     *
     * �ꥹ�ʤ� PreComponentActionListener ��Ѿ������ʲ��Υ����˥�������
     * operator() ��������Ƥ���ɬ�פ����롣
     *
     * PreComponentActionListener::operator()(UniqueId ec_id)
     *
     * �ǥե���ȤǤϡ����δؿ���Ϳ�����ꥹ�ʥ��֥������Ȥν�ͭ����
     * RTObject�˰ܤꡢRTObject���λ��⤷���ϡ�
     * removePreComponentActionListener() �ˤ�������˼�ưŪ�˲��Τ���롣
     * �ꥹ�ʥ��֥������Ȥν�ͭ����ƤӽФ�¦�ǰݻ����������ϡ���3��
     * ���� false ����ꤷ����ưŪ�ʲ��Τ��������뤳�Ȥ��Ǥ��롣
     *
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     * @param autoclean �ꥹ�ʥ��֥������Ȥμ�ưŪ���Τ�Ԥ����ɤ����Υե饰
     *
     * @else
     * @brief Adding PreComponentAction type listener
     *
     * This operation adds certain listeners related to ComponentActions
     * pre events.
     * The following listener types are available.
     *
     * - PRE_ON_INITIALIZE:    before onInitialize
     * - PRE_ON_FINALIZE:      before onFinalize
     * - PRE_ON_STARTUP:       before onStartup
     * - PRE_ON_SHUTDOWN:      before onShutdown
     * - PRE_ON_ACTIVATED:     before onActivated
     * - PRE_ON_DEACTIVATED:   before onDeactivated
     * - PRE_ON_ABORTED:       before onAborted
     * - PRE_ON_ERROR:         before onError
     * - PRE_ON_RESET:         before onReset
     * - PRE_ON_EXECUTE:       before onExecute
     * - PRE_ON_STATE_UPDATE:  before onStateUpdate
     *
     * Listeners should have the following function operator().
     *
     * PreComponentActionListener::operator()(UniqueId ec_id)
     *
     * The ownership of the given listener object is transferred to
     * this RTObject object in default.  The given listener object will
     * be destroied automatically in the RTObject's dtor or if the
     * listener is deleted by removePreComponentActionListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    typedef PreComponentActionListener PreCompActionListener;
    typedef PreComponentActionListenerType PreCompActionListenerType;
    void 
    addPreComponentActionListener(PreComponentActionListenerType listener_type,
                                  PreComponentActionListener* listener,
                                  bool autoclean = true);


    template <class Listener>
    PreComponentActionListener*
    addPreComponentActionListener(PreCompActionListenerType listener_type,
                                   Listener& obj,
                                   void (Listener::*memfunc)(UniqueId ec_id))
    {
      class Noname
        : public PreComponentActionListener
      {
      public:
        Noname(Listener& obj, void (Listener::*memfunc)(UniqueId))
          : m_obj(obj), m_memfunc(memfunc)
        {
        }
        void operator()(UniqueId ec_id)
        {
          (m_obj.*m_memfunc)(ec_id);
        }
      private:
        Listener& m_obj;
        typedef void (Listener::*Memfunc)(UniqueId ec_id);
        Memfunc m_memfunc;
      };
      Noname* listener(new Noname(obj, memfunc));
      addPreComponentActionListener(listener_type, listener, true);
      return listener;
    }

    /*!
     * @if jp
     * @brief PreComponentActionListener �ꥹ�ʤ�������
     *
     * ���ꤷ���Ƽ�ꥹ�ʤ������롣
     * 
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     *
     * @else
     * @brief Removing PreComponentAction type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void 
    removePreComponentActionListener(
                                 PreComponentActionListenerType listener_type,
                                 PreComponentActionListener* listener);


    /*!
     * @if jp
     * @brief PostComponentActionListener �ꥹ�ʤ��ɲä���
     *
     * ComponentAction �����ؿ��θƤӽФ�ľ��Υ��٥�Ȥ˴�Ϣ����Ƽ��
     * ���ʤ����ꤹ�롣
     *
     * ����Ǥ���ꥹ�ʤΥ����פȥ�����Хå����٥�Ȥϰʲ����̤�
     *
     * - POST_ON_INITIALIZE:    onInitialize ľ��
     * - POST_ON_FINALIZE:      onFinalize ľ��
     * - POST_ON_STARTUP:       onStartup ľ��
     * - POST_ON_SHUTDOWN:      onShutdown ľ��
     * - POST_ON_ACTIVATED:     onActivated ľ��
     * - POST_ON_DEACTIVATED:   onDeactivated ľ��
     * - POST_ON_ABORTED:       onAborted ľ��
     * - POST_ON_ERROR:         onError ľ��
     * - POST_ON_RESET:         onReset ľ��
     * - POST_ON_EXECUTE:       onExecute ľ��
     * - POST_ON_STATE_UPDATE:  onStateUpdate ľ��
     *
     * �ꥹ�ʤ� PostComponentActionListener ��Ѿ������ʲ��Υ����˥�������
     * operator() ��������Ƥ���ɬ�פ����롣
     *
     * PostComponentActionListener::operator()(UniqueId ec_id, ReturnCode_t ret)
     *
     * �ǥե���ȤǤϡ����δؿ���Ϳ�����ꥹ�ʥ��֥������Ȥν�ͭ����
     * RTObject�˰ܤꡢRTObject���λ��⤷���ϡ�
     * removePostComponentActionListener() �ˤ�������˼�ưŪ�˲��Τ���롣
     * �ꥹ�ʥ��֥������Ȥν�ͭ����ƤӽФ�¦�ǰݻ����������ϡ���3��
     * ���� false ����ꤷ����ưŪ�ʲ��Τ��������뤳�Ȥ��Ǥ��롣
     *
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     * @param autoclean �ꥹ�ʥ��֥������Ȥμ�ưŪ���Τ�Ԥ����ɤ����Υե饰
     *
     * @else
     * @brief Adding PostComponentAction type listener
     *
     * This operation adds certain listeners related to ComponentActions
     * post events.
     * The following listener types are available.
     *
     * - POST_ON_INITIALIZE:    after onInitialize
     * - POST_ON_FINALIZE:      after onFinalize
     * - POST_ON_STARTUP:       after onStartup
     * - POST_ON_SHUTDOWN:      after onShutdown
     * - POST_ON_ACTIVATED:     after onActivated
     * - POST_ON_DEACTIVATED:   after onDeactivated
     * - POST_ON_ABORTED:       after onAborted
     * - POST_ON_ERROR:         after onError
     * - POST_ON_RESET:         after onReset
     * - POST_ON_EXECUTE:       after onExecute
     * - POST_ON_STATE_UPDATE:  after onStateUpdate
     *
     * Listeners should have the following function operator().
     *
     * PostComponentActionListener::operator()(UniqueId ec_id, ReturnCode_t ret)
     *
     * The ownership of the given listener object is transferred to
     * this RTObject object in default.  The given listener object will
     * be destroied automatically in the RTObject's dtor or if the
     * listener is deleted by removePostComponentActionListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    typedef PostComponentActionListener PostCompActionListener;
    typedef PostComponentActionListenerType PostCompActionListenerType;
    void 
    addPostComponentActionListener(
                               PostComponentActionListenerType listener_type,
                               PostComponentActionListener* listener,
                               bool autoclean = true);

    template <class Listener>
    PostComponentActionListener*
    addPostComponentActionListener(PostCompActionListenerType listener_type,
                                   Listener& obj,
                                   void (Listener::*memfunc)(UniqueId ec_id,
                                                             ReturnCode_t ret))
    {
      class Noname
        : public PostComponentActionListener
      {
      public:
        Noname(Listener& obj, void (Listener::*memfunc)(UniqueId, ReturnCode_t))
          : m_obj(obj), m_memfunc(memfunc)
        {
        }
        void operator()(UniqueId ec_id, ReturnCode_t ret)
        {
          (m_obj.*m_memfunc)(ec_id, ret);
        }
      private:
        Listener& m_obj;
        typedef void (Listener::*Memfunc)(UniqueId ec_id, ReturnCode_t ret);
        Memfunc m_memfunc;
      };
      Noname* listener(new Noname(obj, memfunc));
      addPostComponentActionListener(listener_type, listener, true);
      return listener;
    }

    /*!
     * @if jp
     * @brief PostComponentActionListener �ꥹ�ʤ�������
     *
     * ���ꤷ���Ƽ�ꥹ�ʤ������롣
     * 
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     *
     * @else
     * @brief Removing PostComponentAction type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void 
    removePostComponentActionListener(
                                  PostComponentActionListenerType listener_type,
                                  PostComponentActionListener* listener);



    /*!
     * @if jp
     * @brief PortActionListener �ꥹ�ʤ��ɲä���
     *
     * Port���ɲá�������˥�����Хå������Ƽ�ꥹ�ʤ����ꤹ�롣
     *
     * ����Ǥ���ꥹ�ʤΥ����פȥ�����Хå����٥�Ȥϰʲ����̤�
     *
     * - ADD_PORT:    Port�ɲû�
     * - REMOVE_PORT: Port�����
     *
     * �ꥹ�ʤ� PortActionListener ��Ѿ������ʲ��Υ����˥�������
     * operator() ��������Ƥ���ɬ�פ����롣
     *
     * PortActionListener::operator()(PortProfile& pprof)
     *
     * �ǥե���ȤǤϡ����δؿ���Ϳ�����ꥹ�ʥ��֥������Ȥν�ͭ����
     * RTObject�˰ܤꡢRTObject���λ��⤷���ϡ�
     * removePortActionListener() �ˤ�������˼�ưŪ�˲��Τ���롣
     * �ꥹ�ʥ��֥������Ȥν�ͭ����ƤӽФ�¦�ǰݻ����������ϡ���3��
     * ���� false ����ꤷ����ưŪ�ʲ��Τ��������뤳�Ȥ��Ǥ��롣
     *
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     * @param autoclean �ꥹ�ʥ��֥������Ȥμ�ưŪ���Τ�Ԥ����ɤ����Υե饰
     *
     * @else
     * @brief Adding PortAction type listener
     *
     * This operation adds certain listeners related to ComponentActions
     * post events.
     * The following listener types are available.
     *
     * - ADD_PORT:    At adding Port
     * - REMOVE_PORT: At removing Port
     *
     * Listeners should have the following function operator().
     *
     * PortActionListener::operator()(RTC::PortProfile pprof)
     *
     * The ownership of the given listener object is transferred to
     * this RTObject object in default.  The given listener object will
     * be destroied automatically in the RTObject's dtor or if the
     * listener is deleted by removePortActionListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    void 
    addPortActionListener(PortActionListenerType listener_type,
                          PortActionListener* listener,
                          bool autoclean = true);
    
    template <class Listener>
    PortActionListener*
    addPortActionListener(PortActionListenerType listener_type,
                          Listener& obj,
                          void (Listener::*memfunc)(const RTC::PortProfile&))
    {
      class Noname
        : public PortActionListener
      {
      public:
        Noname(Listener& obj,
               void (Listener::*memfunc)(const RTC::PortProfile&))
          : m_obj(obj), m_memfunc(memfunc)
        {
        }
        void operator()(const RTC::PortProfile& pprofile)
        {
          (m_obj.*m_memfunc)(pprofile);
        }
      private:
        Listener& m_obj;
        typedef void (Listener::*Memfunc)(const RTC::PortProfile&);
        Memfunc m_memfunc;
      };
      Noname* listener(new Noname(obj, memfunc));
      addPortActionListener(listener_type, listener, true);
      return listener;
    }

    /*!
     * @if jp
     * @brief PortActionListener �ꥹ�ʤ�������
     *
     * ���ꤷ���Ƽ�ꥹ�ʤ������롣
     * 
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     *
     * @else
     * @brief Removing PortAction type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void 
    removePortActionListener(PortActionListenerType listener_type,
                             PortActionListener* listener);



    /*!
     * @if jp
     * @brief ExecutionContextActionListener �ꥹ�ʤ��ɲä���
     *
     * ExecutionContext���ɲá�������˥�����Хå������Ƽ�ꥹ�ʤ����ꤹ�롣
     *
     * ����Ǥ���ꥹ�ʤΥ����פȥ�����Хå����٥�Ȥϰʲ����̤�
     *
     * - ATTACH_EC:    ExecutionContext �����å���
     * - DETACH_EC:    ExecutionContext �ǥ��å���
     *
     * �ꥹ�ʤ� ExecutionContextActionListener ��Ѿ������ʲ��Υ����˥�������
     * operator() ��������Ƥ���ɬ�פ����롣
     *
     * ExecutionContextActionListener::operator()(UniqueId��ec_id)
     *
     * �ǥե���ȤǤϡ����δؿ���Ϳ�����ꥹ�ʥ��֥������Ȥν�ͭ����
     * RTObject�˰ܤꡢRTObject���λ��⤷���ϡ�
     * removeExecutionContextActionListener() �ˤ�������˼�ưŪ�˲��Τ���롣
     * �ꥹ�ʥ��֥������Ȥν�ͭ����ƤӽФ�¦�ǰݻ����������ϡ���3��
     * ���� false ����ꤷ����ưŪ�ʲ��Τ��������뤳�Ȥ��Ǥ��롣
     *
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     * @param autoclean �ꥹ�ʥ��֥������Ȥμ�ưŪ���Τ�Ԥ����ɤ����Υե饰
     *
     * @else
     * @brief Adding ExecutionContextAction type listener
     *
     * This operation adds certain listeners related to ComponentActions
     * post events.
     * The following listener types are available.
     *
     * - ADD_PORT:    At adding ExecutionContext
     * - REMOVE_PORT: At removing ExecutionContext
     *
     * Listeners should have the following function operator().
     *
     * ExecutionContextActionListener::operator()(UniqueId ec_id)
     *
     * The ownership of the given listener object is transferred to
     * this RTObject object in default.  The given listener object will
     * be destroied automatically in the RTObject's dtor or if the
     * listener is deleted by removeExecutionContextActionListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    typedef ExecutionContextActionListenerType ECActionListenerType;
    typedef ExecutionContextActionListener ECActionListener;
    void addExecutionContextActionListener(ECActionListenerType listener_type,
                                           ECActionListener* listener,
                                           bool autoclean = true);

    template <class Listener>
    ECActionListener*
    addExecutionContextActionListener(ECActionListenerType listener_type,
                                      Listener& obj,
                                      void (Listener::*memfunc)(UniqueId))
    {
      class Noname
        : public ECActionListener
      {
      public:
        Noname(Listener& obj, void (Listener::*memfunc)(UniqueId))
          : m_obj(obj), m_memfunc(memfunc)
        {
        }
        void operator()(UniqueId ec_id)
        {
          (m_obj.*m_memfunc)(ec_id);
        }
      private:
        Listener& m_obj;
        typedef void (Listener::*Memfunc)(UniqueId);
        Memfunc m_memfunc;
      };
      Noname* listener(new Noname(obj, memfunc));
      addExecutionContextActionListener(listener_type, listener, true);
      return listener;
    }
    

    /*!
     * @if jp
     * @brief ExecutionContextActionListener �ꥹ�ʤ�������
     *
     * ���ꤷ���Ƽ�ꥹ�ʤ������롣
     * 
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     *
     * @else
     * @brief Removing ExecutionContextAction type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void 
    removeExecutionContextActionListener(ECActionListenerType listener_type,
                                         ECActionListener* listener);


    /*!
     * @if jp
     * @brief PortConnectListener �ꥹ�ʤ��ɲä���
     *
     * Port����³������³������˸ƤӽФ����Ƽ�ꥹ�ʤ����ꤹ�롣
     *
     * ����Ǥ���ꥹ�ʤΥ����פȥ�����Хå����٥�Ȥϰʲ����̤�
     *
     * - ON_NOTIFY_CONNECT: notify_connect() �ؿ���ƤӽФ�ľ��
     * - ON_NOTIFY_DISCONNECT: notify_disconnect() �ƤӽФ�ľ��
     * - ON_UNSUBSCRIBE_INTERFACES: notify_disconnect() ���IF���ɲ����
     *
     * �ꥹ�ʤ� PortConnectListener ��Ѿ������ʲ��Υ����˥�������
     * operator() ��������Ƥ���ɬ�פ����롣
     *
     * PortConnectListener::operator()(const char*, ConnectorProfile)
     *
     * �ǥե���ȤǤϡ����δؿ���Ϳ�����ꥹ�ʥ��֥������Ȥν�ͭ����
     * RTObject�˰ܤꡢRTObject���λ��⤷���ϡ�
     * removePortConnectListener() �ˤ�������˼�ưŪ�˲��Τ���롣
     * �ꥹ�ʥ��֥������Ȥν�ͭ����ƤӽФ�¦�ǰݻ����������ϡ���3��
     * ���� false ����ꤷ����ưŪ�ʲ��Τ��������뤳�Ȥ��Ǥ��롣
     *
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     * @param autoclean �ꥹ�ʥ��֥������Ȥμ�ưŪ���Τ�Ԥ����ɤ����Υե饰
     *
     * @else
     * @brief Adding PortConnect type listener
     *
     * This operation adds certain listeners related to Port's connect actions.
     * The following listener types are available.
     *
     * - ON_NOTIFY_CONNECT: right after entering into notify_connect()
     * - ON_NOTIFY_DISCONNECT: right after entering into notify_disconnect()
     * - ON_UNSUBSCRIBE_INTERFACES: unsubscribing IF in notify_disconnect()
     *
     * Listeners should have the following function operator().
     *
     * PortConnectListener::operator()(const char*, ConnectorProfile)
     *
     * The ownership of the given listener object is transferred to
     * this RTObject object in default.  The given listener object will
     * be destroied automatically in the RTObject's dtor or if the
     * listener is deleted by removePortConnectListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    void addPortConnectListener(PortConnectListenerType listener_type,
                                           PortConnectListener* listener,
                                           bool autoclean = true);

    template <class Listener>
    PortConnectListener*
    addPortConnectListener(PortConnectListenerType listener_type,
                           Listener& obj,
                           void (Listener::*memfunc)(const char*,
                                                     ConnectorProfile&))
    {
      class Noname
        : public PortConnectListener
      {
      public:
        Noname(Listener& obj,
               void (Listener::*memfunc)(const char*, ConnectorProfile&))
          : m_obj(obj), m_memfunc(memfunc)
        {
        }
        void operator()(const char* portname, ConnectorProfile& cprofile)
        {
          (m_obj.*m_memfunc)(portname, cprofile);
        }
      private:
        Listener& m_obj;
        typedef void (Listener::*Memfunc)(const char*, ConnectorProfile&);
        Memfunc m_memfunc;
      };
      Noname* listener(new Noname(obj, memfunc));
      addPortConnectListener(listener_type, listener, true);
      return listener;
    }
    

    /*!
     * @if jp
     * @brief PortConnectListener �ꥹ�ʤ�������
     *
     * ���ꤷ���Ƽ�ꥹ�ʤ������롣
     * 
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     *
     * @else
     * @brief Removing PortConnect type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void 
    removePortConnectListener(PortConnectListenerType listener_type,
                              PortConnectListener* listener);

    /*!
     * @if jp
     * @brief PortConnectRetListener �ꥹ�ʤ��ɲä���
     *
     * Port����³������³������˸ƤӽФ����Ƽ�ꥹ�ʤ����ꤹ�롣
     *
     * ����Ǥ���ꥹ�ʤΥ����פȥ�����Хå����٥�Ȥϰʲ����̤�
     *
     * - ON_CONNECT_NEXTPORT: notify_connect() ��Υ��������ɸƤӽФ�ľ��
     * - ON_SUBSCRIBE_INTERFACES: notify_connect() ��Υ��󥿡��ե���������ľ��
     * - ON_CONNECTED: nofity_connect() ��³������λ���˸ƤӽФ����
     * - ON_DISCONNECT_NEXT: notify_disconnect() ��˥��������ɸƤӽФ�ľ��
     * - ON_DISCONNECTED: notify_disconnect() �꥿�����
     *
     * �ꥹ�ʤ� PortConnectRetListener ��Ѿ������ʲ��Υ����˥�������
     * operator() ��������Ƥ���ɬ�פ����롣
     *
     * PortConnectRetListener::operator()(const char*, ConnectorProfile)
     *
     * �ǥե���ȤǤϡ����δؿ���Ϳ�����ꥹ�ʥ��֥������Ȥν�ͭ����
     * RTObject�˰ܤꡢRTObject���λ��⤷���ϡ�
     * removePortConnectRetListener() �ˤ�������˼�ưŪ�˲��Τ���롣
     * �ꥹ�ʥ��֥������Ȥν�ͭ����ƤӽФ�¦�ǰݻ����������ϡ���3��
     * ���� false ����ꤷ����ưŪ�ʲ��Τ��������뤳�Ȥ��Ǥ��롣
     *
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     * @param autoclean �ꥹ�ʥ��֥������Ȥμ�ưŪ���Τ�Ԥ����ɤ����Υե饰
     *
     * @else
     * @brief Adding PortConnectRet type listener
     *
     * This operation adds certain listeners related to Port's connect actions.
     * The following listener types are available.
     *
     * - ON_CONNECT_NEXTPORT: after cascade-call in notify_connect()
     * - ON_SUBSCRIBE_INTERFACES: after IF subscribing in notify_connect()
     * - ON_CONNECTED: completed nofity_connect() connection process
     * - ON_DISCONNECT_NEXT: after cascade-call in notify_disconnect()
     * - ON_DISCONNECTED: completed notify_disconnect() disconnection process
     *
     * Listeners should have the following function operator().
     *
     * PortConnectRetListener::operator()(const char*, ConnectorProfile)
     *
     * The ownership of the given listener object is transferred to
     * this RTObject object in default.  The given listener object will
     * be destroied automatically in the RTObject's dtor or if the
     * listener is deleted by removePortConnectRetListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    void addPortConnectRetListener(PortConnectRetListenerType listener_type,
                                           PortConnectRetListener* listener,
                                           bool autoclean = true);

    template <class Listener>
    PortConnectRetListener*
    addPortConnectRetListener(PortConnectRetListenerType listener_type,
                              Listener& obj,
                              void (Listener::*memfunc)(const char*,
                                                        ConnectorProfile&,
                                                        ReturnCode_t))
    {
      class Noname
        : public PortConnectRetListener
      {
      public:
        Noname(Listener& obj,
               void (Listener::*memfunc)(const char*,
                                         ConnectorProfile&,
                                         ReturnCode_t))
          : m_obj(obj), m_memfunc(memfunc)
        {
        }
        void operator()(const char* portname,
                        ConnectorProfile& cprofile,
                        ReturnCode_t ret)
        {
          (m_obj.*m_memfunc)(portname, cprofile, ret);
        }
      private:
        Listener& m_obj;
        typedef void (Listener::*Memfunc)(const char* portname,
                                          ConnectorProfile& cprofile,
                                          ReturnCode_t ret);
        Memfunc m_memfunc;
      };
      Noname* listener(new Noname(obj, memfunc));
      addPortConnectRetListener(listener_type, listener, true);
      return listener;
    }
    

    /*!
     * @if jp
     * @brief PortConnectRetListener �ꥹ�ʤ�������
     *
     * ���ꤷ���Ƽ�ꥹ�ʤ������롣
     * 
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     *
     * @else
     * @brief Removing PortConnectRet type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void 
    removePortConnectRetListener(PortConnectRetListenerType listener_type,
                                 PortConnectRetListener* listener);


    /*!
     * @if jp
     *
     * @brief ConfigurationParamListener ���ɲä���
     *
     * update(const char* config_set, const char* config_param) ���ƤФ줿�ݤ�
     * �����뤵���ꥹ�� ConfigurationParamListener ���ɲä��롣
     * type �ˤϸ��ߤΤȤ��� ON_UPDATE_CONFIG_PARAM �Τߤ����롣
     *
     * @param type ConfigurationParamListenerType�����͡�
     *             ON_UPDATE_CONFIG_PARAM �����롣
     *
     * @param listener ConfigurationParamListener ���Υꥹ�ʥ��֥������ȡ�
     * @param autoclean �ꥹ�ʥ��֥������Ȥ�ư�Ǻ�����뤫�ɤ����Υե饰
     * 
     * @else
     *
     * @brief Adding ConfigurationParamListener 
     * 
     * This function adds a listener object which is called when
     * update(const char* config_set, const char* config_param) is
     * called. In the type argument, currently only
     * ON_UPDATE_CONFIG_PARAM is allowed.
     *
     * @param type ConfigurationParamListenerType value
     *             ON_UPDATE_CONFIG_PARAM is only allowed.
     *
     * @param listener ConfigurationParamListener listener object.
     * @param autoclean a flag whether if the listener object autocleaned.
     *
     * @endif
     */
    void addConfigurationParamListener(ConfigurationParamListenerType type,
                                       ConfigurationParamListener* listener,
                                       bool autoclean = true);

    template <class Listener>
    ConfigurationParamListener*
    addConfigurationParamListener(ConfigurationParamListenerType listener_type,
                                  Listener& obj,
                                  void (Listener::*memfunc)(const char*,
                                                            const char*))
    {
      class Noname
        : public ConfigurationParamListener
      {
      public:
        Noname(Listener& obj,
               void (Listener::*memfunc)(const char*, const char*))
          : m_obj(obj), m_memfunc(memfunc)
        {
        }
        void operator()(const char* config_set_name,
                        const char* config_param_name)
        {
          (m_obj.*m_memfunc)(config_set_name, config_param_name);
        }
      private:
        Listener& m_obj;
        typedef void (Listener::*Memfunc)(const char*, const char*);
        Memfunc m_memfunc;
      };
      Noname* listener(new Noname(obj, memfunc));
      addConfigurationParamListener(listener_type, listener, true);
      return listener;
    }

    /*!
     * @if jp
     *
     * @brief ConfigurationParamListener ��������
     *
     * addConfigurationParamListener ���ɲä��줿�ꥹ�ʥ��֥������Ȥ������롣
     *
     * @param type ConfigurationParamListenerType�����͡�
     *             ON_UPDATE_CONFIG_PARAM �����롣
     * @param listener Ϳ�����ꥹ�ʥ��֥������ȤؤΥݥ���
     * 
     * @else
     *
     * @brief Removing ConfigurationParamListener 
     * 
     * This function removes a listener object which is added by
     * addConfigurationParamListener() function.
     *
     * @param type ConfigurationParamListenerType value
     *             ON_UPDATE_CONFIG_PARAM is only allowed.
     * @param listener a pointer to ConfigurationParamListener listener object.
     *
     * @endif
     */
    void removeConfigurationParamListener(ConfigurationParamListenerType type,
                                          ConfigurationParamListener* listener);
    
    /*!
     * @if jp
     *
     * @brief ConfigurationSetListener ���ɲä���
     *
     * ConfigurationSet ���������줿�Ȥ��ʤɤ˸ƤФ��ꥹ��
     * ConfigurationSetListener ���ɲä��롣�����ǽ�ʥ��٥�Ȥϰʲ���
     * 2���ब���롣
     *
     * - ON_SET_CONFIG_SET: setConfigurationSetValues() ��
     *                      ConfigurationSet ���ͤ����ꤵ�줿��硣
     * - ON_ADD_CONFIG_SET: addConfigurationSet() �ǿ�����
     *                      ConfigurationSet ���ɲä��줿��硣
     *
     * @param type ConfigurationSetListenerType�����͡�
     * @param listener ConfigurationSetListener ���Υꥹ�ʥ��֥������ȡ�
     * @param autoclean �ꥹ�ʥ��֥������Ȥ�ư�Ǻ�����뤫�ɤ����Υե饰
     * 
     * @else
     *
     * @brief Adding ConfigurationSetListener 
     * 
     * This function add a listener object which is called when
     * ConfigurationSet is updated. Available events are the followings.
     *
     * @param type ConfigurationSetListenerType value
     * @param listener ConfigurationSetListener listener object.
     * @param autoclean a flag whether if the listener object autocleaned.
     *
     * @endif
     */
    void addConfigurationSetListener(ConfigurationSetListenerType type,
                                     ConfigurationSetListener* listener,
                                     bool autoclean = true);

    template <class Listener>
    ConfigurationSetListener*
    addConfigurationSetListener(ConfigurationSetListenerType listener_type,
                                Listener& obj,
                                void (Listener::*memfunc)
                                (const coil::Properties& config_set))
    {
      class Noname
        : public ConfigurationSetListener
      {
      public:
        Noname(Listener& obj,
               void (Listener::*memfunc)(const coil::Properties& config_set))
          : m_obj(obj), m_memfunc(memfunc)
        {
        }
        virtual void operator()(const coil::Properties& config_set)
        {
          (m_obj.*m_memfunc)(config_set);
        }
      private:
        Listener& m_obj;
        typedef void (Listener::*Memfunc)(const coil::Properties& config_set);
        Memfunc m_memfunc;
      };
      Noname* listener(new Noname(obj, memfunc));
      addConfigurationSetListener(listener_type, listener, true);
      return listener;
    }

    /*!
     * @if jp
     *
     * @brief ConfigurationSetListener ��������
     *
     * addConfigurationSetListener ���ɲä��줿�ꥹ�ʥ��֥������Ȥ������롣
     *
     * @param type ConfigurationSetListenerType�����͡�
     * @param listener Ϳ�����ꥹ�ʥ��֥������ȤؤΥݥ���
     * 
     * @else
     *
     * @brief Removing ConfigurationSetListener 
     * 
     * This function removes a listener object which is added by
     * addConfigurationSetListener() function.
     *
     * @param type ConfigurationSetListenerType value
     * @param listener a pointer to ConfigurationSetListener listener object.
     *
     * @endif
     */
    void removeConfigurationSetListener(ConfigurationSetListenerType type,
                                        ConfigurationSetListener* listener);
    
    /*!
     * @if jp
     *
     * @brief ConfigurationSetNameListener ���ɲä���
     *
     * ConfigurationSetName ���������줿�Ȥ��ʤɤ˸ƤФ��ꥹ��
     * ConfigurationSetNameListener ���ɲä��롣�����ǽ�ʥ��٥�Ȥϰʲ���
     * 3���ब���롣
     *
     * - ON_UPDATE_CONFIG_SET: ���� ConfigurationSet �����åץǡ��Ȥ��줿
     * - ON_REMOVE_CONFIG_SET: ���� ConfigurationSet ��������줿
     * - ON_ACTIVATE_CONFIG_SET: ���� ConfigurationSet �������ƥ��ֲ����줿
     *
     * @param type ConfigurationSetNameListenerType�����͡�
     * @param listener ConfigurationSetNameListener ���Υꥹ�ʥ��֥������ȡ�
     * @param autoclean �ꥹ�ʥ��֥������Ȥ�ư�Ǻ�����뤫�ɤ����Υե饰
     * 
     * @else
     *
     * @brief Adding ConfigurationSetNameListener 
     * 
     * This function add a listener object which is called when
     * ConfigurationSetName is updated. Available events are the followings.
     *
     * - ON_UPDATE_CONFIG_SET: A ConfigurationSet has been updated.
     * - ON_REMOVE_CONFIG_SET: A ConfigurationSet has been deleted.
     * - ON_ACTIVATE_CONFIG_SET: A ConfigurationSet has been activated.
     *
     * @param type ConfigurationSetNameListenerType value
     * @param listener ConfigurationSetNameListener listener object.
     * @param autoclean a flag whether if the listener object autocleaned.
     *
     * @endif
     */
    void 
    addConfigurationSetNameListener(ConfigurationSetNameListenerType type,
                                    ConfigurationSetNameListener* listener,
                                    bool autoclean = true);

    template <class Listener>
    ConfigurationSetNameListener*
    addConfigurationSetNameListener(ConfigurationSetNameListenerType type,
                                    Listener& obj,
                                    void (Listener::*memfunc)(const char*))
    {
      class Noname
        : public ConfigurationSetNameListener
      {
      public:
        Noname(Listener& obj, void (Listener::*memfunc)(const char*))
          : m_obj(obj), m_memfunc(memfunc)
        {
        }
        virtual void operator()(const char* config_set_name)
        {
          (m_obj.*m_memfunc)(config_set_name);
        }
      private:
        Listener& m_obj;
        typedef void (Listener::*Memfunc)(const char*);
        Memfunc m_memfunc;
      };
      Noname* listener(new Noname(obj, memfunc));
      addConfigurationSetNameListener(type, listener, true);
      return listener;
    }

    /*!
     * @if jp
     *
     * @brief ConfigurationSetNameListener ��������
     *
     * addConfigurationSetNameListener ���ɲä��줿�ꥹ�ʥ��֥������Ȥ�
     * ������롣
     *
     * @param type ConfigurationSetNameListenerType�����͡�
     *             ON_UPDATE_CONFIG_PARAM �����롣
     * @param listener Ϳ�����ꥹ�ʥ��֥������ȤؤΥݥ���
     * 
     * @else
     *
     * @brief Removing ConfigurationSetNameListener 
     * 
     * This function removes a listener object which is added by
     * addConfigurationSetNameListener() function.
     *
     * @param type ConfigurationSetNameListenerType value
     *             ON_UPDATE_CONFIG_PARAM is only allowed.
     * @param listener a pointer to ConfigurationSetNameListener
     *             listener object.
     *
     * @endif
     */
    void
    removeConfigurationSetNameListener(ConfigurationSetNameListenerType type,
                                       ConfigurationSetNameListener* listener);
    
  protected:
    /*!
     * @if jp
     *
     * @brief RTC ��λ����
     *
     * RTC �ν�λ������¹Ԥ��롣
     * �ݻ����Ƥ����� Port ����Ͽ��������ȤȤ�ˡ��������� CORBA ���֥�������
     * �������������RTC ��λ���롣
     *
     * @else
     *
     * @brief Shutdown RTC
     *
     * This operation ececutes RTC's termination.
     * This unregisters all Ports, deactivates corresponding CORBA objects and 
     * shuts down RTC.
     *
     * @endif
     */
    void shutdown();

    inline void preOnInitialize(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_INITIALIZE].notify(ec_id);
    }

    inline void preOnFinalize(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_FINALIZE].notify(ec_id);
    }

    inline void preOnStartup(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_STARTUP].notify(ec_id);
    }

    inline void preOnShutdown(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_SHUTDOWN].notify(ec_id);
    }

    inline void preOnActivated(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_ACTIVATED].notify(ec_id);
    }

    inline void preOnDeactivated(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_DEACTIVATED].notify(ec_id);
    }

    inline void preOnAborting(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_ABORTING].notify(ec_id);
    }

    inline void preOnError(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_ERROR].notify(ec_id);
    }

    inline void preOnReset(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_RESET].notify(ec_id);
    }

    inline void preOnExecute(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_EXECUTE].notify(ec_id);
    }

    inline void preOnStateUpdate(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_STATE_UPDATE].notify(ec_id);
    }

    inline void preOnRateChanged(UniqueId ec_id)
    {
      m_actionListeners.preaction_[PRE_ON_RATE_CHANGED].notify(ec_id);
    }

    inline void postOnInitialize(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_INITIALIZE].notify(ec_id, ret);
    }

    inline void postOnFinalize(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_FINALIZE].notify(ec_id, ret);
    }

    inline void postOnStartup(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_STARTUP].notify(ec_id, ret);
    }

    inline void postOnShutdown(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_SHUTDOWN].notify(ec_id, ret);
    }

    inline void postOnActivated(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_ACTIVATED].notify(ec_id, ret);
    }

    inline void postOnDeactivated(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_DEACTIVATED].notify(ec_id, ret);
    }

    inline void postOnAborting(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_ABORTING].notify(ec_id, ret);
    }

    inline void postOnError(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_ERROR].notify(ec_id, ret);
    }

    inline void postOnReset(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_RESET].notify(ec_id, ret);
    }

    inline void postOnExecute(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_EXECUTE].notify(ec_id, ret);
    }

    inline void postOnStateUpdate(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_STATE_UPDATE].notify(ec_id, ret);
    }

    inline void postOnRateChanged(UniqueId ec_id, ReturnCode_t ret)
    {
      m_actionListeners.postaction_[POST_ON_RATE_CHANGED].notify(ec_id, ret);
    }

    inline void onAddPort(const PortProfile& pprof)
    {
      m_actionListeners.portaction_[ADD_PORT].notify(pprof);
    }
    
    inline void onRemovePort(const PortProfile& pprof)
    {
      m_actionListeners.portaction_[REMOVE_PORT].notify(pprof);
    }
    
    inline void onAttachExecutionContext(UniqueId ec_id)
    {
      m_actionListeners.ecaction_[EC_ATTACHED].notify(ec_id);
    }
    
    inline void onDetachExecutionContext(UniqueId ec_id)
    {
      m_actionListeners.ecaction_[EC_DETACHED].notify(ec_id);
    }
    
  protected:
    /*!
     * @if jp
     * @brief �������ȥ꡼��
     * @else
     * @brief Logger stream
     * @endif
     */
    mutable Logger rtclog;
    /*!
     * @if jp
     * @brief �ޥ͡����㥪�֥�������
     * @else
     * @brief Manager object
     * @endif
     */
    Manager* m_pManager;
    
    /*!
     * @if jp
     * @brief ORB �ؤΥݥ���
     * @else
     * @brief The pointer to the ORB
     * @endif
     */
    CORBA::ORB_var m_pORB;
    
    /*!
     * @if jp
     * @brief POA �ؤΥݥ���
     * @else
     * @brief The pointer to the POA
     * @endif
     */
    PortableServer::POA_var m_pPOA;
    
    //============================================================
    // SDO �ط����ѿ�
    //============================================================
    /*!
     * @if jp
     * @brief SDO ���ݻ����� organization �Υꥹ��
     * @else
     * @brief SDO owned organization list
     * @endif
     */
    SDOPackage::OrganizationList m_sdoOwnedOrganizations;
    
    /*!
     * @if jp
     * @brief SDOService �Υץ�ե�����ꥹ�Ȥ���id�ǥ��������뤿��Υե��󥯥�
     * @else
     * @brief Functor to find from SDOService Profile List by id
     * @endif
     */
    struct svc_name
    {
      svc_name (const char* id) : m_id(id) {};
      bool operator()(const SDOPackage::ServiceProfile& prof)
      {
	return m_id == std::string(prof.id);
      }
      std::string m_id;
    };  // struct svc_name
    
    /*!
     * @if jp
     * @brief SDO Configuration ���֥������ȤؤΥݥ���
     * @else
     * @brief The pointer to the SDO Configuration Object
     * @endif
     */
    SDOPackage::Configuration_impl* m_pSdoConfigImpl;
    
    /*!
     * @if jp
     * @brief SDO Configuration Interface �ؤΥݥ���
     * @else
     * @brief The pointer to the SDO Configuration Interface
     * @endif
     */
    SDOPackage::Configuration_var  m_pSdoConfig;
    
    /*!
     * @if jp
     * @brief SDO organization
     * @else
     * @brief SDO organization
     * @endif
     */
    SDOPackage::OrganizationList m_sdoOrganizations;
    
    /*!
     * @if jp
     * @brief SDO Status
     * @else
     * @brief SDO Status
     * @endif
     */
    SDOPackage::NVList m_sdoStatus;
    
    //============================================================
    // RTC �ط����ѿ�
    //============================================================
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȥץ�ե�����
     * @else
     * @brief ComponentProfile
     * @endif
     */
    ComponentProfile m_profile;
    
    /*!
     * @if jp
     * @brief ���֥������ȥ�ե����
     * @else
     * @brief Object reference
     * @endif
     */
    RTObject_var m_objref;
    
    /*!
     * @if jp
     * @brief Port �Υ��֥������ȥ�ե���󥹤Υꥹ��
     * @else
     * @brief List of Port Object reference
     * @endif
     */
    PortAdmin m_portAdmin;

    /*!
     * @if jp
     * @brief InPortBase* �Υꥹ��
     * @else
     * @brief List of InPortBase*
     * @endif
     */
    std::vector<InPortBase*> m_inports;

    /*!
     * @if jp
     * @brief OutPortBase* �Υꥹ��
     * @else
     * @brief List of OutPortBase*
     * @endif
     */
    std::vector<OutPortBase*> m_outports;
    
    /*!
     * @if jp
     * @brief ��ʬ��owner��ExecutionContextService �Υꥹ��
     * @else
     * @brief List of owned ExecutionContextService
     * @endif
     */
    ExecutionContextServiceList m_ecMine;
    
    /*!
     * @if jp
     * @brief ExecutionContextBase �Υꥹ��
     * @else
     * @brief List of ExecutionContextBase 
     * @endif
     */
    std::vector<ExecutionContextBase*> m_eclist;
    
    /*!
     * @if jp
     * @brief ���ä��Ƥ���ExecutionContextService �Υꥹ��
     * @else
     * @brief List of participating ExecutionContextService
     * @endif
     */
    ExecutionContextServiceList m_ecOther;
    
    /*!
     * @if jp
     * @brief Created ���֥ե饰
     * @else
     * @brief Created Status Flag
     * @endif
     */
    bool m_created;
    
    /*!
     * @if jp
     * @brief RTC�ν�λ���֥ե饰
     * @else
     * @brief RTC Finalize Status Flag
     * @endif
     */
    bool m_exiting;
    
    /*!
     * @if jp
     * @brief Alive ���֥ե饰
     * @else
     * @brief Alive Status Flag
     * @endif
     */
    //    bool m_alive;
    
    /*!
     * @if jp
     * @brief RTC �Υץ�ѥƥ�
     * @else
     * @brief RTC's Property
     * @endif
     */
    coil::Properties m_properties;
    
    /*!
     * @if jp
     * @brief ����ե�����졼��������������֥�������
     * @else
     * @brief Configuration Administrator Object
     * @endif
     */
    ConfigAdmin m_configsets;
    
    /*!
     * @if jp
     * @brief SDO Service �������֥�������
     * @else
     * @brief SDO Service Administrator Object
     * @endif
     */
    SdoServiceAdmin m_sdoservice;

    /*!
     * @if jp
     * @brief readAll()�ƽ��ѤΥե饰
     * @else
     * @brief flag for readAll()
     * @endif
     */
    bool m_readAll;

    /*!
     * @if jp
     * @brief writeAll()�ƽ��ѤΥե饰
     * @else
     * @brief flag for writeAll()
     * @endif
     */
    bool m_writeAll;

    /*!
     * @if jp
     * @brief readAll()�ѤΥե饰
     *
     * true:readAll()������Ǥǥ��顼��ȯ�����Ƥ�Ǹ�ޤǼ»ܤ��롣
     * false:readAll()������Ǥǥ��顼��ȯ��������罪λ��
     *
     * @else
     * @brief flag for readAll()
     *
     * true:Even if the error occurs during readAll(), it executes it to the 
     *      last minute. 
     * false:End when error occurs during readAll().
     *
     * @endif
     */
    bool m_readAllCompletion;

    /*!
     * @if jp
     * @brief writeAll()�ѤΥե饰
     *
     * true:writeAll()������Ǥǥ��顼��ȯ�����Ƥ�Ǹ�ޤǼ»ܤ��롣
     * false:writeAll()������Ǥǥ��顼��ȯ��������罪λ��
     *
     * @else
     * @brief flag for writeAll()
     *
     * true:Even if the error occurs during writeAll(), it executes it to the 
     *      last minute. 
     * false:End when error occurs during writeAll().
     *
     * @endif
     */
    bool m_writeAllCompletion;

    /*!
     * @if jp
     * @brief ComponentActionListener�ۥ��
     *
     * ComponentActionListenr���ݻ�����ۥ��
     *
     * @else
     * @brief ComponentActionListener holder
     *
     * Holders of ComponentActionListeners
     *
     * @endif
     */
    ComponentActionListeners m_actionListeners;

    /*!
     * @if jp
     * @brief PortConnectListener�ۥ��
     *
     * PortConnectListenr���ݻ�����ۥ��
     *
     * @else
     * @brief PortConnectListener holder
     *
     * Holders of PortConnectListeners
     *
     * @endif
     */
    PortConnectListeners m_portconnListeners;

    //------------------------------------------------------------
    // Functor
    //------------------------------------------------------------
    /*!
     * @if jp
     * @brief NVList �����ѥե��󥯥�
     * @else
     * @brief Functor to find NVList
     * @endif
     */
    struct nv_name
    {
      nv_name(const char* name) : m_name(name) {};
      bool operator()(const SDOPackage::NameValue& nv)
      {
	return m_name == std::string(nv.name);
      }
      std::string m_name;
    };  // struct nv_name
    
    /*!
     * @if jp
     * @brief ExecutionContext ���ԡ��ե��󥯥�
     * @else
     * @brief Functor to copy ExecutionContext
     * @endif
     */
    struct ec_copy
    {
      ec_copy(ExecutionContextList& eclist)
	: m_eclist(eclist)
      {
      }
      void operator()(ExecutionContextService_ptr ecs)
      {
        if (!::CORBA::is_nil(ecs))
          {
	    CORBA_SeqUtil::push_back(m_eclist,
                                     ExecutionContext::_duplicate(ecs));
          }
      }
      ExecutionContextList& m_eclist;
    };  // struct ec_copy
    /*!
     * @if jp
     * @brief ExecutionContext �����ѥե��󥯥�
     * @else
     * @brief Functor to find ExecutionContext
     * @endif
     */
    struct ec_find
    {
      ec_find(ExecutionContext_ptr& ec)
	: m_ec(ExecutionContext::_duplicate(ec))
      {
      }
      bool operator()(ExecutionContextService_ptr ecs)
      {
	try
	  {
            if (!::CORBA::is_nil(ecs))
              {
  	        ExecutionContext_var ec;
	        ec = ExecutionContext::_narrow(ecs);
	        return m_ec->_is_equivalent(ec);
              }
	  }
	catch (...)
	  {
	    return false;
	  }
	return false;
      }
      ExecutionContext_var m_ec;

    };  // struct ec_find
    //    ExecutionContextAdminList m_execContextList;
    
    /*!
     * @if jp
     * @brief RTC ��������ѥե��󥯥�
     * @else
     * @brief Functor to deactivate RTC
     * @endif
     */
    struct deactivate_comps
    {
      deactivate_comps(LightweightRTObject_ptr comp)
	: m_comp(RTC::LightweightRTObject::_duplicate(comp))
      {
      }
      void operator()(ExecutionContextService_ptr ec)
      {
        if (!::CORBA::is_nil(ec) && !ec->_non_existent())
          {
            
	    ec->deactivate_component(RTC::LightweightRTObject::_duplicate(m_comp));
            ec->stop();
          }
      }
      LightweightRTObject_var m_comp;
    };  // struct deactivate_comps
  };  // class RTObject_impl
};  // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_RTOBJECT
