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
 * $Id: InPortCorbaConsumer.h,v 1.3.4.3 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3.4.2  2007/09/19 07:47:28  n-ando
 * A trivial fix.
 *
 * Revision 1.3.4.1  2007/08/20 06:31:10  n-ando
 * push() function was modified to detect buffer read error.
 *
 * Revision 1.3  2007/01/09 09:56:38  n-ando
 * Kanji-code has changed.
 *
 * Revision 1.2  2007/01/06 17:50:57  n-ando
 * Interface subscription/unsubscription functions (subscribeInterface()
 * and unsubscribeInterface()) are added.
 * The clone() function to clone the instance is added.
 *
 * Revision 1.1  2006/12/02 18:39:57  n-ando
 * InPortCorbaConsumer class was moved from InPortConsumer.h
 *
 */

#ifndef InPortCorbaConsumer_h
#define InPortCorbaConsumer_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/InPortConsumer.h>
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
   * @brief InPortCorbaConsumer class
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
     * @endif
     */
    InPortCorbaConsumer(BufferBase<DataType>& buffer)
      : m_buffer(buffer)
    {
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
     *
     * @endif
     */
    InPortCorbaConsumer(const InPortCorbaConsumer<DataType>& consumer)
      : CorbaConsumer<RTC::InPortAny>(consumer), m_buffer(consumer.m_buffer)
    {
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
     *
     * @endif
     */
    InPortCorbaConsumer&
    operator=(const InPortCorbaConsumer<DataType>& consumer)
    {
      if (this == &consumer) return *this;
      m_buffer = consumer.m_buffer;
    }
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortCorbaConsumer()
    {}
    
    /*!
     * @if jp
     * @brief �Хåե��ؤΥǡ������
     *
     * �Хåե��˥ǡ�����񤭹���
     *
     * @param data ����оݥǡ���
     *
     * @else
     *
     * @endif
     */
    void put(DataType& data)
    {
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
     *
     * @endif
     */
    void push()
    {
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
     *
     * @endif
     */
    virtual InPortCorbaConsumer* clone() const
    {
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
     *
     * @endif
     */
    virtual bool subscribeInterface(const SDOPackage::NVList& properties)
    {
      if (!NVUtil::isStringValue(properties,
				 "dataport.dataflow_type",
				 "Push"))
	{
	  return false;
	}
      
      CORBA::Long index;
      index = NVUtil::find_index(properties,
				 "dataport.corba_any.inport_ref");
      if (index < 0)
	{
	  return false;
	}
      
      CORBA::Object_ptr obj;
      if (properties[index].value >>= CORBA::Any::to_object(obj))
	{
	  if (!CORBA::is_nil(obj))
	    {
	      setObject(obj);
	      return true;
	    }
	}
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
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties)
    {
      ;
    }
    
  private:
    BufferBase<DataType>& m_buffer;
  };
};     // namespace RTC
#endif // InPortCorbaConsumer_h
