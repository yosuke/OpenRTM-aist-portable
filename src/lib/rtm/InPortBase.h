// -*- C++ -*-
/*!
 * @file InPortBase.h
 * @brief RTC::Port implementation for InPort
 * @date $Date: 2008-01-13 15:06:40 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPortBase.h 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#ifndef RTC_INPORTBASE_H
#define RTC_INPORTBASE_H

#include <rtm/PortBase.h>
#include <rtm/DataPortStatus.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/ConnectorListener.h>

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
  class InPortProvider;
  class OutPortConsumer;
  class InPortConnector;

  /*!
   * @if jp
   * @class InPortBase
   * @brief InPort �� Port
   *
   * �ǡ������ϥݡ��Ȥμ������饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortBase
   * @brief Port for InPort
   *
   * This is an implementation class for the data input port.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortBase
    : public PortBase, public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM

    typedef std::vector<InPortConnector*> ConnectorList;

    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param name �ݡ���̾��
     * @param data_type �ǡ���������
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port name
     * @param data_type Data type
     *
     * @endif
     */
    InPortBase(const char* name, const char* data_type);
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~InPortBase(void);

    /*!
     * @if jp
     * @brief �ץ�ѥƥ��ν����
     *
     * ���ꤵ�줿�ץ�ѥƥ��ǽ�������롣
     *
     * @param prop ���ꤹ��ץ�ѥƥ�
     * @else
     * @brief Initializing properties
     *
     * This method initializes the port in the specified property. 
     *
     * @param prop Property for setting ports
     * @endif
     */
    void init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief RTObject_impl::readAll()����ƤФ�벾�۴ؿ�
     *
     * DataPort ����ǡ������ɤ߽Ф�
     *
     * @return true:����,false:����
     * @else
     * @brief It is a virtual method that is called from RTObject_impl::readAll().
     * This method reads out data from DataPort. 
     *
     * @return true:Success,false:Failure
     * @endif
     */
    virtual bool read() = 0;

    /*!
     * @if jp
     * @brief �ץ�ѥƥ����������
     *
     * �ݡ��ȤΥץ�ѥƥ���������롣
     *
     * @return �ץ�ѥƥ�
     * @else
     * @brief Get properties
     *
     * This method gets properties in the port. 
     *
     * @return Properties
     * @endif
     */
    coil::Properties& properties();

    /*!
     * @if jp
     * @brief Connector �����
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����������롣
     *
     * @return connector �Υꥹ��
     *
     * @else
     *
     * @brief Connector list
     *
     * This operation returns connector list
     *
     * @return connector list
     *
     * @endif
     */
    const std::vector<InPortConnector*>& connectors();

    /*!
     * @if jp
     * @brief ConnectorProfile �����
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����Profile��������롣
     *
     * @return ConnectorProfile �Υꥹ��
     *
     * @else
     *
     * @brief ConnectorProfile list
     *
     * This operation returns ConnectorProfile list
     *
     * @return connector list
     *
     * @endif
     */
    ConnectorInfoList getConnectorProfiles();

    /*!
     * @if jp
     * @brief ConnectorId �����
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����ID��������롣
     *
     * @return ConnectorId �Υꥹ��
     *
     * @else
     *
     * @brief ConnectorId list
     *
     * This operation returns ConnectorId list
     *
     * @return connector list
     *
     * @endif
     */
    coil::vstring getConnectorIds();

    /*!
     * @if jp
     * @brief Connector��̾�������
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����̾����������롣
     *
     * @return Connector̾�Υꥹ��
     *
     * @else
     *
     * @brief Connector name list
     *
     * This operation returns Connector name list
     *
     * @return connector name list
     *
     * @endif
     */
    coil::vstring getConnectorNames();

    /*!
     * @if jp
     * @brief ConnectorProfile��ID�Ǽ���
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����ID�Ǽ������롣
     *
     * @param id Connector ID
     * @return ���ͥ����ؤΥݥ���
     *
     * @else
     *
     * @brief Getting ConnectorProfile by ID
     *
     * This operation returns Connector specified by ID.
     *
     * @param id Connector ID
     * @return A pointer to connector
     *
     * @endif
     */
    InPortConnector* getConnectorById(const char* id);

     /*!
     * @if jp
     * @brief ConnectorProfile��̾���Ǽ���
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����̾���Ǽ������롣
     *
     * @param name Connector name
     * @return ���ͥ����ؤΥݥ���
     *
     * @else
     *
     * @brief Getting Connector by name
     *
     * This operation returns Connector specified by name.
     *
     * @param id Connector ID
     * @return A pointer to connector
     *
     * @endif
     */
   InPortConnector* getConnectorByName(const char* name);

    /*!
     * @if jp
     * @brief ConnectorProfile��ID�Ǽ���
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����ID�Ǽ������롣
     *
     * @param id Connector ID
     * @param prof ConnectorProfile
     * @return false ���ꤷ��ID���ʤ�
     *
     * @else
     *
     * @brief Getting ConnectorProfile by name
     *
     * This operation returns ConnectorProfile specified by name
     *
     * @param id Connector ID
     * @param prof ConnectorProfile
     * @return false��specified ID does not exist
     *
     * @endif
     */
    bool getConnectorProfileById(const char* id,
                                 ConnectorInfo& prof);

    /*!
     * @if jp
     * @brief ConnectorProfile��̾���Ǽ���
     *
     * ���߽�ͭ���Ƥ��륳�ͥ�����̾���Ǽ������롣
     *
     * @param name Connector name
     * @param prof ConnectorProfile
     * @return false ���ꤷ��̾�����ʤ�
     *
     * @else
     *
     * @brief Getting ConnectorProfile by name
     *
     * This operation returns ConnectorProfile specified by name
     *
     * @param id Connector ID
     * @param prof ConnectorProfile
     * @return false specified name does not exist
     *
     * @endif
     */
    bool getConnectorProfileByName(const char* name,
                                   ConnectorInfo& prof);


    /*!
     * @if jp
     *
     * @brief InPort�� activates ����
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

    /*!
     * @if jp
     * @brief ConnectorDataListener �ꥹ�ʤ��ɲä���
     *
     * �Хåե��񤭹��ߤޤ����ɤ߽Ф����٥�Ȥ˴�Ϣ����Ƽ�ꥹ�ʤ����ꤹ�롣
     *
     * ����Ǥ���ꥹ�ʤΥ����פȥ�����Хå����٥�Ȥϰʲ����̤�
     *
     * - ON_BUFFER_WRITE:          �Хåե��񤭹��߻�
     * - ON_BUFFER_FULL:           �Хåե��ե��
     * - ON_BUFFER_WRITE_TIMEOUT:  �Хåե��񤭹��ߥ����ॢ���Ȼ�
     * - ON_BUFFER_OVERWRITE:      �Хåե���񤭻�
     * - ON_BUFFER_READ:           �Хåե��ɤ߽Ф���
     * - ON_SEND:                  InProt�ؤ�������
     * - ON_RECEIVED:              InProt�ؤ�������λ��
     * - ON_SEND_ERTIMEOUT:        OutPort¦�����ॢ���Ȼ�
     * - ON_SEND_ERERROR:          OutPort¦���顼��
     * - ON_RECEIVER_FULL:         InProt¦�Хåե��ե��
     * - ON_RECEIVER_TIMEOUT:      InProt¦�Хåե������ॢ���Ȼ�
     * - ON_RECEIVER_ERROR:        InProt¦���顼��
     *
     * �ꥹ�ʤ� ConnectorDataListener ��Ѿ������ʲ��Υ����˥�������
     * operator() ��������Ƥ���ɬ�פ����롣
     *
     * ConnectorDataListener::
     *         operator()(const ConnectorProfile&, const cdrStream&)
     *
     * �ǥե���ȤǤϡ����δؿ���Ϳ�����ꥹ�ʥ��֥������Ȥν�ͭ����
     * OutPort�˰ܤꡢOutPort���λ��⤷���ϡ�
     * removeConnectorDataListener() �ˤ�������˼�ưŪ�˲��Τ���롣
     * �ꥹ�ʥ��֥������Ȥν�ͭ����ƤӽФ�¦�ǰݻ����������ϡ���3��
     * ���� false ����ꤷ����ưŪ�ʲ��Τ��������뤳�Ȥ��Ǥ��롣
     *
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     * @param autoclean �ꥹ�ʥ��֥������Ȥμ�ưŪ���Τ�Ԥ����ɤ����Υե饰
     *
     * @else
     * @brief Adding BufferDataListener type listener
     *
     * This operation adds certain listeners related to buffer writing and
     * reading events.
     * The following listener types are available.
     *
     * - ON_BUFFER_WRITE:          At the time of buffer write
     * - ON_BUFFER_FULL:           At the time of buffer full
     * - ON_BUFFER_WRITE_TIMEOUT:  At the time of buffer write timeout
     * - ON_BUFFER_OVERWRITE:      At the time of buffer overwrite
     * - ON_BUFFER_READ:           At the time of buffer read
     * - ON_SEND:                  At the time of sending to InPort
     * - ON_RECEIVED:              At the time of finishing sending to InPort
     * - ON_SENDER_TIMEOUT:        At the time of timeout of OutPort
     * - ON_SENDER_ERROR:          At the time of error of OutPort
     * - ON_RECEIVER_FULL:         At the time of bufferfull of InPort
     * - ON_RECEIVER_TIMEOUT:      At the time of timeout of InPort
     * - ON_RECEIVER_ERROR:        At the time of error of InPort
     *
     * Listeners should have the following function operator().
     *
     * ConnectorDataListener::
     *         operator()(const ConnectorProfile&, const cdrStream&)
     *
     * The ownership of the given listener object is transferred to
     * this OutPort object in default.  The given listener object will
     * be destroied automatically in the OutPort's dtor or if the
     * listener is deleted by removeConnectorDataListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    void addConnectorDataListener(ConnectorDataListenerType listener_type,
                                  ConnectorDataListener* listener,
                                  bool autoclean = true);


    /*!
     * @if jp
     * @brief ConnectorDataListener �ꥹ�ʤ�������
     *
     * ���ꤷ���Ƽ�ꥹ�ʤ������롣
     * 
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     *
     * @else
     * @brief Removing BufferDataListener type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void removeConnectorDataListener(ConnectorDataListenerType listener_type,
                                     ConnectorDataListener* listener);
    

    /*!
     * @if jp
     * @brief ConnectorListener �ꥹ�ʤ��ɲä���
     *
     * �Хåե��񤭹��ߤޤ����ɤ߽Ф����٥�Ȥ˴�Ϣ����Ƽ�ꥹ�ʤ����ꤹ�롣
     *
     * ����Ǥ���ꥹ�ʤΥ����פ�
     *
     * - ON_BUFFER_EMPTY:       �Хåե������ξ��
     * - ON_BUFFER_READTIMEOUT: �Хåե������ǥ����ॢ���Ȥ������
     *
     * �ꥹ�ʤϰʲ��Υ����˥������� operator() ��������Ƥ���ɬ�פ����롣
     *
     * ConnectorListener::operator()(const ConnectorProfile&)
     *
     * �ǥե���ȤǤϡ����δؿ���Ϳ�����ꥹ�ʥ��֥������Ȥν�ͭ����
     * OutPort�˰ܤꡢOutPort���λ��⤷���ϡ�
     * removeConnectorListener() �ˤ�������˼�ưŪ�˲��Τ���롣
     * �ꥹ�ʥ��֥������Ȥν�ͭ����ƤӽФ�¦�ǰݻ����������ϡ���3��
     * ���� false ����ꤷ����ưŪ�ʲ��Τ��������뤳�Ȥ��Ǥ��롣
     *
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     * @param autoclean �ꥹ�ʥ��֥������Ȥμ�ưŪ���Τ�Ԥ����ɤ����Υե饰
     *
     * @else
     * @brief Adding ConnectorListener type listener
     *
     * This operation adds certain listeners related to buffer writing and
     * reading events.
     * The following listener types are available.
     *
     * - ON_BUFFER_EMPTY:       At the time of buffer empty
     * - ON_BUFFER_READTIMEOUT: At the time of buffer read timeout
     *
     * Listeners should have the following function operator().
     *
     * ConnectorListener::operator()(const ConnectorProfile&)
     *  
     * The ownership of the given listener object is transferred to
     * this OutPort object in default.  The given listener object will
     * be destroied automatically in the OutPort's dtor or if the
     * listener is deleted by removeConnectorListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    void addConnectorListener(ConnectorListenerType callback_type,
                              ConnectorListener* listener,
                              bool autoclean = true);

    /*!
     * @if jp
     * @brief ConnectorDataListener �ꥹ�ʤ�������
     *
     * ���ꤷ���Ƽ�ꥹ�ʤ������롣
     * 
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     *
     * @else
     * @brief Removing BufferDataListener type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void removeConnectorListener(ConnectorListenerType callback_type,
                                 ConnectorListener* listener);

    /*!
     * @if jp
     * @brief endian ������֤�
     *
     * endian �����bool�ͤ��֤���
     *
     * @return m_littleEndian ��little�ξ��true��big�ξ��false ���֤���
     *
     * @else
     * @brief
     *
     * return it whether endian setting.
     *
     *@return Return true in the case of "little", false in "big" than it.
     *
     * @endif
     */
    bool isLittleEndian();

    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³��Ԥ�
     *
     * Ϳ����줿 ConnectoionProfile �ξ���˴�Ť���Port�֤���³���Ω
     * ���롣���δؿ��ϼ�˥��ץꥱ�������ץ�����ġ��뤫��Ƥӽ�
     * �����Ȥ�����Ȥ��Ƥ��롣
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
     * @param connector_profile The ConnectorProfile.
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    connect(ConnectorProfile& connector_profile)
      throw (CORBA::SystemException);

  protected:

    /*!
     * @if jp
     * @brief Interface������������
     *
     * Interface�����������롣
     * ������ ConnectorProfile �˳�Ǽ����Ƥ��� dataflow_type �� push ��
     * �ξ��ϡ����ꤵ�줿 interface_type �� InPortProvider �˴ؤ������
     * �� ConnectorProfile::properties �˽���߸ƤӽФ�¦���᤹��
     *
     *  dataport.dataflow_type
     *
     * @param connector_profile ���ͥ����ץ�ե�����
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.
     * Assign the Provider information that owned by this port
     * to ConnectorProfile#properties
     *
     * @param connector_profile The connector profile
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interface����³����
     *
     * Interface����³���롣
     * Port����ͭ����Consumer��Ŭ�礹��Provider�˴ؤ������� 
     * ConnectorProfile#properties ������Ф���
     * Consumer��CORBA���֥������Ȼ��Ȥ����ꤹ�롣
     *
     * @param connector_profile ���ͥ������ץ�ե�����
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     * @brief Subscribe to the interface
     *
     * Subscribe to interface.
     * Derive Provider information that matches Consumer owned by the Port 
     * from ConnectorProfile#properties and 
     * set the Consumer to the reference of the CORBA object.
     *
     * @param connector_profile The connector profile
     *
     * @return ReturnCode_t The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interface�ؤ���³��������
     *
     * Interface�ؤ���³�������롣
     * Ϳ����줿ConnectorProfile�˴�Ϣ����Consumer�����ꤵ�줿���Ƥ�Object��
     * ��������³�������롣
     *
     * @param connector_profile ���ͥ������ץ�ե�����
     *
     * @else
     * @brief Disconnect the interface connection
     *
     * Disconnect the interface connection.
     * Release all objects set in Consumer associated with 
     * given ConnectorProfile and unscribe the interface.
     *
     * @param connector_profile The connector profile
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);


    /*!
     * @if jp
     * @brief InPort provider �ν����
     * @else
     * @brief InPort provider initialization
     * @endif
     */
    void initProviders();

    /*!
     * @if jp
     * @brief OutPort consumer �ν����
     * @else
     * @brief OutPort consumer initialization
     * @endif
     */
    void initConsumers();

    /*!
     * @if jp
     * @brief ���ꥢ�饤���Υ���ǥ����������å�����
     *
     * Ϳ����줿�ץ�ѥƥ������ꤵ��Ƥ��롢�ǡ����Υ��ꥢ�饤���Υ���
     * �ǥ�������������å����롣����������ǥ�������꤬�ʤ���Ƥ���
     * �С�true ���֤������� littleEndian �ˡ������ͤ���ȥ륨��ǥ���
     * ��Ǥ���� true �����ӥå�����ǥ�����Ǥ���� false ���֤���롣
     *
     * @param prop �����å�����ץ�ѥƥ�
     * @param littleEndian ����ǥ���������true:little,false:big��
     * @return true:"serializer"������¸�ߤ��ʤ� �ޤ��� ¸�ߤ��Ƥ������Ƥ����롣
,false:"serializer"������¸�ߤ��Ƥ��뤬���Ƥ��� �ޤ��� ¸�ߤ��Ƥ��뤬���Ƥ�"little","big" �ʳ���
     *
     * @else
     *
     * @brief Checking endian flag of serializer
     *
     * This operation checks endian flag of data serializer that is
     * specified properties. If valid specification is found, this
     * operation returns true and set argument littleEndian. True
     * means little endian, false means big endian.
     *
     * @param prop Properties
     * @param littleEndian Endian Information(true:little,false:big)
     * @return true:"Serializer" key doesn't exist. or  "Serializer" key exists and there is a content.
     *
     *false:There is no content though "Serializer" key exists. or ithe content is not "Little. " though "Serializer" key exists. or The content is not "little" or "big" though "Serializer" key exists.
     *
     * @endif
     */
    bool checkEndian(const coil::Properties& prop, bool& littleEndian);

    /*!
     * @if jp
     * @brief InPort provider ������
     *
     * InPortProvider ��������������� ConnectorProfile �˸������롣
     * �����˼��Ԥ������ 0 ���֤���
     *
     * @else
     * @brief InPort provider creation
     * @endif
     */
    InPortProvider*
    createProvider(ConnectorProfile& cprof, coil::Properties& prop);

    /*!
     * @if jp
     * @brief OutPort consumer ������
     *
     * OutPortConsumer ���������롣
     * �����˼��Ԥ������ 0 ���֤���
     *
     * @else
     * @brief InPort provider creation
     * @endif
     */
    OutPortConsumer*
    createConsumer(const ConnectorProfile& cprof, coil::Properties& prop);

    /*!
     * @if jp
     * @brief InPortPushConnector ������
     *
     * Connector ������������������������� m_connectors ����¸���롣
     * �����˼��Ԥ������ 0 ���֤���
     *
     * @else
     * @brief InPortPushConnector creation
     * @endif
     */
    InPortConnector*
    createConnector(ConnectorProfile& cprof, coil::Properties& prop,
                    InPortProvider* provider);
    /*!
     * @if jp
     * @brief InPortPullConnector ������
     *
     * Connector ������������������������� m_connectors ����¸���롣
     * �����˼��Ԥ������ 0 ���֤���
     *
     * @else
     * @brief InPortPullConnector creation
     * @endif
     */
    InPortConnector*
    createConnector(const ConnectorProfile& cprof, coil::Properties& prop,
                    OutPortConsumer* consumer);

  protected:
    /*!
     * @if jp
     * @brief �Хåե��⡼��
     *
     * true:single buffer mode.
     * false:multi buffer mode.
     *
     * @else
     * @brief Buffer mode
     *
     * true:single buffer mode.
     * false:multi buffer mode.
     *
     * @endif
     */
    bool m_singlebuffer;
    /*!
     * @if jp
     * @brief �Хåե�
     * @else
     * @brief Buffer
     * @endif
     */
    CdrBufferBase* m_thebuffer;
    /*!
     * @if jp
     * @brief �ץ�ѥƥ�
     * @else
     * @brief Properties
     * @endif
     */
    coil::Properties m_properties;
    /*!
     * @if jp
     * @brief ���Ѳ�ǽprovider
     * @else
     * @brief Available providers
     * @endif
     */
    coil::vstring m_providerTypes;
    /*!
     * @if jp
     * @brief ���Ѳ�ǽconsumer
     * @else
     * @brief Available consumers
     * @endif
     */
    coil::vstring m_consumerTypes;
    /*!
     * @if jp
     * @brief ��³�ꥹ��
     * @else
     * @brief Connection list
     * @endif
     */
    ConnectorList m_connectors;
    /*!
     * @if jp
     * @brief ��³����ǥ����� 
     * @else
     * @brief Connected Endian
     * @endif
     */
    bool m_littleEndian;

    /*!
     * @if jp
     * @brief ConnectorDataListener �ꥹ��
     * @else
     * @brief ConnectorDataListener listener
     * @endif
     */
    ConnectorListeners m_listeners;
  };
}; // namespace RTC

#endif // RTC_INPORTBASE_H
