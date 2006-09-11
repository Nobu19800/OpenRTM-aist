// -*- C++ -*-
/*!
 * @file SdoConfiguration.h
 * @brief RT component base class
 * @date $Date: 2006-09-11 18:14:01 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.h,v 1.1 2006-09-11 18:14:01 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef SdoConfiguration_h
#define SdoConfiguration_h

#include <ace/Guard_T.h>
#include <ace/Thread_Mutex.h>
#include <ace/Recursive_Thread_Mutex.h>

// CORBA header include
#include "rtm/RTC.h"
#include "rtm/Util.h"

// local includes
#include "rtm/idl/SDOPackageSkel.h"

namespace SDOPackage
{
  /*!
   * @if jp
   *
   * @class Configuration_impl
   * @brief SDO Configuration $B<BAu%/%i%9(B
   *
   * Configuration interface $B$O(B Resource Data Model $B$GDj5A$5$l$?%G!<%?$N(B
   * $BDI2C!":o=|Ey$NA`:n$r9T$&$?$a$N%$%s%?!<%U%'!<%9$G$"$k!#(B
   * DeviceProfile, ServiceProfile, ConfigurationProfile $B$*$h$S(B Organization
   * $B$NJQ99$r9T$&$?$a$N%*%Z%l!<%7%g%s$rHw$($F$$$k!#(BSDO $B$N;EMM$G$O%"%/%;%9@)8f(B
   * $B$*$h$S%;%-%e%j%F%#$K4X$9$k>\:Y$K$D$$$F$O5,Dj$7$F$$$J$$!#(B
   * 
   * $BJ#?t$N@_Dj(B (Configuration) $B$rJ];}$9$k$3$H$K$h$j!"MF0W$+$DAGAa$/$"$k@_Dj(B
   * $B$rH?1G$5$;$k$3$H$,$G$-$k!#;vA0$KDj5A$5$l$?J#?t$N@_Dj$r(B ConfigurationSets
   * $B$*$h$S(B configuration profile $B$H$7$FJ];}$9$k$3$H$,$G$-$k!#$R$H$D$N(B
   * ConfigurationSet $B$OFCDj$N@_Dj$K4XO"IU$1$i$l$?A4%W%m%Q%F%#CM$N%j%9%H$r!"(B
   * $B%f%K!<%/(BID$B!">\:Y$H$H$b$K;}$C$F$$$k!#$3$l$K$h$j!"3F@_Dj9`L\$N>\:Y$r5-=R$7(B
   * $B6hJL$9$k$3$H$,$G$-$k!#(BConfiguration interface $B$N%*%Z%l!<%7%g%s$O$3$l$i(B
   * ConfiguratioinSets $B$N4IM}$r;Y1g$9$k!#(B
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
    Configuration_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    virtual ~Configuration_impl(){};

    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO $B$N(B DeviceProfile $B$r%;%C%H$9$k(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O(B SDO $B$N(B DeviceProfile $B$r%;%C%H$9$k!#(BSDO $B$,(B
     * DeviceProfile $B$rJ];}$7$F$$$k>l9g$O?7$?$J(B DeviceProfile $B$r@8@.$7!"(B
     * DeviceProfile $B$r$9$G$KJ];}$7$F$$$k>l9g$O4{B8$N$b$N$HCV$-49$($k!#(B
     *
     * @param dProfile SDO $B$K4XO"IU$1$i$l$k(B DeviceProfile$B!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "dProfile" $B$,(B null $B$G$"$k!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] SDO $B$N(B ServiceProfile $B$N%;%C%H(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O$3$N(B Configuration interface $B$r=jM-$9$kBP>](B SDO $B$N(B
     * ServiceProfile $B$r@_Dj$9$k!#$b$70z?t$N(B ServiceProfile $B$N(B id $B$,6u$G$"$l$P(B
     * $B?7$7$$(B ID $B$,@8@.$5$l$=$N(B ServiceProfile $B$r3JG<$9$k!#$b$7(B id $B$,6u$G(B
     * $B$J$1$l$P!"(BSDO $B$OF1$8(B id $B$r;}$D(B ServiceProfile $B$r8!:w$9$k!#(B
     * $BF1$8(B id $B$,B8:_$7$J$1$l$P$3$N(B ServiceProfile $B$rDI2C$7!"(Bid $B$,B8:_$9$l$P(B
     * $B>e=q$-$r$9$k!#(B
     *
     * @param sProfile $BDI2C$9$k(B ServiceProfile
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "sProfile" $B$,(B null$B$G$"$k!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] Organization $B$NDI2C(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O(B Organization object $B$N%j%U%!%l%s%9$rDI2C$9$k!#(B
     *
     * @param org $BDI2C$9$k(B Organization
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "organization" $B$,(B null $B$G$"$k!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @exception InvalidParameter The argument $B!H(Borganization$B!I(B is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean add_organization(Organization_ptr org)
      throw (InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ServiceProfile $B$N:o=|(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O$3$N(B Configuration interface $B$r;}$D(B SDO $B$N(B
     * Service $B$N(B ServiceProfile $B$r:o=|$9$k!#:o=|$9$k(B ServiceProfile
     * $B$O0z?t$K$h$j;XDj$5$l$k!#(B
     *
     * @param id $B:o=|$9$k(B ServcieProfile $B$N(B serviceID$B!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "id" $B$,(B null $B$G$"$k!#$b$7$/$O(B "id" $B$K(B
     *                             $B4XO"IU$1$i$l$?(B ServiceProfile $B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] Organization $B$N;2>H$N:o=|(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O(B Organization $B$N;2>H$r:o=|$9$k!#(B
     *
     * @param organization_id $B:o=|$9$k(B Organization $B$N0l0U$J(B id$B!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter 
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] $B@_Dj%Q%i%a!<%?$N%j%9%H$N<hF@(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O(B configuration parameter $B$N%j%9%H$rJV$9!#(B
     * SDO $B$,@_Dj2DG=$J%Q%i%a!<%?$r;}$?$J$1$l$P6u$N%j%9%H$rJV$9!#(B
     *
     * @return $B@_Dj$rFCD'IU$1$k%Q%i%a!<%?Dj5A$N%j%9%H!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] Configuration parameter $B$NCM$N%j%9%H$N<hF@(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O(B configuration $B%Q%i%a!<%?$*$h$SCM$rJV$9!#(B
     *
     * @return $BA4$F$N(B configuration $B%Q%i%a!<%?$HCM$N%j%9%H!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] Configuration parameter $B$NCM$N<hF@(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O0z?t(B "name" $B$G;XDj$5$l$?%Q%i%a!<%?CM$rJV$9!#(B
     *
     * @param name $BCM$rMW5a$9$k%Q%i%a!<%?$NL>A0!#(B
     * @return $B;XDj$5$l$?%Q%i%a!<%?$NCM!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] Configuration $B%Q%i%a!<%?$NJQ99(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O(B "name" $B$G;XDj$7$?%Q%i%a!<%?$NCM$r(B "value" $B$K(B
     * $BJQ99$9$k!#(B
     *
     * @param name $BJQ99$7$?$$%Q%i%a!<%?$NL>A0!#(B
     * @param value $BJQ99$7$?$$%Q%i%a!<%?$NCM!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+$rJV$9!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] ConfigurationSet $B%j%9%H$N<hF@(B 
     *
     * $B$3$N%*%Z%l!<%7%g%s$O(B ConfigurationProfile $B$,;}$D(B ConfigurationSet $B$N(B
     * $B%j%9%H$rJV$9!#(B SDO $B$,(B ConfigurationSet $B$r;}$?$J$1$l$P6u$N%j%9%H$rJV$9!#(B
     *
     * @return $BJ];}$7$F$$$k(B ConfigurationSet $B$N%j%9%H$N8=:_CM!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
     * @else
     *
     * @brief [CORBA interface] Getting list of ConfigurationSet
     *
     * This operation returns a list of ConfigurationSets that the
     * ConfigurationProfile has. An empty list is returned if the SDO does not
     * have any ConfigurationSets.
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
     * @brief [CORBA interface] ConfigurationSet $B$N<hF@(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O0z?t$G;XDj$5$l$?(B ConfigurationSet $B$N(B ID $B$K4XO"(B
     * $BIU$1$i$l$?(B ConfigurationSet $B$rJV$9!#(B
     *
     * @param config_id ConfigurationSet $B$N<1JL;R!#(B
     * @return $B0z?t$K$h$j;XDj$5$l$?(B ConfigurationSet$B!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter "config_id" $B$,(B null $B$+!";XDj$5$l$?(B
     *            ConfigurationSet $B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] ConfigurationSet $B$r%;%C%H$9$k(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$O;XDj$5$l$?(B id $B$N(B ConfigurationSet $B$r99?7$9$k!#(B
     *
     * @param configu_id $BJQ99$9$k(B ConfigurationSet $B$N(B ID$B!#(B
     * @param configuration_set $BJQ99$9$k(B ConfigurationSet $B$=$N$b$N!#(B
     * @return ConfigurationSet $B$,@5>o$K99?7$G$-$?>l9g$O(B true$B!#(B
     *         $B$=$&$G$J$1$l$P(B false $B$rJV$9!#(B
     * @exception InvalidParameter config_id $B$,(B null $B$+(B ConfigurationSet
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
     * @else
     *
     * @brief [CORBA interface] Set ConfigurationSet
     *
     * This operation modifies the specified ConfigurationSet of an SDO.
     *
     * $B"((B $B%Q%i%a!<%?$N?t$,(B spec $B$H(B IDL $B$G0[$J$k!*!*!*(B
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
     * @brief [CORBA interface] $B%"%/%F%#%V$J(B ConfigurationSet $B$r<hF@$9$k(B
     *
     * $B$3$N%*%Z%l!<%7%g%s$OEv3:(BSDO$B$N8=:_%"%/%F%#%V$J(B ConfigurationSet $B$rJV$9!#(B
     * ($B$b$7(BSDO$B$N8=:_$N@_Dj$,M=$aDj5A$5$l$?(B ConfigurationSet $B$K$h$j@_Dj$5$l$F(B
     * $B$$$k$J$i$P!#(B)
     * ConfigurationSet $B$O0J2<$N>l9g$K$O%"%/%F%#%V$G$O$J$$$b$N$H$_$J$5$l$k!#(B
     *
     * - $B8=:_$N@_Dj$,M=$aDj5A$5$l$?(B ConfigurationSet $B$K$h$j%;%C%H$5$l$F$$$J$$!"(B
     * - SDO $B$N@_Dj$,%"%/%F%#%V$K$J$C$?8e$KJQ99$5$l$?!"(B
     * - SDO $B$r@_Dj$9$k(B ConfigurationSet $B$,JQ99$5$l$?!"(B
     * 
     * $B$3$l$i$N>l9g$K$O!"6u$N(B ConfigurationSet $B$,JV$5$l$k!#(B
     *
     * @return $B8=:_%"%/%F%#%V$J(B ConfigurationSet$B!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] ConfigurationSet $B$rDI2C$9$k(B
     *
     * ConfigurationProfile $B$K(B ConfigurationSet $B$rDI2C$9$k%*%Z%l!<%7%g%s!#(B
     *
     * @param configuration_set $BDI2C$5$l$k(B ConfigurationSet$B!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] ConfigurationSet $B$r:o=|$9$k(B
     *
     * ConfigurationProfile $B$+$i(B ConfigurationSet $B$r:o=|$9$k!#(B
     *
     * @param configu_id $B:o=|$9$k(B ConfigurationSet $B$N(B id$B!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "configurationSetID" $B$,(B null $B$G$"$k!"(B
     *            $B$b$7$/$O!"0z?t$G;XDj$5$l$?(B ConfigurationSet $B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
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
     * @brief [CORBA interface] ConfigurationSet $B$N%"%/%F%#%V2=(B
     *
     * ConfigurationProfile $B$K3JG<$5$l$?(B ConfigurationSet $B$N$&$A0l$D$r(B
     * $B%"%/%F%#%V$K$9$k!#(B
     *
     * @param config_id $B%"%/%F%#%V2=$9$k(B ConfigurationSet $B$N(B id$B!#(B
     * @return $B%*%Z%l!<%7%g%s$,@.8y$7$?$+$I$&$+!#(B
     * @exception SDONotExists $B%?!<%2%C%H$N(BSDO$B$,B8:_$7$J$$!#(B
     * @exception InvalidParameter $B0z?t(B "config_id" $B$,(B null $B$G$"$k!"$b$7$/$O(B
     *            $B0z?t$G;XDj$5$l$?(B ConfigurationSet $B$,B8:_$7$J$$!#(B
     * @exception NotAvailable SDO$B$OB8:_$9$k$,1~Ez$,$J$$!#(B
     * @exception InternalError $BFbItE*%(%i!<$,H/@8$7$?!#(B
     * @else
     *
     * @brief [CORBA interface] Activate ConfigurationSet
     *
     * This operation activates one of the stored ConfigurationSets in the
     * ConfigurationProfile.
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

    const DeviceProfile& getDeviceProfile()
    {
      //      return reinterpret_cast<DeviceProfile&>(m_deviceProfile);
      return m_deviceProfile.data;
    }

    const ServiceProfileList& getServiceProfiles()
    {
      return m_serviceProfiles;
    }

    const ServiceProfile& getServiceProfile(const char* id)
    {
      return m_serviceProfiles.find(service_id(id));
    }

    const OrganizationList& getOrganizations()
    {
      return m_organizations;
    }

  protected:
    // Partial specialization
    template <class T, class X>
    class SeqEx
      : public SequenceEx <T, X, ACE_Thread_Mutex> {};

    /*!
     * @if jp
     * @brief Lock $BIU$-(B SDO DeviceProfile
     * @else
     * @brief SDO DeviceProfile with mutex lock
     * @endif
     */
    LockedStruct<DeviceProfile> m_deviceProfile;

    /*!
     * @if jp
     * @brief SDO ServiceProfileList
     * @else
     * @brief SDO ServiceProfileList
     * @endif
     */
    SeqEx<ServiceProfileList, ServiceProfile>     m_serviceProfiles;

    /*!
     * @if jp
     * @brief SDO ParameterList
     * @else
     * @brief SDO ParameterList
     * @endif
     */
    SeqEx<ParameterList, Parameter>               m_parameters;

    /*!
     * @if jp
     * @brief SDO ConfigurationSetList
     * @else
     * @brief SDO ConfigurationSetList
     * @endif
     */
    SeqEx<ConfigurationSetList, ConfigurationSet> m_configurations;

    /*!
     * @if jp
     * @brief SDO OrganizationList
     * @else
     * @brief SDO OrganizationList
     * @endif
     */
    SeqEx<OrganizationList, Organization_ptr>     m_organizations;

    /*!
     * @if jp
     * @brief $B%"%/%F%#%V$J(B ConfigurationSet i
     * @else
     * @brief Active ConfigurationSet id
     * @endif
     */
    std::string m_activeConfigurationSet;



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
      
    CORBA::ORB_var m_varORB;
    PortableServer::POA_var m_varPOA;

  };

}; // namespace SDOPackage

#endif // SdoConfiguration_h
