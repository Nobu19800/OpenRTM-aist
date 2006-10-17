// -*- C++ -*-
/*!
 * @file RtcNaming.h
 * @brief naming Service helper class
 * @date $Date: 2006-10-17 10:14:52 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcNaming.h,v 1.4 2006-10-17 10:14:52 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2006/09/11 18:26:20  n-ando
 * RtcNaming class was completely rewritten.
 * - Now RtcCorbaNaming is a wrapper of CosNaming::NamingContext
 *   and CosNaming::NamingContextExt with fixed root context.
 * - find() method is separated from this class.
 * - This class constructor connects to the NameServer without using
 *   resolve_initial_reference().
 *
 * Revision 1.2  2005/05/16 06:29:05  n-ando
 * - RtcNaming class was DLL exported for Windows port.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */


#ifndef RtcNaming_h
#define RtcNaming_h

// CORBA header include
//#include "rtm/idl/RTMBaseStub.h"
//#include "rtm/idl/RTMBaseSkel.h"
//#include "rtm/RtcBase.h"
#include "rtm/RTC.h"
#ifdef ORB_IS_OMNIORB
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#include "omniORB4/CORBA.h"
//#include "omniORB4/Naming.h"
#endif

// STL includes
#include <map>
#include <string>
#include <vector>

namespace RTM
{

  class RtcCorbaNaming
  {
  public:
    RtcCorbaNaming(CORBA::ORB_ptr orb, const char* name_server);
    virtual ~RtcCorbaNaming(){};

    typedef CosNaming::NamingContext::NotFound      NotFound;
    typedef CosNaming::NamingContext::CannotProceed CannotProceed;
    typedef CosNaming::NamingContext::InvalidName   InvalidName;
    typedef CosNaming::NamingContext::AlreadyBound  AlreadyBound;
    typedef CosNaming::NamingContext::NotEmpty      NotEmpty;
    typedef CosNaming::NamingContextExt::InvalidAddress InvalidAddress;
    typedef std::vector<CORBA::Object_ptr> ObjectList;

    /*!
     * @if jp
     *
     * @brief Object �� bind ����
     *
     * CosNaming::bind() �Ȥۤ�Ʊ����Ư���򤹤뤬�����Ϳ����줿�͡��ॵ���Ф�
     * �롼�ȥ���ƥ����Ȥ��Ф���bind()���ƤӽФ���������ۤʤ롣
     *
     * Name <name> �� Object <obj> ������ NamingContext ��˥Х���ɤ��롣
     * c_n �� n ���ܤ� NameComponent �򤢤�魯�Ȥ���ȡ�
     * name �� n �Ĥ� NameComponent ��������Ȥ����ʲ��Τ褦�˰����롣
     *
     * cxt->bind(<c_1, c_2, ... c_n>, obj) �ϰʲ�������Ʊ���Ǥ��롣
     * cxt->resolve(<c_1, ... c_(n-1)>)->bind(<c_n>, obj)
     *
     * ���ʤ����1���ܤ���n-1���ܤΥ���ƥ����Ȥ��褷��n-1���ܤΥ���ƥ�����
     * ��� name <n> �Ȥ��ơ�obj �� bind ���롣
     * ̾�����˻��ä��� <c_1, ... c_(n-1)> �� NemingContext �ϡ�
     * bindContext() �� rebindContext() �Ǵ��˥Х���ɺѤߤǤʤ���Фʤ�ʤ���
     * �⤷ <c_1, ... c_(n-1)> �� NamingContext ��¸�ߤ��ʤ����ˤϡ�
     * NotFound �㳰��ȯ�����롣
     *
     * �������������Х���ɥե饰 force �� true �λ��ϡ�<c_1, ... c_(n-1)>
     * ��¸�ߤ��ʤ����ˤ⡢�Ƶ�Ū�˥���ƥ����Ȥ�Х���ɤ��ʤ��顢
     * �ǽ�Ū�� obj ��̾�� name <c_n> �˥Х���ɤ��롣
     *
     * ������ξ��Ǥ⡢n-1���ܤΥ���ƥ����Ⱦ�� name<n> �Υ��֥�������
     * (Object ���뤤�� ����ƥ�����) ���Х���ɤ���Ƥ����
     * AlreadyBound �㳰��ȯ�����롣
     *
     * @param name ���֥������Ȥ��դ���̾���� NameComponent
     * @param obj ��Ϣ�դ����� Object
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     * @exception AlreadyBound name <c_n> �� Object �����Ǥ˥Х���ɤ���Ƥ��롣
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bind(const CosNaming::Name& name, CORBA::Object_ptr obj,
	      const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);


    /*!
     * @if jp
     *
     * @brief Object �� bind ����
     *
     * Object �� bind ����ݤ�Ϳ����̾����ʸ����ɽ���Ǥ��뤳�Ȱʳ��ϡ�bind()
     * ��Ʊ���Ǥ��롣bind(toName(string_name), obj) ��������
     *
     * @param string_name ���֥������Ȥ��դ���̾����ʸ����ɽ��
     * @param obj ��Ϣ�դ����륪�֥�������
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     * @exception AlreadyBound name <n> �� Object �����Ǥ˥Х���ɤ���Ƥ��롣
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindByString(const char* string_name, CORBA::Object_ptr obj,
		      const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief ����Υ���ƥ����Ȥ� bind ���ʤ��� Object �� bind ����
     *
     * context ��Ϳ����줿 NamingContext ���Ф��ơ�name �ǻ��ꤵ�줿
     * �͡��ॳ��ݡ��ͥ�� <c_1, ... c_(n-1)> �� NamingContext �Ȥ���
     * ��褷�ʤ��顢̾�� <c_n> ���Ф��� obj �� bind ���롣
     * �⤷��<c_1, ... c_(n-1)> ���б����� NamingContext ���ʤ����ˤ�
     * ������ NamingContext ��Х���ɤ��롣
     *
     * �ǽ�Ū�� <c_1, c_2, ..., c_(n-1)> ���б����� NamingContext ������
     * �ޤ��ϲ�褵�줿��ǡ�CosNaming::bind(<c_n>, object) ���ƤӽФ���롣
     * ���ΤȤ������Ǥ˥Х���ǥ��󥰤�¸�ߤ���� AlreadyBound�㳰��ȯ�����롣
     *
     * ����Υ���ƥ����Ȥ��褹������ǡ���褷�褦�Ȥ��륳��ƥ����Ȥ�
     * Ʊ��̾���� NamingContext �ǤϤʤ� Binding ��¸�ߤ����硢
     * CannotProceed �㳰��ȯ������������ߤ��롣
     *
     * @param context bind �򳫻Ϥ��롡NamingContext
     * @param name ���֥������Ȥ��դ���̾���Υ͡��ॳ��ݡ��ͥ��
     * @param obj ��Ϣ�դ����륪�֥�������
     *
     * @exception CannotProceed <c_1, ..., c_(n-1)> ���б����� NamingContext 
     *            �Τ����ҤȤĤ������Ǥ� NamingContext �ʳ��� object �˥Х����
     *            ����Ƥ��ꡢ�������³�Ǥ��ʤ���
     * @exception InvalidName ̾�� name ������
     * @exception AlreadyBound name <c_n> �ˤ��Ǥ˲��餫�� object ���Х����
     *            ����Ƥ��롣
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindRecursive(CosNaming::NamingContext_ptr context,
		       const CosNaming::Name& name,
		       CORBA::Object_ptr obj)
      throw(CannotProceed, InvalidName, AlreadyBound);



    /*!
     * @if jp
     *
     * @brief Object �� rebind ����
     *
     * name �ǻ��ꤵ�줿 Binding �����Ǥ�¸�ߤ����������� bind() ��Ʊ��
     * �Ǥ��롣�Х���ǥ��󥰤����Ǥ�¸�ߤ�����ˤϡ��������Х���ǥ��󥰤�
     * �֤��������롣
     *
     * @param name ���֥������Ȥ��դ���̾���� NameComponent
     * @param obj ��Ϣ�դ����륪�֥�������
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebind(const CosNaming::Name& name, CORBA::Object_ptr obj,
		const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);


    /*!
     * @if jp
     *
     * @brief Object �� rebind ����
     *
     * Object �� rebind ����ݤ�Ϳ����̾����ʸ����ɽ���Ǥ��뤳�Ȱʳ��� rebind()
     * ��Ʊ���Ǥ��롣rebind(toName(string_name), obj) ��������
     *
     * @param string_name ���֥������Ȥ��դ���̾����ʸ����ɽ��
     * @param obj ��Ϣ�դ����륪�֥�������
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *
     * @exception NotFound ����� <c_1, c_2, ..., c_(n-1)> ��¸�ߤ��ʤ���
     * @exception CannotProceed ���餫����ͳ�ǽ������³�Ǥ��ʤ���
     * @exception InvalidName ���� name ��̾����������
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindByString(const char* string_name, CORBA::Object_ptr obj,
			const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);

    
    /*!
     * @if jp
     *
     * @brief ����Υ���ƥ����Ȥ� bind ���ʤ��� Object �� rebind ����
     *
     * name <c_n> �ǻ��ꤵ�줿 NamingContext �⤷���� Object �����Ǥ�¸�ߤ���
     * ��������� bindRecursive() ��Ʊ���Ǥ��롣
     *
     * name <c_n> �ǻ��ꤵ�줿�Х���ǥ��󥰤����Ǥ�¸�ߤ�����ˤϡ�
     * �������Х���ǥ��󥰤��֤��������롣
     *
     * @param name ���֥������Ȥ��դ���̾����ʸ����ɽ��
     * @param obj ��Ϣ�դ����륪�֥�������
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *
     * @exception CannotProceed ����Υ���ƥ����Ȥ����Ǥ��ʤ���
     * @exception InvalidName Ϳ����줿 name ��������
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindRecursive(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name,
			 CORBA::Object_ptr obj)
      throw(CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief NamingContext �� bind ����
     *
     * bind ����륪�֥������Ȥ� NamingContext �Ǥ��뤳�Ȥ������ bind() 
     * ��Ʊ���Ǥ��롣
     *
     * @param name ���֥������Ȥ��դ���̾���Υ͡��ॳ��ݡ��ͥ��
     * @param name_cxt ��Ϣ�դ����� NamingContext
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindContext(const CosNaming::Name& name,
		     CosNaming::NamingContext_ptr name_cxt,
		     const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief NamingContext �� bind ����
     *
     * bind ����륪�֥������Ȥ� NamingContext �Ǥ��뤳�Ȥ������ bind() 
     * ��Ʊ���Ǥ��롣
     *
     * @param name ���֥������Ȥ��դ���̾����ʸ����ɽ��
     * @param name_cxt ��Ϣ�դ����� NamingContext
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindContext(const char* string_name,
		     CosNaming::NamingContext_ptr name_cxt,
		     const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief NamingContext �� bind ����
     *
     * bind ����륪�֥������Ȥ� NamingContext �Ǥ��뤳�Ȥ������
     * bindRecursive() ��Ʊ���Ǥ��롣
     *
     * @param context bind �򳫻Ϥ��롡NamingContext
     * @param name ���֥������Ȥ��դ���̾���Υ͡��ॳ��ݡ��ͥ��
     * @param name_cxt ��Ϣ�դ����� NamingContext
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindContextRecursive(CosNaming::NamingContext_ptr context,
			      const CosNaming::Name& name,
			      CosNaming::NamingContext_ptr name_cxt);
    /*!
     * @if jp
     *
     * @brief NamingContext �� rebind ����
     *
     * name �ǻ��ꤵ�줿����ƥ����Ȥ����Ǥ�¸�ߤ����������� bindContext() 
     * ��Ʊ���Ǥ��롣
     * �Х���ǥ��󥰤����Ǥ�¸�ߤ�����ˤϡ��������Х���ǥ��󥰤�
     * �֤��������롣
     *
     * @param name ���֥������Ȥ��դ���̾���Υ͡��ॳ��ݡ��ͥ��
     * @param name_cxt ��Ϣ�դ����� NamingContext
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindContext(const CosNaming::Name& name,
		       CosNaming::NamingContext_ptr name_cxt,
		       const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief NamingContext �� rebind ����
     *
     * name �ǻ��ꤵ�줿����ƥ����Ȥ����Ǥ�¸�ߤ����������� bindContext() 
     * ��Ʊ���Ǥ��롣
     * �Х���ǥ��󥰤����Ǥ�¸�ߤ�����ˤϡ��������Х���ǥ��󥰤�
     * �֤��������롣
     *
     * @param name ���֥������Ȥ��դ���̾����ʸ����ɽ��
     * @param name_cxt ��Ϣ�դ����� NamingContext
     * @param force true�ξ�硢����Υ���ƥ����Ȥ���Ū�˥Х���ɤ���
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindContext(const char* string_name,
		       CosNaming::NamingContext_ptr name_cxt,
		       const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);


    void rebindContextRecursive(CosNaming::NamingContext_ptr context,
				const CosNaming::Name& name,
				CosNaming::NamingContext_ptr name_cxt);

    /*!
     * @if jp
     *
     * @brief Object �� name �����褹��
     *
     * name �� bind ����Ƥ��륪�֥������Ȼ��Ȥ��֤���
     * �͡��ॳ��ݡ��ͥ�� <c_1, c_2, ... c_n> �ϺƵ�Ū�˲�褵��롣
     * 
     * CosNaming::resolve() �Ȥۤ�Ʊ����Ư���򤹤뤬�����Ϳ����줿
     * �͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ��Ф��� resolve() ���ƤӽФ��������
     * �ۤʤ롣
     *
     * @param name ��褹�٤����֥������Ȥ�̾���Υ͡��ॳ��ݡ��ͥ��
     * @return ��褵�줿���֥������Ȼ���
     *
     * @else
     *
     * @endif
     */
    CORBA::Object_ptr resolve(const CosNaming::Name& name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief Object �� name �����褹��
     *
     * name �� bind ����Ƥ��륪�֥������Ȼ��Ȥ��֤���
     * �͡��ॳ��ݡ��ͥ�� <c_1, c_2, ... c_n> �ϺƵ�Ū�˲�褵��롣
     * 
     * CosNaming::resolve() �Ȥۤ�Ʊ����Ư���򤹤뤬�����Ϳ����줿
     * �͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ��Ф��� resolve() ���ƤӽФ��������
     * �ۤʤ롣
     *
     * @param name ��褹�٤����֥������Ȥ�̾����ʸ����ɽ��
     * @return ��褵�줿���֥������Ȼ���
     *
     * @else
     *
     * @endif
     */
    CORBA::Object_ptr resolve(const char* string_name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief ���ꤵ�줿̾���Υ��֥������Ȥ� bind ��������
     *
     * name �� bind ����Ƥ��륪�֥������Ȼ��Ȥ��֤���
     * �͡��ॳ��ݡ��ͥ�� <c_1, c_2, ... c_n> �ϺƵ�Ū�˲�褵��롣
     * 
     * CosNaming::unbind() �Ȥۤ�Ʊ����Ư���򤹤뤬�����Ϳ����줿
     * �͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ��Ф��� unbind() ���ƤӽФ��������
     * �ۤʤ롣
     *
     * @param name ��褹�٤����֥������Ȥ�̾���Υ͡��ॳ��ݡ��ͥ��
     * @return ��褵�줿���֥������Ȼ���
     *
     * @else
     *
     * @endif
     */
    void unbind(const CosNaming::Name& name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief ���ꤵ�줿̾���Υ��֥������Ȥ� bind ��������
     *
     * name �� bind ����Ƥ��륪�֥������Ȼ��Ȥ��֤���
     * �͡��ॳ��ݡ��ͥ�� <c_1, c_2, ... c_n> �ϺƵ�Ū�˲�褵��롣
     * 
     * CosNaming::unbind() �Ȥۤ�Ʊ����Ư���򤹤뤬�����Ϳ����줿
     * �͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ��Ф��� unbind() ���ƤӽФ��������
     * �ۤʤ롣
     *
     * @param name ��褹�٤����֥������Ȥ�̾����ʸ����ɽ��
     * @return ��褵�줿���֥������Ȼ���
     *
     * @else
     *
     * @endif
     */
    void unbind(const char* string_name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief ����������ƥ����Ȥ���������
     *
     * Ϳ����줿�͡��ॵ���о���������줿 NamingContext ���֤���
     * �֤��줿 NamingContext �� bind ����Ƥ��ʤ���
     * 
     * @return �������줿������ NamingContext
     *
     * @else
     *
     * @endif
     */
    CosNaming::NamingContext_ptr newContext();

    /*!
     * @if jp
     *
     * @brief ����������ƥ����Ȥ� bind ����
     *
     * Ϳ����줿 name ���Ф��ƿ���������ƥ����Ȥ�Х���ɤ��롣
     * �������줿��NamingContext �ϥ͡��ॵ���о���������줿��ΤǤ��롣
     * 
     * @param name NamingContext���դ���̾���Υ͡��ॳ��ݡ��ͥ��
     * @return �������줿������ NamingContext
     *
     * @else
     *
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindNewContext(const CosNaming::Name& name, bool force = true)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief ����������ƥ����Ȥ� bind ����
     *
     * Ϳ����줿 name ���Ф��ƿ���������ƥ����Ȥ�Х���ɤ��롣
     * �������줿��NamingContext �ϥ͡��ॵ���о���������줿��ΤǤ��롣
     * 
     * @param name NamingContext���դ���̾����ʸ����ɽ��
     * @return �������줿������ NamingContext
     *
     * @else
     *
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindNewContext(const char* string_name, bool force = true)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief NamingContext ���󥢥��ƥ��ֲ�����
     *
     * context �ǻ��ꤵ�줿 NamingContext ���󥢥��ƥ��ֲ����롣
     * context ��¾�Υ���ƥ����Ȥ��Х���ɤ���Ƥ������ NotEmpty �㳰��
     * ȯ�����롣
     * 
     * @param context �󥢥��ƥ��ֲ����� NamingContext
     *
     * @else
     *
     * @brief Destroy the naming context
     *
     * Delete the specified naming context.
     * any bindings should be <unbind> in which the given context is bound to
     * some names before invoking <destroy> operation on it. 
     *
     * @param context NamingContext which is destroied.
     *     
     * @endif
     */
    void destroy(CosNaming::NamingContext_ptr context)
      throw(NotEmpty);


    /*!
     * @if jp
     * @brief NamingContext ��Ƶ�Ū�˲��ä��󥢥��ƥ��ֲ�����
     * @else
     * @brief Destroy the naming context recursively
     * @endif
     */
    void destroyRecursive(CosNaming::NamingContext_ptr context)
      throw(NotEmpty, NotFound, CannotProceed, InvalidName);


    /*!
     * @if jp
     * @brief ���٤Ƥ� Binding ��������
     * @else
     * @brief Destroy all binding
     * @endif
     */
    void clearAll();


    /*!
     * @if jp
     * @brief Ϳ����줿 NamingContext �� Binding ���������
     * @else
     * @brief Get Binding on the NamingContextDestroy all binding
     * @endif
     */
    void list(CosNaming::NamingContext_ptr name_cxt,
	      unsigned long how_many,
	      CosNaming::BindingList_var& bl,
	      CosNaming::BindingIterator_var& bi);


    //============================================================
    // interface of NamingContextExt
    //============================================================
    /*!
     * @if jp
     * @brief Ϳ����줿 NameComponent ��ʸ����ɽ�����֤�
     * @else
     * @brief Get string representation of given NameComponent
     * @endif
     */
    char* toString(const CosNaming::Name& name)
      throw(InvalidName);
    

    /*!
     * @if jp
     * @brief Ϳ����줿ʸ����ɽ���� NameComponent ��ʬ�򤹤�
     * @else
     * @brief Get NameComponent from gien string name representation
     * @endif
     */
    CosNaming::Name toName(const char* string_name)
      throw(InvalidName);


    /*!
     * @if jp
     * @brief Ϳ����줿 addre �� string_name ���� URLɽ�����������
     * @else
     * @brief Get URL representation from given addr and string_name
     * @endif
     */
    char* toUrl(char* addr, char* string_name)
      throw(InvalidAddress, InvalidName);


    /*!
     * @if jp
     * @brief Ϳ����줿ʸ����ɽ���� resolve �����֥������Ȥ��֤�
     * @else
     * @brief Resolve from name of string representation and get object 
     * @endif
     */
    CORBA::Object_ptr resolveStr(const char* string_name)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);


    //============================================================
    // Find functions
    //============================================================

    //    ObjectList find(const char* name, const char* kind);
    //    ObjectList findById(const char* name, const char* kind);
    //    ObjectList findByKind(const char* name, const char* kind);


    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    const char* getNameServer();
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::NamingContext_ptr getRootContext();

    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    bool isNamingContext(CORBA::Object_ptr obj);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    bool isNamingContext(const CosNaming::Name& name);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    bool isNamingContext(const char* string_name);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::Name subName(const CosNaming::Name& name,
			    long begin,
			    long end = -1);

    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CORBA::Object_ptr bindOrResolve(CosNaming::NamingContext_ptr context,
				    const CosNaming::Name& name,
				    CORBA::Object_ptr obj);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindOrResolveContext(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name,
			 CosNaming::NamingContext_ptr new_context);

    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindOrResolveContext(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name);


  protected:
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CORBA::ULong getNameLength(const CosNaming::Name& name);

    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    void nameToString(const CosNaming::Name& name, char* string_name,
		      unsigned long slen);
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    unsigned int split(const std::string& input,
		       const std::string& delimiter,
		       std::vector<std::string>& results);
    
    CORBA::ORB_var m_varORB;
    std::string m_nameServer;
    CosNaming::NamingContextExt_var m_rootContext;

  private:
    CORBA::ULong m_blLength;
    
  };

}; // end of namespace RTM

#endif // end of __RtcNaming_h__
