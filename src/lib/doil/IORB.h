// -*- C++ -*-
/*!
 * @file IORB.h
 * @brief Generic ORB interface
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

#ifndef DOIL_IORB_H
#define DOIL_IORB_H

#include <coil/Properties.h>
#include <doil/doil.h>
#include <doil/ServantFactory.h>
#include <doil/ImplBase.h>

namespace doil
{

  /*!
   * @if jp
   * @class ���� ORB ���󥿡��ե�����
   * 
   * ���Υ��󥿡��ե����������Ѥ�ORB�Τ���Υ��󥿡��ե������Ǥ��롣��
   * �Ѥ�����ʬ�����֥������ȥߥɥ륦�������Ф��ơ����Υ��󥿡��ե�����
   * ��Ѿ�����ORB�ޥ͡����㥯�饹��������롣ORB���󥿡��ե������Ϥϥ�
   * ���塼�붭���ˤʤ뤿�ᡢ���ڤ��㳰��ȯ�������ƤϤʤ�ʤ������٤Ƥ�
   * ���顼�ϥ��顼�����ɤȤ��ƸƤӽФ�¦���֤����ȡ�
   *
   * @else
   * @class generic ORB interface
   * @endif
   */
  class IORB
  {
  public:
    /*!
     * @if jp
     * @brief ORBManager �� ORB ����Ͽ����
     *
     * ORBManager �� IORB ��Ѿ����� ORB ���֥������Ȥ���Ͽ���롣
     *
     * @else
     * @brief Register an ORB to the ORBManager
     *
     * This operation will register an ORB that inherits IORB
     * interface to the ORBManager.
     *
     * @endif
     */
    virtual ~IORB() throw() {};

    /*!
     * @if jp
     * @brief ORB ��̾�����������
     *
     * ORB ��̾�����֤���
     *
     * @else
     * @brief Getting ORB's name
     *
     * This operation will return ORB's name.
     *
     * @endif
     */
    virtual const char* name() throw() = 0;

    /*!
     * @if jp
     * @brief ORB �� shutdown ����
     *
     * ORB ��λ���롣
     *
     * @else
     * @brief Shutdown ORB
     *
     * This operation will shutdown ORB
     *
     * @endif
     */
    virtual void shutdown() throw() = 0;

    /*!
     * @if jp
     * @brief Servant �� Factory ����Ͽ����
     *
     * Servant �� Factory ����Ͽ���롣
     *
     * @return OK:             ���ｪλ
     *         ALREADY_EXISTS: Ϳ����줿�ե����ȥ�Ϥ��Ǥ���Ͽ�Ѥ�
     *         INVALID_ARGS:   �����ΰ�İʾ夬����
     *         UNKNOWN:        �����ʥ��顼
     *
     * @else
     * @brief Register servant's factory
     *
     * This operation will register servant's factory.
     *
     * @return OK:             Normal return
     *         ALREADY_EXISTS: Given factory already exists.
     *         INVALID_ARGS:   One or more given arguments are invalid.
     *         UNKNOWN:        Unknown error
     *
     * @endif
     */
    virtual ReturnCode_t registerFactory(const char* id,
                                         ServantNewFunc new_func,
                                         ServantDeleteFunc delete_func)
      throw() = 0;
    
    /*!
     * @if jp
     * @brief ���֥������Ȥ�activate����
     *
     * Ϳ����줿���֥������Ȥ򥢥��ƥ��ֲ����롣
     * Ϳ����줿���֥������Ȥ�ID�ȹ��פ��륵���Х�ȤΥե����ȥ꤬
     * ��Ͽ�ѤߤǤ���ɬ�פ����롣�⤷�����֥������Ȥ�ID�ȹ��פ���ե����ȥ�
     * ��¸�ߤ��ʤ���硢INVALID_ARGS ���顼���֤���롣
     *
     * @return OK:             ���ｪλ
     *         ALREADY_EXISTS: Ϳ����줿���֥������ȤϤ��Ǥ�¸�ߤ���
     *         INVALID_ARGS:   ����������
     *         UNKNOWN:        �����ʥ��顼
     *
     * @else
     * @brief Activate object
     *
     * This operation will activate given object
     * The servant that has same ID with the given object's ID should 
     * exist in this ORB servant's map. INVALID_ARGS error code will return
     * if the factory does not exist.
     *
     * @return OK:             Normal return
     *         ALREADY_EXISTS: Given object already exists.
     *         INVALID_ARGS:   The given arguments is invalid.
     *         UNKNOWN:        Unknown error
     *
     * @endif
     */
    virtual ReturnCode_t activateObject(ImplBase* impl)
      throw() = 0;

    /*!
     * @if jp
     * @brief ���֥������Ȥ�activate����
     *
     * Ϳ����줿���֥������Ȥ�Ϳ����줿�����Х�Ȥȶ��˥����ƥ��ֲ����롣
     * ���֥������Ȥ򥢥��ƥ��ֲ����륵���Х�Ȥ�¸�ߤ���ɬ�פϤʤ���
     * ��������Ϳ����줿�����Х�Ȥ�ID��Ϳ����줿���֥������Ȥ�ID��
     * ���פ��Ƥ���ɬ�פ����롣���פ��ʤ����� INVALID_ARGS ���顼���֤���롣
     *
     * @return OK:             ���ｪλ
     *         ALREADY_EXISTS: Ϳ����줿���֥������ȤϤ��Ǥ�¸�ߤ���
     *         INVALID_ARGS:   ����������
     *         UNKNOWN:        �����ʥ��顼
     *
     * @else
     * @brief Activate object
     *
     * This operation will activate given object
     * The servant's factory that activate the given object does not need to
     * exists in this ORB manager. However, the given servant's ID and
     * the given object's ID have to be same. INVALID_ARGS error will be
     * returned if these IDs are not same. 
     *
     * @return OK:             Normal return
     *         ALREADY_EXISTS: Given object already exists.
     *         INVALID_ARGS:   The given arguments is invalid.
     *         UNKNOWN:        Unknown error
     *
     * @endif
     */
    virtual ReturnCode_t activateObject(ImplBase* impl,
                                        ServantBase* servant)
      throw() = 0;

    /*!
     * @if jp
     * @brief ���֥������Ȥ�deactivate����
     *
     * Ϳ����줿���֥������Ȥ��󥢥��ƥ��ֲ����롣
     * ���֥������Ȥ����֥������ȥޥåפˤʤ����� NOT_FOUND ���顼���֤���롣
     *
     * @return OK:             ���ｪλ
     *         NOT_FOUND:      Ϳ����줿���֥������Ȥϥޥå׾��¸�ߤ��ʤ�
     *         INVALID_ARGS:   ����������
     *         UNKNOWN:        �����ʥ��顼
     *
     * @else
     * @brief Deactivate object
     *
     * This operation will deactivate the given object.
     * NOT_FOUND error will be returned if the given object does not exist
     * in the ative object map.
     *
     * @return OK:             Normal return
     *         NOT_FOUND:      Given object does not exist in the map.
     *         INVALID_ARGS:   The given arguments is invalid.
     *         UNKNOWN:        Unknown error
     *
     * @endif
     */
    virtual ReturnCode_t deactivateObject(ImplBase* impl)
      throw() = 0;

    /*!
     * @if jp
     * @brief ���֥������Ȥ�deactivate����
     *
     * Ϳ����줿̾���Υ��֥������Ȥ��󥢥��ƥ��ֲ����롣���֥�������̾
     * �����֥������ȥޥåפˤʤ����� NOT_FOUND ���顼���֤���롣
     *
     * @return OK:             ���ｪλ
     *         NOT_FOUND:      Ϳ����줿���֥������Ȥϥޥå׾��¸�ߤ��ʤ�
     *         INVALID_ARGS:   ����������
     *         UNKNOWN:        �����ʥ��顼
     *
     * @else
     * @brief Deactivate object
     *
     * This operation will deactivate the given name's object.
     * NOT_FOUND error will be returned if the given object does not exist
     * in the ative object map.
     *
     * @return OK:             Normal return
     *         NOT_FOUND:      Given object does not exist in the map.
     *         INVALID_ARGS:   The given arguments is invalid.
     *         UNKNOWN:        Unknown error
     *
     * @endif
     */
    virtual ReturnCode_t deactivateObject(const char* name)
      throw() = 0;

    /*!
     * @if jp
     * @brief Impl���֥������Ȥ�̾���Ǽ�������
     *
     * Ϳ����줿̾���Υ��֥������Ȥ�������롣
     * ���֥������Ȥ��ޥåפˤʤ����� NOT_FOUND ���顼���֤���롣
     *
     * @return OK:             ���ｪλ
     *         NOT_FOUND:      ���֥������Ȥϥޥå׾��¸�ߤ��ʤ�
     *         INVALID_ARGS:   ����������
     *         UNKNOWN:        �����ʥ��顼
     *
     * @else
     * @brief Getting object by name
     *
     * This operation will return a object by given name.  NOT_FOUND
     * error will be returned if the given name's object does not
     * exist in the ative object map.
     *
     * @return OK:             Normal return
     *         NOT_FOUND:      The object does not exist in the map.
     *         INVALID_ARGS:   The given arguments is invalid.
     *         UNKNOWN:        Unknown error
     *
     * @endif
     */
    virtual doil::ImplBase* getImpl(const char* name)
      throw() = 0;

    /*!
     * @if jp
     * @brief Impl���֥������Ȥ�Servant�Ǽ�������
     *
     * Ϳ����줿���֥������Ȥ��б����륵���Х�Ȥ�������롣
     * ���֥������Ȥ��ޥåפˤʤ����� NOT_FOUND ���顼���֤���롣
     *
     * @return OK:             ���ｪλ
     *         NOT_FOUND:      ���֥������Ȥϥޥå׾��¸�ߤ��ʤ�
     *         INVALID_ARGS:   ����������
     *         UNKNOWN:        �����ʥ��顼
     *
     * @else
     * @brief Getting impl object by servant
     *
     * This operation will return an impl object by given servant.
     * NOT_FOUND error will be returned if the given servant's impl object
     * does not exist in the ative object map.
     *
     * @return OK:             Normal return
     *         NOT_FOUND:      The object does not exist in the map.
     *         INVALID_ARGS:   The given arguments is invalid.
     *         UNKNOWN:        Unknown error
     *
     * @endif
     */
    virtual doil::ImplBase* toImpl(doil::ServantBase* servant)
      throw() = 0;

    /*!
     * @if jp
     * @brief Servant���֥������Ȥ��������
     *
     * Ϳ����줿̾����Servant���֥������Ȥ�������롣
     * ���֥������Ȥ��ޥåפˤʤ����� NOT_FOUND ���顼���֤���롣
     *
     * @return OK:             ���ｪλ
     *         NOT_FOUND:      ���֥������Ȥϥޥå׾��¸�ߤ��ʤ�
     *         INVALID_ARGS:   ����������
     *         UNKNOWN:        �����ʥ��顼
     *
     * @else
     * @brief Getting servant object by name
     *
     * This operation will return an servant object by given name.
     * NOT_FOUND error will be returned if the given name's servant object
     * does not exist in the ative object map.
     *
     * @return OK:             Normal return
     *         NOT_FOUND:      The object does not exist in the map.
     *         INVALID_ARGS:   The given arguments is invalid.
     *         UNKNOWN:        Unknown error
     *
     * @endif
     */
    virtual doil::ServantBase* getServant(const char* name)
      throw() = 0;

    /*!
     * @if jp
     * @brief Servant���֥������Ȥ��������
     *
     * Ϳ����줿impl���֥������Ȥ�Servant���֥������Ȥ�������롣
     * ���֥������Ȥ��ޥåפˤʤ����� NOT_FOUND ���顼���֤���롣
     *
     * @return OK:             ���ｪλ
     *         NOT_FOUND:      ���֥������Ȥϥޥå׾��¸�ߤ��ʤ�
     *         INVALID_ARGS:   ����������
     *         UNKNOWN:        �����ʥ��顼
     *
     * @else
     * @brief Getting servant object by impl object
     *
     * This operation will return an servant object by given impl object.
     * NOT_FOUND error will be returned if the given name's servant object
     * does not exist in the ative object map.
     *
     * @return OK:             Normal return
     *         NOT_FOUND:      The object does not exist in the map.
     *         INVALID_ARGS:   The given arguments is invalid.
     *         UNKNOWN:        Unknown error
     *
     * @endif
     */
    virtual doil::ServantBase* toServant(doil::ImplBase* impl)
      throw() = 0;

  };
}; // namespace doil
#endif // DOIL_IORB_H
