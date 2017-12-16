// -*- C++ -*-
/*!
 * @file ConnectorListener.h
 * @brief connector listener class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009-2017
 *     Noriaki Ando
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_CONNECTORLISTENER_H
#define RTC_CONNECTORLISTENER_H

#include <vector>
#include <utility>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <rtm/RTC.h>
#include <rtm/ConnectorBase.h>

class cdrMemoryStream;

namespace RTC
{
  class ConnectorInfo;
  /*!
   * @if jp
   * @class ConnectorListenerStatus mixin class
   * @brief ConnectorListenerStatus mixin ���饹
   *
   * ���Υ��饹�ϡ�enum������줿�꥿���󥳡��ɤ�ConnectorListener��
   * Ϣ�Υ��֥��饹�Ƕ������Ѥ��뤿��� mixin ���饹�Ǥ��롣���Υ꥿��
   * �󥳡��ɤ���Ѥ��륯�饹�Ǥϡ�ConnectorListenerStatus ���饹��
   * public �Ѿ���������define ���Ƥ��� CONNLISTENER_STATUS_ENUM �򥯥�
   * ����˵��Ҥ��뤳�Ȥ����Ѳ�ǽ�Ȥʤ롣����ˤ�ꡢenum ��
   * ReturnCode ���Ȥ��� typedef �����ʸ� ReturnCode �����ѤǤ���褦��
   * ����ȤȤ�ˡ�̾�����֤� enum ������줿�Ƽ��̻Ҥ��������饹̾����
   * �����Ƴ�����롣
   *
   * @else
   * @class DataPortStatus mixin class
   * @brief DataPortStatus mixin class
   *
   * This is a mixin class to provide enumed return codes that are
   * commonly utilised in connector listener related sub-classes. To
   * use this class, sub-class should inherit this class as a public
   * super class, and declare CONNLISTENERSTATUS_ENUM defined
   * below. Consequently, ReturnCode type that is typedefed by this
   * macro can be used in the sub-class, and enumed identifiers are
   * imported to the class's namespace.
   *
   * @endif
   */
  class ConnectorListenerStatus
  {
  public:
    enum Enum
      {
        NO_CHANGE    = 0,
        INFO_CHANGED = 1 << 0,
        DATA_CHANGED = 1 << 1,
        BOTH_CHANGED = INFO_CHANGED | DATA_CHANGED
      };
  };
  ConnectorListenerStatus::Enum operator|(ConnectorListenerStatus::Enum L,
                                          ConnectorListenerStatus::Enum R);
  ConnectorListenerStatus::Enum operator&(ConnectorListenerStatus::Enum L,
                                          ConnectorListenerStatus::Enum R);

  /*!
   * @if jp
   *
   * @brief ::RTC::ConnDataPortStatus Ƴ��
   *
   * ::RTC::DataPortStatus ���������Ƥ��� Enum �Τ��٤ƤΥ��Ф�͡���
   * ���ڡ�����Ƴ�����뤿��Υޥ���DataPortStatus �����Ѥ��륯�饹�ˤ�
   * ���ơ����饹�������Ƭ�ˤ����� DATAPORTSTATUS_ENUM �򵭺ܤ�������ǡ�
   * DataPortStatus ���������Ƥ��� enum ���Ф�̾�����黻�Ҥʤ��˥�
   * ��������ǽ�ˤʤ롣
   *
   * @else
   *
   * @brief Importing ::RTC::DataPortStatus macro
   *
   * This macro imports all the member of enum declared in
   * ::RTC::DataPortStatus into the current namespace.  Inserting at the
   * head of class declaration, classes which utilize DataPortStatus can
   * access Enum members of DataPortStatus without using namespace
   * resolve operator.
   *
   * @endif
   */
#define USE_CONNLISTENER_STATUS                             \
  typedef ::RTC::ConnectorListenerStatus::Enum ReturnCode;  \
  using ::RTC::ConnectorListenerStatus::NO_CHANGE;          \
  using ::RTC::ConnectorListenerStatus::INFO_CHANGED;       \
  using ::RTC::ConnectorListenerStatus::DATA_CHANGED;       \
  using ::RTC::ConnectorListenerStatus::BOTH_CHANGED;

  /*!
   * @if jp
   * @brief ConnectorDataListener �Υ�����
   *
   * - ON_BUFFER_WRITE:          �Хåե��񤭹��߻�
   * - ON_BUFFER_FULL:           �Хåե��ե��
   * - ON_BUFFER_WRITE_TIMEOUT:  �Хåե��񤭹��ߥ����ॢ���Ȼ�
   * - ON_BUFFER_OVERWRITE:      �Хåե���񤭻�
   * - ON_BUFFER_READ:           �Хåե��ɤ߽Ф���
   * - ON_SEND:                  InProt�ؤ�������
   * - ON_RECEIVED:              InProt�ؤ�������λ��
   * - ON_RECEIVER_FULL:         InProt¦�Хåե��ե��
   * - ON_RECEIVER_TIMEOUT:      InProt¦�Хåե������ॢ���Ȼ�
   * - ON_RECEIVER_ERROR:        InProt¦���顼��
   *
   * @else
   * @brief The types of ConnectorDataListener
   *
   * - ON_BUFFER_WRITE:          At the time of buffer write
   * - ON_BUFFER_FULL:           At the time of buffer full
   * - ON_BUFFER_WRITE_TIMEOUT:  At the time of buffer write timeout
   * - ON_BUFFER_OVERWRITE:      At the time of buffer overwrite
   * - ON_BUFFER_READ:           At the time of buffer read
   * - ON_SEND:                  At the time of sending to InPort
   * - ON_RECEIVED:              At the time of finishing sending to InPort
   * - ON_RECEIVER_FULL:         At the time of bufferfull of InPort
   * - ON_RECEIVER_TIMEOUT:      At the time of timeout of InPort
   * - ON_RECEIVER_ERROR:        At the time of error of InPort
   *
   * @endif
   */
  enum ConnectorDataListenerType
    {
      ON_BUFFER_WRITE = 0,
      ON_BUFFER_FULL,
      ON_BUFFER_WRITE_TIMEOUT,
      ON_BUFFER_OVERWRITE,
      ON_BUFFER_READ,
      ON_SEND,
      ON_RECEIVED,
      ON_RECEIVER_FULL,
      ON_RECEIVER_TIMEOUT,
      ON_RECEIVER_ERROR,
      CONNECTOR_DATA_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class ConnectorDataListener ���饹
   * @brief ConnectorDataListener ���饹
   *
   * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������Ƽ磻�٥�Ȥ��Ф��륳��
   * ��Хå���¸�����ꥹ�ʥ��饹�δ��쥯�饹��
   *
   * �������å���OutPort���Ф��ƥǡ����񤭹��ߡ�InPort¦�ǥǡ�������
   * �������ޤǤδ֤�ȯ������Ƽ磻�٥�Ȥ�եå����륳����Хå�����
   * �ꤹ�뤳�Ȥ��Ǥ��롣�ʤ����ꥹ�ʡ����饹��2����¸�ߤ����Хåե���
   * ����������Υ�����Хå��ǡ����λ�����ͭ���ʥǡ�����ե��󥯥��ΰ�
   * ���Ȥ��Ƽ������ ConnectorDataListener �Ǥ��ꡢ�⤦�����ϥǡ�����
   * ��ץƥ���Хåե��ɤ߹��߻��Υ����ॢ���Ȥʤɥǡ����������Ǥ��ʤ�
   * ���ʤɤ˥����뤵���ե��󥯥��ΰ����˲���Ȥ�ʤ餤
   * ConnecotorListener �����롣
   *
   * ConnectorDataListener ���饹�ˤ�äƥǡ�������Ϣ����ư���եå���
   * ������硢�ʲ�����Τ褦�ˡ����Υ��饹��Ѿ��������ͥ����ξ���ȥǡ�
   * ��������˼��ʲ��Τ褦�ʥ�����Хå����֥������Ȥ���������ǡ���
   * �ݡ��Ȥ�Ŭ�ڤʥ�����Хå�����ؿ����饳����Хå����֥������Ȥ򥻥�
   * �Ȥ���ɬ�פ����롣�ʤ���Data Listener �ˤϡ��ǡ����Ȥ��ƥޡ������
   * �󥰸�Υǡ���������˼�� ConnectorDataListener �ȡ��ǡ���������
   * �η��˥���ޡ�����뤷������ͤ�����˼�롢
   * ConnectorDataListenerT �����롣�ʲ�����ϡ�ConnectorDataListenerT
   * �������Ǥ��롣
   *
   * <pre>
   * class MyDataListener
   *   : public ConnectorDataListenerT<RTC::TimedLong>
   * {
   * public:
   *   MyDataListener(const char* name) : m_name(name) {}
   *   virtual ~MyDataListener() {}
   *   virtual ReturnCode operator()(ConnectorInfo& info, TimedLong& data)
   *   {
   *     std::cout << "Data Listener: " << m_name       << std::endl;
   *     std::cout << "Data:          " << data.data    << std::endl;
   *     std::cout << "Profile::name: " << info.name    << std::endl;
   *     std::cout << "Profile::id:   " << info.id      << std::endl;
   *     std::cout << "Profile::properties: "           << std::endl;
   *     std::cout << info.properties;
   *   };
   *   std::string m_name;
   * };
   * </pre>
   *
   * ���Τ褦�ˤ���������줿�ꥹ�ʥ��饹�ϡ��ʲ��Τ褦�˥ǡ����ݡ��Ȥ�
   * �Ф��ơ��ʲ��Τ褦�˥��åȤ���롣
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     m_outOut.
   *         addConnectorDataListener(ON_BUFFER_WRITE,
   *                                  new MyDataListener("ON_BUFFER_WRITE"));
   *    :
   * </pre>
   *
   * ��1������ "ON_BUFFER_WRITE" �ϡ�������Хå���եå�����ݥ���Ȥ�
   * ���ꡢ�ʲ�����󤹤��ͤ��뤳�Ȥ���ǽ�Ǥ��롣�ǡ����ݡ��Ȥˤϡ���
   * ³���˥ǡ�������������ˡ�ˤĤ��ơ����󥿡��ե����������ǡ����ե�
   * �������֥�����ץ�����������ꤹ�뤳�Ȥ��Ǥ��뤬�������������
   * ���եå������ݥ���Ȥϰۤʤ롣�ʲ��ˡ����󥿡��ե�������CORBA
   * CDR���ξ��Υ�����Хå������򼨤���
   *
   * OutPort:
   * -  Push��: Subscription Type�ˤ�ꤵ��˥��٥�Ȥμ��बʬ����롣
   *   - Flush: Flush���ˤϥХåե����ʤ����� ON_BUFFER �ϤΥ��٥�Ȥ�ȯ�����ʤ�
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   - New��
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_OVERWRITE
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   - Periodic��
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   .
   * - Pull��
   *   - ON_BUFFER_WRITE
   *   - ON_BUFFER_FULL
   *   - ON_BUFFER_WRITE_TIMEOUT
   *   - ON_BUFFER_OVERWRITE
   *   - ON_BUFFER_READ
   *   - ON_SEND
   *   .
   * InPort:
   * - Push��:
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_WRITE_OVERWRITE
   *     - ON_BUFFER_READ
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   * - Pull��
   *     - ON_BUFFER_READ
   *
   * @else
   * @class ConnectorDataListener class
   * @brief ConnectorDataListener class
   *
   * This class is abstract base class for listener classes that
   * realize callbacks for various events in the data port's
   * connectors.
   *
   * Callbacks can be hooked to the various kind of events which occur
   * throgh OutPort side data write action to InPort side data-read
   * action.  Two types listener classes exist. One is
   * ConnectorDataListener which receives valid data-port's data value
   * at that time such as buffer-full event, data-send event, and so
   * on. Other is ConnectorListener which does not receive any data
   * such as buffer-empty event, buffer-read-timeout event and so on.
   *
   * If you want to hook actions which related data-port's data by
   * ConnectorDataListener, a class which inherits this class should
   * be defined, and the functor should receive a connector
   * information and a data value as arguments. And then, the defined
   * class must be set to data-port object through its member
   * function, as follows.  Two types of ConnectorDataListeners are
   * available. One is "ConnectorDataListener" which receives
   * marshalled data as data value, the other is
   * "ConnectorDataListenerT" which receives unmarshalled data as data
   * value. The following example is the use of ConnectorDataListenerT.
   *
   * <pre>
   * class MyDataListener
   *   : public ConnectorDataListenerT<RTC::TimedLong>
   * {
   * public:
   *   MyDataListener(const char* name) : m_name(name) {}
   *   virtual ~MyDataListener() {}
   *   virtual ReturnCode operator()(ConnectorInfo& info, TimedLong& data)
   *   {
   *     std::cout << "Data Listener: " << m_name       << std::endl;
   *     std::cout << "Data:          " << data.data    << std::endl;
   *     std::cout << "Profile::name: " << info.name    << std::endl;
   *     std::cout << "Profile::id:   " << info.id      << std::endl;
   *     std::cout << "Profile::properties: "           << std::endl;
   *     std::cout << info.properties;
   *   };
   *   std::string m_name;
   * };
   * </pre>
   *
   * The listener class defained as above can be attached to a
   * data-port as follows.
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     m_outOut.
   *         addConnectorDataListener(ON_BUFFER_WRITE,
   *                                  new MyDataListener("ON_BUFFER_WRITE"));
   *    :
   * </pre>
   *
   * The first argument "ON_BUFFER_WRITE" specifies hook point of
   * callback, and the following values are available. Data-port can
   * be specified some properties such as interface-type,
   * dataflow-type, subscription type and so on. Available hook points
   * vary by the those settings. The following hook points are
   * available when interface type is CORBA CDR type.
   *
   * OutPort:
   * -  Push type: Available hook event varies by subscription type.
   *   - Flush: No ON_BUFFER* events since flush-type has no buffer.
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   - New type:
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_OVERWRITE
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   - Periodic type:
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   .
   * - Pull type:
   *   - ON_BUFFER_WRITE
   *   - ON_BUFFER_FULL
   *   - ON_BUFFER_WRITE_TIMEOUT
   *   - ON_BUFFER_OVERWRITE
   *   - ON_BUFFER_READ
   *   - ON_SEND
   *   .
   * InPort:
   * - Push type:
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_WRITE_OVERWRITE
   *     - ON_BUFFER_READ
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   * - Pull type
   *     - ON_BUFFER_READ
   *
   * @endif
   */
  class ConnectorDataListener
    : public ConnectorListenerStatus
  {
  public:
    USE_CONNLISTENER_STATUS;
    /*!
     * @if jp
     *
     * @brief ConnectorDataListenerType ��ʸ������Ѵ�
     *
     * ConnectorDataListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� ConnectorDataListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert ConnectorDataListenerType into the string.
     *
     * Convert ConnectorDataListenerType into the string.
     *
     * @param type The target ConnectorDataListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(ConnectorDataListenerType type)
    {
      static const char* typeString[] =
        {
          "ON_BUFFER_WRITE",
          "ON_BUFFER_FULL",
          "ON_BUFFER_WRITE_TIMEOUT",
          "ON_BUFFER_OVERWRITE",
          "ON_BUFFER_READ", 
          "ON_SEND", 
          "ON_RECEIVED",
          "ON_RECEIVER_FULL", 
          "ON_RECEIVER_TIMEOUT", 
          "ON_RECEIVER_ERROR",
          "CONNECTOR_DATA_LISTENER_NUM"
        };
      if (type < CONNECTOR_DATA_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorDataListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��᥽�å�
     *
     * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������Ƽ磻�٥�Ȥ��Ф��륳��
     * ��Хå��᥽�å�
     *
     * @else
     *
     * @brief Virtual Callback method
     *
     * This is a the Callback method to various events generated in Connector. 
     *
     * @endif
     */
    virtual ReturnCode operator()(ConnectorInfo& info,
                            cdrMemoryStream& data) = 0;
  };

  /*!
   * @if jp
   * @class ConnectorDataListenerT ���饹
   * @brief ConnectorDataListenerT ���饹
   *
   * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������Ƽ磻�٥�Ȥ��Ф��륳��
   * ��Хå���¸�����ꥹ�ʥ��饹�δ��쥯�饹��
   * 
   * ���Υ��饹�ϡ�operator()() ����2������ cdrMemoryStream ���ǤϤʤ���
   * �ºݤ˥ǡ����ݡ��Ȥǻ��Ѥ�����ѿ�����ƥ�ץ졼�Ȱ����Ȥ���
   * �Ϥ����Ȥ��Ǥ��롣
   *
   * @else
   * @class ConnectorDataListenerT class
   * @brief ConnectorDataListenerT class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in the data port's
   * connectors.
   *
   * This class template can have practical data types that are used
   * as typed variable for DataPort as an argument of template instead
   * of cdrMemoryStream.
   *
   * @endif
   */
  template <class DataType>
  class ConnectorDataListenerT
    : public ConnectorDataListener
  {
  public:
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorDataListenerT(){}

    /*!
     * @if jp
     *
     * @brief ������Хå��᥽�å�
     *
     * �ǡ�����ǡ����ݡ��Ȥǻ��Ѥ�����ѿ������Ѵ����� ConnectorDataListenerT
     * �Υ�����Хå��᥽�åɤ�ƤӽФ���
     *
     * @param info ConnectorInfo 
     * @param cdrdata cdrMemoryStream���Υǡ���
     *
     * @else
     *
     * @brief Callback method
     *
     * This method invokes the callback method of ConnectorDataListenerT. 
     * Data is converted into the variable type used in DataPort.
     *
     * @param info ConnectorInfo 
     * @param cdrdata Data of cdrMemoryStream type
     *
     * @endif
     */
    virtual ReturnCode operator()(ConnectorInfo& info,
                                  cdrMemoryStream& cdrdata)
    {
      DataType data;
      cdrMemoryStream cdr(cdrdata.bufPtr(), cdrdata.bufSize());

      // endian type check
      std::string endian_type;
      endian_type = info.properties.getProperty("serializer.cdr.endian",
                                                "little");
      coil::normalize(endian_type);
      std::vector<std::string> endian(coil::split(endian_type, ","));
      if (endian[0] == "little")
        {
          cdr.setByteSwapFlag(true);
        }
      else if (endian[0] == "big")
        {
          cdr.setByteSwapFlag(false);
        }
      data <<= cdr;
      ReturnCode ret = this->operator()(info, data);
      if (ret == DATA_CHANGED || ret == BOTH_CHANGED)
        {
          cdrdata.rewindPtrs();
          data >>= cdrdata;
        }
      return ret;
    }

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��᥽�å�
     *
     * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������Ƽ磻�٥�Ȥ��Ф��륳��
     * ��Хå��᥽�å�
     *
     * @else
     *
     * @brief Virtual Callback method
     *
     * This method invokes the callback method of ConnectorDataListenerT. 
     * Data is converted into the variable type used in DataPort.
     *
     * @endif
     */
    virtual ReturnCode operator()(ConnectorInfo& info,
                                  DataType& data) = 0;
  };


  /*!
   * @if jp
   * @brief ConnectorListener �Υ�����
   *  
   * - ON_BUFFER_EMPTY:       �Хåե������ξ��
   * - ON_BUFFER_READTIMEOUT: �Хåե������ǥ����ॢ���Ȥ������
   * - ON_SENDER_EMPTY:       OutPort¦�Хåե�����
   * - ON_SENDER_TIMEOUT:     OutPort¦�����ॢ���Ȼ�
   * - ON_SENDER_ERROR:       OutPort¦���顼��
   * - ON_CONNECT:            ��³��Ω��
   * - ON_DISCONNECT:         ��³���ǻ�
   *
   * @else
   * @brief The types of ConnectorListener
   * 
   * - ON_BUFFER_EMPTY:       At the time of buffer empty
   * - ON_BUFFER_READTIMEOUT: At the time of buffer read timeout
   * - ON_BUFFER_EMPTY:       At the time of empty of OutPort
   * - ON_SENDER_TIMEOUT:     At the time of timeout of OutPort
   * - ON_SENDER_ERROR:       At the time of error of OutPort
   * - ON_CONNECT:            At the time of connection
   * - ON_DISCONNECT:         At the time of disconnection
   *
   * @endif
   */
  enum ConnectorListenerType
    {
      ON_BUFFER_EMPTY = 0,
      ON_BUFFER_READ_TIMEOUT,
      ON_SENDER_EMPTY,
      ON_SENDER_TIMEOUT,
      ON_SENDER_ERROR,
      ON_CONNECT,
      ON_DISCONNECT,
      CONNECTOR_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class ConnectorListener ���饹
   * @brief ConnectorListener ���饹
   *
   * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������Ƽ磻�٥�Ȥ��Ф��륳��
   * ��Хå���¸�����ꥹ�ʥ��饹�δ��쥯�饹��
   *
   * �������å���OutPort���Ф��ƥǡ����񤭹��ߡ�InPort¦�ǥǡ�������
   * �������ޤǤδ֤�ȯ������Ƽ磻�٥�Ȥ�եå����륳����Хå�����
   * �ꤹ�뤳�Ȥ��Ǥ��롣�ʤ����ꥹ�ʡ����饹��2����¸�ߤ����Хåե���
   * ����������Υ�����Хå��ǡ����λ�����ͭ���ʥǡ�����ե��󥯥��ΰ�
   * ���Ȥ��Ƽ������ ConnectorDataListener �Ǥ��ꡢ�⤦�����ϥǡ�����
   * ��ץƥ���Хåե��ɤ߹��߻��Υ����ॢ���Ȥʤɥǡ����������Ǥ��ʤ�
   * ���ʤɤ˥����뤵���ե��󥯥��ΰ����˲���Ȥ�ʤ餤
   * ConnecotorListener �����롣
   *
   * ConnectorListener ���饹�ˤ�äƴ�Ϣ����ư���եå���������硢��
   * ������Τ褦�ˡ����Υ��饹��Ѿ��������ͥ����ξ��������˼��ʲ�
   * �Τ褦�ʥ�����Хå����֥������Ȥ���������ǡ����ݡ��Ȥ�Ŭ�ڤʥ���
   * ��Хå�����ؿ����饳����Хå����֥������Ȥ򥻥åȤ���ɬ�פ����롣
   *
   * <pre>
   * class MyListener
   *   : public ConnectorListener
   * {
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *   virtual ReturnCode operator()(ConnectorInfo& info)
   *   {
   *     std::cout << "Data Listener: " << m_name       << std::endl;
   *     std::cout << "Profile::name: " << info.name    << std::endl;
   *     std::cout << "Profile::id:   " << info.id      << std::endl;
   *     std::cout << "Profile::properties: "           << std::endl;
   *     std::cout << info.properties;
   *   };
   *   std::string m_name;
   * };
   * </pre>
   *
   * ���Τ褦�ˤ���������줿�ꥹ�ʥ��饹�ϡ��ʲ��Τ褦�˥ǡ����ݡ��Ȥ�
   * �Ф��ơ��ʲ��Τ褦�˥��åȤ���롣
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     m_outOut.
   *         addConnectorListener(ON_BUFFER_EMPTY,
   *                              new MyListener("ON_BUFFER_EMPTY"));
   *    :
   * </pre>
   *
   * ��1������ "ON_BUFFER_EMPTY" �ϡ�������Хå���եå�����ݥ���Ȥ�
   * ���ꡢ�ʲ�����󤹤��ͤ��뤳�Ȥ���ǽ�Ǥ��롣�ǡ����ݡ��Ȥˤϡ���
   * ³���˥ǡ�������������ˡ�ˤĤ��ơ����󥿡��ե����������ǡ����ե�
   * �������֥�����ץ�����������ꤹ�뤳�Ȥ��Ǥ��뤬�������������
   * ���եå������ݥ���Ȥϰۤʤ롣�ʲ��ˡ����󥿡��ե�������CORBA
   * CDR���ξ��Υ�����Хå������򼨤���
   *
   * OutPort:
   * -  Push��: Subscription Type�ˤ�ꤵ��˥��٥�Ȥμ��बʬ����롣
   *   - Flush: Flush���ˤϥХåե����ʤ����� ON_BUFFER �ϤΥ��٥�Ȥ�ȯ�����ʤ�
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   - New��
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   - Periodic��
   *     - ON_BUFFER_EMPTY
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_SENDER_EMPTY
   *     - ON_SENDER_ERROR
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   .
   * - Pull��
   *   - ON_BUFFER_EMPTY
   *   - ON_BUFFER_READ_TIMEOUT
   *   - ON_SENDER_EMPTY
   *   - ON_SENDER_TIMEOUT
   *   - ON_SENDER_ERROR
   *   - ON_CONNECT
   *   - ON_DISCONNECT
   *   .
   * InPort:
   * - Push��:
   *     - ON_BUFFER_EMPTY
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   * - Pull��
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *
   * @else
   * @class ConnectorListener class
   * @brief ConnectorListener class
   *
   * This class is abstract base class for listener classes that
   * realize callbacks for various events in the data port's
   * connectors.
   *
   * Callbacks can be hooked to the various kind of events which occur
   * throgh OutPort side data write action to InPort side data-read
   * action. Two types listener classes exist. One is
   * ConnectorDataListener which receives valid data-port's data value
   * at that time such as buffer-full event, data-send event, and so
   * on. Other is ConnectorListener which does not receive any data
   * such as buffer-empty event, buffer-read-timeout event and so on.
   *
   * If you want to hook related actions by
   * ConnectorListener, a class which inherits this class should
   * be defined, and the functor should receive a connector
   * information as an argument. And then, the defined
   * class must be set to data-port object through its member
   * function, as follows.
   *
   * <pre>
   * class MyListener
   *   : public ConnectorListener
   * {
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *   virtual ReturnCode operator()(ConnectorInfo& info)
   *   {
   *     std::cout << "Data Listener: " << m_name       << std::endl;
   *     std::cout << "Profile::name: " << info.name    << std::endl;
   *     std::cout << "Profile::id:   " << info.id      << std::endl;
   *     std::cout << "Profile::properties: "           << std::endl;
   *     std::cout << info.properties;
   *   };
   *   std::string m_name;
   * };
   * </pre>
   *
   * The listener class defained as above can be attached to a
   * data-port as follows.
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     m_outOut.
   *         addConnectorListener(ON_BUFFER_EMPTY,
   *                              new MyDataListener("ON_BUFFER_EMPTY"));
   *    :
   * </pre>
   *
   * The first argument "ON_BUFFER_EMPTY" specifies hook point of
   * callback, and the following values are available. Data-port can
   * be specified some properties such as interface-type,
   * dataflow-type, subscription type and so on. Available hook points
   * vary by the those settings. The following hook points are
   * available when interface type is CORBA CDR type.
   *
   * OutPort:
   * -  Push type: Available hook event varies by subscription type.
   *   - Flush: No ON_BUFFER* events since flush-type has no buffer.
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   - New type:
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   - Periodic type:
   *     - ON_BUFFER_EMPTY
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_SENDER_EMPTY
   *     - ON_SENDER_ERROR
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   .
   * - Pull type:
   *   - ON_BUFFER_EMPTY
   *   - ON_BUFFER_READ_TIMEOUT
   *   - ON_SENDER_EMPTY
   *   - ON_SENDER_TIMEOUT
   *   - ON_SENDER_ERROR
   *   - ON_CONNECT
   *   - ON_DISCONNECT
   *   .
   * InPort:
   * - Push type:
   *     - ON_BUFFER_EMPTY
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   * - Pull type:
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *
   * @endif
   */
  class ConnectorListener
    : public ConnectorListenerStatus
  {
  public:
    USE_CONNLISTENER_STATUS;
    /*!
     * @if jp
     *
     * @brief ConnectorListenerType ��ʸ������Ѵ�
     *
     * ConnectorListenerType ��ʸ������Ѵ�����
     *
     * @param type �Ѵ��о� ConnectorListenerType
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert ConnectorListenerType into the string.
     *
     * Convert ConnectorListenerType into the string.
     *
     * @param type The target ConnectorListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(ConnectorListenerType type)
    { 
      static const char* typeStr[] =
        {
          "ON_BUFFER_EMPTY",
          "ON_BUFFER_READ_TIMEOUT",
          "ON_SENDER_EMPTY", 
          "ON_SENDER_TIMEOUT", 
          "ON_SENDER_ERROR", 
          "ON_CONNECT",
          "ON_DISCONNECT",
          "CONNECTOR_LISTENER_NUM"
        };
      if (type < CONNECTOR_LISTENER_NUM) { return typeStr[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorListener();

    /*!
     * @if jp
     *
     * @brief ���ۥ�����Хå��᥽�å�
     *
     * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������Ƽ磻�٥�Ȥ��Ф��륳��
     * ��Хå��᥽�å�
     *
     * @else
     *
     * @brief Virtual Callback method
     *
     * This method invokes the callback method of ConnectorDataListenerT. 
     * Data is converted into the variable type used in DataPort.
     *
     * @endif
     */
    virtual ReturnCode operator()(ConnectorInfo& info) = 0;
  };


  /*!
   * @if jp
   * @class ConnectorDataListenerHolder
   * @brief ConnectorDataListener �ۥ�����饹
   *
   * ʣ���� ConnectorDataListener ���ݻ����������륯�饹��
   *
   * @else
   * @class ConnectorDataListenerHolder
   * @brief ConnectorDataListener holder class
   *
   * This class manages one ore more instances of ConnectorDataListener class.
   *
   * @endif
   */
  class ConnectorDataListenerHolder
    : public ConnectorListenerStatus
  {
    typedef std::pair<ConnectorDataListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    USE_CONNLISTENER_STATUS;
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    ConnectorDataListenerHolder();
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorDataListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ����ɲ�
     *
     * �ꥹ�ʡ����ɲä��롣
     *
     * @param listener �ɲä���ꥹ��
     * @param autoclean true:�ǥ��ȥ饯���Ǻ������,
     *                  false:�ǥ��ȥ饯���Ǻ�����ʤ�
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener. 
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor. 
     * @endif
     */
    void addListener(ConnectorDataListener* listener, bool autoclean);
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ��κ��
     *
     * �ꥹ�ʤ������롣
     *
     * @param listener �������ꥹ��
     * @else
     *
     * @brief Remove the listener. 
     *
     * This method removes the listener. 
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(ConnectorDataListener* listener);
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ��ο�������
     *
     * ������Ͽ����Ƥ���ꥹ�ʡ��������롣
     *
     * @return listener��
     * @else
     *
     * @brief Getting number of listeners.
     *
     * This method returns current number of listenrs.
     *
     * @return number of listeners
     * @endif
     */
    size_t size();

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ������Τ���
     *
     * ��Ͽ����Ƥ���ꥹ�ʤΥ�����Хå��᥽�åɤ�ƤӽФ���
     *
     * @param info ConnectorInfo
     * @param cdrdata �ǡ���
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectorInfo
     * @param cdrdata Data
     * @endif
     */
    ReturnCode notify(ConnectorInfo& info,
                      cdrMemoryStream& cdrdata);

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ������Τ���(�ǡ�����������)
     *
     * ��Ͽ����Ƥ���ꥹ�ʤΥ�����Хå��᥽�åɤ�ƤӽФ���
     * ConnectorDataListenerT ���Υ�����Хå��Τߥ����뤵��롣
     *
     * @param info ConnectorInfo
     * @param typeddata �ǡ����ʥǡ��������ꤢ���
     * @else
     *
     * @brief Notify listeners. (Typed data version)
     *
     * This calls the Callback method of the registered listener.
     * This operation calls only ConnectorDataListenerT type callback.
     *
     * @param info ConnectorInfo
     * @param typeddata Data
     * @endif
     */
    template <class DataType>
    ReturnCode notify(ConnectorInfo& info, DataType& typeddata)
    {
      Guard guard(m_mutex);
      ReturnCode ret(NO_CHANGE);
      for (int i(0), len(m_listeners.size()); i < len; ++i)
        {
          ConnectorDataListenerT<DataType>* listener(0);
          listener =
          dynamic_cast<ConnectorDataListenerT<DataType>*>(m_listeners[i].first);
          if (listener != 0)
            {
              ret = ret | listener->operator()(info, typeddata);
            }
          else
            {
              cdrMemoryStream cdr;
              typeddata >>= cdr;
              ret = ret | m_listeners[i].first->operator()(info, cdr);
            }
        }
      return ret;
    }

  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  /*!
   * @if jp
   * @class ConnectorListenerHolder 
   * @brief ConnectorListener �ۥ�����饹
   *
   * ʣ���� ConnectorListener ���ݻ����������륯�饹��
   *
   * @else
   * @class ConnectorListenerHolder
   * @brief ConnectorListener holder class
   *
   * This class manages one ore more instances of ConnectorListener class.
   *
   * @endif
   */
  class ConnectorListenerHolder
    : public ConnectorListenerStatus
  {
    typedef std::pair<ConnectorListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    USE_CONNLISTENER_STATUS;
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    ConnectorListenerHolder();
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ����ɲ�
     *
     * �ꥹ�ʡ����ɲä��롣
     *
     * @param listener �ɲä���ꥹ��
     * @param autoclean true:�ǥ��ȥ饯���Ǻ������,
     *                  false:�ǥ��ȥ饯���Ǻ�����ʤ�
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener. 
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor. 
     * @endif
     */
    void addListener(ConnectorListener* listener, bool autoclean);
    
    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ��κ��
     *
     * �ꥹ�ʤ������롣
     *
     * @param listener �������ꥹ��
     * @else
     *
     * @brief Remove the listener. 
     *
     * This method removes the listener. 
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(ConnectorListener* listener);

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ��ο�������
     *
     * ������Ͽ����Ƥ���ꥹ�ʡ��������롣
     *
     * @return listener��
     * @else
     *
     * @brief Getting number of listeners.
     *
     * This method returns current number of listenrs.
     *
     * @return number of listeners
     * @endif
     */
    size_t size();

    /*!
     * @if jp
     *
     * @brief �ꥹ�ʡ������Τ���
     *
     * ��Ͽ����Ƥ���ꥹ�ʤΥ�����Хå��᥽�åɤ�ƤӽФ���
     *
     * @param info ConnectorInfo
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectorInfo
     * @endif
     */
    ReturnCode notify(ConnectorInfo& info);
      
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };
  
  /*!
   * @if jp
   * @class ConnectorListeners
   * @brief ConnectorListeners ���饹
   *
   *
   * @else
   * @class ConnectorListeners
   * @brief ConnectorListeners class
   *
   *
   * @endif
   */
  class ConnectorListeners
  {
  public:
    /*!
     * @if jp
     * @brief ConnectorDataListenerType�ꥹ������
     * ConnectorDataListenerType�ꥹ�ʤ��Ǽ
     * @else
     * @brief ConnectorDataListenerType listener array
     * The ConnectorDataListenerType listener is stored.
     * @endif
     */
    ConnectorDataListenerHolder connectorData_[CONNECTOR_DATA_LISTENER_NUM];
    /*!
     * @if jp
     * @brief ConnectorListenerType�ꥹ������
     * ConnectorListenerType�ꥹ�ʤ��Ǽ
     * @else
     * @brief ConnectorListenerType listener array
     * The ConnectorListenerType listener is stored. 
     * @endif
     */
    ConnectorListenerHolder connector_[CONNECTOR_LISTENER_NUM];
  };
};

#endif // RTC_CONNECTORLISTENER_H
