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
 * $Id$
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
   *
   * Class to hold InPort information.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortProvider
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
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
     *
     * Destructor
     *
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
     * @brief Publish InterfaceProfile information
     *
     * Publish InterfaceProfile information.
     *
     * @param properties Properties to receive InterfaceProfile information
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
     * @brief Publish interface information
     *
     * Publish interface information.
     *
     * @param properties Properties to receive interface information
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
     * @brief Set the data type
     *
     * Set the data type.
     *
     * @param data_type The target data type for set
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
     * @brief Set the interface type
     *
     * Set the interface type.
     *
     * @param interface_type The target interface type for set
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
     * @brief Set the dataflow type
     *
     * Set the dataflow type.
     *
     * @param dataflow_type The target data flow type for set
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
     * @brief Set the subscription type
     *
     * Set the subscription type.
     *
     * @param subs_type The target subscription type for set
     *
     * @endif
     */
    void setSubscriptionType(const char* subs_type);
    
    /*!
     * @if jp
     * @brief �ݡ��ȥץ�ե�������ݻ�����ץ�ѥƥ�
     * @else
     * @brief Properties to hold port profile
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
