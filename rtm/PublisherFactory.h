// -*- C++ -*-
/*!
 * @file  PublisherFactory.h
 * @brief PublisherFactory class
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
 * $Id: PublisherFactory.h,v 1.2.4.2 2007-12-31 03:08:06 n-ando Exp $
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
   * �Ƽ�Publisher���֥������Ȥ��������˴����������ե����ȥꥯ�饹
   * ���ƥ�ݥ��ʼ���
   *   ����Ū�ˤ�Ǥ�դ�Publisher�������Ǥ���褦�ˤ��롣
   *
   * @else
   * @class PublisherFactory
   * @brief PublisherFactory class
   *
   * This is a factory class to manage for creation and destruction of
   * various Publisher objects.
   * Note: This is temporary implementation.
   *  We try to be able to generate any Publisher in the future.
   *
   * @endif
   */
  class PublisherFactory
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * �ǥե���ȥ��󥹥ȥ饯��
     *
     * @else
     * @brief Constructor
     *
     * Default constructor
     *
     * @endif
     */
    PublisherFactory(){};
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯��
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~PublisherFactory(){};
    
    /*!
     * @if jp
     * @brief Publisher������
     *
     * Publisher���֥������Ȥ��������롣
     * ���ꤵ�줿�����˱�����Ŭ�ڤ�Publisher�����Υ��֥������Ȥ���������롣
     * ��������Publisher�μ��̤򡢻��ꤵ�줿Property���֥������Ȥ�
     * dataport.subscription_type���Ф����ꤷ�Ƥ���ɬ�פ����롣
     * �ޤ������̤ˤ�äƤϡ�Publisher�ζ�ư�����椹�����򤵤�����ꤹ��ɬ�פ�
     * ���롣
     * �����ζ���Ū�����Ƥϡ����줾���Publisher�����򻲾ȤΤ��ȡ�
     *
     * @param consumer Publisher�ˤ�äƥǡ������Ф��ư����륳�󥷥塼��
     * @param property �������٤�Publisher�����ꤹ�뤿��ξ���䡢Publisher��
     *                 ��ư�����椹�뤿��ξ������ꤵ��Ƥ���Property���֥���
     *                 ����
     *
     * @return ��������Publisher���֥������ȡ������˼��Ԥ�������Null���֤���
     *
     * @else
     * @brief Create the Publisher
     *
     * Create the Publisher's object.
     * The appropriate Publisher implementation object according to the
     * specified argument is generated.
     * The type of generated Publisher needs to be set to the 
     * dataport.subscription_type member of the specified Property object.
     * Also, depending on the type, information that controls the behavior of
     * Publisher needs to be set.
     * For more details on these contents, please refer to each Publisher 
     * implementation.
     *
     * @param consumer Consumer that is driven the data sending by Publisher
     * @param property Property object to be set information for specifying to
     *                 the generated Publisher and for controlling the drive of
     *                 Publisher.
     *
     * @return The generated Publisher's object. Null will be returned if failed
     *         to be generated.
     *
     * @endif
     */
    PublisherBase* create(InPortConsumer* consumer, Properties& property);
    
    /*!
     * @if jp
     * @brief Publisher���˴�
     *
     * ���ꤵ�줿Publisher���֥������Ȥ��˴����롣
     *
     * @param publisher �˴��о�Publisher���֥�������
     *
     * @else
     * @brief Destroy the Publisher
     *
     * Destroy the specified Publisher's object
     *
     * @param publisher The target Publisher's object for the delete
     *
     * @endif
     */
    void destroy(PublisherBase *publisher);
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // PublisherFactory_h

