// -*- C++ -*-
/*!
 * @file NumberingPolicy.cpp
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
 * $Id: NumberingPolicy.cpp,v 1.1.4.2 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.4.1  2007/07/20 15:57:32  n-ando
 * Some ineffective expressions were added to suppress compiler's warning.
 *
 * Revision 1.1  2006/11/04 21:07:31  n-ando
 * Component numbering rule was derived into policy class.
 *
 */

#include <rtm/NumberingPolicy.h>
#include <rtm/StringUtil.h>
//============================================================
// DefaultNumberingPolicy
//============================================================
/*!
 * @if jp
 * @brief ���֥���������������̾�κ���
 * @else
 * 
 * @endif
 */
std::string DefaultNumberingPolicy::onCreate(void* obj)
{
  std::vector<void*>::size_type pos;
  
  ++m_num;
  
  try
    {
      pos = find(NULL);
      m_objects[pos] = obj;
      return otos(pos);
    }
  catch (ObjectNotFound& e)
    {
      e;
      m_objects.push_back(obj);
      return otos((int)(m_objects.size() - 1));
    }
}

/*!
 * @if jp
 * @brief ���֥������Ⱥ������̾�β���
 * @else
 * 
 * @endif
 */
void DefaultNumberingPolicy::onDelete(void* obj)
{
  std::vector<void*>::size_type pos;
  pos = find(obj);
  if (pos < m_objects.size())
    {
      m_objects[pos] = NULL;
    }
  --m_num;
}

/*!
 * @if jp
 * @brief ���֥������Ȥθ���
 * @else
 * 
 * @endif
 */
long int DefaultNumberingPolicy::find(void* obj)
{
  std::vector<void*>::size_type len(m_objects.size());
  std::vector<void*>::size_type i(0);
  for (i = 0; i < len; ++i)
    {
      if (m_objects[i] == obj) return i;
    }
  throw ObjectNotFound();
  return i;
}
