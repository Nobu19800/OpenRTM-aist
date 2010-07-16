// -*- C++ -*-

#ifndef PHANTOM_CONTROL_H
#define PHANTOM_CONTROL_H

#include <iostream>
#include <vector>
#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>

#define THRESHOLD 10.0 // Phantom Joystick$B%b!<%I$G$NogCM(B

using namespace std;

/*!
 * @brief the main scheduler callback for rendering the anchored spring force.
 * $BNO$N%;%C%H$d%Z%s@h$N0LCV!";Q@*$r<hF@$9$k$?$a$N%3!<%k%P%C%/4X?t(B
 * $B$3$N4X?t$N4X?t%]%$%s%?$r;HMQ$9$k$?$a!"%0%m!<%P%k$K@k8@$7$F$$$k!#(B
 */
HDCallbackCode HDCALLBACK AnchoredSpringForceCallback(void *pUserData);


/******************************************************
 $B%3!<%k%P%C%/4X?t!"%a%=%C%I4V$G6&M-$9$kJQ?t(B
 phantom_control.cpp$BFb$K$F@k8@(B
*******************************************************/
extern int g_calibrationStyle;
extern HDboolean g_bRenderForce;
extern HDboolean g_force_error_flag;
extern HDint g_button_1_flag, g_button_2_flag;
extern hduVector3Dd g_force;
extern hduVector3Dd g_cur_position;
extern hduVector3Dd g_cur_angle;


/*!
 * @class phantom_control
 * @brief PHANToM$B%G%P%$%9$+$i$N%G!<%?$N<hF@$HNO$N%;%C%H$r9T$&%/%i%9!#(B
 */
class phantom_control 
{

 public:
  //! $B%3%s%9%H%i%/%?(B
  phantom_control();

  //! $B%G%9%H%i%/%?(B
  ~phantom_control() {;}

  //! $B=i4|2=MQ%a%=%C%I(B
  bool initialize();

  //! $B8e=hM}MQ%a%=%C%I(B
  bool finalize();

  //! $B%a%s%PJQ?t$N%j%;%C%HMQ%a%=%C%I(B
  void reset_member();

  /*!
   * @brief $BNO%G!<%?%;%C%HMQ%a%=%C%I(B
   *    PHANToM$B$K%;%C%H$9$kNO%G!<%?$r0z?t$G;XDj$9$k!#(B
   * @param $BNO%G!<%?$N%j%9%H(B(X,Y,Z)
   */
  void set_data(vector<float> force);

  /*!
   * @brief $B%G!<%?<hF@MQ%a%=%C%I(B
   *    PHANToM$B$N%Z%s@h$N4p=`0LCV$H8=:_$N0LCV$N:9J,$rJV$9!#(B
   *    $B%Z%s@h$N4p=`0LCV$O%Z%s$KIU$$$F$$$k%\%?%s$r2!$7$?;~$N%Z%s@h0LCV!#(B
   *
   * @return $B%Z%s@h$N4p=`0LCV$H8=:_0LCV$H$N:9J,$N%j%9%H(B(X,Y,Z)
   */
  vector<float> get_data();

  //! $BB.EY%G!<%?$NMWAG?t(B(X,Y,Z)
  typedef enum VELOCITY_VECTOR_ELEMENT {
    VelEle = 3
  };

  //! $B%Z%s$N;Q@*%G!<%?$NMWAG?t(B(r,p,y)
  typedef enum ANGLE_VECTOR_ELEMENT {
    AngEle = 3
  };

  //! $BNO%G!<%?$NMWAG?t(B(X,Y,Z)
  typedef enum FORCE_VECTOR_ELEMENT {
    ForceEle = 3
  };

  /*!
   * @brief $B%\%?%sA`:n$K4X$9$k%U%i%0MQDj?t(B
   * B_OFF  : $B2?$b$7$J$$>uBV(B
   * B_ON   : $B%\%?%s$r2!$7$?;~E@(B
   * B_PUSH : $B%\%?%s$r2!$7B3$1$F$$$k>uBV(B
   * B_FREE : $B%\%?%s$r2!$7$?8e!"N%$7$?$^$^$N>uBV(B
   */
  typedef enum BUTTON_STATE {
    B_OFF  = 0,
    B_ON   = 1,
    B_PUSH = 2,
    B_FREE = 4
  };


 private:
  //! $B%Z%s$N0LCV(B
  hduVector3Dd m_init_position;

  //! $B%Z%s$N;Q@*(B
  hduVector3Dd m_init_angle;

  //! $B%Z%s$N4p=`0LCV$H8=:_0LCV$H$N:9J,(B
  hduVector3Dd m_vel;

  //! $B%-%c%j%V%l!<%7%g%s>uBV(B
  int m_supportedCalibrationStyles;

  //! PHANToM$B%G%P%$%9%O%s%I%k(B
  HHD m_hHD;

  //! $B%*%Z%l!<%7%g%sMQ%O%s%I%k(B
  HDSchedulerHandle m_gCallbackHandle; 

};


#endif //  PHANTOM_CONTROL_H
