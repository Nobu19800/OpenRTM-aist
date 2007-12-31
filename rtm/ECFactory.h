// -*- C++ -*-
/*!
 * @file ECFactory.h
 * @brief ExecutionContext Factory class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ECFactory.h,v 1.1.2.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2007/04/13 16:06:22  n-ando
 * ExecutionContext Factory class.
 *
 */

#ifndef ECFactory_h
#define ECFactory_h

#include <rtm/ExecutionContextBase.h>
#include <string>

namespace RTC 
{
  
  typedef ExecutionContextBase* (*ECNewFunc)();
  typedef void (*ECDeleteFunc)(ExecutionContextBase* ec);
  
  /*!
   * @if jp
   *
   * @brief ExecutionContext�����ѥƥ�ץ졼�ȴؿ�
   * 
   * ExecutionContext�Υ��󥹥��󥹤��������뤿��Υƥ�ץ졼�ȴؿ���
   *
   * @return ��������ExecutionContext���󥹥���
   * 
   * @else
   *
   * @endif
   */
  template <class _New>
  ExecutionContextBase* ECCreate()
  {
    return new _New();
  }
  
  /*!
   * @if jp
   *
   * @brief ExecutionContext�˴��ѥƥ�ץ졼�ȴؿ�
   * 
   * ExecutionContext�Υ��󥹥��󥹤��˴����뤿��Υƥ�ץ졼�ȴؿ���
   *
   * @param ec �˴��о�ExecutionContext�Υ��󥹥���
   *
   * @else
   *
   * @endif
   */
  template <class _Delete>
  void ECDelete(ExecutionContextBase* ec)
  {
    delete ec;
  }
  
  /*!
   * @if jp
   * @class ECFactoryBase
   * @brief ECFactoryBase ��ݥ��饹
   * 
   * ExecutionContext������Factory����ݥ��饹��
   * ��ExecutionContext���������뤿��ζ��Factory���饹�ϡ�
   * �ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
   *
   * public���󥿡��ե������Ȥ��ưʲ��Τ�Τ��󶡤��롣
   * - name()   : �����о�ExecutionContext̾�Τμ���
   * - create() : ExecutionContext���󥹥��󥹤�����
   * - destroy(): ExecutionContext���󥹥��󥹤��˴�
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  class ECFactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     *
     * @else
     *
     * @endif
     */
    virtual ~ECFactoryBase(){};
    
    /*!
     * @if jp
     *
     * @brief �����о�ExecutionContext̾�μ����ѽ�貾�۴ؿ�
     * 
     * �����о�ExecutionContext��̾�Τ�������뤿��ν�貾�۴ؿ���
     *
     * @return �����о�ExecutionContext̾��
     * 
     * @else
     *
     * @endif
     */
    virtual const char* name() = 0;
    
    /*!
     * @if jp
     *
     * @brief ExecutionContext�����ѽ�貾�۴ؿ�
     * 
     * ExecutionContext�Υ��󥹥��󥹤��������뤿��ν�貾�۴ؿ���
     *
     * @return ��������ExecutionContext���󥹥���
     * 
     * @else
     *
     * @endif
     */
    virtual ExecutionContextBase* create() = 0;
    
    /*!
     * @if jp
     *
     * @brief ExecutionContext�˴��ѽ�貾�۴ؿ�
     * 
     * ExecutionContext�Υ��󥹥��󥹤��˴����뤿��ν�貾�۴ؿ���
     *
     * @param comp �˴��оݤ�ExecutionContext���󥹥���
     * 
     * @else
     *
     * @endif
     */
    virtual void destroy(ExecutionContextBase* comp) = 0;
  protected:
  };
  
  /*!
   * @if jp
   * @class ECFactoryCXX
   * @brief ECFactoryCXX ���饹
   * 
   * C++������ExecutionContext���󥹥��󥹤���������Factory���饹��
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  class ECFactoryCXX
    : public ECFactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param name �����о�ExecutionContext̾��
     * @param new_func ExecutionContext�����Ѵؿ�
     * @param delete_func ExecutionContext�˴��Ѵؿ�
     * 
     * @else
     *
     * @endif
     */
    ECFactoryCXX(const char* name,
		 ECNewFunc new_func,
		 ECDeleteFunc delete_func);
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * ���ۥǥ��ȥ饯����
     *
     * @else
     *
     * @endif
     */
    ~ECFactoryCXX();
    
    /*!
     * @if jp
     *
     * @brief �����о�ExecutionContext̾�Τ����
     * 
     * �����оݤ�ExecutionContext̾�Τ�������롣
     *
     * @return �����о�ExecutionContext̾��
     * 
     * @else
     *
     * @endif
     */
    virtual const char* name();
    
    /*!
     * @if jp
     *
     * @brief �����о�ExecutionContext���󥹥��󥹤�����
     * 
     * �����оݤ�ExecutionContext���饹�Υ��󥹥��󥹤��������롣
     *
     * @return ��������ExecutionContext���󥹥���
     * 
     * @else
     *
     * @endif
     */
    virtual ExecutionContextBase* create();
    
    /*!
     * @if jp
     *
     * @brief �о�ExecutionContext���󥹥��󥹤��˴�
     * 
     * �о�ExecutionContext���饹�Υ��󥹥��󥹤��˴����롣
     *
     * @param comp �˴��о�ExecutionContext���󥹥���
     * 
     * @else
     *
     * @endif
     */
    virtual void destroy(ExecutionContextBase* comp);
    
  protected:
    /*!
     * @if jp
     * @brief  �����о�ExecutionContext̾��
     * @else
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief  �о�ExecutionContext�����Ѵؿ�
     * @else
     * @endif
     */
    ECNewFunc m_New;
    
    /*!
     * @if jp
     * @brief  �о�ExecutionContext�˴��Ѵؿ�
     * @else
     * @endif
     */
    ECDeleteFunc m_Delete;
  };
};
#endif // ECFactory_h
