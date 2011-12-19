// -*- C++ -*-
/*!
 * @file Factory.h
 * @brief RT-Component factory class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Factory.h 1569 2009-11-12 14:36:47Z n-ando $
 *
 */

#ifndef RTC_FACTORY_H
#define RTC_FACTORY_H

#include <coil/Properties.h>
//#include <rtm/RTObject.h>
#include <rtm/NumberingPolicy.h>


namespace RTC 
{
  class RTObject_impl;
  class Manager;
  
  typedef RTObject_impl* (*RtcNewFunc)(Manager* manager);
  typedef void (*RtcDeleteFunc)(RTObject_impl* rtc);
  
  /*!
   * @if jp
   *
   * @brief RT����ݡ��ͥ�������ѥƥ�ץ졼�ȴؿ�
   * 
   * RT����ݡ��ͥ�ȤΥ��󥹥��󥹤��������뤿��Υƥ�ץ졼�ȴؿ���
   * RT����ݡ��ͥ�ȴ����ѥޥ͡����㤫��ƤӽФ���롣
   * �ºݤˤϳƥ���ݡ��ͥ�ȤΥ��󥹥ȥ饯�����ƤӽФ���롣
   * \<_New\>�������о�RT����ݡ��ͥ�Ȥη�����ꤹ�롣
   *
   * @param manager �ޥ͡����㥪�֥�������
   *
   * @return �������� RT����ݡ��ͥ�� ���󥹥���
   * 
   * @else
   * @brief Template function to create RT-Components
   * 
   * This is the template function to create RT-Component's instances.
   * This is invoked from RT-Components manager.
   * Actually, each component's constructor is invoked.
   * Specify the type of the target RT-Components for creation by \<_New\>.
   *
   * @param manager Manager object
   *
   * @return Created RT-Component's instances
   *
   * @endif
   */
  template <class _New>
  RTObject_impl* Create(Manager* manager)
  {
    return new _New(manager);
  }
  
  /*!
   * @if jp
   *
   * @brief RT����ݡ��ͥ���˴��ѥƥ�ץ졼�ȴؿ�
   * 
   * RT����ݡ��ͥ�ȤΥ��󥹥��󥹤��˴����뤿��Υƥ�ץ졼�ȴؿ���
   * \<_Delete\>�ˤ��˴��о�RT����ݡ��ͥ�Ȥη�����ꤹ�롣
   *
   * @param rtc �˴��о�RT����ݡ��ͥ�ȤΥ��󥹥���
   *
   * @else
   *
   * @brief Template function to destroy RT-Components
   * 
   * This is the template function to destroy RT-Component's instances.
   * Specify the type of the target RT-Components for destroy by \<_Delete\>.
   *
   * @param rtc The target RT-Component's instances for destruction
   *
   * @endif
   */
  template <class _Delete>
  void Delete(RTObject_impl* rtc)
  {
    delete rtc;
  }
  
  /*!
   * @if jp
   *
   * @class FactoryBase
   * @brief FactoryBase ���쥯�饹
   * 
   * ����ݡ��ͥ�ȥե����ȥ�δ��쥯�饹��
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class FactoryBase
   * @brief FactoryBase base class
   *
   * This is a base class for RT-Component factory.
   *
   * @since 0.2.0
   *
   * @endif
   */
  class FactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     *
     * @param profile ����ݡ��ͥ�ȤΥץ�ե�����
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor.
     *
     * @param profile Component profile
     *
     * @endif
     */
    FactoryBase(const coil::Properties& profile);
    
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
    virtual ~FactoryBase(void);
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�Ȥ�����
     *
     * RT-Component �Υ��󥹥��󥹤��������뤿��ν�貾�۴ؿ���
     *
     * @param mgr �ޥ͡����㥪�֥�������
     *
     * @return ������������ݡ��ͥ��
     *
     * @else
     *
     * @brief Create components
     *
     * Pure virtual function to create RT-Component's instances
     *
     * @param mgr Manager object
     *
     * @return Created RT-Components
     *
     * @endif
     */
    virtual RTObject_impl* create(Manager* mgr) = 0;
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�Ȥ��˴�
     *
     * RT-Component �Υ��󥹥��󥹤��˴����뤿��ν�貾�۴ؿ���
     *
     * @param comp �˴��о� RT����ݡ��ͥ��
     *
     * @else
     *
     * @brief Destroy components
     *
     * Pure virtual function to destroy RT-Component's instances
     *
     * @param comp The target RT-Component for destruction
     *
     * @endif
     */
    virtual void destroy(RTObject_impl* comp) = 0;
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�ȥץ�ե�����μ���
     *
     * ����ݡ��ͥ�ȤΥץ�ե�������������
     *
     * @return ����ݡ��ͥ�ȤΥץ�ե�����
     *
     * @else
     *
     * @brief Get the component profile
     *
     * Get the component profile.
     *
     * @return The component profile
     *
     * @endif
     */
    virtual coil::Properties& profile();
    
    /*!
     * @if jp
     *
     * @brief ���ߤΥ��󥹥��󥹿��μ���
     *
     * ����ݡ��ͥ�Ȥθ��ߤΥ��󥹥��󥹿���������롣
     *
     * @return ����ݡ��ͥ�ȤΥ��󥹥��󥹿�
     *
     * @else
     *
     * @brief Get the number of current instances
     *
     * Get the number of current RT-Component's instances.
     *
     * @return Number of RT-Component's instances
     *
     * @endif
     */
    virtual int number();
    
  protected:
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȤΥץ�ե�����
     * @else
     * @brief Component profile
     * @endif
     */
    coil::Properties m_Profile;
    
    /*!
     * @if jp
     * @brief ���ߤΥ��󥹥��󥹿�
     * @else
     * @brief Number of current RT-Component's instances.
     * @endif
     */
    int m_Number;
  };
  
  /*!
   * @if jp
   * @class FactoryCXX
   * @brief FactoryCXX ���饹
   * 
   * C++�ѥ���ݡ��ͥ�ȥե����ȥꥯ�饹��
   *
   * @since 0.2.0
   *
   *
   * @else
   *
   * @class FactoryCXX
   * @brief FactoryCXX class
   *
   * RT-Component factory class for C++.
   *
   * @since 0.2.0
   *
   * @endif
   */
  class FactoryCXX
    : public FactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     * �ץ�ե����롢�����ؿ��ؤΥݥ��󥿡��˴��ؿ��ؤΥݥ��󥿡�
     * ����ݡ��ͥ����������̿̾�ݥꥷ��������˼�ꡢ
     * C++ �Ǽ������줿����ݡ��ͥ�ȤΥե����ȥꥯ�饹���������롣
     *
     * @param profile ����ݡ��ͥ�ȤΥץ�ե�����
     * @param new_func ����ݡ��ͥ�Ȥ������ؿ��ؤΥݥ���
     * @param delete_func ����ݡ��ͥ�Ȥ��˴��ؿ��ؤΥݥ���
     * @param policy ����ݡ��ͥ����������̿̾�ݥꥷ��
     * (�ǥե������:DefaultNumberingPolicy)
     *
     * @else
     *
     * @brief Constructor.
     *
     * Constructor.
     * Create component factory class with three arguments:
     * component profile, function pointer to object create function and
     * object destroy function.
     *
     * @param profile Component profile
     * @param new_func Pointer to component create function
     * @param delete_func Pointer to component destroy function
     * @param policy The naming policy at component creation
     * (The default value:DefaultNumberingPolicy)
     *
     * @endif
     */
    FactoryCXX(const coil::Properties& profile,
	       RtcNewFunc new_func,
	       RtcDeleteFunc delete_func,
	       NumberingPolicy* policy = new DefaultNumberingPolicy());
    
    virtual ~FactoryCXX()
    {
      delete m_policy;
    }

    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�Ȥ�����
     *
     * RT-Component �Υ��󥹥��󥹤��������롣
     *
     * @param mgr �ޥ͡����㥪�֥�������
     *
     * @return ������������ݡ��ͥ��
     *
     * @else
     *
     * @brief Create RT-Components
     *
     * Create RT-Component's instances
     *
     * @param mgr Manager object
     *
     * @return Created RT-Components
     *
     * @endif
     */
    virtual RTObject_impl* create(Manager* mgr);
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�Ȥ��˴�
     *
     * RT-Component �Υ��󥹥��󥹤��˴����롣
     *
     * @param comp �˴��о� RT-Component
     *
     * @else
     *
     * @brief Destroy RT-Components
     *
     * Destroy RT-Component's instances
     *
     * @param comp The target RT-Component for destruction
     *
     * @endif
     */
    virtual void destroy(RTObject_impl* comp);
    
  protected:
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȥ��֥������������ؿ��ؤΥݥ���
     * @else
     * @brief The pointer to component object create function
     * @endif
     */
    RtcNewFunc m_New;
    
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȥ��֥��������˴��ؿ��ؤΥݥ���
     * @else
     * @brief The pointer to component object destroy function
     * @endif
     */
    RtcDeleteFunc m_Delete;
    
    /*!
     * @if jp
     * @brief ����ݡ��ͥ����������̿̾�ݥꥷ��
     * @else
     * @brief The naming policy on creating the components
     * @endif
     */
    NumberingPolicy* m_policy;
  };
};
#endif // RTC_FACTORY_H
