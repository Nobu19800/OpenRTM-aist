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
   * @brief ConnectorListenerStatus mixin �N���X
   *
   * ���̃N���X�́Aenum��`���ꂽ���^�[���R�[�h���AConnectorListener��
   * �A�̃T�u�N���X�ŋ��ʗ��p���邽�߂� mixin �N���X�ł���B���̃��^�[
   * ���R�[�h���g�p����N���X�ł́AConnectorListenerStatus �N���X��
   * public �p�����A����define ���Ă��� CONNLISTENER_STATUS_ENUM ���N��
   * �X���ɋL�q���邱�Ƃŗ��p�\�ƂȂ�B����ɂ��Aenum ��
   * ReturnCode �^�Ƃ��� typedef ���A�Ȍ� ReturnCode �𗘗p�ł���悤��
   * ����ƂƂ��ɁA���O��Ԃ� enum ��`���ꂽ�e���ʎq�𓖊Y�N���X���O��
   * �ԓ��ɓ�������B
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
   * @brief ::RTC::ConnDataPortStatus ����
   *
   * ::RTC::DataPortStatus �Ő錾����Ă��� Enum �̂��ׂẴ����o���l�[��
   * �X�y�[�X�ɓ������邽�߂̃}�N���BDataPortStatus �𗘗p����N���X�ɂ�
   * ���āA�N���X�錾�̐擪�ɂ����� DATAPORTSTATUS_ENUM ���L�ڂ��邾���ŁA
   * DataPortStatus �Ő錾����Ă��� enum �����o�����O�������Z�q�Ȃ��ɃA
   * �N�Z�X�\�ɂȂ�B
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
   * @brief ConnectorDataListener �̃^�C�v
   *
   * - ON_BUFFER_WRITE:          �o�b�t�@�������ݎ�
   * - ON_BUFFER_FULL:           �o�b�t�@�t����
   * - ON_BUFFER_WRITE_TIMEOUT:  �o�b�t�@�������݃^�C���A�E�g��
   * - ON_BUFFER_OVERWRITE:      �o�b�t�@�㏑����
   * - ON_BUFFER_READ:           �o�b�t�@�ǂݏo����
   * - ON_SEND:                  InProt�ւ̑��M��
   * - ON_RECEIVED:              InProt�ւ̑��M������
   * - ON_RECEIVER_FULL:         InProt���o�b�t�@�t����
   * - ON_RECEIVER_TIMEOUT:      InProt���o�b�t�@�^�C���A�E�g��
   * - ON_RECEIVER_ERROR:        InProt���G���[��
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
   * @class ConnectorDataListener �N���X
   * @brief ConnectorDataListener �N���X
   *
   * �f�[�^�|�[�g�� Connector �ɂ����Ĕ�������e��C�x���g�ɑ΂���R�[
   * ���o�b�N���������郊�X�i�N���X�̊��N���X�B
   *
   * �R�A���W�b�N��OutPort�ɑ΂��ăf�[�^�������݁AInPort���Ńf�[�^����
   * �������܂ł̊ԂŔ�������e��C�x���g���t�b�N����R�[���o�b�N���
   * �肷�邱�Ƃ��ł���B�Ȃ��A���X�i�[�N���X��2��ޑ��݂��A�o�b�t�@�t
   * ���⑗�M���̃R�[���o�b�N�ŁA���̎��_�ŗL���ȃf�[�^���t�@���N�^�̈�
   * ���Ƃ��Ď󂯎�� ConnectorDataListener �ł���A��������̓f�[�^�G
   * ���v�e�B��o�b�t�@�ǂݍ��ݎ��̃^�C���A�E�g�Ȃǃf�[�^���擾�ł��Ȃ�
   * �ꍇ�ȂǂɃR�[�������t�@���N�^�̈����ɉ����Ƃ�Ȃ炢
   * ConnecotorListener ������B
   *
   * ConnectorDataListener �N���X�ɂ���ăf�[�^���֘A���铮����t�b�N��
   * �����ꍇ�A�ȉ��̗�̂悤�ɁA���̃N���X���p�����A�R�l�N�^�̏��ƃf�[
   * �^�������Ɏ��ȉ��̂悤�ȃR�[���o�b�N�I�u�W�F�N�g���`���A�f�[�^
   * �|�[�g�̓K�؂ȃR�[���o�b�N�ݒ�֐�����R�[���o�b�N�I�u�W�F�N�g���Z�b
   * �g����K�v������B�Ȃ��AData Listener �ɂ́A�f�[�^�Ƃ��ă}�[�V����
   * ���O��̃f�[�^�������Ɏ�� ConnectorDataListener �ƁA�f�[�^�����
   * �̌^�ɃA���}�[�V����������̒l�������Ɏ��A
   * ConnectorDataListenerT ������B�ȉ��̗�́AConnectorDataListenerT
   * �̒�`��ł���B
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
   * ���̂悤�ɂ��Ē�`���ꂽ���X�i�N���X�́A�ȉ��̂悤�Ƀf�[�^�|�[�g��
   * �΂��āA�ȉ��̂悤�ɃZ�b�g�����B
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
   * ��1������ "ON_BUFFER_WRITE" �́A�R�[���o�b�N���t�b�N����|�C���g��
   * ����A�ȉ��ɗ񋓂���l����邱�Ƃ��\�ł���B�f�[�^�|�[�g�ɂ́A��
   * �����Ƀf�[�^�̑���M���@�ɂ��āA�C���^�[�t�F�[�X�^�A�f�[�^�t���[
   * �^�A�T�u�X�N���v�V�����^����ݒ肷�邱�Ƃ��ł��邪�A�����̐ݒ��
   * ���t�b�N�����|�C���g�͈قȂ�B�ȉ��ɁA�C���^�[�t�F�[�X��CORBA
   * CDR�^�̏ꍇ�̃R�[���o�b�N�ꗗ�������B
   *
   * OutPort:
   * -  Push�^: Subscription Type�ɂ�肳��ɃC�x���g�̎�ނ��������B
   *   - Flush: Flush�^�ɂ̓o�b�t�@���Ȃ����� ON_BUFFER �n�̃C�x���g�͔������Ȃ�
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   - New�^
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
   *   - Periodic�^
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
   * - Pull�^
   *   - ON_BUFFER_WRITE
   *   - ON_BUFFER_FULL
   *   - ON_BUFFER_WRITE_TIMEOUT
   *   - ON_BUFFER_OVERWRITE
   *   - ON_BUFFER_READ
   *   - ON_SEND
   *   .
   * InPort:
   * - Push�^:
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
   * - Pull�^
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
     * @brief ConnectorDataListenerType �𕶎���ɕϊ�
     *
     * ConnectorDataListenerType �𕶎���ɕϊ�����
     *
     * @param type �ϊ��Ώ� ConnectorDataListenerType
     *
     * @return ������ϊ�����
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
     * @brief �f�X�g���N�^
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorDataListener();

    /*!
     * @if jp
     *
     * @brief ���z�R�[���o�b�N���\�b�h
     *
     * �f�[�^�|�[�g�� Connector �ɂ����Ĕ�������e��C�x���g�ɑ΂���R�[
     * ���o�b�N���\�b�h
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
   * @class ConnectorDataListenerT �N���X
   * @brief ConnectorDataListenerT �N���X
   *
   * �f�[�^�|�[�g�� Connector �ɂ����Ĕ�������e��C�x���g�ɑ΂���R�[
   * ���o�b�N���������郊�X�i�N���X�̊��N���X�B
   * 
   * ���̃N���X�́Aoperator()() �̑�2������ cdrMemoryStream �^�ł͂Ȃ��A
   * ���ۂɃf�[�^�|�[�g�Ŏg�p�����ϐ��^���e���v���[�g�����Ƃ���
   * �n�����Ƃ��ł���B
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
     * @brief �f�X�g���N�^
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorDataListenerT(){}

    /*!
     * @if jp
     *
     * @brief �R�[���o�b�N���\�b�h
     *
     * �f�[�^���f�[�^�|�[�g�Ŏg�p�����ϐ��^�ɕϊ����� ConnectorDataListenerT
     * �̃R�[���o�b�N���\�b�h���Ăяo���B
     *
     * @param info ConnectorInfo 
     * @param cdrdata cdrMemoryStream�^�̃f�[�^
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
	  ReturnCode ret = this->operator()(info, data);
	  if (ret == DATA_CHANGED || ret == BOTH_CHANGED)
	  {

#ifdef ORB_IS_ORBEXPRESS
		  cdrdata.cdr.rewind();
		  cdrdata.cdr >> data;
#elif defined(ORB_IS_TAO)
		  cdrdata.cdr.reset();
		  TAO_InputCDR tao_cdr = TAO_InputCDR(cdrdata.cdr);
		  tao_cdr >> data;
#else
		  cdrdata.rewindPtrs();
		  data >>= cdrdata;
#endif
	  }
	  return ret;
    }

    /*!
     * @if jp
     *
     * @brief ���z�R�[���o�b�N���\�b�h
     *
     * �f�[�^�|�[�g�� Connector �ɂ����Ĕ�������e��C�x���g�ɑ΂���R�[
     * ���o�b�N���\�b�h
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
   * @brief ConnectorListener �̃^�C�v
   *  
   * - ON_BUFFER_EMPTY:       �o�b�t�@����̏ꍇ
   * - ON_BUFFER_READTIMEOUT: �o�b�t�@����Ń^�C���A�E�g�����ꍇ
   * - ON_SENDER_EMPTY:       OutPort���o�b�t�@����
   * - ON_SENDER_TIMEOUT:     OutPort���^�C���A�E�g��
   * - ON_SENDER_ERROR:       OutPort���G���[��
   * - ON_CONNECT:            �ڑ��m����
   * - ON_DISCONNECT:         �ڑ��ؒf��
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
   * @class ConnectorListener �N���X
   * @brief ConnectorListener �N���X
   *
   * �f�[�^�|�[�g�� Connector �ɂ����Ĕ�������e��C�x���g�ɑ΂���R�[
   * ���o�b�N���������郊�X�i�N���X�̊��N���X�B
   *
   * �R�A���W�b�N��OutPort�ɑ΂��ăf�[�^�������݁AInPort���Ńf�[�^����
   * �������܂ł̊ԂŔ�������e��C�x���g���t�b�N����R�[���o�b�N���
   * �肷�邱�Ƃ��ł���B�Ȃ��A���X�i�[�N���X��2��ޑ��݂��A�o�b�t�@�t
   * ���⑗�M���̃R�[���o�b�N�ŁA���̎��_�ŗL���ȃf�[�^���t�@���N�^�̈�
   * ���Ƃ��Ď󂯎�� ConnectorDataListener �ł���A��������̓f�[�^�G
   * ���v�e�B��o�b�t�@�ǂݍ��ݎ��̃^�C���A�E�g�Ȃǃf�[�^���擾�ł��Ȃ�
   * �ꍇ�ȂǂɃR�[�������t�@���N�^�̈����ɉ����Ƃ�Ȃ炢
   * ConnecotorListener ������B
   *
   * ConnectorListener �N���X�ɂ���Ċ֘A���铮����t�b�N�������ꍇ�A��
   * ���̗�̂悤�ɁA���̃N���X���p�����A�R�l�N�^�̏��������Ɏ��ȉ�
   * �̂悤�ȃR�[���o�b�N�I�u�W�F�N�g���`���A�f�[�^�|�[�g�̓K�؂ȃR�[
   * ���o�b�N�ݒ�֐�����R�[���o�b�N�I�u�W�F�N�g���Z�b�g����K�v������B
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
   * ���̂悤�ɂ��Ē�`���ꂽ���X�i�N���X�́A�ȉ��̂悤�Ƀf�[�^�|�[�g��
   * �΂��āA�ȉ��̂悤�ɃZ�b�g�����B
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
   * ��1������ "ON_BUFFER_EMPTY" �́A�R�[���o�b�N���t�b�N����|�C���g��
   * ����A�ȉ��ɗ񋓂���l����邱�Ƃ��\�ł���B�f�[�^�|�[�g�ɂ́A��
   * �����Ƀf�[�^�̑���M���@�ɂ��āA�C���^�[�t�F�[�X�^�A�f�[�^�t���[
   * �^�A�T�u�X�N���v�V�����^����ݒ肷�邱�Ƃ��ł��邪�A�����̐ݒ��
   * ���t�b�N�����|�C���g�͈قȂ�B�ȉ��ɁA�C���^�[�t�F�[�X��CORBA
   * CDR�^�̏ꍇ�̃R�[���o�b�N�ꗗ�������B
   *
   * OutPort:
   * -  Push�^: Subscription Type�ɂ�肳��ɃC�x���g�̎�ނ��������B
   *   - Flush: Flush�^�ɂ̓o�b�t�@���Ȃ����� ON_BUFFER �n�̃C�x���g�͔������Ȃ�
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   - New�^
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   - Periodic�^
   *     - ON_BUFFER_EMPTY
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_SENDER_EMPTY
   *     - ON_SENDER_ERROR
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   .
   * - Pull�^
   *   - ON_BUFFER_EMPTY
   *   - ON_BUFFER_READ_TIMEOUT
   *   - ON_SENDER_EMPTY
   *   - ON_SENDER_TIMEOUT
   *   - ON_SENDER_ERROR
   *   - ON_CONNECT
   *   - ON_DISCONNECT
   *   .
   * InPort:
   * - Push�^:
   *     - ON_BUFFER_EMPTY
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   * - Pull�^
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
     * @brief ConnectorListenerType �𕶎���ɕϊ�
     *
     * ConnectorListenerType �𕶎���ɕϊ�����
     *
     * @param type �ϊ��Ώ� ConnectorListenerType
     *
     * @return ������ϊ�����
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
     * @brief �f�X�g���N�^
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorListener();

    /*!
     * @if jp
     *
     * @brief ���z�R�[���o�b�N���\�b�h
     *
     * �f�[�^�|�[�g�� Connector �ɂ����Ĕ�������e��C�x���g�ɑ΂���R�[
     * ���o�b�N���\�b�h
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
   * @brief ConnectorDataListener �z���_�N���X
   *
   * ������ ConnectorDataListener ��ێ����Ǘ�����N���X�B
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
     * @brief �R���X�g���N�^
     * @else
     * @brief Constructor
     * @endif
     */
    ConnectorDataListenerHolder();
    /*!
     * @if jp
     * @brief �f�X�g���N�^
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorDataListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief ���X�i�[�̒ǉ�
     *
     * ���X�i�[��ǉ�����B
     *
     * @param listener �ǉ����郊�X�i
     * @param autoclean true:�f�X�g���N�^�ō폜����,
     *                  false:�f�X�g���N�^�ō폜���Ȃ�
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
     * @brief ���X�i�[�̍폜
     *
     * ���X�i���폜����B
     *
     * @param listener �폜���郊�X�i
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
     * @brief ���X�i�[�̐��𓾂�
     *
     * ���ݓo�^����Ă��郊�X�i�[���𓾂�B
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
     * @brief ���X�i�[�֒ʒm����
     *
     * �o�^����Ă��郊�X�i�̃R�[���o�b�N���\�b�h���Ăяo���B
     *
     * @param info ConnectorInfo
     * @param cdrdata �f�[�^
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
     * @brief ���X�i�[�֒ʒm����(�f�[�^�^�w���)
     *
     * �o�^����Ă��郊�X�i�̃R�[���o�b�N���\�b�h���Ăяo���B
     * ConnectorDataListenerT �^�̃R�[���o�b�N�̂݃R�[�������B
     *
     * @param info ConnectorInfo
     * @param typeddata �f�[�^�i�f�[�^�^�w�肠��j
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
#ifdef ORB_IS_ORBEXPRESS
			  cdr.cdr >> typeddata;
#elif defined(ORB_IS_TAO)
			  TAO_InputCDR tao_cdr = TAO_InputCDR(cdr.cdr);
			  tao_cdr >> typeddata;
#else
              typeddata >>= cdr;
#endif
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
   * @brief ConnectorListener �z���_�N���X
   *
   * ������ ConnectorListener ��ێ����Ǘ�����N���X�B
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
     * @brief �R���X�g���N�^
     * @else
     * @brief Constructor
     * @endif
     */
    ConnectorListenerHolder();
    
    /*!
     * @if jp
     * @brief �f�X�g���N�^
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief ���X�i�[�̒ǉ�
     *
     * ���X�i�[��ǉ�����B
     *
     * @param listener �ǉ����郊�X�i
     * @param autoclean true:�f�X�g���N�^�ō폜����,
     *                  false:�f�X�g���N�^�ō폜���Ȃ�
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
     * @brief ���X�i�[�̍폜
     *
     * ���X�i���폜����B
     *
     * @param listener �폜���郊�X�i
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
     * @brief ���X�i�[�̐��𓾂�
     *
     * ���ݓo�^����Ă��郊�X�i�[���𓾂�B
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
     * @brief ���X�i�[�֒ʒm����
     *
     * �o�^����Ă��郊�X�i�̃R�[���o�b�N���\�b�h���Ăяo���B
     *
     * @param info ConnectorInfo
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectonotifyrInfo
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
   * @brief ConnectorListeners �N���X
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
     * @brief ConnectorDataListenerType���X�i�z��
     * ConnectorDataListenerType���X�i���i�[
     * @else
     * @brief ConnectorDataListenerType listener array
     * The ConnectorDataListenerType listener is stored.
     * @endif
     */
    ConnectorDataListenerHolder connectorData_[CONNECTOR_DATA_LISTENER_NUM];
    /*!
     * @if jp
     * @brief ConnectorListenerType���X�i�z��
     * ConnectorListenerType���X�i���i�[
     * @else
     * @brief ConnectorListenerType listener array
     * The ConnectorListenerType listener is stored. 
     * @endif
     */
    ConnectorListenerHolder connector_[CONNECTOR_LISTENER_NUM];
  };
};

#endif // RTC_CONNECTORLISTENER_H