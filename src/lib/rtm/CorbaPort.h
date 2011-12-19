// -*- C++ -*-
/*!
 * @file  CorbaPort.h
 * @brief CorbaPort class
 * @date  $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2010
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: CorbaPort.h 2034 2011-01-25 06:33:21Z harumi $
 *
 */

#ifndef RTC_CORBAPORT_H
#define RTC_CORBAPORT_H

#include <rtm/PortBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/NVUtil.h>
#include <list>

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
namespace RTC
{
  /*!
   * @if jp
   * @class CorbaPort
   * @brief RT ����ݡ��ͥ�� CORBA provider/consumer �� Port
   *
   * CorbaPort �� RT ����ݡ��ͥ�Ȥˤ����ơ��桼������� CORBA ���֥���
   * ���ȥ����ӥ�����ӥ��󥷥塼�ޤ��󶡤��� Port �����Ǥ��롣
   *
   * RT ����ݡ��ͥ�Ȥϡ�Port ��𤷤ƥ桼����������� CORBA �����ӥ�
   * ���󶡤��뤳�Ȥ��Ǥ�������� RT Service (Provider) �ȸƤ֡��ޤ���
   * ¾�� RT ����ݡ��ͥ�ȤΥ����ӥ������Ѥ��뤿��� CORBA ���֥�����
   * �ȤΥץ졼���ۥ�����󶡤��뤳�Ȥ��Ǥ�������� RT Service
   * Consumer �ȸƤ֡�
   * CorbaPort ��Ǥ�դο��� Provider ����� Consumer ��������뤳�Ȥ���
   * ����Port Ʊ�Τ���³����ݤ��б����� Provider �� Consumer ��Ŭ�ڤ�
   * ��Ϣ�դ��뤳�Ȥ��Ǥ��롣
   * CorbaPort ���̾�ʲ��Τ褦�����Ѥ���롣
   *
   * <pre>
   * RTC::CorbaPort m_port0; // Port �����
   *
   * MyService_impl m_mysvc0; // ���� Port ���󶡤��� Serivce Provider
   * RTC::CorbaConsumer<YourService> m_cons0; // ���� Port �� Consumer
   *
   * // Service Provider �� Port ����Ͽ
   * m_port0.registerProvider("MyService0", "Generic", m_mysvc0);
   * // Service Consumer �� Port ����Ͽ
   * m_port0.registerConsumer("YourService0", "Generic", m_cons0 );
   *
   * // connect ���Ԥ�줿��
   *
   * m_cons0->your_service_function(); // YourService �δؿ��򥳡���
   *
   * // connect ���줿 �̤Υ���ݡ��ͥ�Ȥˤ�����
   * m_cons1->my_service_function(); // MyService �δؿ��򥳡���
   * </pre>
   *
   * ���Τ褦�ˡ��󶡤����� Service Provider �� registerProvider() ����
   * Ͽ���뤳�Ȥˤ�ꡢ¾�Υ���ݡ��ͥ�Ȥ������Ѳ�ǽ�ˤ���¾�������Ѥ�
   * ���� Service Consumer �� registerConsumer() ����Ͽ���뤳�Ȥˤ��¾
   * �Υ���ݡ��ͥ�Ȥ� Service �򥳥�ݡ��ͥ��������Ѳ�ǽ�ˤ��뤳��
   * ���Ǥ��롣
   *
   * PortInterfaceProfile �� Port �˽�°����ץ�Х����⤷���ϥ��󥷥塼
   * �ޥ��󥿡��ե������ˤĤ��Ƥξ���򵭽Ҥ��뤿��Υץ�ե�����Ǥ��롣
   * ��³��Ԥ��ġ������ϡ������ξ���˴�Ť� ConnectorProfile ��Ŭ��
   * ������������³�������� Port �Τ���Ǥ�դΰ�Ĥ��Ф��ư�����
   * ConnectorProfile ��Ϳ���� Port::connect() ��ƤӽФ�ɬ�פ����롣
   *
   * �ʤ���PortInterfaceProfile �Υ��󥹥���̾ "*" ���ü�ʥ��󥹥���
   * ����ɽ����
   *
   * PROVIDED���ʤ���ץ�Х����Υ��󥹥���̾�� "*" �ξ��ϡ���³��
   * �ϻ����Ǥϥ��󥹥��󥹤�¸�ߤ��������󥷥塼�ޤ��׵�˱�����ưŪ��
   * ���󥹥��󥹤��������륿���פΥץ�Х����Ǥ��뤳�Ȥ�ɽ������������
   * �ơ���³���ϻ����Ǥϥ��󥹥���̾��¸�ߤ��ʤ�������³����������
   * �Υ��󥿡��ե��������������ץ����ˤ����ơ��ץ�Х�������������
   * ���󥹥��󥹤��б��������һҤ� ConnectorProfile ��Ŭ�������ꤹ���
   * �ΤȤ��롣(̤����)
   *
   * REQUIRED���ʤ�����󥷥塼�ޤΥ��󥹥���̾�� "*" �ξ��ϡ����
   * �Υ��󥷥塼�ޤ�ʣ���Υץ�Х�������³��ǽ�ʥ����פΥ��󥷥塼�ޤ�
   * ���뤳�Ȥ򼨤���(̤����)
   *
   * �ʲ��ϡ�Port�֤Υ��󥿡��ե���������³���뤿��� ConnectorProfile ��
   * �ޥåԥ󥰤򵭽Ҥ��뤿��Υ롼��򼨤���
   *
   * Port����°���륤�󥿡��ե������λ���ҤΥե����ޥåȤ�ʲ��Τ褦��
   * ���롣���󥿡��ե������˴ؤ���ץ�ѥƥ����ʲ��ξ��
   *
   * - RTC���󥹥���̾:              rtc_iname
   * - �ݡ���̾:                       port_name
   * - ���󥿡��ե���������:           if_polarity
   * - ���󥿡��ե�������̾:           if_tname
   * - ���󥿡��ե��������󥹥���̾: if_iname
   * 
   * ���󥿡��ե������λ���Ҥ�ʲ���ʸ����̾�Τǻ��ꤹ���ΤȤ��롣
   *
   * <rtc_iname>.port.<port_name>.<if_polarity>.<if_tname>.<if_iname>
   *
   * PROVIDED(��)�����ʤ���ץ�Х����Υ��󥿥ե������Υץ�ѥƥ�����
   * ���ξ�硢
   *
   * - rtc_iname   = MyComp0
   * - port_name   = myservice
   * - if_polarity = provided
   * - if_tname    = echo_interface
   * - if_iname    = echo_interface2
   *
   * ���󥿡��ե���������Ҥ�
   *
   * MyComp0.port.myservice.provided.echo_interface.echo_interface2
   *
   * �Τ褦�˵��Ҥ���롣�ޤ���Ʊ�ͤ�REQUIRED(�׵�)�����ʤ�����󥷥塼
   * �ޤΥ��󥿡��ե������Υץ�ѥƥ����ʲ��ξ�硢
   *
   * - rtc_iname   = YourComp0
   * - port_name   = yourservice
   * - if_polarity = required
   * - if_tname    = hoge_interface
   * - if_iname    = hoge_interface1
   *
   * ���󥿡��ե���������Ҥϡ�
   * 
   * YourComp0.port.myservice.required.hoge_interface.hoge_inteface1
   *
   * �Τ褦�˵��Ҥ��뤳�Ȥ��Ǥ��롣
   * 
   * �ʤ���������ưŪ�������󥿡��ե������Υ��󥹥��󥹤Τ�����ü�ʥ�
   * ���פΥ��󥹥���̾���һ�
   *
   * - <type_name>*: ưŪ���������󥹥���̾���һ�
   * - <type_name>+: ���󥯥��󥿥����������󥹥���̾���һ�
   *
   * ��������롣ưŪ�������󥿡��ե������Ȥϡ���³���˥��󥹥��󥹤���
   * ������륿���פΥ��󥿡��ե������Ǥ��롣(̤����)
   *
   * ���󥷥塼�ޤ��׵᤹��ץ�Х������󥿡��ե��������һҤ�ưŪ������
   * ���󥹥���̾���һ� "<type_name>*" �����ꤵ�줿��硢�ץ�Х�����
   * ���󥹥��󥹤�1�Ŀ������������롣"<type_name>*" �ε��һҤˤ��ץ��
   * �������׵᤹�� n �ĤΥ��󥷥塼�ޤ�¸�ߤ����硢����餫����׵�
   * (���ڥ졼����󥳡���)��1 �ĤΥץ�Х����ˤ���������ط����ۤ�
   * ��(����)��
   *
   * <pre>
   * consumer0 ]---<
   * consumer1 ]---<  O----[ provider0
   * consumer2 ]---<
   * </pre>
   *  
   * ������Ф������󥷥塼�ޤ��׵᤹��ץ�Х������󥿡��ե��������һ�
   * �˥��󥯥��󥿥����������󥹥���̾���һ� "<type_name>+" ������
   * ���줿��硢���һ� "<type_name>+" �ο������ץ�Х����Υ��󥹥���
   * ����ưŪ����������롣���ʤ����"<type_name>+" �ε��һҤˤ��ץ��
   * �������׵᤹�� n �ĤΥ��󥷥塼�ޤ�¸�ߤ����硢n �ĤΥץ�Х���
   * �����줾����׵���������ʲ��Τ褦�ʴط������ۤ���롣
   *
   * <pre>
   * consumer0 ]---<  O----[ provider0
   * consumer1 ]---<  O----[ provider1
   * consumer2 ]---<  O----[ provider2
   * </pre>
   *
   *
   * ��³�˺ݤ��ơ��ġ��������� ConnectorProfile::properties ��Ŭ�ڤʥ�
   * �󥿡��ե������ޥåԥ󥰻���򵭽Ҥ��뤳�Ȥǡ���ߤΥץ�Х���/��
   * �󥷥塼�ޥ��󥿡��ե�������ͳ����³���뤳�Ȥ��Ǥ��롣����������
   * ³�˴ؤ�� RTC ����ˡ��ۤʤ륤�󥹥��󥹤Ǥ���ʤ��顢Ʊ��Υ���
   * ����̾��¸�ߤ����硢���󥿡��ե��������һҤΰ�������ݾڤǤ���
   * ���Τǡ�������ˡ�ˤ����³�����ݾڤ���ʤ���
   *
   * �����ǥ��󥿡��ե��������һҤ��ñ�Τ���� <if_desc0>,
   * <if_desc1>, ...  �Ȥ��롣�ޤ���ConnectorProfile::properties ��
   * NVList�� key �� value �� key: value �Τ褦�˵��Ҥ����ΤȤ��롣
   *
   * ���ޡ�2�ĤΥ���ݡ��ͥ�ȤΥ����ӥ��ݡ��Ȥ���³�������ͤ��롣
   * ���줾��Υ���ݡ��ͥ�ȤΥ����ӥ��ݡ��Ȥ��ʲ��ξ�硢
   *
   * - rtc_iname: MyComp0        <br>
   *   port_name: mycomp_service <br>
   *   interfaces:
   *   - if_polarity: provided   <br>
   *     if_iname: echo0         <br>
   *     if_tname: Echo
   *   - if_polarity: required   <br>
   *     if_iname: add0          <br>
   *     if_tname: add
   *
   * - rtc_iname: YourComp0        <br>
   *   port_name: yourcomp_service <br>
   *   interfaces:
   *   - if_polarity: required     <br>
   *     if_iname: echo9           <br>
   *     if_tname: Echo
   *   - if_polarity: provided     <br>
   *     if_iname: add9            <br>
   *     if_tname: add
   *
   * <pre>
   *      MyComp0                                 YourComp0
   *     _______ mycomp_service   yourcomp_service ______
   *            |                                 |
   *          |~~~|---O echo0         echo9 >---|~~~|
   *          |   |---< add0          add9  O---|   |
   *           ~T~                               ~T~
   *            |                                 |
   * </pre>
   *
   * MyComp0 �� echo0 (�ץ�Х���) �� YourComp0 �� echo9 (���󥷥塼��)��
   * MyComp0 �� add0 (���󥷥塼��) �� YourComp0 �� echo9 (�ץ�Х���)
   * �򤽤줾���Фˤ�����³�������ΤȲ��ꤹ�롣���ξ�硢
   * ConnectorProfile �ϰʲ��Τ褦�����ꤹ�롣
   * 
   * <pre>
   * ConnectorProfile:
   *   name: Ǥ�դΥ��ͥ���̾
   *   connector_id: ��ʸ��
   *   ports[]: mycomp_service �λ���, yourcomp_service �λ���
   *   properties:
   *     <add0>: <add9>
   *     <echo9>: <echo0>
   * </pre>
   *
   * �����������줾��
   * 
   * <pre>
   * <add0> �� MyComp0.port.mycomp_service.required.add.add0
   * <add9> �� YourComp0.port.yourcomp_service.provided.add.add9
   * <echo0> �� MyComp0.port.mycomp_service.provided.echo.echo0
   * <echo9> �� YourComp0.port.yourcomp_service.required.echo.echo9
   * </pre>
   *
   * �Ǥ��롣��³�ץ����ˤ����ơ��ƥݡ��ȤΥץ�Х�������ӥ��󥷥塼
   * �ޤϡ����줾��ʲ��κ�Ȥ�CorbaPort::publishInterfaces(),
   * CorbaPort::PortsubscribeInterfaces() ���۴ؿ��ˤ����ƹԤ���
   *
   * �ץ�Х����ϡ�publishInterfaces() �ؿ��ˤ����ơ���ʬ�Υ��󥿡��ե���
   * �����һҤ򥭡��Ȥ����ͤ�IOR��ʸ����ɽ��������Τ�
   * ConnectorProfile::properties �����ꤹ�롣����Ȥ��ơ����Υ��󥿡�
   * �ե��������һҤϺ��Ԥ����Ȥ��Ƥ��륳�ͥ����ˤ����Ƥϰ�դǤ��뤿�ᡢ
   * Ʊ��������1�Ĥ���¸�ߤ��ƤϤ����ʤ���
   *
   * [������ʬ�ε��Ҥ�̤�����ε�ǽ] �ʤ���ưŪ�������󥿡��ե������ˤ�
   * ���Ƥϡ��ʲ��μ�³���˽����������뤳�ȤȤʤ롣publishInterface()
   * �ؿ��ˤ����ơ�ưŪ�������󥹥���̾���һ� "<type_name>*" �ޤ��ϡ�
   * ���󥯥��󥿥����������󥹥���̾���һ� "<type_name>+" ��¸�ߤ�
   * �뤫�ɤ������������롣ưŪ�������󥹥���̾���һ� "<type_name>*"
   * ��¸�ߤ����硢�ץ�Х����Υ��󥹥��󥹤�1�������������Υ��󥿡�
   * �ե���������Ҥ� key �ˡ�IORʸ����� value �����ꤹ��ȤȤ�ˡ�ư
   * Ū�������󥹥���̾���һ� "<type_name>*" �� value �˴ޤह�٤Ƥ�
   * value ��Υ��󥿡��ե���������Ҥ򡢤����������������󥿡��ե�����
   * ����Ҥ��֤������롣
   * 
   * ���󥯥��󥿥����������󥹥���̾���һ�"<type_name>+" ��¸�ߤ�
   * ���硢���󥹥���̾���һҤο������ץ�Х����Υ��󥹥��󥹤�����
   * �������줾��Υ��󥿡��ե���������Ҥ�key �ˡ�IORʸ����� value ��
   * ���ꤹ��ȤȤ�ˡ����󥯥��󥿥����������󥹥���̾���һ�
   * "<type_name>+" �� value �ޤह�٤Ƥ� value ��Υ��󥿡��ե�������
   * ��Ҥ��Ф��ƽ�ˡ������������������줾��Υ��󥿡��ե���������Ҥ�
   * �֤������롣
   *
   * �ץ�Х����� subscribeInterfaces() �Ǥ��ä����ϹԤ�ʤ���
   *
   * ���󥷥塼�ޤϡ� publishInterfaces() �ˤ����Ƥ��ä�����Ԥ�ʤ���
   *
   * ������ subscribeInterfaces() �Ǥϡ���ʬ�ε��һҤ� key �Ȥ���
   * key-value �ڥ� ��¸�ߤ��뤫�ɤ���Ĵ�١��⤷¸�ߤ���С����� value
   * �����ꤵ�줿�ץ�Х����Υ��󥿡��ե���������Ҥǻ��ꤵ��뻲�Ȥ�
   * ����� ConnectorProfile::properties ����õ��������򥳥󥷥塼�ޤ�
   * ��³��Ȥ������ꤹ�롣�ʤ����տ�Ū�˥��󥷥塼�ޤ˥ץ�Х����λ���
   * �����ꤷ�ʤ����ϡ�ͽ��ʸ���� "nil" �ޤ��� "null" �����ꤹ����
   * �Ȥ��롣
   *
   * ���󥷥塼�ޤϡ��⤷��ʬ�ε��һҤ�¸�ߤ��ʤ���硢�ޤ��ϥץ�Х���
   * �λ��Ȥ� Connector::properties ��¸�ߤ��ʤ���硢���󥷥塼�ޤϡ�
   * ��ʬ�Υ��󥹥���̾����ӷ�̾��Ʊ��Υץ�Х�����õ�������λ��Ȥ�
   * ��ʬ���Ȥ����ꤹ�롣����ϡ�OpenRTM-aist-0.4 �Ȥθߴ������ݻ�����
   * ����Υ롼��Ǥ��ꡢ1.0�ʹߤǤϿ侩����ʤ���
   *
   * �ץ�Х����Х��󥷥塼�ޤ��б��ϰ��а�Ǥ���ɬ�פϤʤ����ץ�Х���
   * 1 ���Ф��ơ����󥷥塼�� n���ޤ��ϥ��󥷥塼�� 1 ���Ф��ƥץ�Х�
   * �� n �Υ������������롣�ץ�Х��� 1 ���Ф��ơ����󥷥塼�� n ��
   * �������Ǥϡ�����ץ�Х����λ���Ҥ���ʣ���Υ��󥷥塼�ޤ��Ф��ơ�
   * �嵭����ˡ�ǻ��ꤵ��뤳�Ȥˤ�ꡢ�¸�����롣���������󥷥塼��
   * 1 ���Ф��ƥץ�Х��� n �Υ������Ǥϡ����󥷥塼�޻���Ҥ� key ����
   * ���ơ�ʣ���Υץ�Х����λ���Ҥ�����޶��ڤ����󤵤������Ȥʤ�
   * ��ΤȤ��롣
   *
   * �ʤ������󥿡��ե��������б��ط��θ�̩������ꤹ�륪�ץ����Ȥ��ơ�
   * �ʲ��Υ��ץ�������ꤹ�뤳�Ȥ��Ǥ��롣
   *
   * port.connection.strictness: strict, best_effort 
   *
   * strict: ���٤ƤΥ��󥷥塼�ޤ˻��ꤷ�����Ȥ�¸�ߤ������ĥʥ�����
   *         ���ˤ����������󥷥塼�ޤ�Ŭ�ڤ˥��åȤǤ������ˤΤ� Port
   *         �֤���³���Ω���롣
   *
   * best_effort: �ʥ��������˼��Ԥ������Ǥ⡢���顼���֤����Ȥ�
   *         �� Port �֤���³���Ω���롣
   *
   * @since 0.4.0
   *
   * @else
   * @class CorbaPort
   * @brief RT Conponent CORBA service/consumer Port
   *
   * CorbaPort is an implementation of the Port of RT-Component's that provides
   * user-defined CORBA Object Service and Consumer.
   * <p>
   * RT-Component can provide user-defined CORBA serivces, which is called
   * RT-Serivce (Provider), through the Ports.
   * RT-Component can also provide place-holder, which is called RT-Serivce
   * Consumer, to use other RT-Component's service.
   * <p>
   * The CorbaPort can manage any number of Providers and Consumers, can
   * associate Consumers with correspondent Providers when establishing
   * connection among Ports.
   * <p>
   * Usually, CorbaPort is used like the following.
   *
   * <pre>
   * RTC::CorbaPort m_port0; // declaration of Port
   *
   * MyService_impl m_mysvc0; // Serivce Provider that is provided by the Port
   * RTC::CorbaConsumer<YourService> m_cons0; // Consumer of the Port
   *
   * // register Service Provider to the Port
   * m_port0.registerProvider("MyService0", "Generic", m_mysvc0);
   * // register Service Consumer to the Port
   * m_port0.registerConsumer("YourService0", "Generic", m_cons0 );
   *
   * // after connect established
   *
   * m_cons0->your_service_function(); // call a YourService's function
   *
   * // in another component that is connected with the Port
   * m_cons1->my_service_function(); // call a MyService's function
   * </pre>
   *
   * Registering Service Provider by registerProvider(), it can be
   * used from other RT-Components.  Registering Service Consumer by
   * registerConsumer(), other RT-Component's services can be used
   * through the consumer object.
   *
   * PortInterfaceProfile is a one of the profile information to store
   * Provider interface and Consumer interface information. Tools or
   * other RTCs should call one of the Port::connect() with an
   * appropriate ConnectorProfile.
   *
   * In addition, the instance name "*" declares a special type of instance.
   *
   * When the name of the PROVIDED type interface that is the provider
   * interface is "*", Provider interface's instance does not exist at
   * the beginning of connection sequence.  The instances will be
   * created dynamically according to the consumer interface
   * requirement at the connection sequence.  Although the instance
   * name does not exist at the beginning of connection sequence, the
   * created providers shall publish its references to the
   * ConnectorProfile with interface descriptor adequately in the
   * interface publisher phase of the connection sequence.
   *
   * If REQUIRED interface name that is Consumer interface name is
   * "*", it shows that one Consumer interface is able to connect with
   * multiple Provider interfaces. (This feature is not implemented.)
   * 
   * The following describes the rules that specify interface
   * connection between ports.
   *
   * The descriptor format of interfaces associated with Ports is
   * declared as follows. Now some of interface properties are assumed
   * as the followings.
   *
   * - RTC instance name:              rtc_iname
   * - Port name:                      port_name
   * - Interface polarity:             if_polarity
   * - Interface type name:            if_tname
   * - INterface instance name:        if_iname
   *
   * The interface descriptors shall be declared as follows.
   *
   * <rtc_iname>.port.<port_name>.<if_polarity>.<if_tname>.<if_iname>
   *
   * When PROVIDED that is Provider interface properties are the followings,
   *
   * - rtc_iname   = MyComp0
   * - port_name   = myservice
   * - if_polarity = provided
   * - if_tname    = echo_interface
   * - if_iname    = echo_interface2
   * the interface descriptor is here.
   *
   * MyComp0.port.myservice.provided.echo_interface.echo_interface2
   *
   * And, when REQUIRED that is Consumer interfaces properties are the
   * followings,
   *
   * - rtc_iname   = YourComp0
   * - port_name   = yourservice
   * - if_polarity = required
   * - if_tname    = hoge_interface
   * - if_iname    = hoge_interface1
   *
   * interface descriptor is as follows. 
   *
   * YourComp0.port.myservice.required.hoge_interface.hoge_inteface1
   *
   * Specific instance name descriptors that are dynamically generated
   * at the connection time are defined here.
   *
   * - <type_name>*: "Dynamically generated" instance descriptor.
   * - <type_name>+: "Incrementally generated" instance descriptor.
   *
   * When the "Dynamically generated" instance descriptor:
   * "<type_name>*" is specified as interface descriptor that is
   * required by consumers, the provider will generate a instance. If
   * n consumers who demand a provider by the "<type_name>" descriptor
   * exist, the following relation which processes the call from these
   * consumers by one provider will be established.
   *
   * <pre>
   * consumer0 ]---<
   * consumer1 ]---<  O----[ provider0
   * consumer2 ]---<
   * </pre>
   *  
   * On the other hand, when incremental generated type instance name
   * descriptor "<type_name>+" is specified as the provider interface
   * descriptor whom consumers demand, provider's instances are
   * dynamically generated for the number of the descriptors
   * "<type_name>+". When n consumers who demand a provider by the
   * descriptor "<type_name>+" exist the following relations in which
   * n providers process each call from the consumers will be
   * established.
   *
   * <pre>
   * consumer0 ]---<  O----[ provider0
   * consumer1 ]---<  O----[ provider1
   * consumer2 ]---<  O----[ provider2
   * </pre>
   *
   *
   * Describing the appropriate interface mapping specification in the
   * ConnectorProfile::properties, selective connections between
   * providers/consumers interface can be established at the time of
   * connection. However, when different RTC instances of the same
   * instance name exist in a connection, since an interface
   * descriptor uniqueness cannot be guaranteed, this connection
   * mapping rules cannot be used.
   *
   * Here, assume that an interface descriptor is given as <if_desc0>,
   * <if_desc1>, .... And assume that the key and the value of NVList
   * in ConnectorProfile::properties are given as "key: value".
   *
   * Now the case where the service ports of two components are
   * connected is considered. When the service port of each component
   * is the following,
   * 
   * - rtc_iname: MyComp0          <br>
   *   port_name: mycomp_service   <br>
   *   interfaces:
   *   - if_polarity: provided     <br>
   *     if_iname: echo0           <br>
   *     if_tname: Echo
   *   - if_polarity: required     <br>
   *     if_iname: add0            <br>
   *     if_tname: add
   *
   * - rtc_iname: YourComp0        <br>
   *   port_name: yourcomp_service <br>
   *   interfaces:
   *   - if_polarity: required     <br>
   *     if_iname: echo9           <br>
   *     if_tname: Echo
   *   - if_polarity: provided     <br>
   *     if_iname: add9            <br>
   *     if_tname: add
   *
   *
   * <pre>
   *      MyComp0                                 YourComp0
   *     _______ mycomp_service   yourcomp_service ______
   *            |                                 |
   *          |~~~|---O echo0         echo9 >---|~~~|
   *          |   |---< add0          add9  O---|   |
   *           ~T~                               ~T~
   *            |                                 |
   * </pre>
   * 
   *
   *
   * Assume that connection between echo0 (provider) of MyComp0
   * component and echo9 (consumer) of YourComp0 component, and add0
   * (consumer) of MyComp0 and add0 (provider) of YourComp0 is
   * established.  In this case, ConnectorProfile is set up as
   * follows.
   * 
   * <pre>
   * ConnectorProfile:
   *   name: any connector name
   *   connector_id: empty string
   *   ports[]: mycomp_service's reference, yourcomp_service's reference
   *   properties:
   *     <add0>: <add9>
   *     <echo9>: <echo0>
   * </pre>
   *
   * Please note that <add0>, <add9>, <echo0> and <echo9> are the following.
   * 
   * <pre>
   * <add0> is MyComp0.port.mycomp_service.required.add.add0
   * <add9> is YourComp0.port.yourcomp_service.provided.add.add9
   * <echo0> is MyComp0.port.mycomp_service.provided.echo.echo0
   * <echo9> is YourComp0.port.yourcomp_service.required.echo.echo9
   * </pre>
   *
   * In the connection process, the provider and the consumer of each
   * port carries out the following process respectively in the
   * virtual functions such as CorbaPort::publishInterfaces() and
   * CorbaPort::subscribeInerfaces().
   * 
   * A provider sets its IOR string as a value and its interface
   * descriptor as a key in the ConnectorProfile::properties in a
   * publishInterfaces() function. Since this interface descriptor's
   * uniqueness is guaranteed in the current connector, the key of
   * NameValue in the ConnectorProfile::properties is unique.
   *
   *
   * [This functionalities are not implemented] The dynamically
   * generated provider is processed according to the following
   * procedure. The publishInterface() function scans dynamic instance
   * descriptors such as "<type_name>*" and "<type_name>+" in the
   * ConnectorProfile::properties. When the dynamic generation
   * instance descriptor "<tupe_name>*" exists, one instance of
   * provider is generated, and its descriptor and its IOR string are
   * set to ConnectorProfile::properties as the key and the value
   * respectively. Simultaneously, in the
   * ConnectorProfile::properties, all the instance descriptor with
   * the dynamic generation instance name "<type_name>*" will be
   * replaced with newly generated instance descriptor.
   *
   * When the incremental dynamic generation instance descriptor
   * exists, providers are generated for the number of the
   * descriptors, and its descriptor and its IOR string are set to
   * ConnectorProfile::properties as the key and the value
   * respectively. Simultaneously, in the
   * ConnectorProfile::properties, all the instance descriptor with
   * the dynamic generation instance name "<type_name>+" will be
   * replaced with newly generated instance descriptor.
   *
   * The providers do not perform particular operation in
   * subscribeInterfaces() function.
   *
   *
   * The consumers do not perform particular operation in
   * publisherInterfaces() function.
   *
   * On the other hand, a consumer searches a key-value pair with the
   * key of consumer interface descriptor, and if the pair exists, it
   * obtains provider's descriptor from the value. The consumer
   * searches again a key-value pair with the key of provider
   * interface descriptor, and it obtains provider's reference and the
   * reference is set as the consumer's service object. In addition,
   * reserved string "nil" or "null" are used not to set specific
   * provider.
   *
   * If consumer's interface descriptors does not exists in the
   * ConnectorProfile::properties, the consumer searches a provider
   * with same type name and instance name, and its reference is set
   * to the consumer. This rule is for only backward compatibility,
   * and it is not recommended from version 1.0.
   *
   * The correspondence of a provider versus a consumer does not need
   * to be one to one, and the case of one provider to n-consumers and
   * the case of m-providers to one consumer are allowed. The one
   * provider to n-consumers case can be realized by the above
   * mentioned methods. The one consumer to m-provider case can be
   * specified to set the consumer descriptor and comma-separated
   * provider descriptors into the key and the value respectively.
   *
   * The following option is available to specify the strictness of
   * interfaces connection.
   *
   * port.connection.strictness: strict, best_effort
   *
   * strict: The connection is established, if only all the specified
   *         consumers are set appropriate references and narrowed
   *         successfully.  
   *
   * best_effort: The connection is established without any errors,
   *         even if appropriate reference does not exist or reference
   *         narrowing fails.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class CorbaPort
    : public PortBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯���Ǥϡ�������Ϳ����줿̾���� PortBase ���Ф��ƥ���
     * �Ȥ���ȤȤ�ˡ�PortProfile::properties ���Ф���
     *
     * - port.port_type: "CorbaPort"
     *
     * ��ץ�ѥƥ��Ȥ����ɲä��롣
     *
     * @param name Port ��̾��
     *
     * @else
     *
     * @brief Constructor
     *
     * In the ctor, a given name is set into PortBase, and the
     * following property is added to the PortProfile::properties,
     *
     * - port.port_type: "CorbaPort"
     *
     * @param name The name of Port 
     *
     * @endif
     */
    CorbaPort(const char* name);
    
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
    virtual ~CorbaPort(void);
    
    /*!
     * @if jp
     * @brief �ץ�ѥƥ��ν����
     *
     * OutPort�Υץ�ѥƥ����������롣���Υݡ��Ȥؤ���³������ꤹ��
     * �ץ�ѥƥ� "connection_limit" ���ޤޤ졢Ŭ�ڤʿ��ͤ����ꤵ��Ƥ�
     * ���硢������³���Ȥ��Ƥ��ο��ͤ����ꤵ��롣�ץ�ѥƥ������ꤵ
     * ��Ƥ��ʤ���硢�⤷����Ŭ�ڤ��ͤ����ꤵ��Ƥ��ʤ����ˤϡ�����
     * ��³����̵���¤Ȥʤ롣
     *
     * @param prop CorbaPort �Υץ�ѥƥ�
     *
     * @else
     *
     * @brief Initializing properties
     *
     * This operation initializes outport's properties. If a property
     * "connection_limit" is set and appropriate value is set to this
     * property value, the number of maximum connection is set as this
     * value. If the property does not exist or invalid value is set
     * to this property, the maximum number of connection will be set
     * unlimited.
     *
     * @param prop properties of the CorbaPort
     *
     * @endif
     */
    void init(coil::Properties& prop);

    /*!
     * @if jp
     *
     * @brief Provider ����Ͽ����
     *
     * ���� Port �ˤ������󶡤����������Х�Ȥ򤳤� Port ���Ф�����Ͽ��
     * �롣�����Х�Ȥϡ�������Ϳ������ instance_name, type_name ��
     * �����Х�ȼ��ȤΥ��󥹥���̾����ӥ�����̾�Ȥ��ơ������Х�Ȥ�
     * ��Ϣ�դ����롣���δؿ��ˤ�ꡢ�����Х�Ȥ� CorbaPort ��������
     * �������ȤȤ�ˡ�PortInterfaceProfile ��RTC::PROVIDED ���󥿡�
     * �ե������Ȥ�����Ͽ����롣
     *
     * @param instance_name �����Х�ȤΥ��󥹥���̾
     * @param type_name �����Х�ȤΥ�����̾
     * @param provider CORBA �����Х��
     *
     * @return ����Ʊ̾�� instance_name ����Ͽ����Ƥ���� false ���֤���
     *
     * @else
     *
     * @brief Register the provider
     *
     * This operation registers a servant, which is provided in this
     * Port, to the Port. The servant is associated with
     * "instance_name" and "type_name" as the instance name of the
     * servant and as the type name of the servant. A given servant
     * will be stored in the CorbaPort, and this is registered as
     * RTC::PROVIDED interface into the PortInterfaceProfile.
     *
     * @param instance_name Instance name of servant
     * @param type_name Type name of the servant
     * @param provider CORBA servant
     *
     * @return Return false if the same name of instance_name is already 
     *         registered.
     *
     * @endif
     */
    bool registerProvider(const char* instance_name, const char* type_name,
                          PortableServer::RefCountServantBase& provider);
    
    /*!
     * @if jp
     *
     * @brief Consumer ����Ͽ����
     *
     * ���� Port ���׵᤹�륵���ӥ��Υץ졼���ۥ���Ǥ��륳�󥷥塼��
     * (Consumer) ����Ͽ���롣Consumer ����Ϣ�դ����륵���ӥ��Υ���
     * ����̾����ӥ�����̾�Ȥ��ơ������� instance_name, type_name ��
     * ��� Consumer ���Ȥ�Ϳ���뤳�Ȥˤ�ꡢ�����Ǥ���餬��Ϣ�դ����
     * �롣Port �֤���³ (connect) �� �ˤϡ�subscribeInterfaces() �ǽ�
     * �٤��Ƥ���롼��˴�Ť���Provider Interface �λ��Ȥ���ưŪ��
     * Consumer �˥��åȤ���롣
     *
     * @param instance_name Consumer ���׵᤹�륵���ӥ��Υ��󥹥���̾
     * @param type_name Consumer ���׵᤹�륵���ӥ��Υ�����̾
     * @param consumer CORBA �����ӥ����󥷥塼��
     *
     * @return ����Ʊ̾�� instance_name ����Ͽ����Ƥ���� false ���֤���
     *
     * @else
     *
     * @brief Register the consumer
     *
     * This operation registers a consumer, which is a service
     * placeholder this port requires. These are associated internally
     * with specified instance_name, type_name and Consumer itself to
     * the argument as service's instance name and its type name
     * associated with Consumer.  The service Provider interface'
     * references will be set automatically to the Consumer Interface
     * object when connections are established, according to the rules
     * that are described at the subscribeInterface() function's
     * documentation.
     *
     * @param instance_name Instance name of the service Consumer requires
     * @param type_name Type name of the service Consumer requires
     * @param consumer CORBA service consumer
     *
     * @return False would be returned if the same instance_name was registered
     *
     * @endif
     */
    bool registerConsumer(const char* instance_name, const char* type_name,
                          CorbaConsumerBase& consumer);
    
  protected:
    /*!
     * @if jp
     *
     * @brief Provider Interface ������������
     *
     * ���� Port ����ͭ���� Provider ���󥿡��ե������˴ؤ�������
     * ConnectorProfile::properties ��������¾�� Port ���Ф��Ƹ������롣
     * ����RTC�Υ��󥹥���̾���ξ��󤬰ʲ����̤�Ǥ���Ȥ��ơ�
     *
     * - RTC���󥹥���̾:              rtc_iname
     * - �ݡ���̾:                       port_name
     * - ���󥿡��ե���������:           if_polarity
     * - ���󥿡��ե�������̾:           if_tname
     * - ���󥿡��ե��������󥹥���̾: if_iname
     *
     * NameValue ���� ConnectorProfile::properties �� name �� value �Ȥ���
     * �ʲ��Τ�Τ���Ǽ����롣
     *
     * - name
     *   <rtc_iname>.port.<port_name>.provided.<if_tname>.<if_iname>
     * - value
     *   Provider ���󥿡��ե������� IOR ʸ���� 
     * 
     * �ʤ�����С������Ȥθߴ����Τ���ʲ���ɽ���� NameValue ��Ʊ��
     * �˳�Ǽ����뤬������ΥС������ǤϺ��������ǽ�������롣
     * 
     * - name
     *   port.<if_tname>.<if_iname>
     * - value
     *   Provider ���󥿡��ե������� IOR ʸ����
     *
     * �������ͤ� ConnectorProfile::properties �˳�Ǽ���졢¾�Υݡ��Ȥ��Ф���
     * ��ã����롣¾�� Port �Ǥ��Υ��󥿡��ե���������Ѥ��� Consumer ��
     * ¸�ߤ���С�ConnectorProfile ���餳�Υ������饪�֥������ȥ�ե���󥹤�
     * ���������餫�η��ǻ��Ѥ���롣
     *
     * @param connector_profile ���ͥ����ץ�ե�����
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Publish information about interfaces
     *
     * This operation publishes Provider interfaces information, which
     * is owned by this port, to the other Ports via
     * ConnectorProfile::properties.
     * Now it is assumed RTC instance name and other information is as follows,
     *
     * - RTC instance name:              rtc_iname
     * - Port name:                      port_name
     * - Interface polarity:             if_polarity
     * - Interface type name:            if_tname
     * - Interface instance name:        if_iname
     *
     * the following values are stored as the "name" and the "value"
     * of the NameValue typee element in ConnectorProfile::properties.
     *
     * - name
     *   <rtc_iname>.port.<port_name>.provided.<if_tname>.<if_iname>
     * - value
     *   IOR string value of interface reference
     * 
     * In addition, although the following NameValue values are also
     * stored for the backward compatibility, this will be deleted in
     * the future version.
     *
     * - name
     *   port.<if_tname>.<if_iname>
     * - value
     *   IOR string value of interface reference
     *
     * These values are stored in the ConnectorProfile::properties and
     * are propagated to the other Ports. If the Consumer interface
     * exists that requires this Provider interface, it will retrieve
     * reference from the ConnectorProfile and utilize it.
     *
     * @param connector_profile Connector profile
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief Provider Interface ������������
     *
     * ���� Port����ͭ���� Consumer Interface ��Ŭ�礹�� Provider
     * Interface �˴ؤ�������ConnectorProfile::properties ������Ф�
     * Consumer Interface �˥��֥������Ȼ��Ȥ򥻥åȤ��롣
     *
     * ����RTC �Υ��󥹥���̾�� Consumer Interface ���ξ��󤬰ʲ��Τ�
     * ����Ǥ���Ȳ��ꤹ��ȡ�
     *
     * - RTC���󥹥���̾:              rtc_iname
     * - �ݡ���̾:                       port_name
     * - ���󥿡��ե���������:           if_polarity
     * - ���󥿡��ե�������̾:           if_tname
     * - ���󥿡��ե��������󥹥���̾: if_iname
     *
     * ���� Consumer Interface ��ɽ�����󥿡��ե���������Ҥϰʲ��Τ褦
     * ��ɽ����롣
     *
     * <rtc_iname>.port.<port_name>.required.<if_tname>.<if_iname>
     *
     * ���δؿ��ϡ��ޤ����� ConnectorProfile::properties �˾嵭���󥿡�
     * �ե���������Ҥ򥭡��Ȥ��Ƴ�Ǽ����Ƥ��� Provider Interface ����
     * �Ҥ�õ���Ф�������ˡ����� Provider Interface ����Ҥ򥭡��Ȥ���
     * ��Ǽ����Ƥ��� Provider Interface �λ��Ȥ�ɽ�� IOR ʸ��������
     * ����Consumer Interface �˥��åȤ��롣
     *
     * �������ˡ�Provider �� prov(n), ���λ��Ȥ�IOR(n) ����� Consumer
     * ��cons(n) �Τ褦�˵��Ҥ�������餹�٤ƤΥ��󥿡��ե������η���Ʊ
     * ��Ǥ��ꡢConnectorProfile �˰ʲ����ͤ����ꤵ��Ƥ���Ȥ��롣
     *
     * <pre>
     * ConnectorProfile::properties =
     * {
     *   prov0: IOR0,
     *   prov1: IOR1,
     *   prov2: IOR2,
     *   cons0: prov2,
     *   cons1: prov1,
     *   cons2: prov0
     * }
     * </pre>
     *
     * ���ΤȤ���cons(0..2) �ˤϤ��줾�졢���Ȥ��ʲ��Τ褦�˥��åȤ���롣
     *
     * <pre>
     *   cons0 = IOR2
     *   cons1 = IOR1
     *   cons2 = IOR0
     * </pre>
     *
     * �ʤ�����С������Ȥθߴ����Τ��ᡢ
     * ConnectorProfile::properties �� Consumer Interface �򥭡��Ȥ���
     * �ͤ����åȤ���Ƥ��ʤ����Ǥ⡢���Υ롼�뤬Ŭ�Ѥ���롣
     *
     * �������� Consumer Interface ��
     *
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = REQUIRED;
     *  }
     * </pre>
     *
     * �Ȥ�����Ͽ����Ƥ���С�¾�� Port ��
     *
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = PROVIDED;
     *  }
     * </pre> 
     *
     * �Ȥ�����Ͽ����Ƥ��� Serivce Provider �Υ��֥������Ȼ��Ȥ�õ����
     * Consumer �˥��åȤ��롣�ºݤˤϡ�ConnectorProfile::properties ��
     *
     * <pre>
     * NameValue = { "port.Manipulator.PA10_0": <Object reference> }
     * </pre>
     *
     * �Ȥ�����Ͽ����Ƥ��� NameValue ��õ�������Υ��֥������Ȼ��Ȥ�
     * Consumer �˥��åȤ��롣
     *
     * @param connector_profile ���ͥ����ץ�ե�����
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Subscribe to interface
     *
     * Retrieve information associated with Provider matches Consumer
     * owned by this port and set the object reference to Consumer.
     *
     * Now, Consumer is registered as the following:
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = REQUIRED;
     *  }
     * </pre>
     * Find the object reference of Serivce Provider that is registered as
     * the following of other ports:
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = PROVIDED;
     *  }
     * </pre> 
     * and set to Consumer.
     * In fact, find NameValue that is registered as the following to 
     * ConnectorProfile::properties:
     * <pre>
     * NameValue = { "port.Manipulator.PA10_0": <Object reference> }
     * </pre>
     * and set the object reference to Consumer.
     *
     * @param connector_profile Connector profile
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief Interface �ؤ���³��������
     *
     * Ϳ����줿 ConnectorProfile �˴�Ϣ���� Consumer �˥��åȤ��줿
     * ���٤Ƥ� Object ���������³�������롣
     *
     * @param connector_profile ���ͥ����ץ�ե�����
     *
     * @else
     *
     * @brief Unsubscribe interfaces
     *
     * Release all Objects that was set in Consumer associated with the given 
     * ConnectorProfile.
     *
     * @param connector_profile Connector profile
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);

    //============================================================
    // Local operations
    //============================================================
    /*!
     * @if jp
     *
     * @brief Port �����ƤΥ��󥿡��ե������� activates ����
     *
     * Port ����Ͽ����Ƥ������ƤΥ��󥿡��ե������� activate ���롣
     *
     * @else
     *
     * @brief Activate all Port interfaces
     *
     * This operation activate all interfaces that is registered in the
     * ports.
     *
     * @endif
     */
    virtual void activateInterfaces();

    /*!
     * @if jp
     *
     * @brief ���Ƥ� Port �Υ��󥿡��ե������� deactivates ����
     *
     * Port ����Ͽ����Ƥ������ƤΥ��󥿡��ե������� deactivate ���롣
     *
     * @else
     *
     * @brief Deactivate all Port interfaces
     *
     * This operation deactivate all interfaces that is registered in the
     * ports.
     *
     * @endif
     */
    virtual void deactivateInterfaces();

  protected:
    /*!
     * @if jp
     * @brief �ץ�ѥƥ�
     * @else
     * @brief Properties
     * @endif
     */
    coil::Properties m_properties;
    
  private:
    class CorbaConsumerHolder;
    /*!
     * @if jp
     * @brief Consumer �˹��פ��� Provider �� NVList ���椫�鸫�Ĥ���
     *
     * NVList �椫�� CorbaConsumerHolder ���ݻ�����Ƥ��� Consumer �˹�
     * �פ��륭������� Provider �򸫤Ĥ���IOR ����Ф��ʥ����󥰤���
     * Consumer �˥��åȤ��롣�б����륭����¸�ߤ��ʤ���IOR �����Ĥ���
     * �ʤ����ʥ����󥰤˼��Ԥ�����硢false ���֤���
     *
     * @param nv Provider ���ޤޤ�Ƥ��� ConnectorProfile::properties �� NVList
     * @param cons Provider ���б����� Consumer �Υۥ��
     * 
     * @retrun bool Consumer ���б����� Provider �����Ĥ���ʤ���� false
     *
     * @else
     * @brief Find out a provider corresponding to the consumer from NVList
     *
     * This function finds out a Provider with the key that is matched
     * with Cosumer's name in the CorbaConsumerHolder, extracts IOR
     * and performs narrowing into the Consumer and set it to the
     * Consumer. False is returned when there is no corresponding key
     * and IOR and the narrowing failed.
     *  
     * @param nv NVlist of ConnectorProfile::properties that includes Provider
     * @param cons a Consumer holder to be matched with a Provider
     * 
     * @return bool false is returned if there is no provider for the consumer
     *
     * @endif
     */
    virtual bool findProvider(const NVList& nv, CorbaConsumerHolder& cons,
                              std::string& iorstr);

    /*!
     * @if jp
     * @brief Consumer �˹��פ��� Provider �� NVList ���椫�鸫�Ĥ���
     *
     * ���δؿ��ϡ��Ť��С������θߴ����Τ���δؿ��Ǥ��롣
     *
     * NVList �椫�� CorbaConsumerHolder ���ݻ�����Ƥ��� Consumer �˹�
     * �פ��륭������� Provider �򸫤Ĥ��롣�б����륭����¸�ߤ��ʤ���
     * IOR �����Ĥ���ʤ���硢false ���֤���
     *  
     * @param nv Provider ���ޤޤ�Ƥ��� ConnectorProfile::properties �� NVList
     * @param cons Provider ���б����� Consumer �Υۥ��
     * @param iorstr ���Ĥ��ä�IORʸ������Ǽ�����ѿ�
     * 
     * @retrun bool Consumer ���б����� Provider �����Ĥ���ʤ���� false
     *
     * @else
     * @brief Find out a provider corresponding to the consumer from NVList
     *
     * This function is for the old version's compatibility.
     *
     * This function finds out a Provider with the key that is matched
     * with Cosumer's name in the CorbaConsumerHolder and extracts
     * IOR.  False is returned when there is no corresponding key and
     * IOR.
     *  
     * @param nv NVlist of ConnectorProfile::properties that includes Provider
     * @param cons a Consumer holder to be matched with a Provider
     * @param iorstr variable which is set IOR string
     * 
     * @return bool false is returned if there is no provider for the consumer
     *
     * @endif
     */
    virtual bool findProviderOld(const NVList&nv, CorbaConsumerHolder& cons,
                                 std::string& iorstr);

    /*!
     * @if jp
     * @brief Consumer �� IOR �򥻥åȤ���
     *
     * IOR ��ʥ����󥰤���Consumer �˥��åȤ��롣�ʥ����󥰤˼���
     * ������硢false ���֤�����������IORʸ���󤬡�null�ޤ���nil�ξ�硢
     * ���֥������Ȥ˲��⥻�åȤ����� true ���֤���
     *
     * @param ior ���åȤ��� IOR ʸ����
     * @param cons Consumer �Υۥ��
     * 
     * @retrun bool Consumer �ؤΥʥ����󥰤˼��Ԥ������ false
     *
     * @else
     * @brief Setting IOR to Consumer
     *
     * This function performs narrowing into the Consumer and set it to the
     * Consumer. False is returned when the narrowing failed. But, if IOR
     * string is "null" or "nil", this function returns true.
     *  
     * @param ior IOR string
     * @param cons Consumer holder
     * 
     * @retrun bool false if narrowing failed.
     *
     * @endif
     */
    bool setObject(const std::string& ior, CorbaConsumerHolder& cons);

    /*!
     * @if jp
     * @brief Consumer �Υ��֥������Ȥ��꡼������
     *
     * Consumer �˥��åȤ��줿���Ȥ��꡼�����롣Consumer��IOR��Ϳ����
     * �줿IORʸ����Ȱۤʤ��硢false���֤���
     *
     * @param ior ���åȤ��� IOR ʸ����
     * @param cons Consumer �Υۥ��
     * 
     * @retrun Consumer��IOR��Ϳ����줿IORʸ����Ȱۤʤ��硢false���֤���
     *
     * @else
     * @brief Releasing Consumer Object
     *
     * This function releases object reference of Consumer. If the
     * given IOR string is different from Consumer's IOR string, it
     * returns false.
     *  
     * @param ior IOR string
     * @param cons Consumer holder
     * 
     * @retrun bool False if IOR and Consumer's IOR are different
     *
     * @endif
     */
    bool releaseObject(const std::string& ior, CorbaConsumerHolder& cons);

  private:
    /*!
     * @if jp
     * @class CorbaProviderHolder
     * @brief Provider �ξ�����Ǽ���빽¤��
     *
     * CORBA Provider �Υۥ�����饹
     *
     * @else
     * @class CorbaProviderHolder
     * @brief The structure to be stored Provider information.
     *
     * CORBA Provider holder class
     *
     * @endif
     */
    class CorbaProviderHolder
    {
    public:
      CorbaProviderHolder(const char* type_name,
                          const char* instance_name,
                          PortableServer::RefCountServantBase* servant)
        : m_typeName(type_name),
          m_instanceName(instance_name),
          m_servant(servant),
          m_ior()
      {  
#ifndef ORB_IS_RTORB
        m_oid = Manager::instance().getPOA()->servant_to_id(m_servant);
        try
          {
            Manager::instance().
              getPOA()->activate_object_with_id(m_oid, m_servant);
          }
        catch(...)
          {
            ;
          }
        CORBA::Object_var obj;
        obj = Manager::instance().getPOA()->id_to_reference(m_oid);
        CORBA::ORB_ptr orb = Manager::instance().getORB();
        CORBA::String_var ior_var = orb->object_to_string(obj);
        m_ior = ior_var;
        deactivate();
#else // ORB_IS_RTORB
        // why RtORB does not activate object by __this()
        // and does not deactivate at the end of ctor?
        m_oid = Manager::instance().getPOA()->servant_to_id(m_servant);
        CORBA::Object_var obj;
        obj = CORBA::Object_var(m_servant->__this());
        CORBA::ORB_ptr orb = Manager::instance().getORB();
        CORBA::String_var ior_var = orb->object_to_string(obj);
        m_ior = ior_var;
#endif // ORB_IS_RTORB
      }
      virtual ~CorbaProviderHolder()
      {
        deactivate();
      }
      std::string instanceName() { return m_instanceName; }
      std::string typeName() { return m_typeName; }
      std::string ior() { return m_ior; }
      std::string descriptor() { return m_typeName + "." + m_instanceName; }

      void activate()
      {
        try
          {
            Manager::instance().
              getPOA()->activate_object_with_id(m_oid, m_servant);
          }
        catch(const ::PortableServer::POA::ServantAlreadyActive &)
          {
            ; // do nothing
          }
        catch(...)
          {
            ; // do nothing
          }
      }
      void deactivate()
      {
        try
          {
            Manager::instance().getPOA()->deactivate_object(m_oid);
          }
        catch(...)
          {
            ; // do nothing
          }
      }
    private:
      std::string m_typeName;
      std::string m_instanceName;
      PortableServer::RefCountServantBase* m_servant;
      PortableServer::ObjectId_var m_oid;
      std::string m_ior;
    };

    /*!
     * @if jp
     * @brief Provider �ξ�����Ǽ���� vector
     * @else
     * @brief vector to stored Providers' information
     * @endif
     */
    typedef std::vector<CorbaProviderHolder> CorbaProviderList;
    CorbaProviderList m_providers;

    /*!
     * @if jp
     * @brief Consumer �ξ�����Ǽ���빽¤��
     * @else
     * @brief The structure to be stored Consumer information.
     * @endif
     */
    class CorbaConsumerHolder
    {
    public:
      CorbaConsumerHolder(const char* type_name,
                          const char* instance_name,
                          CorbaConsumerBase* consumer)
        : m_typeName(type_name),
          m_instanceName(instance_name),
          m_consumer(consumer),
          m_ior("")
      {
      }
      std::string instanceName() { return m_instanceName; }
      std::string typeName() { return m_typeName; }
      std::string descriptor() { return m_typeName + "." + m_instanceName; }

      bool setObject(const char* ior)
      {
        m_ior = ior;
        CORBA::ORB_ptr orb = ::RTC::Manager::instance().getORB();
        CORBA::Object_var obj = orb->string_to_object(ior);
        if (CORBA::is_nil(obj))
          {
            return false;
          }

        return m_consumer->setObject(obj.in());
      }
      void releaseObject()
      {
        m_consumer->releaseObject();
      }
      const std::string& getIor()
      {
        return m_ior;
      }
    private:
      std::string m_typeName;
      std::string m_instanceName;
      CorbaConsumerBase* m_consumer;
      std::string m_ior;
    };
    typedef std::vector<CorbaConsumerHolder> CorbaConsumerList;
    CorbaConsumerList m_consumers;
    
    // functors
    /*!
     * @if jp
     * @brief Consumer �Υ��֥������Ȥ�������뤿��� Functor
     * @else
     * @brief Functor to release Consumer's object
     * @endif
     */
    struct unsubscribe
    {
      unsubscribe(CorbaConsumerList& consumers)
        : m_consumers(consumers)
      {
      }
      
      void operator()(const SDOPackage::NameValue& nv)
      {
        for (CorbaConsumerList::iterator it(m_consumers.begin());
             it != m_consumers.end(); ++it)
          {
            std::string name(nv.name);
            if (it->descriptor() == (const char*)nv.name)
              {
                it->releaseObject();
              }
          }
      }
      CorbaConsumerList& m_consumers;
    };
  };
};
#endif // RTC_CORBAPORT_H
