// -*- C++ -*-
/*!
 * @file InPortBase.h
 * @brief RTC::Port implementation for InPort
 * @date $Date: 2008-01-13 15:06:40 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
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

#ifndef RTC_INPORTBASE_H
#define RTC_INPORTBASE_H

#include <rtm/PortBase.h>
#include <rtm/DataPortStatus.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/ConnectorListener.h>

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
 * @brief RT-Component
 *
 * @endif
 */
namespace RTC
{
  class InPortProvider;
  class OutPortConsumer;
  class InPortConnector;

  /*!
   * @if jp
   * @class InPortBase
   * @brief InPort �� Port
   *
   * �ǡ������ϥݡ��Ȥμ������饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortBase
   * @brief Port for InPort
   *
   * This is an implementation class for the data input port.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortBase
    : public PortBase, public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM

    typedef std::vector<InPortConnector*> ConnectorList;

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
     *
     * Constructor
     *
     * @param name Port name
     * @param inport InPort object that is associated with this data input port.
     *               Specify also the data type and the buffer type used in 
     *               the InPort object.
     * @param prop Property for setting ports
     *
     * @endif
     */
    InPortBase(const char* name, const char* data_type);
    
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
    virtual ~InPortBase(void);
    
    coil::Properties& properties();

    void init();

    /*!
     * @if jp
     *
     * @brief InPort�� activates ����
     *
     * InPort�� activate ���롣
     *
     * @else
     *
     * @brief Activate all Port interfaces
     *
     * This operation activate all interfaces that is registered in the
     * ports.
     *
     * @endif
     */
    virtual void activateInterfaces();

    /*!
     * @if jp
     *
     * @brief ���Ƥ� Port �Υ��󥿡��ե������� deactivates ����
     *
     * Port ����Ͽ����Ƥ������ƤΥ��󥿡��ե������� deactivate ���롣
     *
     * @else
     *
     * @brief Deactivate all Port interfaces
     *
     * This operation deactivate all interfaces that is registered in the
     * ports.
     *
     * @endif
     */
    virtual void deactivateInterfaces();

    /*!
     * @if jp
     * @brief ConnectorDataListener �ꥹ�ʤ��ɲä���
     *
     * �Хåե��񤭹��ߤޤ����ɤ߽Ф����٥�Ȥ˴�Ϣ����Ƽ�ꥹ�ʤ����ꤹ�롣
     *
     * ����Ǥ���ꥹ�ʤΥ����פȥ�����Хå����٥�Ȥϰʲ����̤�
     *
     * - ON_BUFFER_WRITE:          �Хåե��񤭹��߻�
     * - ON_BUFFER_FULL:           �Хåե��ե��
     * - ON_BUFFER_WRITE_TIMEOUT:  �Хåե��񤭹��ߥ����ॢ���Ȼ�
     * - ON_BUFFER_OVERWRITE:      �Хåե���񤭻�
     * - ON_BUFFER_READ:           �Хåե��ɤ߽Ф���
     * - ON_SEND:                  InProt�ؤ�������
     * - ON_RECEIVED:              InProt�ؤ�������λ��
     * - ON_SEND_ERTIMEOUT:        OutPort¦�����ॢ���Ȼ�
     * - ON_SEND_ERERROR:          OutPort¦���顼��
     * - ON_RECEIVER_FULL:         InProt¦�Хåե��ե��
     * - ON_RECEIVER_TIMEOUT:      InProt¦�Хåե������ॢ���Ȼ�
     * - ON_RECEIVER_ERROR:        InProt¦���顼��
     *
     * �ꥹ�ʤ� ConnectorDataListener ��Ѿ������ʲ��Υ����˥�������
     * operator() ��������Ƥ���ɬ�פ����롣
     *
     * ConnectorDataListener::
     *         operator()(const ConnectorProfile&, const cdrStream&)
     *
     * �ǥե���ȤǤϡ����δؿ���Ϳ�����ꥹ�ʥ��֥������Ȥν�ͭ����
     * OutPort�˰ܤꡢOutPort���λ��⤷���ϡ�
     * removeConnectorDataListener() �ˤ�������˼�ưŪ�˲��Τ���롣
     * �ꥹ�ʥ��֥������Ȥν�ͭ����ƤӽФ�¦�ǰݻ����������ϡ���3��
     * ���� false ����ꤷ����ưŪ�ʲ��Τ��������뤳�Ȥ��Ǥ��롣
     *
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     * @param autoclean �ꥹ�ʥ��֥������Ȥμ�ưŪ���Τ�Ԥ����ɤ����Υե饰
     *
     * @else
     * @brief Adding BufferDataListener type listener
     *
     * This operation adds certain listeners related to buffer writing and
     * reading events.
     * The following listener types are available.
     *
     * - ON_BUFFER_WRITE:          At the time of buffer write
     * - ON_BUFFER_FULL:           At the time of buffer full
     * - ON_BUFFER_WRITE_TIMEOUT:  At the time of buffer write timeout
     * - ON_BUFFER_OVERWRITE:      At the time of buffer overwrite
     * - ON_BUFFER_READ:           At the time of buffer read
     * - ON_SEND:                  At the time of sending to InPort
     * - ON_RECEIVED:              At the time of finishing sending to InPort
     * - ON_SENDER_TIMEOUT:        At the time of timeout of OutPort
     * - ON_SENDER_ERROR:          At the time of error of OutPort
     * - ON_RECEIVER_FULL:         At the time of bufferfull of InPort
     * - ON_RECEIVER_TIMEOUT:      At the time of timeout of InPort
     * - ON_RECEIVER_ERROR:        At the time of error of InPort
     *
     * Listeners should have the following function operator().
     *
     * ConnectorDataListener::
     *         operator()(const ConnectorProfile&, const cdrStream&)
     *
     * The ownership of the given listener object is transferred to
     * this OutPort object in default.  The given listener object will
     * be destroied automatically in the OutPort's dtor or if the
     * listener is deleted by removeConnectorDataListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    void addConnectorDataListener(ConnectorDataListenerType listener_type,
                                  ConnectorDataListener* listener,
                                  bool autoclean = true);


    /*!
     * @if jp
     * @brief ConnectorDataListener �ꥹ�ʤ�������
     *
     * ���ꤷ���Ƽ�ꥹ�ʤ������롣
     * 
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     *
     * @else
     * @brief Removing BufferDataListener type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void removeConnectorDataListener(ConnectorDataListenerType listener_type,
                                     ConnectorDataListener* listener);
    

    /*!
     * @if jp
     * @brief ConnectorListener �ꥹ�ʤ��ɲä���
     *
     * �Хåե��񤭹��ߤޤ����ɤ߽Ф����٥�Ȥ˴�Ϣ����Ƽ�ꥹ�ʤ����ꤹ�롣
     *
     * ����Ǥ���ꥹ�ʤΥ����פ�
     *
     * - ON_BUFFER_EMPTY:       �Хåե������ξ��
     * - ON_BUFFER_READTIMEOUT: �Хåե������ǥ����ॢ���Ȥ������
     *
     * �ꥹ�ʤϰʲ��Υ����˥������� operator() ��������Ƥ���ɬ�פ����롣
     *
     * ConnectorListener::operator()(const ConnectorProfile&)
     *
     * �ǥե���ȤǤϡ����δؿ���Ϳ�����ꥹ�ʥ��֥������Ȥν�ͭ����
     * OutPort�˰ܤꡢOutPort���λ��⤷���ϡ�
     * removeConnectorListener() �ˤ�������˼�ưŪ�˲��Τ���롣
     * �ꥹ�ʥ��֥������Ȥν�ͭ����ƤӽФ�¦�ǰݻ����������ϡ���3��
     * ���� false ����ꤷ����ưŪ�ʲ��Τ��������뤳�Ȥ��Ǥ��롣
     *
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     * @param autoclean �ꥹ�ʥ��֥������Ȥμ�ưŪ���Τ�Ԥ����ɤ����Υե饰
     *
     * @else
     * @brief Adding ConnectorListener type listener
     *
     * This operation adds certain listeners related to buffer writing and
     * reading events.
     * The following listener types are available.
     *
     * - ON_BUFFER_EMPTY:       At the time of buffer empty
     * - ON_BUFFER_READTIMEOUT: At the time of buffer read timeout
     *
     * Listeners should have the following function operator().
     *
     * ConnectorListener::operator()(const ConnectorProfile&)
     *  
     * The ownership of the given listener object is transferred to
     * this OutPort object in default.  The given listener object will
     * be destroied automatically in the OutPort's dtor or if the
     * listener is deleted by removeConnectorListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    void addConnectorListener(ConnectorListenerType callback_type,
                              ConnectorListener* listener,
                              bool autoclean = true);

    /*!
     * @if jp
     * @brief ConnectorDataListener �ꥹ�ʤ�������
     *
     * ���ꤷ���Ƽ�ꥹ�ʤ������롣
     * 
     * @param listener_type �ꥹ�ʥ�����
     * @param listener �ꥹ�ʥ��֥������ȤؤΥݥ���
     *
     * @else
     * @brief Removing BufferDataListener type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void removeConnectorListener(ConnectorListenerType callback_type,
                                 ConnectorListener* listener);

    /*!
     * @if jp
     * @brief endian ������֤�
     *
     * endian �����bool�ͤ��֤���
     *
     * @return m_littleEndian ��little�ξ��true��big�ξ��false ���֤���
     *
     * @else
     * @brief
     *
     * return it whether endian setting.
     *
     *@return Return true in the case of "little", false in "big" than it.
     *
     * @endif
     */
    bool isLittleEndian();

    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port ����³��Ԥ�
     *
     * Ϳ����줿 ConnectoionProfile �ξ���˴�Ť���Port�֤���³���Ω
     * ���롣���δؿ��ϼ�˥��ץꥱ�������ץ�����ġ��뤫��Ƥӽ�
     * �����Ȥ�����Ȥ��Ƥ��롣
     * 
     * @param connector_profile ConnectorProfile
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation establishes connection according to the given
     * ConnectionProfile inforamtion. This function is premised on
     * calling from mainly application program or tools.
     *
     * @param connector_profile The ConnectorProfile.
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    connect(ConnectorProfile& connector_profile)
      throw (CORBA::SystemException);

  protected:

    /*!
     * @if jp
     * @brief Interface������������
     *
     * Interface�����������롣
     * ������ ConnectorProfile �˳�Ǽ����Ƥ��� dataflow_type �� push ��
     * �ξ��ϡ����ꤵ�줿 interface_type �� InPortProvider �˴ؤ������
     * �� ConnectorProfile::properties �˽���߸ƤӽФ�¦���᤹��
     *
     *  dataport.dataflow_type
     *
     * @param connector_profile ���ͥ����ץ�ե�����
     *
     * @return ReturnCode_t ���Υ꥿���󥳡���
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.
     * Assign the Provider information that owned by this port
     * to ConnectorProfile#properties
     *
     * @param connector_profile The connector profile
     *
     * @return The return code of ReturnCode_t type
     *
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
     * @brief Subscribe to the interface
     *
     * Subscribe to interface.
     * Derive Provider information that matches Consumer owned by the Port 
     * from ConnectorProfile#properties and 
     * set the Consumer to the reference of the CORBA object.
     *
     * @param connector_profile The connector profile
     *
     * @return ReturnCode_t The return code of ReturnCode_t type
     *
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
     * @brief Disconnect the interface connection
     *
     * Disconnect the interface connection.
     * Release all objects set in Consumer associated with 
     * given ConnectorProfile and unscribe the interface.
     *
     * @param connector_profile The connector profile
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);


    /*!
     * @if jp
     * @brief InPort provider �ν����
     * @else
     * @brief InPort provider initialization
     * @endif
     */
    void initProviders();

    /*!
     * @if jp
     * @brief OutPort consumer �ν����
     * @else
     * @brief OutPort consumer initialization
     * @endif
     */
    void initConsumers();

    /*!
     * @if jp
     * @brief InPort provider ������
     *
     * InPortProvider ��������������� ConnectorProfile �˸������롣
     * �����˼��Ԥ������ 0 ���֤���
     *
     * @else
     * @brief InPort provider creation
     * @endif
     */
    InPortProvider*
    createProvider(ConnectorProfile& cprof, coil::Properties& prop);

    /*!
     * @if jp
     * @brief OutPort consumer ������
     *
     * OutPortConsumer ���������롣
     * �����˼��Ԥ������ 0 ���֤���
     *
     * @else
     * @brief InPort provider creation
     * @endif
     */
    OutPortConsumer*
    createConsumer(const ConnectorProfile& cprof, coil::Properties& prop);

    /*!
     * @if jp
     * @brief InPortPushConnector ������
     *
     * Connector ������������������������� m_connectors ����¸���롣
     * �����˼��Ԥ������ 0 ���֤���
     *
     * @else
     * @brief InPortPushConnector creation
     * @endif
     */
    InPortConnector*
    createConnector(ConnectorProfile& cprof, coil::Properties& prop,
                    InPortProvider* provider);
    /*!
     * @if jp
     * @brief InPortPullConnector ������
     *
     * Connector ������������������������� m_connectors ����¸���롣
     * �����˼��Ԥ������ 0 ���֤���
     *
     * @else
     * @brief InPortPullConnector creation
     * @endif
     */
    InPortConnector*
    createConnector(const ConnectorProfile& cprof, coil::Properties& prop,
                    OutPortConsumer* consumer);

  protected:
    bool m_singlebuffer;
    CdrBufferBase* m_thebuffer;
    coil::Properties m_properties;
    coil::vstring m_providerTypes;
    coil::vstring m_consumerTypes;
    ConnectorList m_connectors;
    bool m_littleEndian;

    ConnectorListeners m_listeners;
  };
}; // namespace RTC

#endif // RTC_INPORTBASE_H
