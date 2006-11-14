// -*- C++ -*-
/*!
 * @file 
 * @brief test for NVUtil module.
 * @date $Date: 2006-11-14 07:23:16 $
 * @author Shinji Kurihara
 * $Id: NVUtilTests.cpp,v 1.1 2006-11-14 07:23:16 kurihara Exp $
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

#include "../NVUtil.h"

using namespace NVUtil;
using namespace std;

// NVUtil module �Υƥ���
class NVUtilTests
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(NVUtilTests);
  CPPUNIT_TEST(test_newNV);
  CPPUNIT_TEST(test_newNVStr);
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
   * @brief ���󥹥ȥ饯��
   */
  NVUtilTests()
  {
  }


  /*!
   * @brief �ǥ��ȥ饯��
   */
  ~NVUtilTests()
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
   */
  void test_newNVChar() {
  }


  /*!
   * @brief newNVBool()�Υƥ���
   */
  void test_newNVBool() {}


  /*!
   * @brief newNVOctet()�Υƥ���
   */
  void test_newNVOctet() {}


  /*!
   * @brief copy()�Υƥ���
   */
  void test_copy() {}


  /*!
   * @brief find()�Υƥ���
   */
  void test_find() {}


  /*!
   * @brief isString()�Υƥ���
   */
  void test_isString() {}


  /*!
   * @brief toString()�Υƥ���
   */
  void test_toString() {}

};


/*!
 * @brief register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(NVUtilTests);



int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
   
    return runner.run();
}
