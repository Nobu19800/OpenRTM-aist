// -*- C++ -*-
/*!
 * @file SystemLogger.h
 * @brief RT component logger class
 * @date $Date: 2007-07-20 16:10:32 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef SystemLogger_h
#define SystemLogger_h

#include <rtm/RTC.h>

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <time.h>
#include <errno.h>

// ACE
#include <ace/Mutex.h>

#include <rtm/config_rtc.h>

#ifdef RTM_GCC2
#define NO_LOGGING
#endif

#ifdef WIN32
// It's dummy
#define __restrict
#endif

namespace RTC
{
  
#ifndef NO_LOGGING 
  /*!
   * @if jp
   * @class sync_callback
   * @brief sync_callback ��ݥ��饹
   *
   * �Хåե�Ʊ�������Τ���Υ�����Хå��ؿ�����ݥ��󥿡��ե��������饹��
   *
   * @else
   * @class sync_callback
   * @brief sync_callback abstract class
   *
   * This is the abstract interface class for callback function to
   * synchronize buffer processings.
   *
   * @endif
   */
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class sync_callback
  {
  public:
    /*!
     * @if jp
     * @brief ���ۥǥ��ȥ饯��
     * 
     * @else
     * @brief Virtual destractor
     *
     * @endif
     */
    virtual ~sync_callback(){}
    
    /*!
     * @if jp
     * @brief �����黻��
     *
     * ������Ϳ����줿�ͤ��������롣
     *
     * @param s ������
     *
     * @return �������
     *
     * @else
     *
     * @brief Assignment operator
     *
     * Assign the value given by the argument.
     *
     * @param s Assignment value
     *
     * @return Assignment result
     *
     * @endif
     */
    virtual int operator()(const _CharT* s) = 0;
  };
  
  //============================================================
  /*!
   * @if jp
   *
   * @class basic_logbuf
   *
   * @brief �����Хåե����饹
   *
   * basic_filebuf �饤���ʥ��Хåե����饹��������ե�����ؤΥ��Ǥ��Ф�
   * ���������Хåե����饹��
   *
   * @else
   *
   * @class basic_logbuf
   *
   * @brief Logger buffer class
   *
   * This is a logger buffer class like basic_filebuf.
   * Buffer class that manages to output logfiles to the local file.
   *
   * @endif
   */
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class basic_logbuf
    : public std::basic_filebuf<_CharT, _Traits>
  {
  public:
    // Types:
    typedef _CharT                                     char_type;
    typedef _Traits                                    traits_type;
    typedef std::basic_filebuf<char_type, traits_type> __filebuf_type;
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * �ǥե���ȥ��󥹥ȥ饯��
     *
     * @else
     *
     * @brief constructor.
     *
     * Default constructor
     *
     * @endif
     */
    basic_logbuf()
      : __filebuf_type(), m_pCallBack(NULL)
    {;}
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * �ե�����̾����ӥ����ץ�⡼�ɤ���ꤷ�ƥ��󥹥ȥ饯�Ȥ��륳�󥹥ȥ饯��
     *
     * @param s ���ե�����̾
     * @param mode �����ץ�⡼��(�ǥե������:�񤭹��ߥ⡼��)
     * @param protection 
     *
     * @else
     *
     * @brief Constructor.
     *
     * Constructor that constructs with specifying file names and open-mode.
     *
     * @param s Log file name
     * @param mode Open mode(The default value:write-mode)
     * @param protection 
     *
     * @endif
     */
    basic_logbuf(const char_type* s,
		 std::ios_base::openmode mode = std::ios_base::out, 
		 long protection = 0666)
      : __filebuf_type(), m_pCallBack(NULL)
    {
      this->open(s, mode);
    }
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯�����ե�����򥯥������롣
     *
     * @else
     *
     * @brief Destractor.
     *
     * Destructor. Close the file.
     *
     * @endif
     */
    virtual ~basic_logbuf()
    {
      this->sync();
      this->close();
    };
    
    /*!
     * @if jp
     *
     * @brief �Хåե��ؤν񤭹���
     *
     * ���ꤵ�줿ʸ�������ꤵ�줿ʸ����ʬ�Хåե��ؽ񤭹��ࡣ
     *
     * @param s �񤭹����о�ʸ����
     * @param n �񤭹���ʸ����
     *
     * @return �ºݤ˽񤭹��ߤ�Ԥä�ʸ����
     *
     * @else
     *
     * @brief Write into the buffer
     *
     * Write specified string through specified number of characters into the
     * buffer
     *
     * @param s Target string
     * @param n Number of characters
     *
     * @return Number of actual written characters
     *
     * @endif
     */
    virtual std::streamsize sputn(const char_type* s, std::streamsize n)
    {
      ACE_Guard<ACE_Thread_Mutex> gaurd(m_Mutex);
      //	  std::string ss(s, n);
      //	  std::string sss;
      //	  sss = "HogeDara" + ss;
      std::streamsize ssize = this->xsputn(s, n);
      /*
	if (m_pCallBack != NULL)
	{
	(*m_pCallBack)(sss.c_str());
	}
      */
      this->sync();
      return ssize;
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�Ʊ���ѥ�����Хå��ؿ�������
     *
     * �Хåե�Ʊ����¹Ԥ��뤿��Υ�����Хå��ؿ������ꤹ�롣
     *
     * @param cb �����оݥ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Set callback function for buffer's synchronization
     *
     * Set the callback function to execute the buffer's synchronization.
     *
     * @param cb Target callback function for setting
     *
     * @endif
     */
    void setSyncCallBack(sync_callback<char_type>& cb)
    {
      m_pCallBack = &cb;
    }
    
  protected:
    /*!
     * @if jp
     *
     * @brief �Хåե�Ʊ��
     *
     * �Хåե����ե�å��夵�줿�ݤ˸ƤФ��Ʊ���ؿ���
     *
     * @return �Хåե�Ʊ���������
     *
     * @else
     *
     * @brief Synchronization of buffer
     *
     * Synchronous function to be invoked when the buffer was flushed.
     *
     * @return Synchronous processing result of the buffer
     *
     * @endif
     */
    virtual int sync()
    {
      std::basic_string<_CharT> s(this->pbase(),
				  this->pptr() - this->pbase());
      if (m_pCallBack != NULL)
	{
	  (*m_pCallBack)(s.c_str());
	}
      // __filebuf_type::sync() resets the pointer
      int ret = __filebuf_type::sync();
      
      return ret;
    }
    
  private:
    ACE_Thread_Mutex m_Mutex;
    sync_callback<char_type>* m_pCallBack;
  };
  
  //============================================================
  /*!
   * @if jp
   *
   * @class basic_medlogbuf
   *
   * @brief �������Хåե����饹
   *
   * basic_streambuf �饤���ʥ��Хåե����饹��basic_filebuf �ؤ����򤹤롣
   * stream ���������ä�ʸ����˥إå��ʤɤ��ղä� basic_filebuf ���Ϥ���
   *
   * @else
   *
   * @class basic_medlogbuf
   *
   * @brief Mediate logger buffer class
   *
   * This is a logger buffer class like basic_streambuf.
   * Mediates to basic_filebuf.
   * Add the header etc to the string received from stream and pass it to
   * basic_filebuf.
   *
   * @endif
   */
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class basic_medlogbuf
    : public std::basic_streambuf<_CharT, _Traits>
  {
  public:
    // Types:
    typedef _CharT                                       char_type;
    typedef _Traits                                      traits_type;
    typedef std::basic_streambuf<char_type, traits_type> __streambuf_type;
    typedef std::basic_filebuf<char_type, traits_type>   __filebuf_type;
    
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    basic_medlogbuf()
      : __streambuf_type(), m_pLogbuf(NULL)
    {
      // W3C standard date and time format.
      m_DateFmt = "[%Y-%m-%dT%H.%M.%S%Z]";
    }
    
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param filebuf ���ե������ѥХåե�
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param filebuf Buffer for log file
     *
     * @endif
     */
    basic_medlogbuf(__filebuf_type& filebuf)
      : __streambuf_type(), m_pLogbuf(&filebuf)
    {
      char *pStart = m_Data;
      char *pEnd = m_Data + (LINE_MAX - 1);
      this->setp(pStart, pEnd);            // �񤭹��ߥݥ��󥿡�
      this->setg(pStart, pStart, pEnd);    // �ɤ߼��ݥ��󥿡�
      
      // W3C standard date and time format.
      m_DateFmt = "[%Y-%m-%dT%H.%M.%S%Z]";
    }
    
    /*!
     * @if jp
     *
     * @brief basic_medlogbuf ���ԡ����󥹥ȥ饯��
     *
     * @else
     *
     * @brief basic_medlogbuf copy constructor.
     *
     * @endif
     */
    basic_medlogbuf(const basic_medlogbuf& x)
      : __streambuf_type(), m_pLogbuf(x.m_pLogbuf),
	m_DateFmt(x.m_DateFmt), m_Suffix(x.m_Suffix)
    {
      char *pStart = m_Data;
      char *pEnd = m_Data + (LINE_MAX - 1);
      this->setp(pStart, pEnd);            // �񤭹��ߥݥ��󥿡�
      this->setg(pStart, pStart, pEnd);    // �ɤ߼��ݥ��󥿡�
    }
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     *
     * @else
     *
     * @brief Destractor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~basic_medlogbuf()
    {
      this->sync();
    }
    
    /*!
     * @if jp
     * @brief ���Хåե�����
     *
     * ���ꤷ���ե�����Хåե�����Хåե��Ȥ������ꤹ�롣
     *
     * @param filebuf ���ե������ѥХåե�
     *
     * @else
     * @brief Set the log buffer
     *
     * Set the specified file buffer as log buffer.
     *
     * @param filebuf Buffer for log file
     *
     * @endif
     */
    void setBuffer(__filebuf_type& filebuf)
    {
      m_pLogbuf = &filebuf;
      char *pStart = m_Data;
      char *pEnd = m_Data + (LINE_MAX - 1);
      this->setp(pStart, pEnd);            // �񤭹��ߥݥ��󥿡�
      this->setg(pStart, pStart, pEnd);    // �ɤ߼��ݥ��󥿡�
    }
    
    /*!
     * @if jp
     *
     * @brief �إå����ղä��������ե����ޥåȤ���ꤹ�롣
     *
     * �ե����ޥåȻ���ʸ����ϰʲ��ΤȤ��ꡣ
     * <pre>
     * @%a abbreviated weekday name 
     * @%A full weekday name 
     * @%b abbreviated month name 
     * @%B full month name 
     * @%c the standard date and time string 
     * @%d day of the month, as a number (1-31) 
     * @%H hour, 24 hour format (0-23) 
     * @%I hour, 12 hour format (1-12) 
     * @%j day of the year, as a number (1-366) 
     * @%m month as a number (1-12).
     *    Note: some versions of Microsoft Visual C++ may use values that range
     *    from 0-11. 
     * @%M minute as a number (0-59) 
     * @%p locale's equivalent of AM or PM 
     * @%S second as a number (0-59) 
     * @%U week of the year, sunday as the first day 
     * @%w weekday as a decimal (0-6, sunday=0) 
     * @%W week of the year, monday as the first day 
     * @%x standard date string 
     * @%X standard time string 
     * @%y year in decimal, without the century (0-99) 
     * @%Y year in decimal, with the century 
     * @%Z time zone name 
     * %% a percent sign 
     * </pre>
     *
     * @param fmt �����ե����ޥå�
     *
     * @else
     *
     * @brief Set date/time format for adding the header
     *
     * The format specification string is as follows:
     * <pre>
     * @%a abbreviated weekday name 
     * @%A full weekday name 
     * @%b abbreviated month name 
     * @%B full month name 
     * @%c the standard date and time string 
     * @%d day of the month, as a number (1-31) 
     * @%H hour, 24 hour format (0-23) 
     * @%I hour, 12 hour format (1-12) 
     * @%j day of the year, as a number (1-366) 
     * @%m month as a number (1-12).
     *    Note: some versions of Microsoft Visual C++ may use values that range
     *    from 0-11. 
     * @%M minute as a number (0-59) 
     * @%p locale's equivalent of AM or PM 
     * @%S second as a number (0-59) 
     * @%U week of the year, sunday as the first day 
     * @%w weekday as a decimal (0-6, sunday=0) 
     * @%W week of the year, monday as the first day 
     * @%x standard date string 
     * @%X standard time string 
     * @%y year in decimal, without the century (0-99) 
     * @%Y year in decimal, with the century 
     * @%Z time zone name 
     * %% a percent sign 
     * </pre>
     *
     * @param fmt Datetime format
     *
     * @endif
     */
    void setDateFmt(char* fmt)
    {
      m_DateFmt = std::string(fmt);
    }
    
    /*!
     * @if jp
     *
     * @brief �إå����ղä��������ե����ޥåȤ���ꤹ�롣
     *
     * �ե����ޥåȻ���ʸ����ˤĤ��Ƥϡ�void setDateFmt(char*)�򻲾ȡ�
     *
     * @param fmt �����ե����ޥå�ʸ����
     *
     * @else
     *
     * @brief Set date/time format for adding the header
     *
     * For more details on the format specification string, please refer to
     * void setDateFmt(char*).
     *
     * @param fmt Datetime format string
     *
     * @endif
     */
    void setDateFmt(const std::string& fmt)
    {
      m_DateFmt = fmt;
    }
    
    /*!
     * @if jp
     *
     * @brief �ե����ޥåȤ��줿��������ʸ�����������롣
     *
     * ���ꤵ�줿�񼰤ǵ��Ҥ�������������������롣
     *
     * @return �񼰻��긽������
     *
     * @else
     *
     * @brief Get the current formatted date/time string
     *
     * Get the current datetime described by specified format.
     *
     * @return Format specification current datetime
     *
     * @endif
     */
    std::string getFmtDate()
    {
      const int maxsize = 256;
      char buf[maxsize];
      /*
	struct timeval tp;
	struct timezone tzp;
	gettimeofday(&tp, &tzp);
      */
      time_t timer;
      struct tm* date;
      
      timer = time(NULL);
      date = localtime(&timer);
      strftime(buf, maxsize, m_DateFmt.c_str(), date);
      
      std::string ret(buf);
      return ret;
    }
    
    /*!
     * @if jp
     *
     * @brief �إå��������θ���ղä���ʸ��������ꤹ�롣
     *
     * �إå��������θ���ղä�����Ƭ��ʸ��������ꤹ�롣
     *
     * @param suffix ��Ƭ��ʸ����
     *
     * @else
     *
     * @brief Set suffix of date/time string of header.
     *
     * Set the suffix string added after the datatime of the header.
     *
     * @param suffix Suffix string
     *
     * @endif
     */
    void setSuffix(char* suffix)
    {
      m_Suffix = std::string(suffix);
    }
    
    /*!
     * @if jp
     *
     * @brief �إå��������θ���ղä���ʸ��������ꤹ�롣
     *
     * �إå��������θ���ղä�����Ƭ��ʸ��������ꤹ�롣
     *
     * @param suffix ��Ƭ��ʸ����
     *
     * @else
     *
     * @brief Set suffix of date/time string of header.
     *
     * Set the suffix string added after the datatime of the header.
     *
     * @param suffix Suffix string
     *
     * @endif
     */
    void setSuffix(const std::string& suffix)
    {
      m_Suffix = suffix;
    }
    
    /*!
     * @if jp
     *
     * @brief �إå��������θ���ղä���ʸ�����������롣
     *
     * �إå��������θ���ղä�����Ƭ��ʸ�����������롣
     *
     * @return ��Ƭ��ʸ����
     *
     * @else
     *
     * @brief Get suffix of date/time string of header.
     *
     * Get the suffix string added after the datatime of the header.
     *
     * @return Suffix string
     *
     * @endif
     */
    std::string getSuffix()
    {
      return m_Suffix;
    }
    
    /*
      void setCallBack(void (*call_back)(std::string s))
      {
      
      }
    */
    
  protected:
    /*!
     * @if jp
     *
     * @brief �Хåե�Ʊ��
     *
     * �Хåե����ե�å��夵�줿�ݤ˸ƤФ��Ʊ���ؿ���
     *
     * @return �Хåե�Ʊ���������
     *
     * @else
     *
     * @brief synchronization of buffer
     *
     * Synchronous function to be invoked when the buffer was flushed.
     *
     * @return Synchronous processing result of the buffer
     *
     * @endif
     */
    virtual int sync()
    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      int ret(0); 
      if (m_pLogbuf != NULL && (this->pptr() - this->pbase()) > 0)
	{
	  {
	    //ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
	    *(this->pptr()) = '\0';
	    std::basic_string<_CharT> tmp(this->pbase(),
						  this->pptr() - 
						  this->pbase());
	    
	    std::string s = getFmtDate();
	    s += ( s.size() > 0 ? " " : "" ) + getSuffix();
	    s += ( getSuffix().size() > 0 ? " " : "" ) + tmp;
	    // s += (getSuffix().size() > 0 ? " " : "" ) + getSuffix();
	    // s += (s.size() > 0 ? " " : "") + tmp;
	    m_pLogbuf->sputn(s.c_str(), s.size());
	    m_pLogbuf->pubsync();
	    // Reset pptr() pointer to pbase()
	    // __streambuf_type::sync() resets the pointer
	    ret = __streambuf_type::sync();
	    pbump( this->pbase() - this->pptr() );
	  }
	}
      return ret;
    }
    
  private:
    __filebuf_type* m_pLogbuf;
    char m_Data[LINE_MAX];
    std::string m_DateFmt;
    std::string m_Suffix;
    ACE_Thread_Mutex m_Mutex;
  };
  
  /*!
   * @if jp
   *
   * @class basic_dummybuf
   *
   * @brief ���ߡ��Хåե����饹
   *
   * ���⤷�ʤ����ߡ��Хåե���
   *
   * @else
   *
   * @class basic_dammybuf
   *
   * @brief Dummy buffer class
   *
   * Dummy buffer class that does not do anything.
   *
   * @endif
   */
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class basic_dummybuf
    : public std::basic_streambuf<_CharT, _Traits>
  {
  public:
    // Types:
    typedef _CharT                               char_type;
    typedef _Traits                              traits_type;
    typedef typename traits_type::int_type       int_type;
    typedef typename traits_type::pos_type       pos_type;
    typedef typename traits_type::off_type       off_type;
    typedef std::basic_streambuf<char_type, traits_type> __streambuf_type;
    typedef std::basic_filebuf<char_type, traits_type>   __filebuf_type;
    
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    basic_dummybuf()
    {
      char *pStart = m_Data;
      char *pEnd = m_Data + (LINE_MAX - 1);
      this->setp(pStart, pEnd);
      this->setg(pStart, pStart, pEnd);
    }
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     *
     * @else
     *
     * @brief Destractor
     *
     * Destractor
     *
     * @endif
     */
    ~basic_dummybuf()
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե��񤭽Ф�����
     *
     * �Хåե��ν񤭽Ф�������¹Ԥ��롣
     * ���ϥХåե����ե�ˤʤä��ݤ˸ƤФ�롣
     *
     * @param c �Хåե��˽񤭹���ʸ����
     *
     * @return �񤭹��߽������
     *
     * @else
     *
     * @brief Write the buffer
     *
     * Run writing processing of the buffer
     * When the output buffer is full, this is invoked.
     *
     * @param c String written into the buffer
     *
     * @return Writing processing result
     *
     * @endif
     */
    int_type overflow(int_type c = _Traits::eof() )
    {
      pbump( this->pbase() - this->pptr() );
      return _Traits::not_eof(c);
    }
    
    /*!
     * @if jp
     *
     * @brief �Хåե�Ʊ��
     *
     * �Хåե����ե�å��夵�줿�ݤ˸ƤФ��Ʊ���ؿ���
     *
     * @return Ʊ���������
     *
     * @else
     *
     * @brief synchronization of buffer
     *
     * Synchronous function invoked when the buffer was flushed.
     *
     * @return Synchronous processing result
     *
     * @endif
     */
    virtual int sync()
    {
      pbump( this->pbase() - this->pptr() );
      return 0;
    }
    
  private:
    char m_Data[255];
  };
  
  /*!
   * @if jp
   *
   * @class basic_logstream
   *
   * @brief �����ե����ޥåȥ��饹
   *
   * basic_ostream �饤���ʥ��ե����ޥåȥ��饹��
   *
   * @else
   *
   * @class basic_logstream
   *
   * @brief Logger format class
   *
   * This is a logger format class like basic_ostream.
   *
   * @endif
   */
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class basic_logstream
    : public std::basic_ostream<_CharT, _Traits>
  {
  public:
    // Loglevel
    enum
      {          // No: Write out messages include the following.
	RTL_SILENT,  // 0: ()
	RTL_ERROR,   // 1: (ERROR)
	RTL_WARN,    // 2: (ERROR, WARN)
	RTL_INFO,    // 3: (ERROR, WARN, INFO)
	RTL_NORMAL,  // 4: (ERROR, WARN, INFO, NORMAL)
	RTL_DEBUG,   // 5: (ERROR, WARN, INFO, NORMAL, DEBUG)
	RTL_TRACE,   // 6: (ERROR, WARN, INFO, NORMAL, DEBUG, TRACE)
	RTL_VERBOSE, // 7: (ERROR, WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE)
	RTL_PARANOID,// 8: (ERROR, WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARA)
	RTL_MANDATORY// This level is used for only LogLockLevel
      };
    
    /*!
     * @if jp
     *
     * @brief ����٥�����
     *
     * Ϳ����줿ʸ������б���������٥�����ꤹ�롣
     *
     * @param lv ����٥�ʸ����
     *
     * @return ���ꤷ������٥�
     *
     * @else
     *
     * @brief Set the log level
     *
     * Set the log level corresponding to the given string.
     *
     * @param lv Log level string
     *
     * @return The set log level
     *
     * @endif
     */
    static int strToLogLevel(const std::string& lv)
    {
      if (lv == "SILENT")
	return basic_logstream::RTL_SILENT;
      else if (lv == "ERROR")
	return basic_logstream::RTL_ERROR;
      else if (lv == "WARN")
	return basic_logstream::RTL_WARN;
      else if (lv == "INFO")
	return basic_logstream::RTL_INFO;
      else if (lv == "NORNAL")
	return basic_logstream::RTL_NORMAL;
      else if (lv == "DEBUG")
	return basic_logstream::RTL_DEBUG;
      else if (lv == "TRACE")
	return basic_logstream::RTL_TRACE;
      else if (lv == "VERBOSE")
	return basic_logstream::RTL_VERBOSE;
      else if (lv == "PARANOID")
	return basic_logstream::RTL_PARANOID;
      else if (lv == "MANDATORY")
	return basic_logstream::RTL_MANDATORY;
      else
	return basic_logstream::RTL_NORMAL;
    }
    
    // Types:
    typedef _CharT                                       char_type;
    typedef _Traits                                      traits_type;
    typedef basic_logbuf<char_type, traits_type>         __logbuf_type;
    typedef basic_dummybuf<char_type, traits_type>       __dummybuf_type;
    typedef basic_logstream<char_type, traits_type>      __logstream_type;
    typedef std::basic_ostream<char_type, traits_type>   __ostream_type;
    typedef std::basic_streambuf<char_type, traits_type> __streambuf_type;
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param streambuf basic_streambuf �����֥�������
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param streambuf basic_streambuf type object
     *
     * @endif
     */
    basic_logstream(__streambuf_type& streambuf)
      : __ostream_type(&streambuf),
	m_DummyStream(new __dummybuf_type()),
	m_LogLevel(RTL_NORMAL), m_LogLock(false)
    {
      this->init(&streambuf);
    }
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    ~basic_logstream()
    {
    }
    
    /***
     * @if jp
     *
     * @brief �����ݻ����Ƥ���Хåե��ؤΥݥ��󥿤��֤���
     *
     * @else
     *
     * @brief Return a pointer of a current holding buffer.
     *
     * @endif
     */
    /*
      __logbuf_type*	rdbuf() const
      {
      return const_cast<__logbuf_type*>(&m_Streambuf);
      }
    */
    
    /*!
     * @if jp
     *
     * @brief printf �ե����ޥåȽ���
     *
     * printf�饤���ʽ񼰤ǥ����Ϥ��롣
     *
     * @param fmt ��ʸ����
     *
     * @return ���դ�ʸ�������
     *
     * @else
     *
     * @brief Formatted output like printf
     *
     * Output a log with a format like printf.
     *
     * @param fmt Formatted string
     *
     * @return Formatted string output
     *
     * @endif
     */
    static std::string printf(char const * __restrict fmt, ...)
    {
      char str[LINE_MAX];
      va_list ap;
      
      va_start(ap, fmt);
#ifdef WIN32
      _vsnprintf(str, LINE_MAX - 1, fmt, ap);
#else
      vsnprintf(str, LINE_MAX - 1, fmt, ap);
#endif
      va_end(ap);
      std::string s(str);
      
      return s;
    }
    
    /*!
     * @if jp
     *
     * @brief ����٥�����
     *
     * Ϳ����줿ʸ������б���������٥�����ꤹ�롣
     *
     * @param level ����٥�ʸ����
     *
     * @else
     *
     * @brief Set the log level
     *
     * Set the log level corresponding to the given string.
     *
     * @param level Log level string
     *
     * @endif
     */
    void setLogLevel(const std::string& level)
    {
      m_LogLevel = strToLogLevel(level);
    }
    
    /*!
     * @if jp
     *
     * @brief ����٥�����
     *
     * ����٥�����ꤹ�롣
     *
     * @param level ����٥�
     *
     * @else
     *
     * @brief Set the log level
     *
     * Set the log level.
     *
     * @param level Log level
     *
     * @endif
     */
    void setLogLevel(int level)
    {
      m_LogLevel = level;
    }
    
    /*!
     * @if jp
     *
     * @brief ��å��⡼������
     *
     * ���Υ�å��⡼�ɤ����ꤹ�롣
     *
     * @param lock ����å��ե饰
     *
     * @else
     *
     * @brief Set the lock mode
     *
     * Set the lock mode of log.
     *
     * @param lock Flag of log lock
     *
     * @endif
     */
    void setLogLock(bool lock)
    {
      m_LogLock = lock;
    }
    
    /*!
     * @if jp
     *
     * @brief ��å��⡼������
     *
     * ��å��⡼�ɤ�ͭ���ˤ��롣
     *
     * @else
     *
     * @brief Enable the lock mode
     *
     * Enable the lock mode.
     *
     * @endif
     */
    void enableLogLock()
    {
      m_LogLock = true;
    }
    
    /*!
     * @if jp
     *
     * @brief ��å��⡼�ɲ��
     *
     * ��å��⡼�ɤ�̵���ˤ��롣
     *
     * @else
     *
     * @brief Disable the lock mode
     *
     * Disable the lock mode.
     *
     * @endif
     */
    void disableLogLock()
    {
      m_LogLock = false;
    }
    
    /*!
     * @if jp
     *
     * @brief �����ȥ꡼��μ���
     *
     * ���ꤵ�줿����٥��Ƚ�Ǥ��������ȥ꡼���������롣
     * ���ꤵ�줿����٥뤬���ꤵ��Ƥ������٥�ʲ��ξ��ˤϡ��ܥ��饹��
     * �֤���
     * ���ꤵ�줿����٥뤬���ꤵ��Ƥ������٥��Ķ���Ƥ�����ˤϡ�
     * ���ߡ������饹���֤���
     *
     * @param level �������٥�
     *
     * @return �оݥ����ȥ꡼��
     *
     * @else
     *
     * @brief Acquire log stream
     *
     * Investigate the specified log level and get its log stream.
     * If the specified log level is under the set log level, this class
     * will be returned.
     * If the specified log level exceeds the set log level, a dummy log class
     * will be returned.
     *
     * @param level The specified log level
     *
     * @return Target log stream
     *
     * @endif
     */
    __ostream_type& level(int level)
    {
      if (m_LogLevel >= level)
	{
	  return *this;
	}
      else
	{
	  return m_DummyStream;
	}
    }
    
    /*!
     * @if jp
     *
     * @brief ����å�����
     * ��å��⡼�ɤ����ꤵ��Ƥ����硢���Υ�å���������롣
     *
     * @else
     *
     * @brief Acquire log lock
     * Acquire log lock when the lock mode is set.
     *
     * @endif
     */
    inline void acquire()
    {
      if (m_LogLock) m_Mutex.acquire();
    }
    
    /*!
     * @if jp
     *
     * @brief ����å�����
     * ��å��⡼�ɤ����ꤵ��Ƥ�����ˡ����Υ�å���������롣
     *
     * @else
     *
     * @brief Release the log lock
     * Release the log lock when the lock mode is set.
     *
     * @endif
     */
    inline void release()
    {
      if (m_LogLock) m_Mutex.release();
    }
    
    /*!
     * @if jp
     * @brief ���ߡ���
     * @else
     * @brief Dummy log
     * @endif
     */
    __ostream_type m_DummyStream;
    
  private:
    int m_LogLevel;
    bool m_LogLock;
    ACE_Thread_Mutex m_Mutex;
  };
  typedef sync_callback<char>   SyncCallback;
  typedef basic_logbuf<char>    Logbuf;
  typedef basic_medlogbuf<char> MedLogbuf;
  typedef basic_logstream<char> LogStream;
  
#else //// NO_LOGGING  
  
  /*!
   * @if jp
   * @class sync_callback
   * @brief sync_callback ���ߡ����饹
   *
   * �Хåե�Ʊ�������Τ���Υ�����Хå��ѥ��󥿡��ե��������饹�Υ��ߡ���
   *
   * @else
   * @class sync_callback
   * @brief sync_callback dummy class
   *
   * This is a the dummy interface class for callback function to
   * synchronize buffer processing.
   *
   * @endif
   */
  class SyncCallback
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��(���ߡ�)
     *
     * @else
     * @brief Constructor
     *
     * Constructor(dummy)
     *
     * @endif
     */
    SyncCallback() {;};
    
    /*!
     * @if jp
     * @brief �����黻��
     *
     * ������Ϳ����줿�ͤ��������롣(���ߡ�)
     *
     * @param s ������
     *
     * @return �������
     *
     * @else
     * @brief Assignment operator
     *
     * Assign the value given by the argument(dummy).
     *
     * @param s Assignment value
     *
     * @return Assignment result
     *
     * @endif
     */
    virtual int operator()(const char* s) {;};
  };
  
  /*!
   * @if jp
   *
   * @class Logbuf
   *
   * @brief �����Хåե����ߡ����饹
   *
   * ���Хåե��Υ��ߡ����饹��
   *
   * @else
   *
   * @class Logbuf
   *
   * @brief Logger buffer dummy class
   *
   * Dummy class of log buffer.
   *
   * @endif
   */
  class Logbuf
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * �ǥե���ȥ��󥹥ȥ饯��
     *
     * @else
     *
     * @brief Constructor
     *
     * Default constructor
     *
     * @endif
     */
    Logbuf() {;};
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * �ե�����̾����ӥ����ץ�⡼�ɤ���ꤷ�ƥ��󥹥ȥ饯�Ȥ��륳�󥹥ȥ饯��
     * (���ߡ�)
     *
     * @param s ���ե�����̾
     * @param m �����ץ�⡼��(�ǥե������:�񤭹��ߥ⡼��)
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor that constructs by specifying file names and open mode.
     * (Dummy)
     *
     * @param s Log file name
     * @param m Open mode(The default value:write-mode)
     *
     * @endif
     */
    Logbuf(const char* s, int m) {;};
    
    /*!
     * @if jp
     *
     * @brief ���Хåե��Υ����ץ�
     *
     * �ե�����̾����ӥ����ץ�⡼�ɤ���ꤷ�ƥ��Хåե��򥪡��ץ󤹤롣
     * (���ߡ�)
     *
     * @param s ���ե�����̾
     * @param m �����ץ�⡼��(�ǥե������:�񤭹��ߥ⡼��)
     *
     * @else
     *
     * @brief Open the log buffer
     *
     * Open the log buffer by specifying file names and open mode.
     * (Dummy)
     *
     * @param s Log file name
     * @param m Open mode(The default value:write-mode)
     *
     * @endif
     */
    void open(const char* s, int m) {;};
    
    /*!
     * @if jp
     *
     * @brief �Хåե�Ʊ���ѥ�����Хå��ؿ�������
     *
     * �Хåե�Ʊ����¹Ԥ��뤿��Υ�����Хå��ؿ������ꤹ�롣
     * (���ߡ�)
     *
     * @param cb �����оݥ�����Хå��ؿ�
     *
     * @else
     *
     * @brief Set callback function for buffer's synchronization
     *
     * Set the callback function to execute the buffer's synchronization.
     * (Dummy)
     *
     * @param cb Target callback function for setting
     *
     * @endif
     */
    void setSyncCallBack(SyncCallback& cb) {;};
  };
  
  /*!
   * @if jp
   * @class MedLogbuf
   * @brief �������Хåե����ߡ����饹
   *
   * �������Хåե��Υ��ߡ����饹��
   *
   * @else
   * @class MedLogbuf
   * @brief Mediate logger buffer dummy class
   *
   * Mediate logger buffer dummy class.
   *
   * @endif
   */
  class MedLogbuf
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��(���ߡ�)
     *
     * @else
     * @brief Constructor
     *
     * Constructor(dummy)
     *
     * @endif
     */
    MedLogbuf() {;};
    
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��(���ߡ�)
     *
     * @param filebuf ���ե������ѥХåե�
     *
     * @else
     * @brief Constructor
     *
     * Constructor(dummy)
     *
     * @param filebuf Buffer for log file
     *
     * @endif
     */
    MedLogbuf(Logbuf& f) {;};
    
    /*!
     * @if jp
     * @brief �إå����ղä��������ե����ޥåȤ���ꤹ�롣
     *
     * �����ե����ޥåȻ����ѥ��ߡ�
     *
     * @param fmt �����ե����ޥå�
     *
     * @else
     * @brief Set date/time format for adding the header
     *
     * Dummy for datetime format specification.
     *
     * @param fmt Datetime format
     *
     * @endif
     */
    void setDateFmt(char* fmt) {;};
    
    /*!
     * @if jp
     *
     * @brief �إå����ղä��������ե����ޥåȤ���ꤹ�롣
     *
     * �����ե����ޥåȻ����ѥ��ߡ�
     *
     * @param fmt �����ե����ޥå�ʸ����
     *
     * @else
     *
     * @brief Set date/time format for adding the header
     *
     * Dummy for datetime format specification.
     *
     * @param fmt Datetime format string
     *
     * @endif
     */
    void setDateFmt(const std::string& fmt) {;};
    
    /*!
     * @if jp
     *
     * @brief �إå��������θ���ղä���ʸ��������ꤹ�롣
     *
     * �إå��������θ���ղä�����Ƭ��ʸ��������ꤹ�롣
     * (���ߡ�)
     *
     * @param suffix ��Ƭ��ʸ����
     *
     * @else
     *
     * @brief Set suffix of date/time string of header.
     *
     * Set the suffix string added after the datatime of the header.
     * (Dummy)
     *
     * @param suffix Suffix string
     *
     * @endif
     */
    void setSuffix(const char* suffix) {;};
    
    /*!
     * @if jp
     *
     * @brief �إå��������θ���ղä���ʸ��������ꤹ�롣
     *
     * �إå��������θ���ղä�����Ƭ��ʸ��������ꤹ�롣
     * (���ߡ�)
     *
     * @param suffix ��Ƭ��ʸ����
     *
     * @else
     *
     * @brief Set suffix of date/time string of header.
     *
     * Set the suffix string added after the datatime of the header.
     * (Dummy)
     *
     * @param suffix Suffix string
     *
     * @endif
     */
    void setSuffix(const std::string& suffix) {;};
  };
  
  /*!
   * @if jp
   *
   * @class basic_logstream
   *
   * @brief �����ե����ޥåȥ��ߡ����饹
   *
   * ���ե����ޥå��ѥ��ߡ����饹��
   *
   * @else
   *
   * @class basic_logstream
   *
   * @brief Logger format dummy class
   *
   * Dummy class of log format.
   *
   * @endif
   */
  class LogStream
    : public ostream
  {
  public:
    enum
      {
	SILENT,
	ERROR,
	WARN,
	INFO,
	NORMAL,
	DEBUG,
	TRACE,
	VERBOSE,
	PARANOID,
	MANDATORY
      };
    
    /*!
     * @if jp
     *
     * @brief ����٥�����
     *
     * Ϳ����줿ʸ������б���������٥�����ꤹ�롣
     * (���ߡ�)
     *
     * @param lv ����٥�ʸ����
     *
     * @return ���ꤷ������٥�
     *
     * @else
     *
     * @brief Set the log level
     *
     * Set the log level corresponding to the given string.
     * (Dummy)
     *
     * @param lv Log level string
     *
     * @return Log level that was set
     *
     * @endif
     */
    static int strToLogLevel(const std::string& lv){return NORMAL;}
    
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     * (���ߡ�)
     *
     * @param streambuf basic_streambuf �����֥�������
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     * (Dummy)
     *
     * @param streambuf basic_streambuf type object
     *
     * @endif
     */
    LogStream(MedLogbuf& buf) {;};
    
    /*!
     * @if jp
     *
     * @brief ����٥�����
     *
     * Ϳ����줿ʸ������б���������٥�����ꤹ�롣
     * (���ߡ�)
     *
     * @param level ����٥�ʸ����
     *
     * @else
     *
     * @brief Set the log level
     *
     * Set the log level corresponding to the given string.
     * (Dummy)
     *
     * @param level Log level string
     *
     * @endif
     */
    void setLogLevel(int level) {;};
    
    /*!
     * @if jp
     *
     * @brief ��å��⡼������
     *
     * ���Υ�å��⡼�ɤ����ꤹ�롣
     * (���ߡ�)
     *
     * @param lock ����å��ե饰
     *
     * @else
     *
     * @brief Set the lock mode
     *
     * Set the lock mode of log.
     * (Dummy
     *
     * @param lock Flag of log lock
     *
     * @endif
     */
    void setLogLock(int lock) {;};
    
    /*!
     * @if jp
     *
     * @brief �����ȥ꡼��μ���
     *
     * ����ܥ��ߡ����饹���֤���
     *
     * @param level �������٥�
     *
     * @return �оݥ����ȥ꡼��
     *
     * @else
     *
     * @brief Acquire log stream
     *
     * Always return this dummy class.
     *
     * @param level Specified log level
     *
     * @return Target log stream
     *
     * @endif
     */
    LogStream& level(int level) {return *this;};
    /*
      LogStream& operator<<(const char* s) {return *this;};
      LogStream& operator<<(const string s) {return *this;};
      LogStream& operator<<(const ostream& o) {return *this;};
      LogStream& operator<<(const ostream o) {return *this;};
    */
  };
  
#endif // NO_LOGGING  
  
  
  // __VA_ARGS__ cannot be used in VC	
#if 0
#define RTC_LOG(LV, fmt, ...)						\
  rtcout.level(LV) << rtcout.printf(fmt, __VA_ARGS__) << std::endl;
#define RTC_ERROR(fmt, ...)				\
  RTC_LOG(LogStream::RTL_ERROR, fmt, __VA_ARGS__)
#define RTC_WARN(fmt, ...)				\
  RTC_LOG(LogStream::RTL_WARN, fmt, __VA_ARGS__)
#define RTC_NORMAL(fmt, ...)				\
  RTC_LOG(LogStream::RTL_NORMAL, fmt, __VA_ARGS__)
#define RTC_INFO(fmt, ...)				\
  RTC_LOG(LogStream::RTL_INFO, fmt, __VA_ARGS__)
#define RTC_DEBUG(fmt, ...)				\
  RTC_LOG(LogStream::RTL_DEBUG, fmt, __VA_ARGS__)
#define RTC_TRACE(fmt, ...)				\
  RTC_LOG(LogStream::RTL_TRACE, fmt, __VA_ARGS__)
#define RTC_VERBOSE(fmt, ...)				\
  RTC_LOG(LogStream::RTL_VERBOSE, fmt, __VA_ARGS__)
#define RTC_PARANOID(fmt, ...)				\
  RTC_LOG(LogStream::RTL_PARANOID, fmt, __VA_ARGS__)
#endif
  
#ifndef NO_LOGGING
  
  /*!
   * @if jp
   *
   * @brief ���ѥ����ϥޥ���
   *
   * ����٥뤪��ӽ��ϥե����ޥå�ʸ���������Ȥ��ƤȤ롣
   *
   * @else
   *
   * @brief General-purpose log output macro
   *
   * Acquire log level and output format string as arguments.
   *
   * @endif
   */
#define RTC_LOG(LV, fmt)			      \
  rtcout.acquire();				      \
  rtcout.level(LV) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief ���顼�����ϥޥ���
   *
   * ���顼��٥�Υ����ϥޥ���<BR>����٥뤬
   * ERROR, WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Error log output macro
   *
   * This is a log output macro of the error level.
   * If log levels are ERROR, WARN, INFO, NORMAL, DEBUG, TRACE,
   * VERBOSE or PARANOID, message will be output to log.
   *
   * @endif
   */
#define RTC_ERROR(fmt)							\
  rtcout.acquire();							\
  rtcout.level(LogStream::RTL_ERROR)  << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief ��˥󥰥����ϥޥ���
   *
   * ��˥󥰥�٥�Υ����ϥޥ���<BR>����٥뤬
   * ( WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Warning log output macro
   *
   * If log levels are
   * ( WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_WARN(fmt)							\
  rtcout.acquire();							\
  rtcout.level(LogStream::RTL_WARN) << rtcout.printf fmt << std::endl;	\
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief ����ե������ϥޥ���
   *
   * ����ե���٥�Υ����ϥޥ���<BR>����٥뤬
   * ( INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Information level log output macro
   *
   *  If log levels are
   * ( INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_INFO(fmt)							\
  rtcout.acquire();							\
  rtcout.level(LogStream::RTL_INFO) << rtcout.printf fmt << std::endl;	\
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief �Ρ��ޥ�����ϥޥ���
   *
   * �Ρ��ޥ��٥�Υ����ϥޥ���<BR>����٥뤬
   * ( NORMAL, DEBUG, TRACE, VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Normal level log output macro.
   *
   * If log levels are
   * ( NORMAL, DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_NORMAL(fmt)							\
  rtcout.acquire();							\
  rtcout.level(LogStream::RTL_NORMAL) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief �ǥХå������ϥޥ���
   *
   * �ǥХå���٥�Υ����ϥޥ���<BR>����٥뤬
   * ( DEBUG, TRACE, VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Debug level log output macro.
   *
   * If log levels are
   * ( DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_DEBUG(fmt)							\
  rtcout.acquire();							\
  rtcout.level(LogStream::RTL_DEBUG) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief �ȥ졼�������ϥޥ���
   *
   * �ȥ졼����٥�Υ����ϥޥ���<BR>����٥뤬
   * ( TRACE, VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Trace level log output macro.
   *
   * If log levels are
   * ( TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_TRACE(fmt)							\
  rtcout.acquire();							\
  rtcout.level(LogStream::RTL_TRACE) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief �٥�ܡ��������ϥޥ���
   *
   * �٥�ܡ�����٥�Υ����ϥޥ���<BR>����٥뤬
   * ( VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Verbose level log output macro.
   *
   * If log levels are
   * ( VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_VERBOSE(fmt)						\
  rtcout.acquire();							\
  rtcout.level(LogStream::RTL_VERBOSE) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief �ѥ�Υ��ɥ����ϥޥ���
   *
   * �ѥ�Υ��ɥ�٥�Υ����ϥޥ���<BR>����٥뤬
   * ( PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Paranoid level log output macro.
   *
   * If log levels are
   * ( PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_PARANOID(fmt)						\
  rtcout.acquire();							\
  rtcout.level(LogStream::RTL_PARANOID) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
#else
#define RTC_ERROR(fmt)
#define RTC_WARN(fmt)
#define RTC_NORMAL(fmt)
#define RTC_INFO(fmt)
#define RTC_DEBUG(fmt)
#define RTC_TRACE(fmt)
#define RTC_VERBOSE(fmt)
#define RTC_PARANOID(fmt)
#endif
  
}; // namespace RTC

#endif  // SystemLogger_h
