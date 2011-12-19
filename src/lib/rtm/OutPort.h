// -*- C++ -*-
/*!
 * @file OutPort.h
 * @brief OutPort class
 * @date $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPort.h 2151 2011-05-31 00:23:51Z n-ando $
 *
 */

#ifndef RTC_OUTPORT_H
#define RTC_OUTPORT_H

#include <iostream>
#include <string>

#include <coil/TimeValue.h>
#include <coil/Time.h>
#include <coil/TimeMeasure.h>
#include <coil/OS.h>

#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/OutPortBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortCallback.h>
#include <rtm/OutPortConnector.h>

/*!
 * @if jp
 * @brief �ǡ����˥����ॹ����פ򥻥åȤ���
 *
 * �ǡ����ݡ��ȤΥǡ������Ф��ƥ����ॹ����פ򥻥åȤ��롣�ǡ����ݡ���
 * �Υǡ����Ϲ�¤�ΤΥ��С��Ȥ��� tm.sec, tm.nsec �����ɬ�פ����롣
 *
 * @param data �����ॹ����פ򥻥åȤ���ǡ������¹Ը�¹Ի��Υ����ॹ
 *             ����פ����åȤ����
 *
 * @else
 * @brief Setting timestamp to data
 *
 * This function sets timestamp to data of data port. This data should
 * have tm.sec, tm.nsec as members of the structure.
 *
 * @param data Data to be set timestamp. After executing this
 *             function, current timestamp is set to the data.
 *
 * @endif
 */
template <class DataType>
void setTimestamp(DataType& data)
{
      // set timestamp
      coil::TimeValue tm(coil::gettimeofday());
      data.tm.sec  = tm.sec();
      data.tm.nsec = tm.usec() * 1000;
}

namespace RTC
{
  /*!
   * @if jp
   *
   * @class OutPort
   *
   * @brief OutPort �ƥ�ץ졼�ȥ��饹
   * 
   * OutPort �ƥ�ץ졼�ȥ��饹���ƥ�ץ졼�Ȥΰ����Ȥ��ơ�OutPort��
   * �����ǡ����� DataType ��Ȥ롣
   *
   *
   * OnWrite�ϥ�����Хå� (����ߤ˵������륤�٥�Ȥˤ�ꥳ���뤵���)
   *
   * - void OnWrite<DataType>::operator()(const DataType): 
   *     OutPort::write() ��ƤӽФ��񤭹��ߤ�Ԥ��ݤ˥����뤵��롣
   *
   * - DataType OnWriteConvert<DataType>::operator()(const DataType): 
   *     OutPort::write() ��ƤӽФ����ǡ�����Хåե��˽񤭹������˸ƤФ�
   *     �ǡ������Ѵ���Ԥ���operator()()������ͤ����ꥢ�饤������Хåե���
   *     �񤭹��ޤ�롣
   *
   * @since 0.2.0
   *
   * @else
   *
   * @brief OutPort template class
   * 
   * This is the OutPort template class. 
   * The data type "DateType" supported by OutPort and the buffer type
   * "BufferType" are used as template arguments.
   *
   * @since 0.2.0
   *
   * @endif
   */
  template <class DataType>
  class OutPort
    : public OutPortBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param name �ݡ���̾
     * @param value ���Υݡ��Ȥ˥Х���ɤ����ǡ����ѿ�
     * @param length �Хåե�Ĺ(�ǥե������:8)
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port's name
     * @param value Data variable bound to this port
     * @param length Buffer length (The default value:8)
     *
     * @endif
     */
    OutPort(const char* name, DataType& value)
#if defined(__GNUC__) && (__GNUC__ <= 3 && __GNUC_MINOR__ <= 3) 
      : OutPortBase(name, ::CORBA_Util::toRepositoryIdOfStruct<DataType>()),
#else
      : OutPortBase(name, ::CORBA_Util::toRepositoryId<DataType>()),
#endif
        m_value(value), m_onWrite(0), m_onWriteConvert(0)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     * 
     * �ǥ��ȥ饯��
     * 
     * @else
     *
     * @brief Destructor
     * 
     * Destructor
     * 
     * @endif
     */
    virtual ~OutPort(void)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �ǡ����񤭹���
     *
     * �ݡ��Ȥإǡ�����񤭹��ࡣ
     *
     * - ������Хå��ե��󥯥� OnWrite �����åȤ���Ƥ����硢
     *   OutPort ���ݻ�����Хåե��˽񤭹������� OnWrite ���ƤФ�롣
     * - OutPort ���ݻ�����Хåե��������С��ե��򸡽ФǤ���Хåե��Ǥ��ꡢ
     *   ���ġ��񤭹���ݤ˥Хåե��������С��ե��򸡽Ф�����硢
     *   ������Хå��ե��󥯥� OnOverflow ���ƤФ�롣
     * - ������Хå��ե��󥯥� OnWriteConvert �����åȤ���Ƥ����硢
     *   �Хåե��񤭹��߻��ˡ� OnWriteConvert �� operator() ������ͤ�
     *   �Хåե��˽񤭹��ޤ�롣
     *
     * @param value �񤭹����оݥǡ���
     *
     * @return �񤭹��߽������(�񤭹�������:true���񤭹��߼���:false)
     *
     * @else
     *
     * @brief Write data
     *
     * Write data in the port.
     *
     * - When callback functor OnWrite is already set, OnWrite will be
     *   invoked before writing into the buffer held by OutPort.
     * - When the buffer held by OutPort can detect the overflow,
     *   and when it detected the overflow at writing, callback functor
     *   OnOverflow will be invoked.
     * - When callback functor OnWriteConvert is already set, 
     *   the return value of operator() of OnWriteConvert will be written
     *   into the buffer at the writing.
     *
     * @param value The target data for writing
     *
     * @return Writing result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool write(DataType& value)
    {
      RTC_TRACE(("DataType write()"));

      if (m_onWrite != NULL)
        {
          (*m_onWrite)(value);
          RTC_TRACE(("OnWrite called"));
        }

      bool result(true);
      std::vector<const char *> disconnect_ids;
      {
        Guard guard(m_connectorsMutex);
        // check number of connectors
        size_t conn_size(m_connectors.size());
        if (!(conn_size > 0)) { return false; }
        
        m_status.resize(conn_size);

        for (size_t i(0), len(conn_size); i < len; ++i)
          {
            ReturnCode ret;
            if (m_onWriteConvert != NULL)
              {
                RTC_DEBUG(("m_connectors.OnWriteConvert called"));
                ret = m_connectors[i]->write(((*m_onWriteConvert)(value)));
              }
            else
              {
                RTC_DEBUG(("m_connectors.write called"));
                ret = m_connectors[i]->write(value);
              }
            m_status[i] = ret;
            if (ret == PORT_OK) { continue; }
      
            result = false;
            const char* id(m_connectors[i]->profile().id.c_str());
            RTC::ConnectorProfile prof(findConnProfile(id));

            if (ret == CONNECTION_LOST)
              {
                RTC_WARN(("connection_lost id: %s", id));
                if (m_onConnectionLost != 0)
                  {
                    (*m_onConnectionLost)(prof);
                  }
                disconnect_ids.push_back(id);
              }
          }
      }
      std::for_each(disconnect_ids.begin(),disconnect_ids.end(),
                    std::bind1st(std::mem_fun(&PortBase::disconnect),this));
      return result;
    }
    
    /*!
     * @if jp
     *
     * @brief �ǡ����񤭹���
     *
     * �ݡ��Ȥإǡ�����񤭹��ࡣ
     * �Х���ɤ��줿�ѿ������ꤵ�줿�ͤ�ݡ��Ȥ˽񤭹��ࡣ
     *
     * @return �񤭹��߽������(�񤭹�������:true���񤭹��߼���:false)
     *
     * @else
     *
     * @brief Write data
     *
     * Write data to the port.
     * Write the value, which was set to the bound variable, to the port.
     *
     * @return Writing result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool write()
    {
      return write(m_value);
    }
    
    /*!
     * @if jp
     *
     * @brief �ǡ����񤭹���
     *
     * �ݡ��Ȥإǡ�����񤭹��ࡣ
     * ���ꤵ�줿�ͤ�ݡ��Ȥ˽񤭹��ࡣ
     *
     * @param value �񤭹����оݥǡ���
     *
     * @return �񤭹��߽������(�񤭹�������:true���񤭹��߼���:false)
     *
     * @else
     *
     * @brief Write data
     *
     * Write data to the port.
     * Write the set value to the port.
     *
     * @param value The target data for writing
     *
     * @return Writing result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool operator<<(DataType& value)
    {
      return write(value);
    }

    /*!
     * @if jp
     *
     * @brief ����Υ��ͥ����ؤν񤭹��ߥ��ơ�����������
     *
     * OutPort ����³���Ȥ� Connector �ȸƤФ�벾�ۥǡ�������ͥ���
     * �ġ�write() �ؿ��Ϥ���� Connector ���Ф��ƥǡ�����񤭹��ब��
     * �� Connector �Ͻ񤭹��ߤ��Ȥ˥��ơ��������֤���write() �ؿ��Ǥϡ�
     * ���٤Ƥ� Connector �����ｪλ�����Ȥ��Τ� true ���֤�������ʳ�
     * �Ǥ� false ���ֵѤ��롣���δؿ��� write() �� false �ξ�祹�ơ�
     * ������Ĵ�٤�Τ˻��Ѥ��뤳�Ȥ��Ǥ��롣
     * 
     * @param index Connector �� index
     * @return ���ơ�����
     *
     * @else
     *
     * @brief Getting specified connector's writing status
     *
     * An OutPort has Connectors that are virtual data stream channel
     * for each connection.  "write()" function write into these
     * Connectors, and each Connector returns writing-status.  write()
     * function will return a true value if all Connectors return
     * normal status, and a false value will be returned if at least
     * one Connector failed.  This function can be used to inspect
     * each return status
     *
     * @param index Connector index
     * @return Writing status
     *
     * @endif
     */
    DataPortStatus::Enum getStatus(int index)
    {
      return m_status[index];
    }
    /*!
     * @if jp
     *
     * @brief ����Υ��ͥ����ؤν񤭹��ߥ��ơ������ꥹ�Ȥ�����
     *
     * OutPort ����³���Ȥ� Connector �ȸƤФ�벾�ۥǡ�������ͥ���
     * �ġ�write() �ؿ��Ϥ���� Connector ���Ф��ƥǡ�����񤭹��ब��
     * �� Connector �Ͻ񤭹��ߤ��Ȥ˥��ơ��������֤���write() �ؿ��Ǥϡ�
     * ���٤Ƥ� Connector �����ｪλ�����Ȥ��Τ� true ���֤�������ʳ�
     * �Ǥ� false ���ֵѤ��롣���δؿ��� write() �� false �ξ�祹�ơ�
     * ������Ĵ�٤�Τ˻��Ѥ��뤳�Ȥ��Ǥ��롣
     * 
     * @return ���ơ������ꥹ��
     *
     * @else
     *
     * @brief Getting specified connector's writing status list
     *
     * An OutPort has Connectors that are virtual data stream channel
     * for each connection.  "write()" function write into these
     * Connectors, and each Connector returns writing-status.  write()
     * function will return a true value if all Connectors return
     * normal status, and a false value will be returned if at least
     * one Connector failed.  This function can be used to inspect
     * each return status
     *
     * @return Writing status list
     *
     * @endif
     */
    DataPortStatusList getStatusList()
    {
      return m_status;
    }

    /*!
     * @if jp
     *
     * @brief OnWrite ������Хå�������
     *
     * write() �ƤӽФ����ˡ��ƥ��ͥ������Ф��ƥǡ�����񤭹���ľ���˸�
     * �Ф�� OnWrite ������Хå��ե��󥯥������ꤹ�롣���δؿ��ˤ��
     * ���ꤵ�줿�ե��󥯥����֥������Ȥν�ͭ���ϡ��ƤӽФ�¦�����ġ���
     * ������ const �ơ����Υե��󥯥����֥������Ȥβ�����Ǥ�ϸƤӽФ�¦�ˤ��롣
     * �ե��󥯥����������������ˤϰ����� 0 ���Ϥ����Ȥǡ�������
     * �Хå���̵���Ȥʤ롣
     *
     * @param on_write OnWrite ������Хå��ե��󥯥�
     *
     * @else
     *
     * @brief Set OnWrite callback
     *
     * This operation sets the OnWrite callback functor that is called
     * just before write() operation call.  The ownership of the
     * functor object is owned by caller of this operation.  Therefore
     * caller have to destruct the callback functor object by itself.
     * Giving 0 as an argument for this operation, callback will be
     * disabled.
     *
     * @param on_write OnWrite callback functor
     *
     * @endif
     */
    inline void setOnWrite(OnWrite<DataType>* on_write)
    {
      m_onWrite = on_write;
    }
    
    /*!
     * @if jp
     *
     * @brief OnWriteConvert ������Хå�������
     *
     * write() �ƤӽФ����ˡ��ƥ��ͥ������Ф��ƥǡ�����񤭹���ľ���˸�
     * �Ф졢�ǡ����Ѵ���Ԥ� OnWriteConvert ������Хå��ե��󥯥�����
     * �ꤹ�롣������ľ��ǽ񤭹��ޤ줿�ǡ�����Ϳ����졢����ͤ˼ºݤ�
     * ���ͥ����ޤ��ϥХåե��˽񤭹��ޤ��ǡ������֤��ե��󥯥�������
     * ���롣���δؿ��ˤ�����ꤵ�줿�ե��󥯥����֥������Ȥν�ͭ���ϡ�
     * �ƤӽФ�¦�����ġ��������� const �ơ����Υե��󥯥����֥�������
     * �β�����Ǥ�ϸƤӽФ�¦�ˤ��롣�ե��󥯥����������������ˤ�
     * ������ 0 ���Ϥ����Ȥǡ�������Хå���̵���Ȥʤ롣 �ǡ����񤭹���
     * ���˸ƤФ�� OnWriteConvert ������Хå��ե��󥯥������ꤹ�롣��
     * �Υ�����Хå��ؿ��ν�����̤��񤭹��ޤ�롣���Τ���񤭹��ߥǡ�
     * ���Υե��륿��󥰤���ǽ�Ȥʤ롣
     *
     * @param on_wconvert OnWriteConvert ������Хå��ե��󥯥�
     *
     * @else
     *
     * @brief Set OnWriteConvert callback
     *
     * This operation sets the OnWriteConvert callback functor that
     * converts given data and is called just before write() operation
     * call. A recent data is given to argument and return data will
     * be written into connector or its buffer. The ownership of the
     * functor object is owned by caller of this operation.  Therefore
     * caller have to destruct the callback functor object by itself.
     * Giving 0 as an argument for this operation, callback will be
     * disabled.
     *
     * @param on_wconvert OnWriteConvert callback functor
     *
     * @endif
     */
    inline void setOnWriteConvert(OnWriteConvert<DataType>* on_wconvert)
    {
      m_onWriteConvert = on_wconvert;
    }
    
  private:
    std::string m_typename;
    /*!
     * @if jp
     * @brief �Х���ɤ���� T �����ѿ��ؤλ���
     * @else
     * @brief The reference to type-T variable that is bound.
     * @endif
     */
    DataType& m_value;
    
    /*!
     * @if jp
     * @brief OnWrite ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnWrite callback functor
     * @endif
     */
    OnWrite<DataType>* m_onWrite;
    
    /*!
     * @if jp
     * @brief OnWriteConvert ������Хå��ե��󥯥��ؤΥݥ���
     * @else
     * @brief Pointer to OnWriteConvert callback functor
     * @endif
     */
    OnWriteConvert<DataType>* m_onWriteConvert;

    coil::TimeMeasure m_cdrtime;

    DataPortStatusList m_status;
  };
}; // namespace RTC

#endif // RTC_OUTPORT_H
