// -*- C++ -*-
/*!
 * @file  PhantomJoystick.h
 * @brief PhantomJoystick component
 * @date  $Date$
 *
 * $Id$
 */

#ifndef PHANTOMJOYSTICK_H
#define PHANTOMJOYSTICK_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>

#include "phantom_control.h"

using namespace RTC;

/*!
 * @class PhantomJoystick$B%3%s%]!<%M%s%H%/%i%9(B
 *   PHANToM$B%G%P%$%9$r%8%g%$%9%F%#%C%/$H$7$F;HMQ$9$k%3%s%]!<%M%s%H%/%i(B
 *   $B%9(B
 */
class PhantomJoystick
  : public RTC::DataFlowComponentBase
{
public:
  //! $B%3%s%9%H%i%/%?(B
  PhantomJoystick(RTC::Manager* manager);

  //! $B%G%9%H%i%/%?(B
  ~PhantomJoystick() {delete m_pc;}

  // The initialize action (on CREATED->ALIVE transition)
  virtual RTC::ReturnCode_t onInitialize();

  // The activated action (Active state entry action)
  virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  // The deactivated action (Active state exit action)
  virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  // The execution action that is invoked periodically
  virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /*!
   * @brief $B%j%9%H%G!<%?$N@Q;;$r9T$&%F%s%W%l!<%H4X?t(B
   * @param val1 : $B7k2L$r3JG<$9$k$?$a$N%j%9%H(B
   * @param val2 : $B85$N%G!<%?%j%9%H(B
   * @param val3 : $B3]$1$kCM$N%j%9%H(B
   * @param size : $BBP>]%G!<%?$N%G!<%??t(B
   */
  template<class X, class Y, class Z>
  void data_mul(X &val1, Y &val2, Z &val3, int size) {
    for(int i = 0; i < size; i++) {
      val1[i] = val2[i] * val3[i];
    }
  }

  /*!
   * @brief $B%j%9%H%G!<%?$N%3%T!<$r9T$&%F%s%W%l!<%H4X?t(B
   * @param x : $B%3%T!<@h%G!<%?%j%9%H(B
   * @param y : $B%3%T!<85%G!<%?%j%9%H(B
   * @param ins_point : $B%3%T!<@h%j%9%H$NA^F~%]%$%s%H(B($BMWAGHV9f(B)
   */
  template<class X, class Y>
  void data_copy(X &x, Y &y,int ins_point) {
    for(int i = 0; i < VelEle; i++) {
      x[i+ins_point] = y[i];
    }
  }

  /*!
   * @brief $B%j%9%H%G!<%?$N%3%T!<$r9T$&%F%s%W%l!<%H4X?t(B
   * @param x : $B%3%T!<@h%G!<%?%j%9%H(B
   * @param y : $B%3%T!<85%G!<%?%j%9%H(B
   * @param insPtr  : $B%3%T!<@h%j%9%H$NA^F~%]%$%s%H(B($BMWAGHV9f(B)
   * @param readPtr : $B%3%T!<85%j%9%H$NFI$_9~$_%]%$%s%H(B($BMWAGHV9f(B)
   * @param size    : $B%3%T!<$9$k%G!<%??t(B
   */
  template<class X, class Y>
  void data_copy(X &x, Y &y, int insPtr, int readPtr, int size) {
    for(int i = 0; i < size; i++) {
      x[i+insPtr] = y[i+readPtr];
    }
  }

protected:
  // Configuration variable declaration
  std::vector<float> m_force_gain;
  std::vector<float> m_vel_gain;
  
  // DataInPort declaration
  TimedFloatSeq m_force;
  InPort<TimedFloatSeq> m_forceIn;
  
  // DataOutPort declaration
  TimedFloatSeq m_vel;
  OutPort<TimedFloatSeq> m_velOut;
  
private:
  int dummy;
  //! phantom_control$B%/%i%9$N%$%s%9%?%s%9(B
  phantom_control *m_pc;

};


extern "C"
{
  void PhantomJoystickInit(RTC::Manager* manager);
};

#endif // PHANTOMJOYSTICK_H
