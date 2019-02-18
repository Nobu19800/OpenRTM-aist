#include "ByteData.h"
#include <string.h>

namespace RTC
{
    /*!
     * @if jp
     *
     * @brief �R���X�g���N�^
     *
     *
     *
     * @else
     *
     * @brief Constructor
     *
     *
     * @endif
     */
    ByteData::ByteData() :
        m_buf(NULL), m_len(0), m_little_endian(true)
    {

    }

    /*!
     * @if jp
     *
     * @brief �f�X�g���N�^
     *
     *
     *
     * @else
     *
     * @brief Destructor
     *
     *
     * @endif
     */
    ByteData::~ByteData()
    {
        delete[] m_buf;
    }

    /*!
     * @if jp
     *
     * @brief �R�s�[�R���X�g���N�^
     *
     * @param rhs
     *
     *
     * @else
     *
     * @brief Copy Constructor
     *
     * @param rhs
     *
     *
     * @endif
     */
    ByteData::ByteData(const ByteData &rhs)
    {
        m_len = rhs.m_len;
        m_buf = new unsigned char[m_len];
        memcpy(m_buf, rhs.m_buf, m_len);
    }


    /*!
     * @if jp
     *
     * @brief �R�s�[�R���X�g���N�^
     *
     * @param rhs
     *
     *
     * @else
     *
     * @brief Copy Constructor
     *
     * @param rhs
     *
     * @endif
     */
    ByteData::ByteData(const ByteDataStreamBase &rhs)
    {
        m_len = rhs.getDataLength();
        m_buf = new unsigned char[m_len];
        rhs.readData(m_buf, m_len);
    }
    /*!
     * @if jp
     *
     * @brief ������Z�q
     *
     * @param rhs
     * @return
     *
     *
     * @else
     *
     * @brief
     *
     * @param rhs
     * @return
     *
     * @endif
     */
    ByteData& ByteData::operator= (const ByteData &rhs)
    {
        m_len = rhs.m_len;
        m_buf = new unsigned char[m_len];
        memcpy(m_buf, rhs.m_buf, m_len);
        return *this;
    }
    /*!
     * @if jp
     *
     * @brief ������Z�q
     *
     * @param rhs
     * @return
     *
     *
     * @else
     *
     * @brief
     *
     * @param rhs
     * @return
     *
     * @endif
     */
    ByteData& ByteData::operator= (const ByteDataStreamBase &rhs)
    {
        m_len = rhs.getDataLength();
        m_buf = new unsigned char[m_len];
        rhs.readData(m_buf, m_len);
        return *this;
    }
    /*!
     * @if jp
     *
     * @brief �o�b�t�@�̃|�C���^���擾
     *
     * @return �o�b�t�@�̃|�C���^
     *
     *
     * @else
     *
     * @brief
     *
     * @return
     *
     * @endif
     */
    unsigned char* ByteData::getBuffer() const
    {
        return m_buf;
    }
    /*!
     * @if jp
     *
     * @brief �o�b�t�@�̃T�C�Y���擾
     *
     * @return �o�b�t�@�̃T�C�Y
     *
     *
     * @else
     *
     * @brief
     *
     * @return
     *
     * @endif
     */
    unsigned long ByteData::getDataLength() const
    {
        return m_len;
    }
    /*!
     * @if jp
     *
     * @brief �����̕ϐ��Ƀf�[�^���i�[
     *
     * @param data �������ݐ�̕ϐ�
     * @param length �f�[�^�̒���
     * @return
     *
     *
     * @else
     *
     * @brief
     *
     * @param data
     * @param length
     * @return
     *
     * @endif
     */
    void ByteData::readData(unsigned char* data, unsigned long length) const
    {
        if (length <= 0)
        {
            return;
        }
        if (length > m_len)
        {
            return;
        }
        memcpy(data, m_buf, length);
    }

    /*!
     * @if jp
     *
     * @brief �����̕ϐ��Ƀf�[�^���i�[
     *
     * @param data �������݌��̕ϐ�
     * @param length �f�[�^�̒���
     * @return
     *
     *
     * @else
     *
     * @brief
     *
     * @param data
     * @param length
     * @return
     *
     * @endif
     */
    void ByteData::writeData(const unsigned char* data, unsigned long length)
    {
        if (length <= 0)
        {
            return;
        }
        
        delete[] m_buf;
        
        m_len = length;
        m_buf = new unsigned char[length];
        memcpy(m_buf, data, length);
    }
    /*!
     * @if jp
     *
     * @brief �G���f�B�A���̐ݒ�
     *
     * @param little_endian ���g���G���f�B�A��(True)�A�r�b�O�G���f�B�A��(False)
     *
     *
     *
     * @else
     *
     * @brief
     *
     * @param little_endian
     *
     * @endif
     */
    void ByteData::isLittleEndian(bool little_endian)
    {
        m_little_endian = little_endian;
    }
    /*!
     * @if jp
     *
     * @brief �f�[�^�̃T�C�Y�̐ݒ�
     *
     * @param length �f�[�^�̃T�C�Y
     *
     *
     *
     * @else
     *
     * @brief
     *
     * @param length
     *
     * @endif
     */
    void ByteData::setDataLength(unsigned long length)
    {
        if (length <= 0)
        {
            return;
        }
        delete[] m_buf;

        m_len = length;
        m_buf = new unsigned char[m_len];
    }
    /*!
     * @if jp
     *
     * @brief �G���f�B�A���̎擾
     *
     * @return ���g���G���f�B�A��(True)�A�r�b�O�G���f�B�A��(False)
     *
     *
     *
     * @else
     *
     * @brief
     *
     * @return
     *
     * @endif
     */
    bool ByteData::getEndian()
    {
        return m_little_endian;
    }
}