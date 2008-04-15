// -*- C++ -*-
/*!
 * @file PublisherBase.h
 * @brief Publisher base class
 * @date $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PublisherBase.h,v 1.1.4.2 2007-12-31 03:08:06 n-ando Exp $
 *
 */

#ifndef PublisherBase_h
#define PublisherBase_h

namespace RTC
{
  /*!
   * @if jp
   *
   * @class PublisherBase
   *
   * @brief Publisher ���쥯�饹
   * 
   * �ǡ������Х����ߥ󥰤�����������Ф��ư����Publisher* �δ��쥯�饹��
   * �Ƽ� Publisher �Ϥ��Υ��饹��Ѿ����ƾܺ٤�������롣
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class PublisherBase
   *
   * @brief Base class of Publisher.
   *
   * This is a base class of Publisher*. This class manages data send timing.
   * Variation of Publisher* which implements details of Publisher inherits
   * this PublisherBase class.
   *
   * @endif
   */
  class PublisherBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief ���Х����ߥ󥰤����Τ��롣
     *
     * ���Ф��Ԥĥ��֥������Ȥˡ����Х����ߥ󥰤����Τ��뤿��ν�貾�۴ؿ���
     * 
     * @else
     *
     * @brief Notify the data send timing
     *
     * Pure virtual function to notify the send timing to the object 
     * that waits for the send.
     * 
     * @endif
     */
    virtual void update() = 0;
    
    /*!
     * @if jp
     *
     * @brief �ǥ��ȥ饯��
     *
     * @else
     *
     * @brief Destructor
     *
     * @endif
     */
    virtual ~PublisherBase(){};
    
    /*!
     * @if jp
     *
     * @brief Publisher ���˴����롣
     *
     * ���� Publisher ���˴����롣
     * ���� Publisher �����פˤʤä����� PublisherFactory ����ƤӽФ���롣
     *
     * @else
     *
     * @brief Release the Publisher
     *
     * Release this Publisher.
     * When Publisher becomes unnecessary, this is invoked from
     * PublisherFactory. 
     *
     * @endif
     */
    virtual void release(){}
  };
};
#endif // PublisherBase_h
