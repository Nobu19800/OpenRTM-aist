#ifndef RTC_BYTEDATA_H
#define RTC_BYTEDATA_H


#include "ByteDataStreamBase.h"

namespace RTC
{
    /*!
     * @if jp
     * @class ByteData
     * @brief �V���A���C�Y��̃o�C�g��𑀍삷��N���X
     * 
     *
     *
     * @param
     *
     * @since 2.0.0
     *
     * @else
     * @class ByteData
     * @brief
     *
     *
     * @since 2.0.0
     *
     * @endif
     */
    class ByteData
    {
    public:
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
        ByteData();
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
        ~ByteData();
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
        ByteData(const ByteData &rhs);
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
        ByteData(const ByteDataStreamBase &rhs);
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
        ByteData& operator= (const ByteData &rhs);
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
        ByteData& operator= (const ByteDataStreamBase &rhs);
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
        void readData(unsigned char* data, unsigned long length) const;
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
        void writeData(const unsigned char* data, unsigned long length);
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
        unsigned char* getBuffer() const;
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
        unsigned long getDataLength() const;
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
        void isLittleEndian(bool little_endian);
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
        void setDataLength(unsigned long length);
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
        bool getEndian();
    private:
        unsigned char* m_buf;
        unsigned long m_len;
        bool m_little_endian;
    };

}  // namespace RTC


#endif  // RTC_BYTEDATA_H