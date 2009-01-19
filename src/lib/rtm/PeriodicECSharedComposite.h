// -*- C++ -*-
/*!
 * @file PeriodicECSharedComposite.h
 * @brief Periodic Execution Context Shared Composite Component class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef PeriodicECSharedComposite_h
#define PeriodicECSharedComposite_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>
#include <rtm/RTObject.h>
#include <rtm/PeriodicExecutionContext.h>
#include <rtm/SdoOrganization.h>
#include <coil/stringutil.h>

/*!
 * @if jp
 * @namespace SDOPacakge
 *
 * @brief SDO
 *
 * @else
 *
 * @namespace SDOPackage
 *
 * @brief SDO
 *
 * @endif
 */
namespace SDOPackage
{
  class PeriodicECOrganization
    : public Organization_impl
  {
  public:
    PeriodicECOrganization(::RTC::RTObject_impl* rtobj);
    virtual ~PeriodicECOrganization();

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization���С����ɲä���
     *
     * Organization ���ݻ�������С��ꥹ�Ȥ�Ϳ����줿SDOList���ɲä��롣
     * 
     * @param sdo_list �ɲä���� SDO ���С��Υꥹ��
     * @return �ɲä������������ɤ�����bool���֤����
     *
     * @else
     * 
     * @brief [CORBA interface] Add Organization member
     *
     * This operation adds the given SDOList to the existing organization's 
     * member list
     * 
     * @param sdo_list SDO member list to be added
     * @return boolean will returned if the operation succeed
     *
     * @endif
     */
    virtual ::CORBA::Boolean add_members(const SDOList& sdo_list)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization���С��򥻥åȤ���
     *
     * Organization ���ݻ�������С��ꥹ�Ȥ�������Ϳ����줿
     * SDOList�򿷵��˥��åȤ��롣
     * 
     * @param sdo_list �����˥��åȤ���� SDO ���С��Υꥹ��
     * @return �ɲä������������ɤ�����bool���֤����
     *
     * @else
     * 
     * @brief [CORBA interface] Set Organization member
     *
     * This operation removes existing member list and sets the given
     * SDOList to the existing organization's member list
     * 
     * @param sdo_list SDO member list to be set
     * @return boolean will returned if the operation succeed
     *
     * @endif
     */
    virtual ::CORBA::Boolean set_members(const SDOList& sdos)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization���С���������
     *
     * Organization ���ݻ�������С��ꥹ����������SDO�������롣
     * 
     * @param id �������� SDO �� ID
     * @return �ɲä������������ɤ�����bool���֤����
     *
     * @else
     * 
     * @brief [CORBA interface] Remove a member of Organization
     *
     * This operation removes a SDO from existing member list by specified ID.
     * 
     * @param id The ID of the SDO to be removed
     * @return boolean will returned if the operation succeed
     *
     * @endif
     */
    virtual ::CORBA::Boolean remove_member(const char* id)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);

  protected:
    /*!
     * @if jp
     * @brief SDO����DFC�ؤ��Ѵ�
     * @else
     * @brief Conversion from SDO to DFC
     * @endif
     */
    bool sdoToDFC(const SDO_ptr sdo, ::OpenRTM::DataFlowComponent_ptr& dfc);

    /*!
     * @if jp
     * @brief Owned ExecutionContext ����ߤ�����
     * @else
     * @brief Stop Owned ExecutionContexts
     * @endif
     */
    void stopOwnedEC(::OpenRTM::DataFlowComponent_ptr dfc);

    /*!
     * @if jp
     * @brief DFC �� Organization ���֥������Ȥ�Ϳ����
     * @else
     * @brief Set Organization object to target DFC 
     * @endif
     */
    void setOrganizationToTarget(::OpenRTM::DataFlowComponent_ptr dfc);

    /*!
     * @if jp
     * @brief Composite �� ExecutionContext �� DFC �˥��åȤ���
     * @else
     * @brief Set CompositeRTC's ExecutionContext to the given DFC
     * @endif
     */
    void setCompositeECToTarget(::OpenRTM::DataFlowComponent_ptr dfc);

    /*!
     * @if jp
     * @brief �ݡ��Ȥ�Ѿ�����
     * @else
     * @brief Delegate given RTC's ports to the Composite
     * @endif
     */
    void delegatePort(::OpenRTM::DataFlowComponent_ptr dfc);


  protected:
    ::RTC::RTObject_impl* m_rtobj;
    ::RTC::ExecutionContext_ptr m_ec;
    ::RTC::RTCList m_rtcMembers;

  private:

    class set_member
    {
    public:
      set_member(Organization_ptr org, ::RTC::RTCList& rtcs,
                 ::RTC::RTObject_impl* rtobj)
        : m_org(org), m_rtcMembers(rtcs), m_rtobj(rtobj)
      {
        // std::cout << "set_member() ctor" << std::endl;
        ::RTC::ExecutionContextList_var ecs = m_rtobj->get_owned_contexts();
        // std::cout << "m_rtobj->get_owned_contexts(): " << ecs->length() << std::endl;
        m_ec = ecs[0];
      }
      ~set_member(){}

      void operator()(const SDO_ptr sdo)
      {
        if (::CORBA::is_nil(sdo)) return;

        // narrowing: SDO -> RTC (DataFlowComponent)
        ::OpenRTM::DataFlowComponent_var dfc;
        dfc = ::OpenRTM::DataFlowComponent::_narrow(sdo);
        if (::CORBA::is_nil(dfc)) return;

        // stop target RTC's ExecutionContext
        ::RTC::ExecutionContextList_var ecs;
        ecs = dfc->get_owned_contexts();
        for (::CORBA::ULong i(0), len(ecs->length()); i < len; ++i)
          {
            ecs[i]->stop();
          }

        // get given RTC's configuration object
        Configuration_var conf;
        conf = dfc->get_configuration();
        if (::CORBA::is_nil(conf)) return;

        // set organization to target RTC's conf
        conf->add_organization(m_org);
        // set ec to target RTC
        m_ec->add_component(dfc);

        // port delegation
        ::RTC::PortServiceList_var plist = dfc->get_ports();
        for (::CORBA::ULong i(0), len(plist->length()); i < len; ++i)
          {
            std::string port_name;
            ::RTC::PortProfile_var prof = plist[i]->get_port_profile();
            std::cout << "port name:" << prof->name << std::endl;
            m_rtobj->registerPort(::RTC::PortService::_duplicate(plist[i]));
          }

        // finally store target RTC to member list
        ::CORBA_SeqUtil::push_back(m_rtcMembers,
                                   ::RTC::RTObject::_duplicate(dfc));
        // std::cout << "set_member done" << std::endl;
      }
    private:
      Organization_ptr m_org;
      ::RTC::RTCList& m_rtcMembers;
      ::RTC::RTObject_impl* m_rtobj;
      ::RTC::ExecutionContext_ptr m_ec;
    };

    class erase_pred
    {
    public:
      erase_pred(::RTC::RTObject_ptr rtobj)
        : m_rtobj(rtobj)
      {
      }

      bool operator()(::RTC::RTObject_ptr rtobj)
      {
        return m_rtobj->_is_equivalent(rtobj);
      }
      ::RTC::RTObject_ptr m_rtobj;
    };

    class remove_member_f
    {
    public:
      remove_member_f(Organization_ptr org, ::RTC::RTCList& rtcs, const char* id,
                 ::RTC::RTObject_impl* rtobj)
        : m_org(org), m_rtcMembers(rtcs), m_id(id), m_rtobj(rtobj)
      {
        ::RTC::ExecutionContextList_var ecs = m_rtobj->get_owned_contexts();
        m_ec = ecs[0];
      }
      ~remove_member_f(){}

      void operator()(const SDO_ptr sdo)
      {
        if (::CORBA::is_nil(sdo)) return;

        ::OpenRTM::DataFlowComponent_var dfc;
        dfc = ::OpenRTM::DataFlowComponent::_narrow(sdo);
        if (::CORBA::is_nil(dfc)) return;

        ::RTC::ComponentProfile_var prof = dfc->get_component_profile();
        const char* name = prof->instance_name;
        if (!(m_id == name)) return;


        // stop target RTC's ec
        ::RTC::ExecutionContextList_var ecs;
        ecs = dfc->get_owned_contexts();

        for (::CORBA::ULong i(0), len(ecs->length()); i < len; ++i)
          {
            ecs[i]->start();
          }

        // get configuration object
        Configuration_var conf;
        conf = dfc->get_configuration();
        if (::CORBA::is_nil(conf)) return;

        // set organization to target RTC's conf
        conf->remove_organization(m_org->get_organization_id());

        // set ec to target RTC
        m_ec->remove_component(dfc);

        // port
        ::RTC::PortServiceList_var plist = dfc->get_ports();
        for (::CORBA::ULong i(0), len(plist->length()); i < len; ++i)
          {
            m_rtobj->deletePort(::RTC::PortService::_duplicate(plist[i]));
          }

        ::CORBA_SeqUtil::erase_if(m_rtcMembers, erase_pred(dfc));
      }
    private:
      Organization_ptr m_org;
      ::RTC::RTCList& m_rtcMembers;
      std::string m_id;
      ::RTC::RTObject_impl* m_rtobj;
      ::RTC::ExecutionContext_ptr m_ec;
    };
  };
};


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
  class Manager;

  /*!
   * @if jp
   * @class PeriodicECSharedComposite
   * @brief PeriodicECSharedComposite ���饹
   *
   * �ǡ����ե���RTComponent�δ��쥯�饹��
   * �Ƽ�ǡ����ե���RTComponent�����������ϡ��ܥ��饹��Ѿ�������Ǽ���
   * ���롣
   *
   * @since 0.4.0
   *
   * @else
   * @class PeriodicECSharedComposite
   * @brief PeriodicECSharedComposite class
   *
   * This is a base class of the data flow type RT-Component.
   * Inherit this class when implementing various data flow type RT-Components.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class PeriodicECSharedComposite
    : public RTObject_impl
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param manager �ޥ͡����㥪�֥�������
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param manager Manager object
     *
     * @endif
     */
    PeriodicECSharedComposite(Manager* manager);
    
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
    virtual ~PeriodicECSharedComposite();
    
    /*!
     * @if jp
     * @brief �����
     *
     * �ǡ����ե��� RTComponent �ν������¹Ԥ��롣
     * �ºݤν���������ϡ��ƶ�ݥ��饹��˵��Ҥ��롣
     *
     * @else
     * @brief Initialization
     *
     * Initialization the data flow type RT-Component.
     * Write the actual initialization code in each concrete class.
     *
     * @endif
     */
    virtual ReturnCode_t onInitialize();
    virtual ReturnCode_t onActivated(RTC::UniqueId exec_handle);
    virtual ReturnCode_t onDeactivated(RTC::UniqueId exec_handle);
    virtual ReturnCode_t onReset(RTC::UniqueId exec_handle);

  protected:
    std::vector<std::string> m_members;

    OpenRTM::DataFlowComponent_var m_ref;
    PeriodicExecutionContext* m_pec;
    ExecutionContextService_var m_ecref;
    SDOPackage::PeriodicECOrganization* m_org;
  };
}; // namespace RTC

extern "C"
{
  DLL_EXPORT void PeriodicECSharedCompositeInit(RTC::Manager* manager);
};

#endif // PeriodicECSharedComposite_h
