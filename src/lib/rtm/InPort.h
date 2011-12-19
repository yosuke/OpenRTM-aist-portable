// -*- C++ -*-
/*!
 * @file InPort.h
 * @brief InPort template class
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
 * $Id: InPort.h 2151 2011-05-31 00:23:51Z n-ando $
 *
 */

#ifndef RTC_INPORT_H
#define RTC_INPORT_H

#include <string>
#include <vector>
#include <iostream>

#include <coil/TimeValue.h>
#include <coil/Time.h>
#include <coil/OS.h>

#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/InPortBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortCallback.h>
#include <rtm/InPortConnector.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class InPort
   *
   * @brief InPort �ƥ�ץ졼�ȥ��饹
   * 
   * InPort �μ����Ǥ��� InPort<T> �Υƥ�ץ졼�ȥ��饹��
   * <T> ��BasicDataType.idl �ˤ��������Ƥ��뷿�ǡ����ФȤ���
   * Time ���� tm , ����� T���� data ����Ĺ�¤�ΤǤʤ��ƤϤʤ�ʤ���
   * InPort �������˥�󥰥Хåե�����������������������줿�ǡ�����缡
   * ���Υ�󥰥Хåե��˳�Ǽ���롣��󥰥Хåե��Υ������ϥǥե���Ȥ�64��
   * �ʤäƤ��뤬�����󥹥ȥ饯�������ˤ�ꥵ��������ꤹ�뤳�Ȥ��Ǥ��롣
   * �ǡ����ϥե饰�ˤ�ä�̤�ɡ����ɾ��֤��������졢isNew(), write(), read(),
   * isFull(), isEmpty() ���Υ᥽�åɤˤ��ϥ�ɥ�󥰤��뤳�Ȥ��Ǥ��롣
   *   
   * OnRead�ϥ�����Хå� (�ɤ߽Ф��˵������륤�٥�Ȥˤ�ꥳ���뤵���)
   *
   * - void OnRead::operator(): 
   *     InPort::read() ��ƤӽФ��ɤ߽Ф���Ԥ��ݤ˥����뤵��롣
   *
   * - DataType OnReadConvert::operator(DataType): 
   *     InPort::read() ��ƤӽФ����ǡ�����Хåե������ɤߤ����ݤ˸ƤФ�
   *     �ǡ������Ѵ���Ԥ��������ˤϥХåե������ɤ߽Ф��줿�ͤ�Ϳ����졢
   *     �Ѵ���Υǡ���������ͤȤ����֤��������ͤ�read()���֤��ͤȤʤ롣
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class InPort
   *
   * @brief InPort template class
   *
   * This is a template class that implements InPort.  <T> is the type
   * defined in BasicDataType.idl and must be the structure which has
   * both Time type tm and type-T data as a member. InPort has a ring
   * buffer internally, and stores the received data externally in
   * this buffer one by one. The size of ring buffer can be specified
   * according to the argument of constructor, though the default size
   * is 64. Unread data and data which is already read are managed
   * with the flag, and the data can be handled by the isNew(),
   * write(), read(), isFull() and isEmpty() method etc.
   *
   * @since 0.2.0
   *
   * @endif
   */
  template <class DataType>
  class InPort
    : public InPortBase
  {
  public:
    DATAPORTSTATUS_ENUM
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     * �ѥ�᡼���Ȥ���Ϳ������ T �����ѿ��˥Х���ɤ���롣
     *
     * @param name InPort ̾��InPortBase:name() �ˤ�껲�Ȥ���롣
     * @param value ���� InPort �˥Х���ɤ���� T �����ѿ�
     * @param bufsize InPort �����Υ�󥰥Хåե��ΥХåե�Ĺ(�ǥե������:64)
     * @param read_block �ɹ��֥�å��ե饰��
     *        �ǡ����ɹ�����̤�ɥǡ������ʤ���硢���Υǡ��������ޤǥ֥�å�����
     *        ���ɤ���������(�ǥե������:false)
     * @param write_block ����֥�å��ե饰��
     *        �ǡ���������˥Хåե����ե�Ǥ��ä���硢�Хåե��˶������Ǥ���
     *        �ޤǥ֥�å����뤫�ɤ���������(�ǥե������:false)
     * @param read_timeout �ɹ��֥�å�����ꤷ�Ƥ��ʤ����Ρ��ǡ����ɼ西����
     *        �����Ȼ���(�ߥ���)(�ǥե������:0)
     * @param write_timeout ����֥�å�����ꤷ�Ƥ��ʤ����Ρ��ǡ������������
     *        �����Ȼ���(�ߥ���)(�ǥե������:0)
     *
     * @else
     *
     * @brief A constructor.
     *
     * constructor.
     * This is bound to type-T variable given as a parameter.
     *
     * @param name A name of the InPort. This name is referred by
     *             InPortBase::name().
     * @param value type-T variable that is bound to this InPort.
     * @param bufsize Buffer length of internal ring buffer of InPort
     *                (The default value:64)
     * @param read_block Flag of reading block.
     *                   When there are not unread data at reading data,
     *                   set whether to block data until receiving the next 
     *                   data. (The default value:false)
     * @param write_block Flag of writing block.
     *                    If the buffer was full at writing data, set whether 
     *                    to block data until the buffer has space. 
     *                    (The default value:false)
     * @param read_timeout Data reading timeout time (millisecond) 
     *                     when not specifying read blocking.
     *                     (The default value:0)
     * @param write_timeout Data writing timeout time (millisecond)
     *                      when not specifying writing block.
     *                      (The default value:0)
     *
     * @endif
     */
    InPort(const char* name, DataType& value,
	   int bufsize=64, 
	   bool read_block = false, bool write_block = false,
	   int read_timeout = 0, int write_timeout = 0)
#if defined(__GNUC__) && (__GNUC__ <= 3 && __GNUC_MINOR__ <= 3) 
      :	InPortBase(name, ::CORBA_Util::toRepositoryIdOfStruct<DataType>()),
#else
      :	InPortBase(name, ::CORBA_Util::toRepositoryId<DataType>()),
#endif
        m_name(name), m_value(value),
	m_OnRead(NULL),  m_OnReadConvert(NULL)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~InPort(void){};

    /*!
     * @if jp
     *
     * @brief �ݡ���̾�Τ�������롣
     *
     * �ݡ���̾�Τ�������롣
     *
     * @return �ݡ���̾��
     *
     * @else
     *
     * @brief Get port name
     *
     * Get port name.
     *
     * @return The port name
     *
     * @endif
     */
    virtual const char* name()
    {
      return m_name.c_str();
    }

    
    /*!
     * @if jp
     *
     * @brief �ǿ��ǡ�����¸�ߤ��뤫��ǧ����
     * 
     * InPort��̤�ɤκǿ��ǡ��������夷�Ƥ��뤫��bool�ͤ��֤���
     * InPort��̤��³�ξ�硢�������³���ͥ����ΥХåե���Empty
     * �ξ��ˤ�false���֤���
     *
     * @return true ̤�ɤκǿ��ǡ�����¸�ߤ���
     *         false ̤��³�ޤ��ϥХåե��˥ǡ�����¸�ߤ��ʤ���
     * 
     * @else
     *
     * @brief Check whether the data is newest
     * 
     * Check whether the data stored at a current buffer position is newest.
     *
     * @return Newest data check result
     *         ( true:Newest data. Data has not been readout yet.
     *          false:Past data��Data has already been readout.)
     * 
     * @endif
     */
    virtual bool isNew()
    {
      RTC_TRACE(("isNew()"));

      // In single-buffer mode, all connectors share the same buffer. This
      // means that we only need to read from the first connector to get data
      // received by any connector.
      int r(0);
      {
        Guard guard(m_connectorsMutex);
        if (m_connectors.size() == 0)
          {
            RTC_DEBUG(("no connectors"));
            return false;
          }
        r = m_connectors[0]->getBuffer()->readable();
      }
      
      if (r > 0)
        {
          RTC_DEBUG(("isNew() = true, readable data: %d", r));
          return true;
        }
      
      RTC_DEBUG(("isNew() = false, no readable data"));
      return false;
    }

    /*!
     * @if jp
     *
     * @brief �Хåե��������ɤ�����ǧ����
     * 
     * InPort�ΥХåե��������ɤ����� bool �ͤ��֤���
     * ���ξ��� true, ̤�ɥǡ������������ false ���֤���
     *
     * @return true  �Хåե��϶�
     *         false �Хåե���̤�ɥǡ���������
     * 
     * @else
     *
     * @brief Check whether the data is newest
     * 
     * Check whether the data stored at a current buffer position is newest.
     *
     * @return Newest data check result
     *         ( true:Newest data. Data has not been readout yet.
     *          false:Past data��Data has already been readout.)
     * 
     * @endif
     */
    virtual bool isEmpty()
    {
      RTC_TRACE(("isEmpty()"));
      int r(0);

      {
        Guard guard(m_connectorsMutex);
        if (m_connectors.size() == 0)
          {
            RTC_DEBUG(("no connectors"));
            return true;
          }
        // In single-buffer mode, all connectors share the same buffer. This
        // means that we only need to read from the first connector to get data
        // received by any connector.
        r = m_connectors[0]->getBuffer()->readable();
      }

      if (r == 0)
        {
          RTC_DEBUG(("isEmpty() = true, buffer is empty"));
          return true;
        }
      
      RTC_DEBUG(("isEmpty() = false, data exists in the buffer"));
      return false;
    }

    /*!
     * @if jp
     *
     * @brief DataPort �����ͤ��ɤ߽Ф�
     *
     * InPort�˽񤭹��ޤ줿�ǡ������ɤߤ�������³����0���ޤ��ϥХåե���
     * �ǡ������񤭹��ޤ�Ƥ��ʤ����֤��ɤߤ�������������ͤ�����Ǥ��롣
     * �Хåե������ξ��֤ΤȤ���
     * ���������ꤵ�줿�⡼�� (readback, do_nothing, block) �˱����ơ�
     * �ʲ��Τ褦��ư��򤹤롣
     *
     * - readback: �Ǹ���ͤ��ɤߤʤ�����
     *
     * - do_nothing: ���⤷�ʤ�
     *
     * - block: �֥�å����롣�����ॢ���Ȥ����ꤵ��Ƥ�����ϡ�
     *       �����ॢ���Ȥ���ޤ��Ԥġ�
     *
     * �Хåե������ξ��֤Ǥϡ�InPort�˥Х���ɤ��줿�ѿ����ͤ��֤���롣
     * �������äơ�����ɤ߽Ф����ˤ������ͤ��֤���ǽ�������롣
     * ���δؿ������Ѥ���ݤˤϡ�
     *
     * - isNew(), isEmpty() ��ʻ�Ѥ��������˥Хåե����֤�����å����롣
     * 
     * - ����ɤ߽Ф����������ͤ��֤��ʤ��褦�˥Х�����ѿ�������˽��������
     * 
     * - ReturnCode read(DataType& data) �ؿ������Ѥ�Ƥ���롣
     *
     * ���Ȥ�˾�ޤ�����
     *
     * �ƥ�����Хå��ؿ��ϰʲ��Τ褦�˸ƤӽФ���롣
     * - OnRead: read() �ؿ����ƤФ��ݤ�ɬ���ƤФ�롣
     * 
     * - OnReadConvert: �ǡ������ɤ߽Ф�������������硢�ɤߤ������ǡ�����
     *       �����Ȥ���OnReadConvert���ƤӽФ��졢����ͤ�read()�������
     *       �Ȥ����֤���
     *
     * - OnEmpty: �Хåե������Τ���ǡ������ɤ߽Ф��˼��Ԥ������ƤӽФ���롣
     *        OnEmpty ������ͤ� read() ������ͤȤ����֤���
     *
     * - OnBufferTimeout: �ǡ����ե�����Push���ξ��ˡ��ɤ߽Ф�
     *        �����ॢ���ȤΤ���˥ǡ������ɤ߽Ф��˼��Ԥ������˸ƤФ�롣
     *
     * - OnRecvTimeout: �ǡ����ե�����Pull���ξ��ˡ��ɤ߽Ф������ॢ����
     *        �Τ���˥ǡ����ɤ߽Ф��˼��Ԥ������˸ƤФ�롣
     *
     * - OnReadError: �嵭�ʳ�����ͳ���ɤߤ����˼��Ԥ������˸ƤФ�롣
     *        ��ͳ�Ȥ��Ƥϡ��Хåե�����������硢�㳰��ȯ���ʤɤ��ͤ�����
     *        ���̾�ϵ����ꤨ�ʤ�����Х��β�ǽ�������롣
     *
     * @return �ɤ߽Ф����(�ɤ߽Ф�����:true, �ɤ߽Ф�����:false)
     *
     * @else
     *
     * @brief Readout the value from DataPort
     *
     * Readout the value from DataPort
     *
     * - When Callback functor OnRead is already set, OnRead will be invoked
     *   before reading from the buffer held by DataPort.
     * - When the buffer held by DataPort can detect the underflow,
     *   and when it detected the underflow at reading, callback functor
     *   OnUnderflow will be invoked.
     * - When callback functor OnReadConvert is already set, the return value of
     *   operator() of OnReadConvert will be the return value of read().
     * - When timeout of reading is already set by setReadTimeout(),
     *   it waits for only timeout time until the state of the buffer underflow
     *   is reset, and if OnUnderflow is already set, this will be invoked to 
     *   return.
     *
     * @return Readout result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool read()
    {
      RTC_TRACE(("DataType read()"));

      if (m_OnRead != NULL) 
        {
          (*m_OnRead)();
          RTC_TRACE(("OnRead called"));
        }

      cdrMemoryStream cdr;
      ReturnCode ret;
      {
        Guard guard(m_connectorsMutex);
        if (m_connectors.size() == 0)
          {
            RTC_DEBUG(("no connectors"));
            return false;
          }
        
        // In single-buffer mode, all connectors share the same buffer. This
        // means that we only need to read from the first connector to get data
        // received by any connector.
        ret = m_connectors[0]->read(cdr);
      }
      if (ret == PORT_OK)
        {
          RTC_DEBUG(("data read succeeded"));
          m_value <<= cdr;
          if (m_OnReadConvert != 0) 
            {
              m_value = (*m_OnReadConvert)(m_value);
              RTC_DEBUG(("OnReadConvert called"));
              return true;
            }
          return true;
        }
      else if (ret == BUFFER_EMPTY)
        {
          RTC_WARN(("buffer empty"));
          return false;
        }
      else if (ret == BUFFER_TIMEOUT)
        {
          RTC_WARN(("buffer read timeout"));
          return false;
        }
      RTC_ERROR(("unknown retern value from buffer.read()"));
      return false;
    }
    

    /*!
     * @if jp
     *
     * @brief �Х���ɤ��줿 T �����ѿ��� InPort �Хåե��κǿ��ͤ��ɤ߹���
     *
     * �Х���ɤ��줿 T ���Υǡ����� InPort �κǿ��ͤ��ɤ߹��ࡣ
     * ���󥹥ȥ饯���� T �����ѿ��� InPort ���Х���ɤ���Ƥ��ʤ���Фʤ�ʤ���
     * ���Υ᥽�åɤϥݥ�⡼�ե��å��˻��Ѥ�����������Ȥ��Ƥ��뤿�ᡢ
     * ���˰�¸���ʤ�����������ͤȤʤäƤ��롣
     *
     * @else
     *
     * @brief Read the newly value to type-T variable which is bound to InPort's
     *        buffer.
     *
     * Read the newly value to type-T data which is bound to InPort's buffer.
     * The type-T variable must be bound to InPort in constructor.
     * Since this method assumes to be used for polymorphic,
     * its argument and the return value do not depend on type.
     *
     * @endif
     */
    virtual void update()
    {
      this->read();
    };
    
    /*!
     * @if jp
     *
     * @brief T ���Υǡ����� InPort �κǿ��ͥǡ������ɤ߹���
     *
     * InPort �����ꤵ��Ƥ���ǿ��ǡ������ɤ߹��ߡ�
     * ���ꤵ�줿�ǡ����ѿ������ꤹ�롣
     *
     * @param rhs InPort �Хåե������ͤ��ɤ߹��� T ���ѿ�
     *
     * @else
     *
     * @brief Read the newly value data in InPort to type-T variable
     *
     * Read the newly data set in InPort and set to specified data variable.
     *
     * @param rhs The type-T variable to read from InPort's buffer
     *
     * @endif
     */
    void operator>>(DataType& rhs)
    {
      this->read();
      rhs = m_value;
      return;
    }
    
    /*!
     * @if jp
     *
     * @brief InPort �Хåե��إǡ����ɤ߹��߻��Υ�����Хå�������
     *
     * InPort �����ĥХåե�����ǡ������ɤ߹��ޤ��ľ���˸ƤФ�륳����Хå�
     * ���֥������Ȥ����ꤹ�롣
     * 
     * @param on_read OnRead&lt;DataType&gt;���Υ��֥�������
     *
     * @else
     *
     * @brief Set callback when data is read from the InPort buffer
     *
     * Set the callback object that is invoked right before data is read from 
     * the InPort's buffer
     * 
     * @param on_read OnRead&lt;DataType&gt; type object
     *
     * @endif
     */
    inline void setOnRead(OnRead<DataType>* on_read)
    {
      m_OnRead = on_read;
    }
    
    /*!
     * @if jp
     *
     * @brief InPort �Хåե��إǡ����ɤ߽Ф����Υ�����Хå�������
     *
     * InPort �����ĥХåե�����ǡ������ɤ߽Ф����ݤ˸ƤФ�륳����Хå�
     * ���֥������Ȥ����ꤹ�롣������Хå����֥������Ȥ�����ͤ�read()�᥽�å�
     * �θƽз�̤Ȥʤ롣
     * 
     * @param on_rconvert OnReadConvert&lt;DataType&gt;���Υ��֥�������
     *
     * @else
     *
     * @brief Set callback when data is readout to the InPort buffer
     *
     * Set the callback object that is invoked when data is readout to
     * the InPort's buffer. The return value of callback object is the return
     * result of the read() method.
     * 
     * @param on_rconvert OnReadConvert&lt;DataType&gt; type object
     *
     * @endif
     */
    inline void setOnReadConvert(OnReadConvert<DataType>* on_rconvert)
    {
      m_OnReadConvert = on_rconvert;
    }
    
  private:
    std::string m_typename;
    /*!
     * @if jp
     * @brief �ݡ���̾
     * @else
     * @berif Port's name
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief �Х���ɤ���� T �����ѿ��ؤλ���
     * @else
     * @brief The reference to type-T value bound this OutPort
     * @endif
     */
    DataType& m_value;
    
    /*!
     * @if jp
     * @brief OnRead ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnRead callback functor
     * @endif
     */
    OnRead<DataType>* m_OnRead;
    
    /*!
     * @if jp
     * @brief OnReadConvert ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnReadConvert callback functor
     * @endif
     */
    OnReadConvert<DataType>* m_OnReadConvert;
   
  };
}; // End of namesepace RTM

#endif // RTC_INPORT_H
