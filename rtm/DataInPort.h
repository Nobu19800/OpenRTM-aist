// -*- C++ -*-
/*!
 * @file DataInPort.h
 * @brief RTC::Port implementation for Data InPort
 * @date $Date: 2007-12-31 03:08:02 $
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
 * $Id: DataInPort.h,v 1.6.4.2 2007-12-31 03:08:02 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6.4.1  2007/10/06 12:23:26  n-ando
 * TCP socket data port was added.
 *
 * Revision 1.6  2007/01/21 17:16:58  n-ando
 * Invalid kanji code was deleted.
 *
 * Revision 1.5  2007/01/21 09:43:22  n-ando
 * - A bug about memory access violation to m_providers still exists.
 *   This bug arises on Fedora5/gcc4 environment.
 *   To escape the bug temporarily dummy variable (m_dummy) is defined.
 * - Some functors were moved to cpp file.
 *
 * Revision 1.4  2007/01/14 22:57:48  n-ando
 * A bug fix about template argument for buffer-type in constructor.
 *
 * Revision 1.3  2007/01/12 14:29:48  n-ando
 * A trivial bug fix.
 *
 * Revision 1.2  2007/01/06 17:43:39  n-ando
 * The behavior on notify_connect() and notify_disconnect() are now
 * implemented in protected functions(ex. publisherInterfaces()).
 *
 * Revision 1.1  2006/12/02 18:27:49  n-ando
 * The first commitment.
 *
 *
 */

#ifndef DataInPort_h
#define DataInPort_h

#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortCorbaProvider.h>
#include <rtm/OutPortCorbaConsumer.h>
#include <rtm/InPortTcpSockProvider.h>
#include <rtm/NVUtil.h>
#include <rtm/InPort.h>
#include <stdio.h>

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
   * @class DataInPort
   * @brief InPort �� Port
   *
   * �ǡ������ϥݡ��Ȥμ������饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class DataInPort
   * @brief InPort abstruct class
   * @endif
   */
  class DataInPort
    : public virtual PortBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param name �ݡ���̾��
     * @param inport �����ǡ������ϥݡ��Ȥ˴�Ϣ�դ���InPort���֥�������
     *               InPort���֥������Ȥǰ����ǡ��������Хåե������פ���ꤹ��
     * @param prop �ݡ��������ѥץ�ѥƥ�
     *
     * @else
     * @brief Constructor
     * @endif
     */
    template <class DataType, template <class DataType> class Buffer>
    DataInPort(const char* name, InPort<DataType, Buffer>& inport,
	       Properties& prop)
      : PortBase(name)
    {
      // PortProfile::properties ������
      addProperty("port.port_type", "DataInPort");
      
      // CORBA InPort Provider
      m_providers.push_back(new InPortCorbaProvider<DataType>(inport));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
      
      // TCP Socket InPort Provider
      m_providers.push_back(new InPortTcpSockProvider<DataType>(inport, prop));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
      
      // CORBA OutPort Consumer
      m_consumers.push_back(new OutPortCorbaConsumer<DataType>(inport));
      
      // dummy var
      m_dummy.push_back(1);
    }
    
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
    virtual ~DataInPort();
    
  protected:
    /*!
     * @if jp
     * @brief Interface������������
     *
     * Interface�����������롣
     * ����Port����ͭ���Ƥ���ץ�Х���(Provider)�˴ؤ�������
     * ConnectorProfile#properties���������ޤ���
     *
     * @param connector_profile ���ͥ����ץ�ե�����
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interface����³����
     *
     * Interface����³���롣
     * Port����ͭ����Consumer��Ŭ�礹��Provider�˴ؤ������� 
     * ConnectorProfile#properties ������Ф���
     * Consumer��CORBA���֥������Ȼ��Ȥ����ꤹ�롣
     *
     * @param connector_profile ���ͥ������ץ�ե�����
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interface�ؤ���³��������
     *
     * Interface�ؤ���³�������롣
     * Ϳ����줿ConnectorProfile�˴�Ϣ����Consumer�����ꤵ�줿���Ƥ�Object��
     * ��������³�������롣
     *
     * @param connector_profile ���ͥ������ץ�ե�����
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interface������Functor
     *
     * Interface����������¹Ԥ��뤿���Functor��
     *
     * @else
     *
     * @endif
     */
    struct publish;
    
    /*!
     * @if jp
     * @brief Interface��³��Functor
     *
     * Interface��³������¹Ԥ��뤿���Functor��
     *
     * @else
     *
     * @endif
     */
    struct subscribe;
    
    /*!
     * @if jp
     * @brief Interface��³�����Functor
     *
     * Interface��³���������¹Ԥ��뤿���Functor��
     *
     * @else
     *
     * @endif
     */
    struct unsubscribe;
    
  private:
    /*
     * Bug
     *
     * Fedora5/gcc4.1.1. �ˤ� DataInPort ����Ƭ�ΰ�Υ����˲���
     * �����äƤ������͡�
     * (gdb�Ǥ��ʤ�Ǵ�ä��ɤäƤߤ�����ǰ)
     * ��Ȥ�Ȥ�� std::vector<InPortProvider*> m_providers ����Ƭ
     * ���Τޤޤ��ȡ�
     * $vec->_M_impl._M_start:  begin() ��������
     * $vec->_M_impl._M_finish: end() ��������
     * �ˤ����Ƥ� _M_start ���ԲĲ�ʰ��֤�ؤ����ᡢ
     * m_providers ���Ф��� for_each ��Ŭ�Ѥ����Segv������롣
     *
     * FreeBSD6.0/gcc3.4.4�ǤϤ��θ��ݤ�ȯ��������
     */
    std::vector<int> m_dummy;
    std::vector<InPortProvider*> m_providers;
    std::vector<OutPortConsumer*> m_consumers;
  };
}; // namespace RTC

#endif // DataInPort_h
