// -*- C++ -*-
/*!
 * @file ComponentActionListener.cpp
 * @brief Component action listener class
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

#include <rtm/ComponentActionListener.h>

namespace RTC
{

  //============================================================
  /*!
   * @if jp
   * @class PostComponentActionListener ���饹
   * @else
   * @class PostComponentActionListener class
   * @endif
   */
  PostComponentActionListener::~PostComponentActionListener(){}

  /*!
   * @if jp
   * @class PreComponentActionListener ���饹
   * @else
   * @class PreComponentActionListener class
   * @endif
   */
  PreComponentActionListener::~PreComponentActionListener(){}

  /*!
   * @if jp
   * @class PortActionListener ���饹
   * @else
   * @class PortActionListener class
   * @endif
   */
  PortActionListener::~PortActionListener(){}
  
  /*!
   * @if jp
   * @class ExecutionContextActionListener ���饹
   * @else
   * @class ExecutionContextActionListener class
   * @endif
   */
  ExecutionContextActionListener::~ExecutionContextActionListener(){}
  




  //============================================================
  /*!
   * @if jp
   * @class PreComponentActionListener �ۥ�����饹
   * @else
   * @class PreComponentActionListener holder class
   * @endif
   */
  PreComponentActionListenerHolder::PreComponentActionListenerHolder()
  {
  }
    
  
  PreComponentActionListenerHolder::~PreComponentActionListenerHolder()
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        if (m_listeners[i].second)
          {
            delete m_listeners[i].first;
          }
      }
  }

  
  void PreComponentActionListenerHolder::
  addListener(PreComponentActionListener* listener,
              bool autoclean)
  {
    Guard guard(m_mutex);
    m_listeners.push_back(Entry(listener, autoclean));
  }
  
  
  void PreComponentActionListenerHolder::
  removeListener(PreComponentActionListener* listener)
  {
    Guard guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());
    
    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }
    
  }
  
  
  void PreComponentActionListenerHolder::notify(UniqueId ec_id)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(ec_id);
      }
  }

  //============================================================
  /*!
   * @if jp
   * @class PostComponentActionListener �ۥ�����饹
   * @else
   * @class PostComponentActionListener holder class
   * @endif
   */
  PostComponentActionListenerHolder::PostComponentActionListenerHolder()
  {
  }
  

  PostComponentActionListenerHolder::~PostComponentActionListenerHolder()
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        if (m_listeners[i].second)
          {
            delete m_listeners[i].first;
          }
      }
  }

  
  void PostComponentActionListenerHolder::
  addListener(PostComponentActionListener* listener, bool autoclean)
  {
    Guard guard(m_mutex);
    m_listeners.push_back(Entry(listener, autoclean));
  }

  
  void PostComponentActionListenerHolder::
  removeListener(PostComponentActionListener* listener)
  {
    Guard guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());
    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }
    
  }

    
  void PostComponentActionListenerHolder::notify(UniqueId ec_id,
                                                 ReturnCode_t ret)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(ec_id, ret);
      }
  }


  /*!
   * @if jp
   * @class PortActionListener �ۥ�����饹
   * @else
   * @class PortActionListener holder class
   * @endif
   */
  PortActionListenerHolder::PortActionListenerHolder()
  {
  }
    
  
  PortActionListenerHolder::~PortActionListenerHolder()
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        if (m_listeners[i].second)
          {
            delete m_listeners[i].first;
          }
      }
  }

  
  void PortActionListenerHolder::addListener(PortActionListener* listener,
                                             bool autoclean)
  {
    Guard guard(m_mutex);
    m_listeners.push_back(Entry(listener, autoclean));
  }
  
  
  void PortActionListenerHolder::removeListener(PortActionListener* listener)
  {
    Guard guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());
    
    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }
    
  }
  
  
  void PortActionListenerHolder::notify(const RTC::PortProfile& pprofile)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(pprofile);
      }
  }



  /*!
   * @if jp
   * @class ExecutionContextActionListener �ۥ�����饹
   * @else
   * @class ExecutionContextActionListener holder class
   * @endif
   */
  ExecutionContextActionListenerHolder::ExecutionContextActionListenerHolder()
  {
  }
    
  
  ExecutionContextActionListenerHolder::~ExecutionContextActionListenerHolder()
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        if (m_listeners[i].second)
          {
            delete m_listeners[i].first;
          }
      }
  }

  
  void ExecutionContextActionListenerHolder::
  addListener(ExecutionContextActionListener* listener,
              bool autoclean)
  {
    Guard guard(m_mutex);
    m_listeners.push_back(Entry(listener, autoclean));
  }
  
  
  void ExecutionContextActionListenerHolder::
  removeListener(ExecutionContextActionListener* listener)
  {
    Guard guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());
    
    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }
    
  }
  
  
  void ExecutionContextActionListenerHolder::notify(UniqueId ec_id)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(ec_id);
      }
  }

};


