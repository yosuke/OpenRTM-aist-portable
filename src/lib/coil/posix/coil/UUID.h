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

#ifndef COIL_UUID_H
#define COIL_UUID_H

#include <coil/config_coil.h>
#ifdef COIL_OS_FREEBSD
#include <uuid.h>

namespace coil
{
  class UUID
  {
  public:
    UUID();
    UUID(const uuid_t& uuid);
    ~UUID();
    const char* to_string();
  private:
    uuid_t m_uuid;
    char* m_uuidstr;
  };


  class UUID_Generator
  {
  public:
    UUID_Generator();
    ~UUID_Generator();
    void init();
    coil::UUID* generateUUID(int n, int h);
  };
};
#endif
#if defined(COIL_OS_LINUX) || defined(COIL_OS_DARWIN) || defined(COIL_OS_CYGWIN)
#include <uuid/uuid.h>
namespace coil
{
  class UUID
  {
    uuid_t _uuid;
    char buf[37];
  public:
    UUID();
    UUID(uuid_t*);
    const char* to_string();
  };

  class UUID_Generator
  {
  public:
    UUID_Generator();
    
    void init();
    UUID* generateUUID(int n, int h);
  };
};
#endif

#endif // COIL_UUID_H
