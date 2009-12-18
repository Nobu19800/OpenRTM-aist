// -*- C++ -*-
/*!
 * @file  CorbaPort.h
 * @brief CorbaPort class
 * @date  $Date: 2007-12-31 03:08:02 $
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
 * $Id$
 *
 */

#include <rtm/SystemLogger.h>
#include <rtm/CorbaPort.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/Manager.h>
#include <string>

namespace RTC
{
  /*!
   * @if jp
   * @brief ���󥹥ȥ饯��
   * @else
   * @brief Constructor
   * @endif
   */
  CorbaPort::CorbaPort(const char* name)
    : PortBase(name)
  {
    addProperty("port.port_type", "CorbaPort");
  }
  
  /*!
   * @if jp
   * @brief ���ۥǥ��ȥ饯��
   * @else
   * @brief Virtual destructor
   * @endif
   */
  CorbaPort::~CorbaPort()
  {
  }
  
  /*!
   * @if jp
   * @brief Provider ����Ͽ����
   * @else
   * @brief Register the provider
   * @endif
   */
  bool
  CorbaPort::registerProvider(const char* instance_name,
			      const char* type_name,
			      PortableServer::RefCountServantBase& provider)
  {
    RTC_TRACE(("registerProvider(instance=%s, type_name=%s)",
               instance_name, type_name));

    try
      {
        m_providers.push_back(CorbaProviderHolder(type_name,
                                                  instance_name,
                                                  &provider));
      }
    catch (...)
      {
        RTC_ERROR(("appending provider interface failed"));
        return false;
      }

    if (!appendInterface(instance_name, type_name, RTC::PROVIDED))
      {
        RTC_ERROR(("appending provider interface failed"));
	return false;
      }
    
    return true;
  };
  
  /*!
   * @if jp
   * @brief Consumer ����Ͽ����
   * @else
   * @brief Register the consumer
   * @endif
   */
  bool
  CorbaPort::registerConsumer(const char* instance_name,
			      const char* type_name,
			      CorbaConsumerBase& consumer)
  {
    RTC_TRACE(("registerConsumer()"));

    if (!appendInterface(instance_name, type_name, RTC::REQUIRED))
      {
	return false;
      }
    
    Consumer cons(instance_name, type_name, consumer);
    m_consumers.push_back(cons);
    
    return true;
  }

  //============================================================
  // Local operations
  //============================================================

  /*!
   * @if jp
   * @brief Port �����ƤΥ��󥿡��ե������� activates ����
   * @else
   * @brief Activate all Port interfaces
   * @endif
   */
  void CorbaPort::activateInterfaces()
  {
    CorbaProviderList::iterator it(m_providers.begin());
    while(it != m_providers.end())
      {
        it->activate();
	++it;
      }
  }
  
  /*!
   * @if jp
   * @brief ���Ƥ� Port �Υ��󥿡��ե������� deactivates ����
   * @else
   * @brief Deactivate all Port interfaces
   * @endif
   */
  void CorbaPort::deactivateInterfaces()
  {
    CorbaProviderList::iterator it(m_providers.begin());
    while(it != m_providers.end())
      {
        it->deactivate();
	++it;
      }
  }
  
  //============================================================
  // protected functions
  //============================================================
  /*!
   * @if jp
   * @brief Interface ������������
   * @else
   * @brief Publish interface information
   * @endif
   */
  ReturnCode_t
  CorbaPort::publishInterfaces(ConnectorProfile& connector_profile)
  {
    RTC_TRACE(("publishInterfaces()"));

    NVList properties;
    CorbaProviderList::iterator it(m_providers.begin());
    while (it != m_providers.end())
      {
        // new version descriptor
        // <comp_iname>.port.<port_name>.provider.<type_name>.<instance_name>
        std::string newdesc;
        newdesc = m_ownerInstanceName + ".port." + (const char*)m_profile.name
          + ".provider." + it->descriptor();
        CORBA_SeqUtil::
          push_back(properties,
                    NVUtil::newNV(newdesc.c_str(), it->ior().c_str()));

        // old version descriptor
        // port.<type_name>.<instance_name>
        std::string olddesc;
        olddesc += "port." + it->descriptor();
        CORBA_SeqUtil::
          push_back(properties,
                    NVUtil::newNV(olddesc.c_str(), it->ior().c_str()));
        ++it;
      }

    CORBA_SeqUtil::push_back_list(connector_profile.properties, properties);
    
    RTC_DEBUG_STR((NVUtil::toString(properties)));                         

    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interface ����³����
   * @else
   * @brief Subscribe to interfaces
   * @endif
   */
  ReturnCode_t
  CorbaPort::subscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    RTC_TRACE(("subscribeInterfaces()"));

    const NVList& nv(connector_profile.properties);
    std::cout << NVUtil::toString(nv) << std::endl;
    RTC_DEBUG_STR((NVUtil::toString(nv)));

    CORBA::ORB_ptr orb = ::RTC::Manager::instance().getORB();

    for (int i(0), len(m_consumers.size()); i < len; ++i)
      {
        std::cout << "find if: " << m_consumers[i].name << std::endl;
        CORBA::Long index;
        index = NVUtil::find_index(nv, m_consumers[i].name.c_str());
        if (index < 0) { continue; }

        const char* ior;
        if (!(nv[index].value >>= ior))
          {
            RTC_WARN(("Cannot extract IOR string"));
            continue;
          }

        CORBA::Object_var obj = orb->string_to_object(ior);
        if (CORBA::is_nil(obj))
          {
            RTC_ERROR(("Extracted object is nul reference"));
            continue;
          }
        
        bool result = m_consumers[i].consumer.setObject(obj.in());
        if (!result)
          {
            RTC_ERROR(("Cannot narrow reference"));
            continue;
          }
      }

    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interface �ؤ���³��������
   * @else
   * @brief Unsubscribe interfaces
   * @endif
   */
  void
  CorbaPort::unsubscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    RTC_TRACE(("unsubscribeInterfaces()"));

    const NVList& nv(connector_profile.properties);

    RTC_DEBUG_STR((NVUtil::toString(nv)));
    
    CORBA_SeqUtil::for_each(nv, unsubscribe(m_consumers));
  }
  
};
