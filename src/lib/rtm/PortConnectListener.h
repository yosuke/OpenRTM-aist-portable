// -*- C++ -*-
/*!
 * @file PortConnectListener.h
 * @brief port's internal action listener classes
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_PORTCONNECTLISTENER_H
#define RTC_PORTCONNECTLISTENER_H

#include <vector>
#include <utility>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <rtm/RTC.h>
#include <rtm/idl/RTCSkel.h>

namespace RTC
{
  //============================================================
  /*!
   * @if jp
   * @brief PortConnectListener �Υ�����
   *
   * - ON_NOTIFY_CONNECT:         notify_connect() �ؿ���ƤӽФ�ľ��
   * - ON_NOTIFY_DISCONNECT:      notify_disconnect() �ƤӽФ�ľ��
   * - ON_UNSUBSCRIBE_INTERFACES: notify_disconnect() ���IF���ɲ����
   *
   * @else
   * @brief The types of ConnectorDataListener
   * 
   * - ON_NOTIFY_CONNECT:         right after entering into notify_connect()
   * - ON_NOTIFY_DISCONNECT:      right after entering into notify_disconnect()
   * - ON_UNSUBSCRIBE_INTERFACES: unsubscribing IF in notify_disconnect()
   *
   * @endif
   */
  enum PortConnectListenerType
    {
      ON_NOTIFY_CONNECT,
      ON_NOTIFY_DISCONNECT,
      ON_UNSUBSCRIBE_INTERFACES,
      PORT_CONNECT_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class PortConnectListener ���饹
   * @brief PortConnectListener ���饹
   *
   * �ƥ����������б�����桼���������ɤ��ƤФ��ľ���Υ����ߥ�
   * �ǥ����뤵���ꥹ�ʥ��饹�δ��쥯�饹��
   *
   * - ON_NOTIFY_CONNECT:         notify_connect() �ؿ���ƤӽФ�ľ��
   * - ON_NOTIFY_DISCONNECT:      notify_disconnect() �ƤӽФ�ľ��
   * - ON_UNSUBSCRIBE_INTERFACES: notify_disconnect() ���IF���ɲ����
   *
   * @else
   * @class PortConnectListener class
   * @brief PortConnectListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * - ON_NOTIFY_CONNECT:         right after entering into notify_connect()
   * - ON_NOTIFY_DISCONNECT:      right after entering into notify_disconnect()
   * - ON_UNSUBSCRIBE_INTERFACES: unsubscribing IF in notify_disconnect()
   *
   * @endif
   */
  class PortConnectListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PortConnectListenerType ��ʸ������Ѵ�
     *
     * PortConnectListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� PortConnectListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert PortConnectListenerType into the string.
     *
     * Convert PortConnectListenerType into the string.
     *
     * @param type The target PortConnectListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PortConnectListenerType type);

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PortConnectListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��ؿ�
     *
     * PortConnectListener �Υ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PortConnectListener.
     *
     * @endif
     */
    virtual void operator()(const char* portname,
                            RTC::ConnectorProfile& profile) = 0;
  };


  //============================================================
  /*!
   * @if jp
   * @brief PortConnectRetListenerType �Υ�����
   *
   * - ON_CONNECT_NEXTPORT:     notify_connect() ��Υ��������ɸƤӽФ�ľ��
   * - ON_SUBSCRIBE_INTERFACES: notify_connect() ��Υ��󥿡��ե���������ľ��
   * - ON_CONNECTED:            nofity_connect() ��³������λ���˸ƤӽФ����
   * - ON_DISCONNECT_NEXT:      notify_disconnect() ��˥��������ɸƤӽФ�ľ��
   * - ON_DISCONNECTED:         notify_disconnect() �꥿�����
   *
   * @else
   * @brief The types of PortConnectRetListenerType
   * 
   * - ON_CONNECT_NEXTPORT:     after cascade-call in notify_connect()
   * - ON_SUBSCRIBE_INTERFACES: after IF subscribing in notify_connect()
   * - ON_CONNECTED:            completed nofity_connect() connection process
   * - ON_DISCONNECT_NEXT:      after cascade-call in notify_disconnect()
   * - ON_DISCONNECTED:         completed notify_disconnect() disconnection
   *
   * @endif
   */
  enum PortConnectRetListenerType
    {
      ON_PUBLISH_INTERFACES,
      ON_CONNECT_NEXTPORT,
      ON_SUBSCRIBE_INTERFACES,
      ON_CONNECTED,
      ON_DISCONNECT_NEXT,
      ON_DISCONNECTED,
      PORT_CONNECT_RET_LISTENER_NUM
    };

   /*!
   * @if jp
   * @class PortConnectRetListener ���饹
   * @brief PortConnectRetListener ���饹
   *
   * �ƥ����������б�����桼���������ɤ��ƤФ��ľ���Υ����ߥ�
   * �ǥ����뤵���ꥹ�ʥ��饹�δ��쥯�饹��
   *
   * - ON_PUBLISH_INTERFACES:   notify_connect() ��Υ��󥿡��ե���������ľ��
   * - ON_CONNECT_NEXTPORT:     notify_connect() ��Υ��������ɸƤӽФ�ľ��
   * - ON_SUBSCRIBE_INTERFACES: notify_connect() ��Υ��󥿡��ե���������ľ��
   * - ON_CONNECTED:            nofity_connect() ��³������λ���˸ƤӽФ����
   * - ON_DISCONNECT_NEXT:      notify_disconnect() ��˥��������ɸƤӽФ�ľ��
   * - ON_DISCONNECTED:         notify_disconnect() �꥿�����
   *
   * @else
   * @class PortConnectRetListener class
   * @brief PortConnectRetListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * - ON_CONNECT_NEXTPORT:     after cascade-call in notify_connect()
   * - ON_SUBSCRIBE_INTERFACES: after IF subscribing in notify_connect()
   * - ON_CONNECTED:            completed nofity_connect() connection process
   * - ON_DISCONNECT_NEXT:      after cascade-call in notify_disconnect()
   * - ON_DISCONNECTED:         completed notify_disconnect() disconnection
   *
   * @endif
   */
  class PortConnectRetListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PortConnectRetListenerType ��ʸ������Ѵ�
     *
     * PortConnectRetListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� PortConnectRetListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert PortConnectRetListenerType into string.
     *
     * Convert PortConnectRetListenerType into string.
     *
     * @param type The target PortConnectRetListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PortConnectRetListenerType type);

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PortConnectRetListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��ؿ�
     *
     * PortConnectRetListener �Υ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PortConnectRetListener.
     *
     * @endif
     */
    virtual void operator()(const char* portname,
                            RTC::ConnectorProfile& profile,
                            ReturnCode_t ret) = 0;
  };

  //============================================================
  /*!
   * @if jp
   * @class PortConnectListenerHolder 
   * @brief PortConnectListener �ۥ�����饹
   *
   * ʣ���� PortConnectListener ���ݻ����������륯�饹��
   *
   * @else
   * @class PortConnectListenerHolder
   * @brief PortConnectListener holder class
   *
   * This class manages one ore more instances of
   * PortConnectListener class.
   *
   * @endif
   */
  class PortConnectListenerHolder
  {
    typedef std::pair<PortConnectListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    PortConnectListenerHolder();
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PortConnectListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ����ɲ�
     *
     * �ꥹ�ʡ����ɲä��롣
     *
     * @param listener �ɲä���ꥹ��
     * @param autoclean true:�ǥ��ȥ饯���Ǻ������,
     *                  false:�ǥ��ȥ饯���Ǻ�����ʤ�
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener. 
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor. 
     * @endif
     */
    void addListener(PortConnectListener* listener, bool autoclean);
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ��κ��
     *
     * �ꥹ�ʤ������롣
     *
     * @param listener �������ꥹ��
     * @else
     *
     * @brief Remove the listener. 
     *
     * This method removes the listener. 
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(PortConnectListener* listener);

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ������Τ���
     *
     * ��Ͽ����Ƥ���ꥹ�ʤΥ�����Хå��᥽�åɤ�ƤӽФ���
     *
     * @param info ConnectorInfo
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectorInfo
     * @endif
     */
    void notify(const char* portname, RTC::ConnectorProfile& profile);
      
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  /*!
   * @if jp
   * @class PortConnectRetListenerHolder
   * @brief PortConnectRetListener �ۥ�����饹
   *
   * ʣ���� PortConnectRetListener ���ݻ����������륯�饹��
   *
   * @else
   * @class PortConnectRetListenerHolder
   * @brief PortConnectRetListener holder class
   *
   * This class manages one ore more instances of
   * PortConnectRetListener class.
   *
   * @endif
   */
  class PortConnectRetListenerHolder
  {
    typedef std::pair<PortConnectRetListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    PortConnectRetListenerHolder();

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PortConnectRetListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ����ɲ�
     *
     * �ꥹ�ʡ����ɲä��롣
     *
     * @param listener �ɲä���ꥹ��
     * @param autoclean true:�ǥ��ȥ饯���Ǻ������,
     *                  false:�ǥ��ȥ饯���Ǻ�����ʤ�
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener. 
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor. 
     * @endif
     */
    void addListener(PortConnectRetListener* listener, bool autoclean);
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ��κ��
     *
     * �ꥹ�ʤ������롣
     *
     * @param listener �������ꥹ��
     * @else
     *
     * @brief Remove the listener. 
     *
     * This method removes the listener. 
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(PortConnectRetListener* listener);
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ������Τ���
     *
     * ��Ͽ����Ƥ���ꥹ�ʤΥ�����Хå��᥽�åɤ�ƤӽФ���
     *
     * @param info ConnectorInfo
     * @param cdrdata �ǡ���
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectorInfo
     * @param cdrdata Data
     * @endif
     */
    void notify(const char* portname, RTC::ConnectorProfile& profile,
                ReturnCode_t ret);
    
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };

  /*!
   * @if jp
   * @class PortConnectListeners
   * @brief PortConnectListeners ���饹
   *
   *
   * @else
   * @class PortConnectListeners
   * @brief PortConnectListeners class
   *
   *
   * @endif
   */
  class PortConnectListeners
  {
  public:
    /*!
     * @if jp
     * @brief PortConnectListenerType �ꥹ������
     * PortConnectListenerType �ꥹ�ʤ��Ǽ
     * @else
     * @brief PortConnectListenerType listener array
     * The PortConnectListenerType listener is stored. 
     * @endif
     */
    PortConnectListenerHolder 
    portconnect_[PORT_CONNECT_LISTENER_NUM];
    /*!
     * @if jp
     * @brief PortConnectRetType�ꥹ������
     * PortConnectRetType�ꥹ�ʤ��Ǽ
     * @else
     * @brief PortConnectRetType listener array
     * The PortConnectRetType listener is stored.
     * @endif
     */
    PortConnectRetListenerHolder 
    portconnret_[PORT_CONNECT_RET_LISTENER_NUM];
  };


}; // namespace RTC

#endif // RTC_PORTCONNECTLISTENER_H
