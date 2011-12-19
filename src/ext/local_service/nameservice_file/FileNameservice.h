// -*- C++ -*-
/*!
 * @file FileNameservice.h
 * @brief FileNameservice 
 * @date 2011/08/20
 * @author n-ando
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 * 
 */

#ifndef RTM_LOCALSERVICE_FILENAMESERVICE_H
#define RTM_LOCALSERVICE_FILENAMESERVICE_H

#include <coil/stringutil.h>

#include <rtm/RTC.h>
#include <rtm/SystemLogger.h>
#include <rtm/LocalServiceBase.h>

namespace fs = boost::filesystem;

namespace RTM
{
  namespace LocalService
  {
    /*!
     * @if jp
     * @class FileNameservice ���饹
     * @brief FileNameservice ���饹
     * @else
     * @class FileNameservice class
     * @brief FileNameservice class
     * @endif
     */
    class FileNameservice
      : public RTM::LocalServiceBase
    {
    public:
      /*!
       * @if jp
       * @brief FileNameService ctor
       * @else
       * @brief FileNameService ctor
       * @endif
       */
      FileNameservice();
      
      /*!
       * @if jp
       * @brief FileNameService dtor
       * @else
       * @brief FileNameService dtor
       * @endif
       */
      virtual ~FileNameservice();
      
      /*!
       * @if jp
       * @brief ������ؿ�
       *
       * TODO: Documentation
       *
       * @param profile ��������Ϳ����줿 property
       * @return 
       *
       * @else
       * @brief Initialization function
       *
       * TODO: Documentation
       *
       * @endif
       */
      virtual bool
      init(const ::coil::Properties& profile);
      
      /*!
       * @if jp
       * @brief �ƽ�����ؿ�
       *
       * TODO: Documentation
       *
       * @param profile ��������Ϳ����줿 property
       * @return 
       *
       * @else
       * @brief Reinitialization function
       *
       * TODO: Documentation
       *
       * @endif
       */
      virtual bool
      reinit(const ::coil::Properties& profile);
      
      /*!
       * @if jp
       * @brief LocalServiceProfile ���������
       *
       * TODO: Documentation
       *
       * @return ���Υ��֥������Ȥ��ݻ����Ƥ��� LocalServiceProfile
       *
       * @else
       * @brief Getting LocalServiceProfile
       *
       * TODO: Documentation
       *
       * @return LocalServiceProfile of this service class
       *
       * @endif
       */
      virtual const LocalServiceProfile& getProfile() const;
      
      /*!
       * @if jp
       * @brief ��λ�ؿ�
       *
       * TODO: Documentation
       *
       * @else
       * @brief Finalization function
       *
       * TODO: Documentation
       *
       * @endif
       */
      virtual void finalize();
      
      /*!
       * @if jp
       * @brief ̾����Ͽ���˸ƤФ�륳����Хå�
       *
       * TODO: Documentation
       *
       * @else
       * @brief A call-back at name registration
       *
       * TODO: Documentation
       *
       * @endif
       */
      void
      onRegisterNameservice(coil::vstring& path, coil::vstring& ns_info);
      
      /*!
       * @if jp
       * @brief ̾����Ͽ����˸ƤФ�륳����Хå�
       *
       * TODO: Documentation
       *
       * @else
       * @brief A call-back at name runegistration
       *
       * TODO: Documentation
       *
       * @endif
       */
      void
      onUnregisterNameservice(coil::vstring& path);
      
    protected:
      /*!
       * @if jp
       * @brief �ǥ��쥯�ȥ����
       * TODO: Documentation
       * @else
       * @brief Creating directories
       * TODO: Documentation
       * @endif
       */
      bool createDirectory(fs::path& directory);
      
      /*!
       * @if jp
       * @brief �ե�����̾����
       * TODO: Documentation
       * @else
       * @brief Getting file name
       * TODO: Documentation
       * @endif
       */
      std::string getFname(std::string& path) const;
      
      /*!
       * @if jp
       * @brief ���ե�������
       * TODO: Documentation
       * @else
       * @brief Deleting all files
       * TODO: Documentation
       * @endif
       */
      void cleanupFiles();
      
      /*!
       * @if jp
       * @brief �ץ�ѥƥ��ν���
       * TODO: Documentation
       * @else
       * @brief Processing properties
       * TODO: Documentation
       * @endif
       */
      bool processServiceProfile(const ::coil::Properties& props);
      
    private:
      RTM::LocalServiceProfile m_profile;
      coil::vstring m_files;
      mutable RTC::Logger rtclog;
    };
    
    /*!
     * @if jp
     * @class NamingAction class
     * TODO: Documentation
     * @else
     * @class NamingActin class
     * TODO: Documentation
     * @endif
     */
    class NamingAction
      : public RTM::NamingActionListener
    {
    public:
      /*!
       * @if jp
       * @brief ���󥹥ȥ饯��
       * @else
       * @brief Constructor
       * @endif
       */
      NamingAction(FileNameservice& fns);

      /*!
       * @if jp
       * @brief �ǥ��ȥ饯��
       * @else
       * @brief Destructor
       * @endif
       */
      virtual ~NamingAction();

      /*!
       * @if jp
       * @brief preBind ������Хå��ؿ�
       * TODO: Documentation
       * @else
       * @brief preBind callback function
       * TODO: Documentation
       * @endif
       */
      virtual void preBind(RTC::RTObject_impl* rtobj,
                           coil::vstring& name);
      /*!
       * @if jp
       * @brief postBind ������Хå��ؿ�
       * TODO: Documentation
       * @else
       * @brief postBind callback function
       * TODO: Documentation
       * @endif
       */
      virtual void postBind(RTC::RTObject_impl* rtobj,
                            coil::vstring& name);
      
      /*!
       * @if jp
       * @brief preUnbind ������Хå��ؿ�
       * TODO: Documentation
       * @else
       * @brief preUnbind callback function
       * TODO: Documentation
       * @endif
       */
      virtual void preUnbind(RTC::RTObject_impl* rtobj,
                             coil::vstring& name);
      
      /*!
       * @if jp
       * @brief postUnbind ������Хå��ؿ�
       * TODO: Documentation
       * @else
       * @brief postUnbind callback function
       * TODO: Documentation
       * @endif
       */
      virtual void postUnbind(RTC::RTObject_impl* rtobj,
                              coil::vstring& name);
    private:
      RTM::LocalService::FileNameservice& m_fns;
    };
    
  }; // LocalService
}; // RTM

extern "C"
{
  /*!
   * @if jp
   * @brief �⥸�塼�������ؿ�
   *
   * FileNameservice��ե����ȥ����Ͽ���������ؿ���
   *
   * @else
   * @brief Module initialization
   *
   * This initialization function registers FileNameservice to the factory.
   *
   * @endif
   */
  DLL_EXPORT void FileNameserviceInit();
};

#endif /* FILENAMESERVICE_H_ */
