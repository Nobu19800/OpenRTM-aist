// -*- C++ -*-
/*!
 * @file TimeMeasure.cpp
 * @brief Periodic time measurement class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <limits.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <coil/Mutex.h>
#include <coil/Guard.h>


#define BUFFER_LEN LINE_MAX

namespace coil
{
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class log_streambuf
    : public ::std::basic_streambuf<_CharT, _Traits>
  {
  public:
    typedef _CharT                                       char_type;
    typedef _Traits                                      traits_type;
    typedef std::basic_streambuf<char_type, traits_type> streambuf_type;
    typedef coil::Mutex Mutex;
    typedef coil::Guard<coil::Mutex> Guard;

    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    log_streambuf()
      : streambuf_type()
    {
      char *pStart = m_buf;
      char *pEnd = m_buf + (BUFFER_LEN - 1);
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
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~log_streambuf()
    {
    }

    /*!
     * @if jp
     *
     * @brief ���ȥ꡼����ɲä���
     *
     * log_streambuf �˼ºݤν�����Ǥ��륹�ȥ꡼����ɲä��롣
     * �������ɲä��줿���ȥ꡼��β�����Ǥ�ϥ桼���ˤ��ꡢ
     * log_streambuf ���λ��ˤϲ��Τ���뤳�ȤϤʤ���
     * �ޤ��ɲä���Ƥ��륹�ȥ꡼��� log_streambuf �β�������
     * ���Τ��ƤϤʤ�ʤ������ȥ꡼��β��Τ� log_streambuf �β��θ�ˡ�
     * �桼�������Τ��ʤ���Фʤ�ʤ���
     *
     * @param stream std::basic_streambuf ���Υ��ȥ꡼��ؤΥݥ���
     *
     * @else
     *
     * @brief Destructor
     *
     * This operation adds a stream that is actual output stream.
     * User has responsibility to destruct the stream object, since
     * this object never destructs the stream objects.  The added
     * stream objects should not be destructed before the destruction
     * of this object.  The stream destruction should be done by user
     * after removing it from this object or destructing this object.
     *
     * @param stream a pointer to std::basic_streambuf type stream object
     *
     * @endif
     */
    void addStream(streambuf_type* stream, bool cleanup = false)
    {
      m_streams.push_back(Stream(stream, cleanup));
    }

    /*!
     * @if jp
     *
     * @brief ���ȥ꡼���������
     *
     * log_streambuf ���������Ǥ��륹�ȥ꡼��������롣
     * �����Ǻ�����줿���ȥ꡼��β�����Ǥ�ϥ桼���ˤ��롣
     *
     * @param stream std::basic_streambuf ���Υ��ȥ꡼��ؤΥݥ���
     *
     * @else
     *
     * @brief Destructor
     *
     * This operation remove a stream that is actual output stream.
     * User has responsibility to destruct the stream object.
     *
     * @param stream a pointer to std::basic_streambuf type stream object
     * @return Whether removing the stream succeeded.
     *
     * @endif
     */
    bool removeStream(streambuf_type* stream)
    {
      for (int i(0), len(m_streams.size()); i < len; ++i)
        {
          if (m_streams[i].stream_ == stream)
            {
              m_streams.erase(i);
              return true;
            }
        }
      return false;
    }


    std::vector<streambuf_type*> getBuffers()
    {
      std::vector<streambuf_type*> buffs;
      for (int i(0), len(m_streams.size()); i < len; ++i)
        {
          buffs.push_back(m_streams[i].stream_);
        }
      return buffs;
    }
   
  protected:
    /*!
     * @if jp
     *
     * @brief basic_streambuf::xsputn �Υ����С��饤��
     *
     * @param s ����ʸ����ؤΥݥ���
     * @param n ����ʸ����
     * @return ����ʸ����Υ�����
     *
     * @else
     *
     * @brief override of basic_streambuf::xsputn
     *
     * @param s a pointer to input characters
     * @param n number of input characters
     * @return input stream size
     *
     * @endif
     */
    virtual std::streamsize xsputn(const char_type* s, std::streamsize n)
    {
      for (int i(0), len(m_streams.size()); i < len; ++i)
        {
          Guard gaurd(m_streams[i].mutex_);
          m_streams[i].stream_->sputn(s, n);
        }
      return n;
    }

    /*!
     * @if jp
     *
     * @brief basic_streambuf::overflow �Υ����С��饤��
     *
     * @param c ����ʸ��
     * @return �ֵ���
     *
     * @else
     *
     * @brief override of basic_streambuf::overflow
     *
     * @param c input character
     * @return return value
     *
     * @endif
     */
    virtual int overflow (int c = traits_type::eof())
    {
      Guard guard(m_mutex);
//      if (traits_type::eq_int_type(c, traits_type::eof()))
//        return c;
//
//      char_type last_char = traits_type::to_char_type(c);
//      if (sputn(&last_char, 1) != 1)
//        return traits_type::eof();
//      else
//        return c;

      if (this->pbase())
        {
          if (this->pptr() > this->epptr() || this->pptr() < this->pbase())
            return traits_type::eof();
          // Add extra character to buffer if not EOF
          if (!traits_type::eq_int_type(c, traits_type::eof()))
            {
              *(this->pptr()) = traits_type::to_char_type(c);
              this->pbump(1);
            }
          // Number of characters to write to file
          int bytes_to_write = this->pptr() - this->pbase();
          // Overflow doesn't fail if nothing is to be written
          if (bytes_to_write > 0)
            {
              if (sputn(this->pbase(), bytes_to_write) != bytes_to_write)
                return traits_type::eof();
              // Reset next pointer to point to pbase on success
              this->pbump(-bytes_to_write);
            }
        }
      // Write extra character to file if not EOF
      else if (!traits_type::eq_int_type(c, traits_type::eof()))
        {
          // Impromptu char buffer (allows "unbuffered" output)
          char_type last_char = traits_type::to_char_type(c);
          // If gzipped file won't accept this character, fail
          if (sputn(&last_char, 1) != 1)
            return traits_type::eof();
        }
      // If you got here, you have succeeded (even if c was EOF)
      // The return value should therefore be non-EOF
      if (traits_type::eq_int_type(c, traits_type::eof()))
        return traits_type::not_eof(c);
      else
        return c;
    } 

    /*!
     * @if jp
     *
     * @brief basic_streambuf::sync �Υ����С��饤��
     *
     * @return �ֵ���
     *
     * @else
     *
     * @brief override of basic_streambuf::sync
     *
     * @return return value
     *
     * @endif
     */
    virtual int sync()
    {
      if (this->pbase())
        {
          //          Guard guard(m_mutex);
          if (this->pptr() > this->epptr() || this->pptr() < this->pbase())
            return -1;

          int bytes_to_write = this->pptr() - this->pbase();
          if (bytes_to_write > 0)
            {
              if (sputn(this->pbase(), bytes_to_write) != bytes_to_write)
                {
                  return -1;
                }
              this->pbump(-bytes_to_write);
            }
        }
      else
        {
          this->overflow();
        }
      return 0;
    }

  private:
    log_streambuf(const log_streambuf& x);
    log_streambuf& operator=(const log_streambuf& x);

    struct Stream
    {
      Stream(streambuf_type* stream, bool cleanup = false)
        : stream_(stream), cleanup_(cleanup)
      {
      }

      virtual ~Stream()
      {
      }

      Stream(const Stream& x)
        : stream_(x.stream_)
      {
      }

      Stream& operator=(const Stream& x)
      {
        Stream tmp(x);
        tmp.swap(*this);
        return *this;
      }

      void swap(Stream& x)
      {
        streambuf_type* stream = x.stream_;
        bool cleanup = x.cleanup_;

        x.stream_ = this->stream_;
        x.cleanup_ = this->cleanup_; 

        this->stream_ = stream;
        this->cleanup_ = cleanup;
      }
      mutable Mutex mutex_;
      streambuf_type* stream_;
      bool cleanup_;
    };
    std::vector<Stream> m_streams;
    Mutex m_mutex;
    char m_buf[BUFFER_LEN];
  };


  /*!
   * @if jp
   * @class log_stream ���饹
   *
   * @else
   * @class log_stream class
   *
   * @endif
   */
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class log_stream
    : public std::basic_ostream<_CharT, _Traits>
  {
  public:
    // Types:
    typedef _CharT                                       char_type;
    typedef _Traits                                      traits_type;
    typedef std::basic_ostream<char_type, traits_type>   ostream_type;
    typedef std::basic_streambuf<char_type, traits_type> streambuf_type;
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;

    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param streambuf basic_streambuf �����֥�������
     * @param levelmin ����٥�κǾ���
     * @param levelmax ����٥�κ�����
     * @param �ǥե���ȤΥ���٥�
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param streambuf basic_streambuf type object
     * @param levelmin minimum value for log level
     * @param levelmax maximum value for log level
     * @param level default log level
     *
     * @endif
     */
    log_stream(streambuf_type* sb, int levelmin, int levelmax, int level)
      : ostream_type(sb),
        m_minLevel(levelmin), m_maxLevel(levelmax), m_logLevel(level),
        m_lockEnable(false) 
    {
      if (m_minLevel >= m_maxLevel) throw std::bad_alloc();
      this->init(sb);
    }

    /*!
     * @if jp
     *
     * @brief ��å������Υإå��ɲôؿ�
     *
     * ���֥��饹�ˤ����Ƥ��δؿ��򥪡��С��饤�ɤ���
     * ����å�������Ŭ���ʻ���ʤɤΥإå����ɲä��롣
     *
     * @else
     *
     * @brief Message header appender function
     *
     * Subclasses of this class should override this operation, and
     * this function should be defined to append some header to the
     * log messages.
     *
     * @endif
     */
    virtual void header(int level)
    {
      return;
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
    bool setLevel(int level)
    {
      if (m_minLevel <= level && level <= m_maxLevel)
        {
          m_logLevel = level;
          return true;
        }
      return false;
    }

    /*!
     * @if jp
     *
     * @brief ����٥����
     *
     * ����٥��������롣
     *
     * @return ����٥�
     *
     * @else
     *
     * @brief Get the log level
     *
     * Get the log level.
     *
     * @return Log level
     *
     * @endif
     */
    int getLevel() const
    {
      return m_logLevel;
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
    void enableLock()
    {
      m_lockEnable = true;
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
    void disableLock()
    {
      m_lockEnable = false;
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
    ostream_type& level(int level)
    {
      if (m_minLevel <= level && level <= m_logLevel)
	{
          header(level);
	  return *this;
	}
      else
	{
	  return m_dummy;
	}
    }
    
    bool isValid(int level) const
    {
      return m_minLevel <= level && level <= m_logLevel;
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
    inline void lock()
    {
      if (m_lockEnable) m_mutex.lock();
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
    inline void unlock()
    {
      if (m_lockEnable) m_mutex.unlock();
    }

    
  protected:
    ~log_stream(){};
    log_stream();
    log_stream(const log_stream& x);
    log_stream& operator=(const log_stream& x);

  private:
    int m_minLevel, m_maxLevel;
    int m_logLevel;
    bool m_lockEnable;
    Mutex m_mutex;

    /*!
     * @if jp
     * @brief ���ߡ����ȥ꡼��
     * @else
     * @brief Dummy log
     * @endif
     */
    std::ofstream m_dummy;
  };


  typedef log_streambuf<char> LogStreamBuffer;
  typedef log_stream<char> LogStream;

};
#endif // LOGGER_H
