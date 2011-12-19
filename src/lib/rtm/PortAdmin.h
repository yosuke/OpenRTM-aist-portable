// -*- C++ -*-
/*!
 * @file PortAdmin.h
 * @brief RTC's Port administration class
 * @date $Date: 2007-12-31 03:08:05 $
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
 * $Id: PortAdmin.h 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#ifndef RTC_PORTADMIN_H
#define RTC_PORTADMIN_H

#include <rtm/idl/RTCSkel.h>
#include <rtm/PortBase.h>
#include <rtm/ObjectManager.h>
#include <rtm/SystemLogger.h>

namespace RTC
{
  /*!
   * @if jp
   * @class PortAdmin
   * @brief PortAdmin ���饹
   *
   * �Ƽ� Port �δ�����Ԥ����饹��Port ����Ͽ/��Ͽ����ʤɳƼ�������
   * ��¹Ԥ���ȤȤ�ˡ���Ͽ����Ƥ��� Port Port �δ�����Ԥ����饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class PortAdmin
   * @brief PortAdmin class
   *
   * This is a class to manage various Ports.  It executes various
   * management operations such as registering and unregistering Port
   * etc and also manages registered ports.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class PortAdmin
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param orb ORB
     * @param poa POA
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param orb ORB
     * @param poa POA
     *
     * @endif
     */
    PortAdmin(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    
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
    virtual ~PortAdmin(void){};
    
    /*!
     * @if jp
     *
     * @brief Port �ꥹ�Ȥμ���
     *
     * addPort() �ˤ����Ͽ���줿 Port �� �ꥹ�Ȥ�������롣
     *
     * @return Port �ꥹ��
     *
     * @else
     *
     * @brief Get PortServiceList
     *
     * This operation returns the pointer to the PortServiceList of
     * Ports registered by addPort().
     *
     * @return The pointer points PortServiceList
     *
     * @endif
     */
    PortServiceList* getPortServiceList() const;
    
    /*!
     * @if jp
     *
     * @brief PorProfile �ꥹ�Ȥμ���
     *
     * addPort() �ˤ����Ͽ���줿 Port �� Profile �ꥹ�Ȥ�������롣
     *
     * @return PortProfile �ꥹ��
     *
     * @else
     *
     * @brief Get PorProfileList
     *
     * This operation gets the Profile list of Ports registered by 
     * addPort().
     *
     * @return The pointer points PortProfile list
     *
     * @endif
     */
    PortProfileList getPortProfileList() const;
    
    /*!
     * @if jp
     *
     * @brief Port �Υ��֥������Ȼ��Ȥμ���
     *
     * port_name �ǻ��ꤷ�� Port �Υ��֥������Ȼ��Ȥ��֤���
     * port_name �ǻ��ꤹ�� Port �Ϥ��餫���� addPort() ����Ͽ����Ƥ�
     * �ʤ���Фʤ�ʤ���
     *
     * @param port_name ���Ȥ��֤�Port��̾��
     * @return PortService_ptr Port�Υ��֥������Ȼ���
     *
     * @else
     *
     * @brief Get the reference to Port object
     *
     * This operation returns the reference of Port object specified
     * by port_name.
     * The port specified by port_name must be already registered in 
     * addPort().
     *
     * @param port_name The name of Port to be returned the reference.
     * @return PortService_ptr Port object reference.
     *
     * @endif
     */
    PortService_ptr getPortRef(const char* port_name) const;
    
    /*!
     * @if jp
     *
     * @brief Port �Υ����Х�ȤΥݥ��󥿤μ���
     *
     * port_name �ǻ��ꤷ�� Port �Υ����Х�ȤΥݥ��󥿤��֤���
     * port_name �ǻ��ꤹ�� Port �Ϥ��餫���� addPort() ����Ͽ����Ƥ�
     * �ʤ���Фʤ�ʤ���
     *
     * @param port_name ���Ȥ��֤�Port��̾��
     * @return PortBase* Port�����Х�ȴ��쥯�饹�Υݥ���
     *
     * @else
     *
     * @brief Get pointer to the Port's servant
     *
     * This operation returns the pointer to the PortBase servant registered
     * by addPort().
     * The port specified by port_name must be already registered in 
     * addPort().
     *
     * @param port_name The name of Port to be returned the servant pointer.
     * @return PortBase* The pointer to Port's servant.
     *
     * @endif
     */
    PortBase* getPort(const char* port_name) const;
    
    /*!
     * @if jp
     *
     * @brief Port ����Ͽ����
     *
     * ���� port �ǻ��ꤵ�줿 Port �Υ����Х�Ȥ���Ͽ���롣
     * ��Ͽ���줿 Port �Υ����Х�Ȥϥ��󥹥ȥ饯����Ϳ����줿POA ���
     * activate ���졢���Υ��֥������Ȼ��Ȥ�Port��Profile�˥��åȤ���롣
     *
     * @param port Port �����Х��
     * @return ��Ͽ���(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     *
     * @brief Regsiter the Port
     *
     * This operation registers the Port's servant given by argument.
     * The given Port's servant will be activated on the POA that is given
     * to the constructor, and the created object reference is set
     * to the Port's profile.
     *
     * @param port The Port's servant.
     * @return Register result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool addPort(PortBase& port);

    /*!
     * @if jp
     *
     * @brief Port ����Ͽ����
     *
     * ���� port �ǻ��ꤵ�줿 Port �Υ����Х�Ȥ���Ͽ���롣
     * ��Ͽ���줿 Port �Υ����Х�Ȥϥ��󥹥ȥ饯����Ϳ����줿POA ���
     * activate ���졢���Υ��֥������Ȼ��Ȥ�Port��Profile�˥��åȤ���롣
     *
     * @param port Port �����Х��
     * @return ��Ͽ���(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     *
     * @brief Regsiter the Port
     *
     * This operation registers the Port's servant given by argument.
     * The given Port's servant will be activated on the POA that is given
     * to the constructor, and the created object reference is set
     * to the Port's profile.
     *
     * @param port The Port's servant.
     * @return Register result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool addPort(PortService_ptr port);

    /*!
     * @if jp
     *
     * @brief Port ����Ͽ����
     *
     * ���� port �ǻ��ꤵ�줿 Port �Υ����Х�Ȥ���Ͽ���롣
     * ��Ͽ���줿 Port �Υ����Х�Ȥϥ��󥹥ȥ饯����Ϳ����줿POA ���
     * activate ���졢���Υ��֥������Ȼ��Ȥ�Port��Profile�˥��åȤ���롣
     *
     * @param port Port �����Х��
     *
     * @else
     *
     * @brief Regsiter the Port
     *
     * This operation registers the Port's servant given by argument.
     * The given Port's servant will be activated on the POA that is given
     * to the constructor, and the created object reference is set
     * to the Port's profile.
     *
     * @param port The Port's servant.
     *
     * @endif
     */
    void registerPort(PortBase& port);

    /*!
     * @if jp
     *
     * @brief Port ����Ͽ����
     *
     * ���� port �ǻ��ꤵ�줿 Port �Υ����Х�Ȥ���Ͽ���롣
     * ��Ͽ���줿 Port �Υ����Х�Ȥϥ��󥹥ȥ饯����Ϳ����줿POA ���
     * activate ���졢���Υ��֥������Ȼ��Ȥ�Port��Profile�˥��åȤ���롣
     *
     * @param port Port �����Х��
     *
     * @else
     *
     * @brief Regsiter the Port
     *
     * This operation registers the Port's servant given by argument.
     * The given Port's servant will be activated on the POA that is given
     * to the constructor, and the created object reference is set
     * to the Port's profile.
     *
     * @param port The Port's servant.
     *
     * @endif
     */
    void registerPort(PortService_ptr port);
    
    /*!
     * @if jp
     *
     * @brief Port ����Ͽ��������
     *
     * ���� port �ǻ��ꤵ�줿 Port ����Ͽ�������롣
     * ������� Port �� deactivate ���졢Port��Profile�Υ�ե���󥹤ˤϡ�
     * nil�ͤ���������롣
     *
     * @param port Port �����Х��
     * @return ������(�������:true���������:false)
     *
     * @else
     *
     * @brief Unregister the Port registration
     *
     * This operation unregisters the Port registration.
     * When the Port is unregistered, Port is deactivated, and the object
     * reference in the Port's profile is set to nil.
     *
     * @param port The Port's servant.
     * @return Unregister result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool removePort(PortBase& port);

    /*!
     * @if jp
     *
     * @brief Port ����Ͽ��������
     *
     * ���� port �ǻ��ꤵ�줿 Port ����Ͽ�������롣
     * ������� Port �� deactivate ���졢Port��Profile�Υ�ե���󥹤ˤϡ�
     * nil�ͤ���������롣
     *
     * @param port Port �����Х��
     * @return ������(�������:true���������:false)
     *
     * @else
     *
     * @brief Unregister the Port registration
     *
     * This operation unregisters the Port registration.
     * When the Port is unregistered, Port is deactivated, and the object
     * reference in the Port's profile is set to nil.
     *
     * @param port The Port's servant.
     * @return Unregister result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool removePort(PortService_ptr port);

    /*!
     * @if jp
     *
     * @brief Port ����Ͽ��������
     *
     * ���� port �ǻ��ꤵ�줿 Port ����Ͽ�������롣
     * ������� Port �� deactivate ���졢Port��Profile�Υ�ե���󥹤ˤϡ�
     * nil�ͤ���������롣
     *
     * @param port Port �����Х��
     *
     * @else
     *
     * @brief Unregister the Port registration
     *
     * This operation unregisters the Port registration.
     * When the Port is unregistered, Port is deactivated, and the object
     * reference in the Port's profile is set to nil.
     *
     * @param port The Port's servant.
     *
     * @endif
     */
    void deletePort(PortBase& port);

    /*!
     * @if jp
     *
     * @brief Port ����Ͽ��������
     *
     * ���� port �ǻ��ꤵ�줿 Port ����Ͽ�������롣
     * ������� Port �� deactivate ���졢Port��Profile�Υ�ե���󥹤ˤϡ�
     * nil�ͤ���������롣
     *
     * @param port Port �����Х��
     *
     * @else
     *
     * @brief Unregister the Port registration
     *
     * This operation unregisters the Port registration.
     * When the Port is unregistered, Port is deactivated, and the object
     * reference in the Port's profile is set to nil.
     *
     * @param port The Port's servant.
     *
     * @endif
     */
    void deletePort(PortService_ptr port);
    
    /*!
     * @if jp
     *
     * @brief ̾�λ���ˤ��Port ����Ͽ��������
     *
     * �����ǻ��ꤵ�줿̾������� Port ����Ͽ�������롣
     * ������� Port �� deactivate ���졢Port��Profile�Υ�ե���󥹤ˤϡ�
     * nil�ͤ���������롣
     *
     * @param port_name Port ��̾��
     *
     * @else
     *
     * @brief Unregister the Port's registration by its name
     *
     * This operation unregister the Port's registration specified by
     * port_ name.  When the Port is unregistered, Port is
     * deactivated, and the object reference in the Port's profile is
     * set to nil.
     *
     * @param port_name The Port's name.
     *
     * @endif
     */
    void deletePortByName(const char* port_name);

    /*!
     * @if jp
     *
     * @brief ���Ƥ� Port �Υ��󥿡��ե������� activates ����
     *
     * ��Ͽ����Ƥ������Ƥ� Port �Υ��󥿡��ե��������Ф��ơ�
     * activate ���롣
     * ���δؿ��ϡ�ComponentAction �� on_activate() ��ǸƤФ�롣
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
    void activatePorts();

    /*!
     * @if jp
     *
     * @brief ���Ƥ� Port �Υ��󥿡��ե������� deactivates ����
     *
     * ��Ͽ����Ƥ������Ƥ� Port �Υ��󥿡��ե��������Ф��ơ�
     * deactivate ���롣
     * ���δؿ��ϡ�ComponentAction �� on_deactivate() ��ǸƤФ�롣
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
    void deactivatePorts();

    /*!
     * @if jp
     *
     * @brief ���Ƥ� Port ��deactivate����Ͽ��������
     *
     * ��Ͽ����Ƥ������Ƥ�Port���Ф��ơ������Х�Ȥ�deactivate��Ԥ���
     * ��Ͽ�ꥹ�Ȥ��������롣
     *
     * @else
     *
     * @brief Deactivate all Ports and unregister them
     *
     * This operation deactivates the all Port and deletes the all Port's
     * registrations from the list.
     *
     * @endif
     */
    void finalizePorts();
    
  private:
    /*!
     * @if jp
     * @brief ORB �ؤλ���
     * @else
     * @brief Reference to ORB
     * @endif
     */
    CORBA::ORB_var m_pORB;
    
    /*!
     * @if jp
     * @brief POA �ؤλ���
     * @else
     * @brief Reference to POA
     * @endif
     */
    PortableServer::POA_var m_pPOA;
    
    /*!
     * @if jp
     * @brief Port�Υ��֥������ȥ�ե���󥹤Υꥹ��
     * @else
     * @brief List of Port's object references
     * @endif
     */
    PortServiceList m_portRefs;

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
     * @brief comp_op �ե��󥯥� (̤����?)
     * @else
     * @brief comp_op functor
     * @endif
     */
    template <class T>
    class comp_op
    {
    public:
      comp_op(const char* _name)
	: m_name(_name)
      {
      }
      comp_op(T* obj) 
	: m_name((const char*)(obj->getProfile().name))
      {
      }
      bool operator()(T* obj)
      {
	std::string name((const char*)obj->getProfile().name);
	return m_name == name;
      }
    private:
      std::string m_name;
    };

    /*!
     * @if jp
     * @brief PortProfileList �����ե��󥯥� (̤����?)
     * @else
     * @brief PortProfileList corerection functor
     * @endif
     */
    class port_prof_collect
    {
    public:
      port_prof_collect(PortProfileList& p) : m_p(p) {}
      void operator()(const PortBase* port)
      {
	CORBA_SeqUtil::push_back(m_p, port->getPortProfile());
      }
    private:
      PortProfileList& m_p;
    };

    /*!
     * @if jp
     * @brief PortProfileList �����ե��󥯥�
     * @else
     * @brief PortProfileList corerection functor
     * @endif
     */
    class port_prof_collect2
    {
    public:
      port_prof_collect2(PortProfileList& p) : m_p(p) {}
      void operator()(const PortService_ptr port)
      {
        PortProfile* pp(port->get_port_profile());
	CORBA_SeqUtil::push_back(m_p, *(pp));
        delete pp;
      }
    private:
      PortProfileList& m_p;
    };
    
    struct find_port_name;
    struct find_port;
    struct del_port;
    
    // �����Х�Ȥ�ľ�ܳ�Ǽ���륪�֥������ȥޥ͡�����
    ObjectManager<const char*, PortBase, comp_op<PortBase> > m_portServants;
    
  };
};     // namespace RTC
#endif // RTC_PORTADMIN_H
