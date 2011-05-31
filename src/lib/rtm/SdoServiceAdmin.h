// -*- C++ -*-
/*!
 * @file SdoServiceAdmin.h
 * @brief SDO service administration class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#ifndef RTC_SDOSERVICEADMIN_H
#define RTC_SDOSERVICEADMIN_H

#include <coil/Mutex.h>
#include <coil/Factory.h>

#include <rtm/idl/SDOPackageStub.h>
#include <rtm/SystemLogger.h>

namespace RTC
{
  class RTObject_impl;
  class SdoServiceConsumerBase;

  /*!
   * @if jp
   *
   * @class SDO service administration class
   * @brief SDO service �������饹
   *
   * ���Υ��饹�ϡ�SDO Service ��������뤿��Υ��饹�Ǥ��롣SDO
   * Service �� OMG SDO Specification �ˤ������������Ƥ��롢SDO������
   * �ε�ǽ�Τ�����󶡤ޤ��׵᤹�륵���ӥ��ΰ�ĤǤ��롣�ܺ٤ϻ��ͤˤ�
   * �����������Ƥ��ʤ������ܥ��饹�Ǥϰʲ��Τ褦�˿����񤦥����ӥ���
   * �����ΤȤ���������������뤿��Υ��饹���ܥ��饹�Ǥ��롣
   *
   * SDO Service �ˤ����Ƥϡ�SDO/RTC�˽�ͭ���졢�����Υ����ӥ�����
   * �����Τ� SDO Service Provider��¾��SDO/RTC�䥢�ץꥱ���������
   * �����륵���ӥ����֥������Ȥλ��Ȥ������ꡢ�����ε�ǽ�����Ѥ���
   * ��Τ�SDO Service Consumer �ȸƤ֡�
   *
   * SDO Service Provider ��¾�Υ��ץꥱ������󤫤�ƤФ졢SDO/RTC����
   * �ε�ǽ�˥����������뤿����Ѥ����롣¾��SDO/RTC�ޤ��ϥ��ץꥱ��
   * �����ϡ�
   *
   * - SDO::get_service_profiles ()
   * - SDO::get_service_profile (in UniqueIdentifier id)
   * - SDO::get_sdo_service (in UniqueIdentifier id) 
   *
   * �Τ����줫�Υ��ڥ졼�����ˤ�ꡢServiceProfile �ޤ��� SDO
   * Service �λ��Ȥ����������ǽ�����Ѥ��뤿��Υ��ڥ졼������Ƥӽ�
   * ����¾��SDO/RTC�ޤ��ϥ��ץꥱ��������Ǥλ��Ȥ��˴���Ǥ�դΥ���
   * �ߥ󥰤ǹԤ�졢�����ӥ���¦�Ǥϡ��ɤ�����ɤ�������Ȥ���Ƥ���
   * �����Τ뤳�ȤϤǤ��ʤ��������ǡ�SDO/RTC¦�⡢Ǥ�դΥ����ߥ󥰤ǥ���
   * �ӥ����󶡤���ߤ��뤳�Ȥ�Ǥ��뤿�ᡢ�����ӥ�������¦�Ǥϡ���ˤ�
   * �����ӥ������ѤǤ���Ȥϸ¤�ʤ���ΤȤ��ƥ����ӥ����ڥ졼������
   * �ƤӽФ�ɬ�פ����롣
   *
   * ������SDO Service Consumer ������SDO/RTC�ʳ���SDO/RTC�ޤ��ϥ��ץ�
   * ��������󤬥����ӥ��μ��Τ����������SDO/RTC�˥��֥������Ȼ��Ȥ�
   * �ޤ�ץ�ե������Ϳ���뤳�Ȥǡ�SDO/RTC¦���饵���ӥ����ڥ졼����
   * �󤬸ƤФ쳰����SDO/RTC�ޤ��ϥ��ץꥱ��������󶡤��뵡ǽ������
   * �Ǥ��롣�ޤ������֥�����Ū�ʥ��֥������Ȥ�Ϳ���뤳�Ȥǡ�SDO/RTC¦
   * ����Υ�����Хå���¸����뤿��ˤ����Ѥ��뤳�Ȥ��Ǥ��롣���󥷥塼
   * �ޤϡ��ץ�Х����ȤϰۤʤꡢSDO Configuration���󥿡��ե���������
   * �ɲá�������Ԥ��롣��Ϣ���륪�ڥ졼�����ϰʲ��ΤȤ���Ǥ��롣
   *
   * - Configuration::add_service_profile (in ServiceProfile sProfile)
   * - Configuration::remove_service_profile (in UniqueIdentifier id)
   *
   * ������SDO/RTC�ޤ��ϥ��ץꥱ�������ϡ����Ȥ�����SDO Servcie
   * Provider �λ��Ȥ�ID�����interface type���ץ�ѥƥ��ȤȤ��
   * ServcieProfile �˥��åȤ��������ǡ�add_service_profile() �ΰ�����
   * ����Ϳ���뤳�Ȥǡ�����SDO/RTC�˥����ӥ���Ϳ���롣���κݡ�ID��UUID
   * �ʤɰ�դ�ID�Ǥʤ���Фʤ�ʤ����ޤ����������ݤˤ�ID�ˤ���оݤ�
   * ����ServiceProfile��õ�����뤿�ᡢ�����ӥ���¦�ǤϺ�����ޤ�ID��
   * �ݻ����Ƥ����ʤ���Фʤ�ʤ���
   *
   * 
   *
   *
   *
   * @since 1.1.0
   *
   * @else
   *
   * @class SDO service administration class
   * @brief SDO service administration class
   *
   *
   * @since 1.1.0
   *
   * @endif
   */
  class SdoServiceAdmin
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param 
     * 
     * @else
     *
     * @brief Constructor
     * 
     * Constructor
     *
     * @param 
     *
     * @endif
     */
    SdoServiceAdmin(::RTC::RTObject_impl& rtobj);

    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     * 
     * @else
     *
     * @brief Virtual destractor
     *
     * Virtual destractor.
     *
     * @endif
     */
    virtual ~SdoServiceAdmin();
    
    /*!
     * @if jp
     *
     * @brief Service Consumer Factory ����Ͽ����
     * 
     * @else
     *
     * @brief Add Service Consumer Factory
     *
     * @endif
     */
    bool addSdoServiceConsumerFactory();

    /*!
     * @if jp
     *
     * @brief Service Consumer Factory ��������
     * 
     * @else
     *
     * @brief Remove Service Consumer Factory
     *
     * @endif
     */
    bool removeSdoServiceConsumerFactory();
    
    /*!
     * @if jp
     *
     * @brief Service Consumer ���ɲä���
     * 
     * @else
     *
     * @brief Add Service Consumer
     *
     * @endif
     */
    bool addSdoServiceConsumer(const SDOPackage::ServiceProfile& sProfile);
    
    /*!
     * @if jp
     *
     * @brief Service Consumer ��������
     * 
     * @else
     *
     * @brief Remove Service Consumer
     *
     * @endif
     */
    bool removeSdoServiceConsumer(const char* id);
    
protected:
    /*!
     * @if jp
     *
     * @brief ���Ĥ��줿�����ӥ������ɤ���Ĵ�٤�
     * 
     * @else
     *
     * @brief If it is allowed service type
     *
     * @endif
     */
    bool isAllowedConsumerType(const SDOPackage::ServiceProfile& sProfile);

    /*!
     * @if jp
     *
     * @brief ¸�ߤ��륵���ӥ������ɤ���Ĵ�٤�
     * 
     * @else
     *
     * @brief If it is existing service type
     *
     * @endif
     */
    bool isExistingConsumerType(const SDOPackage::ServiceProfile& sProfile);

    const std::string getUUID() const;
    

  private:
    RTC::RTObject_impl& m_rtobj;
    coil::vstring m_consumerTypes;
    bool m_allConsumerAllowed;
    
    /*!
     * @if jp
     * @brief Lock �դ� SDO ServiceProfileList
     * @else
     * @brief SDO ServiceProfileList with mutex lock
     * @endif
     */
    SDOPackage::ServiceProfileList m_providerProfiles;
    coil::Mutex m_provider_mutex;
    
    /*!
     * @if jp
     * @brief Lock �դ� SDO ServiceProfileList
     * @else
     * @brief SDO ServiceProfileList with mutex lock
     * @endif
     */
    std::vector<SdoServiceConsumerBase*> m_consumers;
    coil::Mutex m_consumer_mutex;

    /*!
     * @if jp
     * @brief logger
     * @else
     * @brief logger
     * @endif
     */
    ::RTC::Logger rtclog;
  };


};

#endif // RTC_SDOSERVICEADMIN_H
