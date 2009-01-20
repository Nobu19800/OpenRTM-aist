// -*- C++ -*-
/*!
 * @file ExecutionContextBase.h
 * @brief ExecutionContext base class
 * @date $Date: 2008-01-14 07:48:55 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef ExecutionContextBase_h
#define ExecutionContextBase_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>
#include <rtm/Factory.h>

namespace RTC
{
  /*!
   * @if jp
   * @class ExecutionContextBase
   * @brief ExecutionContext�Ѵ��쥯�饹
   *
   * ExecutionContext�δ��쥯�饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class ExecutionContextBase
   * @brief A base class for ExecutionContext
   *
   * A base class of ExecutionContext.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ExecutionContextBase
    : public virtual POA_OpenRTM::ExtTrigExecutionContextService,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief ���ۥǥ��ȥ饯��
     *
     * ���ۥǥ��ȥ饯��
     *
     * @else
     * @brief Virtual Destructor
     *
     * Virtual Destructor
     *
     * @endif
     */
    virtual ~ExecutionContextBase(){};
    
    /*!
     * @if jp
     * @brief ExecutionContext�ν�����ʤ��
     *
     * ExecutionContext�ν����򣱼���ʬ�ʤ�롣
     *
     * @else
     * @brief Proceed with tick of ExecutionContext
     *
     * Proceed with tick of ExecutionContext for one period.
     *
     * @endif
     */
    virtual void tick()
      throw (CORBA::SystemException)
    {};

    virtual RTC::ReturnCode_t bindComponent(RtcBase* rtc) = 0;

  };
};
#endif // ExecutionContextBase_h
