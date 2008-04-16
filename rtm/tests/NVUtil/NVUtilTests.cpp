// -*- C++ -*-
/*!
 * @file   NVUtilTests.cpp
 * @brief  NVUtil test class
 * @date   $Date: 2006-11-27 08:26:13 $
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
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2006/11/15 09:47:18  kurihara
 * tests for find(),isString(),toString() are added.
 *
 * Revision 1.1  2006/11/14 07:23:16  kurihara
 * test program for NVUtil module. first commit.
 *
 */

#ifndef NVUtil_cpp
#define NVUtil_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/NVUtil.h>

/*!
 * @class NVUtilTests class
 * @brief NVUtil test
 */
namespace NVUtil
{
  using namespace NVUtil;
  using namespace std;
  
  int g_argc;
  vector<string> g_argv;
  
  class NVUtilTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(NVUtilTests);
    CPPUNIT_TEST(test_newNV);
    //  CPPUNIT_TEST(test_newNVStr);
    CPPUNIT_TEST(test_newNVChar);
    CPPUNIT_TEST(test_newNVBool);
    CPPUNIT_TEST(test_newNVOctet);
    CPPUNIT_TEST(test_copy);
    CPPUNIT_TEST(test_find);
    CPPUNIT_TEST(test_isString);
    CPPUNIT_TEST(test_toString);
    CPPUNIT_TEST_SUITE_END();
    
  private:
    
  public:
    
    /*!
     * @brief Constructor
     */
    NVUtilTests()
    {
      CORBA::ORB_var orb;
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }
      
      orb = CORBA::ORB_init(g_argc, argv);
    }
    
    /*!
     * @brief Destructor
     */
    ~NVUtilTests()
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
     * @brief newNV(char*,Value)�Υƥ���
     *   (1) newNV()���Ѥ�CORBA::Short���Υǡ�����name��NameValue�������
     *   (2) newNV()���Ϥ����ǡ����ȼ�������NameValue�����Ǥ���ӡ�
     *   (3) newNV()���Ѥ�CORBA::Long���Υǡ�����name��NameValue�������
     *   (4) newNV()���Ϥ����ǡ����ȼ�������NameValue�����Ǥ���ӡ�
     *   (5) newNV()���Ѥ�CORBA::Float���Υǡ�����name��NameValue�������
     *   (6) newNV()���Ϥ����ǡ����ȼ�������NameValue�����Ǥ���ӡ�
     *   (7) newNV()���Ѥ�CORBA::Double���Υǡ�����name��NameValue�������
     *   (8) newNV()���Ϥ����ǡ����ȼ�������NameValue�����Ǥ���ӡ�
     */
    void test_newNV() {
      CORBA::Short  setSt, getSt;
      CORBA::Long   setLg, getLg;
      CORBA::Float  setFt, getFt;
      CORBA::Double setDl, getDl;
      SDOPackage::NameValue nv;
      string setname, getname;
      
      // (1) newNV()���Ѥ�CORBA::Short���Υǡ�����name��NameValue�������
      setSt = 1;
      nv = newNV("short", setSt);
      
      // (2) newNV()���Ϥ����ǡ����ȼ�������NameValue�����Ǥ���ӡ�
      setname = "short";
      getname = nv.name;
      CPPUNIT_ASSERT(getname == setname);
      nv.value >>= getSt;
      CPPUNIT_ASSERT(setSt == getSt);
      
      
      
      // (3) newNV()���Ѥ�CORBA::Long���Υǡ�����name��NameValue�������
      setLg = 999999999;
      nv = newNV("long", setLg);
      
      // (4) newNV()���Ϥ����ǡ����ȼ�������NameValue�����Ǥ���ӡ�
      setname = "long";
      getname = nv.name;
      CPPUNIT_ASSERT(getname == setname);
      nv.value >>= getLg;
      CPPUNIT_ASSERT(setLg == getLg);
      
      
      
      // (5) newNV()���Ѥ�CORBA::Float���Υǡ�����name��NameValue�������
      setFt = 99999.9;
      nv = newNV("float", setFt);
      
      // (6) newNV()���Ϥ����ǡ����ȼ�������NameValue�����Ǥ���ӡ�
      setname = "float";
      getname = nv.name;
      CPPUNIT_ASSERT(getname == setname);
      nv.value >>= getFt;
      CPPUNIT_ASSERT(setFt == getFt);
      
      
      
      // (7) newNV()���Ѥ�CORBA::Double���Υǡ�����name��NameValue�������
      setDl = 9999999.999;
      nv = newNV("double", setDl);
      
      // (8) newNV()���Ϥ����ǡ����ȼ�������NameValue�����Ǥ���ӡ�
      setname = "double";
      getname = nv.name;
      CPPUNIT_ASSERT(getname == setname);
      nv.value >>= getDl;
      CPPUNIT_ASSERT(setDl == getDl);
    }
    
    
    /*!
     * @brief newNV(char*,char*)�Υƥ���
     *    (1) const char*����name��value��newNV()���Ϥ���NameValue��������롣
     */
    void test_newNVStr() {
      SDOPackage::NameValue nv;
      const char* name  = "string";
      const char* value = "string-data";
      // (1) const char*����name��value��newNV()���Ϥ���NameValue��������롣
      nv = newNV(name, value);
    }
    
    
    /*!
     * @brief newNVChar()�Υƥ���
     *   (1) CORBA::Char����value��char*����name��newNVChar()���Ϥ���NameValue��������롣
     *   (2) newNVChar()�˥��åȤ���name�ȼ�������NameValue.name����ӡ�
     *   (3) newNVChar()�˥��åȤ���value�ȼ�������NameValue.value����ӡ�
     */
    void test_newNVChar() {
      CORBA::Char ch = 'A', getch;
      SDOPackage::NameValue nv;
      // (1) CORBA::Char����value��char*����name��newNVChar()���Ϥ���NameValue��������롣
      nv = newNVChar("char", ch);
      
      string setstr, getstr;
      
      // (2) newNVChar()�˥��åȤ���name�ȼ�������NameValue.name����ӡ�
      setstr = "char";
      getstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // (3) newNVChar()�˥��åȤ���value�ȼ�������NameValue.value����ӡ�
      nv.value >>= CORBA::Any::to_char(getch);
      CPPUNIT_ASSERT(ch == getch);
    }
    
    
    /*!
     * @brief newNVBool()�Υƥ���
     */
    void test_newNVBool() {
      SDOPackage::NameValue nv;
      CORBA::Boolean setval=false, retval;
      
      nv = newNVBool("bool", setval);
      
      string setstr, getstr;
      
      setstr = "bool";
      getstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      nv.value >>= CORBA::Any::to_boolean(retval);
      CPPUNIT_ASSERT(setval == retval);
    }
    
    
    /*!
     * @brief newNVOctet()�Υƥ���
     */
    void test_newNVOctet() {
      SDOPackage::NameValue nv;
      CORBA::Octet setval=030, getval;
      
      nv = newNVOctet("octet", setval);
      
      string setstr, getstr;
      
      setstr = "octet";
      getstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      nv.value >>= CORBA::Any::to_octet(getval);
      CPPUNIT_ASSERT(setval == getval);
    }
    
    /*!
     * @brief copy()�Υƥ���
     *   (1) RTC::Properties���֥������Ȥ�����
     *   (2��copy()�ˤ�Properties���֥������Ȥ�nvlist�˥��ԡ�
     *   (3) NVList[0].value����ǡ��������
     *   (4) copy()�ˤ�������Ϳ����nvlist���񤭴������Ƥ��뤫���ǧ��
     */
    void test_copy() {
      SDOPackage::NVList nvlist;
      
      map<string, string> mProp;
      // (1) RTC::Properties���֥������Ȥ�����
      // �� Properties�Υ��󥹥ȥ饯���Ǥϰ�����Ϳ���줿map�Υ����ͤ�������¸����롣
      mProp["potr-type"];
      RTC::Properties prop(mProp);
      
      
      // (2��copy()�ˤ�Properties���֥������Ȥ�nvlist�˥��ԡ�
      copy(nvlist, prop);
      
      
      // (3) NVList[0].value����ǡ��������
      const char* getval;
      nvlist[0].value >>= getval;
      
      string setstr, getstr;
      
      
      // (4) copy()�ˤ�������Ϳ����nvlist���񤭴������Ƥ��뤫���ǧ��
      setstr = "potr-type";
      getstr = nvlist[0].name;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = "";
      getstr = getval;
      CPPUNIT_ASSERT(setstr == getstr);
      
    }
    
    
    /*!
     * @brief find()�Υƥ���
     *   (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
     *   (2) NVList���Ǥ�name��"long",value��long���Υǡ����򥻥åȡ�
     *   (3) nvlist���椫��NameValue.name��"long"��NameValue.value�������
     *   (4) nvlist���椫��NameValue.name��"short"��NameValue.value�������
     */
    void test_find() {
      SDOPackage::NVList nvlist;
      CORBA::Any any;
      CORBA::Short setst,getst;
      CORBA::Long  setlg,getlg;
      
      nvlist.length(2);
      
      // (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
      setst = 1;
      nvlist[0].name = "short";
      nvlist[0].value <<= setst;
      
      // (2) NVList���Ǥ�name��"long",value��long���Υǡ����򥻥åȡ�
      setlg =111;
      nvlist[1].name = "long";
      nvlist[1].value <<= setlg;
      
      // (3) nvlist���椫��NameValue.name��"long"��NameValue.value�������
      any = find(nvlist, "long");
      any >>= getlg;
      CPPUNIT_ASSERT(setlg == getlg);
      
      // (4) nvlist���椫��NameValue.name��"short"��NameValue.value�������
      any = find(nvlist, "short");
      any >>= getst;
      CPPUNIT_ASSERT(setst == getst);
    }
    
    
    /*!
     * @brief isString()�Υƥ���
     *   (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
     *   (2) NVList���Ǥ�name��"string",value��string���Υǡ����򥻥åȡ�
     *   (3) isString(nvlist,name)�ˤ�,���ꤵ�줿name��value�η���string���ɤ�����Ƚ�ꡣ
     *   (4) isString(nvlist,name)�ˤ�,���ꤵ�줿name��value�η���string���ɤ�����Ƚ�ꡣ
     */
    void test_isString() {
      bool result;
      SDOPackage::NVList nvlist;
      CORBA::Short setst;
      
      nvlist.length(2);
      
      // (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
      setst = 1;
      nvlist[0].name = "short";
      nvlist[0].value <<= setst;
      
      // (2) NVList���Ǥ�name��"string",value��string���Υǡ����򥻥åȡ�
      string str("test");
      nvlist[1].name = "string";
      nvlist[1].value <<= str.c_str();
      
      // (3) isString(nvlist,name)�ˤ�,���ꤵ�줿name��value�η���string���ɤ�����Ƚ�ꡣ
      result = isString(nvlist, "string");
      CPPUNIT_ASSERT(result == true);
      
      // (4) isString(nvlist,name)�ˤ�,���ꤵ�줿name��value�η���string���ɤ�����Ƚ�ꡣ
      result = isString(nvlist, "short");
      CPPUNIT_ASSERT(result == false);
      
    }
    
    
    /*!
     * @brief toString()�Υƥ���
     *   (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
     *   (2) NVList���Ǥ�name��"string",value��string���Υǡ����򥻥åȡ�
     *   (3) toString(nvlist,name)�ˤ�,���ꤵ�줿name��value��string�Ǽ�����
     *   (4) toString(nvlist,name)�ˤ�,���ꤵ�줿name��value��string�Ǽ�����
     */
    void test_toString() {
      string result;
      SDOPackage::NVList nvlist;
      CORBA::Short setst;
      
      nvlist.length(2);
      
      // (1) NVList���Ǥ�name��"short",value��short���Υǡ����򥻥åȡ�
      setst = 1;
      nvlist[0].name = "short";
      nvlist[0].value <<= setst;
      
      // (2) NVList���Ǥ�name��"string",value��string���Υǡ����򥻥åȡ�
      string str("test"), setstr;
      nvlist[1].name = "string";
      nvlist[1].value <<= str.c_str();
      
      // (3) toString(nvlist,name)�ˤ�,���ꤵ�줿name��value��string�Ǽ�����
      result = toString(nvlist, "string");
      setstr = "test";
      CPPUNIT_ASSERT(result == setstr);
      
      // Failure case:
      // 
      // (4) toString(nvlist,name)�ˤ�,���ꤵ�줿name��value��string�Ǽ�����
      result = toString(nvlist, "short");
      setstr = "";
      CPPUNIT_ASSERT(result == setstr);
    }
    
  };
}; // namespace NVUtil

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(NVUtil::NVUtilTests);

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
#endif // NVUtil_cpp
