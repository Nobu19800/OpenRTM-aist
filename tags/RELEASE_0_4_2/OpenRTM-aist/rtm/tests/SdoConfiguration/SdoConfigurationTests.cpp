// -*- C++ -*-
/*!
 * @file   SdoConfigurationTests.cpp
 * @brief  SdoConfiguration test class
 * @date   $Date: 2007-01-24 16:04:18 $
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
 * $Id$
 *
 */

#ifndef SdoConfiguration_cpp
#define SdoConfiguration_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <vector>
#include <string>

#include <rtm/SdoConfiguration.h>

/*!
 * @class SdoConfigurationTests class
 * @brief SdoConfiguration test
 */
namespace SdoConfiguration
{
  using namespace SDOPackage;
  using namespace std;

  int g_argc;
  vector<string> g_argv;

  class SdoConfigurationTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SdoConfigurationTests);
    CPPUNIT_TEST(test_set_device_profile);
    CPPUNIT_TEST(test_set_service_profile);
    CPPUNIT_TEST(test_add_organization);
    CPPUNIT_TEST(test_remove_service_profile);
    CPPUNIT_TEST(test_remove_organization);
    CPPUNIT_TEST(test_get_configuration_parameters);
    //  CPPUNIT_TEST(test_get_configuration_parameter_values);
    //  CPPUNIT_TEST(test_get_configuration_parameter_value);
    //  CPPUNIT_TEST(test_set_configuration_parameter);
    CPPUNIT_TEST(test_get_configuration_sets);
    //  CPPUNIT_TEST(test_get_configuration_set);
    //  CPPUNIT_TEST(test_set_configuration_set_values);
    //  CPPUNIT_TEST(test_get_active_configuration_set);
    //  CPPUNIT_TEST(test_add_configuration_set);
    //  CPPUNIT_TEST(test_remove_configuration_set);
    //  CPPUNIT_TEST(test_activate_configuration_set);
    //  CPPUNIT_TEST(test_getDeviceProfile);
    //  CPPUNIT_TEST(test_getServiceProfiles);
    //  CPPUNIT_TEST(test_getServiceProfile);
    //  CPPUNIT_TEST(test_getOrganizations);
    CPPUNIT_TEST_SUITE_END();
    
  private:
    Configuration_impl* m_pConf;
    CORBA::ORB_ptr          m_orb;
    PortableServer::POA_ptr m_poa;
    
  public:
    
    /*!
     * @brief Constructor
     */
    SdoConfigurationTests()
    {
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }
      
      m_orb = CORBA::ORB_init(g_argc, argv);
      CORBA::Object_var  obj = m_orb->resolve_initial_references("RootPOA");
      m_poa = PortableServer::POA::_narrow(obj);
    }
    
    /*!
     * @brief Destructor
     */
    ~SdoConfigurationTests()
    {
    }
    
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      // Configuration_impl���饹�Υ��󥹥�������
      m_pConf = new Configuration_impl();
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
      delete m_pConf;
    }
    
    /*
     * @brief set_device_profile(),getDeviceProfile()�Υƥ���
     *    set_device_profile()�ˤ�DeviceProfile�򥻥åȸ�,
     *    getDeviceProfile()��DeviceProfile
     *    ����������åȤ���DeviceProfile�ȼ�������DeviceProfile����Ӥ�Ԥ���
     */
    void test_set_device_profile() {
      
      CORBA::Short st, retst;
      CORBA::Long  lg, retlg;
      CORBA::Float ft, retft;
      NVList nlist;
      
      // DeviceProfile.properties���ǤΥ��å�
      nlist.length(3);
      st = 10;
      nlist[0].name = "short data";
      nlist[0].value <<= st;
      
      lg = 100000;
      nlist[1].name = "long data";
      nlist[1].value <<= lg;
      
      ft = 1234.5;
      nlist[2].name = "float data";
      nlist[2].value <<= ft;
      
      // DeviceProfile���ǤΥ��å�
      DeviceProfile setProf, retProf;
      setProf.device_type = "Joystick";
      setProf.manufacturer = "Aist";
      setProf.model = "hoge";
      setProf.version = "0.4.0";
      setProf.properties = nlist;
      
      CORBA::Boolean result;
      
      // DeviceProfile�Υ��å�
      result = m_pConf->set_device_profile(setProf);
      if (!result)
	cout << "Error: set_device_profile()" << endl;
      
      
      // DeviceProfile�μ���
      retProf = m_pConf->getDeviceProfile();
      string setval, retval;
      
      // ���åȤ���DeviceProfile�����Ǥȼ�������DeviceProfile�����Ǥ���ӡ�
      setval = setProf.device_type;
      retval = retProf.device_type;
      CPPUNIT_ASSERT(retval == setval);
      
      setval = setProf.manufacturer;
      retval = retProf.manufacturer;
      CPPUNIT_ASSERT(retval == setval);
      
      setval = setProf.model;
      retval = retProf.model;
      CPPUNIT_ASSERT(retval == setval);
      
      setval = setProf.version;
      retval = retProf.version;
      CPPUNIT_ASSERT(retval == setval);
      
      setval = nlist[0].name;
      retval = retProf.properties[0].name;
      CPPUNIT_ASSERT(retval == setval);
      (retProf.properties[0].value) >>= retst;
      CPPUNIT_ASSERT(retst == st);
      
      setval = nlist[1].name;
      retval = retProf.properties[1].name;
      CPPUNIT_ASSERT(retval == setval);
      (retProf.properties[1].value) >>= retlg;
      CPPUNIT_ASSERT(retlg == lg);
      
      setval = nlist[2].name;
      retval = retProf.properties[2].name;
      CPPUNIT_ASSERT(retval == setval);
      (retProf.properties[2].value) >>= retft;
      CPPUNIT_ASSERT(retft == ft);
      //=================================================================
    }
    
    
    /* 
     * @brief set_service_profile(),getServiceProfile()�Υƥ��ȡ�
     *    set_service_profile()�ˤ�ServiceProfile�򥻥åȸ塢getServiceProfiles()��
     *    ServiceProfileList�������
     *    ServiceProfile����������ServiceProfileList���ɲä���Ƥ��뤫���ǧ��
     */
    void test_set_service_profile() {
      ServiceProfileList getProf;
      ServiceProfile svcProf0, svcProf1;
      NameValue nv;
      NVList nvlist;
      CORBA::Short setst,getst;
      CORBA::Long  setlg,getlg;
      CORBA::Boolean result;
      
      string setstr, getstr;
      
      // ServiceProfile.properties���ǤΥ��å�
      setst = 10;
      nv.name = "short";
      nv.value <<= setst;
      nvlist.length(1);
      nvlist[0] = nv;
      // ServiceProfile�����ǥ��å�
      svcProf0.id = "setProfId0";
      svcProf0.interface_type = "ifTYpe0";
      svcProf0.properties = nvlist;
      
      // ServiceProfile�Υ��å�
      result = m_pConf->set_service_profile(svcProf0);
      
      // ServiceProfile.properties���ǤΥ��å�
      setlg = 1000;
      nv.name = "long";
      nv.value <<= setlg;
      nvlist.length(1);
      nvlist[0] = nv;
      // ServiceProfile�����ǥ��å�
      svcProf1.id = "setProfId1";
      svcProf1.interface_type = "ifTYpe1";
      svcProf1.properties = nvlist;
      
      // ServiceProfile�Υ��å�
      m_pConf->set_service_profile(svcProf1);
      
      
      
      getProf.length(2);
      
      //====== ServiceProfile�μ����ȥǡ�������� =========================
      getProf[0] = m_pConf->getServiceProfile(svcProf0.id);
      
      setstr = svcProf0.id;
      getstr = getProf[0].id;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = svcProf0.interface_type;
      getstr = getProf[0].interface_type;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = svcProf0.properties[0].name;
      getstr = getProf[0].properties[0].name;
      CPPUNIT_ASSERT(setstr == getstr);
      
      getProf[0].properties[0].value >>= getst;
      CPPUNIT_ASSERT(setst == getst);
      //===================================================================
      
      //======= ServiceProfile�μ��� ======================================
      getProf[1] = m_pConf->getServiceProfile(svcProf1.id);
      setstr = svcProf1.id;
      getstr = getProf[1].id;
      CPPUNIT_ASSERT(setstr == getstr);
      setstr = svcProf1.interface_type;
      getstr = getProf[1].interface_type;
      CPPUNIT_ASSERT(setstr == getstr);
      setstr = svcProf1.properties[0].name;
      getstr = getProf[1].properties[0].name;
      CPPUNIT_ASSERT(setstr == getstr);
      getProf[1].properties[0].value >>= getlg;
      CPPUNIT_ASSERT(setlg == getlg);
      //===================================================================
      
      
      //============  ServiceProfileList�μ����ȥǡ������ ====================
      ServiceProfileList spList;
      spList = m_pConf->getServiceProfiles();
      
      setstr = svcProf0.id;
      getstr = spList[0].id;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = svcProf1.id;
      getstr = spList[1].id;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = svcProf0.interface_type;
      getstr = spList[0].interface_type;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = svcProf1.interface_type;
      getstr = spList[1].interface_type;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = svcProf0.properties[0].name;
      getstr = spList[0].properties[0].name;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = svcProf1.properties[0].name;
      getstr = spList[1].properties[0].name;
      CPPUNIT_ASSERT(setstr == getstr);
      
      
      spList[0].properties[0].value >>= getst;
      CPPUNIT_ASSERT(setst == getst);
      spList[1].properties[0].value >>= getlg;
      CPPUNIT_ASSERT(setlg == getlg);
      //================================================================
      
      
      // ServiceProfileList���������Ϳ����id�����
      // ServiceProfile�κ����Ԥ�
      m_pConf->remove_service_profile(svcProf0.id);
      spList = m_pConf->getServiceProfiles();
      
      setstr = svcProf1.id;
      getstr = spList[0].id;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = svcProf1.interface_type;
      getstr = spList[0].interface_type;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = svcProf1.properties[0].name;
      getstr = spList[0].properties[0].name;
      CPPUNIT_ASSERT(setstr == getstr);
      //==================================================================
    }
    
    
    /* 
     * @brief add_organization()�Υƥ���
     *    
     */
    void test_add_organization() {
      Organization_var orgPtr;
      CORBA::Boolean result;
      OrganizationList orgList;
      
      result = m_pConf->add_organization(orgPtr._retn());
      if (!result)
	cout << "Couldn't add organization object." << endl;
      
      orgList = m_pConf->getOrganizations();
    }
    
    
    /* tests for */
    void test_remove_service_profile() {
      //    test_set_service_profile()�ˤƥƥ���
    }
    
    
    /* tests for */
    void test_remove_organization() {
      //    test_add_organization()�ˤƥƥ���
    }
    
    
    /*
     * @brief get_configuration_parameters()�Υƥ���
     *    
     */
    void test_get_configuration_parameters() {
      ParameterList* paramList;
      
      // length 0�Υꥹ�Ȥ��ᤵ��롣 OK.
      paramList = m_pConf->get_configuration_parameters();
      int length = paramList->length();
      CPPUNIT_ASSERT(length == 0);
    }
    
    
    /* tests for */
    void test_get_configuration_parameter_values() {
      //    test_get_configuration_sets()�ˤƥƥ���
    }
    
    
    /* tests for */
    void test_get_configuration_parameter_value() {
      //    test_get_configuration_sets()�ˤƥƥ���
    }
    
    /* tests for */
    void test_set_configuration_parameter() {
      //    test_get_configuration_sets()�ˤƥƥ���
    }
    
    
    /*
     * @brief get_configuration_sets(), add_configuration_set(),
     *        activate_configuration_set(), set_configuration_parameter()
     *        get_configuration_parameter_values(), get_configuration_set()
     *        get_active_configuration_set(),
     *        remove_configuration_set()�Υƥ���
     */
    void test_get_configuration_sets() {
      ConfigurationSet confset;
      NVList nvlist;
      NameValue nv;
      CORBA::Short st, rst;
      CORBA::Long lg, rlg;
      CORBA::Float ft, rft;
      CORBA::Boolean result;
      string setname, getname;
      CORBA::Any any;
      int llength;
      
      //============ ConfigurationSet1 =================================
      // ConfigurationSet���ǤΥ��å�
      confset.id = "configset_id1";
      confset.description = "configset_description";
      nvlist.length(1);
      nv.name = "short";
      st = 10000;
      nv.value <<= st;
      nvlist[0] = nv;
      confset.configuration_data = nvlist;
      //================================================================
      
      
      // ConfigurationSet���ɲ�
      result = m_pConf->add_configuration_set(confset);
      
      // Activate ConfigurationSet1.
      result = m_pConf->activate_configuration_set(confset.id);
      if(!result)
	cout << "Error: activate_configuration_set()" << endl;
      
      
      //=== set_configuration_parameter()�Υƥ��� ===================
      st = 9;
      any <<= st;
      const char* name = "short";
      result = m_pConf->set_configuration_parameter(name, any);
      
      if(!result)
	cout << "Error: set_configuration_parameter()." << endl;
      //==============================================================
      
      
      //==== get_configuration_parameter_values()�Υƥ��� =====
      NVList* getList;
      
      setname = "short";
      getList = m_pConf->get_configuration_parameter_values();
      getname = (*getList)[0].name;
      CPPUNIT_ASSERT(getname == setname);
      (*getList)[0].value >>= rst;
      CPPUNIT_ASSERT(rst == st);
      //=======================================================
      
      
      //============ ConfigurationSet2 =================================
      // ConfigurationSet���ǤΥ��å�
      confset.id = "configset_id2";
      confset.description = "configset_description2";
      nvlist.length(1);
      nv.name = "long";
      lg = 20000;
      nv.value <<= lg;
      nvlist[0] = nv;
      confset.configuration_data = nvlist;
      //================================================================
      
      
      // ConfigurationSet���ɲ�
      result = m_pConf->add_configuration_set(confset);
      
      // Activate ConfigurationSet2.
      result = m_pConf->activate_configuration_set(confset.id);
      if(!result)
	cout << "Error: activate_configuration_set()" << endl;
      
      
      //================= get_configuration_sets()�Υƥ��� ==============
      ConfigurationSetList* confSetList;
      confSetList = m_pConf->get_configuration_sets();
      llength = confSetList->length();
      CPPUNIT_ASSERT(llength == 2);
      
      setname = "configset_id1";
      getname = (*confSetList)[0].id;
      CPPUNIT_ASSERT(getname == setname);
      (*confSetList)[0].configuration_data[0].value >>= rst;
      CPPUNIT_ASSERT(rst == st);
      
      setname = "configset_id2";
      getname = (*confSetList)[1].id;
      CPPUNIT_ASSERT(getname == setname);
      (*confSetList)[1].configuration_data[0].value >>= rlg;
      CPPUNIT_ASSERT(rlg == lg);
      //=================================================================
      
      
      //=============== get_configuration_set()�Υƥ��� ==================
      ConfigurationSet* confSet;
      confSet = m_pConf->get_configuration_set("configset_id1");
      
      setname = "configset_id1";
      getname = confSet->id;
      CPPUNIT_ASSERT(getname == setname);
      confSet->configuration_data[0].value >>= rst;
      CPPUNIT_ASSERT(rst == st);
      
      confSet = m_pConf->get_configuration_set("configset_id2");
      
      setname = "configset_id2";
      getname = confSet->id;
      CPPUNIT_ASSERT(getname == setname);
      confSet->configuration_data[0].value >>= rlg;
      CPPUNIT_ASSERT(rlg == lg);
      //==================================================================
      
      
      //========== set_configuration_set_values()�Υƥ��� ===============
      confset.id = "configset_id2";
      confset.description = "changed configset_description.";
      nvlist.length(1);
      nv.name = "float";
      ft = 999.999;
      nv.value <<= ft;
      nvlist[0] = nv;
      confset.configuration_data = nvlist;
      result = m_pConf->set_configuration_set_values("configset_id2", confset);
      
      // ConfigurationSet�����������åȤ���Ƥ��뤫���ǧ���뤿��
      // get_configuration_set()����ѡ�
      confSet = m_pConf->get_configuration_set("configset_id2");
      setname = "configset_id2";
      getname = confSet->id;
      CPPUNIT_ASSERT(getname == setname);
      confSet->configuration_data[0].value >>= rft;
      CPPUNIT_ASSERT(rft == ft);
      
      // ConfigurationSet�����������åȤ���Ƥ��뤫���ǧ���뤿��
      // get_configuration_sets()����ѡ�
      confSetList = m_pConf->get_configuration_sets();
      llength = confSetList->length();
      CPPUNIT_ASSERT(llength == 2);
      
      setname = "configset_id1";
      getname = (*confSetList)[0].id;
      CPPUNIT_ASSERT(getname == setname);
      (*confSetList)[0].configuration_data[0].value >>= rst;
      CPPUNIT_ASSERT(rst == st);
      
      setname = "configset_id2";
      getname = (*confSetList)[1].id;
      CPPUNIT_ASSERT(getname == setname);
      (*confSetList)[1].configuration_data[0].value >>= rft;
      CPPUNIT_ASSERT(rft == ft);
      //===================================================================
      
      
      //=========== get_active_configuration_set()�Υƥ��� ===============
      confSet = m_pConf->get_active_configuration_set();
      setname = "configset_id2";
      getname = confSet->id;
      CPPUNIT_ASSERT(getname == setname);
      
      string setdesc,getdesc;
      setdesc = "changed configset_description.";
      getdesc = confSet->description;
      CPPUNIT_ASSERT(getdesc == setdesc);
      //===================================================================
      
      
      //=========== remove_configuration_set()�Υƥ��� ===================
      result = m_pConf->remove_configuration_set("configset_id2");
      // "configset_id2"�����Ǥ˻���ConfigurationSet���������Ƥ��뤫
      // ���ǧ���뤿�� get_configuration_sets()����ѡ�
      confSetList = m_pConf->get_configuration_sets();
      llength = confSetList->length();
      CPPUNIT_ASSERT(llength == 1);
      
      confSet = m_pConf->get_configuration_set("configset_id1");
      
      setname = "configset_id1";
      getname = confSet->id;
      CPPUNIT_ASSERT(getname == setname);
      confSet->configuration_data[0].value >>= rst;
      CPPUNIT_ASSERT(rst == st);
      //===================================================================
    }
    
    
    /* tests for */
    void test_get_configuration_set() {
      //    test_get_configuration_sets()�ˤƥƥ���
    }
    
    /* tests for */
    void test_set_configuration_set_values() {
      //    test_get_configuration_sets()�ˤƥƥ���
    }
    
    
    /* tests for */
    void test_get_active_configuration_set() {
      //    test_get_configuration_sets()�ˤƥƥ���
    }
    
    
    /* tests for */
    void test_add_configuration_set() {
      //    test_get_configuration_sets()�ˤƥƥ��ȡ�
    }
    
    
    /* tests for */
    void test_remove_configuration_set() {
      //    test_get_configuration_sets()�ˤƥƥ��ȡ�
    }
    
    
    /* tests for */
    void test_activate_configuration_set() {
      //    test_get_configuration_sets()�ˤƥƥ��ȡ�
    }
    
    
    /* tests for */
    void test_getDeviceProfile() {
      //    test_set_device_profile()�ˤƥƥ���
    }
    
    
    /* tests for */
    void test_getServiceProfiles() {
      //    test_set_service_profile()�ˤƥƥ���
    }
    
    /* tests for */
    void test_getServiceProfile() {
      //    test_set_service_profile()�ˤƥƥ���
    }
    
    /* tests for */
    void test_getOrganizations() {
      //    test_add_organization()�ˤƥƥ���
    }
    
  };
}; // namespace SdoConfiguration

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SdoConfiguration::SdoConfigurationTests);

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
#endif // SdoConfiguration_cpp
