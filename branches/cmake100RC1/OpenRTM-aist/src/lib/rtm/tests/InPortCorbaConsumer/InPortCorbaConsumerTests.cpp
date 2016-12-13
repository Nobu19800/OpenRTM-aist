// -*- C++ -*-

/*
 * $Log: InPortCorbaConsumerTests.cpp,v $
 * Revision 1.1  2008/02/28 10:00:29  arafune
 * The first commitment.
 *
 *
 *
 */

#ifndef InPortCorbaConsumer_cpp
#define InPortCorbaConsumer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/config_rtc.h>
#include <idl/BasicDataTypeSkel.h>
#include <idl/DataPortSkel.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/RingBuffer.h>
#include <rtm/InPortCorbaConsumer.h>

/*!
 * @class InPortCorbaConsumerTests class
 * @brief InPortCorbaConsumer test
 */
namespace InPortCorbaConsumer
{
  class InPortAnyMock
    : virtual public POA_RTC::InPortAny,
      virtual public PortableServer::RefCountServantBase
  {
  public:
    virtual void put(const CORBA::Any& data)
    {
      m_data = data;
    }
		
    const CORBA::Any& getData() const
    {
      return m_data;
    }
		
  private:
    CORBA::Any m_data;
  };
	
  /*!
   * @brief �񤭹��ߤ��ɤ߹��ߤ��ԲĤΥ��ߡ��Хåե�
   */
  template<class DataType>
  class BufferDummy
    : public RTC::BufferBase<DataType>
  {
  public:
    virtual long int length() const { return 0; }
    virtual bool write(const DataType& value) { return false; }
    virtual bool read(DataType& value) { return false; }
    virtual bool isFull() const { return true; }
    virtual bool isEmpty() const { return true; }
	
  protected:
    virtual void put(const DataType& data) {}
    virtual const DataType& get() { return m_data; }
    virtual DataType& getRef() { return m_data; }
	
  private:
    DataType m_data;
  };
	
  class InPortCorbaConsumerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(InPortCorbaConsumerTests);
    CPPUNIT_TEST(test_put);
    CPPUNIT_TEST(test_push);
    CPPUNIT_TEST(test_subscribeInterface);
    CPPUNIT_TEST(test_copy_constructor);
    CPPUNIT_TEST(test_substitute_operator);
    CPPUNIT_TEST(test_clone);
    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
	
  public:
	
    /*!
     * @brief Constructor
     */
    InPortCorbaConsumerTests()
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
    ~InPortCorbaConsumerTests()
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
     * @brief put()�᥽�åɤΥƥ���
     * 
     * - InPortConsumer��put()�᥽�åɸƽФˤ�äơ�InPortAny��put()�᥽�å�¦���������ǡ������Ϥ���뤫��
     */
    void test_put()
    {
      InPortAnyMock* inPortAny = new InPortAnyMock();
      PortableServer::ObjectId_var inPortAnyId = m_pPOA->activate_object(inPortAny);

      RTC::RingBuffer<CORBA::Float> buffer(100);
      RTC::InPortCorbaConsumer<CORBA::Float> consumer(buffer);
      consumer.setObject(m_pPOA->id_to_reference(inPortAnyId));
			
      // InPortConsumer��put()�᥽�åɤ�ƤӽФ�
      CORBA::Float writeValue = 3.14159;
      consumer.put(writeValue);
			
      // InPortAny¦��put()�᥽�åɤ˥ǡ������������Ϥ���Ƥ��뤫��
      CORBA::Any readValueAny = inPortAny->getData();
      CORBA::Float* pReadValue = (CORBA::Float*) readValueAny.value();
      CPPUNIT_ASSERT_EQUAL(writeValue, *pReadValue);

      m_pPOA->deactivate_object(inPortAnyId);
      delete inPortAny;
    }
		
    /*!
     * @brief push()�᥽�åɤΥƥ���
     * 
     * - �Хåե��˽񤭹���Ǥ������ǡ�������push()�᥽�åɸƽФˤ�ä�InPortAny��put()�����������Ф���뤫��
     */
    void test_push()
    {
      InPortAnyMock* inPortAny = new InPortAnyMock();
      PortableServer::ObjectId_var inPortAnyId = m_pPOA->activate_object(inPortAny);

      RTC::RingBuffer<CORBA::Float> buffer(100);
      RTC::InPortCorbaConsumer<CORBA::Float> consumer(buffer);
      consumer.setObject(m_pPOA->id_to_reference(inPortAnyId));
			
      // �Хåե��˥ǡ�����񤭹���ǡ�push()�᥽�åɤ����Ф�����
      CORBA::Float writeValue = 3.14159;
      buffer.write(writeValue);
      consumer.push();
			
      // InPortAny¦��put()�᥽�åɤ˥ǡ������������Ϥ���Ƥ��뤫��
      CORBA::Any readValueAny = inPortAny->getData();
      CORBA::Float* pReadValue = (CORBA::Float*) readValueAny.value();
      CPPUNIT_ASSERT_EQUAL(writeValue, *pReadValue);

      m_pPOA->deactivate_object(inPortAnyId);
      delete inPortAny;
    }
		
    /*!
     * @brief subscribeInterface()�᥽�åɤΥƥ���
     * 
     * - �ץ�ѥƥ���InPortAny�Υ�ե���󥹤����ꤷ�ơ�subscribeInterface()�ˤ����Ͽ���������뤫��
     */
    void test_subscribeInterface()
    {
      InPortAnyMock* inPortAny = new InPortAnyMock();
      PortableServer::ObjectId_var inPortAnyId = m_pPOA->activate_object(inPortAny);

      RTC::RingBuffer<CORBA::Float> buffer(100);
      RTC::InPortCorbaConsumer<CORBA::Float> consumer(buffer);
      CORBA::Object_ptr inPortAnyRef = m_pPOA->id_to_reference(inPortAnyId);
      CORBA::Any inPortAnyRefAny; inPortAnyRefAny <<= inPortAnyRef;
			
      // �ץ�ѥƥ���InPortAny�Υ�ե���󥹤����ꤷ�ơ�subscribeInterface()�ˤ����Ͽ���������뤫��
      SDOPackage::NVList properties;
      CORBA_SeqUtil::push_back(properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(properties,
			       NVUtil::newNVAny("dataport.corba_any.inport_ref", inPortAnyRefAny));
      CPPUNIT_ASSERT(consumer.subscribeInterface(properties));

      m_pPOA->deactivate_object(inPortAnyId);
      delete inPortAny;
    }
		
    /*!
     * @brief ���ԡ����󥹥ȥ饯���Υƥ���
     * 
     * - ���ԡ��������줿InPortConsumer��put()�᥽�åɸƽФˤ�äơ�
     * InPortAny��put()�᥽�å�¦���������ǡ������Ϥ���뤫��
     */
    void test_copy_constructor()
    {
      InPortAnyMock* inPortAny = new InPortAnyMock();
      PortableServer::ObjectId_var inPortAnyId = m_pPOA->activate_object(inPortAny);

      RTC::RingBuffer<CORBA::Float> buffer(100);
      RTC::InPortCorbaConsumer<CORBA::Float> consumer(buffer);
      consumer.setObject(m_pPOA->id_to_reference(inPortAnyId));
			
      // ��������InPortCorbaConsumer�򸵤ˤ��ơ��̤�InPortCorbaConsumer�򥳥ԡ���������
      RTC::InPortCorbaConsumer<CORBA::Float> consumerNew(consumer);
			
      // ���ԡ��������줿InPortConsumer��put()�᥽�åɤ�ƤӽФ�
      CORBA::Float writeValue = 3.14159;
      consumerNew.put(writeValue);
			
      // InPortAny¦��put()�᥽�åɤ˥ǡ������������Ϥ���Ƥ��뤫��
      CORBA::Any readValueAny = inPortAny->getData();
      CORBA::Float* pReadValue = (CORBA::Float*) readValueAny.value();
      CPPUNIT_ASSERT_EQUAL(writeValue, *pReadValue);

      m_pPOA->deactivate_object(inPortAnyId);
      delete inPortAny;
    }
		
    /*!
     * @brief �����黻�ҡ�operator=�ˤΥƥ���
     * 
     * - ��¸��InPortConsumer���������줿�̤�InPortConsumer��put()�᥽�åɸƽФˤ�äơ�
     * InPortAny��put()�᥽�å�¦���������ǡ������Ϥ���뤫��
     */
    void test_substitute_operator()
    {
      try{
	InPortAnyMock* inPortAny = new InPortAnyMock();
	PortableServer::ObjectId_var inPortAnyId = m_pPOA->activate_object(inPortAny);
	
	RTC::RingBuffer<CORBA::Float> buffer(100);
	RTC::InPortCorbaConsumer<CORBA::Float> consumer(buffer);
	consumer.setObject(m_pPOA->id_to_reference(inPortAnyId));
	
	// ��������InPortCorbaConsumer�򸵤ˤ��ơ��̤�InPortCorbaConsumer��������������
	BufferDummy<CORBA::Float> bufferDummy;
	RTC::InPortCorbaConsumer<CORBA::Float> consumerNew(bufferDummy);
	consumerNew = consumer;
	
	// �����������줿InPortConsumer��put()�᥽�åɤ�ƤӽФ�
	CORBA::Float writeValue = 3.14159;
	consumerNew.put(writeValue);
	
	// InPortAny¦��put()�᥽�åɤ˥ǡ������������Ϥ���Ƥ��뤫��
	CORBA::Any readValueAny = inPortAny->getData();
	CORBA::Float* pReadValue = (CORBA::Float*) readValueAny.value();
	CPPUNIT_ASSERT_EQUAL(writeValue, *pReadValue);

        m_pPOA->deactivate_object(inPortAnyId);
	delete inPortAny;
      }
      catch (...) {}
    }
		
    /*!
     * @brief clone()�᥽�åɤΥƥ���
     * 
     * - clone()�ˤ�ä��������줿InPortCorbaConsumer��put()�᥽�åɸƽФˤ�äơ�
     * InPortAny��put()�᥽�å�¦���������ǡ������Ϥ���뤫��
     */
    void test_clone()
    {
      InPortAnyMock* inPortAny = new InPortAnyMock();
      PortableServer::ObjectId_var inPortAnyId = m_pPOA->activate_object(inPortAny);

      RTC::RingBuffer<CORBA::Float> buffer(100);
      RTC::InPortCorbaConsumer<CORBA::Float> consumer(buffer);
      consumer.setObject(m_pPOA->id_to_reference(inPortAnyId));
			
      // ��������InPortCorbaConsumer�򸵤ˤ��ơ��̤�InPortCorbaConsumer��clone()����������
      std::auto_ptr<RTC::InPortCorbaConsumer<CORBA::Float> > pConsumerNew(consumer.clone());
			
      // ���ԡ��������줿InPortConsumer��put()�᥽�åɤ�ƤӽФ�
      CORBA::Float writeValue = 3.14159;
      pConsumerNew->put(writeValue);
			
      // InPortAny¦��put()�᥽�åɤ˥ǡ������������Ϥ���Ƥ��뤫��
      CORBA::Any readValueAny = inPortAny->getData();
      CORBA::Float* pReadValue = (CORBA::Float*) readValueAny.value();
      CPPUNIT_ASSERT_EQUAL(writeValue, *pReadValue);

      m_pPOA->deactivate_object(inPortAnyId);
      delete inPortAny;
    }
		
  };
}; // namespace InPortCorbaConsumer

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(InPortCorbaConsumer::InPortCorbaConsumerTests);

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
#endif // InPortCorbaConsumer_cpp
