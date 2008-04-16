// -*- C++ -*-
/*!
 * @file  OutPortCorbaConsumer.h
 * @brief OutPortCorbaConsumer class
 * @date  $Date: 2008-01-13 10:28:27 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
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

#ifndef OutPortCorbaConsumer_h
#define OutPortCorbaConsumer_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/OutPortConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortCorbaConsumer
   *
   * @brief OutPortCorbaConsumer ���饹
   *
   * �̿����ʤ� CORBA �����Ѥ������ϥݡ��ȥ��󥷥塼�ޤμ������饹��
   *
   * @param DataType �ܥݡ��Ȥˤư����ǡ�����
   *
   * @since 0.4.0
   *
   * @else
   * @class OutPortCorbaConsumer
   *
   * @brief OutPortCorbaConsumer class
   *
   * This is an implementation class of the output Consumer 
   * that uses CORBA for means of communication.
   *
   * @param DataType Data type for this port
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  class OutPortCorbaConsumer
    : public OutPortConsumer,
      public CorbaConsumer<RTC::OutPortAny>
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param buffer �ܥݡ��Ȥ˳�����Ƥ�Хåե�
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param buffer Buffer that is attached to this port
     *
     * @endif
     */
    OutPortCorbaConsumer(BufferBase<DataType>& buffer)
      : m_buffer(buffer)
    {}
    
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
    virtual ~OutPortCorbaConsumer(){} 
    
    /*!
     * @if jp
     * @brief �ǡ������ɤ߽Ф�
     *
     * ���ꤵ�줿�ǡ������ɤ߽Ф���
     *
     * @param data �ɤ߽Ф����ǡ����������륪�֥�������
     *
     * @return �ǡ����ɤ߽Ф��������(�ɤ߽Ф�����:true���ɤ߽Ф�����:false)
     *
     * @else
     * @brief Read data
     *
     * Read set data
     *
     * @param data Object to receive the read data
     *
     * @return Read result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool get(DataType& data)
    {
      const DataType* d;
      try
	{
	  if ((*(_ptr()->get())) >>= d)
	    {
	      data = (*d);
	      return true;
	    }
	}
      catch (...)
	{
	  return false;
	}
      return false;
    }
    
    /*!
     * @if jp
     * @brief �ݡ��Ȥ���ǡ������������
     *
     * ��³��Υݡ��Ȥ���ǡ�����������롣
     * ���������ǡ��������������ꤵ�줿�Хåե��˽񤭹��ޤ�롣
     *
     * @else
     * @brief Receive data from the port
     *
     * Receive data from the destination port.
     * Write the received data into the set internal buffer.
     *
     * @endif
     */
    virtual void pull()
    {
      DataType data;
      if (get(data))
	{
	  m_buffer.write(data);
	}
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
     * @brief Subscribe the data receive notification
     *
     * Subscribe the data receive notification based on specified property
     * information
     *
     * @param properties Subscription information
     *
     * @return Subscription result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool subscribeInterface(const SDOPackage::NVList& properties)
    {
      CORBA::Long index;
      index = NVUtil::find_index(properties,
				 "dataport.corba_any.outport_ref");
      if (index < 0) return false;
      
      CORBA::Object_ptr obj;
      if (properties[index].value >>= CORBA::Any::to_object(obj))
	{
	  setObject(obj);
	  return true;
	}
      return false;
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
     * @brief Unsubscribe the data receive notification
     *
     * Unsubscribe the data receive notification.
     *
     * @param properties Unsubscription information
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties)
    {
      CORBA::Long index;
      index = NVUtil::find_index(properties,
				 "dataport.corba_any.outport_ref");
      if (index < 0) return;
      
      CORBA::Object_ptr obj;
      if (properties[index].value >>= CORBA::Any::to_object(obj))
	{
	  if (getObject()->_is_equivalent(obj))
	    releaseObject();
	}
    }
    
  private:
    RTC::OutPortAny_var m_outport;
    BufferBase<DataType>& m_buffer;
  };
};     // namespace RTC
#endif // OutPortCorbaConsumer_h
