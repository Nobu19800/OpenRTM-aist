// -*- C++ -*-
/*!
 * @file PortAdmin.h
 * @brief RTC's Port administration class
 * @date $Date: 2006-12-02 18:49:43 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortAdmin.h,v 1.4 2006-12-02 18:49:43 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2006/11/06 01:19:04  n-ando
 * CORBA sequence manipulation has been rewritten by using CORBA_SeqUtil.
 *
 * Revision 1.2  2006/10/17 19:16:40  n-ando
 * registerPort() was modified to store Port's object reference in PortProfile.
 *
 * Revision 1.1  2006/10/17 10:22:01  n-ando
 * The first commitment.
 *
 */

#ifndef PortAdmin_h
#define PortAdmin_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/PortBase.h>
#include <rtm/ObjectManager.h>
// 68608 10 17 23:51 PortAdmin.o
// 54272 10 29 00:53 PortAdmin.o
// 54132 10 29 00:54 PortAdmin.o
namespace RTC
{


  class PortAdmin
  {
  public:
    PortAdmin(CORBA::ORB_ptr, PortableServer::POA_ptr poa);
    virtual ~PortAdmin(){};

    /*!
     * @if jp
     *
     * @brief PortList �μ���
     *
     * registerPort() �ˤ����Ͽ���줿 Port �� PortList �ؤΥݥ��󥿤��֤���
     *
     * @return PortList* PortList �ؤΥݥ���
     *
     * @else
     *
     * @brief Get PortList
     *
     * This operation returns the pointer to the PortList of Ports regsitered
     * by registerPort().
     *
     * @return PortList+ The pointer points PortList
     *
     * @endif
     */
    PortList* getPortList() const;

    /*!
     * @if jp
     *
     * @brief Port �Υ��֥������Ȼ��Ȥμ���
     *
     * port_name �ǻ��ꤷ�� Port �Υ��֥������Ȼ��Ȥ��֤���
     * port_name �ǻ��ꤹ�� Port �Ϥ��餫���� registerPort() ����Ͽ����Ƥ�
     * �ʤ���Фʤ�ʤ���
     *
     * @param port_name ���Ȥ��֤�Port��̾��
     * @return Port_ptr Port�Υ��֥������Ȼ���
     *
     * @else
     *
     * @brief Get PortList
     *
     * This operation returns the pointer to the PortList of Ports regsitered
     * by registerPort().
     *
     * @param port_name The name of Port to be returned the reference.
     * @return Port_ptr Port's object reference.
     *
     * @endif
     */
    Port_ptr getPortRef(const char* port_name) const;


    /*!
     * @if jp
     *
     * @brief Port �Υ����Х�ȤΥݥ��󥿤μ���
     *
     * port_name �ǻ��ꤷ�� Port �Υ����Х�ȤΥݥ��󥿤��֤���
     * port_name �ǻ��ꤹ�� Port �Ϥ��餫���� registerPort() ����Ͽ����Ƥ�
     * �ʤ���Фʤ�ʤ���
     *
     * @param port_name ���Ȥ��֤�Port��̾��
     * @return PortBase* Port�����Х�ȴ��쥯�饹�Υݥ���
     *
     * @else
     *
     * @brief Getpointer to the Port's servant
     *
     * This operation returns the pointer to the PortBase servant regsitered
     * by registerPort().
     *
     * @param port_name The name of Port to be returned the servant pointer.
     * @return PortBase* Port's servant's pointer.
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
     *
     * @else
     *
     * @brief Regsiter Port
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
     * @brief Delete the Port's registration
     *
     * This operation unregisters the Port's registration.
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
     * �����ǻ��ꤵ�줿̾������� Port ����Ͽ�������롣
     * ������� Port �� deactivate ���졢Port��Profile�Υ�ե���󥹤ˤϡ�
     * nil�ͤ���������롣
     *
     * @param port_name Port ��̾��
     *
     * @else
     *
     * @brief Delete the Port' registration
     *
     * This operation delete the Port's registration specified by port_ name.
     * When the Port is unregistered, Port is deactivated, and the object
     * reference in the Port's profile is set to nil.
     *
     * @param port_name The Port's name.
     *
     * @endif
     */
    void deletePortByName(const char* port_name);


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
     * @brief Unregister the Port
     *
     * This operation deactivates the all Port and deletes the all Port's
     * registrations from the list.
     *
     * @endif
     */
    void finalizePorts();

  private:
    // ORB �ؤΥݥ���
    CORBA::ORB_var m_pORB;

    // POA �ؤΥݥ���
    PortableServer::POA_var m_pPOA;

    // Port�Υ��֥������ȥ�ե���󥹤Υꥹ��. PortList
    PortList m_portRefs;


    template <class T>
    class comp_op
    {
    public:
      comp_op(std::string _name) : m_name(_name) {};
      comp_op(T* obj) : m_name(obj->getName()) {};
      bool operator()(T* obj)
      {
	std::string name(obj->getName());
	return m_name == name;
      }
      std::string m_name;
    };
    
    struct find_port_name;
    struct del_port;

    // �����Х�Ȥ�ľ�ܳ�Ǽ���륪�֥������ȥޥ͡�����
    ObjectManager<std::string, PortBase, comp_op<PortBase> > m_portServants;


  };
};     // namespace RTC
#endif // PortAdmin_h
