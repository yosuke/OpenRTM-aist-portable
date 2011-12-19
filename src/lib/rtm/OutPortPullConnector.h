// -*- C++ -*-
/*!
 * @file OutPortPullConnector.h
 * @brief OutPortPull type connector class
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

#ifndef RTC_OUTPORTPULLCONNECTOR_H
#define RTC_OUTPORTPULLCONNECTOR_H

#include <rtm/OutPortConnector.h>
#include <rtm/ConnectorListener.h>

namespace RTC
{
  class OutPortProvider;

  /*!
   * @if jp
   * @class OutPortPullConnector
   * @brief OutPortPullConnector ���饹
   *
   * OutPort �� pull ���ǡ����ե��Τ���� Connector ���饹�����Υ���
   * �������Ȥϡ���³���� dataflow_type �� pull �����ꤵ�줿��硢
   * OutPort �ˤ�ä���������ͭ���졢InPortPullConnector ���Фˤʤäơ�
   * �ǡ����ݡ��Ȥ� pull ���Υǡ����ե���¸����롣��Ĥ���³���Ф��ơ�
   * ��ĤΥǡ������ȥ꡼����󶡤���ͣ��� Connector ���б����롣
   * Connector �� ��³������������� UUID ������ ID �ˤ����̤���롣
   *
   * OutPortPullConnector �ϰʲ��λ��ĤΥ��֥������Ȥ��ͭ���������롣
   *
   * - InPortConsumer
   * - Buffer
   *
   * OutPort �˽񤭹��ޤ줿�ǡ����� OutPortPullConnector::write() ����
   * ���� Buffer �˽񤭹��ޤ�롣InPortPullConnector ��
   * OutPortPullConnector ����ǡ������ɤ߽Ф����Ȥ� InPort �˥ǡ�����
   * ž������롣
   *
   * @since 1.0.0
   *
   * @else
   * @class OutPortPullConnector
   * @brief OutPortPullConnector class
   *
   * Connector class of OutPort for pull type dataflow. When "pull" is
   * specified as dataflow_type at the time of establishing
   * connection, this object is generated and owned by the OutPort.
   * This connector and InPortPullConnector make a pair and realize
   * pull type dataflow of data ports. One connector corresponds to
   * one connection which provides a data stream. Connector is
   * distinguished by ID of the UUID that is generated at establishing
   * connection.
   *
   * OutPortPullConnector owns and manages the following objects.
   *
   * - InPortConsumer
   * - Buffer
   *
   * Data written into the OutPort is passed to
   * OutPortPullConnector::write(), and it is written into the buffer.
   * By reading data from OutPortPullConnector to InPortPullConnector,
   * data transfer is realized.
   *
   * @since 1.0.0
   *
   * @endif
   */
  class OutPortPullConnector
    : public OutPortConnector
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * OutPortPullConnector �Υ��󥹥ȥ饯���ϥ��֥��������������˲���
     * ������ˤȤ롣ConnectorInfo ����³�����ޤߡ����ξ���˽����Х�
     * �ե������������롣OutPort ���󥿡��ե������Υץ�Х������֥�����
     * �ȤؤΥݥ��󥿤��ꡢ��ͭ������ĤΤǡ�OutPortPullConnector ��
     * OutPortProvider �β�����Ǥ����ġ��Ƽ磻�٥�Ȥ��Ф��륳����Х�
     * ���������󶡤��� ConnectorListeners �������Ŭ�ڤʥ����ߥ󥰤ǥ���
     * ��Хå���ƤӽФ����ǡ����Хåե����⤷ OutPortBase �����󶡤�
     * �����Ϥ��Υݥ��󥿤��롣
     *
     * @param info ConnectorInfo
     * @param provider OutPortProvider
     * @param listeners ConnectorListeners ���Υꥹ�ʥ��֥������ȥꥹ��
     * @param buffer CdrBufferBase ���ΥХåե�
     *
     * @else
     * @brief Constructor
     *
     * OutPortPullConnector's constructor is given the following
     * arguments.  According to ConnectorInfo which includes
     * connection information, a buffer is created.  It is also given
     * a pointer to the provider object for the OutPort interface.
     * The owner-ship of the pointer is owned by this
     * OutPortPullConnector, it has responsibility to destruct the
     * OutPortProvider.  OutPortPullConnector also has
     * ConnectorListeners to provide event callback mechanisms, and
     * they would be called at the proper timing.  If data buffer is
     * given by OutPortBase, the pointer to the buffer is also given
     * as arguments.
     *
     * @param info ConnectorInfo
     * @param provider OutPortProvider
     * @param listeners ConnectorListeners type lsitener object list
     * @param buffer CdrBufferBase type buffer
     *
     * @endif
     */
    OutPortPullConnector(ConnectorInfo info,
                         OutPortProvider* provider,
                         ConnectorListeners& listeners,
                         CdrBufferBase* buffer = 0);

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * disconnect() ���ƤФ졢provider, buffer �����Ρ��������롣
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
    virtual ~OutPortPullConnector();

    /*!
     * @if jp
     * @brief �ǡ����ν񤭹���
     *
     * Publisher���Ф��ƥǡ�����񤭹��ߡ�����ˤ���б�����InPort��
     * �ǡ�����ž������롣
     *
     * @else
     *
     * @brief Writing data
     *
     * This operation writes data into publisher and then the data
     * will be transferred to correspondent InPort.
     *
     * @endif
     */
    virtual ReturnCode write(const cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief ��³���
     *
     * consumer, publisher, buffer �����Ρ��������롣
     *
     * @else
     *
     * @brief disconnect
     *
     * This operation destruct and delete the consumer, the publisher
     * and the buffer.
     *
     * @endif
     */
    virtual ReturnCode disconnect();

    /*!
     * @if jp
     * @brief Buffer ���������
     *
     * Connector ���ݻ����Ƥ��� Buffer ���֤�
     *
     * @else
     * @brief Getting Buffer
     *
     * This operation returns this connector's buffer
     *
     * @endif
     */
    virtual CdrBufferBase* getBuffer();

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

    /*!
     * @if jp
     * @brief Buffer������
     * @else
     * @brief create buffer
     * @endif
     */
    CdrBufferBase* createBuffer(ConnectorInfo& info);

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

  protected:

    /*!
     * @if jp
     * @brief OutPortProvider �ؤΥݥ���
     * @else
     * @brief the pointer to the OutPortProvider
     * @endif
     */
    OutPortProvider* m_provider;

    /*!
     * @if jp
     * @brief ConnectorListenrs �ؤλ���
     * @else
     * @brief A reference to a ConnectorListener
     * @endif
     */
    ConnectorListeners& m_listeners;

    /*!
     * @if jp
     * @brief Buffer �ؤΥݥ���
     * @else
     * @brief the pointer to the buffer
     * @endif
     */
    CdrBufferBase* m_buffer;
  };
}; // namespace RTC

#endif  // RTC_PULL_CONNECTOR_H
