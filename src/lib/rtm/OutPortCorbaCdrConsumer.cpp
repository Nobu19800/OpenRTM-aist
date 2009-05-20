// -*- C++ -*-
/*!
 * @file  OutPortCorbaCdrConsumer.h
 * @brief OutPortCorbaCdrConsumer class
 * @date  $Date: 2008-01-13 10:28:27 $
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
 * $Id: OutPortCorbaCdrConsumer.h 1254 2009-04-07 01:09:35Z kurihara $
 *
 */

#include <rtm/Manager.h>
#include <rtm/OutPortCorbaCdrConsumer.h>
#include <rtm/NVUtil.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  OutPortCorbaCdrConsumer::OutPortCorbaCdrConsumer()
  {
  }
    
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  OutPortCorbaCdrConsumer::~OutPortCorbaCdrConsumer(void)
  {
  } 

  /*!
   * @if jp
   * @brief ��������
   * @else
   * @brief Initializing configuration
   * @endif
   */
  void OutPortCorbaCdrConsumer::init(coil::Properties& prop)
  {
  }

  /*!
   * @if jp
   * @brief �Хåե��򥻥åȤ���
   * @else
   * @brief Setting outside buffer's pointer
   * @endif
   */
  void OutPortCorbaCdrConsumer::setBuffer(CdrBufferBase* buffer)
  {
    m_buffer = buffer;
  }

  /*!
   * @if jp
   * @brief �ǡ������ɤ߽Ф�
   * @else
   * @brief Read data
   * @endif
   */
  OutPortConsumer::ReturnCode
  OutPortCorbaCdrConsumer::get(cdrMemoryStream& data)
  {
    ::OpenRTM::CdrData* cdr_data;
    try
      {
        ::OpenRTM::PortStatus ret(_ptr()->get(cdr_data));

        if (ret == ::OpenRTM::PORT_OK)
          {
            data.put_octet_array(&((*cdr_data)[0]), cdr_data->length());
            m_buffer->put(data);
            m_buffer->advanceWptr();
            m_buffer->advanceRptr();

            return PORT_OK;
          }
        return ReturnCode(ret);
      }
    catch (...)
      {
        return CONNECTION_LOST;
      }
    return UNKNOWN_ERROR;
  }
    
  /*!
   * @if jp
   * @brief �ǡ����������Τؤ���Ͽ
   * @else
   * @brief Subscribe the data receive notification
   * @endif
   */
  bool OutPortCorbaCdrConsumer::
  subscribeInterface(const SDOPackage::NVList& properties)
  {
    CORBA::Long index;
    index = NVUtil::find_index(properties,
                               "dataport.corba_cdr.outport_ref");
    if (index < 0) return false;
    
    if (NVUtil::isString(properties,
                         "dataport.corba_cdr.outport_ref"))
      {
        const char* ior;
        properties[index].value >>= ior;

        CORBA::ORB_ptr orb = ::RTC::Manager::instance().getORB();
        CORBA::Object_var var = orb->string_to_object(ior);
        setObject(var.in());
        return true;
      }
    
    return false;
  }
  
  /*!
   * @if jp
   * @brief �ǡ����������Τ������Ͽ���
   * @else
   * @brief Unsubscribe the data receive notification
   * @endif
   */
  void OutPortCorbaCdrConsumer::
  unsubscribeInterface(const SDOPackage::NVList& properties)
  {
    CORBA::Long index;
    index = NVUtil::find_index(properties,
                               "dataport.corba_cdr.outport_ref");
    if (index < 0) return;
    
    const char* ior;
    if (properties[index].value >>= ior)
      {
        CORBA::ORB_ptr orb = RTC::Manager::instance().getORB();
        CORBA::Object_var var = orb->string_to_object(ior);
        if (_ptr()->_is_equivalent(var))
          {
            releaseObject();
          }
      }
  }
};     // namespace RTC

extern "C"
{
  void OutPortCorbaCdrConsumerInit(void)
  {
    RTC::OutPortConsumerFactory& factory(RTC::OutPortConsumerFactory::instance());
    factory.addFactory("corba_cdr",
                       ::coil::Creator< ::RTC::OutPortConsumer,
                                        ::RTC::OutPortCorbaCdrConsumer>,
                       ::coil::Destructor< ::RTC::OutPortConsumer,
                                           ::RTC::OutPortCorbaCdrConsumer>);
  }
};
