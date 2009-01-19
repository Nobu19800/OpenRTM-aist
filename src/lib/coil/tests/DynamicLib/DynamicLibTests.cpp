// -*- C++ -*-
/*!
 * @file   DynamicLibTests.cpp
 * @brief  DynamicLib test class
 * @date   $Date$ 
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$ 
 *
 */

/*
 * $Log$
 *
 */

#ifndef DynamicLib_cpp
#define DynamicLib_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/DynamicLib.h>

/*!
 * @class DynamicLibTests class
 * @brief DynamicLib test
 */
namespace DynamicLib
{
#if defined COIL_OS_LINUX
// #error POSIX.
  const char * LibName = "libcoil.so.0";
//  const char * SymbolName = "svc_run";
  const char * SymbolName = "ForExternTest";

#else
// #error WIN32!!
  const char * LibName = "coil.dll";
  const char * SymbolName = "ForExternTest";

#endif

  class DynamicLibTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DynamicLibTests);
    CPPUNIT_TEST(test_DynamicLib_1);
    CPPUNIT_TEST(test_DynamicLib_2);
    CPPUNIT_TEST(test_DynamicLib_3);
    CPPUNIT_TEST(test_DynamicLib_4);
    CPPUNIT_TEST(test_DynamicLib_open_failure);
    CPPUNIT_TEST(test_DynamicLib_open_and_close);
    CPPUNIT_TEST(test_DynamicLib_symbol_failure);
    CPPUNIT_TEST(test_DynamicLib_symbol);
    CPPUNIT_TEST(test_DynamicLib_error);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    coil::DynamicLib * dl;

  public:
  
    /*!
     * @brief Constructor
     */
    DynamicLibTests()
    {

    }
    
    /*!
     * @brief Destructor
     */
    ~DynamicLibTests()
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
  
    /* test case */

     /*!
     * @brief �R���X�g���N�^���̂P
     */
	void test_DynamicLib_1()
	{
	  // ��O���N���Ȃ���΂n�j�Ƃ���
      coil::DynamicLib * dl1 = new coil::DynamicLib(1);
      int result = dl1->open(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      CPPUNIT_ASSERT_EQUAL(0, result);
      delete dl1;
	}

     /*!
     * @brief �R���X�g���N�^���̂Q
     */
	void test_DynamicLib_2()
	{
	  // ��O���N���Ȃ���΂n�j�Ƃ���
      coil::DynamicLib * dl1 = new coil::DynamicLib(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
	  delete dl1;
	}

     /*!
     * @brief �R���X�g���N�^���̂R
     */
	void test_DynamicLib_3()
	{
	  // ��O���N���Ȃ���΂n�j�Ƃ���
	  coil::DynamicLib dl1(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      coil::DynamicLib dl2(dl1);   // <--- �����ŁAstd::bad_alloc�ɗ����� Kz.080930 �� fix 081006.
	}

     /*!
     * @brief �R���X�g���N�^���̂S
     */
	void test_DynamicLib_4()
	{
	  // ��O���N���Ȃ���΂n�j�Ƃ���
      coil::DynamicLib * dl1 = new coil::DynamicLib(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
       coil::DynamicLib dl2 = *dl1;   // <--- �����ŁAstd::bad_alloc�ɗ����� Kz.080930 �� fix 081006.
	  delete dl1;
	}

     /*!
     * @brief Try to open nonExistence.
     */
	void test_DynamicLib_open_failure()
	{
      coil::DynamicLib * dl1 = new coil::DynamicLib(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      int result = dl1->open("Hoge", COIL_DEFAULT_DYNLIB_MODE, 1);
      CPPUNIT_ASSERT_EQUAL(-1, result);
      delete dl1;
	}

     /*!
     * @brief Open and Close
     */
	void test_DynamicLib_open_and_close()
	{
      coil::DynamicLib * dl1 = new coil::DynamicLib(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      int result = dl1->open(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      CPPUNIT_ASSERT_EQUAL(0, result);

      dl1->close();
      
      delete dl1;
	}

     /*!
     * @brief do symbol
     * note ���݂��Ȃ��V���{����ǂݏo���B
     */
	void test_DynamicLib_symbol_failure()
	{
      coil::DynamicLib * dl1 = new coil::DynamicLib(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      dl1->symbol("Hoge");

      int result = dl1->open(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      CPPUNIT_ASSERT_EQUAL(0, result);

      char * p = (char *)dl1->symbol("HogeHoge");
//      std::cout << "Error : " << dl1->error() << "." << std::endl ;
      CPPUNIT_ASSERT(0 == p);

      dl1->close();
      delete dl1;
	}

     /*!
     * @brief do symbol
     * note ���݂���V���{����ǂݏo���B
     */
	void test_DynamicLib_symbol()
	{
      coil::DynamicLib * dl1 = new coil::DynamicLib(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      dl1->symbol("Hoge");

      int result = dl1->open(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      CPPUNIT_ASSERT_EQUAL(0, result);

      char * p = (char *)dl1->symbol(SymbolName);
//      if (!p) std::cout << "error() : " << dl1->error() << "." << std::endl ;
      CPPUNIT_ASSERT(p);

      dl1->close();
      delete dl1;
	}

     /*!
     * @brief do error
     * note �G���[��������error()����O��Ԃ�����
     */
	void test_DynamicLib_error()
	{
//      coil::DynamicLib * dl1 = new coil::DynamicLib(1);  // ���ǂ���ł���O�͋N���Ȃ�
      coil::DynamicLib * dl1 = new coil::DynamicLib(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      dl1->error();

      dl1->open(LibName, COIL_DEFAULT_DYNLIB_MODE, 1);
      CPPUNIT_ASSERT(!dl1->error());    // ���펞�ɂ͂O��Ԃ�

      dl1->symbol("HogeHogeHoge");
      CPPUNIT_ASSERT(dl1->error());    // �񐳏펞�ɂ͔�O��Ԃ�
//      std::cout << "error() : " << err2 << "." << std::endl;

      dl1->close();
      delete dl1;
	}

  };
}; // namespace DynamicLib

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DynamicLib::DynamicLibTests);

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
#endif // DynamicLib_cpp
