// -*- C++ -*-
/*!
 * @file  Process.h
 * @brief coil process management functions
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2010
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

#ifndef COIL_PROCESS_H
#define COIL_PROCESS_H

#include <windows.h>
#include <tchar.h>
#include <string>
#include <coil/stringutil.h>

namespace coil
{

  /*!
   * @if jp
   * @brief �v���Z�X���N������
   *
   * �v���Z�X���N������B�����ɂ͋N������t�@�C������^����B���s�t�@�C
   * ���͊��ϐ� PATH �ɐݒ肳�ꂽ�R�}���h�T�[�`�p�X�����猟������A��
   * ����΃R�}���h���N�������B�v���Z�X�̋N������������� 0�A���s��
   * ��� -1 ��Ԃ��B
   *
   * @param command �N��������s�t�@�C���̃t���p�X
   * @return 0: ����, -1: ���s
   *
   * @else
   * @brief Launching a process
   *
   * This function launches a process. The argument is command file
   * name be launched. The command will be searched according to the
   * environment variable PATH of command search path. 0 will be
   * returned if launching process is successful, and -1 will be
   * returned if it is failed.
   * 
   * @param command full path string to a command to be executed.
   * @return 0: successful, -1: failed
   *
   * @endif
   */
  int launch_shell(std::string command);

}; // namespace coil
#endif // COIL_PROCESS_H
