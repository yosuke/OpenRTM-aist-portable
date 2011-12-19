// -*- C++ -*-
/*!
 * @file LocalServiceBase.h
 * @brief Local service provider base class and its factory
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
 * $Id$
 *
 */

#ifndef RTM_LOCALSERVICEBASE_H
#define RTM_LOCALSERVICEBASE_H

#include <vector>

#include <coil/Mutex.h>
#include <coil/Factory.h>
#include <coil/Timer.h>
#include <coil/Properties.h>

namespace RTM
{
  
  // forward decl
  class LocalServiceBase;
  
  /*!
   * @if jp
   * @brief LocalService�Υץ�ե�����ǡ���
   * @else
   * @brief Profile data structure of LocalService
   * @endif
   */
  class LocalServiceProfile
  {
  public:
    /*!
     * @if jp
     * @brief LocalService�Υ����ӥ�̾
     * @else
     * @brief The name of LocalService
     * @endif
     */
    std::string name;
    /*!
     * @if jp
     * @brief LocalService�θ�ͭID
     * @else
     * @brief The unique ID of LocalService
     * @endif
     */
    std::string uuid;
    /*!
     * @if jp
     * @brief LocalService�Υץ�ѥƥ�
     * @else
     * @brief Properties of LocalService
     * @endif
     */
    coil::Properties properties;
    /*!
     * @if jp
     * @brief LocalService�Υݥ���
     * @else
     * @brief The pointer to LocalService
     * @endif
     */
    LocalServiceBase* service;
  };
  
  /*!
   * @if jp
   * @brief LocalService�Υꥹ��
   * @else
   * @brief List of LocalServiceProfile
   * @endif
   */
  typedef std::vector<LocalServiceProfile> LocalServiceProfileList;
  
  /*!
   * @if jp
   *
   * @brief LocalService�����쥯�饹
   *
   * Local Service �Ȥ� RT-Middleware�Υޥ͡�����ǡ������ǳƼ掠����
   * �����󶡤��뤿��λ��ȤߤǤ��롣Local Service�ˤϤ����Ĥ��Υ桼��
   * ���������ͤ����롣
   *
   * 1. RTC���������å����Ф��ƥ����ӥ����󶡤��롣����ݡ��ͥ�Ȥγ�
   * ȯ�Ԥϡ�����������Фơ�Local Service�Υ��󥹥��󥹤ؤλ��Ȥ���
   * �ơ����Υ����ӥ������Ѥ��뤳�Ȥ��Ǥ��롣
   *
   * 2. �ޥ͡��������˵�ǽ���ɲä��뤿��Υ����ӥ������Ȥ��ϡ�RTC��̾��
   * ����Ͽ����CORBA�͡��ॵ���ӥ�������ˡ������ʥǥ��쥯�ȥꥵ����
   * ����֥��ɥ��㥹�Ȥˤ��̾�����ε�ǽ�ʤɤ򿷤��ʵ�ǽ��ޥ͡�����
   * ���ɲä��뤿������Ѥ��뤳�Ȥ��Ǥ��롣�ޥ͡�����ˤϡ��͡��ʥ�������
   * ����Ф���եå����Ѱդ���Ƥ��ꡢ��������Ѥ��뤳�Ȥǡ��ޥ͡�����
   * ���͡��ʥ��٥�Ȥ��Ф��ƥ��������򵯤������Ȥ��Ǥ��롣
   *
   * 3. �ޥ͡�����ϼ��ȤΥ����ӥ��ʳ����ղ�Ū�˳������Ф��ƥ����ӥ���
   * �󶡤��뵡ǽ��ͭ���롣��������CORBA��ͳ�ǡ�������ε�ǽ�����Ȥ�
   * �ХǥХ�����꥽�����Υޥͥ����ȵ�ǽ���Ф��ƥ�������������ˡ����
   * �����롣�����ӥ��Υ��󥹥��󥹲���ˡ��ޥ͡�������Ф��ơ��ޥ͡�����
   * �����ӥ��Ȥ�����Ͽ���뤳�Ȥǡ���������Υ�������������դ��뤳�Ȥ�
   * �Ǥ���褦�ˤʤ롣
   *
   * Local Service �ϥ⥸�塼��Ȥ��ƥ��ɤ��졢�̾�ͣ��Υ��󥹥���
   * ����������롣���ʤ����LocalService �ϥ��󥰥�ȥ�Ȥ��Ƽ�������
   * �롣���󥹥��󥹲����줿�����ӥ��ϥ����ӥ��ꥹ�Ȥ���Ͽ���졢RTC��
   * �����̾����UUID�ˤ�äƥ��󥹥��󥹤λ��Ȥ����ꤹ�뤳�Ȥ��Ǥ��롣
   *
   * ���Υ��֥������ȤΥ饤�ե�������ϰʲ����̤ꡣ
   *
   * -# ���֥������Ȥ��̾��ͭ���֥������� (so, DLL) �Ȥ��ƥ���ѥ��롦
   *    ��󥯤���롣
   * -# �ޥ͡�������Ф��ƥ��ɤ����ȥ⥸�塼�������ؿ��ˤ�ꥪ��
   *    �������ȥե����ȥ꤬��LocalServiceFactory ���Ф�����Ͽ����롣
   *    ��Ͽ�Υ����ˤ�UUID��̾�������Ѥ��졢����ˤ�ꥵ���ӥ������̤�
   *    ��롣
   * -# rtc.conf���Υ���ե�����졼��������ˤ�ꡢͭ�������뤳�Ȥ�
   *    ���ꤵ��Ƥ��륵���ӥ�����ץ�Х����ϡ�RTC�ε�ư��Ʊ���˥���
   *    ���󥹲�����롣
   * -# ���󥹥��󥹲��塢������ؿ� init() ���ƤФ�롣�����ˤ���������
   *    �ӥ��Τ���Υ���ե�����졼����󥪥ץ���� coil::Property��
   *    ����Ϥ���롣
   * -# �ޥ͡����㥵���ӥ����ڥ졼����� reinit ���ƤФ��ȡ����٤Ƥ�
   *     Local Service �� reinit ���ƤӽФ��졢�������줿����ե�����졼
   *     ���������ɤ߹��ޤ�롣
   * -# �ޥ͡�������λ��ˤϡ����٤Ƥ� Local Service �� finalize���Ƥ�
   *       �Ф��졢���Τ����Τǡ������ǥ꥽�����β����ʤɽ�λ�������
   *       ����
   *
   * ���Υ��饹�μ����������äƤϡ����ʤ��Ȥ�ʲ��ν�貾�۴ؿ��������
   * ��ɬ�פ����롣
   *
   * - init(): ������ؿ���Ϳ����줿 RTObject ����� ServiceProfile ��
   *   �顢�������֥������Ȥ��������롣
   * - reinit(): �ƽ�����ؿ���ServiceProfile ��������󹹿��Τ���Ʊ��
   *   ID�ǸƤӽФ���뤳�Ȥ�ͭ�뤬�����κݤˤ��δؿ���������
   *   ServiceProfile �ȤȤ�˸ƤӽФ���롣�ؿ���Ǥϡ�������ѹ��ʤ�
   *   �ƽ����������������롣
   * - getProfile(): ���ꤵ�줿�ץ�ե�������֤��ؿ���
   * - finalize(): ��λ���������󥷥塼�ޤ��ǥ��å������ݤ˸ƤӽФ���
   *   ��ؿ����ؿ���ǤϽ�λ������������롣
   *
   * LocalService ���̾ﶦͭ���֥������ȤȤ��ƥ���ѥ��롦���
   * ����롣��ͭ���֥������ȤΥ���ȥ�ݥ���Ȥ��̾拾��ѥ��뤵�줿�ե�
   * ����̾�� basename + "Init" �ˤ��Ƥ������ʲ��ˡ����饹̾���ե�����
   * ̾������ȥ�ݥ���ȴؿ�̾�ο侩��򼨤���
   *
   * - �������饹̾: MyLocalService
   * - �ե�����̾: MyLocalService.h. MyLocalService.cpp
   * - ��ͭ���֥�������̾: MyLocalService.so (or DLL)
   * - ����ȥ�ݥ���ȴؿ�̾: MyLocalServiceInit()
   *
   * ����ȥ�ݥ���ȴؿ����̾�ʲ��Τ褦�ˡ�LocalServiceFactory
   * ���������󥷥塼�ޤΥե����ȥ� (�Ȳ��Υե��󥯥�) ����Ͽ����ʲ���
   * �褦�ʴؿ��ˤʤ롣
   *
   * <pre>
   * extern "C"
   * {
   *   void MyLocalServiceInit()
   *   {
   *     RTC::LocalServiceFactory& factory
   *       = RTC::LocalServiceFactory::instance();
   *     factory.addFactory(::RTC::MyLocalSerivce::name,
   *                        ::coil::Creator< ::RTC::LocalServiceBase,
   *                        ::RTC::MyLocalService>,
   *                        ::coil::Destructor< ::RTC::LocalServiceBase,
   *                        ::RTC::MyLocalService>);
   *   }
   * };
   * </pre>
   *
   * @else
   *
   * @endif
   *
   */
  class LocalServiceBase
  {
  public:
    /*!
     * @if jp
     * @brief ���ۥǥ��ȥ饯��
     * @else
     * @brief virtual destructor
     * @endif
     */
    virtual ~LocalServiceBase()
    {
    }
    
    /*!
     * @if jp
     * @brief LocalService���饹�ν�����ؿ�
     *
     * ���Υ��֥������Ȥν������Ԥ���LocalService ����������硢��
     * ��������������ϡ�����init()�ؿ��ˤ��Ϳ�����롣
     *
     * @param profile ��������Ϳ����줿 LocalServiceProfile
     * @return Ϳ����줿 LocalServiceProfile �������ξ�� false
     *
     * @else
     * @brief Initialization function of the LocalService class
     *
     * @endif
     */
    virtual bool
    init(const coil::Properties& props) = 0;
    /*!
     * @if jp
     * @brief LocalService���饹�κƽ�����ؿ�
     *
     * TODO: �ɥ�����Ⱥ���
     *
     * @param profile ������Ϳ����줿 LocalServiceProfile
     * @return ������ LocalServiceProfile ��Ϳ����줿���� false
     *
     * @else
     * @brief Reinitialization function of the LocalService class
     *
     * TODO: Documentation
     *
     * @endif
     */
    virtual bool
    reinit(const coil::Properties& props) = 0;
    
    /*!
     * @if jp
     * @brief LocalServiceProfile ���֤�
     *
     * init()/reinit()��Ϳ����줿 LocalServiceProfile ���̾索�֥�����
     * ������ݻ�����롣���δؿ��Ǥ��ݻ�����Ƥ��� ServiceProfile ����
     * ����
     *
     * @return ���Υ��֥������Ȥ��ݻ����Ƥ��� LocalServiceProfile
     *
     * @else
     * @brief Getting LocalServiceProfile
     *
     * TODO: Documentation
     *
     * @endif
     */
    virtual const LocalServiceProfile&
    getProfile() const = 0;
    
    /*!
     * @if jp
     * @brief ��λ����
     *
     * LocalService ����λ����ݤ˸ƤӽФ���뽪λ�����Ѵؿ�����������
     * �������Ȥ��ݻ�����꥽�������������ʤɤν�����Ԥ���
     *
     * @else
     * @brief Finalization
     *
     * TODO: Documentation
     *
     * @endif
     */
    virtual void
    finalize() = 0;
  };
  
  /*!
   * @if jp
   * @brief LocalServiceFactory �� typedef
   * @else
   * @brief typedef of sdoServiceProviderFactory
   * @endif
   */
  typedef ::coil::GlobalFactory< ::RTM::LocalServiceBase > LocalServiceFactory;
  
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  /*!
   * @if jp
   * @brief ���饹�ƥ�ץ졼�Ȥ�����Ū���󥹥��󥹲�
   * @else
   * @brief Explicit instantiation of class template
   * @endif
   */
  EXTERN template class DLL_PLUGIN
  ::coil::GlobalFactory< ::RTM::LocalServiceBase >;
#endif
}; // namespace RTM

#endif // RTM_LOCALSERVICEBASE_H
