// -*- C++ -*-
/*!
 * @file ComponentActionListener.h
 * @brief component action listener class
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

#ifndef RTC_COMPONENTACTIONLISTENER_H
#define RTC_COMPONENTACTIONLISTENER_H

#include <vector>
#include <utility>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <rtm/RTC.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/ConnectorBase.h>

namespace RTC
{
  typedef ExecutionContextHandle_t UniqueId;
  //============================================================
  /*!
   * @if jp
   * @brief PreComponentActionListener �Υ�����
   *
   * - PRE_ON_INITIALIZE:    onInitialize ľ��
   * - PRE_ON_FINALIZE:      onFinalize ľ��
   * - PRE_ON_STARTUP:       onStartup ľ��
   * - PRE_ON_SHUTDOWN:      onShutdown ľ��
   * - PRE_ON_ACTIVATED:     onActivated ľ��
   * - PRE_ON_DEACTIVATED:   onDeactivated ľ��
   * - PRE_ON_ABORTING:      onAborted ľ��
   * - PRE_ON_ERROR:         onError ľ��
   * - PRE_ON_RESET:         onReset ľ��
   * - PRE_ON_EXECUTE:       onExecute ľ��
   * - PRE_ON_STATE_UPDATE:  onStateUpdate ľ��
   * - PRE_ON_RATE_CHANGED:  onRateChanged ľ��
   *
   * @else
   * @brief The types of ConnectorDataListener
   * 
   * @endif
   */

  enum PreComponentActionListenerType
    {
      PRE_ON_INITIALIZE,
      PRE_ON_FINALIZE,
      PRE_ON_STARTUP,
      PRE_ON_SHUTDOWN,
      PRE_ON_ACTIVATED,
      PRE_ON_DEACTIVATED,
      PRE_ON_ABORTING,
      PRE_ON_ERROR,
      PRE_ON_RESET,
      PRE_ON_EXECUTE,
      PRE_ON_STATE_UPDATE,
      PRE_ON_RATE_CHANGED,
      PRE_COMPONENT_ACTION_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class PreComponentActionListener ���饹
   * @brief PreComponentActionListener ���饹
   *
   * OMG RTC���ͤ��������Ƥ���ʲ��Υ���ݡ��ͥ�ȥ��������ȤˤĤ�
   * �ơ�
   *
   * - on_initialize()
   * - on_finalize()
   * - on_startup()
   * - on_shutdown()
   * - on_activated
   * - on_deactivated()
   * - on_aborted()
   * - on_error()
   * - on_reset()
   * - on_execute()
   * - on_state_update()
   * - on_rate_changed()
   *
   * �ƥ����������б�����桼���������ɤ��ƤФ��ľ���Υ����ߥ�
   * �ǥ����뤵���ꥹ�ʥ��饹�δ��쥯�饹��
   *
   * - PRE_ON_INITIALIZE:
   * - PRE_ON_FINALIZE:
   * - PRE_ON_STARTUP:
   * - PRE_ON_SHUTDOWN:
   * - PRE_ON_ACTIVATED:
   * - PRE_ON_DEACTIVATED:
   * - PRE_ON_ABORTING:
   * - PRE_ON_ERROR:
   * - PRE_ON_RESET:
   * - PRE_IN_EXECUTE:
   * - PRE_ON_STATE_UPDATE:
   * - PRE_ON_RATE_CHANGED:
   *
   * @else
   * @class PreComponentActionListener class
   * @brief PreComponentActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class PreComponentActionListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PreComponentActionListenerType ��ʸ������Ѵ�
     *
     * PreComponentActionListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� PreComponentActionListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert PreComponentActionListenerType into the string.
     *
     * Convert PreComponentActionListenerType into the string.
     *
     * @param type The target PreComponentActionListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PreComponentActionListenerType type)
    {
      static const char* typeString[] =
        {
          "PRE_ON_INITIALIZE",
          "PRE_ON_FINALIZE",
          "PRE_ON_STARTUP",
          "PRE_ON_SHUTDOWN",
          "PRE_ON_ACTIVATED",
          "PRE_ON_DEACTIVATED",
          "PRE_ON_ABORTING",
          "PRE_ON_ERROR",
          "PRE_ON_RESET",
          "PRE_ON_EXECUTE",
          "PRE_ON_STATE_UPDATE",
          "PRE_ON_RATE_CHANGED",
          "PRE_COMPONENT_ACTION_LISTENER_NUM"
        };
      if (type < PRE_COMPONENT_ACTION_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PreComponentActionListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��ؿ�
     *
     * PreComponentActionListener �Υ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PreComponentActionListener.
     *
     * @endif
     */
    virtual void operator()(UniqueId ec_id) = 0;
  };


  //============================================================
  /*!
   * @if jp
   * @brief PostCompoenntActionListener �Υ�����
   *
   * - POST_ON_INITIALIZE:
   * - POST_ON_FINALIZE:
   * - POST_ON_STARTUP:
   * - POST_ON_SHUTDOWN:
   * - POST_ON_ACTIVATED:
   * - POST_ON_DEACTIVATED:
   * - POST_ON_ABORTING:
   * - POST_ON_ERROR:
   * - POST_ON_RESET:
   * - POST_ON_EXECUTE:
   * - POST_ON_STATE_UPDATE:
   * - POST_ON_RATE_CHANGED:
   *
   * @else
   * @brief The types of ConnectorDataListener
   * 
   * @endif
   */
  enum PostComponentActionListenerType
    {
      POST_ON_INITIALIZE,
      POST_ON_FINALIZE,
      POST_ON_STARTUP,
      POST_ON_SHUTDOWN,
      POST_ON_ACTIVATED,
      POST_ON_DEACTIVATED,
      POST_ON_ABORTING,
      POST_ON_ERROR,
      POST_ON_RESET,
      POST_ON_EXECUTE,
      POST_ON_STATE_UPDATE,
      POST_ON_RATE_CHANGED,
      POST_COMPONENT_ACTION_LISTENER_NUM
    };


  /*!
   * @if jp
   * @class PostComponentActionListener ���饹
   * @brief PostComponentActionListener ���饹
   *
   * OMG RTC���ͤ��������Ƥ���ʲ��Υ���ݡ��ͥ�ȥ��������ȤˤĤ�
   * �ơ�
   *
   * - on_initialize()
   * - on_finalize()
   * - on_startup()
   * - on_shutdown()
   * - on_activated
   * - on_deactivated()
   * - on_aborted()
   * - on_error()
   * - on_reset()
   * - on_execute()
   * - on_state_update()
   * - on_rate_changed()
   *
   * �ƥ����������б�����桼���������ɤ��ƤФ��ľ���Υ����ߥ�
   * �ǥ����뤵���ꥹ�ʥ��饹�δ��쥯�饹��
   *
   * - POST_ON_INITIALIZE:
   * - POST_ON_FINALIZE:
   * - POST_ON_STARTUP:
   * - POST_ON_SHUTDOWN:
   * - POST_ON_ACTIVATED:
   * - POST_ON_DEACTIVATED:
   * - POST_ON_ABORTING:
   * - POST_ON_ERROR:
   * - POST_ON_RESET:
   * - POST_ON_EXECUTE:
   * - POST_ON_STATE_UPDATE:
   * - POST_ON_RATE_CHANGED:
   *
   * @else
   * @class PostComponentActionListener class
   * @brief PostComponentActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class PostComponentActionListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PostComponentActionListenerType ��ʸ������Ѵ�
     *
     * PostComponentActionListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� PostComponentActionListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert PostComponentActionListenerType into the string.
     *
     * Convert PostComponentActionListenerType into the string.
     *
     * @param type The target PostComponentActionListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PostComponentActionListenerType type)
    {
      static const char* typeString[] =
        {
          "POST_ON_INITIALIZE",
          "POST_ON_FINALIZE",
          "POST_ON_STARTUP",
          "POST_ON_SHUTDOWN",
          "POST_ON_ACTIVATED",
          "POST_ON_DEACTIVATED",
          "POST_ON_ABORTING",
          "POST_ON_ERROR",
          "POST_ON_RESET",
          "POST_ON_EXECUTE",
          "POST_ON_STATE_UPDATE",
          "POST_ON_RATE_CHANGED",
          "POST_COMPONENT_ACTION_LISTENER_NUM"
        };
      if (type < POST_COMPONENT_ACTION_LISTENER_NUM)
        {
          return typeString[type];
        }
      return "";
    }

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PostComponentActionListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��ؿ�
     *
     * PostComponentActionListener �Υ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PostComponentActionListener.
     *
     * @endif
     */
    virtual void operator()(UniqueId ec_id,
                            ReturnCode_t ret) = 0;
  };

  //============================================================
  /*!
   * @if jp
   * @brief PortActionListener �Υ�����
   *
   * - ADD_PORT:             Port �ɲû�
   * - REMOVE_PORT:          Port �����
   *
   * @else
   * @brief The types of PortActionListener
   * 
   * @endif
   */

  enum PortActionListenerType
    {
      ADD_PORT,
      REMOVE_PORT,
      PORT_ACTION_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class PortActionListener ���饹
   * @brief PortActionListener ���饹
   *
   * �ƥ����������б�����桼���������ɤ��ƤФ��ľ���Υ����ߥ�
   * �ǥ����뤵���ꥹ�ʥ��饹�δ��쥯�饹��
   *
   * - ADD_PORT:
   * - REMOVE_PORT:
   *
   * @else
   * @class PortActionListener class
   * @brief PortActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class PortActionListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PreComponentActionListenerType ��ʸ������Ѵ�
     *
     * PreComponentActionListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� PreComponentActionListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert PreComponentActionListenerType into the string.
     *
     * Convert PreComponentActionListenerType into the string.
     *
     * @param type The target PreComponentActionListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PortActionListenerType type)
    {
      static const char* typeString[] =
        {
          "ADD_PORT",
          "REMOVE_PORT",
          "PORT_ACTION_LISTENER_NUM"
        };
      if (type < PORT_ACTION_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PortActionListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��ؿ�
     *
     * PortActionListener �Υ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PortActionListener
     *
     * @endif
     */
    virtual void operator()(const ::RTC::PortProfile& pprof) = 0;
  };


  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContextActionListener �Υ�����
   *
   * - ADD_PORT:             ExecutionContext �ɲû�
   * - REMOVE_PORT:          ExecutionContext �����
   *
   * @else
   * @brief The types of ExecutionContextActionListener
   * 
   * @endif
   */

  enum ExecutionContextActionListenerType
    {
      EC_ATTACHED,
      EC_DETACHED,
      EC_ACTION_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class ExecutionContextActionListener ���饹
   * @brief ExecutionContextActionListener ���饹
   *
   * �ƥ����������б�����桼���������ɤ��ƤФ��ľ���Υ����ߥ�
   * �ǥ����뤵���ꥹ�ʥ��饹�δ��쥯�饹��
   *
   * - ADD_PORT:
   * - REMOVE_PORT:
   *
   * @else
   * @class ExecutionContextActionListener class
   * @brief ExecutionContextActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class ExecutionContextActionListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PreComponentActionListenerType ��ʸ������Ѵ�
     *
     * PreComponentActionListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� PreComponentActionListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert PreComponentActionListenerType into the string.
     *
     * Convert PreComponentActionListenerType into the string.
     *
     * @param type The target PreComponentActionListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(ExecutionContextActionListenerType type)
    {
      static const char* typeString[] =
        {
          "ATTACH_EC",
          "DETACH_ECT",
          "EC_ACTION_LISTENER_NUM"
        };
      if (type < EC_ACTION_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ExecutionContextActionListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��ؿ�
     *
     * ExecutionContextActionListener �Υ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for ExecutionContextActionListener
     *
     * @endif
     */
    virtual void operator()(UniqueId ec_id) = 0;
  };



  //============================================================
  /*!
   * @if jp
   * @class PreComponentActionListenerHolder 
   * @brief PreComponentActionListener �ۥ�����饹
   *
   * ʣ���� PreComponentActionListener ���ݻ����������륯�饹��
   *
   * @else
   * @class PreComponentActionListenerHolder
   * @brief PreComponentActionListener holder class
   *
   * This class manages one ore more instances of
   * PreComponentActionListener class.
   *
   * @endif
   */
  class PreComponentActionListenerHolder
  {
    typedef std::pair<PreComponentActionListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    PreComponentActionListenerHolder();
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PreComponentActionListenerHolder();
    
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
    void addListener(PreComponentActionListener* listener, bool autoclean);
    
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
    void removeListener(PreComponentActionListener* listener);

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
    void notify(UniqueId ec_id);
      
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  /*!
   * @if jp
   * @class PostComponentActionListenerHolder
   * @brief PostComponentActionListener �ۥ�����饹
   *
   * ʣ���� PostComponentActionListener ���ݻ����������륯�饹��
   *
   * @else
   * @class PostComponentActionListenerHolder
   * @brief PostComponentActionListener holder class
   *
   * This class manages one ore more instances of
   * PostComponentActionListener class.
   *
   * @endif
   */
  class PostComponentActionListenerHolder
  {
    typedef std::pair<PostComponentActionListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    PostComponentActionListenerHolder();
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PostComponentActionListenerHolder();
    
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
    void addListener(PostComponentActionListener* listener, bool autoclean);
    
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
    void removeListener(PostComponentActionListener* listener);
    
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
    void notify(UniqueId ec_id, ReturnCode_t ret);
    
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  //============================================================
  /*!
   * @if jp
   * @class PortActionListenerHolder
   * @brief PortActionListener �ۥ�����饹
   *
   * ʣ���� PortActionListener ���ݻ����������륯�饹��
   *
   * @else
   * @class PortActionListenerHolder
   * @brief PortActionListener holder class
   *
   * This class manages one ore more instances of
   * PortActionListener class.
   *
   * @endif
   */
  class PortActionListenerHolder
  {
    typedef std::pair<PortActionListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    PortActionListenerHolder();
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PortActionListenerHolder();
    
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
    void addListener(PortActionListener* listener, bool autoclean);
    
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
    void removeListener(PortActionListener* listener);
    
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
    void notify(const RTC::PortProfile& pprofile);
    
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };

  /*!
   * @if jp
   * @class ExecutionContextActionListenerHolder
   * @brief ExecutionContextActionListener �ۥ�����饹
   *
   * ʣ���� ExecutionContextActionListener ���ݻ����������륯�饹��
   *
   * @else
   * @class ExecutionContextActionListenerHolder
   * @brief ExecutionContextActionListener holder class
   *
   * This class manages one ore more instances of
   * ExecutionContextActionListener class.
   *
   * @endif
   */
  class ExecutionContextActionListenerHolder
  {
    typedef std::pair<ExecutionContextActionListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    ExecutionContextActionListenerHolder();
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ExecutionContextActionListenerHolder();
    
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
    void addListener(ExecutionContextActionListener* listener, bool autoclean);
    
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
    void removeListener(ExecutionContextActionListener* listener);
    
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
    void notify(UniqueId ec_id);
    
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  /*!
   * @if jp
   * @class ComponentActionListeners
   * @brief ComponentActionListeners ���饹
   *
   *
   * @else
   * @class ComponentActionListeners
   * @brief ComponentActionListeners class
   *
   *
   * @endif
   */
  class ComponentActionListeners
  {
  public:
    /*!
     * @if jp
     * @brief PreComponentActionListenerType�ꥹ������
     * PreComponentActionListenerType�ꥹ�ʤ��Ǽ
     * @else
     * @brief PreComponentActionListenerType listener array
     * The PreComponentActionListenerType listener is stored. 
     * @endif
     */
    PreComponentActionListenerHolder 
    preaction_[PRE_COMPONENT_ACTION_LISTENER_NUM];
    /*!
     * @if jp
     * @brief PostComponentActionType�ꥹ������
     * PostComponentActionType�ꥹ�ʤ��Ǽ
     * @else
     * @brief PostComponentActionType listener array
     * The PostComponentActionType listener is stored.
     * @endif
     */
    PostComponentActionListenerHolder 
    postaction_[POST_COMPONENT_ACTION_LISTENER_NUM];
    /*!
     * @if jp
     * @brief PortActionType�ꥹ������
     * PortActionType�ꥹ�ʤ��Ǽ
     * @else
     * @brief PortActionType listener array
     * The PortActionType listener is stored.
     * @endif
     */
    PortActionListenerHolder
    portaction_[PORT_ACTION_LISTENER_NUM];
    /*!
     * @if jp
     * @brief ExecutionContextActionType�ꥹ������
     * ExecutionContextActionType�ꥹ�ʤ��Ǽ
     * @else
     * @brief ExecutionContextActionType listener array
     * The ExecutionContextActionType listener is stored.
     * @endif
     */
   ExecutionContextActionListenerHolder
    ecaction_[EC_ACTION_LISTENER_NUM];
  };


}; // namespace RTC

#endif // RTC_COMPONENTACTIONLISTENER_H
