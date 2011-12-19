// -*- C++ -*-
/*!
 * @file ManagerConfig.h
 * @brief RTC manager configuration
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ManagerConfig.h 2102 2011-05-22 13:56:17Z n-ando $
 *
 */

#ifndef RTC_MANAGERCONFIG_H
#define RTC_MANAGERCONFIG_H

#include <coil/Properties.h>


namespace RTC
{
  /*!
   * @if jp
   *
   * @class ManagerConfig
   * @brief Manager configuration ���饹
   *
   * Manager �Υ���ե�����졼������Ԥ������ޥ�ɥ饤������������ꡢ
   * (���뤤�ϰ����ʤ���)���󥹥��󥹲�����롣
   * ���ޥ�ɥ饤������ǻ��ꤵ�줿����ե����롢�Ķ��ѿ��ʤɤ��� Manager ��
   * �ץ�ѥƥ���������ꤹ�롣
   *
   * �������ͥ���٤ϰʲ��ΤȤ���Ǥ��롣
   * <OL>
   * <LI>���ޥ�ɥ饤�󥪥ץ���� "-f"
   * <LI>�Ķ��ѿ� "RTC_MANAGER_CONFIG"
   * <LI>�ǥե��������ե����� "./rtc.conf"
   * <LI>�ǥե��������ե����� "/etc/rtc.conf"
   * <LI>�ǥե��������ե����� "/etc/rtc/rtc.conf"
   * <LI>�ǥե��������ե����� "/usr/local/etc/rtc.conf"
   * <LI>�ǥե��������ե����� "/usr/local/etc/rtc/rtc.conf"
   * <LI>�����ߥ���ե�����졼�������
   *</OL>
   * �����������ޥ�ɥ饤�󥪥ץ���� "-d" �����ꤵ�줿���ϡ�
   * (���Ȥ� -f ������ե��������ꤷ�Ƥ�)�����ߥ���ե�����졼�������
   * �����Ѥ���롣
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class ManagerConfig
   * @brief Manager configuration class
   *
   * Modify Manager's configuration. 
   * This class receives the command line arguments and will be instantiated.
   * Set property information of Manager with the configuration file specified
   * by the command line argument or the environment variable etc.
   *
   * The priorities of each configuration are as follows:
   * <OL>
   * <LI>Command option "-f"
   * <LI>Environment variable "RTC_MANAGER_CONFIG"
   * <LI>Default configuration file "./rtc.conf"
   * <LI>Default configuration file "/etc/rtc.conf"
   * <LI>Default configuration file "/etc/rtc/rtc.conf"
   * <LI>Default configuration file "/usr/local/etc/rtc.conf"
   * <LI>Default configuration file "/usr/local/etc/rtc/rtc.conf"
   * <LI>Embedded configuration value
   *</OL>
   * If the command option "-d" is specified (even if specify configuration file
   * by "-f" option), the embedded configuration values will be used.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ManagerConfig
  {
  public:
    // The list of default configuration file path.
    /*!
     * @if jp
     * @brief Manager ����ե�����졼�����Υǥե���ȡ��ե����롦�ѥ�
     * @else
     * @brief The default configuration file path for manager
     * @endif
     */
    static const char* config_file_path[];
    
    // Environment value to specify configuration file
    /*!
     * @if jp
     * @brief �ǥե���ȡ�����ե�����졼�����Υե����롦�ѥ����̤���
     *        �Ķ��ѿ�
     * @else
     * @brief The environment variable to distinguish the default configuration
     *        file path
     * @endif
     */
    static const char* config_file_env;
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����(���⤷�ʤ�)
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor (Do nothing)
     *
     * @endif
     */
    ManagerConfig();
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * Ϳ����줿�����ˤ�ꥳ��ե�����졼��������ν������Ԥ���
     *
     * @param argc ���ޥ�ɥ饤������ο�
     * @param argv ���ޥ�ɥ饤�����
     *
     * @else
     *
     * @brief Constructor
     *
     * Initialize configuration information by given arguments.
     *
     * @param argc Number of command line arguments
     * @param argv The command line arguments
     *
     * @endif
     */
    ManagerConfig(int argc, char** argv);
    
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
    virtual ~ManagerConfig(void);
    
    /*!
     * @if jp
     *
     * @brief �����
     *
     * ���ޥ�ɥ饤������˱����ƽ������¹Ԥ��롣���ޥ�ɥ饤�󥪥ץ�����
     * �ʲ��Τ�Τ����Ѳ�ǽ�Ǥ��롣
     *
     *  - -f file   : ����ե�����졼�����ե��������ꤹ�롣
     *  - -l module : ���ɤ���⥸�塼�����ꤹ�롣(̤����)
     *  - -o options: ����¾���ץ�������ꤹ�롣(̤����)
     *  - -d        : �ǥե���ȤΥ���ե�����졼������Ȥ���(̤����)
     *
     * @param argc ���ޥ�ɥ饤������ο�
     * @param argv ���ޥ�ɥ饤�����
     *
     * @else
     *
     * @brief Initialization
     *
     * Initialize with command line options. The following command options
     * are available.
     *
     * - -f file   : Specify the configuration file.
     * - -l module : Specify modules to be loaded. (Not implemented)
     * - -o options: Specify other options. (Not implemented)
     * - -d        : Use default static configuration. (Not implemented)
     *
     * @param argc Number of command line arguments
     * @param argv The command line arguments
     *
     * @endif
     */
    void init(int argc, char** argv);
    
    /*!
     * @if jp
     * @brief Configuration ����� Property �����ꤹ��
     * 
     * Manager ��Configuration �������ꤵ�줿 Property �����ꤹ�롣
     *
     * @param prop Configuration �����о� Property
     * 
     * @else
     * @brief Specify the configuration information to the Property
     * 
     * Configure to the properties specified by Manager's configuration
     *
     * @param prop The target properties to configure
     * 
     * @endif
     */
    void configure(coil::Properties& prop);
    
    /*!
     * @if jp
     *
     * @brief ����ե�����졼�������������
     *
     * ����ե�����졼������������롣init()�ƤӽФ����˸Ƥ֤ȡ�
     * ��Ū��������줿�ǥե���ȤΥ���ե�����졼�������֤���
     * init() �ƤӽФ���˸Ƥ֤ȡ����ޥ�ɥ饤��������Ķ��ѿ�����
     * ��Ť�����������줿����ե�����졼�������֤���
     * (̤����)
     *
     * @return Manager �Υ���ե�����졼��������
     *
     * @else
     *
     * @brief Get the configuration.
     *
     * Get the configuration.
     * When this operation is called before calling init() function,
     * return the default configuration statically defined,
     * When this operation is called after calling init() function,
     * return the initialized configuration according to
     * the command line arguments, the environment variables etc.
     * (Not implemented)
     *
     * @return Manager's configuration information
     *
     * @endif
     */
    coil::Properties getConfig() const;
    
  protected:
    /*!
     * @if jp
     *
     * @brief ���ޥ�ɰ�����ѡ�������
     *
     * - -f file   : ����ե�����졼�����ե��������ꤹ�롣
     * - -l module : ���ɤ���⥸�塼�����ꤹ�롣(̤����)
     * - -o options: ����¾���ץ�������ꤹ�롣(̤����)
     * - -d        : �ǥե���ȤΥ���ե�����졼������Ȥ���(̤����)
     *
     * @param argc ���ޥ�ɥ饤������ο�
     * @param argv ���ޥ�ɥ饤�����
     *
     * @else
     *
     * @brief Parse the command arguments
     *
     *  - -f file   : Specify the configuration file.
     *  - -l module : Specify modules to be loaded. (Not implemented)
     *  - -o options: Other options. (Not implemented)
     *  - -d        : Use default static configuration. (Not implemented)
     *
     * @param argc Number of command line arguments
     * @param argv The command line arguments
     *
     * @endif
     */
    void parseArgs(int argc, char** argv);
    
    /*!
     * @if jp
     *
     * @brief Configuration file �θ���
     *
     * Configuration file �򸡺��������ꤹ�롣
     * ���� Configuration file ������Ѥߤξ��ϡ��ե������¸�߳�ǧ��Ԥ���
     *
     * Configuration file ��ͥ����<br>
     * ���ޥ�ɥ��ץ��������Ķ��ѿ���ǥե���ȥե������ǥե��������
     *
     * �ǥե���ȶ������ץ����(-d): �ǥե���ȥե����뤬���äƤ�̵�뤷��
     *                               �ǥե���������Ȥ�
     *
     * @return Configuration file �������
     *
     * @else
     *
     * @brief Find the configuration file
     *
     * Find the configuration file and configure it.
     * Confirm the file existence when the configuration file has 
     * already configured.
     *
     * The priority of the configuration file<br>
     * The command option��the environment variable��the default file��
     * the default configuration
     *
     * Default force option(-d): Ignore any default files and use the default 
     * configuration.
     *
     * @return Configuration file search result
     *
     * @endif
     */
    bool findConfigFile();
    
    /*!
     * @if jp
     *
     * @brief �����ƥ��������ꤹ��
     *
     * �����ƥ�����������ץ�ѥƥ��˥��åȤ��롣���ꤵ��륭���ϰʲ����̤ꡣ
     *  - os.name    : OS̾
     *  - os.release : OS��꡼��̾
     *  - os.version : OS�С������̾
     *  - os.arch    : OS�������ƥ�����
     *  - os.hostname: �ۥ���̾
     *  - manager.pid        : �ץ���ID
     * 
     * @param prop �����ƥ��������ꤷ���ץ�ѥƥ�
     * @else
     * 
     * @brief Set system information
     * 
     * Get the following system info. and set them to Manager's properties.
     *  - os.name    : OS name
     *  - os.release : OS release name
     *  - os.version : OS version
     *  - os.arch    : OS architecture
     *  - os.hostname: Hostname
     *  - manager.pid        : process ID
     *
     * @param prop Properties to set system information
     *
     * @endif
     */
    void setSystemInformation(coil::Properties& prop);
    
    /*!
     * @if jp
     * @brief �ե������¸�߳�ǧ
     *
     * ���ꤵ�줿�ե����뤬¸�ߤ��뤫��ǧ���롣
     *
     * @param filename ��ǧ�оݥե�����̾��
     *
     * @return �оݥե������ǧ���(¸�ߤ������true)
     *
     * @else
     * @brief Check the file existence
     *
     * Confirm whether the specified file exists
     *
     * @param filename The target confirmation file
     *
     * @return file existance confirmation (True if the file exists.)
     *
     * @endif
     */
    bool fileExist(const std::string& filename);
    
    /*!
     * @if jp
     * @brief ���������Ϥ����ץ�ѥƥ�
     * @else
     * @brief configuration properties from arguments
     * @endif
     */
    coil::Properties m_argprop;

    /*!
     * @if jp
     * @brief Manager ����ե�����졼����󡦥ե�����Υѥ�
     * @else
     * @brief Manager's configuration file path
     * @endif
     */
    std::string m_configFile;

    /*!
     * @if jp
     * @brief Manager �ޥ����ե饰
     *
     * true:�ޥ���,false:���졼��
     *
     * @else
     * @brief Manager master flag
     *
     * true:master,false:slave
     *
     * @endif
     */
    bool m_isMaster;
  };
}; // namespace RTC  
#endif // RTC_MANAGERCONFIG_H
