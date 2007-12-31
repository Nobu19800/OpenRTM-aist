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
 * $Id: SdoService.h,v 1.2.4.1 2007-12-31 03:08:07 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/10/17 10:12:51  n-ando
 * Small fixes.
 *
 * Revision 1.1  2006/09/11 18:48:08  n-ando
 * The first commit.
 *
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
     * @brief Setting ServiceProfile.id
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
     * @brief Getting ServiceProfile.id
     * @endif
     */
    inline const char* getName() const
    {
      return this->id;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.interfaceType �򥻥åȤ���
     * 
     * SDO Service ��interfaceType�򥻥åȤ���
     * 
     * @param interfaceType Service ��interfaceType
     * 
     * @else
     * @brief Setting RTCServiceProfile.interfaceType
     * @endif
     */
    inline void setInterfaceType(char* interfaceType)
    {
      this->interfaceType = interfaceType;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.interfaceType ���������
     * 
     * SDO Service ��interfaceType���������
     * 
     * @return Service ��interfaceType
     * 
     * @else
     * @brief Getting RTCServiceProfile.interfaceType
     * @endif
     */
    inline const char* getInterfaceType() const
    {
      return this->interfaceType;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.idlDefinition �򥻥åȤ���
     * 
     * SDO Service ��idlDefinition�򥻥åȤ���
     * 
     * @param idlDefinition Service ��idlDefinition
     * 
     * @else
     * @brief Setting RTCServiceProfile.idlDefnition
     * @endif
     */
    inline void setIdlDefinition(char* idlDefinition)
    {
      this->idlDefinition = idlDefinition;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.idlDefinition ���������
     * 
     * SDO Service ��idlDefinition���������
     * 
     * @return Service ��idlDefinition
     * 
     * @else
     * @brief Getting RTCServiceProfile.idlDefnition
     * @endif
     */
    inline const char* getIdlDefinition() const
    {
      return this->idlDefinition;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.properties �򥻥åȤ���
     * 
     * SDO Service ��properties�򥻥åȤ���
     * 
     * @param properties Service ��properties
     * 
     * @else
     * @brief Setting RTCServiceProfile.properties
     * @endif
     */
    inline void setProperties(NVList properties)
    {
      this->properties = properties;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.properties ���������
     * 
     * SDO Service ��properties���������
     * 
     * @return Service ��properties
     * 
     * @else
     * @brief Getting RTCServiceProfile.properties
     * @endif
     */
    inline const NVList getProperties() const
    {
      return this->properties;
    }
    
    //	bool addProperty(char* name, CORBA::Any data);
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.serviceRef �򥻥åȤ���
     * 
     * SDO Service ��serviceRef�򥻥åȤ���
     * 
     * @param serviceRef Service�ؤλ���
     * 
     * @else
     * @brief Setting RTCServiceProfile.serviceRef
     * @endif
     */
    inline void setServiceRef(RTCService_ptr serviceRef)
    {
      this->serviceRef = serviceRef;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.serviceRef ���������
     * 
     * SDO Service �ؤλ��Ȥ��������
     * 
     * @return Service�ؤλ���
     * 
     * @else
     * @brief Getting RTCServiceProfile.serviceRef
     * @endif
     */
    RTCService_ptr getServiceRef() const
    {
      return this->serviceRef;
    }
  };
};
