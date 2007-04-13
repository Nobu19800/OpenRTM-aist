// -*- C++ -*-
/*!
 * @file RTObject.h
 * @brief RT component base class
 * @date $Date: 2007-04-13 15:55:43 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTObject.h,v 1.6 2007-04-13 15:55:43 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5  2007/01/14 22:59:01  n-ando
 * A bug fix about template argument for buffer-type.
 *
 * Revision 1.4  2007/01/14 19:46:14  n-ando
 * The component action implementation functions for Users' business logic
 * were added (i.e onInitialize(), onExecute(), etc..)
 *
 * Revision 1.3  2007/01/12 14:38:48  n-ando
 * The registeInPort()/registerOutPort functions are added.
 *
 * Revision 1.2  2007/01/09 15:21:47  n-ando
 * SDO interfaces are marged.
 * Some RTObject's operation signatures were changed.
 *
 * Revision 1.1  2006/09/11 19:04:38  n-ando
 * The first commit.
 *
 *
 */

#ifndef RTObject_h
#define RTObject_h

// CORBA header include
#include "rtm/RTC.h"
#include "rtm/Properties.h"
#include "rtm/idl/RTCSkel.h"
#include "rtm/idl/OpenRTMSkel.h"
#include "rtm/PortBase.h"
//#include "rtm/ObjectManager.h"
#include "rtm/PortAdmin.h"
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/InPort.h>
#include <rtm/OutPort.h>

// ACE
#include <ace/Task.h>


namespace SDOPackage
{
  class Configuration_impl;
};

namespace RTC
{
  class Manager;

  class RTObject_impl
    : public virtual POA_RTC::DataFlowComponent, 
      public virtual PortableServer::RefCountServantBase
  {
  public:
    RTObject_impl(Manager* manager);
    RTObject_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    virtual ~RTObject_impl();


  protected:
    //============================================================
    // Overridden functions
    //============================================================
    // The initialize action (on CREATED->ALIVE transition)
    // formaer rtc_init_entry() 
    virtual ReturnCode_t onInitialize();
    
    // The finalize action (on ALIVE->END transition)
    // formaer rtc_exiting_entry()
    virtual ReturnCode_t onFinalize();
    
    // The startup action when ExecutionContext startup
    // former rtc_starting_entry()
    virtual ReturnCode_t onStartup(RTC::UniqueId ec_id);
    
    // The shutdown action when ExecutionContext stop
    // former rtc_stopping_entry()
    virtual ReturnCode_t onShutdown(RTC::UniqueId ec_id);
    
    // The activated action (Active state entry action)
    // former rtc_active_entry()
    virtual ReturnCode_t onActivated(RTC::UniqueId ec_id);
    
    // The deactivated action (Active state exit action)
    // former rtc_active_exit()
    virtual ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
    
    // The execution action that is invoked periodically
    // former rtc_active_do()
    virtual ReturnCode_t onExecute(RTC::UniqueId ec_id);
    
    // The aborting action when main logic error occurred.
    // former rtc_aborting_entry()
    virtual ReturnCode_t onAborting(RTC::UniqueId ec_id);
    
    // The error action in ERROR state
    // former rtc_error_do()
    virtual ReturnCode_t onError(RTC::UniqueId ec_id);
    
    // The reset action that is invoked resetting
    // This is same but different the former rtc_init_entry()
    virtual ReturnCode_t onReset(RTC::UniqueId ec_id);
    
    // The state update action that is invoked after onExecute() action
    // no corresponding operation exists in OpenRTm-aist-0.2.0
    virtual ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

    // The action that is invoked when execution context's rate is changed
    // no corresponding operation exists in OpenRTm-aist-0.2.0
    virtual ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


  public:
    //============================================================
    // RTC::LightweightRTObject
    //============================================================
    /*!
     * @if jp
     *
     * @breif RTC����������
     *
     * ���Υ��ڥ졼�����ƤӽФ��η�̤Ȥ��ơ�ComponentAction::on_initialize
     * ������Хå��ؿ����ƤФ�롣
     * ����
     * Created���֤ˤ���Ȥ��ˤΤߡ���������Ԥ��롣¾�ξ��֤ˤ�����ˤ�
     * ReturnCode_t::PRECONDITION_NOT_MET ���֤���ƤӽФ��ϼ��Ԥ��롣
     * ���Υ��ڥ졼������RTC�Υߥɥ륦��������ƤФ�뤳�Ȥ����ꤷ�Ƥ��ꡢ
     * ���ץꥱ�������ȯ�Ԥ�ľ�ܤ��Υ��ڥ졼������Ƥ֤��Ȥ�����
     * ����Ƥ��ʤ���
     * 
     * @else
     *
     * @breif Initialize the RTC that realizes this interface.
     *
     * The invocation of this operation shall result in the invocation of the
     * callback ComponentAction::on_initialize.
     *
     * Constraints
     * - An RTC may be initialized only while it is in the Created state. Any
     *   attempt to invoke this operation while in another state shall fail
     *   with ReturnCode_t::PRECONDITION_NOT_MET.
     * - Application developers are not expected to call this operation
     *   directly; it exists for use by the RTC infrastructure.
     *
     * @endif
     */
    virtual ReturnCode_t initialize();


    /*!
     * @if jp
     *
     * @brief RTC����ν����Τ��Ὢλ������
     *
     * ���Υ��ڥ졼�����ƤӽФ��Ϸ�̤Ȥ���ComponentAction::on_finalize()
     * ��ƤӽФ���
     *
     * ����
     * - ���� RTC ��°���� Running ���֤μ¹ԥ���ƥ������桢Active ���֤ˤ���
     *   ��Τ�����Ф��� RTC �Ͻ�λ����ʤ������ξ�硢���Υ��ڥ졼�����Ƥ�
     *   �Ф��Ϥ����ʤ���� ReturnCode_t::PRECONDITION_NOT_ME �Ǽ��Ԥ��롣
     * - ���� RTC �� Created ���֤Ǥ����硢��λ�����ϹԤ��ʤ���
     *   ���ξ�硢���Υ��ڥ졼�����ƤӽФ��Ϥ����ʤ���� 
     *   ReturnCode_t::PRECONDITION_NOT_MET �Ǽ��Ԥ��롣
     * - ���ץꥱ�������ȯ�ԤϤ��Υ��ڥ졼������ľ��Ū�˸ƤӽФ����Ȥ�
     *   �ޤ�Ǥ��ꡢ�����Ƥ���RTC����ե饹�ȥ饯���㤫��ƤӽФ���롣
     *
     * @else
     *
     * @brief Finalize the RTC for preparing it for destruction
     * 
     * This invocation of this operation shall result in the invocation of the
     * callback ComponentAction::on_finalize.
     *
     * Constraints
     * - An RTC may not be finalized while it is Active in any Running
     *   execution context. Any attempt to invoke this operation at such a time
     *   shall fail with ReturnCode_t::PRECONDITION_NOT_MET.
     * - An RTC may not be finalized while it is in the Created state.
     *   Any attempt to invoke this operation while in that state shall fail
     *   with ReturnCode_t::PRECONDITION_NOT_MET.
     * - Application developers are not expected to call this operation
     *   directly; it exists for use by the RTC infrastructure.
     *
     * @endif
     */
    virtual ReturnCode_t finalize();


    /*!
     * @if jp
     *
     * @brief RTC����ߤ��������Υ���ƥ�Ĥȶ��˽�λ������
     *
     * ���� RTC �������ʡ��Ǥ��뤹�٤Ƥμ¹ԥ���ƥ����Ȥ���ߤ���롣
     * ���� RTC ��¾�μ¹ԥ���ƥ����Ȥ��ͭ���� RTC ��°����¹ԥ���ƥ�����
     * (i.e. �¹ԥ���ƥ����Ȥ��ͭ���� RTC �Ϥ��ʤ�����μ¹ԥ���ƥ����Ȥ�
     * �����ʡ��Ǥ��롣)�˻��ä��Ƥ����硢���� RTC �Ϥ����Υ���ƥ����Ⱦ�
     * �������������ʤ���Фʤ�ʤ���
     * 
     * ����
     * - RTC �����������Ƥ��ʤ���С���λ�����뤳�ȤϤǤ��ʤ���
     *   Created ���֤ˤ��� RTC �� exit() ��ƤӽФ�����硢
     *   ReturnCode_t::PRECONDITION_NOT_MET �Ǽ��Ԥ��롣
     *
     * @else
     *
     * @brief Stop the RTC's and finalize it along with its contents.
     * 
     * Any execution contexts for which the RTC is the owner shall be stopped. 
     * If the RTC participates in any execution contexts belonging to another
     * RTC that contains it, directly or indirectly (i.e. the containing RTC
     * is the owner of the ExecutionContext), it shall be deactivated in those
     * contexts.
     * After the RTC is no longer Active in any Running execution context, it
     * and any RTCs contained transitively within it shall be finalized.
     *
     * Constraints
     * - An RTC cannot be exited if it has not yet been initialized. Any
     *   attempt to exit an RTC that is in the Created state shall fail with
     *   ReturnCode_t::PRECONDITION_NOT_MET.
     *
     * @endif
     */
    virtual ReturnCode_t exit(); 

    /*!
     * @if jp
     *
     * @brief
     *
     * @else
     *
     * @brief
     *
     * A component is alive or not regardless of the execution context from
     * which it is observed. However, whether or not it is Active, Inactive,
     * or in Error is dependent on the execution context(s) in which it is
     * running. That is, it may be Active in one context but Inactive in
     * another. Therefore, this operation shall report whether this RTC is
     * either Active, Inactive or in Error; which of those states a component
     * is in with respect to a particular context may be queried from the
     * context itself.
     *
     * @endif
     */
    virtual CORBA::Boolean is_alive();


    /*!
     * @if jp
     * @brief [CORBA interface] ExecutionContextList���������
     * @else
     * @brief [CORBA interface] Get ExecutionContextList.
     * @endif
     */
    virtual ExecutionContextList* get_contexts();

    /*!
     * @if jp
     * @brief [CORBA interface] ExecutionContext���������
     * @else
     * @brief [CORBA interface] Get ExecutionContext.
     * @endif
     */
    virtual ExecutionContext_ptr get_context(const UniqueId ec_id);

    /*
    virtual UniqueId 
    set_execution_context_service(const ExecutionContextService_ptr ec);
    */

    //============================================================
    // RTC::RTObject
    //============================================================
    /*!
     * @if jp
     *
     * @brief [RTObject CORBA interface] ����ݡ��ͥ�ȥץ�ե�����μ���
     *
     * ��������ݡ��ͥ�ȤΥץ�ե����������֤��� 
     *
     * @else
     *
     * @brief [RTObject CORBA interface] Get RTC's profile
     *
     * This operation returns the ComponentProfile of the RTC
     *
     * @endif
     */
    virtual ComponentProfile* get_component_profile();


    /*!
     * @if jp
     *
     * @brief [RTObject CORBA interface] �ݡ��Ȥμ���
     *
     * ��������ݡ��ͥ�Ȥ���ͭ����ݡ��Ȥλ��Ȥ��֤���
     *
     * @else
     *
     * @brief [RTObject CORBA interface] Get Ports
     *
     * This operation returns a list of the RTCs ports.
     *
     * @endif
     */
    virtual PortList* get_ports();


    /*!
     * @if jp
     *
     * @brief [RTObject CORBA interface] ExecutionContextAdmin �μ���
     *
     * ���Υ��ڥ졼������������RTC ����°���� ExecutionContext�˴�Ϣ����
     * ExecutionContextAdmin �Υꥹ�Ȥ��֤���
     *
     * @else
     *
     * @brief [RTObject CORBA interface] Get ExecutionContextAdmin
     *
     * This operation returns a list containing an ExecutionContextAdmin for
     * every ExecutionContext owned by the RTC.	
     *
     * @endif
     */
    virtual ExecutionContextServiceList* get_execution_context_services();



    // RTC::ComponentAction
    UniqueId attach_executioncontext(ExecutionContext_ptr exec_context);
    ReturnCode_t detach_executioncontext(UniqueId ec_id);
    virtual ReturnCode_t on_initialize();
    virtual ReturnCode_t on_finalize();
    virtual ReturnCode_t on_startup(UniqueId ec_id);
    virtual ReturnCode_t on_shutdown(UniqueId ec_id);
    virtual ReturnCode_t on_activated(UniqueId ec_id);
    virtual ReturnCode_t on_deactivated(UniqueId ec_id);
    virtual ReturnCode_t on_aborting(UniqueId ec_id);
    virtual ReturnCode_t on_error(UniqueId ec_id);
    virtual ReturnCode_t on_reset(UniqueId ec_id);

    virtual ReturnCode_t on_execute(UniqueId ec_id);
    virtual ReturnCode_t on_state_update(UniqueId ec_id);
    virtual ReturnCode_t on_rate_changed(UniqueId ec_id);



    //============================================================
    // SDOPackage::SdoSystemElement
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
    virtual SDOPackage::OrganizationList* get_owned_organizations()
      throw (SDOPackage::NotAvailable);


    //============================================================
    // SDOPackage::SDO
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
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError);
    
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
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError);

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
    virtual SDOPackage::DeviceProfile* get_device_profile()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError);
    
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
    virtual SDOPackage::ServiceProfileList* get_service_profiles()
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
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
    virtual SDOPackage::ServiceProfile* get_service_profile(const char* id)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
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
    virtual SDOPackage::SDOService_ptr get_sdo_service(const char* id)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
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
    virtual SDOPackage::Configuration_ptr get_configuration()
      throw (SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
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
    virtual SDOPackage::Monitoring_ptr get_monitoring()
      throw (SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);

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
    virtual SDOPackage::OrganizationList* get_organizations()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError);
    
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
    virtual SDOPackage::NVList* get_status_list()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError);
    
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
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);



    //============================================================
    // Local interfaces
    //============================================================
    const char* getInstanceName() {return m_profile.instance_name;}
    void setInstanceName(const char* instance_name);
    const char* getTypeName() {return m_profile.type_name;}
    const char* getDescription() { return m_profile.description;}
    const char* getVersion() {return m_profile.version;}
    const char* getVendor() {return m_profile.vendor;}
    const char* getCategory() {return m_profile.category;}

    std::vector<std::string> getNamingNames();

    void setObjRef(const RTObject_ptr rtobj);
    RTObject_ptr getObjRef() const;



    /*!
     * @if jp
     * 
     * @brief [local interface] RTC �Υץ�ѥƥ������ꤹ��
     *
     * RTC ���ݻ����٤��ץ�ѥƥ������ꤹ�롣Ϳ������ץ�ѥƥ��ϡ�
     * ComponentProfile �������ꤵ���٤����������ʤ���Фʤ�ʤ���
     * ���Υ��ڥ졼�������̾� RTC ������������ݤ� Manager ����
     * �ƤФ�뤳�Ȥ�տޤ��Ƥ��롣
     * 
     * @param prop RTC �Υץ�ѥƥ�
     *
     * @else
     *
     * @brief [local interface] Set RTC property
     *
     * This operation sets the properties to the RTC. The given property
     * values should include information for ComponentProfile.
     * Generally, this operation is designed to be called from Manager, when
     * RTC is initialized
     *
     * @param prop Property for RTC.
     *
     * @endif
     */
    void setProperties(const Properties& prop);

    /*!
     * @if jp
     * 
     * @brief [local interface] RTC �Υץ�ѥƥ����������
     *
     * RTC ���ݻ����Ƥ���ץ�ѥƥ����֤���Ϳ������ץ�ѥƥ��ϡ�
     * RTC���ץ�ѥƥ�������ʤ����϶��Υץ�ѥƥ����֤���롣
     * 
     * @return RTC �Υץ�ѥƥ�
     *
     * @else
     *
     * @brief [local interface] Get RTC property
     *
     * This operation returns the properties of the RTC.
     * Empty property would be returned, if RTC has no property.
     *
     * @return Property for RTC.
     *
     * @endif
     */
    Properties& getProperties();


    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ����
     *
     * RTC ���ݻ�����Port����Ͽ���롣
     * Port �������饢��������ǽ�ˤ��뤿��ˤϡ����Υ��ڥ졼�����ˤ��
     * ��Ͽ����Ƥ��ʤ���Фʤ�ʤ�����Ͽ����� Port �Ϥ��� RTC �����ˤ�����
     * PortProfile.name �ˤ����̤���롣�������äơ�Port �� RTC ��ˤ����ơ�
     * ��ˡ����� PortProfile.name ������ʤ���Фʤ�ʤ���
     * ��Ͽ���줿 Port ��������Ŭ�ڤ˥����ƥ��ֲ����줿�塢���λ��Ȥ�
     * ���֥������Ȼ��Ȥ��ꥹ�������¸����롣
     * 
     * @param port RTC ����Ͽ���� Port
     *
     * @else
     *
     * @brief [local interface] Register Port
     *
     * This operation registers a Port to be held by this RTC.
     * In order to enable access to the Port from outside of RTC, the Port
     * must be registered by this operation. The Port that is registered by
     * this operation would be identified by PortProfile.name in the inside of
     * RTC. Therefore, the Port should have unique PortProfile.name in the RTC.
     * The registering Port would be activated properly, and the reference
     * and the object reference would be stored in lists in RTC.
     *
     * @param port Port which is registered in the RTC
     *
     * @endif
     */
    void registerPort(PortBase& port);

    template <class DataType, template <class DataType> class Buffer>
    void registerInPort(const char* name,
			InPort<DataType, Buffer>& inport)
    {
      PortBase* port = new DataInPort(name, inport);
      registerPort(*port);
    }

    template <class DataType, template <class DataType> class Buffer>
    void registerOutPort(const char* name,
			 OutPort<DataType, Buffer>& outport)
    {
      PortBase* port = new DataOutPort(name, outport);
      registerPort(*port);
    }
      

    /*!
     * @if jp
     * 
     * @brief [local interface] Port ����Ͽ��������
     *
     * RTC ���ݻ�����Port����Ͽ�������롣
     * 
     * @param port RTC ����Ͽ���� Port
     *
     * @else
     *
     * @brief [local interface] Register Port
     *
     * This operation registers a Port to be held by this RTC.
     * In order to enable access to the Port from outside of RTC, the Port
     * must be registered by this operation. The Port that is registered by
     * this operation would be identified by PortProfile.name in the inside of
     * RTC. Therefore, the Port should have unique PortProfile.name in the RTC.
     * The registering Port would be activated properly, and the reference
     * and the object reference would be stored in lists in RTC.
     *
     * @param port Port which is registered in the RTC
     *
     * @endif
     */
    void deletePort(PortBase& port);
    void deletePortByName(const char* port_name);
    void finalizePorts();



    /*
    template <class DataType>
    void registerInPort(BufferBase<DataType>& buffer)
    {
      CorbaInPort<DataType>* port;
      p = new CorbaInPort<DataType>(buffer);
      Port_var inport;
      inport = new PortInPort();
      inport->setInPortRef(p->_this());
    }
    */





  protected:
    //============================================================
    // SDO �ط����ѿ�
    //============================================================
    /*!
     * SDO owned organization list
     */
    SDOPackage::OrganizationList m_sdoOwnedOrganizations;

    /*!
     * SDOService �Υץ�ե�����ꥹ��
     */
    SDOPackage::ServiceProfileList m_sdoSvcProfiles;

    /*!
     * SDOService �Υץ�ե�����ꥹ�Ȥ���id�ǥ��������뤿��Υե��󥯥�
     */
    struct svc_name
    {
      svc_name (const char* id) : m_id(id) {};
      bool operator()(const SDOPackage::ServiceProfile& prof)
      {
	return m_id == std::string(prof.id);
      }
      std::string m_id;
    };

    /*!
     * SDO Configuratio Interface �ؤΥݥ���
     */
    SDOPackage::Configuration_impl* m_pSdoConfigImpl;
    SDOPackage::Configuration_var  m_pSdoConfig;

    /*!
     * SDO organization
     */
    SDOPackage::OrganizationList m_sdoOrganizations;

    /*!
     * SDO Status
     */
    SDOPackage::NVList m_sdoStatus;

    
    //============================================================
    // RTC �ط����ѿ�
    //============================================================
    /*!
     * RTC::ComponentProfile
     */
    ComponentProfile m_profile;

    RTObject_ptr m_objref;
    /*!
     * Port �Υ��֥������ȥ�ե���󥹤Υꥹ��
     */
    PortAdmin m_portAdmin;

    ExecutionContextServiceList m_execContexts;

    bool m_created;
    bool m_alive;

    /*!
     * RTC �Υץ�ѥƥ�
     */
    Properties m_properties;

    struct nv_name
    {
      nv_name(const char* name) : m_name(name) {};
      bool operator()(const SDOPackage::NameValue& nv)
      {
        return m_name == std::string(nv.name);
      }
      std::string m_name;
    };


    struct ec_copy
    {
      ec_copy(ExecutionContextList& eclist)
	: m_eclist(eclist)
      {
      }
      void operator()(ExecutionContextService_ptr ecs)
      {
	CORBA_SeqUtil::push_back(m_eclist, ExecutionContext::_duplicate(ecs));
      }
      ExecutionContextList& m_eclist;
    };
    //    ExecutionContextAdminList m_execContextList;

    struct deactivate_comps
    {
      deactivate_comps(LightweightRTObject_ptr comp)
	: m_comp(comp)
      {
      }
      void operator()(ExecutionContextService_ptr ec)
      {
	ec->deactivate_component(RTC::LightweightRTObject::_duplicate(m_comp));
      }
      LightweightRTObject_var m_comp;
    };


  };
};
#endif // RTObject
