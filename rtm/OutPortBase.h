// -*- C++ -*-
/*!
 * @file RtcOutPortBase.h
 * @brief InPortBase base class
 * @date $Date: 2006-12-02 18:46:13 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPortBase.h,v 1.1 2006-12-02 18:46:13 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
     * @brief OutPortBase ���饹���󥹥ȥ饯��
     *
     * OutPortBase �Υ��饹���󥹥ȥ饯����
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
     * @brief OutPortBase ���饹�ǥ��ȥ饯��
     *
     * OutPortBase �Υ��饹�ǥ��ȥ饯����
     *
     * @else
     *
     * @brief A destructor of OutPortBase class.
     *
     * Destructor of OutPortBase.
     *
     * @endif
     */
    virtual ~OutPortBase();


    /*!
     * @if jp
     * @brief OutPort��̾��
     *
     * OutPort��̾�����֤���
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
     * Publisher���ɲä��롣
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
     * @brief Publisher���ɲ�
     *
     * Publisher��ꥹ�Ȥ���Ƭ���ɲä��롣
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
     * @brief Publisher���ɲ�
     *
     * Publisher��ꥹ�ȤκǸ������ɲä��롣
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
     * Publisher�������롣
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
     * Publisher�˥ǡ����ι��������Τ��롣
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
    std::string m_name;

    /*!
     * @brief Publisher struct
     */ 
    struct Publisher
    {
      Publisher(const char* _id, PublisherBase* _publisher)
	: id(_id), publisher(_publisher){};
      std::string id;
      PublisherBase* publisher;
    };

    /*!
     * @brief Publisher list
     */ 
    std::vector<Publisher*> m_publishers;


    // Functor to find Publisher by id
    struct find_id;

    // Functor to notify update to Publishers
    struct pub_push;

    // Functor to delete Publishers
    struct pub_del;

  };


  
}; // End of namespace RTM

#endif // RtcOutPortBase_h
