// -*- C++ -*-
/*!
 * @file RTCUtil.h
 * @brief RTComponent utils
 * @date $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTCUtil.h,v 1.1.2.1 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */
#ifndef RTCUtil_h
#define RTCUtil_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RT����ݡ��ͥ���ѥ桼�ƥ���ƥ��ؿ�
 *
 * RT����ݡ��ͥ�Ȥ��Ф��ưʲ��Υ桼�ƥ���ƥ��ؿ����󶡤��롣
 * 
 * - isDataFlowParticipant
 * - isFsmParticipant
 * - isFsmObject
 * - isMultiModeObject
 *
 * @else
 *
 * @endif
 */
namespace RTC
{
  /*!
   * @if jp
   *
   * @brief DataFlowComponent �Ǥ��뤫Ƚ�ꤹ��
   *
   * ���ꤵ�줿RT����ݡ��ͥ�Ȥ� DataFlowComponent �Ǥ��뤫Ƚ�ꤹ�롣
   * DataFlowComponent�� ExecutionContext �� Semantics ��
   * Periodic Sampled Data Processing �ξ������Ѥ����RT����ݡ��ͥ�Ȥη�
   * �Ǥ��롣
   *
   * @param obj Ƚ���оݤ� CORBA ���֥�������
   *
   * @return DataFlowComponent Ƚ����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  bool isDataFlowParticipant(CORBA::Object_ptr obj);
  
  /*!
   * @if jp
   *
   * @brief FsmParticipant �Ǥ��뤫Ƚ�ꤹ��
   *
   * ���ꤵ�줿RT����ݡ��ͥ�Ȥ� FsmParticipant �Ǥ��뤫Ƚ�ꤹ�롣
   * FsmParticipant �ϡ� ExecutionContext �� Semantics ��
   * Stimulus Response Processing �ξ��ˡ�������Υ���������������뤿���
   * ���Ѥ����RT����ݡ��ͥ�Ȥη��Ǥ��롣
   *
   * @param obj Ƚ���оݤ� CORBA ���֥�������
   *
   * @return FsmParticipant Ƚ����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  bool isFsmParticipant(CORBA::Object_ptr obj);
  
  /*!
   * @if jp
   *
   * @brief Fsm �Ǥ��뤫Ƚ�ꤹ��
   *
   * ���ꤵ�줿RT����ݡ��ͥ�Ȥ� Fsm �Ǥ��뤫Ƚ�ꤹ�롣
   * Fsm �ϡ� ExecutionContext �� Semantics �� Stimulus Response Processing ��
   * ���ˡ��������ܤ�������뤿������Ѥ����RT����ݡ��ͥ�Ȥη��Ǥ��롣
   *
   * @param obj Ƚ���оݤ� CORBA ���֥�������
   *
   * @return Fsm Ƚ����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  bool isFsmObject(CORBA::Object_ptr obj);
  
  /*!
   * @if jp
   *
   * @brief multiModeComponent �Ǥ��뤫Ƚ�ꤹ��
   *
   * ���ꤵ�줿RT����ݡ��ͥ�Ȥ� multiModeComponent �Ǥ��뤫Ƚ�ꤹ�롣
   * Fsm �ϡ� ExecutionContext �� Semantics �� Modes of Operatin �ξ��ˡ�
   * Mode ��������뤿������Ѥ����RT����ݡ��ͥ�Ȥη��Ǥ��롣
   *
   * @param obj Ƚ���оݤ� CORBA ���֥�������
   *
   * @return multiModeComponent Ƚ����
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  bool isMultiModeObject(CORBA::Object_ptr obj);
}; // namespace RTC
#endif // RTCUtil_h
