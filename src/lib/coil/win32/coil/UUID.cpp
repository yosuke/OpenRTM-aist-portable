// -*- C++ -*-
/*!
 * @file  MutexPosix.h
 * @brief RT-Middleware Service interface
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
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

#include <coil/UUID.h>

namespace coil
{
  //------------------------------------------------------------
  // UUID class
  //------------------------------------------------------------
  /*!
   * @if jp
   * @brief UUID�N���X �R���X�g���N�^
   * @else
   * @brief UUID class constructor
   * @endif
   */
  UUID::UUID()
    : m_uuidstr(0)
  {
  }
  
  /*!
   * @if jp
   * @brief UUID�N���X �R���X�g���N�^
   * @else
   * @brief UUID class constructor
   * @endif
   */
  UUID::UUID(const uuid_t& uuid)
    : m_uuid(uuid), m_uuidstr(0)
  {
  }

  /*!
   * @if jp
   * @brief UUID�N���X �f�X�g���N�^
   * @else
   * @brief UUID class destructor
   * @endif
   */
  UUID::~UUID()
  {
    ::RpcStringFreeA((RPC_CSTR*)&m_uuidstr);
  }

  /*!
   * @if jp
   * @brief UUID�l�𕶎���ɕϊ�����
   * @else
   * @brief Converting from UUID value to string
   * @endif
   */
  const char* UUID::to_string()
  {
    if(::UuidToStringA(&m_uuid, (RPC_CSTR*)&m_uuidstr)
       != RPC_S_OK)
      {
        return 0;
      }
    else
      {
        return m_uuidstr;
      }
  }
    
  //------------------------------------------------------------
  // UUID_Generator class
  //------------------------------------------------------------
  /*!
   * @if jp
   * @brief UUID�N���X �R���X�g���N�^
   *
   * @else
   * @brief UUID class constructor
   *
   * @endif
   */
  UUID_Generator::UUID_Generator()
  {
  }
  /*!
   * @if jp
   * @brief UUID�N���X �f�X�g���N�^
   * @else
   * @brief UUID class destructor
   * @endif
   */
  UUID_Generator::~UUID_Generator()
  {
  }

  /*!
   * @if jp
   * @brief ������
   * @else
   * @brief Initialization
   * @endif
   */
  void UUID_Generator::init()
  {
  }

  /*!
   * @if jp
   * @brief UUID�𐶐�����
   * @else
   * @brief Generate UUID value
   * @endif
   */
  UUID* UUID_Generator::generateUUID(int n, int h)
  {
    uuid_t uuid;
    if(::UuidCreate(&uuid) != RPC_S_OK)
      {
        return 0;
      }
    else
      {
        return new UUID(uuid);
      }
  }
}; // coil
