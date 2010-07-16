// -*- C++ -*-

#include "phantom_control.h"

/******************************************************
 $B%3!<%k%P%C%/4X?t!"%a%=%C%I4V$G6&M-$9$kJQ?t(B
*******************************************************/
int g_calibrationStyle;
HDboolean g_bRenderForce;
HDboolean g_force_error_flag;
HDint g_button_1_flag, g_button_2_flag;
hduVector3Dd g_force;
hduVector3Dd g_cur_position;
hduVector3Dd g_cur_angle;


phantom_control::phantom_control()
  : m_vel(0.0, 0.0, 0.0),
    m_init_position(0.0, 0.0, 0.0),
    m_init_angle(0.0, 0.0, 0.0)
{
  g_bRenderForce = FALSE;
  g_force_error_flag = TRUE;
  g_button_1_flag = B_OFF;
  g_button_2_flag = B_OFF;
  g_force.set(0.0, 0.0, 0.0);
  g_cur_position.set(0.0, 0.0, 0.0);
  g_cur_angle.set(0.0, 0.0, 0.0);
}



bool phantom_control::initialize()
{
  this->reset_member();

  HDErrorInfo error;

  // $B%G%P%$%9$N=i4|2=(B
  m_hHD = hdInitDevice(HD_DEFAULT_DEVICE);

  // $B%(%i!<%A%'%C%/(B
  if (HD_DEVICE_ERROR(error = hdGetError())) {
    hduPrintError(stderr, &error, "Failed to initialize haptic device");
    return false;
  }

  // PHANToM$B%-%c%j%V%l!<%7%g%s%9%?%$%k$N<hF@(B
  hdGetIntegerv(HD_CALIBRATION_STYLE, &m_supportedCalibrationStyles);
  if (m_supportedCalibrationStyles & HD_CALIBRATION_ENCODER_RESET)
    {
      g_calibrationStyle = HD_CALIBRATION_ENCODER_RESET;
      cout << "ENCODER_RESET" << endl;
      cout << "Please prepare for manual calibration by placing the device " << endl;
      cout << "at its reset position." << endl;
      
      // PHANToM$B$N%-%c%j%V%l!<%7%g%s(B
      hdUpdateCalibration(g_calibrationStyle);
    }
  if (m_supportedCalibrationStyles & HD_CALIBRATION_INKWELL)
    {
      g_calibrationStyle = HD_CALIBRATION_INKWELL;
      cout << "CALIBRATION_INKWELL" << endl;
    }
  if (m_supportedCalibrationStyles & HD_CALIBRATION_AUTO)
    {
      g_calibrationStyle = HD_CALIBRATION_AUTO;
      cout << "CALIBRATION_AUTO" << endl;
    }

  /***********************************************************************
    Schedule the haptic callback function for continuously monitoring the
    button state and rendering the anchored spring force
  ************************************************************************/
  m_gCallbackHandle = hdScheduleAsynchronous(AnchoredSpringForceCallback, 0, HD_MAX_SCHEDULER_PRIORITY);

  // $BNO@)8f$NM-8z2=(B
  hdEnable(HD_FORCE_OUTPUT);

  // $B%9%1%8%e!<%i$N3+;O(B
  hdStartScheduler();

  if (HD_DEVICE_ERROR(error = hdGetError())) {
    hduPrintError(stderr, &error, "Failed to start the scheduler");
    return false;
  } 

  return true;
}



bool phantom_control::finalize()
{
  // $B%a%s%P!<JQ?t%j%;%C%H(B
  this->reset_member();

  // $B%9%1%8%e!<%i$NDd;_(B
  hdStopScheduler();

  // $B%9%1%8%e!<%i%*%Z%l!<%7%g%s$N=*N;(B
  hdUnschedule(m_gCallbackHandle);

  // $B%G%P%$%9$NL58z2=(B
  hdDisableDevice(m_hHD);

  return true;
}



void phantom_control::reset_member()
{
  m_init_position.set(0.0, 0.0, 0.0); g_cur_position.set(0.0, 0.0, 0.0);
  m_init_angle.set(0.0, 0.0, 0.0); g_cur_angle.set(0.0, 0.0, 0.0);
  g_force.set(0.0, 0.0, 0.0);
  m_vel.set(0.0, 0.0, 0.0);
  g_bRenderForce = FALSE;
  g_force_error_flag = FALSE;
}



void phantom_control::set_data(vector<float> force)
{
  int vec_size = force.size();
  
  for (int i = 0; i < ForceEle; i++) {
    g_force[i] = (double)force[i];
  }
}



vector<float> phantom_control::get_data()
{  

  hduVector3Dd temp_vel(0.0, 0.0, 0.0);
  hduVector3Dd temp_angle(0.0, 0.0, 0.0);
  int i(0);

  if(g_button_1_flag == B_ON) {
    m_init_position = g_cur_position;
  }
  else if(g_button_1_flag == B_FREE) {
    hduVecSubtract(temp_vel, g_cur_position, m_init_position);
  }

  if(g_button_2_flag == B_ON) {
    m_init_angle = g_cur_angle;
  }
  else if(g_button_2_flag == B_PUSH) {
    hduVecSubtract(temp_angle, g_cur_angle, m_init_angle);

    for(int i = 0; i < VelEle; i++) {
     temp_vel[i] = 0.0;
    }
  }

  double dis;

  // $B%Z%s$N=ENO$K$h$kJQ0\$r(B0$B$H$9$k!#(B
  dis = sqrt(powf((float)temp_vel[0], 2) + powf((float)temp_vel[1], 2) + powf((float)temp_vel[2], 2));
  if(dis < THRESHOLD) {
    for(int i = 0; i < VelEle; i++) temp_vel[i] = 0.0;
    for(int i = 0; i < AngEle; i++) temp_angle[i] = 0.0;
  }
  
  // PHANToM$B$N%5!<%\0[>o;~$N=hM}(B
  if(g_force_error_flag == FALSE) {
    cout << "Please Push Blue Button." << endl;
    for(int i = 0; i < VelEle; i++) temp_vel[i] = 0.0;
    for(int i = 0; i < AngEle; i++) temp_angle[i] = 0.0;
  }

  vector<float> ret_val;
  for (int i = 0; i < VelEle; i++) {
    ret_val.push_back((float)(temp_vel[i]));
  }
  for (int i = 0; i < AngEle; i++) {
    ret_val.push_back((float)(temp_angle[i]));
  }

  return ret_val;
}



HDCallbackCode HDCALLBACK AnchoredSpringForceCallback(void *pUserData)
{
    static hduVector3Dd anchor;
    static HDdouble gSpringStiffness = 0.1;
    HDErrorInfo error;
    HDint nCurrentButtons, nLastButtons;
    hduVector3Dd position;
    hduVector3Dd force;

    // Haptic$B%U%l!<%`$N3+;O(B
    hdBeginFrame(hdGetCurrentDevice());

    // $B%-%c%j%V%l!<%7%g%s(B
    if(hdCheckCalibration() == HD_CALIBRATION_NEEDS_UPDATE) {
      hdUpdateCalibration(g_calibrationStyle);
    }

    // $B%Z%s$N0LCV<hF@(B
    hdGetDoublev(HD_CURRENT_POSITION, position);

    // $B%\%?%s$N>uBV<hF@(B
    hdGetIntegerv(HD_CURRENT_BUTTONS, &nCurrentButtons);
    hdGetIntegerv(HD_LAST_BUTTONS, &nLastButtons);

    /******************* $B@D%\%?%s$K4X$9$k=hM}(B ***********************************/
    // button down
    if ((nCurrentButtons & HD_DEVICE_BUTTON_1) != 0 &&
        (nLastButtons & HD_DEVICE_BUTTON_1) == 0) {
      g_bRenderForce = FALSE;
      g_button_1_flag = phantom_control::B_ON;
      g_force_error_flag = TRUE;
      hdSetDoublev(HD_CURRENT_FORCE, force);
    }
    // button up
    else if ((nCurrentButtons & HD_DEVICE_BUTTON_1) == 0 &&
             (nLastButtons & HD_DEVICE_BUTTON_1) != 0) {
      memcpy(anchor, position, sizeof(hduVector3Dd));
      g_button_1_flag = phantom_control::B_FREE;
      g_bRenderForce = TRUE;
    }
    /****************************************************************************/
    
    /******************* $BGr%\%?%s$K4X$9$k=hM}(B ***********************************/
    // button down
    if((nCurrentButtons & HD_DEVICE_BUTTON_2) != 0 &&
	   (nLastButtons & HD_DEVICE_BUTTON_2) == 0) {
      g_button_2_flag = phantom_control::B_ON;
    }
    // during button down
    else if((nCurrentButtons & HD_DEVICE_BUTTON_2) != 0 &&
	    (nLastButtons & HD_DEVICE_BUTTON_2) != 0) {
	  g_button_2_flag = phantom_control::B_PUSH;
    }
    // button up
    else if((nCurrentButtons & HD_DEVICE_BUTTON_2) == 0 &&
	    (nLastButtons & HD_DEVICE_BUTTON_2) != 0) {
      g_button_2_flag = phantom_control::B_OFF;
    }
    
    // PHANToM$B$X$NNO%;%C%H(B
    if (g_bRenderForce)
    {
      hduVecSubtract(force, anchor, position);
      hduVecScaleInPlace(force, gSpringStiffness);
      hduVecSubtract(force, force, g_force);
      hdSetDoublev(HD_CURRENT_FORCE, force);
    }

    // $B%Z%s$N0LCV!";Q@*<hF@(B
    hdGetDoublev(HD_CURRENT_POSITION, g_cur_position);
    hdGetDoublev(HD_CURRENT_GIMBAL_ANGLES, g_cur_angle);

    // Haptic$B%U%l!<%`$N=*N;(B
    hdEndFrame(hdGetCurrentDevice());

    // $B%(%i!<%A%'%C%/(B
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        if (hduIsForceError(&error))
        {
		  g_bRenderForce = FALSE;
		  g_force_error_flag = FALSE;
        }
        else if (hduIsSchedulerError(&error))
        {
		  return HD_CALLBACK_DONE;
        }
    }
	
    return HD_CALLBACK_CONTINUE;
}
