// -*- C++ -*-
/*!
 * @file SdoSystemElement.h
 * @brief SDOSystemElement and SDO classes
 * @date $Date: 2006-10-17 10:12:44 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoSystemElement.h,v 1.2 2006-10-17 10:12:44 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/09/11 18:14:41  n-ando
 * The first commit.
 *
 *
 */

#ifndef SdoSystemElement_h
#define SdoSystemElement_h

// CORBA header include
#include "rtm/RTC.h"
#include "rtm/Util.h"



// local includes
#include "rtm/idl/SDOPackageSkel.h"



namespace SDOPackage
{
  class Configuration_impl;
  class Organization_impl;
  /*!
   * @if jp
   *
   * @class SDOSystemElement_impl
   * @brief SDOSystemElement �������饹
   *
   * SDOSystemElement ���󥿡��ե�������SDOSystemElement�Υ��֥��饹��
   * �������뤿������Ѥ���롣
   *
   * @else
   *
   * @class SDOSystemElement_impl
   * @brief SDOSystemElement implementation class
   *
   * The SDOSystemElement interface is used to manage the subclass of
   * SDOSystemElement itself.
   *
   * @endif
   */
  class SDOSystemElement_impl
    : public virtual POA_SDOPackage::SDOSystemElement, 
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief SDOSystemElement ���饹���󥹥ȥ饯��
     *
     * @else
     *
     * @brief A constructor of SDOSystemElement
     *
     * @endif
     */
    SDOSystemElement_impl();
    SDOSystemElement_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);

    /*!
     * @if jp
     * 
     * @brief RtcBase ���饹�ǥ��ȥ饯��
     *
     * @else
     *
     * @brief A destructor of RtcBase class.
     *
     * @endif
     */
    virtual ~SDOSystemElement_impl();

    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �ꥹ�Ȥμ��� 
     *
     * SDOSystemElement ��0�Ĥ⤷���Ϥ���ʾ�� Organization ���ͭ���뤳�Ȥ�
     * ����롣 SDOSystemElement ��1�İʾ�� Organization ���ͭ���Ƥ�����
     * �ˤϡ����Υ��ڥ졼�����Ͻ�ͭ���� Organization �Υꥹ�Ȥ��֤���
     * �⤷Organization���Ĥ��ͭ���Ƥ��ʤ�����ж��Υꥹ�Ȥ��֤���
     *
     * @else
     *
     * @brief [CORBA interface] Getting Organizations
     *
     * SDOSystemElement can be the owner of zero or more organizations.
     * If the SDOSystemElement owns one or more Organizations, this operation
     * returns the list of Organizations that the SDOSystemElement owns.
     * If it does not own any Organization, it returns empty list.
     *
     * @endif
     */
    virtual OrganizationList* get_owned_organizations()
      throw (NotAvailable);

    // end of CORBA interface definition
    //============================================================

  protected:
    // Partial specialization
    template <class T, class X>
    class SeqEx
      : public SequenceEx <T, X, ACE_Thread_Mutex> {};
    
    SeqEx<OrganizationList, Organization_ptr> m_ownedOrganizations;

    CORBA::ORB_var m_pORB;
    PortableServer::POA_var m_pPOA;
    

  };
  

  //============================================================
  // SDO_impl
  //============================================================
  /*!
   * @if jp
   *
   * @class SDO_impl
   * @brief SDO �������饹
   *
   * SDO ���󥿡��ե�������SDO���Ǥ�������뤿��˻��Ѥ���롣
   * SDO ���ͤˤ������������Ƥ���¾�����ƤΥ��󥿡��ե�������
   * SDO ���󥿡��ե���������������롣
   *
   * @else
   *
   * @class SDO_impl
   * @brief SDO implementation class
   *
   * The SDO interface is used to manage elements of the SDO.
   * All the other interfaces specified in this specification are
   * navigated from SDO interface.
   *
   * @endif
   */
  class SDO_impl
    : public virtual SDOSystemElement_impl
  {
  public:
    //    SDO_impl();
    //    SDO_impl(char* id = "", char* type = "");
    SDO_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    virtual ~SDO_impl(){};

    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO ID �μ���
     *
     * SDO ID ���֤����ڥ졼�����
     * ���Υ��ڥ졼�����ϰʲ��η����㳰��ȯ�������롣
     * 
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @return    �꥽�����ǡ�����ǥ���������Ƥ��� SDO �� ID
     *
     * @else
     *
     * @brief [CORBA interface] Getting SDO ID
     *
     * This operation returns id of the SDO.
     * This operation throws SDOException with one of the following types.
     *
     * @exception SDONotExists if the target SDO does not exist.
     * @exception NotAvailable if the target SDO is reachable but cannot
     *                         respond.
     * @exception InternalError if the target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @return    id of the SDO defined in the resource data model.
     *
     * @endif
     */
    virtual char* get_sdo_id()
      throw (NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO �����פμ���
     * 
     * SDO Type ���֤����ڥ졼�����
     * ���Υ��ڥ졼�����ϰʲ��η����㳰��ȯ�������롣
     *
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @return    �꥽�����ǡ�����ǥ���������Ƥ��� SDO �� Type
     *
     * @else
     *
     * @brief [CORBA interface] Getting SDO type
     *
     * This operation returns sdoType of the SDO.
     * This operation throws SDOException with one of the following types.
     *
     * @exception SDONotExists if the target SDO does not exist.
     * @exception NotAvailable if the target SDO is reachable but cannot
     *                         respond.
     * @exception InternalError if the target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @return    Type of the SDO defined in the resource data model.
     *
     * @endif
     */
    virtual char* get_sdo_type()
      throw (NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO DeviceProfile �ꥹ�Ȥμ��� 
     *
     * SDO �� DeviceProfile ���֤����ڥ졼����� SDO ���ϡ��ɥ������ǥХ���
     * �˴�Ϣ�դ����Ƥ��ʤ����ˤϡ����� DeviceProfile ���֤���롣
     * ���Υ��ڥ졼�����ϰʲ��η����㳰��ȯ�������롣
     *
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @return    SDO DeviceProfile
     *
     * @else
     *
     * @brief [CORBA interface] Getting SDO DeviceProfile
     *
     * This operation returns the DeviceProfile of the SDO. If the SDO does not
     * represent any hardware device, then a DeviceProfile with empty values
     * are returned.
     * This operation throws SDOException with one of the following types.
     *
     * @exception NotAvailable if the target SDO is reachable but cannot
     *                         respond.
     * @exception InternalError if the target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @return    The DeviceProfile of the SDO.
     *
     * @endif
     */
    virtual DeviceProfile* get_device_profile()
      throw (NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO ServiceProfile �μ��� 
     *
     * SDO ����ͭ���Ƥ��� Service �� ServiceProfile ���֤����ڥ졼�����
     * SDO �������ӥ����Ĥ��ͭ���Ƥ��ʤ����ˤϡ����Υꥹ�Ȥ��֤���
     * ���Υ��ڥ졼�����ϰʲ��η����㳰��ȯ�������롣
     * 
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @return    SDO ���󶡤������Ƥ� Service �� ServiceProfile��
     *
     * @else
     *
     * @brief [CORBA interface] Getting SDO ServiceProfile
     * 
     * This operation returns a list of ServiceProfiles that the SDO has.
     * If the SDO does not provide any service, then an empty list is returned.
     * This operation throws SDOException with one of the following types.
     * 
     * @exception NotAvailable if the target SDO is reachable but cannot
     *                         respond.
     * @exception InternalError if the target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @return    List of ServiceProfiles of all the services the SDO is
     *            providing.
     *
     * @endif
     */
    virtual ServiceProfileList* get_service_profiles()
      throw (InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] �����ServiceProfile�μ��� 
     *
     * ���� "id" �ǻ��ꤵ�줿̾���Υ����ӥ��� ServiceProfile ���֤���
     * 
     * @param     id SDO Service �� ServiceProfile �˴�Ϣ�դ���줿���̻ҡ�
     * @return    ���ꤵ�줿 SDO Service �� ServiceProfile��
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [CORBA interface] Getting Organizations
     *
     * This operation returns the ServiceProfile that is specified by the
     * argument "id."
     * 
     * @param     id The identifier referring to one of the ServiceProfiles.
     * @return    The profile of the specified service.
     * @exception NotAvailable If the target SDO is reachable but cannot
     *                         respond.
     * @exception InternalError If the target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual ServiceProfile* get_service_profile(const char* id)
      throw (InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ���ꤵ�줿 SDO Service �μ���
     *
     * ���Υ��ڥ졼�����ϰ��� "id" �ǻ��ꤵ�줿̾���ˤ�äƶ��̤����
     * SDO �� Service �ؤΥ��֥������Ȼ��Ȥ��֤��� SDO �ˤ���󶡤����
     * Service �Ϥ��줾���դμ��̻Ҥˤ����̤���롣
     *
     * @param id SDO Service �˴�Ϣ�դ���줿���̻ҡ�
     * @return �׵ᤵ�줿 SDO Service �ؤλ��ȡ�
     *
     * @else
     *
     * @brief [CORBA interface] Getting specified SDO Service's reference
     *
     * This operation returns an object implementing an SDO's service that
     * is identified by the identifier specified as an argument. Different
     * services provided by an SDO are distinguished with different
     * identifiers. See OMG SDO specification Section 2.2.8, "ServiceProfile,"
     * on page 2-12 for more details.
     *
     * @param id The identifier referring to one of the SDO Service
     * @return The object implementing the requested service.
     *
     * @endif
     */
    virtual SDOService_ptr get_sdo_service(const char* id)
      throw (InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Configuration ���֥������Ȥμ��� 
     *
     * ���Υ��ڥ졼������ Configuration interface �ؤλ��Ȥ��֤���
     * Configuration interface �ϳ� SDO ��������뤿��Υ��󥿡��ե�������
     * �ҤȤĤǤ��롣���Υ��󥿡��ե������� DeviceProfile, ServiceProfile,
     * Organization ��������줿 SDO ��°���ͤ����ꤹ�뤿��˻��Ѥ���롣
     * Configuration ���󥿡��ե������ξܺ٤ˤĤ��Ƥϡ�OMG SDO specification
     * �� 2.3.5��, p.2-24 �򻲾ȤΤ��ȡ�
     *
     * @return SDO �� Configuration ���󥿡��ե������ؤλ���
     * @exception InterfaceNotImplemented SDO��Configuration���󥿡��ե�������
     *                                    �����ʤ���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [CORBA interface] Getting Configuration object
     *
     * This operation returns an object implementing the Configuration
     * interface. The Configuration interface is one of the interfaces that
     * each SDO maintains. The interface is used to configure the attributes
     * defined in DeviceProfile, ServiceProfile, and Organization.
     * See OMG SDO specification Section 2.3.5, "Configuration Interface,"
     * on page 2-24 for more details about the Configuration interface.
     *
     * @return The Configuration interface of an SDO.
     * @exception InterfaceNotImplemented The target SDO has no Configuration
     *                                    interface.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual Configuration_ptr get_configuration()
      throw (InterfaceNotImplemented, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Monitoring ���֥������Ȥμ��� 
     *
     * ���Υ��ڥ졼������ Monitoring interface �ؤλ��Ȥ��֤���
     * Monitoring interface �� SDO ���������륤�󥿡��ե������ΰ�ĤǤ��롣
     * ���Υ��󥿡��ե������� SDO �Υץ�ѥƥ����˥���󥰤��뤿���
     * ���Ѥ���롣
     * Monitoring interface �ξܺ٤ˤĤ��Ƥ� OMG SDO specification ��
     * 2.3.7�� "Monitoring Interface" p.2-35 �򻲾ȤΤ��ȡ�
     *
     * @return SDO �� Monitoring interface �ؤλ���
     * @exception InterfaceNotImplemented SDO��Configuration���󥿡��ե�������
     *                                    �����ʤ���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [CORBA interface] Get Monitoring object
     *
     * This operation returns an object implementing the Monitoring interface.
     * The Monitoring interface is one of the interfaces that each SDO
     * maintains. The interface is used to monitor the properties of an SDO.
     * See OMG SDO specification Section 2.3.7, "Monitoring Interface," on
     * page 2-35 for more details about the Monitoring interface.
     *
     * @return The Monitoring interface of an SDO.
     * @exception InterfaceNotImplemented The target SDO has no Configuration
     *                                    interface.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual Monitoring_ptr get_monitoring()
      throw (InterfaceNotImplemented, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �ꥹ�Ȥμ��� 
     *
     * SDO ��0�İʾ�� Organization (�ȿ�)�˽�°���뤳�Ȥ��Ǥ��롣 �⤷ SDO ��
     * 1�İʾ�� Organization �˽�°���Ƥ����硢���Υ��ڥ졼�����Ͻ�°����
     * Organization �Υꥹ�Ȥ��֤���SDO �� �ɤ� Organization �ˤ��°���Ƥ��ʤ�
     * ���ˤϡ����Υꥹ�Ȥ��֤���롣
     *
     * @return SDO ����°���� Organization �Υꥹ�ȡ�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Getting Organizations
     *
     * An SDO belongs to zero or more organizations. If the SDO belongs to one
     * or more organizations, this operation returns the list of organizations
     * that the SDO belongs to. An empty list is returned if the SDO does not
     * belong to any Organizations.
     *
     * @return The list of Organizations that the SDO belong to.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual OrganizationList* get_organizations()
      throw (NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO Status �ꥹ�Ȥμ��� 
     *
     * ���Υ��ڥ졼������ SDO �Υ��ơ�������ɽ�� NVList ���֤���
     *
     * @return SDO �Υ��ơ�������
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     *
     * @else
     *
     * @brief [CORBA interface] Get SDO Status
     *
     * This operation returns an NVlist describing the status of an SDO.
     *
     * @return The actual status of an SDO.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual NVList* get_status_list()
      throw (NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO Status �μ��� 
     *
     * This operation returns the value of the specified status parameter.
     * 
     * @param name SDO �Υ��ơ��������������ѥ�᡼����
     * @return ���ꤵ�줿�ѥ�᡼���Υ��ơ������͡�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InvalidParameter ���� "name" �� null ���뤤��¸�ߤ��ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get SDO Status
     *
     * @param name One of the parameters defining the "status" of an SDO.
     * @return The value of the specified status parameter.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The parameter defined by "name" is null or
     *                             does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     *
     * @endif
     */
    virtual CORBA::Any* get_status(const char* name)
      throw (InvalidParameter, NotAvailable, InternalError);
    
    // end of CORBA interface definition
    //============================================================


    //============================================================
    //
    // <<< Local interfaces >>>
    //
    //============================================================

    void setSdoId(const char* sdo_id);
    void setSdoType(const char* sdo_type);
    void setDeviceProfile(const DeviceProfile& device_profile);
    void setServiceProfiles(const ServiceProfileList& service_profile);
    void addServiceProfile(const ServiceProfile& service_profile);
    
    
  protected:
    // Partial specialization
    template <class T, class X>
    class SeqEx
      : public SequenceEx <T, X, ACE_Thread_Mutex> {};
    
    struct SdoId
    {
      CORBA::String_var _id;
      ACE_Thread_Mutex _mutex;
    };

    struct SdoType
    {
      CORBA::String_var _type;
      ACE_Thread_Mutex _mutex;
    };

    SdoId m_SdoId;
    SdoType m_SdoType;


    Configuration_impl* m_pConfig;


    Configuration_var m_varConfiguration;
    Monitoring_var m_varMonitoring;
    SeqEx<NVList, NameValue> m_Status;
    
    // functor for ServiceProfile
    struct nv_name
    {
      nv_name(const char* id) : m_name(id) {};
      bool operator()(const NameValue& v)
      {
	std::string name(v.name);
	return m_name == name;
      }
      const std::string m_name;
    };


    PortableServer::ObjectId_var m_varConfigId;
    SDOPackage::Configuration_var m_varConfigObj;

    PortableServer::ObjectId_var m_varOrgId;
    SDOPackage::Configuration_var m_varOrgObj;

  };

}; // namespace SDOPackage

#endif // SdoSystemElement_h
