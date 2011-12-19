// -*- C++ -*-
/*!
 * @file InPortPushConnector.h
 * @brief Push type connector class
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

#ifndef RTC_INPORTPUSHCONNECTOR_H
#define RTC_INPORTPUSHCONNECTOR_H

#include <rtm/InPortConnector.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherBase.h>

namespace RTC
{
  class InPortProvider;

  /*!
   * @if jp
   * @class InPortPushConnector
   * @brief InPortPushConnector ���饹
   *
   * InPort �� push ���ǡ����ե��Τ���� Connector ���饹�����Υ���
   * �������Ȥϡ���³���� dataflow_type �� push �����ꤵ�줿��硢
   * InPort �ˤ�ä���������ͭ���졢OutPortPushConnector ���Фˤʤäơ�
   * �ǡ����ݡ��Ȥ� push ���Υǡ����ե���¸����롣��Ĥ���³���Ф��ơ�
   * ��ĤΥǡ������ȥ꡼����󶡤���ͣ��� Connector ���б����롣
   * Connector �� ��³������������� UUID ������ ID �ˤ����̤���롣
   *
   * InPortPushConnector �ϰʲ��λ��ĤΥ��֥������Ȥ��ͭ���������롣
   *
   * - InPortProvider
   * - Buffer
   *
   * OutPort �˽񤭹��ޤ줿�ǡ����ϡ�OutPortConnector �ˤ�ä�
   * InPortProvider::put() �˥ǡ������Ϥ���롣�񤭹��ޤ줿�ǡ�����
   * Connector ��� Buffer �˥ǡ������񤭹��ޤ�롣
   *
   * @since 1.0.0
   *
   * @else
   * @class InPortPushConnector
   * @brief InPortPushConnector class
   *
   * Connector class of InPort for push type dataflow.  When "push"
   * is specified as dataflow_type at the time of establishing
   * connection, this object is generated and owned by the InPort.
   * This connector and OutPortPushConnector make a pair and realize
   * push type dataflow of data ports.  One connector corresponds to
   * one connection which provides a data stream.  Connector is
   * distinguished by ID of the UUID that is generated at establishing
   * connection.
   *
   * InPortPushConnector owns and manages the following objects.
   *
   * - OutPortConsumer
   * - Buffer
   *
   * Data written into the OutPort are passed to the
   * InPortProvider::put() by OutPortConnector.  The data is written
   * into the buffer in the connector.
   *
   * @since 1.0.0
   *
   * @endif
   */
  class InPortPushConnector
    : public InPortConnector
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * InPortPushConnector �Υ��󥹥ȥ饯���ϥ��֥��������������˲�����
     * �����ˤȤ롣ConnectorInfo ����³�����ޤߡ����ξ���˽����Хåե�
     * �����������롣InPort ���󥿡��ե������Υץ�Х������֥������Ȥ�
     * �Υݥ��󥿤��ꡢ��ͭ������ĤΤǡ�InPortPushConnector ��
     * InPortProvider �β�����Ǥ����ġ��Ƽ磻�٥�Ȥ��Ф��륳����Х�
     * ���������󶡤��� ConnectorListeners �������Ŭ�ڤʥ����ߥ󥰤ǥ���
     * ��Хå���ƤӽФ����ǡ����Хåե����⤷ InPortBase �����󶡤���
     * ����Ϥ��Υݥ��󥿤��롣
     *
     * @param info ConnectorInfo
     * @param provider InPortProvider
     * @param listeners ConnectorListeners ���Υꥹ�ʥ��֥������ȥꥹ��
     * @param buffer CdrBufferBase ���ΥХåե�
     *
     * @elsek
     * @brief Constructor
     *
     * InPortPushConnector's constructor is given the following
     * arguments.  According to ConnectorInfo which includes
     * connection information, a buffer is created.
     * It is also given a pointer to the provider object for the
     * InPort interface.  The owner-ship of the pointer is owned by
     * this InPortPushConnector, it has responsibility to destruct
     * the InPortProvider.  InPortPushConnector also has
     * ConnectorListeners to provide event callback mechanisms, and
     * they would be called at the proper timing.  If data buffer is
     * given by InPortBase, the pointer to the buffer is also given
     * as arguments.
     *
     * @param info ConnectorInfo
     * @param provider InPortProvider
     * @param listeners ConnectorListeners type lsitener object list
     * @param buffer CdrBufferBase type buffer
     *
     * @endif
     */
    InPortPushConnector(ConnectorInfo info,
                        InPortProvider* provider,
                        ConnectorListeners& listeners,
                        CdrBufferBase* buffer = 0);

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * disconnect() ���ƤФ졢consumer, publisher, buffer �����Ρ��������롣
     *
     * @else
     *
     * @brief Destructor
     *
     * This operation calls disconnect(), which destructs and deletes
     * the consumer, the publisher and the buffer.
     *
     * @endif
     */
    virtual ~InPortPushConnector();

    /*!
     * @if jp
     * @brief �ǡ������ɤ߽Ф�
     *
     * �Хåե�����ǡ������ɤ߽Ф���������ɤ߽Ф�����硢����ͤ�
     * PORT_OK �Ȥʤꡢdata ���ɤ߽Ф��줿�ǡ�������Ǽ����롣����ʳ�
     * �ξ��ˤϡ����顼�ͤȤ��� BUFFER_EMPTY, TIMEOUT,
     * PRECONDITION_NOT_MET, PORT_ERROR ���֤���롣
     *
     * @return PORT_OK              ���ｪλ
     *         BUFFER_EMPTY         �Хåե��϶��Ǥ���
     *         TIMEOUT              �����ॢ���Ȥ���
     *         PRECONDITION_NOT_MET ���������������ʤ�
     *         PORT_ERROR           ����¾�Υ��顼
     *
     * @else
     *
     * @brief Reading data
     *
     * This function reads data from the buffer. If data is read
     * properly, this function will return PORT_OK return code. Except
     * normal return, BUFFER_EMPTY, TIMEOUT, PRECONDITION_NOT_MET and
     * PORT_ERROR will be returned as error codes.
     *  
     * @return PORT_OK              Normal return
     *         BUFFER_EMPTY         Buffer empty
     *         TIMEOUT              Timeout
     *         PRECONDITION_NOT_MET Preconditin not met
     *         PORT_ERROR           Other error
     *
     * @endif
     */
    virtual ReturnCode read(cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief ��³���
     *
     * consumer, publisher, buffer �����Ρ��������롣
     *
     * @return PORT_OK
     *
     * @else
     *
     * @brief disconnect
     *
     * This operation destruct and delete the consumer, the publisher
     * and the buffer.
     *
     * @return PORT_OK
     *
     * @endif
     */
    virtual ReturnCode disconnect();

    /*!
     * @if jp
     * @brief �����ƥ��ֲ�
     *
     * ���Υ��ͥ����򥢥��ƥ��ֲ�����
     *
     * @else
     *
     * @brief Connector activation
     *
     * This operation activates this connector
     *
     * @endif
     */
    virtual void activate(){}; // do nothing

    /*!
     * @if jp
     * @brief �󥢥��ƥ��ֲ�
     *
     * ���Υ��ͥ������󥢥��ƥ��ֲ�����
     *
     * @else
     *
     * @brief Connector deactivation
     *
     * This operation deactivates this connector
     *
     * @endif
     */
    virtual void deactivate(){}; // do nothing

  protected:
    /*!
     * @if jp
     * @brief Buffer������
     *
     * Ϳ����줿��³����˴�Ť��Хåե����������롣
     *
     * @param info ��³����
     * @return �Хåե��ؤΥݥ���
     *
     * @else
     * @brief create buffer
     *
     * This function creates a buffer based on given information.
     *
     * @param info Connector information
     * @return The poitner to the buffer
     *
     * @endif
     */
    virtual CdrBufferBase* createBuffer(ConnectorInfo& info);

    /*!
     * @if jp
     * @brief ��³��Ω���˥�����Хå���Ƥ�
     * @else
     * @brief Invoke callback when connection is established
     * @endif
     */
    void onConnect();

    /*!
     * @if jp
     * @brief ��³���ǻ��˥�����Хå���Ƥ�
     * @else
     * @brief Invoke callback when connection is destroied
     * @endif
     */
    void onDisconnect();

  private:
    /*!
     * @if jp
     * @brief InPortConsumer �ؤΥݥ���
     * @else
     * @brief the pointer to the InPortConsumer
     * @endif
     */
    InPortProvider* m_provider;

    /*!
     * @if jp
     * @brief ConnectorListenrs �ؤλ���
     * @else
     * @brief A reference to a ConnectorListener
     * @endif
     */
    ConnectorListeners& m_listeners;

    bool m_deleteBuffer;
  };
}; // namespace RTC

#endif  // RTC_PUSH_CONNECTOR_H
