// -*- C++ -*-
/*!
 * @file   ManagerConfigTests.cpp
 * @brief  ManagerConfig test class
 * @date   $Date: 2006-11-27 08:25:57 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef ManagerConfig_cpp
#define ManagerConfig_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <fstream>
#include <vector>
#include <string>

#include <rtm/ManagerConfig.h>

/*!
 * @class ManagerConfigTests class
 * @brief ManagerConfig test
 */
namespace ManagerConfig
{
  using namespace std;
  
  int g_argc;
  //char* g_argv[10];
  vector<string> g_argv;
  
  class ManagerConfigTests
    : public CppUnit::TestFixture,
      public RTC::ManagerConfig
  {
    CPPUNIT_TEST_SUITE(ManagerConfigTests);
    CPPUNIT_TEST(test_init);
    CPPUNIT_TEST(test_parseArgs);
    CPPUNIT_TEST(test_findConfigFile);
    CPPUNIT_TEST(test_setSystemInformation);
    CPPUNIT_TEST(test_fileExist);
    CPPUNIT_TEST_SUITE_END();
    
  private:
    
  public:
    
    /*!
     * @brief Constructor
     */
    ManagerConfigTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~ManagerConfigTests()
    {
    }
    
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
    /* tests for init()*/
    void test_init() {
      RTC::Properties prop;
      //    if (g_argc > 1)
      
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++)
	argv[i] = (char *)g_argv[i].c_str();
      
      prop = init(g_argc, argv);
      
      cout << endl;
      prop.list(std::cout);
    }
    
    
    /* tests for parseArgs()*/
    void test_parseArgs() {
      char* argv[g_argc];
      
      for (int i = 0; i < g_argc; i++)
	argv[i] = (char *)g_argv[i].c_str();
      
      parseArgs(g_argc, argv);
      
      if (g_argc > 1) {
	if (g_argv[1] == "-f") {
	  string str(g_argv[2]);
	  CPPUNIT_ASSERT_EQUAL_MESSAGE("config file is not found.",
				       str, m_configFile);
	}
      }
      else {
	CPPUNIT_ASSERT(m_configFile == "");
      }
    }
    
    
    /* tests for findConfigFile() */
    void test_findConfigFile() {
      
      // rtc.conf��̵�����¹Ի����顼�Ȥʤ뤿��,
      // ���줬�������켡����٥ƥ��Ȥ�ɬ�ס�
      CPPUNIT_ASSERT(findConfigFile());
    }
    
    
    /* tests for setSystemInformation() */
    void test_setSystemInformation() {
      RTC::Properties prop;
      cout << endl << endl;
      setSystemInformation(prop);
      prop.list(std::cout);
    }
    
    
    /* tests for fileExist() */
    void test_fileExist() {
      // ������Ϳ�����ˤ��Υץ�����¹Ԥ���ȡ������ǥƥ��Ȥ����Ԥ���褦��
      // �ǥե���ȤΥե�����̾��"test.config"�Ȥ��Ƥ��롣
      string filename("test.config");
      if (g_argc == 2)
	filename = g_argv[1];
      else if(g_argc == 3)
	filename = g_argv[2];
      
      CPPUNIT_ASSERT(!fileExist(filename));
      // �¹Ի���¸�ߤ��ʤ��ե������"-f"���ץ����ǻ��ꤹ��ȡ�
      // false���֤��������ǧ��
      // �����Ǥϡ�"rtc.conf"���ɤ��ˤ�̵�����,�¹Ի���
      // �������ȥ��顼�ˤʤ뤿��
      // ������˺ƥƥ��Ȥ�ɬ�פ��ꡣ
    }
    
  };
}; // namespace ManagerConfig

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ManagerConfig::ManagerConfigTests);

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
#endif // ManagerConfig_cpp
