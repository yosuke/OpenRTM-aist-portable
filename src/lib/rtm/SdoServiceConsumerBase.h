// -*- C++ -*-
/*!
 * @file SdoServiceConsumerBase.h
 * @brief SDO service consumer base class and its factory
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


#ifndef RTC_SDOSERVICECONSUMERBASE_H
#define RTC_SDOSERVICECONSUMERBASE_H

#include <coil/Mutex.h>
#include <coil/Factory.h>
#include <coil/Timer.h>
#include <rtm/RTObject.h>
#include <rtm/idl/SDOPackageStub.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @brief SdoServiceConsumer�����쥯�饹
   *
   * SDO���������Ƥ���SDO�����ӥ��Υ��󥷥塼�ޤ�������뤿��δ��쥯
   * �饹��SDO�����ӥ��ˤϡ����������󶡥����ӥ���RTC(SDO)¦�����Ѥ���
   * SDO�����ӥ����󥷥塼�ޤȡ�RTC(SDO)���Ȥ�SDO�����ӥ����󶡤���SDO
   * �����ӥ��ץ�Х��������롣���٤Ƥ�SDO�����ӥ����󥷥塼�ޤϤ��δ�
   * �쥯�饹��Ѿ����Ƽ�������롣
   *
   * ���Υ��֥������ȤΥ饤�ե�������ϰʲ����̤ꡣ
   *
   * -# ���֥������Ȥ��̾��ͭ���֥������� (so, DLL) �Ȥ��ƥ���ѥ��롦
   *    ��󥯤���롣
   * -# �ޥ͡�������Ф��ƥ��ɤ����ȥ⥸�塼�������ؿ��ˤ�ꥪ��
   *    �������ȥե����ȥ꤬��SdoServiceConsumerFactory ���Ф�����Ͽ��
   *    ��롣��Ͽ�Υ����ˤϥ����ӥ����󥿡��ե������� IFR (interface
   *    repository) ID �����Ѥ��졢����ˤ�ꥵ���ӥ������̤���롣
   * -# �����Υġ���ʤɤ��饵���ӥ��ץ�Х����������å����줿��硢����
   *    �ӥ����󥿡��ե������� IFR ID ��Ʊ��Ǥ��� SDO ���󥷥塼�ޤ���
   *    �󥹥��󥹲����졢�󶡤��줿SDO�����ӥ��� ServiceProfile (����
   *    ��¤�Τϥ����ӥ��Υ��֥������ȥ�ե���󥹤�ޤ�) �����󥷥塼
   *    �ޤ˥����å�����롣
   * -# ���ΤȤ��Υ����å��������󥹤ϰʲ����̤ꡣ
   *   -# SDO::get_configuration() �ˤ�� Configuration ���֥������Ȥ����
   *   -# Configuration::add_service_profile() �ˤ�곰��¦��
   *      SdoServiceProvider �� ServiceProfile �ˤ�� RTC ��Ϳ���롣
   *   -# RTC¦�ǥ����ӥ���ƤӽФ�ɬ�פ�ͭ�ä���硢����
   *      SdoServiceConsumer ���ݻ����Ƥ��륵���ӥ����֥������ȥץ���
   *      ���Ф��ƸƤӽФ���Ԥ�
   * -# �ǽ�Ū�� SdoServiceConsumer �����פˤʤä����ˤϡ�
   *     Configuration::remove_service_profile() �� id �ȤȤ�˸ƤӽФ���
   *     SDO�����ӥ����󥷥塼�ޤ� RTC ����������롣
   *
   * <pre>
   * 
   *   [RTC] [SDO consumer] [Configuration]  [SDO service]    [Other]
   *     |          :             |                 |            |
   *     |          :         get_configuration()   |            |
   *     |<---------:-------------------------------|------------|
   *     |          :             |                 |            |
   *     |          :             |   add_service_profile(prof)  |
   *     |          :  create()   |<----------------|------------|
   *     |          |<------------|                 |            |
   *     |          |         call_sdo_service()    |            |
   *     |          |-------------|---------------->|            |
   *     |          |         call_sdo_service2()   |            |
   *     |          |-------------|---------------->|            |
   *     |          |             |       :         |            |
   *     |          |             |                 |            |
   *     |          |             | remove_service_profile(id)   |
   *     |          |  delete()   |<----------------|------------|
   *     |          x<------------|                 |            |
   *     |                        |                 x            x
   *
   * </pre>
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
   * SdoServiceConsumer ���̾ﶦͭ���֥������ȤȤ��ƥ���ѥ��롦���
   * ����롣��ͭ���֥������ȤΥ���ȥ�ݥ���Ȥ��̾拾��ѥ��뤵�줿�ե�
   * ����̾�� basename + "Init" �ˤ��Ƥ������ʲ��ˡ����饹̾���ե�����
   * ̾������ȥ�ݥ���ȴؿ�̾�ο侩��򼨤���
   *
   * - �������饹̾: MySdoServiceConusmer 
   * - �ե�����̾: MySdoServiceConsumer.h. MySdoServiceConsumer.cpp
   * - ��ͭ���֥�������̾: MySdoServiceConsumer.so (or DLL)
   * - ����ȥ�ݥ���ȴؿ�̾: MySdoServiceConsumerInit()
   *
   * ����ȥ�ݥ���ȴؿ����̾�ʲ��Τ褦�ˡ�SdoServiceConsumerFactory
   * ���������󥷥塼�ޤΥե����ȥ� (�Ȳ��Υե��󥯥�) ����Ͽ����ʲ���
   * �褦�ʴؿ��ˤʤ롣
   *
   * <pre>
   * extern "C"
   * {
   *   void MySdoServiceConsumerInit()
   *   {
   *     RTC::SdoServiceConsumerFactory& factory
   *       = RTC::SdoServiceConsumerFactory::instance();
   *     factory.addFactory(CORBA_Util::toRepositoryId<OpenRTM::MySdoService>(),
   *                        ::coil::Creator< ::RTC::SdoServiceConsumerBase,
   *                        ::RTC::MySdoServiceConsumer>,
   *                        ::coil::Destructor< ::RTC::SdoServiceConsumerBase,
   *                        ::RTC::MySdoServiceConsumer>);
   *   }
   * };
   * </pre>
   * 
   * @else
   *
   * @endif
   *
   */
  class SdoServiceConsumerBase
  {
  public:
    /*!
     * @if jp
     * @brief ���ۥǥ��ȥ饯��
     * @else
     * @brief virtual destructor
     * @endif
     */
    virtual ~SdoServiceConsumerBase() {};

    /*!
     * @if jp
     * @brief ���󥷥塼�ޥ��饹�ν�����ؿ�
     *
     * ���Υ��֥������Ȥν������Ԥ�����������SDO�����ӥ���
     * ServiceProfile �ȤȤ�˥����å������ȡ�SDO���󥷥塼�ޤ�����
     * ���󥹲����졢����ľ��� SDO �����ӥ��������å����줿 RTC ��Ϳ��
     * ��줿 ServiceProfile ������Ȥ��Ƥ��δؿ����ƤФ�롣
     *
     * �ؿ���Ǥϡ�ServiceProfile ��� SDO �����ӥ���ե���󥹤�
     * CorbaConsumer ���饹�������Ѥ����֥�����������ݻ�����ȤȤ�ˡ�
     * properties �����������Ƥ��ɤ߹��ߥ����ӥ���ͭ����������Ԥ���Ϳ
     * ����줿�����ӥ��Υ��֥������ȥ�ե���󥹤����������뤤��
     * properties �����Ƥ����������ξ�������ͤ� false ���֤���
     *
     * @param rtobj ���Υ��֥������Ȥ����󥹥��󥹲����줿 RTC
     * @param profile ��������Ϳ����줿 SDO ServiceProfile
     * @return Ϳ����줿 SDO Service �� ServiceProfile �������ξ�� false
     *
     * @else
     * @brief Initialization function of the consumer class
     *
     * @endif
     */
    virtual bool init(RTObject_impl& rtobj,
                      const SDOPackage::ServiceProfile& profile) = 0;
    /*!
     * @if jp
     * @brief ���󥷥塼�ޥ��饹�κƽ�����ؿ�
     *
     * ���Υ��֥������Ȥκƽ������Ԥ���ServiceProfile �ˤ� id �ե���
     * ��ɤ˥��å�����ͭ�� UUID �����åȤ���Ƥ��뤬��Ʊ��� id �ξ�
     * �硢properties �����ꤵ�줿���������ѹ��䡢service �ե������
     * �Υ����ӥ��λ��Ȥ��ѹ����Ԥ��롣���κݤ˸ƤФ��Τ�����
     * reinit() �ؿ��Ǥ��롣�����Ǥϡ�service �ե�����ɤΥ��֥�������
     * ��ե���󥹤�Ʊ�������ǧ�����ۤʤäƤ������ݻ����Ƥ����ե�
     * ��󥹤򹹿�����ɬ�פ����롣�ޤ� properties �ˤϿ��������꤬Ϳ��
     * ���Ƥ����ǽ��������Τǡ����Ƥ��ɤ߹�������򹹿����롣
     *
     * @param profile ������Ϳ����줿 SDO ServiceProfile
     * @return ������ ServiceProfile ��Ϳ����줿���� false
     *
     * @else
     * @brief Reinitialization function of the consumer class
     *
     * @endif
     */
    virtual bool reinit(const SDOPackage::ServiceProfile& profile) = 0;

    /*!
     * @if jp
     * @brief ServiceProfile ���֤�
     *
     * init()/reinit()��Ϳ����줿 ServiceProfile ���̾索�֥���������
     * ���ݻ�����롣SDO Service �����ե졼�����ϴ����夳�Υ��֥���
     * ���Ȥ��б����� ServiceProfile ��ɬ�פȤ���Τǡ����δؿ��Ǥ��ݻ�
     * ����Ƥ��� ServiceProfile ���֤���
     * 
     * @return ���Υ��֥������Ȥ��ݻ����Ƥ��� ServiceProfile
     *
     * @else
     * @brief Getting ServiceProfile
     * @endif
     */
    virtual const SDOPackage::ServiceProfile& getProfile() const = 0;

    /*!
     * @if jp
     * @brief ��λ����
     *
     * SDO�����ӥ����ǥ��å������ݤ˸ƤӽФ���뽪λ�����Ѵؿ�������
     * �ӥ��Τǥ��å��˺ݤ��ơ��������֥������Ȥ��ݻ�����꥽���������
     * ����ʤɤν�����Ԥ���
     *
     * @else
     * @brief Finalization
     *
     * @endif
     */
    virtual void finalize() = 0;
  };

    /*!
     * @if jp
     * @brief SdoServiceConsumerFactory �� typedef
     * @else
     * @brief typedef of sdoServiceConsumerFactory
     * @endif
     */
  typedef ::coil::GlobalFactory<
    ::RTC::SdoServiceConsumerBase > SdoServiceConsumerFactory;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    /*!
     * @if jp
     * @brief ���饹�ƥ�ץ졼�Ȥ�����Ū���󥹥��󥹲�
     * @else
     * @brief Explicit instantiation of class template
     * @endif
     */
  EXTERN template class DLL_PLUGIN 
                     ::coil::GlobalFactory< ::RTC::SdoServiceConsumerBase >;
#endif  
}; // namespace RTC

#endif // RTC_SDOSERVICECONSUMERBASE_H
