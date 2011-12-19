// -*- C++ -*-
/*!
 * @file ECFactory.h
 * @brief ExecutionContext Factory class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ECFactory.h 1569 2009-11-12 14:36:47Z n-ando $
 *
 */

#ifndef RTC_ECFACTORY_H
#define RTC_ECFACTORY_H

#include <rtm/ExecutionContextBase.h>
#include <string>

namespace RTC 
{
  
  typedef ExecutionContextBase* (*ECNewFunc)();
  typedef void (*ECDeleteFunc)(ExecutionContextBase* ec);
  
  /*!
   * @if jp
   *
   * @brief ExecutionContext�����ѥƥ�ץ졼�ȴؿ�
   * 
   * ExecutionContext�Υ��󥹥��󥹤��������뤿��Υƥ�ץ졼�ȴؿ���
   *
   * @return ��������ExecutionContext���󥹥���
   * 
   * @else
   *
   * @brief Template function to create ExecutionContext
   * 
   * Template function to create ExecutionContext's instances.
   *
   * @return Created ExecutionContext's instances
   *
   * @endif
   */
  template <class _New>
  ExecutionContextBase* ECCreate()
  {
    return new _New();
  }
  
  /*!
   * @if jp
   *
   * @brief ExecutionContext�˴��ѥƥ�ץ졼�ȴؿ�
   * 
   * ExecutionContext�Υ��󥹥��󥹤��˴����뤿��Υƥ�ץ졼�ȴؿ���
   *
   * @param ec �˴��о�ExecutionContext�Υ��󥹥���
   *
   * @else
   *
   * @brief Template function to destroy ExecutionContext
   * 
   * Template function to destroy ExecutionContext's instances.
   *
   * @param ec The target ExecutionContext's instances for destruction
   *
   * @endif
   */
  template <class _Delete>
  void ECDelete(ExecutionContextBase* ec)
  {
    delete ec;
  }
  
  /*!
   * @if jp
   * @class ECFactoryBase
   * @brief ECFactoryBase ��ݥ��饹
   * 
   * ExecutionContext������Factory����ݥ��饹��
   * ��ExecutionContext���������뤿��ζ��Factory���饹�ϡ�
   * �ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
   *
   * public���󥿡��ե������Ȥ��ưʲ��Τ�Τ��󶡤��롣
   * - name()   : �����о�ExecutionContext̾�Τμ���
   * - create() : ExecutionContext���󥹥��󥹤�����
   * - destroy(): ExecutionContext���󥹥��󥹤��˴�
   *
   * @since 0.4.0
   *
   * @else
   * @class ECFactoryBase
   * @brief ECFactoryBase abstract class
   * 
   * This is the abstruct Factory classes for ExecutionContext creation.
   * Concrete classes for each ExecutionContext creation must implement 
   * the following pure virtual functions.
   *
   * This class provides the following public interfaces.
   * - name()   : Get names of the target ExecutionContext for creation
   * - create() : Create ExecutionContext's instances
   * - destroy(): Destroy ExecutionContext's instances
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ECFactoryBase
  {
  public:
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
     * Virtual destructor
     *
     * @endif
     */
    virtual ~ECFactoryBase(void){};
    
    /*!
     * @if jp
     *
     * @brief �����о�ExecutionContext̾�μ����ѽ�貾�۴ؿ�
     * 
     * �����о�ExecutionContext��̾�Τ�������뤿��ν�貾�۴ؿ���
     *
     * @return �����о�ExecutionContext̾��
     * 
     * @else
     *
     * @brief Pure virtual function to get names of creation target 
     *        ExecutionContext
     * 
     * Pure virtual function to get names of the target ExecutionContext
     * for creation.
     *
     * @return Names of the target ExecutionContext for creation
     *
     * @endif
     */
    virtual const char* name() = 0;
    
    /*!
     * @if jp
     *
     * @brief ExecutionContext�����ѽ�貾�۴ؿ�
     * 
     * ExecutionContext�Υ��󥹥��󥹤��������뤿��ν�貾�۴ؿ���
     *
     * @return ��������ExecutionContext���󥹥���
     * 
     * @else
     *
     * @brief Pure virtual function to create ExecutionContext.
     * 
     * Pure virtual function to create ExecutionContext's instances.
     *
     * @return Created ExecutionContext's instances
     *
     * @endif
     */
    virtual ExecutionContextBase* create() = 0;
    
    /*!
     * @if jp
     *
     * @brief ExecutionContext�˴��ѽ�貾�۴ؿ�
     * 
     * ExecutionContext�Υ��󥹥��󥹤��˴����뤿��ν�貾�۴ؿ���
     *
     * @param comp �˴��оݤ�ExecutionContext���󥹥���
     * 
     * @else
     *
     * @brief Pure virtual function to destroy ExecutionContext.
     * 
     * Pure virtual function to destroy ExecutionContext's instances.
     *
     * @param comp The target ExecutionContext's instances for destruction
     *
     * @endif
     */
    virtual void destroy(ExecutionContextBase* comp) = 0;
  protected:
  };
  
  /*!
   * @if jp
   * @class ECFactoryCXX
   * @brief ECFactoryCXX ���饹
   * 
   * C++������ExecutionContext���󥹥��󥹤���������Factory���饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class ECFactoryCXX
   * @brief ECFactoryCXX class
   * 
   * Factory class to create the ExecutionContext's instances for C++.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ECFactoryCXX
    : public ECFactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param name �����о�ExecutionContext̾��
     * @param new_func ExecutionContext�����Ѵؿ�
     * @param delete_func ExecutionContext�˴��Ѵؿ�
     * 
     * @else
     *
     * @brief Constructor
     * 
     * Constructor
     *
     * @param name Name of the target ExecutionContext for creation
     * @param new_func Function to create ExecutionContext
     * @param delete_func Function to destroy ExecutionContext
     *
     * @endif
     */
    ECFactoryCXX(const char* name,
		 ECNewFunc new_func,
		 ECDeleteFunc delete_func);
    
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
     * Virtual destructor.
     *
     * @endif
     */
    ~ECFactoryCXX(void);
    
    /*!
     * @if jp
     *
     * @brief �����о�ExecutionContext̾�Τ����
     * 
     * �����оݤ�ExecutionContext̾�Τ�������롣
     *
     * @return �����о�ExecutionContext̾��
     * 
     * @else
     *
     * @brief Get names of the target ExecutionContext for creation
     * 
     * Get names of the target ExecutionContext for creation.
     *
     * @return Names of target ExecutionContext for creation
     *
     * @endif
     */
    virtual const char* name();
    
    /*!
     * @if jp
     *
     * @brief �����о�ExecutionContext���󥹥��󥹤�����
     * 
     * �����оݤ�ExecutionContext���饹�Υ��󥹥��󥹤��������롣
     *
     * @return ��������ExecutionContext���󥹥���
     * 
     * @else
     *
     * @brief Create the target ExecutionContext's instances
     * 
     * Create the target ExecutionContext class's instances.
     *
     * @return Created ExecutionContext's instances
     *
     * @endif
     */
    virtual ExecutionContextBase* create();
    
    /*!
     * @if jp
     *
     * @brief �о�ExecutionContext���󥹥��󥹤��˴�
     * 
     * �о�ExecutionContext���饹�Υ��󥹥��󥹤��˴����롣
     *
     * @param comp �˴��о�ExecutionContext���󥹥���
     * 
     * @else
     *
     * @brief Destroy the target ExecutionContext's instances
     * 
     * Destroy the target ExecutionContext's instances.
     *
     * @param comp The target ExecutionContext's instances to destroy
     *
     * @endif
     */
    virtual void destroy(ExecutionContextBase* comp);
    
  protected:
    /*!
     * @if jp
     * @brief  �����о�ExecutionContext̾��
     * @else
     * @brief  Names of the target ExecutionContext for creation
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief  �о�ExecutionContext�����Ѵؿ�
     * @else
     * @brief  Function to create the target ExecutionContext
     * @endif
     */
    ECNewFunc m_New;
    
    /*!
     * @if jp
     * @brief  �о�ExecutionContext�˴��Ѵؿ�
     * @else
     * @brief  Function to destroy the target ExecutionContext
     * @endif
     */
    ECDeleteFunc m_Delete;
  };
};
#endif // RTC_ECFACTORY_H
