/*! -*- C++ -*-
 *
 * @file OutPortBase.cpp
 * @brief Output porty base class
 * @date $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
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

#include <algorithm>
#include <rtm/OutPortBase.h>
#include <rtm/PublisherBase.h>
#include <iostream>

namespace RTC
{
  
  /*!
   * @if jp
   * @brief Publisher �� ID �ˤ�äƸ������뤿��� Functor
   * @else
   * @brief Functor to find Publisher by ID
   * @endif
   */
  // Functor to find Publisher by id
  struct OutPortBase::find_id
  {
    find_id(const char* id) : m_id(id) {};
    bool operator()(Publisher* pub)
    {
      return m_id == pub->id;
    }
    std::string m_id;
  };
  
  /*!
   * @if jp
   * @brief Publisher �˥ǡ������������Τ��뤿��� Functor
   * @else
   * @brief Functor to notify the data update to Publishers
   * @endif
   */
  // Functor to notify update to Publishers
  struct OutPortBase::pub_push
  {
    void operator()(Publisher* pub)
    {
      pub->publisher->update();
    }
  };
  
  /*!
   * @if jp
   * @brief Publisher �������뤿��� Functor
   * @else
   * @brief Functor to delete Publishers
   * @endif
   */
  // Functor to delete Publishers
  struct OutPortBase::pub_del
  {
    void operator()(Publisher* pub)
    {
      delete pub;
    }
  }; 
  
  /*!
   * @if jp
   * @brief �ǥ��ȥ饯��
   * @else
   * @brief Destructor
   * @endif
   */
  OutPortBase::~OutPortBase()
  {
    std::for_each(m_publishers.begin(), m_publishers.end(), pub_del());
  }
  
  /*!
   * @if jp
   * @brief Publisher���ɲ�
   * @else
   * @brief Attach the publisher
   * @endif
   */
  void OutPortBase::attach(const char* id, PublisherBase* publisher)
  {
    attach_back(id, publisher);
  }
  
  /*!
   * @if jp
   * @brief �ꥹ����Ƭ�ؤ�Publisher���ɲ�
   * @else
   * @brief Attach the publisher to the top of the Publisher list.
   * @endif
   */
  void OutPortBase::attach_front(const char* id, PublisherBase* publisher)
  {
    m_publishers.insert(m_publishers.begin(), new Publisher(id, publisher));
  }
  
  /*!
   * @if jp
   * @brief �ꥹ�ȺǸ����ؤ�Publisher���ɲ�
   * @else
   * @brief Attach the publisher at the end of the Publisher list.
   * @endif
   */
  void OutPortBase::attach_back(const char* id, PublisherBase* publisher)
  {
    m_publishers.push_back(new Publisher(id, publisher));
  }
  
  /*!
   * @if jp
   * @brief Publisher�κ��
   * @else
   * @brief Detach the publisher
   * @endif
   */
  PublisherBase* OutPortBase::detach(const char* id)
  {
    std::vector<Publisher*>::iterator it;
    it = std::find_if(m_publishers.begin(), m_publishers.end(), find_id(id));
    if (it == m_publishers.end())
      return NULL;
    PublisherBase* pub((*it)->publisher);
    delete (*it);
    m_publishers.erase(it);
    return pub;
  }
  
  /*!
   * @if jp
   * @brief ����������
   * @else
   * @brief Notify the data update
   * @endif
   */
  void OutPortBase::notify()
  {
    std::for_each(m_publishers.begin(), m_publishers.end(), pub_push());
  }
}; // end of namespace RTM
