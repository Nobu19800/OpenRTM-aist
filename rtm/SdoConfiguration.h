// -*- C++ -*-
/*!
 * @file SdoConfiguration.h
 * @brief RT component base class
 * @date $Date: 2007-04-23 04:58:21 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.h,v 1.7 2007-04-23 04:58:21 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6  2007/01/24 16:03:58  n-ando
 * The ctor. was changed.
 *
 * Revision 1.5  2007/01/21 13:05:13  n-ando
 * A trivial fix.
 *
 * Revision 1.4  2006/11/08 20:00:21  n-ando
 * ConfigurationSet related interfaces are fixed.
 *
 * Revision 1.3  2006/10/30 08:05:45  n-ando
 * CORBA sequence operations were replaced by CORBA_SeqUtil functions.
 *
 * Revision 1.2  2006/10/17 10:13:15  n-ando
 * Small fixes.
 *
 * Revision 1.1  2006/09/11 18:14:01  n-ando
 * The first commit.
 *
 *
 */

#ifndef SdoConfiguration_h
#define SdoConfiguration_h

#include <ace/Guard_T.h>
#include <ace/Thread_Mutex.h>

// CORBA header include
#include <rtm/RTC.h>

// local includes
#include <rtm/idl/SDOPackageSkel.h>
#include <rtm/ConfigAdmin.h>
#include <string>

// SdoConfiguration with SeqEx 159120
// SdoConfiguration with SeqUtil 114504 114224

namespace SDOPackage
{
  /*!
   * @if jp
   *
   * @class Configuration_impl
   * @brief SDO Configuration �������饹
   *
   * Configuration interface �� Resource Data Model ��������줿�ǡ�����
   * �ɲá������������Ԥ�����Υ��󥿡��ե������Ǥ��롣
   * DeviceProfile, ServiceProfile, ConfigurationProfile ����� Organization
   * ���ѹ���Ԥ�����Υ��ڥ졼�����������Ƥ��롣SDO �λ��ͤǤϥ�����������
   * ����ӥ������ƥ��˴ؤ���ܺ٤ˤĤ��Ƥϵ��ꤷ�Ƥ��ʤ���
   * 
   * ʣ�������� (Configuration) ���ݻ����뤳�Ȥˤ�ꡢ�ưפ������᤯��������
   * ��ȿ�Ǥ����뤳�Ȥ��Ǥ��롣������������줿ʣ��������� ConfigurationSets
   * ����� configuration profile �Ȥ����ݻ����뤳�Ȥ��Ǥ��롣�ҤȤĤ�
   * ConfigurationSet �����������˴�Ϣ�դ���줿���ץ�ѥƥ��ͤΥꥹ�Ȥ�
   * ��ˡ���ID���ܺ٤ȤȤ�˻��äƤ��롣����ˤ�ꡢ��������ܤξܺ٤򵭽Ҥ�
   * ���̤��뤳�Ȥ��Ǥ��롣Configuration interface �Υ��ڥ졼�����Ϥ����
   * ConfiguratioinSets �δ�����ٱ礹�롣
   *
   *
   * - ConfigurationSet: id, description, NVList ���鹽�������1���åȤ�����
   * - ConfigurationSetList: ConfigurationSet �Υꥹ��
   * - Parameter: name, type, allowed_values ���鹽�������ѥ�᡼�������
   * - ActiveConfigurationSet: ����ͭ���ʥ���ե�����졼������1���åȡ�
   *
   * �ʲ���SDO���ͤ���������Ƥ��ʤ��⤷���ϲ�᤬�狼��ʤ������ȼ����
   *
   * �ʲ��δؿ��� ParameterList ���Ф��ƽ�����Ԥ���
   * - get_configuration_parameters()
   *
   * �ʲ��δؿ��ϥ����ƥ��֤�ConfigurationSet���Ф��������Ԥ�
   * - get_configuration_parameter_values()
   * - get_configuration_parameter_value()
   * - set_configuration_parameter()
   *
   * �ʲ��δؿ���ConfigurationSetList���Ф��ƽ�����Ԥ�
   * - get_configuration_sets()
   * - get_configuration_set()
   * - set_configuration_set_values()
   * - get_active_configuration_set()
   * - add_configuration_set()
   * - remove_configuration_set()
   * - activate_configuration_set()
   *
   * @else
   *
   * @class Configuration_impl
   * @brief Configuration implementation class
   *
   * Configuration interface provides operations to add or remove data
   * specified in resource data model. These operations provide functions to
   * change DeviceProfile, ServiceProfile, ConfigurationProfile, and
   * Organization. This specification does not address access control or
   * security aspects. Access to operations that modifies or removes profiles
   * should be controlled depending upon the application.
   *
   * Different configurations can be stored for simple and quick activation.
   * Different predefined configurations are stored as different
   * ConfigurationSets or configuration profile. A ConfigurationSet stores the
   * value of all properties assigned for the particular configuration along
   * with its unique id and description to identify and describe the
   * configuration respectively. Operations in the configuration interface
   * help manage these ConfigurationSets.
   *
   * @endif
   */
  class Configuration_impl
    : public virtual POA_SDOPackage::Configuration,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    Configuration_impl(RTC::ConfigAdmin& configAdmin);
    virtual ~Configuration_impl();

    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO �� DeviceProfile �򥻥åȤ���
     *
     * ���Υ��ڥ졼������ SDO �� DeviceProfile �򥻥åȤ��롣SDO ��
     * DeviceProfile ���ݻ����Ƥ�����Ͽ����� DeviceProfile ����������
     * DeviceProfile �򤹤Ǥ��ݻ����Ƥ�����ϴ�¸�Τ�Τ��֤������롣
     *
     * @param dProfile SDO �˴�Ϣ�դ����� DeviceProfile��
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InvalidParameter ���� "dProfile" �� null �Ǥ��롣
     * @exception InternalError ����Ū���顼��ȯ��������
     * 
     * @else
     *
     * @brief [CORBA interface] Set DeviceProfile of SDO
     *
     * This operation sets the DeviceProfile of an SDO. If the SDO does not
     * have DeviceProfile, the operation will create a new DeviceProfile,
     * otherwise it will replace the existing DeviceProfile.
     *
     * @param dProfile The device profile that is to be assigned to this SDO.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "dProfile" is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_device_profile(const DeviceProfile& dProfile)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO �� ServiceProfile �Υ��å�
     *
     * ���Υ��ڥ졼�����Ϥ��� Configuration interface ���ͭ�����о� SDO ��
     * ServiceProfile �����ꤹ�롣�⤷������ ServiceProfile �� id �����Ǥ����
     * ������ ID ���������줽�� ServiceProfile ���Ǽ���롣�⤷ id ������
     * �ʤ���С�SDO ��Ʊ�� id ����� ServiceProfile �򸡺����롣
     * Ʊ�� id ��¸�ߤ��ʤ���Ф��� ServiceProfile ���ɲä���id ��¸�ߤ����
     * ��񤭤򤹤롣
     *
     * @param sProfile �ɲä��� ServiceProfile
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "sProfile" �� null�Ǥ��롣
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set SDO's ServiceProfile
     *
     * This operation adds ServiceProfile to the target SDO that navigates this
     * Configuration interface. If the id in argument ServiceProfile is null,
     * new id is created and the ServiceProfile is stored. If the id is not
     * null, the target SDO searches for ServiceProfile in it with the same id.
     * It adds the ServiceProfile if not exist, or overwrites if exist.
     *
     * @param sProfile ServiceProfile to be added.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "sProfile" is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_service_profile(const ServiceProfile& sProfile)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization ���ɲ�
     *
     * ���Υ��ڥ졼������ Organization object �Υ�ե���󥹤��ɲä��롣
     *
     * @param org �ɲä��� Organization
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InvalidParameter ���� "organization" �� null �Ǥ��롣
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Add Organization
     *
     * This operation adds reference of an Organization object.
     *
     * @param org Organization to be added.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument ��organization�� is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean add_organization(Organization_ptr org)
      throw (InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ServiceProfile �κ��
     *
     * ���Υ��ڥ졼�����Ϥ��� Configuration interface ����� SDO ��
     * Service �� ServiceProfile �������롣������� ServiceProfile
     * �ϰ����ˤ����ꤵ��롣
     *
     * @param id ������� ServcieProfile �� serviceID��
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "id" �� null �Ǥ��롣�⤷���� "id" ��
     *                             ��Ϣ�դ���줿 ServiceProfile ��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Remove ServiceProfile
     *
     * This operation removes ServiceProfile object to the SDO that has this
     * Configuration interface. The ServiceProfile object to be removed is
     * specified by argument.
     *
     * @param id serviceID of a ServiceProfile to be removed.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter The argument "sProfile" is null, or if the
     *          object that is specified by argument "sProfile" does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean remove_service_profile(const char* id)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �λ��Ȥκ��
     *
     * ���Υ��ڥ졼������ Organization �λ��Ȥ������롣
     *
     * @param organization_id ������� Organization �ΰ�դ� id��
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter 
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Remove the reference of Organization 
     *
     * This operation removes the reference of an Organization object.
     *
     * @param organization_id Unique id of the organization to be removed.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter The argument "organizationID" is null,
     *            or the object which is specified by argument "organizationID"
     *            does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean remove_organization(const char* organization_id)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ����ѥ�᡼���Υꥹ�Ȥμ���
     *
     * ���Υ��ڥ졼������ configuration parameter �Υꥹ�Ȥ��֤���
     * SDO �������ǽ�ʥѥ�᡼��������ʤ���ж��Υꥹ�Ȥ��֤���
     *
     * @return �������ħ�դ���ѥ�᡼������Υꥹ�ȡ�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Getting a list of configuration parameter
     *
     * This operation returns a list of Parameters. An empty list is returned
     * if the SDO does not have any configurable parameter.
     *
     * @return The list with definitions of parameters characterizing the
     *          configuration.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual ParameterList* get_configuration_parameters()
      throw (NotAvailable, InternalError);

     /*!
     * @if jp
     * 
     * @brief [CORBA interface] Configuration parameter ���ͤΥꥹ�Ȥμ���
     *
     * ���Υ��ڥ졼������ configuration �ѥ�᡼��������ͤ��֤���
     *
     * @return ���Ƥ� configuration �ѥ�᡼�����ͤΥꥹ�ȡ�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Getting value list of configuration parameter
     *
     * This operation returns all configuration parameters and their values.
     *
     * @return List of all configuration parameters and their values.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual NVList* get_configuration_parameter_values()
      throw (NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Configuration parameter ���ͤμ���
     *
     * ���Υ��ڥ졼�����ϰ��� "name" �ǻ��ꤵ�줿�ѥ�᡼���ͤ��֤���
     *
     * @param name �ͤ��׵᤹��ѥ�᡼����̾����
     * @return ���ꤵ�줿�ѥ�᡼�����͡�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Getting value of configuration parameter
     *
     * This operation returns a value of parameter that is specified by
     * argument "name."
     *
     * @param Name of the parameter whose value is requested.
     * @return The value of the specified parameter.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Any* get_configuration_parameter_value(const char* name)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Configuration �ѥ�᡼�����ѹ�
     *
     * ���Υ��ڥ졼������ "name" �ǻ��ꤷ���ѥ�᡼�����ͤ� "value" ��
     * �ѹ����롣
     *
     * @param name �ѹ��������ѥ�᡼����̾����
     * @param value �ѹ��������ѥ�᡼�����͡�
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Modify the parameter value
     *
     * This operation sets a parameter to a value that is specified by argument
     * "value." The parameter to be modified is specified by argument " name."
     *
     * @param name The name of parameter to be modified.
     * @param value New value of the specified parameter.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter if arguments ("name" and/or "value") is
     *            null, or if the parameter that is specified by the argument
     *            "name" does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_configuration_parameter(const char* name,
						       const CORBA::Any& value)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet �ꥹ�Ȥμ��� 
     *
     * ���Υ��ڥ졼������ ConfigurationProfile ������ ConfigurationSet ��
     * �ꥹ�Ȥ��֤��� SDO �� ConfigurationSet ������ʤ���ж��Υꥹ�Ȥ��֤���
     *
     * @return �ݻ����Ƥ��� ConfigurationSet �Υꥹ�Ȥθ����͡�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Getting list of ConfigurationSet
     *
     * This operation returns a list of ConfigurationSets that the
     * ConfigurationProfile has. An empty list is returned if the SDO does not
     * have any ConfigurationSets.
     * This operation returns a list of all ConfigurationSets of the SDO.
     * If no predefined ConfigurationSets exist, then empty list is returned.
     *
     * @return The list of stored configuration with their current values.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual ConfigurationSetList* get_configuration_sets()
      throw (NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet �μ���
     *
     * ���Υ��ڥ졼�����ϰ����ǻ��ꤵ�줿 ConfigurationSet �� ID �˴�Ϣ
     * �դ���줿 ConfigurationSet ���֤���
     *
     * @param config_id ConfigurationSet �μ��̻ҡ�
     * @return �����ˤ����ꤵ�줿 ConfigurationSet��
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter "config_id" �� null �������ꤵ�줿
     *            ConfigurationSet ��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Getting a ConfigurationSet
     *
     * This operation returns the ConfigurationSet specified by the parameter
     * configurationSetID.
     *
     * @param config_id Identifier of ConfigurationSet requested.
     * @return The configuration set specified by the parameter config_id.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual ConfigurationSet* get_configuration_set(const char* config_id)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet �򥻥åȤ���
     *
     * ���Υ��ڥ졼�����ϻ��ꤵ�줿 id �� ConfigurationSet �򹹿����롣
     *
     * @param configu_id �ѹ����� ConfigurationSet �� ID��
     * @param configuration_set �ѹ����� ConfigurationSet ���Τ�Ρ�
     * @return ConfigurationSet ������˹����Ǥ������� true��
     *         �����Ǥʤ���� false ���֤���
     * @exception InvalidParameter config_id �� null �� ConfigurationSet
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set ConfigurationSet
     *
     * This operation modifies the specified ConfigurationSet of an SDO.
     *
     * �� �ѥ�᡼���ο��� spec �� IDL �ǰۤʤ롪����
     * @param configu_id The ID of ConfigurationSet to be modified.
     * @param configuration_set ConfigurationSet to be replaced.
     * @return A flag indicating if the ConfigurationSet was modified 
     *         successfully. "true" - The ConfigurationSet was modified
     *         successfully. "false" - The ConfigurationSet could not be
     *         modified successfully.
     * @exception InvalidParameter if the parameter 'configurationSetID' is
     *            null or if there is no ConfigurationSet stored with such id.
     *            This exception is also raised if one of the attributes
     *            defining ConfigurationSet is not valid.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean
    set_configuration_set_values(const char* config_id,
				 const ConfigurationSet& configuration_set)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] �����ƥ��֤� ConfigurationSet ���������
     *
     * ���Υ��ڥ졼����������SDO�θ��ߥ����ƥ��֤� ConfigurationSet ���֤���
     * (�⤷SDO�θ��ߤ����꤬ͽ��������줿 ConfigurationSet �ˤ�����ꤵ���
     * ����ʤ�С�)
     * ConfigurationSet �ϰʲ��ξ��ˤϥ����ƥ��֤ǤϤʤ���ΤȤߤʤ���롣
     *
     * - ���ߤ����꤬ͽ��������줿 ConfigurationSet �ˤ�ꥻ�åȤ���Ƥ��ʤ���
     * - SDO �����꤬�����ƥ��֤ˤʤä�����ѹ����줿��
     * - SDO �����ꤹ�� ConfigurationSet ���ѹ����줿��
     * 
     * �����ξ��ˤϡ����� ConfigurationSet ���֤���롣
     *
     * @return ���ߥ����ƥ��֤� ConfigurationSet��
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get active ConfigurationSet
     *
     * This operation returns the current active ConfigurationSet of an
     * SDO (i.e., if the current configuration of the SDO was set using
     * predefined configuration set).
     * ConfigurationSet cannot be considered active if the:
     *
     * - current configuration of the SDO was not set using any predefined
     *   ConfigurationSet, or
     * - configuration of the SDO was changed after it has been active, or
     * - ConfigurationSet that was used to configure the SDO was modified.
     *
     * Empty ConfigurationSet is returned in these cases.
     *
     * @return The active ConfigurationSet.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual ConfigurationSet* get_active_configuration_set()
      throw (NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet ���ɲä���
     *
     * ConfigurationProfile �� ConfigurationSet ���ɲä��륪�ڥ졼�����
     *
     * @param configuration_set �ɲä���� ConfigurationSet��
     * @return ���ڥ졼����������������ɤ�����
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Add ConfigurationSet
     *
     * This operation adds a ConfigurationSet to the ConfigurationProfile.
     *
     * @param configuration_set The ConfigurationSet that is added.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter If the argument "configurationSet" is null,
     *            or if one of the attributes defining "configurationSet" is
     *            invalid, or if the specified identifier of the configuration
     *            set already exists.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean
    add_configuration_set(const ConfigurationSet& configuration_set)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet ��������
     *
     * ConfigurationProfile ���� ConfigurationSet �������롣
     *
     * @param configu_id ������� ConfigurationSet �� id��
     * @return ���ڥ졼����������������ɤ�����
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "configurationSetID" �� null �Ǥ��롢
     *            �⤷���ϡ������ǻ��ꤵ�줿 ConfigurationSet ��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Remove ConfigurationSet
     *
     * This operation removes a ConfigurationSet from the ConfigurationProfile.
     *
     * @param config_id The id of ConfigurationSet which is removed.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter The arguments "configurationSetID" is null,
     *            or if the object specified by the argument
     *            "configurationSetID" does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean remove_configuration_set(const char* config_id)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet �Υ����ƥ��ֲ�
     *
     * ConfigurationProfile �˳�Ǽ���줿 ConfigurationSet �Τ�����Ĥ�
     * �����ƥ��֤ˤ��롣
     * ���Υ��ڥ졼����������� ConfigurationSet �򥢥��ƥ��֤ˤ��롣
     * ���ʤ����SDO �Υ���ե�����졼����󡦥ץ�ѥƥ������γ�Ǽ����Ƥ���
     * ConfigurationSet �ˤ�����ꤵ���ץ�ѥƥ����ͤ��ѹ�����롣
     * ���ꤵ�줿 ConfigurationSet ���ͤ������ƥ��֡�����ե�����졼�����
     * �˥��ԡ������Ȥ������Ȥ��̣���롣
     *
     * @param config_id �����ƥ��ֲ����� ConfigurationSet �� id��
     * @return ���ڥ졼����������������ɤ�����
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "config_id" �� null �Ǥ��롢�⤷����
     *            �����ǻ��ꤵ�줿 ConfigurationSet ��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Activate ConfigurationSet
     *
     * This operation activates one of the stored ConfigurationSets in the
     * ConfigurationProfile.
     * This operation activates the specified stored ConfigurationSets.
     * This means that the configuration properties of the SDO are changed as
     * the values of these properties specified in the stored ConfigurationSet.
     * In other words, values of the specified ConfigurationSet are now copied
     * to the active configuration.
     *
     * @param Identifier of ConfigurationSet to be activated.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter if the argument ("configID") is null or
     *            there is no configuration set with identifier specified by
     *            the argument.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean activate_configuration_set(const char* config_id)
      throw (InvalidParameter, NotAvailable, InternalError);

    // end of CORBA interface definition
    //============================================================

    Configuration_ptr getObjRef();

    const DeviceProfile getDeviceProfile();

    const ServiceProfileList getServiceProfiles();

    const ServiceProfile getServiceProfile(const char* id);
    
    const OrganizationList getOrganizations();

  protected:
    const std::string getUUID() const;

    Configuration_var m_objref;

    typedef ACE_Guard<ACE_Thread_Mutex> Guard;
    /*!
     * @if jp
     * @brief Lock �դ� SDO DeviceProfile
     * @else
     * @brief SDO DeviceProfile with mutex lock
     * @endif
     */
    DeviceProfile m_deviceProfile;
    ACE_Thread_Mutex m_dprofile_mutex;

    /*!
     * @if jp
     * @brief SDO ServiceProfileList
     * @else
     * @brief SDO ServiceProfileList
     * @endif
     */
    ServiceProfileList m_serviceProfiles;
    ACE_Thread_Mutex m_sprofile_mutex;

    /*!
     * @if jp
     * @brief SDO ParameterList
     * @else
     * @brief SDO ParameterList
     * @endif
     */
    /*
    struct Parameter
    {
      string         name;
      TypeCode  type;
      AllowedValues allowed_values;
    };
    */
    ParameterList m_parameters;
    ACE_Thread_Mutex m_params_mutex;

    /*!
     * @if jp
     * @brief SDO ConfigurationSetList
     * @else
     * @brief SDO ConfigurationSetList
     * @endif
     */
    /*
      struct ConfigurationSet
      {
      string id;
      string description;
      NVList configuration_data;
      };
    */
    RTC::ConfigAdmin& m_configsets;
    ACE_Thread_Mutex m_config_mutex;

    /*!
     * @if jp
     * @brief SDO OrganizationList
     * @else
     * @brief SDO OrganizationList
     * @endif
     */
    OrganizationList m_organizations;
    ACE_Thread_Mutex m_org_mutex;

    /*!
     * @if jp
     * @brief �����ƥ��֤� ConfigurationSet
     * @else
     * @brief Active ConfigurationSet id
     * @endif
     */

    struct nv_name
    {
      nv_name(const char* name) : m_name(name) {};
      bool operator()(const NameValue& nv)
      {
	return m_name == std::string(nv.name);
      }
      std::string m_name;
    };


    // functor for ServiceProfile
    struct service_id
    {
      service_id(const char* id) : m_id(id) {};
      bool operator()(const ServiceProfile& s)
      {
	std::string id(s.id);
	return m_id == id;
      }
      const std::string m_id;
    };

    // functor for Organization
    struct org_id
    {
      org_id(const char* id) : m_id(id) {};
      bool operator()(const Organization_ptr& o)
      {
	std::string id(o->get_organization_id());
	return m_id == id;
      }
      const std::string m_id;
    };
    
    // functor for ConfigurationSet
    struct config_id
    {
      config_id(const char* id) :  m_id(id) {};
      bool operator()(const ConfigurationSet& c)
      {
	std::string id(c.id);
	return m_id == id;
      }
      const std::string m_id;
    };

  };

}; // namespace SDOPackage

#endif // SdoConfiguration_h
