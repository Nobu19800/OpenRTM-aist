/*!
 * @file ExecutionContext.h
 * @brief ExecutionContext class
 * @date $Date: 2007-04-13 15:45:29 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <rtm/ExecutionContext.h>
#include <rtm/CORBA_SeqUtil.h>

namespace RTC
{
  
  ExecutionContextBase::ExecutionContextBase(RTObject_ptr owner)
    : m_running(false)
  {
    m_profile.kind = OTHER;
    m_profile.rate = 0.0;
    m_profile.owner = owner;
    m_profile.participants.length(0);
  }

  /*!
   * @if jp
   * @brief ExecutionContext ���¹��椫�ɤ����Υƥ���
   * @else
   * @brief Test for ExecutionContext running state
   * @endif
   */
  CORBA::Boolean ExecutionContextBase::is_running()
  {
    return m_running;
  }
  

  /*!
   * @if jp
   * @brief ExecutionContext �򥹥����Ȥ�����
   * @else
   * @brief Start the ExecutionContext
   * @endif
   */
  ReturnCode_t ExecutionContextBase::start()
  {
    return RTC::RTC_OK;
  }
  

  /*!
   * @if jp
   * @brief ExecutionContext �򥹥ȥåפ�����
   * @else
   * @brief Stop the ExecutionContext
   * @endif
   */
  ReturnCode_t ExecutionContextBase::stop()
  {
    return RTC::RTC_OK;
  }
  
  
  /*!
   * @if jp
   * @brief �¹Լ���(Hz)���������
   * @else
   * @brief Get executionrate(Hz)
   * @endif
   */
  CORBA::Double ExecutionContextBase::get_rate()
  {
    return m_profile.rate;
  }
  
  
  /*!
   * @if jp
   * @brief �¹Լ���(Hz)��Ϳ���� 
   * @else
   * @brief Set rate (Hz)
   * @endif
   */
  ReturnCode_t ExecutionContextBase::set_rate(CORBA::Double rate)
  {
    if (rate > 0.0)
      {
	m_profile.rate = rate;
	return RTC::RTC_OK;
      }
    return RTC::BAD_PARAMETER;
  }
  

  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ򥢥��ƥ��ֲ�����
   * @else
   * @brief Activate a component
   * @endif
   */ 
  ReturnCode_t
  ExecutionContextBase::activate_component(LightweightRTObject_ptr comp)
  {
    return RTC::RTC_OK;
  }
  

  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ�����
   * @else
   * @brief Deactivate a component
   * @endif
   */  
  ReturnCode_t
  ExecutionContextBase::deactivate_component(LightweightRTObject_ptr comp)
  {
    return RTC::RTC_OK;
  }
  

  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ��󥢥��ƥ��ֲ�����
   * @else
   * @brief Deactivate a component
   * @endif
   */  
  ReturnCode_t
  ExecutionContextBase::reset_component(LightweightRTObject_ptr comp)
  {
    return RTC::RTC_OK;
  }
  
  
  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥξ��֤��������
   * @else
   * @brief Get component's state
   * @endif
   */
  LifeCycleState
  ExecutionContextBase::get_component_state(LightweightRTObject_ptr comp)
  {
    return RTC::INACTIVE_STATE;
  }
  
  
  /*!
   * @if jp
   * @brief ExecutionKind ���������
   * @else
   * @brief Get the ExecutionKind
   * @endif
   */
  ExecutionKind ExecutionContextBase::get_kind()
  {
    return m_profile.kind;
  }
  

  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ��ɲä���
   * @else
   * @brief Add a component
   * @endif
   */
  ReturnCode_t ExecutionContextBase::add(LightweightRTObject_ptr comp)
  {
    if (!CORBA::is_nil(comp))
      {
	CORBA_SeqUtil::push_back(m_profile.participants,
				 RTC::RTObject::_narrow(comp));
	return RTC::RTC_OK;
      }
    return RTC::BAD_PARAMETER;
  }
  
  
  /*!
   * @if jp
   * @brief ����ݡ��ͥ�Ȥ򥳥�ݡ��ͥ�ȥꥹ�Ȥ���������
   * @else
   * @brief Remove the component from component list
   * @endif
   */	
  ReturnCode_t
  ExecutionContextBase::remove(LightweightRTObject_ptr comp)
  {
    CORBA::ULong index;
    index = CORBA_SeqUtil::find(m_profile.participants,
		find_objref<RTObject_ptr>(RTC::RTObject::_narrow(comp)));
				
    if (index < 0) return RTC::BAD_PARAMETER;
    CORBA_SeqUtil::erase(m_profile.participants, index);
    return RTC::RTC_OK;
  }


  //============================================================
  // ExecutionContextAdmin interfaces
  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContextProfile ���������
   * @else
   * @brief Get the ExecutionContextProfile
   * @endif
   */
  ExecutionContextProfile* ExecutionContextBase::get_profile()
  {
    ExecutionContextProfile_var p;
    p = new ExecutionContextProfile(m_profile);
    return p._retn();
  }
  
  
  
}; // namespace RTC
