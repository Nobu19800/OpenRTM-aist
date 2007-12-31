// -*- C++ -*-
/*!
 * @file  InPortProvider.h
 * @brief InPortProvider class
 * @date  $Date: 2007-12-31 03:08:03 $
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
 * $Id: InPortProvider.h,v 1.4.4.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2007/01/21 09:49:52  n-ando
 * The destructor was moved to cpp file.
 *
 * Revision 1.3  2007/01/06 17:53:42  n-ando
 * Interface and its profile publish functions (publishInterfaceProfile()
 * and publishInterface()) are added.
 *
 * Revision 1.2  2006/12/02 18:41:51  n-ando
 * A trivial fix.
 *
 * Revision 1.1  2006/11/27 09:44:40  n-ando
 * The first commitment.
 *
 */

#ifndef InPortProvider_h
#define InPortProvider_h

#include <rtm/NVUtil.h>
#include <string>

namespace RTC
{
  /*!
   * @if jp
   * @class InPortProvider
   * @brief InPortProvider ���饹
   *
   * InPort�ξ�����ݻ����뤿��Υ��饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortProvider
   * @brief InPortProvider class
   * @endif
   */
  class InPortProvider
  {
  public:
    /***
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     * @endif
     */
    //    InPortProvider();
    
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
    virtual ~InPortProvider();
    
    /*!
     * @if jp
     * @brief InterfaceProfile������������
     *
     * InterfaceProfile�����������롣
     *
     * @param properties InterfaceProfile�����������ץ�ѥƥ�
     *
     * @else
     *
     * @endif
     */
    virtual void publishInterfaceProfile(SDOPackage::NVList& properties);
    
    /*!
     * @if jp
     * @brief Interface������������
     *
     * Interface�����������롣
     *
     * @param properties Interface�����������ץ�ѥƥ�
     *
     * @else
     *
     * @endif
     */
    virtual void publishInterface(SDOPackage::NVList& properties);
    
  protected:
    /*!
     * @if jp
     * @brief �ǡ��������פ����ꤹ��
     *
     * �ǡ��������פ����ꤹ�롣
     *
     * @param data_type �����оݥǡ���������
     *
     * @else
     *
     * @endif
     */
    void setDataType(const char* data_type);
    
    /*!
     * @if jp
     * @brief ���󥿥ե����������פ����ꤹ��
     *
     * ���󥿥ե����������פ����ꤹ�롣
     *
     * @param interface_type �����оݥ��󥿥ե�����������
     *
     * @else
     *
     * @endif
     */
    void setInterfaceType(const char* interface_type);
    
    /*!
     * @if jp
     * @brief �ǡ����ե������פ����ꤹ��
     *
     * �ǡ����ե������פ����ꤹ�롣
     *
     * @param dataflow_type �����оݥǡ����ե�������
     *
     * @else
     *
     * @endif
     */
    void setDataFlowType(const char* dataflow_type);
    
    /*!
     * @if jp
     * @brief ���֥�����ץ���󥿥��פ����ꤹ��
     *
     * ���֥�����ץ���󥿥��פ����ꤹ�롣
     *
     * @param subs_type �����оݥ��֥�����ץ���󥿥���
     *
     * @else
     *
     * @endif
     */
    void setSubscriptionType(const char* subs_type);
    
    /*!
     * @if jp
     * @brief �ݡ��ȥץ�ե�������ݻ�����ץ�ѥƥ�
     * @else
     *
     * @endif
     */
    SDOPackage::NVList m_properties;
    
  private:
    std::string m_dataType;
    std::string m_interfaceType;
    std::string m_dataflowType;
    std::string m_subscriptionType;
  };
};     // namespace RTC
#endif // InPortProvider_h
