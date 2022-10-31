﻿// -*- C++ -*-
/*!
 * @file CORBA_CdrMemoryStream.cpp
 * @brief CORBA CDR Stream Buffer class
 * @date $Date: 2019-1-26 03:08:06 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2006-2019
 *     Noriaki Ando
 *     Robot Innovation Research Center,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */



#include <rtm/CORBA_CdrMemoryStream.h>



 /*!
  * @if jp
  * @namespace RTC
  *
  * @brief RTコンポーネント
  *
  * @else
  *
  * @namespace RTC
  *
  * @brief RT-Component
  *
  * @endif
  */
namespace RTC
{

    CORBA_CdrMemoryStream::CORBA_CdrMemoryStream()
    {
    }

    void CORBA_CdrMemoryStream::setEndian(bool little_endian)
    {
        m_endian = little_endian;
#ifdef ORB_IS_ORBEXPRESS
        m_cdr.rewind();
        m_cdr.is_little_endian(little_endian);
#elif defined(ORB_IS_TAO)
        m_cdr.reset();
#else
        m_cdr.rewindPtrs();
        m_cdr.setByteSwapFlag(little_endian);
#endif
    }

    unsigned long CORBA_CdrMemoryStream::getCdrDataLength() const
    {
#ifdef ORB_IS_ORBEXPRESS
        return m_cdr.size_written();
#elif defined(ORB_IS_TAO)
        return static_cast<unsigned long>(m_cdr.total_length());
#else
        return m_cdr.bufSize();
#endif
    }

    const unsigned char* CORBA_CdrMemoryStream::getBuffer()
    {
#ifdef ORB_IS_ORBEXPRESS
        return (unsigned char*)m_cdr.get_buffer();
#elif defined(ORB_IS_TAO)
        return (unsigned char*)m_cdr.begin();
#else
        return static_cast<unsigned char*>(m_cdr.bufPtr());
#endif
    }

#ifdef ORB_IS_ORBEXPRESS
    CORBA::Stream& CORBA_CdrMemoryStream::getCdr()
#elif defined(ORB_IS_TAO)
    TAO_OutputCDR& CORBA_CdrMemoryStream::getCdr()
#else
    cdrMemoryStream& CORBA_CdrMemoryStream::getCdr()
#endif
    {
        return m_cdr;
    }


    void CORBA_CdrMemoryStream::writeCdrData(const unsigned char* buffer, unsigned long length)
    {
#ifdef ORB_IS_ORBEXPRESS
        m_cdr.write_array_1(buffer, length);
#elif defined(ORB_IS_TAO)
        m_cdr.write_octet_array((const unsigned char*)buffer, length);
#elif defined(ORB_IS_RTORB)
        m_cdr.put_octet_array(reinterpret_cast<char*>(const_cast<unsigned char*>(buffer)), length);
#else
        m_cdr.put_octet_array(buffer, length);
#endif
    }

    bool CORBA_CdrMemoryStream::copyToCdrData(unsigned char* buffer, unsigned long length)
    {
#ifdef ORB_IS_ORBEXPRESS
      m_cdr.write_array_1(buffer, length);
      return false;
#elif defined(ORB_IS_TAO)
      m_cdr.write_octet_array((const unsigned char*)buffer, length);
      return false;
#elif defined(ORB_IS_RTORB)
      m_cdr.put_octet_array(reinterpret_cast<char*>(const_cast<unsigned char*>(buffer)), length);
      return false;
#else
      m_cdr = cdrMemoryStream(static_cast<CORBA::Octet*>(buffer), length);
      return true;
#endif
    }

    void CORBA_CdrMemoryStream::readCdrData(unsigned char* buffer, unsigned long length) const
    {
#ifdef ORB_IS_ORBEXPRESS
        length = tmp_data.cdr.size_written();
        m_cdr.read_array_1(buffer, length);
#elif defined(ORB_IS_TAO)
        (void)length;
        CORBA::Octet *buf = (CORBA::Octet *)buffer;
        for (const ACE_Message_Block *i = m_cdr.begin(); i != nullptr; i = i->cont())
        {
            const size_t len = i->length();
            ACE_OS::memcpy(buf, i->rd_ptr(), len);
            buf += len;
        }
#else
        memcpy(buffer, m_cdr.bufPtr(), length);
#endif
    }

    bool CORBA_CdrMemoryStream::copyFromCdrData(unsigned char*& buffer, unsigned long /*length*/)
    {
#ifdef ORB_IS_ORBEXPRESS
      length = tmp_data.cdr.size_written();
      m_cdr.read_array_1(buffer, length);
      return false;
#elif defined(ORB_IS_TAO)
      (void)length;
      CORBA::Octet* buf = (CORBA::Octet*)buffer;
      for (const ACE_Message_Block* i = m_cdr.begin(); i != nullptr; i = i->cont())
      {
        const size_t len = i->length();
        ACE_OS::memcpy(buf, i->rd_ptr(), len);
        buf += len;
      }
      return false;
#else
      buffer = static_cast<unsigned char*>(m_cdr.bufPtr());
      //m_cdr.getOctetStream(static_cast<CORBA::Octet*>(buffer));
      //length = m_cdr.bufSize();
      //m_cdr.getOctetStream(static_cast<CORBA::Octet*>(buffer), length, length);
      //m_cdr = OpenRTMCdrStream();
      return true;
#endif
    }

    CORBA_CdrMemoryStream::CORBA_CdrMemoryStream(const CORBA_CdrMemoryStream & rhs)
    {
#ifdef ORB_IS_ORBEXPRESS
      m_cdr.copy(rhs.m_cdr);
#elif defined(ORB_IS_TAO)
      for (const ACE_Message_Block* i = rhs.m_cdr.begin(); i != nullptr; i = i->cont())
      {
        m_cdr.write_octet_array_mb(i);
      }
#else
      m_cdr = rhs.m_cdr;
#endif
    }

    CORBA_CdrMemoryStream& CORBA_CdrMemoryStream::operator= (const CORBA_CdrMemoryStream& rhs)
    {
#ifdef ORB_IS_ORBEXPRESS
      m_cdr.copy(rhs.m_cdr);
      return *this;
#elif defined(ORB_IS_TAO)
      for (const ACE_Message_Block* i = rhs.m_cdr.begin(); i != nullptr; i = i->cont())
      {
        m_cdr.write_octet_array_mb(i);
      }
      return *this;
#else
      m_cdr = rhs.m_cdr;
      return *this;
#endif
    }

    /*!
     * @if jp
     * @brief データのアドレスのコピーを許可しているかを返す
     *
     * @return false：実装上の都合でアドレスのコピーを許可していない
     *
     * @else
     * @brief
     *
     * @return 
     *
     * @endif
     */
    bool CORBA_CdrMemoryStream::availableCopyFromAddress()
    {
#ifdef ORB_IS_ORBEXPRESS
      return false;
#elif defined(ORB_IS_TAO)
      return false;
#else
      return true;
#endif
    }

} // namespace RTC
