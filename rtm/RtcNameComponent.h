// -*- C++ -*-
/*!
 * @file RtcNameComponent.h
 * @brief Name component helper class
 * @date $Date: 2005-05-12 09:06:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcNameComponent.h,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcNameComponent_h
#define RtcNameComponent_h

// CORBA header include
#include "rtm/idl/RTMBaseStub.h"
#include "rtm/idl/RTMBaseSkel.h"

// STL includes
#include <string>
#include <vector>

namespace RTM
{

  /*!
   * @if jp
   *
   * @class RtcNameComponent
   *
   * @brief CORBA Naming Service ���Ѥ��� Name Component �إ�ѡ����饹
   *
   * @else
   *
   * @class RtcNameComponent
   *
   * @brief Name component handling class for CORBA Naming Service.
   *
   * @endif
   */
  class RtcNameComponent
  {
  public:
	/*!
	 * @if jp
	 * @brief RtcNaming ���饹���󥹥ȥ饯��
	 *
	 * @else
	 *
	 * @brief A constructor of RtcNaming class.
	 *
	 * @endif
	 */
	RtcNameComponent();

	/*!
	 * @if jp
	 * @brief Name Component ������
	 *
	 * Ϳ����줿ʸ���󤫤� Name Component ��������롣
	 * 
     * @param path Name Component ������ѥ�ʸ����
	 *
	 * @else
	 *
	 * @brief Create name component
	 *
     * Create a name component from given string.
	 *
     * @param path path string to be name component.
	 *
	 * @endif
	 */
	RtcNameComponent(const std::string path);
	
	/*!
	 * @if jp
	 * @brief Name Component ������
	 *
	 * Ϳ����줿ʸ���󤫤� Name Component ��������롣
	 * 
     * @param path Name Component ������ѥ�ʸ����
	 *
	 * @else
	 *
	 * @brief Create name component
	 *
     * Create a naming component from given string.
	 *
     * @param path path string to be name component.
	 *
	 * @endif
	 */
	RtcNameComponent(const char* path);

	/*!
	 * @if jp
	 * @brief Name Component �μ���
	 *
	 * �����ݻ�����Ƥ��� Name Component ��������롣
	 * 
	 * @else
	 *
	 * @brief Get current name component
	 *
     * Create a name component from given string.
	 *
     * @param path path string to be name component.
	 *
	 * @endif
	 */
	CosNaming::Name get();

	/*!
	 * @if jp
	 * @brief Name Component ��pop
	 *
	 * �����ݻ�����Ƥ��� Name Component �κ�������pop���롣
	 * 
	 * @else
	 *
	 * @brief Pop the last name component.
	 *
     * Pop and return the last name component from current name components.
	 *
	 * @endif
	 */
	CosNaming::Name pop();

	/*!
	 * @if jp
	 * @brief Name Component �� push
	 *
	 * �����ݻ�����Ƥ��� Name Component �κ������� push ���롣
	 * 
	 * @else
	 *
	 * @brief Push the given string.
	 *
     * Push the given string to the last of name components.
	 *
	 * @endif
	 */
	CosNaming::Name push(const std::string& path);

	/*!
	 * @if jp
	 * @brief Name Component �ξõ�
	 *
	 * �����ݻ�����Ƥ��� Name Component ��õ�롣
	 * 
	 * @else
	 *
	 * @brief Erase the current name components.
	 *
     * Erase the curent name component which this object is holding.
	 *
	 * @endif
	 */
	void erase();

	inline int length() {return m_Length;}

	/*!
	 * @if jp
	 * @brief Name Component �κ���
	 *
	 * Ϳ����줿ʸ���󤫤� Name Component �����������Ū���Х᥽�åɡ�
	 * 
	 * @else
	 *
	 * @brief Create name component.
	 *
     * Static member method which creates name component from given path string.
	 *
	 * @endif
	 */
	static CosNaming::Name stringToNameComponent(const std::string& path);

  private:
	/*!
	 * @if jp
	 * @brief ʸ�����ʬ��
	 *
	 * Ϳ����줿ʸ���󤫤� Name Component �����������Ū���Х᥽�åɡ�
	 * 
     * @param input ����ʸ���� std::string ����
     * @param delimiter �ǥ�ߥ��� std::string ����
     * @param results ��̡� std::vector<std::string> ����
	 *
	 * @else
	 *
	 * @brief Split string.
	 *
     * Static member method which creates name component from given path string.
	 *
     * @param input Input string to be split. std::string tyoe.
     * @param delimiter Delimter. std::string type.
     * @param results Results. std::vector<std::string> type.
	 *
	 * @endif
	 */
	static int split(const std::string& input, const std::string& delimiter,
					 std::vector<std::string>& results);

	static void nodeToIdKind(const std::string& node, std::string& id,
							 std::string& kind);

	/*!
	 * @if jp
	 * @brief Name Component
	 *
	 * ���֥��������������ݻ������ name component��
	 * 
	 * @else
	 *
	 * @brief name Component
	 *
     * A name component to be hold by this object.
	 *
	 * @endif
	 */
	CosNaming::Name m_Name;
	/*!
	 * @if jp
	 * @brief Name Component ��Ĺ��
	 *
	 * ���֥��������������ݻ������ name component ��Ĺ����
	 * 
	 * @else
	 *
	 * @brief Length of the name component
	 *
     * The length of the name component.
	 *
	 * @endif
	 */
	int m_Length;
  };
};

#endif // RtcNameComponent_h
