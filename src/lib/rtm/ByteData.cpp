﻿#include "ByteData.h"
#include "ByteDataStreamBase.h"
#include <cstring>


namespace RTC
{
    /*!
     * @if jp
     *
     * @brief コンストラクタ
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
    ByteData::ByteData()
    {

    }

    /*!
     * @if jp
     *
     * @brief デストラクタ
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
      if (!m_external_buffer)
      {
        delete[] m_buf;
      }
    }

    /*!
     * @if jp
     *
     * @brief コピーコンストラクタ
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
    ByteData::ByteData(ByteData &rhs)
    {
      m_len = rhs.m_len;
      m_buf = rhs.m_buf;
      rhs.m_external_buffer = true;
    }
    ByteData::ByteData(const ByteData& rhs)
    {
      m_len = rhs.m_len;
      m_buf = new unsigned char[m_len];
      memcpy(m_buf, rhs.m_buf, m_len);
    }


    /*!
     * @if jp
     *
     * @brief コピーコンストラクタ
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
    ByteData::ByteData(ByteDataStreamBase &rhs)
    {
      m_len = rhs.getDataLength();
      rhs.copyFromData(m_buf, m_len);
    }
    ByteData::ByteData(const ByteDataStreamBase& rhs)
    {
      m_len = rhs.getDataLength();
      m_buf = new unsigned char[m_len];
      rhs.readData(m_buf, m_len);
    }
    /*!
     * @if jp
     *
     * @brief 代入演算子
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
    ByteData& ByteData::operator= (ByteData &rhs)
    {
      if (!m_external_buffer)
      {
        delete[] m_buf;
        m_buf = nullptr;
      }
      m_len = rhs.m_len;
      m_buf = rhs.m_buf;
      rhs.m_external_buffer = true;
      m_external_buffer = false;
      return *this;
    }
    ByteData& ByteData::operator= (const ByteData& rhs)
    {
      if (m_len != rhs.m_len)
      {
        m_len = rhs.m_len;
        if (!m_external_buffer)
        {
          delete[] m_buf;
          m_buf = nullptr;
        }
        m_buf = new unsigned char[m_len];
      }
      memcpy(m_buf, rhs.m_buf, m_len);
      return *this;
    }
    /*!
     * @if jp
     *
     * @brief 代入演算子
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
    ByteData& ByteData::operator= (ByteDataStreamBase &rhs)
    {
      if (!m_external_buffer)
      {
        delete[] m_buf;
        m_buf = nullptr;
      }
      
      m_len = rhs.getDataLength();
      rhs.copyFromData(m_buf, m_len);
      m_external_buffer = true;
 
      return *this;
      
    }
    ByteData& ByteData::operator= (const ByteDataStreamBase& rhs)
    {
      if (m_len != rhs.getDataLength())
      {
        m_len = rhs.getDataLength();
        if (!m_external_buffer)
        {
          delete[] m_buf;
        }
        m_buf = new unsigned char[m_len];
      }
      rhs.readData(m_buf, m_len);
      return *this;
    }
    /*!
     * @if jp
     *
     * @brief バッファのポインタを取得
     *
     * @return バッファのポインタ
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
     * @brief バッファのサイズを取得
     *
     * @return バッファのサイズ
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
     * @brief 引数の変数にデータを格納
     *
     * @param data 書き込み先の変数
     * @param length データの長さ
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
     * @brief 内部の変数にデータを格納
     *
     * @param data 書き込み元の変数
     * @param length データの長さ
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

        if(m_len != length)
        {
          if (!m_external_buffer)
          {
            delete[] m_buf;
          }
          m_len = length;
          m_buf = new unsigned char[length];
        }
        memcpy(m_buf, data, length);
    }
    /*!
     * @if jp
     *
     * @brief 引数の変数にデータを格納
     *
     * @param data 書き込み先の変数
     * @param length データの長さ
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
    void ByteData::copyFromData(unsigned char*& data, unsigned long /*length*/) const
    {
      data = m_buf;
    }

    /*!
     * @if jp
     *
     * @brief 内部の変数にデータを格納
     *
     * @param data 書き込み元の変数
     * @param length データの長さ
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
    void ByteData::copyToData(unsigned char* data, unsigned long length)
    {
      m_len = length;
      m_buf = data;
      m_external_buffer = true;
    }
    /*!
     * @if jp
     *
     * @brief エンディアンの設定
     *
     * @param little_endian リトルエンディアン(True)、ビッグエンディアン(False)
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
     * @brief データのサイズの設定
     *
     * @param length データのサイズ
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
        if (length <= 0 || m_len == length)
        {
            return;
        }
        if (!m_external_buffer)
        {
          delete[] m_buf;
        }
        m_len = length;
        m_buf = new unsigned char[m_len];
    }
    /*!
     * @if jp
     *
     * @brief エンディアンの取得
     *
     * @return リトルエンディアン(True)、ビッグエンディアン(False)
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

    void ByteData::setExternalBuffer(const bool ext)
    {
      m_external_buffer = ext;
    }

    void ByteData::copyFromData(ByteDataStreamBase& data)
    {
      m_len = data.getDataLength();
      data.copyFromData(m_buf, m_len);
      m_external_buffer = true;
    }

    void ByteData::copyToData(ByteDataStreamBase& data)
    {
      data.copyToData(m_buf, m_len);
      //m_external_buffer = true;
    }

    void ByteData::copyFromData(ByteDataStreamBase* data)
    {
      m_len = data->getDataLength();
      data->copyFromData(m_buf, m_len);
      m_external_buffer = true;
    }

    void ByteData::copyToData(ByteDataStreamBase* data)
    {
      data->copyToData(m_buf, m_len);
      //m_external_buffer = true;
    }


} // namespace RTC
