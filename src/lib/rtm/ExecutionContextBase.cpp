// -*- C++ -*-
/*!
 * @file ExecutionContextBase.cpp
 * @brief ExecutionContext base class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <rtm/ExecutionContextBase.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���ۥǥ��ȥ饯��
   * @else
   * @brief Virtual Destructor
   * @endif
   */
  ExecutionContextBase::~ExecutionContextBase(void)
  {
  }

  /*!
   * @if jp
   * @brief ExecutionContext�ν�����ʤ��
   * @else
   * @brief Proceed with tick of ExecutionContext
   * @endif
   */
  void ExecutionContextBase::init(coil::Properties& props)
  {
  }


    /*!
     * @if jp
     * @brief ����ݡ��ͥ�Ȥ�Х���ɤ��롣
     * @else
     * @brief Bind the component.
     * @endif
     */
  //  TC::ReturnCode_t bindComponent(RTObject_impl* rtc) = 0;

    /*!
     * @if jp
     * @brief ���֥������ȤΥ�ե���󥹤�������롣
     *
     * ���֥������ȤΥ�ե���󥹤�������롣
     *
     * @else
     * @brief Get the reference of the object. 
     *
     * Get the reference of the object.
     *
     * @endif
     */
  //    virtual RTC::ExecutionContextService_ptr getObjRef() = 0;
};  // namespace RTC
