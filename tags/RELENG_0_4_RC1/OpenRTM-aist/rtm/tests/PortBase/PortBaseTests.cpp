// -*- C++ -*-
/*!
 * @file   PortBaseTests.cpp
 * @brief  PortBase test class
 * @date   $Date: 2007-01-12 14:44:43 $
 * @author Shinji Kurihara
 *         Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortBaseTests.cpp,v 1.2 2007-01-12 14:44:43 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 08:35:12  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.2  2006/11/13 12:30:06  kurihara
 *
 * document is added.
 *
 * Revision 1.1  2006/11/08 01:19:07  kurihara
 *
 * test program for PortBase class.
 *
 */

#ifndef PortBase_cpp
#define PortBase_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <vector>
#include <string>
#include <rtm/PortBase.h>
#include <rtm/RTObject.h>

/*!
 * @class PortBaseTests class
 * @brief PortBase test
 */
namespace PortBase
{
  class PortBase
	: public RTC::PortBase
  {
  public:
	const std::string getUUID() const
	{
	  return RTC::PortBase::getUUID();
	}
  protected:
	virtual RTC::ReturnCode_t publishInterfaces(RTC::ConnectorProfile&)
	{
	  return RTC::OK;
	}
	virtual RTC::ReturnCode_t subscribeInterfaces(const RTC::ConnectorProfile&)
	{
	  return RTC::OK;
	}
	virtual void unsubscribeInterfaces(const RTC::ConnectorProfile&)
	{
	}
  };

  using namespace RTC;
  using namespace std;
  int g_argc;
  vector<string> g_argv;

  class PortBaseTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PortBaseTests);
    CPPUNIT_TEST(test_get_port_profile);
    CPPUNIT_TEST(test_get_connector_profiles);
    CPPUNIT_TEST(test_get_connector_profile);
    CPPUNIT_TEST(test_connect);
    CPPUNIT_TEST(test_disconnect);
    CPPUNIT_TEST(test_disconnect_all);
    //  CPPUNIT_TEST(test_setProfile);
    //  CPPUNIT_TEST(test_getProfile);
    //    CPPUNIT_TEST(test_setName);
    //    CPPUNIT_TEST(test_getName);
    //    CPPUNIT_TEST(test_setInterfaceProfiles);
    //  CPPUNIT_TEST(test_addInterfaceProfiles);
    //  CPPUNIT_TEST(test_getInterfaceProfiles);
    //  CPPUNIT_TEST(test_getInterfaceProfile);
    CPPUNIT_TEST(test_setPortRef);
    //  CPPUNIT_TEST(test_getPortRef);
    //  CPPUNIT_TEST(test_addConnectorProfile);
    //  CPPUNIT_TEST(test_eraseConnectorProfile);
    //  CPPUNIT_TEST(test_getConnectorProfileList);
    //  CPPUNIT_TEST(test_getConnectorProfile);
    CPPUNIT_TEST(test_setOwner);
    CPPUNIT_TEST(test_getOwner);
	//    CPPUNIT_TEST(test_setProperties);
	//    CPPUNIT_TEST(test_getProperties);
    CPPUNIT_TEST(test_getUUID);
    CPPUNIT_TEST_SUITE_END();
    
  private:
    PortBase* m_ppb;
    CORBA::ORB_ptr          m_orb;
    PortableServer::POA_ptr m_poa;
    
    SDOPackage::NVList m_nvlist;
    SDOPackage::NameValue m_nv;
    CORBA::Float m_cnctProfVal,m_portProfVal;
  public:
    
    /*!
     * @brief Constructor
     */
    PortBaseTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~PortBaseTests()
    {
    }
    
    /*!
     * @brief �����
     *    (1) ORB�ν����,POA��activate
     *    (2) PortBase�Υ��󥹥�������
     *    (3) PortInterfaceProfile���֥����������ǤΥ��å�
     *    (4) PortInterfaceProfileList���֥�����������
     *        (PortProfile������)�Υ��å�
     *    (5) ConnectorProfile���֥����������ǤΥ��å�
     *    (6) ConnectorProfileList���֥�����������(PortProfile������)�Υ��å�
     *    (7) PortProfile���֥����������ǤΥ��å�
     *    (8) PortProfile���֥������ȤΥ��å�
     */
    virtual void setUp()
    {
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }
      
      // (1) ORB�ν����,POA��activate
      m_orb = CORBA::ORB_init(g_argc, argv);
      CORBA::Object_var  obj = m_orb->resolve_initial_references("RootPOA");
      m_poa = PortableServer::POA::_narrow(obj);
      PortableServer::POAManager_var pman = m_poa->the_POAManager();
      pman->activate();
      
      // (2) PortBase�Υ��󥹥�������
      m_ppb = new PortBase();
      
      // (3) PortInterfaceProfile���֥�����������(PortProfile������)�Υ��å�
      PortInterfaceProfile pIProf;
      pIProf.instance_name = "PortInterfaceProfile-instance_name";
      pIProf.type_name = "PortInterfaceProfile-type_name";
      pIProf.polarity = REQUIRED;
      
      // (4) PortInterfaceProfileList���֥����������ǤΥ��å�
      PortInterfaceProfileList pIFProfList;
      pIFProfList.length(1);
      pIFProfList[0] = pIProf;
      
      // (5) ConnectorProfile���֥����������ǤΥ��å�
      ConnectorProfile cProf;
      cProf.name = "ConnectorProfile-name";
      cProf.connector_id = "connect_id0";
      m_nv.name = "ConnectorProfile-properties0-name";
      m_cnctProfVal = 1.1;
      m_nv.value <<= m_cnctProfVal;
      m_nvlist.length(1);
      m_nvlist[0] = m_nv;
      cProf.properties = m_nvlist;
      
      // (6) ConnectorProfileList���֥�����������(PortProfile������)�Υ��å�
      ConnectorProfileList cProfList;
      cProfList.length(1);
      cProfList[0] = cProf;
      
      // (7) PortProfile���֥����������ǤΥ��å�
      PortProfile pProf;
      pProf.name = "inport0";
      pProf.interfaces = pIFProfList;
      pProf.connector_profiles = cProfList;
      m_nv.name = "PortProfile-properties0-name";
      m_portProfVal = 2.2;
      m_nv.value <<= m_portProfVal;
      m_nvlist[0] = m_nv;
      pProf.properties = m_nvlist;
      
      // (8) PortProfile���֥������ȤΥ��å�
      //### m_ppb->setProfile(pProf);
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
    
    /*!
     * @brief get_port_profile()�Υƥ���
     *    �� PortProfile��setUp()����Ͽ�ѤߤǤ��롣
     *    (1) get_port_profile()�ˤ�PortProfile*�����
     *    (2) ���åȤ���PortProfile�ȼ�������PortProfile�����Ǥ����
     */
    void test_get_port_profile() {
      PortProfile* getProf;
      
      // (1) get_port_profile()�ˤ�PortProfile*�����
      getProf = m_ppb->get_port_profile();
      
      string setstr, getstr;
      // (2) ���åȤ���PortProfile�ȼ�������PortProfile�����Ǥ����
      // check PortProfile.name
      getstr = getProf->name;
      setstr = "inport0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check PortProfile.interfaces
      getstr = getProf->interfaces[0].instance_name;
      setstr = "PortInterfaceProfile-instance_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf->interfaces[0].type_name;
      setstr = "PortInterfaceProfile-type_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CPPUNIT_ASSERT(getProf->interfaces[0].polarity == REQUIRED);
      
      // check PortProfile.connector_profiles
      getstr = getProf->connector_profiles[0].name;
      setstr = "ConnectorProfile-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf->connector_profiles[0].connector_id;
      setstr = "connect_id0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf->connector_profiles[0].properties[0].name;
      setstr = "ConnectorProfile-properties0-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CORBA::Float retval;
      getProf->connector_profiles[0].properties[0].value >>= retval;
      CPPUNIT_ASSERT(retval == m_cnctProfVal);
      
      // check PortProfile.properties
      getstr = getProf->properties[0].name;
      setstr = "PortProfile-properties0-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getProf->properties[0].value >>= retval;
      CPPUNIT_ASSERT(retval == m_portProfVal);
    }
    
    
    /*!
     * @brief get_connector_profiles()�Υƥ���
     *    �� ConnectorProfileList��PortProfile�����ǤǤ��ꡢ
     *       setUp()����Ͽ�ѤߤǤ��롣
     *    (1��get_connector_profiles()�ˤ�ConnectorProfileList�����
     *    (2) ���åȤ���ConnectorProfile�ȼ�������ConnectorProfileList��
     *        ���ǤǤ���ConnectorProfile�����Ǥ���ӡ�
     */
    void test_get_connector_profiles() {
      ConnectorProfileList* cpList;
      string setstr, getstr;
      
      // get ConnectorProfileList
      cpList = m_ppb->get_connector_profiles();
      
      // (2) ���åȤ���ConnectorProfile�ȼ�������ConnectorProfileList��
      //     ���ǤǤ���
      //      ConnectorProfile�����Ǥ���ӡ�
      // check ConnectorProfile.name
      setstr = "ConnectorProfile-name";
      getstr = (*cpList)[0].name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.connector_id
      setstr = "connect_id0";
      getstr = (*cpList)[0].connector_id;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.properties.name
      setstr = "ConnectorProfile-properties0-name";
      getstr = (*cpList)[0].properties[0].name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.properties.value
      CORBA::Float retval;
      (*cpList)[0].properties[0].value >>= retval;
      CPPUNIT_ASSERT(m_cnctProfVal == retval);
    }
    
    
    /*!
     * @brief get_connector_profile()�Υƥ���
     *    �� ConnectorProfile��ConnectorProfileList�����ǤǤ��ꡢ
     *       ConnectorProfileList��PortProfile�����ǤǤ��롣
     *       PortProfile��setUp()����Ͽ�ѤߤǤ��롣
     *    (1) get_connector_profile�ˤ�ConnectorProfile�������
     *    (2) ���åȤ���ConnectorProfile�ȼ�������ConnectorProfile����ӡ�
     */
    void test_get_connector_profile() {
      ConnectorProfile* cProf;
      string setstr, getstr;
      
      // (1) get_connector_profile�ˤ�ConnectorProfile�������
      cProf = m_ppb->get_connector_profile("connect_id0");
      
      // ���åȤ���ConnectorProfile�ȼ�������ConnectorProfile����ӡ�
      // check ConnectorProfile.name
      setstr = "ConnectorProfile-name";
      getstr = cProf->name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.connector_id
      setstr = "connect_id0";
      getstr = cProf->connector_id;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.properties.name
      setstr = "ConnectorProfile-properties0-name";
      getstr = cProf->properties[0].name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.properties.value
      CORBA::Float retval;
      cProf->properties[0].value >>= retval;
      CPPUNIT_ASSERT(m_cnctProfVal == retval);
      
      ReturnCode_t result;
      
      result = m_ppb->connect(*cProf);
      
      if (result == OK)
	cout << "connect result OK. " << endl;
      else if (result == ERROR)
	cout << "connect result ERROR. " << endl;
      else if (result == BAD_PARAMETER)
	cout << "connect result BAD_PARAMETER. " << endl;
      else if (result == UNSUPPORTED)
	cout << "connect result UNSUPPORTED. " << endl;
      else if (result == OUT_OF_RESOURCES)
	cout << "connect result OUT_OF_RESOURCES. " << endl;
      else if (result == PRECONDITION_NOT_MET)
	cout << "connect result PRECONDITION_NOT_MET. " << endl;
    }
    
    
    /*!
     * @brief connect()�Υƥ���
     *   ̤�ƥ���
     */
    void test_connect() {}
    
    
    /*!
     * @brief disconnect()�Υƥ���
     *   ̤�ƥ���
     */
    void test_disconnect() {}
    
    
    /*!
     * @brief disconnect_all()�Υƥ���
     *   ̤�ƥ���
     */
    void test_disconnect_all() {}
    
    
    /*!
     * @brief setProfile()�Υƥ���
     *   test_get_port_profile() �ˤƥƥ��ȺѤ�
     */
    void test_setProfile() {}
    
    
    /*!
     * @brief getProfile()�Υƥ���
     *   �� PortProfile��setUp()����Ͽ�ѤߤǤ��롣
     *   (1) getProfile()�ˤ�PortProfile�������
     *   (2) ���åȤ���PortProfile�ȼ�����������Ȥ����Ǥ���ӡ�
     */
    /*
    void test_getProfile() {
      PortProfile getProf;
      
      // (1) getProfile()�ˤ�PortProfile�������
      // ### getProf = m_ppb->getProfile();
      
      string setstr, getstr;
      
      // (2) ���åȤ���PortProfile�ȼ�����������Ȥ����Ǥ���ӡ�
      // check PortProfile.name
      getstr = getProf.name;
      setstr = "inport0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check PortProfile.interfaces
      getstr = getProf.interfaces[0].instance_name;
      setstr = "PortInterfaceProfile-instance_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.interfaces[0].type_name;
      setstr = "PortInterfaceProfile-type_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CPPUNIT_ASSERT(getProf.interfaces[0].polarity == REQUIRED);
      
      // check PortProfile.connector_profiles
      getstr = getProf.connector_profiles[0].name;
      setstr = "ConnectorProfile-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.connector_profiles[0].connector_id;
      setstr = "connect_id0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.connector_profiles[0].properties[0].name;
      setstr = "ConnectorProfile-properties0-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CORBA::Float retval;
      getProf.connector_profiles[0].properties[0].value >>= retval;
      CPPUNIT_ASSERT(retval == m_cnctProfVal);
      
      // check PortProfile.properties
      getstr = getProf.properties[0].name;
      setstr = "PortProfile-properties0-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getProf.properties[0].value >>= retval;
      CPPUNIT_ASSERT(retval == m_portProfVal);
    }
    */
    
    /*!
     * @brief setName()�Υƥ���
     *   �� PortProfile��setUp()�ˤ���Ͽ�ѤߤǤ��롣
     *   (1) setName()�ˤ�PortProfile.name�򥻥åȡ�
     *   (2) getProfile()�ˤ�PortProfile�������
     *   (3) (1)�ǥ��åȤ���name��(2)�Ǽ�������PortProfile.name����ӡ�
     */
    /*
    void test_setName() {
      // (1) setName()�ˤ�PortProfile.name�򥻥åȡ�
      m_ppb->setName("inport0-changed");
      
      PortProfile getProf;
      
      // (2) getProfile()�ˤ�PortProfile�������
      getProf = m_ppb->getProfile();
      
      string setstr, getstr;
      
      // (3) (1)�ǥ��åȤ���name��(2)�Ǽ�������PortProfile.name����ӡ�
      getstr = getProf.name;
      setstr = "inport0-changed";
      CPPUNIT_ASSERT(getstr == setstr);
    }
    */
    
    /*!
     * @brief  getName()�Υƥ���
     *   �� PortProfile��setUp()�ˤ���Ͽ�ѤߤǤ��롣
     *   (1) geName()�ˤ�PortProfile.name�������
     *   (2) ���åȺѤߤ�PortProfile.name��(1)�Ǽ�������name����ӡ�
     */
    /*
    void test_getName() {
      // (1) geName()�ˤ�PortProfile.name�������
      const char* retval(m_ppb->getName());
      
      string setname, getname;
      
      // (2) ���åȺѤߤ�PortProfile.name��(1)�Ǽ�������name����ӡ�
      setname = "inport0";
      getname = retval;
      CPPUNIT_ASSERT(getname == setname);
    }
    */
    
    /*!
     * @brief setInterfaceProfiles()�Υƥ���
     *   (1) PortInterfaceProfile���֥����������ǤΥ��åȡ�
     *   (2) (1)�ǥ��åȤ���PortInterfaceProfile��PortInterfaceProfileList��
     *       ���åȡ�
     *   (3��setInterfaceProfiles()�ˤ�PortInterfaceProfileList�򥻥åȡ�
     *   (4) getInterfaceProfiles()�ˤ�PortInterfaceProfileList�������
     *   (5) (3)�ǥ��åȤ���PortInterfaceProfileList�����Ǥȡ�
     *       (4)�Ǽ�����������Ȥ���ӡ�
     *   (6) addInterfaceProfile()�ˤ�PortInterfaceProfile���ɲá�
     *   (7) getInterfaceProfiles()�ˤ�PortInterfaceProfileList�������
     *   (8) (6)���ɲä���PortInterfaceProfileList�����Ǥȡ�
     *       (7)�Ǽ�����������Ȥ���ӡ�
     *   (9) getInterfaceProfile(name)�ˤ�PortInterfaceProfile�������
     *   (10) (6)���ɲä���PortInterfaceProfileList�����Ǥȡ�
     *        (9)�Ǽ�����������Ȥ���ӡ�
     */
    /*
    void test_setInterfaceProfiles() {
      // (1) PortInterfaceProfile���֥����������ǤΥ��åȡ�
      PortInterfaceProfile pIProf;
      pIProf.instance_name = "PortInterfaceProfile-instance_name-changed";
      pIProf.type_name = "PortInterfaceProfile-type_name-changed";
      pIProf.polarity = REQUIRED;
      
      
      // (2) (1)�ǥ��åȤ���PortInterfaceProfile��PortInterfaceProfileList
      // �˥��åȡ�
      PortInterfaceProfileList pIFProfList;
      pIFProfList.length(1);
      pIFProfList[0] = pIProf;
      
      
      // (3��setInterfaceProfiles()�ˤ�PortInterfaceProfileList�򥻥åȡ�
      m_ppb->setInterfaceProfiles(pIFProfList);
      
      
      // (4) getInterfaceProfiles()�ˤ�PortInterfaceProfileList�������
      PortInterfaceProfileList getList;
      getList = m_ppb->getInterfaceProfiles();
      
      
      // (5) (3)�ǥ��åȤ���PortInterfaceProfileList�����Ǥȡ�
      // (4)�Ǽ�����������Ȥ���ӡ�
      string getstr, setstr;
      getstr = getList[0].instance_name;
      setstr = "PortInterfaceProfile-instance_name-changed";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getList[0].type_name;
      setstr = "PortInterfaceProfile-type_name-changed";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CPPUNIT_ASSERT(getList[0].polarity == REQUIRED);
      
      
      // (6) addInterfaceProfile()�ˤ�PortInterfaceProfile���ɲá�
      pIProf.instance_name = "PortInterfaceProfile-instance_name-add";
      pIProf.type_name = "PortInterfaceProfile-type_name-add";
      pIProf.polarity = PROVIDED;
      m_ppb->addInterfaceProfile(pIProf);
      
      
      // (7) getInterfaceProfiles()�ˤ�PortInterfaceProfileList�������
      getList = m_ppb->getInterfaceProfiles();
      
      
      // (8) (6)���ɲä���PortInterfaceProfileList�����Ǥȡ�
      // (7)�Ǽ�����������Ȥ���ӡ�
      getstr = getList[1].instance_name;
      setstr = "PortInterfaceProfile-instance_name-add";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getList[1].type_name;
      setstr = "PortInterfaceProfile-type_name-add";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CPPUNIT_ASSERT(getList[1].polarity == PROVIDED);
      
      
      // (9) getInterfaceProfile(name)�ˤ�PortInterfaceProfile�������
      PortInterfaceProfile getProf;
      getProf = m_ppb->getInterfaceProfile("PortInterfaceProfile-instance_name-add");
      
      // (10) (6)���ɲä���PortInterfaceProfileList�����Ǥȡ�(9)�Ǽ�����������Ȥ���ӡ�
      getstr = getProf.instance_name;
      setstr = "PortInterfaceProfile-instance_name-add";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.type_name;
      setstr = "PortInterfaceProfile-type_name-add";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CPPUNIT_ASSERT(getProf.polarity == PROVIDED);
    }
    */
    /*!
     * @brief addInterfaceProfiles()�Υƥ���
     *   test_setInterfaceProfiles()�ˤƥƥ��ȺѤߡ�
     */
    void test_addInterfaceProfiles() {}
    
    
    /*!
     * @brief getInterfaceProfiles()�Υƥ���
     *   test_setInterfaceProfiles()�ˤƥƥ��ȺѤߡ�
     */
    void test_getInterfaceProfiles() {}
    
    
    /*!
     * @brief getInterfaceProfile()�Υƥ���
     *   test_setInterfaceProfiles()�ˤƥƥ��ȺѤߡ�
     */
    void test_getInterfaceProfile() {}
    
    
    
    /*!
     * @brief  setPortRef()�Υƥ���
     *   �� PortProfile��setUp()�ˤ���Ͽ�Ѥߡ�
     *   (1) setPortRef()�ˤ�PortBase���֥������Ȥλ��Ȥ򥻥åȡ�
     *   (2) getPortRef()�ˤ�Port���󥿥ե������Υ��֥������Ȼ��Ȥ������
     *   (3) (2)�Ǽ����������֥������Ȼ��Ȥ��Ѥ�Port���󥿥ե�������
     *       ���ڥ졼�����ƤӽФ��ƥ��ȡ�
     *   (4) (3)�Υ��ڥ졼�����ƤӽФ��ˤƼ�������PortProfile�����Ǥ�
     *       setUp()�ǥ��åȤ�������Ȥ���ӡ�
     */
    void test_setPortRef() {
      Port_var port = m_ppb->_this();
      m_ppb->_remove_ref();
      
      // (1) setPortRef()�ˤ�PortBase���֥������Ȥλ��Ȥ򥻥åȡ�
      m_ppb->setPortRef(port._retn());
      
      
      // (2) getPortRef()�ˤ�Port���󥿥ե������Υ��֥������Ȼ��Ȥ������
      Port_ptr getP;
      PortProfile* pProf;
      getP = m_ppb->getPortRef();
      
      
      // (3) (2)�Ǽ����������֥������Ȼ��Ȥ��Ѥ�Port���󥿥ե������Υ��ڥ졼�����ƤӽФ��ƥ��ȡ�
      pProf = getP->get_port_profile();
      
      
      // (4) (3)�Υ��ڥ졼�����ƤӽФ��ˤƼ�������PortProfile�����Ǥ�setUp()��
      //     ���åȤ�������Ȥ���ӡ�
      string setstr, getstr;
      getstr = pProf->name;
      setstr = "inport0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = pProf->interfaces[0].instance_name;
      setstr = "PortInterfaceProfile-instance_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = pProf->interfaces[0].type_name;
      setstr = "PortInterfaceProfile-type_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CORBA::Float getval;
      pProf->properties[0].value >>= getval;
      CPPUNIT_ASSERT(m_portProfVal == getval);
      
      getstr = pProf->properties[0].name;
      setstr = "PortProfile-properties0-name";
      CPPUNIT_ASSERT(getstr == setstr);
    }
    
    
    /*!
     * @brief getPortRef�Υƥ���
     *   test_setPortRef()�ˤƥƥ��ȺѤߡ�
     */
    void test_getPortRef() {}
    
    
    /*!
     * @brief addConnectorProfile()�Υƥ���
     *   �� PortProfile��setUp()����Ͽ�Ѥߡ�
     *   (1) ConnectorProfile���֥����������ǤΥ��å�
     *   (2) (1)�ǥ��åȤ���ConnectorProfile��addConnectorProfile()�ˤ��ɲá�
     *   (3��ConnectorProfileList�μ�����
     *   (4) (2)���ɲä���ConnectorProfile��(3)�Ǽ�����������Ȥ���ӡ�
     *   (5) eraseConnectorProfile(id)�ˤ�,�����ǻ��ꤷ��id�����
     *       ConnectorProfile��ConnectorProfileList���������롣
     *   (6) (5)�Ǻ�����ConnectorProfileList�����
     *   (7) (6)�Ǽ�������ConnectorProfileList�����Ǥ��ǧ��
     */
    /*
    void test_addConnectorProfile() {
      // (1) ConnectorProfile���֥����������ǤΥ��å�
      ConnectorProfile cProf,getProf;
      cProf.name = "ConnectorProfile-name-add";
      cProf.connector_id = "connect_id0-add";
      
      SDOPackage::NameValue nv;
      NVList nvlist;
      CORBA::Double db, retdb;
      nv.name = "ConnectorProfile-properties0-name-add";
      db = 9999999.999;
      nv.value <<= db;
      nvlist.length(1);
      nvlist[0] = nv;
      cProf.properties = nvlist;
      
      
      // (2) (1)�ǥ��åȤ���ConnectorProfile��addConnectorProfile()�ˤ��ɲá�
      m_ppb->addConnectorProfile(cProf);
      
      
      // (3��ConnectorProfileList�μ�����
      ConnectorProfileList cnctPList;
      cnctPList = m_ppb->getConnectorProfileList();
      
      
      // (4) (2)���ɲä���ConnectorProfile��(3)�Ǽ�����������Ȥ���ӡ�
      string setstr, getstr;
      getstr = cnctPList[1].name;
      setstr = cProf.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = cnctPList[1].connector_id;
      setstr = cProf.connector_id;
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = cnctPList[1].properties[0].name;
      setstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      cnctPList[1].properties[0].value >>= retdb;
      CPPUNIT_ASSERT(retdb == db);
      
      
      // (5) eraseConnectorProfile(id)�ˤ�,�����ǻ��ꤷ��id�����
      //     ConnectorProfile��ConnectorProfileList���������롣
      // test eraseConnectorProfile()
      // Failure case: ��Ͽ���Ƥ��ʤ�ID��eraseConnectorProfile()��
      // �Ƥ֤ȥ��ܡ��Ȥ��롣
      //    m_ppb->eraseConnectorProfile("hoge");
      m_ppb->eraseConnectorProfile("connect_id0");
      
      
      // (6) (5)�Ǻ�����ConnectorProfileList�������
      getProf = m_ppb->getConnectorProfile("connect_id0-add");
      
      
      // (7) (6)�Ǽ�������ConnectorProfileList�����Ǥ��ǧ��
      getstr = getProf.name;
      setstr = getProf.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.connector_id;
      setstr = getProf.connector_id;
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.properties[0].name;
      setstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      getProf.properties[0].value >>= retdb;
      CPPUNIT_ASSERT(retdb == db);
    }
    */
    
    /*!
     * @brief  eraseConnectorProfile()�Υƥ���
     *   test_addConnectorProfileList()�ˤƥƥ��ȺѤߡ�
     */
    void test_eraseConnectorProfile() {}
    
    
    /*!
     * @brief getConnectorProfileList()�Υƥ���
     *   test_addConnectorProfileList()�ˤƥƥ��ȺѤߡ�
     */
    void test_getConnectorProfileList() {}
    
    
    /*!
     * @brief getConnectorProfile()�Υƥ���
     *   test_addConnectorProfileList()�ˤƥƥ��ȺѤߡ�
     */
    void test_getConnectorProfile() {}
    
    
    /*!
     * @brief setOwner()
     *   RTObject���󥿥ե������μ�������λ���Ƥ��ʤ���
     */
    void test_setOwner() {
      /*
	RTObject_impl* rtobj;
	
	rtobj = new RTObject_impl(m_orb, m_poa);
	
	RTObject_var p_rtobj = rtobj->_this();
	rtobj->_remove_ref();
	
	// check setOwner()
	m_ppb->setOwner(p_rtobj._retn());
      */
      
    }
    
    /*!
     * @brief getOwner()�Υƥ���
     */
    void test_getOwner() {}
    
    
    /*!
     * @brief setProperties()�Υƥ���
     *   �� PortProfile��setUp()����Ͽ�ѤߤǤ��롣
     *   (1) getProperties()�ˤ�PortProfile.property�������
     *   (2) (1)�Ǽ�������property�����Ǥ�setUp()�ǥ��åȤ�������Ȥ���ӡ�
     *   (3) setProperties()�ˤ�PortProfile.property�򥻥å�
     *   (4) getProperties()�ˤ�PortProfile.property�������
     *   (5) (3)�ǥ��åȤ���PortProfile.property��(4)�Ǽ�����������Ȥ���ӡ�
     */
	/*
    void test_setProperties() {
      NVList setlist, getlist;
      SDOPackage::NameValue nv;
      
      // (1) getProperties()�ˤ�PortProfile.property�������
      getlist = m_ppb->getProperties();
      
      
      // (2) (1)�Ǽ�������property�����Ǥ�setUp()�ǥ��åȤ�������Ȥ���ӡ�
      string getstr, setstr;
      CORBA::Float setval, retval;
      getlist[0].value >>= retval;
      
      getstr = getlist[0].name;
      setstr = m_nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      CPPUNIT_ASSERT(retval == m_portProfVal);
      
      
      // (3) setProperties()�ˤ�PortProfile.property�򥻥å�
      nv.name = "setProperties test";
      setval = 999.9;
      nv.value <<= setval;
      
      setlist.length(1);
      setlist[0] = nv;
      m_ppb->setProperties(setlist);
      
      
      // (4) getProperties()�ˤ�PortProfile.property�������
      getlist = m_ppb->getProperties();
      
      
      // (5) (3)�ǥ��åȤ���PortProfile.property��(4)�Ǽ�����������Ȥ���ӡ�
      getlist[0].value >>= retval;
      
      getstr = getlist[0].name;
      setstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      CPPUNIT_ASSERT(retval == setval);
      
    }
    */
    
    /*!
     * @brief getProperties()�Υƥ���
     *   test_setProperties�ˤƥƥ��ȺѤߡ�
     */
	/*
    void test_getProperties() {}
    */
    
    /*!
     * @brief  getUUID()�Υƥ���
     *   (1) getUUID()�ˤ�UUID�μ�����
     *   (2) ��������UUID��ɸ����Ϥ˽��ϡ�
     */
    void test_getUUID() {
      // (1) getUUID()�ˤ�UUID�μ�����
      string getuuid = m_ppb->getUUID();
      
      // (2) ��������UUID��ɸ����Ϥ˽��ϡ�
      cout << endl << "uuid: " << getuuid << endl;
    }
    
  };
}; // namespace PortBase

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PortBase::PortBaseTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  CppUnit::Outputter* outputter = 
    new CppUnit::TextOutputter(&runner.result(), std::cout);
  runner.setOutputter(outputter);
  bool retcode = runner.run();
  return !retcode;
}
#endif // MAIN
#endif // PortBase_cpp
