// -*- C++ -*-
/*!
 * @file OutPortBase.h
 * @brief InPortBase base class
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

#ifndef RtcOutPortBase_h
#define RtcOutPortBase_h

#include <vector>
#include <string>

namespace RTC
{
  class PublisherBase;
  /*!
   * @if jp
   *
   * @class OutPortBase
   *
   * @brief OutPort ���쥯�饹
   * 
   * OutPort �μ����Ǥ��� OutPort<T> �δ��쥯�饹��
   *
   * OutPortBase �� PublisherBase �ϰ��� Observer �ѥ������������Ƥ��롣
   * OutPortBase �� attach(), detach(), notify() �����
   * PublisherBase �� push() �� Observer �ѥ�����˴�Ϣ�����᥽�åɤǤ��롣
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class OutPortBase
   *
   * @brief Output base class.
   *
   * The base class of OutPort<T> which are implementations of OutPort
   *
   * Form a kind of Observer pattern with OutPortBase and PublisherBase.
   * attach(), detach(), notify() of OutPortBase and
   * push() of PublisherBase are methods associated with the Observer pattern.
   *
   * @since 0.2.0
   *
   * @endif
   */
  class OutPortBase
  {
  public:
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯����
     *
     * @param name �ݡ���̾
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port name
     *
     * @endif
     */
    OutPortBase(const char* name)
      : m_name(name)
    {
    };
    
    /*!
     * @if jp
     * @brief �ǥ��ȥ饯��
     *
     * �ǥ��ȥ饯����
     * ��Ͽ���줿���Ƥ� Publisher �������롣
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     * Detach all subscribed Publishers.
     *
     * @endif
     */
    virtual ~OutPortBase(void);
    
    /*!
     * @if jp
     * @brief OutPort̾�Τμ���
     *
     * OutPort��̾�Τ�������롣
     *
     * @return �ݡ���̾��
     *
     * @else
     *
     * @brief Retrieve OutPort name
     *
     * Retrieve OutPort name
     *
     * @return the port name
     *
     * @endif
     */
    inline const char* name() {return m_name.c_str();}
    
    /*!
     * @if jp
     * @brief Publisher���ɲ�
     *
     * ���ꤷ��Publisher��ǡ�������������Ȥ��ƥꥹ�ȤκǸ������ɲä��롣
     * attach_back() ��Ʊ�ͤʵ�ǽ��
     *
     * @param id ���ꤵ�줿Publisher�˳�����Ƥ�ID
     * @param publisher ��Ͽ�о�Publisher���֥�������
     *
     * @else
     *
     * @brief Attach the publisher
     *
     * Attach the specified publisher as the destination of the data update
     * notification to the end of the Publisher list.
     * This function is similar to attach_back().
     *
     * @param id ID assigned to the Publisher that is specified
     * @param publisher The target Publisher object for attachment
     *
     * @endif
     */
    void attach(const char* id, PublisherBase* publisher);
    
    /*!
     * @if jp
     * @brief �ꥹ����Ƭ�ؤ�Publisher���ɲ�
     *
     * Publisher��ꥹ�Ȥ���Ƭ���ɲä��롣
     *
     * @param id ���ꤵ�줿Publisher�˳�����Ƥ�ID
     * @param publisher ��Ͽ�о�Publisher���֥�������
     *
     * @else
     *
     * @brief Attach the publisher to the top of the Publisher list.
     *
     * Attach the publisher to the top of the Publisher list.
     *
     * @param id ID assigned to the Publisher that is specified
     * @param publisher The target Publisher object for attachment
     *
     * @endif
     */
    void attach_front(const char* id, PublisherBase* publisher);
    
    /*!
     * @if jp
     * @brief �ꥹ�ȺǸ����ؤ�Publisher���ɲ�
     *
     * Publisher��ꥹ�ȤκǸ������ɲä��롣
     *
     * @param id ���ꤵ�줿Publisher�˳�����Ƥ�ID
     * @param publisher ��Ͽ�о�Publisher���֥�������
     *
     * @else
     *
     * @brief Attach the publisher at the end of the Publisher list.
     *
     * Attach the publisher to the end of the Publisher list.
     *
     * @param id ID assigned to the Publisher that is specified
     * @param publisher The target Publisher object for attachment
     *
     * @endif
     */
    void attach_back(const char* id, PublisherBase* publisher);
    
    /*!
     * @if jp
     * @brief Publisher�κ��
     *
     * ���ꤵ�줿 Publisher ��ǡ�������������ꥹ�Ȥ��������롣
     *
     * @param id ����о� Publisher ��ID
     *
     * @return ����������������ϡ�������� Publisher ���֥�������
     *         ���ꤷ�� Publisher ��¸�ߤ��ʤ����� null
     *
     * @else
     *
     * @brief Detach the publisher
     *
     * Detach the specified Publisher from the update notification list
     *
     * @param id ID of the deleted Publisher
     *
     * @return The deleted publisher object if the deletion completed
     *         successfully.
     *         Null if the specified Publisher does not exist.
     *
     * @endif
     */
    PublisherBase* detach(const char* id);
    
    /*!
     * @if jp
     * @brief ����������
     *
     * ��Ͽ����Ƥ������Ƥ� Publisher �˥ǡ������������Τ��롣
     *
     * @else
     *
     * @brief Notify the data updates
     *
     * Notify data updates to all registered Publishers
     *
     * @endif
     */
    void notify();

    virtual void onConnect(const char* id, PublisherBase* publisher){};
    virtual void onDisconnect(const char* id){};
    
  protected:
    /*!
     * @if jp
     * @brief �ݡ���̾
     * @else
     * @brief Port name
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief Publisher �ѹ�¤��
     * @else
     * @brief Structure of Publisher
     * @endif
     */
    struct Publisher
    {
      Publisher(const char* _id, PublisherBase* _publisher)
	: id(_id), publisher(_publisher){};
      std::string id;
      PublisherBase* publisher;
    };
    
    /*!
     * @if jp
     * @brief ��Ͽ���줿 Publisher �ꥹ��
     * @else
     * @brief Registered Publisher list
     * @endif
     */
    std::vector<Publisher*> m_publishers;
    
    /*!
     * @if jp
     * @brief Publisher �� ID �ˤ�äƸ������뤿��� Functor
     * @else
     * @brief Functor to find Publisher by id
     * @endif
     */
    // Functor to find Publisher by id
    struct find_id;
    
    /*!
     * @if jp
     * @brief Publisher �˥ǡ������������Τ��뤿��� Functor
     * @else
     * @brief Functor to notify updates to Publishers
     * @endif
     */
    // Functor to notify update to Publishers
    struct pub_push;
    
    /*!
     * @if jp
     * @brief Publisher �������뤿��� Functor
     * @else
     * @brief Functor to delete Publishers
     * @endif
     */
    // Functor to delete Publishers
    struct pub_del;
  };
}; // End of namespace RTM
#endif // RtcOutPortBase_h
