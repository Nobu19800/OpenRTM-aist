// -*- C++ -*-
/*!
 * @file CorbaConsumer.h
 * @brief CORBA Consumer class
 * @date $Date: 2006-11-21 08:32:26 $
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
 * $Id: CorbaConsumer.h,v 1.1 2006-11-21 08:32:26 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef Consumer_h
#define Consumer_h

#ifdef ORB_IS_MICO
#include <CORBA.h>
#endif
#ifdef ORB_IS_OMNIORB
#include <omniORB4/CORBA.h>
#endif
#ifdef ORB_IS_ORBACUS
#include <OB/CORBA.h>
#endif
#ifdef ORB_IS_ORBIT2
#include <orbitcpp/orb-cpp/orbitcpp.h>
#endif
#ifdef ORB_IS_ORBIX
#include <CORBA.h>
#endif
#ifdef ORB_IS_TAO
#include <tao/corba.h>
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class ConsumerBase
   * @brief ���֥������ȥ�ե���󥹤��ݻ�����ץ졼���ۥ�����쥯�饹
   * @else
   * @class ConsumerBase
   * @brief Placeholder base class to hold remote object reference.
   * @endif
   */
  class ConsumerBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Consructor
     * @endif
     */
    ConsumerBase(){};

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConsumerBase(){};

    /*!
     * @if jp
     *
     * @brief CORBA���֥������Ȥ򥻥åȤ���
     *
     * Ϳ����줿���֥������ȥ�ե���󥹤ϡ�ConsumerBase ���֥����������
     * CORBA::Object_var ���Ȥ����ݻ�����롣 
     *
     * @param obj CORBA ���֥������ȤΥ�ե����
     * @return obj �� nil ��ե���󥹤ξ�� false ���֤���
     *
     * @else
     *
     * @brief Set CORBA Object
     *
     * The given CORBA Object is held as CORBA::Object_var type
     *
     * @param obj Object reference of CORBA object
     * @return If obj is nil reference, it returns false.
     *
     * @endif
     */
    virtual bool setObject(CORBA::Object_ptr obj)
    {
      if (CORBA::is_nil(obj))
	{
	  return false;
	}
      m_objref = obj;
      return true;
    }

    /*!
     * @if jp
     *
     * @brief CORBA���֥������Ȥ��������
     *
     * Ϳ����줿���֥������ȥ�ե���󥹤ϡ�ConsumerBase ���֥����������
     * CORBA::Object_var ���Ȥ����ݻ�����롣 
     *
     * @param obj CORBA ���֥������ȤΥ�ե����
     *
     * @else
     *
     * @brief Set CORBA Object
     *
     * The given CORBA Object is held as CORBA::Object_var type
     *
     * @param obj Object reference of CORBA object
     *
     * @endif
     */
    virtual CORBA::Object_ptr getObject()
    {
      return m_objref;
    }

  protected:
    CORBA::Object_var m_objref;
  };



  /*!
   * @if jp
   *
   * @class Consumer
   * @brief ���֥������ȥ�ե���󥹤��ݻ�����ץ졼���ۥ���ƥ�ץ졼�ȥ��饹
   * 
   * �ƥ�ץ졼�Ȱ�����Ϳ����줿���Υ��֥������Ȥ��ݻ����롣
   * ���֥������Ȥ����åȤ��줿�Ȥ��ˡ�Ϳ����줿���� narrow �����Τǡ�
   * _ptr() �Ǽ��������ե���󥹤ϡ�narrow �ѤߤΥ�ե���󥹤Ǥ��롣
   * ����Ū�ʻ��ѤΤ���ˡ�_ptr ��, _var����Ʊ���˥ƥ�ץ졼�Ȱ����Ȥ���
   * Ϳ����ɬ�פ����롣(������ջ��໲��)
   * <br>  
   * ���: ObjectTypePtr = ObjectType::_ptr_type �Ȥ��Ƥ��뤫��
   *       _ptr_type ��ɸ��Ǥϵ��ꤵ��Ƥ��ʤ���
   *       ��������omniORB, TAO, MICO �Ǥϡ��ץ������饹�����ǡ�
   *       Type_ptr ���� _ptr_type �� typedef ���Ƥ���Τǡ�
   *       �ƥ�ץ졼�Ȥ���2��������ꤷ�ʤ��Ƥ⥳��ѥ�����̤롣
   *
   * @param ObjectType ���Υۥ�����ݻ����륪�֥������Ȥη�
   * @param ObjectTypePtr ���Υۥ�����ݻ����� _ptr ��
   * @param ObjectTypeVar ���Υۥ�����ݻ����� _var ��
   *
   * @else
   *
   * @class Consumer
   * @brief Placeholder template class to hold remote object reference.
   *
   * This class holds a type of object that given by template parameter.
   * For internal use, _ptr type and _var type should be given as template
   * parameter. (Please refere the following notation.)
   *
   * Note: ObjectTypePtr's default value is defined as ObjectType::_ptr_type,
   *       although _ptr_type is not defined as normative type.
   *       However, omniORB, TAO, MICO, ORBit, ORBacus define _ptr_type and
   *       _var_type as _ptr type and _var type in stub code.
   *       Usually, you don't need to specify 2nd and 3rd template arguments.
   *       
   * @endif
   */
  template <class ObjectType,
	    class ObjectTypePtr = class ObjectType::_ptr_type,
	    class ObjectTypeVar = class ObjectType::_var_type>
  class Consumer
    : public ConsumerBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Consructor
     * @endif
     */
    Consumer(){};
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~Consumer(){};

    /*!
     * @if jp
     * @brief ���֥������Ȥ򥻥åȤ���
     *
     * ConsumerBase �Υ����С��饤�ɡ�CORBA::Object_var �˥��֥������Ȥ򥻥å�
     * ����ȤȤ�ˡ�template�ѥ�᡼���η��� narrow �������֥������Ȥ�
     * �����ѿ����ݻ����롣
     *
     * @param obj CORBA Objecct
     * 
     * @else
     * @brief Set Object
     *
     * Override function of ConsumerBase. This operation set an Object to 
     * CORBA:Object_var in the class, and this object is narrowed to
     * given template parameter and stored in the member variable.
     *
     * @endif
     */
    virtual bool setObject(CORBA::Object_ptr obj)
    {
      if (ConsumerBase::setObject(obj))
	{
	  m_var = ObjectType::_narrow(m_objref);
	  if (!CORBA::is_nil(m_var))
	    return true;
	}
      return false; // object is nil
    }

    inline ObjectTypePtr _ptr()
    {
      return m_var;
    }
  protected:
    ObjectTypeVar m_var;

  };
}; // namespace RTC
#endif // Consumer_h
