// -*- C++ -*-
/*!
 * @file NumberingPolicy.h
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
 * $Id: NumberingPolicy.h,v 1.2.4.1 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/21 09:52:28  n-ando
 * A trivial bug fix about dtor.
 *
 * Revision 1.1  2006/11/04 21:07:40  n-ando
 * Component numbering rule was derived into policy class.
 *
 */

#ifndef NumberingPolicy_h
#define NumberingPolicy_h

#include <string>
#include <vector>

/*!
 * @if jp
 *
 * @brief ���֥��������������͡��ߥ󥰡��ݥꥷ��(̿̾��§)��������ݥ��饹
 *
 * ���֥������Ȥ���������ݤΥ͡��ߥ󥰡��ݥꥷ��(̿̾��§)��������뤿���
 * ��ݥ��󥿡��ե��������饹��
 * ��ݥ��饹�ϡ��ʲ��ν�貾�۴ؿ��μ������󶡤��ʤ���Фʤ�ʤ���
 * - onCreate() : ���֥���������������̾�κ���
 * - onDelete() : ���֥������Ⱥ������̾�β���
 *
 * @since 0.4.0
 *
 * @else
 *
 * @endif
 */
class NumberingPolicy
{
public:
  /*!
   * @if jp
   * @brief ���֥�������̤ȯ���㳰�����ѹ�¤��
   * @else
   *
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
   * @brief virtual destractor
   *
   * @endif
   */
  virtual ~NumberingPolicy(){};
  
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
   * @endif
   */
  virtual void onDelete(void* obj) = 0;
};

/*!
 * @if jp
 *
 * @brief ���֥��������������͡��ߥ󥰡��ݥꥷ��(̿̾��§)�����ѥ��饹
 *
 * ���֥������Ȥ���������ݤΥ͡��ߥ󥰡��ݥꥷ��(̿̾��§)��������뤿���
 * ���饹��
 *
 * @since 0.4.0
 *
 * @else
 *
 * @endif
 */
class DefaultNumberingPolicy
  : public NumberingPolicy 
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
   * @brief virtual destractor
   *
   * @endif
   */
  DefaultNumberingPolicy() : m_num(0) {};
  
  /*!
   * @if jp
   *
   * @brief �ǥ��ȥ饯��
   * 
   * @else
   *
   * @brief destractor
   *
   * @endif
   */
  virtual ~DefaultNumberingPolicy(){};
  
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
   * @endif
   */
  long int find(void* obj);
  
private:
  int m_num;
  std::vector<void*> m_objects;
};
#endif // NumberingPolicy_h
