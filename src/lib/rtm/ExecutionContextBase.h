// -*- C++ -*-
/*!
 * @file ExecutionContextBase.h
 * @brief ExecutionContext base class
 * @date $Date: 2008-01-14 07:48:55 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_EXECUTIONCONTEXTBASE_H
#define RTC_EXECUTIONCONTEXTBASE_H

#include <coil/Factory.h>

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>
#include <rtm/Factory.h>
#include <rtm/ExecutionContextProfile.h>

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace coil
{
  class Properties;
}

namespace RTC
{
  /*!
   * @if jp
   * @class ExecutionContextBase
   * @brief ExecutionContext�Ѵ��쥯�饹
   *
   * ExecutionContext�δ��쥯�饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class ExecutionContextBase
   * @brief A base class for ExecutionContext
   *
   * A base class of ExecutionContext.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ExecutionContextBase
  {
  public:
    /*!
     * @if jp
     * @brief ���ۥǥ��ȥ饯��
     *
     * ���ۥǥ��ȥ饯��
     *
     * @else
     * @brief Virtual Destructor
     *
     * Virtual Destructor
     *
     * @endif
     */
    virtual ~ExecutionContextBase(void);

    /*!
     * @if jp
     * @brief ExecutionContext�ν�����ʤ��
     *
     * ExecutionContext�ν����򣱼���ʬ�ʤ�롣
     *
     * @else
     * @brief Proceed with tick of ExecutionContext
     *
     * Proceed with tick of ExecutionContext for one period.
     *
     * @endif
     */
    virtual void init(coil::Properties& props);

    /*!
     * @if jp
     * @brief ����ݡ��ͥ�Ȥ�Х���ɤ��롣
     *
     * ����ݡ��ͥ�Ȥ�Х���ɤ��롣
     *
     * @else
     * @brief Bind the component.
     *
     * Bind the component.
     *
     * @endif
     */
    virtual RTC::ReturnCode_t bindComponent(RTObject_impl* rtc) = 0;

    //============================================================
    // Delegated functions to ExecutionContextProfile
    //============================================================
    /*!
     * @if jp
     * @brief CORBA ���֥������Ȼ��Ȥμ���
     *
     * �ܥ��֥������Ȥ� ExecutioncontextService �Ȥ��Ƥ� CORBA ���֥���
     * ���Ȼ��Ȥ�������롣
     *
     * @return CORBA ���֥������Ȼ���
     *
     * @else
     * @brief Get the reference to the CORBA object
     *
     * Get the reference to the CORBA object as
     * ExecutioncontextService of this object.
     *
     * @return The reference to CORBA object
     *
     * @endif
     */
    void setObjRef(RTC::ExecutionContextService_ptr ec_ptr)
    {
      m_profile.setObjRef(ec_ptr);
    }

    /*!
     * @if jp
     * @brief CORBA ���֥������Ȼ��Ȥμ���
     *
     * �ܥ��֥������Ȥ� ExecutioncontextService �Ȥ��Ƥ� CORBA ���֥���
     * ���Ȼ��Ȥ�������롣
     *
     * @return CORBA ���֥������Ȼ���
     *
     * @else
     * @brief Get the reference to the CORBA object
     *
     * Get the reference to the CORBA object as
     * ExecutioncontextService of this object.
     *
     * @return The reference to CORBA object
     *
     * @endif
     */
    RTC::ExecutionContextService_ptr getObjRef(void) const
    {
      return m_profile.getObjRef();
    }

    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Լ���(Hz)�����ꤹ��
     *
     * Active ���֤ˤ�RT����ݡ��ͥ�Ȥ��¹Ԥ�������(ñ��:Hz)�����ꤹ
     * �롣�¹Լ������ѹ��ϡ�DataFlowComponentAction ��
     * on_rate_changed �ˤ�äƳ�RT����ݡ��ͥ�Ȥ���ã����롣
     *
     * @param rate ��������(ñ��:Hz)
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *         RTC_OK: ���ｪλ
     *         BAD_PARAMETER: �����ͤ������
     *
     * @else
     *
     * @brief Set execution rate(Hz) of ExecutionContext
     *
     * This operation shall set the rate (in hertz) at which this
     * context��s Active participating RTCs are being called.  If the
     * execution kind of the context is PERIODIC, a rate change shall
     * result in the invocation of on_rate_changed on any RTCs
     * realizing DataFlowComponentAction that are registered with any
     * RTCs participating in the context.
     *
     * @param rate Execution cycle(Unit:Hz)
     *
     * @return The return code of ReturnCode_t type
     *         RTC_OK: Succeed
     *         BAD_PARAMETER: Invalid value. The value might be negative.
     *
     * @endif
     */
    RTC::ReturnCode_t setRate(double rate)
    {
      return m_profile.setRate(rate);;
    }

    /*!
     * @if jp
     * @brief ExecutionContext �μ¹Լ���(Hz)���������
     *
     * Active ���֤ˤ�RT����ݡ��ͥ�Ȥ��¹Ԥ�������(ñ��:Hz)�������
     * �롣
     *
     * @return ��������(ñ��:Hz)
     *
     * @else
     *
     * @brief Get execution rate(Hz) of ExecutionContext
     *
     * This operation shall return the rate (in hertz) at which its
     * Active participating RTCs are being invoked.
     *
     * @return Execution cycle(Unit:Hz)
     *
     * @endif
     */
    double getRate(void) const
    {
      return m_profile.getRate();
    }

    /*!
     * @if jp
     * @brief ExecutionKind ��ʸ���󲽤���
     *
     * RTC::ExecutionKind ���������Ƥ��� PERIODIC, EVENT_DRIVEN,
     * OTHER ��ʸ���󲽤��롣
     *
     * @param kind ExecutionKind
     * @return ʸ���󲽤��줿ExecutionKind
     *
     * @else
     *
     * @brief Converting ExecutionKind enum to string 
     *
     * This function converts enumeration (PERIODIC, EVENT_DRIVEN,
     * OTHER) defined in RTC::ExecutionKind to string.
     *
     * @param kind ExecutionKind
     * @return String of ExecutionKind
     *
     * @endif
     */
    const char* getKindString(RTC::ExecutionKind kind) const
    {
      return m_profile.getKindString(kind);
    }

    /*!
     * @if jp
     * @brief ExecutionKind �����ꤹ��
     *
     * ���� ExecutionContext �� ExecutionKind �����ꤹ��
     *
     * @param kind ExecutionKind
     *
     * @else
     *
     * @brief Set the ExecutionKind
     *
     * This operation sets the kind of the execution context.
     *
     * @param kind ExecutionKind
     *
     * @endif
     */
    RTC::ReturnCode_t setKind(RTC::ExecutionKind kind)
    {
      return m_profile.setKind(kind);
    }

    /*!
     * @if jp
     * @brief ExecutionKind ���������
     *
     * �� ExecutionContext �� ExecutionKind ���������
     *
     * @return ExecutionKind
     *
     * @else
     *
     * @brief Get the ExecutionKind
     *
     * This operation shall report the execution kind of the execution
     * context.
     *
     * @return ExecutionKind
     *
     * @endif
     */
    RTC::ExecutionKind getKind(void) const
    {
      return m_profile.getKind();
    }

    /*!
     * @if jp
     * @brief Owner����ݡ��ͥ�Ȥ򥻥åȤ��롣
     *
     * ����EC��Owner�Ȥʤ�RTC�򥻥åȤ��롣
     *
     * @param comp Owner�Ȥʤ�RT����ݡ��ͥ��
     * @return ReturnCode_t ���Υ꥿���󥳡���
     * @else
     * @brief Setting owner component of the execution context
     *
     * This function sets an RT-Component to be owner of the execution context.
     *
     * @param comp an owner RT-Component of this execution context
     * @return The return code of ReturnCode_t type
     * @endif
     */
    RTC::ReturnCode_t setOwner(RTC::LightweightRTObject_ptr comp)
    {
      return m_profile.setOwner(comp);
    }

    /*!
     * @if jp
     * @brief Owner����ݡ��ͥ�Ȥλ��Ȥ��������
     *
     * ����EC��Owner�Ǥ���RTC�λ��Ȥ�������롣
     *
     * @return OwnerRT����ݡ��ͥ�Ȥλ���
     * @else
     * @brief Getting a reference of the owner component
     *
     * This function returns a reference of the owner RT-Component of
     * this execution context
     *
     * @return a reference of the owner RT-Component
     * @endif
     */
    const RTC::RTObject_ptr getOwner() const
    {
      return m_profile.getOwner();
    }

    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ��ɲä���
     *
     * ���ꤷ��RT����ݡ��ͥ�Ȥ򻲲üԥꥹ�Ȥ��ɲä��롣�ɲä��줿RT��
     * ��ݡ��ͥ�Ȥ� attach_context ���ƤФ졢Inactive ���֤����ܤ��롣
     * ���ꤵ�줿RT����ݡ��ͥ�Ȥ�null�ξ��ϡ�BAD_PARAMETER ���֤���
     * �롣���ꤵ�줿RT����ݡ��ͥ�Ȥ� DataFlowComponent �ʳ��ξ��ϡ�
     * BAD_PARAMETER ���֤���롣
     *
     * @param comp �ɲ��о�RT����ݡ��ͥ��
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Add an RT-component
     *
     * The operation causes the given RTC to begin participating in
     * the execution context.  The newly added RTC will receive a call
     * to LightweightRTComponent::attach_context and then enter the
     * Inactive state.  BAD_PARAMETER will be invoked, if the given
     * RT-Component is null or if the given RT-Component is other than
     * DataFlowComponent.
     *
     * @param comp The target RT-Component for add
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    RTC::ReturnCode_t addComponent(RTC::LightweightRTObject_ptr comp)
    {
      return m_profile.addComponent(comp);
    }

    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥ򻲲üԥꥹ�Ȥ���������
     *
     * ���ꤷ��RT����ݡ��ͥ�Ȥ򻲲üԥꥹ�Ȥ��������롣������줿
     * RT����ݡ��ͥ�Ȥ� detach_context ���ƤФ�롣���ꤵ�줿RT����ݡ�
     * �ͥ�Ȥ����üԥꥹ�Ȥ���Ͽ����Ƥ��ʤ����ϡ�BAD_PARAMETER ����
     * ����롣
     *
     * @param comp ����о�RT����ݡ��ͥ��
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief Remove the RT-Component from participant list
     *
     * This operation causes a participant RTC to stop participating in the
     * execution context.
     * The removed RTC will receive a call to
     * LightweightRTComponent::detach_context.
     * BAD_PARAMETER will be returned, if the given RT-Component is not
     * participating in the participant list.
     *
     * @param comp The target RT-Component for delete
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    RTC::ReturnCode_t removeComponent(RTC::LightweightRTObject_ptr comp)
    {
      return m_profile.removeComponent(comp);
    }

    /*!
     * @if jp
     * @brief RT����ݡ��ͥ�Ȥλ��üԥꥹ�Ȥ��������
     *
     * ������Ͽ����Ƥ��뻲�ü�RTC�Υꥹ�Ȥ�������롣
     *
     * @return ���ü�RTC�Υꥹ��
     *
     * @else
     *
     * @brief Getting participant RTC list
     *
     * This function returns a list of participant RTC of the execution context.
     *
     * @return Participants RTC list
     *
     * @endif
     */
    const RTC::RTCList& getComponentList() const
    {
      return m_profile.getComponentList();
    }

    /*!
     * @if jp
     * @brief Properties�򥻥åȤ���
     *
     * ExecutionContextProfile::properties �򥻥åȤ��롣
     *
     * @param props ExecutionContextProfile::properties �˥��åȤ����
     *              ��ѥƥ���
     *
     * @else
     * @brief Setting Properties
     *
     * This function sets ExecutionContextProfile::properties by
     * coil::Properties.
     *
     * @param props Properties to be set to
     *              ExecutionContextProfile::properties.
     *
     * @endif
     */
    void setProperties(coil::Properties& props)
    {
      m_profile.setProperties(props);
    }

    /*!
     * @if jp
     * @brief Properties���������
     *
     * ExecutionContextProfile::properties ��������롣
     *
     * @return coil::Properties���Ѵ����줿
     *              ExecutionContextProfile::properties
     *
     * @else
     * @brief Setting Properties
     *
     * This function sets ExecutionContextProfile::properties by
     * coil::Properties.
     *
     * @param props Properties to be set to ExecutionContextProfile::properties.
     *
     * @endif
     */
    const coil::Properties getProperties() const
    {
      return m_profile.getProperties();
    }

    /*!
     * @if jp
     * @brief Profile���������
     *
     * RTC::ExecutionContextProfile ��������롣��������
     * ExecutionContextProfile �ν�ͭ���ϸƤӽФ�¦�ˤ��롣�������줿��
     * �֥������Ȥ����פˤʤä���硢�ƤӽФ�¦������������Ǥ���餦��
     *
     * @return RTC::ExecutionContextProfile
     *
     * @else
     * @brief Getting Profile
     *
     * This function gets RTC::ExecutionContextProfile.  The ownership
     * of the obtained ExecutionContextProfile is given to caller. The
     * caller should release obtained object when it is unneccessary
     * anymore.
     *
     * @return RTC::ExecutionContextProfile
     *
     * @endif
     */
    RTC::ExecutionContextProfile* getProfile(void)
    {
      return m_profile.getProfile();
    }

    /*!
     * @if jp
     * @brief Profile���������
     *
     * RTC::ExecutionContextProfile ��������롣
     *
     * @return RTC::ExecutionContextProfile
     *
     * @else
     * @brief Getting Profile
     *
     * This function gets RTC::ExecutionContextProfile.
     *
     * @return RTC::ExecutionContextProfile
     *
     * @endif
     */
    const RTC::ExecutionContextProfile& getProfile(void) const
    {
      return m_profile.getProfile();
    }
    // end of delegated functions to ExecutionContextProfile
    //============================================================



  protected:
    RTC_impl::ExecutionContextProfile m_profile;
  };  // class ExecutionContextBase

  typedef coil::GlobalFactory<ExecutionContextBase> ExecutionContextFactory;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  EXTERN template class DLL_PLUGIN coil::GlobalFactory<ExecutionContextBase>;
#endif
};  // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_EXECUTIONCONTEXTBASE_H
