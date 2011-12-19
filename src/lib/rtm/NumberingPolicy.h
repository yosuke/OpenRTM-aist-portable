// -*- C++ -*-
/*!
 * @file NumberingPolicy.h
 * @brief Object numbering policy class
 * @date $Date: 2007-12-31 03:08:04 $
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
 * $Id: NumberingPolicy.h 1569 2009-11-12 14:36:47Z n-ando $
 *
 */

#ifndef RTC_NUMBERINGPOLICY_H
#define RTC_NUMBERINGPOLICY_H

#include <string>
#include <vector>

/*!
 * @if jp
 *
 * @class NumberingPolicy
 * @brief ���֥��������������͡��ߥ󥰡��ݥꥷ��(̿̾��§)��������ݥ��饹
 *
 * ���֥������Ȥ���������ݤΥ͡��ߥ󥰡��ݥꥷ��(̿̾��§)��������뤿���
 * ��ݥ��󥿡��ե��������饹��
 * ��ݥ��饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
 * - onCreate() : ���֥���������������̾�κ���
 * - onDelete() : ���֥������Ⱥ������̾�β���
 *
 * @since 0.4.0
 *
 * @else
 * @class NumberingPolicy
 * @brief Abstruct class for naming policy management when creating objects
 *
 * This is the abstract interface class to manage the naming policy when
 * creating objects.
 * Concrete classes must implement the following pure virtual functions.
 * - onCreate() : Create the name when creating objects.
 * - onDelete() : Delete the name when deleting objects.
 *
 * @since 0.4.0
 *
 * @endif
 */
class NumberingPolicy
{
public:
  /*!
   * @if jp
   * @brief ���֥�������̤ȯ���㳰�����ѹ�¤��
   * @else
   * @brief The structures for exception handling when object was not
   *        found.
   * @endif
   */
  struct ObjectNotFound {};
  
  /*!
   * @if jp
   *
   * @brief ���ۥǥ��ȥ饯��
   * 
   * @else
   *
   * @brief Virtual destractor
   *
   * @endif
   */
  virtual ~NumberingPolicy(void){};
  
  /*!
   * @if jp
   *
   * @brief ���֥���������������̾�κ���
   *
   * ���֥���������������̾�Τ��������뤿��ν�貾�۴ؿ�
   * 
   * @param obj ̾�������оݥ��֥�������
   *
   * @return �����������֥�������̾��
   *
   * @else
   *
   * @brief Create the name when creating objects
   *
   * Pure virtual function to create the name when creating objects.
   * 
   * @param obj The target object for the creation
   *
   * @return Name of the created object
   *
   * @endif
   */
  virtual std::string onCreate(void* obj) = 0;
  
  /*!
   * @if jp
   *
   * @brief ���֥������Ⱥ������̾�β���
   *
   * ���֥������Ⱥ������̾�Τ�������뤿��ν�貾�۴ؿ�
   * 
   * @param obj ̾�β����оݥ��֥�������
   *
   * @else
   *
   * @brief Delete the name when deleting objects
   *
   * Pure virtual function to delete the name when deleting object.
   * 
   * @param obj The target object of the delete
   *
   * @endif
   */
  virtual void onDelete(void* obj) = 0;
};

/*!
 * @if jp
 *
 * @class DefaultNumberingPolicy
 * @brief ���֥��������������͡��ߥ󥰡��ݥꥷ��(̿̾��§)�����ѥ��饹
 *
 * ���֥������Ȥ���������ݤΥ͡��ߥ󥰡��ݥꥷ��(̿̾��§)��������뤿���
 * ���饹��
 *
 * @since 0.4.0
 *
 * @else
 *
 * @class DefaultNumberingPolicy
 * @brief Class for naming policy management when creating objects
 *
 * This is a class to manage the naming policy when creating objects.
 *
 * @since 0.4.0
 *
 * @endif
 */
class DefaultNumberingPolicy
  : public NumberingPolicy 
{
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
  DefaultNumberingPolicy() : m_num(0) {};
  
  /*!
   * @if jp
   *
   * @brief �ǥ��ȥ饯��
   * 
   * @else
   *
   * @brief Destractor
   *
   * @endif
   */
  virtual ~DefaultNumberingPolicy(void){};
  
  /*!
   * @if jp
   *
   * @brief ���֥���������������̾�κ���
   *
   * ���֥���������������̾�Τ��������롣
   * �����Ѥߥ��󥹥��󥹤ο��˱�����̾�Τ��������롣
   * 
   * @param obj ̾�������оݥ��֥�������
   *
   * @return �����������֥�������̾��
   *
   * @else
   *
   * @brief Create the name when creating object
   *
   * Create the name when creating object.
   * Create the name corresponding to the number of generated instances.
   * 
   * @param obj The target object for the name creation
   *
   * @return Names of the created object
   *
   * @endif
   */
  virtual std::string onCreate(void* obj);
  
  /*!
   * @if jp
   *
   * @brief ���֥������Ⱥ������̾�β���
   *
   * ���֥������Ⱥ������̾�Τ�������롣
   * ���֥������Ⱥ�����������Ѥߥ��󥹥��󥹿��򸺻����롣
   * 
   * @param obj ̾�β����оݥ��֥�������
   *
   * @else
   *
   * @brief Delete the name when deleting object
   *
   * Delete the name when deleting object.
   * Substract the generated number of instances when deleting the object.
   * 
   * @param obj The target object for the name delete
   *
   * @endif
   */
  virtual void onDelete(void* obj);
  
protected:
  /*!
   * @if jp
   *
   * @brief ���֥������Ȥθ���
   *
   * ���֥������ȥꥹ�Ȥ�����ꤵ�줿���֥������Ȥ򸡺�����
   * �������륪�֥������Ȥ���Ǽ����Ƥ�����ˤϥ���ǥå������֤���
   * 
   * @param obj �����оݥ��֥�������
   *
   * @return ���֥������ȳ�Ǽ����ǥå���
   *
   * @else
   *
   * @brief Find the object
   *
   * Find the specified object in the object list and return its index
   * when it is stored.
   * 
   * @param obj The target object for the find
   *
   * @return Object index for storage
   *
   * @endif
   */
  long int find(void* obj);
  
private:
  int m_num;
  std::vector<void*> m_objects;
};
#endif // RTC_NUMBERINGPOLICY_H
