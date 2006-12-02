// -*- C++ -*-
/*!
 * @file DataInPort.h
 * @brief RTC::Port implementation for Data InPort
 * @date $Date: 2006-12-02 18:27:49 $
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
 * $Id: DataInPort.h,v 1.1 2006-12-02 18:27:49 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
    DataInPort(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa,
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

      addProperty("port.port_type",             "DataInPort");
      addProperty("dataport.data_type",         any_var.type().name());
      addProperty("dataport.interface_type",    "CORBA_Any, RawTCP");
      addProperty("dataport.dataflow_type",     "Push, Pull");
      addProperty("dataport.subscription_type", "Any");

      InPortCorbaProvider<DataType>* inport;
      inport = new InPortCorbaProvider<DataType>(buffer);
      addProvider(name, "InPortAny", inport);

      OutPortConsumer* outport;
      outport = new OutPortCorbaConsumer<DataType>();
      addConsumer(name, "OutPortAny", outport);
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
    virtual ReturnCode_t connect(ConnectorProfile& connector_profile);
    virtual ReturnCode_t disconnect(const char* connector_id);

  protected:
    bool setInPortRef(ConnectorProfile& cprof);
    bool getOutPortRef(ConnectorProfile& cprof);
  private:
    struct find_conn_id;
  };
}; // namespace RTC

#endif // DataInPort_h
