// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2008-01-14 07:56:44 $
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
 * $Id: PortBase.h 2048 2011-02-22 21:20:51Z n-ando $
 *
 */

#ifndef RTC_PORTBASE_H
#define RTC_PORTBASE_H

#include <rtm/RTC.h>

#include <string>
#include <vector>
#include <coil/Guard.h>
#include <coil/Mutex.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/SystemLogger.h>
#include <rtm/PortConnectListener.h>
#include <iostream>

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  class ConnectionCallback;

  /*!
   * @if jp
   * @class PortBase
   * @brief Port �δ��쥯�饹
   *
   * RTC::Port �δ���Ȥʤ륯�饹��
   * RTC::Port �Ϥۤ� UML Port �γ�ǰ��Ѿ����Ƥ��ꡢ�ۤ�Ʊ���Τ�ΤȤߤʤ�
   * ���Ȥ��Ǥ��롣RT ����ݡ��ͥ�ȤΥ��󥻥ץȤˤ����Ƥϡ�
   * Port �ϥ���ݡ��ͥ�Ȥ���°��������ݡ��ͥ�Ȥ�¾�Υ���ݡ��ͥ�Ȥ���ߺ���
   * ��Ԥ������Ǥ��ꡢ�̾���Ĥ��Υ��󥿡��ե������ȴ�Ϣ�դ����롣
   * ����ݡ��ͥ�Ȥ� Port ���̤��Ƴ������Ф����󥿡��ե��������󶡤ޤ����׵�
   * ���뤳�Ȥ��Ǥ���Port�Ϥ�����³�������������ô����
   * <p>
   * Port �ζ�ݥ��饹�ϡ��̾� RT ����ݡ��ͥ�ȥ��󥹥�����������Ʊ����
   * �������졢�󶡡��׵ᥤ�󥿡��ե���������Ͽ�����塢RT ����ݡ��ͥ�Ȥ�
   * ��Ͽ���졢�������饢��������ǽ�� Port �Ȥ��Ƶ�ǽ���뤳�Ȥ����ꤷ�Ƥ��롣
   * <p>
   * RTC::Port �� CORBA ���󥿡��ե������Ȥ��ưʲ��Υ��ڥ졼�������󶡤��롣
   *
   * - get_port_profile()
   * - get_connector_profiles()
   * - get_connector_profile()
   * - connect()
   * - notify_connect()
   * - disconnect()
   * - notify_disconnect()
   * - disconnect_all()
   *
   * ���Υ��饹�Ǥϡ������Υ��ڥ졼�����μ������󶡤��롣
   * <p>
   * �����Υ��ڥ졼�����Τ�����get_port_profile(), get_connector_profiles(),
   * get_connector_profile(), connect(), disconnect(), disconnect_all() �ϡ�
   * ���֥��饹�ˤ������ä˿����񤤤��ѹ�����ɬ�פ��ʤ����ᡢ�����С��饤��
   * ���뤳�ȤϿ侩����ʤ���
   * <p>
   * notify_connect(), notify_disconnect() �ˤĤ��Ƥϡ����֥��饹���󶡡��׵�
   * ���륤�󥿡��ե������μ���˱����ơ������񤤤��ѹ�����ɬ�פ�������
   * ��ǽ�������뤬��������ľ�ܥ����С��饤�ɤ��뤳�ȤϿ侩���줺��
   * ��Ҥ� notify_connect(), notify_disconnect() �ι�ˤ����Ƥ�Ҥ٤����̤�
   * �����δؿ��˴�Ϣ���� protected �ؿ��򥪡��С��饤�ɤ��뤳�Ȥˤ��
   * �����񤤤��ѹ����뤳�Ȥ��侩����롣
   *
   * @since 0.4.0
   *
   * @else
   * @class PortBase
   * @brief Port base class
   *
   * This class is a base class of RTC::Port.
   * RTC::Port inherits a concept of RT-Component, and can be regarded as almost
   * the same as it. In the concept of RT-Component, Port is attached to the
   * component, can mediate interaction between other components and usually is
   * associated with some interfaces.
   * Component can provide or require interface for outside via Port, and the
   * Port plays a role to manage the connection.
   * <p>
   * Concrete class of Port assumes to be usually created at the same time that
   * RT-Component's instance is created, be registerd to RT-Component after
   * provided and required interfaces are registerd, and function as accessible
   * Port from outside.
   * <p>
   * RTC::Port provides the following operations as CORBA interface:
   *
   * - get_port_profile()
   * - get_connector_profiles()
   * - get_connector_profile()
   * - connect()
   * - notify_connect()
   * - disconnect()
   * - notify_disconnect()
   * - disconnect_all()
   *
   * This class provides implementations of these operations.
   * <p>
   * In these operations, as for get_port_profile(), get_connector_profiles(),
   * get_connector_profile(), connect(), disconnect() and disconnect_all(),
   * since their behaviors especially need not to be change in subclass, 
   * overriding is not recommended.
   * <p>
   * As for notify_connect() and notify_disconnect(), you may have to modify
   * behavior according to the kind of interfaces that subclass provides and
   * requires, however it is not recommended these are overriden directly.
   * In the section of notify_connect() and notify_disconnect() as described
   * below, it is recommended that you modify behavior by overriding the
   * protected function related to these functions.
   *
   * @since 0.4.0
   *
   * @endif
   */  
  class PortBase
    : public virtual POA_RTC::PortService,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * PortBase �Υ��󥹥ȥ饯���� Port ̾ name ������˼��������Ԥ�
     * ��Ʊ���ˡ���ʬ���Ȥ� CORBA Object �Ȥ��Ƴ������������Ȥ� PortProfile
     * �� port_ref �˼��ȤΥ��֥������ȥ�ե���󥹤��Ǽ���롣
     * ̾���ˤϡ�"." �ʳ���ʸ�������Ѥ��뤳�Ȥ��Ǥ��롣
     *
     * @param name Port ��̾��(�ǥե������:"")
     *
     * @else
     *
     * @brief Constructor
     *
     * The constructor of the ProtBase class is given the name of this Port
     * and initialized. At the same time, the PortBase activates itself
     * as CORBA object and stores its object reference to the PortProfile's 
     * port_ref member.
     * Characters except "." can be used for the name of the port.
     *
     * @param name The name of Port (The default value:"")
     *
     * @endif
     */
    PortBase(const char* name = "");
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯���Ǥϡ�PortService CORBA ���֥������Ȥ� deactivate ��
     * �Ԥ���deactivate�˺ݤ����㳰���ꤲ�뤳�ȤϤʤ���
     *
     * @else
     *
     * @brief Destructor
     *
     * In the destructor, PortService CORBA object is deactivated.
     * This function never throws exception.
     *
     * @endif
     */
    virtual ~PortBase(void);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] PortProfile���������
     *
     * Port���ݻ�����PortProfile���֤������δؿ��� CORBA ���ڥ졼�����
     * �Ǥ��ꡢCORBA �Υ��������§�˽������ƤӽФ�¦���֤����
     * PortProfile ���֥������Ȥ���Τ�����Ǥ�����롣PortProfile ��¤��
     * �ϰʲ��Υ��С�����ġ�
     *
     * - name              [string ��] Port ��̾����
     * - interfaces        [PortInterfaceProfileList ��] Port ���ݻ�����
     *                     PortInterfaceProfile �Υ�������
     * - port_ref          [Port Object ��] Port ���ȤΥ��֥������ȥ�ե����
     * - connector_profile [ConnectorProfileList ��] Port �������ݻ�����
     *                     ConnectorProfile �Υ�������
     * - owner             [RTObject Object ��] ���� Port ���ͭ����
     *                     RTObject�Υ�ե����
     * - properties        [NVList ��] ����¾�Υץ�ѥƥ���
     *
     * @post ���δؿ���ƤӽФ����Ȥˤ���������֤��ѹ�����뤳�ȤϤʤ���
     *
     * @return PortProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the PortProfile of the Port
     *
     * This operation returns the PortProfile of the Port. Since this
     * function is CORBA operation, callers have responsibility to
     * destruction of the returned PortProfile object according to the
     * CORBA memory management rules.
     *
     * PortProfile struct has the following members:
     *
     * - name              [string type] The name of the Port.
     * - interfaces        [PortInterfaceProfileList type] The sequence of 
     *                     PortInterfaceProfile owned by the Port
     * - port_ref          [Port Object type] The object reference of the Port.
     * - connector_profile [ConnectorProfileList type] The sequence of 
     *                     ConnectorProfile owned by the Port.
     * - owner             [RTObject Object type] The object reference of 
     *                     RTObject that is owner of the Port.
     * - properties        [NVList type] The other properties.
     *
     * @post This function never changes the state of the object.
     *
     * @return PortProfile of the Port
     *
     * @endif
     */
    virtual PortProfile* get_port_profile()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief PortProfile ��������롣
     *
     * ���δؿ��ϡ����֥��������������ݻ�����Ƥ��� PortProfile ��
     * const ���Ȥ��֤� const �ؿ��Ǥ��롣
     * 
     * @post ���δؿ���ƤӽФ����Ȥˤ���������֤��ѹ�����뤳�ȤϤʤ���
     *
     * @return PortProfile
     *
     * @else
     *
     * @brief Get the PortProfile of the Port
     *
     * This function is a const function that returns a const
     * reference of the PortProfile stored in this Port.
     *
     * @post This function never changes the state of the object.
     *
     * @return PortProfile
     *
     * @endif
     */
    const PortProfile& getPortProfile() const;
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] ConnectorProfileList���������
     *
     * Port���ݻ����� ConnectorProfile �� sequence ���֤������δؿ���
     * CORBA ���ڥ졼�����Ǥ��ꡢCORBA �Υ��������§�˽������Ƥӽ�
     * ��¦���֤���� ConnectorProfileList ���֥������Ȥ���Τ�����Ǥ��
     * ���롣
     *
     * ConnectorProfile �� Port �֤���³�ץ�ե����������ݻ����빽¤�ΤǤ��ꡢ
     * ��³����Port�֤Ǿ���򴹤�Ԥ�����Ϣ���뤹�٤Ƥ� Port ��Ʊ����ͤ�
     * �ݻ�����롣
     * ConnectorProfile �ϰʲ��Υ��С����ݻ����Ƥ��롣
     *
     * - name         [string ��] ���Υ��ͥ�����̾����
     * - connector_id [string ��] ��ˡ�����ID
     * - ports        [Port sequnce] ���Υ��ͥ����˴�Ϣ���� Port �Υ��֥�������
     *                ��ե���󥹤Υ������󥹡�
     * - properties   [NVList ��] ����¾�Υץ�ѥƥ���
     *
     * @post ���δؿ���ƤӽФ����Ȥˤ���������֤��ѹ�����뤳�ȤϤʤ���
     *
     * @return ���� Port ���ݻ����� ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfileList of the Port
     *
     * This operation returns a list of the ConnectorProfiles of the
     * Port.  Since this function is CORBA operation, callers have
     * responsibility to destruction of the returned ConnectorProfileList
     * object according to the CORBA memory management rules.
     *
     * ConnectorProfile includes the connection information that
     * describes relation between (among) Ports, and Ports exchange
     * the ConnectionProfile on connection process and hold the same
     * information in every Port.  ConnectionProfile has the following
     * members:
     *
     * - name         [string type] The name of the connection.
     * - connector_id [string type] Unique identifier.
     * - ports        [Port sequnce] The sequence of Port's object reference
     *                that are related the connection.
     * - properties   [NVList type] The other properties.
     *
     * @post This function never changes the state of the object.
     *
     * @return ConnectorProfileList of the Port
     *
     * @endif
     */
    virtual ConnectorProfileList* get_connector_profiles()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] ConnectorProfile ���������
     *
     * connector_id �ǻ��ꤵ�줿 ConnectorProfile ���֤������δؿ���
     * CORBA ���ڥ졼�����Ǥ��ꡢCORBA �Υ��������§�˽������Ƥӽ�
     * ��¦���֤���� ConnectorProfile ���֥������Ȥ���Τ�����Ǥ�����롣
     *
     * @pre ������Ϳ���� connector_id ��ͭ����ʸ����Ǥʤ���Фʤ�ʤ���
     * ��ʸ������ꤷ����硢�ޤ��ϻ��ꤷ�� connector_id �����
     * ConnectorProfile �����Ĥ���ʤ����ϡ����� ConnectorProfile ��
     * �֤���
     *
     * @post ���δؿ���ƤӽФ����Ȥˤ���������֤��ѹ�����뤳�ȤϤʤ���
     *
     * @param connector_id ConnectorProfile �� ID
     * @return connector_id �ǻ��ꤵ�줿 ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfile
     *
     * This operation returns the ConnectorProfiles specified
     * connector_id.  Since this function is CORBA operation, callers
     * have responsibility to destruction of the returned
     * ConnectorProfile object according to the CORBA memory
     * management rules.
     *
     * If ConnectorProfile with specified connector_id is not included,
     * empty ConnectorProfile is returned.
     *
     * @post This function never changes the state of the object.
     *
     * @param connector_id ID of the ConnectorProfile
     * @return the ConnectorProfile identified by the connector_id
     *
     * @endif
     */
    virtual ConnectorProfile* get_connector_profile(const char* connector_id)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³��Ԥ�
     *
     * Ϳ����줿 ConnectoionProfile �ξ���˴�Ť���Port�֤���³���Ω
     * ���롣���δؿ��ϼ�˥��ץꥱ�������ץ�����ġ��뤫��Ƥӽ�
     * �����Ȥ�����Ȥ��Ƥ��롣
     * 
     * @pre ���ץꥱ�������ץ����ϡ�����ݡ��ͥ�ȴ֤�ʣ����
     * Port ����³���뤿��ˡ�Ŭ�ڤ��ͤ򥻥åȤ��� ConnectorProfile ��
     * connect() �ΰ����Ȥ���Ϳ���ƸƤӽФ��ʤ���Фʤ�ʤ���
     *
     * @pre connect() ��Ϳ���� ConnectorProfile �Υ��С��Τ�����
     * name, ports, properties ���С����Ф��ƥǡ����򥻥åȤ��ʤ����
     * �ʤ�ʤ���connector_id �ˤ��̾��ʸ�������ꤹ�뤫��Ŭ����UUID��
     * ʸ��������ꤹ��ɬ�פ����롣
     *
     * @pre ConnectorProfile::name ����³�ˤĤ���̾���� CORBA::string
     * ���˳�Ǽ�Ǥ���Ǥ�դ�ʸ����Ǥ���ɬ�פ����롣
     * 
     * @pre ConnectorProfile::connector_id �Ϥ��٤Ƥ���³���Ф��ư�դ�
     * ID (�̾��UUID) ����Ǽ����롣UUID������� connect() �ؿ���ǹ�
     * ����Τǡ��ƤӽФ�¦�϶�ʸ�������ꤹ�롣��¸����³��Ʊ��UUID��
     * ���ꤷ connect() ��ƤӽФ������ˤ� PRECONDITION_NOT_MET ���顼
     * ���֤���������������γ�ĥ�Ǵ�¸����³�ץ�ե�����򹹿����뤿��
     * �˴�¸�� UUID �����ꤷ�ƸƤӽФ�����ˡ���Ѥ������ǽ�������롣
     *
     * @pre ConnectorProfile::ports �� RTC::PortService �Υ������󥹤ǡ�
     * ��³���������̾�2�İʾ�Υݡ��ȤΥ��֥������Ȼ��Ȥ���������ɬ
     * �פ����롣�㳰�Ȥ��ơ��ݡ��ȤΥ��֥������Ȼ��Ȥ�1�Ĥ�����Ǽ����
     * connect()��ƤӽФ����Ȥǡ��ݡ��ȤΥ��󥿡��ե���������������
     * ���ꡢ�ü�ʥݡ���(CORBA��RTC::PortService�ʳ������)���Ф�����
     * ³��Ԥ����⤢�롣
     *
     * @pre ConnectorProfile::properties �ϥݡ��Ȥ˴�Ϣ�դ���줿���󥿡�
     * �ե��������Ф���ץ�ѥƥ���Ϳ���뤿��˻��Ѥ��롣�ץ�ѥƥ��ϡ�
     * string ���򥭡���Any �����ͤȤ��Ƥ�ĥڥ��Υ������󥹤Ǥ��ꡢ��
     * �ˤ�Ǥ�դ�CORBA�ǡ��������Ǽ�Ǥ��뤬����ǽ�ʸ¤� string ���Ȥ�
     * �Ƴ�Ǽ����뤳�Ȥ��侩����롣
     *
     * @pre �ʾ� connect() �ƤӽФ��������ꤹ�� ConnectorProfile �Υ��
     * �Ф�ޤȤ��Ȱʲ��Τ褦�ˤʤ롣
     *
     * - ConnectorProfile::name: Ǥ�դ���³̾
     * - ConnectorProfile::connector_id: ��ʸ��
     * - ConnectorProfile::ports: 1�İʾ�Υݡ���
     * - ConnectorProfile::properties: ���󥿡��ե��������Ф���ץ�ѥƥ�
     *
     * @post connect() �ؿ��ϡ�ConnectorProfile::ports�˳�Ǽ���줿�ݡ�
     * �ȥ������󥹤���Ƭ�Υݡ��Ȥ��Ф��� notify_connect() ��Ƥ֡�
     *
     * @post notify_connect() �� ConnectorProfile::ports �˳�Ǽ���줿�ݡ�
     * �Ƚ�� notify_connect() �򥫥������ɸƤӽФ����롣���Υ���������
     * �ƤӽФ��ϡ������notify_connect() �ǥ��顼���ФƤ�ݡ��ȤΥ���
     * �������Ȼ��Ȥ�ͭ���Ǥ���¤ꡢɬ�����٤ƤΥݡ��Ȥ��Ф��ƹԤ���
     * ���Ȥ��ݾڤ���롣ͭ���Ǥʤ����֥������Ȼ��Ȥ������������¸��
     * �����硢���Υݡ��Ȥ򥹥��åפ��ơ����Υݡ��Ȥ��Ф���
     * notify_connect() ��ƤӽФ���
     *
     * @post connect() �ؿ��ϡ�notify_connect()������ͤ�RTC_OK�Ǥ���С�
     * RTC_OK ���֤������λ�������³�ϴ�λ���롣RTC_OK�ʳ�
     * �ξ��ϡ�������³ID���Ф���disconnect()��ƤӽФ���³��������
     * notify_connect() ���֤������顼�꥿���󥳡��ɤ򤽤Τޤ��֤���
     * 
     * @post connect() �ΰ����Ȥ����Ϥ��� ConnectorProfile �ˤϡ�
     * ConnectorProfile::connector_id ����ӡ�����Υݡ��Ȥ�
     * publishInterfaces() �Ǹ��������ݡ��ȥ��󥿡��ե������γƼ����
     * ��Ǽ����Ƥ��롣connect() ���������� notify_connect() ��
     * ConnectorProfile::{name, ports} ���ѹ����뤳�ȤϤʤ���
     *  
     * @param connector_profile ConnectorProfile
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation establishes connection according to the given
     * ConnectionProfile inforamtion. This function is premised on
     * calling from mainly application program or tools.
     *
     * @pre To establish the connection among Ports of RT-Components,
     * application programs must call this operation giving
     * ConnectorProfile with valid values as an argument.
     *
     * @pre Out of ConnectorProfile member variables, "name", "ports"
     * and "properties" members shall be set valid
     * data. "connector_id" shall be set as empty string value or
     * valid string UUID value.
     *
     * @pre ConnectorProfile::name that is connection identifier shall
     * be any valid CORBA::string.
     * 
     *
     * @pre ConnectorProfile::connector_id shall be set unique
     * identifier (usually UUID is used) for all connections. Since
     * UUID string value is usually set in the connect() function,
     * caller should just set empty string. If the connect() is called
     * with the same UUID as existing connection, this function
     * returns PRECONDITION_NOT_MET error. However, in order to update
     * the existing connection profile, the "connect()" operation with
     * existing connector ID might be used as valid method by future
     * extension
     *
     * @pre ConnectorProfile::ports, which is sequence of
     * RTC::PortService references, shall store usually two or more
     * ports' references. As exceptions, the "connect()" operation
     * might be called with only one reference in ConnectorProfile, in
     * case of just getting interfaces information from the port, or
     * connecting a special port (i.e. the peer port except
     * RTC::PortService on CORBA).
     *
     * @pre ConnectorProfile::properties might be used to give certain
     * properties to the service interfaces associated with the port.
     * The properties is a sequence variable with a pair of key string
     * and Any type value. Although the A variable can store any type
     * of values, it is not recommended except string.
     *
     * @pre The following is the summary of the ConnectorProfile
     * member to be set when this operation is called.
     *
     * - ConnectorProfile::name: The any name of connection
     * - ConnectorProfile::connector_id: Empty string
     * - ConnectorProfile::ports: One or more port references
     * - ConnectorProfile::properties: Properties for the interfaces
     *
     * @post connect() operation will call the first port in the
     * sequence of the ConnectorProfile.
     *
     * @post "noify_connect()"s perform cascaded call to the ports
     * stored in the ConnectorProfile::ports by order. Even if errors
     * are raised by intermediate notify_connect() operation, as long
     * as ports' object references are valid, it is guaranteed that
     * this cascaded call is completed in all the ports.  If invalid
     * or dead ports exist in the port's sequence, the ports are
     * skipped and notify_connect() is called for the next valid port.
     *
     * @post connect() function returns RTC_OK if all the
     * notify_connect() return RTC_OK. At this time the connection is
     * completed.  If notify_connect()s return except RTC_OK,
     * connect() calls disconnect() operation with the connector_id to
     * destruct the connection, and then it returns error code from
     * notify_connect().
     *
     * @post The ConnectorProfile argument of the connect() operation
     * returns ConnectorProfile::connector_id and various information
     * about service interfaces that is published by
     * publishInterfaces() in the halfway ports. The connect() and
     * halfway notify_connect() functions never change
     * ConnectorProfile::{name, ports}.
     *
     * @param connector_profile The ConnectorProfile.
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t connect(ConnectorProfile& connector_profile)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³���Τ�Ԥ�
     *
     * ���Υ��ڥ졼�����ϡ�Port�֤���³���Ԥ���ݤˡ�Port�֤�����Ū
     * �˸ƤФ�륪�ڥ졼�����Ǥ��äơ��̾異�ץꥱ�������ץ����
     * �䡢Port�ʳ���RTC��Ϣ���֥�������������ƤӽФ���뤳�Ȥ����ꤵ
     * ��Ƥ��ʤ���
     *
     * notify_connect() ���Τϥƥ�ץ졼�ȥ᥽�åɥѥ�����Ȥ��ơ�����
     * ���饹�Ǽ�������뤳�Ȥ������ publishInterfaces(),
     * subscribeInterfaces() ��2�Ĥδؿ��������ǸƤӽФ��������μ���
     * �ʲ����̤�Ǥ��롣
     *
     * - publishInterfaces(): ���󥿡��ե���������θ���
     * - connectNext(): ���� Port �� notify_connect() �θƤӽФ�
     * - subscribeInterfaces(): ���󥿡��ե���������μ���
     * - ��³�������¸
     *
     * notify_connect() �� ConnectorProfile::ports �˳�Ǽ����Ƥ���
     * Port �ν���˽��äơ����������ɾ��˸ƤӽФ���Ԥ����Ȥˤ�ꡢ��
     * �󥿡��ե���������θ����ȼ������Ϣ�����٤ƤΥݡ��Ȥ��Ф��ƹԤ���
     * ���Υ��������ɸƤӽФ�����������Ǥ���뤳�ȤϤʤ���ɬ��
     * ConnectorProfile::ports �˳�Ǽ����Ƥ������ݡ��Ȥ��Ф��ƹԤ��롣
     *
     * @pre notify_connect() �� ConnectorProfile::ports ��˳�Ǽ�����
     * ���� Port ���ȥꥹ�ȤΤ��������� Port ���Ȥλ��Ȥμ��˳�Ǽ�����
     * ���� Port ���Ф��� notify_connect() ��ƤӽФ����������ä�
     * ConnectorProfile::ports �ˤ����� Port �λ��Ȥ���Ǽ����Ƥ���ɬ��
     * �����롣�⤷�����Ȥλ��Ȥ���Ǽ����Ƥ��ʤ���硢����¾�ν����ˤ�
     * �ꥨ�顼����񤭤���ʤ���С�BAD_PARAMETER ���顼���֤���롣
     *
     * @pre �ƤӽФ����� ConnectorProfile::connector_id �ˤϰ�դ�ID��
     * ���� UUID ���ݻ�����Ƥ���ɬ�פ����롣�̾� connector_id ��
     * connect() �ؿ��ˤ��Ϳ����졢��ʸ���ξ���ư���̤����Ǥ��롣
     *
     * @post ConnectorProfile::name, ConnectorProfile::connector_id,
     * ConnectorProfile::ports �� notify_connect() �θƤӽФ��ˤ��
     * �񤭴������뤳�ȤϤʤ����ѤǤ��롣
     *
     * @post ConnectorProfile::properties �� notify_connect() �������ǡ�
     * ���� Port �����ĥ����ӥ����󥿡��ե������˴ؤ�������¾�� Port
     * �������뤿��ˡ��ץ�ѥƥ����󤬽񤭹��ޤ�롣
     *
     * @post �ʤ���ConnectorProfile::ports �Υꥹ�Ȥκǽ� Port ��
     * notify_connet() ����λ���������Ǥϡ����٤Ƥδ�Ϣ���� Port ��
     * notify_connect() �θƤӽФ�����λ���롣publishInterfaces(),
     * connectNext(), subscribeInterfaces() �������³�������¸�Τ���
     * �줫���ʳ��ǥ��顼��ȯ���������Ǥ⡢���顼�����ɤ�����Ū���ݻ�
     * ����Ƥ��ꡢ�ǽ�����������顼�Υ��顼�����ɤ��֤���롣
     *
     * @param connector_profile ConnectorProfile
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Notify the Ports connection
     *
     * This operation is usually called from other ports' connect() or
     * notify_connect() operations when connection between ports is
     * established.  This function is not premised on calling from
     * other functions or application programs.
     *
     * According to the template method pattern, the notify_connect()
     * calls "publishInterfaces()" and "subsctiveInterfaces()"
     * functions, which are premised on implementing in the
     * subclasses. The processing sequence is as follows.
     *
     * - publishInterfaces(): Publishing interface information
     * - connectNext(): Calling notify_connect() of the next port
     * - subscribeInterfaces(): Subscribing interface information
     * - Storing connection profile
     *
     * According to the order of port's references stored in the
     * ConnectorProfile::ports, publishing interface information to
     * all the ports and subscription interface information from all
     * the ports is performed by "notify_connect()"s.  This cascaded
     * call never aborts in the halfway operations, and calling
     * sequence shall be completed for all the ports.
     *
     * @pre notify_connect() calls notify_connect() for the port's
     * reference that is stored in next of this port's reference in
     * the sequence of the ConnectorProfile::ports. Therefore the
     * reference of this port shall be stored in the
     * ConnectorProfile::ports. If this port's reference is not stored
     * in the sequence, BAD_PARAMETER error will be returned, except
     * the return code is overwritten by other operations.
     *
     * @pre UUID shall be set to ConnectorProfile::connector_id as a
     * unique identifier when this operation is called.  Usually,
     * connector_id is given by a connect() function and, the behavior
     * is undefined in the case of a null character.
     *
     * @post ConnectorProfile::name, ConnectorProfile::connector_id,
     * ConnectorProfile::ports are invariant, and they are never
     * rewritten by notify_connect() operations.
     *
     * @post In order to transfer interface information to other
     * ports, interface property information is stored into the
     * ConnectorProfile::properties.
     *
     * @post At the end of notify_connect() operation for the first
     * port stored in the ConnectorProfile::ports sequence, the
     * related ports' notify_connect() invocations complete. Even if
     * errors are raised at the halfway of publishInterfaces(),
     * connectNext(), subscribeInterfaces() and storing process of
     * ConnectorProfile, error codes are saved and the first error is
     * returned.
     *
     * @param connector_profile The ConnectorProfile.
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t notify_connect(ConnectorProfile& connector_profile)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³��������
     *
     * ���Υ��ڥ졼������Ϳ����줿 connector_id ���б�������³����
     * ���롣connector_id ���̾�����ƥ����Τˤ����ư�դ� UUID ��ʸ
     * ����Ǥ��ꡢ������ connect()/notify_connect() �θƤӽФ��ˤ���
     * Ω���줿��³�ץ�ե����� ConnectorProfile::connector_id ���б���
     * �롣
     *
     * @pre connector_id �� Port ���ݻ����� ConnectorProfile �ξ��ʤ���
     * ���Ĥ� ID �˰��פ���ʸ����Ǥʤ���Фʤ�ʤ������� Port ������
     * ConnectorProfile �Υꥹ����� connector_id ��Ʊ��� ID �����
     * ConnectorProfile ��¸�ߤ��ʤ���Ф��δؿ��� BAD_PARAMETER ���顼
     * ���֤���
     *
     * @pre connector_id ��Ʊ�� ID ����� ConnectorProfile::ports �ˤ�
     * ͭ���� Port �λ��Ȥ��ޤޤ�Ƥ��ʤ���Фʤ�ʤ���
     *
     * @post disconnect() �ؿ��ϡ�ConnectorProfile::ports �� Port �λ�
     * �ȥꥹ�Ȥ���Ƭ���Ф��ơ�notify_disconnect() ��ƤӽФ������Ȥ�̵
     * ���Ǥ���ʤɡ�notify_disconnect() �θƤӽФ��˼��Ԥ������ˤϡ�
     * ���ȥꥹ�Ȥ���Ƭ������֤���������ޤ� notify_disconnect() �θ�
     * �ӽФ�����notify_disconnect() �θƤӽФ��˰�ĤǤ���������С�
     * notify_disconnect() ���ֵ��ͤ򤽤Τޤ��֤�����Ĥ��������ʤ��ä�
     * ���ˤ� RTC_ERROR ���顼���֤���
     * 
     * @param connector_id ConnectorProfile �� ID
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Disconnect the Port
     *
     * This operation destroys connection between this port and the
     * peer port according to given connector_id. Usually connector_id
     * should be a UUID string that is unique in the system.  And the
     * connection, which is established by connect()/notify_connect()
     * functions, is identified by the ConnectorProfile::connector_id.
     *
     * @pre connector_id shall be a character string which is same
     * with ID of at least one of the ConnectorProfiles stored in this
     * port. If ConnectorProfile that has same ID with the given
     * connector_id does not exist in the list of ConnectorProfile,
     * this operation returns BAD_PARAMTER error.
     *
     * @pre ConnectorProfile::ports that is same ID with given
     * connector_id shall store the valid ports' references.
     *
     * @post disconnect() function invokes the notify_disconnect() for
     * the port that is stored in the first of the
     * ConnectorProfile::ports. If notify_disconnect() call fails for
     * the first port, It tries on calling "notify_disconnect()" in
     * order for ports stored in ConnectorProfile::ports until the
     * operation call is succeeded. If notify_disconnect() succeeded
     * for at least one port, it returns return code from
     * notify_disconnect(). If none of notify_connect() call
     * succeeded, it returns RTC_ERROR error.
     *
     * @param connector_id The ID of the ConnectorProfile.
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t disconnect(const char* connector_id)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³������Τ�Ԥ�
     *
     * ���Υ��ڥ졼�����ϡ�Port�֤���³������Ԥ���ݤˡ�Port�֤���
     * ��Ū�˸ƤФ�륪�ڥ졼�����Ǥ��ꡢ�̾異�ץꥱ�������ץ���
     * ��䡢 Port �ʳ��� RTC ��Ϣ���֥�������������ƤӽФ���뤳�Ȥ�
     * ���ꤵ��Ƥ��ʤ���
     *
     * notify_disconnect() ���Τϥƥ�ץ졼�ȥ᥽�åɥѥ�����Ȥ��ơ���
     * �֥��饹�Ǽ�������뤳�Ȥ������ unsubscribeInterfaces() �ؿ���
     * �����ǸƤӽФ��������μ��ϰʲ����̤�Ǥ��롣
     *
     * - ConnectorProfile �θ���
     * - ���� Port �� notify_disconnect() �ƤӽФ�
     * - unsubscribeInterfaces()
     * - ConnectorProfile �κ��
     *
     * notify_disconnect() �� ConnectorProfile::ports �˳�Ǽ����Ƥ���
     * Port �ν���˽��äơ����������ɾ��˸ƤӽФ���Ԥ����Ȥˤ�ꡢ��
     * ³�β���򤹤٤Ƥ� Port �����Τ��롣
     *
     * @pre Port ��Ϳ����줿 connector_id ���б����� ConnectorProfile
     * ���ݻ����Ƥ��ʤ���Фʤ�ʤ���
     *
     * @post connector_id ���б����� ConnectorProfile �����Ĥ���ʤ���
     * ���BAD_PARAMETER ���顼���֤���
     *
     * @post ���������ɸƤӽФ���Ԥ��ݤˤ� ConnectorProfile::ports ��
     * �ݻ�����Ƥ��� Port �λ��ȥꥹ�ȤΤ��������Ȥλ��Ȥμ��λ��Ȥ���
     * ���� notify_disconnect() ��ƤӽФ��������θƤӽФ����㳰��ȯ��
     * �������ˤϡ��ƤӽФ��򥹥��åפ��ꥹ�Ȥμ��λ��Ȥ��Ф���
     * notify_disconnect() ��ƤӽФ�����Ĥ�ƤӽФ����������ʤ���硢
     * RTC_ERROR ���顼�����ɤ��֤���
     *
     * @post �ʤ���ConnectorProfile::ports �Υꥹ�Ȥκǽ� Port ��
     * notify_disconnet() ����λ���������Ǥϡ����٤Ƥδ�Ϣ���� Port ��
     * notify_disconnect() �θƤӽФ�����λ���롣
     * 
     * @param connector_id ConnectorProfile �� ID
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Notify the Ports disconnection
     *
     * This operation is invoked between Ports internally when the
     * connection is destroied. Generally it is not premised on
     * calling from application programs or RTC objects except Port
     * object.
     *
     * According to the template method pattern, the
     * notify_disconnect() calls unsubsctiveInterfaces() function,
     * which are premised on implementing in the subclasses. The
     * processing sequence is as follows.
     *
     * - Searching ConnectorProfile
     * - Calling notify_disconnect() for the next port
     * - Unsubscribing interfaces
     * - Deleting ConnectorProfile
     *
     * notify_disconnect() notifies disconnection to all the ports by
     * cascaded call to the stored ports in the
     * ConnectorProfile::ports in order.
     *
     * @pre The port shall store the ConnectorProfile having same id
     * with connector_id.
     *
     * @post If ConnectorProfile of same ID with connector_id does not
     * exist, it returns BAD_PARAMETER error.
     *
     * @post For the cascaded call, this operation calls
     * noify_disconnect() for the port that is stored in the next of
     * this port in the ConnectorProfile::ports.  If the operation
     * call raises exception for some failure, it tries to call
     * notify_disconnect() and skips until the operation succeeded.
     * If none of operation call succeeded, it returns RTC_ERROR.
     *
     * @post At the end of notify_disconnect() operation for the first
     * port stored in the ConnectorProfile::ports sequence, the
     * related ports' notify_disconnect() invocations complete.
     *
     * @param connector_id The ID of the ConnectorProfile.
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t notify_disconnect(const char* connector_id)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ������³��������
     *
     * ���Υ��ڥ졼�����Ϥ��� Port �˴�Ϣ�������Ƥ���³�������롣
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Disconnect the All Ports
     *
     * This operation destroys all connections associated with this Port.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t disconnect_all()
      throw (CORBA::SystemException);
    
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
    virtual void activateInterfaces() = 0;

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
    virtual void deactivateInterfaces() = 0;

    /*!
     * @if jp
     * @brief Port ��̾�������ꤹ��
     *
     * Port ��̾�������ꤹ�롣����̾���� Port ���ݻ����� PortProfile.name
     * ��ȿ�Ǥ���롣
     *
     * @param name Port ��̾��
     *
     * @else
     * @brief Set the name of this Port
     *
     * This operation sets the name of this Port. The given Port's name is
     * applied to Port's PortProfile.name.
     *
     * @param name The name of this Port.
     *
     * @endif
     */
    void setName(const char* name);

     /*!
     * @if jp
     * @brief Port ��̾�����������
     *
     * Port ��̾����������롣
     *
     * @return Port ��̾��
     *
     * @else
     * @brief Get the name of this Port
     *
     * This operation returns the name of this Port.
     *
     * @return The name of this Port.
     *
     * @endif
     */
   const char* getName() const;

    /*!
     * @if jp
     * @brief PortProfile���������
     *
     * Port���ݻ����� PortProfile �� const ���Ȥ��֤���
     *
     * @return ���� Port �� PortProfile
     *
     * @else
     * @brief Get the PortProfile of the Port
     *
     * This operation returns const reference of the PortProfile.
     *
     * @return PortProfile of the Port
     *
     * @endif
     */
    const PortProfile& getProfile() const;
    
    /*!
     * @if jp
     *
     * @brief Port �Υ��֥������Ȼ��Ȥ����ꤹ��
     *
     * ���Υ��ڥ졼������ Port �� PortProfile �ˤ��� Port ���Ȥ�
     * ���֥������Ȼ��Ȥ����ꤹ�롣
     *
     * @param port_ref ���� Port �Υ��֥������Ȼ���
     *
     * @else
     *
     * @brief Set the object reference of this Port
     *
     * This operation sets the object reference itself
     * to the Port's PortProfile.
     *
     * @param port_ref The object reference of this Port.
     *
     * @endif
     */
    void setPortRef(PortService_ptr port_ref);
    
    /*!
     * @if jp
     *
     * @brief Port �Υ��֥������Ȼ��Ȥ��������
     *
     * ���Υ��ڥ졼������ Port �� PortProfile ���ݻ����Ƥ���
     * ���� Port ���ȤΥ��֥������Ȼ��Ȥ�������롣
     *
     * @return ���� Port �Υ��֥������Ȼ���
     *
     * @else
     *
     * @brief Get the object reference of this Port
     *
     * This operation returns the object reference
     * that is stored in the Port's PortProfile.
     *
     * @return The object reference of this Port.
     *
     * @endif
     */
    PortService_ptr getPortRef();
    
    /*!
     * @if jp
     *
     * @brief Port �� owner �� RTObject ����ꤹ��
     *
     * ���Υ��ڥ졼������ Port �� PortProfile.owner �����ꤹ�롣
     *
     * @param owner ���� Port ���ͭ���� RTObject �λ���
     *
     * @else
     *
     * @brief Set the owner RTObject of the Port
     *
     * This operation sets the owner RTObject of this Port.
     *
     * @param owner The owner RTObject's reference of this Port
     *
     * @endif
     */
    void setOwner(RTObject_ptr owner);

    //============================================================
    // callbacks
    //============================================================
    /*!
     * @if jp
     *
     * @brief ���󥿡��ե��������������ݤ˸ƤФ�륳����Хå��򥻥åȤ���
     *
     * ���Υ��ڥ졼�����ϡ����Υݡ��Ȥ���³���ˡ��ݡ��ȼ��Ȥ����ĥ���
     * �ӥ����󥿡��ե����������������륿���ߥ󥰤ǸƤФ�륳����Х�
     * ���ե��󥯥��򥻥åȤ��롣
     *
     * ������Хå��ե��󥯥��ν�ͭ���ϡ��ƤӽФ�¦�ˤ��ꡢ���֥�������
     * ��ɬ�פʤ��ʤä����˲��Τ���ΤϸƤӽФ�¦����Ǥ�Ǥ��롣
     *
     * ���Υ�����Хå��ե��󥯥��ϡ�PortBase���饹�β��۴ؿ��Ǥ���
     * publishInterfaces() ���ƤФ줿���Ȥˡ�Ʊ������ ConnectorProfile ��
     * �Ȥ�˸ƤӽФ���롣���Υ�����Хå������Ѥ��ơ�
     * publishInterfaces() ���������� ConnectorProfile ���ѹ����뤳�Ȥ���
     * ǽ�Ǥ��뤬����³�ط���������򾷤��ʤ��褦��ConnectorProfile ��
     * �ѹ��ˤ���դ��פ��롣
     *
     * @param on_publish ConnectionCallback �Υ��֥��饹���֥������ȤΥݥ���
     *
     * @else
     *
     * @brief Setting callback called on publish interfaces
     *
     * This operation sets a functor that is called after publishing
     * interfaces process when connecting between ports.
     *
     * Since the ownership of the callback functor object is owned by
     * the caller, it has the responsibility of object destruction.
     * 
     * The callback functor is called after calling
     * publishInterfaces() that is virtual member function of the
     * PortBase class with an argument of ConnectorProfile type that
     * is same as the argument of publishInterfaces() function.
     * Although by using this functor, you can modify the ConnectorProfile
     * published by publishInterfaces() function, the modification
     * should be done carefully for fear of causing connection
     * inconsistency.
     *
     * @param on_publish a pointer to ConnectionCallback's subclasses
     *
     * @endif
     */
    void setOnPublishInterfaces(ConnectionCallback* on_publish);

    /*!
     * @if jp
     *
     * @brief ���󥿡��ե��������������ݤ˸ƤФ�륳����Хå��򥻥åȤ���
     *
     * ���Υ��ڥ졼�����ϡ����Υݡ��Ȥ���³���ˡ����Υݡ��Ȥ����ĥ���
     * �ӥ����󥿡��ե����������������륿���ߥ󥰤ǸƤФ�륳����Х�
     * ���ե��󥯥��򥻥åȤ��롣
     *
     * ������Хå��ե��󥯥��ν�ͭ���ϡ��ƤӽФ�¦�ˤ��ꡢ���֥�������
     * ��ɬ�פʤ��ʤä����˲��Τ���ΤϸƤӽФ�¦����Ǥ�Ǥ��롣
     *
     * ���Υ�����Хå��ե��󥯥��ϡ�PortBase���饹�β��۴ؿ��Ǥ���
     * subscribeInterfaces() ���ƤФ�����ˡ�Ʊ������ ConnectorProfile ��
     * �Ȥ�˸ƤӽФ���롣���Υ�����Хå������Ѥ��ơ�
     * subscribeInterfaces() ��Ϳ���� ConnectorProfile ���ѹ����뤳�Ȥ���
     * ǽ�Ǥ��뤬����³�ط���������򾷤��ʤ��褦��ConnectorProfile ��
     * �ѹ��ˤ���դ��פ��롣
     *
     * @param on_subscribe ConnectionCallback �Υ��֥��饹���֥������ȤΥݥ���
     *
     * @else
     *
     * @brief Setting callback called on publish interfaces
     *
     * This operation sets a functor that is called before subscribing
     * interfaces process when connecting between ports.
     *
     * Since the ownership of the callback functor object is owned by
     * the caller, it has the responsibility of object destruction.
     * 
     * The callback functor is called before calling
     * subscribeInterfaces() that is virtual member function of the
     * PortBase class with an argument of ConnectorProfile type that
     * is same as the argument of subscribeInterfaces() function.
     * Although by using this functor, you can modify ConnectorProfile
     * argument for subscribeInterfaces() function, the modification
     * should be done carefully for fear of causing connection
     * inconsistency.
     *
     * @param on_subscribe a pointer to ConnectionCallback's subclasses
     *
     * @endif
     */
    void setOnSubscribeInterfaces(ConnectionCallback* on_subscribe);

    /*!
     * @if jp
     *
     * @brief ��³��λ���˸ƤФ�륳����Хå��򥻥åȤ���
     *
     * ���Υ��ڥ졼�����ϡ����Υݡ��Ȥ���³��λ���˸ƤФ�롢������Х�
     * ���ե��󥯥��򥻥åȤ��롣
     *
     * ������Хå��ե��󥯥��ν�ͭ���ϡ��ƤӽФ�¦�ˤ��ꡢ���֥�������
     * ��ɬ�פʤ��ʤä����˲��Τ���ΤϸƤӽФ�¦����Ǥ�Ǥ��롣
     *
     * ���Υ�����Хå��ե��󥯥��ϡ��ݡ��Ȥ���³�¹Դؿ��Ǥ���
     * notify_connect() �ν�λľ���ˡ���³���������ｪλ����ݤ˸¤ä�
     * �ƤӽФ���륳����Хå��Ǥ��롣��³�����β����ǥ��顼��ȯ������
     * ���ˤϸƤӽФ���ʤ���
     * 
     * ���Υ�����Хå��ե��󥯥��� notify_connect() �� out �ѥ�᡼��
     * �Ȥ����֤��Τ�Ʊ������ ConnectorProfile �ȤȤ�˸ƤӽФ����Τǡ�
     * ������³�ˤ����Ƹ������줿���٤ƤΥ��󥿡��ե�������������뤳��
     * ���Ǥ��롣���Υ�����Хå������Ѥ��ơ�notify_connect() ���֤�
     * ConnectorProfile ���ѹ����뤳�Ȥ���ǽ�Ǥ��뤬����³�ط���������
     * �򾷤��ʤ��褦��ConnectorProfile ���ѹ��ˤ���դ��פ��롣
     *
     * @param on_subscribe ConnectionCallback �Υ��֥��饹���֥������ȤΥݥ���
     *
     * @else
     *
     * @brief Setting callback called on connection established
     *
     * This operation sets a functor that is called when connection
     * between ports established.
     *
     * Since the ownership of the callback functor object is owned by
     * the caller, it has the responsibility of object destruction.
     * 
     * The callback functor is called only when notify_connect()
     * function successfully returns. In case of error, the functor
     * will not be called.
     *
     * Since this functor is called with ConnectorProfile argument
     * that is same as out-parameter of notify_connect() function, you
     * can get all the information of published interfaces of related
     * ports in the connection.  Although by using this functor, you
     * can modify ConnectorProfile argument for out-paramter of
     * notify_connect(), the modification should be done carefully for
     * fear of causing connection inconsistency.
     *
     * @param on_subscribe a pointer to ConnectionCallback's subclasses
     *
     * @endif
     */
    void setOnConnected(ConnectionCallback* on_connected);

    /*!
     * @if jp
     *
     * @brief ���󥿡��ե��������������ݤ˸ƤФ�륳����Хå��򥻥åȤ���
     *
     * ���Υ��ڥ졼�����ϡ����Υݡ��Ȥ���³���ˡ����Υݡ��Ȥ����ĥ���
     * �ӥ����󥿡��ե����������������륿���ߥ󥰤ǸƤФ�륳����Х�
     * ���ե��󥯥��򥻥åȤ��롣
     *
     * ������Хå��ե��󥯥��ν�ͭ���ϡ��ƤӽФ�¦�ˤ��ꡢ���֥�������
     * ��ɬ�פʤ��ʤä����˲��Τ���ΤϸƤӽФ�¦����Ǥ�Ǥ��롣
     *
     * ���Υ�����Хå��ե��󥯥��ϡ�PortBase���饹�β��۴ؿ��Ǥ���
     * unsubscribeInterfaces() ���ƤФ�����ˡ�Ʊ������ ConnectorProfile ��
     * �Ȥ�˸ƤӽФ���롣���Υ�����Хå������Ѥ��ơ�
     * unsubscribeInterfaces() ��Ϳ���� ConnectorProfile ���ѹ����뤳�Ȥ���
     * ǽ�Ǥ��뤬����³�ط���������򾷤��ʤ��褦��ConnectorProfile ��
     * �ѹ��ˤ���դ��פ��롣
     *
     * @param on_unsubscribe ConnectionCallback �Υ��֥��饹���֥�����
     * �ȤΥݥ���
     *
     * @else
     *
     * @brief Setting callback called on unsubscribe interfaces
     *
     * This operation sets a functor that is called before unsubscribing
     * interfaces process when disconnecting between ports.
     *
     * Since the ownership of the callback functor object is owned by
     * the caller, it has the responsibility of object destruction.
     * 
     * The callback functor is called before calling
     * unsubscribeInterfaces() that is virtual member function of the
     * PortBase class with an argument of ConnectorProfile type that
     * is same as the argument of unsubscribeInterfaces() function.
     * Although by using this functor, you can modify ConnectorProfile
     * argument for unsubscribeInterfaces() function, the modification
     * should be done carefully for fear of causing connection
     * inconsistency.
     *
     * @param on_unsubscribe a pointer to ConnectionCallback's subclasses
     *
     * @endif
     */
    void setOnUnsubscribeInterfaces(ConnectionCallback* on_subscribe);

    /*!
     * @if jp
     *
     * @brief ��³����˸ƤФ�륳����Хå��򥻥åȤ���
     *
     * ���Υ��ڥ졼�����ϡ����Υݡ��Ȥ���³������˸ƤФ�롢������Х�
     * ���ե��󥯥��򥻥åȤ��롣
     *
     * ������Хå��ե��󥯥��ν�ͭ���ϡ��ƤӽФ�¦�ˤ��ꡢ���֥�������
     * ��ɬ�פʤ��ʤä����˲��Τ���ΤϸƤӽФ�¦����Ǥ�Ǥ��롣
     *
     * ���Υ�����Хå��ե��󥯥��ϡ��ݡ��Ȥ���³����¹Դؿ��Ǥ���
     * notify_disconnect() �ν�λľ���ˡ��ƤӽФ���륳����Хå��Ǥ��롣
     * 
     * ���Υ�����Хå��ե��󥯥�����³���б����� ConnectorProfile �Ȥ�
     * ��˸ƤӽФ���롣���� ConnectorProfile �Ϥ��Υե��󥯥��ƽФ���
     * ���˴������Τǡ��ѹ����ۤ��˱ƶ���Ϳ���뤳�ȤϤʤ���
     *
     * @param on_disconnected ConnectionCallback �Υ��֥��饹���֥�����
     * �ȤΥݥ���
     *
     * @else
     *
     * @brief Setting callback called on disconnected
     *
     * This operation sets a functor that is called when connection
     * between ports is destructed.
     *
     * Since the ownership of the callback functor object is owned by
     * the caller, it has the responsibility of object destruction.
     * 
     * The callback functor is called just before notify_disconnect()
     * that is disconnection execution function returns.
     *
     * This functor is called with argument of corresponding
     * ConnectorProfile.  Since this ConnectorProfile will be
     * destructed after calling this functor, modifications never
     * affect others.
     *
     * @param on_disconnected a pointer to ConnectionCallback's subclasses
     *
     * @endif
     */
    void setOnDisconnected(ConnectionCallback* on_disconnected);

    /*!
     * @if jp
     * @brief �ݡ��Ȥ���³�����Ȥ������˸ƤӽФ���륳����Хå��򥻥åȤ���
     *
     * ���Υ��ڥ졼�����ϡ����Υݡ��Ȥ���³�����Ȥ������˸ƤФ�롢
     * ������Хå��ե��󥯥��򥻥åȤ��롣
     *
     * InPort�ϡ����¦OutPort�Ȥ�
     * ��³����Ȥ�����硢��³����Ū�����Ǥ���Τǡ�
     * ����³�� OnDisconnect ������Хå����ƤӽФ���롣
     *
     * @param on_connection_lost ConnectionCallback �Υ��֥��饹���֥�����
     * �ȤΥݥ���
     *
     * @else
     * @brief Setting callback called on connection lost
     *
     * This operation sets a functor that is called when connection
     * of this port does lost. 
     *
     * @param on_connection_lost a pointer to ConnectionCallback's subclasses
     *
     * @endif
     */
    void setOnConnectionLost(ConnectionCallback* on_connection_lost);

    /*!
     * @if jp
     * @brief PortConnectListeners �Υۥ���򥻥åȤ���
     *
     * �ݡ��Ȥ���³�˴ؤ���ꥹ�ʷ����ݻ�����ۥ�����饹�ؤΥݥ��󥿤�
     * ���åȤ��롣���δؿ����̾�Ƥ�RTObject����ƤФ졢RTObject������
     * �ۥ�����饹�ؤΥݥ��󥿤����åȤ���롣
     *
     * @param portconnListeners PortConnectListeners ���֥������ȤΥݥ���
     *
     * @else
     * @brief Setting PortConnectListener holder
     *
     * This operation sets a functor that is called when connection
     * of this port does lost. 
     *
     * @param on_connection_lost a pointer to ConnectionCallback's subclasses
     *
     * @endif
     */
    void setPortConnectListenerHolder(PortConnectListeners* portconnListeners);

    //============================================================
    // protected operations
    //============================================================
  protected:
    /*! @if jp
     *
     * @brief Interface ������������
     *
     * ���Υ��ڥ졼�����ϡ�notify_connect() �����������󥹤λϤ�˥�����
     * ������貾�۴ؿ��Ǥ��롣
     * notify_connect() �Ǥϡ�
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * �ν�� protected �ؿ��������뤵����³�������Ԥ��롣
     * <br>
     * ��� Port �ǤϤ��Υ��ڥ졼�����򥪡��С��饤�ɤ��������Ȥ���
     * Ϳ����줿 ConnectorProfile �˽���������Ԥ����ѥ�᡼������Ŭ��
     * �Ǥ���С�RteurnCode_t ���Υ��顼�����ɤ��֤���
     * �̾� publishInterafaces() ��ˤ����Ƥϡ����� Port ��°����
     * ���󥿡��ե������˴ؤ������� ConnectorProfile ���Ф���Ŭ�ڤ����ꤷ
     * ¾�� Port �����Τ��ʤ���Фʤ�ʤ���
     * <br>
     * �ޤ������δؿ��������뤵����ʳ��Ǥϡ�¾�� Port �� Interface �˴ؤ���
     * ����Ϥ��٤ƴޤޤ�Ƥ��ʤ��Τǡ�¾�� Port �� Interface ������������
     * �� subscribeInterfaces() ��ǹԤ���٤��Ǥ��롣
     * <br>
     * ���Υ��ڥ졼�����ϡ������� connector_id ���Ф��Ƥ���³��������
     * ��¸�� connector_id ���Ф��ƤϹ�����Ŭ�ڤ˹Ԥ���ɬ�פ����롣
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Publish interface information
     *
     * This operation is pure virutal function that would be called at the
     * beginning of the notify_connect() process sequence.
     * In the notify_connect(), the following methods would be called in order.
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile() 
     *
     * In the concrete Port, this method should be overridden. This method
     * processes the given ConnectorProfile argument and if the given parameter
     * is invalid, it would return error code of ReturnCode_t.
     * Usually, publishInterfaces() method should set interfaces information
     * owned by this Port, and publish it to the other Ports.
     * <br>
     * When this method is called, other Ports' interfaces information may not
     * be completed. Therefore, the process to obtain other Port's interfaces
     * information should be done in the subscribeInterfaces() method.
     * <br>
     * This operation should create the new connection for the new
     * connector_id, and should update the connection for the existing
     * connection_id.
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile) = 0;
    
    /*!
     * @if jp
     *
     * @brief ���� Port ���Ф��� notify_connect() �򥳡��뤹��
     *
     * ConnectorProfile �� port_ref ��˳�Ǽ����Ƥ��� Port �Υ��֥�������
     * ��ե���󥹤Υ������󥹤��椫�顢���Ȥ� Port �μ��� Port ���Ф���
     * notify_connect() �򥳡��뤹�롣
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Call notify_connect() of the next Port
     *
     * This operation calls the notify_connect() of the next Port's 
     * that stored in ConnectorProfile's port_ref sequence.
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t connectNext(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief ���� Port ���Ф��� notify_disconnect() �򥳡��뤹��
     *
     * ConnectorProfile �� port_ref ��˳�Ǽ����Ƥ��� Port �Υ��֥�������
     * ��ե���󥹤Υ������󥹤��椫�顢���Ȥ� Port �μ��� Port ���Ф���
     * notify_disconnect() �򥳡��뤹�롣
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Call notify_disconnect() of the next Port
     *
     * This operation calls the notify_disconnect() of the next Port's 
     * that stored in ConnectorProfile's port_ref sequence.
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t disconnectNext(ConnectorProfile& connector_profile);
    
    /*! @if jp
     *
     * @brief Interface ������������
     *
     * ���Υ��ڥ졼�����ϡ�notify_connect() �����������󥹤���֤˥�����
     * ������貾�۴ؿ��Ǥ��롣
     * notify_connect() �Ǥϡ�
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * �ν�� protected �ؿ��������뤵����³�������Ԥ��롣
     * <br>
     * ��� Port �ǤϤ��Υ��ڥ졼�����򥪡��С��饤�ɤ��������Ȥ���
     * Ϳ����줿 ConnectorProfile �˽���������Ԥ����ѥ�᡼������Ŭ��
     * �Ǥ���С�RteurnCode_t ���Υ��顼�����ɤ��֤���
     * ���� ConnectorProfile �ˤ�¾�� Port �� Interface �˴ؤ������
     * ���ƴޤޤ�Ƥ��롣
     * �̾� subscribeInterafaces() ��ˤ����Ƥϡ����� Port �����Ѥ���
     * Interface �˴ؤ���������������׵�¦�Υ��󥿡��ե��������Ф���
     * ��������ꤷ�ʤ���Фʤ�ʤ���
     * <br>
     * ���Υ��ڥ졼�����ϡ������� connector_id ���Ф��Ƥ���³��������
     * ��¸�� connector_id ���Ф��ƤϹ�����Ŭ�ڤ˹Ԥ���ɬ�פ����롣
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Publish interface information
     *
     * This operation is pure virutal function that would be called at the
     * mid-flow of the notify_connect() process sequence.
     * In the notify_connect(), the following methods would be called in order.
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * In the concrete Port, this method should be overridden. This method
     * processes the given ConnectorProfile argument and if the given parameter
     * is invalid, it would return error code of ReturnCode_t.
     * The given argument ConnectorProfile includes all the interfaces
     * information in it.
     * Usually, subscribeInterafaces() method obtains information of interfaces
     * from ConnectorProfile, and should set it to the interfaces that require
     * them.
     * <br>
     * This operation should create the new connection for the new
     * connector_id, and should update the connection for the existing
     * connection_id.
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile) = 0;
    
    /*! @if jp
     *
     * @brief Interface ����³��������
     *
     * ���Υ��ڥ졼�����ϡ�notify_disconnect() �����������󥹤ν����˥�����
     * ������貾�۴ؿ��Ǥ��롣
     * notify_disconnect() �Ǥϡ�
     * - disconnectNext()
     * - unsubscribeInterfaces()
     * - eraseConnectorProfile()
     * �ν�� protected �ؿ��������뤵����³����������Ԥ��롣
     * <br>
     * ��� Port �ǤϤ��Υ��ڥ졼�����򥪡��С��饤�ɤ��������Ȥ���
     * Ϳ����줿 ConnectorProfile �˽�����³���������Ԥ���
     *
     * @param connector_profile ��³�˴ؤ���ץ�ե��������
     *
     * @else
     *
     * @brief Disconnect interface connection
     *
     * This operation is pure virutal function that would be called at the
     * end of the notify_disconnect() process sequence.
     * In the notify_disconnect(), the following methods would be called
     * in order to disconnect.
     * - disconnectNext()
     * - unsubscribeInterfaces()
     * - eraseConnectorProfile() 
     *  <br>
     * In the concrete Port, this method should be overridden. This method
     * processes the given ConnectorProfile argument and disconnect interface
     * connection.
     *
     * @param connector_profile The connection profile information
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile) = 0;

    /*! @if jp
     *
     * @brief ��³�κ���������ꤹ�롣
     *
     * @param limit_value �����
     *
     * @else
     *
     * @brief Set the maximum number of connections
     *
     *
     * @param limit_value The maximum number of connections
     *
     * @endif
     */
    virtual void setConnectionLimit(int limit_value);
    
    /*!
     * @if jp
     * @brief Interface������������
     *
     * Interface�����������롣
     *
     *  dataport.dataflow_type
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.
     *
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t _publishInterfaces(void);
    //============================================================
    // protected utility functions
    //============================================================
    /*!
     * @if jp
     *
     * @brief ConnectorProfile �� connector_id �ե�����ɤ������ɤ���Ƚ��
     *
     * ���ꤵ�줿 ConnectorProfile �� connector_id �����Ǥ��뤫�ɤ�����Ƚ���
     * �Ԥ���
     *
     * @param connector_profile Ƚ���оݥ��ͥ����ץ�ե�����
     *
     * @return ������Ϳ����줿 ConnectorProfile �� connector_id �����Ǥ���С�
     *         true�������Ǥʤ���� false ���֤���
     *
     * @else
     *
     * @brief Check whether connector_id of ConnectorProfile is empty
     *
     * Check whether connector_id of specified ConnectorProfile is empty.
     * 
     * @param connector_profile Target ConnectorProfile for the check
     *
     * @return If the given ConnectorProfile's connector_id is empty string,
     *         it returns true.
     *
     * @endif
     */
    bool isEmptyId(const ConnectorProfile& connector_profile) const;
    
    /*!
     * @if jp
     *
     * @brief UUID����������
     *
     * ���Υ��ڥ졼������ UUID ���������롣
     *
     * @return uuid
     *
     * @else
     *
     * @brief Generate the UUID
     *
     * This operation generates UUID.
     *
     * @return uuid
     *
     * @endif
     */
    const std::string getUUID() const;
    
    /*!
     * @if jp
     *
     * @brief UUID�������� ConnectorProfile �˥��åȤ���
     *
     * ���Υ��ڥ졼������ UUID ����������ConnectorProfile �˥��åȤ��롣
     *
     * @param connector_profile connector_id �򥻥åȤ��� ConnectorProfile
     *
     * @else
     *
     * @brief Generate and set the UUID to the ConnectorProfile
     *
     * This operation generates and set UUID to the ConnectorProfile.
     *
     * @param connector_profile ConnectorProfile to be set connector_id
     *
     * @endif
     */
    void setUUID(ConnectorProfile& connector_profile) const;
    
    /*!
     * @if jp
     *
     * @brief id ����¸�� ConnectorProfile �Τ�Τ��ɤ���Ƚ�ꤹ��
     *
     * ���Υ��ڥ졼������Ϳ����줿 ID ����¸�� ConnectorProfile �Υꥹ�����
     * ¸�ߤ��뤫�ɤ���Ƚ�ꤹ�롣
     *
     * @param id Ƚ�ꤹ�� connector_id
     *
     * @return id ��¸��Ƚ����
     *
     * @else
     *
     * @brief Check whether the given id exists in stored ConnectorProfiles
     *
     * This operation returns boolean whether the given id exists in 
     * the Port's ConnectorProfiles.
     *
     * @param id connector_id to be find in Port's ConnectorProfiles
     *
     * @return id exestance resutl
     *
     * @endif
     */
    bool isExistingConnId(const char* id);
    
    /*!
     * @if jp
     *
     * @brief id ����� ConnectorProfile ��õ��
     *
     * ���Υ��ڥ졼������Ϳ����줿 ID ����� ConnectorProfile �� Port ��
     * ��� ConnectorProfile �Υꥹ���椫��õ����
     * �⤷��Ʊ��� id ����� ConnectorProfile ���ʤ���С����� ConnectorProfile
     * ���֤���롣
     *
     * @param id �������� connector_id
     *
     * @return connector_id ����� ConnectorProfile
     *
     * @else
     *
     * @brief Find ConnectorProfile with id
     *
     * This operation returns ConnectorProfile with the given id from Port's
     * ConnectorProfiles' list.
     * If the ConnectorProfile with connector id that is identical with the
     * given id does not exist, empty ConnectorProfile is returned.
     *
     * @param id the connector_id to be searched in Port's ConnectorProfiles
     *
     * @return CoonectorProfile with connector_id
     *
     * @endif
     */
    ConnectorProfile findConnProfile(const char* id);
    
    /*!
     * @if jp
     *
     * @brief id ����� ConnectorProfile ��õ��
     *
     * ���Υ��ڥ졼������Ϳ����줿 ID ����� ConnectorProfile �� Port ��
     * ��� ConnectorProfile �Υꥹ���椫��õ������ǥå������֤���
     * �⤷��Ʊ��� id ����� ConnectorProfile ���ʤ���С�-1 ���֤���
     *
     * @param id �������� connector_id
     *
     * @return Port �� ConnectorProfile �ꥹ�ȤΥ���ǥå���
     *
     * @else
     *
     * @brief Find ConnectorProfile with id
     *
     * This operation returns ConnectorProfile with the given id from Port's
     * ConnectorProfiles' list.
     * If the ConnectorProfile with connector id that is identical with the
     * given id does not exist, -1 is returned.
     *
     * @param id the connector_id to be searched
     *
     * @return The index of ConnectorProfile of the Port
     *
     * @endif
     */
    CORBA::Long findConnProfileIndex(const char* id);
    
    /*!
     * @if jp
     *
     * @brief ConnectorProfile ���ɲä⤷���Ϲ���
     *
     * ���Υ��ڥ졼������Ϳ����줿 ConnectorProfile �� Port ���ɲä⤷����
     * ������¸���롣
     * Ϳ����줿 ConnectorProfile �� connector_id ��Ʊ�� ID �����
     * ConnectorProfile ���ꥹ�Ȥˤʤ���С��ꥹ�Ȥ��ɲä���
     * Ʊ�� ID ��¸�ߤ���� ConnectorProfile ������¸���롣
     *
     * @param connector_profile �ɲä⤷���Ϲ������� ConnectorProfile
     *
     * @else
     *
     * @brief Append or update the ConnectorProfile list
     *
     * This operation appends or updates ConnectorProfile of the Port
     * by the given ConnectorProfile.
     * If the connector_id of the given ConnectorProfile does not exist
     * in the Port's ConnectorProfile list, the given ConnectorProfile would be
     * append to the list. If the same id exists, the list would be updated.
     *
     * @param connector_profile the ConnectorProfile to be appended or updated
     *
     * @endif
     */
    void updateConnectorProfile(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief ConnectorProfile ��������
     *
     * ���Υ��ڥ졼������ Port �� PortProfile ���ݻ����Ƥ���
     * ConnectorProfileList �Τ���Ϳ����줿 id ����� ConnectorProfile
     * �������롣
     *
     * @param id ������� ConnectorProfile �� id
     *
     * @return ����˺���Ǥ������� true��
     *         ���ꤷ�� ConnectorProfile �����Ĥ���ʤ����� false ���֤�
     *
     * @else
     *
     * @brief Delete the ConnectorProfile
     *
     * This operation deletes a ConnectorProfile specified by id from
     * ConnectorProfileList owned by PortProfile of this Port.
     *
     * @param id The id of the ConnectorProfile to be deleted.
     *
     * @return true would be returned if it deleted correctly.
     *         false woluld be returned if specified ConnectorProfile
     *         cannot be found.
     *
     * @endif
     */
    bool eraseConnectorProfile(const char* id);
    
    /*!
     * @if jp
     *
     * @brief PortInterfaceProfile �� ���󥿡��ե���������Ͽ����
     *
     * ���Υ��ڥ졼������ Port ������ PortProfile �Ρ�PortInterfaceProfile
     * �˥��󥿡��ե������ξ�����ɲä��롣
     * ���ξ���ϡ�get_port_profile() �ˤ�ä������� PortProfile �Τ���
     * PortInterfaceProfile ���ͤ��ѹ�����ΤߤǤ��ꡢ�ºݤ˥��󥿡��ե�������
     * �󶡤������׵ᤷ���ꤹ����ˤϡ����֥��饹�ǡ� publishInterface() ,
     *  subscribeInterface() ���δؿ���Ŭ�ڤ˥����С��饤�ɤ����󥿡��ե�������
     * �󶡡��׵������Ԥ�ʤ���Фʤ�ʤ���
     *
     * ���󥿡��ե�����(�Υ��󥹥���)̾�� Port ��ǰ�դǤʤ���Фʤ�ʤ���
     * Ʊ̾�Υ��󥿡��ե����������Ǥ���Ͽ����Ƥ����硢���δؿ��� false ��
     * �֤���
     *
     * @param name ���󥿡��ե������Υ��󥹥��󥹤�̾��
     * @param type_name ���󥿡��ե������η���̾��
     * @param pol ���󥿡��ե�������°�� (RTC::PROVIDED �⤷���� RTC:REQUIRED)
     *
     * @return ���󥿡��ե�������Ͽ������̡�
     *         Ʊ̾�Υ��󥿡��ե�������������Ͽ����Ƥ���� false ���֤���
     *
     * @else
     *
     * @brief Append an interface to the PortInterfaceProfile
     *
     * This operation appends interface information to the PortInterfaceProfile
     * that is owned by the Port.
     * The given interfaces information only updates PortInterfaceProfile of
     * PortProfile that is obtained through get_port_profile().
     * In order to provide and require interfaces, proper functions (for
     * example publishInterface(), subscribeInterface() and so on) should be
     * overridden in subclasses, and these functions provide concrete interface
     * connection and disconnection functionality.
     *
     * The interface (instance) name have to be unique in the Port.
     * If the given interface name is identical with stored interface name,
     * this function returns false.
     *
     * @param name The instance name of the interface.
     * @param type_name The type name of the interface.
     * @param pol The interface's polarity (RTC::PROVIDED or RTC:REQUIRED)
     *
     * @return false would be returned if the same name is already registered.
     *
     * @endif
     */
    bool appendInterface(const char* name, const char* type_name,
			 PortInterfacePolarity pol);
    
    /*!
     * @if jp
     *
     * @brief PortInterfaceProfile ���饤�󥿡��ե�������Ͽ��������
     *
     * ���Υ��ڥ졼������ Port ������ PortProfile �Ρ�PortInterfaceProfile
     * ���饤�󥿡��ե������ξ���������롣
     *
     * @param name ���󥿡��ե������Υ��󥹥��󥹤�̾��
     * @param pol ���󥿡��ե�������°�� (RTC::PROVIDED �⤷���� RTC:REQUIRED)
     *
     * @return ���󥿡��ե��������������̡�
     *         ���󥿡��ե���������Ͽ����Ƥ��ʤ���� false ���֤���
     *
     * @else
     *
     * @brief Delete the interface registration from the PortInterfaceProfile
     *
     * This operation deletes interface information from the
     * PortInterfaceProfile that is owned by the Port.
     *
     * @param name The instance name of the interface.
     * @param pol The interface's polarity (RTC::PROVIDED or RTC:REQUIRED)
     *
     * @return Delete processing result of interface.
     *         false would be returned if the given name is not registered.
     *
     * @endif
     */
    bool deleteInterface(const char* name, PortInterfacePolarity pol);
    
    /*!
     * @if jp
     *
     * @brief PortProfile �� properties �� NameValue �ͤ��ɲä���
     *
     * PortProfile �� properties �� NameValue �ͤ��ɲä��롣
     * �ɲä���ǡ����η���ValueType�ǻ��ꤹ�롣
     *
     * @param key properties �� name
     * @param value properties �� value
     *
     * @else
     *
     * @brief Add NameValue data to PortProfile's properties
     *
     * Add NameValue data to PortProfile's properties.
     * Type of additional data is specified by ValueType.
     *
     * @param key The name of properties
     * @param value The value of properties
     *
     * @endif
     */
    template <class ValueType>
    void addProperty(const char* key, ValueType value)
    {
      CORBA_SeqUtil::push_back(m_profile.properties,
			       NVUtil::newNV(key, value));
    }

    /*!
     * @if jp
     *
     * @brief PortProfile �� properties �� NameValue �ͤ����Ǥ��ɲä���
     *
     * PortProfile �� properties �� NameValue �ͤ����Ǥ��ɲä��롣����
     * �ؿ��ˤ�����ꤵ�줿 properties �� get_prot_profile() �ˤ�곰��
     * ���黲�Ȥ���롣
     *
     * @param key properties �� name
     * @param value properties �� value
     *
     * @else
     *
     * @brief Append NameValue data to PortProfile's properties
     *
     * Append NameValue data to PortProfile's properties.  The
     * properties which are set by this function would be referred
     * through get_port_profile() from outsides.
     *
     * @param key The name of properties
     * @param value The value of properties
     *
     * @endif
     */
    void appendProperty(const char* key, const char* value)
    {
      NVUtil::appendStringValue(m_profile.properties, key, value);
    }
    
  protected:
    /*!
     * @if jp
     *
     * @brief ¸�ߤ��ʤ��ݡ��Ȥ�disconnect���롣
     *
     * ����Port�򸡽Ф����⤷���Ǥ���ݡ��Ȥ����ä����ˤϡ���³��
     * ������롣
     *
     * @else
     *
     * @brief Disconnect ports that doesn't exist. 
     *
     * This function detects dead-port, and if dead ports are found in
     * the connection list, disconnects them.
     *
     * @endif
     */
    void updateConnectors();

    /*!
     * @if jp
     *
     * @brief �ݡ��Ȥ�¸�ߤ��ǧ���롣
     *
     * @param ports ��ǧ����ݡ���
     * @return true:¸�ߤ���,false:¸�ߤ��ʤ�
     *
     * @else
     *
     * @brief Existence of ports
     *
     * @param ports Checked ports
     * @return true:existent,false:non existent
     *
     * @endif
     */
#ifndef ORB_IS_RTORB
    bool checkPorts(::RTC::PortServiceList& ports);
#else // ORB_IS_RTORB
    bool checkPorts(RTC_PortServiceList& ports);
#endif // ORB_IS_RTORB


    inline void onNotifyConnect(const char* portname,
                                RTC::ConnectorProfile& profile)
    {
      if (m_portconnListeners != NULL)
        {
          m_portconnListeners->
            portconnect_[ON_NOTIFY_CONNECT].notify(portname, profile);
        }
    }

    inline void onNotifyDisconnect(const char* portname,
                                   RTC::ConnectorProfile& profile)
    {
      if (m_portconnListeners != NULL)
        {
          m_portconnListeners->
            portconnect_[ON_NOTIFY_DISCONNECT].notify(portname, profile);
        }
    }
    inline void onUnsubscribeInterfaces(const char* portname,
                                        RTC::ConnectorProfile& profile)
    {
      if (m_portconnListeners != NULL)
        {
          m_portconnListeners->
            portconnect_[ON_UNSUBSCRIBE_INTERFACES].notify(portname, profile);
        }
    }

    inline void onPublishInterfaces(const char* portname,
                                    RTC::ConnectorProfile& profile,
                                    ReturnCode_t ret)
    {
      if (m_portconnListeners != NULL)
        {
          m_portconnListeners->
            portconnret_[ON_PUBLISH_INTERFACES].notify(portname,
                                                       profile, ret);
        }
    }

    inline void onConnectNextport(const char* portname,
                                  RTC::ConnectorProfile& profile,
                                  ReturnCode_t ret)
    {
      if (m_portconnListeners != NULL)
        {
          m_portconnListeners->
            portconnret_[ON_CONNECT_NEXTPORT].notify(portname,
                                                     profile, ret);
        }
    }

    inline void onSubscribeInterfaces(const char* portname,
                                      RTC::ConnectorProfile& profile,
                                      ReturnCode_t ret)
    {
      if (m_portconnListeners != NULL)
        {
          m_portconnListeners->
            portconnret_[ON_SUBSCRIBE_INTERFACES].notify(portname,
                                                         profile, ret);
        }
    }

    inline void onConnected(const char* portname,
                            RTC::ConnectorProfile& profile,
                            ReturnCode_t ret)
    {
      if (m_portconnListeners != NULL)
        {
          m_portconnListeners->
            portconnret_[ON_CONNECTED].notify(portname, profile, ret);
        }
    }

    inline void onDisconnectNextport(const char* portname,
                                 RTC::ConnectorProfile& profile,
                                 ReturnCode_t ret)
    {
      if (m_portconnListeners != NULL)
        {
          m_portconnListeners->
            portconnret_[ON_DISCONNECT_NEXT].notify(portname, profile, ret);
        }
    }

    inline void onDisconnected(const char* portname,
                               RTC::ConnectorProfile& profile,
                               ReturnCode_t ret)
    {
      if (m_portconnListeners != NULL)
        {
          m_portconnListeners->
            portconnret_[ON_DISCONNECTED].notify(portname, profile, ret);
        }
    }

  protected:
    /*!
     * @if jp
     * @brief �������ȥ꡼��
     * @else
     * @brief Logger stream
     * @endif
     */
    mutable Logger rtclog;
    /*!
     * @if jp
     * @brief Port �� PortProfile
     * @else
     * @brief PortProfile of the Port
     * @endif
     */
    PortProfile m_profile;
    
    /*!
     * @if jp
     * @brief Port �� ���֥������Ȼ���
     * @else
     * @brief Object Reference of the Port
     * @endif
     */
    RTC::PortService_var m_objref;
    /*!
     * @if jp
     * @brief PortProfile �� mutex
     * @else
     * @brief Mutex of PortProfile
     * @endif
     */
    mutable coil::Mutex m_profile_mutex;
    mutable coil::Mutex m_connectorsMutex;
    typedef coil::Guard<coil::Mutex> Guard;

    /*!
     * @if jp
     * @brief ���󥹥���̾
     * @else
     * @brief Instance name
     * @endif
     */
    std::string m_ownerInstanceName;

    /*!
     * @if jp
     * @brief Port ����³�κ����
     * @else
     * @brief The maximum number of connections
     * @endif
     */
    int m_connectionLimit;
    
    /*!
     * @if jp
     * @brief Callback functor ���֥�������
     *
     * ���󥿡��ե��������������ݤ˸ƤФ�륳����Хå����֥�������
     *
     * @else
     * @brief Callback functor objects
     *
     * This is callback objedct that is called when the interface is opened 
     * to the public.
     *
     * @endif
     */
    ConnectionCallback* m_onPublishInterfaces;
    /*!
     * @if jp
     * @brief Callback functor ���֥�������
     *
     * ���󥿡��ե��������������ݤ˸ƤФ�륳����Хå����֥�������
     *
     * @else
     * @brief Callback functor objects
     *
     * This is callback objedct that is called when the interface is got.
     *
     * @endif
     */
    ConnectionCallback* m_onSubscribeInterfaces;
    /*!
     * @if jp
     * @brief Callback functor ���֥�������
     *
     * ��³��λ���˸ƤФ�륳����Хå����֥�������
     *
     * @else
     * @brief Callback functor objects
     *
     * This is a callback object that is called 
     * when the connection is completed. 
     *
     * @endif
     */
    ConnectionCallback* m_onConnected;
    /*!
     * @if jp
     * @brief Callback functor ���֥�������
     *
     * ���󥿡��ե��������������ݤ˸ƤФ�륳����Хå����֥�������
     *
     * @else
     * @brief Callback functor objects
     *
     * This is a callback object that is called when the interface is released. 
     *
     * @endif
     */
    ConnectionCallback* m_onUnsubscribeInterfaces;
    /*!
     * @if jp
     * @brief Callback functor ���֥�������
     *
     * ��³����˸ƤФ�륳����Хå����֥�������
     *
     * @else
     * @brief Callback functor objects
     *
     * This is a callback object that is called in connected release. 
     *
     * @endif
     */
    ConnectionCallback* m_onDisconnected;

    /*!
     * @if jp
     * @brief Callback functor ���֥�������
     *
     * �ݡ��Ȥ���³�����Ȥ������˸ƤӽФ���륳����Хå����֥�������
     *
     * @else
     * @brief Callback functor objects
     *
     * This is a callback object called when the connection of the port does 
     * lost. 
     *
     * @endif
     */
    ConnectionCallback* m_onConnectionLost;

    /*!
     * @if jp
     * @brief PortConnectListener�ۥ��
     *
     * PortConnectListenr���ݻ�����ۥ��
     *
     * @else
     * @brief PortConnectListener holder
     *
     * Holders of PortConnectListeners
     *
     * @endif
     */
    PortConnectListeners* m_portconnListeners;

    //============================================================
    // Functor
    //============================================================
    /*!
     * @if jp
     * @brief id ����� ConnectorProfile ��õ�� Functor
     * @else
     * @brief Functor to find a ConnectorProfile named id
     * @endif
     */
    struct find_conn_id
    {
      find_conn_id(const char* id) : m_id(id) {};
      bool operator()(const ConnectorProfile& cprof)
      {
	return m_id == std::string(cprof.connector_id);
      }
      std::string m_id;
    };  // struct find_conn_id
    
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯������ port_ref ��Ʊ�����֥������Ȼ��Ȥ�õ�� Functor
     * @else
     * @brief Functor to find the object reference that is identical port_ref
     * @endif
     */
    struct find_port_ref
    {
      find_port_ref(PortService_ptr port_ref) : m_port(port_ref) {};
      bool operator()(PortService_ptr port_ref)
      {
	return m_port->_is_equivalent(port_ref);
      }
      PortService_ptr m_port;
    };  // struct find_port_ref
    
    /*!
     * @if jp
     * @brief name �� polarity ���� interface ��õ�� Functor
     * @else
     * @brief Functor to find interface from name and polarity
     * @endif
     */
    struct find_interface
    {
      find_interface(const char* name, PortInterfacePolarity pol)
	: m_name(name), m_pol(pol)
      {}
      
      bool operator()(const PortInterfaceProfile& prof)
      {
	CORBA::String_var name(CORBA::string_dup(prof.instance_name));
	return ((m_name == (const char *)name) && (m_pol == prof.polarity));
      }
      std::string m_name;
      PortInterfacePolarity m_pol;
    };  // struct find_interface
  };  // class PortBase
};  // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_PORTBASE_H
