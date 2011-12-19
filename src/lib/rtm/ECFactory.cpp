// -*- C++ -*-
/*!
 * @file ECFactory.cpp
 * @brief ExecutionContext fuctory class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ECFactory.cpp 1034 2008-11-10 10:32:16Z kojima $
 *
 */

#include <rtm/RTC.h>
#include <rtm/ECFactory.h>

namespace RTC 
{
  
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  ECFactoryCXX::ECFactoryCXX(const char* name,
			     ECNewFunc new_func,
			     ECDeleteFunc delete_func)
    : m_name(name),
      m_New(new_func),
      m_Delete(delete_func)
  {
  }
  
  /*!
   * @if jp
   * @brief ���ۥǥ��ȥ饯��
   * @else
   * @brief Virtual destructor
   * @endif
   */
  ECFactoryCXX::~ECFactoryCXX()
  {
  }
  
  /*!
   * @if jp
   * @brief �����о�ExecutionContext̾�Τ����
   * @else
   * @brief Get names of the target ExecutionContext for creation
   * @endif
   */
  const char* ECFactoryCXX::name()
  {
    return m_name.c_str();
  }
  
  /*!
   * @if jp
   * @brief �����о�ExecutionContext���󥹥��󥹤�����
   * @else
   * @brief Create the target ExecutionContext's instances
   * @endif
   */
  ExecutionContextBase* ECFactoryCXX::create()
  {
    return m_New();
  }
  
  /*!
   * @if jp
   * @brief �о�ExecutionContext���󥹥��󥹤��˴�
   * @else
   * @brief Destroy the target ExecutionContext's instances
   * @endif
   */
  void ECFactoryCXX::destroy(ExecutionContextBase* ec)
  {
    m_Delete(ec);
  }
  
};
