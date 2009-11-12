// -*- C++ -*-
/*!
 * @file  TcpSockServer.h
 * @brief TcpSockServer class
 * @date  $Date: 2007-10-06 12:30:16 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
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

#ifndef RTC_TCPSOCKSERVER_H
#define RTC_TCPSOCKSERVER_H

#define RAWTCP_DEFAULT_BUFFER_SIZE 128

#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Event_Handler.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>
#include <coil/Task.h>
#include <ace/OS.h>
#include <iostream>
#include <rtm/BufferBase.h>
#include <rtm/StringUtil.h>
#include <rtm/Properties.h>

namespace RTC
{
  
  //============================================================
  // TCP Server classes
  //============================================================
  template <class DataType> class TcpHandler;
  
  /*!
   * @if jp
   * @class TcpAcceptor
   * @brief TcpAcceptor ���饹
   *
   * TCP �������ѥ������ץ����饹��
   *
   * @param DataType �������ץ��ǽ�������ǡ�����
   *
   * @else
   *
   * @class TCPAcceptor
   * @brief TcpAcceptor class
   *
   * TCP Server acceptor class.
   * 
   * @param DataType Data type processed in the acceptor
   *
   * @endif
   */
  template <class DataType>
  class TcpAcceptor
    : public ACE_Event_Handler
  {
    friend class TcpHandler<DataType>;
    
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param buffer �Хåե�
     * @param prop �ץ�ѥƥ�����
     *
     * @else
     * @brief Constructor
     * 
     * Constructor
     *
     * @param buffer Buffer
     * @param prop Property information
     *
     * @endif
     */
    TcpAcceptor(BufferBase<DataType>& buffer, Properties& prop)
      : m_buffer(buffer), m_prop(prop)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * @else
     *
     * @brief Virtual destructor
     *
     * @endif
     */
    virtual ~TcpAcceptor(void)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief �����åȥ����ץ�ȥϥ�ɥ���Ͽ
     * 
     * ���ꤵ�줿���ɥ쥹��ƻ뤹�뤿��Υꥹ�ʡ�����������ȤȤ�ˡ�
     * �ͥåȥ���̿���ƻ뤹�뤿��Υ��٥�ȥϥ�ɥ����Ͽ���롣
     *
     * @param addr �ƻ��оݥ��ɥ쥹
     * @param reactor �̿����٥�ȴƻ��ѥꥢ����
     *
     * @return �������
     *
     * @else
     *
     * @brief Opening socket and registering handler
     * 
     * Initialize listener to monitor the specified address and
     * register the event handler to monitor the network communication.
     *
     * @param addr Address for monitoring
     * @param reactor Reactor to monitor the communication event
     *
     * @return Handling result
     *
     * @endif
     */
    int open(const ACE_INET_Addr& addr, ACE_Reactor* reactor)
    {
      if (this->m_peerAcceptor.open(addr, 1) == -1)
	{
	  return -1;
	}
      m_reactor = reactor;
      
      // Getting real acceptor's address and port number.
      this->m_peerAcceptor.get_local_addr(m_addr);
      
      // Set handler
      int ret;
      ret = m_reactor->register_handler(this, ACE_Event_Handler::ACCEPT_MASK);
      return ret;
    }
    
    /***
     * @if jp
     *
     * @brief ���ɥ쥹�μ���
     * 
     * �����ץ�������ꤷ�����ɥ쥹���֤�
     *
     * @else
     *
     * @brief Get the address
     *
     * Return the address set at the time of opening.
     *
     * @endif
     */
    /*
      ACE_INET_Addr get_addr() const
      {
      return m_addr;
      }
    */
    
    /*!
     * @if jp
     *
     * @brief �ݡ����ֹ�μ���
     * 
     * �����ץ�������ꤷ���ݡ����ֹ��������롣
     *
     * @return �ݡ����ֹ�
     *
     * @else
     *
     * @brief Get the port number
     *
     * Get the port number set at the time of opening.
     *
     * @return The port number
     *
     * @endif
     */
    unsigned short get_port_number(void) const
    {
      return m_addr.get_port_number();
    }
    
  private:
    /*!
     * @if jp
     *
     * @brief �ϥ�ɥ����
     * 
     * �ԥ��������ץ��Υϥ�ɥ��������롣
     *
     * @return �ϥ�ɥ����
     *
     * @else
     *
     * @brief Get the handle
     *
     * Get the peer acceptor handle.
     *
     * @return Handle information
     *
     * @endif
     */
    ACE_HANDLE get_handle(void) const
    { 
      return m_peerAcceptor.get_handle(); 
    }
    
    /*!
     * @if jp
     *
     * @brief ���ϥϥ�ɥ�ؿ�
     * 
     * �����åȤ���³�����ä����˸ƤФ��ϥ�ɥ�ؿ���
     *
     * @return ���٥�Ƚ������
     *
     * @else
     *
     * @brief Input handler function
     *
     * Handler function to be invoked when sock connection is accepted.
     *
     * @return Event handling result
     *
     * @endif
     */
    int handle_input(ACE_HANDLE)
    {
      std::cout << "handle_input" << std::endl;
      m_svcHandler = new TcpHandler<DataType>(m_buffer, m_prop);
      if (m_peerAcceptor.accept(*m_svcHandler, &m_remoteAddr) == -1)
	{
	  // accept failed
	  return -1;
	}
      
      // start service handler
      if (m_svcHandler->open(m_reactor) == -1)
	{
	  // connection closed
	  return -1;
	}
      return 0;
    }
    
  protected:
    /*!
     * @if jp
     * @brief �Хåե�
     * @else
     * @brief Buffer
     * @endif
     */
    BufferBase<DataType>& m_buffer;
    
    /*!
     * @if jp
     * @brief �ץ�ѥƥ�
     * @else
     * @brief Properties
     * @endif
     */
    Properties& m_prop;
    
    /*!
     * @if jp
     * @brief �ƻ��оݥ��ɥ쥹
     * @else
     * @brief Address for the monitor
     * @endif
     */
    ACE_INET_Addr m_addr;
    
    /*!
     * @if jp
     * @brief ��⡼�ȥ��ɥ쥹
     * @else
     * @brief Remote address
     * @endif
     */
    ACE_INET_Addr m_remoteAddr;
    
    /*!
     * @if jp
     * @brief �������ץ�
     * @else
     * @brief Acceptor
     * @endif
     */
    ACE_SOCK_Acceptor m_peerAcceptor;     
    
    /*!
     * @if jp
     * @brief �ꥢ����
     * @else
     * @brief Reactor
     * @endif
     */
    ACE_Reactor* m_reactor;
    
    /*!
     * @if jp
     * @brief ���٥�ȥϥ�ɥ�
     * @else
     * @brief Event handler
     * @endif
     */
    TcpHandler<DataType>* m_svcHandler;
    
    /*!
     * @if jp
     * @brief �ݡ����ֹ�
     * @else
     * @brief Port's number
     * @endif
     */
    unsigned short m_port;
  };
  
  //============================================================
  // TCP Server class
  //============================================================
  /*!
   * @if jp
   * @class TcpServer
   * @brief TcpServer ���饹
   *
   * TCP �������ѥ��饹��
   *
   * @param DataType �����Фǰ����ǡ�����
   *
   * @else
   * @class TcpServer
   * @brief TcpServer class
   *
   * TCP Server class.
   *
   * @param DataType Data type used by the server
   *
   * @endif
   */
  template <class DataType>
  class TcpServer
    : public coil::Task
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param buffer �Хåե�
     * @param prop �ץ�ѥƥ�����
     *
     * @else
     * @brief Constructor
     * 
     * Constructor
     *
     * @param buffer Buffer
     * @param prop Property information
     *
     * @endif
     */
    TcpServer(BufferBase<DataType>& buffer, Properties& prop)
      : m_acceptor(buffer, prop), m_buffer(buffer), m_prop(prop),
	m_running(true)
    {
      if (m_prop["inport_addr"] != "")
	{
	  m_addr.set(m_prop["inport_addr"].c_str());
	}
      std::cout << "hostname: " << m_addr.get_host_name() << std::endl;
    }
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * @else
     *
     * @brief Virtual destructor
     *
     * @endif
     */
    virtual ~TcpServer(void)
    {
    }
    
    /***
	void setAddr(const char* addr)
	{
	m_addr.set(addr);
	}
    */
    
    /*!
     * @if jp
     *
     * @brief TCP �ꥢ���ƥ��֥����Фγ���
     *
     * ���ꤷ�����ɥ쥹�˥ꥢ�����������ꤷ���ꥢ���ƥ��֥����С��򳫻Ϥ��롣
     *
     * @return ���Ͻ������
     *
     * @else
     *
     * @brief Start TCP reactive server
     *
     * Set the reactor to the specified address and start the reactive server.
     *
     * @return Start processing result
     *
     * @endif
     */
    int start(void)
    {
      // open socket and acceptor
      if (m_acceptor.open(m_addr, &m_reactor) == -1)
	{
	  // opening acceptor fail
	  return -1;
	}
      
      // get real port number
      m_port = m_acceptor.get_port_number();
      
      return 0;
    }
    
    /*!
     * @if jp
     *
     * @brief TCP �����Фγ���
     *
     * TCP �����Ф�ư����ȤȤ�ˡ��������ѥ���åɤ򳫻Ϥ��롣
     *
     * @param args ��ư�Ѱ���
     *
     * @return ���Ͻ������
     *
     * @else
     *
     * @brief Start TCP server
     *
     * Launch the TCP server and start the thread for server.
     *
     * @param args The argument for the launch
     *
     * @return Start processing result
     *
     * @endif
     */
    virtual int open(void *args)
    {
      start();
      activate();
      return 0;
    }
    
    /*!
     * @if jp
     *
     * @brief TCP �����Фμ¹�
     *
     * �ꥢ������ TCP �����Ф�¹Ԥ��Ƥ��륹��åɤ����ꤷ��
     * �ͥåȥ���̿����٥�Ȥ�ȯ������Τ��Ԥ������롣
     *
     * @return ���٥�Ƚ������
     *
     * @else
     *
     * @brief Run TCP server
     *
     * Set the thread that is running the TCP server to the reactor,
     * and wait to be occured the network communication event. 
     *
     * @return Event handling result
     *
     * @endif
     */
    virtual int svc(void)
    {
      m_reactor.owner(ACE_OS::thr_self()); 
      while (m_running)
	{
	  std::cout << "handle_event" << std::endl;
	  m_reactor.handle_events();
	}
      std::cout << "handle_event done" << std::endl;
      return 0;
    }
    
    /*!
     * @if jp
     *
     * @brief TCP �����Фμ¹�
     *
     * �ͥåȥ���̿����٥�Ȥ�ȯ������Τ��Ԥ������롣
     *
     * @return ���٥�Ƚ������
     *
     * @else
     *
     * @brief Run TCP server
     *
     * Wait for the network communication event occurring.
     *
     * @return Event handling result
     *
     * @endif
     */
    void run(void)
    {
      while (m_running)
	{
	  std::cout << "handle_event run" << std::endl;
	  m_reactor.handle_events();
	}
      std::cout << "handle_event run done" << std::endl;
    }	  
    
    /*!
     * @if jp
     *
     * @brief �ݡ����ֹ�μ���
     * 
     * �����ץ�������ꤷ���ݡ����ֹ��������롣
     *
     * @return �ݡ����ֹ�
     *
     * @else
     *
     * @brief Get the port number
     *
     * Get the port number set at the time of opening.
     *
     * @return Port's number
     *
     * @endif
     */
    unsigned short getPortNumber(void)
    {
      return m_port;
    }
    
    /*!
     * @if jp
     *
     * @brief �ۥ���̾�μ���
     * 
     * �����ץ�������ꤷ���ۥ���̾��������롣
     *
     * @return �ۥ���̾
     *
     * @else
     *
     * @brief Get the host name
     *
     * Get the host name set at the time of opening.
     *
     * @return The host name
     *
     * @endif
     */
    const char* getHostName(void)
    {
      return m_addr.get_host_name();
    }
    
  private:
    TcpAcceptor<DataType> m_acceptor;
    
    BufferBase<DataType>& m_buffer;
    Properties& m_prop;
    
    bool m_running;
    
    unsigned short m_port;
    ACE_INET_Addr m_addr;
    
    ACE_Reactor m_reactor;
  };
  
  //============================================================
  // TCP handler class
  //============================================================
  /*!
   * @if jp
   * @class TcpHandler
   * @brief TcpHandler ���饹
   *
   * TCP �̿��ѥ��٥�ȥϥ�ɥ饯�饹��
   *
   * @param DataType �Хåե��Υǡ�����
   *
   * @else
   * @class TcpHandler
   * @brief TcpHandler class
   *
   * Event handler class for TCP communication.
   *
   * @param DataType Data type of the buffer
   *
   * @endif
   */
  template <class DataType>
  class TcpHandler
    : public ACE_Event_Handler
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * 
     * ���󥹥ȥ饯��
     *
     * @param buffer �Хåե�
     * @param prop �ץ�ѥƥ�����
     *
     * @else
     * @brief Constructor
     * 
     * Constructor
     *
     * @param buffer Buffer
     * @param prop Property information
     *
     * @endif
     */
    TcpHandler(BufferBase<DataType>& buffer, Properties& prop)
      : m_buffer(buffer), m_prop(prop), m_pRecvBuffer(0),
	m_recvBufSize(1024), m_byteswap(true)
    {
      m_recvBufSize = atoi(m_prop.getProperty("buffer_size", "1024").c_str());
      std::cout << "m_recvBufSize: " << m_recvBufSize << std::endl;
      m_byteswap    = toBool(m_prop["byteswap"], "YES", "NO", true);
      std::cout << "m_byteswap: " << m_prop["byteswap"] << std::endl;
      m_pRecvBuffer = new char[m_recvBufSize];
    }
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * @else
     *
     * @brief Virtual destructor
     *
     * @endif
     */
    virtual ~TcpHandler(void)
    {
      if (!m_pRecvBuffer)
	delete[] m_pRecvBuffer;
    }
    
    /*!
     * @if jp
     *
     * @brief ���٥�ȴƻ�γ���
     *
     * ���٥�ȥϥ�ɥ��ꥢ��������Ͽ�����ꥢ�������Ф��륤�٥�Ȥδƻ��
     * ���Ϥ��롣
     * 
     * @param reactor �оݥꥢ����
     *
     * @return ���Ͻ������
     *
     * @else
     *
     * @brief Start monitoring event
     *
     * Register the event handler to the reactor and start monitoring the 
     * event for the reactor.
     * 
     * @param reactor The target reactor
     *
     * @return Start processing result
     *
     * @endif
     */
    int open(ACE_Reactor* reactor)
    {
      //      std::cout << "Tcphandler::open()" << std::endl;
      m_reactor = reactor;
      
      if (m_reactor->register_handler(this, ACE_Event_Handler::READ_MASK) == -1)
	{
	  // can't register with reactor 
	  return -1;
	}
      return 0;
    }
    
    /*!
     * @if jp
     *
     * @brief ���٥�ȴƻ�ν�λ
     *
     * ���٥�ȥϥ�ɥ��λ���롣
     *
     * @return ��λ�������
     *
     * @else
     *
     * @brief Close the event monitoring
     *
     * Close the event handler.
     *
     * @return Close processing result
     *
     * @endif
     */
    int close (void)
    {
      return this->handle_close(ACE_INVALID_HANDLE,
				ACE_Event_Handler::RWE_MASK);
    }
    
    /*!
     * @if jp
     *
     * @brief �����åȥ��ȥ꡼��μ���
     *
     * ���ꤵ�줿�����åȥ��ȥ꡼���������롣
     *
     * @return �����åȥ��ȥ꡼��
     *
     * @else
     *
     * @brief Get the socket stream
     *
     * Get the specified socket stream.
     *
     * @return The socket stream
     *
     * @endif
     */
    operator ACE_SOCK_Stream &(void)
    {
      return this->m_clientStream;
    }
    
  protected:
    /*!
     * @if jp
     *
     * @brief �����åȥ��ȥ꡼���ѥϥ�ɥ�μ���
     *
     * ���ꤵ�줿�����åȥ��ȥ꡼��Υϥ�ɥ��������롣
     *
     * @return �����åȥ��ȥ꡼���ѥϥ�ɥ�
     *
     * @else
     *
     * @brief Get the socket stream handle
     *
     * Get the socket stream handle that was set.
     *
     * @return The socket stream handle
     *
     * @endif
     */
    ACE_HANDLE get_handle (void) const
    {
      return this->m_clientStream.get_handle();
    }
    
    /*!
     * @if jp
     *
     * @brief �ǡ������������
     *
     * ���ꤵ�줿�����åȥ��ȥ꡼��ϥ�ɥ뤫��ǡ�����������롣
     * �����Хåե������礭�ʥ������Υǡ���������������ˤϡ������Хåե���
     * ��������ưŪ�˳�ĥ���롣
     * 
     * @param �ǡ��������оݥϥ�ɥ�
     * 
     * @return �ǡ��������������
     *
     * @else
     *
     * @brief Receive data
     *
     * Receive data from the set socket stream handle. 
     * When receiving data which is bigger size than the receive buffer, 
     * the buffer size is automatically enhanced.
     * 
     * @param The target handle for data receive
     * 
     * @return Data receive result
     *
     * @endif
     */
    int handle_input(ACE_HANDLE)
    {
      // data format
      // [length][client data]
      // length = sizeof ULong + client data length
      
      // get CDR data size
      long int len(0);
      char tmpbuf[sizeof(CORBA::ULong)];
      CORBA::ULong datasize; // actual data size except header
      len = this->m_clientStream.recv(tmpbuf, sizeof(CORBA::ULong));
      
      if (len > 0)
	{
	  cdrMemoryStream cdrSize(tmpbuf);
	  cdrSize.setByteSwapFlag(m_byteswap);
	  datasize <<= cdrSize;
	  datasize -= sizeof(CORBA::ULong);
	  if ((long int)datasize > m_recvBufSize)
	    {
	      std::cout << "recv buffer reallocated" << std::endl;
	      delete[] m_pRecvBuffer;
	      m_recvBufSize = datasize;
	      m_pRecvBuffer = new char[m_recvBufSize];
	      std::cout << "new buffer size " << m_recvBufSize << std::endl;
	    }
	  
	  int recvd(0);
	  do 
	    {
	      recvd += this->m_clientStream.recv(m_pRecvBuffer + recvd,
						 datasize);
	    }
	  while (recvd < (int)datasize);
	  
	  if (recvd == (int)datasize)
	    {
	      cdrMemoryStream cdr(m_pRecvBuffer);
	      cdr.setByteSwapFlag(m_byteswap);
	      m_data <<= cdr;
	      m_buffer.write(m_data);
	    }
	  else
	    {
	      std::cout << "invalid data length" << std::endl;
	      std::cout << "recvs: " << recvd << std::endl;
	      std::cout << "cdrlen: " << datasize << std::endl;
	      return -1;
	    }
	}
      else return -1;
      
      return 0;
    }
    
    /*!
     * @if jp
     *
     * @brief �����åȥ��ȥ꡼��򥯥�������
     *
     * ���ꤷ�������åȥ��ȥ꡼��ϥ�ɥ�򥯥�������ȤȤ�ˡ�
     * �����åȥ��ȥ꡼�༫�Υ��������롣
     * 
     * @param �������оݥϥ�ɥ�
     * @param mask �������оݥ��٥��
     * 
     * @return �������������
     *
     * @else
     *
     * @brief Close the socket stream
     *
     * Close the specified socket stream handle, and also close
     * the socket stream itself. 
     * 
     * @param The target handle for the close
     * @param mask The target event for the close
     * 
     * @return Close processing result
     *
     * @endif
     */
    int handle_close(ACE_HANDLE, ACE_Reactor_Mask mask)
    {
      m_reactor->remove_handler(this, mask|ACE_Event_Handler::DONT_CALL);
      m_clientStream.close();
      delete this;          
      return 0;
    }
    
  protected:
    /*!
     * @if jp
     * @brief ���� TCP �����Ф˳�����Ƥ�줿�Хåե�
     * @else
     * @brief Buffer assigned to this TCP server
     * @endif
     */
    BufferBase<DataType>& m_buffer;
    
    /*!
     * @if jp
     * @brief �����ѥץ�ѥƥ�
     * @else
     * @brief Properties for setting
     * @endif
     */
    Properties& m_prop;
    
    /*!
     * @if jp
     * @brief �ǡ��������ѥХåե�
     * @else
     * @brief Buffer for data reception
     * @endif
     */
    char* m_pRecvBuffer;
    
    /*!
     * @if jp
     * @brief �����ǡ���������
     * @else
     * @brief Receive data size
     * @endif
     */
    long int m_recvBufSize;
    /*!
     * @if jp
     * @brief �Х��ȥ���åץե饰
     * @else
     * @brief Byte swap flag
     * @endif
     */
    bool m_byteswap;
    
    /*!
     * @if jp
     * @brief �����åȥ��ȥ꡼��ϥ�ɥ�
     * @else
     * @brief Socket stream handle
     * @endif
     */
    ACE_SOCK_Stream m_clientStream; 
    /*!
     * @if jp
     * @brief �ꥢ����
     * @else
     * @brief Reactor
     * @endif
     */
    ACE_Reactor* m_reactor;
    /*!
     * @if jp
     * @brief �񤭹����оݥǡ���
     * @else
     * @brief The target data for writing
     * @endif
     */
    DataType m_data;
  };
}; // namespace RTC
#endif // RTC_TCPSOCKSERVER_H
