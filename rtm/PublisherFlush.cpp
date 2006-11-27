// -*- C++ -*-
/*!
 * @file  PublisherFlush.cpp
 * @brief PublisherFlush class
 * @date  $Date: 2006-11-27 09:44:46 $
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
 * $Id: PublisherFlush.cpp,v 1.1 2006-11-27 09:44:46 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <rtm/PublisherFlush.h>
#include <rtm/Properties.h>
#include <rtm/InPortConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  PublisherFlush::PublisherFlush(InPortConsumer& consumer,
				 Properties property)
    : m_consumer(consumer)
  {
  }


  /*!
   * @if jp
   * @brief Observer�ؿ�
   * @else
   * @brief Observer function
   * @endif
   */
  void PublisherFlush::update()
  {
    m_consumer.push();
    return;
  }
  
}; // namespace RTC
