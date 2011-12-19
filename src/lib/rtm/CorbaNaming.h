// -*- C++ -*-
/*!
 * @file CorbaNaming.h
 * @brief CORBA naming service helper class
 * @date $Date: 2007-12-31 03:08:02 $
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
 * $Id: CorbaNaming.h 2019 2011-01-06 17:02:23Z n-ando $
 *
 */

#ifndef RTC_CORBANAMING_H
#define RTC_CORBANAMING_H

#include <rtm/RTC.h>

// STL includes
#include <map>
#include <string>
#include <vector>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RT����ݡ��ͥ��
 *
 * @else
 *
 * @namespace RTC
 *
 * @brief RT-Component
 *
 * @endif
 */

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class CorbaNaming
   * @brief CORBA Naming Service �إ�ѡ����饹
   *
   * ���Υ��饹�ϡ�CosNaming::NamingContext ���Ф����åѡ����饹�Ǥ��롣
   * CosNaming::NamingContext �����ĥ��ڥ졼�����Ȥۤ�Ʊ����ǽ��
   * ���ڥ졼�������󶡤���ȤȤ�ˡ��͡��ॳ��ݡ��ͥ�� CosNaming::Name
   * �������ʸ����ˤ��̾��ɽ��������դ��륪�ڥ졼�������󶡤��롣
   *
   * ���֥������Ȥ������������뤤������ľ��� CORBA �͡��ॵ���Ф���³��
   * �ʸ塢���Υ͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ��Ф��Ƽ�Υ��ڥ졼�����
   * ��������롣
   * �������ؤΥ͡��ߥ󥰥���ƥ����Ȥκ����䥪�֥������ȤΥХ���ɤˤ����ơ�
   * ����Υ���ƥ����Ȥ�¸�ߤ��ʤ����Ǥ⡢����Ū�˥���ƥ����Ȥ�Х����
   * ����Ū�Υ���ƥ����Ȥ䥪�֥������ȤΥХ���ɤ�Ԥ����Ȥ�Ǥ��롣
   *
   * @since 0.4.0
   *
   * @else
   * @class CorbaNaming
   * @brief CORBA Naming Service helper class
   *
   * This class is a wrapper class of CosNaming::NamingContext.
   * Almost the same operations which CosNaming::NamingContext has are
   * provided, and some operation allows string naming representation of
   * context and object instead of CosNaming::Name.
   *
   * The object of the class would connect to a CORBA naming server at
   * the instantiation or immediately after instantiation.
   * After that the object invokes operations to the root context of it.
   * This class realizes forced binding to deep NamingContext, without binding
   * intermediate NamingContexts explicitly.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class CorbaNaming
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * @param orb ORB
     *
     * @else
     *
     * @brief Consructor
     *
     * @param orb ORB
     *
     * @endif
     */
    CorbaNaming(CORBA::ORB_ptr orb);
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * @param orb ORB
     * @param name_server �͡��ॵ���Ф�̾��
     *
     * @else
     *
     * @brief Consructor
     *
     * @param orb ORB
     * @param name_server Name of the name server
     *
     * @endif
     */
    CorbaNaming(CORBA::ORB_ptr orb, const char* name_server);
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * @else
     * 
     * @brief Virtual destructor
     * 
     * @endif
     */
    virtual ~CorbaNaming(void){};
    
    /*!
     * @if jp
     *
     * @brief �͡��ߥ󥰥����ӥ��ν����
     * 
     * ���ꤵ�줿�͡��ॵ���о�Υ͡��ߥ󥰥����ӥ����������ޤ���
     * 
     * @param name_server �͡��ॵ���Ф�̾��
     * 
     * @else
     *
     * @brief Initialize the Naming Service
     * 
     * Initialize the Naming Service on the specified name server.
     * 
     * @param name_server Name of the name server
     * 
     * @endif
     */
    void init(const char* name_server);

    bool isAlive();
    
    typedef CORBA::SystemException SystemException;
    typedef CosNaming::NamingContext::NotFound      NotFound;
    typedef CosNaming::NamingContext::CannotProceed CannotProceed;
    typedef CosNaming::NamingContext::InvalidName   InvalidName;
    typedef CosNaming::NamingContext::AlreadyBound  AlreadyBound;
    typedef CosNaming::NamingContext::NotEmpty      NotEmpty;
    typedef CosNaming::NamingContextExt::InvalidAddress InvalidAddress;
    typedef std::vector<CORBA::Object_ptr> ObjectList;
    
    /*!
     * @if jp
     *
     * @brief Object �� bind ����
     *
     * CosNaming::bind() �Ȥۤ�Ʊ����Ư���򤹤뤬�����Ϳ����줿�͡��ॵ���Ф�
     * �롼�ȥ���ƥ����Ȥ��Ф���bind()���ƤӽФ���������ۤʤ롣
     *
     * Name <name> �� Object <obj> ������ NamingContext ��˥Х���ɤ��롣
     * c_n �� n ���ܤ� NameComponent �򤢤�魯�Ȥ���ȡ�
     * name �� n �Ĥ� NameComponent ��������Ȥ����ʲ��Τ褦�˰����롣
     *
     * cxt->bind(<c_1, c_2, ... c_n>, obj) �ϰʲ�������Ʊ���Ǥ��롣
     * cxt->resolve(<c_1, ... c_(n-1)>)->bind(<c_n>, obj)
     *
     * ���ʤ����1���ܤ���n-1���ܤΥ���ƥ����Ȥ��褷��n-1���ܤΥ���ƥ�����
     * ��� name <n> �Ȥ��ơ�obj �� bind ���롣
     * ̾�����˻��ä��� <c_1, ... c_(n-1)> �� NemingContext �ϡ�
     * bindContext() �� rebindContext() �Ǵ��˥Х���ɺѤߤǤʤ���Фʤ�ʤ���
     * �⤷ <c_1, ... c_(n-1)> �� NamingContext ��¸�ߤ��ʤ����ˤϡ�
     * NotFound �㳰��ȯ�����롣
     *
     * �������������Х���ɥե饰 force �� true �λ��ϡ�<c_1, ... c_(n-1)>
     * ��¸�ߤ��ʤ����ˤ⡢�Ƶ�Ū�˥���ƥ����Ȥ�Х���ɤ��ʤ��顢
     * �ǽ�Ū�� obj ��̾�� name <c_n> �˥Х���ɤ��롣
     *
     * ������ξ��Ǥ⡢n-1���ܤΥ���ƥ����Ⱦ�� name<n> �Υ��֥�������
     * (Object ���뤤�� ����ƥ�����) ���Х���ɤ���Ƥ����
     * AlreadyBound �㳰��ȯ�����롣
     *
     * @param name ���֥������Ȥ��դ���̾���� NameComponent
     * @param obj ��Ϣ�դ����� Object
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *              (�ǥե������:true)
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     * @exception AlreadyBound name <c_n> �� Object �����Ǥ˥Х���ɤ���Ƥ��롣
     *
     * @else
     *
     * @brief Bind object on specified name component position
     *
     * Almost the same operation as CosNaming::bind(), but there is a difference 
     * that bind() is invoked for the root context of the given name server.
     *
     * Bind between Name <name> and Object <obj> on this NamingContext.
     * If c_n indicates the n-th of NameComponent,
     * when name consists of n pieces of NameComponent, it is handled as 
     * follows. 
     *
     * cxt->bind(<c_1, c_2, ... c_n>, obj) is the same as the following
     * operation.
     * cxt->resolve(<c_1, ... c_(n-1)>)->bind(<c_n>, obj)
     *
     * In other word, resolve from the first to the (n-1)th context and bind 
     * obj as name<n> on the (n-1)th context.
     * NemingContext of <c_1, ... c_(n-1)> for resolving name must be already 
     * bound in bindContext() or rebindContext().
     * If NamingContext of <c_1, ... c_(n-1)> does not exist, NotFound excption
     * will occur.
     *
     * However, when flag of forced bind is true, even if <c_1, ... c_(n-1)> does
     * not exist, finally obj will be bound to name name <c_n> by binding to 
     * the context recursively.
     *
     * Even in any case, if the object of name<n> (Object or context) is bound
     * on the (n-1)th context, AlreadyBound exception will occur.
     *
     * @param name NameComponent of name applied to object
     * @param obj Object that is associated
     * @param force If true, the intermediate context is bound forcibly.
     *              (The default value:true)
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     * @exception AlreadyBound The object of name<c_n> is already bound.
     *
     * @endif
     */
    void bind(const CosNaming::Name& name, CORBA::Object_ptr obj,
	      const bool force = 1)
      throw (SystemException, NotFound, CannotProceed,
             InvalidName, AlreadyBound);
    
    /*!
     * @if jp
     *
     * @brief Object �� bind ����
     *
     * Object �� bind ����ݤ�Ϳ����̾����ʸ����ɽ���Ǥ��뤳�Ȱʳ��ϡ�bind()
     * ��Ʊ���Ǥ��롣bind(toName(string_name), obj) ��������
     *
     * @param string_name ���֥������Ȥ��դ���̾����ʸ����ɽ��
     * @param obj ��Ϣ�դ����륪�֥�������
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *              (�ǥե������:true)
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     * @exception AlreadyBound name <n> �� Object �����Ǥ˥Х���ɤ���Ƥ��롣
     *
     * @else
     *
     * @brief Bind object on specified string name position
     *
     * This is the same as bind() except as the given name is string 
     * representation when Object is bound. 
     * bind(toName(string_name),obj) is the same. 
     *
     * @param string_name The string representation of name applied to object
     * @param obj Object that is associated
     * @param force If true, the intermediate context is bound forcibly.
     *              (The default value:true)
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     * @exception AlreadyBound The object of name<c_n> is already bound.
     *
     * @endif
     */
    void bindByString(const char* string_name, CORBA::Object_ptr obj,
		      const bool force = 1)
      throw (SystemException, NotFound, CannotProceed,
             InvalidName, AlreadyBound);
    
    /*!
     * @if jp
     *
     * @brief ����Υ���ƥ����Ȥ�Ƶ�Ū�� bind ���ʤ��� Object �� bind ����
     *
     * context ��Ϳ����줿 NamingContext ���Ф��ơ�name �ǻ��ꤵ�줿
     * �͡��ॳ��ݡ��ͥ�� <c_1, ... c_(n-1)> �� NamingContext �Ȥ���
     * ��褷�ʤ��顢̾�� <c_n> ���Ф��� obj �� bind ���롣
     * �⤷��<c_1, ... c_(n-1)> ���б����� NamingContext ���ʤ����ˤ�
     * ������ NamingContext ��Х���ɤ��롣
     *
     * �ǽ�Ū�� <c_1, c_2, ..., c_(n-1)> ���б����� NamingContext ������
     * �ޤ��ϲ�褵�줿��ǡ�CosNaming::bind(<c_n>, object) ���ƤӽФ���롣
     * ���ΤȤ������Ǥ˥Х���ǥ��󥰤�¸�ߤ���� AlreadyBound�㳰��ȯ�����롣
     *
     * ����Υ���ƥ����Ȥ��褹������ǡ���褷�褦�Ȥ��륳��ƥ����Ȥ�
     * Ʊ��̾���� NamingContext �ǤϤʤ� Binding ��¸�ߤ����硢
     * CannotProceed �㳰��ȯ������������ߤ��롣
     *
     * @param context bind �򳫻Ϥ��롡NamingContext
     * @param name ���֥������Ȥ��դ���̾���Υ͡��ॳ��ݡ��ͥ��
     * @param obj ��Ϣ�դ����륪�֥�������
     *
     * @exception CannotProceed <c_1, ..., c_(n-1)> ���б����� NamingContext 
     *            �Τ����ҤȤĤ������Ǥ� NamingContext �ʳ��� object �˥Х����
     *            ����Ƥ��ꡢ�������³�Ǥ��ʤ���
     * @exception InvalidName ̾�� name ������
     * @exception AlreadyBound name <c_n> �ˤ��Ǥ˲��餫�� object ���Х����
     *            ����Ƥ��롣
     * @else
     *
     * @brief Bind intermediate context recursively and bind object
     *
     * For NamingContext given in context, bind obj to name <c_n> with solving
     * name component <c_1, ... c_(n-1)> specified by name as NamingContext.
     * Bind new NamingContext when there is no NamingContext corresponding to
     * c_(n-1) >.
     *
     * Finally, NamingContext corresponding to <c_1, c_2, ..., c_(n-1)> 
     * will be generated, or CosNaming::bind(<c_n>, object) will be invoked
     * after solving. At this time, if the binding already exists, 
     * the AlreadyBound exception will occur.
     *
     * During process, when Binding that is not NamingContext of the same name
     * as the context for solving exists, CannotProceed exception will occur
     * and stop processing.
     *
     * @param context NamingContext that starts the bind
     * @param name NameComponent of name applied to object
     * @param obj Object that is associated
     *
     * @exception CannotProceed Since one of NamingContext corresponding to
     *                          <c_1, ..., c_(n-1)> is already bound to object
     *                          other than NamingContext and processing cannot 
     *                          be continued
     * @exception InvalidName name 'name' is invalid.
     * @exception AlreadyBound The object of name<c_n> is already bound.
     *
     * @endif
     */
    void bindRecursive(CosNaming::NamingContext_ptr context,
		       const CosNaming::Name& name,
		       CORBA::Object_ptr obj)
      throw (SystemException, CannotProceed, InvalidName, AlreadyBound);
    
    /*!
     * @if jp
     *
     * @brief Object �� rebind ����
     *
     * name �ǻ��ꤵ�줿 Binding �����Ǥ�¸�ߤ����������� bind() ��Ʊ��
     * �Ǥ��롣�Х���ǥ��󥰤����Ǥ�¸�ߤ�����ˤϡ��������Х���ǥ��󥰤�
     * �֤��������롣
     *
     * @param name ���֥������Ȥ��դ���̾���� NameComponent
     * @param obj ��Ϣ�դ����륪�֥�������
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *              (�ǥե������:true)
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ̾�� name ������
     *
     * @else
     *
     * @brief Rebind object
     *
     * This is the same as bind() except as Binding specified by name 
     * already exists. If the binding already exists, new binding will be 
     * replaced.
     *
     * @param name NameComponent of name applied to object
     * @param obj Object that is associated
     * @param force If true, the intermediate context is bound forcibly.
     *              (The default value:true)
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName Name 'name' is invalid.
     *
     * @endif
     */
    void rebind(const CosNaming::Name& name, CORBA::Object_ptr obj,
		const bool force = 1)
      throw (SystemException, NotFound, CannotProceed, InvalidName);
    
    /*!
     * @if jp
     *
     * @brief Object �� rebind ����
     *
     * Object �� rebind ����ݤ�Ϳ����̾����ʸ����ɽ���Ǥ��뤳�Ȱʳ��� rebind()
     * ��Ʊ���Ǥ��롣rebind(toName(string_name), obj) ��������
     *
     * @param string_name ���֥������Ȥ��դ���̾����ʸ����ɽ��
     * @param obj ��Ϣ�դ����륪�֥�������
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *              (�ǥե������:true)
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     *
     * @else
     *
     * @brief Rebind Object
     *
     * This is the same as rebind() except as the given name is string
     * representation when object is rebound. rebind(toName(string_name), obj) 
     * is the same.
     *
     * @param string_name NameComponent of name applied to object
     * @param obj Object that is associated
     * @param force If true, the intermediate context is bound forcibly.
     *              (The default value:true)
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     *
     * @endif
     */
    void rebindByString(const char* string_name, CORBA::Object_ptr obj,
			const bool force = 1)
      throw (SystemException, NotFound, CannotProceed, InvalidName);
    
    /*!
     * @if jp
     *
     * @brief ����Υ���ƥ����Ȥ� bind ���ʤ��� Object �� rebind ����
     *
     * name <c_n> �ǻ��ꤵ�줿 NamingContext �⤷���� Object �����Ǥ�¸�ߤ���
     * ��������� bindRecursive() ��Ʊ���Ǥ��롣
     *
     * name <c_n> �ǻ��ꤵ�줿�Х���ǥ��󥰤����Ǥ�¸�ߤ�����ˤϡ�
     * �������Х���ǥ��󥰤��֤��������롣
     *
     * @param context bind �򳫻Ϥ��롡NamingContext
     * @param name ���֥������Ȥ��դ���̾���� NameComponent
     * @param obj ��Ϣ�դ����륪�֥�������
     *
     * @exception CannotProceed ����Υ���ƥ����Ȥ����Ǥ��ʤ���
     * @exception InvalidName Ϳ����줿 name ��������
     *
     * @else
     *
     * @brief Bind intermediate context recursively and rebind object
     *
     * This is the same as bindRecursive() except as NamingContext 
     * or Object specified by name <c_n> already exists.
     *
     * If the binding specified by name <c_n> already exists, 
     * new binding will be replaced.
     *
     * @param context NamingContext that starts the bind
     * @param name NameComponent of name applied to object
     * @param obj Object that is associated
     *
     * @exception CannotProceed The intermediate context cannot resolved.
     * @exception InvalidName The given name is invalid.
     *
     * @endif
     */
    void rebindRecursive(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name,
			 CORBA::Object_ptr obj)
      throw (SystemException, CannotProceed, InvalidName);
    
    /*!
     * @if jp
     *
     * @brief NamingContext �� bind ����
     *
     * bind ����륪�֥������Ȥ� NamingContext �Ǥ��뤳�Ȥ������ bind() 
     * ��Ʊ���Ǥ��롣
     *
     * @param name ���֥������Ȥ��դ���̾���Υ͡��ॳ��ݡ��ͥ��
     * @param name_cxt ��Ϣ�դ����� NamingContext
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *              (�ǥե������:true)
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     * @exception AlreadyBound name <c_n> �� Object �����Ǥ˥Х���ɤ���Ƥ��롣
     *
     * @else
     *
     * @brief Bind NamingContext
     *
     * This is the same as bind() except as the bound object is NamingContext.
     *
     * @param name NameComponent of name applied to object
     * @param name_cxt Object that is associated
     * @param force If true, the intermediate context is bound forcibly.
     *              (The default value:true)
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     * @exception AlreadyBound The object of name<c_n> is already bound.
     *
     * @endif
     */
    void bindContext(const CosNaming::Name& name,
		     CosNaming::NamingContext_ptr name_cxt,
		     const bool force = 1)
      throw (SystemException, NotFound, CannotProceed,
             InvalidName, AlreadyBound);
    
    /*!
     * @if jp
     *
     * @brief NamingContext �� bind ����
     *
     * bind ����륪�֥������Ȥ� NamingContext �Ǥ��뤳�Ȥ������
     * bindByString() ��Ʊ���Ǥ��롣
     *
     * @param string_name ���֥������Ȥ��դ���̾����ʸ����ɽ��
     * @param name_cxt ��Ϣ�դ����� NamingContext
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *              (�ǥե������:true)
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     * @exception AlreadyBound name <n> �� Object �����Ǥ˥Х���ɤ���Ƥ��롣
     *
     * @else
     *
     * @brief Bind NamingContext
     *
     * This is the same as bindByString() except as the bound object is
     * NamingContext.
     *
     * @param string_name String representation of name applied to object
     * @param name_cxt NamingContext that is associated
     * @param force If true, the intermediate context is bound forcibly.
     *              (The default value:true)
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     * @exception AlreadyBound The object of name<n> is already bound.
     *
     * @endif
     */
    void bindContext(const char* string_name,
		     CosNaming::NamingContext_ptr name_cxt,
		     const bool force = 1)
      throw (SystemException, NotFound, CannotProceed,
             InvalidName, AlreadyBound);
    
    /*!
     * @if jp
     *
     * @brief ����Υ���ƥ����Ȥ�Ƶ�Ū�� bind �� NamingContext �� bind ����
     *
     * bind ����륪�֥������Ȥ� NamingContext �Ǥ��뤳�Ȥ������
     * bindRecursive() ��Ʊ���Ǥ��롣
     *
     * @param context bind �򳫻Ϥ��롡NamingContext
     * @param name ���֥������Ȥ��դ���̾���Υ͡��ॳ��ݡ��ͥ��
     * @param name_cxt ��Ϣ�դ����� NamingContext
     *
     * @else
     *
     * @brief Bind intermediate context recursively and bind NamingContext
     *
     * This is the same as bindRecursive() except as the bound object
     * is NamingContext.
     *
     * @param context NamingContext that starts the bind
     * @param name NameComponent of name applied to object
     * @param name_cxt NamingContext that is associated
     *
     * @endif
     */
    void bindContextRecursive(CosNaming::NamingContext_ptr context,
			      const CosNaming::Name& name,
			      CosNaming::NamingContext_ptr name_cxt);
    
    /*!
     * @if jp
     *
     * @brief NamingContext �� rebind ����
     *
     * name �ǻ��ꤵ�줿����ƥ����Ȥ����Ǥ�¸�ߤ����������� bindContext() 
     * ��Ʊ���Ǥ��롣
     * �Х���ǥ��󥰤����Ǥ�¸�ߤ�����ˤϡ��������Х���ǥ��󥰤�
     * �֤��������롣
     *
     * @param name ���֥������Ȥ��դ���̾���Υ͡��ॳ��ݡ��ͥ��
     * @param name_cxt ��Ϣ�դ����� NamingContext
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *              (�ǥե������:true)
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     *
     * @else
     *
     * @brief Rebind NamingContext
     *
     * This is the same as bindContext() except as context specified
     * by name already exists.
     * If the binding already exists, new binding will be replaced.
     *
     * @param name NameComponent applied to object
     * @param name_cxt Object that is associated
     * @param force If true, the intermediate context is bound forcibly.
     *              (The default value:true)
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName the argument 'name' is invalid.
     *
     * @endif
     */
    void rebindContext(const CosNaming::Name& name,
		       CosNaming::NamingContext_ptr name_cxt,
		       const bool force = 1)
      throw (SystemException, NotFound, CannotProceed, InvalidName);
    
    /*!
     * @if jp
     *
     * @brief NamingContext �� rebind ����
     *
     * name �ǻ��ꤵ�줿����ƥ����Ȥ����Ǥ�¸�ߤ����������� bindContext() 
     * ��Ʊ���Ǥ��롣
     * �Х���ǥ��󥰤����Ǥ�¸�ߤ�����ˤϡ��������Х���ǥ��󥰤�
     * �֤��������롣
     *
     * @param string_name ���֥������Ȥ��դ���̾����ʸ����ɽ��
     * @param name_cxt ��Ϣ�դ����� NamingContext
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *              (�ǥե������:true)
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     *
     * @else
     *
     * @brief Rebind NamingContext
     *
     * This is the same as bindContext() except as context specified
     * by name already exists.
     * If the binding already exists, new binding will be replaced.
     *
     * @param string_name String representation of name applied to object
     * @param name_cxt NamingContext that is associated
     * @param force If true, the intermediate context is bound forcibly.
     *              (The default value:true)
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     *
     * @endif
     */
    void rebindContext(const char* string_name,
		       CosNaming::NamingContext_ptr name_cxt,
		       const bool force = 1)
      throw (SystemException, NotFound, CannotProceed, InvalidName);
    
    /*!
     * @if jp
     *
     * @brief ����Υ���ƥ����Ȥ�Ƶ�Ū�� rebind �� NamingContext �� rebind ����
     *
     * bind ����륪�֥������Ȥ� NamingContext �Ǥ��뤳�Ȥ������
     * rebindRecursive() ��Ʊ���Ǥ��롣
     *
     * @param context bind �򳫻Ϥ��롡NamingContext
     * @param name ���֥������Ȥ��դ���̾���� NameComponent
     * @param name_cxt ��Ϣ�դ����� NamingContext
     *
     * @else
     *
     * @brief Rebind intermediate context recursively and rebind NamingContext
     *
     * This is the same as rebindRecursive() except as the bound object is 
     * NamingContext.
     *
     * @param context NamingContext that starts the bind
     * @param name NameComponent applied to object
     * @param name_cxt NamingContext that is associated
     *
     * @endif
     */
    void rebindContextRecursive(CosNaming::NamingContext_ptr context,
				const CosNaming::Name& name,
				CosNaming::NamingContext_ptr name_cxt);
    
    /*!
     * @if jp
     *
     * @brief Ϳ����줿 NameComponent �˥Х���ɤ���Ƥ��� Object ���֤�
     *
     * name �� bind ����Ƥ��륪�֥������Ȼ��Ȥ��֤���
     * �͡��ॳ��ݡ��ͥ�� <c_1, c_2, ... c_n> �ϺƵ�Ū�˲�褵��롣
     * 
     * CosNaming::resolve() �Ȥۤ�Ʊ����Ư���򤹤뤬�����Ϳ����줿
     * �͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ��Ф��� resolve() ���ƤӽФ��������
     * �ۤʤ롣
     *
     * @param name ��褹�٤����֥������Ȥ�̾���Υ͡��ॳ��ݡ��ͥ��
     *
     * @return ��褵�줿���֥������Ȼ���
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     *
     * @else
     *
     * @brief Return object bound on the specified NameComponent
     *
     * Return the object reference that is bound to name.
     * Resolve the name component<c_1, c_2, ... c_n> recursively.
     * 
     * Almost the same operation as CosNaming::resolve(), 
     * but there is a difference that resolve() is invoked for the root context
     * of the given name server.
     *
     * @param name The name component of object name that should be resolved
     *
     * @return The reference to the resolved object
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     *
     * @endif
     */
    CORBA::Object_ptr resolve(const CosNaming::Name& name)
      throw (SystemException, NotFound, CannotProceed, InvalidName);
    
    /*!
     * @if jp
     *
     * @brief Ϳ����줿 NameComponent �˥Х���ɤ���Ƥ��� Object ���֤�
     *
     * name �� bind ����Ƥ��륪�֥������Ȼ��Ȥ��֤���
     * �͡��ॳ��ݡ��ͥ�� <c_1, c_2, ... c_n> �ϺƵ�Ū�˲�褵��롣
     * 
     * CosNaming::resolve() �Ȥۤ�Ʊ����Ư���򤹤뤬�����Ϳ����줿
     * �͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ��Ф��� resolve() ���ƤӽФ��������
     * �ۤʤ롣
     *
     * @param string_name ��褹�٤����֥������Ȥ�̾����ʸ����ɽ��
     *
     * @return ��褵�줿���֥������Ȼ���
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     *
     * @else
     *
     * @brief Return object bound on the specified name
     *
     * Return the object reference that is bound to name.
     * Resolve the name component<c_1, c_2, ... c_n> recursively.
     * 
     * Almost the same operation as CosNaming::resolve(), 
     * but there is a difference that resolve() is invoked for the root context
     * of the given name server.
     *
     * @param string_name The string representation of object name 
     *             that should be resolved
     *
     * @return The reference to the resolved object
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     *
     * @endif
     */
    CORBA::Object_ptr resolve(const char* string_name)
      throw (SystemException, NotFound, CannotProceed, InvalidName);
    
    /*!
     * @if jp
     *
     * @brief Ϳ����줿 NameComponent �ΥХ���ǥ��󥰤�������
     *
     * name �� bind ����Ƥ��륪�֥������Ȼ��Ȥ��֤���
     * �͡��ॳ��ݡ��ͥ�� <c_1, c_2, ... c_n> �ϺƵ�Ū�˲�褵��롣
     * 
     * CosNaming::unbind() �Ȥۤ�Ʊ����Ư���򤹤뤬�����Ϳ����줿
     * �͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ��Ф��� unbind() ���ƤӽФ��������
     * �ۤʤ롣
     *
     * @param name ������륪�֥������ȤΥ͡��ॳ��ݡ��ͥ��
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     *
     * @else
     *
     * @brief Unbind a binding specified by NameComponent
     *
     * Return the object reference that is bound to name.
     * Resolve the name component<c_1, c_2, ... c_n> recursively.
     * 
     * Almost the same operation as CosNaming::unbind(), 
     * but there is a difference that unbind() is invoked for the root context
     * of the always given name server.
     *
     * @param name The name component of the deleted object
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     *
     * @endif
     */
    void unbind(const CosNaming::Name& name)
      throw (SystemException, NotFound, CannotProceed, InvalidName);
    
    /*!
     * @if jp
     *
     * @brief Ϳ����줿 NameComponent �ΥХ���ǥ��󥰤�������
     *
     * name �� bind ����Ƥ��륪�֥������Ȼ��Ȥ��֤���
     * �͡��ॳ��ݡ��ͥ�� <c_1, c_2, ... c_n> �ϺƵ�Ū�˲�褵��롣
     * 
     * CosNaming::unbind() �Ȥۤ�Ʊ����Ư���򤹤뤬�����Ϳ����줿
     * �͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ��Ф��� unbind() ���ƤӽФ��������
     * �ۤʤ롣
     *
     * @param string_name ��褹�٤����֥������Ȥ�̾����ʸ����ɽ��
     *
     * @return ��褵�줿���֥������Ȼ���
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     *
     * @else
     *
     * @brief Unbind a binding specified by string representation
     *
     * Return the object reference that is bound to name.
     * Resolve the name component<c_1, c_2, ... c_n> recursively.
     * 
     * Almost the same operation as CosNaming::unbind(), 
     * but there is a difference that unbind() is invoked for the root context
     * of the always given name server.
     *
     * @param string_name The string representation of object name
     *                    that should be resolved
     *
     * @return The resolved object reference
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     *
     * @endif
     */
    void unbind(const char* string_name)
      throw (SystemException, NotFound, CannotProceed, InvalidName);
    
    /*!
     * @if jp
     *
     * @brief ����������ƥ����Ȥ���������
     *
     * Ϳ����줿�͡��ॵ���о���������줿 NamingContext ���֤���
     * �֤��줿 NamingContext �� bind ����Ƥ��ʤ���
     * 
     * @return �������줿������ NamingContext
     *
     * @else
     *
     * @brief Create new NamingContext
     *
     * Return NamingContext that has been created on the given name server.
     * The returned NamingContext has not bound yet.
     * 
     * @return New created NamingContext
     *
     * @endif
     */
    CosNaming::NamingContext_ptr newContext();
    
    /*!
     * @if jp
     *
     * @brief ����������ƥ����Ȥ� bind ����
     *
     * Ϳ����줿 name ���Ф��ƿ���������ƥ����Ȥ�Х���ɤ��롣
     * �������줿��NamingContext �ϥ͡��ॵ���о���������줿��ΤǤ��롣
     * 
     * @param name NamingContext���դ���̾���Υ͡��ॳ��ݡ��ͥ��
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *              (�ǥե������:true)
     *
     * @return �������줿������ NamingContext
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     * @exception AlreadyBound name <n> �� Object �����Ǥ˥Х���ɤ���Ƥ��롣
     *
     * @else
     *
     * @brief Bind new NamingContext
     *
     * Bind new context for the given name.
     * The created NamingContext is a creation on the name server.
     * 
     * @param name NameComponent applied to NamingContext
     * @param force If true, the intermediate context is bound forcibly.
     *              (The default value:true)
     *
     * @return New created NamingContext
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     * @exception AlreadyBound The object of name<n> is already bound.
     *
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindNewContext(const CosNaming::Name& name, bool force = true)
      throw (SystemException, NotFound, CannotProceed,
             InvalidName, AlreadyBound);
    
    /*!
     * @if jp
     *
     * @brief ����������ƥ����Ȥ� bind ����
     *
     * Ϳ����줿ʸ������б����뿷��������ƥ����Ȥ�Х���ɤ��롣
     * �������줿��NamingContext �ϥ͡��ॵ���о���������줿��ΤǤ��롣
     * 
     * @param string_name NamingContext���դ���̾����ʸ����ɽ��
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *              (�ǥե������:true)
     * 
     * @return �������줿������ NamingContext
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     * @exception AlreadyBound name <n> �� Object �����Ǥ˥Х���ɤ���Ƥ��롣
     *
     * @else
     *
     * @brief Bind new NamingContext
     *
     * Bind new context corresponding to the given string.
     * The created NamingContext is a creation on the name server.
     * 
     * @param string_name The string representation of name applied to 
     *                    NamingContext
     * @param force If true, the intermediate context is bound forcibly.
     *              (The default value:true)
     * 
     * @return New created NamingContext
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     * @exception AlreadyBound The object of name<n> is already bound.
     *
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindNewContext(const char* string_name, bool force = true)
      throw (SystemException, NotFound, CannotProceed,
             InvalidName, AlreadyBound);
    
    /*!
     * @if jp
     *
     * @brief NamingContext ���󥢥��ƥ��ֲ�����
     *
     * context �ǻ��ꤵ�줿 NamingContext ���󥢥��ƥ��ֲ����롣
     * context ��¾�Υ���ƥ����Ȥ��Х���ɤ���Ƥ������ NotEmpty �㳰��
     * ȯ�����롣
     * 
     * @param context �󥢥��ƥ��ֲ����� NamingContext
     *
     * @exception NotEmpty �о�context ��¾�Υ���ƥ����Ȥ��Х���ɤ���Ƥ��롣
     *
     * @else
     *
     * @brief Destroy the naming context
     *
     * Destroy the specified naming context.
     * Any bindings should be <unbind> in which the given context is bound to
     * some names before invoking <destroy> operation on it. 
     *
     * @param context NamingContext which is destroied.
     *     
     * @exception NotEmpty The target context is bound to the other context.
     *
     * @endif
     */
    void destroy(CosNaming::NamingContext_ptr context)
      throw (SystemException, NotEmpty);
    
    /*!
     * @if jp
     * @brief NamingContext ��Ƶ�Ū�˲��ä��󥢥��ƥ��ֲ�����
     *
     * context ��Ϳ����줿 NamingContext ���Ф��ơ�name �ǻ��ꤵ�줿
     * �͡��ॳ��ݡ��ͥ�� <c_1, ... c_(n-1)> �� NamingContext �Ȥ���
     * ��褷�ʤ��顢̾�� <c_n> ���Ф��� �󥢥��ƥ��ֲ���Ԥ���
     *
     * @param context �󥢥��ƥ��ֲ����� NamingContext
     *
     * @exception NotEmpty �о�context ��¾�Υ���ƥ����Ȥ��Х���ɤ���Ƥ��롣
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     *
     * @else
     *
     * @brief Destroy the naming context recursively
     *
     * For NamingContext given by Context, Destroy name <c_n> with 
     * solving the name component specified by name as NamingContext recursively.
     *
     * @param context NamingContext which is Destroied.
     *
     * @exception NotEmpty The target context is bound to the other context.
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     *
     * @endif
     */
    void destroyRecursive(CosNaming::NamingContext_ptr context)
      throw (SystemException, NotEmpty, NotFound, CannotProceed, InvalidName);
    
    /*!
     * @if jp
     * @brief ���٤Ƥ� Binding ��������
     *
     * ��Ͽ����Ƥ������Ƥ�Binding �������롣
     *
     * @else
     * @brief Destroy all bindings
     *
     * Destroy all bindings that are registered.
     *
     * @endif
     */
    void clearAll();
    
    /*!
     * @if jp
     * @brief Ϳ����줿 NamingContext �� Binding ���������
     *
     * ���ꤵ�줿 NamingContext �� Binding ��������롣
     *
     * @param name_cxt Binding �����о� NamingContext
     * @param how_many Binding ��������볬�ؤο���
     * @param bl �������� Binding ���ݻ�����ۥ��
     * @param bi �������� Binding �򤿤ɤ뤿��Υ��ƥ졼��
     *
     * @else
     * @brief Get Binding of the given NamingContext
     *
     * Get Binding of the given NamingContext.
     *
     * @param name_cxt NamingContext of the getting target Binding
     * @param how_many The depth to get Binding
     * @param bl The holder to hold the got Binding
     * @param bi The iterator to detect the got Binding
     *
     * @endif
     */
    void list(CosNaming::NamingContext_ptr name_cxt,
	      CORBA::ULong how_many,
	      CosNaming::BindingList_var& bl,
	      CosNaming::BindingIterator_var& bi);
    
    //============================================================
    // interface of NamingContextExt
    //============================================================
    /*!
     * @if jp
     * @brief Ϳ����줿 NameComponent ��ʸ����ɽ�����֤�
     *
     * ���ꤵ�줿 NameComponent ��ʸ�����Ѵ����롣
     *
     * @param name �Ѵ��о� NameComponent
     *
     * @return ʸ�����Ѵ����
     *
     * @exception InvalidName ���� name ��̾����������
     *
     * @else
     * @brief Get string representation of given NameComponent
     *
     * Transform specified NameComponent into string representation.
     *
     * @param name The target NameComponent for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @exception InvalidName The argument 'name' is invalid.
     *
     * @endif
     */
    char* toString(const CosNaming::Name& name)
      throw (SystemException, InvalidName);
    
    /*!
     * @if jp
     * @brief Ϳ����줿ʸ����ɽ���� NameComponent ��ʬ�򤹤�
     *
     * ���ꤵ�줿ʸ����� NameComponent ���Ѵ����롣
     *
     * @param string_name �Ѵ��о�ʸ����
     *
     * @return NameComponent �Ѵ����
     *
     * @exception InvalidName ���� string_name ��������
     *
     * @else
     * @brief Resolve given string representation to NameComponent
     *
     * Transform given string representation to NameComponent.
     *
     * @param string_name The target string representation to transform
     *
     * @return NameComponent The result of transformation
     *
     * @exception InvalidName The argument 'name' is invalid.
     *
     * @endif
     */
    CosNaming::Name toName(const char* string_name)
      throw (SystemException, InvalidName);
    
    /*!
     * @if jp
     * @brief Ϳ����줿 addre �� string_name ���� URLɽ�����������
     *
     * ���ꤵ�줿���ɥ쥹��̾�Τ�URL���Ѵ����롣
     *
     * @param addr �Ѵ��оݥ��ɥ쥹
     * @param string_name �Ѵ��о�̾��
     *
     * @return URL �Ѵ����
     *
     * @exception InvalidAddress ���� addr ��������
     * @exception InvalidName ���� string_name ��������
     *
     * @else
     * @brief Get URL representation from given addr and string_name
     *
     * Convert specified addr and string_name into URL
     *
     * @param addr The target address for conversion
     * @param string_name The target name for conversion
     *
     * @return URL Conversion result
     *
     * @exception InvalidAddress The argument 'addr' is invalid.
     * @exception InvalidName The argument 'string_name' is invalid.
     *
     * @endif
     */
    char* toUrl(char* addr, char* string_name)
      throw (SystemException, InvalidAddress, InvalidName);
    
    /*!
     * @if jp
     * @brief Ϳ����줿ʸ����ɽ���� resolve �����֥������Ȥ��֤�
     *
     * ���ꤵ�줿ʸ����ɽ����resolve�������֥������Ȥ�������롣
     *
     * @param string_name �����оݥ��֥�������ʸ����ɽ��
     *
     * @return ��褵�줿���֥�������
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     * @exception AlreadyBound name <n> �� Object �����Ǥ˥Х���ɤ���Ƥ��롣
     *
     * @else
     * @brief Resolve from name of string representation and get object
     *
     * Resolve specified string representation and get object
     *
     * @param string_name The string representation of getting target object
     *
     * @return The resolved object
     *
     * @exception NotFound There is not <c_1, c_2, ..., c_(n-1)>.
     * @exception CannotProceed Processing cannot be continued for some reasons.
     * @exception InvalidName The argument 'name' is invalid.
     * @exception AlreadyBound The object of name<n> is already bound.
     *
     * @endif
     */
    CORBA::Object_ptr resolveStr(const char* string_name)
      throw (SystemException, NotFound, CannotProceed,
             InvalidName, AlreadyBound);
    
    //============================================================
    // Find functions
    //============================================================
    
    //    ObjectList find(const char* name, const char* kind);
    //    ObjectList findById(const char* name, const char* kind);
    //    ObjectList findByKind(const char* name, const char* kind);
    
    /*!
     * @if jp
     *
     * @brief ���֥������Ȥ�̾����Х���ɤޤ��ϲ�褹��
     *
     * ���ꤵ�줿����ƥ����Ȥ��Ф��ƥ��֥������Ȥ� NameComponent �ǻ��ꤵ�줿
     * ���֤˥Х���ɤ��롣
     * Ʊ��ս�˴���¾�����Ǥ��Х���ɺѤߤξ��ϡ���¸�ΥХ���ɺѤ����Ǥ�
     * �������롣
     *
     * @param context bind �⤷���� resole �оݥ���ƥ�����
     * @param name ���֥������Ȥ��դ���̾���� NameComponent
     * @param obj ��Ϣ�դ����� Object
     *
     * @return NameComponent �ǻ��ꤵ�줿���֤˥Х���ɤ���Ƥ��륪�֥�������
     *
     * @else
     * @brief Bind or resolve the given name component
     *
     * Bind object at the position that specified in NameComponent for the 
     * specified context.
     * When other elements are already bound at the same position, get the 
     * already bound element.
     *
     * @param context The context to bind or resole
     * @param name NameComponent applied to object
     * @param obj Object that is associated
     *
     * @return The object that is bound at position specified with NameComponent
     *
     * @endif
     */
    CORBA::Object_ptr bindOrResolve(CosNaming::NamingContext_ptr context,
				    const CosNaming::Name& name,
				    CORBA::Object_ptr obj);
    
    /*!
     * @if jp
     *
     * @brief ̾����Х���ɤޤ��ϲ�褹��
     *
     * ���ꤵ�줿����ƥ����Ȥ��Ф��� Context�� NameComponent �ǻ��ꤵ�줿���֤�
     * �Х���ɤ��롣
     * Ʊ��ս�˴���¾�����Ǥ��Х���ɺѤߤξ��ϡ���¸�ΥХ���ɺѤ����Ǥ�
     * �������롣
     *
     * @param context bind �⤷���� resole �оݥ���ƥ�����
     * @param name ����ƥ����Ȥ��դ���̾���� NameComponent
     * @param new_context ��Ϣ�դ����� Context
     *
     * @return NameComponent �ǻ��ꤵ�줿���֤˥Х���ɤ���Ƥ���Context
     *
     * @else
     * @brief Bind or resolve the given name component
     *
     * Bind Context at the position that specified in NameComponent for the 
     * specified context.
     * When other elements are already bound at the same position, get the 
     * already bound element.
     *
     * @param context The context to bind or resole
     * @param name NameComponent applied to object
     * @param new_context Context that is associated
     *
     * @return The Context that is bound at the position specified with 
     *         NameComponent
     *
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindOrResolveContext(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name,
			 CosNaming::NamingContext_ptr new_context);
    
    /*!
     * @if jp
     * @brief ̾����Х���ɤޤ��ϲ�褹��
     *
     * ���ꤵ�줿����ƥ����Ȥ��Ф��� NameComponent �ǻ��ꤵ�줿���֤�
     * ��������ƥ����Ȥ�Х���ɤ��롣
     * Ʊ��ս�˴���¾�����Ǥ��Х���ɺѤߤξ��ϡ���¸�ΥХ���ɺѤ����Ǥ�
     * �������롣
     *
     * @param context bind �⤷���� resole �оݥ���ƥ�����
     * @param name �����������륳��ƥ����Ȥΰ��֤�ɽ�� NameComponent
     *
     * @return NameComponent �ǻ��ꤵ�줿���֤˥Х���ɤ���Ƥ���Context
     *
     * @else
     * @brief Bind or resolve the given name component
     *
     * Bind new Context at the position that specified in NameComponent for the 
     * specified context.
     * When other elements are already bound at the same position, get the 
     * already bound element.
     *
     * @param context The context to bind or resole
     * @param name NameComponent that indicates the position of new context
     *
     * @return The Context that is bound at the position specified with 
     *         NameComponent
     *
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindOrResolveContext(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name);
    
    /*!
     * @if jp
     * @brief �͡��ॵ���Ф�̾�����������
     *
     * ���ꤷ���͡��ॵ���Ф�̾����������롣
     *
     * @return �͡��ॵ���Ф�̾��
     *
     * @else
     * @brief Get the name of name server
     *
     * Get the configured name of name server
     *
     * @return The name of name server
     *
     * @endif
     */
    const char* getNameServer();
    
    /*!
     * @if jp
     * @brief �롼�ȥ���ƥ����Ȥ��������
     *
     * ���ꤷ���͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ�������롣
     *
     * @return �͡��ॵ���ФΥ롼�ȥ���ƥ�����
     *
     * @else
     * @brief Get the root context
     *
     * Get the root context of the configured name server
     *
     * @return Root context ot name server
     *
     * @endif
     */
    CosNaming::NamingContext_ptr getRootContext();
    
    /*!
     * @if jp
     * @brief ���֥������Ȥ��͡��ߥ󥰥���ƥ����Ȥ�Ƚ�̤���
     *
     * ���ꤷ�����Ǥ��͡��ߥ󥰥���ƥ����Ȥ�Ƚ�̤���
     *
     * @param obj Ƚ���о�����
     *
     * @return Ƚ�̷��(�͡��ߥ󥰥���ƥ�����:true������ʳ�:false)
     *
     * @else
     * @brief Determine whether the object is NamingContext
     *
     * Determine whether the specified element is NamingContext
     *
     * @param obj The target element for determination
     *
     * @return Determination result (NamingContext:true, Else:false)
     *
     * @endif
     */
    bool isNamingContext(CORBA::Object_ptr obj);
    
    /*!
     * @if jp
     * @brief Ϳ����줿̾�����͡��ߥ󥰥���ƥ����Ȥ��ɤ���
     *
     * NameComponent�ǻ��ꤷ�����Ǥ��͡��ߥ󥰥���ƥ����Ȥ�Ƚ�̤���
     *
     * @param name Ƚ���о�NameComponent
     *
     * @return Ƚ�̷��(�͡��ߥ󥰥���ƥ�����:true������ʳ�:false)
     *
     * @else
     * @brief Determine whether the given name component is NamingContext
     *
     * Determine whether the specified element is NameComponent
     *
     * @param name The target NameComponent for determination
     *
     * @return Determination result (NamingContext:true, Else:false)
     *
     * @endif
     */
    bool isNamingContext(const CosNaming::Name& name);
    
    /*!
     * @if jp
     * @brief Ϳ����줿̾�����͡��ߥ󥰥���ƥ����Ȥ��ɤ���
     *
     * ʸ����ǻ��ꤷ�����Ǥ��͡��ߥ󥰥���ƥ����Ȥ�Ƚ�̤���
     *
     * @param string_name Ƚ���о�ʸ����
     *
     * @return Ƚ�̷��(�͡��ߥ󥰥���ƥ�����:true������ʳ�:false)
     *
     * @else
     * @brief Determine whether the given string name is NamingContext
     *
     * Determine whether the element specified by string name is NamingContext
     *
     * @param string_name The string representation for determination
     *
     * @return Determination result (NamingContext:true, Else:false)
     *
     * @endif
     */
    bool isNamingContext(const char* string_name);
    
    /*!
     * @if jp
     * @brief �͡��ॳ��ݡ��ͥ�Ȥ���ʬ���֤�
     *
     * ���ꤵ�줿�ϰϤΥ͡��ॳ��ݡ��ͥ�Ȥ�������롣
     * ��λ���֤����ꤵ��Ƥ��ʤ����ϡ��Ǹ�����Ǥ�������͡��ॳ��ݡ��ͥ��
     * ���֤���
     *
     * @param name �����о�NameComponent
     * @param begin �����ϰϳ��ϰ���
     * @param end �����ϰϽ�λ����(�ǥե������:-1)
     *
     * @return NameComponent �������
     *
     * @else
     * @brief Get subset of given name component
     *
     * Get the name component in specified range.
     * Return the name component except the last element if the end 
     * position is not specified.
     *
     * @param name The target NameComponent for search
     * @param begin The beginning position for getting range
     * @param end The end position for getting range (The default value:-1)
     *
     * @return NameComponent Getting result
     *
     * @endif
     */
    CosNaming::Name subName(const CosNaming::Name& name,
			    CORBA::Long begin,
			    CORBA::Long end = -1);
    
  protected:
    /*!
     * @if jp
     * @brief �͡��ॳ��ݡ��ͥ�Ȥ�ʸ����ɽ�����������
     *
     * ���ꤷ���ϰϤΥ͡��ॳ��ݡ��ͥ�Ȥ�ʸ����ɽ����������롣
     * ʸ����ɽ���ϡ�NameComponent�ι�����{Nc[0], Nc[1], Nc[2]...}�ξ�硢
     *   Nc[0]id.Nc[0].kind/Nc[1]id.Nc[1].kind/Nc[2].id/Nc[2].kind...
     * �Ȥ��������Ǽ����Ǥ��롣
     * ��������ʸ�����Ĺ�������ꤷ��Ĺ���ʾ�ξ��ϡ�
     * ���ꤷ��Ĺ�����ڤ�ΤƤ��롣
     *
     * @param name �����о�NameComponent
     * @param string_name �������ʸ����
     * @param slen �����о�ʸ���������
     *
     * @else
     * @brief Get string representation of name component
     *
     * Get string representation of the name component in specified range.
     * In string representation, if NameComponent consists of 
     * {Nc[0],Nc[1],Nc[2]...}, the format of 
     * Nc[0]id.Nc[0].kind/Nc[1]id.Nc[1].kind/Nc[2].id/Nc[2].kind...
     * will be got.
     * It is rounded by the specified length when the length of the got
     * string is over the specified length. 
     *
     * @param name The getting target NameComponent
     * @param string_name The string of getting result
     * @param slen The maximum length value of getting string
     *
     * @endif
     */
    void nameToString(const CosNaming::Name& name, char* string_name,
		      CORBA::ULong slen);
    /*!
     * @if jp
     * @brief �͡��ॳ��ݡ��ͥ�Ȥ�ʸ����ɽ������ʸ��Ĺ���������
     *
     * ���ꤷ���͡��ॳ��ݡ��ͥ�Ȥ�ʸ�����ɽ����������Ĺ����������롣
     * ʸ����ɽ���ϡ�NameComponent�ι�����{Nc[0],Nc[1],Nc[2]...}�ξ�硢
     *   Nc[0]id.Nc[0].kind/Nc[1]id.Nc[1].kind/Nc[2].id/Nc[2].kind...
     * �Ȥ��������Ǽ����Ǥ��롣
     *
     * @param name �����о�NameComponent
     *
     * @return ���ꤷ���͡��ॳ��ݡ��ͥ�Ȥ�ʸ����Ĺ��
     *
     * @else
     * @brief Get string length of the name component's string representation
     *
     * Get string length of the name component's string representation.
     * In string representation, if NameComponent consists of 
     * {Nc[0],Nc[1],Nc[2]������}, the format of 
     * Nc[0]id.Nc[0].kind/Nc[1]id.Nc[1].kind/Nc[2].id/Nc[2].kind������
     * will be got.
     *
     * @param name The getting target NameComponent
     *
     * @return The string length value of specified component
     *
     * @endif
     */
    CORBA::ULong getNameLength(const CosNaming::Name& name);
    
    /*!
     * @if jp
     * @brief ʸ�����ʬ��
     *
     * ʸ�������ꤷ���ǥ�ߥ���ʬ�䤹�롣
     *
     * @param input ʬ���о�ʸ����
     * @param delimiter ʬ���ѥǥ�ߥ�
     * @param results ʬ����
     *
     * @return ʬ�䤷��ʸ��������ǿ�
     *
     * @else
     * @brief Split of string
     *
     * Split string with specified delimiter.
     *
     * @param input The split target string
     * @param delimiter The delimiter for split
     * @param results Split result
     *
     * @return The number of split string elements
     *
     * @endif
     */
    unsigned int split(const std::string& input,
		       const std::string& delimiter,
		       std::vector<std::string>& results);
    
    /*!
     * @if jp
     * @brief ORB
     * @else
     * @brief ORB
     * @endif
     */
    CORBA::ORB_var m_varORB;
    
    /*!
     * @if jp
     * @brief �͡��ॵ����̾��
     * @else
     * @brief Name of the name server
     * @endif
     */
    std::string m_nameServer;
    /*!
     * @if jp
     * @brief ���ꤷ���͡��ॵ���ФΥ롼�ȥ���ƥ�����
     * @else
     * @brief The root context of specified name server
     * @endif
     */
    CosNaming::NamingContextExt_var m_rootContext;
    
  private:
    CORBA::ULong m_blLength;
    
  }; // class CorbaNaming
}; // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // end of RTC_CORBANAMING_H
