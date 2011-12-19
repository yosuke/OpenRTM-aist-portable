// -*- C++ -*-
/*!
 * @file PeriodicECSharedComposite.h
 * @brief Periodic Execution Context Shared Composite Component class
 * @date $Date$
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

#ifndef RTC_PERIODICECSHAREDCOMPOSITE_H
#define RTC_PERIODICECSHAREDCOMPOSITE_H

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>
#include <rtm/RTObject.h>
#include <rtm/PeriodicExecutionContext.h>
#include <rtm/SdoOrganization.h>
#include <coil/stringutil.h>

/*!
 * @if jp
 * @namespace SDOPackage
 *
 * @brief SDO �ѥå�����
 *
 * @else
 *
 * @namespace SDOPackage
 *
 * @brief SDO Package
 *
 * @endif
 */

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace SDOPackage
{
  /*!
   * @if jp
   * @class PeriodicECOrganization
   * @brief PeriodicECOrganization ���饹
   *
   * Organization_imp �μ���
   *
   * @else
   * @class PeriodicECOrganization
   * @brief PeriodicECOrganization class
   *
   * Implement of Organization_imp
   *
   * @endif
   */
  class PeriodicECOrganization
    : public Organization_impl
  {
    typedef std::vector<std::string> PortList;

  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param rtobj ���֥�������
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param rtobj Object
     *
     * @endif
     */
    PeriodicECOrganization(::RTC::RTObject_impl* rtobj);
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
    virtual ~PeriodicECOrganization(void);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization���С����ɲä���
     *
     * Organization ���ݻ�������С��ꥹ�Ȥ�Ϳ����줿SDOList���ɲä��롣
     * 
     * @param sdo_list �ɲä���� SDO ���С��Υꥹ��
     * @return �ɲä������������ɤ�����bool���֤����
     *
     * @else
     * 
     * @brief [CORBA interface] Add Organization member
     *
     * This operation adds the given SDOList to the existing organization's 
     * member list
     * 
     * @param sdo_list SDO member list to be added
     * @return boolean will returned if the operation succeed
     *
     * @endif
     */
    virtual ::CORBA::Boolean add_members(const SDOList& sdo_list)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization���С��򥻥åȤ���
     *
     * Organization ���ݻ�������С��ꥹ�Ȥ�������Ϳ����줿
     * SDOList�򿷵��˥��åȤ��롣
     * 
     * @param sdo_list �����˥��åȤ���� SDO ���С��Υꥹ��
     * @return �ɲä������������ɤ�����bool���֤����
     *
     * @else
     * 
     * @brief [CORBA interface] Set Organization member
     *
     * This operation removes existing member list and sets the given
     * SDOList to the existing organization's member list
     * 
     * @param sdo_list SDO member list to be set
     * @return boolean will returned if the operation succeed
     *
     * @endif
     */
    virtual ::CORBA::Boolean set_members(const SDOList& sdos)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization���С���������
     *
     * Organization ���ݻ�������С��ꥹ����������SDO�������롣
     * 
     * @param id �������� SDO �� ID
     * @return �ɲä������������ɤ�����bool���֤����
     *
     * @else
     * 
     * @brief [CORBA interface] Remove a member of Organization
     *
     * This operation removes a SDO from existing member list by specified ID.
     * 
     * @param id The ID of the SDO to be removed
     * @return boolean will returned if the operation succeed
     *
     * @endif
     */
    virtual ::CORBA::Boolean remove_member(const char* id)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * @brief Organization���С���������
     * @else
     * @brief Remove a member of Organization
     * @endif
     */
    void removeAllMembers(void);
    /*!
     * @if jp
     * @brief Organization���С��򹹿�/�������
     * @else
     * @brief Update/Remove a member of Organization
     * @endif
     */
    void updateDelegatedPorts(void);

  protected:
    class Member;
    /*!
     * @if jp
     * @brief SDO����DFC�ؤ��Ѵ�
     * @else
     * @brief Conversion from SDO to DFC
     * @endif
     */
    bool sdoToDFC(const SDO_ptr sdo, ::OpenRTM::DataFlowComponent_ptr& dfc);

    /*!
     * @if jp
     * @brief Owned ExecutionContext ����ߤ�����
     * @else
     * @brief Stop Owned ExecutionContexts
     * @endif
     */
    void stopOwnedEC(Member& member);

    /*!
     * @if jp
     * @brief Owned ExecutionContext ��ư����
     * @else
     * @brief Start Owned ExecutionContexts
     * @endif
     */
    void startOwnedEC(Member& member);

    /*!
     * @if jp
     * @brief DFC �� Organization ���֥������Ȥ�Ϳ����
     * @else
     * @brief Set Organization object to target DFC 
     * @endif
     */
    void addOrganizationToTarget(Member& member);

    /*!
     * @if jp
     * @brief Organization ���֥������Ȥ� DFC����������
     * @else
     * @brief Remove Organization object from a target DFC 
     * @endif
     */
    void removeOrganizationFromTarget(Member& member);

    /*!
     * @if jp
     * @brief Composite �� ExecutionContext �� DFC �˥��åȤ���
     * @else
     * @brief Set CompositeRTC's ExecutionContext to the given DFC
     * @endif
     */
    void addParticipantToEC(Member& member);

    /*!
     * @if jp
     * @brief Composite �� ExecutionContext ���� DFC ��������
     * @else
     * @brief Remove participant DFC from CompositeRTC's ExecutionContext
     * @endif
     */
    void removeParticipantFromEC(Member& member);

    /*!
     * @if jp
     * @brief �ݡ��Ȥ�Ѿ�����
     * @else
     * @brief Delegate given RTC's ports to the Composite
     * @endif
     */
    void addPort(Member& member, PortList& portlist);

    /*!
     * @if jp
     * @brief �Ѿ����Ƥ����ݡ��Ȥ�������
     * @else
     * @brief Remove delegated participatns's ports from the composite
     * @endif
     */
    void removePort(Member& member, PortList& portlist);

    /*!
     * @if jp
     * @brief PortsList�򹹿�����
     * @else
     * @brief PortsList is updated. 
     * @endif
     */
    void updateExportedPortsList(void);

  protected:
    /*!
     * @if jp
     * @brief �������ȥ꡼��
     * @else
     * @brief Logger stream
     * @endif
     */
    RTC::Logger rtclog;

    /*!
     * @if jp
     * @brief RT ���֥�������
     * @else
     * @brief RT Object
     * @endif
     */
    ::RTC::RTObject_impl* m_rtobj;

    /*!
     * @if jp
     * @brief ExecutionContext ���֥������ȥ�ե����
     * @else
     * @brief ExecutionContext Object reference
     * @endif
     */
    ::RTC::ExecutionContext_var m_ec;

    class Member
    {
    public:
      Member(RTC::RTObject_ptr rtobj)
      //        : rtobj_(rtobj),
      //          profile_(rtobj->get_component_profile()),
      //          eclist_(rtobj->get_owned_contexts()),
      //          config_(rtobj->get_configuration())
      {
        rtobj_   = RTC::RTObject::_duplicate(rtobj);
	profile_ = rtobj->get_component_profile();
	eclist_  = rtobj->get_owned_contexts();
	config_  = rtobj->get_configuration();
      }

      virtual ~Member(void)
      {
	/*
        rtobj_.out();
        profile_.out();
        eclist_.out();
        config_.out();
	*/
      }

      Member(const Member& x)
      //        : rtobj_(x.rtobj_),
      //          profile_(x.profile_),
      //          eclist_(x.eclist_),
      //          config_(x.config_)
      {
        rtobj_   = x.rtobj_;
        profile_ = x.profile_;
        eclist_  = x.eclist_;
        config_  = x.config_;
      }

      Member& operator=(const Member& x)
      {
//        std::cout << "####################op=" << std::endl;
        Member tmp(x);
        tmp.swap(*this);
        return *this;
      }
//
      void swap(Member& x)
      {
        RTC::RTObject_var rtobj(x.rtobj_);
        RTC::ComponentProfile_var profile(x.profile_);
        RTC::ExecutionContextList_var eclist(x.eclist_);
        SDOPackage::Configuration_var config(x.config_);

        x.rtobj_ = this->rtobj_;
        x.profile_ = this->profile_;
        x.eclist_ = this->eclist_;
        x.config_ = this->config_;

        this->rtobj_ = rtobj;
        this->profile_ = profile;
        this->eclist_ = eclist;
        this->config_ = config;
      }

      RTC::RTObject_var rtobj_;
      RTC::ComponentProfile_var profile_;
      RTC::ExecutionContextList_var eclist_;
      SDOPackage::Configuration_var config_;
    };

    /*!
     * @if jp
     * @brief RTC���С��ꥹ��
     * @else
     * @brief Member list
     * @endif
     */
    std::vector<Member> m_rtcMembers;
    typedef std::vector<Member>::iterator MemIt;

    /*!
     * @if jp
     * @brief Port List
     * @else
     * @brief Port List
     * @endif
     */
    PortList m_expPorts;
    
    /*!
     * @if jp
     * @brief PortList��ɸ����Ϥ��롣
     * @else
     * @brief Output PortList to StandardOutput. 
     * @endif
     */
    void print(PortList p)
    {
      for (int i(0), len(p.size()); i < len; ++i)
        {
          std::cout << p[i] << std::endl;
        }
    }
  };
};


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
  class Manager;

  /*!
   * @if jp
   * @class PeriodicECSharedComposite
   * @brief PeriodicECSharedComposite ���饹
   *
   * �ǡ����ե���RTComponent�δ��쥯�饹��
   * �Ƽ�ǡ����ե���RTComponent�����������ϡ��ܥ��饹��Ѿ�������Ǽ���
   * ���롣
   *
   * @since 0.4.0
   *
   * @else
   * @class PeriodicECSharedComposite
   * @brief PeriodicECSharedComposite class
   *
   * This is a base class of the data flow type RT-Component.
   * Inherit this class when implementing various data flow type RT-Components.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class PeriodicECSharedComposite
    : public RTObject_impl
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
     * @brief Constructor
     *
     * Constructor
     *
     * @param manager Manager object
     *
     * @endif
     */
    PeriodicECSharedComposite(Manager* manager);
    
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
    virtual ~PeriodicECSharedComposite(void);
    
    /*!
     * @if jp
     * @brief �����
     *
     * �ǡ����ե��� RTComponent �ν������¹Ԥ��롣
     * �ºݤν���������ϡ��ƶ�ݥ��饹��˵��Ҥ��롣
     *
     * @else
     * @brief Initialization
     *
     * Initialization the data flow type RT-Component.
     * Write the actual initialization code in each concrete class.
     *
     * @endif
     */
    virtual ReturnCode_t onInitialize(void);
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
    virtual ReturnCode_t onActivated(RTC::UniqueId exec_handle);
    /*!
     * @if jp
     *
     * @brief ������������ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_deactivated ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå�
     * �ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�Ȥμºݤ�������������ϡ��ܴؿ��򥪡��С��饤�ɤ��Ƽ�������
     * ɬ�פ����롣
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
    virtual ReturnCode_t onDeactivated(RTC::UniqueId exec_handle);

    /*!
     * @if jp
     *
     * @brief �ꥻ�åȽ����ѥ�����Хå��ؿ�
     * 
     * ComponentAction::on_reset ���ƤФ줿�ݤ˼¹Ԥ���륳����Хå��ؿ���<BR>
     * �ܴؿ���̵���� RTC::RTC_OK ���֤��褦�˥��ߡ���������Ƥ���Τǡ�
     * �ƥ���ݡ��ͥ�ȤμºݤΥꥻ�åȽ����ϡ��ܴؿ��򥪡��С��饤�ɤ��Ƽ�������
     * ɬ�פ����롣
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
    virtual ReturnCode_t onReset(RTC::UniqueId exec_handle);
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
    virtual ReturnCode_t onFinalize(void);
    
  protected:
    /*!
     * @if jp
     * @brief ����ݡ��ͥ��
     * @else
     * @brief Components
     * @endif
     */
    std::vector<std::string> m_members;

    /*!
     * @if jp
     * @brief ���֥������ȤΥ�ե����
     * @else
     * @brief Reference of object
     * @endif
     */
    OpenRTM::DataFlowComponent_var m_ref;
//    PeriodicExecutionContext* m_pec;
//    ExecutionContextService_var m_ecref;
    /*!
     * @if jp
     * @brief Organization�Υ�ե����
     * @else
     * @brief Reference of Organization
     * @endif
     */
    SDOPackage::PeriodicECOrganization* m_org;
  };  // class PeriodicECOrganization
}; // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif


extern "C"
{
  DLL_EXPORT void PeriodicECSharedCompositeInit(RTC::Manager* manager);
};

#endif // RTC_PERIODICECSHAREDCOMPOSITE_H
