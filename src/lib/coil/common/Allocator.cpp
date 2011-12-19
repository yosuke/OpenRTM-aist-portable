// -*- C++ -*-
/*!
 * @file  Allocator.cpp
 * @brief Memory allocator class
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PublisherPeriodic.h 1225 2009-02-28 02:30:25Z n-ando $
 *
 */

#include <coil/Allocator.h>

namespace coil
{
  
  /*!
   * @if jp
   * @brief �����ΰ����
   * @else
   * @brief Create of memory allocation
   * @endif
   */
  void* Allocator::New(size_t t) throw (std::bad_alloc)
  {
    return operator new(t);
  }
  
  /*!
   * @if jp
   * @brief �����ΰ����
   * @else
   * @brief Delete of memory allocation
   * @endif
   */
  void Allocator::Delete(void* p) throw ()
  {
    operator delete(p);
  }

  /*!
   * @if jp
   * @brief �����ѥ����ΰ����
   * @else
   * @brief Create of array memory allocation
   * @endif
   */
  void* Allocator::NewArray(size_t t) throw (std::bad_alloc)
  {
    return operator new [](t);
  }
  
  /*!
   * @if jp
   * @brief �����ѥ����ΰ����
   * @else
   * @brief Delete of array memory allocation
   * @endif
   */
  void Allocator::DeleteArray(void* p) throw ()
  {
    operator delete[](p);
  }
};

