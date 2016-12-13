// -*- C++ -*-
/*!
 * @file  PublisherFactory.h
 * @brief PublisherFactory class
 * @date  $Date: 2007-06-22 10:55:11 $
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
 * $Id: PublisherFactory.h,v 1.2.4.1 2007-06-22 10:55:11 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/06 18:00:31  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:45  n-ando
 * The first commitment.
 *
 */

#ifndef PublisherFactory_h
#define PublisherFactory_h

#include <rtm/Properties.h>
 
namespace RTC
{
  class PublisherBase;
  class InPortConsumer;
  class Properties;
  /*!
   * @if jp
   * @class PublisherFactory
   * @brief PublisherFactory ���饹
   *
   * ���ƥ�ݥ��ʼ���
   *   ����Ū�ˤ�Ǥ�դ�Publisher�������Ǥ���褦�ˤ��롣
   *
   * @else
   * @class PublisherFactory
   * @brief PublisherFactory class
   * @endif
   */
  class PublisherFactory
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     * @else
     * @brief Constructor
     * @endif
     */
    PublisherFactory(){};

    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PublisherFactory(){};

    /*!
     * @if jp
     * @brief Publisher������
     * @else
     * @brief Create Publisher
     * @endif
     */
    PublisherBase* create(InPortConsumer* consumer, Properties& property);

    void destroy(PublisherBase *publisher);
  protected:
  
  private:

  };
 
};     // namespace RTC
#endif // PublisherFactory_h

