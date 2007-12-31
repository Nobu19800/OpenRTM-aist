// -*- C++ -*-
/*!
 * @file  PublisherFlush.h
 * @brief PublisherFlush class
 * @date  $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PublisherFlush.h,v 1.2.4.1 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/06 18:00:44  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:47  n-ando
 * The first commitment.
 *
 */

#ifndef PublisherFlush_h
#define PublisherFlush_h

#include <rtm/PublisherBase.h>

namespace RTC
{
  class InPortConsumer;
  class Properties;
  /*!
   * @if jp
   * @class PublisherFlush
   * @brief PublisherFlush ���饹
   *
   * Flush �� Publisher ���饹
   * �Хåե���˳�Ǽ����Ƥ���̤�����ǡ������������롣
   * �ǡ������Ф��Ԥĥ��󥷥塼�ޤ����Ф���¦��Ʊ������åɤ�ư����롣
   *
   * @else
   * @class PublisherFlush
   * @brief PublisherFlush class
   * @endif
   */
  class PublisherFlush
    : public PublisherBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param consumer �ǡ������Ф��Ԥĥ��󥷥塼��
     * @param property ��Publisher�ζ�ư�����������ꤷ��Property���֥�������
     *
     * @else
     * @brief Constructor
     * @endif
     */
    PublisherFlush(InPortConsumer* consumer,
		   const Properties& property);
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     * ����Publisher���˴�����ݤˡ�PublisherFactory�ˤ��ƤӽФ���롣
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PublisherFlush();
    
    /*!
     * @if jp
     * @brief Observer�ؿ�
     *
     * ���Х����ߥ󥰻��˸ƤӽФ���
     * ¨�¤�Ʊ�쥹��åɤˤƥ��󥷥塼�ޤ����н������ƤӽФ���롣
     *
     * @else
     * @brief Observer function
     * @endif
     */
    virtual void update();
  protected:
    
  private:
    InPortConsumer* m_consumer;
    
  };
};     // namespace RTC
#endif // PublisherFlush_h
