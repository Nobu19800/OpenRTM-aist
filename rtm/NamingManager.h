// -*- C++ -*-
/*!
 * @file NamingManager.h
 * @brief naming Service helper class
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NamingManager.h,v 1.3.2.1 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/26 15:37:48  n-ando
 * getObjects() function was added.
 *
 * Revision 1.2  2007/04/13 18:08:42  n-ando
 * Some changes for NameServers rebinding and objects rebinding.
 *
 * Revision 1.1  2006/11/04 21:11:44  n-ando
 * NamingManager was introduced to support multiple name server.
 *
 */
#ifndef NamingManager_h
#define NamingManager_h

#include <rtm/RTC.h>

#include <ace/Task.h>
#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/SystemLogger.h>

namespace RTC
{
  class Manager;
  /*!
   * @if jp
   *
   * @brief NamingService ��������ݥ��饹
   *
   * NamingServer ��������ݥ��󥿡��ե��������饹��
   * ��ݴ������饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
   * - bindObject() : ���ꤷ�����֥������Ȥ�NamingService�ؤΥХ����
   * - unbindObject() : ���ꤷ�����֥������Ȥ�NamingService����Υ���Х����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  class NamingBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * @else
     *
     * @endif
     */
    NamingBase() {};
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief destructor
     *
     * @endif
     */
    virtual ~NamingBase() {};
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�����֥������Ȥ�NamingService�إХ���ɤ����貾�۴ؿ�
     *
     * @param name �Х���ɻ���̾��
     * @param rtobj �Х�����оݥ��֥�������
     *
     * @else
     *
     * @endif
     */
    virtual void bindObject(const char* name, const RTObject_impl* rtobj) = 0;
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�����֥������Ȥ�NamingService���饢��Х���ɤ��뤿���
     *        ��貾�۴ؿ�
     *
     * @param name ����Х�����оݥ��֥�������
     *
     * @else
     *
     * @endif
     */
    virtual void unbindObject(const char* name) = 0;
  };
  
  /*!
   * @if jp
   *
   * @brief CORBA �� NamingServer �������饹
   *
   * CORBA �� NamingServer �����ѥ��饹��
   * CORBA ����ݡ��ͥ�Ȥ�NamingService�ؤ���Ͽ������ʤɤ�������롣
   *
   * @since 0.4.0
   *
   * @else
   *
   * @biref ModuleManager class
   *
   * @endif
   */
  class NamingOnCorba
    : public virtual NamingBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param orb ORB
     * @param names NamingServer ̾��
     *
     * @else
     *
     * @endif
     */
    NamingOnCorba(CORBA::ORB_ptr orb, const char* names)
      : m_cosnaming(orb, names)
    {};
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief destructor
     *
     * @endif
     */
    virtual ~NamingOnCorba(){};
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�� CORBA ���֥������Ȥ�NamingService�إХ����
     * 
     * ���ꤷ�� CORBA ���֥������Ȥ���ꤷ��̾�Τ� CORBA NamingService ��
     * �Х���ɤ��롣
     * 
     * @param name �Х���ɻ���̾��
     * @param rtobj �Х�����оݥ��֥�������
     *
     * @else
     *
     * @endif
     */
    virtual void bindObject(const char* name, const RTObject_impl* rtobj);
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�� CORBA ���֥������Ȥ�NamingService���饢��Х����
     * 
     * ���ꤷ�� CORBA ���֥������Ȥ� CORBA NamingService ���饢��Х���ɤ��롣
     * 
     * @param name ����Х�����оݥ��֥�������
     *
     * @else
     *
     * @endif
     */
    virtual void unbindObject(const char* name);
    
  private:
    CorbaNaming m_cosnaming;
    std::map<std::string, RTObject_impl*> m_names;
  };
  
  /*!
   * @if jp
   *
   * @brief NamingServer �������饹
   *
   * NamingServer �����ѥ��饹��
   * ����ݡ��ͥ�Ȥ�NamingService�ؤ���Ͽ������ʤɤ�������롣
   *
   * @since 0.4.0
   *
   * @else
   *
   * @biref ModuleManager class
   *
   * @endif
   */
  class NamingManager
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param manager �ޥ͡����㥪�֥�������
     *
     * @else
     *
     * @endif
     */
    NamingManager(Manager* manager);
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief destructor
     *
     * @endif
     */
    virtual ~NamingManager();
    
    /*!
     * @if jp
     *
     * @brief NameServer ����Ͽ
     *
     * ���ꤷ�������� NameServer ����Ͽ���롣
     * ���߻����ǽ�ʷ����� CORBA �Τߡ�
     *
     * @param method NamingService �η���
     * @param name_server ��Ͽ���� NameServer ��̾��
     *
     * @else
     *
     * @endif
     */
    void registerNameServer(const char* method, const char* name_server);
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�����֥������Ȥ�NamingService�إХ����
     * 
     * ���ꤷ�����֥������Ȥ���ꤷ��̾�Τ� CORBA NamingService �إХ���ɤ��롣
     * 
     * @param name �Х���ɻ���̾��
     * @param rtobj �Х�����оݥ��֥�������
     *
     * @else
     *
     * @endif
     */
    void bindObject(const char* name, const RTObject_impl* rtobj);
    
    /*!
     * @if jp
     *
     * @brief NamingServer �ξ���ι���
     * 
     * ���ꤵ��Ƥ��� NameServer �����Ͽ����Ƥ��륪�֥������Ȥξ����
     * �������롣
     * 
     * @else
     *
     * @endif
     */
    void update();
    
    /*!
     * @if jp
     *
     * @brief ���ꤷ�����֥������Ȥ�NamingService���饢��Х����
     * 
     * ���ꤷ�����֥������Ȥ� NamingService ���饢��Х���ɤ��롣
     * 
     * @param name ����Х�����оݥ��֥�������
     *
     * @else
     *
     * @endif
     */
    void unbindObject(const char* name);
    
    /*!
     * @if jp
     *
     * @brief ���ƤΥ��֥������Ȥ�NamingService���饢��Х����
     * 
     * ���ƤΥ��֥������Ȥ� CORBA NamingService ���饢��Х���ɤ��롣
     * 
     * @else
     *
     * @endif
     */
    void unbindAll();
    
    /*!
     * @if jp
     *
     * @brief �Х���ɤ���Ƥ������ƤΥ��֥������Ȥ����
     * 
     * �Х���ɤ���Ƥ������ƤΥ��֥������Ȥ� �������롣
     *
     * @return �Х���ɺѤߥ��֥������� �ꥹ��
     * 
     * @else
     *
     * @endif
     */
    std::vector<RTObject_impl*> getObjects();
    
  protected:
    /*!
     * @if jp
     *
     * @brief NameServer �����ѥ��֥������Ȥ�����
     * 
     * ���ꤷ������NameServer �����ѥ��֥������Ȥ��������롣
     *
     * @param method NamingService ����
     * @param name_server NameServer ̾��
     * 
     * @return �������� NameServer ���֥�������
     * 
     * @else
     *
     * @endif
     */
    NamingBase* createNamingObj(const char* method, const char* name_server);
    
    /*!
     * @if jp
     *
     * @brief ����Ѥߥ���ݡ��ͥ�Ȥ� NameServer ����Ͽ
     * 
     * ����Ѥߥ���ݡ��ͥ�Ȥ���ꤷ�� NameServer ����Ͽ���롣
     *
     * @param ns ��Ͽ�о� NameServer
     * 
     * @else
     *
     * @endif
     */
    void bindCompsTo(NamingBase* ns);
    
    /*!
     * @if jp
     *
     * @brief NameServer ����Ͽ���륳��ݡ��ͥ�Ȥ�����
     * 
     * NameServer ����Ͽ���륳��ݡ��ͥ�Ȥ����ꤹ�롣
     *
     * @param name ����ݡ��ͥ�Ȥ���Ͽ��̾��
     * @param rtobj ��Ͽ�оݥ��֥�������
     * 
     * @else
     *
     * @endif
     */
    void registerCompName(const char* name, const RTObject_impl* rtobj);
    
    /*!
     * @if jp
     *
     * @brief NameServer ����Ͽ���륳��ݡ��ͥ�Ȥ�������
     * 
     * NameServer ����Ͽ���륳��ݡ��ͥ�Ȥ�����������롣
     *
     * @param name �������оݥ���ݡ��ͥ�Ȥ�̾��
     * 
     * @else
     *
     * @endif
     */
    void unregisterCompName(const char* name);
    
  protected:
    // Name Servers' method/name and object
    /*!
     * @if jp
     * @brief NameServer �����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct Names
    {
      Names(const char* meth, const char* name, NamingBase* naming)
	: method(meth), nsname(name), ns(naming)
      {
      }
      std::string method;
      std::string nsname;
      NamingBase* ns;
    };
    /*!
     * @if jp
     * @brief NameServer �ꥹ��
     * @else
     *
     * @endif
     */
    std::vector<Names*> m_names;
    ACE_Thread_Mutex m_namesMutex;
    
    // Components' name and object
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȴ����ѹ�¤��
     * @else
     *
     * @endif
     */
    struct Comps
    {
      Comps(const char* n, const RTObject_impl* obj)
	: name(n), rtobj(obj)
      {}
      std::string name;
      const RTObject_impl* rtobj;
    };
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȥꥹ��
     * @else
     *
     * @endif
     */
    std::vector<Comps*> m_compNames;
    ACE_Thread_Mutex m_compNamesMutex;
    
    /*!
     * @if jp
     * @brief �ޥ͡����㥪�֥�������
     * @else
     *
     * @endif
     */
    Manager* m_manager;
    
    /*!
     * @if jp
     * @brief �������Хåե�
     * @else
     * @brief Logger mediation buffer
     * @endif
     */
    MedLogbuf m_MedLogbuf;
    
    /*!
     * @if jp
     * @brief �������ȥ꡼��
     * @else
     * @brief Logger stream
     * @endif
     */
    LogStream rtcout;
  }; // class NamingManager
}; // namespace RTC

#endif // NamingManager_h
