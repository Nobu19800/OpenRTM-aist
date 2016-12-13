// -*- C++ -*-
/*!
 * @file DataFlowComponentImpl.h
 * @brief DataFlowComponentImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <DataFlowComponentImpl.h>
#include <iostream>
#include <string>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{
  /*!
   * @if jp
   * @class DataFlowComponentImpl
   * @brief DataFlowComponentServant��ѥ���ץ���ȥ��饹
   * @else
   * @class DataFlowComponentImpl
   * @brief DataFlowComponent implementation class for DataFlowComponentServant' unittest.
   * @endif
   */
   int DataFlowComponentImpl::count = 0;

    DataFlowComponentImpl::DataFlowComponentImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    DataFlowComponentImpl::DataFlowComponentImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    DataFlowComponentImpl::~DataFlowComponentImpl()
    {
    }




}; // namespace Local 
}; // namespace SDOPackage 
