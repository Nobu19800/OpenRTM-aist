// -*- C++ -*-
/*!
 * @file SdoServiceProviderBase.h
 * @brief SDO service provider base class and its factory
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
 * $Id$
 *
 */


#ifndef RTC_SDOSERVICEPROVIDERBASE_H
#define RTC_SDOSERVICEPROVIDERBASE_H

#include <coil/Mutex.h>
#include <coil/Factory.h>
#include <coil/Timer.h>
#include <rtm/RTC.h>
#include <rtm/RTObject.h>
#include <rtm/idl/SDOPackageStub.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @brief SdoServiceProvider�����쥯�饹
   *
   * SDO���������Ƥ���SDO�����ӥ��Υץ�Х�����������뤿��δ��쥯��
   * ����SDO�����ӥ��ˤϡ����������󶡥����ӥ���RTC(SDO)¦�����Ѥ���
   * SDO�����ӥ����󥷥塼�ޤȡ�RTC(SDO)���Ȥ�SDO�����ӥ����󶡤���SDO
   * �����ӥ��ץ�Х��������롣���٤Ƥ�SDO�����ӥ��ץ�Х����Ϥ��δ���
   * ���饹��Ѿ����Ƽ�������롣
   *
   * ���Υ��֥������ȤΥ饤�ե�������ϰʲ����̤ꡣ
   *
   * -# ���֥������Ȥ��̾��ͭ���֥������� (so, DLL) �Ȥ��ƥ���ѥ��롦
   *    ��󥯤���롣
   * -# �ޥ͡�������Ф��ƥ��ɤ����ȥ⥸�塼�������ؿ��ˤ�ꥪ��
   *    �������ȥե����ȥ꤬��SdoServiceProviderFactory ���Ф�����Ͽ��
   *    ��롣��Ͽ�Υ����ˤϥ����ӥ����󥿡��ե������� IFR (interface
   *    repository) ID �����Ѥ��졢����ˤ�ꥵ���ӥ������̤���롣
   * -# rtc.conf���Υ���ե�����졼��������ˤ�ꡢͭ�������뤳�Ȥ�
   *    ���ꤵ��Ƥ��륵���ӥ�����ץ�Х����ϡ�RTC�ε�ư��Ʊ���˥���
   *    ���󥹲�����롣
   * -# ���󥹥��󥹲��塢������ؿ� init() ���ƤФ�롣�����ˤ���������
   *    �ӥ��Τ���Υ���ե�����졼����󥪥ץ���� coil::Property��
   *    ����Ϥ���롣
   * -# ���󥹥��󥹲����줿SDO�����ӥ��ץ�Х�����
   *    SDO::get_sdo_service() �ˤ�곰�����饢����������롣���Τ�
   *    ���������ӥ�����ꤹ��ID��IFR ID��Ʊ���Ǥ��롣���ΤȤ��Υ�����
   *    ���������󥹤ϰʲ����̤ꡣ
   * -# RTC��finalize������Τ�����Ʊ����SDO�����ӥ��ץ�Х��������
   *    ����뤬�����κݤˤ�SdoServiceProviderBase::finalize()��������
   *    �����Τǡ������ǥ꥽�����β����ʤɽ�λ������Ԥ���
   *
   * <pre>
   * 
   *   [RTC]      [SDO service]               [Other]
   *     |              :                        |
   *     | instantiate  :                        |
   *     |------------->:                        |
   *     |    init()    |                        |
   *     |------------->|                        |
   *     |              | get_service_profiles() |
   *     |<--------------------------------------|
   *     |              |    get_sdo_service()   |
   *     |<--------------------------------------|
   *     |              |        use service     |
   *     |              |<-----------------------|
   *     |              |                        |
   *     |  finalize()  |                        |
   *     |------------->x                        |
   *     x              x                        |
   *
   * </pre>
   *
   * ���Υ��饹�μ����������äƤϡ����ʤ��Ȥ�ʲ��ν�貾�۴ؿ��������
   * ��ɬ�פ����롣
   *
   * - init(): ������ؿ���Ϳ����줿 RTObject ����� ServiceProfile ��
   *   �顢�������֥������Ȥ��������롣
   * - reinit(): �ƽ�����ؿ���ServiceProfile ��������󹹿��Τ���Ʊ��
   *   ID�ǸƤӽФ���뤳�Ȥ�ͭ�뤬�����κݤˤ��δؿ���������
   *   ServiceProfile �ȤȤ�˸ƤӽФ���롣�ؿ���Ǥϡ�������ѹ��ʤ�
   *   �ƽ����������������롣
   * - getProfile(): ���ꤵ�줿�ץ�ե�������֤��ؿ���
   * - finalize(): ��λ���������󥷥塼�ޤ��ǥ��å������ݤ˸ƤӽФ���
   *   ��ؿ����ؿ���ǤϽ�λ������������롣
   *
   * SdoServiceProvider ���̾ﶦͭ���֥������ȤȤ��ƥ���ѥ��롦���
   * ����롣��ͭ���֥������ȤΥ���ȥ�ݥ���Ȥ��̾拾��ѥ��뤵�줿�ե�
   * ����̾�� basename + "Init" �ˤ��Ƥ������ʲ��ˡ����饹̾���ե�����
   * ̾������ȥ�ݥ���ȴؿ�̾�ο侩��򼨤���
   *
   * - �������饹̾: MySdoServiceProvider 
   * - �ե�����̾: MySdoServiceProvider.h. MySdoServiceProvider.cpp
   * - ��ͭ���֥�������̾: MySdoServiceProvider.so (or DLL)
   * - ����ȥ�ݥ���ȴؿ�̾: MySdoServiceProviderInit()
   *
   * ����ȥ�ݥ���ȴؿ����̾�ʲ��Τ褦�ˡ�SdoServiceProviderFactory
   * ���������󥷥塼�ޤΥե����ȥ� (�Ȳ��Υե��󥯥�) ����Ͽ����ʲ���
   * �褦�ʴؿ��ˤʤ롣
   *
   * <pre>
   * extern "C"
   * {
   *   void MySdoServiceProviderInit()
   *   {
   *     RTC::SdoServiceProviderFactory& factory
   *       = RTC::SdoServiceProviderFactory::instance();
   *     factory.addFactory(CORBA_Util::toRepositoryId<OpenRTM::MySdoService>(),
   *                        ::coil::Creator< ::RTC::SdoServiceProviderBase,
   *                        ::RTC::MySdoServiceProvider>,
   *                        ::coil::Destructor< ::RTC::SdoServiceProviderBase,
   *                        ::RTC::MySdoServiceProvider>);
   *   }
   * };
   * </pre>
   * 
   * @else
   *
   * @endif
   *
   */
  class SdoServiceProviderBase
    : public virtual POA_SDOPackage::SDOService,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief ���ۥǥ��ȥ饯��
     * @else
     * @brief virtual destructor
     * @endif
     */
    virtual ~SdoServiceProviderBase() {};

    /*!
     * @if jp
     * @brief ���󥷥塼�ޥ��饹�ν�����ؿ�
     *
     * ������ؿ���Ϳ����줿 RTObject ����� ServiceProfile ���顢����
     * ���֥������Ȥ��������ޤ������Υ����ӥ���
     * ''sdo.service.provider.enabled_services'' ��ͭ��������Ƥ���С�
     * ���δؿ����б�����RTC�����󥹥��󥹲����줿ľ��˸ƤӽФ���ޤ���
     *
     * ServiceProfile �ˤϰʲ��ξ������ä����֤ǸƤӽФ���ޤ���
     *
     * - ServiceProfile.id: ���������ӥ���IFR��
     * - ServiceProfile.interface_type: ���������ӥ���IFR��
     * - ServiceProfile.service: ���������ӥ��Υ��֥������Ȼ���
     * - ServiceProfile.properties: rtc.conf �� <component>.conf ����Ϳ
     *                   ����줿SDO�����ӥ���ͭ�Υ��ץ�����Ϥ���롣
     *                   conf�ե��������
     *                   �ϡ�''<pragma>.<module_name>.<interface_name>''
     *                   �Ȥ����ץ�ե��å�����Ĥ������ץ����Ȥ���Ϳ
     *                   ���뤳�Ȥ��Ǥ���properties ��ˤϡ����Υץ�
     *                   �ե��å�������������ץ����key:value������
     *                   �ޤޤ�Ƥ��롣
     *
     * �ؿ���Ǥϡ���� properties �����������Ƥ��ɤ߹��ߥ����ӥ���ͭ��
     * ��������Ԥ��ޤ���Ϳ����줿 ServiceProfile�����Ƥ����������뤤
     * �Ϥ���¾����ͳ�����������ӥ��򥤥󥹥��󥹲����ʤ����� false
     * ���֤��ޤ������ξ�硢finalize() ���ƤӽФ��줽�θ奪�֥�������
     * �Ϻ������ޤ�������ʳ��ξ��� true ���֤��ȡ������ӥ����֥���
     * ���Ȥ� RTC ����ݻ�����ޤ���
     *
     * @param rtobj ���Υ��֥������Ȥ����󥹥��󥹲����줿 RTC
     * @param profile ��������Ϳ����줿 SDO ServiceProfile
     * @return Ϳ����줿 SDO Service �� ServiceProfile �������ξ�� false
     *
     * @else
     * @brief Initialization function of the consumer class
     *
     * @endif
     */
    virtual bool init(RTObject_impl& rtobj,
                      const SDOPackage::ServiceProfile& profile) = 0;
    /*!
     * @if jp
     * @brief ���󥷥塼�ޥ��饹�κƽ�����ؿ�
     *
     * ���Υ��֥������Ȥκƽ������Ԥ���ServiceProfile �ˤ� id �ե���
     * ��ɤ˥��å�����ͭ�� UUID �����åȤ���Ƥ��뤬��Ʊ��� id �ξ�
     * �硢properties �����ꤵ�줿���������ѹ��䡢service �ե������
     * �Υ����ӥ��λ��Ȥ��ѹ����Ԥ��롣���κݤ˸ƤФ��Τ�����
     * reinit() �ؿ��Ǥ��롣�����Ǥϡ�service �ե�����ɤΥ��֥�������
     * ��ե���󥹤�Ʊ�������ǧ�����ۤʤäƤ������ݻ����Ƥ����ե�
     * ��󥹤򹹿�����ɬ�פ����롣�ޤ� properties �ˤϿ��������꤬Ϳ��
     * ���Ƥ����ǽ��������Τǡ����Ƥ��ɤ߹�������򹹿����롣
     *
     * @param profile ������Ϳ����줿 SDO ServiceProfile
     * @return ������ ServiceProfile ��Ϳ����줿���� false
     *
     * @else
     * @brief Reinitialization function of the consumer class
     *
     * @endif
     */
    virtual bool reinit(const SDOPackage::ServiceProfile& profile) = 0;

    /*!
     * @if jp
     * @brief ServiceProfile ���֤�
     *
     * init()/reinit()��Ϳ����줿 ServiceProfile ���̾索�֥���������
     * ���ݻ�����롣SDO Service �����ե졼�����ϴ����夳�Υ��֥���
     * ���Ȥ��б����� ServiceProfile ��ɬ�פȤ���Τǡ����δؿ��Ǥ��ݻ�
     * ����Ƥ��� ServiceProfile ���֤���
     * 
     * @return ���Υ��֥������Ȥ��ݻ����Ƥ��� ServiceProfile
     *
     * @else
     * @brief Getting ServiceProfile
     * @endif
     */
    virtual const SDOPackage::ServiceProfile& getProfile() const = 0;

    /*!
     * @if jp
     * @brief ��λ����
     *
     * SDO�����ӥ����ǥ��å������ݤ˸ƤӽФ���뽪λ�����Ѵؿ�������
     * �ӥ��Τǥ��å��˺ݤ��ơ��������֥������Ȥ��ݻ�����꥽���������
     * ����ʤɤν�����Ԥ���
     *
     * @else
     * @brief Finalization
     *
     * @endif
     */
    virtual void finalize() = 0;
  };

    /*!
     * @if jp
     * @brief SdoServiceProviderFactory �� typedef
     * @else
     * @brief typedef of sdoServiceProviderFactory
     * @endif
     */
  typedef ::coil::GlobalFactory<
    ::RTC::SdoServiceProviderBase > SdoServiceProviderFactory;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    /*!
     * @if jp
     * @brief ���饹�ƥ�ץ졼�Ȥ�����Ū���󥹥��󥹲�
     * @else
     * @brief Explicit instantiation of class template
     * @endif
     */
  EXTERN template class DLL_PLUGIN 
                     ::coil::GlobalFactory< ::RTC::SdoServiceProviderBase >;
#endif  
}; // namespace RTC

#endif // RTC_SDOSERVICEPROVIDERBASE_H
