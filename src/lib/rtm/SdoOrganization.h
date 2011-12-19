// -*- C++ -*-
/*!
 * @file SdoOrganization.h
 * @brief SDO Organization implementation class
 * @date $Date: 2008-01-14 07:49:28 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoOrganization.h 2019 2011-01-06 17:02:23Z n-ando $
 *
 */

#ifndef RTC_SDOORGANIZATION_H
#define RTC_SDOORGANIZATION_H

#include <rtm/RTC.h>
#include <rtm/idl/SDOPackageSkel.h>
#include <rtm/SystemLogger.h>
#include <string>
#include <coil/Mutex.h>
#include <coil/Guard.h>

/*!
 * @if jp
 * @namespace SDOPackage
 *
 * @brief SDO �ѥå�����
 *
 * @else
 *
 * @namespace SDOPackage
 *
 * @brief SDO Package
 *
 * @endif
 */

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace SDOPackage
{
  /*!
   * @if jp
   *
   * @class Organization_impl
   * @brief SDO Organization �������饹
   *
   * Organization interface �� Resource Data Model ��������줿�ǡ�����
   * �ɲá������������Ԥ�����Υ��󥿡��ե������Ǥ��롣
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class Organization_impl
   * @brief Organization implementation class
   *
   * Organization interface is an interface to add and delete etc data
   * defined by Resource Data Model.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class Organization_impl
    : public virtual POA_SDOPackage::Organization,
      public virtual PortableServer::RefCountServantBase
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
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
#ifdef ORB_IS_RTORB
    Organization_impl(RTC::RTObject_ptr sdo);
#endif // ORB_IS_RTROB
    Organization_impl(SDOSystemElement_ptr sdo);
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     * 
     * @else
     *
     * @brief Virtual destructor
     * 
     * Virtual Virtual destructor
     *
     * @endif
     */
    virtual ~Organization_impl(void);
    
    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization ID ���������
     *
     * Organization �� ID ���֤����ڥ졼�����
     *
     * @return Resource Data Model ��������줿 Organization ID��
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get Organization ID
     *
     * This operation returns the 'ID' of the Organization.
     *
     * @return The id of the Organization defined in the resource data model.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual char* get_organization_id()
      throw (CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] OrganizationProperty �Υ��å�
     *
     * �� SDO Specification �� PIM ���Ҥȥ��ڥ졼�����̾���ۤʤ롣
     * �� addOrganizationProperty ���б�����<BR>
     * OrganizationProperty �� Organization ���ɲä��륪�ڥ졼�����
     * OrganizationProperty �� Organization �Υץ�ѥƥ����ҤǤ��롣
     *
     * @param org_property ���åȤ��� OrganizationProperty
     *
     * @return ���ڥ졼����������������ɤ������֤���
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception InvalidParameter "org_property" �� null��
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set OrganizationProperty
     *
     * Note: The PIM description of SDO Specification differs from the operation
     *       name.
     * Note: Does this operation correspond to addOrganizationProperty?
     * This operation adds the OrganizationProperty to an Organization. The
     * OrganizationProperty is the property description of an Organization.
     *
     * @param org_property The type of organization to be added.
     *
     * @return If the operation was successfully completed.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception InvalidParameter The argument "organizationProperty" is null.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean
    add_organization_property(const OrganizationProperty& org_property)
      throw (CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] OrganizationProperty �μ���
     *
     * Organization ����ͭ���� OrganizationProperty ���֤����ڥ졼�����
     * Organization ���ץ�ѥƥ�������ʤ���ж��Υꥹ�Ȥ��֤���
     *
     * @return Organization �Υץ�ѥƥ��Υꥹ�ȡ�
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get OrganizationProperty
     *
     * This operation returns the OrganizationProperty that an Organization
     * has. An empty OrganizationProperty is returned if the Organization does
     * not have any properties.
     *
     * @return The list with properties of the organization.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual OrganizationProperty* get_organization_property()
      throw (CORBA::SystemException,
	     NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] OrganizationProperty ��������ͤμ���
     *
     * OrganizationProperty �λ��ꤵ�줿�ͤ��֤����ڥ졼�����
     * ���� "name" �ǻ��ꤵ�줿�ץ�ѥƥ����ͤ��֤���
     *
     * @param name �ͤ��֤��ץ�ѥƥ���̾����
     *
     * @return ���� "name" �ǻ��ꤵ�줿�ץ�ѥƥ����͡�
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception InvalidParameter ���� "name" �ǻ��ꤵ�줿�ץ�ѥƥ���
     *            ¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get specified value of OrganizationProperty
     *
     * This operation returns a value in the OrganizationProperty.
     * The value to be returned is specified by argument "name."
     *
     * @param name The name of the value to be returned.
     *
     * @return The value of property which is specified by argument "name".
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception InvalidParameter There are no Property stored with argument
     *                             "name".
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Any* get_organization_property_value(const char* name)
      throw (CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] OrganizationProperty ���ͤΥ��å�
     *
     * OrganizationProperty �� NVList �� name �� value �Υ��åȤ��ɲä⤷����
     * �������륪�ڥ졼�����name �� value �ϰ��� "name" �� "value" �ˤ��
     * ���ꤹ�롣
     *
     * @param name �ɲá����������ץ�ѥƥ���̾����
     * @param value �ɲá����������ץ�ѥƥ����͡�
     *
     * @return ���ڥ졼����������������ɤ������֤���
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception InvalidParameter ���� "name" �ǻ��ꤵ�줿�ץ�ѥƥ���
     *            ¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set specified value of OrganizationProperty
     *
     * This operation adds or updates a pair of name and value as a property
     * of Organization to/in NVList of the OrganizationProperty. The name and
     * the value to be added/updated are specified by argument "name" and
     * "value."
     *
     * @param name The name of the property to be added/updated.
     * @param value The value of the property to be added/updated.
     *
     * @return If the operation was successfully completed.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The property that is specified by argument
     *                             "name" does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean
    set_organization_property_value(const char* name, const CORBA::Any& value)
      throw (CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] OrganizationProperty �κ��
     *
     * OrganizationProperty �� NVList ��������Υץ�ѥƥ��������롣
     * ��������ץ�ѥƥ���̾���ϰ��� "name" �ˤ����ꤵ��롣
     *
     * @param name �������ץ�ѥƥ���̾����
     *
     * @return ���ڥ졼����������������ɤ������֤���
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception InvalidParameter ���� "name" �ǻ��ꤵ�줿�ץ�ѥƥ���
     *            ¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Remove specified OrganizationProperty
     *
     * This operation removes a property of Organization from NVList of the
     * OrganizationProperty. The property to be removed is specified by
     * argument "name."
     *
     * @param name The name of the property to be removed.
     *
     * @return If the operation was successfully completed.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The property that is specified by argument
     *                             "name" does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean remove_organization_property(const char* name)
      throw (CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO ���С����ɲ�
     *
     * Organization �˥��С��Ȥ��� SDO ���ɲä��롣
     * ���� "sdo" ���ɲä�����С� SDO ����ꤹ�롣
     *
     * @param sdo_list Organization ���ɲä���� SDO �Υꥹ�ȡ�
     *
     * @return ���ڥ졼����������������ɤ������֤���
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception InvalidParameter ���� "sdo" �� null�Ǥ��롣
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Add the member SDOs
     *
     * This operation adds a member that is an SDO to the organization.
     * The member to be added is specified by argument "sdo."
     *
     * @param sdo_list The member to be added to the organization.
     *
     * @return If the operation was successfully completed.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "sdo" is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean add_members(const SDOList& sdo_list)
      throw (CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �Υ��С����������
     *
     * Organization �Υ��С��� SDO �Υꥹ�Ȥ��֤���
     * ���С���¸�ߤ��ʤ���ж��Υꥹ�Ȥ��֤���
     *
     * @return Organization �˴ޤޤ����С� SDO �Υꥹ�ȡ�
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get the member list of the Organization
     *
     * This operation returns a list of SDOs that are members of an
     * Organization. An empty list is returned if the Organization does not
     * have any members.
     *
     * @return Member SDOs that are contained in the Organization object.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual SDOList* get_members()
      throw (CORBA::SystemException,
	     NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO �� ���å�
     *
     * SDO �Υꥹ�Ȥ� Organization �Υ��С��Ȥ��ƥ��åȤ��롣
     * Organization �����Ǥ˥��С��� SDO ��������Ƥ�����ϡ�
     * Ϳ����줿 SDO �Υꥹ�Ȥ��֤������롣
     *
     * @param sdos ���С��� SDO��
     *
     * @return ���ڥ졼����������������ɤ������֤���
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception InvalidParameter ���� "SDOList" �� null�Ǥ��롢�⤷����
     *            �����˻��ꤵ�줿 "SDOList" ��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set SDO
     *
     * This operation assigns a list of SDOs to an Organization as its members.
     * If the Organization has already maintained a member SDO(s) when it is
     * called, the operation replaces the member(s) with specified list of
     * SDOs.
     *
     * @param sdos Member SDOs to be assigned.
     *
     * @return If the operation was successfully completed.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "SDOList" is null, or the object
     *                             that is specified by the argument "sdos"
     *                             does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_members(const SDOList& sdos)
      throw (CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO ���С��κ��
     *
     * Organization ��������ǻ��ꤵ�줿 "id" �� SDO �������롣
     *
     * @param id ������� SDO �� id��
     *
     * @return ���ڥ졼����������������ɤ������֤���
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception InvalidParameter ���� "id" �� null �⤷����¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Remove member SDO from Organization
     *
     * This operation removes a member from the organization. The member to be
     * removed is specified by argument "id."
     *
     * @param id Id of the SDO to be removed from the organization.
     *
     * @return If the operation was successfully completed.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "id" is null or does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean remove_member(const char* id)
      throw (CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �Υ����ʡ����������
     *
     * ���� Organization �Υ����ʡ��ؤλ��Ȥ��֤���
     *
     * @return �����ʡ����֥������Ȥؤλ��ȡ�
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get the owner of Organization
     *
     * This operation returns the SDOSystemElement that is owner of
     * the Organization.
     *
     * @return Reference of owner object.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual SDOSystemElement_ptr get_owner()
      throw (CORBA::SystemException,
	     NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �˥����ʡ��򥻥åȤ���
     *
     * Organization ���Ф��� SDOSystemElement �򥪡��ʡ��Ȥ��ƥ��åȤ��롣
     * ���� "sdo" �˥��åȤ��� SDOSystemElement ����ꤹ�롣
     *
     * @param sdo �����ʡ����֥������Ȥλ��ȡ�
     *
     * @return ���ڥ졼����������������ɤ������֤���
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception InvalidParameter ���� "sdo" �� null�Ǥ��롢�⤷���ϡ�
     *                             "sdo" ��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set the owner to the Organization
     *
     * This operation sets an SDOSystemElement to the owner of the
     * Organization. The SDOSystemElement to be set is specified by argument
     * "sdo."
     *
     * @param sdo Reference of owner object.
     *
     * @return If the operation was successfully completed.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "sdo" is null, or the object
     *                             that is specified by "sdo" in argument "sdo"
     *                             does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_owner(SDOSystemElement_ptr sdo)
      throw (CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �� DependencyType �����
     *
     * Organization �δط���ɽ�� "DependencyType" ���֤���
     *
     * @return Organization �ΰ�¸�ط� DependencyType ���֤���
     *         DependencyType �� OMG SDO ���ͤ� Section 2.2.2 2-3 �ڡ�����
     *         "Data Structures Used by Resource Data Model" �򻲾ȡ�
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get the DependencyType of the Organization
     *
     * This operation gets the relationship "DependencyType" of the
     * Organization.
     *
     * @return The relationship of the Organization as DependencyType.
     *         DependencyType is defined in Section 2.2.2, "Data Structures
     *         Used by Resource Data Model," on page 2-3
     *         of OMG SDO Specification.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual DependencyType get_dependency()
      throw (CORBA::SystemException,
	     NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �� DependencyType �򥻥åȤ���
     *
     * Organization �ΰ�¸�ط� "DependencyType" �򥻥åȤ��롣
     * ���� "dependency" �ˤ���¸�ط���Ϳ���롣
     *
     * @param dependency Organization �ΰ�¸�ط���ɽ�� DependencyType��
     *        DependencyType �� OMG SDO ���ͤ� Section 2.2.2��2-3 �ڡ�����
     *        "Data Structures Used by Resource Data Model" �򻲾ȡ�
     *
     * @return ���ڥ졼����������������ɤ������֤���
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���(���㳰�ϡ�CORBAɸ��
     *                         �����ƥ��㳰��OBJECT_NOT_EXIST�˥ޥåԥ󥰤����)
     * @exception InvalidParameter ���� "sProfile" �� null�Ǥ��롣
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set the DependencyType of the Organization
     *
     * This operation sets the relationship "DependencyType" of the
     * Organization. The value to be set is specified by argument "dependency."
     *
     * @param dependency The relationship of the Organization as
     *                   DependencyType. DependencyType is defined in Section
     *                   2.2.2, "Data Structures Used by Resource Data Model,"
     *                   on page 2-3.
     *
     * @return If the operation was successfully completed.
     *
     * @exception SDONotExists The target SDO does not exist.(This exception 
     *                         is mapped to CORBA standard system exception
     *                         OBJECT_NOT_EXIST.)
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "dependency" is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_dependency(DependencyType dependency)
      throw (CORBA::SystemException,
	     NotAvailable, InternalError);
    
    // end of CORBA interface definition
    //============================================================
    Organization_ptr getObjRef() {return m_objref;};

  protected:
    ::RTC::Logger rtclog;
    Organization_var m_objref;
    /*!
     * @if jp
     * @brief Organization �μ��̻�
     * @else
     * @brief The identifier of the Organization.
     * @endif
     */
    std::string m_pId;
    
    /*!
     * @if jp
     * @brief Organization �˴�Ϣ�դ���줿 SDO ���ФΥꥹ��
     * @else
     * @brief A list of SDO members associated with the Organization
     * @endif
     */
    SDOPackage::SDOList m_memberList;
    
    /*!
     * @if jp
     * @brief Organization �� owner
     * @else
     * @brief The owner of the Organization
     * @endif
     */   
    SDOPackage::SDOSystemElement_var m_varOwner;
    
    /*!
     * @if jp
     * 
     * @brief ��¸�ط��Υ�����
     *
     * Owner �� member �ΰ�¸�ط�����ꤹ��°����
     * Organization �ϰʲ��Υȥݥ��ѥ������ɽ�����뤳�Ȥ��Ǥ��롣
     *
     * -# owner �� member ��������볬��Ū��¤�����ξ�� DependencyType �� OWN
     *    �Ȥ����ͤ���ġ�
     * -# members �� owner ���������ո����γ���Ū��¤�����ξ���
     *    DependencyType �� OWNER �Ȥ����ͤ���ġ�
     * -# owner �� member �˰�¸�ط����ʤ��ե�åȤʹ�¤�����ξ���
     *    DependencyType �� NO_DEPENDENCY �Ȥ����ͤ���ġ�
     * 
     * SDO ����� SDOSystemElement �Υ��֥��饹�� Organization �� owner �Ȥ���
     * ���񤦤��Ȥ�����롣SDO �� owner �ξ��ˤ�Organization �Ͼ嵭��
     * �����줫�Υȥݥ����ѥ������Ȥ롣
     *
     * - Organization �� 1. �Υȥݥ����ѥ��������ľ�硢ͣ��Ĥ� owner SDO
     *   �� member SDO �����椹�롣���Ȥ��С���������(owner)�ϡ�
     *   ���٥���(member)�����٥���(member)�����������(member)�����椹�롣
     * - Organization �� 2. �Υȥݥ�����ľ��ϡ�ʣ���� SDO member ��ͣ���
     *   SDO owner ��ͭ���롣���Ȥ��С������(owner)�Ϥ����Ĥ���AV
     *   ����ݡ��ͥ��(member)���鶦ͭ����롣
     * - SDO �ǤϤʤ� SDOSystemElement �Υ��֥��饹�� owner �ξ�硢
     *   �ʲ��Τ褦�ʥȥݥ����㤬�ͤ����롣
     * -- User(owner)-SDO(member): �桼��(owner) �ϰ�İʾ�� SDO(member)��
     *   �������롣����Ͼ嵭�ȥݥ��ѥ���1.�ˤ����롣
     * -- Location(owner)-SDO(members): ��İʾ�� SDO(member) ������ξ��
     *   = location(owner) ��ư��Ƥ����硢Organization �Υȥݥ��ѥ�����
     *   �� 3. �ξ��ˤʤ롣���Ȥ��С�ʣ���� PDA �����������ˤ��ꡢ�ߤ���Ʊ��
     *   �ʴط��Ǥ�����ߤ��̿���ǽ�ʾ��Ϥ���ˤ����롣
     *
     * @else
     *
     * @brief Dependency type
     *
     * This attribute specifies the dependency relation between the owner and
     * members of the organization.
     * Organization is used to form the following three patterns of topology.
     *
     * -# Hierarchical organization, which indicates owner supervises members.
     *    In this case, DependencyType should hold OWN value (see description
     *    of DependencyType on previous pages).
     * -# Reversely hierarchical organization, which indicates members
     *    supervise owner. In this case, DependencyType should hold OWNED value
     *    (see description of DependencyType on previous pages).
     * -# Flat organization, which indicates no dependency exists. In this
     *    case, DependencyType should hold NO_DEPENDENCY value (see description
     *    of DependencyType on previous pages).
     *
     * Both an SDO and another subclass of SDOSystemElement can act as owner
     * of an Organization. When an SDO is an owner, Organization can represent
     * any of the above three topology patterns.
     *
     * - When an Organization represents topology pattern (1), an SDO (owner)
     *   controls one or more SDOs (members). For example, air conditioner
     *   (owner) controls a temperature sensor (member), humidity sensor
     *   (member), and wind flow controller (member).
     * - When an Organization represents topology pattern (2), multiple
     *   SDOs(members) share an SDO (owner). For example, an amplifier (owner)
     *   is shared by several AV components (members) in an AV stereo.
     * - When a subclass of SDOSystemElement, which is not an SDO is an owner
     *   examples of the topology are as follows.
     * -- User (owner)-SDO (members): When a user (owner) supervises one or
     *    more SDOs (members), the organization represents topology pattern 1.
     * -- Location (owner)-SDO (members): When one or more SDOs (members) are
     *    operating in a specific location (owner), the organization represents
     *    topology pattern 3. For example, multiple PDAs in the same place
     *    (e.g., a room) have equal relationships among them to communicate
     *    with each other.
     * @endif
     */
    SDOPackage::DependencyType m_dependency;
    
    /*!
     * @if jp
     *
     * @brief Organization �ץ�ѥƥ�
     *
     * OrganizationProperty �� Organization �Υץ�ѥƥ�������ݻ����롣
     * ��Ĥ� Organization ��0�Ĥ⤷����1�Ĥ� OrganizationProperty ���ġ�
     *
     * @else
     *
     * @brief Organization property
     *
     * OrganizationProperty contains the properties of an Organization.
     * An Organization has zero or one (at most one) instance
     * of OrganizationProperty.
     *
     * @endif
     */
    SDOPackage::OrganizationProperty m_orgProperty;
    Mutex m_org_mutex;
    
    /*!
     * @if jp
     * @brief  NameValue��functor
     * @else
     * @brief  Functor for NameValue
     * @endif
     */
    struct nv_name
    {
      nv_name(const char* name) : m_name(name) {};
      bool operator()(const NameValue& nv)
      {
	return m_name == std::string(nv.name);
      }
      std::string m_name;
    };  // struct nv_name
    
    /*!
     * @if jp
     * @brief  SDO��functor
     * @else
     * @brief  Functor for SDO
     * @endif
     */
    struct sdo_id
    {
      sdo_id(const char* id) : m_id(id) {};
      bool operator()(const SDO_ptr sdo)
      {
        CORBA::String_var id(sdo->get_sdo_id());
	return m_id == (const char*)id;
      }
      std::string m_id;
    };  // struct sdo_id
  };  // class Organization_impl
};  // namespace SDOPackage

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_NAMESPACE SDOPACKAGE
