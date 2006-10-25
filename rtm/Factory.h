// -*- C++ -*-
/*!
 * @file Factory.h
 * @brief RTComponent factory class
 * @date $Date: 2006-10-25 17:36:00 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Factory.h,v 1.4 2006-10-25 17:36:00 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2006/10/24 14:23:45  n-ando
 * Renamed RtcFactory.h to Factory.h
 *
 * Revision 1.2  2005/05/16 06:06:30  n-ando
 * - RtcFactoryBase, RtcFactoryCXX classes were DLL exported for Windows port.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcFactory_h
#define RtcFactory_h
#define EXPORTS
#include "rtm/Properties.h"


namespace RTC 
{
  class RtcBase;
  class Manager;

  typedef RtcBase* (*RtcNewFunc)(Manager* manager);
  typedef void (*RtcDeleteFunc)(RtcBase* rtc);

  template <class _New>
  RtcBase* Create(Manager* manager)
  {
    return new _New(manager);
  }

  template <class _Delete>
  void Delete(RtcBase* rtc)
  {
    delete rtc;
  }


  /*!
   * @if jp
   *
   * @class RtcFactoryBase
   *
   * @brief RtcFactoryBase ���쥯�饹
   * 
   * ����ݡ��ͥ�ȥե����ȥ�δ��쥯�饹��
   *
   * @else
   *
   * @class RtcFactoryBase
   *
   * @brief RtcFactoryBase base class
   *
   * RTComponent factory base class.
   *
   * @endif
   */
  class EXPORTS FactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief RtcFactoryBase ���饹���󥹥ȥ饯��
     *
     * RtcFactoryBase ���饹�Υ��󥹥ȥ饯����
     *
     * @param profile ����ݡ��ͥ�ȤΥץ�ե�����
     *
     * @else
     *
     * @brief RtcFactoryBase class constructor.
     *
     * RtcFactoryBase class constructor.
     *
     * @param profile component profile
     *
     * @endif
     */
    FactoryBase(Properties profile);
    virtual ~FactoryBase();
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�Ȥ�����
     *
     * Python �Ǽ������줿 RTComponent �Υ��󥹥��󥹤��������롣
     * ��貾�۴ؿ���
     *
     * @param mgr RtcManager �ؤΥݥ���
     *
     * @else
     *
     * @brief Create component
     *
     * Create component implemented in Python.
     * Pure virtual method.
     *
     * @param mgr pointer to RtcManager
     *
     * @endif
     */
    virtual RtcBase* create(Manager* mgr) = 0;
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�Ȥ��˴�
     *
     * RTComponent �Υ��󥹥��󥹤��˴����롣
     * ��貾�۴ؿ���
     *
     * @param comp RtcBase �ؤΥݥ���
     *
     * @else
     *
     * @brief Destroy component
     *
     * Destroy component instance
     * Pure virtual method.
     *
     * @param comp pointer to RtcBase
     *
     * @endif
     */
    virtual void destroy(RtcBase* comp) = 0;
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�ȥץ�ե�����μ���
     *
     * ����ݡ��ͥ�ȤΥץ�ե�������������
     *
     * @else
     *
     * @brief Get component profile
     *
     * Get component profile.
     *
     * @endif
     */
    virtual Properties& profile();
    
    /*!
     * @if jp
     *
     * @brief ���ߤΥ��󥹥��󥹿�
     *
     * ����ݡ��ͥ�Ȥθ��ߤΥ��󥹥��󥹿���������롣
     *
     * @else
     *
     * @brief Get number of component instances
     *
     * Get number of current component instances.
     *
     * @endif
     */
    virtual int number();
    
  protected:
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȤΥץ�ե�����
     * @else
     * @brief Component profile
     * @endif
     */
    Properties m_Profile;
    /*!
     * @if jp
     * @brief ���ߤΥ��󥹥��󥹿�
     * @else
     * @brief Number of current component instances.
     * @endif
     */
    int m_Number;
  };
  
  
  
  /*!
   * @if jp
   *
   * @class RtcFactoryCXX
   *
   * @brief RtcFactoryCXX ���饹
   * 
   * C++�ѥ���ݡ��ͥ�ȥե����ȥꥯ�饹��
   *
   * @else
   *
   * @class RtcFactoryCXX
   *
   * @brief RtcFactoryCXX class
   *
   * RTComponent factory class for C++.
   *
   * @endif
   */
  class EXPORTS FactoryCXX
    : public FactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief RtcFactoryCXX ���饹���󥹥ȥ饯��
     *
     * RtcFactoryCXX ���饹�Υ��󥹥ȥ饯����
     * �ץ�ե����롢�����ؿ��ؤΥݥ��󥿡��˴��ؿ��ؤΥݥ��󥿤�����˼�ꡢ
     * C++ �Ǽ������줿����ݡ��ͥ�ȤΥե����ȥꥯ�饹���������롣
     *
     * @param profile ����ݡ��ͥ�ȤΥץ�ե�����
     * @param new_func ����ݡ��ͥ�Ȥ������ؿ��ؤΥݥ���
     * @param delete_func ����ݡ��ͥ�Ȥ��˴��ؿ��ؤΥݥ���
     *
     * @else
     *
     * @brief RtcFactoryCXX class constructor.
     *
     * RtcFactoryCXX class constructor.
     * Create component factory class with three arguments:
     * component profile, function pointer to object create function and
     * object delete function.
     *
     * @param profile Component profile
     * @param new_func Pointer to component create function
     * @param delete_func Pointer to component delete function
     *
     * @endif
     */
    FactoryCXX(Properties profile,
	       RtcNewFunc new_func,
	       RtcDeleteFunc delete_func);
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�Ȥ�����
     *
     * Python �Ǽ������줿 RTComponent �Υ��󥹥��󥹤��������롣
     *
     * @param mgr RtcManager �ؤΥݥ���
     *
     * @else
     *
     * @brief Create component
     *
     * Create component implemented in Python.
     *
     * @param mgr pointer to RtcManager
     *
     * @endif
     */
    virtual RtcBase* create(Manager* mgr);
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�Ȥ��˴�
     *
     * RTComponent �Υ��󥹥��󥹤��˴����롣
     *
     * @param comp RtcBase �ؤΥݥ���
     *
     * @else
     *
     * @brief Destroy component
     *
     * Destroy component instance
     *
     * @param comp pointer to RtcBase
     *
     * @endif
     */
    virtual void destroy(RtcBase* comp);
    
  protected:
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȥ��֥������������ؿ��ؤΥݥ���
     * @else
     * @brief The pointer to component object create function
     * @endif
     */
    RtcNewFunc m_New;
    
    /*!
     * @if jp
     * @brief ����ݡ��ͥ�ȥ��֥��������˴��ؿ��ؤΥݥ���
     * @else
     * @brief The pointer to component object delete function
     * @endif
     */
    RtcDeleteFunc m_Delete;
  };
};


#endif // RtcFactory_h
