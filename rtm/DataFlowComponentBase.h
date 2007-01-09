// -*- C++ -*-
/*!
 * @file DataFlowComponentBase.h
 * @brief DataFlowParticipant RT-Component base class
 * @date $Date: 2007-01-09 09:47:22 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: DataFlowComponentBase.h,v 1.1 2007-01-09 09:47:22 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef DataFlowComponentBase_h
#define DataFlowComponentBase_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/RTObject.h>
#include <rtm/PeriodicExecutionContext.h>

namespace RTC
{
  /*!
   * @if jp
   * @class DataFlowComponentBas
   * @brief DataFlowComponentBase $B%/%i%9(B
   * @else
   * @class DataFlowComponentBase
   * @brief DataFlowComponentBase class
   * @endif
   */
  class Manager;

  class DataFlowComponentBase
    : public RTObject_impl
      
  {
  public:
    /*!
     * @if jp
     * @brief $B%3%s%9%H%i%/%?(B
     * @else
     * @brief Constructor
     * @endif
     */
    DataFlowComponentBase(Manager* manager);


    /*!
     * @if jp
     * @brief $B%G%9%H%i%/%?(B
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~DataFlowComponentBase();


    /*!
     * @if jp
     * @brief $B=i4|2=(B
     * @else
     * @brief Initialization
     * @endif
     */
    void init();


  private:
    DataFlowComponent_var m_ref;
    PeriodicExecutionContext* m_pec;
    ExecutionContextService_var m_ecref;
  };

}; // namespace RTC
#endif // DataFlowComponentBase_h
