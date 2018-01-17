// -*- C++ -*-
/*!
 * @file ProcessUniquePolicy.h
 * @brief Object numbering policy class
 * @date $Date: 2007-12-31 03:08:04 $
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
 * $Id$
 *
 */

#ifndef RTC_NUMBERINGPOLICY_H
#define RTC_NUMBERINGPOLICY_H

#include <string>
#include <vector>
#include <rtm/RTC.h>
#include <rtm/NumberingPolicyBase.h>

namespace RTM
{
  /*!
   * @if jp
   *
   * @class ProcessUniquePolicy
   * @brief ���֥��������������͡��ߥ󥰡��ݥꥷ��(̿̾��§)�����ѥ��饹
   *
   * ���֥������Ȥ���������ݤΥ͡��ߥ󥰡��ݥꥷ��(̿̾��§)��������뤿���
   * ���饹��
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class ProcessUniquePolicy
   * @brief Class for naming policy management when creating objects
   *
   * This is a class to manage the naming policy when creating objects.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ProcessUniquePolicy
    : public NumberingPolicyBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    ProcessUniquePolicy() : m_num(0) {};
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     * 
     * @else
     *
     * @brief Destractor
     *
     * @endif
     */
    virtual ~ProcessUniquePolicy(void){};
    
    /*!
     * @if jp
     *
     * @brief ���֥���������������̾�κ���
     *
     * ���֥���������������̾�Τ��������롣
     * �����Ѥߥ��󥹥��󥹤ο��˱�����̾�Τ��������롣
     * 
     * @param obj ̾�������оݥ��֥�������
     *
     * @return �����������֥�������̾��
     *
     * @else
     *
     * @brief Create the name when creating object
     *
     * Create the name when creating object.
     * Create the name corresponding to the number of generated instances.
     * 
     * @param obj The target object for the name creation
     *
     * @return Names of the created object
     *
     * @endif
     */
    virtual std::string onCreate(void* obj);
    
    /*!
     * @if jp
     *
     * @brief ���֥������Ⱥ������̾�β���
     *
     * ���֥������Ⱥ������̾�Τ�������롣
     * ���֥������Ⱥ�����������Ѥߥ��󥹥��󥹿��򸺻����롣
     * 
     * @param obj ̾�β����оݥ��֥�������
     *
     * @else
     *
     * @brief Delete the name when deleting object
     *
     * Delete the name when deleting object.
     * Substract the generated number of instances when deleting the object.
     * 
     * @param obj The target object for the name delete
     *
     * @endif
     */
    virtual void onDelete(void* obj);
    
  protected:
    /*!
     * @if jp
     *
     * @brief ���֥������Ȥθ���
     *
     * ���֥������ȥꥹ�Ȥ�����ꤵ�줿���֥������Ȥ򸡺�����
     * �������륪�֥������Ȥ���Ǽ����Ƥ�����ˤϥ���ǥå������֤���
     * 
     * @param obj �����оݥ��֥�������
     *
     * @return ���֥������ȳ�Ǽ����ǥå���
     *
     * @else
     *
     * @brief Find the object
     *
     * Find the specified object in the object list and return its index
     * when it is stored.
     * 
     * @param obj The target object for the find
     *
     * @return Object index for storage
     *
     * @endif
     */
    long int find(void* obj);
    
  private:
    int m_num;
    std::vector<void*> m_objects;
  };
}; // namespace RTM

extern "C"
{
  void DLL_EXPORT ProcessUniquePolicyInit();
};

#endif // RTC_NUMBERINGPOLICY_H
