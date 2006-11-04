// -*- C++ -*-
/*!
 * @file CorbaObjectManager.h
 * @brief CORBA Object manager class
 * @date $Date: 2006-11-04 19:54:40 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: CorbaObjectManager.cpp,v 1.1 2006-11-04 19:54:40 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <rtm/CorbaObjectManager.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief $B%3%s%9%H%i%/%?(B
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
   * @brief CORBA $B%*%V%8%'%/%H$r%"%/%F%#%V2=$9$k(B
   * @else
   * @brief Activate CORBA object
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
   * @brief CORBA $B%*%V%8%'%/%H$rHs%"%/%F%#%V2=$9$k(B
   * @else
   * @brief Deactivate CORBA object
   * @endif
   */
  void CorbaObjectManager::deactivate(RTObject_impl* comp)
  {
    PortableServer::ObjectId_var id;
    id = m_pPOA->servant_to_id(comp);
    m_pPOA->deactivate_object(id);
  }
  
}; // namespace RTC
