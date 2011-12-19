// -*- C++ -*-
/*!
 * @file Listener.h
 * @brief Listener class
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Listener.h 826 2008-08-26 08:13:39Z n-ando $
 *
 */

#ifndef Listener_h
#define Listener_h


/*!
 * @if jp
 * @class ListenerBase
 * @brief ListenerBase ���饹
 *
 * �����ޡ�����Ͽ����ꥹ�ʡ�����ݥ��󥿡��ե��������饹��
 *
 * @since 0.4.0
 *
 * @else
 * @class ListenerBase
 * @brief ListenerBase class
 *
 * This is the abstract interface for Listener that registers
 * to the timer
 *
 * @since 0.4.0
 *
 * @endif
 */
class ListenerBase
{
public:
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
  virtual ~ListenerBase(){}
  
  /*!
   * @if jp
   * @brief ������Хå�����
   *
   * ������Хå������ѽ�貾�۴ؿ�
   *
   * @else
   * @brief Callback
   *
   * Pure virtual function for callback-handling
   *
   * @endif
   */
  virtual void invoke() = 0;
};

/*!
 * @if jp
 * @class ListenerObject
 * @brief ListenerObject ���饹
 *
 * �����ޡ�����Ͽ����ꥹ�ʡ��Ѵ��쥯�饹��
 *
 * @since 0.4.0
 *
 * @else
 * @class ListenerObject
 * @brief ListenerObject class
 *
 * This is a base class for Listener that registers to the timer
 *
 * @since 0.4.0
 *
 * @endif
 */
template <class ListenerClass,
	  class CallbackFunc = void (ListenerClass::*)()>
class ListenerObject
  : public ListenerBase
{
public:
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   *
   * ���󥹥ȥ饯��
   *
   * @param obj �ꥹ�ʡ����֥�������
   * @param cbf ������Хå��Ѵؿ�
   *
   * @else
   * @brief Constructor
   *
   * Constructor
   *
   * @param obj Listener Object
   * @param cbf Callback Function
   *
   * @endif
   */
  ListenerObject(ListenerClass* obj, CallbackFunc cbf)
    : m_obj(obj), m_cbf(cbf)
  {
  }
  
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
  virtual ~ListenerObject()
  {
  }
  
  /*!
   * @if jp
   * @brief ������Хå��ѽ���
   *
   * ������Хå������Ѵؿ�
   *
   * @else
   * @brief Callback
   *
   * Callback function
   *
   * @endif
   */
  virtual void invoke()
  {
    (m_obj->*m_cbf)();
  }
  
private:
  ListenerClass* m_obj;
  CallbackFunc m_cbf;
};

/*!
 * @if jp
 * @class ListenerFunc
 * @brief ListenerFunc ���饹
 *
 * ������Хå��ѥ��֥������ȡ�
 *
 * @since 0.4.0
 *
 * @else
 * @class ListenerFunc
 * @brief ListenerFunc class
 *
 * Callback object
 *
 * @since 0.4.0
 *
 * @endif
 */
typedef void (*CallbackFunc)();
class ListenerFunc
  : public ListenerBase
{
public:
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   *
   * ���󥹥ȥ饯��
   *
   * @param cbf ������Хå��Ѵؿ�
   *
   * @else
   * @brief Constructor
   *
   * Constructor
   *
   * @param cbf Callback Function
   *
   * @endif
   */
  ListenerFunc(CallbackFunc cbf)
    : m_cbf(cbf)
  {
  }
  
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
  virtual ~ListenerFunc(){}
  
  /*!
   * @if jp
   * @brief ������Хå�����
   *
   * ������Хå������Ѵؿ�
   *
   * @else
   * @brief Callback
   *
   * Callback function
   *
   * @endif
   */
  virtual void invoke()
  {
    (*m_cbf)();
  }
  
private:
  CallbackFunc m_cbf;
};

#endif // Listener_h
