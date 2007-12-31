// -*- C++ -*-
/*!
 * @file  OutPortProvider.h
 * @brief OutPortProvider class
 * @date  $Date: 2007-12-31 03:08:05 $
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
 * $Id: OutPortProvider.h,v 1.2.4.1 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/06 17:58:52  n-ando
 * Interface and its profile publish functions (publishInterfaceProfile()
 * and publishInterface()) are added.
 *
 *
 */

#ifndef OutPortProvider_h
#define OutPortProvider_h

#include <rtm/NVUtil.h>
#include <string>

namespace RTC
{
  /*!
   * @if jp
   *
   * @brief OutPort
   *
   * - Port ���Ф��Ʋ����󶡤��Ƥ��뤫��������롣
   *   PortProfile �� properties �� Provider �˴ؤ��������ɲä��롣
   *
   * (��) OutPort �� Provide ������
   *
   * OutPortCorbaProvider ���ʲ������
   * dataport.interface_type = CORBA_Any
   * dataport.dataflow_type = Push, Pull
   * dataport.subscription_type = Once, New, Periodic
   * 
   * OutPortRawTCPProvider���ʲ������
   * dataport.interface_type = RawTCP
   * dataport.dataflow_type = Push, Pull
   * dataport.subscription_type = Once, New, Periodic
   * 
   * �ǽ�Ū�� PortProfile::properties ��
   * dataport.interface_type = CORBA_Any, RawTCP
   * dataport.dataflow_type = Push, Pull
   * dataport.subscription_type = Once, New, Periodic
   *
   * @since 0.4.0
   *
   * @else
   *
   *
   * @endif
   */
  class OutPortProvider
  {
  public:
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
    virtual ~OutPortProvider(){};
    
    /*!
     * @if jp
     * @brief InterfaceProfile������������
     *
     * InterfaceProfile�����������롣
     * �����ǻ��ꤹ��ץ�ѥƥ�������� NameValue ���֥������Ȥ�
     * dataport.interface_type �ͤ�Ĵ�١������ݡ��Ȥ����ꤵ��Ƥ���
     * ���󥿡��ե����������פȰ��פ�����Τ߾����������롣
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
     * �����ǻ��ꤹ��ץ�ѥƥ�������� NameValue ���֥������Ȥ�
     * dataport.interface_type �ͤ�Ĵ�١������ݡ��Ȥ����ꤵ��Ƥ��ʤ����
     * NameValue �˾�����ɲä��롣
     * ���Ǥ�Ʊ�쥤�󥿡��ե���������Ͽ�Ѥߤξ��ϲ���Ԥ�ʤ���
     *
     * @param properties InterfaceProfile�����������ץ�ѥƥ�
     *
     * @else
     *
     * @endif
     */
    virtual void publishInterface(SDOPackage::NVList& properties);
    
  protected:
    /*!
     * @if jp
     * @brief �ݡ��ȥ����פ����ꤹ��
     *
     * �����ǻ��ꤷ���ݡ��ȥ����פ����ꤹ�롣
     *
     * @param port_type �����оݥݡ��ȥ�����
     *
     * @else
     *
     * @endif
     */
    void setPortType(const char* port_type);
    
    /*!
     * @if jp
     * @brief �ǡ��������פ����ꤹ��
     *
     * �����ǻ��ꤷ���ǡ��������פ����ꤹ�롣
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
     * @brief ���󥿡��ե����������פ����ꤹ��
     *
     * �����ǻ��ꤷ�����󥿡��ե����������פ����ꤹ�롣
     *
     * @param interface_type �����оݥ��󥿡��ե�����������
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
     * �����ǻ��ꤷ���ǡ����ե������פ����ꤹ�롣
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
     * �����ǻ��ꤷ�����֥�����ץ���󥿥��פ����ꤹ�롣
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
    std::string m_portType;
    std::string m_dataType;
    std::string m_interfaceType;
    std::string m_dataflowType;
    std::string m_subscriptionType;
  };
}; // namespace RTC
#endif // OutPortProvider_h
