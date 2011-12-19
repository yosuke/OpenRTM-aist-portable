// -*- C++ -*-
/*!
 * @file LocalServiceAdmin.h
 * @brief SDO service administration class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#ifndef RTC_LOCALSERVICEADMIN_H
#define RTC_LOCALSERVICEADMIN_H

#include <coil/Mutex.h>
#include <coil/Factory.h>
#include <coil/Singleton.h>

#include <rtm/idl/SDOPackageStub.h>
#include <rtm/SystemLogger.h>
#include <rtm/LocalServiceBase.h>

namespace RTM
{
  // forward decl
  class LocalServiceBase;
  typedef LocalServiceBase* (*ECNewFunc)();
  typedef void (*ECDeleteFunc)(LocalServiceBase* ls);
  typedef coil::Guard<coil::Mutex> Guard;

  /*!
   * @if jp
   *
   * @class LocalService administration class
   * @brief LocalService �������饹
   *
   * TODO: Documentation
   *
   * @since 1.1.0
   *
   *
   * @else
   *
   * @class SDO service administration class
   * @brief SDO service administration class
   *
   * TODO: Documentation
   *
   * @since 1.1.0
   *
   * @endif
   */
  class LocalServiceAdmin
    : public coil::Singleton<LocalServiceAdmin>
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
    LocalServiceAdmin();
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     * 
     * @else
     *
     * @brief Virtual destractor
     *
     * Virtual destractor.
     *
     * @endif
     */
    virtual ~LocalServiceAdmin();
    
    /*!
     * @if jp
     *
     * @brief LocaServiceAdmin�ν����
     *
     * TODO: Documentation
     *
     * @else
     *
     * @brief Initialization of LocalServiceAdmin
     *
     * TODO: Documentation
     *
     * @endif
     */
    void init(coil::Properties& props);
    
    /*!
     * @if jp
     *
     * @brief LocalserviceAdmin �ν�λ����
     *
     * TODO: Documentation
     *
     * @else
     *
     * @brief Finalization ofLocalServiceAdmin
     *
     * TODO: Documentation
     *
     * @endif
     */
    void finalize();
    
    /*!
     * @if jp
     *
     * @brief LocalServiceProfileList�μ���
     * 
     * TODO: Documentation
     *
     * @else
     *
     * @brief Getting LocalServiceProfileList
     *
     * TODO: Documentation
     *
     * @endif
     */
    ::RTM::LocalServiceProfileList getServiceProfiles();
    
    /*!
     * @if jp
     *
     * @brief LocalServiceProfile ���������
     *
     * id �ǻ��ꤵ�줿ID�����LocalService ��
     * LocalServiceProfile ��������롣id �� NULL �ݥ��󥿤ξ�硢���ꤵ�줿
     * id �˳�������ServiceProfile ��¸�ߤ��ʤ���硢false���֤���
     *
     * @param id LocalService �� IFR ID
     * @return ���ꤵ�줿 id ����� LocalServiceProfile
     * 
     * @else
     *
     * @brief Get LocalServiceProfile of an LocalService
     *
     * This operation returns LocalServiceProfile of a LocalService
     * which has the specified id. If the specified id is
     * NULL pointer or the specified id does not exist in the
     * ServiceProfile list, false will be returned.
     *
     * @param id ID of an LocalService
     * @return LocalServiceProfile which has the specified id
     *
     * @endif
     */
    bool getServiceProfile(std::string name,
                           ::RTM::LocalServiceProfile& prof);
    
    /*!
     * @if jp
     *
     * @brief LocalService �� Service ���������
     *
     * id �ǻ��ꤵ�줿ID�����LocalService �Υݥ��󥿤�������롣id ��
     * NULL �ݥ��󥿤ξ�硢���ꤵ�줿 id �˳�������ServiceProfile ��¸
     * �ߤ��ʤ���硢NULL���֤���
     *
     * @param id LocalService �� ID
     * @return ���ꤵ�줿 id ����� LocalService �Υݥ���
     * 
     * @else
     *
     * @brief Get a pointer of a LocalService
     *
     * This operation returnes a pointer to the LocalService
     * which has the specified id. If the specified id is
     * NULL pointer or the specified id does not exist in the
     * ServiceProfile list, NULL pointer will be returned.
     *
     * @param id ID of a LocalService
     * @return a pointer which has the specified id
     *
     * @endif
     */
    ::RTM::LocalServiceBase* getService(const char* id);
    
    /*!
     * @if jp
     * @brief SDO service provider �򥻥åȤ���
     *
     * TODO: Documentation
     * 
     * @else
     * @brief Set a SDO service provider
     *
     * TODO: Documentation
     *
     * @endif
     */
    bool addLocalService(::RTM::LocalServiceBase* service);
    
    /*!
     * @if jp
     * @brief LocalService ��������
     *
     * TODO: Documentation
     *
     * @else
     * @brief Remove a LocalService
     *
     * TODO: Documentation
     *
     * @endif
     */
    bool removeLocalService(const std::string name);
    
  private:
    /*!
     * @if jp
     * @brief ���ꤵ�줿ID��ͭ�����ɤ��������å�����
     * @else
     * @brief Check if specified ID is enabled
     * @endif
     */
    bool isEnabled(const std::string& id, const coil::vstring& enabled);
    
    /*!
     * @if jp
     * @brief ���ꤵ�줿ID�����Ǥ�¸�ߤ��뤫�ɤ��������å�����
     * @else
     * @brief Check if specified ID is existing
     * @endif
     */
    bool notExisting(const std::string& id);
    
    /*!
     * @if jp
     * @brief Lock �դ� SDO ServiceProfileList
     * @else
     * @brief SDO ServiceProfileList with mutex lock
     * @endif
     */
    std::vector<LocalServiceBase*> m_services;
    coil::Mutex m_services_mutex;
    
    /*!
     * @if jp
     * @brief logger
     * @else
     * @brief logger
     * @endif
     */
    ::RTC::Logger rtclog;
  };
}; // RTM

#endif // RTC_LOCALSERVICEADMIN_H
