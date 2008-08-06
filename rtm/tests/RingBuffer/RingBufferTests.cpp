// -*- C++ -*-
/*!
 * @file   RingBufferTests.cpp
 * @brief  RingBuffer test class
 * @date   $Date: 2008/01/24 01:52:14 $
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

/*
 * $Log: RingBufferTests.cpp,v $
 * Revision 1.3  2008/01/24 01:52:14  tsakamoto
 * *** empty log message ***
 *
 * Revision 1.2  2008/01/11 11:27:11  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2007/12/20 07:50:17  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2006/12/02 18:53:08  n-ando
 * Some tests were added.
 *
 * Revision 1.1  2006/11/27 08:37:03  n-ando
 * TestSuites are devided into each directory.
 *
 *
 */

#ifndef RingBuffer_cpp
#define RingBuffer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <string>
#include <sstream>
#include <rtm/RingBuffer.h>

//#define DEBUG

namespace RingBuffer
{
  /*!
   * @class RingBufferTests class
   * @brief RingBuffer test
   */
  class RingBufferTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(RingBufferTests);
		
    CPPUNIT_TEST(test_length);
    CPPUNIT_TEST(test_isFull);
    CPPUNIT_TEST(test_isEmpty);
    CPPUNIT_TEST(test_init);
    CPPUNIT_TEST(test_write_read);
    CPPUNIT_TEST(test_write_read_with_small_length);
    CPPUNIT_TEST(test_isNew);
		
    CPPUNIT_TEST_SUITE_END();
		
  private:
		
  public:
    /*!
     * @brief Constructor
     */
    RingBufferTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~RingBufferTests()
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
		
    /*!
     * @brief length()�᥽�åɤΥƥ���
     * 
     * - ���󥹥ȥ饯���ǻ��ꤵ�줿�Хåե�Ĺ�������������Ǥ��뤫��
     */
    void test_length()
    {
      RTC::RingBuffer<int> buff(123);
      CPPUNIT_ASSERT_EQUAL((long int) 123, buff.length());
    }

    /*!
     * @brief isEmpty()�᥽�åɤΥƥ���
     * 
     * - �Хåե������ľ�塢���ǤϤʤ���Ƚ�ꤵ��뤫��
     * - �Ǹ�˥ǡ������ɤ߼��줿�塢�������ǡ������񤭹��ߤ���Ƥ��ʤ���硢����Ƚ�ꤵ��뤫��
     * - �Ǹ�˥ǡ������ɤ߼��줿�塢�������ǡ������񤭹��ߤ��줿��硢���ǤϤʤ���Ƚ�ꤵ��뤫��
     */
    void test_isEmpty()
    {
      long int length = 10;
      RTC::RingBuffer<int> buff(length);
			
      // (1) �Хåե������ľ�塢���ǤϤʤ���Ƚ�ꤵ��뤫��
      int initialValue = 12345;
      buff.init(initialValue);
      CPPUNIT_ASSERT_EQUAL(false, buff.isEmpty());			
			
      // (2) �Ǹ�˥ǡ������ɤ߼��줿�塢�������ǡ������񤭹��ߤ���Ƥ��ʤ���硢����Ƚ�ꤵ��뤫��
      int readValue;
      CPPUNIT_ASSERT_EQUAL(true, buff.read(readValue));
      CPPUNIT_ASSERT_EQUAL(true, buff.isEmpty());
			
      // (3) �Ǹ�˥ǡ������ɤ߼��줿�塢�������ǡ������񤭹��ߤ��줿��硢���ǤϤʤ���Ƚ�ꤵ��뤫��
      int writeValue = 98765;
      CPPUNIT_ASSERT_EQUAL(true, buff.write(writeValue));
      CPPUNIT_ASSERT_EQUAL(false, buff.isEmpty());
    }
		
    /*!
     * @brief isEmpty()�᥽�åɤΥƥ���
     * @attention �ܥƥ��Ȥϡ�RingBuffer�μ������ͤ���󥰾��Хåե��б����줿��Τ��Ф���ƥ������ƤˤʤäƤ��롣
     * ��󥰾��Хåե��б�����RinguBuffer�Ǥ��ܥƥ��Ȥϼ��Ԥ��롣
     *
     * - �Ǹ�Σ��ǡ�����Ĥ����ɤ߼�ꡢ����Ƚ�ꤵ��ʤ����Ȥ��ǧ����
     * - �Ǹ�Σ��ǡ����ޤ��ɤ߼�ꡢ����Ƚ�ꤵ��뤳�Ȥ��ǧ����
     */
    void _test_isEmpty()
    {
      // �Хåե����������
      long int length = 10;
      RTC::RingBuffer<int> buff(length);
			
      int value = 12345;
      buff.init(value);

      // (1) �Ǹ�Σ��ǡ�����Ĥ����ɤ߼�ꡢ����Ƚ�ꤵ��ʤ����Ȥ��ǧ����
      for (long int i = 0; i < length - 1; i++) {
	int data;
	buff.read(data);
	CPPUNIT_ASSERT_EQUAL(false, buff.isEmpty());
      }

      // (2) �Ǹ�Σ��ǡ����ޤ��ɤ߼�ꡢ����Ƚ�ꤵ��뤳�Ȥ��ǧ����
      int data;
      buff.read(data);
      CPPUNIT_ASSERT_EQUAL(true, buff.isEmpty());
    }
		
    /*!
     * @brief isFull()�᥽�åɤΥƥ���
     * 
     * - �Хåե������ξ�硢�ե�Ƚ��ϵ��Ȥʤ뤫��
     * - ���Хåե��˥ǡ������񤭹��ޤ�Ƥ�����֤Ǥ⡢�ե�Ƚ��ϵ��Ȥʤ뤫��
     * - �Хåե��˴�ʬ�ǡ������񤭹��ޤ�Ƥ�����֤ǡ��ե�Ƚ��ϵ��Ȥʤ뤫��
     */
    void test_isFull()
    {
      // (1) �Хåե������ξ�硢�ե�Ƚ��ϵ��Ȥʤ뤫��
      int length1 = 10;
      RTC::RingBuffer<int> buff1(length1);
      CPPUNIT_ASSERT_EQUAL(false, buff1.isFull());
			
      // (2) ���Хåե��˥ǡ������񤭹��ޤ�Ƥ�����֤Ǥ⡢�ե�Ƚ��ϵ��Ȥʤ뤫��
      int length2 = 10;
      RTC::RingBuffer<int> buff2(length2);
      for (int i = 0; i < length2; i++) {
	buff2.write(i);
      }
      CPPUNIT_ASSERT_EQUAL(false, buff2.isFull());
			
      // (3) �Хåե��˴�ʬ�ǡ������񤭹��ޤ�Ƥ�����֤ǡ��ե�Ƚ��ϵ��Ȥʤ뤫��
      int length3 = 10;
      RTC::RingBuffer<int> buff3(length3);
      for (int i = 0; i < length3 / 2; i++) {
	buff3.write(i);
      }
      CPPUNIT_ASSERT_EQUAL(false, buff3.isFull());
    }
				
    /*!
     * @brief init()�᥽�åɤΥƥ���
     * 
     * - ���餫����ǡ����ǽ���������塢���ꤷ���ǡ������������ɤ߽Ф��뤫��
     */
    void test_init()
    {
      // �Хåե���������ơ�init()�ǽ��������
      long int length = 10;
      RTC::RingBuffer<int> buff(length);
			
      int value = 12345;
      buff.init(value);
			
      // ���ꤷ���ǡ������������ɤ߽Ф��뤫��
      int expected = 12345;
      for (long int i = 0; i < length; i++) {
	int actual;
	buff.read(actual);
	CPPUNIT_ASSERT_EQUAL(expected, actual);
      }
    }

    /*!
     * @brief write()�᥽�åɤ����read()�᥽�åɤΥƥ���
     * 
     * - �Хåե������֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
     * - ���Хåե��˥ǡ������񤭹��ޤ�Ƥ�����֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
     * - ���Хåե��˴�ʬ�ǡ������񤭹��ޤ�Ƥ�����֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
     */
    void test_write_read()
    {
      // (1) �Хåե������֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
      // �Хåե������������Τޤޤˤ���
      long int length1 = 10;
      RTC::RingBuffer<int> buff1(length1);
			
      // ���ǡ���������ɽФ�Ԥ�
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// �����
	buff1.write(writeValue);
				
	// �ɽФ�
	int readValue;
	buff1.read(readValue);
				
	// �񤭹�����ǡ������������ɤ߽Ф�������
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
			
      // (2) ���Хåե��˥ǡ������񤭹��ޤ�Ƥ�����֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
      // �Хåե����������ե���֤ˤ���
      long int length2 = 10;
      RTC::RingBuffer<int> buff2(length2);
      for (int i = 0; i < length2; i++) {
	buff2.write(i + 123);
      }
			
      // ���ǡ���������ɽФ�Ԥ�
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// �����
	buff2.write(writeValue);
				
	// �ɽФ�
	int readValue;
	buff2.read(readValue);
				
	// �񤭹�����ǡ������������ɤ߽Ф�������
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
			
      // (3) �Хåե��˴�ʬ�ǡ������񤭹��ޤ�Ƥ�����֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
      long int length3 = 10;
      RTC::RingBuffer<int> buff3(length3);
      for (int i = 0; i < length3 / 2; i++) {
	buff3.write(i + 123);
      }
			
      // ���ǡ���������ɽФ�Ԥ�
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// �����
	buff3.write(writeValue);
				
	// �ɽФ�
	int readValue;
	buff3.read(readValue);
				
	// �񤭹�����ǡ������������ɤ߽Ф�������
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
    }
		
    /*!
     * @brief write()�᥽�åɤ����read()�᥽�åɤΥƥ��ȡʥХåե�Ĺ���ξ���
     * 
     * - �Хåե������֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
     * - ���Хåե��˥ǡ������񤭹��ޤ�Ƥ�����֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
     * - �Хåե��˴�ʬ�ǡ������񤭹��ޤ�Ƥ�����֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
     */
    void test_write_read_with_small_length()
    {
      // (1) �Хåե������֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
      // �Хåե������������Τޤޤˤ���
      long int length1 = 2;
      RTC::RingBuffer<int> buff1(length1);
			
      // ���ǡ���������ɽФ�Ԥ�
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// �����
	buff1.write(writeValue);
				
	// �ɽФ�
	int readValue;
	buff1.read(readValue);
				
	// �񤭹�����ǡ������������ɤ߽Ф�������
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
			
      // (2) ���Хåե��˥ǡ������񤭹��ޤ�Ƥ�����֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
      // �Хåե����������ե���֤ˤ���
      long int length2 = 2;
      RTC::RingBuffer<int> buff2(length2);
      for (int i = 0; i < length2; i++) {
	buff2.write(i + 123);
      }
			
      // ���ǡ���������ɽФ�Ԥ�
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// �����
	buff2.write(writeValue);
				
	// �ɽФ�
	int readValue;
	buff2.read(readValue);
				
	// �񤭹�����ǡ������������ɤ߽Ф�������
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
			
      // (3) �Хåե��˴�ʬ�ǡ������񤭹��ޤ�Ƥ�����֤ǣ��ǡ���������ɽФ�Ԥ����񤭹�����ǡ������������ɤ߽Ф��뤫��
      long int length3 = 2;
      RTC::RingBuffer<int> buff3(length3);
      for (int i = 0; i < 1; i++) {
	buff3.write(i + 123);
      }
			
      // ���ǡ���������ɽФ�Ԥ�
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// �����
	buff3.write(writeValue);
				
	// �ɽФ�
	int readValue;
	buff3.read(readValue);
				
	// �񤭹�����ǡ������������ɤ߽Ф�������
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
    }
		
    /*!
     * @brief isNew()�᥽�åɤΥƥ���
     * 
     * - �Хåե������ξ��֤ǡ�isNewȽ�꤬���ˤʤ뤫��
     * - ���Хåե��˥ǡ������񤭹��ޤ�Ƥ�����֤ǡ��ǡ���������isNewȽ�꤬���ˤʤ뤫��
     * - ���Хåե��˥ǡ������񤭹��ޤ�Ƥ�����֤ǡ��ǡ�������������Υǡ����ɽФ�Ԥä����isNewȽ�꤬���ˤʤ뤫��
     * - �Хåե��˴�ʬ�ǡ������񤭹��ޤ�Ƥ�����֤ǡ��ǡ���������isNewȽ�꤬���ˤʤ뤫��
     * - �Хåե��˴�ʬ�ǡ������񤭹��ޤ�Ƥ�����֤ǡ��ǡ�������������Υǡ����ɽФ�Ԥä����isNewȽ�꤬���ˤʤ뤫��
     */
    void test_isNew()
    {
      // (1) �Хåե������ξ��֤ǡ�isNewȽ�꤬���ˤʤ뤫��
      long int length1 = 10;
      RTC::RingBuffer<int> buff1(length1);
      CPPUNIT_ASSERT_EQUAL(false, buff1.isNew());
			
      // ���Хåե��˥ǡ������񤭹��ޤ�Ƥ�����֤�...
      long int length2 = 10;
      RTC::RingBuffer<int> buff2(length2);
			
      for (int i = 0; i < length2; i++) {
	// (2) ...�ǡ���������isNewȽ�꤬���ˤʤ뤫��
	int writeValue = i + 123;
	buff2.write(writeValue);
	CPPUNIT_ASSERT_EQUAL(true, buff2.isNew());
				
	// (3) ...�ǡ�������������Υǡ����ɽФ�Ԥä����isNewȽ�꤬���ˤʤ뤫��
	int readValue;
	buff2.read(readValue);
	CPPUNIT_ASSERT_EQUAL(false, buff2.isNew());
      }
			
      // �Хåե��˴�ʬ�ǡ������񤭹��ޤ�Ƥ�����֤�...
      long int length3 = 10;
      RTC::RingBuffer<int> buff3(length3);
      for (int i = 0; i < length3 / 2; i++) {
	buff3.write(i + 456);
      }
			
      for (int i = 0; i < length3; i++) {
	// (4) ...�ǡ���������isNewȽ�꤬���ˤʤ뤫��
	int writeValue = i + 123;
	buff3.write(writeValue);
	CPPUNIT_ASSERT_EQUAL(true, buff3.isNew());
				
	// (5) ...�ǡ�������������Υǡ����ɽФ�Ԥä����isNewȽ�꤬���ˤʤ뤫��
	int readValue;
	buff3.read(readValue);
	CPPUNIT_ASSERT_EQUAL(false, buff3.isNew());
      }
    }
		
  };
}; // namespace RingBuffer

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(RingBuffer::RingBufferTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{

  FORMAT format = TEXT_OUT;
  int target = 0;
  std::string xsl;
  std::string ns;
  std::string fname;
  std::ofstream ofs;

  int i(1);
  while (i < argc)
    {
      std::string arg(argv[i]);
      std::string next_arg;
      if (i + 1 < argc) next_arg = argv[i + 1];
      else              next_arg = "";

      if (arg == "--text") { format = TEXT_OUT; break; }
      if (arg == "--xml")
	{
	  if (next_arg == "")
	    {
	      fname = argv[0];
	      fname += ".xml";
	    }
	  else
	    {
	      fname = next_arg;
	    }
	  format = XML_OUT;
	  ofs.open(fname.c_str());
	}
      if ( arg == "--compiler"  ) { format = COMPILER_OUT; break; }
      if ( arg == "--cerr"      ) { target = 1; break; }
      if ( arg == "--xsl"       )
	{
	  if (next_arg == "") xsl = "default.xsl"; 
	  else                xsl = next_arg;
	}
      if ( arg == "--namespace" )
	{
	  if (next_arg == "")
	    {
	      std::cerr << "no namespace specified" << std::endl;
	      exit(1); 
	    }
	  else
	    {
	      xsl = next_arg;
	    }
	}
      ++i;
    }
  CppUnit::TextUi::TestRunner runner;
  if ( ns.empty() )
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  else
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry(ns).makeTest());
  CppUnit::Outputter* outputter = 0;
  std::ostream* stream = target ? &std::cerr : &std::cout;
  switch ( format )
    {
    case TEXT_OUT :
      outputter = new CppUnit::TextOutputter(&runner.result(),*stream);
      break;
    case XML_OUT :
      std::cout << "XML_OUT" << std::endl;
      outputter = new CppUnit::XmlOutputter(&runner.result(),
					    ofs, "shift_jis");
      static_cast<CppUnit::XmlOutputter*>(outputter)->setStyleSheet(xsl);
      break;
    case COMPILER_OUT :
      outputter = new CppUnit::CompilerOutputter(&runner.result(),*stream);
      break;
    }
  runner.setOutputter(outputter);
  runner.run();
  return 0; // runner.run() ? 0 : 1;
}
#endif // MAIN
#endif // RingBuffer_cpp
