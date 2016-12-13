// -*- C++ -*-
/*!
 * @file CorbaNaming.h
 * @brief CORBA naming service helper class
 * @date $Date: 2006-11-04 19:43:01 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: CorbaNaming.h,v 1.1 2006-11-04 19:43:01 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */


#ifndef CorbaNaming_h
#define CorbaNaming_h

#include <rtm/RTC.h>
#ifdef ORB_IS_OMNIORB
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#include <omniORB4/CORBA.h>
#endif

// STL includes
#include <map>
#include <string>
#include <vector>

namespace RTC
{
  /*!
   * @if jp
   * @class CorbaNaming
   * @brief CORBA Naming Service �إ�ѡ����饹
   *
   * ���Υ��饹�ϡ�CosNaming::NamingContext ���Ф����åѡ����饹�Ǥ��롣
   * CosNaming::NamingContext �����ĥ��ڥ졼�����Ȥۤ�Ʊ����ǽ��
   * ���ڥ졼�������󶡤���ȤȤ�ˡ��͡��ॳ��ݡ��ͥ�� CosNaming::Name
   * �������ʸ����ˤ��̾��ɽ��������դ��륪�ڥ졼�������󶡤��롣
   *
   * ���֥������Ȥ������������뤤������ľ��� CORBA �͡��ॵ���Ф���³��
   * �ʸ塢���Υ͡��ॵ���ФΥ롼�ȥ���ƥ����Ȥ��Ф��Ƽ�Υ��ڥ졼�����
   * ��������롣
   * �������ؤΥ͡��ߥ󥰥���ƥ����Ȥκ����䥪�֥������ȤΥХ���ɤˤ����ơ�
   * ����Υ���ƥ����Ȥ�¸�ߤ��ʤ����Ǥ⡢����Ū�˥���ƥ����Ȥ�Х����
   * ����Ū�Υ���ƥ����Ȥ䥪�֥������ȤΥХ���ɤ�Ԥ����Ȥ�Ǥ��롣
   *
   * @else
   * @class CorbaNaming
   * @brief CORBA Naming Service helper class
   *
   * This class is a wrapper class of CosNaming::NamingContext.
   * Almost the same operations which CosNaming::NamingContext has are
   * provided, and some operation allows string naming representation of
   * context and object instead of CosNaming::Name.
   *
   * The object of the class would connect to a CORBA naming server at
   * the instantiation or immediately after instantiation.
   * After that the object invokes operations to the root context of it.
   * This class realizes forced binding to deep NamingContext, without binding
   * intermediate NamingContexts explicitly.
   *
   * @endif
   */
  class CorbaNaming
  {
  public:
    CorbaNaming(CORBA::ORB_ptr orb);
    CorbaNaming(CORBA::ORB_ptr orb, const char* name_server);
    virtual ~CorbaNaming(){};
    void init(const char* name_server);

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
     * @brief ̾����Х���ɤޤ��ϲ�褹��
     * @else
     * @brief Bind of resolve the given name component
     * @endif
     */
    CORBA::Object_ptr bindOrResolve(CosNaming::NamingContext_ptr context,
				    const CosNaming::Name& name,
				    CORBA::Object_ptr obj);
    
    /*!
     * @if jp
     * @brief ̾����Х���ɤޤ��ϲ�褹��
     * @else
     * @brief Bind of resolve the given name component
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindOrResolveContext(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name,
			 CosNaming::NamingContext_ptr new_context);

    
    /*!
     * @if jp
     * @brief ̾����Х���ɤޤ��ϲ�褹��
     * @else
     * @brief Bind of resolve the given name component
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindOrResolveContext(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name);


    /*!
     * @if jp
     * @brief �͡��ॵ���Ф�̾�����������
     * @else
     * @brief Get the name of naming server
     * @endif
     */
    const char* getNameServer();
    
    /*!
     * @if jp
     * @brief �롼�ȥ���ƥ����Ȥ��������
     * @else
     * @brief Get the root context
     * @endif
     */
    CosNaming::NamingContext_ptr getRootContext();

    
    /*!
     * @if jp
     * @brief ���֥������Ȥ��͡��ߥ󥰥���ƥ����Ȥ�Ƚ�̤���
     * @else
     * @brief Whether the object is NamingContext
     * @endif
     */
    bool isNamingContext(CORBA::Object_ptr obj);
    
    /*!
     * @if jp
     * @brief Ϳ����줿̾�����͡��ߥ󥰥���ƥ����Ȥ��ɤ���
     * @else
     * @brief Whether the given name component is NamingContext
     * @endif
     */
    bool isNamingContext(const CosNaming::Name& name);
    
    /*!
     * @if jp
     * @brief Ϳ����줿̾�����͡��ߥ󥰥���ƥ����Ȥ��ɤ���
     * @else
     * @brief Whether the given string name is NamingContext
     * @endif
     */
    bool isNamingContext(const char* string_name);
    
    /*!
     * @if jp
     * @brief �͡��ॳ��ݡ��ͥ�Ȥ���ʬ���֤�
     * @else
     * @brief Get subset of given name component
     * @endif
     */
    CosNaming::Name subName(const CosNaming::Name& name,
			    long begin,
			    long end = -1);


  protected:
    /*!
     * @if jp
     * @brief �͡��ॳ��ݡ��ͥ�Ȥ�ʸ����ɽ�����������
     * @else
     * @brief Get string representation of name component
     * @endif
     */
    void nameToString(const CosNaming::Name& name, char* string_name,
		      unsigned long slen);
    /*!
     * @if jp
     * @brief �͡��ॳ��ݡ��ͥ�Ȥ�ʸ����ɽ������ʸ��Ĺ���������
     * @else
     * @brief Get string length of the name component's string representation
     * @endif
     */
    CORBA::ULong getNameLength(const CosNaming::Name& name);

    /*!
     * @if jp
     * @brief ʸ�����ʬ��
     * @else
     * @brief Split of string
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
    
  }; // class CorbaNaming

}; // namespace RTC

#endif // end of __Naming_h__
