// -*- C++ -*-
/*!
 * @file ECFactory.cpp
 * @brief ExecutionContext fuctory class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ECFactory.cpp,v 1.1.2.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2007/04/13 16:06:16  n-ando
 * ExecutionContext Factory class.
 *
 */

#include <rtm/ECFactory.h>

namespace RTC 
{
  
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   *
   * @endif
   */
  ECFactoryCXX::ECFactoryCXX(const char* name,
			     ECNewFunc new_func,
			     ECDeleteFunc delete_func)
    : m_name(name),
      m_New(new_func),
      m_Delete(delete_func)
  {
  }
  
  /*!
   * @if jp
   * @brief ���ۥǥ��ȥ饯��
   * @else
   *
   * @endif
   */
  ECFactoryCXX::~ECFactoryCXX()
  {
  }
  
  /*!
   * @if jp
   * @brief �����о�ExecutionContext̾�Τ����
   * @else
   *
   * @endif
   */
  const char* ECFactoryCXX::name()
  {
    return m_name.c_str();
  }
  
  /*!
   * @if jp
   * @brief �����о�ExecutionContext���󥹥��󥹤�����
   * @else
   *
   * @endif
   */
  ExecutionContextBase* ECFactoryCXX::create()
  {
    return m_New();
  }
  
  /*!
   * @if jp
   * @brief �о�ExecutionContext���󥹥��󥹤��˴�
   * @else
   *
   * @endif
   */
  void ECFactoryCXX::destroy(ExecutionContextBase* ec)
  {
    m_Delete(ec);
  }
  
};
