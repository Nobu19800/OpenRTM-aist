// -*- C++ -*-
/*!
 * @file CorbaObjManager.h
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
 * $Id: CorbaObjectManager.h,v 1.2.4.1 2007-12-31 03:08:02 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/11/04 19:57:05  n-ando
 * Kanji-code was converted into EUC.
 *
 * Revision 1.1  2006/11/04 19:54:48  n-ando
 * CORBA object activation class was created.
 *
 */

#ifndef CorbaObjectManager_h
#define CorbaObjectManager_h

#include <rtm/RTC.h>
#include <rtm/RTObject.h>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RT����ݡ��ͥ��
 *
 * @else
 *
 * @namespace RTC
 *
 * @endif
 */
namespace RTC
{
  /*!
   * @if jp
   * @class CorbaObjectManager
   * @brief CORBA ���֥������Ȥ򥢥��ƥ��ֲ����󥢥��ƥ��ֲ�����
   *
   * RTObject�Υ����ƥ��ֲ����󥢥��ƥ��ֲ���Ԥ����饹�Ǥ��롣
   * �ݻ����Ƥ���ORB��POA���Ѥ��� CORBA ���֥������ȤΥ����ƥ��ֲ���
   * �󥢥��ƥ��ֲ���Ԥ���
   *
   * @since 0.4.0
   *
   * @else
   * @class CorbaObjectManager
   * @brief Activate and deactivate CORBA objects
   * @endif
   */
  class CorbaObjectManager
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * @param orb ORB
     * @param poa POA
     *
     * @else
     *
     * @brief Consructor
     *
     * @param orb ORB
     *
     * @endif
     */
    CorbaObjectManager(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * @else
     * 
     * @brief virtual destructor
     * 
     * @endif
     */
    virtual ~CorbaObjectManager() {};
    
    /*!
     * @if jp
     * @brief CORBA ���֥������Ȥ򥢥��ƥ��ֲ�����
     *
     * ���ꤵ�줿RTObject�� CORBA ���֥������ȤȤ��ƥ����ƥ��ֲ�����
     * ���֥������ȥ�ե���󥹤����ꤹ�롣
     *
     * @param comp �����ƥ��ֲ��о�RTObject
     *
     * @else
     * @brief Activate CORBA object
     * @endif
     */
    void activate(RTObject_impl* comp);
    
    /*!
     * @if jp
     * @brief CORBA ���֥������Ȥ��󥢥��ƥ��ֲ�����
     *
     * ���ꤵ�줿RTObject���󥢥��ƥ��ֲ���Ԥ�
     *
     * @param comp �󥢥��ƥ��ֲ��о�RTObject
     *
     * @else
     * @brief Deactivate CORBA object
     * @endif
     */
    void deactivate(RTObject_impl* comp);
    
  private:
    CORBA::ORB_var m_pORB;
    PortableServer::POA_var m_pPOA;
  };
}; // namespace RTC

#endif // CoabrObjectManager
