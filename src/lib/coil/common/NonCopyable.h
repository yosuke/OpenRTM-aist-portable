// -*- C++ -*-
/*!
 * @file  NonCopyable.h
 * @brief Non Copyable mixin class
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

namespace coil
{
  /*!
   * @if jp
   * @class NonCopyable
   * @brief ���ԡ��ػߥߥå�������
   * 
   * �оݥ��饹�Υ��֥������ȤΥ��ԡ���ػߤ��롣���ԡ���ػߤ���������
   * ���Ǥϡ�NonCopyable��private�Ѿ����뤳�Ȥǥ��֥������ȤΥ��ԡ����
   * �ߤ��뤳�Ȥ��Ǥ��롣
   *
   * -��:
   * class CopyProhibitedClass : private NonCopyable {};
   *
   * @else
   *
   * @class NonCopyable
   * @brief Non-copyable Mixin
   *
   * This mix-in class prevents objects of a class from being
   * copy-constructed or assigned to each other. User can prohibit the
   * class copying by inheriting from NonCopyable class as a private
   * base class.
   *
   * -example:
   * class CopyProhibitedClass : private NonCopyable {};
   *
   * @endif
   */
  class NonCopyable
  {
  protected:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    NonCopyable() {}

    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    ~NonCopyable() {}
  private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
  };

  /*!
   * @if jp
   * @class NonCopyableCRTP
   * @brief ���ԡ��ػߥߥå�������(CRTP��)
   * 
   * �оݥ��饹�Υ��֥������ȤΥ��ԡ���ػߤ��롣���ԡ���ػߤ���������
   * ���Ǥϡ�NonCopyable��private�Ѿ����뤳�Ȥǥ��֥������ȤΥ��ԡ����
   * �ߤ��뤳�Ȥ��Ǥ��롣����CRTP (Curiously Recursive Template
   * Pattern) �Ǥϡ����δ��쥯�饹���Ф����Ŭ�� (Empty Base
   * Optimization) ��Ԥ碌�����������Ѥ��롣
   *
   * -��:
   * struct A : NonCopyableCRTP<A> {};
   * struct B : NonCopyableCRTP<B> {};
   * struct C: A, B {};
   *
   * @else
   *
   * @class NonCopyable
   * @brief Non-copyable Mixin
   *
   * This mix-in class prevents objects of a class from being
   * copy-constructed or assigned to each other. User can prohibit the
   * class copying by inheriting from NonCopyable class as a private
   * base class.��The CRTP (Curiously Recursive Template Pattern)
   * version would be used for empty base optimization for
   * multipe-inherited.
   *
   * -example:
   * class CopyProhibitedClass : private NonCopyable {};
   *
   * @endif
   */
  template <class T>
  class NonCopyableCRTP
  {
  protected:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    NonCopyableCRTP() {}

    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    ~NonCopyableCRTP() {}
  private: 
    NonCopyableCRTP(const NonCopyableCRTP &);
    T & operator=(const T &);
  };
};
