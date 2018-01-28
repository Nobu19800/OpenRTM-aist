// -*- C++ -*-
/*!
 * @file RTC.h
 * @brief RTComponent header
 * @date $Date: 2008-02-29 04:57:44 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_H
#define RTC_H

#include <rtm/config_rtc.h>

#ifdef ORB_IS_MICO
#include <CORBA.h>
#include <coss/CosNaming.h>
#include <rtm/idl/RTC.h>
#endif

#ifdef ORB_IS_TAO
#include <tao/corba.h>
#include <orbsvcs/CosNamingC.h>
#include <rtm/idl/DataPortSkel.h>
#endif

#ifdef ORB_IS_RTORB
#include <RtORB/cdrStream.h>
#endif // ORB_IS_RTORB

#ifdef ORB_IS_OMNIORB

#ifdef WIN32
#pragma warning( disable : 4267 )
#pragma warning( disable : 4290 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#endif // WIN32

#include <omniORB4/CORBA.h>
#include <omnithread.h>

#ifdef WIN32
#pragma warning( default : 4267 )
#pragma warning( default : 4290 )
#pragma warning( default : 4311 )
#pragma warning( default : 4312 )
#endif // WIN32

#endif // ORB_IS_OMNIORB

#include <rtm/idl/OpenRTMSkel.h>

#ifdef RTC_CORBA_CXXMAPPING11
#define RefCountServantBase ServantBase
#endif

// for Windows DLL export 
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define DLL_EXPORT __declspec(dllexport)
// #   define usleep(x) Sleep(x/1000);
// #   define LINE_MAX 256
BOOL WINAPI DllMain (HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved);
#else 
#   define DLL_EXPORT 
#   define WINAPI
#endif /* Windows */

#ifdef ORB_IS_ORBEXPRESS
#include <CosNaming.h>
#endif


//#if defined(COMPAT_OPENRTM_0_4)
#include <coil/Properties.h>

namespace RTC
{
  typedef coil::Properties Properties;

};

#ifdef ORB_IS_ORBEXPRESS
class cdrMemoryStream
{
public:
  cdrMemoryStream()
  {
  };
  cdrMemoryStream(const cdrMemoryStream &rhs)
  {
    cdr.copy(rhs.cdr);
  };
  cdrMemoryStream& operator= (const cdrMemoryStream &rhs)
  {
    cdr.copy(rhs.cdr);
    return *this;
  };
  CORBA::Stream cdr;
};
#elif defined(ORB_IS_TAO)
class cdrMemoryStream
{
public:
	cdrMemoryStream()
	{ 
	};
	cdrMemoryStream(const cdrMemoryStream& rhs)
	{
		for (const ACE_Message_Block *i = rhs.cdr.begin(); i != 0; i = i->cont())
		{
			cdr.write_octet_array_mb(i);
		}
	};
	
	cdrMemoryStream& operator= (const cdrMemoryStream& rhs)
	{
		for (const ACE_Message_Block *i = rhs.cdr.begin(); i != 0; i = i->cont())
		{
			cdr.write_octet_array_mb(i);
		}
		return *this;
	};
	
	void encodeCDRData(::OpenRTM::CdrData *data)
	{
		data->length(cdr.total_length());
		CORBA::Octet *buf = data->get_buffer();
		for (const ACE_Message_Block *i = cdr.begin(); i != 0; i = i->cont())
		{
			const size_t len = i->length();
			ACE_OS::memcpy(buf, i->rd_ptr(), len);
			buf += len;
		}
	}

	void encodeCDRData(::OpenRTM::CdrData &data)
	{
		encodeCDRData(&data);
	}

	
	void decodeCDRData(const ::OpenRTM::CdrData *data)
	{
		cdr.write_octet_array(data->get_buffer(), data->length());
	}

	void decodeCDRData(const ::OpenRTM::CdrData &data)
	{
		decodeCDRData(&data);
	}

	TAO_OutputCDR cdr;
};
//typedef TAO_OutputCDR cdrMemoryStream;
#endif

//#endif // COMPAT_OPENRTM_0_4

#endif // RTC_H
