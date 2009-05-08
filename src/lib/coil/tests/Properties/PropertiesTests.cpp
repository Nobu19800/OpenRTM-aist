// -*- C++ -*-
/*!
 * @file   PropertiesTests.cpp
 * @brief  Properties test class
 * @date   $Date: 2008/01/09 04:12:46 $
 * @author Noriaki Ando <n-ando@aist.go.jp>,
 *         Shinji Kurihara
 *
 *  $Id$
 *
 */

/*
 * $Log: PropertiesTests.cpp,v $
 * Revision 1.3  2008/01/09 04:12:46  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2008/01/08 07:53:11  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2006/11/27 08:23:25  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.3  2006/10/18 05:59:55  kurihara
 *
 * test_list(),test_load(),test_store() added and It is a revision generally.
 *
 */

#ifndef Properties_cpp
#define Properties_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <fstream>
#include <coil/Properties.h>
#include <algorithm>

/*!
 * @class PropertiesTests class
 * @brief Properties test
 */
using namespace std;

typedef std::map<std::string, std::string>::iterator Itr;

namespace Properties
{
  class PropertiesTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PropertiesTests);
		
    CPPUNIT_TEST(test_ctor_char_char);
    CPPUNIT_TEST(test_ctor_map);
    CPPUNIT_TEST(test_ctor_char);
    CPPUNIT_TEST(test_copy_ctor);
    CPPUNIT_TEST(test_substitute);
    CPPUNIT_TEST(test_dtor);

    CPPUNIT_TEST(test_getName);
    CPPUNIT_TEST(test_getValue);
    CPPUNIT_TEST(test_getDefaultValue);
    CPPUNIT_TEST(test_getLeaf);
    CPPUNIT_TEST(test_getRoot);

    CPPUNIT_TEST(test_getProperty);
    CPPUNIT_TEST(test_getPropertyDefault);
    CPPUNIT_TEST(test_opbrace_rhs);
    CPPUNIT_TEST(test_opbrace_lhs);
    CPPUNIT_TEST(test_getDefault);   
    CPPUNIT_TEST(test_setProperty);
    CPPUNIT_TEST(test_setDefault);
    CPPUNIT_TEST(test_setDefaults);

    CPPUNIT_TEST(test_list);
    CPPUNIT_TEST(test_load);
    CPPUNIT_TEST(test_store);

    CPPUNIT_TEST(test_propertyNames);
    CPPUNIT_TEST(test_size);
    CPPUNIT_TEST(test_findNode);
    CPPUNIT_TEST(test_getNode);
    CPPUNIT_TEST(test_createNode);
    CPPUNIT_TEST(test_removeNode);
    CPPUNIT_TEST(test_hasKey);
    CPPUNIT_TEST(test_clear);
    CPPUNIT_TEST(test_streamInput);

    CPPUNIT_TEST(test_splitKeyValue);


	
    CPPUNIT_TEST_SUITE_END();
		
  private:
    string EMPTY_STRING;
    map<string, string> DEFAULTS_CONF;
		
//    RTC::Properties* m_prop;
    coil::Properties* m_prop;
    
  public:
    /*!
     * @brief Constructor
     */
    PropertiesTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~PropertiesTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      EMPTY_STRING = "";
			
      DEFAULTS_CONF["rtc.openrtm.version"] = "0.4.0";
      DEFAULTS_CONF["rtc.openrtm.release"] = "aist";
      DEFAULTS_CONF["rtc.openrtm.vendor"] = "AIST";
      DEFAULTS_CONF["rtc.openrtm.author"] = "Noriaki Ando";
      DEFAULTS_CONF["rtc.manager.nameserver"] = "zonu.a02.aist.go.jp";
      DEFAULTS_CONF["rtc.manager.debug.level"] = "PARANOID";
      DEFAULTS_CONF["rtc.manager.orb"] = "omniORB";
      DEFAULTS_CONF["rtc.manager.orb.options"] =
        "IIOPAddrPort, -ORBendPoint, giop:tcp:";
      DEFAULTS_CONF["rtc.manager.arch"] = "i386";
      DEFAULTS_CONF["rtc.manager.os"] = "FreeBSD";
      DEFAULTS_CONF["rtc.manager.os.release"] = "6.1-RELEASE";
      DEFAULTS_CONF["rtc.manager.language"] = "C++";
      DEFAULTS_CONF["rtc.manager.subsystems"] =
        "Camera, Manipulator, Force Sensor";
      DEFAULTS_CONF["rtc.component.conf.path"] =
        "C:\\\\Program\\\\ Files\\\\OpenRTM-aist";
      DEFAULTS_CONF["rtc.manager.opening_message"] = "\"Hello \" World\"";
    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }

    /*!
     * @brief Properties(const char*, const char*)���󥹥ȥ饯���Υƥ���
     */
    void test_ctor_char_char()
    {
    }
		
    /*!
     * @brief Properties(std::map<string, string>&)���󥹥ȥ饯���Υƥ���
     * 
     * <ul>
     * <li>std::map�ǻ��ꤷ���ǥե�����ͤ����ǥե�����ͤȤ�����������
     * ������뤫��</li>
     * </ul>
     */
    void test_ctor_map()
    {
      map<string, string> defaults;
      defaults["rtc.component.conf.path"] = "C:\\Program\\ Files\\OpenRTM-aist";
      defaults["rtc.manager.arch"] = "i386";
      defaults["rtc.manager.debug.level"] = "PARANOID";
      defaults["rtc.manager.language"] = "C++";
      defaults["rtc.manager.nameserver"] = "zonu.a02.aist.go.jp";
      defaults["rtc.manager.opening_message"] = "Hello World";
      defaults["rtc.manager.orb.name"] = "omniORB";
      defaults["rtc.manager.orb.options"] =
        "IIOPAddrPort, -ORBendPoint, giop:tcp:";
      defaults["rtc.manager.os.name"] = "FreeBSD";
      defaults["rtc.manager.os.release"] = "6.1-RELEASE";
      defaults["rtc.manager.subsystems"] = "Camera, Manipulator, Force Sensor";
      defaults["rtc.openrtm.author"] = "Noriaki Ando";
      defaults["rtc.openrtm.release"] = "aist";
      defaults["rtc.openrtm.vendor"] = "AIST TaskIntelligence";
      defaults["rtc.openrtm.version"] = "0.4.0";
			
      /* map�ˤ��ǥե�����ͻ����Properties���֥������Ȥ���������    */
      coil::Properties prop(defaults);
			
      /* �ƥץ�ѥƥ��Υǥե�����ͤ�����̾��ͤ�������⡢���󥹥ȥ饯 */
      /* ���ǻ��ꤷ���ͤǼ�������뤳�Ȥ��ǧ����                       */
      map<string, string>::iterator it;
      it = defaults.begin();
      for (; it != defaults.end(); ++it) {
	string key = it->first;
	string value = it->second;
	CPPUNIT_ASSERT_EQUAL(value, prop.getDefault(key));
	CPPUNIT_ASSERT_EQUAL(value, prop.getProperty(key));
      }
    }
		
    /*!
     * @brief Properties(const char*[])���󥹥ȥ饯���Υƥ���
     * 
     * <ul>
     * <li>std::map�ǻ��ꤷ���ǥե�����ͤ����ǥե�����ͤȤ�����������
     * ������뤫��</li>
     * </ul>
     */		
    void test_ctor_char()
    {
      const char* defaults[] = {
	"rtc.component.conf.path", "C:\\Program\\ Files\\OpenRTM-aist",
	"rtc.manager.arch", "i386",
	"rtc.manager.debug.level", "PARANOID",
	"rtc.manager.language", "C++",
	"rtc.manager.nameserver", "zonu.a02.aist.go.jp",
	"rtc.manager.opening_message", "Hello World",
	"rtc.manager.orb.name", "omniORB",
	"rtc.manager.orb.options", "IIOPAddrPort, -ORBendPoint, giop:tcp:",
	"rtc.manager.os.name", "FreeBSD",
	"rtc.manager.os.release", "6.1-RELEASE",
	"rtc.manager.subsystems", "Camera, Manipulator, Force Sensor",
	"rtc.openrtm.author", "Noriaki Ando",
	"rtc.openrtm.release", "aist",
	"rtc.openrtm.vendor", "AIST TaskIntelligence",
	"rtc.openrtm.version", "0.4.0",
	""
      };
			
      coil::Properties prop(defaults);
      /* �ƥץ�ѥƥ��Υǥե�����ͤ�����̾��ͤ�������⡢���󥹥ȥ饯 */
      /* ���ǻ��ꤷ���ͤǼ�������뤳�Ȥ��ǧ����                       */
      for (int i = 0; defaults[i] != ""; i += 2) {
	string key = defaults[i];
	string value = defaults[i + 1];
	CPPUNIT_ASSERT_EQUAL(value, prop.getDefault(key));
	CPPUNIT_ASSERT_EQUAL(value, prop.getProperty(key));
      }
    }

    /*!
     * @brief copy ctro test
     */
    void test_copy_ctor()
    {
    }

    /*!
     * @brief =�黻�ҡ������黻�ҡˤΥƥ���
     * 
     * <ul>
     * <li>�ǥե�����͡��̾��ͤΤ���������ꤵ��Ƥ�����ˡ������ξ
     * ������������������뤫��</li>
     * <li>�ǥե�����ͤΤ����ꤵ��Ƥ��ꡢ�̾��ͤ����ꤵ��Ƥ��ʤ����
     * �ˡ������ξ������������������뤫��</li>
     * <li>�ǥե�����ͤ����ꤵ��Ƥ��ʤ������̾��ͤ����ꤵ��Ƥ�����
     * �ˡ������ξ������������������뤫��</li>
     * </ul>
     */
    void test_substitute()
    {
      /* �������Ȥʤ�Properties��������� */
      coil::Properties propSrc;
			
      /* (1) �ǥե�����͡��̾��ͤΤ���������ꤵ��Ƥ����� */
      string key1 = "key1";
      string key1DefaultValue = "key1-default-value";
      string key1Value = "key1-value";
      propSrc.setDefault(key1, key1DefaultValue);
      propSrc.setProperty(key1, key1Value);
			
      /* (2) �ǥե�����ͤΤ����ꤵ��Ƥ��ꡢ�̾��ͤ����ꤵ��Ƥ��ʤ���� */
      string key2 = "key2";
      string key2DefaultValue = "key2-default-value";
      propSrc.setDefault(key2, key2DefaultValue);
			
      /* (3) �ǥե�����ͤ����ꤵ��Ƥ��ʤ������̾��ͤ����ꤵ��Ƥ����� */
      string key3 = "key3";
      string key3Value = "key3-value";
      propSrc.setProperty(key3, key3Value);
			
      /* ������Ԥ������줾��ξ��ǡ��������������줿���Ȥ��ǧ���� */
      coil::Properties prop;
      prop = propSrc;
			
      CPPUNIT_ASSERT_EQUAL(key1DefaultValue, prop.getDefault(key1));
      CPPUNIT_ASSERT_EQUAL(key1Value, prop.getProperty(key1));
      CPPUNIT_ASSERT_EQUAL(key2DefaultValue, prop.getDefault(key2));
      CPPUNIT_ASSERT_EQUAL(key2DefaultValue, prop.getProperty(key2));
      CPPUNIT_ASSERT_EQUAL(EMPTY_STRING, prop.getDefault(key3));
      CPPUNIT_ASSERT_EQUAL(key3Value, prop.getProperty(key3));
    }

    /*!
     * @brief dtor test
     *
     * �Ρ��ɰʲ������٤Ƥ����Ǥ��������뤫�Υƥ���
     */
    void test_dtor()
    {
    }

    /*!
     * @brief getName test
     *
     * �Ρ��ɤ��ݻ�����̾�Τ��������ƥ���
     */
    void test_getName()
    {
    }
    
    /*!
     * @brief getValue test
     *
     * �Ρ��ɤ��ݻ������ͤ��������ƥ���
     */		
    void test_getValue()
    {
    }

    /*!
     * @brief getDefaultValue test
     *
     * �Ρ��ɤ��ݻ�����ǥե�����ͤ��������ƥ���
     */		
    void test_getDefaultValue()
    {
    }
	

    /*!
     * @brief getLeaf test
     *
     * �Ρ��ɤ��ݻ���������Ǥ��������ƥ���
     */		
    void test_getLeaf()
    {
    }

    /*!
     * @brief getLeaf test
     *
     * �Ρ��ɤ��ݻ���������Ǥ��������ƥ���
     */		
    void test_getRoot()
    {
    }

    /*!
     * @brief getProperty()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>�ǥե�����ͤ����ꤵ��Ƥ��ꡢ�����̾���ͤ����ꤵ��Ƥ����
     *     ��ˡ��ץ�ѥƥ��ͤȤ����������̾���ͤ���������뤫��</li>
     * <li>�ǥե�����ͤ����ꤵ��Ƥ��뤬���̾���ͤ����ꤵ��Ƥ��ʤ���
     *     ��ˡ��ץ�ѥƥ��ͤȤ����������ǥե�����ͤ���������뤫��</li>
     * <li>�ǥե�����ͤ����ꤵ��Ƥ��ʤ������̾���ͤ����ꤵ��Ƥ����
     *     ��ˡ��ץ�ѥƥ��ͤȤ����������̾���ͤ���������뤫��</li>
     * <li>�ǥե�����͡��̾���ͤΤ���������ꤵ��Ƥ��ʤ����ˡ��ץ�
     *     �ѥƥ��ͤȤ�����������ʸ���󤬼�������뤫��</li>
     * </ul>
     */		
    void test_getProperty()
    {
      coil::Properties prop;
			
      prop.setDefault("property_1", "default_1");
      prop.setProperty("property_1", "value_1");
      prop.setDefault("property_2", "default_2");
      prop.setProperty("property_3", "value_3");
			
      // (1) �ǥե�����ͤ����ꤵ��Ƥ��ꡢ�����̾���ͤ����ꤵ��Ƥ���
      // ���ˡ��ץ�ѥƥ��ͤȤ����������̾���ͤ���������뤫��
      string expected_1 = "value_1";
      CPPUNIT_ASSERT_EQUAL(expected_1, prop.getProperty("property_1"));
			
      // (2) �ǥե�����ͤ����ꤵ��Ƥ��뤬���̾���ͤ����ꤵ��Ƥ��ʤ�
      // ���ˡ��ץ�ѥƥ��ͤȤ����������ǥե�����ͤ���������뤫��
      string expected_2 = "default_2";
      CPPUNIT_ASSERT_EQUAL(expected_2, prop.getProperty("property_2"));
			
      // (3) �ǥե�����ͤ����ꤵ��Ƥ��ʤ������̾���ͤ����ꤵ��Ƥ���
      // ���ˡ��ץ�ѥƥ��ͤȤ����������̾���ͤ���������뤫��
      string expected_3 = "value_3";
      CPPUNIT_ASSERT_EQUAL(expected_3, prop.getProperty("property_3"));
			
      // (4) �ǥե�����͡��̾���ͤΤ���������ꤵ��Ƥ��ʤ����ˡ���
      // ��ѥƥ��ͤȤ�����������ʸ���󤬼�������뤫��
      string expected_4 = "";
      CPPUNIT_ASSERT_EQUAL(expected_4, prop.getProperty("property_4"));
    }

    /*!
     * @brief getProperty(key, default) �Υƥ���
     */
    void test_getPropertyDefault()
    {
    }

    /*!
     * @brief operator[] (������) �Υƥ���
     */
    void test_opbrace_rhs()
    {
    }

    /*!
     * @brief operator[] (������) �Υƥ���
     */
    void test_opbrace_lhs()
    {
    }

    /*!
     * @brief getDefault()�Υƥ���
     * 
     * <ul>
     *
     * <li>�ǥե�����ͤ����ꤵ��Ƥ��ꡢ�����̾���ͤ����ꤵ��Ƥ����
     * ��ˡ����������ꤵ��Ƥ���ǥե�����ͤ�����Ǥ��뤫��</li>
     *
     * <li>�ǥե�����ͤ����ꤵ��Ƥ��뤬���̾���ͤ����ꤵ��Ƥ��ʤ���
     * ��ˡ����������ꤵ��Ƥ���ǥե�����ͤ�����Ǥ��뤫��</li>
     * 
     * <li>�ǥե�����ͤ����ꤵ��Ƥ��ʤ������̾���ͤ����ꤵ��Ƥ����
     * ��ˡ��ǥե�����ͤȤ��ƶ�ʸ���󤬼�������뤫��</li>
     * 
     * <li>�ǥե�����͡��̾���ͤΤ���������ꤵ��Ƥ��ʤ����ˡ��ǥե�
     * ����ͤȤ��ƶ�ʸ���󤬼�������뤫��</li>
     *
     * </ul>
     */
    void test_getDefault()
    {
      coil::Properties prop;
			
      string key1 = "key1";
      string key1DefaultValue = "key1-default-value";
      string key1Value = "key1-value";
      prop.setDefault(key1, key1DefaultValue);
      prop.setProperty(key1, key1Value);
			
      string key2 = "key2";
      string key2DefaultValue = "key2-default-value";
      prop.setDefault(key2, key2DefaultValue);
			
      string key3 = "key3";
      string key3Value = "key3-value";
      prop.setProperty(key3, key3Value);
			
      // (1) �ǥե�����ͤ����ꤵ��Ƥ��ꡢ�����̾���ͤ����ꤵ��Ƥ���
      // ���ˡ����������ꤵ��Ƥ���ǥե�����ͤ�����Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(key1DefaultValue, prop.getDefault(key1));
			
      // (2) �ǥե�����ͤ����ꤵ��Ƥ��뤬���̾���ͤ����ꤵ��Ƥ��ʤ�
      // ���ˡ����������ꤵ��Ƥ���ǥե�����ͤ�����Ǥ��뤫��
      CPPUNIT_ASSERT_EQUAL(key2DefaultValue, prop.getDefault(key2));
			
      // (3) �ǥե�����ͤ����ꤵ��Ƥ��ʤ������̾���ͤ����ꤵ��Ƥ���
      // ���ˡ��ǥե�����ͤȤ��ƶ�ʸ���󤬼�������뤫��
      CPPUNIT_ASSERT_EQUAL(EMPTY_STRING, prop.getDefault(key3));
			
      // (4) �ǥե�����͡��̾���ͤΤ���������ꤵ��Ƥ��ʤ����ˡ���
      // �ե�����ͤȤ��ƶ�ʸ���󤬼�������뤫��
      string keyNonExist = "key-non-exist";
      CPPUNIT_ASSERT_EQUAL(EMPTY_STRING, prop.getDefault(keyNonExist));
    }
		
    /*!
     * @brief setProperty()�᥽�åɤΥƥ���
     * 
     * <ul>
     * <li>������˻��ꤷ���ͤ������������ꤵ��뤫��</li>
     * <li>�����������ͤȤ��ơ����������ͤ���������������뤫��</li>
     * </ul>
     */
    void test_setProperty()
    {
      string key = "key";
      string oldValue = "old-value";
      string newValue = "new-value";
			
      coil::Properties prop;
      prop.setProperty(key, oldValue);
			
      // (1) ������˻��ꤷ���ͤ������������ꤵ��뤫��
      CPPUNIT_ASSERT_EQUAL(oldValue, prop.getProperty(key));

      // (2) �����������ͤȤ��ơ����������ͤ���������������뤫��
      CPPUNIT_ASSERT_EQUAL(oldValue, prop.setProperty(key, newValue));

      // (1) ������˻��ꤷ���ͤ������������ꤵ��뤫���ʤ��Σ���
      CPPUNIT_ASSERT_EQUAL(newValue, prop.getProperty(key));
    }

    void test_setDefault()
    {
    }

    void test_setDefaults()
    {
    }

    /*!
     * @brief list()�᥽�åɤΥƥ���
     * 
     * <ul>
     *
     * <li>���ꤵ��Ƥ���ץ�ѥƥ��ͤ������������Ϥ���뤫��</li>
     *
     * <li>\�ʥХå�����å���ˤ�ޤ��ͤ������������������׽��������
     * ���Ϥ���뤫��</li>
     *
     * </ul>
     */
    void test_list()
    {
      coil::Properties prop;
      prop.setProperty("rtc.component.conf.path",
                       "C:\\Program\\ Files\\OpenRTM-aist");
      prop.setProperty("rtc.manager.arch", "i386");
      prop.setProperty("rtc.manager.debug.level", "PARANOID");
      prop.setProperty("rtc.manager.language", "C++");
      prop.setProperty("rtc.manager.nameserver", "zonu.a02.aist.go.jp");
      prop.setProperty("rtc.manager.opening_message", "Hello World");
      prop.setProperty("rtc.manager.orb.name", "omniORB");
      prop.setProperty("rtc.manager.orb.options",
                       "IIOPAddrPort, -ORBendPoint, giop:tcp:");
      prop.setProperty("rtc.manager.os.name", "FreeBSD");
      prop.setProperty("rtc.manager.os.release", "6.1-RELEASE");
      prop.setProperty("rtc.manager.subsystems",
                       "Camera, Manipulator, Force Sensor");
      prop.setProperty("rtc.openrtm.author", "Noriaki Ando");
      prop.setProperty("rtc.openrtm.release", "aist");
      prop.setProperty("rtc.openrtm.vendor", "AIST TaskIntelligence");
      prop.setProperty("rtc.openrtm.version", "0.4.0");
			
      std::ofstream outFile("listed.conf");
      prop.list(outFile);
      outFile.close();
			
      vector<string> expectedLines;
      expectedLines.push_back("rtc.component.conf.path: C:\\\\Program\\\\ Files\\\\OpenRTM-aist");
      expectedLines.push_back("rtc.manager.arch: i386");
      expectedLines.push_back("rtc.manager.debug.level: PARANOID");
      expectedLines.push_back("rtc.manager.language: C++");
      expectedLines.push_back("rtc.manager.nameserver: zonu.a02.aist.go.jp");
      expectedLines.push_back("rtc.manager.opening_message: Hello World");
      expectedLines.push_back("rtc.manager.orb.name: omniORB");
      expectedLines.push_back("rtc.manager.orb.options: IIOPAddrPort, -ORBendPoint, giop:tcp:");
      expectedLines.push_back("rtc.manager.os.name: FreeBSD");
      expectedLines.push_back("rtc.manager.os.release: 6.1-RELEASE");
      expectedLines.push_back("rtc.manager.subsystems: Camera, Manipulator, Force Sensor");
      expectedLines.push_back("rtc.openrtm.author: Noriaki Ando");
      expectedLines.push_back("rtc.openrtm.release: aist");
      expectedLines.push_back("rtc.openrtm.vendor: AIST TaskIntelligence");
      expectedLines.push_back("rtc.openrtm.version: 0.4.0");
			
      vector<string> storedLines;
      std::ifstream inFile("listed.conf");
      string str;
      while (getline(inFile, str))
	{
          storedLines.push_back(str);
        }
      inFile.close();
			
      /* �ե�����˽񤭹��ޤ줿���Ƥȴ����ͤ���Ӥ��� */
      sort(expectedLines.begin(), expectedLines.end());
      sort(storedLines.begin(), storedLines.end());
      CPPUNIT_ASSERT_EQUAL(expectedLines.size(), storedLines.size());
      for (vector<string>::size_type i = 0; i < expectedLines.size(); i++)
        {
          CPPUNIT_ASSERT_EQUAL(expectedLines[i], storedLines[i]);
        }
    }
		
    /*!
     * @brief load()�᥽�åɤΥƥ���
     * <ul>
     *
     * <li>�ץ�ѥƥ��ꥹ�Ȥ�ե����뤫��Properties���֥������Ȥ�������
     * �ɤ߹���뤫��</li>
     *
     * </ul>
     */
    void test_load()
    {
      /* �ץ�ѥƥ��ꥹ�Ȥ�ե����뤫��Properties���֥������Ȥ��ɤ߹��� */
      coil::Properties prop;
      std::ifstream ifl("defaults.conf");
      prop.load(ifl);
      ifl.close();
			
      /* �����ͤ���Ӥ��ơ��������ɤ߹��ޤ줿���Ȥ��ǧ���� */
      map<string, string>::iterator expected;
      for (expected = DEFAULTS_CONF.begin();
           expected != DEFAULTS_CONF.end(); expected++) {
	string key = expected->first;
	string value = expected->second;
	CPPUNIT_ASSERT_EQUAL(value, prop.getProperty(key));
      }
    }
		
    /*!
     * @brief store()�᥽�åɤΥƥ���
     * 
     * <ul>
     *
     * <li>���ꤵ��Ƥ���ץ�ѥƥ��ͤ������������Ϥ���뤫��</li>
     *
     * <li>���ꤷ���إå�ʸ���󤬡����������Ϥ���뤫��</li>
     *
     * <li>\�ʥХå�����å���ˤ�ޤ��ͤ������������������׽��������
     * ���Ϥ���뤫��</li>
     *
     * </ul>
     */
    void test_store()
    {
      /* �ƥ����ѤΥץ�ѥƥ������ꤹ�� */
      coil::Properties prop;
      prop.setProperty("rtc.component.conf.path",
                       "C:\\Program\\ Files\\OpenRTM-aist");
      prop.setProperty("rtc.manager.arch", "i386");
      prop.setProperty("rtc.manager.debug.level", "PARANOID");
      prop.setProperty("rtc.manager.language", "C++");
      prop.setProperty("rtc.manager.nameserver", "zonu.a02.aist.go.jp");
      prop.setProperty("rtc.manager.opening_message", "Hello World");
      prop.setProperty("rtc.manager.orb.name", "omniORB");
      prop.setProperty("rtc.manager.orb.options",
                       "IIOPAddrPort, -ORBendPoint, giop:tcp:");
      prop.setProperty("rtc.manager.os.name", "FreeBSD");
      prop.setProperty("rtc.manager.os.release", "6.1-RELEASE");
      prop.setProperty("rtc.manager.subsystems",
                       "Camera, Manipulator, Force Sensor");
      prop.setProperty("rtc.openrtm.author", "Noriaki Ando");
      prop.setProperty("rtc.openrtm.release", "aist");
      prop.setProperty("rtc.openrtm.vendor", "AIST TaskIntelligence");
      prop.setProperty("rtc.openrtm.version", "0.4.0");
      prop.setProperty("hello", "\tHello\t");
			
      std::ofstream outFile("stored.conf");
      prop.store(outFile, "stored data");
      outFile.close();
			
      /* ��ӤΤ���δ����ͤ�������� */
      vector<string> expectedLines;
      expectedLines.push_back("# stored data");
      expectedLines.push_back("rtc.component.conf.path: C:\\\\Program\\\\ Files\\\\OpenRTM-aist");
      expectedLines.push_back("rtc.manager.arch: i386");
      expectedLines.push_back("rtc.manager.debug.level: PARANOID");
      expectedLines.push_back("rtc.manager.language: C++");
      expectedLines.push_back("rtc.manager.nameserver: zonu.a02.aist.go.jp");
      expectedLines.push_back("rtc.manager.opening_message: Hello World");
      expectedLines.push_back("rtc.manager.orb.name: omniORB");
      expectedLines.push_back("rtc.manager.orb.options: IIOPAddrPort, -ORBendPoint, giop:tcp:");
      expectedLines.push_back("rtc.manager.os.name: FreeBSD");
      expectedLines.push_back("rtc.manager.os.release: 6.1-RELEASE");
      expectedLines.push_back("rtc.manager.subsystems: Camera, Manipulator, Force Sensor");
      expectedLines.push_back("rtc.openrtm.author: Noriaki Ando");
      expectedLines.push_back("rtc.openrtm.release: aist");
      expectedLines.push_back("rtc.openrtm.vendor: AIST TaskIntelligence");
      expectedLines.push_back("rtc.openrtm.version: 0.4.0");
      expectedLines.push_back("hello: \\tHello\\t");
			
      /* ���Ϥ��줿�ե��������Ȥ򣱹ԤŤ��ɤ߹��� */
      vector<string> storedLines;
      std::ifstream inFile("stored.conf");
      string str;
      while (getline(inFile, str))	{
	storedLines.push_back(str);
      }
      inFile.close();
			
      /* �ե�����˽񤭹��ޤ줿���Ƥȴ����ͤ���Ӥ��� */
      sort(expectedLines.begin(), expectedLines.end());
      sort(storedLines.begin(), storedLines.end());
      CPPUNIT_ASSERT_EQUAL(expectedLines.size(), storedLines.size());
      for (vector<string>::size_type i = 0; i < expectedLines.size(); i++) {
	CPPUNIT_ASSERT_EQUAL(expectedLines[i], storedLines[i]);
      }
    }


    /*!
     * @brief propertyNames()�᥽�åɤΥƥ���
     * 
     * <ul>
     *
     * <li>�̾�Υץ�ѥƥ��ͤȥǥե�����ͤ�ξ�������ꤵ��Ƥ���ץ��
     * �ƥ��ˤĤ��ơ�����̾����������뤫��</li>
     *
     * <li>�̾�Υץ�ѥƥ��ͤΤߤ����ꤵ��Ƥ���ץ�ѥƥ��ˤĤ��ơ�����
     * ̾����������뤫��</li>
     *
     * <li>�ǥե�����ͤΤߤ����ꤵ��Ƥ���ץ�ѥƥ��ˤĤ��ơ�����̾��
     * ��������뤫��</li>
     *
     * </ul>
     */
    void test_propertyNames()
    {
      coil::Properties prop;
			
      /* (1) �̾�Υץ�ѥƥ��ͤȥǥե�����ͤ�ξ�������ꤹ�� */
      prop.setProperty("property_01", "value_01");
      prop.setDefault("property_01", "default_01");
			
      /* (2) �̾�Υץ�ѥƥ��ͤΤߤ����ꤹ�� */
      prop.setProperty("property_02", "value_02");
			
      /* (3) �ǥե�����ͤΤߤ����ꤹ�� */
      prop.setDefault("property_03", "default_03");
			
      /* (1),(2),(3)������ξ��ˤĤ��Ƥ⥭��̾����������뤳�Ȥ��ǧ���� */
      vector<string> keys = prop.propertyNames();
      CPPUNIT_ASSERT_EQUAL(3, (int) keys.size());
      CPPUNIT_ASSERT(find(keys.begin(), keys.end(), "property_01")
                     != keys.end());
      CPPUNIT_ASSERT(find(keys.begin(), keys.end(), "property_02")
                     != keys.end());
      CPPUNIT_ASSERT(find(keys.begin(), keys.end(), "property_03")
                     != keys.end());
    }

    void test_size()
    {
    }

    void test_findNode()
    {
      coil::Properties prop;
      const char* text0 = "Hello, World!";


      prop["a0.b0.c0"] = text0;

      CPPUNIT_ASSERT(prop.findNode("a0.b0") != 0);
      CPPUNIT_ASSERT(prop.findNode("a0")    != 0);
      CPPUNIT_ASSERT(prop.findNode("")      == 0);

      coil::Properties* prop1(prop.findNode("a0.b1"));
      CPPUNIT_ASSERT(prop1 == 0);

      coil::Properties p;
      p["a0"] = "hoge";

      CPPUNIT_ASSERT(p["a0"] == "hoge");

      p["a0.b0"] = "dara";

      CPPUNIT_ASSERT( p["a0.b0"] == "dara");
      CPPUNIT_ASSERT(p["a0"] == "hoge");
      return;      
    }

    void test_getNode()
    {
      coil::Properties prop;
      const char* text0 = "Hello, World!";
      const char* text1 = "Hello World!";

      prop["a0.b0.c0"] = text0;

      CPPUNIT_ASSERT(prop.getNode("a0.b0")["c0"] == text0);
      CPPUNIT_ASSERT(prop.getNode("a0")["b0.c0"] == text0);
      CPPUNIT_ASSERT(prop.getNode("")["a0.b0.c0"] == text0);
      //      return;
      coil::Properties& prop1(prop.getNode("a0.b1"));
      // now node "a0.b1" is created
      prop1["c1"] = text1; // a0.b1.c1 = text1

      CPPUNIT_ASSERT(prop["a0.b1.c1"] == text1);
    }

    /*!
     * @brief createNode()�Υƥ���
     * 
     * <ul>
     *
     * <li>�ǥե�����ͤ����ꤵ��Ƥ��ꡢ�����̾���ͤ����ꤵ��Ƥ����
     * ��ˡ���������̾�ο����Ρ��ɺ��������տޤɤ��꼺�Ԥ��뤫��</li>
     *
     * <li>�ǥե�����ͤ����ꤵ��Ƥ��뤬���̾���ͤ����ꤵ��Ƥ��ʤ���
     * ��ˡ���������̾�ο����Ρ��ɺ��������տޤɤ��꼺�Ԥ��뤫��</li>
     *
     * <li>�ǥե�����ͤ����ꤵ��Ƥ��ʤ������̾���ͤ����ꤵ��Ƥ����
     * ��ˡ���������̾�ο����Ρ��ɺ��������տޤɤ��꼺�Ԥ��뤫��</li>
     *
     * <li>�ǥե�����͡��̾���ͤΤ���������ꤵ��Ƥ��ʤ����ˡ�����
     * �Ρ��ɺ������������뤫��</li>
     *
     * </ul>
     */
    void test_createNode()
    {
      coil::Properties prop;
			
      string key1 = "key1";
      string key1DefaultValue = "key1-default-value";
      string key1Value = "key1-value";
      prop.setDefault(key1, key1DefaultValue);
      prop.setProperty(key1, key1Value);
			
      string key2 = "key2";
      string key2DefaultValue = "key2-default-value";
      prop.setDefault(key2, key2DefaultValue);
			
      string key3 = "key3";
      string key3Value = "key3-value";
      prop.setProperty(key3, key3Value);
			
      // (1) �ǥե�����ͤ����ꤵ��Ƥ��ꡢ�����̾���ͤ����ꤵ��Ƥ���
      // ���ˡ���������̾�ο����Ρ��ɺ��������տޤɤ��꼺�Ԥ��뤫��
      CPPUNIT_ASSERT(! prop.createNode(key1.c_str()));
			
      // (2) �ǥե�����ͤ����ꤵ��Ƥ��뤬���̾���ͤ����ꤵ��Ƥ��ʤ�
      // ���ˡ���������̾�ο����Ρ��ɺ��������տޤɤ��꼺�Ԥ��뤫��
      CPPUNIT_ASSERT(! prop.createNode(key2.c_str()));
			
      // (3) �ǥե�����ͤ����ꤵ��Ƥ��ʤ������̾���ͤ����ꤵ��Ƥ���
      // ���ˡ���������̾�ο����Ρ��ɺ��������տޤɤ��꼺�Ԥ��뤫��
      CPPUNIT_ASSERT(! prop.createNode(key3.c_str()));
			
      // (4) �ǥե�����͡��̾���ͤΤ���������ꤵ��Ƥ��ʤ����ˡ���
      // ���Ρ��ɺ������������뤫��
      string keyNonExist = "key-non-exist";
      CPPUNIT_ASSERT(prop.createNode(keyNonExist.c_str()));
    }

    /*!
     * @brief removeNode
     */
    void test_removeNode()
    {
    }

    /*!
     * @brief hasKey
     */
    void test_hasKey()
    {
    }

    /*!
     * @brief clear
     */
    void test_clear()
    {
    }

    /*!
     * @brief <<�黻�ҤΥƥ���
     * 
     * <ul>
     *
     * <li>�ǥե�����ͤϡ����Ϥ���ʤ����Ȥ��ǧ����</li>
     *
     * <li>���Ĥ�Properties�Τ����������������ꤵ��Ƥ��륭���˴ؤ��ơ�
     * ���ꤵ��Ƥ����̾��ͤ�������������Ѳ����ʤ�����</li>
     *
     * <li>���Ĥ�Properties��ξ���˶��̤��Ƥ��륭���˴ؤ��ơ����ꤵ���
     * �����̾��ͤ����Ϥ����ͤǾ�񤭤���뤫��</li>
     *
     * </ul>
     */
    void test_streamInput()
    {
      /* ���ϸ��Ȥʤ�Properties�Σ����ܤ�������� */
      coil::Properties propA;
			
      string keyA1 = "keyA1";
      string keyA1DefaultValue = "keyA1-default-value";
      string keyA1Value = "keyA1-value";
      propA.setDefault(keyA1, keyA1DefaultValue);
      propA.setProperty(keyA1, keyA1Value);
			
      string keyA2 = "keyA2";
      string keyA2DefaultValue = "keyA2-default-value";
      propA.setDefault(keyA2, keyA2DefaultValue);
			
      string keyA3 = "keyA3";
      string keyA3Value = "keyA3-value";
      propA.setProperty(keyA3, keyA3Value);
			
      /* ���ϸ��Ȥʤ�Properties�Σ����ܤ�������� */
      coil::Properties propB;
			
      string keyB1 = "keyB1";
      string keyB1DefaultValue = "keyB1-default-value";
      string keyB1Value = "keyB1-value";
      propB.setDefault(keyB1, keyB1DefaultValue);
      propB.setProperty(keyB1, keyB1Value);
			
      string keyB2 = "keyB2";
      string keyB2DefaultValue = "keyB2-default-value";
      propB.setDefault(keyB2, keyB2DefaultValue);

      string keyB3 = "keyB3";
      string keyB3Value = "keyB3-value";
      propB.setProperty(keyB3, keyB3Value);
			
      // ���Ĥ�Properties�ˡ����̤��륭��̾�Ǹߤ��˰ۤʤ��ͤ����ꤷ�Ƥ���
      string keyCommon = "keyCommon";
      string keyCommonValueA = "keyCommon-value-A";
      string keyCommonValueB = "keyCommon-value-B";
      propA.setProperty(keyCommon, keyCommonValueA);
      propB.setProperty(keyCommon, keyCommonValueB);

      /* propB��propA�����Ϥ��� */
      propA << propB;
			
      /* �������ޡ������줿���Ȥ��ǧ���� */
      /* (1) �������������ꤵ��Ƥ��ꡢ���̥����Ǥʤ���Τϡ���ȤΤޤ� */
      /* �Ǥ��뤳�Ȥ��ǧ����                                           */
      CPPUNIT_ASSERT_EQUAL(keyA1DefaultValue, propA.getDefault(keyA1));
      CPPUNIT_ASSERT_EQUAL(keyA1Value, propA.getProperty(keyA1));
      CPPUNIT_ASSERT_EQUAL(keyA2DefaultValue, propA.getDefault(keyA2));
      CPPUNIT_ASSERT_EQUAL(keyA2DefaultValue, propA.getProperty(keyA2));
      CPPUNIT_ASSERT_EQUAL(EMPTY_STRING, propA.getDefault(keyA3));
      CPPUNIT_ASSERT_EQUAL(keyA3Value, propA.getProperty(keyA3));

      /* (2) �̾��ͤ����Ϥ��졢�ǥե�����ͤ����Ϥ���ʤ����Ȥ��ǧ���� */
      CPPUNIT_ASSERT_EQUAL(EMPTY_STRING, propA.getDefault(keyB1));
      CPPUNIT_ASSERT_EQUAL(keyB1Value, propA.getProperty(keyB1));
      CPPUNIT_ASSERT_EQUAL(EMPTY_STRING, propA.getDefault(keyB2));
      CPPUNIT_ASSERT_EQUAL(keyB2DefaultValue, propA.getProperty(keyB2));
      CPPUNIT_ASSERT_EQUAL(EMPTY_STRING, propA.getDefault(keyB3));
      CPPUNIT_ASSERT_EQUAL(keyB3Value, propA.getProperty(keyB3));
			
      /* (3) ���̥���̾�ˤĤ��ơ����Ϥ����ͤǾ�񤭤���Ƥ��뤳�Ȥ��ǧ���� */
      CPPUNIT_ASSERT_EQUAL(keyCommonValueB, propA.getProperty(keyCommon));
    }

    /*!
     * @brief splitKeyValue()�᥽�åɤΥƥ���
     * 
     * <ul>
     *
     * <li>���������˶���ʸ����ޤ���ˤĤ��ơ��������ͤ�������ʬΥ��
     * ���뤫��</li>
     *
     * <li>�����ȥǥ�ߥ��δ֤˶���ʸ����ޤ���ˤĤ��ơ��������ͤ���
     * ����ʬΥ�Ǥ��뤫��</li>
     *
     * <li>�ǥ�ߥ����ͤδ֤˶���ʸ����ޤ���ˤĤ��ơ��������ͤ�����
     * ��ʬΥ�Ǥ��뤫��</li>
     *
     *a <li>�ͤθ��˶���ʸ����ޤ���ˤĤ��ơ��������ͤ�������ʬΥ��
     * ���뤫��</li>
     *
     * </ul>
     */
    void test_splitKeyValue()
    {
      class P : public coil::Properties
      {
      public:
	void splitKeyValue_protected(const std::string& str,
                                     std::string& key, std::string& value)
	{
	  splitKeyValue(str, key, value);
	}
      };
			
      string keyAndValue = " property_name : C:\\abc\\pqr.xyz ";
			
      string key, value;
      P prop;
      prop.splitKeyValue_protected(keyAndValue, key, value);
			
      /* �������ͤ���;ʬ�ʶ���ʸ��������줿������ʬΥ����Ƥ��뤳�� */
      /* ���ǧ����                                                     */
      string expectedKey("property_name");
      CPPUNIT_ASSERT_EQUAL(expectedKey, key);

      string expectedValue("C:\\abc\\pqr.xyz");
      CPPUNIT_ASSERT_EQUAL(expectedValue, value);
    }
    

		
  };
}; // namespace Properties

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(Properties::PropertiesTests);

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
#endif // Properties_cpp
