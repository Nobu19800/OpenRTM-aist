// -*- C++ -*-
/*!
 * @file DirectInPortBase.h
 * @brief DirectInPortBase class
 * @date $Date: 2018-1-23 03:08:05 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2018
 *     Nobuhiko Miyamoto
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 *
 */

#ifndef RTC_DIRECTINPORTBASE_H
#define RTC_DIRECTINPORTBASE_H



#include <coil/Mutex.h>
#include <rtm/DirectPortBase.h>



namespace RTC
{
	/*!
	* @if jp
	* @class DirectInPortBase
	* @brief direct��³��InPort���쥯�饹
	*
	*
	* @since 1.2.0
	*
	* @else
	* @class DirectOutPortBase
	* @brief
	*
	*
	*
	* @since 1.2.0
	*
	* @endif
	*/
  template <class DataType>
  class DirectInPortBase : public DirectPortBase
  {
  public:
	  /*!
	  * @if jp
	  * @brief ���󥹥ȥ饯��
	  *
	  * @param value
	  *
	  * @else
	  * @brief Constructor
	  *
	  * @param value
	  *
	  * @endif
	  */
    DirectInPortBase(DataType& value)
    {
    }
    
	/*!
	* @if jp
	* @brief �ǥ��ȥ饯��
	*
	*
	* @else
	* @brief Destructor
	*
	*
	* @endif
	*/
    virtual ~DirectInPortBase(void){};



    
    /*!
     * @if jp
     *
     * @brief �ǿ��ǡ�����¸�ߤ��뤫��ǧ����
     * 
     * InPort��̤�ɤκǿ��ǡ��������夷�Ƥ��뤫��bool�ͤ��֤���
     * InPort��̤��³�ξ�硢�������³���ͥ����ΥХåե���Empty
     * �ξ��ˤ�false���֤���
     *
     * @return true ̤�ɤκǿ��ǡ�����¸�ߤ���
     *         false ̤��³�ޤ��ϥХåե��˥ǡ�����¸�ߤ��ʤ���
     * 
     * @else
     *
     * @brief Check whether the data is newest
     * 
     * Check whether the data stored at a current buffer position is newest.
     *
     * @return Newest data check result
     *         ( true:Newest data. Data has not been readout yet.
     *          false:Past data��Data has already been readout.)
     * 
     * @endif
     */
    virtual bool isNew()
    {
		return false;
    }

    /*!
     * @if jp
     *
     * @brief �Хåե��������ɤ�����ǧ����
     * 
     * InPort�ΥХåե��������ɤ����� bool �ͤ��֤���
     * ���ξ��� true, ̤�ɥǡ������������ false ���֤���
     *
     * @return true  �Хåե��϶�
     *         false �Хåե���̤�ɥǡ���������
     * 
     * @else
     *
     * @brief Check whether the data is newest
     * 
     * Check whether the data stored at a current buffer position is newest.
     *
     * @return Newest data check result
     *         ( true:Newest data. Data has not been readout yet.
     *          false:Past data��Data has already been readout.)
     * 
     * @endif
     */
    virtual bool isEmpty()
    {
		return true;
    }

	/*!
	* @if jp
	* @brief �ǡ����ν񤭹���
	*
	* @param data �ǡ���
	*
	* @else
	* @brief
	*
	* @param data
	*
	* @endif
	*/
    virtual void write(const DataType& data)
    {
    }


  protected:
    

  };
}; // End of namesepace RTM

#endif // RTC_DIRECTINPORTBASE_H
