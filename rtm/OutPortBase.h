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
 * $Id: OutPortBase.h,v 1.1.4.1 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/12/02 18:46:13  n-ando
 * The first commitment.
 *
 * Revision 1.3  2005/05/27 07:34:21  n-ando
 * - InPort/OutPort interface was changed.
 *   subscribe/unsubscribe were completely changed.
 *
 * Revision 1.2  2005/05/16 06:37:11  n-ando
 * - OutPortBase class was DLL exported for Windows port.
 * - m_Profile.name should be initialized with empty string.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
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
   * @brief Output port base class.
   *
   * The base class of OutPort<T> s which are implementations of OutPort  
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
     *
     * @brief A constructor of OutPortBase class.
     *
     * Constructor of OutPortBase.
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
     * @brief destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~OutPortBase();
    
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
     * @brief OutPort's name
     *
     * This operation returns OutPort's name
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
     * @brief Attach a publisher
     *
     * Attach a publisher to observe OutPort.
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
     * @brief Attach a publisher
     *
     * Attach a publisher to the head of the Publisher list.
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
     * @brief Attach a publisher
     *
     * Attach a publisher to the taile of the Publisher list.
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
     * @brief Detach a publisher
     *
     * Detach a publisher to observe OutPort.
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
     * @brief Notify data update
     *
     * This operation notify data update to Publishers
     *
     * @endif
     */
    void notify();
    
  protected:
    /*!
     * @if jp
     * @brief �ݡ���̾
     * @else
     *
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief Publisher �ѹ�¤��
     * @else
     *
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
     *
     * @endif
     */
    std::vector<Publisher*> m_publishers;
    
    /*!
     * @if jp
     * @brief Publisher �� ID �ˤ�äƸ������뤿��� Functor
     * @else
     *
     * @endif
     */
    // Functor to find Publisher by id
    struct find_id;
    
    /*!
     * @if jp
     * @brief Publisher �˥ǡ������������Τ��뤿��� Functor
     * @else
     *
     * @endif
     */
    // Functor to notify update to Publishers
    struct pub_push;
    
    /*!
     * @if jp
     * @brief Publisher �������뤿��� Functor
     * @else
     *
     * @endif
     */
    // Functor to delete Publishers
    struct pub_del;
  };
}; // End of namespace RTM
#endif // RtcOutPortBase_h
