// -*- C++ -*-
/*!
 * @file  PublisherFlush.h
 * @brief PublisherFlush class
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
 * $Id: PublisherFlush.h 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#ifndef RTC_PUBLISHERFLUSH_H
#define RTC_PUBLISHERFLUSH_H

#include <coil/Condition.h>
#include <rtm/PublisherBase.h>
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
   * @class PublisherFlush
   * @brief PublisherFlush ���饹
   *
   * Flush �� Publisher ���饹
   * �Хåե���˳�Ǽ����Ƥ���̤�����ǡ������������롣
   * �ǡ������Ф��Ԥĥ��󥷥塼�ޤ����Ф���¦��Ʊ������åɤ�ư����롣
   *
   * @else
   * @class PublisherFlush
   * @brief PublisherFlush class
   *
   * This is a Publisher class of Flush type.
   * This class sends unsend data that has been stored in the buffer.
   * This executes Consumer that waits for the data send timing in the same 
   * thread as its send side.
   *
   * @endif
   */
  class PublisherFlush
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
     * ���󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     *
     * Consrtuctor.
     *
     * @endif
     */
    PublisherFlush();
    
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
    virtual ~PublisherFlush(void);

    /*!
     * @if jp
     * @brief �����
     *
     * ���Υ��饹�Υ��֥������Ȥ���Ѥ���Τ���Ω����ɬ�����δؿ���Ƥ�
     * �Ф�ɬ�פ����롣������������ PublisherFlush �ϸ����ǽ���������
     * ��᡼��������ʤ���
     *    
     * @param property ��Publisher�ζ�ư�����������ꤷ��Property���֥�������
     * @return ReturnCode PORT_OK ���ｪλ
     *                    INVALID_ARGS Properties ���������ͤ�ޤ�
     *
     * @else
     * @brief initialization
     *
     * This function have to be called before using this class object.
     * However, this PublisherFlush class has no parameters to be initialized.
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
     * PublisherFlush�Ǥϡ��Хåե�����Ѥ��ʤ����ᡢ�����ʤ����
     * PORT_OK ���֤���
     *
     * @param buffer CDR�Хåե�
     * @return PORT_OK ���ｪλ
     *
     * @else
     * @brief Setting buffer pointer
     *
     * Since PublisherFlush does not use any buffers, This function
     * always returns PORT_OK.
     *
     * @param buffer CDR buffer
     * @return PORT_OK
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
    virtual ::RTC::DataPortStatus::Enum
    setListener(ConnectorInfo& profile,
                RTC::ConnectorListeners* listeners);

    /*!
     * @if jp
     * @brief �ǡ�����񤭹���
     *
     * Publisher ���ݻ����륳�󥷥塼�ޤ��Ф��ƥǡ�����񤭹��ࡣ����
     * ���塼�ޡ��ꥹ������Ŭ�ڤ����ꤵ��Ƥ��ʤ�����Publisher ���֥���
     * ���Ȥ����������������Ƥ��ʤ���硢���δؿ���ƤӽФ��ȥ��顼����
     * �� PRECONDITION_NOT_MET ���֤��졢���󥷥塼�ޤؤν񤭹���������
     * ��ϰ��ڹԤ��ʤ���
     *
     * ���󥷥塼�ޤؤν񤭹��ߤ��Ф��ơ����󥷥塼�ޤ��ե���֡�����
     * ���塼�ޤΥ��顼�����󥷥塼�ޤؤν񤭹��ߤ������ॢ���Ȥ������
     * �ˤϤ��줾�졢���顼������ SEND_FULL, SEND_ERROR, SEND_TIMEOUT
     * ���֤���롣
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
     *         SEND_FULL           �����褬�ե����
     *         SEND_TIMEOUT        �����褬�����ॢ���Ȥ���
     *         CONNECTION_LOST     ��³�����Ǥ��줿���Ȥ��Τ�����
     *
     * @else
     * @brief Write data 
     *
     * This function writes data into the consumer associated with
     * this Publisher. If this function is called without initializing
     * correctly such as a consumer, listeners, etc., error code
     * PRECONDITION_NOT_MET will be returned and no operation of the
     * writing to the consumer etc. will be performed.
     *
     * When publisher writes data to the buffer, if the consumer
     * returns full-status, returns error, is returned with timeout,
     * error codes BUFFER_FULL, BUFFER_ERROR and BUFFER_TIMEOUT will
     * be returned respectively.
     *
     * In other cases, PROT_ERROR will be returned.
     *
     * @param data Data to be wrote to the buffer
     * @param sec Timeout time in unit seconds
     * @param nsec Timeout time in unit nano-seconds
     * @return PORT_OK             Normal return
     *         PRECONDITION_NO_MET Precondition does not met. A consumer,
     *                             a buffer, listenes are not set properly.
     *         SEND_FULL           Data was sent but full-status returned
     *         SEND_TIMEOUT        Data was sent but timeout occurred
     *         CONNECTION_LOST     detected that the connection has been lost
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

  protected:
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
    
  private:
    Logger rtclog;
    InPortConsumer* m_consumer;
    ConnectorInfo m_profile;
    ConnectorListeners* m_listeners;
    ReturnCode m_retcode;
    Mutex m_retmutex;
    bool m_active;
  };

};     // namespace RTC

extern "C"
{
  void DLL_EXPORT PublisherFlushInit();
};

#endif // RTC_PUBLISHERFLUSH_H

