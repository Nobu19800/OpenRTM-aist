// -*- C++ -*-
/*!
 * @file SdoOrganization.h
 * @brief SDO Organization implementation class
 * @date $Date: 2006-10-17 10:12:57 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoOrganization.h,v 1.2 2006-10-17 10:12:57 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/09/11 18:14:20  n-ando
 * The first commit.
 *
 *
 */

#ifndef SdoOrganization_h
#define SdoOrganization_h

#include "rtm/RTC.h"

#include "rtm/idl/SDOPackageSkel.h"

namespace SDOPackage
{
  
  class Organization_impl 
  {
  public:
    Organization_impl();
    virtual ~Organization_impl();

    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization ID ���������
     *
     * Organization �� ID ���֤����ڥ졼�����
     *
     * @return Resource Data Model ��������줿 Organization ID��
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get Organization Id
     *
     * This operation returns the 'id' of the Organization.
     *
     * @return The id of the Organization defined in the resource data model.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual char* get_organization_id()
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] OrganizationProperty �μ���
     *
     * Organization ����ͭ���� OrganizationProperty ���֤����ڥ졼�����
     * Organization ���ץ�ѥƥ�������ʤ���ж��Υꥹ�Ȥ��֤���
     *
     * @return Organization �Υץ�ѥƥ��Υꥹ�ȡ�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get OrganizationProperty
     *
     * This operation returns the OrganizationProperty that an Organization
     * has. An empty OrganizationProperty is returned if the Organization does
     * not have any properties.
     *
     * @return The list with properties of the organization.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual OrganizationProperty* get_organization_property()
      throw (NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] OrganizationProperty ��������ͤμ���
     *
     * OrganizationProperty �λ��ꤵ�줿�ͤ��֤����ڥ졼�����
     * ���� "name" �ǻ��ꤵ�줿�ץ�ѥƥ����ͤ��֤���
     *
     * @param name �ͤ��֤��ץ�ѥƥ���̾����
     * @return ���� "name" �ǻ��ꤵ�줿�ץ�ѥƥ����͡�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "namne" �ǻ��ꤵ�줿�ץ�ѥƥ���
     *            ¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get specified value of OrganizationProperty
     *
     * This operation returns a value in the OrganizationProperty.
     * The value to be returned is specified by argument "name."
     *
     * @param name The name of the value to be returned.
     * @return The value of property which is specified by argument "name."
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Any* get_organization_property_value(const char* name)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] OrganizationProperty �Υ��å�
     *
     * �� SDO Specification �� PIM ���Ҥȥ��ڥ졼�����̾���ۤʤ롣
     * �� addOrganizationProperty ���б�����
     * OrganizationProperty �� Organization ���ɲä��륪�ڥ졼�����
     * OrganizationProperty �� Organization �Υץ�ѥƥ����ҤǤ��롣
     *
     * @param org_property ���åȤ��� OrganizationProperty
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter "org_property" �� null��
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set OrganizationProperty
     *
     * �� SDO Specification �� PIM ���Ҥȥ��ڥ졼�����̾���ۤʤ롣
     * �� addOrganizationProperty ���б�����
     * This operation adds the OrganizationProperty to an Organization. The
     * OrganizationProperty is the property description of an Organization.
     *
     * @param org_property The type of organization to be added.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter The argument "organizationProperty" is null.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean
    set_organization_property(const OrganizationProperty& org_property)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] OrganizationProperty ���ͤΥ��å�
     *
     * OrganizationProperty �� NVList �� name �� value �Υ��åȤ��ɲä⤷����
     * �������륪�ڥ졼�����name �� value �ϰ��� "name" �� "value" �ˤ��
     * ���ꤹ�롣
     *
     * @param name �ɲá����������ץ�ѥƥ���̾����
     * @param value �ɲá����������ץ�ѥƥ����͡�
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "name" �ǻ��ꤵ�줿�ץ�ѥƥ���
     *            ¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set specified value of OrganizationProperty
     *
     * This operation adds or updates a pair of name and value as a property
     * of Organization to/in NVList of the OrganizationProperty. The name and
     * the value to be added/updated are specified by argument "name" and
     * "value."
     *
     * @param name The name of the property to be added/updated.
     * @param value The value of the property to be added/updated.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The property that is specified by argument
     *            "name" does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean
    set_organization_property_value(const char* name, const CORBA::Any& value)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] OrganizationProperty �κ��
     *
     * OrganizationProperty �� NVList ��������Υץ�ѥƥ��������롣
     * ��������ץ�ѥƥ���̾���ϰ��� "name" �ˤ����ꤵ��롣
     *
     * @param name �������ץ�ѥƥ���̾����
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "name" �ǻ��ꤵ�줿�ץ�ѥƥ���
     *            ¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Remove specified OrganizationProperty
     *
     * This operation removes a property of Organization from NVList of the
     * OrganizationProperty. The property to be removed is specified by
     * argument "name."
     *
     * @param name The name of the property to be removed.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The property that is specified by argument
     *            "name" does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean remove_organization_property(const char* name)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO �� ServiceProfile �Υ��å�
     *
     * ���� Organization �Υ����ʡ��ؤλ��Ȥ��֤���
     *
     * @return �����ʡ����֥������Ȥؤλ��ȡ�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set SDO's ServiceProfile
     *
     * This operation returns the SDOSystemElement that is owner of
     * the Organization.
     *
     * @return Reference of owner object.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual SDOSystemElement_ptr get_owner()
      throw (NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �˥����ʡ��򥻥åȤ���
     *
     * Organization ���Ф��� SDOSystemElement �򥪡��ʡ��Ȥ��ƥ��åȤ��롣
     * ���� "sdo" �˥��åȤ��� SDOSystemElement ����ꤹ�롣
     *
     * @param sdo �����ʡ����֥������Ȥλ��ȡ�
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "sdo" �� null�Ǥ��롢�⤷���ϡ�
     *                             "sdo" ��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set the orner of the Organization
     *
     * This operation sets an SDOSystemElement to the owner of the
     * Organization. The SDOSystemElement to be set is specified by argument
     * "sdo."
     *
     * @param sdo Reference of owner object.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "sdo" is null, or the object
     *            that is specified by "sdo" in argument "sdo" does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_owner(SDOSystemElement_ptr sdo)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �Υ��С����������
     *
     * Organization �Υ��С��� SDO �Υꥹ�Ȥ��֤���
     * ���С���¸�ߤ��ʤ���ж��Υꥹ�Ȥ��֤���
     *
     * @return Organization �˴ޤޤ����С� SDO �Υꥹ�ȡ�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get a menber list of the Organization
     *
     * This operation returns a list of SDOs that are members of an
     * Organization. An empty list is returned if the Organization does not
     * have any members.
     *
     * @return Member SDOs that are contained in the Organization object.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual SDOList* get_members()
      throw (NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO �� ServiceProfile �Υ��å�
     *
     * SDO �Υꥹ�Ȥ� Organization �Υ��С��Ȥ��ƥ��åȤ��롣
     * Organization �����Ǥ˥��С��� SDO ��������Ƥ�����ϡ�
     * Ϳ����줿 SDO �Υꥹ�Ȥ��֤������롣
     *
     * @param sdos ���С��� SDO��
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "SDOList" �� null�Ǥ��롢�⤷����
     *            �����˻��ꤵ�줿 "SDOList" ��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set SDO's ServiceProfile
     *
     * This operation assigns a list of SDOs to an Organization as its members.
     * If the Organization has already maintained a member SDO(s) when it is
     * called, the operation replaces the member(s) with specified list of
     * SDOs.
     *
     * @param sdos Member SDOs to be assigned.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "SDOList" is null, or if the
     *            object that is specified by the argument "sdos" does not
     *            exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_members(const SDOList& sdos)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO ���С����ɲ�
     *
     * Organization �˥��С��Ȥ��� SDO ���ɲä��롣
     * ���� "sdo" ���ɲä�����С� SDO ����ꤹ�롣
     *
     * @param sdo Organization ���ɲä���� SDO �Υꥹ�ȡ�
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "sdo" �� null�Ǥ��롣
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Add the menebr SDOs
     *
     * This operation adds a member that is an SDO to the organization.
     * The member to be added is specified by argument "sdo."
     *
     * @param sdo The member to be added to the organization.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "sdo" is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean add_members(const SDOList& sdo_list)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO ���С��κ��
     *
     * Organization ��������ǻ��ꤵ�줿 "id" �� SDO �������롣
     *
     * @param id ������� SDO �� id��
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "id" �� null �⤷����¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Remove menber SDO from Organization
     *
     * This operation removes a member from the organization. The member to be
     * removed is specified by argument "id."
     *
     * @param id Id of the SDO to be removed from the organization.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "id" is null or does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean remove_member(const char* id)
      throw (InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �� DependencyType �����
     *
     * Organization �δط���ɽ�� "DependencyType" ���֤���
     *
     * @return Organizaton �ΰ�¸�ط� DependencyType ���֤���
     *         DependencyType �� OMG SDO ���ͤ� Section 2.2.2 2-3 �ڡ�����
     *         "Data Structures Used by Resource Data Model" �򻲾ȡ�
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Get the DependencyType of the Organization
     *
     * This operation gets the relationship "DependencyType" of the
     * Organization.
     *
     * @return The relationship of the Organization as DependencyType.
     *         DependencyType is defined in Section 2.2.2, "Data Structures
     *         Used by Resource Data Model," on page 2-3
     *         of OMG SDO Specification.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual DependencyType get_dependency()
      throw (NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization �� DependencyType �򥻥åȤ���
     *
     * Organization �ΰ�¸�ط� "DependencyType" �򥻥åȤ��롣
     * ���� "dependencty" �ˤ���¸�ط���Ϳ���롣
     *
     * @param dependency Organization �ΰ�¸�ط���ɽ�� DependencyType��
     *        DependencyType �� OMG SDO ���ͤ� Section 2.2.2��2-3 �ڡ�����
     *        "Data Structures Used by Resource Data Model" �򻲾ȡ�
     * @return ���ڥ졼����������������ɤ������֤���
     * @exception SDONotExists �������åȤ�SDO��¸�ߤ��ʤ���
     * @exception InvalidParameter ���� "sProfile" �� null�Ǥ��롣
     * @exception NotAvailable SDO��¸�ߤ��뤬�������ʤ���
     * @exception InternalError ����Ū���顼��ȯ��������
     * @else
     *
     * @brief [CORBA interface] Set the DependencyType of the Organization
     *
     * This operation sets the relationship "DependencyType" of the
     * Organization. The value to be set is specified by argument "dependency."
     *
     * @param dependency The relationship of the Organization as
     *                   DependencyType. DependencyType is defined in Section
     *                   2.2.2, "Data Structures Used by Resource Data Model,"
     *                   on page 2-3.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "dependency" is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_dependency(DependencyType dependency)
      throw (NotAvailable, InternalError);

    // end of CORBA interface definition
    //============================================================


    
  protected:
    /*!
     * @if jp
     *
     * @brief Organization �μ��̻�
     *
     * @else
     *
     * @brief The identifier of the Organization.
     *
     * @endif
     */
    char* m_pId;

    /*!
     * @if jp
     *
     * @brief Organization �˴�Ϣ�դ���줿 SDO ���ФΥꥹ��
     *
     * @else
     *
     * @brief A list of reference to SDOs that are the members associated with
     *        the Organization.
     *
     * @endif
     */
    SDOPackage::SDOList m_MemberList;

    /*!
     * @if jp
     *
     * @brief Organization �� owner
     *
     * @else
     *
     * @brief The owner of the Organization
     *
     * @endif
     */   
    SDOPackage::SDOSystemElement_var m_varOwner;

    /*!
     * @if jp
     * 
     * @brief ��¸�ط��Υ�����
     *
     * Owner �� member �ΰ�¸�ط�����ꤹ��°����
     * Organization �ϰʲ��Υȥݥ��ѥ������ɽ�����뤳�Ȥ��Ǥ��롣
     *
     * 1. owenr �� member ��������볬��Ū��¤�����ξ�� DependencyType �� OWN
     *    �Ȥ����ͤ���ġ�
     * 2. members �� owner ���������ո����γ���Ū��¤�����ξ���
     *    DependencyType �� OWNER �Ȥ����ͤ���ġ�
     * 3. owner �� member �˰�¸�ط����ʤ��ե�åȤʹ�¤�����ξ���
     *    DependencyType �� NO_DEPENDENCY �Ȥ����ͤ���ġ�
     * 
     * SDO ����� SDOSystemElement �Υ��֥��饹�� Organization �� owner �Ȥ���
     * ���񤦤��Ȥ�����롣SDO �� owner �ξ��ˤ�Organization �Ͼ嵭��
     * �����줫�Υȥݥ����ѥ������Ȥ롣
     *
     * - Organization �� 1. �Υȥݥ����ѥ��������ľ�硢ͣ��Ĥ� owner SDO
     *   �� member SDO �����椹�롣���Ȥ��С���������(owner)�ϡ�
     *   ���٥���(member)�����٥���(member)�����������(member)�����椹�롣
     * - Organization �� 2. �Υȥݥ�����ľ��ϡ�ʣ���� SDO member ��ͣ���
     *   SDO owner ��ͭ���롣���Ȥ��С������(owner)�Ϥ����Ĥ���AV
     *   ����ݡ��ͥ��(member)���鶦ͭ����롣
     * - SDO �ǤϤʤ� SDOSystemElement �Υ��֥��饹�� owner �ξ�硢
     *   �ʲ��Τ褦�ʥȥݥ����㤬�ͤ����롣
     * -- User(owner)-SDO(member): �桼��(owner) �ϰ�İʾ�� SDO(member)��
     *   �������롣����Ͼ嵭�ȥݥ��ѥ���1.�ˤ����롣
     * -- Location(owner)-SDO(members): ��İʾ�� SDO(member) ������ξ��
     *   = location(owner) ��ư��Ƥ����硢Organization �Υȥݥ��ѥ�����
     *   �� 3. �ξ��ˤʤ롣���Ȥ��С�ʣ���� PDA �����������ˤ��ꡢ�ߤ���Ʊ��
     *   �ʴط��Ǥ�����ߤ��̿���ǽ�ʾ��Ϥ���ˤ����롣
     *
     * @else
     *
     * @brief Dependency type
     *
     * This attribute specifies the dependency relation between the owner and
     * members of the organization.
     * Organization is used to form the following three patterns of topology.
     *
     * 1. Hierarchical organization, which indicates owner supervises members.
     *    In this case, DependencyType should hold OWN value (see description
     *    of DependencyType on previous pages).
     * 2. Reversely hierarchical organization, which indicates members
     *    supervise owner. In this case, DependencyType should hold OWNED value
     *    (see description of DependencyType on previous pages).
     * 3. Flat organization, which indicates no dependency exists. In this
     *    case, DependencyType should hold NO_DEPENDENCY value (see description
     *    of DependencyType on previous pages).
     *
     * Both an SDO and another subclass of SDOSystemElement can act as owner
     * of an Organization. When an SDO is an owner, Organization can represent
     * any of theabove three topology patterns.
     *
     * - When an Organization represents topology pattern (1), an SDO (owner)
     *   controls one or more SDOs (members). For example, air conditioner
     *   (owner) controls a temperature sensor (member), humidity sensor
     *   (member), and wind flow controller (member).
     * - When an Organization represents topology pattern (2), multiple
     *   SDOs(members) share an SDO (owner). For example, an amplifier (owner)
     *   is shared by several AV components (members) in an AV stereo.
     * - When a subclass of SDOSystemElement, which is not an SDO is an owner
     *   examples of the topology are as follows.
     * -- User (owner)-SDO (members): When a user (owner) supervises one or
     *    more SDOs (members), the organization represents topology pattern 1.
     * -- Location (owner)-SDO (members): When one or more SDOs (members) are
     *    operating in a specific location (owner), the organization represents
     *    topology pattern 3. For example, multiple PDAs in the same place
     *    (e.g., a room) have equal relationships among them to communicate
     *    with each other.
     * @endif
     */
    SDOPackage::DependencyType m_Dependency;

    /*!
     * @if jp
     *
     * @brief Organization �ץ�ѥƥ�
     *
     * OrganizationProperty �� Organization �Υץ�ѥƥ�������ݻ����롣
     * ��Ĥ� Organization ��0�Ĥ⤷����1�Ĥ� OrganizationProperty ���ġ�
     *
     * @member property NVList
     *
     * @else
     *
     * @brief Organization property
     *
     * OrganizationProperty contains the properties of an Organization.
     * An Organization has zero or one (at most one) instance
     * of OrganizationProperty.
     *
     * @member property NVList
     *
     * @endif
     */
    SDOPackage::OrganizationProperty m_OrganizationProperty;

  };
  
  
};

#endif // namespace SDOPackage
