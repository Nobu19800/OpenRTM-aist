// -*- C++ -*-
/*!
 * @file  InPortCorbaConsumer.h
 * @brief InPortCorbaConsumer class
 * @date  $Date: 2007-12-31 03:08:03 $
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
 * $Id$
 *
 */

#ifndef InPortCorbaConsumer_h
#define InPortCorbaConsumer_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/InPortConsumer.h>
#include <rtm/Manager.h>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class InPortCorbaConsumer
   *
   * @brief InPortCorbaConsumer ���饹
   *
   * �̿����ʤ� CORBA �����Ѥ������ϥݡ��ȥ��󥷥塼�ޤμ������饹��
   *
   * @param DataType �ܥݡ��Ȥˤư����ǡ�����
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortCorbaConsumer
   *
   * @brief InPortCorbaConsumer class
   *
   * This is an implementation class of the input port Consumer 
   * that uses CORBA for means of communication.
   *
   * @param DataType Data type for this port
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  class InPortCorbaConsumer
    : public InPortConsumer,
      public CorbaConsumer<RTC::InPortAny>
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param buffer �������󥷥塼�ޤ˳�����Ƥ�Хåե����֥�������
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param buffer The buffer object that is attached to this Consumer
     *
     * @endif
     */
    InPortCorbaConsumer(BufferBase<DataType>& buffer)
      : rtclog("InPortCorbaConsumer"), m_buffer(buffer)
    {
      rtclog.setLevel("PARANOID");
    }
    
    /*!
     * @if jp
     * @brief ���ԡ����󥹥ȥ饯��
     *
     * ���ԡ����󥹥ȥ饯��
     *
     * @param consumer ���ԡ��� InPortCorbaConsumer ���֥�������
     *
     * @else
     * @brief Copy constructor
     *
     * Copy constructor
     *
     * @param consumer InPortCorbaConsumer object of copy source
     *
     * @endif
     */
    InPortCorbaConsumer(const InPortCorbaConsumer<DataType>& consumer)
      : CorbaConsumer<RTC::InPortAny>(consumer),
        rtclog("InPortCorbaConsumer"), m_buffer(consumer.m_buffer)
    {
      rtclog.setLevel("PARANOID");
    }
    
    /*!
     * @if jp
     * @brief �����黻��
     *
     * �����黻��
     *
     * @param consumer ������ InPortCorbaConsumer ���֥�������
     *
     * @return �������
     *
     * @else
     * @brief Assignment operator
     *
     * Assignment operator
     *
     * @param consumer InPortCorbaConsumer object of assignment source
     *
     * @return The assignment result
     *
     * @endif
     */
    InPortCorbaConsumer&
    operator=(const InPortCorbaConsumer<DataType>& consumer)
    {
      if (this == &consumer) return *this;
      m_buffer = consumer.m_buffer;
      m_var = consumer.m_var;  
    }
    
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
    virtual ~InPortCorbaConsumer(void)
    {
    }
    
    /*!
     * @if jp
     * @brief �Хåե��ؤΥǡ������
     *
     * �Хåե��˥ǡ�����񤭹���
     *
     * @param data ����оݥǡ���
     *
     * @else
     * @brief Write data into the buffer
     *
     * Write data into the buffer.
     *
     * @param data The target data for writing
     *
     * @endif
     */
    void put(DataType& data)
    {
      RTC_PARANOID(("put()"));
      CORBA::Any tmp;
      tmp <<= data;
      _ptr()->put(tmp);
    }
    
    /*!
     * @if jp
     * @brief �Хåե�����Υǡ������
     *
     * �Хåե�����ǡ�������Ф������Ф��롣
     *
     * @else
     * @brief Read data from the buffer
     *
     * Read data from the buffer and send it.
     *
     * @endif
     */
    void push()
    {
      RTC_PARANOID(("push()"));
      DataType data;
      CORBA::Any tmp;
      m_buffer.read(data);
      tmp <<= data;
      
      // �����ϥ��顼�����򤹤٤�
      if (CORBA::is_nil(_ptr())) return;
      try
	{
	  _ptr()->put(tmp);
	}
      catch(...)
	{
          RTC_INFO(("exception while invoking _ptr()->put()"));
	  //hoge ���֥������Ȥ�̵���ˤʤä���disconnect���٤�
	  return;
	}
    }
    
    /*!
     * @if jp
     * @brief ���ԡ�������
     *
     * ����InPortCorbaConsumer���֥������Ȥ�ʣ�����������롣
     *
     * @return ���ԡ����줿InPortCorbaConsumer���֥�������
     *
     * @else
     * @brief Generate clone
     *
     * Clone this InPortCorbaConsumer object.
     *
     * @return The clone InPortCorbaConsumer object
     *
     * @endif
     */
    virtual InPortCorbaConsumer* clone() const
    {
      RTC_TRACE(("clone()"));
      return new InPortCorbaConsumer<DataType>(*this);
    }
    
    /*!
     * @if jp
     * @brief �ǡ����������Τؤ���Ͽ
     *
     * ���ꤵ�줿�ץ�ѥƥ��˴�Ť��ơ��ǡ����������Τμ���������Ͽ���롣
     *
     * @param properties ��Ͽ����
     *
     * @return ��Ͽ�������(��Ͽ����:true����Ͽ����:false)
     *
     * @else
     * @brief Subscribe to the data sending notification
     *
     * Subscribe to the data sending notification based on specified 
     * property information.
     *
     * @param properties Information for subscription
     *
     * @return Subscription result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool subscribeInterface(const SDOPackage::NVList& properties)
    {
      RTC_TRACE(("subscribeInterface()"));
      RTC_DEBUG_STR((NVUtil::toString(properties)));

      if (!NVUtil::isStringValue(properties,
				 "dataport.dataflow_type",
				 "Push"))
	{
	  return false;
	}

       // getting InPort's ref from IOR string
      if (subscribeFromIor(properties)) { return true; }

      // getting InPort's ref from Object reference
      if (subscribeFromRef(properties)) { return true; }

      return false;;
    }
    
    /*!
     * @if jp
     * @brief �ǡ����������Τ������Ͽ���
     *
     * �ǡ����������Τμ�����꤫����Ͽ�������롣
     *
     * @param properties ��Ͽ�������
     *
     * @else
     * @brief Unsubscribe the data send notification
     *
     * Unsubscribe the data send notification.
     *
     * @param properties Information for unsubscription
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties)
    {
      RTC_TRACE(("unsubscribeInterface()"));
      RTC_DEBUG_STR((NVUtil::toString(properties)));

      if (unsubscribeFromIor(properties)) { return; }
      unsubscribeFromRef(properties);
    }

  private:
    /*!
     * @if jp
     * @brief IORʸ���󤫤饪�֥������Ȼ��Ȥ��������
     *
     * @return true: �������, false: ��������
     *
     * @else
     * @brief Getting object reference fromn IOR string
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool subscribeFromIor(const SDOPackage::NVList& properties)
    {
      RTC_TRACE(("subscribeFromIor()"));

      CORBA::Long index;
      index = NVUtil::find_index(properties,
                                 "dataport.corba_any.inport_ior");
      if (index < 0)
        {
          RTC_ERROR(("inport_ior not found"));
          return false;
        }

      char* ior(0);
      if (!(properties[index].value >>= ior))
        {
          RTC_ERROR(("inport_ior has no string"));
          return false;
        }

      CORBA::ORB_ptr orb = RTC::Manager::instance().getORB();
      CORBA::Object_var obj = orb->string_to_object(ior);
      
      if (CORBA::is_nil(obj))
        {
          RTC_ERROR(("invalid IOR string has been passed"));
          return false;
        }

      if (!setObject(obj.in()))
        {
          RTC_WARN(("Setting object to consumer failed."));
          return false;
        }
      return true;
    }

    /*!
     * @if jp
     * @brief Any����ľ�ܥ��֥������Ȼ��Ȥ��������
     *
     * @return true: �������, false: ��������
     *
     * @else
     * @brief Getting object reference fromn Any directry
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool subscribeFromRef(const SDOPackage::NVList& properties)
    {
      RTC_TRACE(("subscribeFromRef()"));
      CORBA::Long index;
      index = NVUtil::find_index(properties,
                                 "dataport.corba_any.inport_ref");
      if (index < 0)
        {
          RTC_ERROR(("inport_ref not found"));
          return false;
        }

      CORBA::Object_var obj;
      if (!(properties[index].value >>= CORBA::Any::to_object(obj.out())))
        {
          RTC_ERROR(("prop[inport_ref] is not objref"));
          return true;
        }

      if (CORBA::is_nil(obj))
        {
          RTC_ERROR(("prop[inport_ref] is not objref"));
          return false;
        }
      
      if (!setObject(obj.in()))
        {
          RTC_ERROR(("Setting object to consumer failed."));
          return false;
        }
      return true;
    }

    /*!
     * @if jp
     * @brief ��³���(IOR��)
     *
     * @return true: �������, false: ��������
     *
     * @else
     * @brief ubsubscribing (IOR version)
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool unsubscribeFromIor(const SDOPackage::NVList& properties)
    {
      RTC_TRACE(("unsubscribeFromIor()"));
      CORBA::Long index;
      index = NVUtil::find_index(properties,
                                 "dataport.corba_any.inport_ior");
      if (index < 0)
        {
          RTC_ERROR(("inport_ior not found"));
          return false;
        }

      char* ior;
      if (!(properties[index].value >>= ior))
        {
          RTC_ERROR(("prop[inport_ior] is not string"));
          return false;
        }

      CORBA::ORB_ptr orb = RTC::Manager::instance().getORB();
      CORBA::Object_var var = orb->string_to_object(ior);
      if (!(_ptr()->_is_equivalent(var)))
        {
          RTC_ERROR(("connector property inconsistency"));
          return false;
        }

      releaseObject();
      return true;
    }

    /*!
     * @if jp
     * @brief ��³���(Object reference��)
     *
     * @return true: �������, false: ��������
     *
     * @else
     * @brief ubsubscribing (Object reference version)
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool unsubscribeFromRef(const SDOPackage::NVList& properties)
    {
      RTC_TRACE(("unsubscribeFromRef()"));
      CORBA::Long index;
      index = NVUtil::find_index(properties,
                                 "dataport.corba_any.inport_ref");
      if (index < 0) { return false; }

      CORBA::Object_var obj;
      if (!(properties[index].value >>= CORBA::Any::to_object(obj.out()))) 
        {
          return false;
        }

      if (!(_ptr()->_is_equivalent(obj.in()))) { return false; }

      releaseObject();
      return true;
    }



    
  private:
    mutable Logger rtclog;
    BufferBase<DataType>& m_buffer;
  };
};     // namespace RTC
#endif // InPortCorbaConsumer_h
