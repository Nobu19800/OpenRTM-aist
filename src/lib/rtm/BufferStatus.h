// -*- C++ -*-
/*!
 *
 * @file BufferStatus.h
 * @brief Buffer status enum definition
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 */

#ifndef RTC_BUFFERSTATUS_H
#define RTC_BUFFERSTATUS_H

namespace RTC
{
  /*!
   * @if jp
   * @class BufferStatus mixin class
   * @brief BufferStatus mixin ���饹
   *
   * ���Υ��饹�ϡ�enum������줿�꥿���󥳡��ɤ򡢥Хåե���Ϣ���֥���
   * ���Ƕ������Ѥ��뤿��� mixin ���饹�Ǥ��롣���Υ꥿���󥳡��ɤ��
   * �Ѥ��륯�饹�Ǥϡ�BufferStatus ���饹��public �Ѿ��������� define
   * ���Ƥ��� BUFFERSTATUS_ENUM �򥯥饹��˵��Ҥ��뤳�Ȥ����Ѳ�ǽ�Ȥ�
   * �롣����ˤ�ꡢenum �� ReturnCode_t ���Ȥ��� typedef �����ʸ�
   * ReturnCode_t �����ѤǤ���褦�ˤ���ȤȤ�ˡ�̾�����֤� enum ���
   * ���줿�Ƽ��̻Ҥ��������饹̾���������Ƴ�����롣
   *
   * @else
   * @class BufferStatus mixin class
   * @brief BufferStatus mixin class
   *
   * This is a mixin class to provide enumed return codes that are
   * commonly utilised in buffer realted sub-classes. To use this
   * class, sub-class should inherit this class as a public super
   * class, and declare BUFFERSTATUS_ENUM defined below. Consequently,
   * ReturnCode_t type that is typedefed by this macro can be used in
   * the sub-class, and enumed identifiers are imported to the class's
   * namespace.
   *
   * @endif
   */
  class BufferStatus
  {
  public:
    /*!
     * @if jp
     * @brief DataPortStatus �꥿���󥳡���
     *
     * �ǡ����ݡ��ȴ�Ϣ�Υ��饹�Ƕ��̤Υ꥿���󥳡���
     *
     * - BUFFER_OK:            ���ｪλ
     * - BUFFER_ERROR:         �Хåե����顼
     * - BUFFER_FULL:          �Хåե��ե�
     * - BUFFER_EMPTY:         �Хåե�����ץƥ�
     * - NOT_SUPPORTED:        ̤���ݡ��ȵ�ǽ
     * - TIMEOUT:              �����ॢ����
     * - PRECONDITION_NOT_MET: ���������������Ƥ��ʤ�
     *
     * @else
     * @brief DataPortStatus return codes
     *
     * Common return codes for buffer classes.
     *
     * - BUFFER_OK:            Normal return
     * - BUFFER_ERROR:         Buffer error
     * - BUFFER_FULL:          Buffer full
     * - BUFFER_EMPTY:         Buffer empty
     * - NOT_SUPPORTED:        Not supported function
     * - TIMEOUT:              Timeout
     * - PRECONDITION_NOT_MET: Precodition not met
     *
     * @endif
     */
    enum Enum
      {
        BUFFER_OK = 0,
        BUFFER_ERROR,
        BUFFER_FULL,
        BUFFER_EMPTY,
        NOT_SUPPORTED,
        TIMEOUT,
        PRECONDITION_NOT_MET
      };

    /*!
     * @if jp
     *
     * @brief DataPortStatus �꥿���󥳡��ɤ�ʸ������Ѵ�
     *
     * DataPortStatus �꥿���󥳡��ɤ�ʸ������Ѵ�����
     *
     * @param status �Ѵ��о� DataPortStatus �꥿���󥳡���
     *
     * @return ʸ�����Ѵ����
     *
     * @else
     *
     * @brief Convert DataPortStatus into the string.
     *
     * Convert DataPortStatus into the string.
     *
     * @param status The target DataPortStatus for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(Enum status)
    {
      const char* str[] = {
        "BUFFER_OK",
        "BUFFER_ERROR",
        "BUFFER_FULL",
        "BUFFER_EMPTY",
        "NOT_SUPPORTED",
        "TIMEOUT",
        "PRECONDITION_NOT_MET"
      };
      return str[status];
    }
  };
}; // namespace RTC

#define BUFFERSTATUS_ENUM \
  typedef ::RTC::BufferStatus::Enum ReturnCode;       \
  using ::RTC::BufferStatus::BUFFER_OK;               \
  using ::RTC::BufferStatus::BUFFER_ERROR;            \
  using ::RTC::BufferStatus::BUFFER_FULL;             \
  using ::RTC::BufferStatus::BUFFER_EMPTY;            \
  using ::RTC::BufferStatus::NOT_SUPPORTED;           \
  using ::RTC::BufferStatus::TIMEOUT;                 \
  using ::RTC::BufferStatus::PRECONDITION_NOT_MET;

#endif // RTC_BUFFERSTATUS_H
