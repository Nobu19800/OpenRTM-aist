// -*- C++ -*-
/*!
 * @file SdoService.h
 * @brief SDO Service administration class
 * @date $Date: 2007-12-31 03:08:07 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

/*!
 * @if jp
 * @namespace SDOPackage
 *
 * @brief SDO �ѥå�����
 *
 * @else
 *
 * @namespace SDOPackage
 *
 * @brief SDO package
 *
 * @endif
 */
namespace SDOPackage
{
  /*!
   * @if jp
   *
   * @class SDOServiceProfile
   * @brief SDO Service Profile���饹
   *
   * SDO Service Profile �� SDO Service �ξ�����ݻ����뤿��Υ��饹�Ǥ��롣
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class SDOServiceProfile
   * @brief SDO Service Profile class
   *
   * SDO Service Profile is a class to hold information of SDO Service.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class SDOServiceProfile
    : public SDOpackage::ServiceProfile
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param id Service ��ID(�ǥե������:"")
     * @param type Service �η�(�ǥե������:"")
     *
     * @else
     *
     * @brief Constructor
     * 
     * Constructor
     *
     * @param id ID of the Service(The default value:"")
     * @param type Type of the Service(The default value:"")
     *
     * @endif
     */
    SDOService(char* id = "", char type = "")
    {
    }
    
    /*!
     * @if jp
     *
     * @brief Service Profile���������
     * 
     * Service Profile���������
     * 
     * @return Service Profile
     * 
     * @else
     *
     * @brief Get Service Profile
     * 
     * Get Service Profile.
     * 
     * @return Service Profile
     * 
     * @endif
     */
    inline const SDOPackage::Service getProfile()
    {
      return *this;
    }
    
    /*!
     * @if jp
     * @brief ServiceProfile.id �򥻥åȤ���
     * 
     * SDO Service ��ID�򥻥åȤ���
     * 
     * @param id Service ��ID
     * 
     * @else
     * @brief Set ServiceProfile.id
     * 
     * Set ID of SDO Service.
     * 
     * @param id ID of the Service
     * 
     * @endif
     */
    inline void setName(char* id)
    {
      // this->name is CORBA::string member of the struct
      this->id = id;
    }
    
    /*!
     * @if jp
     * @brief ServiceProfile.id �����
     * 
     * SDO Service ��ID���������
     * 
     * @return Service ��ID
     * 
     * @else
     * @brief Get ServiceProfile.id
     * 
     * Get ID of SDO Service.
     * 
     * @return ID of the Service
     * 
     * @endif
     */
    inline const char* getName() const
    {
      return this->id;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.interfaceType �򥻥åȤ���
     * 
     * SDO Service ��interfaceType�򥻥åȤ���
     * 
     * @param interfaceType Service ��interfaceType
     * 
     * @else
     * @brief Set SDOServiceProfile.interfaceType
     * 
     * Set interfaceType of SDO Service.
     * 
     * @param interfaceType interfaceType of the Service
     * 
     * @endif
     */
    inline void setInterfaceType(char* interfaceType)
    {
      this->interfaceType = interfaceType;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.interfaceType ���������
     * 
     * SDO Service ��interfaceType���������
     * 
     * @return Service ��interfaceType
     * 
     * @else
     * @brief Get SDOServiceProfile.interfaceType
     * 
     * Get interfaceType of SDO Service
     * 
     * @return interfaceType of the Service
     * 
     * @endif
     */
    inline const char* getInterfaceType() const
    {
      return this->interfaceType;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.idlDefinition �򥻥åȤ���
     * 
     * SDO Service ��idlDefinition�򥻥åȤ���
     * 
     * @param idlDefinition Service ��idlDefinition
     * 
     * @else
     * @brief Set SDOServiceProfile.idlDefnition
     * 
     * Set idlDefinition of SDO Service
     * 
     * @param idlDefinition idlDefinition of the Service
     * 
     * @endif
     */
    inline void setIdlDefinition(char* idlDefinition)
    {
      this->idlDefinition = idlDefinition;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.idlDefinition ���������
     * 
     * SDO Service ��idlDefinition���������
     * 
     * @return Service ��idlDefinition
     * 
     * @else
     * @brief Get SDO ServiceProfile.idlDefnition
     * 
     * Get idlDefinition of SDO Service
     * 
     * @return idlDefinition of the Service
     * 
     * @endif
     */
    inline const char* getIdlDefinition() const
    {
      return this->idlDefinition;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.properties �򥻥åȤ���
     * 
     * SDO Service ��properties�򥻥åȤ���
     * 
     * @param properties Service ��properties
     * 
     * @else
     * @brief Set SDO ServiceProfile.properties
     * 
     * Set properties of SDO Service
     * 
     * @param properties Properties of the Service
     * 
     * @endif
     */
    inline void setProperties(NVList properties)
    {
      this->properties = properties;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.properties ���������
     * 
     * SDO Service ��properties���������
     * 
     * @return Service ��properties
     * 
     * @else
     * @brief Get SDO ServiceProfile.properties
     * 
     * Get properties of SDO Service
     * 
     * @return Properties of the Service
     * 
     * @endif
     */
    inline const NVList getProperties() const
    {
      return this->properties;
    }
    
    //	bool addProperty(char* name, CORBA::Any data);
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.serviceRef �򥻥åȤ���
     * 
     * SDO Service ��serviceRef�򥻥åȤ���
     * 
     * @param serviceRef Service�ؤλ���
     * 
     * @else
     * @brief Set SDO ServiceProfile.serviceRef
     * 
     * Set serviceRef of SDO Service.
     * 
     * @param serviceRef The reference to Service
     * 
     * @endif
     */
    inline void setServiceRef(RTCService_ptr serviceRef)
    {
      this->serviceRef = serviceRef;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.serviceRef ���������
     * 
     * SDO Service �ؤλ��Ȥ��������
     * 
     * @return Service�ؤλ���
     * 
     * @else
     * @brief Get SDO ServiceProfile.serviceRef
     * 
     * Get the reference to SDO Service
     * 
     * @return The reference to Service
     * 
     * @endif
     */
    RTCService_ptr getServiceRef() const
    {
      return this->serviceRef;
    }
  };
};
