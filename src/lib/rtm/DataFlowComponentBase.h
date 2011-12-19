// -*- C++ -*-
/*!
 * @file DataFlowComponentBase.h
 * @brief DataFlowParticipant RT-Component base class
 * @date $Date: 2007-12-31 03:08:02 $
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
 * $Id: DataFlowComponentBase.h 1569 2009-11-12 14:36:47Z n-ando $
 *
 */

#ifndef RTC_DATAFLOWCOMPONENTBASE_H
#define RTC_DATAFLOWCOMPONENTBASE_H

#include <rtm/idl/RTCSkel.h>
#include <rtm/RTObject.h>
#include <rtm/PeriodicExecutionContext.h>

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
   * @class DataFlowComponentBase
   * @brief DataFlowComponentBase ���饹
   *
   * �ǡ����ե���RTComponent�δ��쥯�饹��
   * �Ƽ�ǡ����ե���RTComponent�����������ϡ��ܥ��饹��Ѿ�������Ǽ���
   * ���롣
   *
   * @since 0.4.0
   *
   * @else
   * @class DataFlowComponentBase
   * @brief DataFlowComponentBase class
   *
   * This is a base class of the data flow type RT-Component.
   * Inherit this class when implementing various data flow type RT-Components.
   *
   * @since 0.4.0
   *
   * @endif
   */
  
  class DataFlowComponentBase
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
    DataFlowComponentBase(Manager* manager);
    
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
    virtual ~DataFlowComponentBase(void);
    
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
    void init();
    
  private:
    //    OpenRTM::DataFlowComponent_var m_ref;
    //    PeriodicExecutionContext* m_pec;
    //    ExecutionContextService_var m_ecref;
  };
}; // namespace RTC
#endif // RTC_DATAFLOWCOMPONENTBASE_H
