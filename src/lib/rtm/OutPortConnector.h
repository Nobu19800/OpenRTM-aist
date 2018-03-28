// -*- C++ -*-
/*!
 * @file OutPortConnector.h
 * @brief OutPortConnector class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
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

#ifndef RTC_OUTPORTCONNECTOR_H
#define RTC_OUTPORTCONNECTOR_H

#include <rtm/SystemLogger.h>
#include <rtm/ConnectorBase.h>
#include <rtm/ConnectorListener.h>
#include <rtm/DirectInPortBase.h>
#include <rtm/PortBase.h>



namespace RTC
{
  class InPortBase;
  /*!
   * @if jp
   * @class OutPortConnector
   * @brief OutPortConnector ���쥯�饹
   *
   * OutPort �� Push/Pull �Ƽ� Connector �����������뤿���
   * ���쥯�饹��
   *
   * @since 1.0.0
   *
   * @else
   * @class OutPortConnector
   * @brief OutPortConnector base class
   *
   * The base class to derive subclasses for OutPort's Push/Pull Connectors
   *
   * @since 1.0.0
   *
   * @endif
   */
  class OutPortConnector
    : public ConnectorBase
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    OutPortConnector(ConnectorInfo& info, ConnectorListeners& listeners);

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~OutPortConnector();
   /*!
     * @if jp
     * @brief Profile ����
     *
     * Connector Profile ���������
     *
     * @else
     * @brief Getting Profile
     *
     * This operation returns Connector Profile
     *
     * @endif
     */
    const ConnectorInfo& profile();

    /*!
     * @if jp
     * @brief Connector ID ����
     *
     * Connector ID ���������
     *
     * @else
     * @brief Getting Connector ID
     *
     * This operation returns Connector ID
     *
     * @endif
     */
    const char* id();

    /*!
     * @if jp
     * @brief Connector ̾����
     *
     * Connector ̾���������
     *
     * @else
     * @brief Getting Connector name
     *
     * This operation returns Connector name
     *
     * @endif
     */
    const char* name();

    /*!
     * @if jp
     * @brief ��³����ؿ�
     *
     * Connector ���ݻ����Ƥ�����³��������
     *
     * @else
     * @brief Disconnect connection
     *
     * This operation disconnect this connection
     *
     * @endif
     */
    virtual ReturnCode disconnect() = 0;

    /*!
     * @if jp
     * @brief Buffer ���������
     *
     * Connector ���ݻ����Ƥ��� Buffer ���֤�
     *
     * @else
     * @brief Getting Buffer
     *
     * This operation returns this connector's buffer
     *
     * @endif
     */
    virtual CdrBufferBase* getBuffer() = 0;

    /*!
     * @if jp
     * @brief write �ؿ�
     *
     * OutPort ����ǡ����� Buffer �� write ����ؿ�
     *
     * @else
     * @brief Destructor
     *
     * The write function to write data from OutPort to Buffer
     *
     * @endif
     */
    virtual ReturnCode write(cdrMemoryStream& data) = 0;

    /*!
     * @if jp
     * @brief endian����������
     *
     * endian�����פ����ꤹ��
     *
     * @else
     * @brief Setting an endian type
     *
     * This operation set this connector's endian type
     *
     * @endif
     */
    virtual void setEndian(const bool endian_type);

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
    virtual bool isLittleEndian();

    /*!
     * @if jp
     * @brief �ǡ��������Ѵ��ƥ�ץ졼��
     *
     * Timed* ���� CdrMemoryStream ���Ѵ����롣
     *
     * @else
     * @brief The conversion template of the data type
     *
     * This is convert it from Timed* into CdrStream.
     *
     * @endif
     */
    template <class DataType>
    ReturnCode write(DataType& data)
    {
      if (m_directInPort != NULL)
        {
			DirectInPortBase<DataType>* inport = static_cast<DirectInPortBase<DataType>*>(m_directInPort->getDirectPort());
			
          if (inport->isNew())
            {
              // ON_BUFFER_OVERWRITE(In,Out), ON_RECEIVER_FULL(In,Out) callback
              m_listeners.
                connectorData_[ON_BUFFER_OVERWRITE].notify(m_profile, data);
              m_inPortListeners->
                connectorData_[ON_BUFFER_OVERWRITE].notify(m_profile, data);
              m_listeners.
                connectorData_[ON_RECEIVER_FULL].notify(m_profile, data);
              m_inPortListeners->
                connectorData_[ON_RECEIVER_FULL].notify(m_profile, data);
              RTC_PARANOID(("ON_BUFFER_OVERWRITE(InPort,OutPort), "
                            "ON_RECEIVER_FULL(InPort,OutPort) "
                            "callback called in direct mode."));
            }
          // ON_BUFFER_WRITE(In,Out) callback
          m_listeners.
            connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
          m_inPortListeners->
            connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
          RTC_PARANOID(("ON_BUFFER_WRITE(InPort,OutPort), "
                            "callback called in direct mode."));
          inport->write(data); // write to InPort variable!!
          // ON_RECEIVED(In,Out) callback
          m_listeners.
            connectorData_[ON_RECEIVED].notify(m_profile, data);
          m_inPortListeners->
            connectorData_[ON_RECEIVED].notify(m_profile, data);
          RTC_PARANOID(("ON_RECEIVED(InPort,OutPort), "
                        "callback called in direct mode."));
          return PORT_OK;
        }
      // normal case
#ifdef ORB_IS_ORBEXPRESS
      m_cdr.cdr.rewind();

      RTC_TRACE(("connector endian: %s", isLittleEndian() ? "little":"big"));
      m_cdr.cdr.is_little_endian(isLittleEndian());
      m_cdr.cdr << data;
#elif defined(ORB_IS_TAO)
      m_cdr.cdr.reset();
      RTC_TRACE(("connector endian: %s", isLittleEndian() ? "little" : "big"));
      m_cdr.cdr << data;
#else
      m_cdr.rewindPtrs();

      RTC_TRACE(("connector endian: %s", isLittleEndian() ? "little":"big"));
      m_cdr.setByteSwapFlag(isLittleEndian());
      data >>= m_cdr;
#endif
      return write(m_cdr);
    }

	bool setInPort(InPortBase* directInPort);
	/*!
	* @if jp
	* @brief �����쥯����³�⡼�ɤ�����
	*
	*
	* @else
	* @brief
	*
	*
	* @endif
	*/
	virtual void setPullDirectMode();
	/*!
	* @if jp
	* @brief �����쥯����³�⡼�ɤ���Ƚ��
	*
	* @return True�������쥯����³�⡼��,false������ʳ�
	*
	* @else
	* @brief
	*
	*
	* @endif
	*/
	virtual bool pullDirectMode();
  protected:
    /*!
     * @if jp
     * @brief �������ȥ꡼��
     * @else
     * @brief Logger streamf
     * @endif
     */
    Logger rtclog;
    /*!
     * @if jp
     * @brief Port �� PortProfile
     * @else
     * @brief PortProfile of the Port
     * @endif
     */
    ConnectorInfo m_profile;
    /*!
     * @if jp
     * @brief ��³����ǥ����� 
     * @else
     * @brief Connected Endian
     * @endif
     */
    bool m_littleEndian;
    /*!
     * @if jp
     * @brief cdr���ȥ꡼��
     * @else
     * @brief CDR stream
     * @endif
     */
    cdrMemoryStream m_cdr;


    /*!
     * @if jp
     * @brief Ʊ��ץ�����Υԥ�InPort�Υݥ���
     * @else
     * @brief InProt pointer to the peer in the same process
     * @endif
     */
    PortBase* m_directInPort;

    /*!
     * @if jp
     * @brief ConnectorListenrs �ؤλ���
     * @else
     * @brief A reference to a ConnectorListener
     * @endif
     */
    ConnectorListeners& m_listeners;

    /*!
     * @if jp
     * @brief InPort ¦�� ConnectorListenrs �ؤλ���
     * @else
     * @brief A pointer to a InPort's ConnectorListener
     * @endif
     */
    ConnectorListeners* m_inPortListeners;

	bool m_directMode;

  };
}; // namespace RTC

#endif // RTC_CONNECTORBASE_H
