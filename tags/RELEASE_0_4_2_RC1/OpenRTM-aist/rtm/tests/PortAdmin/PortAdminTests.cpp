// -*- C++ -*-
/*!
 * @file   PortAdminTests.cpp
 * @brief  PortAdmin test class
 * @date   $Date: 2007-04-13 15:05:03 $
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
 * $Id: PortAdminTests.cpp,v 1.3 2007-04-13 15:05:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/12 14:44:36  n-ando
 * Some fixes for distribution control.
 *
 * Revision 1.1  2006/11/27 08:34:18  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.2  2006/11/14 02:21:09  kurihara
 *
 * test_deletePortByName() and test_finalizePorts() were added.
 *
 * Revision 1.1  2006/11/13 04:18:45  kurihara
 *
 * test program for PortAdmin class.
 *
 */

#ifndef PortAdmin_cpp
#define PortAdmin_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <vector>
#include <string>

#include <rtm/PortAdmin.h>

/*!
 * @class PortAdminTests class
 * @brief PortAdmin test
 */
namespace PortAdmin
{
  using namespace RTC;
  using namespace std;
  
  int g_argc;
  vector<string> g_argv;
  
  class PortBase
	: public RTC::PortBase
  {
  protected:
	virtual RTC::ReturnCode_t publishInterfaces(RTC::ConnectorProfile&)
	{
	  return RTC::RTC_OK;
	}
	virtual RTC::ReturnCode_t subscribeInterfaces(const RTC::ConnectorProfile&)
	{
	  return RTC::RTC_OK;
	}
	virtual void unsubscribeInterfaces(const RTC::ConnectorProfile&)
	{
	}
  };


  class PortAdminTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PortAdminTests);
    CPPUNIT_TEST(test_getPortList);
    CPPUNIT_TEST(test_getPortRef);
    CPPUNIT_TEST(test_getPort);
    CPPUNIT_TEST(test_registerPort);
    CPPUNIT_TEST(test_deletePort);
    CPPUNIT_TEST(test_deletePortByName);
    CPPUNIT_TEST(test_finalizePorts);
    CPPUNIT_TEST_SUITE_END();
    
  private:
	RTC::PortAdmin* m_ppadm;
	PortBase* m_ppb;
	PortBase* m_ppb2;
    CORBA::ORB_ptr          m_orb;
    PortableServer::POA_ptr m_poa;
    
  public:
    
    /*!
     * @brief Constructor
     */
    PortAdminTests()
    {
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }
      
      m_orb = CORBA::ORB_init(g_argc, argv);
      CORBA::Object_var  obj = m_orb->resolve_initial_references("RootPOA");
      m_poa = PortableServer::POA::_narrow(obj);
      PortableServer::POAManager_var pman = m_poa->the_POAManager();
      pman->activate();
    }
    
    /*!
     * @brief Destructor
     */
    ~PortAdminTests()
    {
    }
    
    /*!
     * @brief �����/�����
     * �����Ǥϰʲ��ν�����ԤäƤ��롣
     *  (1) PortAdmin���饹��PortBase���饹�Υ��󥹥�������
     *  (2) PortBase���饹��PortProfile����Ͽ
     *  (3) PortAdmin���饹��PortBase���֥������Ȥ���Ͽ
     */
    virtual void setUp()
    {
      // PortAdmin���饹�Υ��󥹥�������
      m_ppadm = new RTC::PortAdmin(m_orb, m_poa);
      
      // PortBase���饹�Υ��󥹥�������
      m_ppb = new PortBase();
      
      // PortBase���饹�Υ��󥹥�������
      m_ppb2 = new PortBase();
      
      // PortProfile����Ͽ
      m_ppb->setName("port0");
      m_ppb2->setName("port1");
      
      // PortBase���֥������Ȥ���Ͽ
      m_ppadm->registerPort(*m_ppb);
      m_ppadm->registerPort(*m_ppb2);
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
      //    delete m_ppb;
      // PortAdmin���󥹥��󥹤��˴�
      delete m_ppadm;
    }
    
    /*!
     * @brief getPortList()�Υƥ���
     *    getPortList()��PortList�Υݥ��󥿤�����������Υݥ��󥿤��Ѥ�Port���󥿥ե�������
     *    ���ڥ졼�����ƤӽФ���ԤäƤ��롣
     *    PortList�ϻ�����setUp()�᥽�åɤ���Ͽ���Ƥ��롣
     */
    void test_getPortList() {
      PortList* getPList;
      // getPortList()�Υƥ���
      getPList = m_ppadm->getPortList();
      
      PortProfile *getProf0, *getProf1;
      // ��������Port���󥿥ե������Υ��ڥ졼�����ƤӽФ���
      getProf0 = (*getPList)[0]->get_port_profile();
      
      string setstr, getstr;
      getstr = getProf0->name;
      setstr = "port0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getProf1 = (*getPList)[1]->get_port_profile();
      getstr = getProf1->name;
      setstr = "port1";
      CPPUNIT_ASSERT(getstr == setstr);
    }
    
    
    /*!
     * @brief getPortRef()�Υƥ���
     *   (1) get_PortRef()��Port�Υ��֥������ȥ�ե���󥹼���
     *   (2) �����������֥������ȥ�ե���󥹤��Ѥ�Port���ڥ졼�����θƤӽФ���Ԥ���
     *   �� Port�Υ��֥������ȥ�ե���󥹤�setUp()�ˤ���Ͽ���Ƥ��롣
     */
    void test_getPortRef() {
      Port_var getP;
      string getstr, setstr;
      PortProfile *getProf;
      
      //========= Failure case ================
      // ��Ͽ���Ƥ��ʤ�PortProfile.name��getPortRef()��Ƥ֤�nill���֤���롣OK.
      //    getP = m_ppadm->getPortRef("");
      //    if (CORBA::is_nil(getP))
      //      cout << "getP is nil." << endl;
      //    getP = m_ppadm->getPortRef("test");
      //    if (CORBA::is_nil(getP))
      //      cout << "getP is nil." << endl;
      //========================================================
      
      // getPortRef()�Υƥ���
      getP = m_ppadm->getPortRef("port1");
      
      if (CORBA::is_nil(getP))
	cout << "getP is nil." << endl;
      
      getProf = getP->get_port_profile();
      getstr = getProf->name;
      setstr = "port1";
      CPPUNIT_ASSERT(getstr == setstr);
      
      
      // test  getPortRef()
      getP = m_ppadm->getPortRef("port0");
      
      if (CORBA::is_nil(getP))
	cout << "getP is nil." << endl;
      
      getProf = getP->get_port_profile();
      getstr = getProf->name;
      setstr = "port0";
      CPPUNIT_ASSERT(getstr == setstr);
    }
    
    
    /*!
     * @brief getPort()�Υƥ���
     *   (1) getPort()�ˤ�PortBase�ؤΥݥ��󥿤����
     *   (2) ���������ݥ��󥿤��Ѥ���PortBase���饹�Υ᥽�åɸƤӽФ���Ԥ���
     *   �� PortBase���饹�Υݥ��󥿤�setUp()����Ͽ�ѤߤǤ��롣
     */
    void test_getPort() {
	  RTC::PortBase* pb;
      PortProfile* getProf;
      string setstr, getstr;
      
      // Failure case: unknown exception�㳰ȯ����
      //    pb = m_ppadm->getPort("");
      //    pb = m_ppadm->getPort("test"); // ��Ͽ���Ƥ��ʤ�name
      
      // test getPort()
      pb = m_ppadm->getPort("port1");
      getProf = pb->get_port_profile();
      setstr = "port1";
      getstr = getProf->name;
      CPPUNIT_ASSERT(setstr == getstr);
      
      // test getPort()
      pb = m_ppadm->getPort("port0");
      getProf = pb->get_port_profile();
      setstr = "port0";
      getstr = getProf->name;
      CPPUNIT_ASSERT(setstr == getstr);
    }
    
    
    /*!
     * @brief tests for registerPort()
     */
    void test_registerPort() {
      // setUp()�ˤƥƥ��ȡ�
    }
    
    
    /*!
     * @brief deletePort()�Υƥ���
     *   �� Port_ptr��setUp()�ˤ�registerPort()���Ѥ�����Ͽ�ѤߤǤ��롣(2�ĤΥݡ��Ȥ���Ͽ��)
     *   (1) deletePort()�ƤӽФ���
     *   (2) getPortList()�ˤ�PortList�������
     *   (3) (1)�ν������������Ԥ��Ƥ��뤫���ǧ��
     */
    void test_deletePort() {
      
      // (1) deletePort()�ƤӽФ���
      m_ppadm->deletePort(*m_ppb2);
      
      // (2) getPortList()�ˤ�PortList�������
      PortList* getPList;
      getPList = m_ppadm->getPortList();
      
      cout << getPList->length() << endl;
      
      
      // (3) (1)�ν������������Ԥ��Ƥ��뤫���ǧ��
      PortProfile *getProf0, *getProf1;
      // ��������PortBase���֥������ȡݥ��ڥ졼�����ƤӽФ���
      getProf0 = (*getPList)[0]->get_port_profile();
      string setstr, getstr;
      getstr = getProf0->name;
      setstr = "port0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      
      // Failure case :
      //    setUp()��2�ĤΥݡ��Ȥ���Ͽ���Ƥ��ꡢ(1)�ǰ�ĺ�������Τǡ������Ǥν�����
      //    ���顼�Ȥʤ�Ϥ��Ǥ��롣
      getProf1 = (*getPList)[1]->get_port_profile();
      getstr = getProf1->name;
      setstr = "port1";
      CPPUNIT_ASSERT(getstr == setstr);
    }
    
    
    /*!
     * @brief tests for deletePortByName()
     *   �� Port_ptr��setUp()�ˤ�registerPort()���Ѥ�����Ͽ�ѤߤǤ��롣(2�ĤΥݡ��Ȥ���Ͽ��)
     *    (1) getPortList()�ˤ�PortList���������Ͽ����Ƥ���Port�ο����ǧ��
     *    (2��deletePortByName()�ˤ�"port1"��̾�������Port�κ����Ԥ���
     *    (3) getPortList()�ˤ�PortList���������Ͽ����Ƥ���Port�ο����ǧ��
     */
    void test_deletePortByName() {
      PortList* getPList;
      
      // (1) getPortList()�ˤ�PortList���������Ͽ����Ƥ���Port�ο����ǧ��
      getPList = m_ppadm->getPortList();
      cout << getPList->length() << endl;
      
      m_ppadm->deletePortByName("port1");
      
      // (3) getPortList()�ˤ�PortList���������Ͽ����Ƥ���Port�ο����ǧ��
      getPList = m_ppadm->getPortList();
      cout << getPList->length() << endl;
    }
    
    
    /*!
     * @brief tests for finalizePorts()
     *   (1) getPortList()�ˤ�PortList���������Ͽ����Ƥ���Port�ο����ǧ��
     *   (2) finalizePorts()�θƤӽФ���
     *   (3) getPortList()�ˤ�PortList���������Ͽ����Ƥ���Port�ο����ǧ��
     */
    void test_finalizePorts() {
      PortList* getPList;
      
      // (1) getPortList()�ˤ�PortList���������Ͽ����Ƥ���Port�ο����ǧ��
      getPList = m_ppadm->getPortList();
      cout << getPList->length() << endl;
      
      
      // (2) finalizePorts()�θƤӽФ���
      m_ppadm->finalizePorts();
      
      
      // (3) getPortList()�ˤ�PortList���������Ͽ����Ƥ���Port�ο����ǧ��
      getPList = m_ppadm->getPortList();
      cout << getPList->length() << endl;
    }
    
    
  };
}; // namespace PortAdmin

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PortAdmin::PortAdminTests);

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
#endif // PortAdmin_cpp
