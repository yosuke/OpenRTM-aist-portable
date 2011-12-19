// -*- C++ -*-
/*!
 * @file CorbaNaming.cpp
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
 * $Id: CorbaNaming.cpp 2019 2011-01-06 17:02:23Z n-ando $
 *
 */

#ifdef WIN32
#define ACE_HAS_WINSOCK2 0
#endif //WIN32

#include <assert.h>
#include <rtm/CorbaNaming.h>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  CorbaNaming::CorbaNaming(CORBA::ORB_ptr orb)
    : m_varORB(orb), m_nameServer(""),
      m_rootContext(CosNaming::NamingContextExt::_nil()),
      m_blLength(100)
  {
  }
  
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  CorbaNaming::CorbaNaming(CORBA::ORB_ptr orb, const char* name_server)
    : m_varORB(CORBA::ORB::_duplicate(orb)), m_nameServer(name_server),
      m_rootContext(CosNaming::NamingContextExt::_nil()),
      m_blLength(100)
  {
    CORBA::Object_var obj;
    m_nameServer = "corbaloc::" + m_nameServer + "/NameService";
    try
      {
	obj = m_varORB->string_to_object(m_nameServer.c_str());
	m_rootContext = CosNaming::NamingContextExt::_narrow(obj);
	if (CORBA::is_nil(m_rootContext)) throw std::bad_alloc();
      }
    catch(...)
      {
	throw std::bad_alloc();
      }
  }
  
  /*!
   * @if jp
   * @brief �͡��ߥ󥰥����ӥ��ν����
   * @else
   * @brief Initialize the Naming Service
   * @endif
   */
  void CorbaNaming::init(const char* name_server)
  {
    m_nameServer = name_server;
    m_nameServer = "corbaloc::" + m_nameServer + "/NameService";
    CORBA::Object_var obj;
    obj = m_varORB->string_to_object(m_nameServer.c_str());
    m_rootContext = CosNaming::NamingContextExt::_narrow(obj);
    if (CORBA::is_nil(m_rootContext)) throw std::bad_alloc();
  }

  bool CorbaNaming::isAlive()
  {
    try
      {
        if (m_rootContext->_non_existent()) { return false; }
        return true;
      }
    catch (...)
      {
        return false;
      }
    return false;
  }
  
  /*!
   * @if jp
   * @brief Object �� bind ����
   * @else
   * @brief Bind object on specified name component position
   * @endif
   */
  void CorbaNaming::bind(const CosNaming::Name& name, CORBA::Object_ptr obj,
			 const bool force)
    throw (SystemException, NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    try
      {
	m_rootContext->bind(name, obj);
      }
    catch (NotFound& e)
      {
	force ? bindRecursive(m_rootContext, name, obj) : throw e;
      }
    catch (CannotProceed& e)
      {
#ifndef ORB_IS_RTORB
        force ? bindRecursive(e.cxt, e.rest_of_name, obj) : throw e;
#else // ORB_IS_RTORB
        force ? bindRecursive(e.cxt(), e.rest_of_name(), obj) : throw e;
#endif // ORB_IS_RTORB
      }
  }
  
  /*!
   * @if jp
   * @brief Object �� bind ����
   * @else
   * @brief Bind object on specified string name position
   * @endif
   */
  void CorbaNaming::bindByString(const char* string_name, CORBA::Object_ptr obj,
				 const bool force)
    throw (SystemException, NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    this->bind(toName(string_name), obj, force);
  }
  
  /*!
   * @if jp
   * @brief ����Υ���ƥ����Ȥ�Ƶ�Ū�� bind ���ʤ��� Object �� bind ����
   * @else
   * @brief Bind intermediate context recursively and bind object
   * @endif
   */
  void CorbaNaming::bindRecursive(CosNaming::NamingContext_ptr context,
				  const CosNaming::Name& name,
				  CORBA::Object_ptr obj)
    throw (SystemException, CannotProceed, InvalidName, AlreadyBound)
  {
    CORBA::ULong len(name.length());
    CosNaming::NamingContext_var cxt;
    cxt = CosNaming::NamingContext::_duplicate(context);
    
    for (CORBA::ULong i = 0; i < len; ++i)
      {
	if (i == (len - 1))
	  { // this operation may throw AlreadyBound, 
	    cxt->bind(subName(name, i, i), obj);
	    return;
	  }
	else
	  { // If the context is not a NamingContext, CannotProceed is thrown
	    if (isNamingContext(cxt))
	      cxt = bindOrResolveContext(cxt, subName(name, i, i));
	    else
	      throw CannotProceed(cxt, subName(name, i));
	  }
      }
    return;
  }
  
  /*!
   * @if jp
   * @brief Object �� rebind ����
   * @else
   * @brief Rebind object
   * @endif
   */
  void CorbaNaming::rebind(const CosNaming::Name& name,
			   CORBA::Object_ptr obj,
			   const bool force)
    throw (SystemException, NotFound, CannotProceed, InvalidName)
  {
    try
      {
	m_rootContext->rebind(name, obj);
      }
    catch (NotFound& e)
      {
	force ? rebindRecursive(m_rootContext, name, obj) : throw e;
      }
    catch (CannotProceed& e)
      {
#ifndef ORB_IS_RTORB
        force ? rebindRecursive(e.cxt, e.rest_of_name, obj) : throw e;
#else // ORB_IS_RTORB
        force ? rebindRecursive(e.cxt(), e.rest_of_name(), obj) : throw e;
#endif // ORB_IS_RTORB
      }
  }
  
  /*!
   * @if jp
   * @brief Object �� rebind ����
   * @else
   * @brief Rebind object
   * @endif
   */
  void CorbaNaming::rebindByString(const char* string_name,
				   CORBA::Object_ptr obj,
				   const bool force)
    throw (SystemException, NotFound, CannotProceed, InvalidName)
  {
    rebind(toName(string_name), obj, force);
  }
  
  /*!
   * @if jp
   * @brief ����Υ���ƥ����Ȥ� bind ���ʤ��� Object �� rebind ����
   * @else
   * @brief Bind intermediate context recursively and rebind object
   * @endif
   */
  void CorbaNaming::rebindRecursive(CosNaming::NamingContext_ptr context,
				    const CosNaming::Name& name,
				    CORBA::Object_ptr obj)
    throw (SystemException, CannotProceed, InvalidName)
  {
    CORBA::ULong len(name.length());
    CosNaming::NamingContext_var cxt;
    cxt = CosNaming::NamingContext::_duplicate(context);
    
    for (CORBA::ULong i = 0; i < len; ++i)
      {
	if (i == (len - 1))
	  {
	    cxt->rebind(subName(name, i, i), obj);
	    return;
	  }
	else
	  { // If the context is not a NamingContext, CannotProceed is thrown
	    if (isNamingContext(cxt))
	      {
		try
		  {
		    cxt = cxt->bind_new_context(subName(name, i, i));
		  }
		catch (AlreadyBound& e)
		  {
		    (void)(e);
		    cxt = CosNaming::
		      NamingContextExt::
		      _narrow(cxt->resolve(subName(name, i, i)));
		  }
	      }
	    else
	      throw CannotProceed(cxt, subName(name, i));
	  }
      }
    return;
  }
  
  /*!
   * @if jp
   * @brief NamingContext �� bind ����
   * @else
   * @brief Bind NamingContext
   * @endif
   */
  void CorbaNaming::bindContext(const CosNaming::Name& name,
				CosNaming::NamingContext_ptr name_cxt,
				const bool force)
    throw (SystemException, NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    bind(name, name_cxt, force);
  }
  
  /*!
   * @if jp
   * @brief NamingContext �� bind ����
   * @else
   * @brief Bind NamingContext
   * @endif
   */
  void CorbaNaming::bindContext(const char* string_name,
				CosNaming::NamingContext_ptr name_cxt,
				const bool force)
    throw (SystemException, NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    bindContext(toName(string_name), name_cxt, force);
  }
  
  /*!
   * @if jp
   * @brief ����Υ���ƥ����Ȥ�Ƶ�Ū�� bind �� NamingContext �� bind ����
   * @else
   * @brief Bind intermediate context recursively and bind NamingContext
   * @endif
   */
  void
  CorbaNaming::bindContextRecursive(CosNaming::NamingContext_ptr context,
				    const CosNaming::Name& name,
				    CosNaming::NamingContext_ptr name_cxt)
  {
    bindRecursive(context, name, name_cxt);
    return;
  }
  
  /*!
   * @if jp
   * @brief NamingContext �� rebind ����
   * @else
   * @brief Rebind NamingContext
   * @endif
   */
  void CorbaNaming::rebindContext(const CosNaming::Name& name,
				  CosNaming::NamingContext_ptr name_cxt,
				  const bool force)
    throw (SystemException, NotFound, CannotProceed, InvalidName)
  {
    rebind(name, name_cxt, force);
    return;
  }
  
  /*!
   * @if jp
   * @brief NamingContext �� rebind ����
   * @else
   * @brief Rebind NamingContext
   * @endif
   */
  void CorbaNaming::rebindContext(const char* string_name,
				  CosNaming::NamingContext_ptr name_cxt,
				  const bool force)
    throw (SystemException, NotFound, CannotProceed, InvalidName)
  {
    rebindContext(toName(string_name), name_cxt, force);
  }
  
  /*!
   * @if jp
   * @brief ����Υ���ƥ����Ȥ�Ƶ�Ū�� rebind �� NamingContext �� rebind ����
   * @else
   * @brief Rebind intermediate context recursively and rebind NamingContext 
   * @endif
   */
  void
  CorbaNaming::rebindContextRecursive(CosNaming::NamingContext_ptr context,
				      const CosNaming::Name& name,
				      CosNaming::NamingContext_ptr name_cxt)
  {
    rebindRecursive(context, name, name_cxt);
    return;
  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿 NameComponent �˥Х���ɤ���Ƥ��� Object ���֤�
   * @else
   * @brief Return object bound on the specified NameComponent
   * @endif
   */
  CORBA::Object_ptr CorbaNaming::resolve(const CosNaming::Name& name)
    throw (SystemException, NotFound, CannotProceed, InvalidName)
  { 
    return m_rootContext->resolve(name);
  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿 NameComponent �˥Х���ɤ���Ƥ��� Object ���֤�
   * @else
   * @brief Return object bound on the specified name
   * @endif
   */
  CORBA::Object_ptr CorbaNaming::resolve(const char* string_name)
    throw (SystemException, NotFound, CannotProceed, InvalidName)
  { 
    return resolve(toName(string_name));
  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿 NameComponent �ΥХ���ǥ��󥰤�������
   * @else
   * @brief Unbind a binding specified by NameComponent
   * @endif
   */   
  void CorbaNaming::unbind(const CosNaming::Name& name)
    throw (SystemException, NotFound, CannotProceed, InvalidName)
  {
    m_rootContext->unbind(name);
  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿 NameComponent �ΥХ���ǥ��󥰤�������
   * @else
   * @brief Unbind a binding specified by NameComponent
   * @endif
   */
  void CorbaNaming::unbind(const char* string_name)
    throw (SystemException, NotFound, CannotProceed, InvalidName)
  {
    unbind(toName(string_name));
  }
  
  /*!
   * @if jp
   * @brief ����������ƥ����Ȥ���������
   * @else
   * @brief Create new NamingContext
   * @endif
   */
  CosNaming::NamingContext_ptr CorbaNaming::newContext()
  {
    return m_rootContext->new_context();
  }
  
  /*!
   * @if jp
   * @brief ����������ƥ����Ȥ� bind ����
   * @else
   * pbrief Bind new namingContext
   * @endif
   */
  CosNaming::NamingContext_ptr
  CorbaNaming::bindNewContext(const CosNaming::Name& name, bool force)
    throw (SystemException, NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    try
      {
	return m_rootContext->bind_new_context(name);
      }
    catch (NotFound& e)
      {
	force ? bindRecursive(m_rootContext, name, newContext()) : throw e;
      }
    catch (CannotProceed& e)
      {
#ifndef ORB_IS_RTORB
        force ? bindRecursive(e.cxt, e.rest_of_name, newContext()) : throw e;
#else // ORB_IS_RTORB
        force ? 
          bindRecursive(e.cxt(), e.rest_of_name(), newContext()) : throw e;
#endif // ORB_IS_RTORB
      }
    return CosNaming::NamingContext::_nil();
  }
  
  /*!
   * @if jp
   * @brief ����������ƥ����Ȥ� bind ����
   * @else
   * pbrief Bind new namingContext
   * @endif
   */
  CosNaming::NamingContext_ptr
  CorbaNaming::bindNewContext(const char* string_name, bool force)
    throw (SystemException, NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    return bindNewContext(toName(string_name));
  }
  
  /*!
   * @if jp
   * @brief NamingContext ���󥢥��ƥ��ֲ�����
   * @else
   * @brief Destroy the naming context
   * @endif
   */
  void CorbaNaming::destroy(CosNaming::NamingContext_ptr context)
    throw (SystemException, NotEmpty)
  {
    context->destroy();
  }
  
  /*!
   * @if jp
   * @brief NamingContext ��Ƶ�Ū�˲��ä��󥢥��ƥ��ֲ�����
   * @else
   * @brief Destroy the naming context recursively
   * @endif
   */
  void CorbaNaming::destroyRecursive(CosNaming::NamingContext_ptr context)
    throw (SystemException, NotEmpty, NotFound, CannotProceed, InvalidName)
  {
    CosNaming::BindingList_var     bl;
    CosNaming::BindingIterator_var bi;
    CORBA::Boolean cont(true);
    
#ifndef ORB_IS_RTORB
    context->list(m_blLength, bl.out(), bi.out());
#else // ORB_IS_RTORB
    //    context->list(m_blLength, bl, bi);
    context->list(m_blLength, (CosNaming::BindingList_out)bl,
                  (CosNaming::BindingIterator_ptr)bi);
#endif // ORB_IS_RTORB
    
    while (cont)
      {
	CORBA::ULong len(bl->length());
	
	for (CORBA::ULong i = 0; i < len; ++i)
	  {
	    if (bl[i].binding_type == CosNaming::ncontext)
	      {	// If Object is context, destroy recursive.
		CosNaming::NamingContext_var next_context;
		next_context = CosNaming::NamingContext::
		  _narrow(context->resolve(bl[i].binding_name));
		
		// Recursive function call
		destroyRecursive(next_context); // +++ Recursive call +++
		context->unbind(bl[i].binding_name);
		next_context->destroy();
	      }
	    else if (bl[i].binding_type == CosNaming::nobject)
	      {	// If Object is object, unbind it.
		context->unbind(bl[i].binding_name);
	      }
	    else assert(0); // never comes here
	  }
	
	// no more binding -> do-while loop will be finished
	if (CORBA::is_nil(bi)) cont = false;
	else bi->next_n(m_blLength, bl);
      }
    
    if (!CORBA::is_nil(bi)) bi->destroy();
    return;
  }
  
  /*!
   * @if jp
   * @brief ���٤Ƥ� Binding ��������
   * @else
   * @brief Destroy all bindings
   * @endif
   */
  void CorbaNaming::clearAll()
  {
    destroyRecursive(m_rootContext);
  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿 NamingContext �� Binding ���������
   * @else
   * @brief Get Binding on the given NamingContext
   * @endif
   */
  void CorbaNaming::list(CosNaming::NamingContext_ptr name_cxt,
			 CORBA::ULong how_many,
			 CosNaming::BindingList_var& bl,
			 CosNaming::BindingIterator_var& bi)
  {
#ifndef ORB_IS_RTORB
    name_cxt->list(how_many, bl.out(), bi.out());
#else // ORB_IS_RTORB
    name_cxt->list(how_many, (CosNaming::BindingList_out)bl,
                   (CosNaming::BindingIterator_ptr)bi);
#endif // ORB_IS_RTORB

  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿 NameComponent ��ʸ����ɽ�����֤�
   * @else
   * @brief Get string representation of given NameComponent
   * @endif
   */
  char* CorbaNaming::toString(const CosNaming::Name& name)
    throw (SystemException, InvalidName)
  {
    if (name.length() == 0)
      throw InvalidName();
    
    CORBA::ULong slen = 0;
    slen = getNameLength(name);
    
    CORBA::String_var string_name = CORBA::string_alloc(slen);
    nameToString(name, (char*)string_name, slen);
    
    return string_name._retn();
  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿ʸ����ɽ���� NameComponent ��ʬ�򤹤�
   * @else
   * @brief Resolve given string representation to NameComponent
   * @endif
   */
  CosNaming::Name CorbaNaming::toName(const char* sname)
    throw (SystemException, InvalidName)
  {
    if (!sname)         throw InvalidName();
    if (*sname == '\0') throw InvalidName();
    
    std::string string_name(sname);
    std::vector<std::string> name_comps;
    
    // String name should include 1 or more names
    CORBA::ULong nc_length = 0;
    nc_length = split(string_name, std::string("/"), name_comps);
    if (!(nc_length > 0)) throw InvalidName();
    
    // Name components are allocated
    CosNaming::Name_var    name = new CosNaming::Name();
    name->length(nc_length);
    
    // Insert id and kind to name components
    for (CORBA::ULong i = 0; i < nc_length; ++i)
      {
	std::string::size_type pos;
	pos = name_comps[i].find_last_of(".");
	if (pos != name_comps[i].npos)
	  {
	    name[i].id   = 
	      CORBA::string_dup(name_comps[i].substr(0, pos).c_str());
	    name[i].kind = 
	      CORBA::string_dup(name_comps[i].substr(pos + 1).c_str());
	  }
	else
	  {
	    name[i].id   = CORBA::string_dup(name_comps[i].c_str());
#ifndef ORB_IS_RTORB
	    name[i].kind = "";
#else // ORB_IS_RTORB
	    name[i].kind = (char*)"";
#endif // ORB_IS_RTORB
	  }
      }
    return name;
  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿 addre �� string_name ���� URLɽ�����������
   * @else
   * @brief Get URL representation from given addr and string_name
   * @endif
   */
  char* CorbaNaming::toUrl(char* addr, char* string_name)
    throw (SystemException, InvalidAddress, InvalidName)
  {
    return m_rootContext->to_url(addr, string_name);
  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿ʸ����ɽ���� resolve �����֥������Ȥ��֤�
   * @else
   * @brief Resolve from name of string representation and get object
   * @endif
   */
  CORBA::Object_ptr CorbaNaming::resolveStr(const char* string_name)
    throw (SystemException, NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    return resolve(string_name);
  }
  
  //======================================================================
  // Util functions
  //======================================================================
  /*!
   * @if jp
   * @brief ���֥������Ȥ�̾����Х���ɤޤ��ϲ�褹��
   * @else
   * @brief Bind or resolve the given name component
   * @endif
   */
  CORBA::Object_ptr
  CorbaNaming::bindOrResolve(CosNaming::NamingContext_ptr context,
			     const CosNaming::Name& name,
			     CORBA::Object_ptr obj)
  {
    try
      {
	context->bind(name, obj);
	return obj;
      }
    catch (AlreadyBound& e)
      {
	(void)(e);
	return context->resolve(name);
      }
    return CORBA::Object::_nil();
  }
  
  /*!
   * @if jp
   * @brief ̾����Х���ɤޤ��ϲ�褹��
   * @else
   * @brief Bind or resolve the given name component
   * @endif
   */
  CosNaming::NamingContext_ptr
  CorbaNaming::bindOrResolveContext(CosNaming::NamingContext_ptr context,
				    const CosNaming::Name& name,
				    CosNaming::NamingContext_ptr new_context)
  {
    return CosNaming::NamingContext
      ::_narrow(bindOrResolve(context, name, new_context));
  }
  
  /*!
   * @if jp
   * @brief ̾����Х���ɤޤ��ϲ�褹��
   * @else
   * @brief Bind or resolve the given name component
   * @endif
   */
  CosNaming::NamingContext_ptr
  CorbaNaming::bindOrResolveContext(CosNaming::NamingContext_ptr context,
				    const CosNaming::Name& name)
  {
    return bindOrResolveContext(context, name, newContext());
  }
  
  /*!
   * @if jp
   * @brief �͡��ॵ���Ф�̾�����������
   * @else
   * @brief Get the name of naming server
   * @endif
   */
  const char* CorbaNaming::getNameServer()
  {
    return m_nameServer.c_str();
  }
  
  /*!
   * @if jp
   * @brief �롼�ȥ���ƥ����Ȥ��������
   * @else
   * @brief Get the root context
   * @endif
   */
  CosNaming::NamingContext_ptr CorbaNaming::getRootContext()
  {
    return m_rootContext;
  }
  
  /*!
   * @if jp
   * @brief ���֥������Ȥ��͡��ߥ󥰥���ƥ����Ȥ�Ƚ�̤���
   * @else
   * @brief Determine whether the object is NamingContext
   * @endif
   */
  bool CorbaNaming::isNamingContext(CORBA::Object_ptr obj)
  {
    CosNaming::NamingContext_var nc;
    nc = CosNaming::NamingContext::_narrow(obj);
    return CORBA::is_nil(nc) ? false : true;
  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿̾�����͡��ߥ󥰥���ƥ����Ȥ��ɤ���
   * @else
   * @brief Determine whether the given name component is NamingContext
   * @endif
   */
  bool CorbaNaming::isNamingContext(const CosNaming::Name& name)
  {
    return isNamingContext(resolve(name));
  }
  
  /*!
   * @if jp
   * @brief Ϳ����줿̾�����͡��ߥ󥰥���ƥ����Ȥ��ɤ���
   * @else
   * @brief Determine whether the given string name is NamingContext
   * @endif
   */
  bool CorbaNaming::isNamingContext(const char* string_name)
  {
    return isNamingContext(resolve(string_name));
  }
  
  /*!
   * @if jp
   * @brief �͡��ॳ��ݡ��ͥ�Ȥ���ʬ���֤�
   * @else
   * @brief Get subset of given name component
   * @endif
   */
  CosNaming::Name CorbaNaming::subName(const CosNaming::Name& name,
				       CORBA::Long begin,
				       CORBA::Long end)
  {
    if (end < 0) end = name.length() - 1;
    
    CosNaming::Name sub_name;
    CORBA::ULong sub_len(end - (begin - 1));
    if (sub_len > 0)
      {
	sub_name.length(sub_len);
      }
    else
      {
	sub_name.length(0);
	return sub_name;
      }
    
    for (CORBA::ULong i = 0; i < sub_len; ++i)
      {
	sub_name[i] = name[begin + i];
      }
    return sub_name;
  }
  
  //------------------------------------------------------------
  // Protected member functions
  //------------------------------------------------------------
  /*!
   * @if jp
   * @brief �͡��ॳ��ݡ��ͥ�Ȥ�ʸ����ɽ�����������
   * @else
   * @brief Get string representation of name component
   * @endif
   */
  void CorbaNaming::nameToString(const CosNaming::Name& name,
				 char* string_name,
				 CORBA::ULong slen)
  {
    char* s = string_name;
    for (CORBA::ULong i = 0; i < name.length(); ++i)
      {
	// Copy id to string_name
	for (const char* id = name[i].id; *id != '\0'; ++id)
	  {
	    if (*id == '/' || *id == '.' || *id == '\\') *s++ = '\\';
	    *s++ = *id;
	  }
	// '.' if there is a kind, or no id
	if (((const char*)(name[i].id  ))[0] == '\0' || 
	    ((const char*)(name[i].kind))[0] != '\0')
	  *s++ = '.';
	// Copy kind to string_name
	for (const char* kind = name[i].kind; *kind != '\0'; ++kind)
	  {
	    if (*kind == '/' || *kind == '.' || *kind == '\\')
	      *s++ = '\\';
	    *s++ = *kind;
	  }
	// The end of string_name will be overwritten by '\0'
	*s++ = '/';
      }
    string_name[slen-1] = '\0';
  }
  
  /*!
   * @if jp
   * @brief �͡��ॳ��ݡ��ͥ�Ȥ�ʸ����ɽ������ʸ��Ĺ���������
   * @else
   * @brief Get string length of the name component's string representation
   * @endif
   */
  CORBA::ULong CorbaNaming::getNameLength(const CosNaming::Name& name)
  {
    CORBA::ULong slen = 0;
    
    for (CORBA::ULong i = 0; i < name.length(); ++i)
      {
	// Count string length of id(s)
	for (const char* id = name[i].id; *id; ++id)
	  {
	    // Escape character '/', '.', '\' will convert to "\/", "\.", "\\".
	    if (*id == '/' || *id == '.' || *id == '\\') slen++;
	    slen++;
	  }
	// If kind exists, space for '.' is counted
	if (((const char*)(name[i].id  ))[0] == '\0' || 
	    ((const char*)(name[i].kind))[0] != '\0')
	  {
	    slen++;
	  }
	// Count string length of kind(s)
	for (const char* kind = name[i].kind; *kind; kind++)
	  {
	    if (*kind == '/' || *kind == '.' || *kind == '\\') slen++;
	    slen++;
	  }
	// Space for '/' or '\0'
	slen++;
      }
    return slen;
  }
  
  /*!
   * @if jp
   * @brief ʸ�����ʬ��
   * @else
   * @brief Split of string
   * @endif
   */
  unsigned int CorbaNaming::split(const std::string& input,
				  const std::string& delimiter,
				  std::vector<std::string>& results)
  {
    typedef std::string::size_type size;
    size delim_size = delimiter.size();
    size found_pos(0), begin_pos(0), pre_pos(0), substr_size(0);
    
    if (input.substr(0, delim_size) == delimiter)
      begin_pos = pre_pos = delim_size;
    
    while (1)
      {
      REFIND:
	found_pos = input.find(delimiter, begin_pos);
	if (found_pos == std::string::npos) 
	  {
	    results.push_back(input.substr(pre_pos));
	    break;
	  }
	if ('\\' == input.at(found_pos - 1))
	  {
	    begin_pos = found_pos + delim_size;
	    goto REFIND;
	  }
	
	substr_size = found_pos - pre_pos;
	
	if (substr_size > 0)
	  {
	    results.push_back(input.substr(pre_pos, substr_size));
	  }
	begin_pos = found_pos + delim_size;
	pre_pos   = found_pos + delim_size;
      }
    return results.size();
  }
}; // namespace RTC
