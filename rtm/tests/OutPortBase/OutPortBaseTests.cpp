// -*- C++ -*-
/*!
 * @file   OutPortBaseTests.cpp
 * @brief  OutPortBase test class
 * @date   $Date: 2006-12-02 18:55:54 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

#ifndef OutPortBase_cpp
#define OutPortBase_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/PublisherBase.h>
#include <rtm/OutPortBase.h>

/*!
 * @class OutPortBaseTests class
 * @brief OutPortBase test
 */
namespace OutPortBase
{
  class PublisherA
    : public RTC::PublisherBase
  {
  public:
    std::string& m_str;
    PublisherA(std::string& str) : m_str(str) {};
    virtual ~PublisherA(){m_str = "DeleteA";}
    void update(){m_str += "A";}
  };
  class PublisherB
    : public RTC::PublisherBase
  {
  public:
    std::string& m_str;
    PublisherB(std::string& str) : m_str(str) {};
    virtual ~PublisherB(){m_str = "DeleteB";}
    void update(){m_str += "B";}
  };
  class PublisherC
    : public RTC::PublisherBase
  {
  public:
    std::string& m_str;
    PublisherC(std::string& str) : m_str(str) {};
    virtual ~PublisherC(){m_str = "DeleteC";}
    void update(){m_str += "C";}
  };
  class PublisherD
    : public RTC::PublisherBase
  {
  public:
    std::string& m_str;
    PublisherD(std::string& str) : m_str(str) {};
    virtual ~PublisherD(){m_str = "DeleteD";}
    void update(){m_str += "D";}
  };


  const char* outport_name = "MyOutPort";

  class OutPort
    : public RTC::OutPortBase
  {
  public:
    OutPort(const char* name)
      : OutPortBase(name)
    {
    }
  };
  class OutPortBaseTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortBaseTests);
    CPPUNIT_TEST(test_name);
    CPPUNIT_TEST(test_attach);
    CPPUNIT_TEST(test_attach_back);
    CPPUNIT_TEST(test_attach_front);
    CPPUNIT_TEST(test_attach_mix);
    CPPUNIT_TEST(test_detach);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    PublisherA* m_pubA;
    PublisherB* m_pubB;
    PublisherC* m_pubC;
    PublisherD* m_pubD;
    OutPort* m_outport;
    std::string m_str;
  public:
  
    /*!
     * @brief Constructor
     */
    OutPortBaseTests()
    {
      m_pubA = new PublisherA(m_str);
      m_pubB = new PublisherB(m_str);
      m_pubC = new PublisherC(m_str);
      m_pubD = new PublisherD(m_str);
      m_outport = new OutPort(outport_name);
    }
    
    /*!
     * @brief Destructor
     */
    ~OutPortBaseTests()
    {
      if (m_outport != NULL)
	delete m_outport;
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
     * @brief OutPortBase::name() $B$N%F%9%H(B
     */
    void test_name()
    {
      CPPUNIT_ASSERT(!strcmp(outport_name, m_outport->name()));
    }

    /*!
     * @brief OutPortBase::attach() $B$N%F%9%H(B
     * Publisher$B$N%j%9%H$K(BA,B,C,D$B$N=g$G(Bpush_back$B$9$k!#(B
     * notify() $B$r8F$V$H(B m_str $B$K(B A,B,C,D$B$N=g$GJ8;z$,F~$k(B
     */
    void test_attach()
    {
      m_outport->attach("A", m_pubA);
      m_outport->attach("B", m_pubB);
      m_outport->attach("C", m_pubC);
      m_outport->attach("D", m_pubD);
      m_outport->notify();

      CPPUNIT_ASSERT(m_str == "ABCD");
    }

    /*!
     * @brief OutPortBase::attach_back() $B$N%F%9%H(B
     * Publisher$B$N%j%9%H$K(BA,B,C,D$B$N=g$G(Bpush_back$B$9$k!#(B
     * notify() $B$r8F$V$H(B m_str $B$K(B A,B,C,D$B$N=g$GJ8;z$,F~$k(B
     */
    void test_attach_back()
    {
      m_outport->attach_back("A", m_pubA);
      m_outport->attach_back("B", m_pubB);
      m_outport->attach_back("C", m_pubC);
      m_outport->attach_back("D", m_pubD);
      m_outport->notify();

      CPPUNIT_ASSERT(m_str == "ABCD");
    }

    /*!
     * @brief OutPortBase::attach_front() $B$N%F%9%H(B
     * Publisher$B$N%j%9%H$K(BA,B,C,D$B$N=g$G%j%9%H$N@hF,$KA^F~$9$k!#(B
     * notify() $B$r8F$V$H(B m_str $B$K(B D,C,B,A$B$N=g$GJ8;z$,F~$k!#(B
     */
    void test_attach_front()
    {
      m_outport->attach_front("A", m_pubA);
      m_outport->attach_front("B", m_pubB);
      m_outport->attach_front("C", m_pubC);
      m_outport->attach_front("D", m_pubD);
      m_outport->notify();

      CPPUNIT_ASSERT(m_str == "DCBA");
    }

    /*!
     * @brief OutPortBase::attach_front/back() $B$N%F%9%H(B
     * Publisher$B$N%j%9%H$K(BA,B,C,D$B$r(Battach_front(), attach_back()
     * $B$r:.$<$F%3!<%k!#(Bback:A, back:B, front:C, front:D $B$J$N$G(B
     * notify() $B$r8F$V$H(B m_str $B$K(B D,C,A,B$B$N=g$GJ8;z$,F~$k!#(B
     */
    void test_attach_mix()
    {
      m_outport->attach_back ("A", m_pubA); // A
      m_outport->attach_back ("B", m_pubB); // AB
      m_outport->attach_front("C", m_pubC); // CAB
      m_outport->attach_front("D", m_pubD); // DCAB
      m_outport->notify();

      CPPUNIT_ASSERT(m_str == "DCAB");
    }

    /*!
     * @brief OutPortBase::detach() $B$N%F%9%H(B
     *
     * $B%j%9%H$K(BA,B,C,D$B$N=g$K(Battach()$B$7!"(BA,B,D,C $B$N=g$G(Bdetach()$B!#(B
     * notify() $B$r8F$s$G!";D$j$N(BPublisher$B$r%A%'%C%/!#(B
     * 
     * detach() $B$O8F$P$l$k$H!"(BPublisher $B$N%]%$%s%?$rJV$9$N$G$=$l$r(Bdelete$B!#(B
     * Publisher$B$N%G%9%H%i%/%?$G$O!"(Bm_str $B$K(B "Delete?" $B$r%;%C%H$9$k$N$G!"(B
     * m_str $B$r%A%'%C%/!#(B
     */
    void test_detach()
    {
      // A,B,C,D $B$N=g$K%"%?%C%A(B
      RTC::PublisherBase* pub;
      m_outport->attach("A", m_pubA);
      m_outport->attach("B", m_pubB);
      m_outport->attach("C", m_pubC);
      m_outport->attach("D", m_pubD);
      // update() $B$,8F$P$l$F(B m_str = "ABCD" $B$N$O$:(B
      m_outport->notify();
      CPPUNIT_ASSERT(m_str == "ABCD");

      // detach $B$N%F%9%H(B
      m_str.clear();
      pub = m_outport->detach("A");
      m_outport->notify();
      // "A" $B$r%G%?%C%A$7$?$N$G(B m_str = "BCD" $B$N$O$:(B
      CPPUNIT_ASSERT(m_str == "BCD");

      // A $B$r(Bdelete$B$9$k$N$G!"%G%9%H%i%/%?$G(B m_str = "DeleteA"
      delete pub;
      CPPUNIT_ASSERT(m_str == "DeleteA");

      m_str.clear();
      pub = m_outport->detach("B");
      m_outport->notify();
      // "B" $B$r%G%?%C%A$7$?$N$G(B m_str = "CD" $B$N$O$:(B
      CPPUNIT_ASSERT(m_str == "CD");

      // B $B$r(Bdelete$B$9$k$N$G!"%G%9%H%i%/%?$G(B m_str = "DeleteB"
      delete pub;
      CPPUNIT_ASSERT(m_str == "DeleteB");

      m_str.clear();
      pub = m_outport->detach("D");
      m_outport->notify();
      // "D" $B$r%G%?%C%A$7$?$N$G(B m_str = "C" $B$N$O$:(B
      CPPUNIT_ASSERT(m_str == "C");

      // D $B$r(Bdelete$B$9$k$N$G!"%G%9%H%i%/%?$G(B m_str = "DeleteD"
      delete pub;
      CPPUNIT_ASSERT(m_str == "DeleteD");

      m_str.clear();
      pub = m_outport->detach("C");
      m_outport->notify();
      // "C" $B$r%G%?%C%A$7$?$N$G(B m_str = "" $B$N$O$:(B
      CPPUNIT_ASSERT(m_str == "");

      // C $B$r(Bdelete$B$9$k$N$G!"%G%9%H%i%/%?$G(B m_str = "DeleteC"
      delete pub;
      CPPUNIT_ASSERT(m_str == "DeleteC");
    }

  };
}; // namespace OutPortBase

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPortBase::OutPortBaseTests);

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
#endif // OutPortBase_cpp
