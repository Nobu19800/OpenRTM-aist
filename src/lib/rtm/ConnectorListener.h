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
   * ���Υ��饹�ϡ�enumāE�����E���E����󥳡��ɤ�ConnectorListener��
   * Ϣ�Υ��֥��饹�Ƕ������Ѥ���E���� mixin ���饹�Ǥ���E����Υ�E���
   * �󥳡��ɤ���Ѥ���E��饹�Ǥϡ�ConnectorListenerStatus ���饹��E   * public �Ѿ���������define ���Ƥ���ECONNLISTENER_STATUS_ENUM �򥯥�E   * ����˵��Ҥ���E��Ȥ����Ѳ�ǽ�Ȥʤ�E�����Eˤ�ꡢenum ��E   * ReturnCode ���Ȥ��� typedef �����ʸ�EReturnCode �����ѤǤ���E褦��
   * ����EȤȤ�ˡ�̾�����֤� enum āE�����E��Ƽ��̻Ҥ��������饹̾����E   * �����Ƴ������E�
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

  /*!
   * @if jp
   * ���ơ����饹��E�����Ƭ�ˤ����� DATAPORTSTATUS_ENUM �򵭺ܤ���E����ǡ�
   * DataPortStatus ����E�����EƤ���Eenum ���Ф�̾�����黻�Ҥʤ��˥�
   * ��������ǽ�ˤʤ�E�
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
   * - ON_BUFFER_FULL:           �Хåե��ե�E�
   * - ON_BUFFER_WRITE_TIMEOUT:  �Хåե��񤭹��ߥ����ॢ���Ȼ�
   * @brief ConnectorDataListener �Υ�����
   *
   * - ON_BUFFER_WRITE:          �Хåե��񤭹��߻�
   * - ON_BUFFER_FULL:           �Хåե��ե�E�
   * - ON_BUFFER_WRITE_TIMEOUT:  �Хåե��񤭹��ߥ����ॢ���Ȼ�
   * - ON_BUFFER_OVERWRITE:      �Хåե���񤭻�
   * - ON_BUFFER_READ:           �Хåե��ɤ߽Ф���
   * - ON_SEND:                  InProt�ؤ�������
   * - ON_RECEIVED:              InProt�ؤ�������λ��
   * - ON_RECEIVER_FULL:         InProt¦�Хåե��ե�E�
   * - ON_RECEIVER_TIMEOUT:      InProt¦�Хåե������ॢ���Ȼ�
   * - ON_RECEIVER_ERROR:        InProt¦���顼��
   *
   * @else
   * @brief The types of ConnectorDataListener
   * - ON_BUFFER_READ:           At the time of buffer read
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
      ON_SEND,
      ON_RECEIVED,
      ON_RECEIVER_FULL,
      ON_RECEIVER_TIMEOUT,
      ON_RECEIVER_ERROR,
      CONNECTOR_DATA_LISTENER_NUM
      ON_RECEIVED,

  /*!
      ON_RECEIVER_ERROR,
      CONNECTOR_DATA_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class ConnectorDataListener ���饹
   * @brief ConnectorDataListener ���饹
   *
   * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������EƼ�E��٥�Ȥ��Ф���E���
   * ��EХå���¸�����E�E��ʥ��饹�δ�āE��饹��
   *
   * ���������å���OutPort���Ф��ƥǡ����񤭹��ߡ�InPort¦�ǥǡ�������E   * ������E�EޤǤδ֤�ȯ������EƼ�E��٥�Ȥ�եå�����E�����EХå�����
   * �ꤹ��E��Ȥ��Ǥ���E��ʤ�����E��ʡ����饹��2��E�¸�ߤ����Хåե���
   * ��E��������Υ�����EХå��ǡ����λ�����ͭ���ʥǡ�����ե��󥯥��ΰ�E   * ���Ȥ��Ƽ����褁EConnectorDataListener �Ǥ��ꡢ�⤦��E��ϥǡ�����
   * ��ץƥ���Хåե��ɤ߹��߻��Υ����ॢ���Ȥʤɥǡ����������Ǥ��ʤ�
   * ��E�ʤɤ˥�����E���E�Eե��󥯥��ΰ����˲���Ȥ�ʤ餤
   * ConnecotorListener ������E�
   *
   * �ǡ����ݡ��Ȥˤϡ���³���˥ǡ�������������ˡ�ˤĤ��ƥǡ����ե�������
   * ���֥�����Eץ�����������ꤹ��E��Ȥ��Ǥ���E�
   *
   * <pre>
   * class MyDataListener
   *   : public ConnectorDataListenerT<RTC::TimedLong>
   * {
   * public:
   *   MyDataListener(const char* name) : m_name(name) {}
   *   virtual ~MyDataListener() {}
   *   virtual ReturnCode operator()(ConnectorInfo& info, TimedLong& data)
   * -  Push��: Subscription Type�ˤ�ꤵ��˥��٥�Ȥμ�Eबʬ����E�E�
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
   * ���Τ褦�ˤ���āE�����E���E��ʥ��饹�ϡ��ʲ��Τ褦�˥ǡ����ݡ��Ȥ�
   * �Ф��ơ��ʲ��Τ褦�˥��åȤ���E�E�
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
   * E������ "ON_BUFFER_WRITE" �ϡ�������EХå���եå�����Eݥ���Ȥ�
   * ���ꡢ�ʲ�����󤹤�Eͤ�褁E��Ȥ���ǽ�Ǥ���E��ǡ����ݡ��Ȥˤϡ���
   * ³���˥ǡ�������������ˡ�ˤĤ��ơ����󥿡��ե����������ǡ����ե���
   * �������֥�����Eץ�����������ꤹ��E��Ȥ��Ǥ���E�������E�������
   * �褁Eեå�����E�Eݥ���Ȥϰۤʤ�E��ʲ��ˡ����󥿡��ե�������CORBA
   * CDR���ξ�E�Υ�����EХå���E��򼨤���
   *
   * OutPort:
   * -  Push��: Subscription Type�ˤ�ꤵ��˥��٥�Ȥμ�Eबʬ����E�E�
   *   - Flush: Flush���ˤϥХåե����ʤ�����EON_BUFFER �ϤΥ��٥�Ȥ�ȯ�����ʤ�
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   - Flush: Flush���ˤϥХåե����ʤ�����EON_BUFFER �ϤΥ��٥�Ȥ�ȯ�����ʤ�
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     - ON_CONNECT
   *     - ON_DISCONNECT
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
   *     - ON_SENDER_ERROR
   *     - ON_CONNECT
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     - ON_BUFFER_EMPTY
   *     - ON_SENDER_EMPTY
   * - Pull��
   *   - ON_BUFFER_READ
   *   - ON_SEND
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_WRITE_OVERWRITE
   *   - ON_BUFFER_EMPTY
   *   - ON_BUFFER_READ_TIMEOUT
   *     - ON_RECEIVED
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_WRITE_OVERWRITE
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *
   * @else
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *
   * @class ConnectorDataListener class
   * @brief ConnectorDataListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in the data port's
   * connectors.
   * such as buffer-empty event, buffer-read-timeout event and so on.
   * @endif
   */
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
  class ConnectorDataListener
  {
  public:
     * ConnectorDataListenerType ��ʸ������Ѵ�����E     *
    /*!
     * @if jp
     * @return ʸ�����Ѵ���E�
     *
     * @brief ConnectorDataListenerType ��ʸ������Ѵ�
     *
     * ConnectorDataListenerType ��ʸ������Ѵ�����E     *
     * @param type �Ѵ��о� ConnectorDataListenerType
     *
     * @return ʸ�����Ѵ���E�
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
     * @brief ���ۥ�����EХå��᥽�å�
     *
     * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������EƼ�E��٥�Ȥ��Ф���E���
     * ��EХå��᥽�å�
     *
     * @else
     *
     * @brief Virtual Callback method
     *
     * This is a the Callback method to various events generated in Connector. 
     *
     * @endif
     */
    virtual void operator()(const ConnectorInfo& info,
                            const cdrMemoryStream& data) = 0;
   * ��EХå���¸�����E�E��ʥ��饹�δ�āE��饹��
   * 

  /*!
   * @if jp
   * @class ConnectorDataListenerT ���饹
   * @brief ConnectorDataListenerT ���饹
   *
   * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������EƼ�E��٥�Ȥ��Ф���E���
   * ��EХå���¸�����E�E��ʥ��饹�δ�āE��饹��
   * 
   * ���Υ��饹�ϡ�operator()() ��E������ cdrMemoryStream ���ǤϤʤ���
   * �ºݤ˥ǡ����ݡ��Ȥǻ��Ѥ���E�Eѿ�����ƥ�ץ�E��Ȱ����Ȥ���
   * �Ϥ����Ȥ��Ǥ���E�
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
     * @brief ������EХå��᥽�å�
     *
     * �ǡ�����ǡ����ݡ��Ȥǻ��Ѥ���E�Eѿ������Ѵ����� ConnectorDataListenerT
     * �Υ�����EХå��᥽�åɤ�ƤӽФ���
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
    virtual void operator()(const ConnectorInfo& info,
                            const cdrMemoryStream& cdrdata)
    {
      DataType data;
#ifdef ORB_IS_ORBEXPRESS
      cdrMemoryStream cdr(cdrdata);
#elif defined(ORB_IS_TAO)
      cdrMemoryStream cdr(cdrdata);
#else
      cdrMemoryStream cdr(cdrdata.bufPtr(), cdrdata.bufSize());
#endif
      // endian type check
      std::string endian_type;
      endian_type = info.properties.getProperty("serializer.cdr.endian",
                                                "little");
      coil::normalize(endian_type);
      std::vector<std::string> endian(coil::split(endian_type, ","));

#ifdef ORB_IS_ORBEXPRESS
      if (endian[0] == "little")
        {
          cdr.cdr.is_little_endian(true);
        }
      else if (endian[0] == "big")
        {
          cdr.cdr.is_little_endian(false);
        }
       cdr.cdr >> data;
#elif defined(ORB_IS_TAO)
       TAO_InputCDR tao_cdr = TAO_InputCDR(cdr.cdr);
       tao_cdr >> data;
#else
      if (endian[0] == "little")
        {
          cdr.setByteSwapFlag(true);
        }
      else if (endian[0] == "big")
        {
          cdr.setByteSwapFlag(false);
        }
      data <<= cdr;
#endif





      this->operator()(info, data);
    }

    /*!
     * @if jp
     *
     * @brief ���ۥ�����EХå��᥽�å�
     *
     * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������EƼ�E��٥�Ȥ��Ф���E���
     * ��EХå��᥽�å�
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
    virtual void operator()(const ConnectorInfo& info,
                            const DataType& data) = 0;
                            
   * - ON_SENDER_ERROR:       OutPort¦���顼��
   * - ON_CONNECT:            ��³��Ω��
  /*!
   * @if jp
   * @brief ConnectorListener �Υ�����
   *  
   * - ON_BUFFER_EMPTY:       �Хåե������ξ�E�E   * - ON_BUFFER_READTIMEOUT: �Хåե������ǥ����ॢ���Ȥ�����E�E   * - ON_SENDER_EMPTY:       OutPort¦�Хåե�����E   * - ON_SENDER_TIMEOUT:     OutPort¦�����ॢ���Ȼ�
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
   * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������EƼ�E��٥�Ȥ��Ф���E���
   * ��EХå���¸�����E�E��ʥ��饹�δ�āE��饹��
   *
   * @if jp
   * @class ConnectorListener ���饹
   * @brief ConnectorListener ���饹
   *
   * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������EƼ�E��٥�Ȥ��Ф���E���
   * ��EХå���¸�����E�E��ʥ��饹�δ�āE��饹��
   *
   * ���������å���OutPort���Ф��ƥǡ����񤭹��ߡ�InPort¦�ǥǡ�������E   * ������E�EޤǤδ֤�ȯ������EƼ�E��٥�Ȥ�եå�����E�����EХå�����
   * �ꤹ��E��Ȥ��Ǥ���E��ʤ�����E��ʡ����饹��2��E�¸�ߤ����Хåե���
   * ��E��������Υ�����EХå��ǡ����λ�����ͭ���ʥǡ�����ե��󥯥��ΰ�E   * ���Ȥ��Ƽ����褁EConnectorDataListener �Ǥ��ꡢ�⤦��E��ϥǡ�����
   * ��ץƥ���Хåե��ɤ߹��߻��Υ����ॢ���Ȥʤɥǡ����������Ǥ��ʤ�
   * ��E�ʤɤ˥�����E���E�Eե��󥯥��ΰ����˲���Ȥ�ʤ餤
   * ConnecotorListener ������E�
   *
   * �ǡ����ݡ��Ȥˤϡ���³���˥ǡ�������������ˡ�ˤĤ��ƥǡ����ե�������
   * ���֥�����Eץ�����������ꤹ��E��Ȥ��Ǥ���E�
   * ConnectorDaataListener/ConnectorListener �϶��ˤˡ��͡��ʥ��٥��
   * ���Ф���E�����EХå������ꤹ��E��Ȥ��Ǥ���E�������E�ǡ����ե�����
   * ����ӥ��֥�����Eץ���󷿤�����˱����ơ����ѤǤ���E�Ρ��Ǥ��ʤ�
   * ��Ρ��ޤ��ƤӽФ���E�E����ߥ󥰤��ۤʤ�E��ʲ��ˡ����󥿡��ե�����
   * ��CORBA CDR���ξ�E�Υ�����EХå���E��򼨤���
   *
   *     std::cout << "Profile::name: " << info.name    << std::endl;
   *     std::cout << "Profile::id:   " << info.id      << std::endl;
   *     std::cout << "Profile::properties: "           << std::endl;
   *     std::cout << info.properties;
   *     - ON_RECEIVER_ERROR
   *   std::string m_name;
   * };
   * </pre>
   *
   * ���Τ褦�ˤ���āE�����E���E��ʥ��饹�ϡ��ʲ��Τ褦�˥ǡ����ݡ��Ȥ�
   * �Ф��ơ��ʲ��Τ褦�˥��åȤ���E�E�
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
   * E������ "ON_BUFFER_EMPTY" �ϡ�������EХå���եå�����Eݥ���Ȥ�
   * ���ꡢ�ʲ�����󤹤�Eͤ�褁E��Ȥ���ǽ�Ǥ���E��ǡ����ݡ��Ȥˤϡ���
   * ³���˥ǡ�������������ˡ�ˤĤ��ơ����󥿡��ե����������ǡ����ե���
   * �������֥�����Eץ�����������ꤹ��E��Ȥ��Ǥ���E�������E�������
   * �褁Eեå�����E�Eݥ���Ȥϰۤʤ�E��ʲ��ˡ����󥿡��ե�������CORBA
   * CDR���ξ�E�Υ�����EХå���E��򼨤���
   *
   * OutPort:
   * -  Push��: Subscription Type�ˤ�ꤵ��˥��٥�Ȥμ�Eबʬ����E�E�
   *   - Flush: Flush���ˤϥХåե����ʤ�����EON_BUFFER �ϤΥ��٥�Ȥ�ȯ�����ʤ�
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
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *   - ON_BUFFER_READ
   *   .
   *   - ON_SEND
   *   - ON_BUFFER_EMPTY
   *   - ON_BUFFER_READ_TIMEOUT
   *   - ON_SENDER_EMPTY
   *   - ON_SENDER_TIMEOUT
   *   - ON_SENDER_ERROR
   *   - ON_CONNECT
   * InPort:
   * - Push��:
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_WRITE_OVERWRITE
   *     - ON_RECEIVED
   *
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   * connectors.
   *
   * @class ConnectorListener class
   * @brief ConnectorListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in the data port's
   * connectors.
   *
   * @endif
   */
  class ConnectorListener
  {
  public:
   * class must be set to data-port object through its member
     * @if jp
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
     * ConnectorListenerType ��ʸ������Ѵ�����E     *
     * @param type �Ѵ��о� ConnectorListenerType
     *
     * @brief ConnectorListenerType ��ʸ������Ѵ�
     *
     * ConnectorListenerType ��ʸ������Ѵ�����E     *
     *
     * @param type �Ѵ��о� ConnectorListenerType
     *
     * Convert ConnectorListenerType into the string.
     * @return ʸ�����Ѵ���E�
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
     * @brief ���ۥ�����EХå��᥽�å�
     *
     * �ǡ����ݡ��Ȥ� Connector �ˤ�����ȯ������EƼ�E��٥�Ȥ��Ф���E���
     * ��EХå��᥽�å�
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
    virtual void operator()(const ConnectorInfo& info) = 0;
  };


  /*!
   * @if jp
   * @class ConnectorDataListenerHolder
   * @brief ConnectorDataListener �ۥ�E����饹
   *
   *
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
  {
    typedef std::pair<ConnectorDataListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @brief �ǥ��ȥ饯��
     * @endif
     */
    ConnectorDataListenerHolder();
    /*!
    virtual ~ConnectorDataListenerHolder();
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
     * @brief ��E��ʡ����ɲ�
     *
     * ��E��ʡ����ɲä���E�
     *
     * @param listener �ɲä���E�E���
     * @param autoclean true:�ǥ��ȥ饯���Ǻ�E�E���E
     *                  false:�ǥ��ȥ饯���Ǻ�E�E��ʤ�
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
     * @brief ��E��ʡ��κ�E�E     *
     * ��E��ʤ�E�E���E�
     *
     * @param listener ��E�E���E�E���
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
     * @brief ��E��ʡ��ο�������E     *
     * ������Ͽ����EƤ���E�E��ʡ���������E�
     *
     * @return listener��E     * @else
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
     * @brief ��E��ʡ������Τ���E     *
     * ��Ͽ����EƤ���E�E��ʤΥ�����EХå��᥽�åɤ�ƤӽФ���
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
    void notify(const ConnectorInfo& info,
                const cdrMemoryStream& cdrdata);

    /*!
     * @if jp
     *
     * @brief ��E��ʡ������Τ���E�ǡ�������āE�)
     *
     * ��Ͽ����EƤ���E�E��ʤΥ�����EХå��᥽�åɤ�ƤӽФ���
     * COnnectorDataListenerT ���Υ�����EХå��Τߥ�����E���E�E�
     *
     * @param info ConnectorInfo
     * @param typeddata �ǡ����ʥǡ��������ꤢ���
     * @param info ConnectorInfo
     * @param typeddata Data
     * @brief Notify listeners. (Typed data version)
     *
     * This calls the Callback method of the registered listener.
     * This operation calls only ConnectorDataListenerT type callback.
     *
     * @param info ConnectorInfo
     * @param typeddata Data
      for (int i(0), len(m_listeners.size()); i < len; ++i)
     */
    template <class DataType>
    void notify(const ConnectorInfo& info, const DataType& typeddata)
    {
      Guard guard(m_mutex);
      for (int i(0), len(m_listeners.size()); i < len; ++i)
        {
          ConnectorDataListenerT<DataType>* listener(0);
          listener =
          dynamic_cast<ConnectorDataListenerT<DataType>*>(m_listeners[i].first);
          if (listener != 0)
            {
              listener->operator()(info, typeddata);
            }
        }
      return ret;

  private:
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  /*!
   * @if jp
   * @class ConnectorListenerHolder 
   * @brief ConnectorListener �ۥ�E����饹
   *
   * ʣ���� ConnectorListener ���ݻ�����������E��饹��
   *
   * @else
   * @class ConnectorListenerHolder
   * @brief ConnectorListener holder class
   *
   * This class manages one ore more instances of ConnectorListener class.
   * ʣ���� ConnectorListener ���ݻ�����������E��饹��
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
  {
    typedef std::pair<ConnectorListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    ConnectorListenerHolder();
    
     * @endif
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @if jp
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief ��E��ʡ����ɲ�
     *
     * ��E��ʡ����ɲä���E�
     *
     * @param listener �ɲä���E�E���
     * @param autoclean true:�ǥ��ȥ饯���Ǻ�E�E���E
     *                  false:�ǥ��ȥ饯���Ǻ�E�E��ʤ�
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
     * @brief ��E��ʡ��κ�E�E     *
     * ��E��ʤ�E�E���E�
     *
     * @param listener ��E�E���E�E���
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
     * @brief ��E��ʡ��ο�������E     *
     * ������Ͽ����EƤ���E�E��ʡ���������E�
     *
     * @return listener��E     * @else
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
     * @brief ��E��ʡ������Τ���E     *
     * ��Ͽ����EƤ���E�E��ʤΥ�����EХå��᥽�åɤ�ƤӽФ���
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
    void notify(const ConnectorInfo& info);
      
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
     * @if jp
   * @endif
   */
  class ConnectorListeners
  {
  public:
    /*!
     * @if jp
     * @brief ConnectorDataListenerType��E�����΁E     * ConnectorDataListenerType��E��ʤ��Ǽ
     * @else
     * @brief ConnectorDataListenerType listener array
     * The ConnectorDataListenerType listener is stored.
     * @endif
     */
    ConnectorDataListenerHolder connectorData_[CONNECTOR_DATA_LISTENER_NUM];
    /*!
     * @if jp
     * @brief ConnectorListenerType��E�����΁E     * ConnectorListenerType��E��ʤ��Ǽ
     * @else
     * @brief ConnectorListenerType listener array
     * The ConnectorListenerType listener is stored. 
     * @endif
