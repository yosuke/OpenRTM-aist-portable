// -*- C++ -*-
/*!
 * @file ExecutionContextBase.h
 * @brief ExecutionContext base class
 * @date $Date: 2008-01-14 07:48:55 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ExecutionContextBase.h 1727 2010-01-21 01:50:30Z fsi-katami $
 *
 */

#ifndef RTC_EXECUTIONCONTEXTBASE_H
#define RTC_EXECUTIONCONTEXTBASE_H

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>
#include <rtm/Factory.h>

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class ExecutionContextBase
   * @brief ExecutionContext�Ѵ��쥯�饹
   *
   * ExecutionContext�δ��쥯�饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class ExecutionContextBase
   * @brief A base class for ExecutionContext
   *
   * A base class of ExecutionContext.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ExecutionContextBase
    : public virtual POA_OpenRTM::ExtTrigExecutionContextService,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief ���ۥǥ��ȥ饯��
     *
     * ���ۥǥ��ȥ饯��
     *
     * @else
     * @brief Virtual Destructor
     *
     * Virtual Destructor
     *
     * @endif
     */
    virtual ~ExecutionContextBase(void){};
    
    /*!
     * @if jp
     * @brief ExecutionContext�ν�����ʤ��
     *
     * ExecutionContext�ν����򣱼���ʬ�ʤ�롣
     *
     * @else
     * @brief Proceed with tick of ExecutionContext
     *
     * Proceed with tick of ExecutionContext for one period.
     *
     * @endif
     */
    virtual void tick()
      throw (CORBA::SystemException)
    {};

    /*!
     * @if jp
     * @brief ����ݡ��ͥ�Ȥ�Х���ɤ��롣
     *
     * ����ݡ��ͥ�Ȥ�Х���ɤ��롣
     *
     * @else
     * @brief Bind the component.
     *
     * Bind the component.
     *
     * @endif
     */
    virtual RTC::ReturnCode_t bindComponent(RTObject_impl* rtc) = 0;

    /*!
     * @if jp
     * @brief ���֥������ȤΥ�ե���󥹤�������롣
     *
     * ���֥������ȤΥ�ե���󥹤�������롣
     *
     * @else
     * @brief Get the reference of the object. 
     *
     * Get the reference of the object.
     *
     * @endif
     */
    virtual RTC::ExecutionContextService_ptr getObjRef() = 0;
  };  // class ExecutionContextBase
};  // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_EXECUTIONCONTEXTBASE_H
