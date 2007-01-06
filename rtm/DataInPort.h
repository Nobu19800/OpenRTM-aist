// -*- C++ -*-
/*!
 * @file DataInPort.h
 * @brief RTC::Port implementation for Data InPort
 * @date $Date: 2007-01-06 17:43:39 $
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
 * $Id: DataInPort.h,v 1.2 2007-01-06 17:43:39 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/12/02 18:27:49  n-ando
 * The first commitment.
 *
 *
 */

#ifndef DataInPort_h
#define DataInPort_h

#include <rtm/RTObject.h>
#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortCorbaProvider.h>
#include <rtm/OutPortCorbaConsumer.h>
#include <rtm/NVUtil.h>
#include <rtm/InPort.h>
namespace RTC
{
  /*!
   * @if jp
   *
   * @class DataInPort
   * @brief InPort �� Port
   * @else
   * @class DataInPort
   * @brief InPort abstruct class
   * @endif
   */

  class DataInPort
    : public virtual PortBase
  {

  public:
    template <class DataType>
    DataInPort(const char* name, InPort<DataType>& inport)
      : PortBase(name)
    {
      // PortProfile::properties ������
      addProperty("port.port_type", "DataInPort");

      m_providers.push_back(new InPortCorbaProvider<DataType>(inport));

      m_consumers.push_back(new OutPortCorbaConsumer<DataType>(inport));

    }

    virtual ~DataInPort(){};

    /*!
     * @if jp
     * @brief [CORBA interface] Port ����³��Ԥ�
     *
     * InPort �� OutPort �Ȥ���³��Ԥ���
     *
     * InPort ¦�� connect() �Ǥϰʲ��Υ������󥹤ǽ������Ԥ��롣
     *
     * 1. InPort �˴�Ϣ���� connector �������������ӥ��å�
     *  - ConnectorProfile::properties["dataport.interface_type"] = CORBA_Any
     *    �ξ�硢InPortAny ���̤��ơ�RawTCP �ξ�� Raw TCP socket ���̤���
     *    �ǡ����򴹤���롣
     *  - ConnectorProfile::properties["dataport.corba_any.inport_ref"]��
     *    InPortAny �Υ��֥������ȥ�ե���󥹤򥻥åȤ��롣(CORBA_Any�ξ��)
     *  - ConnectorProfile::properties["dataport.raw_tcp.server_addr"]
     *    ��InPort¦�Υ����Х��ɥ쥹�򥻥åȤ��롣(RawTCP �ξ��)
     * 2. OutPort�˴�Ϣ���� connector ����μ���
     *  - ConnectorProfile::properties["dataport.corba_any.outport_ref"]��
     *    OutPortAny �Υ��֥������ȥ�ե���󥹤����ꤵ��Ƥ����硢
     *    ��ե���󥹤��������Consumer���֥������Ȥ˥��åȤ��롣
     *    ��ե���󥹤����åȤ���Ƥ��ʤ����̵�뤷�Ʒ�³��
     *    (InPort��connect() �ƤӽФ��Υ���ȥ�ݥ���Ȥξ��ϡ�
     *    OutPort�Υ��֥������ȥ�ե���󥹤ϥ��åȤ���Ƥ��ʤ��Ϥ��Ǥ��롣)
     * 3. PortBase::connect() �򥳡���
     *    Port����³�δ��ܽ������Ԥ��롣
     * 4. �嵭2.��OutPort�Υ�ե���󥹤������Ǥ��ʤ���С�����OutPort��
     *    ��Ϣ���� connector �����������롣
     * 5. �嵭�ν����Τ�����ĤǤ⥨�顼�Ǥ���С����顼�꥿���󤹤롣
     *    ����˽������Ԥ�줿����RTC::OK�ǥ꥿���󤹤롣
     *  
     * @else
     * @brief [CORBA interface] Connect the Port
     * @endif
     */
 

  protected:
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);

    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);

    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);
    
    struct publish
    {
      publish(SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(InPortProvider* provider)
      {
	provider->publishInterface(m_prop);
      }
      SDOPackage::NVList& m_prop;
    };

    struct subscribe
    {
      subscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortConsumer* consumer)
      {
	consumer->subscribeInterface(m_prop);
      }
      const SDOPackage::NVList& m_prop;
    };

    struct unsubscribe
    {
      unsubscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortConsumer* consumer)
      {
	consumer->unsubscribeInterface(m_prop);
      }
      const SDOPackage::NVList& m_prop;
    };

  private:
    struct find_conn_id;
    std::vector<InPortProvider*> m_providers;
    std::vector<OutPortConsumer*> m_consumers;
  };
}; // namespace RTC

#endif // DataInPort_h
