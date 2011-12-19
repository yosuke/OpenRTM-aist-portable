// -*- C++ -*-
/*!
 * @file ORBManager.cpp
 * @brief Generic ORB manager
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <assert.h>
#include <doil/ORBManager.h>
#include <doil/DefaultConfiguration.h>

namespace doil
{
  // singleton pointer initializer
  ORBManager* ORBManager::manager = NULL;
  coil::Mutex ORBManager::mutex;

  //------------------------------------------------------------
  // public functions
  //------------------------------------------------------------
  /*!
   * @if jp
   * @brief ������ؿ�
   * @else
   * @brief initializer
   * @endif
   */
  ORBManager* ORBManager::init(coil::Properties prop)
    throw()
  {
    if (!manager)
      {
        coil::Guard<coil::Mutex> guard(mutex);
        if (!manager)
          {
            manager = new ORBManager();
            //            manager->initORBManager(prop);
          }
      }
    return manager;
  };

  /*!
   * @if jp
   * @brief ���󥹥��󥹼����ؿ�
   * @else
   * @brief getting instance
   * @endif
   */
  ORBManager& ORBManager::instance()
    throw()
  {
    return *ORBManager::init(default_config);
  }


  /*!
   * @if jp
   * @brief ORBManager �� shutdown ����
   * @else
   * @brief shutdown ORBManager
   * @endif
   */
  void ORBManager::shutdown() throw()
  {
    try
      {
        m_orbs.for_each(orb_shutdown());
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return;
      }
  }
  
  /*!
   * @if jp
   * @brief ORBManager �� ORB ����Ͽ����
   * @else
   * @brief Register an ORB to the ORBManager
   * @endif
   */
  ReturnCode_t ORBManager::addORB(IORB* orb) throw()
  {
    try
      {
        if (getORB(orb->name()) != NULL) return ALREADY_EXISTS;
        m_orbs.registerObject(orb);
        return OK;
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return UNKNOWN;
      }
  }
  
  /*!
   * @if jp
   * @brief ��Ͽ�Ѥߤ� ORB ���������
   * @else
   * @brief Get an ORB that is registered in this ORBManager
   * @endif
   */
  IORB* ORBManager::getORB(const char* name) throw()
  {
    try
      {
        IORB* orb;
        orb = m_orbs.find(name);
        if (orb == NULL) return NULL;
        return orb;
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return NULL;
      }
  }
  
  /*!
   * @if jp
   * @brief ��Ͽ�ѤߤΤ��٤Ƥ� ORB ���������
   * @else
   * @brief Get all the ORBs that are registered in this ORBManager
   * @endif
   */
  const std::vector<IORB*> ORBManager::getORBs() throw()
  {
    try
      {
        collect_orbs o;
        o = m_orbs.for_each(o);
        return o.orbs_;
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return std::vector<IORB*>();
      }
  }
  
  /*!
   * @if jp
   * @brief ��Ͽ�ѤߤΤ��٤Ƥ� ORB ��̾�����������
   * @else
   * @brief Get all the ORBs' name that are registered in this ORBManager
   * @endif
   */
  const std::vector<std::string> ORBManager::availableORBs() throw()
  {
    try
      {
        available_orbs o;
        o = m_orbs.for_each(o);
        return o.orbs_;
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return std::vector<std::string>();
      }
  }
  
  /*!
   * @if jp
   * @brief ��Ͽ�Ѥߤ� ORB �� ORBManager �Υꥹ�Ȥ���������
   * @else
   * @brief Delete registered ORB by name.
   * @endif
   */
  IORB* ORBManager::deleteORB(const char* name) throw()
  {
    if (name == NULL) return NULL;
    try
      {
        return m_orbs.unregisterObject(name);
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return NULL;
      }
  }
  
  /*!
   * @if jp
   * @brief ���֥������Ȥ򥢥��ƥ��ֲ�����
   * @else
   * @brief Activate object
   * @endif
   */
  ReturnCodes
  ORBManager::activateObject(ImplBase* impl,
                             const char* orbname) throw()
  {
    if (impl == NULL || orbname == NULL) return ReturnCodes(INVALID_ARGS);
    if (getObject(impl->name()) != NULL) return ReturnCodes(ALREADY_EXISTS);

    try
      {
        activate_impl a(impl, orbname);
        a = m_orbs.for_each(a);
        return a.retcodes_;
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return ReturnCodes();
      }
  }
  
  /*!
   * @if jp
   * @brief ���֥������Ȥ��󥢥��ƥ��ֲ�����
   * @else
   * @brief Deactivate object
   * @endif
   */
  ReturnCodes
  ORBManager::deactivateObject(ImplBase* impl,
                               const char* orbname) throw()
  {
    if (impl == NULL || orbname == NULL) return INVALID_ARGS;
    if (getObject(impl->name()) == NULL) return NOT_FOUND;

    try
      {
        deactivate_impl d(impl, orbname);
        d = m_orbs.for_each(d);
        return d.retcodes_;
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return ReturnCodes();
      }
  }
  
  ReturnCodes
  ORBManager::deactivateObject(const char* name,
                               const char* orbname) throw()
  {
    if (name == NULL || orbname == NULL) return INVALID_ARGS;
    if (getObject(name) == NULL) return NOT_FOUND;

    try
      {
        deactivate_by_name d(name, orbname);
        d = m_orbs.for_each(d);
        return d.retcodes_;
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return ReturnCodes();
      }
  }
  
  const std::vector<ImplBase*> ORBManager::getObjects() throw()
  {
    try
      {
        collect_impl o;
        o = m_impls.for_each(o);
        return o.impls_;
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return std::vector<ImplBase*>();
      }
  }
  
  
  ImplBase* ORBManager::getObject(const char* name) throw()
  {
    if (name == NULL) return NULL;
    try
      {
        return m_impls.find(name);
      }
    catch (...)
      {
        // should never come here
        assert(false);
        return NULL;
      }
  }

  //------------------------------------------------------------
  // private functions
  //------------------------------------------------------------

};
