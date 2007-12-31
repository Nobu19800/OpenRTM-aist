// -*- C++ -*-
/*!
 * @file Factory.h
 * @brief RTComponent factory class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Factory.h,v 1.5.4.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5  2006/11/06 01:28:36  n-ando
 * Now the "instance_name" is set to the component at creation time.
 *
 * Revision 1.4  2006/10/25 17:36:00  n-ando
 * Classes were renamed, and class reference manual was described.
 *
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

#ifndef Factory_h
#define Factory_h

#include <rtm/Properties.h>
#include <rtm/RTObject.h>
#include <rtm/NumberingPolicy.h>


namespace RTC 
{
  typedef RTObject_impl RtcBase;
  class Manager;
  
  typedef RtcBase* (*RtcNewFunc)(Manager* manager);
  typedef void (*RtcDeleteFunc)(RtcBase* rtc);
  
  /*!
   * @if jp
   *
   * @brief RT����ݡ��ͥ�������ѥƥ�ץ졼�ȴؿ�
   * 
   * RT����ݡ��ͥ�ȤΥ��󥹥��󥹤��������뤿��Υƥ�ץ졼�ȴؿ���
   * RT����ݡ��ͥ�ȴ����ѥޥ͡����㤫��ƤӽФ���롣
   * �ºݤˤϳƥ���ݡ��ͥ�ȤΥ��󥹥ȥ饯�����ƤӽФ���롣
   * \<_New\>�������о�RT����ݡ��ͥ�Ȥη�����ꤹ�롣
   *
   * @param manager �ޥ͡����㥪�֥�������
   *
   * @return �������� RT����ݡ��ͥ�� ���󥹥���
   * 
   * @else
   *
   * @endif
   */
  template <class _New>
  RtcBase* Create(Manager* manager)
  {
    return new _New(manager);
  }
  
  /*!
   * @if jp
   *
   * @brief RT����ݡ��ͥ���˴��ѥƥ�ץ졼�ȴؿ�
   * 
   * RT����ݡ��ͥ�ȤΥ��󥹥��󥹤��˴����뤿��Υƥ�ץ졼�ȴؿ���
   * \<_Delete\>�ˤ��˴��о�RT����ݡ��ͥ�Ȥη�����ꤹ�롣
   *
   * @param rtc �˴��о�RT����ݡ��ͥ�ȤΥ��󥹥���
   *
   * @else
   *
   * @endif
   */
  template <class _Delete>
  void Delete(RtcBase* rtc)
  {
    delete rtc;
  }
  
  /*!
   * @if jp
   *
   * @class FactoryBase
   * @brief FactoryBase ���쥯�饹
   * 
   * ����ݡ��ͥ�ȥե����ȥ�δ��쥯�饹��
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class FactoryBase
   * @brief FactoryBase base class
   *
   * RTComponent factory base class.
   *
   * @since 0.2.0
   *
   * @endif
   */
  class FactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     *
     * @param profile ����ݡ��ͥ�ȤΥץ�ե�����
     *
     * @else
     *
     * @brief Constructor.
     *
     * Constructor.
     *
     * @param profile component profile
     *
     * @endif
     */
    FactoryBase(const Properties& profile);
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~FactoryBase();
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�Ȥ�����
     *
     * RTComponent �Υ��󥹥��󥹤��������뤿��ν�貾�۴ؿ���
     *
     * @param mgr �ޥ͡����㥪�֥�������
     *
     * @return ������������ݡ��ͥ��
     *
     * @else
     *
     * @brief Create component
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
     * RTComponent �Υ��󥹥��󥹤��˴����뤿��ν�貾�۴ؿ���
     *
     * @param comp �˴��о� RT����ݡ��ͥ��
     *
     * @else
     *
     * @brief Destroy component
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
     * @return ����ݡ��ͥ�ȤΥץ�ե�����
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
     * @brief ���ߤΥ��󥹥��󥹿��μ���
     *
     * ����ݡ��ͥ�Ȥθ��ߤΥ��󥹥��󥹿���������롣
     *
     * @return ����ݡ��ͥ�ȤΥ��󥹥��󥹿�
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
   * @class FactoryCXX
   * @brief FactoryCXX ���饹
   * 
   * C++�ѥ���ݡ��ͥ�ȥե����ȥꥯ�饹��
   *
   * @since 0.2.0
   *
   *
   * @else
   *
   * @class FactoryCXX
   * @brief FactoryCXX class
   *
   * RTComponent factory class for C++.
   *
   * @endif
   */
  class FactoryCXX
    : public FactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     * �ץ�ե����롢�����ؿ��ؤΥݥ��󥿡��˴��ؿ��ؤΥݥ��󥿡�
     * ����ݡ��ͥ����������̿̾�ݥꥷ��������˼�ꡢ
     * C++ �Ǽ������줿����ݡ��ͥ�ȤΥե����ȥꥯ�饹���������롣
     *
     * @param profile ����ݡ��ͥ�ȤΥץ�ե�����
     * @param new_func ����ݡ��ͥ�Ȥ������ؿ��ؤΥݥ���
     * @param delete_func ����ݡ��ͥ�Ȥ��˴��ؿ��ؤΥݥ���
     * @param policy ����ݡ��ͥ����������̿̾�ݥꥷ��
     * (�ǥե������:DefaultNumberingPolicy)
     *
     * @else
     *
     * @brief Constructor.
     *
     * Constructor.
     * Create component factory class with three arguments:
     * component profile, function pointer to object create function and
     * object delete function.
     *
     * @param profile Component profile
     * @param new_func Pointer to component create function
     * @param delete_func Pointer to component delete function
     * @param policy Pointer to component delete function
     *
     * @endif
     */
    FactoryCXX(const Properties& profile,
	       RtcNewFunc new_func,
	       RtcDeleteFunc delete_func,
	       NumberingPolicy* policy = new DefaultNumberingPolicy());
    
    /*!
     * @if jp
     *
     * @brief ����ݡ��ͥ�Ȥ�����
     *
     * RTComponent �Υ��󥹥��󥹤��������롣
     *
     * @param mgr �ޥ͡����㥪�֥�������
     *
     * @return ������������ݡ��ͥ��
     *
     * @else
     *
     * @brief Create component
     *
     * Create component implemented in Python.
     *
     * @param mgr
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
     * @param comp �˴��о� RTComponent
     *
     * @else
     *
     * @brief Destroy component
     *
     * Destroy component instance
     *
     * @param comp
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
    
    /*!
     * @if jp
     * @brief ����ݡ��ͥ����������̿̾�ݥꥷ��
     * @else
     * @endif
     */
    NumberingPolicy* m_policy;
  };
};
#endif // Factory_h
