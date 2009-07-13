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

    if (!appendInterface(instance_name, type_name, RTC::PROVIDED))
      {
	return false;
      }
    
    PortableServer::ObjectId_var oid = Manager::instance().getPOA()->servant_to_id(&provider);
    try
      {
        Manager::instance().getPOA()->activate_object_with_id(oid, &provider);
      }
    catch(const ::PortableServer::POA::ServantAlreadyActive &)
      {
	return false;
      }
    catch(const ::PortableServer::POA::ObjectAlreadyActive &)
      {
      }

    CORBA::Object_ptr obj;
    obj = Manager::instance().getPOA()->id_to_reference(oid);
    
    std::string key("port");
    key.append(".");key.append(type_name);
    key.append(".");key.append(instance_name);
    
    CORBA::ORB_ptr orb = Manager::instance().getORB();
    CORBA::String_var ior = orb->object_to_string(obj);
    CORBA_SeqUtil::
      push_back(m_providers, NVUtil::newNV(key.c_str(), ior));
    m_servants.insert(std::pair<std::string, ProviderInfo>(instance_name,ProviderInfo(&provider,oid)));
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
    ServantMap::iterator it = m_servants.begin();
    while(it != m_servants.end())
      {
        try
          {
            Manager::instance().getPOA()->activate_object_with_id(it->second.oid, it->second.servant);
          }
        catch(const ::PortableServer::POA::ServantAlreadyActive &)
          {
          }
        catch(const ::PortableServer::POA::ObjectAlreadyActive &)
          {
          }
	it++;
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
    ServantMap::iterator it = m_servants.begin();
    while(it != m_servants.end())
      {
        Manager::instance().getPOA()->deactivate_object(it->second.oid);
	it++;
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

    CORBA_SeqUtil::push_back_list(connector_profile.properties,
				  m_providers);
    RTC_DEBUG_STR((NVUtil::toString(m_providers)));

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
    
    RTC_DEBUG_STR((NVUtil::toString(nv)));

    CORBA::ORB_ptr orb = ::RTC::Manager::instance().getORB();

    for (int i(0), len(m_consumers.size()); i < len; ++i)
      {
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
