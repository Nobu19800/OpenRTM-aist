// -*- C++ -*-
/*!
 * @file SharedMemory_win32.h
 * @brief SharedMemory class
 * @date $Date$
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2017 Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_SHAREDMEMORY_H
#define COIL_SHAREDMEMORY_H

#include <windows.h>

#include <string>
#include <coil/config_coil.h>

#define DEFAULT_MEMORY_SIZE 2097152



namespace coil
{
  /*!
   * @if jp
   *
   * @class SharedMemory
   * @brief SharedMemory �N���X
   *
   * @else
   *
   * @class SharedMemory
   * @brief SharedMemory class
   *
   * @endif
   */
  class SharedMemory
  {
  public:

    /*!
     * @if jp
     *
     * @brief �R���X�g���N�^
     *
     * �R���X�g���N�^�B
     *
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     *
     * @endif
     */
    SharedMemory();



    /*!
     * @if jp
     *
     * @brief �f�X�g���N�^
     *
     * �f�X�g���N�^�B
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~SharedMemory();

    /*!
     * @if jp
     *
     * @brief �R�s�[�R���X�g���N�^
     *
     * �R�s�[�R���X�g���N�^�B
     *
     * @param rhs �R�s�[�����L�������I�u�W�F�N�g
     *
     * @else
     *
     * @brief Copy Constructor
     *
     * Copy Constructor
     *
     * @param rhs shared memory object of copy source.
     *
     * @endif
     */
    SharedMemory(const SharedMemory& rhs);

    /*!
     * @if jp
     *
     * @brief ������Z�q
     *
     * ���L�������I�u�W�F�N�g���R�s�[����B
     *
     * @param rhs ��������I���L�������I�u�W�F�N�g
     *
     * @return �������
     *
     * @else
     *
     * @brief Assignment operator
     *
     * Copy a shared memory object.
     *
     * @param rhs shared memory object of assignment source.
     *
     * @return Assignment result.
     *
     * @endif
     */
    SharedMemory& operator=(const SharedMemory& rhs);


    /*!
     * @if jp
     *
     * @brief ���L�������̐���
     *�B
     *
     * @param shm_address ���L�������̎��ʎq
     * @param memory_size ���L�������̃T�C�Y
     *
     * @return 0: ����, -1: ���s
     *
     * @else
     *
     * @brief Create Shared Memory 
     *
     *
     * @param shm_address 
     * @param memory_size 
     *
     * @return 0: successful, -1: failed
     *
     * @endif
     */
    virtual int create(std::string shm_address,
                     int memory_size = DEFAULT_MEMORY_SIZE);


    /*!
     * @if jp
     *
     * @brief ���L�������ւ̃A�N�Z�X
     *�B
     *
     * @param shm_address ���L�������̎��ʎq
     *
     * @return 0: ����, -1: ���s
     *
     * @else
     *
     * @brief Open Shared Memory 
     *
     *
     * @param shm_address 
     * @param memory_size 
     *
     * @return 0: successful, -1: failed
     *
     * @endif
     */
	virtual int open(std::string shm_address,
		int memory_size = DEFAULT_MEMORY_SIZE);


    /*!
     * @if jp
     *
     * @brief ���L�������ւ̏�������
     *�B
     *
     * @param data �������ރf�[�^
     *
     * @return 0: ����, -1: ���s
     *
     * @else
     *
     * @brief Write Shared Memory 
     *
     *
     * @param data 
     *
     * @return 0: successful, -1: failed
     *
     * @endif
     */
    virtual int write(const char *data, const int pos, const int size);


    /*!
     * @if jp
     *
     * @brief ���L����������̓ǂݍ���
     *�B
     *
     * @param data �ǂݍ��ރf�[�^
     *
     * @return 0: ����, -1: ���s
     *
     * @else
     *
     * @brief Read Shared Memory 
     *
     *
     * @param data 
     *
     * @return 0: successful, -1: failed
     *
     * @endif
     */
    virtual int read(char* data, const int pos, const int size);

    /*!
     * @if jp
     *
     * @brief ���L�������̍폜
     *�B
     *
     *
     * @return 0: ����, -1: ���s
     *
     * @else
     *
     * @brief Close Shared Memory 
     *
     *
     *
     * @return 0: successful, -1: failed
     *
     * @endif
     */
    virtual int close();
    /*!
     * @if jp
     *
     * @brief �������̃T�C�Y�擾
     *�B
     *
     *
     * @return �T�C�Y
     *
     * @else
     *
     * @brief 
     *
     *
     *
     * @return size
     *
     * @endif
     */
    virtual unsigned int get_size();
    /*!
     * @if jp
     *
     * @brief �������̃A�h���X�擾
     *�B
     *
     *
     * @return �A�h���X
     *
     * @else
     *
     * @brief 
     *
     *
     *
     * @return address
     *
     * @endif
     */
	virtual std::string get_addresss();
    /*!
     * @if jp
     *
     * @brief �������̎擾
     *
     *
     *
     * @return ������
     *
     * @else
     *
     * @brief 
     *
     *
     *
     * @return memory
     *
     * @endif
     */
    virtual char *get_data();
    /*!
     * @if jp
     *
     * @brief �t�@�C���폜(Windows�̏ꍇ�͉������Ȃ�)
     *
     *
     *
     * @return 0: ����, -1: ���s
     *
     * @else
     *
     * @brief 
     *
     *
     *
     * @return 0: successful, -1: failed
     *
     * @endif
     */
    virtual int unlink();
     /*!
     * @if jp
     *
     * @brief ���L�������ɐ����ς݂��̊m�F
     *
     *
     *
     * @return true: �쐬�ς�, false: ���쐬
     *
     * @else
     *
     * @brief 
     *
     *
     *
     * @return
     *
     * @endif
     */
    virtual bool created();

  private:
    int m_memory_size;
    std::string m_shm_address;
    char *m_shm;
    HANDLE m_handle;
    bool m_file_create;
  };  // class SharedMemory

};  // namespace coil

#endif // SharedMemory_h
