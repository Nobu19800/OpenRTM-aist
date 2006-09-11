// -*- C++ -*-
/*!
 * @file SdoSystemElement.h
 * @brief SDOSystemElement and SDO classes
 * @date $Date: 2006-09-11 18:14:41 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoSystemElement.h,v 1.1 2006-09-11 18:14:41 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef SdoSystemElement_h
#define SdoSystemElement_h

// CORBA header include
#include "rtm/RTC.h"
#include "rtm/Util.h"



// local includes
#include "rtm/idl/SDOPackageSkel.h"



namespace SDOPackage
{
  class Configuration_impl;
  class Organization_impl;
  /*!
   * @if jp
   *
   * @class SDOSystemElement_impl
   * @brief SDOSystemElement $B<BAu%/%i%9(B
   *
   * SDOSystemElement $B%$%s%?!<%U%'!<%9$O(BSDOSystemElement$B$N%5%V%/%i%9$r(B
   * $B4IM}$9$k$?$a$KMxMQ$5$l$k!#(B
   *
   * @else
   *
   * @class SDOSystemElement_impl
   * @brief SDOSystemElement implementation class
   *
   * The SDOSystemElement interface is used to manage the subclass of
   * SDOSystemElement itself.
   *
   * @endif
   */
  class SDOSystemElement_impl
    : public virtual POA_SDOPackage::SDOSystemElement, 
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief SDOSystemElement $B%/%i%9%3%s%9%H%i%/%?(B
     *
     * @else
     *
     * @brief A constructor of SDOSystemElement
     *
     * @endif
     */
    SDOSystemElement_impl();
    SDOSystemElement_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);

    /*!
     * @if jp
     * 
     * @brief RtcBase $B%/%i%9%G%9%H%i%/%?(B
     *
     * @else
     *
     * @brief A destructor of RtcBase class.
     *
     * @endif
     */
    virtual ~SDOSystemElement_impl();

    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization $B%j%9%H$N<hF@(B 
     *
     * SDOSystemElement $B$O(B0$B8D$b$7$/$O$=$l0J>e$N(B Organization $B$r=jM-$9$k$3$H$,(B
     * $B=PMh$k!#(B SDOSystemElement $B$,(B1$B$D0J>e$N(B Organization $B$r=jM-$7$F$$$k>l9g(B
     * $B$K$O!"$3$N%*%Z%l!<%7%g%s$O=jM-$9$k(B Organization $B$N%j%9%H$rJV$9!#(B
     * $B$b$7(BOrganization$B$r0l$D$b=jM-$7$F$$$J$$$1$l$P6u$N%j%9%H$rJV$9!#(B
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
    virtual OrganizationList* get_owned_organizations()
      throw (NotAvailable);

    // end of CORBA interface definition
    //============================================================

  protected:
    // Partial specialization
    template <class T, class X>
    class SeqEx
      : public SequenceEx <T, X, ACE_Thread_Mutex> {};
    
    SeqEx<OrganizationList, Organization_ptr> m_ownedOrganizations;

    CORBA::ORB_var m_pORB;
    PortableServer::POA_var m_pPOA;
    

  };
  

  //============================================================
  // SDO_impl
  //============================================================
  /*!
   * @if jp
   *
   * @class SDO_impl
   * @brief SDO $B<BAu%/%i%9(B
   *
   * SDO $B%$%s%?!<%U%'!<%9$O(BSDO$BMWAG$r4IM}$9$k$?$a$K;HMQ$5$l$k!#(B
   * SDO $B;EMM$K$*$$$FDj5A$5$l$F$$$kB>$NA4$F$N%$%s%?!<%U%'!<%9$O(B
   * SDO $B%$%s%?!<%U%'!<%9$r5/E@$KA`:n$5$l$k!#(B
   *
   * @else
   *
   * @class SDO_impl
   * @brief SDO implementation class
   *
   * The SDO interface is used to manage elements of the SDO.
   * All the other interfaces specified in this specification are
   * navigated from SDO interface.
   *
   * @endif
   */
  class SDO_impl
    : public virtual SDOSystemElement_impl
  {
  public:
    //    SDO_impl();
    //    SDO_impl(char* id = "", char* type = "");
    SDO_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    virtual ~SDO_impl(){};

    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO ID $B$N<hF@(B
     *
     * SDO ID $B$rJV$9%*%Z%l!<%7%g%s!#(B
     * $B$3$N%*%Z%l!<%7%g%s$O0J2<$N7?$NNc30$rH/@8$5$;$k!#(B
     * 
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
     * @return    $B%j%=!<%9%G!<%?%b%G%k$GDj5A$5$l$F$$$k(B SDO $B$N(B ID
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
      throw (NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO $B%?%$%W$N<hF@(B
     * 
     * SDO Type $B$rJV$9%*%Z%l!<%7%g%s!#(B
     * $B$3$N%*%Z%l!<%7%g%s$O0J2<$N7?$NNc30$rH/@8$5$;$k!#(B
     *
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
     * @return    $B%j%=!<%9%G!<%?%b%G%k$GDj5A$5$l$F$$$k(B SDO $B$N(B Type
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
      throw (NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO DeviceProfile $B%j%9%H$N<hF@(B 
     *
     * SDO $B$N(B DeviceProfile $B$rJV$9%*%Z%l!<%7%g%s!#(B SDO $B$,%O!<%I%&%(%"%G%P%$%9(B
     * $B$K4XO"IU$1$i$l$F$$$J$$>l9g$K$O!"6u$N(B DeviceProfile $B$,JV$5$l$k!#(B
     * $B$3$N%*%Z%l!<%7%g%s$O0J2<$N7?$NNc30$rH/@8$5$;$k!#(B
     *
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
    virtual DeviceProfile* get_device_profile()
      throw (NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO ServiceProfile $B$N<hF@(B 
     *
     * SDO $B$,=jM-$7$F$$$k(B Service $B$N(B ServiceProfile $B$rJV$9%*%Z%l!<%7%g%s!#(B
     * SDO $B$,%5!<%S%9$r0l$D$b=jM-$7$F$$$J$$>l9g$K$O!"6u$N%j%9%H$rJV$9!#(B
     * $B$3$N%*%Z%l!<%7%g%s$O0J2<$N7?$NNc30$rH/@8$5$;$k!#(B
     * 
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
     * @return    SDO $B$,Ds6!$9$kA4$F$N(B Service $B$N(B ServiceProfile$B!#(B
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
    virtual ServiceProfileList* get_service_profiles()
      throw (InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] $BFCDj$N(BServiceProfile$B$N<hF@(B 
     *
     * $B0z?t(B "id" $B$G;XDj$5$l$?L>A0$N%5!<%S%9$N(B ServiceProfile $B$rJV$9!#(B
     * 
     * @param     id SDO Service $B$N(B ServiceProfile $B$K4XO"IU$1$i$l$?<1JL;R!#(B
     * @return    $B;XDj$5$l$?(B SDO Service $B$N(B ServiceProfile$B!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
    virtual ServiceProfile* get_service_profile(const char* id)
      throw (InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] $B;XDj$5$l$?(B SDO Service $B$N<hF@(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O0z?t(B "id" $B$G;XDj$5$l$?L>A0$K$h$C$F6hJL$5$l$k(B
     * SDO $B$N(B Service $B$X$N%*%V%8%'%/%H;2>H$rJV$9!#(B SDO $B$K$h$jDs6!$5$l$k(B
     * Service $B$O$=$l$>$l0l0U$N<1JL;R$K$h$j6hJL$5$l$k!#(B
     *
     * @param id SDO Service $B$K4XO"IU$1$i$l$?<1JL;R!#(B
     * @return $BMW5a$5$l$?(B SDO Service $B$X$N;2>H!#(B
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
    virtual SDOService_ptr get_sdo_service(const char* id)
      throw (InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Configuration $B%*%V%8%'%/%H$N<hF@(B 
     *
     * $B$3$N%*%Z%l!<%7%g%s$O(B Configuration interface $B$X$N;2>H$rJV$9!#(B
     * Configuration interface $B$O3F(B SDO $B$r4IM}$9$k$?$a$N%$%s%?!<%U%'!<%9$N(B
     * $B$R$H$D$G$"$k!#$3$N%$%s%?!<%U%'!<%9$O(B DeviceProfile, ServiceProfile,
     * Organization $B$GDj5A$5$l$?(B SDO $B$NB0@-CM$r@_Dj$9$k$?$a$K;HMQ$5$l$k!#(B
     * Configuration $B%$%s%?!<%U%'!<%9$N>\:Y$K$D$$$F$O!"(BOMG SDO specification
     * $B$N(B 2.3.5$B@a(B, p.2-24 $B$r;2>H$N$3$H!#(B
     *
     * @return SDO $B$N(B Configuration $B%$%s%?!<%U%'!<%9$X$N;2>H(B
     * @exception InterfaceNotImplemented SDO$B$O(BConfiguration$B%$%s%?!<%U%'!<%9$r(B
     *                                    $B;}$?$J$$!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
    virtual Configuration_ptr get_configuration()
      throw (InterfaceNotImplemented, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Monitoring $B%*%V%8%'%/%H$N<hF@(B 
     *
     * $B$3$N%*%Z%l!<%7%g%s$O(B Monitoring interface $B$X$N;2>H$rJV$9!#(B
     * Monitoring interface $B$O(B SDO $B$,4IM}$9$k%$%s%?!<%U%'!<%9$N0l$D$G$"$k!#(B
     * $B$3$N%$%s%?!<%U%'!<%9$O(B SDO $B$N%W%m%Q%F%#$r%b%K%?%j%s%0$9$k$?$a$K(B
     * $B;HMQ$5$l$k!#(B
     * Monitoring interface $B$N>\:Y$K$D$$$F$O(B OMG SDO specification $B$N(B
     * 2.3.7$B@a(B "Monitoring Interface" p.2-35 $B$r;2>H$N$3$H!#(B
     *
     * @return SDO $B$N(B Monitoring interface $B$X$N;2>H(B
     * @exception InterfaceNotImplemented SDO$B$O(BConfiguration$B%$%s%?!<%U%'!<%9$r(B
     *                                    $B;}$?$J$$!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
    virtual Monitoring_ptr get_monitoring()
      throw (InterfaceNotImplemented, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization $B%j%9%H$N<hF@(B 
     *
     * SDO $B$O(B0$B8D0J>e$N(B Organization ($BAH?%(B)$B$K=jB0$9$k$3$H$,$G$-$k!#(B $B$b$7(B SDO $B$,(B
     * 1$B8D0J>e$N(B Organization $B$K=jB0$7$F$$$k>l9g!"$3$N%*%Z%l!<%7%g%s$O=jB0$9$k(B
     * Organization $B$N%j%9%H$rJV$9!#(BSDO $B$,(B $B$I$N(B Organization $B$K$b=jB0$7$F$$$J$$(B
     * $B>l9g$K$O!"6u$N%j%9%H$,JV$5$l$k!#(B
     *
     * @return SDO $B$,=jB0$9$k(B Organization $B$N%j%9%H!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
    virtual OrganizationList* get_organizations()
      throw (NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO Status $B%j%9%H$N<hF@(B 
     *
     * $B$3$N%*%Z%l!<%7%g%s$O(B SDO $B$N%9%F!<%?%9$rI=$9(B NVList $B$rJV$9!#(B
     *
     * @return SDO $B$N%9%F!<%?%9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
    virtual NVList* get_status_list()
      throw (NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO Status $B$N<hF@(B 
     *
     * This operation returns the value of the specified status parameter.
     * 
     * @param name SDO $B$N%9%F!<%?%9$rDj5A$9$k%Q%i%a!<%?!#(B
     * @return $B;XDj$5$l$?%Q%i%a!<%?$N%9%F!<%?%9CM!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "name" $B$,(B null $B$"$k$$$OB8:_$7$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
      throw (InvalidParameter, NotAvailable, InternalError);
    
    // end of CORBA interface definition
    //============================================================


    //============================================================
    //
    // <<< Local interfaces >>>
    //
    //============================================================

    void setSdoId(const char* sdo_id);
    void setSdoType(const char* sdo_type);
    void setDeviceProfile(const DeviceProfile& device_profile);
    void setServiceProfiles(const ServiceProfileList& service_profile);
    void addServiceProfile(const ServiceProfile& service_profile);
    
    
  protected:
    // Partial specialization
    template <class T, class X>
    class SeqEx
      : public SequenceEx <T, X, ACE_Thread_Mutex> {};
    
    struct SdoId
    {
      CORBA::String_var _id;
      ACE_Thread_Mutex _mutex;
    };

    struct SdoType
    {
      CORBA::String_var _type;
      ACE_Thread_Mutex _mutex;
    };

    SdoId m_SdoId;
    SdoType m_SdoType;


    Configuration_impl* m_pConfig;


    Configuration_var m_varConfiguration;
    Monitoring_var m_varMonitoring;
    SeqEx<NVList, NameValue> m_Status;
    
    // functor for ServiceProfile
    struct nv_name
    {
      nv_name(const char* id) : m_name(id) {};
      bool operator()(const NameValue& v)
      {
	std::string name(v.name);
	return m_name == name;
      }
      const std::string m_name;
    };


    PortableServer::ObjectId_var m_varConfigId;
    SDOPackage::Configuration_var m_varConfigObj;

    PortableServer::ObjectId_var m_varOrgId;
    SDOPackage::Configuration_var m_varOrgObj;

  };

}; // namespace SDOPackage

#endif // SdoSystemElement_h
