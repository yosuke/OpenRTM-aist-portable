// -*- C++ -*-
/*!
 * @file DataPortStatus.h
 * @brief DataPortStatus class
 * @date $Date$
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

#ifndef RTC_DATAPORTSTATUS_H
#define RTC_DATAPORTSTATUS_H

#include <vector>

namespace RTC
{
  /*!
   * @if jp
   * @class DataPortStatus mixin class
   * @brief DataPortStatus mixin ���饹
   *
   * ���Υ��饹�ϡ�enum������줿�꥿���󥳡��ɤ򡢥ǡ����ݡ��ȴ�Ϣ�Υ�
   * �֥��饹�Ƕ������Ѥ��뤿��� mixin ���饹�Ǥ��롣���Υ꥿���󥳡�
   * �ɤ���Ѥ��륯�饹�Ǥϡ�DataPortStatus ���饹��public �Ѿ���������
   * define ���Ƥ���DATAPORTSTATUS_ENUM �򥯥饹��˵��Ҥ��뤳�Ȥ�����
   * ��ǽ�Ȥʤ롣����ˤ�ꡢenum �� ReturnCode_t ���Ȥ��� typedef ����
   * �ʸ�ReturnCode_t �����ѤǤ���褦�ˤ���ȤȤ�ˡ�̾�����֤� enum
   * ������줿�Ƽ��̻Ҥ��������饹̾���������Ƴ�����롣
   *
   * @else
   * @class DataPortStatus mixin class
   * @brief DataPortStatus mixin class
   *
   * This is a mixin class to provide enumed return codes that are
   * commonly utilised in data port related sub-classes. To use this
   * class, sub-class should inherit this class as a public super
   * class, and declare DATAPORTSTATUS_ENUM defined
   * below. Consequently, ReturnCode_t type that is typedefed by this
   * macro can be used in the sub-class, and enumed identifiers are
   * imported to the class's namespace.
   *
   * @endif
   */
  class DataPortStatus
  {
  public:
    /*!
     * @if jp
     * brief DataPortStatus �꥿���󥳡���
     *
     * �ǡ����ݡ��ȴ�Ϣ�Υ��饹�Ƕ��̤Υ꥿���󥳡���
     *  
     * - PORT_OK:              ���ｪλ
     * - PORT_ERROR:           �۾ｪλ
     * - BUFFER_ERROR:         �Хåե����顼
     * - BUFFER_FULL:          �Хåե��ե�
     * - BUFFER_EMPTY:         �Хåե�����ץƥ�
     * - BUFFER_TIMEOUT:       �Хåե������ॢ����
     * - SEND_FULL:            �ǡ��������ä������¦���Хåե��ե����
     * - SEND_TIMEOUT:         �ǡ��������ä������¦�������ॢ���Ȥ���
     * - RECV_EMPTY:           �ǡ�����������褦�Ȥ������ǡ�����������
     * - RECV_TIMEOUT:         �ǡ�����������褦�Ȥ����������द�Ȥ���
     * - INVALID_ARGS:         �����ʰ���
     * - PRECONDITION_NOT_MET: ���������������Ƥ��ʤ�
     * - CONNECTION_LOST:      ��³�����Ǥ��줿
     * - UNKNOWN_ERROR:        �����ʥ��顼
     *
     * �ǡ����ݡ��ȤΥǡ�����ϩ��Υ��顼ȯ���Ľ꤫��ƤӽФ�¦�إ��顼
     * ����������뤿��ˤ��Υ��顼�����ɤ���Ѥ��롣��ˡ�����ϩ��Υ�
     * �顼��������Υ��顼�ʤɤ��ͤ����뤬������ʬ�γ��̤�ȯ�����륨
     * �顼��ʲ�����󤹤롣
     *
     * (1) Push��
     *  a) InPortConsumer �� Publisher/Activity �֤�ȯ������꥿���󥳡���
     *     PORT_OK, PORT_ERROR, SEND_FULL, SEND_TIMEOUT, CONNECTION_LOST,
     *     UNKNOWN_ERROR
     *
     *  b) Activity �� OutPort �� Buffer/Connector �֤�ȯ������꥿���󥳡���
     *     PORT_OK, PORT_ERROR, BUFFER_ERROR, BUFFER_FULL, BUFFER_TIMEOUT,
     *     UNKNOWN_ERROR, 
     *
     * (2) Pull��
     *  a) Activity �� InPort �δ֤�ȯ������꥿���󥳡���
     *     PORT_OK, PORT_ERROR, RECV_EMPTY, RECV_TIMEOUT, CONNETION_LOST,
     *     UNKNOWN_ERROR
     *
     * �ƴؿ����֤��꥿���󥳡��ɤϴؿ����ȤΥ�ե���󥹤򻲾ȤΤ��ȡ�
     *
     * @else
     * @brief DataPortStatus return codes
     *
     * Common return codes for data ports related classes.
     *
     * - PORT_OK:              Normal return
     * - PORT_ERROR:           Error return
     * - BUFFER_ERROR:         Buffer error
     * - BUFFER_FULL:          Buffer full
     * - BUFFER_EMPTY:         Buffer empty
     * - BUFFER_TIMEOUT:       Buffer timeout
     * - SEND_FULL:            Buffer full although OutPort tried to send data
     * - SEND_TIMEOUT:         Timeout although OutPort tried to send data
     * - RECV_EMPTY:           Buffer empty although InPort tried to receive
     *                         data
     * - RECV_TIMEOUT:         Timeout although InPort tried to receive data
     * - INVALID_ARGS:         Invalid arguments
     * - PRECONDITION_NOT_MET: Precondition not met
     * - CONNECTION_LOST:      Connection has been lost
     * - UNKNOWN_ERROR:        Unknown error
     *
     * This error codes might be used to propagate error status from
     * the error occurring point to the function caller in the data
     * stream path. It would occur in data-transfer path and data
     * receiver/sender. The errors that occur in the interface of each
     * portion of data port are shown below.
     *
     * (1) Push Type
     *  a) The return codes between InPortConsumer and Publisher/Activity
     *     PORT_OK, PORT_ERROR, SEND_FULL, SEND_TIMEOUT, CONNECTION_LOST,
     *     UNKNOWN_ERROR
     *  b) The return codes between Activity and Buffer/Connector of OutPort
     *     PORT_OK, PORT_ERROR, BUFFER_ERROR, BUFFER_FULL, BUFFER_TIMEOUT,
     *     UNKNOWN_ERROR, 
     *
     * (2) Pull Type
     *  a) The return codes between Activity and InPort
     *     PORT_OK, PORT_ERROR, RECV_EMPTY, RECV_TIMEOUT, CONNETION_LOST,
     *     UNKNOWN_ERROR
     *
     * See function references for detailed return codes for each function.
     *
     * @endif
     */
    enum Enum
      {
        PORT_OK = 0,
        PORT_ERROR,
        BUFFER_ERROR,
        BUFFER_FULL,
        BUFFER_EMPTY,
        BUFFER_TIMEOUT,
        SEND_FULL,
        SEND_TIMEOUT,
        RECV_EMPTY,
        RECV_TIMEOUT,
        INVALID_ARGS,
        PRECONDITION_NOT_MET,
        CONNECTION_LOST,
        UNKNOWN_ERROR
      };

    /*!
     * @if jp
     *
     * @brief DataPortStatus �꥿���󥳡��ɤ�ʸ������Ѵ�
     *
     * DataPortStatus �꥿���󥳡��ɤ�ʸ������Ѵ�����
     *
     * @param status �Ѵ��о� DataPortStatus �꥿���󥳡���
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert DataPortStatus into the string.
     *
     * Convert DataPortStatus into the string.
     *
     * @param status The target DataPortStatus for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(DataPortStatus::Enum status)
    {
      const char* str[] = {
        "PORT_OK",
        "PORT_ERROR",
        "BUFFER_ERROR",
        "BUFFER_FULL",
        "BUFFER_EMPTY",
        "BUFFER_TIMEOUT",
        "SEND_FULL",
        "SEND_TIMEOUT",
        "RECV_EMPTY",
        "RECV_TIMEOUT",
        "INVALID_ARGS",
        "PRECONDITION_NOT_MET",
        "CONNECTION_LOST",
        "UNKNOWN_ERROR"
      };
      return str[status];
    }
  };
  
  typedef std::vector<DataPortStatus::Enum> DataPortStatusList;

};

/*!
 * @if jp
 *
 * @brief ::RTC::DataPortStatus Ƴ��
 * 
 * ::RTC::DataPortStatus ���������Ƥ��� Enum �Τ��٤ƤΥ��Ф�͡���
 * ���ڡ�����Ƴ�����뤿��Υޥ���DataPortStatus �����Ѥ��륯�饹�ˤ�
 * ���ơ����饹�������Ƭ�ˤ����� DATAPORTSTATUS_ENUM �򵭺ܤ�������ǡ�
 * DataPortStatus ���������Ƥ��� enum ���Ф�̾�����黻�Ҥʤ��˥�
 * ��������ǽ�ˤʤ롣
 *
 * @else
 *
 * @brief Importing ::RTC::DataPortStatus macro
 *
 * This macro imports all the member of enum declared in
 * ::RTC::DataPortStatus into the current namespace.  Inserting at the
 * head of class declaration, classes which utilize DataPortStatus can
 * access Enum members of DataPortStatus without using namespace
 * resolve operator.
 *
 * @endif
 */
#define DATAPORTSTATUS_ENUM                             \
  typedef ::RTC::DataPortStatus::Enum ReturnCode;       \
  using ::RTC::DataPortStatus::PORT_OK;                 \
  using ::RTC::DataPortStatus::PORT_ERROR;              \
  using ::RTC::DataPortStatus::BUFFER_FULL;             \
  using ::RTC::DataPortStatus::BUFFER_EMPTY;            \
  using ::RTC::DataPortStatus::BUFFER_TIMEOUT;          \
  using ::RTC::DataPortStatus::SEND_FULL;               \
  using ::RTC::DataPortStatus::SEND_TIMEOUT;            \
  using ::RTC::DataPortStatus::RECV_EMPTY;              \
  using ::RTC::DataPortStatus::RECV_TIMEOUT;            \
  using ::RTC::DataPortStatus::INVALID_ARGS;            \
  using ::RTC::DataPortStatus::PRECONDITION_NOT_MET;    \
  using ::RTC::DataPortStatus::CONNECTION_LOST;         \
  using ::RTC::DataPortStatus::UNKNOWN_ERROR;

#endif // RTC_DATAPORTSTATUS_H
