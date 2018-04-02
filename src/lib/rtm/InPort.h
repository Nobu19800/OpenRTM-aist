﻿// -*- C++ -*-
/*!
 * @file InPort.h
 * @brief InPort template class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
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

#ifndef RTC_INPORT_H
#define RTC_INPORT_H

#include <string>
#include <vector>
#include <iostream>

#include <coil/TimeValue.h>
#include <coil/Time.h>
#include <coil/OS.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>

#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/InPortBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortCallback.h>
#include <rtm/InPortConnector.h>
#include <rtm/Timestamp.h>
#include <rtm/DirectInPortBase.h>



namespace RTC
{
  /*!
   * @if jp
   *
   * @class InPort
   *
   * @brief InPort テンプレートクラス
   * 
   * InPort の実装である InPort<T> のテンプレートクラス。
   * <T> はBasicDataType.idl にて定義されている型で、メンバとして
   * Time 型の tm , および T型の data を持つ構造体でなくてはならない。
   * InPort は内部にリングバッファを持ち、外部から送信されたデータを順次
   * このリングバッファに格納する。リングバッファのサイズはデフォルトで64と
   * なっているが、コンストラクタ引数によりサイズを指定することができる。
   * データはフラグによって未読、既読状態が管理され、isNew(), write(), read(),
   * isFull(), isEmpty() 等のメソッドによりハンドリングすることができる。
   *   
   * OnRead系コールバック (読み出しに起因するイベントによりコールされる)
   *
   * - void OnRead::operator(): 
   *     InPort::read() を呼び出し読み出しを行う際にコールされる。
   *
   * - DataType OnReadConvert::operator(DataType): 
   *     InPort::read() を呼び出し、データをバッファから読みだす際に呼ばれ
   *     データの変換を行う。引数にはバッファから読み出された値が与えられ、
   *     変換後のデータを戻り値として返す。この値がread()の返す値となる。
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class InPort
   *
   * @brief InPort template class
   *
   * This is a template class that implements InPort.  <T> is the type
   * defined in BasicDataType.idl and must be the structure which has
   * both Time type tm and type-T data as a member. InPort has a ring
   * buffer internally, and stores the received data externally in
   * this buffer one by one. The size of ring buffer can be specified
   * according to the argument of constructor, though the default size
   * is 64. Unread data and data which is already read are managed
   * with the flag, and the data can be handled by the isNew(),
   * write(), read(), isFull() and isEmpty() method etc.
   *
   * @since 0.2.0
   *
   * @endif
   */
  template <class DataType>
  class InPort
	  : public InPortBase, DirectInPortBase<DataType>
  {
  public:
    DATAPORTSTATUS_ENUM
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ。
     * パラメータとして与えられる T 型の変数にバインドされる。
     *
     * @param name InPort 名。InPortBase:name() により参照される。
     * @param value この InPort にバインドされる T 型の変数
     * @param bufsize InPort 内部のリングバッファのバッファ長(デフォルト値:64)
     * @param read_block 読込ブロックフラグ。
     *        データ読込時に未読データがない場合、次のデータ受信までブロックする
     *        かどうかを設定(デフォルト値:false)
     * @param write_block 書込ブロックフラグ。
     *        データ書込時にバッファがフルであった場合、バッファに空きができる
     *        までブロックするかどうかを設定(デフォルト値:false)
     * @param read_timeout 読込ブロックを指定していない場合の、データ読取タイム
     *        アウト時間(ミリ秒)(デフォルト値:0)
     * @param write_timeout 書込ブロックを指定していない場合の、データ書込タイム
     *        アウト時間(ミリ秒)(デフォルト値:0)
     *
     * @else
     *
     * @brief A constructor.
     *
     * constructor.
     * This is bound to type-T variable given as a parameter.
     *
     * @param name A name of the InPort. This name is referred by
     *             InPortBase::name().
     * @param value type-T variable that is bound to this InPort.
     * @param bufsize Buffer length of internal ring buffer of InPort
     *                (The default value:64)
     * @param read_block Flag of reading block.
     *                   When there are not unread data at reading data,
     *                   set whether to block data until receiving the next 
     *                   data. (The default value:false)
     * @param write_block Flag of writing block.
     *                    If the buffer was full at writing data, set whether 
     *                    to block data until the buffer has space. 
     *                    (The default value:false)
     * @param read_timeout Data reading timeout time (millisecond) 
     *                     when not specifying read blocking.
     *                     (The default value:0)
     * @param write_timeout Data writing timeout time (millisecond)
     *                      when not specifying writing block.
     *                      (The default value:0)
     *
     * @endif
     */
    InPort(const char* name, DataType& value,
           int bufsize=64, 
           bool read_block = false, bool write_block = false,
           int read_timeout = 0, int write_timeout = 0)
#if defined(__GNUC__) && (__GNUC__ <= 3 && __GNUC_MINOR__ <= 3) 
      : InPortBase(name, ::CORBA_Util::toRepositoryIdOfStruct<DataType>()),
#else
      : InPortBase(name, ::CORBA_Util::toRepositoryId<DataType>()),
#endif
	  DirectInPortBase<DataType>(value),
        m_name(name), m_value(value),
        m_OnRead(NULL),  m_OnReadConvert(NULL),
        m_status(1), m_directNewData(false)
    {
      this->addConnectorDataListener(ON_RECEIVED,
                                     new Timestamp<DataType>("on_received"));
      this->addConnectorDataListener(ON_BUFFER_READ,
                                     new Timestamp<DataType>("on_read"));
	  m_directport = this;
    }
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * デストラクタ。
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~InPort(void){};

    /*!
     * @if jp
     *
     * @brief ポート名称を取得する。
     *
     * ポート名称を取得する。
     *
     * @return ポート名称
     *
     * @else
     *
     * @brief Get port name
     *
     * Get port name.
     *
     * @return The port name
     *
     * @endif
     */
    virtual const char* name()
    {
      return m_name.c_str();
    }

    
    /*!
     * @if jp
     *
     * @brief 最新データが存在するか確認する
     * 
     * InPortに未読の最新データが到着しているかをbool値で返す。
     * InPortが未接続の場合、および接続コネクタのバッファがEmpty
     * の場合にはfalseを返す。
     *
     * @return true 未読の最新データが存在する
     *         false 未接続またはバッファにデータが存在しない。
     * 
     * @else
     *
     * @brief Check whether the data is newest
     * 
     * Check whether the data stored at a current buffer position is newest.
     *
     * @return Newest data check result
     *         ( true:Newest data. Data has not been readout yet.
     *          false:Past data．Data has already been readout.)
     * 
     * @endif
     */
    virtual bool isNew()
    {
      RTC_TRACE(("isNew()"));

      // In single-buffer mode, all connectors share the same buffer. This
      // means that we only need to read from the first connector to get data
      // received by any connector.
      {
        Guard gurad(m_valueMutex);
        if (m_directNewData == true)
          {
            RTC_DEBUG(("isNew() returns true because of direct write."));
            return true;
          }
      }
      int r(0);
      {
        Guard guard(m_connectorsMutex);
        if (m_connectors.size() == 0)
          {
            RTC_DEBUG(("no connectors"));
            return false;
          }
        r = m_connectors[0]->getBuffer()->readable();
      }
      
      if (r > 0)
        {
          RTC_DEBUG(("isNew() = true, readable data: %d", r));
          return true;
        }
      
      RTC_DEBUG(("isNew() = false, no readable data"));
      return false;
    }

    /*!
     * @if jp
     *
     * @brief バッファが空かどうか確認する
     * 
     * InPortのバッファが空かどうかを bool 値で返す。
     * 空の場合は true, 未読データがある場合は false を返す。
     *
     * @return true  バッファは空
     *         false バッファに未読データがある
     * 
     * @else
     *
     * @brief Check whether the data is newest
     * 
     * Check whether the data stored at a current buffer position is newest.
     *
     * @return Newest data check result
     *         ( true:Newest data. Data has not been readout yet.
     *          false:Past data．Data has already been readout.)
     * 
     * @endif
     */
    virtual bool isEmpty()
    {
      RTC_TRACE(("isEmpty()"));
      if (m_directNewData == true) { return false; }
      int r(0);

      {
        Guard guard(m_connectorsMutex);
        if (m_connectors.size() == 0)
          {
            RTC_DEBUG(("no connectors"));
            return true;
          }
        // In single-buffer mode, all connectors share the same buffer. This
        // means that we only need to read from the first connector to get data
        // received by any connector.
        r = m_connectors[0]->getBuffer()->readable();
      }

      if (r == 0)
        {
          RTC_DEBUG(("isEmpty() = true, buffer is empty"));
          return true;
        }
      
      RTC_DEBUG(("isEmpty() = false, data exists in the buffer"));
      return false;
    }

    virtual void write(DataType& data)
    {
      Guard guard(m_valueMutex);
      m_value = data;
      m_directNewData = true;
    }

    /*!
     * @if jp
     *
     * @brief DataPort から値を読み出す
     *
     * InPortに書き込まれたデータを読みだす。接続数が0、またはバッファに
     * データが書き込まれていない状態で読みだした場合の戻り値は不定である。
     * バッファが空の状態のとき、
     * 事前に設定されたモード (readback, do_nothing, block) に応じて、
     * 以下のような動作をする。
     *
     * - readback: 最後の値を読みなおす。
     *
     * - do_nothing: 何もしない
     *
     * - block: ブロックする。タイムアウトが設定されている場合は、
     *       タイムアウトするまで待つ。
     *
     * バッファが空の状態では、InPortにバインドされた変数の値が返される。
     * したがって、初回読み出し時には不定値を返す可能性がある。
     * この関数を利用する際には、
     *
     * - isNew(), isEmpty() と併用し、事前にバッファ状態をチェックする。
     * 
     * - 初回読み出し時に不定値を返さないようにバインド変数を事前に初期化する
     * 
     * - ReturnCode read(DataType& data) 関数の利用を検討する。
     *
     * ことが望ましい。
     *
     * 各コールバック関数は以下のように呼び出される。
     * - OnRead: read() 関数が呼ばれる際に必ず呼ばれる。
     * 
     * - OnReadConvert: データの読み出しが成功した場合、読みだしたデータを
     *       引数としてOnReadConvertが呼び出され、戻り値をread()が戻り値
     *       として返す。
     *
     * - OnEmpty: バッファが空のためデータの読み出しに失敗した場合呼び出される。
     *        OnEmpty の戻り値を read() の戻り値として返す。
     *
     * - OnBufferTimeout: データフロー型がPush型の場合に、読み出し
     *        タイムアウトのためにデータの読み出しに失敗した場合に呼ばれる。
     *
     * - OnRecvTimeout: データフロー型がPull型の場合に、読み出しタイムアウト
     *        のためにデータ読み出しに失敗した場合に呼ばれる。
     *
     * - OnReadError: 上記以外の理由で読みだしに失敗した場合に呼ばれる。
     *        理由としては、バッファ設定の不整合、例外の発生などが考えられる
     *        が通常は起こりえないためバグの可能性がある。
     *
     * @return 読み出し結果(読み出し成功:true, 読み出し失敗:false)
     *
     * @else
     *
     * @brief Readout the value from DataPort
     *
     * Readout the value from DataPort
     *
     * - When Callback functor OnRead is already set, OnRead will be invoked
     *   before reading from the buffer held by DataPort.
     * - When the buffer held by DataPort can detect the underflow,
     *   and when it detected the underflow at reading, callback functor
     *   OnUnderflow will be invoked.
     * - When callback functor OnReadConvert is already set, the return value of
     *   operator() of OnReadConvert will be the return value of read().
     * - When timeout of reading is already set by setReadTimeout(),
     *   it waits for only timeout time until the state of the buffer underflow
     *   is reset, and if OnUnderflow is already set, this will be invoked to 
     *   return.
     *
     * @return Readout result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool read()
    {
      RTC_TRACE(("DataType read()"));

      if (m_OnRead != NULL) 
        {
          (*m_OnRead)();
          RTC_TRACE(("OnRead called"));
        }
      // 1) direct connection
      {
        Guard guard(m_valueMutex);
        if (m_directNewData == true)
          {
            RTC_DEBUG(("Direct data transfer"));
            if (m_OnReadConvert != 0) 
              {
                m_value = (*m_OnReadConvert)(m_value);
                RTC_DEBUG(("OnReadConvert for direct data called"));
                return true;
              }
            m_directNewData = false;
            return true;
          }
      }
      // 2) network connection
      cdrMemoryStream cdr;
      ReturnCode ret;
      {
        Guard guard(m_connectorsMutex);
        if (m_connectors.size() == 0)
          {
            RTC_DEBUG(("no connectors"));
            return false;
          }

        
      }

	  if (!m_connectors[0]->getDirectData(m_value))
	  {
		  {
			  Guard guard(m_connectorsMutex);
			  // In single-buffer mode, all connectors share the same buffer. This
			  // means that we only need to read from the first connector to get data
			  // received by any connector.
			  ret = m_connectors[0]->read(cdr);
		  }
		  m_status[0] = ret;
		  if (ret == PORT_OK)
		  {
			  Guard guard(m_valueMutex);
			  RTC_DEBUG(("data read succeeded"));
			  m_value <<= cdr;
			  if (m_OnReadConvert != 0)
			  {
				  m_value = (*m_OnReadConvert)(m_value);
				  RTC_DEBUG(("OnReadConvert called"));
				  return true;
			  }
			  return true;
		  }
		  else if (ret == BUFFER_EMPTY)
		  {
			  RTC_WARN(("buffer empty"));
			  return false;
		  }
		  else if (ret == BUFFER_TIMEOUT)
		  {
			  RTC_WARN(("buffer read timeout"));
			  return false;
		  }
	  }
	  else
	  {
		  return true;
	  }
      RTC_ERROR(("unknown retern value from buffer.read()"));
      return false;
    }
    

    /*!
     * @if jp
     *
     * @brief バインドされた T 型の変数に InPort バッファの最新値を読み込む
     *
     * バインドされた T 型のデータに InPort の最新値を読み込む。
     * コンストラクタで T 型の変数と InPort がバインドされていなければならない。
     * このメソッドはポリモーフィックに使用される事を前提としているため、
     * 型に依存しない引数、戻り値となっている。
     *
     * @else
     *
     * @brief Read the newly value to type-T variable which is bound to InPort's
     *        buffer.
     *
     * Read the newly value to type-T data which is bound to InPort's buffer.
     * The type-T variable must be bound to InPort in constructor.
     * Since this method assumes to be used for polymorphic,
     * its argument and the return value do not depend on type.
     *
     * @endif
     */
    virtual void update()
    {
      this->read();
    };
    
    /*!
     * @if jp
     *
     * @brief T 型のデータへ InPort の最新値データを読み込む
     *
     * InPort に設定されている最新データを読み込み、
     * 指定されたデータ変数に設定する。
     *
     * @param rhs InPort バッファから値を読み込む T 型変数
     *
     * @else
     *
     * @brief Read the newly value data in InPort to type-T variable
     *
     * Read the newly data set in InPort and set to specified data variable.
     *
     * @param rhs The type-T variable to read from InPort's buffer
     *
     * @endif
     */
    void operator>>(DataType& rhs)
    {
      this->read();
      rhs = m_value;
      return;
    }

    /*!
     * @if jp
     *
     * @brief 特定のコネクタへの書き込みステータスを得る
     *
     * InPort は接続ごとに Connector と呼ばれる仮想データチャネルを持
     * つ。write() 関数はこれら Connector に対してデータを書き込むが、
     * 各 Connector は書き込みごとにステータスを返す。write() 関数では、
     * すべての Connector が正常終了したときのみ true を返し、それ以外
     * では false を返却する。この関数は write() が false の場合ステー
     * タスを調べるのに使用することができる。
     *
     * @param index Connector の index
     * @return ステータス
     *
     * @else
     *
     * @brief Getting specified connector's writing status
     *
     * An InPort has Connectors that are virtual data stream channel
     * for each connection.  "write()" function write into these
     * Connectors, and each Connector returns writing-status.  write()
     * function will return a true value if all Connectors return
     * normal status, and a false value will be returned if at least
     * one Connector failed.  This function can be used to inspect
     * each return status
     *
     * @param index Connector index
     * @return Writing status
     *
     * @endif
     */
    DataPortStatus::Enum getStatus(int index)
    {
      return m_status[0];
    }
    /*!
     * @if jp
     *
     * @brief 特定のコネクタへの書き込みステータスリストを得る
     *
     * InPort は接続ごとに Connector と呼ばれる仮想データチャネルを持
     * つ。write() 関数はこれら Connector に対してデータを書き込むが、
     * 各 Connector は書き込みごとにステータスを返す。write() 関数では、
     * すべての Connector が正常終了したときのみ true を返し、それ以外
     * では false を返却する。この関数は write() が false の場合ステー
     * タスを調べるのに使用することができる。
     *
     * @return ステータスリスト
     *
     * @else
     *
     * @brief Getting specified connector's writing status list
     *
     * An InPort has Connectors that are virtual data stream channel
     * for each connection.  "write()" function write into these
     * Connectors, and each Connector returns writing-status.  write()
     * function will return a true value if all Connectors return
     * normal status, and a false value will be returned if at least
     * one Connector failed.  This function can be used to inspect
     * each return status
     *
     * @return Writing status list
     *
     * @endif
     */
    DataPortStatusList getStatusList()
    {
      return m_status;
    }    
    
    /*!
     * @if jp
     *
     * @brief InPort バッファへデータ読み込み時のコールバックの設定
     *
     * InPort が持つバッファからデータが読み込まれる直前に呼ばれるコールバック
     * オブジェクトを設定する。
     * 
     * @param on_read OnRead&lt;DataType&gt;型のオブジェクト
     *
     * @else
     *
     * @brief Set callback when data is read from the InPort buffer
     *
     * Set the callback object that is invoked right before data is read from 
     * the InPort's buffer
     * 
     * @param on_read OnRead&lt;DataType&gt; type object
     *
     * @endif
     */
    inline void setOnRead(OnRead<DataType>* on_read)
    {
      m_OnRead = on_read;
    }
    
    /*!
     * @if jp
     *
     * @brief InPort バッファへデータ読み出し時のコールバックの設定
     *
     * InPort が持つバッファからデータが読み出される際に呼ばれるコールバック
     * オブジェクトを設定する。コールバックオブジェクトの戻り値がread()メソッド
     * の呼出結果となる。
     * 
     * @param on_rconvert OnReadConvert&lt;DataType&gt;型のオブジェクト
     *
     * @else
     *
     * @brief Set callback when data is readout to the InPort buffer
     *
     * Set the callback object that is invoked when data is readout to
     * the InPort's buffer. The return value of callback object is the return
     * result of the read() method.
     * 
     * @param on_rconvert OnReadConvert&lt;DataType&gt; type object
     *
     * @endif
     */
    inline void setOnReadConvert(OnReadConvert<DataType>* on_rconvert)
    {
      m_OnReadConvert = on_rconvert;
    }
    
  private:
    std::string m_typename;
    /*!
     * @if jp
     * @brief ポート名
     * @else
     * @berif Port's name
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief バインドされる T 型の変数への参照
     * @else
     * @brief The reference to type-T value bound this OutPort
     * @endif
     */
    DataType& m_value;
    mutable coil::Mutex m_valueMutex;
    
    /*!
     * @if jp
     * @brief OnRead コールバックファンクタへのポインタ
     * @else
     * @brief Pointer to OnRead callback functor
     * @endif
     */
    OnRead<DataType>* m_OnRead;
    
    /*!
     * @if jp
     * @brief OnReadConvert コールバックファンクタへのポインタ
     * @else
     * @brief Pointer to OnReadConvert callback functor
     * @endif
     */
    OnReadConvert<DataType>* m_OnReadConvert;

    /*!
     * @if jp
     * @brief コネクタごとのリードステータス
     * @else
     * @brief Read status of each connector
     * @endif
     */
    DataPortStatusList m_status;

    /*!
     * @if jp
     * @brief ダイレクトデータ転送フラグ
     * @else
     * @brief A flag for direct data transfer
     * @endif
     */
    bool m_directNewData;
  };
}; // End of namesepace RTM

#endif // RTC_INPORT_H
