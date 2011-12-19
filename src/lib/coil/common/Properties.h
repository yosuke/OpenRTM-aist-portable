// -*- C++ -*-
/*!
 * @file Properties.h
 * @brief Property list class (derived from Java Properties)
 * @date $Date: 2007-12-31 03:08:06 $
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
 * $Id: Properties.h 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#ifndef COIL_PROPERTIES_H
#define COIL_PROPERTIES_H


#include <string>
#include <vector>
#include <map>
#include <climits>


/*!
 * @if jp
 * @namespace coil 
 *
 * @brief Common Object Interface Layer
 *
 *
 * @else
 * @namespace coil
 *
 * @brief Common Object Interface Layer
 *
 *
 * @endif
 */
namespace coil
{
  /*!
   * @if jp
   *
   * @class Properties
   * @brief �ץ�ѥƥ����åȤ�ɽ�����륯�饹
   *
   * Properties ���饹�ϡ����ѤΥץ�ѥƥ����åȤ�ɽ���� Properties �򥹥ȥ꡼��
   * ���ݴɤ����ꡢ���ȥ꡼�फ����ɤ����ꤹ�뤳�Ȥ��Ǥ��롣
   * �ץ�ѥƥ��ꥹ�Ȥγƥ���������Ӥ�����б������ͤ�ʸ����ȤʤäƤ��롣
   *
   * �ץ�ѥƥ��ꥹ�Ȥˤϡ����Ρ֥ǥե�����͡פȤ����̤Υץ�ѥƥ��ꥹ�Ȥ����
   * ���Ȥ��Ǥ��롣���Υץ�ѥƥ��ꥹ�Ȥǥץ�ѥƥ����������Ĥ���ʤ��ȡ�����
   * 2���ܤΥץ�ѥƥ��ꥹ�Ȥ���������롣 
   *
   * �ץ�ѥƥ��μ����ˤ� getProperty() ���ץ�ѥƥ��Υ��åȤˤ� setProperty() ��
   * ���ä��᥽�åɤ���Ѥ��뤳�Ȥ��侩����롣
   *
   * �ץ�ѥƥ��򥹥ȥ꡼�����¸����Ȥ����ޤ��ϥ��ȥ꡼�फ����ɤ���Ȥ�
   * �ˡ�ISO 8859-1 ʸ�����󥳡��ǥ��󥰤����Ѥ���롣���Υ��󥳡��ǥ��󥰤�
   * ľ��ɽ���Ǥ��ʤ�ʸ���ϡ��������Ȥ��Ǥ��ʤ���
   *
   * ���Υ��饹�ϡ�Java �� Properties ���饹 (java.util.Properties) �Ȥۤ�Ʊ�ͤ�
   * �᥽�åɤ���ġ��ޤ��������Ϥ����ե������ Java �� Properties ���饹��
   * ���Ϥ����Τȸߴ��������뤬��Unicode ��ޤ��Τϰ������Ȥ��Ǥ��ʤ���
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class Properties
   * @brief Class represents a set of properties
   *
   * The Properties class represents a persistent set of properties. The
   * Properties can be saved to a stream or loaded from a stream. Each key and
   * its corresponding value in the property list is a string. 
   *
   * A property list can contain another property list as its "defaults". This
   * second property list is searched if the property key is not found in the
   * original property list. 
   *
   * It is recommended to use these method; setProperty() to get properties,
   * setProperty() to set properties. 
   *
   * When propertis are stored in a stream or when they are loaded from
   * the stream, the ISO 8859-1 character encoding is used.
   * Characters that cannot be directly represented in this encoding can be used.
   *
   * This class has almost same methods of Java's Properties class
   * (java.util.Properties). Also, input and output files are compatible with 
   * outputs of Java's Properties class, but Unicode encoded property file
   * is not be supported.
   *
   * @endif
   */
  class Properties
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��(root�Ρ��ɤΤߺ���)
     *
     * key �� value �Τߤ�Ϳ���� Property �Υ롼�ȥΡ��ɤ�������롣
     * �ͤ����ƥǥե�����ͤȤ������ꤵ��롣
     *
     * @param key �ץ�ѥƥ��Υ���(�ǥե������:"")
     * @param value �ץ�ѥƥ�����(�ǥե������:"")
     * 
     * @else
     *
     * @brief Constructor(Create only root node)
     *
     * Create a root node of Property with root's key and value.
     * All values are set as default value.
     *
     * @param key Properties's keys(The default values:"")
     * @param value Properties's values(The default values:"")
     * 
     * @endif
     */
    Properties(const char* key = "", const char* value = "");
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��(map�ǥǥե�����ͤ�Ϳ����)
     *
     * std::string �� std::map ��ǥե�����ͤˤ�� Properties ��������롣
     * �ͤ����ƥǥե�����ͤȤ������ꤵ��롣
     * 
     * @param defaults �ǥե�����ͤȤ��ƻ��ꤵ���map
     * 
     * @else
     *
     * @brief Constructor(Give the default value with map)
     *
     * Create Properties with default value of std::string map.
     * All values are set as default value.
     * 
     * @param defaults map that is spcified as the default value
     * 
     * @endif
     */
    Properties(std::map<std::string, std::string>& defaults);
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��(char*[] �ǥǥե�����ͤ�Ϳ����)
     *
     * ���ꤵ�줿�ǥե�����ͤ���Ķ��Υץ�ѥƥ��ꥹ�Ȥ�������롣
     * �ͤ����ƥǥե�����ͤȤ������ꤵ��롣
     * �ǥե�����ͤ� char* ������ˤ��Ϳ����졢key �� value ���Фˤʤä�
     * ���ꡢ�ꥹ�Ȥν�ü������ο���ɽ������ num ������ʸ���� key ��Ϳ������
     * �ʤ���Фʤ�ʤ���
     * �ʲ�����򼨤���
     *
     * <pre>
     * const char* defaults = {
     *     "key1", "value1",
     *     "key2", "value2",
     *     "key3", "value3",
     *     "key4", "value4",
     *     "key5", "value5",
     *     "" };
     * Properties p(defaults);
     * // �⤷����
     * Properties p(defaults, 10);
     * </pre>
     * 
     * @param defaults �ǥե�����ͤ���ꤹ������
     * @param num �ǥե�����ͤ����ꤹ�����ǿ�(�ǥե������:LONG_MAX)
     * 
     * @else
     *
     * @brief Constructor(Give the default value with char*[])
     *
     * Creates an empty property list with the specified defaults.
     * All values are set as the default values.
     * The default values are given by array of char*, which should be pairs
     * of "key" and "value". The end of list is specified by argument "num"
     * which specifies number of array, or null character of key.
     * The following is an example.
     *
     * <pre>
     * const char* defaults = {
     *     "key1", "value1",
     *     "key2", "value2",
     *     "key3", "value3",
     *     "key4", "value4",
     *     "key5", "value5",
     *     "" };
     * Properties p(defaults);
     * // or
     * Properties p(defaults, 10);
     * </pre>
     * 
     * @param defaults Array that specifies the default values
     * @param num Number of elements that specifies the default value
     *            (The default value:LONG_MAX)
     * 
     * @endif
     */
    Properties(const char* defaults[], long num = LONG_MAX);
    
    /*!
     * @if jp
     * @brief ���ԡ����󥹥ȥ饯��
     *
     * ������Ϳ����줿 Properties �Υ������ͤ���ӥǥե�����ͤ�
     * ���Ƥ��Τޤޥ��ԡ�����롣
     *
     * @else
     *
     * @brief Copy Constructor
     *
     * All of given Properties's keys, values and default values 
     * are copied to new Properties.
     * 
     * @endif
     */
    Properties(const Properties& prop);
    
    /*!
     * @if jp
     * @brief �����黻��
     *
     * �����ͤ� Properties �Υ������ͤ���ӥǥե�����ͤ����ƺ�����졢
     * �����ͤ� Properties �Υ������ͤ���ӥǥե�����ͤ����Ƥ��Τޤ�
     * ���ԡ�����롣
     *
     * @else
     * @brief Assignment operator
     *
     * All Properties's keys, values and default values of left side
     * are deleted, all Properties's keys, values and default values of
     * right side are copied to new Properties.
     *
     * @endif
     */
    Properties& operator=(const Properties& prop);
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief Destructor
     *
     * @endif
     */
    virtual ~Properties(void);
    
    //============================================================
    // public functions
    //============================================================
    
    /*!
     * @if jp
     * @brief Name �μ���
     *
     * �ץ�ѥƥ���̾�Τ�������롣
     *
     * @return �ץ�ѥƥ�̾
     *
     * @else
     * @brief Get Names
     *
     * Get Properties's names.
     *
     * @return Properties's names
     *
     * @endif
     */
    inline const char* getName(void) const          {return name.c_str();}
    
    /*!
     * @if jp
     * @brief �ͤμ���
     *
     * �ץ�ѥƥ����ͤ�������롣
     *
     * @return �ץ�ѥƥ���
     *
     * @else
     * @brief Get values
     *
     * Get Properties's values.
     *
     * @return Properties's values
     *
     * @endif
     */
    inline const char* getValue(void) const         {return value.c_str();}
    
    /*!
     * @if jp
     * @brief �ǥե�����ͤμ���
     *
     * �ץ�ѥƥ��Υǥե�����ͤ�������롣
     *
     * @return �ץ�ѥƥ��ǥե������
     *
     * @else
     * @brief Get default values
     *
     * Get Properties's default values.
     *
     * @return Properties's default values
     *
     * @endif
     */
    inline const char* getDefaultValue(void) const {return default_value.c_str();}
    
    /*!
     * @if jp
     * @brief �����Ǥμ���
     *
     * �ץ�ѥƥ��λ����Ǥ�������롣
     *
     * @return ������
     *
     * @else
     * @brief Get elements of leaf
     *
     * Get Properties's elements of leaf.
     *
     * @return Elements of leaf
     *
     * @endif
     */
    inline const std::vector<Properties*>& getLeaf(void) const {return leaf;}
    
    /*!
     * @if jp
     * @brief �롼�����Ǥμ���
     *
     * �ץ�ѥƥ��Υ롼�����Ǥ�������롣
     *
     * @return �롼������
     *
     * @else
     * @brief Get root element
     *
     * Get Properties's root element.
     *
     * @return Root element
     *
     * @endif
     */
    inline const Properties* getRoot(void) const    {return root;}
    
    /*!
     * @if jp
     *
     * @brief ���ꤵ�줿��������ĥץ�ѥƥ��򡢥ץ�ѥƥ��ꥹ�Ȥ���õ��
     *
     * ���ꤵ�줿��������ĥץ�ѥƥ��򡢥ץ�ѥƥ��ꥹ�Ȥ���õ����
     * ���Υ������ץ�ѥƥ��ꥹ�Ȥˤʤ��ȡ��ǥե���ȤΥץ�ѥƥ��ꥹ�ȡ�
     * ����ˤ��Υǥե�����ͤ������֤�Ĵ�٤��롣
     * ���Υץ�ѥƥ������Ĥ���ʤ����ϡ�null ���֤���롣 
     *
     * @param key �ץ�ѥƥ�����
     *
     * @return ���ꤵ�줿�����ͤ���Ĥ��Υץ�ѥƥ��ꥹ�Ȥ���
     *
     * @else
     *
     * @brief Search for the property with the specified key in this property
     *
     * Search for the property with the specified key in this property list.
     * If the key is not found in this property list, the default property list,
     * and its defaults, recursively, are then checked. The method returns null
     * if the property is not found. 
     *
     * @param key The property key.
     *
     * @return The value in this property list with the specified key value.
     *
     * @endif
     */
    const std::string& getProperty(const std::string& key) const;
    
    /*!
     * @if jp
     *
     * @brief ���ꤵ�줿��������ĥץ�ѥƥ��򡢥ץ�ѥƥ��ꥹ�Ȥ���õ��
     *
     * ���ꤵ�줿��������ĥץ�ѥƥ��򡢥ץ�ѥƥ��ꥹ�Ȥ���õ����
     * ���Υ������ץ�ѥƥ��ꥹ�Ȥˤʤ����ϡ��ǥե�����ͤΰ������֤���롣 
     *
     * @param key �ץ�ѥƥ�����
     * @param def �ǥե������
     *
     * @return ���ꤵ�줿�����ͤ���Ĥ��Υץ�ѥƥ��ꥹ�Ȥ���
     *
     * @else
     *
     * @brief Search for the property with the specified key in property list
     *
     * Search for the property with the specified key in this property list.
     * The method returns the default value argument if the property is not 
     * found.
     *
     * @param key The property key
     * @param def The  default value. 
     *
     * @return The value in this property list with the specified key value.
     *
     * @endif
     */
    const std::string& getProperty(const std::string& key,
				   const std::string& def) const;
    
    /*!
     * @if jp
     *
     * @brief ���ꤵ�줿��������ĥץ�ѥƥ��򡢥ץ�ѥƥ��ꥹ�Ȥ���õ��
     *
     * ���ꤵ�줿��������ĥץ�ѥƥ����֤���
     * ���Υ������ץ�ѥƥ��ꥹ�Ȥˤʤ���Хǥե�����ͤ��֤���
     * ����˸��Ĥ���ʤ���С���ʸ�����֤���
     *
     * @param key �ץ�ѥƥ�����
     *
     * @return ���ꤵ�줿�����ͤ���Ĥ��Υץ�ѥƥ��ꥹ�Ȥ���
     *
     * @else
     *
     * @brief Search for the property with the specified key in property list
     *
     * Search for the property with the specified key in this property list.
     * If the key is not found in this property list, the default property list,
     * and its defaults, recursively, are then checked. The method returns 
     * empty string if the property is not found. 
     *
     * @param key The property key
     *
     * @return The value in this property list with the specified key value.
     *
     * @endif
     */
    const std::string& operator[](const std::string& key) const;
    
    /*!
     * @if jp
     *
     * @brief ���ꤵ�줿��������ĥץ�ѥƥ��򡢥ץ�ѥƥ��ꥹ�Ȥ���õ��
     *
     * ���ꤵ�줿��������ĥץ�ѥƥ����֤���
     * ���Υ������ͤ��ץ�ѥƥ��ꥹ�Ȥˤʤ���Хǥե�����ͤ��֤���
     * ����˸��Ĥ���ʤ���С���ʸ�����֤���
     * �����ͤˤʤ���ˡ�Ʊ���ͤ�������Ǥ��ʤ��Ȥ���Ϳ����줿����
     * ���б�����ץ�ѥƥ��˱����ͤ�������
     *
     * @param key �ץ�ѥƥ�����
     *
     * @return ���ꤵ�줿�����ͤ���Ĥ��Υץ�ѥƥ��ꥹ�Ȥ���
     *
     * @else
     *
     * @brief Search for the property with the specified key in property list
     *
     * Search for the property with the specified key in this property list.
     * If the key is not found in this property list, the default property list,
     * and its defaults, recursively, are then checked. The method returns 
     * empty string if the property is not found.
     * If there is no element with the same value in the left value, insert the
     * right value in corresponding property.
     *
     * @param key The property key
     *
     * @return The value in this property list with the specified key value.
     *
     * @endif
     */
    std::string& operator[](const std::string& key);
    
    /*!
     * @if jp
     * @brief ���ꤵ�줿�������Ф��ƥǥե�����ͤ��������
     *
     * ���ꤵ�줿��������ĥץ�ѥƥ��Υǥե�����ͤ��֤���
     * ���ꤵ�줿��������ĥץ�ѥƥ���¸�ߤ��ʤ����ˤ϶�ʸ�����֤���
     *
     * @param key �ץ�ѥƥ�����
     *
     * @return ���ꤵ�줿�����ͤ���ĥץ�ѥƥ��Υǥե������
     *
     * @else
     * @brief Get the default values with specified key.
     *
     * Return the default values with specified key.
     * If the property with specified key does not exist, the method returns
     * empty string.
     *
     * @param key The property key
     *
     * @return The value in this property list with the specified key value.
     *
     * @endif
     */
    const std::string& getDefault(const std::string& key) const;
    
    /*!
     * @if jp
     *
     * @brief Properties �� value �� key �ˤĤ�����Ͽ����
     *
     * Properties �� value �� key �ˤĤ�����Ͽ���롣
     * ���Ǥ� key ���Ф����ͤ���äƤ����硢����ͤ˸Ť��ͤ��֤���
     *
     * @param key �ץ�ѥƥ��ꥹ�Ȥ����֤���륭��
     * @param value key ���б������� 
     *
     * @return �ץ�ѥƥ��ꥹ�Ȥλ��ꤵ�줿�����������͡����줬�ʤ����� null
     *
     * @else
     *
     * @brief Set a value associated with key in the property list
     *
     * This method sets the "value" associated with "key" in the property list.
     * If the property list has a value of "key", old value is returned.
     *
     * @param key The key to be placed into this property list.
     * @param value The value corresponding to key. 
     *
     * @return The previous value of the specified key in this property list,
     *         or null if it did not have one.
     *
     *@endif
     */
    std::string setProperty(const std::string& key, const std::string& value);
    
    /*!
     * @if jp
     * @brief �ǥե�����ͤ���Ͽ����
     *
     * key �ǻ��ꤵ������Ǥ˥ǥե�����ͤ���Ͽ���롣
     *
     * @param key �ǥե�����ͤ���Ͽ����ץ�ѥƥ��Υ���
     * @param value ��Ͽ�����ǥե������
     *
     * @return ���ꤵ�줿�ǥե������
     *
     * @else
     * @brief Set a default value associated with key in the property list
     *
     * Set the default value to element specified by "key".
     *
     * @param key Property's key to set the default value
     * @param value The default value that is set
     *
     * @return The specified default value
     *
     * @endif
     */
    std::string setDefault(const std::string& key, const std::string& value);
    
    /*!
     * @if jp
     * @brief Properties �˥ǥե�����ͤ�ޤȤ����Ͽ����
     *
     * ����ǻ��ꤵ�줿���Ǥ˥ǥե�����ͤ�ޤȤ����Ͽ���롣
     * �ǥե�����ͤ� char* ������ˤ��Ϳ����졢key �� value ���Фˤʤä�
     * ���ꡢ�ꥹ�Ȥν�ü������ο���ɽ������ num ������ʸ���� key ��Ϳ������
     * �ʤ���Фʤ�ʤ���
     * 
     * @param defaults �ǥե�����ͤ���ꤹ������
     * @param num �ǥե�����ͤ����ꤹ�����ǿ�(�ǥե������:LONG_MAX)
     * 
     * @else
     * @brief Set a default value together in the property list
     *
     * Set the default value to the element specified by array together in the
     * property list.
     * The default values are given by array of char*, which should be pairs
     * of "key" and "value". The end of list is specified by argument "num",
     * which specifies number of array or null character of key.
     * 
     * @param defaults Array that specifies the default values
     * @param num Number of elements that specifies the default value
     *            (Default value:LONG_MAX)
     * 
     * @endif
     */
    void setDefaults(const char* defaults[], long num = LONG_MAX);
    
    //============================================================
    // load and save functions
    //============================================================
    /*!
     * @if jp
     *
     * @brief ���ꤵ�줿���ϥ��ȥ꡼��ˡ��ץ�ѥƥ��ꥹ�Ȥ���Ϥ���
     *
     * ���ꤵ�줿���ϥ��ȥ꡼��ˡ��ץ�ѥƥ��ꥹ�Ȥ���Ϥ��롣
     * ���Υ᥽�åɤϼ�˥ǥХå����Ѥ����롣
     *
     * @param out ���ϥ��ȥ꡼��
     *
     * @else
     *
     * @brief Prints this property list out to the specified output stream
     *
     * Prints this property list out to the specified output stream.
     * This method is useful for debugging.
     *
     * @param out Output stream.
     *
     * @endif
     */
    void list(std::ostream& out);
    
    /*!
     * @if jp
     *
     * @brief ���ϥ��ȥ꡼�फ�饭�������Ǥ��Фˤʤä��ץ�ѥƥ��ꥹ�Ȥ��ɤ߹���
     *
     * ���ϥ��ȥ꡼�फ�饭�������Ǥ��Фˤʤä��ץ�ѥƥ��ꥹ�Ȥ��ɤ߹��ࡣ
     * ���ȥ꡼��ϡ�ISO 8859-1 ʸ�����󥳡��ǥ��󥰤���Ѥ��Ƥ���Ȥߤʤ���롣
     * �ƥץ�ѥƥ��ϡ����ϥ��ȥ꡼��˹�ñ�̤���Ͽ����Ƥ����ΤȤߤʤ��졢
     * �ƹԤϹԶ��ڤ�ʸ�� (\\n��\\r���ޤ��� \\r\\n) �ǽ���롣
     * ���ϥ��ȥ꡼�फ���ɤ߹�����Ԥϡ����ϥ��ȥ꡼��ǥե�����ν�����
     * ã����ޤǽ�������롣
     *
     * ����ʸ�������ιԡ��ޤ��Ϻǽ�������ʸ���� ASCII ʸ�� # �ޤ��� ! �Ǥ���
     * �Ԥ�̵�뤵��롣�Ĥޤꡢ# �ޤ��� ! �ϥ����ȹԤ򼨤���
     *
     * ����Ԥޤ��ϥ����ȹ԰ʳ��Τ��٤ƤιԤϡ��ơ��֥���ɲä����ץ�ѥƥ�
     * �򵭽Ҥ��롣���������Ԥν���꤬ \ �ξ��ϡ����ιԤ�����з�³�ԤȤ���
     * ������ (�����򻲾�)�� �����ϡ��ǽ�������ʸ�����顢�ǽ�� ASCII ʸ��
     * =��:���ޤ��϶���ʸ����ľ���ޤǤΡ�����Τ��٤Ƥ�ʸ�����鹽������롣
     *
     * �����ν����򼨤�ʸ���ϡ����� \ ���դ��뤳�Ȥˤ�ꥭ���˴ޤ�뤳�Ȥ�
     * �Ǥ��롣�����θ��ζ���Ϥ��٤ƥ����åפ���롣
     * �����θ��κǽ�������ʸ���� = �ޤ��� : �Ǥ�����ϡ������Υ�����
     * ̵�뤵�졢���Τ��Ȥζ���ʸ���⤹�٤ƥ����åפ���롣
     * ����Τ���ʳ���ʸ���Ϥ��٤ơ���Ϣ��������ʸ����ΰ����Ȥʤ롣
     * ����ʸ������Ǥϡ�ASCII ���������ץ������� \\t��\\n��\\r��\\\\��\\"��
     * \\'��\\ (�ߵ���ȥ��ڡ���)������� \\uxxxx ��ǧ�����졢ñ�Ȥ�ʸ�����Ѵ�
     * ����롣
     * �ޤ����ԤκǸ��ʸ���� \ �Ǥ�����ϡ����ιԤϸ��ߤιԤη�³�Ȥ���
     * �����롣���ξ�硢\ �ȹԶ��ڤ�ʸ�����˴����졢��³�Ԥ���Ƭ�˶���
     * ����Ф���⤹�٤��˴����졢����ʸ����ΰ����ˤϤʤ�ʤ��� 
     *
     * ���Ȥ��С����� 3 �ԤϤ��줾�쥭�� Truth �ȴ�Ϣ���������� Beauty ��ɽ����
     * 
     * Truth = Beauty <BR>
     * Truth:Beauty <BR>
     * Truth\\t\\t\\t:Beauty <BR>
     *
     * �ޤ������� 3 �Ԥ� 1 �ĤΥץ�ѥƥ���ɽ���� 
     *
     * fruits\\t\\t\\t\\tapple, banana, pear, \ <BR>
     *                                  cantaloupe, watermelon, \ <BR>
     *                                  kiwi, mango <BR>
     * ������ fruits �ǡ��������Ǥ˴�Ϣ�դ�����롣 
     * "apple, banana, pear, cantaloupe, watermelon, kiwi, mango"
     * �ǽ�Ū�ʷ�̤ǥ���ޤΤ��Ȥ�ɬ�����ڡ�����ɽ�������褦�ˡ�
     * �� \ �����˥��ڡ��������롣�Ԥν����򼨤� \ �ȡ���³�Ԥ���Ƭ�ˤ���
     * ������˴����졢¾��ʸ�����ִ�����ʤ��� 
     * �ޤ������� 3 ���ܤ���Ǥϡ������� cheeses �ǡ���Ϣ�������Ǥ�����ʸ����
     * �Ǥ��뤳�Ȥ�ɽ���� 
     *
     * cheeses <BR>
     * �����ϡ�cheeses �ǡ���Ϣ���Ǥ϶���ʸ����Ǥ��뤳�Ȥ���ꤷ�Ƥ��롣 
     *
     * @param inStream ���ϥ��ȥ꡼�� 
     *
     * @else
     *
     * @brief Loads property list that consists of key:value from input stream
     *
     * Reads a property list (key and element pairs) from the input stream.
     * The stream is assumed to be using the ISO 8859-1 character encoding.
     * Each property is assumed to be registered in the input stream by each
     * line, and each line terminator is should be a line break characters
     * (\\n or \\r or \\r\\n).
     * Lines are read from the input stream until end of file is reached. 
     *
     * A line that contains only white space characters or a line that its
     * first non-white space character is an ASCII '#' or '!' is ignored.
     * In a word, '#' or '!' represents comment lines.
     *
     * All lines except the blank line or comment line is described the property
     * that added to the table. However, if the line terminator is '\' and the 
     * next line continues, it is treated as a continuation line (See below).
     * The key is composed of all characters.
     * All of these key termination characters in the line starting with the 
     * first non-white space character and up to, but not including, the first
     * unescaped '=', ':', or white space character other than a line 
     * terminator. 
     * 
     * Line terminator characters can be included using \ escape sequences.
     * Any white space after the key is skipped.
     * If the first non-white space character after the key is '=' or ':',
     * then it is ignored and any white space characters after it are also 
     * skipped.
     * All remaining characters on the line become part of the associated element
     * string.
     * In element string, ASCII escape sequence such as \\t and \\n and \\r
     * and \\\\ and \\" and \\' and \\ (backslash character and space) 
     * and \\uxxxx have affect and they will be converted into a single 
     * character.
     * Also, if termination character in the line is \, the next line will be  
     * treated as continuing. In that case, \ and break character will be 
     * destroyed, and also its first space character will be destroyed, 
     * so these characters on the line will not become part of the element 
     * string.
     *
     * As an example, each of the following three lines specifies the key 
     * "Truth" and the associated element value "Beauty": 
     * 
     * Truth = Beauty <BR>
     * Truth:Beauty <BR>
     * Truth\\t\\t\\t:Beauty <BR>
     *
     * As another example, the following three lines specify a single 
     * property: 
     *
     * fruits\\t\\t\\t\\tapple, banana, pear, \ <BR>
     *                                  cantaloupe, watermelon, \ <BR>
     *                                  kiwi, mango <BR>
     * The key is "fruits" and the associated element is: 
     * "apple, banana, pear, cantaloupe, watermelon, kiwi, mango".
     * Note that a space appears before each \ so that a space will
     * each comma in the final result; the \, line terminator, and leading white
     * space on the continuation line are merely discarded and are not replaced
     * by one or more other characters. 
     * As a third example, the line: 
     *
     * cheeses <BR>
     * specifies that the key is "cheeses" and the associated element is the
     * empty string "".
     *
     * @param inStream the input stream.
     *
     * @endif
     */
    void load(std::istream& inStream);
    
    /*!
     * @if jp
     *
     * @brief �ץ�ѥƥ��ꥹ�Ȥ���ꤵ�줿���ȥ꡼�����¸����
     *
     * �侩����Ƥ��ޤ��󡣥ץ�ѥƥ��ꥹ�Ȥ���¸��ˡ�Ȥ��Ƥϡ�
     * store(ostream out, string header) �᥽�åɤλ��Ѥ��侩����롣
     * ���Υ᥽�åɤ� Java Properties �Ȥθߴ����Τ�����������Ƥ��롣
     *
     * @param out ���ϥ��ȥ꡼��
     * @param header �ץ�ѥƥ��ꥹ�Ȥε��� 
     *
     * @else
     *
     * @brief Save the property list to the specified stream
     *
     * It is not recommended. To save the property list,
     * the store(ostream out, string header) method is recommended.
     * This method is defined for compatibility of Java Properties.
     *
     * @param out The output stream
     * @param header A description of the property list
     *
     * @endif
     */
    void save(std::ostream& out, const std::string& header);
    
    /*!
     * @if jp
     *
     * @brief �ץ�ѥƥ��ꥹ�Ȥ���ϥ��ȥ꡼�����¸����
     *
     * Properties �ơ��֥���Υץ�ѥƥ��ꥹ�� (���������ǤΥڥ�) ��load
     * �᥽�åɤ�Ȥä� Properties �ơ��֥�˥��ɤ���Τ�Ŭ�ڤʥե����ޥåȤ�
     * ���ϥ��ȥ꡼��˽񤭹��ࡣ 
     *
     * Properties �ơ��֥���Υץ�ѥƥ��ꥹ�� (���������ǤΥڥ�) ��load
     * �᥽�åɤ�Ȥä� Properties �ơ��֥�˥��ɤ���Τ�Ŭ�ڤʥե����ޥåȤ�
     * ���ϥ��ȥ꡼��˽񤭹��ࡣ���ȥ꡼��ϡ�ISO 8859-1 ʸ��
     * ���󥳡��ǥ��󥰤���Ѥ��ƽ񤭹��ޤ�롣 
     * Properties �ơ��֥� (¸�ߤ�����) �Υǥե���ȥơ��֥뤫���
     * �ץ�ѥƥ��ϡ����Υ᥽�åɤˤ�äƤϽ񤭹��ޤ�ʤ��� 
     *
     * header ������ null �Ǥʤ����ϡ�ASCII ʸ���� #��header ��ʸ����
     * ����ӹԶ��ڤ�ʸ�����ǽ�˽��ϥ��ȥ꡼��˽񤭹��ޤ�ޤ������Τ��ᡢ
     * header �ϼ��̥����ȤȤ��ƻȤ����Ȥ��Ǥ��롣 
     *
     * ���ˡ�ASCII ʸ���� #�����ߤ����� (Date �� toString �᥽�åɤˤ�ä�
     * ���߻��郎���������Τ�Ʊ��)������� Writer �ˤ�ä����������Զ��ڤ�
     * ����ʤ륳���ȹԤ��񤭹��ޤ�롣 
     *
     * ³���ơ� Properties �ơ��֥���Τ��٤ƤΥ���ȥ꤬ 1 �Ԥ��Ľ񤭽Ф���롣
     * �ƥ���ȥ�Υ���ʸ����ASCII ʸ����=����Ϣ��������ʸ���󤬽񤭹��ޤ�롣
     * ����ʸ����γ�ʸ���ϡ����������ץ������󥹤Ȥ������褹��ɬ�פ����뤫
     * �ɤ�����ǧ����롣ASCII ʸ���� \�����֡����ԡ�����������Ϥ��줾�� \\\\��
     * \\t��\\n������� \\r �Ȥ��ƽ񤭹��ޤ�롣\\u0020 ��꾮����ʸ�������
     * \\u007E ����礭��ʸ���ϡ��б����� 16 ���� xxxx ��Ȥä� \\uxxxx �Ȥ���
     * �񤭹��ޤ�롣�����߶���ʸ���Ǥ��񤭶���ʸ���Ǥ�ʤ���Զ���ʸ���ϡ�
     * ���� \ ���դ��ƽ񤭹��ޤ�롣�������ͤ�ʸ�� #��!��=������� : �ϡ�
     * ɬ�����������ɤ����褦�ˡ����˥���å�����դ��ƽ񤭹��ޤ�롣 
     *
     * ����ȥ꤬�񤭹��ޤ줿���Ȥǡ����ϥ��ȥ꡼�ब�ե�å��夵��롣
     * ���ϥ��ȥ꡼��Ϥ��Υ᥽�åɤ��������������ȤⳫ�����ޤޤȤʤ롣 
     *
     * @param out ���ϥ��ȥ꡼��
     * @param header �ץ�ѥƥ��ꥹ�Ȥε��� 
     *
     * @else
     *
     * @brief Stores property list to the output stream
     *
     * Write this property list (key and element pairs) in this Properties 
     * table to the output stream in a format suitable for loading into a 
     * Properties table using the load method. The stream is written using the 
     * ISO 8859-1 character encoding. 
     * Properties from the defaults table of this Properties table (if any) are
     * not written out by this method. 
     *
     * If the header argument is not null, then an ASCII # character, the
     * comments string, and a line separator are first written to the output
     * stream. Thus, the header can serve as an identifying comment. 
     *
     * Next, a comment line is always written, consisting of an ASCII #
     * character, the current date and time (as if produced by the toString
     * method of Date for the current time), and a line separator as generated
     * by the Writer. 
     *
     * Then every entry in this Properties table is written out, one per line.
     * For each entry the key string is written, then an ASCII =, then the
     * associated element string. Each character of the key and element strings
     * is examined to see whether it should be rendered as an escape sequence.
     * The ASCII characters \, tab, form feed, newline, and carriage return are
     * written as \\\\, \\t, \\f \\n, and \\r, respectively. Characters less than
     * \\u0020 and characters greater than \\u007E are written as \\uxxxx for the
     * appropriate hexadecimal value xxxx. For the key, all space characters are
     * written with a preceding \ character. For the element, leading space
     * characters, but not embedded or trailing space characters, are written
     * with a preceding \ character. The key and element characters #, !, =, and
     * : are written with a preceding backslash to ensure that they are properly
     * loaded. 
     *
     * After the entries have been written, the output stream is flushed. The
     * output stream remains open after this method returns. 
     *
     * @param out An output stream.
     * @param header The description of the property list.
     *
     * @endif
     */
    void store(std::ostream& out, const std::string& header);
    
    //============================================================
    // other util functions
    //============================================================
    /*!
     * @if jp
     *
     * @brief �ץ�ѥƥ��Υ����Υꥹ�Ȥ� vector ���֤�
     *
     * �ᥤ��ץ�ѥƥ��ꥹ�Ȥ�Ʊ��̾���Υ��������Ĥ���ʤ����ϡ��ǥե���Ȥ�
     * �ץ�ѥƥ��ꥹ�Ȥˤ�����̤Υ�����ޤࡢ���Υץ�ѥƥ��ꥹ�Ȥˤ��뤹�٤�
     * �Υ����Υꥹ�Ȥ��֤��� 
     *
     * @return �ץ�ѥƥ��ꥹ�Ȥˤ��뤹�٤ƤΥ����Υꥹ�ȡ�
     *         �ǥե���ȤΥץ�ѥƥ��ꥹ�Ȥˤ��륭����ޤ�
     *
     * @else
     *
     * @brief Return an vector of all the keys in this property
     *
     * Returns an enumeration of all the keys in this property list, including
     * distinct keys in the default property list if a key of the same name has
     * not already been found from the main properties list.
     *
     * @return A vector of all the keys in this property list, including the
     *         keys in the default property list.
     *
     * @endif
     */
    std::vector<std::string> propertyNames(void) const;
    
    /*!
     * @if jp
     * @brief �ץ�ѥƥ��ο����������
     *
     * ����ѤߤΥץ�ѥƥ�����������롣
     *
     * @return �ץ�ѥƥ���
     *
     * @else
     * @brief Get the number of Properties
     *
     * Get the number of Properties that has already set.
     *
     * @return Number of Properties
     *
     * @endif
     */
    int size(void) const;
    
    /*!
     * @if jp
     * @brief �Ρ��ɤ��������
     *
     * ���ꤷ����������ĥΡ��ɤ�������롣
     * ¸�ߤ��ʤ�����������Ӷ�ʸ���ξ�� 0 ���֤���
     *
     * @param key �����оݥΡ��ɤΥ���
     *
     * @return �оݥΡ���
     *
     * @else
     * @brief Get node of properties
     *
     * Get node with specified key.
     *
     * @param key Target node key for getting
     *
     * @return Target node
     *
     * @endif
     */
    Properties* const findNode(const std::string& key) const;
    /*!
     * @if jp
     * @brief �Ρ��ɤ��������
     *
     * ���ꤷ����������ĥΡ��ɤ�������롣
     * ¸�ߤ��ʤ�����������Ӷ�ʸ���ξ�� 0 ���֤���
     *
     * @param key �����оݥΡ��ɤΥ���
     *
     * @return �оݥΡ���
     *
     * @else
     * @brief Get node of properties
     *
     * Get node with specified key.
     *
     * @param key Target node key for getting
     *
     * @return Target node
     *
     * @endif
     */
    Properties& getNode(const std::string& key);
    
    /*!
     * @if jp
     * @brief �����Ρ��ɤ���������
     *
     * ���ꤷ����������Ŀ����Ρ��ɤ��������롣
     * ����Ʊ�쥭������ĥΡ��ɤ���Ͽ�Ѥߤξ��ˤϥ��顼���֤���
     *
     * @param key �����Ρ��ɤΥ���
     *
     * @return �����Ρ����������
     *         ���ꤷ����������ĥΡ��ɤ�����¸�ߤ�����ˤ�false
     *
     * @else
     * @brief Create newly node of Properties
     *
     * Create nowly node with specified key.
     * If the node with the same key has been registered, error will be returned.
     *
     * @param key Newly node key
     *
     * @return Newly node creation result.
     *         false will be returned if the node with specified key has already
     *         existed.
     *
     * @endif
     */
    bool createNode(const std::string& key);
    
    /*!
     * @if jp
     * @brief �Ρ��ɤ�������
     *
     * ���ꤷ��̾�Τ���ĥץ�ѥƥ��������롣
     * ��������ץ�ѥƥ����֤���
     *
     * @param leaf_name ����оݥץ�ѥƥ�̾��
     *
     * @return ��������ץ�ѥƥ�
     *
     * @else
     * @brief Remove node of Properties
     *
     * Remove properties with specified name.
     * Properties that were deleted will be returned.
     *
     * @param leaf_name Target property's name for the delete
     *
     * @return Deleted properties
     *
     * @endif
     */
    Properties* removeNode(const char* leaf_name);
    
    /*!
     * @if jp
     * @brief �ҥΡ��ɤ�key�����뤫�ɤ���
     *
     * ���ꤷ����������ĻҥΡ��ɤ�¸�ߤ��뤫�ɤ�����ǧ���롣
     * ¸�ߤ����硢�ҥΡ��ɤ��֤���
     *
     * @param key ��ǧ�оݤΥ���
     *
     * @return �ҥΡ���
     *
     * @else
     * @brief Check whether key exists in the children
     *
     * Check whether the children with specified key exist.
     * If the children exist, they will be returned.
     *
     * @param key Check key
     *
     * @return Children node
     *
     * @endif
     */
    Properties* hasKey(const char* key) const;
    
    /*!
     * @if jp
     * @brief �ҥΡ��ɤ����ƺ������
     * @else
     * @brief Clear the children
     * @endif
     */
    void clear(void);
    
    /*!
     * @if jp
     * @brief Property��ޡ�������
     *
     * ���ߤΥץ�ѥƥ������ꤷ���ץ�ѥƥ���ޡ������롣
     *
     * @param prop �ޡ�������ץ�ѥƥ�
     *
     * @return �ץ�ѥƥ��ޡ������
     *
     * @else
     * @brief Merge properties
     *
     * Merge properties that have set to the current properties.
     *
     * @param prop Properties for the merge
     *
     * @return Property merge result
     *
     * @endif
     */
    Properties& operator<<(const Properties& prop);
    
  protected:
    /*!
     * @if jp
     * @brief ʸ����򥭡����ͤΥڥ���ʬ�䤹��
     *
     * Ϳ����줿ʸ��������ꤵ�줿�ǥ�ߥ��ǥ������ͤΥڥ���ʬ�䤹�롣
     * �ޤ��ǽ��Ϳ����줿ʸ�����':'�⤷����'='���ޤޤ�뤫�򸡺�����
     * �ɤ��餫��ʸ�����ޤޤ�Ƥ�����ˤϤ����ǥ�ߥ��Ȥ��ƻ��Ѥ��롣
     * ξ���Ȥ�ޤޤ�Ƥ��ʤ����ˤϡ�' '(���ڡ���)���Ѥ���ʬ����ߤ롣
     * ���ƤΥǥ�ߥ����䤬�ޤޤ�Ƥ��ʤ����ˤϡ�Ϳ����줿ʸ����򥭡��Ȥ���
     * ���ꤷ���ͤ˶���ʸ��������ꤹ�롣
     * �ɤΥǥ�ߥ�����ˤĤ��Ƥ⥨�������פ���Ƥ���(ľ����'\'�����ꤵ��Ƥ���)
     * ���ˤϡ��ǥ�ߥ��Ȥ��ƻ��Ѥ��ʤ���
     *
     * @param str ʬ���о�ʸ����
     * @param key ʬ���̥���
     * @param value ʬ������
     *
     * @else
     * @brief Split the string into a pair of the key and the value.
     *
     * Split the given string into a pair of the key and the value with
     * the set delimiter.
     * First, search whether the fist given string includes ':' or '=', and 
     * if either character is included, it is used as delimiter.
     * If neither is included, try to divide it with ' '(space).
     * When all delimiter candidates are not included, set the given string
     * as key then set empty string to the its value.
     * If any delimiter candidate is escaped ('\' is set right before it),
     * this method does not use as delimiter.
     *
     * @param str Target string for the division
     * @param key Division result key
     * @param value Division result value
     *
     * @endif
     */
    static void splitKeyValue(const std::string& str, std::string& key,
			      std::string& value);
    
    /*!
     * @if jp
     * @brief ʸ�����ʬ�䤹��
     *
     * Ϳ����줿ʸ�����Ϳ����줿�ǥ�ߥ���ʬ�䤹�롣
     * Ϳ����줿ʸ���󤬶��ξ��ϡ����顼���֤���
     * Ϳ����줿�ǥ�ߥ������������פ���Ƥ���(ľ����'\'�����ꤵ��Ƥ���)���
     * �ˤϡ��ǥ�ߥ��Ȥ��ƻ��Ѥ��ʤ���
     *
     * @param str ʬ���о�ʸ����
     * @param delim �ǥ�ߥ�
     * @param value ʬ�����ͥꥹ��
     *
     * @return ʬ��������
     *
     * @else
     * @brief Split the string
     *
     * Divide given string with given delimiter.
     * If the given string is empty, error will be returned.
     * When the given delimiter is escaped ('\' is set right before it)
     * this method does not use as delimiter.
     *
     * @param str Target string for the division
     * @param delim Delimiter
     * @param value Division result list
     *
     * @return Division result
     *
     * @endif
     */
    static bool split(const std::string& str, const char delim,
		      std::vector<std::string>& value);
    
    /*!
     * @if jp
     * @brief �ץ�ѥƥ����������
     *
     * �����ꥹ�Ȥǻ��ꤵ�줿�ץ�ѥƥ���������롣
     * �����ꥹ�ȤǤϡ����ꤹ�륭���Υץ�ѥƥ��Ǥγ��شط���ꥹ�ȷ�����ɽ��
     * ���롣
     * ���ꤷ�������ꥹ�Ȥ˳�������ץ�ѥƥ���¸�ߤ��ʤ�����NULL���֤���
     *
     * @param keys �����оݥץ�ѥƥ��Υ����Υꥹ��ɽ��
     * @param index �����ꥹ�Ȥγ��ؿ�
     * @param curr �����оݥץ�ѥƥ�
     *
     * @return �����оݥץ�ѥƥ�
     *
     * @else
     * @brief Get properties
     *
     * Get properties specified by key list.
     * In the key list, hierarchical relation in the properties is represented
     * by a list format.
     * If properties corresponding to specified key list do not exist,
     * null will be returned.
     *
     * @param keys Target properties's key list representation for getting
     * @param index Number of hierarchy of key list
     * @param curr Target properties for the search
     *
     * @return Target properties for the search
     *
     * @endif
     */
    static Properties* _getNode(std::vector<std::string>& keys,
				std::vector<Properties*>::size_type index,
				const Properties* curr);
    
    /*!
     * @if jp
     * @brief �ץ�ѥƥ���̾�Υꥹ�Ȥ��������
     *
     * �ץ�ѥƥ���̾�Τ�'.'���ڤ��ɽ�������ꥹ�Ȥ�������롣
     *
     * @param names �ץ�ѥƥ���̾�Υꥹ��
     * @param curr_name ���ߤΥץ�ѥƥ�̾
     * @param curr �оݥץ�ѥƥ�
     *
     * @else
     * @brief Get property name list
     *
     * Get a list expressed by separating each property name with '.'.
     *
     * @param names Name list of property
     * @param curr_name Current property's name
     * @param curr Target properties
     *
     * @endif
     */
    static void _propertiyNames(std::vector<std::string>& names,
				std::string curr_name,
				const Properties* curr);
    
    /*!
     * @if jp
     * @brief �ץ�ѥƥ���̾�Υꥹ�Ȥ���¸����
     *
     * �ץ�ѥƥ���̾�Τ�'.'���ڤ��ɽ�������ꥹ�Ȥ���¸���롣
     *
     * @param out �ץ�ѥƥ���̾�Υꥹ����¸��ν��ϥ��ȥ꡼��
     * @param curr_name ���ߤΥץ�ѥƥ�̾
     * @param curr �оݥץ�ѥƥ�
     *
     * @else
     * @brief Store the property name list
     *
     * Store a list expressed by separating each property name with '.'.
     *
     * @param out Output stream of property's name list of save destination.
     * @param curr_name Current property's name
     * @param curr Target properties
     *
     * @endif
     */
    static void _store(std::ostream& out, std::string curr_name,
		       Properties* curr);
    
    /*!
     * @if jp
     * @brief �ץ�ѥƥ������Ƥ���¸����
     *
     * �ץ�ѥƥ������ꤵ�줿���Ƥ���¸���롣
     * ��¸���ˤϥץ�ѥƥ����ؤο�����ɽ���������ղä���롣
     * �ͤ����ꤵ��Ƥ��ʤ��ץ�ѥƥ��ˤĤ��Ƥϡ��ǥե�����ͤ����Ϥ���롣
     *
     * @param out �ץ�ѥƥ�������¸��ν��ϥ��ȥ꡼��
     * @param curr �оݥץ�ѥƥ�
     * @param index ���ߤΥץ�ѥƥ�����
     *
     * @else
     * @brief Save property's contents
     *
     * Save the contents that were set to the property.
     * The figure represented the depth of the property hierarchy is
     * added when saving.
     * If property with the value that is not set, the default value will
     * be output.
     *
     * @param out Output stream of property's contents of save destination.
     * @param curr Target property
     * @param index Current property hierarchy
     *
     * @endif
     */
    static std::ostream& _dump(std::ostream& out, const Properties& curr,
			       int index);
    
    /*!
     * @if jp
     * @brief ����ǥ�Ȥ���������
     *
     * ���ꤵ�줿�����˽��ä�������������ǥ�Ȥ��֤���
     * �֤���륤��ǥ�Ȥϡ����������2�Ĥζ���
     *
     * @param index ����ǥ�ȿ��λ���
     *
     * @return �������줿����ǥ��
     *
     * @else
     * @brief Create indents
     *
     * Return indents according to specified figure.
     * Returned indents are specified figure x two blanks.
     *
     * @param index The specification of Number of indent
     *
     * @return Created indent
     *
     * @endif
     */
    static std::string indent(int index);
    
  private:
    std::string name;
    std::string value;
    std::string default_value;
    Properties* root;
    std::vector<Properties*> leaf;
    const std::string m_empty;

    /*!
     * @if jp
     * @brief Property�򥹥ȥ꡼��˽��Ϥ���
     *
     * Property�򥹥ȥ꡼��˽��Ϥ��롣
     *
     * @param lhs ���ϥ��ȥ꡼��
     * @param rhs �ץ�ѥƥ�
     *
     * @return ���ϥ��ȥ꡼��
     *
     * @else
     * @brief Output Properties to stream
     *
     * Output Properties to stream.
     *
     * @param lhs Output stream
     * @param rhs Properties
     *
     * @return Output stream
     *
     * @endif
     */
    friend std::ostream& operator<<(std::ostream& lhs, const Properties& rhs);

  };   // class Properties
};     // namespace coil  
#endif // COIL_PROPERTIES_H

