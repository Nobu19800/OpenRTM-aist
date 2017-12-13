// -*- C++ -*-
/*!
 * @file ExtendedFsmServiceProvider.h
 * @brief Component observer SDO service consumer implementation
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2016
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */


#ifndef RTC_EXTENDEDFSMSERVICEPROVIDER_H
#define RTC_EXTENDEDFSMSERVICEPROVIDER_H

#include <coil/Mutex.h>
#include <coil/Factory.h>
#include <coil/stringutil.h>
#include <rtm/SdoServiceProviderBase.h>
#include <rtm/ComponentActionListener.h>
#include <rtm/idl/SDOPackageStub.h>
#include <rtm/idl/ExtendedFsmServiceSkel.h>

namespace RTC
{

  /*!
   * @if jp
   * @else
   * @endif
   */
  class ExtendedFsmServiceProvider
    : public virtual POA_RTC::ExtendedFsmService,
      public SdoServiceProviderBase
  {
  public:
    /*!
     * @if jp
     * @brief ctor of ExtendedFsmServiceProvider
     * @else
     * @brief ctor of ExtendedFsmServiceProvider
     * @endif
     */
    ExtendedFsmServiceProvider();

    /*!
     * @if jp
     * @brief dtor
     * @else
     * @brief dtor
     * @endif
     */
    virtual ~ExtendedFsmServiceProvider();

    /*!
     * @if jp
     * @brief �����
     * @else
     * @brief Initialization
     * @endif
     */
    virtual bool init(RTObject_impl& rtobj,
                      const SDOPackage::ServiceProfile& profile);

    /*!
     * @if jp
     * @brief �ƽ����
     * @else
     * @brief Re-initialization
     * @endif
     */
    virtual bool reinit(const SDOPackage::ServiceProfile& profile);

    /*!
     * @if jp
     * @brief ServiceProfile ���������
     * @else
     * @brief getting ServiceProfile
     * @endif
     */
    virtual const SDOPackage::ServiceProfile& getProfile() const;
    
    /*!
     * @if jp
     * @brief ��λ����
     * @else
     * @brief Finalization
     * @endif
     */
    virtual void finalize();

    //============================================================
    // CORBA operations
    //
    // string get_current_state();
    // ReturnCode_t set_fsm_structure(in FsmStructure fsm_structure);
    // ReturnCode_t get_fsm_structure(out FsmStructure fsm_structure);
    //============================================================

    /*!
     * @if jp
     * @brief FSM�θ��ߤξ��֤����
     *
     * ���Υ��ڥ졼������FSM����ݡ��ͥ�Ȥ�FSM�θ��ߤξ��֤��֤���
     * (FSM4RTC spec. p.20)
     *
     * @return ���ߤξ��֤�ɽ��ʸ����
     *
     * @else
     * @brief Get Current FSM State
     *
     * This operation returns the current state of an FSM in the
     * target FSM component. (FSM4RTC spec. p.20)
     *
     * @return A string which represent the current status
     *
     * @endif
     */
    virtual char* get_current_state();
    /*!
     * @if jp
     * @brief FSM�ι�¤�����ꤹ��
     *
     * ���Υ��ڥ졼�������оݤΥ���ݡ��ͥ�Ȥ��Ф��ơ�FSM�ι�¤����
     * ������ FsmStruccture �����ꤹ�롣�оݥ���ݡ��ͥ�Ȥ�
     * fsm_structure ��Ϳ����줿�ͤ��˾������ܥ롼������FSM��¤���
     * ���ꤹ�롣���Υ��ڥ졼�����̤�����ξ��ϡ�UNSUPPORTED ���֤���
     *
     * @param fsm_structure FSM�ι�¤��ɽ��FsmStructure��¤�Ρ�
     * @return RTC_OK ���ｪλ
     *         RTC_ERROR ����¾�Υ��顼
     *         BAD_PARAMETER �����ʥѥ�᡼��
     *         UNSUPPORTED ̤���ݡ���
     *
     * @else
     * @brief Set FSM Structure
     *
     * This operation sets an FsmStructure to the target
     * component. Then the target component reconfigures its FSM
     * structure such as transition rules according to the values of
     * the given fsm_structure. RTCs may return UNSUPPORTED if this
     * operation is not implemented.
     *
     * @param fsm_structure FsmStructure structure which represents
     *        FSM structure
     * @return RTC_OK normal return
     *         RTC_ERROR other error
     *         BAD_PARAMETER invalid parameter
     *         UNSUPPORTED unsupported or not implemented
     *
     * @endif
     */
    virtual ReturnCode_t
    set_fsm_structure(const ::RTC::FsmStructure& fsm_structure);
    /*!
     * @if jp
     * @brief FSM�ι�¤���������
     *
     * ���Υ��ڥ졼�������оݤΥ���ݡ��ͥ�Ȥ��Ф��ơ������ݻ����Ƥ�
     * ��FSM�ι�¤��������롣ExtendedFsmService ��¤�Τϥե������
     * name (FSM��̾��), structure (FSM�ι�¤) ��EventProfile �ʤɤ���
     * ����structure �Υե����ޥåȤϡ��ե������ properties ��˳�Ǽ��
     * �줿���� "fsm_structure.format" �˻��ꤵ��롣���Υ��ڥ졼�����
     * ��̤�����ξ��ϡ�UNSUPPORTED ���֤���
     *
     * ref: SCXML https://www.w3.org/TR/scxml/
     *
     * @param fsm_structure FSM�ι�¤��ɽ��FsmStructure��¤�Ρ�
     * @return RTC_OK ���ｪλ
     *         RTC_ERROR ����¾�Υ��顼
     *         BAD_PARAMETER �����ʥѥ�᡼��
     *         UNSUPPORTED ̤���ݡ���
     *
     * @else
     * @brief Set FSM Structure
     *
     * This operation returns the structure of an FSM in the target
     * FSM component. ExtendedFsmService returns the name, structure
     * with format specified by fsm_structure.format and
     * EventProfiles. RTCs may return UNSUPPORTED if this operation is
     * not implemented.
     *
     * @param fsm_structure FsmStructure structure which represents
     *        FSM structure
     * @return RTC_OK normal return
     *         RTC_ERROR other error
     *         BAD_PARAMETER invalid parameter
     *         UNSUPPORTED unsupported or not implemented
     *
     * @endif
     */
    virtual ReturnCode_t
    get_fsm_structure(::RTC::FsmStructure_out fsm_structure);

    

  protected:
    /*!
     * @if jp
     * @brief RTObject�ؤΥꥹ����³����
     * @else
     * @brief Connectiong listeners to RTObject
     * @endif
     */
    void setListeners(coil::Properties& prop);

    /*!
     * @if jp
     * @brief FSM��������
     * @else
     * @brief FSM status change
     * @endif
     */
    void changeStatus(std::string state);

    /*!
     * @if jp
     * @brief �ϡ��ȥӡ��Ȥ�������
     * @else
     * @brief Unsetting heartbeat
     * @endif
     */
    void changeStructure(std::string fsm_structure);

    //============================================================
    // FSM status related functions
    /*!
     * @if jp
     * @brief FSM�����Ѳ��ꥹ�ʤ��������
     * @else
     * @brief Setting FSM status listeners
     * @endif
     */
    void setFSMStatusListeners();

    /*!
     * @if jp
     * @brief FSM�����Ѳ��ꥹ�ʤβ������
     * @else
     * @brief Unsetting FSM status listeners
     * @endif
     */
    void unsetFSMStatusListeners();

    //============================================================
    // FsmProfile related functions
    /*!
     * @if jp
     * @brief FsmProfile�����Ѳ��ꥹ�ʤ�����
     * @else
     * @brief Setting FsmProfile listener
     * @endif
     */
    void setFSMProfileListeners();

    /*!
     * @if jp
     * @brief FsmProfile�����Ѳ��ꥹ�ʤβ��
     * @else
     * @brief Unsetting FsmProfile listener
     * @endif
     */
    void unsetFSMProfileListeners();

    //============================================================
    // FsmStructure related functions
    /*!
     * @if jp
     * @brief FsmStructure�����Ѳ��ꥹ�ʤ�����
     * @else
     * @brief Setting FsmStructure listener
     * @endif
     */
    void setFSMStructureListeners();

    /*!
     * @if jp
     * @brief FsmStructure�����Ѳ��ꥹ�ʤβ��
     * @else
     * @brief Unsetting FsmStructure listener
     * @endif
     */
    void unsetFSMStructureListeners();

  private:
    RTC::RTObject_impl* m_rtobj;
    SDOPackage::ServiceProfile m_profile;
    coil::Properties m_properties;
    FsmStructure m_fsmStructure;
    std::string m_fsmState;

  };

}; // namespace RTC

extern "C"
{
  DLL_EXPORT void ExtendedFsmServiceProviderInit();
};

#endif // RTC_EXTENDEDFSMSERVICEPROVIDER_H


