// -*- C++ -*-
/*!
 * @file  OutPortCorbaCdrConsumer.h
 * @brief OutPortCorbaCdrConsumer class
 * @date  $Date: 2008-01-13 10:28:27 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009-2010
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

#ifndef RTC_OUTPORTCORBACDRCONSUMER_H
#define RTC_OUTPORTCORBACDRCONSUMER_H

#include <rtm/idl/DataPortSkel.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/OutPortConsumer.h>
#include <rtm/ConnectorListener.h>
#include <rtm/ConnectorBase.h>

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortCorbaCdrConsumer
   * @brief OutPortCorbaCdrConsumer ���饹
   *
   * OutPortConsumer 
   *
   * �ǡ���ž���� CORBA �� OpenRTM::OutPortCdr ���󥿡��ե����������Ѥ�
   * ����pull ���ǡ����ե�����¸����� OutPort ���󥷥塼�ޥ��饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class OutPortCorbaCdrConsumer
   * @brief OutPortCorbaCdrConsumer class
   *
   * The OutPort consumer class which uses the OpenRTM::OutPortCdr
   * interface in CORBA for data transfer and realizes a pull-type
   * dataflow.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class OutPortCorbaCdrConsumer
    : public OutPortConsumer,
      public CorbaConsumer< ::OpenRTM::OutPortCdr >
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    OutPortCorbaCdrConsumer();

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
    virtual ~OutPortCorbaCdrConsumer(void); 

    /*!
     * @if jp
     * @brief ��������
     *
     * OutPortConsumer�γƼ������Ԥ����������饹�Ǥϡ�Ϳ����줿
     * Properties����ɬ�פʾ����������ƳƼ������Ԥ������� init() ��
     * ���ϡ�OutPortProvider����ľ�太��ӡ���³���ˤ��줾��ƤФ���
     * ǽ�������롣�������äơ����δؿ���ʣ����ƤФ�뤳�Ȥ����ꤷ�Ƶ�
     * �Ҥ����٤��Ǥ��롣
     * 
     * @param prop �������
     *
     * @else
     *
     * @brief Initializing configuration
     *
     * This operation would be called to configure in initialization.
     * In the concrete class, configuration should be performed
     * getting appropriate information from the given Properties data.
     * This function might be called right after instantiation and
     * connection sequence respectivly.  Therefore, this function
     * should be implemented assuming multiple call.
     *
     * @param prop Configuration information
     *
     * @endif
     */
    virtual void init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief �Хåե��򥻥åȤ���
     *
     * OutPortConsumer���ǡ�������Ф��Хåե��򥻥åȤ��롣
     * ���Ǥ˥��åȤ��줿�Хåե��������硢�����ΥХåե��ؤ�
     * �ݥ��󥿤��Ф��ƾ�񤭤���롣
     * OutPortProvider�ϥХåե��ν�ͭ�����ꤷ�Ƥ��ʤ��Τǡ�
     * �Хåե��κ���ϥ桼������Ǥ�ǹԤ�ʤ���Фʤ�ʤ���
     *
     * @param buffer OutPortProvider���ǡ�������Ф��Хåե��ؤΥݥ���
     *
     * @else
     * @brief Setting outside buffer's pointer
     *
     * A pointer to a buffer from which OutPortProvider retrieve data.
     * If already buffer is set, previous buffer's pointer will be
     * overwritten by the given pointer to a buffer.  Since
     * OutPortProvider does not assume ownership of the buffer
     * pointer, destructor of the buffer should be done by user.
     * 
     * @param buffer A pointer to a data buffer to be used by OutPortProvider
     *
     * @endif
     */
    virtual void setBuffer(CdrBufferBase* buffer);

    /*!
     * @if jp
     * @brief �ꥹ�ʤ����ꤹ�롣
     *
     * InPort �ϥǡ������������ˤ�����Ƽ磻�٥�Ȥ��Ф�������Υꥹ��
     * ���֥������Ȥ򥳡��뤹�륳����Хå��������󶡤��롣�ܺ٤�
     * ConnectorListener.h �� ConnectorDataListener, ConnectorListener
     * ���򻲾ȤΤ��ȡ�OutPortCorbaCdrProvider �Ǥϡ��ʲ��Υ�����Хå�
     * ���󶡤���롣
     * 
     * - ON_BUFFER_WRITE
     * - ON_BUFFER_FULL
     * - ON_RECEIVED
     * - ON_RECEIVER_FULL 
     * - ON_SENDER_EMPTY
     * - ON_SENDER_TIMEOUT
     * - ON_SENDER_ERROR
     *
     * @param info ��³����
     * @param listeners �ꥹ�ʥ��֥�������
     *
     * @else
     * @brief Set the listener. 
     *
     * OutPort provides callback functionality that calls specific
     * listener objects according to the events in the data publishing
     * process. For details, see documentation of
     * ConnectorDataListener class and ConnectorListener class in
     * ConnectorListener.h. In this OutPortCorbaCdrProvider provides
     * the following callbacks.
     * 
     * - ON_BUFFER_WRITE
     * - ON_BUFFER_FULL
     * - ON_RECEIVED
     * - ON_RECEIVER_FULL 
     * - ON_SENDER_EMPTY
     * - ON_SENDER_TIMEOUT
     * - ON_SENDER_ERROR
     *
     * @param info Connector information
     * @param listeners Listener objects
     *
     * @endif
     */
    virtual void setListener(ConnectorInfo& info,
                             ConnectorListeners* listeners);

    /*!
     * @if jp
     * @brief �ǡ������ɤ߽Ф�
     *
     * ���ꤵ�줿�ǡ������ɤ߽Ф���
     *
     * @param data �ɤ߽Ф����ǡ����������륪�֥�������
     *
     * @return �ǡ����ɤ߽Ф��������(�ɤ߽Ф�����:true���ɤ߽Ф�����:false)
     *
     * @else
     * @brief Read data
     *
     * Read set data
     *
     * @param data Object to receive the read data
     *
     * @return Read result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual ReturnCode get(cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief �ǡ����������Τؤ���Ͽ
     *
     * ���ꤵ�줿�ץ�ѥƥ��˴�Ť��ơ��ǡ����������Τμ���������Ͽ���롣
     *
     * @param properties ��Ͽ����
     *
     * @return ��Ͽ�������(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     * @brief Subscribe the data receive notification
     *
     * Subscribe the data receive notification based on specified property
     * information
     *
     * @param properties Subscription information
     *
     * @return Subscription result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool subscribeInterface(const SDOPackage::NVList& properties);
    
    /*!
     * @if jp
     * @brief �ǡ����������Τ������Ͽ���
     *
     * �ǡ����������Τμ�����꤫����Ͽ�������롣
     *
     * @param properties ��Ͽ�������
     *
     * @else
     * @brief Unsubscribe the data receive notification
     *
     * Unsubscribe the data receive notification.
     *
     * @param properties Unsubscription information
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties);
    
  private:
    /*!
     * @if jp
     * @brief �꥿���󥳡����Ѵ� (DataPortStatus -> BufferStatus)
     * @else
     * @brief Return codes conversion
     * @endif
     */
    OutPortConsumer::ReturnCode convertReturn(::OpenRTM::PortStatus status,
                                              const cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE �Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_WRITE event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWrite(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_FULL �Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_FULL event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_FULL].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVED �Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVED event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceived(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVED].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_FULL �Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVER_FULL event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_FULL].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_SENDER_EMPTY�Υꥹ�ʤ����Τ��롣 
     * @else
     * @brief Notify an ON_SENDER_EMPTY event to listeners
     * @endif
     */
    inline void onSenderEmpty()
    {
      m_listeners->
        connector_[ON_SENDER_EMPTY].notify(m_profile);
    }

    /*!
     * @if jp
     * @brief ON_SENDER_TIMEOUT �Υꥹ�ʤ����Τ��롣 
     * @else
     * @brief Notify an ON_SENDER_TIMEOUT event to listeners
     * @endif
     */
    inline void onSenderTimeout()
    {
      m_listeners->
        connector_[ON_SENDER_TIMEOUT].notify(m_profile);
    }

    /*!
     * @if jp
     * @brief ON_SENDER_ERROR�Υꥹ�ʤ����Τ��롣 
     * @else
     * @Brief Notify an ON_SENDER_ERROR event to listeners
     * @endif
     */
    inline void onSenderError()
    {
      m_listeners->
        connector_[ON_SENDER_ERROR].notify(m_profile);
    }

    //    RTC::OutPortCdr_var m_outport;
    CdrBufferBase* m_buffer;
    ConnectorListeners* m_listeners;
    ConnectorInfo m_profile;
  };
};     // namespace RTC

extern "C"
{
  /*!
   * @if jp
   * @brief �⥸�塼�������ؿ�
   *
   * OutPortCorbaCdrConsumer �Υե����ȥ����Ͽ���������ؿ���
   *
   * @else
   * @brief Module initialization
   *
   * This initialization function registers OutPortCorbaCdrConsumer's factory.
   *
   * @endif
   */
  void OutPortCorbaCdrConsumerInit(void);
};

#endif // RTC_OUTPORTCORBACDRCONSUMER_H
