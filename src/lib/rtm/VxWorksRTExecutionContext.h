// -*- C++ -*-
/*!
 * @file VxWorksRTExecutionContext.h
 * @brief VxWorksRTExecutionContext class
 * @date $Date: 2017-07-11 10:53:05 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Nobuhiko Miyamoto
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 *
 */

#ifndef RTC_VXWORKSRTEXECUTIONCONTEXT_H
#define RTC_VXWORKSRTEXECUTIONCONTEXT_H

#include <vector>
#include <iostream>

#include <coil/Task.h>
#include <coil/Mutex.h>
#include <coil/Condition.h>

#include <rtm/PeriodicExecutionContext.h>



namespace RTC_exp
{
  class TimeValue_nano;
  /*!
   * @if jp
   * @class VxWorksRTExecutionContext
   * @brief VxWorksRTExecutionContext ���饹
   *
   * Periodic Sampled Data Processing(�����¹���)ExecutionContext���饹��
   *
   * @since 0.4.0
   *
   * @else
   * @class VxWorksRTExecutionContext
   * @brief VxWorksRTExecutionContext class
   *
   * Periodic Sampled Data Processing (for the execution cycles)
   * ExecutionContext class
   *
   * @since 0.4.0
   *
   * @endif
   */
  class VxWorksRTExecutionContext
      : public RTC_exp::PeriodicExecutionContext
  {
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief �ǥե���ȥ��󥹥ȥ饯��
     *
     * �ǥե���ȥ��󥹥ȥ饯��
     * �ץ�ե�����˰ʲ��ι��ܤ����ꤹ�롣
     *  - kind : PERIODIC
     *  - rate : 0.0
     *
     * @else
     * @brief Default Constructor
     *
     * Default Constructor
     * Set the following items to profile.
     *  - kind : PERIODIC
     *  - rate : 0.0
     *
     * @endif
     */
    VxWorksRTExecutionContext();

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
    virtual ~VxWorksRTExecutionContext(void);

    /*!
     * @if jp
     * @brief ExecutionContext�ν������Ԥ�
     *
     * ExecutionContext�ν��������
     *
     * @else
     * @brief Initialize the ExecutionContext
     *
     * This operation initialize the ExecutionContext
     *
     * @endif
     */
    virtual  void init(coil::Properties& props);

    /*!
     * @if jp
     * @brief ExecutionContext �ѤΥ���åɼ¹Դؿ�
     *
     * ExecutionContext �ѤΥ���åɼ¹Դؿ�����Ͽ���줿����ݡ��ͥ��
     * �ν�����ƤӽФ���
     *
     * @return �¹Է��
     *
     * @else
     * @brief Thread execution function for ExecutionContext
     *
     * Thread execution function for ExecutionContext.  Invoke the
     * registered components operation.
     *
     * @return The execution result
     *
     * @endif
     */
    virtual int svc(void);



  protected:
  private:
    /*!
     * @if jp
     * @brief ͥ���٤�����
     *
     * @param prop
     *
     * @return 
     *
     * @else
     * @brief set priority
     * 
     * @param prop
     *
     * @return 
     *
     * @endif
     */
   void setPriority(coil::Properties& props);
    /*!
     * @if jp
     * @brief �����å�������������
     *
     * @param prop
     *
     * @return 
     *
     * @else
     * @brief set stack size
     * 
     * @param prop
     *
     * @return 
     *
     * @endif
     */
   void setStackSize(coil::Properties& props);
    /*!
     * @if jp
     * @brief �ʥ���ñ�̤�sleep
     *
     * @param interval
     *
     * @return 
     *
     * @else
     * @brief 
     * 
     * @param interval
     *
     * @return 
     *
     * @endif
     */
   int sleep_nano(TimeValue_nano interval);
  }; // class VxWorksRTExecutionContext
  class TimeValue_nano
  {
  public:
    TimeValue_nano(long sec=0, long usec=0);
    TimeValue_nano(double timeval);
    ~TimeValue_nano();
    TimeValue_nano operator-(TimeValue_nano& tm);
    TimeValue_nano operator+(TimeValue_nano& tm);
    TimeValue_nano operator=(double time);
    operator double() const;
    int sign() const;
    void normalize();
    inline long int sec() const {return m_sec;}
    inline long int nsec() const {return m_nsec;}
  private:
    long int m_sec;
    long int m_nsec;
  };
}; // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif


extern "C"
{
  /*!
   * @if jp
   * @brief ECFactory�ؤ���Ͽ�Τ���ν�����ؿ�
   * @else
   * @brief Initialization function to register to ECFactory
   * @endif
   */
  void VxWorksRTExecutionContextInit(RTC::Manager* manager);
};

#endif // RTC_VXWORKSRTEXECUTIONCONTEXT_H

