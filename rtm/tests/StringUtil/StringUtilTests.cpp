// -*- C++ -*-
/*!
 * @file   StringUtilTests.cpp
 * @brief  StringUtil test class
 * @date   $Date: 2008/01/10 01:49:58 $
 * @author Noriaki Ando <n-ando@aist.go.jp>,
 *         Shinji Kurihara
 *
 * $Id$
 *
 */

/*
 * $Log: StringUtilTests.cpp,v $
 * Revision 1.2  2008/01/10 01:49:58  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2007/12/20 07:50:16  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2006/11/27 08:25:52  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.2  2006/10/23 07:38:37  n-ando
 * Some fixes for split() tests.
 *
 * Revision 1.1  2006/10/23 06:10:17  kurihara
 *
 * test program for StringUtil class.
 *
 *
 */

#ifndef StringUtil_cpp
#define StringUtil_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <fstream>
#include <iostream>
#include <rtm/StringUtil.h>

namespace StringUtil
{
  using namespace std;
  /*!
   * @class StringUtilTests
   * @brief StringUtil test
   */
  class StringUtilTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(StringUtilTests);
		
    CPPUNIT_TEST(test_isEscaped);
    CPPUNIT_TEST(test_escape);
    CPPUNIT_TEST(test_unescape);
    CPPUNIT_TEST(test_eraseHeadBlank);
    CPPUNIT_TEST(test_eraseTailBlank);
    CPPUNIT_TEST(test_replaceString);
    CPPUNIT_TEST(test_split);
    CPPUNIT_TEST(test_toBool);
    CPPUNIT_TEST(test_isAbsolutePath);
    CPPUNIT_TEST(test_isURL);
    CPPUNIT_TEST(test_unique_sv);
    CPPUNIT_TEST(test_flatten);
		
    CPPUNIT_TEST_SUITE_END();
		
  private:
	
  public:
		    
    /*!
     * @brief Constructor
     */
    StringUtilTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~StringUtilTests()
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
     * @brief isEscaped()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>���������פ���Ƥ���ʸ������Ф��ơ����������������פ���Ƥ����Ƚ��Ǥ��뤫��</li>
     * <li>���������פ���Ƥ��ʤ�ʸ������Ф��ơ����������������פ���Ƥ��ʤ���Ƚ��Ǥ��뤫��</li>
     * </ul>
     */
    void test_isEscaped()
    {
      vector<string> escapedStrs;
      escapedStrs.push_back("\\t");
      escapedStrs.push_back("\\n");
      escapedStrs.push_back("\\f");
      escapedStrs.push_back("\\r");

      for (unsigned int i = 0; i < escapedStrs.size(); i++) {
	string str = escapedStrs[i];
	CPPUNIT_ASSERT(isEscaped(str, str.length() - 1));
      }
			
      vector<string> noescapedStrs;
      noescapedStrs.push_back("\t");
      noescapedStrs.push_back("\n");
      noescapedStrs.push_back("\f");
      noescapedStrs.push_back("\r");

      for (unsigned int i = 0; i < noescapedStrs.size(); i++) {
	string str = noescapedStrs[i];
	CPPUNIT_ASSERT(! isEscaped(str, str.length() - 1));
      }
    }
		
    /*!
     * @brief espace()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>HT�����������������פ���뤫��</li>
     * <li>LF�����������������פ���뤫��</li>
     * <li>CR�����������������פ���뤫��</li>
     * <li>FF�����������������פ���뤫��</li>
     * <li>�Хå�����å���ʸ�������������������פ���뤫��</li>
     * </ul>
     */
    void test_escape()
    {
      // (1) \t�����������������פ���뤫��
      string target1 = "\t";
      string expected1 = "\\t";
      CPPUNIT_ASSERT_EQUAL(expected1, escape(target1));
			
      // (2) \n�����������������פ���뤫��
      string target2 = "\n";
      string expected2 = "\\n";
      CPPUNIT_ASSERT_EQUAL(expected2, escape(target2));

      // (3) \f�����������������פ���뤫��
      string target3 = "\f";
      string expected3 = "\\f";
      CPPUNIT_ASSERT_EQUAL(expected3, escape(target3));

      // (4) \r�����������������פ���뤫��
      string target4 = "\r";
      string expected4 = "\\r";
      CPPUNIT_ASSERT_EQUAL(expected4, escape(target4));
			
      // (5) �����������оݳ��Ǥ�����֥륯�����Ȥϡ����������פ��줺���Τޤޤ���
      string target5 = "\"";
      string expected5 = "\"";
      CPPUNIT_ASSERT_EQUAL(expected5, escape(target5));
			
      // (6) �����������оݳ��Ǥ��륷�󥰥륯�����Ȥϡ����������פ��줺���Τޤޤ���
      string target6 = "'";
      string expected6 = "'";
      CPPUNIT_ASSERT_EQUAL(expected6, escape(target6));
			
      // (7) \�ʥХå�����å���ʸ���ˤϡ����������������פ���뤫��
      string target7 = "\\";
      string expected7 = "\\\\";
      CPPUNIT_ASSERT_EQUAL(expected7, escape(target7));
			
      // (8) �����������оݤ�ʸ����ʣ���ޤ�ʸ����ϡ����������������פ���뤫��
      string target8 = "\tHello!\t";
      string expected8 = "\\tHello!\\t";
      CPPUNIT_ASSERT_EQUAL(expected8, escape(target8));
    }
		
    /*!
     * @brief unescape()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>"\t"�����������󥨥������פ���뤫��</li>
     * <li>"\n"�����������󥨥������פ���뤫��</li>
     * <li>"\f"�����������󥨥������פ���뤫��</li>
     * <li>"\r"�����������󥨥������פ���뤫��</li>
     * <li>���󥰥륯�����ȡ�'�ˤ����������󥨥������פ���뤫��</li>
     * <li>���֥륯�����ȡ�"�ˤ����������󥨥������פ���뤫��</li>
     * </ul>
     */
    void test_unescape()
    {
      // (1) \t�����������󥨥������פ���뤫��
      string target1 = "\\t";
      string expected1 = "\t";
      CPPUNIT_ASSERT_EQUAL(expected1, unescape(target1));
			
      // (2) \n�����������󥨥������פ���뤫��
      string target2 = "\\n";
      string expected2 = "\n";
      CPPUNIT_ASSERT_EQUAL(expected2, unescape(target2));

      // (3) \f�����������󥨥������פ���뤫��
      string target3 = "\\f";
      string expected3 = "\f";
      CPPUNIT_ASSERT_EQUAL(expected3, unescape(target3));

      // (4) \r�����������󥨥������פ���뤫��
      string target4 = "\\r";
      string expected4 = "\r";
      CPPUNIT_ASSERT_EQUAL(expected4, unescape(target4));
			
      // (5) ���֥륯�����Ȥϡ����������������פ���뤫��
      string target5 = "\\\"";
      string expected5 = "\"";
      CPPUNIT_ASSERT_EQUAL(expected5, unescape(target5));
			
      // (6) ���󥰥륯�����Ȥϡ����������������פ���뤫��
      string target6 = "\\'";
      string expected6 = "'";
      CPPUNIT_ASSERT_EQUAL(expected6, unescape(target6));
			
      // (7) \�ʥХå�����å���ʸ���ˤϡ����������������פ���뤫��
      string target7 = "\\\\";
      string expected7 = "\\";
      CPPUNIT_ASSERT_EQUAL(expected7, unescape(target7));
			
      // (8) ���󥨥��������оݤ�ʸ����ʣ���ޤ�ʸ����ϡ����������󥨥������פ���뤫��
      string target8 = "\\tHello!\\t";
      string expected8 = "\tHello!\t";
      CPPUNIT_ASSERT_EQUAL(expected8, unescape(target8));
    }
		
    /*!
     * @brief eraseHeadBlank()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>��Ƭ�˶���ʸ����ޤޤʤ���硢�Ѳ������ˤ��Τޤޤ���</li>
     * <li>��Ƭ�˥��ڡ�����ʸ�������ޤ��硢�����������뤫��</li>
     * <li>��Ƭ�˥��ڡ�����ʣ��ʸ���ޤ��硢�����������뤫��</li>
     * <li>��Ƭ�˥��֤򣱤Ĥ����ޤ��硢�����������뤫��</li>
     * <li>��Ƭ�˥��֤�ʣ���ޤ��硢�����������뤫��</li>
     * <li>��Ƭ�˥��ڡ����ȥ��֤����ߤ��ƴޤޤ���硢�����������뤫��</li>
     * </ul>
     */
    void test_eraseHeadBlank()
    {
      // (1) ��Ƭ�˶���ʸ����ޤޤʤ���硢�Ѳ������ˤ��Τޤޤ���
      string target1 = "Hello, World! ";
      string expected1 = "Hello, World! ";
      eraseHeadBlank(target1);
      CPPUNIT_ASSERT_EQUAL(expected1, target1);
			
      // (2) ��Ƭ�˥��ڡ�����ʸ�������ޤ��硢�����������뤫��
      string target2 = " Hello, World! ";
      string expected2 = "Hello, World! ";
      eraseHeadBlank(target2);
      CPPUNIT_ASSERT_EQUAL(expected2, target2);
			
      // (3) ��Ƭ�˥��ڡ�����ʣ��ʸ���ޤ��硢�����������뤫��
      string target3 = "     Hello, World! ";
      string expected3 = "Hello, World! ";
      eraseHeadBlank(target3);
      CPPUNIT_ASSERT_EQUAL(expected3, target3);
			
      // (4) ��Ƭ�˥��֤򣱤Ĥ����ޤ��硢�����������뤫��
      string target4 = "\tHello, World! ";
      string expected4 = "Hello, World! ";
      eraseHeadBlank(target4);
      CPPUNIT_ASSERT_EQUAL(expected4, target4);
			
      // (5) ��Ƭ�˥��֤�ʣ���ޤ��硢�����������뤫��
      string target5 = "\t\t\tHello, World! ";
      string expected5 = "Hello, World! ";
      eraseHeadBlank(target5);
      CPPUNIT_ASSERT_EQUAL(expected5, target5);
			
      // (6) ��Ƭ�˥��ڡ����ȥ��֤����ߤ��ƴޤޤ���硢�����������뤫��
      string target6 = " \t\t  \t Hello, World! ";
      string expected6 = "Hello, World! ";
      eraseHeadBlank(target6);
      CPPUNIT_ASSERT_EQUAL(expected6, target6);
    }
		
    /*!
     * @brief eraseTailBlank()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>�Ǹ����˶���ʸ����ޤޤʤ���硢�Ѵ����줺�ˤ��Τޤ޻Ĥ뤫��</li>
     * <li>�Ǹ����˥��ڡ�����ʸ�������ޤ��硢�����������뤫��</li>
     * <li>�Ǹ����˥��ڡ�����ʣ��ʸ���ޤ��硢�����������뤫��</li>
     * <li>�Ǹ����˥��֤�ʸ�������ޤ��硢�����������뤫��</li>
     * <li>�Ǹ����˥��֤�ʣ���ޤ��硢�����������뤫��</li>
     * <li>�Ǹ����˥��ڡ����ȥ��֤򺮺ߤ��ƴޤ��硢�����������뤫��</li>
     * </ul>
     */
    void test_eraseTailBlank()
    {
      // (1) �Ǹ����˶���ʸ����ޤޤʤ���硢�Ѵ����줺�ˤ��Τޤ޻Ĥ뤫��
      string target1 = " Hello, World!";
      string expected1 = " Hello, World!";
      eraseTailBlank(target1);
      CPPUNIT_ASSERT_EQUAL(expected1, target1);
			
      // (2) �Ǹ����˥��ڡ�����ʸ�������ޤ��硢�����������뤫��
      string target2 = " Hello, World! ";
      string expected2 = " Hello, World!";
      eraseTailBlank(target2);
      CPPUNIT_ASSERT_EQUAL(expected2, target2);
			
      // (3) �Ǹ����˥��ڡ�����ʣ��ʸ���ޤ��硢�����������뤫��
      string target3 = " Hello, World!   ";
      string expected3 = " Hello, World!";
      eraseTailBlank(target3);
      CPPUNIT_ASSERT_EQUAL(expected3, target3);
			
      // (4) �Ǹ����˥��֤�ʸ�������ޤ��硢�����������뤫��
      string target4 = " Hello, World!\t";
      string expected4 = " Hello, World!";
      eraseTailBlank(target4);
      CPPUNIT_ASSERT_EQUAL(expected4, target4);
			
      // (5) �Ǹ����˥��֤�ʣ���ޤ��硢�����������뤫��
      string target5 = " Hello, World!\t\t\t";
      string expected5 = " Hello, World!";
      eraseTailBlank(target5);
      CPPUNIT_ASSERT_EQUAL(expected5, target5);
			
      // (6) �Ǹ����˥��ڡ����ȥ��֤򺮺ߤ��ƴޤ��硢�����������뤫��
      string target6 = " Hello, World!\t\t \t   \t ";
      string expected6 = " Hello, World!";
      eraseTailBlank(target6);
      CPPUNIT_ASSERT_EQUAL(expected6, target6);
    }
		
    /*!
     * @brief replaceString()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>�ִ�����ʸ�����ִ��壱ʸ���ξ�硢�������ִ��Ǥ��뤫��</li>
     * <li>�ִ�����ʸ�����ִ���ʣ��ʸ���ξ�硢�������ִ��Ǥ��뤫��</li>
     * <li>�ִ���ʣ��ʸ�����ִ��壱ʸ���ξ�硢�������ִ��Ǥ��뤫��</li>
     * <li>�ִ���ʣ��ʸ�����ִ���ʣ��ʸ���ξ�硢�������ִ��Ǥ��뤫��</li>
     * </ul>
     */
    void test_replaceString()
    {
      // (1) �ִ�����ʸ�����ִ��壱ʸ���ξ�硢�������ִ��Ǥ��뤫��
      string target1 = "*Hello,*World!*";
      string expected1 = " Hello, World! ";
      replaceString(target1, "*", " ");
      CPPUNIT_ASSERT_EQUAL(expected1, target1);
			
      // (2) �ִ�����ʸ�����ִ���ʣ��ʸ���ξ�硢�������ִ��Ǥ��뤫��
      string target2 = "*Hello,*World!*";
      string expected2 = " - Hello, - World! - ";
      replaceString(target2, "*", " - ");
      CPPUNIT_ASSERT_EQUAL(expected2, target2);

      // (3) �ִ���ʣ��ʸ�����ִ��壱ʸ���ξ�硢�������ִ��Ǥ��뤫��
      string target3 = "*|-Hello,*|-World!*|-";
      string expected3 = " Hello, World! ";
      replaceString(target3, "*|-", " ");
      CPPUNIT_ASSERT_EQUAL(expected3, target3);
			
      // (4) �ִ���ʣ��ʸ�����ִ���ʣ��ʸ���ξ�硢�������ִ��Ǥ��뤫��
      string target4 = "*|-Hello,*|-World!*|-";
      string expected4 = " - Hello, - World! - ";
      replaceString(target4, "*|-", " - ");
      CPPUNIT_ASSERT_EQUAL(expected4, target4);
    }
		
    /*!
     * @brief split()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>�ǥ�ߥ�����ʸ���ξ�硢������ʬ��Ǥ��뤫��</li>
     * <li>�ǥ�ߥ���ʣ��ʸ���ξ�硢������ʬ��Ǥ��뤫��</li>
     * <li>ʬ�䤵�줿ʸ�������ҤΤ�����ʸ����Ĺ���Τ�ΤϽ����뤫��</li>
     * </ul>
     */
    void test_split()
    {
      // (1) �ǥ�ߥ�����ʸ���ξ�硢������ʬ��Ǥ��뤫��
      string target1 = "It's|a|small|world.";
      string expected1[] = {"It's", "a", "small", "world."};
      vector<string> splited1 = split(target1, "|");
      CPPUNIT_ASSERT_EQUAL(4, (int) splited1.size());
      CPPUNIT_ASSERT_EQUAL(expected1[0], splited1[0]);
      CPPUNIT_ASSERT_EQUAL(expected1[1], splited1[1]);
      CPPUNIT_ASSERT_EQUAL(expected1[2], splited1[2]);
      CPPUNIT_ASSERT_EQUAL(expected1[3], splited1[3]);
			
      // (2) �ǥ�ߥ���ʣ��ʸ���ξ�硢������ʬ��Ǥ��뤫��
      string target2 = "It's*-*a*-*small*-*world.";
      string expected2[] = {"It's", "a", "small", "world."};
      vector<string> splited2 = split(target2, "*-*");
      CPPUNIT_ASSERT_EQUAL(4, (int) splited2.size());
      CPPUNIT_ASSERT_EQUAL(expected2[0], splited2[0]);
      CPPUNIT_ASSERT_EQUAL(expected2[1], splited2[1]);
      CPPUNIT_ASSERT_EQUAL(expected2[2], splited2[2]);
      CPPUNIT_ASSERT_EQUAL(expected2[3], splited2[3]);
			
      // (3) ʬ�䤵�줿ʸ�������ҤΤ�����ʸ����Ĺ���Τ�ΤϽ����뤫��
      string target3 = "@It's@@a@@@small@@@@world.@@@@@";
      string expected3[] = {"It's", "a", "small", "world."};
      vector<string> splited3 = split(target3, "@");
      CPPUNIT_ASSERT_EQUAL(4, (int) splited3.size());
      CPPUNIT_ASSERT_EQUAL(expected3[0], splited3[0]);
      CPPUNIT_ASSERT_EQUAL(expected3[1], splited3[1]);
      CPPUNIT_ASSERT_EQUAL(expected3[2], splited3[2]);
      CPPUNIT_ASSERT_EQUAL(expected3[3], splited3[3]);
    }
		
    /*!
     * @brief toBool()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>trueɽ��ʸ����˰��פ����ǥե���Ȥ�true�ξ��ˡ�������true�Ȥʤ뤫��</li>
     * <li>trueɽ��ʸ����˰��פ����ǥե���Ȥ�false�ξ��ˡ�������true�Ȥʤ뤫��</li>
     * <li>falseɽ��ʸ����˰��פ����ǥե���Ȥ�true�ξ��ˡ�������false�Ȥʤ뤫��</li>
     * <li>falseɽ��ʸ����˰��פ����ǥե���Ȥ�false�ξ��ˡ�������false�Ȥʤ뤫��</li>
     * <li>true/false�������ɽ��ʸ����ˤ���פ������ǥե���Ȥ�true�ξ��ˡ�������true�Ȥʤ뤫��</li>
     * <li>true/false�������ɽ��ʸ����ˤ���פ������ǥե���Ȥ�false�ξ��ˡ�������false�Ȥʤ뤫��</li>
     * </ul>
     */
    void test_toBool()
    {
      string T = "TRUE";
      string F = "FALSE";
			
      // (1) trueɽ��ʸ����˰��פ����ǥե���Ȥ�true�ξ��ˡ�������true�Ȥʤ뤫��
      CPPUNIT_ASSERT_EQUAL(true, toBool("TRUE", T, F, true));
			
      // (2) trueɽ��ʸ����˰��פ����ǥե���Ȥ�false�ξ��ˡ�������true�Ȥʤ뤫��
      CPPUNIT_ASSERT_EQUAL(true, toBool("TRUE", T, F, false));
			
      // (3) falseɽ��ʸ����˰��פ����ǥե���Ȥ�true�ξ��ˡ�������false�Ȥʤ뤫��
      CPPUNIT_ASSERT_EQUAL(false, toBool("FALSE", T, F, true));
			
      // (4) falseɽ��ʸ����˰��פ����ǥե���Ȥ�false�ξ��ˡ�������false�Ȥʤ뤫��
      CPPUNIT_ASSERT_EQUAL(false, toBool("FALSE", T, F, false));
			
      // (5) true/false�������ɽ��ʸ����ˤ���פ������ǥե���Ȥ�true�ξ��ˡ�������true�Ȥʤ뤫��
      CPPUNIT_ASSERT_EQUAL(true, toBool("UNKNOWN", T, F, true));
			
      // (6) true/false�������ɽ��ʸ����ˤ���פ������ǥե���Ȥ�false�ξ��ˡ�������false�Ȥʤ뤫��
      CPPUNIT_ASSERT_EQUAL(false, toBool("UNKNOWN", T, F, false));
    }
		
    /*!
     * @brief isAbsolutePath()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>��Ƭʸ������/�פξ�硢���Хѥ���Ƚ�ꤵ��뤫��</li>
     * <li>��Ƭ��ʸ������../�פξ�硢���Хѥ���Ƚ�ꤵ��뤫��</li>
     * <li>��Ƭ��ʸ����������ե��٥å� + ��:\�פξ�硢���Хѥ���Ƚ�ꤵ��뤫��</li>
     * <li>��Ƭ��ʸ������..\�פξ�硢���Хѥ���Ƚ�ꤵ��뤫��</li>
     * <li>��Ƭ��ʸ������\\�פξ�硢���Хѥ���Ƚ�ꤵ��뤫��</li>
     * </ul>
     */
    void test_isAbsolutePath()
    {
      // (1) ��Ƭʸ������/�פξ�硢���Хѥ���Ƚ�ꤵ��뤫��
      CPPUNIT_ASSERT_EQUAL(true, isAbsolutePath("/usr/local/lib"));
			
      // (2) ��Ƭ��ʸ������../�פξ�硢���Хѥ���Ƚ�ꤵ��뤫��
      CPPUNIT_ASSERT_EQUAL(false, isAbsolutePath("../usr/local/lib"));
			
      // (3) ��Ƭ��ʸ����������ե��٥å� + ��:\�פξ�硢���Хѥ���Ƚ�ꤵ��뤫��
      CPPUNIT_ASSERT_EQUAL(true, isAbsolutePath("C:\\Program Files"));
			
      // (4) ��Ƭ��ʸ������..\�פξ�硢���Хѥ���Ƚ�ꤵ��뤫��
      CPPUNIT_ASSERT_EQUAL(false, isAbsolutePath("..\\Program Files"));
			
      // (5) ��Ƭ��ʸ������\\�פξ�硢���Хѥ���Ƚ�ꤵ��뤫��
      CPPUNIT_ASSERT_EQUAL(true, isAbsolutePath("\\\\server01"));
    }
		
    /*!
     * @brief isURL()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>1ʸ���ʾ��ʸ���� + ��://�פǻϤޤ���ˡ�URL�Ȥ���Ƚ�ꤵ��뤫��</li>
     * <li>��://�פǻϤޤ���ˡ�URL�ǤϤʤ���Ƚ�ꤵ��뤫��</li>
     * </ul>
     */
    void test_isURL()
    {
      // (1) 1ʸ���ʾ��ʸ����ܡ�://�פǻϤޤ���ˡ�URL�Ȥ���Ƚ�ꤵ��뤫��
      CPPUNIT_ASSERT_EQUAL(true, isURL("http://domain"));
			
      // (2) ��://�פǻϤޤ���ˡ�URL�ǤϤʤ���Ƚ�ꤵ��뤫��
      CPPUNIT_ASSERT_EQUAL(false, isURL("://domain"));
    }
		
    /*!
     * @brief unique_sv()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>��ʣ�����ʸ����٥������Ф��ơ���ʣ������������Ǥ��뤫��</li>
     * </ul>
     */
    void test_unique_sv()
    {
      // ��ʣ����ĥ٥������������
      vector<string> overlappedStrs;
      overlappedStrs.push_back("unique1");
      overlappedStrs.push_back("overlapped1");
      overlappedStrs.push_back("unique2");
      overlappedStrs.push_back("overlapped1");
      overlappedStrs.push_back("overlapped2");
      overlappedStrs.push_back("overlapped2");
      overlappedStrs.push_back("unique3");
			
      // ��ʣ�����δ����ͤȤʤ�٥������������
      vector<string> expectedStrs;
      expectedStrs.push_back("unique1");
      expectedStrs.push_back("overlapped1");
      expectedStrs.push_back("unique2");
      expectedStrs.push_back("overlapped2");
      expectedStrs.push_back("unique3");
			
      // ��ʣ���������Ԥ�
      vector<string> uniqueStrs = unique_sv(overlappedStrs);
      sort(uniqueStrs.begin(), uniqueStrs.end());
      sort(expectedStrs.begin(), expectedStrs.end());
			
      // ��ʣ������������줿���������ͤ���Ӥ��ƥ����å�����
      CPPUNIT_ASSERT_EQUAL(expectedStrs.size(), uniqueStrs.size());
      for (vector<string>::size_type i = 0; i < expectedStrs.size(); i++) {
	CPPUNIT_ASSERT_EQUAL(expectedStrs[i], uniqueStrs[i]);
      }
    }
		
    /*!
     * @brief flatten()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>���֤�ޤ�ʸ����ˤĤ��ơ����������Ϥ���뤫��</li>
     * <li>����ޤ�ޤ�ʸ����ˤĤ��ơ����������Ϥ���뤫���ʥ���ޤ����������פ���뤳�ȤϤʤ����ͤ�����Ȥ��ơ�</li>
     * </ul>
     */
    void test_flatten()
    {
      vector<string> values;
      values.push_back("value"); // �̾��ʸ����
      values.push_back("\ttabbed\t"); // ���֤�ޤ�ʸ����
      values.push_back("hello, world"); // ����ޤ�ޤ�ʸ����
			
      string flattened = flatten(values);
      string expected = "value, \ttabbed\t, hello, world";
      CPPUNIT_ASSERT_EQUAL(expected, flattened);
    }
		
  };
}; // namespace StringUtil

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(StringUtil::StringUtilTests);

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
#endif // StringUtil_cpp
