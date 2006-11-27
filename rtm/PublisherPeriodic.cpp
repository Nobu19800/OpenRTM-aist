// -*- C++ -*-
/*!
 * @file  PublisherPeriodic.cpp
 * @brief PublisherPeriodic class
 * @date  $Date: 2006-11-27 09:44:50 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PublisherPeriodic.cpp,v 1.1 2006-11-27 09:44:50 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <rtm/PublisherPeriodic.h>
#include <rtm/InPortConsumer.h>
#include <rtm/Properties.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  PublisherPeriodic::PublisherPeriodic(InPortConsumer& consumer,
				       Properties property)
    : m_consumer(consumer), m_running(true)
  {
    std::string rate(property.getProperty("dataport.push_interval"));
    unsigned long hz;

    if (rate != "")
      {
	hz = atoi(rate.c_str());
      }
    else
      {
	hz = 1;
      }
    m_usec = 1000000/hz;
  }

  /*!
   * @if jp
   * @brief Observer�ؿ�
   * @else
   * @brief Observer function
   * @endif
   */
  void PublisherPeriodic::update()
  {
  }
  

  /*!
   * @if jp
   * @brief ����åɼ¹Դؿ�
   * @else
   * @brief Thread execution function
   * @endif
   */
  int PublisherPeriodic::svc(void)
  {
    
#ifdef ARTLinux
    art_enter( ART_PRIO_MAX, ART_TASK_PERIODIC, m_usec );
#endif // ARTLinux
    while (m_running)
      {
	m_consumer.push();
#ifdef ARTLinux
	art_wait();
#else
	usleep(m_usec);
#endif //ARTLinux
      }
    return 0;
  }


  /*!
   * @if jp
   * @brief ����������
   * @else
   * @brief Task start function
   * @endif
   */
  int PublisherPeriodic::open(void *args)
  {
        m_running = true;
        this->activate();
        return 0;
  }

  
  /*!
   * @if jp
   * @brief ��������λ�ؿ�
   * @else
   * @brief Task terminate function
   * @endif
   */
  void PublisherPeriodic::release()
  {
    m_running = false;
  }

}; // namespace RTC
