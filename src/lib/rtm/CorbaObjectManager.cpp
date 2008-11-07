// -*- C++ -*-
/*!
 * @file CorbaObjectManager.cpp
 * @brief CORBA Object manager class
 * @date $Date: 2007-12-31 03:08:02 $
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

#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4290 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#endif // WIN32

#include <rtm/CorbaObjectManager.h>

#ifdef WIN32
#pragma warning( pop )
#endif // WIN32

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  CorbaObjectManager::CorbaObjectManager(CORBA::ORB_ptr orb,
					 PortableServer::POA_ptr poa)
    : m_pORB(orb), m_pPOA(poa)
  {
  }
  
  /*!
   * @if jp
   * @brief CORBA ���֥������Ȥ򥢥��ƥ��ֲ�����
   * @else
   * @brief Activate the CORBA object
   * @endif
   */
  void CorbaObjectManager::activate(RTObject_impl* comp)
  {
    PortableServer::ObjectId_var id;
    id = m_pPOA->activate_object(comp);
    comp->setObjRef(RTObject::_narrow(m_pPOA->id_to_reference(id)));
    
  }
  
  /*!
   * @if jp
   * @brief CORBA ���֥������Ȥ��󥢥��ƥ��ֲ�����
   * @else
   * @brief Deactivate the CORBA object
   * @endif
   */
  void CorbaObjectManager::deactivate(RTObject_impl* comp)
  {
    PortableServer::ObjectId_var id;
    id = m_pPOA->servant_to_id(comp);
    m_pPOA->deactivate_object(id);
  }
  
}; // namespace RTC
