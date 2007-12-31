// -*- C++ -*-
/*!
 * @file  OutPortCorbaConsumer.h
 * @brief OutPortCorbaConsumer class
 * @date  $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2007
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPortCorbaConsumer.h,v 1.2.4.1 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/06 17:57:27  n-ando
 * Interface subscription/unsubscription functions (subscribeInterface()
 * and unsubscribeInterface()) are added.
 *
 * Revision 1.1  2006/12/02 18:47:29  n-ando
 * OutPortCorbaConsumer class was moved from OutPortConsumer.h
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
   * @brief OutPortCorbaConsumer class
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
     *
     * @endif
     */
    bool get(DataType& data)
    {
      DataType* d;
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
