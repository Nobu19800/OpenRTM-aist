// -*- C++ -*-
/*!
 * @file ExecutionContextBase.h
 * @brief ExecutionContext base class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ExecutionContextBase.h,v 1.1.2.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2007/04/13 16:07:22  n-ando
 * ExecutionContext base class.
 *
 */

#ifndef ExecutionContextBase_h
#define ExecutionContextBase_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>

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
   * @endif
   */
  class ExecutionContextBase
    : public virtual POA_RTC::ExtTrigExecutionContextService,
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
     * @brief Destructor
     * @endif
     */
    virtual void tick(){};
  };
};
#endif // ExecutionContextBase_h
