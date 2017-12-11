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
     * @brief ������
     * @else
     * @brief Initialization
     * @endif
     */
    virtual bool init(RTObject_impl& rtobj,
                      const SDOPackage::ServiceProfile& profile);

    /*!
     * @if jp
     * @brief �ď�����
     * @else
     * @brief Re-initialization
     * @endif
     */
    virtual bool reinit(const SDOPackage::ServiceProfile& profile);

    /*!
     * @if jp
     * @brief ServiceProfile ���擾����
     * @else
     * @brief getting ServiceProfile
     * @endif
     */
    virtual const SDOPackage::ServiceProfile& getProfile() const;
    
    /*!
     * @if jp
     * @brief �I������
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
     * @brief FSM�̌��݂̏�Ԃ��擾
     *
     * ���̃I�y���[�V������FSM�R���|�[�l���g��FSM�̌��݂̏�Ԃ�Ԃ��B
     * (FSM4RTC spec. p.20)
     *
     * @return ���݂̏�Ԃ�\��������
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
     * @brief FSM�̍\����ݒ肷��
     *
     * ���̃I�y���[�V�����͑Ώۂ̃R���|�[�l���g�ɑ΂��āAFSM�̍\�����
     * ������ FsmStruccture ��ݒ肷��B�ΏۃR���|�[�l���g��
     * fsm_structure �ɗ^����ꂽ�l����ɏ�ԑJ�ڃ��[������FSM�\������
     * �ݒ肷��B���̃I�y���[�V�������������̏ꍇ�́AUNSUPPORTED ��Ԃ��B
     *
     * @param fsm_structure FSM�̍\����\��FsmStructure�\���́B
     * @return RTC_OK ����I��
     *         RTC_ERROR ���̑��̃G���[
     *         BAD_PARAMETER �s���ȃp�����[�^
     *         UNSUPPORTED ���T�|�[�g
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
     * @brief FSM�̍\�����擾����
     *
     * ���̃I�y���[�V�����͑Ώۂ̃R���|�[�l���g�ɑ΂��āA���ݕێ����Ă�
     * ��FSM�̍\�����擾����BExtendedFsmService �\���̂̓t�B�[���h
     * name (FSM�̖���), structure (FSM�̍\��) �AEventProfile �Ȃǂ��
     * ���Bstructure �̃t�H�[�}�b�g�́A�t�B�[���h properties ���Ɋi�[��
     * �ꂽ�L�[ "fsm_structure.format" �Ɏw�肳���B���̃I�y���[�V����
     * ���������̏ꍇ�́AUNSUPPORTED ��Ԃ��B
     *
     * ref: SCXML https://www.w3.org/TR/scxml/
     *
     * @param fsm_structure FSM�̍\����\��FsmStructure�\���́B
     * @return RTC_OK ����I��
     *         RTC_ERROR ���̑��̃G���[
     *         BAD_PARAMETER �s���ȃp�����[�^
     *         UNSUPPORTED ���T�|�[�g
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
     * @brief RTObject�ւ̃��X�i�ڑ�����
     * @else
     * @brief Connectiong listeners to RTObject
     * @endif
     */
    void setListeners(coil::Properties& prop);

    /*!
     * @if jp
     * @brief FSM��ԑJ��
     * @else
     * @brief FSM status change
     * @endif
     */
    void changeStatus(std::string state);

    /*!
     * @if jp
     * @brief �n�[�g�r�[�g����������
     * @else
     * @brief Unsetting heartbeat
     * @endif
     */
    void changeStructure(std::string fsm_structure);

    //============================================================
    // FSM status related functions
    /*!
     * @if jp
     * @brief FSM��ԕω����X�i�̐ݒ菈��
     * @else
     * @brief Setting FSM status listeners
     * @endif
     */
    void setFSMStatusListeners();

    /*!
     * @if jp
     * @brief FSM��ԕω����X�i�̉�������
     * @else
     * @brief Unsetting FSM status listeners
     * @endif
     */
    void unsetFSMStatusListeners();

    //============================================================
    // FsmProfile related functions
    /*!
     * @if jp
     * @brief FsmProfile��ԕω����X�i�̐ݒ�
     * @else
     * @brief Setting FsmProfile listener
     * @endif
     */
    void setFSMProfileListeners();

    /*!
     * @if jp
     * @brief FsmProfile��ԕω����X�i�̉���
     * @else
     * @brief Unsetting FsmProfile listener
     * @endif
     */
    void unsetFSMProfileListeners();

    //============================================================
    // FsmStructure related functions
    /*!
     * @if jp
     * @brief FsmStructure��ԕω����X�i�̐ݒ�
     * @else
     * @brief Setting FsmStructure listener
     * @endif
     */
    void setFSMStructureListeners();

    /*!
     * @if jp
     * @brief FsmStructure��ԕω����X�i�̉���
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


