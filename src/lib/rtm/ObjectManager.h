// -*- C++ -*-
/*!
 * @file ObjectManager.h
 * @brief Object management class
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ObjectManager.h 1569 2009-11-12 14:36:47Z n-ando $
 *
 */

#ifndef RTC_OBJECTMANAGER_H
#define RTC_OBJECTMANAGER_H

#include <rtm/RTC.h>

#include <vector>
#include <string>
#include <algorithm>

#include <coil/Mutex.h>
#include <coil/Guard.h>

/*!
 * @if jp
 *
 * @brief ���֥������ȴ����ѥ��饹
 *
 * �Ƽ索�֥������Ȥ�������뤿��Υ��饹��
 *
 * @since 0.4.0
 *
 * @else
 *
 * @brief Class for managing objects
 *
 * This is a class for managing various objects.
 *
 * @since 0.4.0
 *
 * @endif
 */
template <typename Identifier, typename Object, typename Predicate>
class ObjectManager
{
public:
  typedef std::vector<Object*>                  ObjectVector;
  typedef typename ObjectVector::iterator       ObjectVectorItr;
  typedef typename ObjectVector::const_iterator ObjectVectorConstItr;
  typedef coil::Mutex Mutex;
  typedef coil::Guard<coil::Mutex> Guard;
  /*!
   * @if jp
   *
   * @brief ���󥹥ȥ饯��
   * 
   * ���󥹥ȥ饯��
   * 
   * @else
   *
   * @brief Constructor
   * 
   * Constructor
   * 
   * @endif
   */
  ObjectManager(){};
  
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
  ~ObjectManager(void){};
  
  /*!
   * @if jp
   *
   * @brief ���ꤷ�����֥������Ȥ���Ͽ����
   * 
   * ���ꤷ�����֥������Ȥ���Ͽ���롣
   * Ʊ�쥪�֥������Ȥ���Ͽ�Ѥߤξ��ϡ�����Ԥ�ʤ���
   *
   * @param obj ��Ͽ�оݥ��֥�������
   *
   * @return ��Ͽ�������(���֥������Ȥ���Ͽ��������true)
   * 
   * @else
   *
   * @brief Register the specified object
   * 
   * Register the object that was specified.
   * If the same object is already registered, this does not anything.
   *
   * @param obj The target object for the registration
   *
   * @return Registration result (True if object was registerd)
   * 
   * @endif
   */
  bool registerObject(Object* obj)
  {
    ObjectVectorItr it;
    Guard guard(m_objects._mutex);
    
    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(obj));
    if (it == m_objects._obj.end())
      {
	m_objects._obj.push_back(obj);
	return true;
      }
    return false;
  }
  
  /*!
   * @if jp
   *
   * @brief ���ꤷ�����֥������Ȥ���Ͽ�������
   * 
   * ���ꤷ�����֥������Ȥ���Ͽ���������������롣
   * ���ꤷ�����֥������Ȥ���Ͽ����Ƥ��ʤ����ˤ�NULL���֤���
   *
   * @param id ��Ͽ����оݥ��֥������Ȥ�ID
   *
   * @return ��Ͽ������줿���֥�������
   * 
   * @else
   *
   * @brief Unregister the specified object
   * 
   * Unregister the object that was specified and get it.
   * This operation returns NULL if the specified object is not 
   * registered.
   *
   * @param id ID of the target object for the unregistration
   *
   * @return Unregistered object
   * @endif
   */
  Object* unregisterObject(const Identifier& id)
  {
    ObjectVectorItr it;
    Guard guard(m_objects._mutex);
    
    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(id));
    if (it != m_objects._obj.end())
      {
	Object* obj(*it);
	m_objects._obj.erase(it);
	return obj;
      }
    return NULL;;
  }
  
  /*!
   * @if jp
   *
   * @brief ���֥������Ȥ򸡺�����
   * 
   * ��Ͽ����Ƥ��륪�֥������Ȥ��椫����ꤷ�����˹��פ��륪�֥������Ȥ򸡺�
   * ���Ƽ������롣
   * ���ꤷ�����˹��פ��륪�֥������Ȥ���Ͽ����Ƥ��ʤ����ˤ�NULL���֤���
   *
   * @param id �����оݥ��֥������Ȥ�ID
   *
   * @return ���֥������Ȥθ������
   * 
   * @else
   *
   * @brief Find the object
   * 
   * Find the object that matches the specified condition among the registered
   * objects and get it.
   * This operation returns NULL if the object that does matches the specified
   * condition is not registered.
   *
   * @param id ID of the target object for finding
   *
   * @return Result of finding object
   * 
   * @endif
   */
  Object* find(const Identifier& id) const
  {
    ObjectVectorConstItr it;
    Guard guard(m_objects._mutex);
    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(id));
    if (it != m_objects._obj.end())
      {
	return *it;
      }
    return NULL;
  }
  
  /*!
   * @if jp
   *
   * @brief ��Ͽ����Ƥ��륪�֥������ȤΥꥹ�Ȥ��������
   * 
   * ��Ͽ����Ƥ��륪�֥������ȤΥꥹ�Ȥ�������롣
   *
   * @return ��Ͽ����Ƥ��륪�֥������ȡ��ꥹ��
   * 
   * @else
   *
   * @brief Get a list of obejects that are registerd
   * 
   * Get a list of objects that are registerd.
   *
   * @return List of registerd objects.
   * 
   * @endif
   */
  std::vector<Object*> getObjects() const
  {
    Guard guard(m_objects._mutex);
    return m_objects._obj;
  }
  
  /*!
   * @if jp
   * @brief ���֥������ȸ����ѥե��󥯥�
   * @else
   * @brief Functor for searching object
   * @endif
   */
  template <class Pred>
  Pred for_each(Pred p)
  {
    Guard guard(m_objects._mutex);
    return std::for_each(m_objects._obj.begin(), m_objects._obj.end(), p);
  }
  
  /*!
   * @if jp
   * @brief ���֥������ȸ����ѥե��󥯥�
   * @else
   * @brief Functor for searching object
   * @endif
   */
  template <class Pred>
  Pred for_each(Pred p) const
  {
    Guard guard(m_objects._mutex);
    return std::for_each(m_objects._obj.begin(), m_objects._obj.end(), p);
  }
  
protected:
  /*!
   * @if jp
   * @brief ���֥������ȴ����ѹ�¤��
   * @else
   * @brief The structure for object management
   * @endif
   */
  struct Objects
  {
    mutable Mutex _mutex;
    ObjectVector _obj;
  };
  /*!
   * @if jp
   * @brief ��Ͽ�Ѥߥ��֥������ȡ��ꥹ��
   * @else
   * @brief The list of registered objects
   * @endif
   */
  Objects m_objects;
};
#endif // RTC_OBJECTMANAGER_H
