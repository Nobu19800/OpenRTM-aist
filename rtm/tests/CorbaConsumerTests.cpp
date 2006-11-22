// -*- C++ -*-
/*!
 * @file 
 * @brief test class
 * @date $Date: 2006-11-22 11:43:22 $
 * @author Shinji Kurihara
 * $Id: CorbaConsumerTests.cpp,v 1.1 2006-11-22 11:43:22 kurihara Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include "../CorbaConsumer.h"
#include "Test.hh"

using namespace std;

int g_argc;
vector<string> g_argv;

/*!
 * @brief Test.idl���������interface�μ������饹(�����Х��)
 *    ConbaConsumer::setObject()���Ϥ�����Υƥ��ȥ��饹
 */
class Test_i : public POA_Test,
	       public PortableServer::RefCountServantBase
{
public:
  // ���󥹥ȥ饯��
  inline Test_i(){}

  // �ǥ��ȥ饯��
  virtual ~Test_i(){}

  // hello()���ڥ졼�����μ���
  virtual void hello() {cout << "operation hello !!!" << endl;}
};


/*!
 * @brief ConsumerBase���饹,Consumer���饹�Υƥ��ȥ��饹
 */
class CorbaConsumerTests
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CorbaConsumerTests);
  CPPUNIT_TEST(test_ConsumerBase);
  //  CPPUNIT_TEST(test_Consumer);
  CPPUNIT_TEST_SUITE_END();

private:
  Test_ptr m_testObj;
  RTC::ConsumerBase* m_consBase;

  typedef RTC::Consumer<Test, Test::_ptr_type, Test::_var_type> TestConsumer;
  TestConsumer* m_cons;

public:
  
  /*!
   * @brief ���󥹥ȥ饯��
   *    (1) ORB�ν����
   *    (2) POA�ν����
   *    (3) �����Х�ȥ��饹�Υ��󥹥�������
   *    (4) �����Х�Ȥγ����������֥������ȥ�ե���󥹤μ���
   *    (5) POAManager�γ�����
   */
  CorbaConsumerTests()
  {
    char* argv[g_argc];
    for (int i = 0; i < g_argc; i++) {
      argv[i] = (char *)g_argv[i].c_str();
    }

    CORBA::ORB_var m_orb;
    PortableServer::POA_var m_poa;

    // (1) ORB�ν����
    m_orb = CORBA::ORB_init(g_argc, argv);
    CORBA::Object_var  obj = m_orb->resolve_initial_references("RootPOA");

    // (2) POA�ν����
    m_poa = PortableServer::POA::_narrow(obj);

    // (3) �����Х�ȥ��饹�Υ��󥹥�������
    Test_i* test = new Test_i();

    // (4) �����Х�Ȥγ����������֥������ȥ�ե���󥹤μ���
    m_testObj = test->_this();

    test->_remove_ref();

    PortableServer::POAManager_var pman = m_poa->the_POAManager();

    // (5) POAManager�γ�����
    pman->activate();
  }


  /*!
   * @brief �ǥ��ȥ饯��
   */
  ~CorbaConsumerTests()
  {
  }
  
  /*! 
   * @brief �����
   */
  virtual void setUp()
  {
  }
  

  /*!
   * @brief ��Ͻ���
   */
  virtual void tearDown()
  { 
  }


  /*!
   * @brief ConsumerBase���饹�Υƥ���
   *    (1) ConsumerBase���饹�Υ��󥹥�������
   *    (2) setObject()�᥽�åɤ�Ƥ�,���֥������ȥ�ե���󥹤���Ͽ��Ԥ���
   *    (3) getObject()�᥽�åɤ�Ƥӡ����֥������ȥ�ե���󥹤μ�����Ԥ���
   *    (4) �����������֥������ȥ�ե���󥹤�Test���饹��narrow���롣
   *    (5��(4)��narrow�������֥������ȥ�ե���󥹤��Ѥ�Test���󥿥ե�������
   *        hello()���ڥ졼�����ƤӽФ���Ԥ���
   *    (6) setObject()�᥽�åɤ�Ƥ�,���֥������ȥ�ե���󥹤���Ͽ��Ԥ���
   *    (7) getObject()�᥽�åɤ�Ƥӡ����֥������ȥ�ե���󥹤μ�����Ԥ���
   *    (8) �����������֥������ȥ�ե���󥹤�Test���饹��narrow���롣
   *    (9) hello()���ڥ졼�����ƤӽФ���
   *    (10) ConsumerBase���饹�Υ��󥹥����˴�
   */
  void test_ConsumerBase() {
    bool result;

    // (1) ConsumerBase���饹�Υ��󥹥�������
    m_consBase = new RTC::ConsumerBase();

    // (2) setObject()�᥽�åɤ�Ƥ�,���֥������ȥ�ե���󥹤���Ͽ��Ԥ���
    result = m_consBase->setObject(m_testObj);

    if(!result)
      cout << "setObject() is Failed." << endl;

    CORBA::Object_ptr getObj;

    // (3) getObject()�᥽�åɤ�Ƥӡ����֥������ȥ�ե���󥹤μ�����Ԥ���
    getObj = m_consBase->getObject();

    Test_var testObj;

    // (4) �����������֥������ȥ�ե���󥹤�Test���饹��narrow���롣
    testObj = Test::_narrow(getObj);
    if(CORBA::is_nil(testObj))
      cout << "is_nil" << endl;

    // (5��(4)��narrow�������֥������ȥ�ե���󥹤��Ѥ�Test���󥿥ե�������
    //     hello()���ڥ졼�����ƤӽФ���Ԥ���
    testObj->hello();


    // ����setObject(),getObject()��Ƥ֡�
    // (6) setObject()�᥽�åɤ�Ƥ�,���֥������ȥ�ե���󥹤���Ͽ��Ԥ���
    result = m_consBase->setObject(m_testObj);

    // (7) getObject()�᥽�åɤ�Ƥӡ����֥������ȥ�ե���󥹤μ�����Ԥ���
    getObj = m_consBase->getObject();

    // (8) �����������֥������ȥ�ե���󥹤�Test���饹��narrow���롣
    testObj = Test::_narrow(getObj);

    // (9) hello()���ڥ졼�����ƤӽФ���
    testObj->hello();

    // (10) ConsumerBase���饹�Υ��󥹥����˴�
    delete m_consBase;
  }


  /*!
   * @brief Consumer���饹�Υƥ���
   *    (1) Consumer���饹�Υ��󥹥�������
   *    (2) setObject()�᥽�åɤ�Ƥ�,���֥������ȥ�ե���󥹤���Ͽ��Ԥ���
   *    (3) getObject()�᥽�åɤ�Ƥӡ����֥������ȥ�ե���󥹤μ�����Ԥ���
   *    (4) �����������֥������ȥ�ե���󥹤�Test���饹��narrow���롣
   *    (5��(4)��narrow�������֥������ȥ�ե���󥹤��Ѥ�Test���󥿥ե�������
   *        hello()���ڥ졼�����ƤӽФ���Ԥ���
   *    (6) _ptr()�᥽�åɤ�Ƥӡ�Test��narrow���줿���֥������Ȥ�������롣
   *    (7) (6)�Ǽ����������֥������Ȥ��Ф���hello()���ڥ졼������ƤӽФ���
   *    (8) Consumer���饹�Υ��󥹥����˴�
   */
  void test_Consumer() {
    bool result;

    // (1) Consumer���饹�Υ��󥹥�������
    m_cons = new TestConsumer();

    // (2) setObject()�᥽�åɤ�Ƥ�,���֥������ȥ�ե���󥹤���Ͽ��Ԥ���
    result = m_cons->setObject(m_testObj);

    CORBA::Object_ptr getObj;

    // (3) getObject()�᥽�åɤ�Ƥӡ����֥������ȥ�ե���󥹤μ�����Ԥ���
    getObj = m_cons->getObject();

    Test_var test;

    // (4) �����������֥������ȥ�ե���󥹤�Test���饹��narrow���롣
    test = Test::_narrow(getObj);
    if(CORBA::is_nil(test))
      cout << "is_nil" << endl;

    // (5��(4)��narrow�������֥������ȥ�ե���󥹤��Ѥ�Test���󥿥ե�������
    //     hello()���ڥ졼�����ƤӽФ���Ԥ���
    test->hello();


    Test::_ptr_type testObj;

    // (6) _ptr()�᥽�åɤ�Ƥӡ�Test��narrow���줿���֥������Ȥ�������롣
    testObj = m_cons->_ptr();
    
    // (7) (6)�Ǽ����������֥������Ȥ��Ф���hello()���ڥ졼������ƤӽФ���
    testObj->hello();


    // ����setObject(),getObject(),_ptr()��Ƥ֡�
    result = m_cons->setObject(m_testObj);
    getObj = m_cons->getObject();
    test = Test::_narrow(getObj);
    test->hello();
    testObj = m_cons->_ptr();
    testObj->hello();

    // (8) Consumer���饹�Υ��󥹥����˴�
    delete m_cons;
  }

};


/*!
 * @brief register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(CorbaConsumerTests);



int main(int argc, char* argv[])
{
  
  g_argc = argc;
  for (int i = 0; i < argc; i++) {
    g_argv.push_back(argv[i]);
  }
  
  CppUnit::TextUi::TestRunner runner;
  
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  CppUnit::Outputter* outputter = 
    new CppUnit::TextOutputter(&runner.result(), std::cout);
  runner.setOutputter(outputter);
  
  return runner.run();
}
