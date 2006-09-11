// -*- C++ -*-
/*!
 * @file SdoOrganization.h
 * @brief SDO Organization implementation class
 * @date $Date: 2006-09-11 18:14:20 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoOrganization.h,v 1.1 2006-09-11 18:14:20 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
     * @brief [CORBA interface] Organization ID $B$r<hF@$9$k(B
     *
     * Organization $B$N(B ID $B$rJV$9%*%Z%l!<%7%g%s!#(B
     *
     * @return Resource Data Model $B$GDj5A$5$l$?(B Organization ID$B!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] OrganizationProperty $B$N<hF@(B
     *
     * Organization $B$,=jM-$9$k(B OrganizationProperty $B$rJV$9%*%Z%l!<%7%g%s!#(B
     * Organization $B$,%W%m%Q%F%#$r;}$?$J$1$l$P6u$N%j%9%H$rJV$9!#(B
     *
     * @return Organization $B$N%W%m%Q%F%#$N%j%9%H!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] OrganizationProperty $B$NFCDj$NCM$N<hF@(B
     *
     * OrganizationProperty $B$N;XDj$5$l$?CM$rJV$9%*%Z%l!<%7%g%s!#(B
     * $B0z?t(B "name" $B$G;XDj$5$l$?%W%m%Q%F%#$NCM$rJV$9!#(B
     *
     * @param name $BCM$rJV$9%W%m%Q%F%#$NL>A0!#(B
     * @return $B0z?t(B "name" $B$G;XDj$5$l$?%W%m%Q%F%#$NCM!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "namne" $B$G;XDj$5$l$?%W%m%Q%F%#$,(B
     *            $BB8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] OrganizationProperty $B$N%;%C%H(B
     *
     * $B"((B SDO Specification $B$N(B PIM $B5-=R$H%*%Z%l!<%7%g%sL>$,0[$J$k!#(B
     * $B"((B addOrganizationProperty $B$KBP1~$+!)(B
     * OrganizationProperty $B$r(B Organization $B$KDI2C$9$k%*%Z%l!<%7%g%s!#(B
     * OrganizationProperty $B$O(B Organization $B$N%W%m%Q%F%#5-=R$G$"$k!#(B
     *
     * @param org_property $B%;%C%H$9$k(B OrganizationProperty
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter "org_property" $B$,(B null$B!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
     * @else
     *
     * @brief [CORBA interface] Set OrganizationProperty
     *
     * $B"((B SDO Specification $B$N(B PIM $B5-=R$H%*%Z%l!<%7%g%sL>$,0[$J$k!#(B
     * $B"((B addOrganizationProperty $B$KBP1~$+!)(B
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
     * @brief [CORBA interface] OrganizationProperty $B$NCM$N%;%C%H(B
     *
     * OrganizationProperty $B$N(B NVList $B$K(B name $B$H(B value $B$N%;%C%H$rDI2C$b$7$/$O(B
     * $B99?7$9$k%*%Z%l!<%7%g%s!#(Bname $B$H(B value $B$O0z?t(B "name" $B$H(B "value" $B$K$h$j(B
     * $B;XDj$9$k!#(B
     *
     * @param name $BDI2C!&99?7$5$l$k%W%m%Q%F%#$NL>A0!#(B
     * @param value $BDI2C!&99?7$5$l$k%W%m%Q%F%#$NCM!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "name" $B$G;XDj$5$l$?%W%m%Q%F%#$O(B
     *            $BB8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] OrganizationProperty $B$N:o=|(B
     *
     * OrganizationProperty $B$N(B NVList $B$+$iFCDj$N%W%m%Q%F%#$r:o=|$9$k!#(B
     * $B:o=|$5$l$k%W%m%Q%F%#$NL>A0$O0z?t(B "name" $B$K$h$j;XDj$5$l$k!#(B
     *
     * @param name $B:o=|$9$k%W%m%Q%F%#$NL>A0!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "name" $B$G;XDj$5$l$?%W%m%Q%F%#$O(B
     *            $BB8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] SDO $B$N(B ServiceProfile $B$N%;%C%H(B
     *
     * $B$3$N(B Organization $B$N%*!<%J!<$X$N;2>H$rJV$9!#(B
     *
     * @return $B%*!<%J!<%*%V%8%'%/%H$X$N;2>H!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] Organization $B$K%*!<%J!<$r%;%C%H$9$k(B
     *
     * Organization $B$KBP$7$F(B SDOSystemElement $B$r%*!<%J!<$H$7$F%;%C%H$9$k!#(B
     * $B0z?t(B "sdo" $B$K%;%C%H$9$k(B SDOSystemElement $B$r;XDj$9$k!#(B
     *
     * @param sdo $B%*!<%J!<%*%V%8%'%/%H$N;2>H!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "sdo" $B$,(B null$B$G$"$k!"$b$7$/$O!"(B
     *                             "sdo" $B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] Organization $B$N%a%s%P!<$r<hF@$9$k(B
     *
     * Organization $B$N%a%s%P!<$N(B SDO $B$N%j%9%H$rJV$9!#(B
     * $B%a%s%P!<$,B8:_$7$J$1$l$P6u$N%j%9%H$rJV$9!#(B
     *
     * @return Organization $B$K4^$^$l$k%a%s%P!<(B SDO $B$N%j%9%H!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] SDO $B$N(B ServiceProfile $B$N%;%C%H(B
     *
     * SDO $B$N%j%9%H$r(B Organization $B$N%a%s%P!<$H$7$F%;%C%H$9$k!#(B
     * Organization $B$,$9$G$K%a%s%P!<$N(B SDO $B$r4IM}$7$F$$$k>l9g$O!"(B
     * $BM?$($i$l$?(B SDO $B$N%j%9%H$KCV$-49$($k!#(B
     *
     * @param sdos $B%a%s%P!<$N(B SDO$B!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "SDOList" $B$,(B null$B$G$"$k!"$b$7$/$O(B
     *            $B0z?t$K;XDj$5$l$?(B "SDOList" $B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] SDO $B%a%s%P!<$NDI2C(B
     *
     * Organization $B$K%a%s%P!<$H$7$F(B SDO $B$rDI2C$9$k!#(B
     * $B0z?t(B "sdo" $B$KDI2C$9$k%a%s%P!<(B SDO $B$r;XDj$9$k!#(B
     *
     * @param sdo Organization $B$KDI2C$5$l$k(B SDO $B$N%j%9%H!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "sdo" $B$,(B null$B$G$"$k!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] SDO $B%a%s%P!<$N:o=|(B
     *
     * Organization $B$+$i0z?t$G;XDj$5$l$?(B "id" $B$N(B SDO $B$r:o=|$9$k!#(B
     *
     * @param id $B:o=|$9$k(B SDO $B$N(B id$B!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "id" $B$,(B null $B$b$7$/$OB8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] Organization $B$N(B DependencyType $B$r<hF@(B
     *
     * Organization $B$N4X78$rI=$9(B "DependencyType" $B$rJV$9!#(B
     *
     * @return Organizaton $B$N0MB84X78(B DependencyType $B$rJV$9!#(B
     *         DependencyType $B$O(B OMG SDO $B;EMM$N(B Section 2.2.2 2-3 $B%Z!<%8$N(B
     *         "Data Structures Used by Resource Data Model" $B$r;2>H!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] Organization $B$N(B DependencyType $B$r%;%C%H$9$k(B
     *
     * Organization $B$N0MB84X78(B "DependencyType" $B$r%;%C%H$9$k!#(B
     * $B0z?t(B "dependencty" $B$K$h$j0MB84X78$rM?$($k!#(B
     *
     * @param dependency Organization $B$N0MB84X78$rI=$9(B DependencyType$B!#(B
     *        DependencyType $B$O(B OMG SDO $B;EMM$N(B Section 2.2.2$B!"(B2-3 $B%Z!<%8$N(B
     *        "Data Structures Used by Resource Data Model" $B$r;2>H!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "sProfile" $B$,(B null$B$G$"$k!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief Organization $B$N<1JL;R(B
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
     * @brief Organization $B$K4XO"IU$1$i$l$?(B SDO $B%a%s%P$N%j%9%H(B
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
     * @brief Organization $B$N(B owner
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
     * @brief $B0MB84X78$N%?%$%W(B
     *
     * Owner $B$H(B member $B$N0MB84X78$r;XDj$9$kB0@-!#(B
     * Organization $B$O0J2<$N%H%]%m%8%Q%?!<%s$rI=8=$9$k$3$H$,$G$-$k!#(B
     *
     * 1. owenr $B$,(B member $B$r4IM}$9$k3,AXE*9=B$!#$3$N>l9g(B DependencyType $B$O(B OWN
     *    $B$H$$$&CM$r;}$D!#(B
     * 2. members $B$,(B owner $B$r4IM}$9$k5U8~$-$N3,AXE*9=B$!#$3$N>l9g$O(B
     *    DependencyType $B$O(B OWNER $B$H$$$&CM$r;}$D!#(B
     * 3. owner $B$H(B member $B$K0MB84X78$,$J$$%U%i%C%H$J9=B$!#$3$N>l9g$O(B
     *    DependencyType $B$O(B NO_DEPENDENCY $B$H$$$&CM$r;}$D!#(B
     * 
     * SDO $B$*$h$S(B SDOSystemElement $B$N%5%V%/%i%9$O(B Organization $B$N(B owner $B$H$7$F(B
     * $B?6Iq$&$3$H$,=PMh$k!#(BSDO $B$,(B owner $B$N>l9g$K$O(BOrganization $B$O>e5-$N(B
     * $B$$$:$l$+$N%H%]%m%8!<%Q%?!<%s$r$H$k!#(B
     *
     * - Organization $B$,(B 1. $B$N%H%]%m%8!<%Q%?!<%s$r;}$D>l9g!"M#0l$D$N(B owner SDO
     *   $B$O(B member SDO $B$r@)8f$9$k!#$?$H$($P!"%(%"%3%s(B(owner)$B$O!"(B
     *   $B29EY%;%s%5(B(member)$B!"<>EY%;%s%5(B(member)$B!"IwNL@)8f4o(B(member)$B$r@)8f$9$k!#(B
     * - Organization $B$,(B 2. $B$N%H%]%m%8$r;}$D>l9g$O!"J#?t$N(B SDO member $B$,M#0l$N(B
     *   SDO owner $B$r6&M-$9$k!#$?$H$($P!"%"%s%W(B(owner)$B$O$$$/$D$+$N(BAV
     *   $B%3%s%]!<%M%s%H(B(member)$B$+$i6&M-$5$l$k!#(B
     * - SDO $B$G$O$J$$(B SDOSystemElement $B$N%5%V%/%i%9$,(B owner $B$N>l9g!"(B
     *   $B0J2<$N$h$&$J%H%]%m%8!<Nc$,9M$($i$l$k!#(B
     * -- User(owner)-SDO(member): $B%f!<%6(B(owner) $B$O0l$D0J>e$N(B SDO(member)$B$r(B
     *   $B4IM}$9$k!#$3$l$O>e5-%H%]%m%8%Q%?%s(B1.$B$K$"$?$k!#(B
     * -- Location(owner)-SDO(members): $B0l$D0J>e$N(B SDO(member) $B$,FCDj$N>l=j(B
     *   = location(owner) $B$GF0:n$7$F$$$k>l9g!"(BOrganization $B$N%H%]%m%8%Q%?!<%s(B
     *   $B$O(B 3. $B$N>l9g$K$J$k!#$?$H$($P!"J#?t$N(B PDA $B$,$"$kIt20$K$"$j!"8_$$$KF1Ey(B
     *   $B$J4X78$G$"$jAj8_$KDL?.2DG=$J>l9g$O$3$l$K$"$?$k!#(B
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
     * @brief Organization $B%W%m%Q%F%#(B
     *
     * OrganizationProperty $B$O(B Organization $B$N%W%m%Q%F%#>pJs$rJ];}$9$k!#(B
     * $B0l$D$N(B Organization $B$O(B0$B8D$b$7$/$O(B1$B8D$N(B OrganizationProperty $B$r$b$D!#(B
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
