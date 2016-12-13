// -*- C++ -*-

/*
 * $Log: OutPortCorbaConsumerTests.cpp,v $
 * Revision 1.1  2008/03/13 10:26:38  arafune
 * The first commitment.
 *
 *
 */

#ifndef OutPortCorbaConsumer_cpp
#define OutPortCorbaConsumer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/DataPortSkel.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/RingBuffer.h>
#include <rtm/OutPortCorbaConsumer.h>

/*!
 * @class OutPortCorbaConsumerTests class
 * @brief OutPortCorbaConsumer test
 */
namespace OutPortCorbaConsumer
{
  class OutPortAnyMock
    : virtual public POA_RTC::OutPortAny,
      virtual public PortableServer::RefCountServantBase
  {
  public:
    virtual CORBA::Any* get()
    {
      return new CORBA::Any(m_data);
    }
		
    void setData(const CORBA::Any& data)
    {
      m_data = data;
    }
		
  private:
    CORBA::Any m_data;
  };
	
  class OutPortCorbaConsumerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortCorbaConsumerTests);
    CPPUNIT_TEST(test_get);
    CPPUNIT_TEST(test_pull);
    CPPUNIT_TEST(test_subscribeInterface);
    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
	
  public:
	
    /*!
     * @brief Constructor
     */
    OutPortCorbaConsumerTests()
    {
      int argc = 0;
      char** argv = 0;
			
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
					    m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();
    }
		
    /*!
     * @brief Destructor
     */
    ~OutPortCorbaConsumerTests()
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
     * @brief get()�᥽�åɤΥƥ���
     * 
     * - OutPortConsumer��get()�᥽�åɸƽФˤ�äơ�Provider¦�Υǡ����������������Ǥ��롩
     */
    void test_get()
    {
      // ��³��Ȥʤ�Provider¦�Υ��֥������Ȥ������������ꤹ��
      OutPortAnyMock* outPortAny = new OutPortAnyMock();
      PortableServer::ObjectId_var outPortAnyId = m_pPOA->activate_object(outPortAny);

      RTC::RingBuffer<RTC::TimedFloat> buffer(100);
      RTC::OutPortCorbaConsumer<RTC::TimedFloat> consumer(buffer);
      consumer.setObject(m_pPOA->id_to_reference(outPortAnyId));
			
      // Provider¦�˥ƥ����ѤΥǡ��������ꤷ�Ƥ���
      RTC::TimedFloat writeValue;
      writeValue.data = 3.14159;
      CORBA::Any writeValueAny;
      writeValueAny <<= writeValue;
      outPortAny->setData(writeValueAny);
			
      // OutPortCorbaConsumer::get()���Ѥ��ơ��ǡ������ɤ߼��
      RTC::TimedFloat readValue;
      CPPUNIT_ASSERT(consumer.get(readValue));
			
      // �ƥ����Ѥ����ꤷ�Ƥ������ǡ������ɤ߼�ä��ǡ�������Ӥ��������������Ǥ������Ȥ��ǧ����
      CPPUNIT_ASSERT_EQUAL(writeValue.data, readValue.data);
    }
		
    /*!
     * @brief pull()�᥽�åɤΥƥ���
     * 
     * - OutPortConsumer��pull()�᥽�åɸƽФˤ�äơ�Provider¦�Υǡ������������Хåե��˽񤭹��ޤ�뤫��
     */
    void test_pull()
    {
      // ��³��Ȥʤ�Provider¦�Υ��֥������Ȥ������������ꤹ��
      OutPortAnyMock* outPortAny = new OutPortAnyMock();
      PortableServer::ObjectId_var outPortAnyId = m_pPOA->activate_object(outPortAny);

      RTC::RingBuffer<RTC::TimedFloat> buffer(100);
      RTC::OutPortCorbaConsumer<RTC::TimedFloat> consumer(buffer);
      consumer.setObject(m_pPOA->id_to_reference(outPortAnyId));
			
      // Provider¦�˥ƥ����ѤΥǡ��������ꤷ�Ƥ���
      RTC::TimedFloat writeValue;
      writeValue.data = 3.14159;
      CORBA::Any writeValueAny;
      writeValueAny <<= writeValue;
      outPortAny->setData(writeValueAny);
			
      // pull()�᥽�åɤ�ƽФ��ơ�OutPortAny¦�Υǡ�����Хåե����ɤ߹���
      consumer.pull();
			
      // �Хåե�����ǡ������ɤ߽Ф��ơ��ƥ����Ѥ����ꤷ�Ƥ������ǡ������ɤ߼�ä��ǡ�������Ӥ��������������Ǥ������Ȥ��ǧ����
      RTC::TimedFloat readValue;
      CPPUNIT_ASSERT(buffer.read(readValue));
      CPPUNIT_ASSERT_EQUAL(writeValue.data, readValue.data);
    }

    /*!		
     * @brief subscribeInterface()�᥽�åɤΥƥ���
     * 
     * - �ץ�ѥƥ���OutPortAny�Υ�ե���󥹤����ꤷ�ơ�subscribeInterface()�ˤ����Ͽ���������뤫��
     */
    void test_subscribeInterface()
    {
      OutPortAnyMock* outPortAny = new OutPortAnyMock();
      PortableServer::ObjectId_var outPortAnyId = m_pPOA->activate_object(outPortAny);

      RTC::RingBuffer<RTC::TimedFloat> buffer(100);
      RTC::OutPortCorbaConsumer<RTC::TimedFloat> consumer(buffer);
      CORBA::Object_ptr outPortAnyRef = m_pPOA->id_to_reference(outPortAnyId);
      CORBA::Any outPortAnyRefAny; outPortAnyRefAny <<= outPortAnyRef;
			
      // �ץ�ѥƥ���OutPortAny�Υ�ե���󥹤����ꤷ�ơ�subscribeInterface()�ˤ����Ͽ���������뤫��
      SDOPackage::NVList properties;
      CORBA_SeqUtil::push_back(properties,
			       NVUtil::newNV("dataport.dataflow_type", "Pull"));
      CORBA_SeqUtil::push_back(properties,
			       NVUtil::newNVAny("dataport.corba_any.outport_ref", outPortAnyRefAny));
      CPPUNIT_ASSERT(consumer.subscribeInterface(properties));
    }
		
  };
}; // namespace OutPortCorbaConsumer

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPortCorbaConsumer::OutPortCorbaConsumerTests);

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
#endif // OutPortCorbaConsumer_cpp
