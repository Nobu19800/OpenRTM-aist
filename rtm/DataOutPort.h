// -*- C++ -*-
/*!
 * @file DataOutPort.h
 * @brief Base class of OutPort
 * @date $Date: 2006-11-27 09:44:37 $
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
 * $Id: DataOutPort.h,v 1.1 2006-11-27 09:44:37 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef DataOutPort_h
#define DataOutPort_h

#include <rtm/RTObject.h>
#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/DataPort.h>
#include <rtm/NVUtil.h>
#include <rtm/PublisherFactory.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class DataOutPort
   * @brief InPort �� Port
   * @else
   * @class DataOutPort
   * @brief InPort abstruct class
   * @endif
   */
  
  class DataOutPort
    : public virtual PortBase
  {
    
  public:
    template <class DataType>
    DataOutPort(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa,
		const char* name, BufferBase<DataType>* buffer,
		RTObject_ptr owner)
      : PortBase(orb, poa)
    {
      m_profile.name = CORBA::string_dup(name);
      m_profile.connector_profiles.length(0);
      m_profile.owner = owner;
      
      CORBA::Any any_var;
      DataType   tmp_var;
      any_var <<= tmp_var;
      
      addProperty("port.port_type",             "DataOutPort");
      addProperty("dataport.data_type",         any_var.type().name());
      addProperty("dataport.interface_type",    "CORBA_Any, RawTCP");
      addProperty("dataport.dataflow_type",     "Push, Pull");
      addProperty("dataport.subscription_type", "Once, New, Periodic");
      
      OutPortProvider<DataType> outport;
      outport = new OutPortProvider<DataType>(buffer);
      addProvider(name, "OutPortAny", outport);
      
      InPortConsumer<DataType> inport;
      inport = new InPortConsumer<DataType>();
      addConsumer(name, "InPortAny", inport);
    }
    
    virtual ~DataOutPort(){};

    /*!
     * @if jp
     * @brief [CORBA interface] Port ����³��Ԥ�
     *
     * OutPort �� InPort �Ȥ���³��Ԥ���
     *
     * OutPort ¦�� connect() �Ǥϰʲ��Υ������󥹤ǽ������Ԥ��롣
     *
     * 1. OutPort �˴�Ϣ���� connector �������������ӥ��å�
     *
     * 2. InPort�˴�Ϣ���� connector ����μ���
     *  - ConnectorProfile::properties["dataport.corba_any.inport_ref"]��
     *    OutPortAny �Υ��֥������ȥ�ե���󥹤����ꤵ��Ƥ����硢
     *    ��ե���󥹤��������Consumer���֥������Ȥ˥��åȤ��롣
     *    ��ե���󥹤����åȤ���Ƥ��ʤ����̵�뤷�Ʒ�³��
     *    (OutPort��connect() �ƤӽФ��Υ���ȥ�ݥ���Ȥξ��ϡ�
     *    InPort�Υ��֥������ȥ�ե���󥹤ϥ��åȤ���Ƥ��ʤ��Ϥ��Ǥ��롣)
     * 3. PortBase::connect() �򥳡���
     *    Port����³�δ��ܽ������Ԥ��롣
     * 4. �嵭2.��InPort�Υ�ե���󥹤������Ǥ��ʤ���С�����InPort��
     *    ��Ϣ���� connector �����������롣
     *
     * 5. ConnectorProfile::properties ��Ϳ����줿���󤫤顢
     *    OutPort¦�ν����������Ԥ���
     *
     * - [dataport.interface_type]
     * -- CORBA_Any �ξ��: 
     *    InPortAny ���̤��ƥǡ����򴹤���롣
     *    ConnectorProfile::properties["dataport.corba_any.inport_ref"]��
     *    InPortAny �Υ��֥������ȥ�ե���󥹤򥻥åȤ��롣
     * -- RawTCP �ξ��: Raw TCP socket ���̤��ƥǡ����򴹤���롣
     *    ConnectorProfile::properties["dataport.raw_tcp.server_addr"]
     *    ��InPort¦�Υ����Х��ɥ쥹�򥻥åȤ��롣
     *
     * - [dataport.dataflow_type]
     * -- Push�ξ��: Subscriber���������롣Subscriber�Υ����פϡ�
     *    dataport.subscription_type �����ꤵ��Ƥ��롣
     * -- Pull�ξ��: InPort¦���ǡ�����Pull���Ǽ������뤿�ᡢ
     *    �ä˲��⤹��ɬ�פ�̵����
     *
     * - [dataport.subscription_type]
     * -- Once�ξ��: SubscriberOnce���������롣
     * -- New�ξ��: SubscriberNew���������롣
     * -- Periodic�ξ��: SubscriberPeriodic���������롣
     *
     * - [dataport.push_interval]
     * -- dataport.subscription_type=Periodic�ξ����������ꤹ�롣
     *
     * 6. �嵭�ν����Τ�����ĤǤ⥨�顼�Ǥ���С����顼�꥿���󤹤롣
     *    ����˽������Ԥ�줿����RTC::OK�ǥ꥿���󤹤롣
     *  
     * @else
     * @brief [CORBA interface] Connect the Port
     * @endif
     */
    virtual ReturnCode_t connect(ConnectorProfile& connector_profile);
    virtual ReturnCode_t disconnect(const char* connector_id);
    
  protected:
    bool setOutPortRef(ConnectorProfile& cprof);
    bool getInPortRef(const ConnectorProfile& cprof);
    PublisherFactory m_pf;

  };
}; // namespace RTC

#endif // DataOutPort_h
