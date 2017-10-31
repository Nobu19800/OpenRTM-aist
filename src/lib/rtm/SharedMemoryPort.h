// -*- C++ -*-
/*!
 * @file SharedMemoryPort.h
 * @brief Shared Memory Port class
 * @date $Date: 2017-10-29 07:57:18 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2006-2017
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 *
 */

#ifndef SHAREDMEMORYPORT_H
#define SHAREDMEMORYPORT_H


#include <rtm/Manager.h>
#include <rtm/idl/SharedMemorySkel.h>
#include <coil/SharedMemory.h>

#define DEFAULT_DATA_SIZE 8
#define DEFAULT_SHARED_MEMORY_SIZE 2097152

namespace RTC
{
  /*!
   * @if jp
   * @class SharedMemoryPort
   * @brief SharedMemory �N���X
   *
   * SharedMemoryPort 
   *
   * ���L����������N���X
   * CORBA�ɂ��ʐM�ɂ��Ammap�̏������A�I���Ȃǂ������[�g�ɑ���ł���
   *
   * @since 1.2.0
   *
   * @else
   * @class 
   * @brief 
   *
   * 
   *
   * @since 1.2.0
   *
   * @endif
   */
  class SharedMemoryPort
      : public virtual POA_OpenRTM::PortSharedMemory,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief �R���X�g���N�^
     *
     * �R���X�g���N�^
     *
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param manager Manager object
     *
     * @endif
     */
	  SharedMemoryPort();
    /*!
     * @if jp
     * @brief �f�X�g���N�^
     *
     * �f�X�g���N�^
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
	  virtual ~SharedMemoryPort();
    /*!
     * @if jp
     * @brief ������Ŏw�肵���f�[�^�T�C�Y�𐔒l�ɕϊ�����
	 * 1M �� 1048576
	 * 1k �� 1024
	 * 100 �� 100
     *
     * @param size_str �f�[�^�T�C�Y(������)
     * @return �f�[�^�T�C�Y(���l)
     *
     *
     *
     * @else
     * @brief 
     *
     * @param 
     * @return 
     *
     * @endif
     */
    virtual int string_to_MemorySize(std::string size_str);
     /*!
     * @if jp
     * @brief ���L�������̏�����
	 * windows�ł̓y�[�W���O�t�@�C����ɗ̈���m�ۂ���
	 * Linux�ł�/dev/shm�ȉ��Ƀt�@�C�����쐬����
	 * �쐬�����t�@�C���̓��e�����z�A�h���X�Ƀ}�b�s���O����
     *
     *
     *
     * @else
     * @brief 
     *
     * @param memory_size 
     * @param shm_address 
     *
     * @endif
     */
	virtual void create_memory(::CORBA::ULongLong memory_size, const char *shm_address)
    	throw (CORBA::SystemException);
     /*!
     * @if jp
     * @brief ���L�������̃}�b�s���O���s��
     *
     * @param memory_size ���L�������̃T�C�Y
     * @param shm_address ��Ԗ�
     *
     *
     *
     * @else
     * @brief 
     *
     * @param memory_size 
     * @param shm_address 
     *
     * @endif
     */
	virtual void open_memory(::CORBA::ULongLong memory_size, const char *shm_address)
    	throw (CORBA::SystemException);
     /*!
     * @if jp
     * @brief �}�b�s���O�������L���������A���}�b�v����
     * @param unlink Linux��/dev/shm�ȉ��ɍ쐬�����t�@�C�����폜����ꍇ��True�ɂ���
     *
     *
     * @else
     * @brief 
     *
     * @param unlink
     *
     * @endif
     */
	virtual void close_memory(::CORBA::Boolean unlink = false)
    	throw (CORBA::SystemException);
     /*!
     * @if jp
     * @brief �f�[�^����������
	 * �擪8byte�Ƀf�[�^�T�C�Y���������݁A���̌��Ƀf�[�^����������
	 * �ݒ肵���f�[�^�T�C�Y�����L�������̃T�C�Y���������ꍇ�A���L�������̏��������s��
	 *
     * @param data �������ރf�[�^
     *
     *
     *
     * @else
     * @brief 
     *
     * @param data 
     *
     * @endif
     */
    virtual void write(const cdrMemoryStream& data);
     /*!
     * @if jp
     * @brief �f�[�^��ǂݍ���
     * @return �f�[�^
     *
     *
     *
     * @else
     * @brief 
     *
     * @return 
     *
     * @endif
     */
    virtual void read(cdrMemoryStream& data);
     /*!
     * @if jp
     * @brief �ʐM���CORBA�C���^�[�t�F�[�X��o�^����
	 * �o�^���鎖�ɂ�苤�L�������̏����������Ƃ��ɁA�ʐM��ł��}�b�s���O����蒼�����Ƃ��ł���
	 *
     * @param sm SharedMemory�̃I�u�W�F�N�g���t�@�����X
     *
     *
     *
     * @else
     * @brief 
     *
     * @return 
     *
     * @endif
     */
	virtual void setInterface(::OpenRTM::PortSharedMemory_ptr sm)
    	throw (CORBA::SystemException);
     /*!
     * @if jp
     * @brief �G���f�B�A����ݒ肷��
	 *
     * @param endian �G���f�B�A��
	 *
     *
     *
     * @else
     * @brief 
     *
     * @param 
     *
     * @endif
     */
	virtual void setEndian(::CORBA::Boolean endian)
    	throw (CORBA::SystemException);
     /*!
     * @if jp
     * @brief �f�[�^�̑��M��m�点��
	 *
     * @return 
     *
     *
     *
     * @else
     * @brief 
     *
     * @return 
     *
     * @endif
     */
    virtual ::OpenRTM::PortStatus put()
      throw (CORBA::SystemException);
     /*!
     * @if jp
     * @brief �f�[�^�̑��M��v������
	 *
     * @return 
     *
     *
     *
     * @else
     * @brief 
     *
     * @return 
     *
     * @endif
     */
    virtual ::OpenRTM::PortStatus get()
      throw (CORBA::SystemException);

	virtual ::OpenRTM::PortSharedMemory_ptr getObjRef();

 protected:
    //mutable Logger rtclog;
    ::OpenRTM::PortSharedMemory_var m_smInterface;
    bool m_endian;
    coil::SharedMemory m_shmem;
	//::OpenRTM::PortSharedMemory_var m_objref;

    
  };  // class SharedMemoryPort
};  // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_RTOBJECT
