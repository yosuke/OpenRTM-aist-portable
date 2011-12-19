// -*- C++ -*-
/*!
 * @file  PublisherPeriodic.h
 * @brief PublisherPeriodic class
 * @date  $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2010
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PublisherPeriodic.h 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#ifndef RTC_PUBLISHERPERIODIC_H
#define RTC_PUBLISHERPERIODIC_H

#include <coil/Task.h>
#include <coil/Mutex.h>
#include <coil/Condition.h>
#include <coil/PeriodicTask.h>

#include <rtm/RTC.h>
#include <rtm/PublisherBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/SystemLogger.h>
#include <rtm/ConnectorBase.h>
#include <rtm/ConnectorListener.h>

namespace coil
{
  class Properties;
};

namespace RTC
{
  class InPortConsumer;
  /*!
   * @if jp
   * @class PublisherPeriodic
   * @brief PublisherPeriodic ���饹
   *
   * ����Ū�˥ǡ������������뤿��� Publisher ���饹�����Υ��饹�ϡ���
   * �� Connector ��ˤ��äơ��Хåե�����ӥ��󥷥塼�ޤ˴�Ϣ�դ����
   * �롣����������Ȥ˥Хåե�����ǡ�������Ф����󥷥塼�ޤ��Ф���
   * �ǡ��������Ф��롣
   *
   * @else
   * @class PublisherPeriodic
   * @brief PublisherPeriodic class
   *
   * Publisher for periodic data transmitting. Usually this class
   * object exists in a Connector object, and it is associated with a
   * buffer and a consumer. This publisher periodically gets data from
   * the buffer and publish it into the consumer.
   *
   * @endif
   */
  class PublisherPeriodic
    : public PublisherBase
  {
  public: 
    typedef coil::Mutex Mutex;
    typedef coil::Condition<Mutex> Condition;
    typedef coil::Guard<coil::Mutex> Guard;
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     *
     * @endif
     */
    PublisherPeriodic(void);
    
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
    virtual ~PublisherPeriodic(void);
    
    /*!
     * @if jp
     * @brief �����
     *
     * ���Υ��饹�Υ��֥������Ȥ���Ѥ���Τ���Ω����ɬ�����δؿ���Ƥ�
     * �Ф�ɬ�פ����롣�����ˤϡ����Υ��֥������ȤγƼ���������ޤ�
     * Properties ��Ϳ���롣���ʤ��Ȥ⡢���н����θƤӽФ�������ñ��
     * Hz �ο��ͤȤ��� Property���֥������Ȥ� publisher.push_rate �򥭡�
     * �Ȥ������Ǥ����ꤹ��ɬ�פ����롣���� 5ms ���ʤ����200Hz�ξ�硢
     * 200.0 �����ꤹ�롣 dataport.publisher.push_rate ��̤����ξ�硢
     * false ���֤���롣�ǡ�����ץå��夹��ݤΥݥꥷ���Ȥ���
     * publisher.push_policy �򥭡��Ȥ����ͤˡ�all, fifo, skip, new ��
     * �����줫��Ϳ���뤳�Ȥ��Ǥ��롣
     * 
     * �ʲ��Υ��ץ�����Ϳ���뤳�Ȥ��Ǥ��롣
     * 
     * - publisher.thread_type: ����åɤΥ����� (ʸ���󡢥ǥե����: default)
     * - publisher.push_rate: Publisher���������� (����)
     * - publisher.push_policy: Push�ݥꥷ�� (all, fifo, skip, new)
     * - publisher.skip_count: �嵭�ݥꥷ�� skip �ΤȤ��Υ����å׿�
     * - measurement.exec_time: �������¹Ի��ַ�¬ (enable/disable)
     * - measurement.exec_count: �������ؿ��¹Ի��ַ�¬���� (����, ���)
     * - measurement.period_time: �������������ַ�¬ (enable/disable)
     * - measurement.period_count: �������������ַ�¬���� (����, ���)
     *
     * @param property ��Publisher�ζ�ư�����������ꤷ��Property���֥�������
     * @return ReturnCode PORT_OK ���ｪλ
     *                    INVALID_ARGS Properties ���������ͤ�ޤ�
     *
     * @else
     * @brief Initialization
     *
     * This function have to be called before using this class object.
     * Properties object that includes certain configuration
     * information should be given as an argument.  At least, a
     * numerical value of unit of Hz with the key of
     * "dataport.publisher.push_rate" has to be set to the Properties
     * object of argument.  The value is the invocation cycle of data
     * sending process.  In case of 5 ms period or 200 Hz, the value
     * should be set as 200.0. False will be returned, if there is no
     * value with the key of "dataport.publisher.push_rate".
     *
     * The following options are available.
     * 
     * - publisher.thread_type: Thread type (string, default: default)
     * - publisher.push_rate: Publisher sending period (numberical)
     * - publisher.push_policy: Push policy (all, fifo, skip, new)
     * - publisher.skip_count: The number of skip count in the "skip" policy
     * - measurement.exec_time: Task execution time measurement (enable/disable)
     * - measurement.exec_count: Task execution time measurement count
     *                           (numerical, number of times)
     * - measurement.period_time: Task period time measurement (enable/disable)
     * - measurement.period_count: Task period time measurement count 
     *                             (number, count)
     *
     * @param property Property objects that includes the control information
     *                 of this Publisher
     * @return ReturnCode PORT_OK normal return
     *                    INVALID_ARGS Properties with invalid values.
     * @endif
     */
    virtual ReturnCode init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief InPort���󥷥塼�ޤΥ��å�
     *
     * ���δؿ��Ǥϡ����� Publisher �˴�Ϣ�դ����륳�󥷥塼�ޤ򥻥åȤ��롣
     * ���󥷥塼�ޥ��֥������Ȥ��̥�ݥ��󥿤ξ�硢INVALID_ARGS���֤���롣
     * ����ʳ��ξ��ϡ�PORT_OK ���֤���롣
     *
     * @param consumer Consumer �ؤΥݥ���
     * @return ReturnCode PORT_OK ���ｪλ
     *                    INVALID_ARGS �������������ͤ��ޤޤ�Ƥ���
     *
     * @else
     * @brief Store InPort consumer
     *
     * This operation sets a consumer that is associated with this
     * object. If the consumer object is NULL, INVALID_ARGS will be
     * returned.
     *
     * @param consumer A pointer to a consumer object.
     * @return ReturnCode PORT_OK normal return
     *                    INVALID_ARGS given argument has invalid value
     *
     * @endif
     */
    virtual ReturnCode setConsumer(InPortConsumer* consumer);

    /*!
     * @if jp
     * @brief �Хåե��Υ��å�
     *
     * ���δؿ��Ǥϡ����� Publisher �˴�Ϣ�դ�����Хåե��򥻥åȤ��롣
     * �Хåե����֥������Ȥ��̥�ݥ��󥿤ξ�硢INVALID_ARGS���֤���롣
     * ����ʳ��ξ��ϡ�PORT_OK ���֤���롣
     *
     * @param buffer CDR buffer �ؤΥݥ���
     * @return ReturnCode PORT_OK ���ｪλ
     *                    INVALID_ARGS �������������ͤ��ޤޤ�Ƥ���
     *
     * @else
     * @brief Setting buffer pointer
     *
     * This operation sets a buffer that is associated with this
     * object. If the buffer object is NULL, INVALID_ARGS will be
     * returned.
     *
     * @param buffer A pointer to a CDR buffer object.
     * @return ReturnCode PORT_OK normal return
     *                    INVALID_ARGS given argument has invalid value
     *
     * @endif
     */
    virtual ReturnCode setBuffer(CdrBufferBase* buffer);

    /*!
     * @if jp
     * @brief �ꥹ�ʤ����ꤹ�롣
     *
     * Publisher ���Ф��ƥꥹ�ʥ��֥������� ConnectorListeners �����ꤹ�롣
     * �Ƽ�ꥹ�ʥ��֥������Ȥ�ޤ� ConnectorListeners �򥻥åȤ��뤳�Ȥǡ�
     * �Хåե����ɤ߽񤭡��ǡ��������������ˤ����Υꥹ�ʤ򥳡��뤹�롣
     * ConnectorListeners ���֥������Ȥν�ͭ���ϥݡ��Ȥޤ��� RTObject ������
     * Publisher ������� ConnectorListeners �Ϻ������뤳�ȤϤʤ���
     * ConnectorListeners ���̥�ݥ��󥿤ξ�� INVALID_ARGS ���֤���
     *
     * @param info ConnectorProfile ������벽�������֥������� ConnectorInfo
     * @param listeners �ꥹ�ʤ�¿���ݻ����� ConnectorListeners ���֥�������
     * @return PORT_OK      ���ｪλ
     *         INVALID_ARGS �����ʰ���
     * @else
     * @brief Set the listener. 
     *
     * This function sets ConnectorListeners listener object to the
     * Publisher. By setting ConnectorListeners containing various
     * listeners objects, these listeners are called at the time of
     * reading and writing of a buffer, and transmission of data
     * etc. Since the ownership of the ConnectorListeners object is
     * owned by Port or RTObject, the Publisher never deletes the
     * ConnectorListeners object. If the given ConnectorListeners'
     * pointer is NULL, this function returns INVALID_ARGS.
     *
     * @param info ConnectorInfo that is localized object of ConnectorProfile
     * @param listeners ConnectorListeners that holds various listeners
     * @return PORT_OK      Normal return
     *         INVALID_ARGS Invalid arguments
     * @endif
     */
    virtual ReturnCode setListener(ConnectorInfo& info,
                                   ConnectorListeners* listeners);
    /*!
     * @if jp
     * @brief �ǡ�����񤭹���
     *
     * Publisher ���ݻ�����Хåե����Ф��ƥǡ�����񤭹��ࡣ���󥷥塼
     * �ޡ��Хåե����ꥹ������Ŭ�ڤ����ꤵ��Ƥ��ʤ�����Publisher ����
     * �������Ȥ����������������Ƥ��ʤ���硢���δؿ���ƤӽФ��ȥ��顼
     * ������ PRECONDITION_NOT_MET ���֤��졢�Хåե��ؤν񤭹���������
     * ��ϰ��ڹԤ��ʤ���
     *
     * �Хåե��ؤν񤭹��ߤȡ�InPort�ؤΥǡ�������������Ʊ��Ū�˹Ԥ��
     * �뤿�ᡢ���δؿ��ϡ�InPort�ؤΥǡ��������η�̤򼨤���
     * CONNECTION_LOST, BUFFER_FULL �ʤɤΥ꥿���󥳡��ɤ��֤����Ȥ���
     * �롣���ξ�硢�ǡ����ΥХåե��ؤν񤭹��ߤϹԤ��ʤ���
     *
     * �Хåե��ؤν񤭹��ߤ��Ф��ơ��Хåե����ե���֡��Хåե��Υ�
     * �顼���Хåե��ؤν񤭹��ߤ������ॢ���Ȥ�����硢�Хåե��λ���
     * ��郎��������ʤ����ˤϤ��줾�졢���顼������ BUFFER_FULL,
     * BUFFER_ERROR, BUFFER_TIMEOUT, PRECONDITION_NOT_MET ���֤���롣
     *
     * �����ʳ��Υ��顼�ξ�硢PORT_ERROR ���֤���롣
     * 
     *
     * @param data �񤭹���ǡ��� 
     * @param sec �����ॢ���Ȼ���
     * @param nsec �����ॢ���Ȼ���
     *
     * @return PORT_OK             ���ｪλ
     *         PRECONDITION_NO_MET consumer, buffer, listener����Ŭ�ڤ�����
     *                             ����Ƥ��ʤ��������Υ��֥������Ȥλ������
     *                             ���������ʤ���硣
     *         CONNECTION_LOST     ��³�����Ǥ��줿���Ȥ��Τ�����
     *         BUFFER_FULL         �Хåե����ե���֤Ǥ��롣
     *         BUFFER_ERROR        �Хåե��˲��餫�Υ��顼����������硣
     *         NOT_SUPPORTED       ���ݡ��Ȥ���ʤ����Ԥ�줿��
     *         TIMEOUT             �����ॢ���Ȥ�����
     *
     * @else
     * @brief Write data 
     *
     * This function writes data into the buffer associated with this
     * Publisher.  If a Publisher object calls this function, without
     * initializing correctly such as a consumer, a buffer, listeners,
     * etc., error code PRECONDITION_NOT_MET will be returned and no
     * operation of the writing to a buffer etc. will be performed.
     *
     * Since writing into the buffer and sending data to InPort are
     * performed asynchronously, occasionally this function returns
     * return-codes such as CONNECTION_LOST and BUFFER_FULL that
     * indicate the result of sending data to InPort. In this case,
     * writing data into buffer will not be performed.
     *
     * When publisher writes data to the buffer, if the buffer is
     * filled, returns error, is returned with timeout and returns
     * precondition error, error codes BUFFER_FULL, BUFFER_ERROR,
     * BUFFER_TIMEOUT and PRECONDITION_NOT_MET will be returned
     * respectively.
     *
     * In other cases, PROT_ERROR will be returned.
     *
     * @param data Data to be wrote to the buffer
     * @param sec Timeout time in unit seconds
     * @param nsec Timeout time in unit nano-seconds
     * @return PORT_OK             Normal return
     *         PRECONDITION_NO_MET Precondition does not met. A consumer,
     *                             a buffer, listenes are not set properly.
     *         CONNECTION_LOST     detected that the connection has been lost
     *         BUFFER_FULL         The buffer is full status.
     *         BUFFER_ERROR        Some kind of error occurred in the buffer.
     *         NOT_SUPPORTED       Some kind of operation that is not supported
     *                             has been performed.
     *         TIMEOUT             Timeout occurred when writing to the buffer.
     *
     * @endif
     */
    virtual ReturnCode write(const cdrMemoryStream& data,
                             unsigned long sec,
                             unsigned long usec);
    /*!
     * @if jp
     *
     * @brief �����ƥ��ֲ���ǧ
     * 
     * Publisher �ϥǡ����ݡ��Ȥ�Ʊ������ activate/deactivate ����롣
     * activate() / deactivate() �ؿ��ˤ�äơ������ƥ��־��֤��󥢥��ƥ�
     * �־��֤��ڤ��ؤ�롣���δؿ��ˤ�ꡢ���ߥ����ƥ��־��֤����󥢥�
     * �ƥ��־��֤����ǧ���뤳�Ȥ��Ǥ��롣
     *
     * @return ���ֳ�ǧ���(�����ƥ��־���:true���󥢥��ƥ��־���:false)
     *
     * @else
     *
     * @brief If publisher is active state
     * 
     * A Publisher can be activated/deactivated synchronized with the
     * data port.  The active state and the non-active state are made
     * transition by the "activate()" and the "deactivate()" functions
     * respectively. This function confirms if the publisher is in
     * active state.
     *
     * @return Result of state confirmation
     *         (Active state:true, Inactive state:false)
     *
     * @endif
     */
    virtual bool isActive();

    /*!
     * @if jp
     * @brief �����ƥ��ֲ�����
     *
     * Publisher �򥢥��ƥ��ֲ����롣���δؿ���ƤӽФ����Ȥˤ�ꡢ
     * Publisher�����ġ��ǡ������������륹��åɤ�ư��򳫻Ϥ��롣���
     * �����Ԥ��Ƥ��ʤ��ʤɤˤ�ꡢ���������������ʤ���硢���顼����
     * �� PRECONDITION_NOT_MET ���֤���
     *
     * @return PORT_OK ���ｪλ
     *         PRECONDITION_NOT_MET ���������������ʤ�
     *
     * @else
     * @brief activation
     *
     * This function activates the publisher. By calling this
     * function, this publisher starts the thread that pushes data to
     * InPort. If precondition such as initialization process and so
     * on is not met, the error code PRECONDITION_NOT_MET is returned.
     *
     * @return PORT_OK normal return
     *         PRECONDITION_NOT_MET precondition is not met
     *
     * @endif
     */
    virtual ReturnCode activate();

    /*!
     * @if jp
     * @brief �󥢥��ƥ��ֲ�����
     *
     * Publisher ���󥢥��ƥ��ֲ����롣���δؿ���ƤӽФ����Ȥˤ�ꡢ
     * Publisher�����ġ��ǡ������������륹��åɤ�ư�����ߤ��롣���
     * �����Ԥ��Ƥ��ʤ��ʤɤˤ�ꡢ���������������ʤ���硢���顼����
     * �� PRECONDITION_NOT_MET ���֤���
     *
     * @return PORT_OK ���ｪλ
     *         PRECONDITION_NOT_MET ���������������ʤ�
     *
     * @else
     * @brief deactivation
     *
     * This function deactivates the publisher. By calling this
     * function, this publisher stops the thread that pushes data to
     * InPort. If precondition such as initialization process and so
     * on is not met, the error code PRECONDITION_NOT_MET is returned.
     *
     * @return PORT_OK normal return
     *         PRECONDITION_NOT_MET precondition is not met
     *
     * @endif
     */
    virtual ReturnCode deactivate();
    
    /*!
     * @if jp
     * @brief ����åɼ¹Դؿ�
     *
     * coil::PeriodicTask �ˤ������¹Ԥ���륿�����¹Դؿ���
     *
     * @else
     * @brief Thread execution function
     *
     * A task execution function to be executed by coil::PeriodicTask.
     *
     * @endif
     */
    virtual int svc(void);
    
  protected:
    enum Policy
      {
        ALL,
        FIFO,
        SKIP,
        NEW
      };

    /*!
     * @if jp
     * @brief PushPolicy ������
     * @else
     * @brief Setting PushPolicy
     * @endif
     */
    void setPushPolicy(const coil::Properties& prop);

    /*!
     * @if jp
     * @brief Task ������
     * @else
     * @brief Setting Task
     * @endif
     */
    bool createTask(const coil::Properties& prop);

    /*!
     * @brief push "all" policy
     */
    ReturnCode pushAll();

    /*!
     * @brief push "fifo" policy
     */
    ReturnCode pushFifo();

    /*!
     * @brief push "skip" policy
     */
    ReturnCode pushSkip();

    /*!
     * @brief push "new" policy
     */
    ReturnCode pushNew();

    /*!
     * @if jp
     * @brief BufferStatus ���� DataPortStatus �ؤ��Ѵ�
     *
     * �Хåե����������ͤ� DataPortStatus::Enum �����Ѵ�����ؿ�����
     * �줾�졢�ʲ��Τ褦���Ѵ�����롣�Ѵ����˥�����Хå���Ƥ־�硢
     * ������Х��ؿ����յ����롣
     * 
     * - BUFFER_OK: PORT_OK
     *  - None
     * - BUFFER_ERROR: BUFFER_ERROR
     *  - None
     * - BUFFER_FULL: BUFFER_FULL
     *  - onBufferFull()
     * - NOT_SUPPORTED: PORT_ERROR
     *  - None
     * - TIMEOUT: BUFFER_TIMEOUT
     *  - onBufferWriteTimeout()
     * - PRECONDITION_NOT_MET: PRECONDITION_NOT_MET
     *  - None
     * - other: PORT_ERROR
     *  - None
     *
     * @param status BufferStatus
     * @param data cdrMemoryStream
     * @return DataPortStatu ���Υ꥿���󥳡���
     *
     * @else
     * @brief Convertion from BufferStatus to DataPortStatus
     * 
     * This function converts return value from the buffer to
     * DataPortStatus::Enum typed return value. The conversion rule is
     * as follows. Callback functions are also shown, if it exists.
     * 
     * - BUFFER_OK: PORT_OK
     *  - None
     * - BUFFER_ERROR: BUFFER_ERROR
     *  - None
     * - BUFFER_FULL: BUFFER_FULL
     *  - onBufferFull()
     * - NOT_SUPPORTED: PORT_ERROR
     *  - None
     * - TIMEOUT: BUFFER_TIMEOUT
     *  - onBufferWriteTimeout()
     * - PRECONDITION_NOT_MET: PRECONDITION_NOT_MET
     *  - None
     * - other: PORT_ERROR
     *  - None
     *
     * @param status BufferStatus
     * @param data cdrMemoryStream
     * @return DataPortStatus typed return code
     *
     * @endif
     */
    ReturnCode convertReturn(BufferStatus::Enum status,
                             const cdrMemoryStream& data);


    /*!
     * @if jp
     * @brief DataPortStatus�˽��äƥꥹ�ʤ����Τ���ؿ���ƤӽФ���
     *
     * @param status DataPortStatus
     * @param data cdrMemoryStream
     * @return �꥿���󥳡���
     *
     * @else
     * @brief Call listeners according to the DataPortStatus
     *
     * @param status DataPortStatus
     * @param data cdrMemoryStream
     * @return Return code
     *
     * @endif
     */
    ReturnCode invokeListener(DataPortStatus::Enum status,
                              const cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE�Υꥹ�ʤ����Τ��롣 
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
     * @brief ON_BUFFER_FULL�ꥹ�ʤإ��٥�Ȥ����Τ��롣 
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
     * @brief ON_BUFFER_WRITE_TIMEOUT�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_WRITE_TIMEOUT event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWriteTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE_TIMEOUT].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_READ�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_READ event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferRead(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_READ].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_SEND�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_SEND event to listners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onSend(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_SEND].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVED�Υꥹ�ʤ����Τ��롣 
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
     * @brief ON_RECEIVER_FULL�Υꥹ�ʤ����Τ��롣 
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
     * @brief ON_RECEIVER_TIMEOUT�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVER_TIMEOUT event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_TIMEOUT].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_ERROR�Υꥹ�ʤ����Τ��롣 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVER_ERROR event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverError(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_ERROR].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_EMPTY�Υꥹ�ʤ����Τ��롣 
     * @else
     * @brief Notify an ON_BUFFER_EMPTY event to listeners
     * @endif
     */
    inline void onBufferEmpty()
    {
      m_listeners->
        connector_[ON_BUFFER_EMPTY].notify(m_profile);
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
     * @brief ON_SENDER_ERROR�Υꥹ�ʤ����Τ��롣 
     * @else
     * @brief Notify an ON_SENDER_ERROR event to listeners
     * @endif
     */
    inline void onSenderError()
    {
      m_listeners->
        connector_[ON_SENDER_ERROR].notify(m_profile);
    }


  private:
    bool bufferIsEmpty()
    {
      if (m_buffer->empty() && !m_readback)
        {
          RTC_DEBUG(("buffer empty"));
          onBufferEmpty();
          onSenderEmpty();
          return true;
        }
      return false;
    }

    Logger rtclog;
    InPortConsumer* m_consumer;
    CdrBufferBase* m_buffer;
    ConnectorInfo m_profile;
    coil::PeriodicTaskBase* m_task;
    ConnectorListeners* m_listeners;
    ReturnCode m_retcode;
    Mutex m_retmutex;
    Policy m_pushPolicy;
    int m_skipn;
    bool m_active;
    bool m_readback;
    int m_leftskip;
  };
};     // namespace RTC

extern "C"
{
  void DLL_EXPORT PublisherPeriodicInit();
};

#endif // RTC_PUBLISHERPERIODIC_H

