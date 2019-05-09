// -*- C++ -*-
/*!
 * @file NumberingPolicyBase.h
 * @brief Object numbering policy base class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Noriaki Ando
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_NUMBERINGPOLICYBASE_H
#define RTC_NUMBERINGPOLICYBASE_H

#include <string>
#include <vector>
#include <coil/Factory.h>

namespace RTM
{
  /*!
   * @if jp
   *
   * @class NumberingPolicyBase
   * @brief ���֥��������������͡��ߥ󥰡��ݥꥷ��(̿̾��§)��������ݥ��饹
   *
   * ���֥������Ȥ���������ݤΥ͡��ߥ󥰡��ݥꥷ��(̿̾��§)��������뤿���
   * ��ݥ��󥿡��ե��������饹��
   * ��ݥ��饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
   * - onCreate() : ���֥���������������̾�κ���
   * - onDelete() : ���֥������Ⱥ������̾�β���
   *
   * @since 1.2
   *
   * @else
   * @class NumberingPolicy
   * @brief Abstruct class for naming policy management when creating objects
   *
   * This is the abstract interface class to manage the naming policy when
   * creating objects.
   * Concrete classes must implement the following pure virtual functions.
   * - onCreate() : Create the name when creating objects.
   * - onDelete() : Delete the name when deleting objects.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class NumberingPolicyBase
  {
  public:
    /*!
     * @if jp
     * @brief ���֥�������̤ȯ���㳰�����ѹ�¤��
     * @else
     * @brief The structures for exception handling when object was not
     *        found.
     * @endif
     */
    struct ObjectNotFound {};
    
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * @else
     *
     * @brief Virtual destractor
     *
     * @endif
     */
    virtual ~NumberingPolicyBase(void) {};
    
    /*!
     * @if jp
     *
     * @brief ���֥���������������̾�κ���
     *
     * ���֥���������������̾�Τ��������뤿��ν�貾�۴ؿ�
     * 
     * @param obj ̾�������оݥ��֥�������
     *
     * @return �����������֥�������̾��
     *
     * @else
     *
     * @brief Create the name when creating objects
     *
     * Pure virtual function to create the name when creating objects.
     * 
     * @param obj The target object for the creation
     *
     * @return Name of the created object
     *
     * @endif
     */
    virtual std::string onCreate(void* obj) = 0;
    
    /*!
     * @if jp
     *
     * @brief ���֥������Ⱥ������̾�β���
     *
     * ���֥������Ⱥ������̾�Τ�������뤿��ν�貾�۴ؿ�
     * 
     * @param obj ̾�β����оݥ��֥�������
     *
     * @else
     *
     * @brief Delete the name when deleting objects
     *
     * Pure virtual function to delete the name when deleting object.
     * 
     * @param obj The target object of the delete
     *
     * @endif
     */
    virtual void onDelete(void* obj) = 0;
  };
  
  typedef coil::GlobalFactory<NumberingPolicyBase> NumberingPolicyFactory;
  
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  EXTERN template class DLL_PLUGIN coil::GlobalFactory<NumberingPolicyBase>;
#endif
  
};

#ifdef __GNUC__
extern template class coil::Singleton<coil::GlobalFactory<RTM::NumberingPolicyBase> >;
#endif

#endif // RTC_NUMBERINGPOLICYBASE_H
